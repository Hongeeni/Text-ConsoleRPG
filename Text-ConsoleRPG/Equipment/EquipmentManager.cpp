#include "EquipmentManager.h"
#include "ItemData.h"
#include <iomanip>
#include <conio.h>
#include <iostream>

EquipmentSlots g_equip_slot;

struct EquipParts {
    EquipInfo* slot;
    std::string slot_name;
};


bool EquipGear(Player& player, const EquipInfo& answer) {
    static const std::unordered_map<EquipType, EquipParts> kSlotMap = {
    {EquipType::Weapon, {&g_equip_slot.weapon, "무기"}},
    {EquipType::Shield, {&g_equip_slot.armor, "방패"}},
    {EquipType::Armor, {&g_equip_slot.shield, "갑옷"}},
    {EquipType::Hands, {&g_equip_slot.hands, "장갑"}},
    {EquipType::Feet, {&g_equip_slot.feet, "신발"}},
    {EquipType::Ring, {&g_equip_slot.ring, "반지"}},
    };

    std::cout << "\n---------------------------------------------------------------------\n";
    auto it = kSlotMap.find(answer.type_);
    if (it == kSlotMap.end()) {
        std::cout << "해당 아이템은 장착할 수 없습니다.\n";
        std::cout << "-------------------------------------------------------------------\n";
        _getch();
        return false;
    }
    EquipInfo* gear_slot = it->second.slot;
    const std::string& slot_name = it->second.slot_name;
    std::cout << "\n---------------------------------------------------------------------\n";
    if (!gear_slot->is_empty_()) {
        ApplyEquipStat(player, gear_slot->name_, false);   // 기존 장비 효과 해제
        std::cout << "[" << gear_slot->name_ << "]" << slot_name <<"를 해제했습니다.\n";
        AddItem(g_player_armory, gear_slot->name_, 1);
    }
        *gear_slot = answer;
        ApplyEquipStat(player, answer.name_, true);                     // 새 장비 효과 적용
        std::cout << "[" << gear_slot->name_ << "]" << slot_name << "를 장착했습니다.\n";
        std::cout << "---------------------------------------------------------------------\n";
        return true;
   
}

bool UnequipGear(Player& player, const std::string& answer) {
    static const std::unordered_map<std::string, EquipParts> kSlotMap = {
    {"weapon", {&g_equip_slot.weapon, "무기"}},
    {"armor", {&g_equip_slot.armor, "갑옷"}},
    {"shield", {&g_equip_slot.shield, "방패"}},
    {"hands", {&g_equip_slot.hands, "장갑"}},
    {"feet", {&g_equip_slot.feet, "신발"}},
    {"ring", {&g_equip_slot.ring, "반지"}},
    };

    std::cout << "\n---------------------------------------------------------------------\n";
    auto it = kSlotMap.find(answer);
    if (it == kSlotMap.end()) {
        std::cout << "해제할 아이템이 없습니다.\n";
        std::cout << "-------------------------------------------------------------------\n";
        _getch();
        return false;
    }
    EquipInfo* gear_slot = it->second.slot;
    const std::string& slot_name = it->second.slot_name;
    if (gear_slot->is_empty_()) {
        std::cout << "해제할 " << slot_name << "가 없습니다.\n";
            std::cout << "---------------------------------------------------------------------\n";
            _getch();
            return false;
    }
        ApplyEquipStat(player, gear_slot->name_ , false);
        AddItem(g_player_armory, gear_slot->name_, 1);
        g_equip_slot.weapon = {"", EquipType::None};
        std::cout <<  slot_name <<"를 해제했습니다.\n";
        std::cout << "---------------------------------------------------------------------\n";
        _getch();
        return true;
}

void DisplayEquipMenu(Player& player) {
    const static std::unordered_map<std::string, std::string> kSlotName = {
        {"무기", "weapon"},
        {"갑옷", "armor"},
        {"방패", "shield"},
        {"장갑", "hands"},
        {"신발", "feet"},
        {"반지", "ring"},
    };
    while (true) {
        system("cls");
        ViewInventory(g_player_armory, false);
        std::cout << "[장비칸]\n";
        std::cout << "무기: [" << g_equip_slot.weapon.name_ << "]\n";
        std::cout << "방패: [" << g_equip_slot.shield.name_ << "]\n";
        std::cout << "갑옷: [" << g_equip_slot.armor.name_ << "]\n";
        std::cout << "장갑: [" << g_equip_slot.hands.name_ << "]\n";
        std::cout << "신발: [" << g_equip_slot.feet.name_ << "]\n";
        std::cout << "반지: [" << g_equip_slot.ring.name_ << "]\n";
        std::cout << "---------------------------------------------------------------------\n";
        std::cout << "[장비 이름: 장착] [장비칸: 해제] [[0]: 돌아가기]" << std::endl;
        std::cout << ":: ";
        std::string answer;
        getline(std::cin >> std::ws, answer);
            if (answer == "0") {
                break;
            }
            auto slot_name = kSlotName.find(answer);
            if (slot_name != kSlotName.end()) {
                UnequipGear(player, slot_name->second);
                continue;
            }
            
        ItemData item_data = FindItem(answer);
        EquipType equip_type = EquipType::None;
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
        if (item_data.category == "weapon") {
            equip_type = EquipType::Weapon;
        }
        else if (item_data.category == "armor") {
            equip_type = EquipType::Armor;
        }
        else {
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

