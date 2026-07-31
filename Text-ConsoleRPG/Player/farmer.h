#ifndef _FARMER_H_
#define _FARMER_H_

#include "player.h"

class Farmer : public Player {
private:
	const unsigned short kSpecialAttackCost = 20;

public:
	Farmer(const std::string new_player_name, const std::map<std::string, unsigned short> new_player_status);

	const unsigned short GetSpecialAttackCost(void);

	~Farmer(void);
};

#endif
