#include "item.h"

//¾îÄ¯
using namespace std;

Item::Item(int id, string name, string category, int price, int healAmount, string desc, int count)
    : m_id(id), m_name(name), m_category(category), m_price(price),
    m_healAmount(healAmount), m_desc(desc), m_count(count)
{
}

void Item::PrintInfo() const {
    cout << m_name << " x" << m_count << " (" << m_price << "G) - " << m_desc << endl;
}
 