#pragma once
#include "TemplateInventory.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "Inventory.h"
#include "Player.h"
struct ShopItems {
	std::string name_;
	int count_;
};
struct ShopData {
	std::string shop_name_;
	std::string greet_;
	std::string description_;
	float multiple_; // increase item value (gold * multiple) in dungeon
	Inventory<ShopItems> items_;
};
//vector for shoplist
std::vector<ShopData> kShopList();
extern std::unordered_map<std::string, ShopData> g_map_shop;
//need to exec this when game started
void LoadShop();
ShopData FindShopData(const std::string name); //export shop datas

void AddGoods(const std::string& shop_name, const std::string& item_name, int count);
bool RemoveGoods(const std::string& shop_name, const std::string& item_name, int count);
bool CheckGoods(const std::string& shop_name, const std::string& item_name, int count);
void ViewShop(const std::string& shop_name, const std::string& name, Player& player);

bool SellItemMenu(Inventory<InventoryInfo>& inven, Player& player);

bool BuyItems(Inventory<InventoryInfo>& inven, Player& player, const std::string& shop_name, const std::string& item_name);
bool SellItems(Inventory<InventoryInfo>& inven, Player& player, const std::string& item_name);