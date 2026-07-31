#ifndef _WARRIOR_H_
#define _WARRIOR_H_

#include "player.h"

class Warrior : public Player {
private:
	const unsigned short kSpecialAttackCost = 20;

public:
	Warrior(Player* player_info = nullptr);

	const unsigned short GetSpecialAttackCost(void);

	~Warrior(void);
};

#endif
