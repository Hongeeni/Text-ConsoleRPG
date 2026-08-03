#pragma once

#include <string>

class Player;

struct TreasureResult {
    std::string itemName;
};

class TreasureRoomEvent {
public:
    static TreasureResult Trigger(Player& player);
};
