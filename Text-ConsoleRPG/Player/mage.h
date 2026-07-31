#ifndef _MAGE_H_
#define _MAGE_H_

#include "player.h"

class Mage : public Player {
private:
	const unsigned short kSpecialAttackCost = 20;

public:
	Mage(Player* player_info);

	const unsigned short GetSpecialAttackCost(void);

	~Mage(void);
};

#endif

