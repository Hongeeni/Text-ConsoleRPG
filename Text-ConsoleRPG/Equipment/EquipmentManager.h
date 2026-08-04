#pragma once
#include "Inventory.h"
#include <string>
#include <iostream>
#include "Player.h"
enum class EquipType {
	None,
	Weapon,
	Shield,
	Armor,
	Hands,
	Feet,
	Ring
};
struct EquipInfo {
	std::string name_ = "";
	EquipType type_ = EquipType::None;
	bool is_empty_() const {
		return name_.empty();
	}
};
struct EquipmentSlots {
	EquipInfo weapon, shield, armor, ring, hands, feet;
	};

extern EquipmentSlots g_equip_slot;

bool EquipGear(Player& player, const EquipInfo& answer);
bool UnequipGear(Player& player, const std::string& answer);
void DisplayEquipMenu(Player& player);

EquipType CategoryToEquipType(const std::string& category);
EquipInfo* SlotOf(EquipType type);
std::string EquipTypeName(EquipType type);

// 장비 스탯을 플레이어에 반영(equip=true)하거나 되돌림(equip=false)
void ApplyEquipStat(Player& player, const std::string& item_name, bool equip);
