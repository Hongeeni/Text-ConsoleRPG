#include "warrior.h"

Warrior::Warrior(const std::string new_player_name, const std::map<std::string, unsigned short> new_player_status): Player(new_player_name, new_player_status) {
	this->player_job = "Warrior";
}

const unsigned short Warrior::GetSpecialAttackCost(void) {
	return this->kSpecialAttackCost;
}

Warrior::~Warrior(void) {}