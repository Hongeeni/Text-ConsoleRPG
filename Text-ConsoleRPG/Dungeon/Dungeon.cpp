#include "Dungeon.h"
#include "Player.h"
#include "Monster.h"
#include "CombatSystem.h"
#include "Shop.h"
#include "Inventory.h"

#include <iostream>
#include <algorithm>
#include <numeric>
#include <array>
#include <vector>

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
    return player.GetPlayerCurrentHp() > 0;
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
    // Shop.cpp kShopList()에 정의된 실제 상점 이름과 매칭
    switch (type_) {
    case DungeonType::Slime:  return "슬라임 상점";
    case DungeonType::Undead: return "언데드 상점";
    case DungeonType::Golem:  return "골렘 상점";
    }
    return "상점";
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

// ---- 이벤트 진행 ----

DungeonEvent Dungeon::RollEvent() {
    // (미확정) 몬스터 조우 외 5개 항목 상대 비율
    std::vector<double> weights = {
        40.0,                       // Monster
        12.0,                       // Treasure
        12.0,                       // Shop
        12.0,                       // Altar
        12.0,                       // Fountain
        bossFound_ ? 0.0 : 12.0     // BossFound
    };
    std::discrete_distribution<int> dist(weights.begin(), weights.end());
    return static_cast<DungeonEvent>(dist(rng_));
}

Dungeon::MonsterFightOutcome Dungeon::FightMonster(Player& player) {
    MonsterFightOutcome outcome;

    // Monster / CombatSystem은 아직 미확정이라 기존 임시 호출 형태 그대로 유지
    Monster monster = Monster::Create(type_, player.GetPlayerCurrentLevel()); // (미확정) Monster 실제 함수명

    CombatSystem combat;
    combat.Fight(player, monster); // (미확정) CombatSystem 실제 함수명

    if (!IsPlayerAlive(player)) {
        outcome.playerDefeated = true;
        outcome.defeat = OnDefeat(player);
    }
    return outcome;
}

AdvanceResult Dungeon::Resolve(DungeonEvent e, Player& player) {
    AdvanceResult result;
    result.event = e;

    switch (e) {
    case DungeonEvent::Monster: {
        MonsterFightOutcome outcome = FightMonster(player);
        result.playerDefeated = outcome.playerDefeated;
        result.defeat = outcome.defeat;
        break;
    }
    case DungeonEvent::Treasure:
        result.treasure = TreasureRoomEvent::Trigger(player);
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
        MonsterFightOutcome outcome = FightMonster(player);
        result.playerDefeated = outcome.playerDefeated;
        result.defeat = outcome.defeat;
        return result;
    }

    result.success = true;
    exitRequested_ = true;
    return result;
}

std::string Dungeon::GetBossRoomAnswer() const {
    // (미확정) 던전별 실제 문제/정답
    switch (type_) {
    case DungeonType::Slime:  return "SLIME_ANSWER";
    case DungeonType::Undead: return "UNDEAD_ANSWER";
    case DungeonType::Golem:  return "GOLEM_ANSWER";
    }
    return "";
}

BossRoomResult Dungeon::EnterBossRoom(const std::string& answer, Player& player) {
    BossRoomResult result;
    result.correctAnswer = (answer == GetBossRoomAnswer());
    if (!result.correctAnswer) {
        return result;
    }

    // Monster / CombatSystem은 아직 미확정이라 기존 임시 호출 형태 그대로 유지
    Monster boss = Monster::CreateBoss(type_, player.GetPlayerCurrentLevel()); // (미확정) Monster 실제 함수명

    CombatSystem combat;
    combat.Fight(player, boss); // (미확정) CombatSystem 실제 함수명

    if (IsPlayerAlive(player)) {
        result.cleared = true;
        s_cleared[static_cast<int>(type_)] = true; // Player에 클리어 정보가 없어 Dungeon이 static으로 자체 관리
        exitRequested_ = true;
    }
    else {
        result.playerDefeated = true;
        result.defeat = OnDefeat(player);
    }
    return result;
}

DefeatResult Dungeon::OnDefeat(Player& player) {
    DefeatResult result;

    player.SetPlayerHp(1); // 체력을 1로 강제 조정

    std::uniform_int_distribution<int> goldLossRange(5, 20); // (미확정) 골드 손실 범위
    int goldLoss = std::min<int>(goldLossRange(rng_), player.GetPlayerGold());
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
