#ifndef _FARMER_H_
#define _FARMER_H_

#include "player.h"

class Farmer : public Player {
public:
	Farmer(const std::string new_player_name, const std::map<std::string, unsigned short> new_player_status);

	~Farmer(void);
};

#endif
