#include <iostream>
#include <string>
#include "Game/Game.h"
#include "Logger/Logger.h"
#include "Player/Player.h"
#include "Shop/Shop.h"

int main(void) {
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