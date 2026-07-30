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

Dungeon::Dungeon(DungeonType type) : type_(type) {}

std::string Dungeon::GetName() const {
    switch (type_) {
    case DungeonType::Slime:  return "슬라임 던전";
    case DungeonType::Zombie: return "좀비 던전";
    case DungeonType::Golem:  return "골렘 던전";
    }
    return "알 수 없는 던전";
}

void Dungeon::ShowMenu() const {
    std::cout << "========== " << GetName() << " ==========\n";
    std::cout << "1. 전진\n";
    std::cout << "2. 인벤토리\n";
    if (bossFound_) {
        std::cout << "3. 보스방으로 가기\n";
        std::cout << "4. 던전 탈출\n";
    }
    else {
        std::cout << "3. 던전 탈출\n";
    }
    std::cout << "선택: ";
}

int Dungeon::GetChoice(int maxOption) const {
    int choice = -1;
    while (!(std::cin >> choice) || choice < 1 || choice > maxOption) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "잘못된 입력입니다. 다시 선택하세요: ";
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
            ViewInventory(player.GetInventory()); // (미확정) Player::GetInventory 반환 타입 확인
        }
        else if (bossFound_ && choice == 3) {
            if (TryEnterBossRoom()) {
                OnBossFight(player);
            }
            else {
                std::cout << "정답이 틀렸습니다. 보스방에 들어갈 수 없습니다.\n";
            }
        }
        else {
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
    std::cout << "몬스터와 마주쳤습니다!\n";
    Monster monster = Monster::Create(type_, player.GetLevel()); // (미확정) Monster 실제 함수명

    CombatSystem combat;
    combat.Fight(player, monster); // (미확정) CombatSystem 실제 함수명

    if (!player.IsAlive()) {
        OnDefeat(player);
    }
}

void Dungeon::OnTreasure(Player& player) {
    TreasureRoomEvent::Trigger(player);
}

void Dungeon::OnShop(Player& player) {
    std::cout << "던전 상인을 만났습니다.\n";

    // 상점 로직 자체는 Shop 클래스 그대로 사용, 가격만 던전 상점 기준(true)으로 다르게 적용
    Shop dungeonShop(true);
    dungeonShop.Open(player); // (미확정) Shop 실제 진입 함수명
}

void Dungeon::OnAltar(Player& player) {
    AltarEvent::Trigger(player);
}

void Dungeon::OnFountain(Player& player) {
    FountainEvent::Trigger(player);
}

void Dungeon::OnBossFound() {
    bossFound_ = true;
    std::cout << "보스방을 발견했습니다!\n";
}

void Dungeon::OnBossFight(Player& player) {
    std::cout << GetName() << "의 보스방에 입장합니다!\n";
    Monster boss = Monster::CreateBoss(type_, player.GetLevel()); // (미확정) Monster 실제 함수명

    CombatSystem combat;
    combat.Fight(player, boss);

    if (player.IsAlive()) {
        std::cout << GetName() << " 클리어! 토벌 증서를 획득했습니다.\n";
        player.SetCleared(type_); // (미확정) Player 실제 함수명
        exitRequested_ = true;
    }
    else {
        OnDefeat(player);
    }
}

bool Dungeon::TryEscape(Player& player) {
    std::bernoulli_distribution fail(escapeFailPercent_ / 100.0);
    if (fail(rng_)) {
        std::cout << "탈출에 실패했습니다! 몬스터와 마주칩니다.\n";
        OnMonster(player);
        return false;
    }
    std::cout << "탈출에 성공했습니다.\n";
    return true;
}

std::string Dungeon::GetBossRoomAnswer() const {
    // (미확정) 던전별 실제 문제/정답
    switch (type_) {
    case DungeonType::Slime:  return "SLIME_ANSWER";
    case DungeonType::Zombie: return "ZOMBIE_ANSWER";
    case DungeonType::Golem:  return "GOLEM_ANSWER";
    }
    return "";
}

bool Dungeon::TryEnterBossRoom() const {
    std::cout << "보스방 입구의 문제: 정답을 입력하세요: ";
    std::string answer;
    std::cin >> answer;
    return answer == GetBossRoomAnswer();
}

void Dungeon::OnDefeat(Player& player) {
    std::cout << "쓰러졌습니다... 던전에서 강제로 밀려납니다.\n";

    player.ForceHpToOne(); // (미확정) Player 실제 함수명

    std::uniform_int_distribution<int> goldLossRange(5, 20); // (미확정) 골드 손실 범위
    int goldLoss = std::min(goldLossRange(rng_), player.GetGold());
    player.SpendGold(goldLoss);
    std::cout << "골드 " << goldLoss << "을(를) 잃었습니다.\n";

    auto items = player.GetInventory().ViewInventory();
    int removeCount = std::min<int>(2, static_cast<int>(items.size()));

    if (removeCount > 0) {
        std::vector<int> indices(items.size());
        std::iota(indices.begin(), indices.end(), 0);
        std::vector<int> picked;
        std::sample(indices.begin(), indices.end(), std::back_inserter(picked), removeCount, rng_);

        for (int idx : picked) {
            RemoveItem(player.GetInventory(), items[idx].name_, items[idx].count_);
        }
        std::cout << "아이템 " << removeCount << "종류를 잃었습니다.\n";
    }

    exitRequested_ = true;
}