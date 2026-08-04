#include "monsterdata.h"

using namespace std;

vector<MonsterData> MonsterList() {
    vector<MonsterData> monsters = {


        // group, name,          hp, power, def, spd, crit, dropitemname,    category, gold, exp, isboss
// Slime
{ MonsterGroup::Slime,  "작은 슬라임",    80,  15,  5,  5, 10, "슬라임 부산물",  "parts",  25,  20, false },
{ MonsterGroup::Slime,  "독 슬라임",     100,  18,  5, 10, 10, "붉은 허브",      "parts",  28,  25, false },
{ MonsterGroup::Slime,  "슬라임 무리",   120,  20,  8,  5, 10, "붉은 허브",      "parts",  30,  30, false },
{ MonsterGroup::Slime,  "얼음 슬라임",   130,  22,  8, 10, 10, "푸른 허브",      "parts",  32,  35, false },
{ MonsterGroup::Slime,  "하얀 슬라임",   140,  20, 10, 10, 10, "푸른 허브",      "parts",  34,  38, false },
{ MonsterGroup::Slime,  "불타는 슬라임", 150,  25,  8, 15, 10, "슬라임 부산물",  "parts",  36,  40, false },
{ MonsterGroup::Slime,  "검은 슬라임",   180,  30, 10, 15, 10, "슬라임 부산물",  "parts",  40,  50, false },
{ MonsterGroup::Slime,  "메탈 슬라임",    60,  10, 30, 30, 10, "슬라임 부산물",  "parts",  50,  60, false },
{ MonsterGroup::Slime,  "슬라임 킹",     300,  40, 15, 20, 30, "토벌 증서",    "license", 300, 100, true  },

// Undead 
{ MonsterGroup::Undead, "죽은 새",       100,  20,  5, 30, 10, "붉은 허브",      "parts",  50,  25, false },
{ MonsterGroup::Undead, "좀비",          140,  25, 10, 20, 10, "붉은 허브",      "parts",  55,  35, false },
{ MonsterGroup::Undead, "좀비 무리",     170,  30, 10, 20, 30, "언데드 부산물",  "parts",  60,  45, false },
{ MonsterGroup::Undead, "해골",          200,  35, 12, 25, 30, "언데드 부산물",  "parts",  65,  55, false },
{ MonsterGroup::Undead, "해골 궁수",     180,  40,  8, 30, 30, "언데드 부산물",  "parts",  65,  50, false },
{ MonsterGroup::Undead, "망령",          160,  28, 10, 25, 10, "언데드 부산물",  "parts",  60,  42, false },
{ MonsterGroup::Undead, "구울",          220,  30, 15, 15, 30, "푸른 허브",      "parts",  70,  60, false },
{ MonsterGroup::Undead, "리치",          250,  38, 10, 20, 30, "언데드 부산물",  "parts",  80,  70, false },
{ MonsterGroup::Undead, "크리처",        350,  45, 18, 30, 40, "토벌 증서",    "license", 600, 120, true  },

// Golem 
 { MonsterGroup::Golem,  "진흙 골렘",     130,  18, 15, 20, 10, "골렘의 핵",     "parts",  90,  30, false },
 { MonsterGroup::Golem,  "나무 골렘",     190,  28, 20, 20, 10, "붉은 허브",     "parts", 100,  50, false },
 { MonsterGroup::Golem,  "모래 골렘",     160,  22, 18, 20, 10, "골렘의 핵",     "parts",  95,  40, false },
 { MonsterGroup::Golem,  "이끼 골렘",     170,  20, 20, 15, 20, "붉은 허브",     "parts",  95,  45, false },
 { MonsterGroup::Golem,  "바위 골렘",     230,  35, 25, 30, 20, "붉은 허브",     "parts", 120,  65, false },
 { MonsterGroup::Golem,  "수정 골렘",     200,  25, 22, 15, 20, "붉은 허브",     "parts", 125,  55, false },
 { MonsterGroup::Golem,  "철 골렘",       260,  40, 28, 10, 30, "푸른 허브",     "parts", 140,  75, false },
 { MonsterGroup::Golem,  "거대 골렘",     400,  50, 30, 15, 30, "토벌 증서",   "license", 900, 150, true  },

 //finalboss
 { MonsterGroup::finalboss,    "마왕",   1000, 250,200, 50, 30, "토벌 증서",   "license",1000, 300, true  },

    };
    return monsters;
}

/*
// and then return Monster 
Monster CreateMonster(string name) {
    auto monsters = MonsterList();
    for (const auto& m : monsters) {
        if (m.name == name) {
            return Monster(m.group, m.name, m.hp, m.power, m.defence, m.speed, m.critical,
                m.dropName, m.dropCategory, m.dropGold,
                m.rewardExp, m.isBoss);
        }

    }
    const MonsterData& f = monsters[0];
    return Monster(f.group, f.name, f.hp, f.power, f.defence, f.speed, f.critical,
        f.dropName, f.dropCategory, f.dropGold, f.rewardExp, f.isBoss);

}
*/
