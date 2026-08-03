#include "item.h"

using namespace std;

Item::Item(string category, 
    string name, string description,
    int price, int count,
    int healHp, int healMp,
    int bonusHp, int bonusMp, int bonusPower, int bonusDefense, 
    int bonusCritical, int bonusSpeed)

    : m_category(category), 
    m_name(name), m_description(description), 
    m_price(price), m_count(count),
    m_healHp(healHp), m_healMp(healMp), 
    m_bonusHp(bonusHp), m_bonusMp(bonusMp), 
    m_bonusPower(bonusPower), m_bonusDefense(bonusDefense), 
    m_bonusCritical(bonusCritical), m_bonusSpeed(bonusSpeed)
{
}

void Item::PrintInfo() const {
    cout << m_name << " x" << m_count << " (" << m_price << "G) - " << m_description << endl;
}
