#include "Shop.h"
#include <iostream>
#include <iomanip>
#include <conio.h>

std::vector<ShopData> kShopList() {
	std::vector<ShopData> shops = {
		{"Normal Shop", "Hello.", "Town Shop",  1,{
			{"Health Potion", 5},
			{"Mana Potion", 5},
		}},
		{"Slime Shop", "Hello", "Slime Dungeon Shop", 1.5,{
			{"Health Potion", 5},
			{"Mana Potion", 5},
		}},
		{"Undead Dungeon Shop", "Welcome", "Undead Shop",  2, {
			{"Health Potion", 5},
			{"Mana Potion", 5},
		}},
		{"Stone Shop", "Greeting.", "Golem Shop.",  2,{
			{"Health Potion", 5},
			{"Mana Potion", 5},
		}}
	};
	return shops;
}
std::unordered_map<std::string, ShopData> g_map_shop;
void LoadShop() {
	for (const auto& shop : kShopList()) {
		g_map_shop[shop.shop_name_] = shop;
	}
}
ShopData FindShopData(const std::string name) {
	std::vector<ShopData> shops = kShopList();
	for (const auto& s : shops) {
		if (s.shop_name_ == name) {
			return s;
		}
	}
	return shops[0];
}
void AddGoods(const std::string& shop_name, const std::string& item_name, int count) {
	g_map_shop.at(shop_name).items_.Add(item_name, count);
}
bool RemoveGoods(const std::string& shop_name, const std::string& item_name, int count) {
	return g_map_shop.at(shop_name).items_.Remove(item_name, count);
}
bool CheckGoods(const std::string& shop_name, const std::string& item_name, int count) {
	return g_map_shop.at(shop_name).items_.Check(item_name, count);
}

bool BuyItems(Inventory<InventoryInfo>& inven, Player& player, const std::string& shop_name, const std::string& item_name) {

	bool existed = CheckGoods(shop_name, item_name, 1);
	if (!existed) {
		std::cout << "---------------------------------------------------------------------\n";
		std::cout << "Can not find that item.\n";
		std::cout << "---------------------------------------------------------------------\n";
		_getch();
		return false;
	}
	// int d = FindItem(item_name); 
	// ItemInfo data = GetItemData(d); !Need a function that bring item informations
	// if (data.buy_value > playe.GetPlayerGold()) {
	//	cout << "---------------------------------------------------------------------\n";
	//	cout << "You don't have enough gold.\n";
	//	cout << "---------------------------------------------------------------------\n";
	//	
	//	return false;
	//}
	//ItemInfo data = GetItemData[item_name]; !Need a function that bring item informations
	// RemoveGoods(shop_name, data.name, 1);
	// g_map_shop.at(shop_name);
	// AddItem(inven, data.name, 1);
	// SetPlayerGold(GetPlayerGold() - (data.buy_value * multiple_));
	// std::cout << "---------------------------------------------------------------------\n";
	// std::cout << "You bought [" << data.name << "].\n";
	// std::cout << "You spent [" << data.buy_value << "].\n";
	// std::cout << "---------------------------------------------------------------------\n";
	 _getch();
	 return true;
}
bool SellItems(Inventory<InventoryInfo>& inven, Player& player, const std::string& item_name) {
	// // ItemInfo data = FindItem(item_name); !Need a function that bring item informations

	//  if (id == -1) {
	//  	std::cout << "---------------------------------------------------------------------\n";
	//  	std::cout << "Can not find that item.\n";
	//  	std::cout << "---------------------------------------------------------------------\n";
	//  	_getch();
	//  	return false;
	//  }
	
	if (!CheckItem(inven, item_name, 1)) {
	  	std::cout << "---------------------------------------------------------------------\n";
	  	std::cout << "You don't have that item in your inventory.\n";
	  	std::cout << "---------------------------------------------------------------------\n";
	  	_getch();
	  	return false;
	  }
	//  ItemInfo data = GetItemData(item_name);
	//  cout << "---------------------------------------------------------------------\n";
	//  cout << "You sold [" << data.name << "]\n";
	//  cout << "You gain [" << data.sell_value << "]\n";
	//  cout << "---------------------------------------------------------------------\n";
	//removeItem(inven, data.name, 1);
	// SetPlayerGold(GetPlayerGold() + data.buy_value);
	 _getch();
	 return true;
}

void ViewShop(const std::string& shop_name, const std::string& name, Player& player) {
	while (true) {
		system("cls");
		ShopData shop_data = FindShopData(name);
			std::cout << "=========================================================\n";
		std::cout << "[" << shop_data.shop_name_ << "]\n";
		std::cout << shop_data.greet_ << std::endl;
		std::cout << "---------------------------------------------------------\n";
		std::cout << std::left << std::setw(5) << "[No]"
			<< std::left << std::setw(12) << "[Name]"
			<< std::left << std::setw(12) << "[Count]"
			<< std::endl;
		std::cout << "---------------------------------------------------------\n";
		int number = 1;
		for (const auto& i : shop_data.items_.ViewInventory()) {
			std::cout << std::left << std::setw(5) << number
				<< std::left << std::setw(12) << i.name_
				<< std::left << std::setw(12) << i.count_
				<< std::endl;
			++number;
		}
		std::cout << "---------------------------------------------------------\n";
		std::cout << "Current [" << player.GetPlayerGold() << "]\n";
		std::cout << "---------------------------------------------------------\n";
		std::cout << "[Item Name: Buy] [[1]: Sell Item] [[2]: Sell Gears] [[0]: Back]\n";
		std::string answer;
		std::cin.clear();
		getline(std::cin >> std::ws, answer);
		if (answer == "1") {
			SellItemMenu(g_player_inventory, player);
			continue;
		}
		if (answer == "2") {
			SellItemMenu(g_player_armory, player);
			continue;
		}
		if (answer == "0") { 
			return; 
		}

		// BuyItems(inven, player, shop_name, answer); Need a function from itemdata
		continue;
	}
}

bool SellItemMenu(Inventory<InventoryInfo>& inven, Player& player) {
	while (true) {
		system("cls");
		ViewInventory(inven);
		std::cout << "---------------------------------------------------------\n";
		std::cout << "[Item Name: Sell] [[0]: Back]\n";
		std::string answer;
		getline(std::cin >> std::ws, answer);
		if (answer == "0") { 
			return false; 
		}
		SellItems(inven, player, answer);
		continue;
	}
}