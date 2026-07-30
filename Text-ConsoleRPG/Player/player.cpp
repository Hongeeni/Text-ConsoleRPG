#include "player.h"

Player::Player() {}

void Player::SetPlayerName(std::string new_player_name) {
	this->player_name = new_player_name;
}
void Player::SetPlayerJob(std::string new_player_job) {
	this->player_job = new_player_job;
}
void Player::SetPlayerLevel(int new_current_level) {
	this->player_level["current_level"] = new_current_level;
}
void Player::SetPlayerLevel(int new_current_level, int new_max_level) {
	this->player_level["current_level"] = new_current_level;
	this->player_level["max_level"] = new_max_level;
}
void Player::SetPlayerExp(int new_current_exp) {
	this->player_exp["current_exp"] = new_current_exp;
}
void Player::SetPlayerExp(int new_current_exp, int new_max_exp) {
	this->player_exp["current_exp"] = new_current_exp;
	this->player_exp["max_exp"] = new_max_exp;
}
void Player::SetPlayerHp(int new_current_hp) {
	this->player_hp["current_hp"] = new_current_hp;
}
void Player::SetPlayerHp(int new_current_hp, int new_max_hp) {
	this->player_hp["current_hp"] = new_current_hp;
	this->player_hp["max_hp"] = new_max_hp;
}
void Player::SetPlayerMp(int new_current_mp) {
	this->player_mp["current_mp"] = new_current_mp;
}
void Player::SetPlayerMp(int new_current_mp, int new_max_mp) {
	this->player_mp["current_mp"] = new_current_mp;
	this->player_mp["max_mp"] = new_max_mp;
}
void Player::SetPlayerGold(int new_player_gold) {
	this->player_gold = new_player_gold;
}

const std::string Player::GetPlayerName(void) {
	return this->player_name;
}
const std::string Player::GetPlayerJob(void) {
	return this->player_job;
}
const std::unordered_map<std::string, int> Player::GetPlayerLevel(void) {
	return this->player_level;
}
const std::unordered_map<std::string, int> Player::GetPlayerExp(void) {
	return this->player_exp;
}
const std::unordered_map<std::string, int> Player::GetPlayerHp(void) {
	return this->player_hp;
}
const std::unordered_map<std::string, int> Player::GetPlayerMp(void) {
	return this->player_mp;
}
const std::unordered_map<std::string, int> Player::GetPlayerStatus(void) {
	return this->player_status;
}
const int Player::GetPlayerGold(void) {
	return this->player_gold;
}

void Player::PlayerAttack(int mp_decrease_amount) {
	SetPlayerMp(GetPlayerMp().at("current_mp") - mp_decrease_amount);
}
void Player::PlayerDamage(int hp_decrease_amount) {
	SetPlayerHp(GetPlayerHp().at("current_hp") - hp_decrease_amount);
}
void Player::HpRecovery(int hp_decrease_amount) {
	SetPlayerHp(GetPlayerHp().at("current_hp") + hp_decrease_amount);
}
void Player::MpRecovery(int mp_decrease_amount) {
	SetPlayerMp(GetPlayerMp().at("current_mp") + mp_decrease_amount);
}
void Player::GainExp(int exp_increase_amount) {
	if (GetPlayerLevel().at("current_level") < GetPlayerLevel().at("max_level")) {
		if ((GetPlayerExp().at("current_exp") + exp_increase_amount) < 100) {
			SetPlayerExp(GetPlayerExp().at("current_exp") + exp_increase_amount);
		}
		else {
			SetPlayerExp(0, (GetPlayerExp().at("max_exp") * 3) / 2);
			PlayerLevelUp();
		}
	}
}

void Player::AddGold(int add_amount) {
	SetPlayerGold(GetPlayerGold() + add_amount);
}
void Player::DecreaseGold(int decrease_amount) {
	SetPlayerGold(GetPlayerGold() - decrease_amount);
}

void Player::PlayerLevelUp(void) {
	SetPlayerLevel(GetPlayerLevel().at("current_level") + 1);
}