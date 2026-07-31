#pragma once
#include <string>

enum class MonsterGroup {
    Slime = 1,
    Undead = 2,
    Golem = 3
};

class Monster {
public:
    Monster(MonsterGroup group, std::string name, int hp, int atk, int def,
        std::string dropName, std::string dropCategory, int dropPrice,
        int rewardExp, bool isBoss);

    // group
    MonsterGroup GetGroup() const { return m_group; }

    // getter
    std::string GetName() const { return m_name; }
    int GetHP() const { return m_hp; }
    int GetATK() const { return m_atk; }
    int GetDEF() const { return m_def; }
    bool IsAlive() const { return m_hp > 0; }

    // boss check
    bool IsBoss() const { return m_isBoss; }


    // item, exp
    std::string GetDropName() const { return m_dropName; }
    std::string GetDropCategory() const { return m_dropCategory; }
    int GetDropPrice() const { return m_dropPrice; }
    int GetRewardExp() const { return m_rewardExp; }

private:
    std::string m_name;
    int m_hp;
    int m_atk;
    int m_def;

    bool m_isBoss;
    MonsterGroup m_group;

    std::string m_dropName;
    std::string m_dropCategory;
    int m_dropPrice;
    int m_rewardExp;
};
