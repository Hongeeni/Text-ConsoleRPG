#include "itemdata.h"

using namespace std;

vector<ItemData> ItemList() {
    vector<ItemData> items = {
        // category, name,              desc,               price, healHp, healMp,      hp, mp, atk, def, crit, spd

        // Potions
        { "potion", "Health Potion", "Restores HP +50",       50, 50, 0,            0, 0, 0, 0, 0, 0 },
        { "potion", "Mana Potion",   "Restores MP +30",       50, 0, 30,            0, 0, 0, 0, 0, 0 },

        // Parts (monster drops)
        { "parts", "Slime Jelly",  "Jelly from slimes",       10, 0, 0,             0, 0, 0, 0, 0, 0 },
        { "parts", "Rotten Flesh", "Flesh from undead",        15, 0, 0,            0, 0, 0, 0, 0, 0 },
        { "parts", "Dark Heart",   "Heart of the creature",    90, 0, 0,            0, 0, 0, 0, 0, 0 },
        { "parts", "Golem Heart",  "Heart of a golem",         35, 0, 0,            0, 0, 0, 0, 0, 0 },

        // Equips
        { "equip", "Basic Armor",    "Add HP +5",             100, 0, 0,            5, 0, 0, 0, 0, 0 },
        { "equip", "Silver Ring",    "Add MP +5",             150, 0, 0,            0, 5, 0, 0, 0, 0 },
        { "equip", "Short Sword",    "Add Atk +5",            120, 0, 0,            0, 0, 5, 0, 0, 0 },
        { "equip", "Leather Shield", "Add Def +5",            140, 0, 0,            0, 0, 0, 5, 0, 0 },
        { "equip", "Feather Boots",  "Add Crit +5",           130, 0, 0,            0, 0, 0, 0, 5, 0 },
        { "equip", "Cotten Gloves",  "Add Spd +5",            110, 0, 0,            0, 0, 0, 0, 0, 5 },
    };
    return items;
}

Item CreateItem(string name, int count) {
    auto items = ItemList();
    for (const auto& i : items) {
        if (i.name == name) {
            return Item(i.category, i.name, i.desc,
                i.price, count,
                i.healHp, i.healMp,
                i.bonusHp, i.bonusMp, i.bonusAtk,
                i.bonusDef, i.bonusCrit, i.bonusSpd);
        }
    }
    auto first = items[0];
    return Item(first.category, first.name, first.desc,
        first.price, count,
        first.healHp, first.healMp,
        first.bonusHp, first.bonusMp, first.bonusAtk,
        first.bonusDef, first.bonusCrit, first.bonusSpd);
}
