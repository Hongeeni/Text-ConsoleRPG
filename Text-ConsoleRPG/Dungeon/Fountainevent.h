#pragma once

class Player;

struct FountainResult {
    int hpRestored = 0;
    int mpRestored = 0;
};

class FountainEvent {
public:
    static FountainResult Trigger(Player& player);
};
