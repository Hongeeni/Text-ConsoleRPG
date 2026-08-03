#include "Dungeon.h"
#include "Player.h"
#include "Monster.h"
#include "MonsterData.h"
#include "combat.h"
#include "Shop.h"
#include "Inventory.h"

#include <iostream>
#include <algorithm>
#include <numeric>
#include <array>
#include <vector>

namespace {
    // DungeonType(0,1,2)과 MonsterGroup(1,2,3)은 값이 달라서 직접 변환
    MonsterGroup ToMonsterGroup(DungeonType type) {
        switch (type) {
        case DungeonType::Slime:  return MonsterGroup::Slime;
        case DungeonType::Undead: return MonsterGroup::Undead;
        case DungeonType::Golem:  return MonsterGroup::Golem;
        }
        return MonsterGroup::Slime;
    }

    Monster MakeMonster(const MonsterData& data) {
        return Monster(data.group, data.name, data.hp, data.attack, data.defence, data.speed,
            data.dropName, data.dropCategory, data.dropGold,
            data.rewardExp, data.isBoss);
    }
}

Dungeon::Dungeon(DungeonType type) : type_(type) {}

// 던전 타입별 클리어 여부 저장 (인덱스 = static_cast<int>(DungeonType))
std::array<bool, 3> Dungeon::s_cleared{};

bool Dungeon::IsCleared(DungeonType type) {
    return s_cleared[static_cast<int>(type)];
}

bool Dungeon::IsBossFound() const {
    return bossFound_;
}

bool Dungeon::IsExitRequested() const {
    return exitRequested_;
}

// ---- 제단 (발견과 발동이 분리되어 있다) ----

bool Dungeon::IsAltarPending() const {
    return altarPending_;
}

AltarResult Dungeon::TouchAltar(Player& player) {
    if (!altarPending_) {
        return AltarResult{};   // 제단 앞이 아니면 아무 일도 없음
    }
    altarPending_ = false;
    return AltarEvent::Trigger(player);
}

void Dungeon::SkipAltar() {
    altarPending_ = false;
}

bool Dungeon::IsPlayerAlive(Player& player) const {
    return player.GetCurrentHp() > 0;
}

std::string Dungeon::GetName() const {
    switch (type_) {
    case DungeonType::Slime:  return "슬라임 던전";
    case DungeonType::Undead: return "언데드 던전";
    case DungeonType::Golem:  return "골렘 던전";
    }
    return "알 수 없는 던전";
}

std::string Dungeon::GetShopName() const {
    switch (type_) {
    case DungeonType::Slime:  return "슬라임 상인";
    case DungeonType::Undead: return "언데드 상인";
    case DungeonType::Golem:  return "골렘 상인";
    }
    return "일반 상점";
}

// ---- 입력 수신 전용 ----

int Dungeon::ReadIntInput() {
    int value = 0;
    std::cin >> value;
    return value;
}

std::string Dungeon::ReadLineInput() {
    std::string value;
    std::cin >> value;
    return value;
}

// ---- 몬스터 선택 ----

Monster Dungeon::PickBoss() const {
    const MonsterGroup group = ToMonsterGroup(type_);

    for (const auto& data : MonsterList()) {
        if (data.group == group && data.isBoss) {
            return MakeMonster(data);
        }
    }
    return MakeMonster(MonsterList()[0]);   // 데이터 누락 방어
}

Monster Dungeon::PickNormalMonster() {
    const MonsterGroup group = ToMonsterGroup(type_);

    std::vector<MonsterData> candidates;
    for (const auto& data : MonsterList()) {
        if (data.group == group && !data.isBoss) {
            candidates.push_back(data);
        }
    }
    if (candidates.empty()) {
        return MakeMonster(MonsterList()[0]);
    }

    std::uniform_int_distribution<int> pick(0, static_cast<int>(candidates.size()) - 1);
    return MakeMonster(candidates[pick(rng_)]);
}

// ---- 전투 ----

MonsterFightResult Dungeon::FightMonster(Player& player, Monster& monster) {
    MonsterFightResult result;
    result.monsterName = monster.GetName();

    CombatSystem combat(player, monster);
    combat.StartBattle();

    if (!monster.IsAlive()) {
        result.monsterDefeated = true;
        result.dropName = monster.GetDropName();
        AddItem(g_player_inventory, monster.GetDropName(), 1);
    }
    return result;
}

// ---- 이벤트 진행 ----

DungeonEvent Dungeon::RollEvent() {
    const bool canFindBoss = !bossFound_ && !IsCleared(type_);

    std::vector<double> weights = {
        60.0,                        // Monster
        8.0,                        // Treasure
        8.0,                        // Shop
        8.0,                        // Altar
        8.0,                        // Fountain
        canFindBoss ? 8.0 : 0.0     // BossFound
    };
    std::discrete_distribution<int> dist(weights.begin(), weights.end());
    return static_cast<DungeonEvent>(dist(rng_));
}

AdvanceResult Dungeon::Resolve(DungeonEvent e, Player& player) {
    AdvanceResult result;
    result.event = e;

    switch (e) {
    case DungeonEvent::Monster: {
        Monster monster = PickNormalMonster();
        result.monster = FightMonster(player, monster);
        if (!IsPlayerAlive(player)) {
            result.playerDefeated = true;
            result.defeat = OnDefeat(player);
        }
        break;
    }
    case DungeonEvent::Treasure:
        result.treasure = TreasureRoomEvent::Trigger(player, type_);
        break;
    case DungeonEvent::Shop:
        ViewShop(GetShopName(), GetShopName(), player);
        break;
    case DungeonEvent::Altar:
        // game.cpp가 "만진다/지나친다" 선택을 받은 뒤 TouchAltar() / SkipAltar()를 호출한다.
        altarPending_ = true;
        break;
    case DungeonEvent::Fountain:
        result.fountain = FountainEvent::Trigger(player);
        break;
    case DungeonEvent::BossFound:
        bossFound_ = true;
        break;
    }
    return result;
}

AdvanceResult Dungeon::Advance(Player& player) {
    // 이전 제단에서 선택을 안 하고 넘어왔으면 지나친 것으로 처리한다
    altarPending_ = false;
    return Resolve(RollEvent(), player);
}

EscapeResult Dungeon::TryEscape(Player& player) {
    EscapeResult result;

    std::bernoulli_distribution fail(escapeFailPercent_ / 100.0);
    if (fail(rng_)) {
        result.success = false;

        Monster monster = PickNormalMonster();   // 탈출 실패는 항상 일반 몬스터
        result.monster = FightMonster(player, monster);

        if (!IsPlayerAlive(player)) {
            result.playerDefeated = true;
            result.defeat = OnDefeat(player);
        }
        return result;
    }

    result.success = true;
    exitRequested_ = true;
    return result;
}

// ---- 보스방 ----

std::string Dungeon::GetBossRoomAnswer() const {
    switch (type_) {
    case DungeonType::Slime:  return "김동현";
    case DungeonType::Undead: return "문승호";
    case DungeonType::Golem:  return "손승현";
    }
    return "";
}

BossRoomResult Dungeon::EnterBossRoom(const std::string& answer, Player& player) {
    BossRoomResult result;

    if (IsCleared(type_)) {
        result.alreadyCleared = true;
        return result;
    }

    result.correctAnswer = (answer == GetBossRoomAnswer());
    if (!result.correctAnswer) {
        return result;
    }

    Monster boss = PickBoss();
    result.monster = FightMonster(player, boss);

    if (IsPlayerAlive(player)) {
        result.cleared = true;
        s_cleared[static_cast<int>(type_)] = true;
        exitRequested_ = true;
    }
    else {
        result.playerDefeated = true;
        result.defeat = OnDefeat(player);
    }
    return result;
}

// ---- 패배 처리 ----

DefeatResult Dungeon::OnDefeat(Player& player) {
    DefeatResult result;

    player.SetHp(1);   // 체력을 1로 강제 조정

    std::uniform_int_distribution<int> goldLossRange(5, 20);
    int goldLoss = std::min<int>(goldLossRange(rng_), player.GetGold());
    player.DecreaseGold(goldLoss);
    result.goldLost = goldLoss;

    auto items = g_player_inventory.ViewInventory();
    int removeCount = std::min<int>(2, static_cast<int>(items.size()));

    if (removeCount > 0) {
        std::vector<int> indices(items.size());
        std::iota(indices.begin(), indices.end(), 0);
        std::vector<int> picked;
        std::sample(indices.begin(), indices.end(), std::back_inserter(picked), removeCount, rng_);

        for (int idx : picked) {
            RemoveItem(g_player_inventory, items[idx].name_, items[idx].count_);
        }
        result.itemsLost = removeCount;
    }

    exitRequested_ = true;
    return result;
}