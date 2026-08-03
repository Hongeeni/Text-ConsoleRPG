#include "monsterdata.h"

using namespace std;

vector<MonsterData> MonsterList() {
    vector<MonsterData> monsters = {


        // group, name,          hp, attack, def, spd, crit, dropitenname,    category, gold, exp, isboss
// Slime
{ MonsterGroup::Slime,  "작은 슬라임",    80,  15,  5,  5, 10, "슬라임 부산물",  "parts",  10,  20, false },
{ MonsterGroup::Slime,  "독 슬라임",     100,  18,  5, 10, 10, "붉은 허브",      "parts",  12,  25, false },
{ MonsterGroup::Slime,  "슬라임 무리",   120,  20,  8,  5, 10, "붉은 허브",      "parts",  10,  30, false },
{ MonsterGroup::Slime,  "얼음 슬라임",   130,  22,  8, 10, 10, "푸른 허브",      "parts",  12,  35, false },
{ MonsterGroup::Slime,  "하얀 슬라임",   140,  20, 10, 10, 10, "푸른 허브",      "parts",  14,  38, false },
{ MonsterGroup::Slime,  "불타는 슬라임", 150,  25,  8, 15, 10, "슬라임 부산물",    "parts",  10,  40, false },
{ MonsterGroup::Slime,  "검은 슬라임",   180,  30, 10, 15, 10, "슬라임 부산물",      "parts",  10,  50, false },
{ MonsterGroup::Slime,  "메탈 슬라임",    60,  10, 30, 30, 10, "슬라임 부산물",      "parts",  50,  60, false },
{ MonsterGroup::Slime,  "슬라임 킹",     300,  40, 15, 20, 30, "토벌 증서",     "license",10, 100, true  },

// Undead 
{ MonsterGroup::Undead, "죽은 새",       100,  20,  5, 30, 10, "붉은 허브",  "parts",  15,  25, false },
{ MonsterGroup::Undead, "좀비",          140,  25, 10, 20, 10, "붉은 허브",  "parts",  15,  35, false },
{ MonsterGroup::Undead, "좀비 무리",     170,  30, 10, 20, 30, "언데드 부산물",   "parts",  15,  45, false },
{ MonsterGroup::Undead, "해골",          200,  35, 12, 25, 30, "언데드 부산물",    "parts",  15,  55, false },
{ MonsterGroup::Undead, "해골 궁수",     180,  40,  8, 30, 30, "언데드 부산물",      "parts",  20,  50, false },
{ MonsterGroup::Undead, "망령",          160,  28, 10, 25, 10, "언데드 부산물",   "parts",  18,  42, false },
{ MonsterGroup::Undead, "구울",          220,  30, 15, 15, 30, "푸른 허브",        "parts",  25,  60, false },
{ MonsterGroup::Undead, "리치",          250,  38, 10, 20, 30, "언데드 부산물",    "parts",  40,  70, false },
{ MonsterGroup::Undead, "크리처",        350,  45, 18, 30, 40, "토벌 증서",      "license",90, 120, true  },

// Golem 
 { MonsterGroup::Golem,  "진흙 골렘",     130,  18, 15, 20, 10, "골렘의 핵",      "parts",  35,  30, false },
 { MonsterGroup::Golem,  "나무 골렘",     190,  28, 20, 20, 10, "붉은 허브",      "parts",  35,  50, false },
 { MonsterGroup::Golem,  "모래 골렘",     160,  22, 18, 20, 10, "골렘의 핵",   "parts",  35,  40, false },
 { MonsterGroup::Golem,  "이끼 골렘",     170,  20, 20, 15, 20, "붉은 허브",      "parts",  30,  45, false },
 { MonsterGroup::Golem,  "바위 골렘",     230,  35, 25, 30, 20, "붉은 허브",      "parts",  35,  65, false },
 { MonsterGroup::Golem,  "수정 골렘",     200,  25, 22, 15, 20, "붉은 허브",    "parts",  45,  55, false },
 { MonsterGroup::Golem,  "철 골렘",       260,  40, 28, 10, 30, "푸른 허브",        "parts",  50,  75, false },
 { MonsterGroup::Golem,  "거대 골렘",     400,  50, 30, 15, 30, "토벌 증서",      "license",100,150, true  },


 //finalboss
     { MonsterGroup::finalboss,  "마왕",      1000, 250, 200, 50, 30, "토벌 증서",   "license", 1000, 300, true  },

    };
    return monsters;
}


// and then return Monster 
Monster CreateMonster(string name) {
    auto monsters = MonsterList();
    for (const auto& m : monsters) {
        if (m.name == name) {
            return Monster(m.group, m.name, m.hp, m.attack, m.defence, m.speed, m.critical,
                m.dropName, m.dropCategory, m.dropGold,
                m.rewardExp, m.isBoss);
        }

    } return std::nullopt;

}
