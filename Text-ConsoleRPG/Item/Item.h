#pragma once

#include <string>
#include <iostream>

class Item {
public:
    Item(std::string category, 
        std::string name, std::string description,
        int price, int count, 
        int healHp, int healMp,
        int bonusHp, int bonusMp, int bonusAttack, int bonusDefense, int bonusCritical, int bonusSpeed);

    // getter
    std::string GetCategory() const { return m_category; }

    std::string GetName() const { return m_name; }
    std::string Getdescription() const { return m_description; }

    int GetBuyPrice() const { return m_price; }
    int GetSellPrice() const { return m_price / 2; }
    int GetCount() const { return m_count; }

    int GetHealHPAmount() const { return m_healHp; }
    int GetHealMPAmount() const { return m_healMp; }


    // equip bonus
    int GetBonusHp() const { return m_bonusHp; }
    int GetBonusMp() const { return m_bonusMp; }
    int GetBonusAttack() const { return m_bonusPower; }
    int GetBonusDefense() const { return m_bonusDefense; }
    int GetBonusCritical() const { return m_bonusCritical; }
    int GetBonusSpeed() const { return m_bonusSpeed; }

    // setter
    void AddCount(int amount) { m_count += amount; }
    void UseItem()         
        {
            if (m_category == "license") return;  // license 카테고리는 사용 불가 (개수가 줄어들지 않음)
            if (m_count > 0) m_count--;
        }

    bool IsEmpty() const { return m_count <= 0; }

    // print
    void PrintInfo() const;

private:
    std::string m_category;

    std::string m_name;
    std::string m_description;

    int m_price;
    int m_count;

    int m_healHp;
    int m_healMp;

    int m_bonusHp;
    int m_bonusMp;
    int m_bonusPower;
    int m_bonusDefense;
    int m_bonusCritical;
    int m_bonusSpeed;
};
