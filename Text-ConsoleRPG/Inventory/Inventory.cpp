#include "Inventory.h"
#include "Item/Itemdata.h"
#include "Player/Player.h"
#include <iomanip>
#include <iostream>


Inventory<InventoryInfo> g_player_armory;
Inventory<InventoryInfo> g_player_inventory;

void AddItem(Inventory<InventoryInfo>& inven, const std::string name, int count) {
	inven.Add(name, count);
}
bool RemoveItem(Inventory<InventoryInfo>& inven, const std::string name, int count) {
	return inven.Remove(name, count);
}
bool CheckItem(const Inventory<InventoryInfo>& inven, const std::string name, int count) {
	return inven.Check(name, count);
}
void ViewInventory(const Inventory<InventoryInfo>& inven) {
	std::cout << "==========================================================================\n";
	std::cout << std::left << std::setw(6) << "[번호]"
		<< std::left << std::setw(30) << "[이름]"
		<< std::left << std::setw(8) << "[개수]"
		<< "[설명]"
		<< std::endl;
	std::cout << "--------------------------------------------------------------------------\n";
	int number = 1;
	for (const auto& i : inven.ViewInventory()) {
		ItemData data = FindItem(i.name_);
		std::cout << std::left << std::setw(6) << number
			<< std::left << std::setw(30) << i.name_
			<< std::left << std::setw(8) << i.count_
			<< (data.found ? data.description : "")
			<< std::endl;
		++number;
	}
	std::cout << "==========================================================================\n";
}

bool UseItemOnPlayer(Inventory<InventoryInfo>& inven, Player& player, const std::string& name) {
	if (!CheckItem(inven, name, 1)) {
		return false;
	}

	ItemData data = FindItem(name);
	if (!data.found) {
		return false;
	}

	if (data.healHp <= 0 && data.healMp <= 0) {
		return false;
	}

	if (data.healHp > 0) player.HpRecovery(data.healHp);
	if (data.healMp > 0) player.MpRecovery(data.healMp);

	RemoveItem(inven, name, 1);
	return true;
}