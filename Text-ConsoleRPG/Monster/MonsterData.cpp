#include "monsterdata.h"

using namespace std;

vector<MonsterData> MonsterList() {
    vector<MonsterData> monsters = {


                        // group, name,          hp, attack, def, spd, dropitenname,    category, gold, exp, isboss
        // Slime
        { MonsterGroup::Slime,  "작은 슬라임",   80,  15, 5, 0,  "슬라임 부산물",     "parts",  10, 20,  false },
        { MonsterGroup::Slime,  "슬라임 무리",        120, 20, 8, 0,  "슬라임 부산물"     "parts",  10, 30,  false },
        { MonsterGroup::Slime,  "불타는 슬라임",   150, 25, 8, 0, "슬라임 부산물",      "parts",  10, 40,  false },
        { MonsterGroup::Slime,  "검은 슬라임",   180, 30, 10, 0, "슬라임 부산물",      "parts",  10, 50,  false },
        { MonsterGroup::Slime,  "슬라임 킹",    300, 40, 15, 0, "토벌 증서",     "license",  10, 100, true  },

        // Undead 
        { MonsterGroup::Undead,  "죽은 새",  100, 20, 5, 0, "언데드 부산물",   "parts",  15, 25,  false },
        { MonsterGroup::Undead,  "좀비",  140, 25, 10, 0, "언데드 부산물",     "parts",  15, 35,  false },
        { MonsterGroup::Undead,  "좀비 무리",       170, 30, 10, 0, "언데드 부산물",   "parts",  15, 45,  false },
        { MonsterGroup::Undead,  "해골",     200, 35, 12, 0, "언데드 부산물",       "parts",  15, 55,  false },
        { MonsterGroup::Undead,  "크리처",  350, 45, 18, 0, "토벌 증서",     "license",  90, 120, true  },

        // Golem 
        { MonsterGroup::Golem,  "진흙 골렘",     130, 18, 15, 0, "골렘의 핵",    "parts",  35, 30,  false },
        { MonsterGroup::Golem,  "모래 골렘",    160, 22, 18, 0, "골렘의 핵",     "parts",  35, 40,  false },
        { MonsterGroup::Golem,  "나무 골렘",    190, 28, 20, 0, "골렘의 핵",     "parts",  35, 50,  false },
        { MonsterGroup::Golem,  "바위 골렘",   230, 35, 25, 0, "골렘의 핵",      "parts",  35, 65,  false },
        { MonsterGroup::Golem,  "거대 골렘",      400, 50, 30, 0, "토벌 증서",   "license", 100, 150, true  },

        //finalboss
        { MonsterGroup::finalboss,  "마왕",      1000, 250, 200, 50, "토벌 증서",   "license", 1000, 300, true  },

    };
    return monsters;
}


// and then return Monster 
Monster CreateMonster(int id) {
    auto monsters = MonsterList();
    for (const auto& m : monsters) {
        if (m.id == id) {
            return Monster(m.group, m.name, m.hp, m.attack, m.defence, m.speed,
                m.dropName, m.dropCategory, m.dropGold,
                m.rewardExp, m.isBoss);
        }
}
