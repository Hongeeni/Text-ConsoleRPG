#pragma once
#include "Inventory.h"
#include <string>
#include <iostream>
#include "Player.h"
enum class EquipType {
	None,
	Weapon,
	Armor
};
struct EquipInfo {
	std::string name_ = ""; // "" mean = empty
	EquipType type_;
	bool is_empty_() const {
		return name_.empty();
	}
};
struct EquipmentSlots {
	EquipInfo weapon;
	EquipInfo armor;
};

extern EquipmentSlots g_equip_slot;

bool EquipGear(const EquipInfo& answer);
bool UnequipGear(const std::string& answer);
void DisplayEquipMenu();
