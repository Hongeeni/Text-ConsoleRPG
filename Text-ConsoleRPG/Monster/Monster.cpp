#include "monster.h"

Monster::Monster(MonsterGroup group, string name, int hp, int atk, int def, int spd,
    string dropName, string dropCategory, 
    int dropGold,int rewardExp, bool isBoss)
    : m_group(group), m_name(name), m_hp(hp), m_atk(atk), m_def(def),
    m_dropName(dropName), m_dropCategory(dropCategory),
    m_dropGold(dropGold), m_rewardExp(rewardExp),
    m_isBoss(isBoss)
{
}
