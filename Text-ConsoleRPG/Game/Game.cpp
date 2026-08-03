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
			// Logger 확장 필요, 잘못된 입력입니다.
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
				// Logger 확장 필요, 드랍 아이템 이름 출력
			}
			break;

		case DungeonEvent::Treasure:
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
				// logger 확장 필요, a.blessed / a.target / a.amount 출력
			}
			else {
				dungeon.SkipAltar();
			}
			break;
		}

		case DungeonEvent::Fountain:
			HpRecoveryLog();
			// r.fountain.hpRestored, r.fountain.mpRestored 처리
			break;

		case DungeonEvent::BossFound:
			// 보스방 발견 안내
			break;
		}

		if (r.playerDefeated) {
			BattleDefeat();
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
			// 정답이 아닌 경우 안내
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
			
		}
	}
}