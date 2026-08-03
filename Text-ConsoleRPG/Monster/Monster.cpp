#include "monster.h"


Monster::Monster(MonsterGroup group, std::string name, int hp, int power, int defence, int speed, int critical,
    std::string dropName, std::string dropCategory, 
    int dropGold,int rewardExp, bool isBoss)
    : m_name(name), m_hp(hp), m_power(power), m_defence(defence), m_speed(speed), m_critical(critical),
    m_isBoss(isBoss), m_group(group),
    m_dropName(dropName), m_dropCategory(dropCategory),
    m_dropGold(dropGold), m_rewardExp(rewardExp)
{
}

bool Monster::GetDamage(int damageAmount) {
    m_hp = m_hp - damageAmount;
    if (m_hp < 0) m_hp = 0;
    return IsAlive();
}
