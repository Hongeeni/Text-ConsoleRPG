#pragma once
#include "TemplateInventory.h"
#include <string>


struct InventoryInfo {
	std::string name_;
	int count_;
};

extern Inventory<InventoryInfo> g_player_inventory;
extern Inventory<InventoryInfo> g_player_armory;

void AddItem(Inventory<InventoryInfo>& inven, const std::string name, int count);
bool RemoveItem(Inventory<InventoryInfo>& inven, const std::string name, int count);
bool CheckItem(const Inventory<InventoryInfo>& inven, const std::string name, int count);
int ViewInventory(const Inventory<InventoryInfo>& inven, bool on_battle);
class Player;
bool BattleInventory(Player& player);
void RunInventory(Player& player);
bool UseItemOnPlayer(Inventory<InventoryInfo>& inven, Player& player, const std::string& name);