#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "item.h"

struct ItemData {
    std::string category;

    std::string name;
    std::string description;

    int price;

    int healHp;
    int healMp;

    int bonusHp;
    int bonusMp;
    int bonusPower;
    int bonusDefense;
    int bonusCritical;
    int bonusSpeed;

    bool found = false; // 아이템을 찾았는지 여부를 나타내는 멤버 변수
};

std::vector<ItemData> ItemList();

std::unordered_map<std::string, ItemData> GetItemMap();
ItemData FindItem(const std::string& name);

Item CreateItem(std::string name, int count = 1); // default count, 1
