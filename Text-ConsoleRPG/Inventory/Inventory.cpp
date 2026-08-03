#include "Inventory.h"
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
	std::cout << "=========================================================\n";
	std::cout << std::left << std::setw(5) << "[번호]"
		<< std::left << std::setw(12) << "[이름]"
		<< std::left << std::setw(12) << "[개수]"
		<< std::endl;
	std::cout << "---------------------------------------------------------\n";
	int number = 1;
	for (const auto& i : inven.ViewInventory()) {
		std::cout << std::left << std::setw(5) <<  number
			<< std::left << std::setw(12) << i.name_
			<< std::left << std::setw(12) << i.count_
			<< std::endl;
		++number;
	}
	std::cout << "=========================================================\n";
}