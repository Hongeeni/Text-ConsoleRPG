#pragma once
#include <string>

enum class MonsterGroup {
    Slime = 1,
    Undead = 2,
    Golem = 3
};

class Monster {
public:
    Monster(MonsterGroup group, std::string name, int hp, int atk, int def, int spd,
        std::string dropName, std::string dropCategory, int dropPrice,
        int rewardExp, bool isBoss);

    // group
    MonsterGroup GetGroup() const { return m_group; }

    // getter
    std::string GetName() const { return m_name; }
    int GetHP() const { return m_hp; }
    int GetATK() const { return m_atk; }
    int GetDEF() const { return m_def; }
    int GetSpd() const { return m_spd; }
    bool IsAlive() const { return m_hp > 0; }

    // boss check
    bool IsBoss() const { return m_isBoss; }


    // item, exp
    std::string GetDropName() const { return m_dropName; }
    std::string GetDropCategory() const { return m_dropCategory; }
    int GetDropGold() const { return m_dropGold; }
    int GetRewardExp() const { return m_rewardExp; }

private:
    std::string m_name;
    int m_hp;
    int m_atk;
    int m_def;
    int m_spd;

    bool m_isBoss;
    MonsterGroup m_group;

    std::string m_dropName;
    std::string m_dropCategory;
    int m_dropGold;
    int m_rewardExp;
};
