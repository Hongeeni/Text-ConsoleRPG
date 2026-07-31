#include "mage.h"

Mage::Mage(Player* player_info) {
	this->player_job = "Warrior";

	this->player_name = player_info->GetPlayerName();
	this->player_current_level = player_info->GetPlayerCurrentLevel();
	this->player_current_life = player_info->GetPlayerCurrentLife();
	this->player_current_exp = player_info->GetPlayerCurrentExp();
	this->player_max_exp = player_info->GetPlayerMaxExp();
	this->player_current_hp = player_info->GetPlayerCurrentHp();
	this->player_max_hp = player_info->GetPlayerMaxHp();
	this->player_current_mp = player_info->GetPlayerCurrentMp();
	this->player_max_mp = player_info->GetPlayerMaxMp();
	this->player_attack = player_info->GetPlayerAttack();
	this->player_defense = player_info->GetPlayerDefense();
	this->player_critical = player_info->GetPlayerCritical();
	this->player_speed = player_info->GetPlayerSpeed();
	this->player_gold = player_info->GetPlayerGold();
}

const unsigned short Mage::GetSpecialAttackCost(void) {
	return this->kSpecialAttackCost;
}

Mage::~Mage(void) {
	std::cout << "The mage object was successfully delete." << std::endl;
}