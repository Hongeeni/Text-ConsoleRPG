#include "farmer.h"

Farmer::Farmer(Player* player_info = nullptr) : Player(player_info) {
	this->player_job = "Farmer";
}

Farmer::~Farmer(void) {}