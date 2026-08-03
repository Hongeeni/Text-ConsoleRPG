#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#include "Game/Game.h"
#include "Logger/Logger.h"
#include "Player/Player.h"
#include "Shop/Shop.h"

int main(void) {
#ifdef _WIN32
    // 콘솔 한글(UTF-8) 출력 + ANSI 색상(VT) 활성화
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (h != INVALID_HANDLE_VALUE && GetConsoleMode(h, &mode))
        SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
    
    LoadShop();

    TitleScreen();
    StoryScreen();

    Player player;

    NameInputScreen();
    std::string name;
    std::getline(std::cin, name);
    if (!name.empty()) {
        player.SetName(name);
    }

    Tutorial();

    RunGame(player);

    return 0;
}
