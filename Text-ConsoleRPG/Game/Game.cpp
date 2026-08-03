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

	int ReadChoice(int minValue, int maxValue) {
		int choice = Dungeon::ReadIntInput();
		while (choice < minValue || choice > maxValue) {
			std::cout << "잘못된 입력입니다." << std::endl; //Logger 확장 필요
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
				std::cout << "드랍 아이템: " << r.monster.dropName << std::endl; // Logger 확장 필요
			}
			break;

		case DungeonEvent::Treasure:
			std::cout << "보물 발견!" << std::endl; // Logger 확장 필요
			// r.treasure.rewards, r.treasure.gold 처리
			break;

		case DungeonEvent::Shop:
			// 상점 이벤트는 이미 ViewShop()에서 처리됨
			break;

		case DungeonEvent::Altar: {
			DungeonEventMenu();
			const int choice = ReadChoice(0, 1);

			if (choice == 1) {
				AltarResult a = dungeon.TouchAltar(player);
				std::cout << "성물에 축복이 내려졌습니다." << std::endl; // Logger 확장 필요
				// logger 확장 필요, a.blessed / a.target / a.amount 출력
			}
			else {
				dungeon.SkipAltar();
			}
			break;
		}

		case DungeonEvent::Fountain:
			HpRecoveryLog();
			std::cout << "분수대에서 체력을 회복했습니다." << std::endl; // Logger 확장 필요
			// r.fountain.hpRestored, r.fountain.mpRestored 처리
			break;

		case DungeonEvent::BossFound:
			// 보스방 발견 안내
			break;
		}

		if (r.playerDefeated) {
			BattleDefeat();
			std::cout << "전투에서 패배했습니다." << std::endl; // Logger 확장 필요
			// Logger 확장 필요, r.defeat.goldLost / r.defeat.itemsLost 출력
		}
	}

	void HandleBossRoom(Dungeon& dungeon, Player& player) {
		// 보스방 입장 안내
		const std::string answer = Dungeon::ReadLineInput();

		BossRoomResult r = dungeon.EnterBossRoom(answer, player);

		if (r.alreadyCleared) {
			EmptyDungeon();
			return;
		}
		if (!r.correctAnswer) {
			std::cout << "정답이 아닙니다." << std::endl; // Logger 확장 필요
			return;
		}
		if (r.cleared) {
			BattleVictory();
		}
		else if (r.playerDefeated) {
			BattleDefeat();
		}
	}

	void RunDungeon(Player& player, DungeonType type) {
		Dungeon dungeon(type);

		if (Dungeon::IsCleared(type)) {
			EmptyDungeon();
			return;
		}
		
		while (!dungeon.IsExitRequested()) {
			if (player.GetCurrentHp() <= 0) {
				BattleDefeat();
				return;
			}

			DungeonMenu();

			const int maxOption = dungeon.IsBossFound() ? 3 : 2;
			const int choice = ReadChoice(0, maxOption);

			if (choice == 1) {
				AdvanceResult r = dungeon.Advance(player);
				HandleAdvance(dungeon, player, r);
			}
			else if (choice == 2) {  
				InventoryScreen();
				ViewInventory(g_player_inventory);
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
			if (LicenseCount() >= 3){
				FightFinalBoss(player);
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
            // (Logger 확장 필요) 아래 목록을 화면에 출력
            //   PotionCrafting::OwnedMaterials()    보유 재료
            //   PotionCrafting::RecipeList()        전체 레시피
            //   PotionCrafting::CraftableRecipes()  지금 만들 수 있는 번호
		}
	}
}

void RunGame(Player& player) {
	bool running = true;

	while (running) {
		MainMenu();
		const int choice = ReadChoice(0, 6);

		switch (choice) {
		case 1:
			SelectDungeon(player);
			break;
		case 2:
			PrintStatus();
			break;
		case 3:
			InventoryScreen();
			ViewInventory(g_player_inventory);
			break;
		case 4:
			EquipmentMenu();
			DisplayEquipMenu();
			break;
		case 5:
			RunPotionCrafting();
			break;
		case 6:
			ShopLog();
			ViewShop("일반 상점", "일반 상점", player);
			break;
		case 0:
			running = false;
			break;
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