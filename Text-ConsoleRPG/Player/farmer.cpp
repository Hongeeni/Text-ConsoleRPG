#include "farmer.h"

Farmer::Farmer(std::string new_player_name) {
	this->player_name = new_player_name;
	this->player_job = "Farmer";
}

Farmer::~Farmer(void) {
	std::cout << "The farmer object was successfully delete." << std::endl;
}