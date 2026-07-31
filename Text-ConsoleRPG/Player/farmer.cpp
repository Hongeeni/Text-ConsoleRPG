#include "farmer.h"

Farmer::Farmer(const std::string new_player_name, const std::map<std::string, unsigned short> new_player_status) : Player(new_player_name, new_player_status) {
	this->player_job = "Farmer";
}

const unsigned short Farmer::GetSpecialAttackCost(void) {
	return this->kSpecialAttackCost;
}

Farmer::~Farmer(void) {}