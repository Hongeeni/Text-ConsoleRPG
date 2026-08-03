
#include "monster.h"


Monster::Monster(MonsterGroup group, string name, int hp, int attack, int defence, int speed,
    std::string dropName, std::string dropCategory, 
    int dropGold,int rewardExp, bool isBoss)
    : m_group(group), m_name(name), m_hp(hp), m_attack(attack), m_defence(defence), m_speed(speed),
    m_dropName(dropName), m_dropCategory(dropCategory),
    m_dropGold(dropGold), m_rewardExp(rewardExp),S
    m_isBoss(isBoss)
{
}

bool Monster::GetDamage(int damageAmount) {
    m_hp = m_hp - damageAmount;
    if (m_hp < 0) m_hp = 0;
    return IsAlive();
}
