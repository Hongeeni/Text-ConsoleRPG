#pragma once
#include<string>

enum class MapType {
	Village,
	DungeonEntrance,
	Shop,
	Inventory,
	Equipment,
	Armor,
	Weapon,
	Status,
	SlimeDungeon,
	UndeadDungeon,
	GolemDungeon,
	HealEvent, // 생명의샘
	RandomHealEvent//제단
};

void MapScreen(); // 맵(배경) 화면 
void TitleScreen(); // 시작 메뉴
void StoryScreen(); // 인트로부분 스토리
void NameInputScreen(); // 이름 입력
void Tutorial(); // 튜토리얼(시간나면 구상)
void MainMenu();// 메인 메뉴
void DungeonMenu(); // 던전 메뉴
void DungeonEventMenu(); // 던전 내 플레이어 선택지
void EmptyDungeon(); // 던전 클리어 이후 출력
void Battle(); // 전투 입력
void BattleMenu(); // 전투 시 플레이어 선택메뉴
void BattleVictory(); // 배틀승리
void BattleDefeat(); // 배틀패배 
void EquipmentMenu(); // 장비
void WeaponScreen(); // 장비 - 무기
void ArmorScreen(); // 장비 - 방어구
void InventoryScreen(); // 인벤토리
void ShopLog(); // 상점 입장시 인삿말
void ShopMenu(); // 상점 메뉴
void ShopBuyScreen();// 상점 구매 화면
void ShopSellScreen(); // 상점 판매 화면
void PrintStatus(); // 스탯 출력
void Ending(); // 엔딩 
void HpRecoveryLog(); // 체력 회복 출력
void MaxLevelLog(); // 최대 레발 도달시 출력
void MaxExpLog();// 최대 레발 도달시 경험치 얻을때 출력
void GameOverScreen(); // 게임오버
