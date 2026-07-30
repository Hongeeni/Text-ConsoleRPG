#pragma once
#include <string>
#include <iostream>

// ¾îÄ¯
class Item {
public:
    Item(int id, std::string name, std::string category, int price, 
        int healAmount, int count, std::string desc);

    // getter
    int GetID() const { return m_id; }
    std::string GetName() const { return m_name; }
    std::string GetCategory() const { return m_category; }
    int GetPrice() const { return m_price; }
    int GetHealAmount() const { return m_healAmount; }
    int GetCount() const { return m_count; }
    std::string GetDesc() const { return m_desc; }

    // setter
    void AddCount(int amount) { m_count += amount; }
    bool IsEmpty() const { return m_count <= 0; }

    // Ãâ·Â
    void PrintInfo() const;

private:
    int m_id;
    std::string m_name;
    std::string m_category;
    int m_price;
    int m_healAmount;
    int m_count;
    std::string m_desc;

};
 