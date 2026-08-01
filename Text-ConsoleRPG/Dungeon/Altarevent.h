#pragma once

class Player;

struct AltarResult {
    bool blessed = false;      // true = 축복(회복), false = 저주(피해)
    unsigned short amount = 0;
};

class AltarEvent {
public:
    static AltarResult Trigger(Player& player);
};
