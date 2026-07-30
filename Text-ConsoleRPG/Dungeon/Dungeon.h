#pragma once

#include <string>
#include <random>
#include "DungeonType.h"

class Player;

class Dungeon {
public:
    explicit Dungeon(DungeonType type);
    void Run(Player& player);

private:
    enum class Event { Monster, Treasure, Shop, Altar, Fountain, BossFound };

    DungeonType type_;
    bool bossFound_ = false;
    bool exitRequested_ = false;
    std::mt19937 rng_{ std::random_device{}() };

    int escapeFailPercent_ = 20;

    void ShowMenu() const;
    int GetChoice(int maxOption) const;
    std::string GetName() const;
    std::string GetBossRoomAnswer() const; // 던전 종류별 정답 (미확정)

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

    void OnDefeat(Player& player);
};