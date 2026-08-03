#include <iostream>
#include <string>



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


void MainMenu(){
    std::cout << "============== 메인 메뉴 ==============\n";
    std::cout << "1. 던전\n";
    std::cout << "2. 스탯\n";
    std::cout << "3. 인벤토리\n";
    std::cout << "4. 장비\n";
    std::cout << "5. 상점\n";
    std::cout << "6. 포션 제작\n";
    std::cout << "0. 게임 종료\n";
    std::cout << "======================================";
    ;
}

void Ending(){
    std::cout << "                   마왕이 쓰러졌다.\n\n";
    std::cout << "         구름이 걷히고 오랜만에 햇빛이 들었다.\n";
    std::cout << "  농사는 검을 내려놓고 다시 호미를 챙겨 밭으로 돌아간다.\n\n";
    std::cout << "                   - 게임 클리어 -\n";
    system("pause");
    system("cls");
}

//임시
void NameInputScreen() {
    std::cout << "이름을 입력하세요: ";
}
void Tutorial() {}
void MapScreen() {
    std::cout << "1. 슬라임 던전\n2. 언데드 던전\n3. 골렘 던전\n";
    std::cout << "4. 마왕의 성\n0. 돌아가기\n선택: ";
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
void BattleVictory() {
    std::cout << "승리했습니다!\n";
}
void BattleDefeat() {
    std::cout << "패배했습니다...\n";
}
void EquipmentMenu() {}
void InventoryScreen() {}
void ShopLog() {
    std::cout << "어서오세요!\n";
}
void PrintStatus() {}
void HpRecoveryLog() {}
void GameOverScreen() {
    std::cout << "===============================\n";
    std::cout << "         게 임 오 버\n";
    std::cout << "   목숨이 모두 소진되었습니다.\n";
    std::cout << "===============================\n";
}