#include "TreasureRoomEvent.h"
#include "Player.h"
#include "Inventory.h"

#include <random>
#include <string>
#include <vector>

namespace {
    std::mt19937& Rng() {
        static std::mt19937 rng{ std::random_device{}() };
        return rng;
    }

    struct Reward {
        std::string name;
        int weight;
    };

    // (미확정) 실제 아이템 이름/확률은 아이템 담당자 디자인으로 교체
    const std::vector<Reward> kRewardTable = {
        { "무기",     35 },
        { "장비",     35 },
        { "포션",     25 },
        { "영약",      5 }, // 낮은 확률, 능력치 영구 증가용 (미확정)
    };
}

TreasureResult TreasureRoomEvent::Trigger(Player& player) {
    std::vector<double> weights;
    weights.reserve(kRewardTable.size());
    for (const auto& reward : kRewardTable) {
        weights.push_back(reward.weight);
    }

    std::discrete_distribution<int> dist(weights.begin(), weights.end());
    const Reward& picked = kRewardTable[dist(Rng())];

    AddItem(g_player_inventory, picked.name, 1);

    TreasureResult result;
    result.itemName = picked.name;
    return result;
}
