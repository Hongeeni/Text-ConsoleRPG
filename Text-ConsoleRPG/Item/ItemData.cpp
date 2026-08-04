#include "itemdata.h"

using namespace std;

vector<ItemData> ItemList() {
    vector<ItemData> items = {
        // category, name,              description,               price, healHp, healMp,      hp, mp, Power, Defense, Critical, Speed

        //other
        { "other", false , "정체를 알 수 없는 종이 #1", "아셨쬬?",              0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { "other", false ,"정체를 알 수 없는 종이 #2", "식사요정",             0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ "other", false ,"정체를 알 수 없는 종이 #3", "대머리",               0, 0, 0, 0, 0, 0, 0, 0, 0 },

        { "other",false , "정체를 알 수 없는 종이 #4", "cookie",               0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { "other",false , "정체를 알 수 없는 종이 #5", "목도리 토끼",          0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { "other",false , "정체를 알 수 없는 종이 #6", "코드카타 타이머",      0, 0, 0, 0, 0, 0, 0, 0, 0 },

        { "other",false , "정체를 알 수 없는 종이 #7", "진짜 아님",            0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { "other",false , "정체를 알 수 없는 종이 #8", "파란 종이",            0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { "other",false , "정체를 알 수 없는 종이 #9", "숙제입니다.",          0, 0, 0, 0, 0, 0, 0, 0, 0 },


        // Potions
        { "potion",false , "힐링 포션", "HP를 회복합니다. (+50)",       50, 50, 0,            0, 0, 0, 0, 0, 0 },
        { "potion",false , "마나 포션",   "MP를 회복합니다. (+50)",       50, 0, 30,            0, 0, 0, 0, 0, 0 },

        // License
        { "license",false , "토벌 증서",   "던전을 토벌한 증표입니다.",       0, 0, 0,            0, 0, 0, 0, 0, 0 },

        // Parts (monster drops)
        { "parts",false , "슬라임 부산물",  "슬라임의 조각입니다.",       10, 0, 0,             0, 0, 0, 0, 0, 0 },
        { "parts",false , "언데드 부산물", "언데드의 일부입니다.",        15, 0, 0,            0, 0, 0, 0, 0, 0 },
        { "parts",false , "크리처의 심장",   "크리처의 심장입니다.",    90, 0, 0,            0, 0, 0, 0, 0, 0 },
        { "parts",false , "골렘의 핵",  "골렘의 핵입니다.",         35, 0, 0,            0, 0, 0, 0, 0, 0 },

        // 포션 제작 재료
        { "parts",false , "붉은 허브",       "포션 제작에 사용됩니다.",       10, 0, 0,    0, 0, 0, 0, 0, 0 },
        { "parts",false , "푸른 허브",       "포션 제작에 사용됩니다.",       10, 0, 0,    0, 0, 0, 0, 0, 0 },

        // Weapon
        { "weapon",true, "호미",        "공격력을 올려줍니다. (+5)",              120, 0, 0,    0, 0, 5, 0, 0, 0 },
        { "weapon",true, "짧은 검",     "공격력을 올려줍니다. (+10)",             240, 0, 0,    0, 0, 10, 0, 0, 0 },
        { "weapon",true, "긴 검",       "공격력을 올려줍니다. (+20)",             480, 0, 0,    0, 0, 20, 0, 0, 0 },
        { "weapon",true, "양손검",      "공격력을 올려줍니다. (+30)",             720, 0, 0,    0, 0, 30, 0, 0, 0 },
        { "weapon",true, "미스릴 검",   "공격력을 올려줍니다. (+40)",             960, 0, 0,    0, 0, 40, 0, 0, 0 },
        { "weapon",true, "전설의 검",   "공격력을 올려줍니다. (+50)",            1200, 0, 0,    0, 0, 50, 0, 0, 0 },

        // Armor
        { "armor", true,"얇은 갑옷",       "최대 HP를 올려줍니다. (+5)",             100, 0, 0,    5, 0, 0, 0, 0, 0 },
        { "armor", true,"가죽 갑옷",       "최대 HP를 올려줍니다. (+10)",            200, 0, 0,    10, 0, 0, 0, 0, 0 },
        { "armor", true,"사슬 갑옷",       "최대 HP를 올려줍니다. (+20)",            400, 0, 0,    20, 0, 0, 0, 0, 0 },
        { "armor", true,"판금 갑옷",       "최대 HP를 올려줍니다. (+30)",            600, 0, 0,    30, 0, 0, 0, 0, 0 },
        { "armor", true,"미스릴 갑옷",     "최대 HP를 올려줍니다. (+40)",            800, 0, 0,    40, 0, 0, 0, 0, 0 },
        { "armor", true,"전설의 갑옷",     "최대 HP를 올려줍니다. (+50)",           1000, 0, 0,    50, 0, 0, 0, 0, 0 },

        { "ring",true, "고철 반지",         "최대 MP를 올려줍니다. (+5)",         150, 0, 0,    0, 5, 0, 0, 0, 0 },
        { "ring",true, "순은 반지",     "최대 MP를 올려줍니다. (+10)",            300, 0, 0,    0, 10, 0, 0, 0, 0 },
        { "ring",true, "도금 반지",         "최대 MP를 올려줍니다. (+20)",        600, 0, 0,    0, 20, 0, 0, 0, 0 },
        { "ring",true, "순금 반지",     "최대 MP를 올려줍니다. (+30)",            900, 0, 0,    0, 30, 0, 0, 0, 0 },
        { "ring",true, "미스릴 반지",     "최대 MP를 올려줍니다. (+40)",         1200, 0, 0,    0, 40, 0, 0, 0, 0 },
        { "ring",true, "전설의 반지",  "최대 MP를 올려줍니다. (+50)",            1500, 0, 0,    0, 50, 0, 0, 0, 0 },

        { "shield",true, "얇은 방패",       "방어력을 올려줍니다. (+5)",              140, 0, 0,    0, 0, 0, 5, 0, 0 },
        { "shield",true, "나무 방패",       "방어력을 올려줍니다. (+10)",             280, 0, 0,    0, 0, 0, 10, 0, 0 },
        { "shield",true, "가죽 방패",       "방어력을 올려줍니다. (+20)",             560, 0, 0,    0, 0, 0, 20, 0, 0 },
        { "shield",true, "사슬 방패",       "방어력을 올려줍니다. (+30)",             840, 0, 0,    0, 0, 0, 30, 0, 0 },
        { "shield",true, "판금 방패",       "방어력을 올려줍니다. (+40)",            1120, 0, 0,    0, 0, 0, 40, 0, 0 },
        { "shield",true, "전설의 방패",     "방어력을 올려줍니다. (+50)",            1400, 0, 0,    0, 0, 0, 50, 0, 0 },

        { "hands",true, "면 장갑",      "치명타 확률을 올려줍니다. (+5)",             110, 0, 0,    0, 0, 0, 0, 5, 0 },
        { "hands",true, "가죽 장갑",    "치명타 확률을 올려줍니다. (+10)",            220, 0, 0,    0, 0, 0, 0, 10, 0 },
        { "hands",true, "사슬 장갑",    "치명타 확률을 올려줍니다. (+20)",            440, 0, 0,    0, 0, 0, 0, 20, 0 },
        { "hands",true, "판금 장갑",    "치명타 확률을 올려줍니다. (+30)",            660, 0, 0,    0, 0, 0, 0, 30, 0 },
        { "hands",true, "미스릴 장갑",  "치명타 확률을 올려줍니다. (+40)",            880, 0, 0,    0, 0, 0, 0, 40, 0 },
        { "hands",true, "전설의 장갑",  "치명타 확률을 올려줍니다. (+50)",           1100, 0, 0,    0, 0, 0, 0, 50, 0 },

        { "feet",true, "얇은 신발",   "속도를 올려줍니다. (+5)",                    130, 0, 0,    0, 0, 0, 0, 0, 5},
        { "feet",true, "가죽 신발",   "속도를 올려줍니다. (+10)",                   260, 0, 0,    0, 0, 0, 0, 0, 10 },
        { "feet",true, "사슬 신발",   "속도를 올려줍니다. (+20)",                   520, 0, 0,    0, 0, 0, 0, 0, 20 },
        { "feet",true, "판금 신발",   "속도를 올려줍니다. (+30)",                   780, 0, 0,    0, 0, 0, 0, 0, 30 },
        { "feet",true, "미스릴 신발", "속도를 올려줍니다. (+40)",                  1040, 0, 0,    0, 0, 0, 0, 0, 40 },
        { "feet",true, "전설의 신발", "속도를 올려줍니다. (+50)",                  1300, 0, 0,    0, 0, 0, 0, 0, 50 },

    };
    return items;
}

Item CreateItem(string name, int count) {
    auto items = ItemList();
    for (const auto& i : items) {
        if (i.name == name) {
            return Item(i.category, i.name, i.description,
                i.price, count,
                i.healHp, i.healMp,
                i.bonusHp, i.bonusMp, i.bonusPower,
                i.bonusDefense, i.bonusCritical, i.bonusSpeed);
        }
    }
    auto first = items[0];
    return Item(first.category, first.name, first.description,
        first.price, count,
        first.healHp, first.healMp,
        first.bonusHp, first.bonusMp, first.bonusPower,
        first.bonusDefense, first.bonusCritical, first.bonusSpeed);
}

unordered_map<string, ItemData> GetItemMap() {
    auto items = ItemList();
    unordered_map<string, ItemData> itemMap;

    for (const auto& i : items) {
        itemMap[i.name] = i;    // 이름을 key로 저장
    }

    return itemMap;
}

ItemData FindItem(const string& name) {
    auto itemMap = GetItemMap();
    auto it = itemMap.find(name);

    if (it != itemMap.end()) {
		ItemData data = it->second;
		data.found = true; // 아이템을 찾았음을 표시
        return data;      
    }

    ItemData empty{};
    return empty;
}
