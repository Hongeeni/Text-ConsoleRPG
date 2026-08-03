#include "FountainEvent.h"
#include "Player.h"

FountainResult FountainEvent::Trigger(Player& player) {
    FountainResult result;

    int missingHp = player.GetMaxHp() - player.GetCurrentHp();
    if (missingHp > 0) {
        player.HpRecovery(missingHp);
        result.hpRestored = missingHp;
    }

    // 전투 시스템 개편으로 매 턴 MP 자동 회복이 사라져서, 생명의 샘에서 MP도 함께 회복
    int missingMp = player.GetMaxMp() - player.GetCurrentMp();
    if (missingMp > 0) {
        player.MpRecovery(missingMp);
        result.mpRestored = missingMp;
    }

    return result;
}