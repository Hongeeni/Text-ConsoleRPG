#include "Inventory.h"
#include "Item/Itemdata.h"
#include "Player/Player.h"
#include <iomanip>
#include <iostream>
#include <conio.h>

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
int ViewInventory(const Inventory<InventoryInfo>& inven, bool on_battle) {
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
		if (on_battle) {
			if (data.category == "potion") {
				std::cout << std::left << std::setw(6) << number
					<< std::left << std::setw(30) << i.name_
					<< std::left << std::setw(8) << i.count_
					<< (data.found ? data.description : "")
					<< std::endl;
				++number;
			}
		}
		else {
			std::cout << std::left << std::setw(6) << number
				<< std::left << std::setw(30) << i.name_
				<< std::left << std::setw(8) << i.count_
				<< (data.found ? data.description : "")
				<< std::endl;
			++number;
		}
	}
	std::cout << "==========================================================================\n";
	return number - 1;
}

void RunInventory(Player& player) {
	while (true) {
		system("cls");
		std::cout << "============== 인 벤 토 리 ==============\n";
		ViewInventory(g_player_inventory, false);
		std::cout << "[아이템 이름: 사용] [0: 돌아가기]\n:: ";

		std::string answer;
		std::getline(std::cin >> std::ws, answer);

		if (answer == "0") {
			return;
		}
		ItemData item_data = FindItem(answer);
		if (!item_data.found) {
			std::cout << "\n---------------------------------------------------------------------\n";
			std::cout << "해당 아이템을 찾을 수 없습니다.\n";
			std::cout << "---------------------------------------------------------------------\n";
			_getch();
			continue;
		}
		if (!CheckItem(g_player_inventory, answer, 1)) {
			std::cout << "\n---------------------------------------------------------------------\n";
			std::cout << "그 아이템을 가지고 있지 않습니다..\n";
			std::cout << "---------------------------------------------------------------------\n";
			_getch();
			continue;
		}
		if (UseItemOnPlayer(g_player_inventory, player, answer)) {
			std::cout << "\n---------------------------------------------------------------------\n";
			std::cout << "[" << answer << "]을(를) 사용했습니다.\n";
			std::cout << "---------------------------------------------------------------------\n";
		}
		else {
			std::cout << "\n---------------------------------------------------------------------\n";
			std::cout << "사용할 수 없는 아이템입니다.\n";
			std::cout << "---------------------------------------------------------------------\n";
		}
		_getch();
	}
}
bool BattleInventory(Player& player) {
	while (true) {
		std::cout << "============== 포션 파우치 ==============\n";
		int item_count = ViewInventory(g_player_inventory, true);
		std::cout << "[아이템 이름: 사용] [0: 돌아가기]\n:: ";
		std::cin.clear();
		std::string answer;
		std::getline(std::cin >> std::ws, answer);
		int number = 0;

		if (answer == "0") {
			return false;
		}
		ItemData item_data = FindItem(answer);
		if (!item_data.found) {
			std::cout << "\n---------------------------------------------------------------------\n";
			std::cout << "해당 아이템을 찾을 수 없습니다.\n";
			std::cout << "---------------------------------------------------------------------\n";
			_getch();
			std::cout << "\033[" << (12+ item_count )<<"A\n";
			continue;
		}
		if (!CheckItem(g_player_inventory, answer, 1)) {
			std::cout << "\n---------------------------------------------------------------------\n";
			std::cout << "그 아이템을 가지고 있지 않습니다..\n";
			std::cout << "---------------------------------------------------------------------\n";
			_getch();
			std::cout << "\033[" << (12 + item_count) << "A\n";
			continue;
		}
		if (item_data.category != "potion") {
			std::cout << "\n---------------------------------------------------------------------\n";
			std::cout << "지금은 사용할 수 없는 아이템입니다..\n";
			std::cout << "---------------------------------------------------------------------\n";
			_getch();
			std::cout << "\033[" << (12 + item_count) << "A\n";
			continue;
		}
		if (UseItemOnPlayer(g_player_inventory, player, answer)) {
			std::cout << "\n---------------------------------------------------------------------\n";
			std::cout << "[" << answer << "]을(를) 사용했습니다.\n";
			std::cout << "---------------------------------------------------------------------\n";
			_getch();
			return true;
		}
		else {
			std::cout << "\n---------------------------------------------------------------------\n";
			std::cout << "사용할 수 없는 아이템입니다.\n";
			std::cout << "---------------------------------------------------------------------\n";
			_getch();
			std::cout << "\033[" << (12 + item_count) << "A\n";
			continue;
		}
	}
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