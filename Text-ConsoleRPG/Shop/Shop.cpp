#include "Shop.h"
#include "ItemData.h"
#include <iostream>
#include <iomanip>
#include <conio.h>

std::vector<ShopData> kShopList() {
	std::vector<ShopData> shops = {
		{"일반 상점", "어서오세요.", "마을 상점",  1,{
			{"힐링 포션", 99}, {"마나 포션", 99},
			{"호미", 1}, {"얇은 방패", 1}, {"얇은 갑옷", 1}, {"얇은 신발", 1},
		}},
		{"슬라임 상인", "슬라임슬라임", "슬라임 던전 상점", 1.5,{
			{"힐링 포션", 10}, {"마나 포션", 10},
			{"짧은 검", 1}, {"나무 방패", 1}, {"가죽 갑옷", 1}, {"고철 반지", 1},
		}},
		{"언데드 상인", "언데드언데드", "언데드 던전 상점",  2, {
			{"힐링 포션", 10}, {"마나 포션", 10},
			{"긴 검", 1}, {"가죽 방패", 1}, {"사슬 갑옷", 1}, {"가죽 장갑", 1},
		}},
		{"골렘 상인", "골골렘렘.", "골렘 던전 상점.",  2,{
			{"힐링 포션", 10}, {"마나 포션", 10},
			{"양손검", 1}, {"사슬 방패", 1}, {"판금 갑옷", 1}, {"사슬 장갑", 1},
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
		std::cout << "\n---------------------------------------------------------------------\n";
		std::cout << "해당 아이템을 찾을 수 없습니다.\n";
		std::cout << "---------------------------------------------------------------------\n";
		_getch();
		return false;
	}
	ItemData item_data = FindItem(item_name);

	float multiple = 1.0f;
	auto it = g_map_shop.find(shop_name);
	if (it != g_map_shop.end()) {
		multiple = it->second.multiple_;
	}
	const int real_price = static_cast<int>(item_data.price * multiple);

	if (real_price > player.GetGold()) {
		std::cout << "\n---------------------------------------------------------------------\n";
		std::cout << "골드가 충분하지 않습니다..\n";
		std::cout << "---------------------------------------------------------------------\n";
		_getch();
		return false;
	}
	RemoveGoods(shop_name, item_data.name, 1);
	AddItem(inven, item_data.name, 1);
	player.DecreaseGold(real_price);
	std::cout << "\n---------------------------------------------------------------------\n";
	std::cout << "[" << item_data.name << "]를 구매했습니다.\n";
	std::cout << "[" << real_price << "]골드를 사용했습니다.\n";
	std::cout << "---------------------------------------------------------------------\n";
	_getch();
	return true;
}

bool SellItems(Inventory<InventoryInfo>& inven, Player& player, const std::string& item_name) {
	ItemData item_data = FindItem(item_name);
	 if (!item_data.found) {
	 	std::cout << "\n---------------------------------------------------------------------\n";
	 	std::cout << "해당 아이템을 찾을 수 없습니다.\n";
	 	std::cout << "---------------------------------------------------------------------\n";
	 	_getch();
	 	return false;
	 }
	 if (item_data.category == "license" || item_data.category == "other") {
		 std::cout << "\n---------------------------------------------------------------------\n";
		 std::cout << "이 물건은 팔 수 없습니다.\n";
		 std::cout << "---------------------------------------------------------------------\n";
		 _getch();
		 return false;
	 }
	if (!CheckItem(inven, item_name, 1)) {
	  	std::cout << "\n---------------------------------------------------------------------\n";
	  	std::cout << "해당 아이템을 가지고 있지 않습니다.\n";
	  	std::cout << "---------------------------------------------------------------------\n";
	  	_getch();
	  	return false;
	  }
	int sell_value = item_data.price / 3;
	 std::cout << "\n---------------------------------------------------------------------\n";
	 std::cout << "[" << item_data.name << "]를 판매했습니다.\n";
	 std::cout << "[" << sell_value << "]골드를 얻었습니다.\n";
	 std::cout << "---------------------------------------------------------------------\n";
	 RemoveItem(inven, item_data.name, 1);
	 player.AddGold(sell_value);
	 _getch();
	 return true;
}

void ViewShop(const std::string& shop_name, Player& player) {
	while (true) {
		system("cls");
		auto it = g_map_shop.find(shop_name);
		if (it == g_map_shop.end()) {
			return;
		}
		const ShopData& shop_data = it->second;
		std::cout << "=========================================================\n";
		std::cout << "[" << shop_data.shop_name_ << "]\n";
		std::cout << shop_data.greet_ << std::endl;
		std::cout << "---------------------------------------------------------\n";
		std::cout << std::left << std::setw(6) << "[번호]"
			<< std::left << std::setw(20) << "[이름]"
			<< std::left << std::setw(8) << "[갯수]"
			<< "[가격]"
			<< std::endl;
		std::cout << "---------------------------------------------------------\n";
		int number = 1;
		for (const auto& i : shop_data.items_.ViewInventory()) {
			ItemData data = FindItem(i.name_);
			const int price = static_cast<int>(data.price * shop_data.multiple_);
			std::cout << std::left << std::setw(6) << number
				<< std::left << std::setw(20) << i.name_
				<< std::left << std::setw(8) << i.count_
				<< price << "G"
				<< std::endl;
			++number;
		}
		std::cout << "---------------------------------------------------------\n";
		std::cout << "골드: [" << player.GetGold() << "]\n";
		std::cout << "---------------------------------------------------------\n";
		std::cout << "[아이템 이름: 구매] [[1]: 아이템 판매] [[2]: 장비 판매] [[0]: 뒤로]\n";
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
		ItemData item_data = FindItem(answer);
		const std::string& c = item_data.category;
		const bool is_gear = (c == "weapon" || c == "shield" || c == "armor"
			|| c == "ring" || c == "gloves" || c == "shoes");
		Inventory<InventoryInfo>& inventype = is_gear ? g_player_armory : g_player_inventory;
	
		BuyItems(inventype, player, shop_name, answer); 
		continue;
	}
}

bool SellItemMenu(Inventory<InventoryInfo>& inven, Player& player) {
	while (true) {
		system("cls");
		ViewInventory(inven, false);
		std::cout << "---------------------------------------------------------\n";
		std::cout << "[아이템 이름: 판매] [[0]: 뒤로]\n";
		std::string answer;
		getline(std::cin >> std::ws, answer);
		if (answer == "0") { 
			return false; 
		}
		SellItems(inven, player, answer);
		continue;
	}
}