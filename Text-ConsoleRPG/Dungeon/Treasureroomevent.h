#pragma once

#include <string>
#include <vector>
#include "DungeonType.h"

class Player;

struct TreasureReward {
    std::string itemName;
    std::string category;        // "weapon" / "armor" / "potion" / "other"(힌트 종이)
    int count = 1;               // 같은 아이템이 여러 개 나오면 합쳐진다
    bool isHintPaper = false;
};

struct TreasureResult {
    std::vector<TreasureReward> rewards;   // 1 ~ 3종
    int gold = 0;
};

class TreasureRoomEvent {
public:
    // 던전 타입에 따라 아이템 등급 상한, 골드량, 힌트 종이 번호가 달라진다
    static TreasureResult Trigger(Player& player, DungeonType type);
};