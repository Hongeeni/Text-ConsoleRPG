#include "Shop.h"
#include <iostream>
#include <iomanip>
#include <conio.h>

std::vector<ShopData> kShopList() {
	std::vector<ShopData> shops = {
		{"일반 상점", "어서오세요", "마을에 있는 잡화 상점",  1,{
			{"체력 포션", 5},
			{"마나 포션", 5},
		}},
		{"슬라임 던전 상점", "어서오세요", "슬라임 던전에 있는 상점", 1.5,{
			{"체력 포션", 5},
			{"마나 포션", 5},
		}},
		{"언데드 던전 상점", "어서오세요", "좀비 던전에 있는 잡화 상점",  2, {
			{"체력 포션", 5},
			{"마나 포션", 5},
		}},
		{"골렘 던전 상점", "어서오세요", "골렘 던전에 있는 잡화 상점",  2,{
			{"체력 포션", 5},
			{"마나 포션", 5},
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
// const std::vector<ShopItems>& ViewShop(const std::string& name) {
// 	return g_map_shop.at(shop_name).items_.at(name).ViewInventory();
// }
bool BuyItems(Inventory<InventoryInfo>& inven, Player& player, const std::string& shop_name, const std::string& item_name) {

	bool existed = CheckGoods(shop_name, item_name, 1);
	if (!existed) {
		std::cout << "---------------------------------------------------------------------\n";
		std::cout << "선택한 아이템을 찾을 수 없습니다.\n";
		std::cout << "---------------------------------------------------------------------\n";
		_getch();
		return false;
	}
	// int d = FindItem(item_name); 
	// ItemInfo data = GetItemData(d); !아이템 정보를 가져올 수 있는 함수 필요함
	// if (data.buy_value > playe.GetPlayerGold()) {
	//	cout << "---------------------------------------------------------------------\n";
	//	cout << "골드가 충분하지 않습니다.\n";
	//	cout << "---------------------------------------------------------------------\n";
	//	
	//	return false;
	//}
	//ItemInfo data = GetItemData[item_name]; !아이템 정보 가져오는 함수 필요함
	// RemoveGoods(shop_name, data.name, 1);
	// g_map_shop.at(shop_name);
	// AddItem(inven, data.name, 1);
	// SetPlayerGold(GetPlayerGold() - (data.buy_value * multiple_));
	// std::cout << "---------------------------------------------------------------------\n";
	// std::cout << "[" << data.name << "] 를 구매했습니다.\n";
	// std::cout << "[" << data.buy_value << "]골드를 사용했습니다.\n";
	// std::cout << "---------------------------------------------------------------------\n";
	 _getch();
	 return true;
}
bool SellItems(Inventory<InventoryInfo>& inven, Player& player, const std::string& item_name) {
	// // ItemInfo data = FindItem(item_name); 아이템 정보 가져오는 함수

	//  if (id == -1) {
	//  	std::cout << "---------------------------------------------------------------------\n";
	//  	std::cout << "선택한 아이템을 찾을 수 없습니다.\n";
	//  	std::cout << "---------------------------------------------------------------------\n";
	//  	_getch();
	//  	return false;
	//  }
	
	if (!CheckItem(inven, item_name, 1)) {
	  	std::cout << "---------------------------------------------------------------------\n";
	  	std::cout << "선택한 아이템을 가지고 있지 않습니다.\n";
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
		std::cout << "[아이템 이름: 구매] [[1]: 아이템 판매] [[2]: 장비 판매] [[0]: 돌아가기]\n";
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

		// BuyItems(inven, player, shop_name, answer); 아이템 구분 로직 아직 없음
		continue;
	}
}

bool SellItemMenu(Inventory<InventoryInfo>& inven, Player& player) {
	while (true) {
		system("cls");
		ViewInventory(inven);
		std::cout << "---------------------------------------------------------\n";
		std::cout << "[아이템 이름: 판매] [[0]: 돌아가기]\n";
		std::string answer;
		getline(std::cin >> std::ws, answer);
		if (answer == "0") { 
			return false; 
		}
		SellItems(inven, player, answer);
		continue;
	}
}