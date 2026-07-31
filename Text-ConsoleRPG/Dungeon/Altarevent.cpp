#include "AltarEvent.h"
#include "Player.h"

#include <random>
#include <iostream>

namespace {
    std::mt19937& Rng() {
        static std::mt19937 rng{ std::random_device{}() };
        return rng;
    }
}

void AltarEvent::Trigger(Player& player) {
    std::cout << "You found an old altar.\n";

    // (미확정) 좋은/나쁜 효과 목록 - 우선 체력 증감 1종류씩만 구현
    const unsigned short kHealAmount = 20;   // (미확정)
    const unsigned short kDamageAmount = 20; // (미확정)

    std::bernoulli_distribution isGood(0.5);
    if (isGood(Rng())) {
        player.HpRecovery(kHealAmount);
        std::cout << "The altar bestowed a blessing! (HP +" << kHealAmount << ")\n";
    }
    else {
        player.PlayerDamage(kDamageAmount);
        std::cout << "The altar cast a curse! (HP -" << kDamageAmount << ")\n";
    }
}
