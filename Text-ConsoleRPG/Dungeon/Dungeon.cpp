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
    case DungeonType::Slime:  return "슬라임 던전";
    case DungeonType::Zombie: return "좀비 던전";
    case DungeonType::Golem:  return "골렘 던전";
    }
    return "알 수 없는 던전";
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
            ViewInventory(g_player_inventory); // 전역 인벤토리 사용
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
    std::cout << "몬스터와 마주쳤습니다!\n";

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
    std::cout << "던전 상인을 만났습니다.\n";

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
    std::cout << "보스방을 발견했습니다!\n";
}

void Dungeon::OnBossFight(Player& player) {
    std::cout << GetName() << "의 보스방에 입장합니다!\n";

    // Monster / CombatSystem은 아직 미확정이라 기존 임시 호출 형태 그대로 유지
    Monster boss = Monster::CreateBoss(type_, player.GetPlayerLevel().at("current_level")); // (미확정) Monster 실제 함수명

    CombatSystem combat;
    combat.Fight(player, boss);

    if (IsPlayerAlive(player)) {
        std::cout << GetName() << " 클리어! 토벌 증서를 획득했습니다.\n";
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

    player.SetPlayerHp(1); // 체력을 1로 강제 조정 (기존 ForceHpToOne 대체)

    std::uniform_int_distribution<int> goldLossRange(5, 20); // (미확정) 골드 손실 범위
    int goldLoss = std::min<int>(goldLossRange(rng_), player.GetPlayerGold());
    player.DecreaseGold(static_cast<unsigned short>(goldLoss));
    std::cout << "골드 " << goldLoss << "을(를) 잃었습니다.\n";

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
        std::cout << "아이템 " << removeCount << "종류를 잃었습니다.\n";
    }

    exitRequested_ = true;
}
