#include "Dungeon.h"
#include "Player.h"
#include "Monster.h"
#include "CombatSystem.h"
#include "Shop.h"
#include "Inventory.h"
#include "TreasureRoomEvent.h"
#include "AltarEvent.h"
#include "FountainEvent.h"

#include <iostream>
#include <algorithm>
#include <numeric>
#include <array>

Dungeon::Dungeon(DungeonType type) : type_(type) {}

// 던전 타입별 클리어 여부 저장 (인덱스 = static_cast<int>(DungeonType))
std::array<bool, 3> Dungeon::s_cleared{};

bool Dungeon::IsCleared(DungeonType type) {
    return s_cleared[static_cast<int>(type)];
}

// Player::IsAlive()가 private라 외부에서 호출 불가 -> 일단 임시
bool Dungeon::IsPlayerAlive(Player& player) const {
    return player.GetPlayerHp().at("current_hp") > 0;
}

std::string Dungeon::GetName() const {
    switch (type_) {
    case DungeonType::Slime:  return "Slime Dungeon";
    case DungeonType::Zombie: return "Undead Dungeon";
    case DungeonType::Golem:  return "Golem Dungeon";
    }
    return "Unknown Dungeon";
}

std::string Dungeon::GetShopName() const {
    // Shop.cpp kShopList()에 정의된 실제 상점 이름과 매칭
    switch (type_) {
    case DungeonType::Slime:  return "Slime Shop";
    case DungeonType::Zombie: return "Undead Dungeon Shop";
    case DungeonType::Golem:  return "Stone Shop";
    }
    return "Normal Shop";
}

void Dungeon::ShowMenu() const {
    std::cout << "========== " << GetName() << " ==========\n";
    std::cout << "1. Advance\n";
    std::cout << "2. Inventory\n";
    if (bossFound_) {
        std::cout << "3. Go to Boss Room\n";
        std::cout << "4. Escape Dungeon\n";
    }
    else {
        std::cout << "3. Escape Dungeon\n";
    }
    std::cout << "Choice: ";
}

int Dungeon::GetChoice(int maxOption) const {
    int choice = -1;
    while (!(std::cin >> choice) || choice < 1 || choice > maxOption) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input. Please choose again: ";
    }
    return choice;
}

void Dungeon::Run(Player& player) {
    exitRequested_ = false;

    while (!exitRequested_) {
        ShowMenu();
        int maxOption = bossFound_ ? 4 : 3;
        int choice = GetChoice(maxOption);

        if (choice == 1) {
            Resolve(RollEvent(), player);
        }
        else if (choice == 2) {
            ViewInventory(g_player_inventory); // 전역 인벤토리 사용
        }
        else if (bossFound_ && choice == 3) {
            if (TryEnterBossRoom()) {
                OnBossFight(player);
            }
            else {
                std::cout << "Wrong answer. You cannot enter the boss room.\n";
            }
        }
        else {
            // bossFound_가 false면 3, true면 4가 이 분기(탈출 시도)로 들어옴
            if (TryEscape(player)) {
                exitRequested_ = true;
            }
        }
    }
}

Dungeon::Event Dungeon::RollEvent() {
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
    return static_cast<Event>(dist(rng_));
}

void Dungeon::Resolve(Event e, Player& player) {
    switch (e) {
    case Event::Monster:   OnMonster(player);  break;
    case Event::Treasure:  OnTreasure(player); break;
    case Event::Shop:      OnShop(player);     break;
    case Event::Altar:     OnAltar(player);    break;
    case Event::Fountain:  OnFountain(player); break;
    case Event::BossFound: OnBossFound();      break;
    }
}

void Dungeon::OnMonster(Player& player) {
    std::cout << "You encountered a monster!\n";

    // Monster / CombatSystem은 아직 미확정이라 기존 임시 호출 형태 그대로 유지
    Monster monster = Monster::Create(type_, player.GetPlayerLevel().at("current_level")); // (미확정) Monster 실제 함수명

    CombatSystem combat;
    combat.Fight(player, monster); // (미확정) CombatSystem 실제 함수명

    if (!IsPlayerAlive(player)) {
        OnDefeat(player);
    }
}

void Dungeon::OnTreasure(Player& player) {
    TreasureRoomEvent::Trigger(player);
}

void Dungeon::OnShop(Player& player) {
    std::cout << "You met the dungeon merchant.\n";

    // Shop은 클래스가 아니라 이름 문자열 기반 자유 함수 구조 (Shop.h 참고)
    // ViewShop(shop_name, name, player)는 내부적으로 두 번째 인자(name)만 실제 조회에 사용함
    ViewShop(GetShopName(), GetShopName(), player);
}

void Dungeon::OnAltar(Player& player) {
    AltarEvent::Trigger(player);
}

void Dungeon::OnFountain(Player& player) {
    FountainEvent::Trigger(player);
}

void Dungeon::OnBossFound() {
    bossFound_ = true;
    std::cout << "You discovered the boss room!\n";
}

void Dungeon::OnBossFight(Player& player) {
    std::cout << "Entering the boss room of" << GetName() << "\n";

    // Monster / CombatSystem은 아직 미확정이라 기존 임시 호출 형태 그대로 유지
    Monster boss = Monster::CreateBoss(type_, player.GetPlayerLevel().at("current_level")); // (미확정) Monster 실제 함수명

    CombatSystem combat;
    combat.Fight(player, boss);

    if (IsPlayerAlive(player)) {
        std::cout << GetName() << " cleared! You obtained a Subjugation Certificate.\n";
        s_cleared[static_cast<int>(type_)] = true; // Player에 클리어 정보가 없어 Dungeon이 static으로 자체 관리
        exitRequested_ = true;
    }
    else {
        OnDefeat(player);
    }
}

bool Dungeon::TryEscape(Player& player) {
    std::bernoulli_distribution fail(escapeFailPercent_ / 100.0);
    if (fail(rng_)) {
        std::cout << "Escape failed! You run into a monster.\n";
        OnMonster(player);
        return false;
    }
    std::cout << "Escape succeeded.\n";
    return true;
}

std::string Dungeon::GetBossRoomAnswer() const {
    // (미확정) 던전별 실제 문제/정답
    switch (type_) {
    case DungeonType::Slime:  return "SLIME_ANSWER";
    case DungeonType::Zombie: return "Undead_ANSWER";
    case DungeonType::Golem:  return "GOLEM_ANSWER";
    }
    return "";
}

bool Dungeon::TryEnterBossRoom() const {
    std::cout << "Boss room riddle \nenter the answer: ";
    std::string answer;
    std::cin >> answer;
    return answer == GetBossRoomAnswer();
}

void Dungeon::OnDefeat(Player& player) {
    std::cout << "You have fallen... You are forcibly ejected from the dungeon.\n";

    player.SetPlayerHp(1); // 체력을 1로 강제 조정 (기존 ForceHpToOne 대체)

    std::uniform_int_distribution<int> goldLossRange(5, 20); // (미확정) 골드 손실 범위
    int goldLoss = std::min<int>(goldLossRange(rng_), player.GetPlayerGold());
    player.DecreaseGold(static_cast<unsigned short>(goldLoss));
    std::cout << "You lost" << goldLoss << "gold.\n";

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
        std::cout << "You lost" << removeCount << "item(s).\n";
    }

    exitRequested_ = true;
}
