#include "TreasureRoomEvent.h"
#include "Player.h"
#include "Inventory.h"
#include "Itemdata.h"

#include <random>
#include <string>
#include <vector>
#include <utility>

namespace {
    std::mt19937& Rng() {
        static std::mt19937 rng{ std::random_device{}() };
        return rng;
    }

    const std::vector<ItemData>& AllItems() {
        static const std::vector<ItemData> items = ItemList();
        return items;
    }

    const std::string kHintPaperPrefix = "정체를 알 수 없는 종이 #";

    // 던전별 힌트 종이 번호 시작값
    // 슬라임(0) -> 1,2,3 / 언데드(1) -> 4,5,6 / 골렘(2) -> 7,8,9
    int HintPaperBaseNumber(DungeonType type) {
        return static_cast<int>(type) * 3 + 1;
    }

    // (미확정) 던전 등급별 아이템 가격 상한
    int MaxItemPrice(DungeonType type) {
        switch (type) {
        case DungeonType::Slime:  return 320;
        case DungeonType::Undead: return 960;
        case DungeonType::Golem:  return 99999;
        }
        return 320;
    }

    // 던전 등급별 골드 보상 범위
    std::pair<int, int> GoldRange(DungeonType type) {
        switch (type) {
        case DungeonType::Slime:  return { 60, 120 };
        case DungeonType::Undead: return { 120, 240 };
        case DungeonType::Golem:  return { 250, 450 };
        }
        return { 60, 120 };
    }

    // 상자당 아이템 개수 - 1개 50% / 2개 35% / 3개 15%
    const std::vector<double> kCountWeights = { 50.0, 35.0, 15.0 };

    // 카테고리별 등장 비율
    const std::vector<std::string> kCategories =
    { "weapon", "shield", "armor", "ring", "gloves", "shoes", "potion", "hint" };
    const std::vector<double> kCategoryWeights =
    { 7.0,      7.0,     7.0,    6.0,     7.0,      6.0,     20.0,    40.0 };

    // 같은 아이템이 또 나오면 개수만 늘린다
    void AddReward(std::vector<TreasureReward>& rewards,
        const std::string& name, const std::string& category, bool isHint) {
        for (auto& reward : rewards) {
            if (reward.itemName == name) {
                reward.count++;
                return;
            }
        }
        rewards.push_back(TreasureReward{ name, category, 1, isHint });
    }
}

TreasureResult TreasureRoomEvent::Trigger(Player& player, DungeonType type) {
    TreasureResult result;

    // ---- 골드 ----
    const std::pair<int, int> range = GoldRange(type);
    std::uniform_int_distribution<int> goldDist(range.first, range.second);
    result.gold = goldDist(Rng());
    player.AddGold(result.gold);

    // ---- 아이템 개수 (1 ~ 3) ----
    std::discrete_distribution<int> countDist(kCountWeights.begin(), kCountWeights.end());
    const int itemCount = countDist(Rng()) + 1;

    std::discrete_distribution<int> categoryDist(kCategoryWeights.begin(), kCategoryWeights.end());

    for (int i = 0; i < itemCount; ++i) {
        const std::string category = kCategories[categoryDist(Rng())];

        // ---- 보스방 힌트 종이 ----
        if (category == "hint") {
            // 해당 던전의 3종 중 1장. 중복 허용
            const int base = HintPaperBaseNumber(type);
            std::uniform_int_distribution<int> paperDist(0, 2);
            const std::string name = kHintPaperPrefix + std::to_string(base + paperDist(Rng()));

            AddItem(g_player_inventory, name, 1);
            AddReward(result.rewards, name, "other", true);
            continue;
        }

        // ---- 일반 아이템 (던전 등급에 맞는 가격대만) ----
        const int maxPrice = MaxItemPrice(type);

        std::vector<const ItemData*> candidates;
        for (const auto& item : AllItems()) {
            if (item.category == category && item.price <= maxPrice) {
                candidates.push_back(&item);
            }
        }
        if (candidates.empty()) {
            continue;   // 해당 등급에 후보가 없으면 이번 칸은 건너뛴다
        }

        std::uniform_int_distribution<int> itemDist(0, static_cast<int>(candidates.size()) - 1);
        const ItemData* reward = candidates[itemDist(Rng())];
        if (reward->is_gear) {
            AddItem(g_player_armory, reward->name, 1);
        }
        else {
            AddItem(g_player_inventory, reward->name, 1);
        }
        
        AddReward(result.rewards, reward->name, reward->category, false);
    }

    return result;
}