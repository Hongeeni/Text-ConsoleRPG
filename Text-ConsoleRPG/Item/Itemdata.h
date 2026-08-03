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
    int bonusAttack;
    int bonusDefense;
    int bonusCritical;
    int bonusSpeed;
};

std::vector<ItemData> ItemList();

std::unordered_map<std::string, ItemData> GetItemMap();
ItemData FindItem(const std::string& name);

Item CreateItem(std::string name, int count = 1); // default count, 1
