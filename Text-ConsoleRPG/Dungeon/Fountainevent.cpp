#include "FountainEvent.h"
#include "Player.h"

FountainResult FountainEvent::Trigger(Player& player) {
    FountainResult result;

    // Player는 최대/현재 체력을 GetPlayerHp() 맵 하나로 제공 (max_hp / current_hp)
    const auto hp = player.GetPlayerHp();
    unsigned short missingHp = hp.at("max_hp") - hp.at("current_hp");
    if (missingHp > 0) {
        player.HpRecovery(missingHp);
        result.hpRestored = missingHp;
    }

    const auto mp = player.GetPlayerMp();
    unsigned short missingMp = mp.at("max_mp") - mp.at("current_mp");
    if (missingMp > 0) {
        player.MpRecovery(missingMp);
        result.mpRestored = missingMp;
    }

    return result;
}
