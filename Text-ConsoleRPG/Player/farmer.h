#ifndef _FARMER_H_
#define _FARMER_H_

#include "player.h"

class Farmer : public Player {
public:
	Farmer(Player* player_info = nullptr);

	~Farmer(void);
};

#endif
