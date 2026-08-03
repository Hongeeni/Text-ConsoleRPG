#include "Game/Game.h"

#include "Logger/Logger.h"
#include "Player/Player.h"
#include "Monster/Monster.h"
#include "Monster/MonsterData.h"
#include "CombatSystem/combat.h"
#include "Dungeon/Dungeon.h"
#include "Inventory/Inventory.h"
#include "Item/ItemData.h"
#include "Shop/Shop.h"
#include "Equipment/EquipmentManager.h"
#include "PotionCrafting/PotionCrafting.h"

#include <iostream>
#include <string>
#include <vector>

namespace {
	const std::string kLicenseItemName = "토벌 증서";
	const int kLicenseItemCount = 3;
	const int kAwakenLevel = 2;

	int ReadChoice(int minValue, int maxValue) {
		int choice = Dungeon::ReadIntInput();
		while (choice < minValue || choice > maxValue) {
			InvalidInputLog();
			if (!std::cin) {
				return minValue;
			}
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			choice = Dungeon::ReadIntInput();
		}
		return choice;
	}

	int LicenseCount() {
		for (const auto& item : g_player_inventory.ViewInventory()) {
			if (item.name_ == kLicenseItemName) {
				return item.count_;
			}
		}
		return 0;
	}

	void HandleAdvance(Dungeon& dungeon, Player& player, const AdvanceResult& r) {
		switch (r.event) {

		case DungeonEvent::Monster:
			if (r.monster.monsterDefeated) {
				BattleVictory();
				DropItemLog(r.monster.dropName);
			}
			break;

		case DungeonEvent::Treasure:
			TreasureLog(r.treasure.gold);
			for (const auto& reward : r.treasure.rewards) {
				TreasureItemLog(reward.itemName, reward.count, reward.isHintPaper);
			}
			break;

		case DungeonEvent::Shop:
			// 상점 이벤트는 이미 ViewShop()에서 처리됨
			break;

		case DungeonEvent::Altar: {
			DungeonEventMenu();
			const int choice = ReadChoice(0, 1);

			if (choice == 1) {
				AltarResult a = dungeon.TouchAltar(player);
				AltarLog(a.blessed, a.target, a.amount);
			}
			else {
				dungeon.SkipAltar();
			}
			break;
		}

		case DungeonEvent::Fountain:
			HpRecoveryLog(r.fountain.hpRestored, r.fountain.mpRestored);
			break;

		case DungeonEvent::BossFound:
			BossFoundLog();
			break;
		}

		if (r.playerDefeated) {
			BattleDefeat();
			DefeatLog(r.defeat.goldLost, r.defeat.itemsLost, player.GetCurrentLife());
		}
	}

	void HandleBossRoom(Dungeon& dungeon, Player& player) {
		BossRoomQuestion();
		const std::string answer = Dungeon::ReadLineInput();

		BossRoomResult r = dungeon.EnterBossRoom(answer, player);

		if (r.alreadyCleared) {
			EmptyDungeon();
			return;
		}
		if (!r.correctAnswer) {
			WrongAnswerLog();
			return;
		}
		if (r.cleared) {
			BattleVictory();
			BossClearLog();
		}
		else if (r.playerDefeated) {
			BattleDefeat();
			DefeatLog(r.defeat.goldLost, r.defeat.itemsLost, player.GetCurrentLife());
		}
	}

	// 레벨 2 도달 시 전직
	void CheckAwaken(Player& player) {
		if (player.GetArousal()) return;
		if (player.GetCurrentLevel() < kAwakenLevel) return;

		AwakenMenu();

		const int job = ReadChoice(1, 2);
		player.PlayerAwaken(job == 1 ? JobType::Warrior : JobType::Mage);
	}

	void RunInventory(Player& player) {
		while (true) {
			InventoryScreen();
			ViewInventory(g_player_inventory);
			std::cout << "[아이템 이름: 사용] [0: 돌아가기]\n선택: ";

			std::string answer;
			std::getline(std::cin >> std::ws, answer);

			if (!std::cin) return;      // EOF 방어
			if (answer == "0") return;

			if (UseItemOnPlayer(g_player_inventory, player, answer)) {
				std::cout << "[" << answer << "]을(를) 사용했습니다.\n";
			}
			else {
				std::cout << "사용할 수 없는 아이템입니다.\n";
			}
			PauseScreen();
		}
	}

	void RunDungeon(Player& player, DungeonType type) {
		LoadShop();
		Dungeon dungeon(type);

		ClearLog();
		if (Dungeon::IsCleared(type)) {
			EmptyDungeon();
		}

		while (!dungeon.IsExitRequested()) {
			if (player.GetCurrentLife() <= 0) {
				return;
			}

			DungeonScreen(dungeon.GetName(), player, dungeon.IsBossFound());

			const int maxOption = dungeon.IsBossFound() ? 3 : 2;
			const int choice = ReadChoice(0, maxOption);

			if (choice == 1) {
				AdvanceResult r = dungeon.Advance(player);
				HandleAdvance(dungeon, player, r);
			}
			else if (choice == 2) {
				RunInventory(player);
			}
			else if (choice == 3 && dungeon.IsBossFound()) {
				HandleBossRoom(dungeon, player);
			}
			else {
				EscapeResult r = dungeon.TryEscape(player);
				if (!r.success) {
					if (r.playerDefeated) {
						BattleDefeat();
					}
				}
			}

			CheckAwaken(player);

			if (!std::cin) {
				return;
			}
		}
	}

	void FightFinalBoss(Player& player) {
		for (const auto& data : MonsterList()) {
			if (data.name != "마왕") continue;

			Monster finalBoss(data.group, data.name, data.hp, data.power, data.defence, data.speed, data.critical,
				data.dropName, data.dropCategory, data.dropGold,
				data.rewardExp, data.isBoss);

			CombatSystem combat(player, finalBoss);
			combat.StartBattle();

			if (!finalBoss.IsAlive()) {
				Ending();
			}
			else {
				BattleDefeat();
			}
			return;
		}
	}

	void SelectDungeon(Player& player) {
		MapScreen();

		// 1. 슬라임 던전 2. 언데드 던전 3. 골렘 던전 4. 마왕의 성 0. 돌아가기
		const int choice = ReadChoice(0, 4);
		if (choice == 0) return;

		if (choice == 4) {
			const int count = LicenseCount();
			if (count >= kLicenseItemCount) {
				FightFinalBoss(player);
			}
			else {
				LicenseNotEnoughLog(count, kLicenseItemCount);
			}
			return;
		}

		DungeonType type = DungeonType::Slime;
		if (choice == 2) type = DungeonType::Undead;
		else if (choice == 3) type = DungeonType::Golem;

		RunDungeon(player, type);
	}

	void RunPotionCrafting() {
		while (true) {
			ClearScreen();
			const std::vector<CraftRecipe>& recipes = PotionCrafting::RecipeList();
			const std::vector<MaterialInfo>  owned = PotionCrafting::OwnedMaterials();
			const std::vector<int>           craftable = PotionCrafting::CraftableRecipes();

			std::cout << "\n=============== 포션 제작 ===============\n";

			std::cout << "[보유 재료]\n";
			if (owned.empty()) {
				std::cout << "  (없음)\n";
			}
			for (const auto& m : owned) {
				std::cout << "  " << m.name << " x" << m.count << "\n";
			}

			std::cout << "-----------------------------------------\n";
			std::cout << "[레시피]\n";

			for (int i = 0; i < static_cast<int>(recipes.size()); ++i) {
				bool possible = false;
				for (int idx : craftable) {
					if (idx == i) {
						possible = true;
						break;
					}
				}

				std::cout << "  " << (i + 1) << ". ";
				for (size_t j = 0; j < recipes[i].materials.size(); ++j) {
					if (j > 0) std::cout << " + ";
					std::cout << recipes[i].materials[j];
				}
				std::cout << " -> " << recipes[i].resultName
					<< " x" << recipes[i].resultCount
					<< (possible ? "   [제작 가능]" : "   [재료 부족]") << "\n";
			}

			std::cout << "  0. 돌아가기\n";
			std::cout << "=========================================\n";
			std::cout << "선택: ";

			const int choice = ReadChoice(0, static_cast<int>(recipes.size()));
			if (!std::cin) return;
			if (choice == 0) return;

			CraftResult r = PotionCrafting::CraftByRecipe(choice - 1);
			if (r.success) {
				std::cout << "[" << r.resultName << "] x" << r.resultCount << " 을(를) 만들었습니다!\n";
			}
			else {
				std::cout << "재료가 부족합니다.\n";
			}
			PauseScreen();
		}
	}
}

void RunGame(Player& player) {
	bool running = true;

	while (running) {
		MainScreen(player);
		const int choice = ReadChoice(0, 6);

		switch (choice) {
		case 1:
			SelectDungeon(player);
			break;
		case 2:
			PrintStatus(player);
			break;
		case 3:
			RunInventory(player);
			break;
		case 4:
			EquipmentMenu();
			DisplayEquipMenu(player);
			break;
		case 5:
			RunPotionCrafting();
			break;
		case 6:
			ShopLog();
			ViewShop("일반 상점", player);
			break;
		case 0:
			running = false;
			break;
		}

		if (running) {
			CheckAwaken(player);
		}

		if (running && player.GetCurrentLife() <= 0) {
			GameOverScreen();
			running = false;
		}

		if (!std::cin) {
			running = false;
		}
	}
}