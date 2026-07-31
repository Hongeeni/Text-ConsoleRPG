#include "warrior.h"

Warrior::Warrior(Player* player_info = nullptr) : Player(player_info) {
	this->player_job = "Warrior";
}

const unsigned short Warrior::GetSpecialAttackCost(void) {
	return this->kSpecialAttackCost;
}

Warrior::~Warrior(void) {}