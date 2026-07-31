#pragma once

#include <string>
#include <random>
#include <array>
#include "DungeonType.h"

class Player;

class Dungeon {
public:
    explicit Dungeon(DungeonType type);
    void Run(Player& player);

    // 해당 타입의 던전을 이미 클리어했는지 (Player 쪽에 클리어 기록이 없어 Dungeon이 자체 보관)
    static bool IsCleared(DungeonType type);

private:
    enum class Event { Monster, Treasure, Shop, Altar, Fountain, BossFound };

    DungeonType type_;
    bool bossFound_ = false;
    bool exitRequested_ = false;
    std::mt19937 rng_{ std::random_device{}() };

    int escapeFailPercent_ = 20;

    // 던전 타입별 클리어 여부 (인덱스 = static_cast<int>(DungeonType))
    static std::array<bool, 3> s_cleared;

    void ShowMenu() const;
    int GetChoice(int maxOption) const;
    std::string GetName() const;
    std::string GetShopName() const;       // 던전별 실제 상점 이름 (Shop.cpp kShopList() 기준)
    std::string GetBossRoomAnswer() const; // 보스방 정답 (미확정)

    Event RollEvent();
    void Resolve(Event e, Player& player);

    void OnMonster(Player& player);
    void OnTreasure(Player& player);
    void OnShop(Player& player);
    void OnAltar(Player& player);
    void OnFountain(Player& player);
    void OnBossFound();
    void OnBossFight(Player& player);

    bool TryEscape(Player& player);
    bool TryEnterBossRoom() const;
    bool IsPlayerAlive(Player& player) const; // Player::IsAlive()가 private라 HP 값으로 직접 판정

    void OnDefeat(Player& player);
};
