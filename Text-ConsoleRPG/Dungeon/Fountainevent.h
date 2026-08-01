#pragma once

class Player;

struct FountainResult {
    unsigned short hpRestored = 0;
    unsigned short mpRestored = 0;
};

class FountainEvent {
public:
    static FountainResult Trigger(Player& player);
};
