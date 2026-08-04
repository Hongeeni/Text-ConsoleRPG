#include "monsterdata.h"

using namespace std;

vector<MonsterData> MonsterList() {
    vector<MonsterData> monsters = {
        // group, name,          hp, power, def, spd, crit, dropitemname,    category, gold, exp, isboss
// Slime
{ MonsterGroup::Slime,  "작은 슬라임",    90,  20,  5,  5, 10, "슬라임 부산물",  "parts",   25,  20, false },
{ MonsterGroup::Slime,  "독 슬라임",     115,  25,  5, 10, 10, "붉은 허브",      "parts",   28,  25, false },
{ MonsterGroup::Slime,  "슬라임 무리",   140,  25,  8,  5, 10, "붉은 허브",      "parts",   30,  30, false },
{ MonsterGroup::Slime,  "얼음 슬라임",   150,  30,  8, 10, 10, "푸른 허브",      "parts",   32,  35, false },
{ MonsterGroup::Slime,  "하얀 슬라임",   160,  25, 10, 10, 10, "푸른 허브",      "parts",   34,  38, false },
{ MonsterGroup::Slime,  "불타는 슬라임", 175,  35,  8, 15, 10, "슬라임 부산물",  "parts",   36,  40, false },
{ MonsterGroup::Slime,  "검은 슬라임",   205,  40, 10, 15, 10, "슬라임 부산물",  "parts",   40,  50, false },
{ MonsterGroup::Slime,  "메탈 슬라임",    60,  10, 30, 30, 10, "슬라임 부산물",  "parts",   50,  60, false },
{ MonsterGroup::Slime,  "슬라임 킹",     345,  50, 15, 20, 30, "토벌 증서",    "license",  300, 100, true  },

// Undead
{ MonsterGroup::Undead, "죽은 새",       115,  25,  5, 30, 10, "붉은 허브",      "parts",   50,  25, false },
{ MonsterGroup::Undead, "좀비",          160,  35, 10, 20, 10, "붉은 허브",      "parts",   55,  35, false },
{ MonsterGroup::Undead, "좀비 무리",     195,  40, 10, 20, 30, "언데드 부산물",  "parts",   60,  45, false },
{ MonsterGroup::Undead, "해골",          230,  45, 12, 25, 30, "언데드 부산물",  "parts",   65,  55, false },
{ MonsterGroup::Undead, "해골 궁수",     205,  50,  8, 30, 30, "언데드 부산물",  "parts",   65,  50, false },
{ MonsterGroup::Undead, "망령",          185,  35, 10, 25, 10, "언데드 부산물",  "parts",   60,  42, false },
{ MonsterGroup::Undead, "구울",          255,  40, 15, 15, 30, "푸른 허브",      "parts",   70,  60, false },
{ MonsterGroup::Undead, "리치",          290,  50, 10, 20, 30, "푸른 허브",      "parts",   80,  70, false },
{ MonsterGroup::Undead, "크리처",        400,  60, 18, 30, 40, "토벌 증서",    "license",  600, 120, true  },

// Golem
{ MonsterGroup::Golem,  "진흙 골렘",     150,  25, 15, 20, 10, "골렘의 핵",      "parts",   90,  30, false },
{ MonsterGroup::Golem,  "나무 골렘",     220,  35, 20, 20, 10, "붉은 허브",      "parts",  100,  50, false },
{ MonsterGroup::Golem,  "모래 골렘",     185,  30, 18, 20, 10, "골렘의 핵",      "parts",   95,  40, false },
{ MonsterGroup::Golem,  "이끼 골렘",     195,  25, 20, 15, 20, "붉은 허브",      "parts",   95,  45, false },
{ MonsterGroup::Golem,  "바위 골렘",     265,  45, 25, 30, 20, "붉은 허브",      "parts",  120,  65, false },
{ MonsterGroup::Golem,  "수정 골렘",     230,  35, 22, 15, 20, "붉은 허브",      "parts",  125,  55, false },
{ MonsterGroup::Golem,  "철 골렘",       300,  50, 28, 10, 30, "푸른 허브",      "parts",  140,  75, false },
{ MonsterGroup::Golem,  "거대 골렘",     460,  65, 30, 15, 30, "토벌 증서",    "license", 900, 150, true  },

// finalboss
{ MonsterGroup::finalboss, "마왕",      1000, 250, 200, 50, 30, "토벌 증서",   "license",1000, 300, true  },

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
