#pragma once

#include <string>

class Player;

struct AltarResult {
    bool blessed = false;   // true = 축복, false = 저주
    std::string target;
    int amount = 0;
};

class AltarEvent {
public:
    static AltarResult Trigger(Player& player);
};