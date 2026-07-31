#include "monsterdata.h"

using namespace std;

vector<MonsterData> MonsterList() {
    vector<MonsterData> monsters = {


                        // group, name,          hp, atk, def, spd, dropitenname,    category, price, exp, isboss
        // Slime
        { MonsterGroup::Slime,  "Small Slime",   80,  15, 5, 0,  "Slime Jelly",     "parts",  10, 20,  false },
        { MonsterGroup::Slime,  "Slimes",        120, 20, 8, 0,  "Slime Jelly",     "parts",  10, 30,  false },
        { MonsterGroup::Slime,  "Fire Slimes",   150, 25, 8, 0, "Slime Jelly",      "parts",  10, 40,  false },
        { MonsterGroup::Slime,  "Dark Slimes",   180, 30, 10, 0, "Slime Jelly",      "parts",  10, 50,  false },
        { MonsterGroup::Slime,  "Slime King",    300, 40, 15, 0, "Slime Jelly",     "parts",  10, 100, true  },

        // Undead 
        { MonsterGroup::Undead,  "Rotten Crows",  100, 20, 5, 0, "Rotten Flesh",   "parts",  15, 25,  false },
        { MonsterGroup::Undead,  "Working Dead",  140, 25, 10, 0, "Rotten Flesh",     "parts",  15, 35,  false },
        { MonsterGroup::Undead,  "Zombies",       170, 30, 10, 0, "Rotten Flesh",   "parts",  15, 45,  false },
        { MonsterGroup::Undead,  "Skeletons",     200, 35, 12, 0, "Rotten Flesh",       "parts",  15, 55,  false },
        { MonsterGroup::Undead,  "The Creature",  350, 45, 18, 0, "Dark Heart",     "parts",  90, 120, true  },

        // Golem 
        { MonsterGroup::Golem,  "Mud Golem",     130, 18, 15, 0, "Golem Heart",       "parts",  35, 30,  false },
        { MonsterGroup::Golem,  "Sand Golem",    160, 22, 18, 0, "Golem Heart",    "parts",  35, 40,  false },
        { MonsterGroup::Golem,  "Wood Golem",    190, 28, 20, 0, "Golem Heart",    "parts",  35, 50,  false },
        { MonsterGroup::Golem,  "Stone Golem",   230, 35, 25, 0, "Golem Heart",      "parts",  35, 65,  false },
        { MonsterGroup::Golem,  "The Huge",      400, 50, 30, 0, "Golem Heart",     "parts", 100, 150, true  },
    };
    return monsters;
}


// and then return Monster 
Monster CreateMonster(int id) {
    auto monsters = MonsterList();
    for (const auto& m : monsters) {
        if (m.id == id) {
            return Monster(m.group, m.name, m.hp, m.atk, m.def, m.spd,
                m.dropName, m.dropCategory, m.dropPrice,
                m.rewardExp, m.isBoss);
        }
}
