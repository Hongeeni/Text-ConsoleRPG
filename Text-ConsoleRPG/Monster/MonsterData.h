#pragma once

#include <string>
#include <vector>

#include "monster.h"

struct MonsterData {
    MonsterGroup group;
    std::string name;
    int hp;
    int power;
    int defence;
    int speed;
	int critical;

    std::string dropName;
    std::string dropCategory;
    int dropGold;
    int rewardExp;
    
    bool isBoss;
};

std::vector<MonsterData> MonsterList();
Monster CreateMonster(std::string name);

