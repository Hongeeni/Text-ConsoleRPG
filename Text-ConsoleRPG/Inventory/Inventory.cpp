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

void RunInventory(Player& player) {
	while (true) {
		system("cls");
		std::cout << "============== 인 벤 토 리 ==============\n";
		ViewInventory(g_player_inventory);
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