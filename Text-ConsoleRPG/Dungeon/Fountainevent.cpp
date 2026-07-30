#include "FountainEvent.h"
#include "Player.h"

#include <iostream>

void FountainEvent::Trigger(Player& player) {
    std::cout << "생명의 샘을 발견했습니다. 체력이 모두 회복됩니다.\n";
    player.Heal(player.GetMaxHP() - player.GetHP()); // (미확정) Player 실제 함수명
}