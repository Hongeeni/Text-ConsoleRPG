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
    // DungeonType(0,1,2)과 MonsterGroup(1,2,3)은 값이 달라서 직접 변환한다
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

// Player::IsAlive()가 private라 외부에서 호출 불가 -> HP 값으로 직접 판정
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
    // Shop.cpp kShopList()에 등록된 이름과 정확히 일치해야 한다 ("상점"이 아니라 "상인")
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

// 던전당 보스는 1마리 고정.
// 마왕(finalboss)은 MonsterGroup이 달라서 여기 걸리지 않는다.
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

    // 경험치/골드 지급은 CombatSystem::GetResult()가 담당한다.
    // 던전은 드랍 아이템만 처리한다. (보스 드랍이 "토벌 증서")
    if (!monster.IsAlive()) {
        result.monsterDefeated = true;
        result.dropName = monster.GetDropName();
        AddItem(g_player_inventory, monster.GetDropName(), 1);
    }
    return result;
}

// ---- 이벤트 진행 ----

DungeonEvent Dungeon::RollEvent() {
    // 이미 클리어한 던전은 보스방이 다시 등장하지 않는다.
    // 토벌 증서 3종이 전부 같은 이름이라, 한 던전 반복으로 3개를 모으는 걸 막기 위함.
    const bool canFindBoss = !bossFound_ && !IsCleared(type_);

    // (미확정) 이벤트 상대 비율
    std::vector<double> weights = {
        40.0,                        // Monster
        12.0,                        // Treasure
        12.0,                        // Shop
        12.0,                        // Altar
        12.0,                        // Fountain
        canFindBoss ? 12.0 : 0.0     // BossFound
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
        // Shop은 클래스가 아니라 이름 문자열 기반 자유 함수 구조 (Shop.h 참고)
        // ViewShop(shop_name, name, player)는 내부적으로 두 번째 인자(name)만 실제 조회에 사용함
        ViewShop(GetShopName(), GetShopName(), player);
        break;
    case DungeonEvent::Altar:
        result.altar = AltarEvent::Trigger(player);
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
    // (미확정) 종이 3장의 힌트로 유추할 실제 정답
    switch (type_) {
    case DungeonType::Slime:  return "SLIME_ANSWER";
    case DungeonType::Undead: return "UNDEAD_ANSWER";
    case DungeonType::Golem:  return "GOLEM_ANSWER";
    }
    return "";
}

BossRoomResult Dungeon::EnterBossRoom(const std::string& answer, Player& player) {
    BossRoomResult result;

    // 클리어한 던전의 보스는 다시 잡을 수 없다 (토벌 증서 중복 획득 차단)
    if (IsCleared(type_)) {
        result.alreadyCleared = true;
        return result;
    }

    result.correctAnswer = (answer == GetBossRoomAnswer());
    if (!result.correctAnswer) {
        return result;   // 오답이면 보스방 앞에 그대로 남는다
    }

    Monster boss = PickBoss();
    result.monster = FightMonster(player, boss);

    if (IsPlayerAlive(player)) {
        // 보스 드랍이 "토벌 증서"라 FightMonster()에서 이미 인벤토리에 들어갔다
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

    std::uniform_int_distribution<int> goldLossRange(5, 20);   // (미확정) 골드 손실 범위
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