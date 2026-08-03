#include "Logger.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <vector>

void TitleScreen(){
    std::cout << "=========================================\n";
    std::cout << "     농부였던 내가 오늘부터는 용사?! \n";
    std::cout << "=========================================\n";
    system("pause");
    system("cls");
}

void StoryScreen(){
    std::cout << R"(
========================================

마왕이 세상을 지배한 이후

세상은 끝없는 흉년에 빠졌습니다.

햇빛은 사라지고 농작물은 모두 말라 죽었고,
농부였던 당신의 밭도 결국 황무지가 되었습니다.

"농사가 안 된다면...
마왕을 쓰러뜨리면 되는 거 아닌가?"

그렇게 당신은 낫을 들고
마왕을 향한 여정을 시작합니다.

하지만 마왕에게 가는 길에는
수많은 던전과 강력한 몬스터들이 기다리고 있습니다.

모든 던전을 돌파하고
세상에 다시 풍년을 되찾으세요!

========================================
)";
}

void NameInputScreen() {
    std::cout << "이름을 입력하세요: ";
}

void Tutorial() {
    std::cout << "\n=============== 조작 안내 ===============\n";
    std::cout << "메뉴는 번호를 입력해 선택합니다.\n";
    std::cout << "던전에서 전진하면 몬스터, 보물상자, 상점,\n";
    std::cout << "제단, 생명의 샘, 보스방 중 하나를 만납니다.\n\n";
    std::cout << "전투는 라운드마다 행동 토큰 2개를 받습니다.\n";
    std::cout << "  일반 공격 / 스킬 공격 : 토큰 2\n";
    std::cout << "  아이템 사용           : 토큰 1\n\n";
    std::cout << "각 던전 보스방에는 문제가 있습니다.\n";
    std::cout << "보물상자에서 나오는 [정체를 알 수 없는 종이]가 힌트입니다.\n";
    std::cout << "인벤토리에서 종이의 설명을 확인하세요.\n\n";
    std::cout << "던전 3곳을 토벌해 [토벌 증서] 3장을 모으면\n";
    std::cout << "마왕의 성에 들어갈 수 있습니다.\n";
    std::cout << "=========================================\n";
    system("pause");
    system("cls");
}

void MapScreen() {
    std::cout << "1. 슬라임 던전\n2. 언데드 던전\n3. 골렘 던전\n";
    std::cout << "4. 마왕의 성\n0. 돌아가기\n선택: ";
}

void MainMenu(){
    std::cout << "============== 메인 메뉴 ==============\n";
    std::cout << "1. 던전\n";
    std::cout << "2. 스탯\n";
    std::cout << "3. 인벤토리\n";
    std::cout << "4. 장비\n";
    std::cout << "5. 포션 제작\n";
    std::cout << "6. 상점\n";
    std::cout << "0. 게임 종료\n";
    std::cout << "======================================\n";
    std::cout << "선택: ";
}

void DungeonMenu() {
    std::cout << "1. 전진\n2. 인벤토리\n3. 보스룸\n0. 탈출\n선택: ";
}

void DungeonEventMenu() {
    std::cout << "1. 제단을 만진다\n0. 지나친다\n선택: ";
}

void EmptyDungeon() {
    std::cout << "이미 토벌을 마친 던전입니다.\n";
}

// ---- 전투 ----

void Battle() {
    std::cout << "\n-----------------------------------------\n";
    std::cout << "              전  투  개  시\n";
    std::cout << "-----------------------------------------\n";
}

void BattleStart(const std::string& monsterName, int monsterHp, int monsterPower, int monsterDefence) {
    std::cout << "\n[" << monsterName << "]이(가) 나타났다!\n";
    std::cout << "  체력 " << monsterHp
        << "  공격력 " << monsterPower
        << "  방어력 " << monsterDefence << "\n";
}

void BattleStatus(const std::string& playerName, int playerHp, int playerMaxHp,
    int playerMp, int playerMaxMp, const std::string& monsterName, int monsterHp) {
    std::cout << "\n-----------------------------------------\n";
    std::cout << playerName << "   HP " << playerHp << "/" << playerMaxHp
        << "   MP " << playerMp << "/" << playerMaxMp << "\n";
    std::cout << monsterName << "   HP " << monsterHp << "\n";
    std::cout << "-----------------------------------------\n";
}

void BattleMenu(int token, int currentMp, int skillCost) {
    std::cout << "\n[남은 행동 토큰: " << token << "]\n";
    std::cout << "1. 일반 공격 (토큰 2)\n";
    std::cout << "2. 스킬 공격 (토큰 2, MP " << skillCost << " / 현재 " << currentMp << ")\n";
    std::cout << "3. 아이템 사용 (토큰 1)\n";
    std::cout << "선택: ";
}

void AttackLog(const std::string& attacker, const std::string& target, int damage, bool critical) {
    if (critical) {
        std::cout << "치명타! ";
    }
    std::cout << attacker << " -> " << target << "  " << damage << " 피해\n";
}

void SkillUseLog(int mpCost, int currentMp) {
    std::cout << "스킬을 사용했다. (MP -" << mpCost << " / 남은 MP " << currentMp << ")\n";
}

void NotEnoughMpLog() {
    std::cout << "마나가 부족해 일반 공격으로 대체됩니다.\n";
}

void ItemSelectMenu(const std::vector<std::string>& itemNames) {
    std::cout << "\n[아이템]\n";
    for (size_t i = 0; i < itemNames.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << itemNames[i] << "\n";
    }
    std::cout << "  0. 취소\n선택: ";
}

void ItemUseLog(const std::string& itemName) {
    std::cout << "[" << itemName << "]을(를) 사용했습니다.\n";
}

void ItemUseFailLog() {
    std::cout << "사용할 수 없는 아이템입니다.\n";
}

void NoUsableItemLog() {
    std::cout << "사용할 수 있는 아이템이 없습니다.\n";
}

void BattleVictory() {
    std::cout << "승리했습니다!\n";
}

void BattleDefeat() {
    std::cout << "패배했습니다...\n";
}

void BattleRewardLog(int exp, int gold) {
    std::cout << "경험치 " << exp << " 획득\n";
    std::cout << "골드 " << gold << " 획득\n";
}

// ---- 성장 ----

void LevelUpLog(int level, int maxHp, int maxMp, int power, int defense, int critical, int speed) {
    std::cout << "\n*** 레벨 업! Lv." << level << " ***\n";
    std::cout << "  최대 HP " << maxHp << "   최대 MP " << maxMp << "\n";
    std::cout << "  공격력 " << power << "   방어력 " << defense
        << "   치명타 " << critical << "   속도 " << speed << "\n";
}

void MaxLevelLog() {
    std::cout << "최대 레벨에 도달했습니다.\n";
}

void MaxExpLog() {
    std::cout << "최대 레벨이라 경험치를 얻지 못했습니다.\n";
}

void AwakenMenu() {
    std::cout << "\n=========================================\n";
    std::cout << "  농부의 손에 낯선 힘이 깃든다.\n";
    std::cout << "  당신은 더 이상 농부가 아니다.\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "1. 전사\n";
    std::cout << "     방어력 +5, 최대 HP +100\n";
    std::cout << "     레벨업마다 방어력 +2, 최대 HP +50\n";
    std::cout << "2. 마법사\n";
    std::cout << "     공격력 +3, 최대 MP +100\n";
    std::cout << "     레벨업마다 공격력 +2, 최대 MP +50\n";
    std::cout << "     스킬 위력 3배\n";
    std::cout << "=========================================\n";
    std::cout << "선택: ";
}

void AwakenResultLog(const std::string& job) {
    std::cout << "[" << job << "]로 각성했습니다.\n";
}

// ---- 장비 / 인벤토리 ----

void EquipmentMenu() {
    std::cout << "\n================ 장 비 ================\n";
}

void WeaponScreen() {
    std::cout << "\n---------------- 무 기 ----------------\n";
}

void ArmorScreen() {
    std::cout << "\n--------------- 방 어 구 ---------------\n";
}

void InventoryScreen() {
    std::cout << "\n============== 인 벤 토 리 ==============\n";
}

// ---- 상점 ----

void ShopLog() {
    std::cout << "어서오세요!\n";
}

void ShopMenu() {
    std::cout << "[아이템 이름: 구매] [1: 아이템 판매] [2: 장비 판매] [0: 뒤로]\n선택: ";
}

void ShopBuyScreen() {
    std::cout << "\n--------------- 구 매 ---------------\n";
}

void ShopSellScreen() {
    std::cout << "\n--------------- 판 매 ---------------\n";
}

// ---- 스탯 ----

void PrintStatus(Player& player) {
    std::cout << "\n=========================================\n";
    std::cout << "  " << player.GetName() << "   [" << player.GetJob() << "]\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "  레벨      " << player.GetCurrentLevel() << " / " << player.GetMaxLevel() << "\n";
    std::cout << "  목숨      " << player.GetCurrentLife() << " / " << player.GetMaxLife() << "\n";
    std::cout << "  경험치    " << player.GetCurrentExp() << " / " << player.GetMaxExp() << "\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "  HP        " << player.GetCurrentHp() << " / " << player.GetMaxHp() << "\n";
    std::cout << "  MP        " << player.GetCurrentMp() << " / " << player.GetMaxMp() << "\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "  공격력    " << player.GetPower() << "\n";
    std::cout << "  방어력    " << player.GetDefense() << "\n";
    std::cout << "  치명타    " << player.GetCritical() << "%\n";
    std::cout << "  속도      " << player.GetSpeed() << "\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "  골드      " << player.GetGold() << "\n";
    std::cout << "  스킬 소모 MP " << player.GetSkillCost() << "\n";
    std::cout << "=========================================\n";
    system("pause");
}

// ---- 던전 이벤트 ----

void InvalidInputLog() {
    std::cout << "잘못된 입력입니다.\n";
}

void DropItemLog(const std::string& itemName) {
    if (itemName.empty()) {
        return;
    }
    std::cout << "드랍 아이템: " << itemName << "\n";
}

void TreasureLog(int gold) {
    std::cout << "\n낡은 보물상자를 발견했다!\n";
    std::cout << "골드 " << gold << " 획득\n";
}

void TreasureItemLog(const std::string& itemName, int count, bool isHintPaper) {
    std::cout << "  " << itemName << " x" << count;
    if (isHintPaper) {
        std::cout << "   (보스방 힌트)";
    }
    std::cout << "\n";
}

void AltarLog(bool blessed, const std::string& target, int amount) {
    if (target.empty()) {
        std::cout << "제단은 아무 반응이 없다.\n";
        return;
    }
    if (blessed) {
        std::cout << "제단이 빛난다. " << target << "이(가) " << amount << " 올랐다!\n";
    }
    else {
        std::cout << "제단이 검게 물든다. " << target << "이(가) " << amount << " 깎였다...\n";
    }
}

void HpRecoveryLog(int hpRestored, int mpRestored) {
    std::cout << "\n생명의 샘에서 몸을 씻었다.\n";
    std::cout << "  HP " << hpRestored << " 회복\n";
    std::cout << "  MP " << mpRestored << " 회복\n";
}

void DefeatLog(int goldLost, int itemsLost, int lifeLeft) {
    std::cout << "정신을 잃었다가 던전 입구에서 눈을 떴다.\n";
    std::cout << "  골드 " << goldLost << " 손실\n";
    std::cout << "  아이템 " << itemsLost << "종 손실\n";
    std::cout << "  남은 목숨 " << lifeLeft << "\n";
}

void BossFoundLog() {
    std::cout << "\n커다란 문을 발견했다. 보스방으로 갈 수 있다.\n";
}

void BossRoomQuestion() {
    std::cout << "=========================================\n";
    std::cout << "    거대한 문 앞에 글귀가 새겨져 있다.\n\n";
    std::cout << "    \"흩어진 세 장의 종이가 가리키는\n";
    std::cout << "             정답을 말하라.\"\n";
    std::cout << "=========================================\n";
    std::cout << "정답: ";
}

void WrongAnswerLog() {
    std::cout << "문은 꿈쩍도 하지 않는다.\n";
}

void BossClearLog() {
    std::cout << "\n던전을 토벌했다! [토벌 증서]를 손에 넣었다.\n";
}

void LicenseNotEnoughLog(int count, int need) {
    std::cout << "\n마왕성의 문은 굳게 닫혀 있다.\n";
    std::cout << "토벌 증서 " << count << " / " << need << "\n";
}

// ---- 기타 ----

void Ending(){
    std::cout << "                   마왕이 쓰러졌다.\n\n";
    std::cout << "         구름이 걷히고 오랜만에 햇빛이 들었다.\n";
    std::cout << "  농사는 검을 내려놓고 다시 호미를 챙겨 밭으로 돌아간다.\n\n";
    std::cout << "                   - 게임 클리어 -\n";
    system("pause");
    system("cls");
}

void GameOverScreen() {
    std::cout << "===============================\n";
    std::cout << "         게 임 오 버\n";
    std::cout << "   목숨이 모두 소진되었습니다.\n";
    std::cout << "===============================\n";
}
