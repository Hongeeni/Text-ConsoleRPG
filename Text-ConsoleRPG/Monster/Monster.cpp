#include "monster.h"

Monster::Monster(MonsterGroup group, string name, int hp, int atk, int def,
    string dropName, string dropCategory, int dropPrice,
    int rewardExp, bool isBoss)
    : m_group(group), m_name(name), m_hp(hp), m_atk(atk), m_def(def),
    m_dropName(dropName), m_dropCategory(dropCategory),
    m_dropPrice(dropPrice), m_rewardExp(rewardExp),
    m_isBoss(isBoss)
{
}
