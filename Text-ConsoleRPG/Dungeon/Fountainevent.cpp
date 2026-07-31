#include "FountainEvent.h"
#include "Player.h"

#include <iostream>

void FountainEvent::Trigger(Player& player) {
    std::cout << "You found the Fountain of Life. Your HP is fully restored.\n";

    // Player는 최대/현재 체력을 GetPlayerHp() 맵 하나로 제공 (max_hp / current_hp)
    const auto hp = player.GetPlayerHp();
    unsigned short missingHp = hp.at("max_hp") - hp.at("current_hp");
    if (missingHp > 0) {
        player.HpRecovery(missingHp);
    }
}
