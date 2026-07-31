#pragma once

#include <string>
#include <iostream>

class Item {
public:
    Item(int id, std::string category, 
        std::string name, std::string desc,
        int price, int count, 
        int healHp, int healMp,
        int bonusHp, int bonusMp, int bonusAtk, int bonusDef, int bonusCrit, int bonusSpd);

    // getter
    int GetID() const { return m_id; }
    std::string GetCategory() const { return m_category; }

    std::string GetName() const { return m_name; }
    std::string GetDesc() const { return m_desc; }

    int GetPrice() const { return m_price; }
    int GetCount() const { return m_count; }

    int GetHealHPAmount() const { return m_healHp; }
    int GetHealMPAmount() const { return m_healMp; }


    // equip bonus
    int GetBonusHp() const { return m_bonusHp; }
    int GetBonusMp() const { return m_bonusMp; }
    int GetBonusAtk() const { return m_bonusAtk; }
    int GetBonusDef() const { return m_bonusDef; }
    int GetBonusCrit() const { return m_bonusCrit; }
    int GetBonusSpd() const { return m_bonusSpd; }

    // setter
    void AddCount(int amount) { m_count += amount; }
    void UseItem() { if (m_count > 0) m_count--; }
    bool IsEmpty() const { return m_count <= 0; }

    // print
    void PrintInfo() const;

private:
    int m_id;
    std::string m_category;

    std::string m_name;
    std::string m_desc;

    int m_price;
    int m_count;

    int m_healHp;
    int m_healMp;

    int m_bonusHp;
    int m_bonusMp;
    int m_bonusAtk;
    int m_bonusDef;
    int m_bonusCrit;
    int m_bonusSpd;
};
