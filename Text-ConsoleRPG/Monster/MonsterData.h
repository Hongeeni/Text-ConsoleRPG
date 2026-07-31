#pragma once

#include <string>
#include <vector>

#include "monster.h"

struct MonsterData {
    MonsterGroup group;
    std::string name;
    int hp;
    int atk;
    int def;
    int spd;

    std::string dropName;
    std::string dropCategory;
    int dropPrice;
    int rewardExp;
    
    bool isBoss;
};

std::vector<MonsterData> MonsterList();
Monster CreateMonster(int id);
