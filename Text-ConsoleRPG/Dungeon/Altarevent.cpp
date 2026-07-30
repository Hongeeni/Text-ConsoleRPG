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
    std::cout << "낡은 재단을 발견했습니다.\n";

    // (미확정) 좋은/나쁜 효과 목록 - 우선 체력 증감 1종류씩만 구현
    const int kHealAmount = 20;   // (미확정)
    const int kDamageAmount = 20; // (미확정)

    std::bernoulli_distribution isGood(0.5);
    if (isGood(Rng())) {
        player.Heal(kHealAmount);
        std::cout << "재단이 축복을 내렸습니다! (체력 " << kHealAmount << " 회복)\n";
    }
    else {
        player.TakeDamage(kDamageAmount);
        std::cout << "재단이 저주를 내렸습니다! (체력 " << kDamageAmount << " 감소)\n";
    }
}