#include "TemplateInventory.h"
#include <string>
#pragma once

struct InventoryInfo {
	std::string name_;
	int count_;
};

extern Inventory<InventoryInfo> g_player_inventory;
extern Inventory<InventoryInfo> g_player_armory;

void AddItem(Inventory<InventoryInfo>& inven, const std::string name, int count);
bool RemoveItem(Inventory<InventoryInfo>& inven, const std::string name, int count);
bool CheckItem(const Inventory<InventoryInfo>& inven, const std::string name, int count);
void ViewInventory(const Inventory<InventoryInfo>& inven);