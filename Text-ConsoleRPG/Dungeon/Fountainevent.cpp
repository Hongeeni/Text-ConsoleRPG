#include "FountainEvent.h"
#include "Player.h"

#include <iostream>

void FountainEvent::Trigger(Player& player) {
    std::cout << "생명의 샘을 발견했습니다. 체력이 모두 회복됩니다.\n";

    // Player는 최대/현재 체력을 GetPlayerHp() 맵 하나로 제공 (max_hp / current_hp)
    const auto hp = player.GetPlayerHp();
    unsigned short missingHp = hp.at("max_hp") - hp.at("current_hp");
    if (missingHp > 0) {
        player.HpRecovery(missingHp);
    }
}
