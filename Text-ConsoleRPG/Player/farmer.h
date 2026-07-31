#ifndef _FARMER_H_
#define _FARMER_H_

#include "player.h"

class Farmer : public Player {
public:
	Farmer(std::string new_player_name);

	~Farmer(void);
};

#endif
