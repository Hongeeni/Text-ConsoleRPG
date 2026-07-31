#ifndef _WARRIOR_H_
#define _WARRIOR_H_

#include "player.h"

class Warrior : public Player {
private:
	const unsigned short kSpecialAttackCost = 20;

public:
	Warrior(const std::string new_player_name, const std::map<std::string, unsigned short> new_player_status);

	const unsigned short GetSpecialAttackCost(void);

	~Warrior(void);
};

#endif
