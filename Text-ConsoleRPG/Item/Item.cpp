#include "item.h"

using namespace std;

Item::Item(string category, 
    string name, string desc,
    int price, int count,
    int healHp, int healMp,
    int bonusHp, int bonusMp, int bonusAtk, int bonusDef, int bonusCrit, int bonusSpd)

    : m_id(id), m_category(category), 
    m_name(name), m_price(price),
    m_healHp(healHp), m_healMp(healMp), m_desc(desc), m_count(count),
    m_bonusHp(bonusHp), m_bonusMp(bonusMp), m_bonusAtk(bonusAtk),
    m_bonusDef(bonusDef), m_bonusCrit(bonusCrit), m_bonusSpd(bonusSpd)
{
}

void Item::PrintInfo() const {
    cout << m_name << " x" << m_count << " (" << m_price << "G) - " << m_desc << endl;
}
