#include "AltarEvent.h"
#include "Player.h"

#include <random>

namespace {
    std::mt19937& Rng() {
        static std::mt19937 rng{ std::random_device{}() };
        return rng;
    }
}

AltarResult AltarEvent::Trigger(Player& player) {
    AltarResult result;

    // (미확정) 좋은/나쁜 효과 목록 - 우선 체력 증감 1종류씩만 구현
    const unsigned short kHealAmount = 20;   // (미확정)
    const unsigned short kDamageAmount = 20; // (미확정)

    std::bernoulli_distribution isGood(0.5);
    if (isGood(Rng())) {
        player.HpRecovery(kHealAmount);
        result.blessed = true;
        result.amount = kHealAmount;
    }
    else {
        player.PlayerDamage(kDamageAmount);
        result.blessed = false;
        result.amount = kDamageAmount;
    }
    return result;
}
