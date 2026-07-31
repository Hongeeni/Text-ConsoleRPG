#pragma once

#include <string>
#include <vector>

#include "item.h"

struct ItemData {
    std::string category;

    std::string name;
    std::string desc;
    
    int price;
    
    int healHp;
    int healMp;
    
    int bonusHp;
    int bonusMp;
    int bonusAtk;
    int bonusDef;
    int bonusCrit;
    int bonusSpd;
};

std::vector<ItemData> ItemList();


Item CreateItem(string name, int count = 1); // default count, 1
