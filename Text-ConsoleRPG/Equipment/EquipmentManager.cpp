#include "EquipmentManager.h"
#include "ItemData.h"
#include <iomanip>
#include <conio.h>
#include <iostream>

EquipmentSlots g_equip_slot;

bool EquipGear(Player& player, const EquipInfo& answer) {
    std::cout << "---------------------------------------------------------------------\n";
    if (answer.type_ == EquipType::Weapon) {
        if (!g_equip_slot.weapon.is_empty_()) {
            ApplyEquipStat(player, g_equip_slot.weapon.name_, false);   // 기존 장비 효과 해제
            std::cout << "[" << g_equip_slot.weapon.name_ << "]무기를 해제했습니다.\n";
            AddItem(g_player_armory, g_equip_slot.weapon.name_, 1);
        }
        g_equip_slot.weapon = answer;
        ApplyEquipStat(player, answer.name_, true);                     // 새 장비 효과 적용
        std::cout << "[" << g_equip_slot.weapon.name_ << "]무기를 장착했습니다.\n";
        std::cout << "---------------------------------------------------------------------\n";
        return true;
    }
    if (answer.type_ == EquipType::Armor) {
        if (!g_equip_slot.armor.is_empty_()) {
            ApplyEquipStat(player, g_equip_slot.armor.name_, false);
            std::cout << "[" << g_equip_slot.armor.name_ << "]방어구를 해제했습니다.\n";
            AddItem(g_player_armory, g_equip_slot.armor.name_, 1);
        }
        g_equip_slot.armor = answer;
        ApplyEquipStat(player, answer.name_, true);
        std::cout << "[" << g_equip_slot.armor.name_ << "]방어구를 장착했습니다.\n";
        std::cout << "---------------------------------------------------------------------\n";
        return true;
    }

    std::cout << "해당 아이템은 장착할 수 없습니다.\n";
    std::cout << "-------------------------------------------------------------------\n";
    return false;
}


bool UnequipGear(Player& player, const std::string& answer) {
    std::cout << "---------------------------------------------------------------------\n";
    if (answer == "weapon") {
        if (g_equip_slot.weapon.is_empty_()) {
            std::cout << "해제할 무기가 없습니다.\n";
            std::cout << "---------------------------------------------------------------------\n";
            _getch();
            return false;
        }
        ApplyEquipStat(player, g_equip_slot.weapon.name_, false);
        AddItem(g_player_armory, g_equip_slot.weapon.name_, 1);
        g_equip_slot.weapon = {"", EquipType::None};
        std::cout << "무기를 해제했습니다.\n";
        
        std::cout << "---------------------------------------------------------------------\n";
        _getch();
        return true;
    }
    if (answer == "armor") {
        if (g_equip_slot.armor.is_empty_()) {
            std::cout << "해제할 방어구가 없습니다.\n";
            std::cout << "---------------------------------------------------------------------\n";
            _getch();
            return false;
        }
        ApplyEquipStat(player, g_equip_slot.armor.name_, false);
        AddItem(g_player_armory, g_equip_slot.armor.name_, 1);
        g_equip_slot.armor = {"", EquipType::None};
        std::cout << "방어구를 해제했습니다.\n";
        std::cout << "---------------------------------------------------------------------\n";
        _getch();
        return true;
    }

    std::cout << "해제할 아이템이 없습니다.\n";
    std::cout << "-------------------------------------------------------------------\n";
    _getch();
    return false;
}

void DisplayEquipMenu(Player& player) {
    while (true) {
        system("cls");
        ViewInventory(g_player_armory);
        std::cout << "[장비 이름: 장착] [무기/방어구: 해제] [[0]: 돌아가기]" << std::endl;
        std::cout << ":: ";
        std::string answer;
        getline(std::cin, answer);
        if (answer == "0") {
            break;
        }
        if (answer == "무기") {
            UnequipGear(player, "weapon");
            continue;
        }
        else if (answer == "방어구") {
            UnequipGear(player, "armor");
            continue;
        }
        ItemData item_data = FindItem(answer);
        EquipType equip_type = EquipType::None;
        if (!item_data.found) {
            std::cout << "---------------------------------------------------------------------\n";
            std::cout << "해당 아이템을 찾을 수 없습니다.\n";
            std::cout << "---------------------------------------------------------------------\n";
            _getch();
            continue;
        }
        if (!CheckItem(g_player_armory, answer, 1)) {
            std::cout << "---------------------------------------------------------------------\n";
            std::cout << "그 아이템을 가지고 있지 않습니다..\n";
            std::cout << "---------------------------------------------------------------------\n";
            _getch();
            continue;
        }
        if (item_data.category == "weapon") {
            equip_type = EquipType::Weapon;
        }
        else if (item_data.category == "armor") {
            equip_type = EquipType::Armor;
        }
        else {
            std::cout << "---------------------------------------------------------------------\n";
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

