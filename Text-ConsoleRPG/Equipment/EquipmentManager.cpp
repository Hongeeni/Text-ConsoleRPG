#include "EquipmentManager.h"
#include "ItemData.h"
#include <iomanip>
#include <conio.h>
#include <iostream>

EquipmentSlots g_equip_slot;

EquipType CategoryToEquipType(const std::string& category) {
    if (category == "weapon") return EquipType::Weapon;
    if (category == "shield") return EquipType::Shield;
    if (category == "armor")  return EquipType::Armor;
    if (category == "ring")   return EquipType::Ring;
    if (category == "gloves") return EquipType::Gloves;
    if (category == "shoes")  return EquipType::Shoes;
    return EquipType::None;
}

EquipInfo* SlotOf(EquipType type) {
    switch (type) {
    case EquipType::Weapon: return &g_equip_slot.weapon;
    case EquipType::Shield: return &g_equip_slot.shield;
    case EquipType::Armor:  return &g_equip_slot.armor;
    case EquipType::Ring:   return &g_equip_slot.ring;
    case EquipType::Gloves: return &g_equip_slot.gloves;
    case EquipType::Shoes:  return &g_equip_slot.shoes;
    default: return nullptr;
    }
}

std::string EquipTypeName(EquipType type) {
    switch (type) {
    case EquipType::Weapon: return "무기";
    case EquipType::Shield: return "방패";
    case EquipType::Armor:  return "갑옷";
    case EquipType::Ring:   return "반지";
    case EquipType::Gloves: return "장갑";
    case EquipType::Shoes:  return "신발";
    default: return "없음";
    }
}

bool EquipGear(Player& player, const EquipInfo& answer) {
    EquipInfo* slot = SlotOf(answer.type_);
    std::cout << "\n---------------------------------------------------------------------\n";

    if (slot == nullptr) {
        std::cout << "해당 아이템은 장착할 수 없습니다.\n";
        std::cout << "---------------------------------------------------------------------\n";
        return false;
    }

    const std::string part = EquipTypeName(answer.type_);

    if (!slot->is_empty_()) {
        ApplyEquipStat(player, slot->name_, false);
        AddItem(g_player_armory, slot->name_, 1);
        std::cout << "[" << slot->name_ << "]" << part << "를 해제했습니다.\n";
    }

    *slot = answer;
    ApplyEquipStat(player, answer.name_, true);
    std::cout << "[" << answer.name_ << "]" << part << "를 장착했습니다.\n";
    std::cout << "---------------------------------------------------------------------\n";
    return true;
}

bool UnequipGear(Player& player, const std::string& answer) {
    EquipType type = EquipType::None;
    if (answer == "무기")      type = EquipType::Weapon;
    else if (answer == "방패") type = EquipType::Shield;
    else if (answer == "갑옷") type = EquipType::Armor;
    else if (answer == "반지") type = EquipType::Ring;
    else if (answer == "장갑") type = EquipType::Gloves;
    else if (answer == "신발") type = EquipType::Shoes;

    EquipInfo* slot = SlotOf(type);
    std::cout << "\n---------------------------------------------------------------------\n";

    if (slot == nullptr) {
        std::cout << "해제할 아이템이 없습니다.\n";
        std::cout << "---------------------------------------------------------------------\n";
        _getch();
        return false;
    }
    if (slot->is_empty_()) {
        std::cout << "해제할 " << EquipTypeName(type) << "가 없습니다.\n";
        std::cout << "---------------------------------------------------------------------\n";
        _getch();
        return false;
    }

    ApplyEquipStat(player, slot->name_, false);
    AddItem(g_player_armory, slot->name_, 1);
    std::cout << "[" << slot->name_ << "]" << EquipTypeName(type) << "를 해제했습니다.\n";
    *slot = EquipInfo{ "", EquipType::None };
    std::cout << "---------------------------------------------------------------------\n";
    _getch();
    return true;
}

void DisplayEquipMenu(Player& player) {
    while (true) {
        system("cls");
        ViewInventory(g_player_armory, false);
        std::cout << "[장비칸]\n";
        std::cout << "무기: [" << g_equip_slot.weapon.name_ << "]  "
            << "방패: [" << g_equip_slot.shield.name_ << "]  "
            << "갑옷: [" << g_equip_slot.armor.name_ << "]\n";
        std::cout << "반지: [" << g_equip_slot.ring.name_ << "]  "
            << "장갑: [" << g_equip_slot.gloves.name_ << "]  "
            << "신발: [" << g_equip_slot.shoes.name_ << "]\n";
        std::cout << "---------------------------------------------------------------------\n";
        std::cout << "[장비 이름: 장착] [무기/방패/갑옷/반지/장갑/신발: 해제] [[0]: 돌아가기]" << std::endl;
        std::cout << ":: ";

        std::string answer;
        getline(std::cin >> std::ws, answer);
        if (!std::cin) return;
        if (answer == "0") {
            break;
        }
        if (answer == "무기" || answer == "방패" || answer == "갑옷"
            || answer == "반지" || answer == "장갑" || answer == "신발") {
            UnequipGear(player, answer);
            continue;
        }

        ItemData item_data = FindItem(answer);
        if (!item_data.found) {
            std::cout << "\n---------------------------------------------------------------------\n";
            std::cout << "해당 아이템을 찾을 수 없습니다.\n";
            std::cout << "---------------------------------------------------------------------\n";
            _getch();
            continue;
        }
        if (!CheckItem(g_player_armory, answer, 1)) {
            std::cout << "\n---------------------------------------------------------------------\n";
            std::cout << "그 아이템을 가지고 있지 않습니다..\n";
            std::cout << "---------------------------------------------------------------------\n";
            _getch();
            continue;
        }

        EquipType equip_type = CategoryToEquipType(item_data.category);
        if (equip_type == EquipType::None) {
            std::cout << "\n---------------------------------------------------------------------\n";
            std::cout << "잘못된 아이템을 입력했습니다.\n";
            std::cout << "---------------------------------------------------------------------\n";
            _getch();
            continue;
        }

        EquipInfo equip_info = { item_data.name, equip_type };
        if (EquipGear(player, equip_info)) {
            RemoveItem(g_player_armory, item_data.name, 1);
        }
        _getch();
        continue;
    }
}

void ApplyEquipStat(Player& player, const std::string& item_name, bool equip) {
    ItemData data = FindItem(item_name);
    if (!data.found) return;

    const int sign = equip ? 1 : -1;   // 장착이면 +, 해제면 -

    if (data.bonusPower != 0) {
        player.SetPower(player.GetPower() + data.bonusPower * sign);
    }
    if (data.bonusDefense != 0) {
        player.SetDefense(player.GetDefense() + data.bonusDefense * sign);
    }
    if (data.bonusCritical != 0) {
        player.SetCritical(player.GetCritical() + data.bonusCritical * sign);
    }
    if (data.bonusSpeed != 0) {
        player.SetSpeed(player.GetSpeed() + data.bonusSpeed * sign);
    }
    if (data.bonusHp != 0) {
        // 최대 HP만 조정하고 현재 HP는 그대로 둔다
        player.SetHp(player.GetCurrentHp(), player.GetMaxHp() + data.bonusHp * sign);
    }
    if (data.bonusMp != 0) {
        player.SetMp(player.GetCurrentMp(), player.GetMaxMp() + data.bonusMp * sign);
    }

    // 해제로 최대치가 낮아졌을 때 현재값이 넘치지 않게 보정
    if (player.GetCurrentHp() > player.GetMaxHp()) {
        player.SetHp(player.GetMaxHp());
    }
    if (player.GetCurrentMp() > player.GetMaxMp()) {
        player.SetMp(player.GetMaxMp());
    }
}

