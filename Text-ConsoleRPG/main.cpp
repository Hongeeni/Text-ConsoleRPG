#include <iostream>
#include <string>
#include "Game/Game.h"
#include "Logger/Logger.h"
#include "Player/Player.h"
#include "Shop/Shop.h"
#include "Inventory/Inventory.h"

int main(void) {
    LoadShop();

    AddItem(g_player_inventory, "힐링 포션", 3);
    AddItem(g_player_inventory, "마나 포션", 2);
    AddItem(g_player_armory, "호미", 1);

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