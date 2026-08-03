#pragma once
#include<string>
#include<vector>

class Player;

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

// 화면
void MapScreen(); // 맵(배경) 화면
void TitleScreen(); // 시작 메뉴
void StoryScreen(); // 인트로부분 스토리
void NameInputScreen(); // 이름 입력
void Tutorial(); // 튜토리얼
void MainMenu();// 메인 메뉴
void DungeonMenu(); // 던전 메뉴
void DungeonEventMenu(); // 던전 내 플레이어 선택지
void EmptyDungeon(); // 던전 클리어 이후 출력

// 전투
void Battle(); // 전투 진입 구분선
void BattleMenu(int token, int currentMp, int skillCost); // 전투 시 플레이어 선택메뉴
void BattleStart(const std::string& monsterName, int monsterHp, int monsterPower, int monsterDefence); // 전투 시작
void BattleStatus(const std::string& playerName, int playerHp, int playerMaxHp, int playerMp, int playerMaxMp, const std::string& monsterName, int monsterHp); // 라운드 상태
void AttackLog(const std::string& attacker, const std::string& target, int damage, bool critical); // 공격 결과
void SkillUseLog(int mpCost, int currentMp); // 스킬 사용
void NotEnoughMpLog(); // 마나 부족
void ItemSelectMenu(const std::vector<std::string>& itemNames); // 전투 중 아이템 선택
void ItemUseLog(const std::string& itemName); // 아이템 사용
void ItemUseFailLog(); // 아이템 사용 실패
void NoUsableItemLog(); // 사용 가능한 아이템 없음
void BattleVictory(); // 배틀승리
void BattleDefeat(); // 배틀패배
void BattleRewardLog(int exp, int gold); // 전투 보상

// 성장
void LevelUpLog(int level, int maxHp, int maxMp, int power, int defense, int critical, int speed); // 레벨업
void MaxLevelLog(); // 최대 레벨 도달시 출력
void MaxExpLog();// 최대 레벨 도달시 경험치 얻을때 출력
void AwakenMenu(); // 전직 선택
void AwakenResultLog(const std::string& job); // 전직 결과

// 장비 / 인벤토리
void EquipmentMenu(); // 장비
void WeaponScreen(); // 장비 - 무기
void ArmorScreen(); // 장비 - 방어구
void InventoryScreen(); // 인벤토리

// 상점
void ShopLog(); // 상점 입장시 인삿말
void ShopMenu(); // 상점 메뉴
void ShopBuyScreen();// 상점 구매 화면
void ShopSellScreen(); // 상점 판매 화면

// 스탯
void PrintStatus(Player& player); // 스탯 출력

// 던전 이벤트
void InvalidInputLog(); // 잘못된 입력
void DropItemLog(const std::string& itemName); // 드랍 아이템
void TreasureLog(int gold); // 보물상자 발견
void TreasureItemLog(const std::string& itemName, int count, bool isHintPaper); // 보물상자 획득 아이템
void AltarLog(bool blessed, const std::string& target, int amount); // 제단 효과
void HpRecoveryLog(int hpRestored, int mpRestored); // 생명의 샘 회복
void DefeatLog(int goldLost, int itemsLost, int lifeLeft); // 패배 손실
void BossFoundLog(); // 보스방 발견
void BossRoomQuestion(); // 보스방 문제 출력
void WrongAnswerLog(); // 오답
void BossClearLog(); // 보스 토벌
void LicenseNotEnoughLog(int count, int need); // 토벌 증서 부족

// 기타
void Ending(); // 엔딩
void GameOverScreen(); // 게임오버
