#pragma once
#include <string>

enum class MonsterGroup {
    Slime = 1,
    Undead = 2,
    Golem = 3,
    finalboss = 4
};

class Monster {
public:
    Monster(MonsterGroup group, std::string name, int hp, int power, int defence, int speed, int critical,
        std::string dropName, std::string dropCategory, int dropPrice,
        int rewardExp, bool isBoss);

    // group
    MonsterGroup GetGroup() const { return m_group; }

    // getter
    std::string GetName() const { return m_name; }
    int GetHP() const { return m_hp; }
    int GetPower() const { return m_power; }
    int GetDefence() const { return m_defence; }
    int GetSpeed() const { return m_speed; }
	int GetCritical() const { return m_critical; }
    bool IsAlive() const { return m_hp > 0; }

    // boss check
    bool IsBoss() const { return m_isBoss; }


    // item, exp
    std::string GetDropName() const { return m_dropName; }
    std::string GetDropCategory() const { return m_dropCategory; }
    int GetDropGold() const { return m_dropGold; }
    int GetRewardExp() const { return m_rewardExp; }

    // damage
    bool GetDamage(int damageAmount);


private:
    std::string m_name;
    int m_hp;
    int m_power;
    int m_defence;
    int m_speed;
	int m_critical;

    bool m_isBoss;
    MonsterGroup m_group;

    std::string m_dropName;
    std::string m_dropCategory;
    int m_dropGold;
    int m_rewardExp;
};
