#include "player.h"

Player::Player(Player* player_info = nullptr) {
	if (player_info != nullptr) {
		this->player_name = player_info->GetPlayerName();
		this->player_current_level = player_info->GetPlayerCurrentLevel();
	}
}

// Setter
void Player::SetPlayerName(std::string new_player_name) {
	this->player_name = new_player_name;
}
void Player::SetPlayerJob(std::string new_player_job) {
	this->player_job = new_player_job;
}
void Player::SetPlayerLevel(int new_current_level) {
	this->player_current_level = new_current_level;
}
void Player::SetPlayerLife(int new_current_life) {
	this->player_current_life = new_current_life;
}
void Player::SetPlayerExp(int new_current_exp) {
	this->player_current_exp = new_current_exp;
}
void Player::SetPlayerExp(int new_current_exp, int new_max_exp) {
	this->player_current_exp = new_current_exp;
	this->player_max_exp = new_max_exp;
}
void Player::SetPlayerHp(int new_current_hp) {
	this->player_current_hp = new_current_hp;
}
void Player::SetPlayerHp(int new_current_hp, int new_max_hp) {
	this->player_current_hp = new_current_hp;
	this->player_max_hp = new_max_hp;
}
void Player::SetPlayerMp(int new_current_mp) {
	this->player_current_mp = new_current_mp;
}
void Player::SetPlayerMp(int new_current_mp, int new_max_mp) {
	this->player_current_mp = new_current_mp;
	this->player_max_mp = new_max_mp;
}
void Player::SetPlayerAttack(int new_player_attack) {
	this->player_attack = new_player_attack;
}
void Player::SetPlayerDefense(int new_player_defense) {
	this->player_defense = new_player_defense;
}
void Player::SetPlayerCritical(int new_player_critical) {
	this->player_critical = new_player_critical;
}
void Player::SetPlayerSpeed(int new_player_speed) {
	this->player_speed = new_player_speed;
}
void Player::SetPlayerGold(int new_player_gold) {
	this->player_gold = new_player_gold;
}

// Getter
const std::string Player::GetPlayerName(void) {
	return this->player_name;
}
const std::string Player::GetPlayerJob(void) {
	return this->player_job;
}
const int Player::GetPlayerCurrentLevel(void) {
	return this->player_current_level;
}
const int Player::GetPlayerCurrentLife(void) {
	return this->player_current_life;
}
const int Player::GetPlayerCurrentExp(void) {
	return this->player_current_exp;
}
const int Player::GetPlayerMaxExp(void) {
	return this->player_max_exp;
}
const int Player::GetPlayerCurrentHp(void) {
	return this->player_current_hp;
}
const int Player::GetPlayerMaxHp(void) {
	return this->player_max_hp;
}
const int Player::GetPlayerCurrentMp(void) {
	return this->player_current_mp;
}
const int Player::GetPlayerMaxMp(void) {
	return this->player_max_mp;
}
const int Player::GetPlayrerAttack(void) {
	return this->player_attack;
}
const int Player::GetPlayrerDefense(void) {
	return this->player_defense;
}
const int Player::GetPlayrerCritical(void) {
	return this->player_critical;
}
const int Player::GetPlayrerSpeed(void) {
	return this->player_speed;
}
const int Player::GetPlayerGold(void) {
	return this->player_gold;
}

// Construct Value Getter
const int Player::GetMaxExpIncreaseAmount(void) {
	return this->kMaxExpIncreaseAmount;
}
const int Player::GetAttackCost(void) {
	return this->kAttackCost;
}
const int Player::GetPlayerMaxLevel(void) {
	return this->player_max_level;
}
const int Player::GetPlayerMaxLife(void) {
	return this->player_max_life;
}

// Player Function
bool Player::PlayerAttack(int mp_decrease_amount) {
	if ((GetPlayerCurrentMp() - mp_decrease_amount) >= 0) {
		SetPlayerMp(GetPlayerCurrentMp() - mp_decrease_amount);
		return true;
	}
	return false;
}
bool Player::PlayerDamage(int hp_decrease_amount) {
	SetPlayerHp(std::min((GetPlayerCurrentHp() - hp_decrease_amount), 0));
	return IsAlive(GetPlayerCurrentHp());
}
void Player::HpRecovery(int hp_decrease_amount) {
	SetPlayerHp(std::max((GetPlayerCurrentHp() + hp_decrease_amount), GetPlayerMaxHp()));
}
void Player::MpRecovery(int mp_decrease_amount) {
	SetPlayerMp(std::max((GetPlayerCurrentMp() + mp_decrease_amount), GetPlayerMaxMp()));
}
void Player::GainExp(int exp_increase_amount) {
	if (GetPlayerCurrentLevel() < GetPlayerMaxLevel()) {
		SetPlayerExp(GetPlayerCurrentExp() + exp_increase_amount);
		if ((GetPlayerCurrentExp() + exp_increase_amount) >= GetPlayerMaxExp()) {
			SetPlayerExp((GetPlayerCurrentExp() - GetPlayerMaxExp()), GetMaxExpIncreaseAmount());
			PlayerLevelUp();
		}
	}
}

// Gold Function
void Player::AddGold(int add_amount) {
	SetPlayerGold(GetPlayerGold() + add_amount);
}
void Player::DecreaseGold(int decrease_amount) {
	SetPlayerGold(std::min((GetPlayerGold() - decrease_amount), 0));
}

Player::~Player(void) {}

// Private Player Function
void Player::PlayerLevelUp(void) {
	SetPlayerLevel(GetPlayerCurrentLevel() + 1);
}
void Player::DecreaseLife(void) {
	SetPlayerLife(std::min((GetPlayerCurrentLife() - 1), 0));
}
bool Player::IsAlive(int current_hp) {
	if (current_hp > 0) {
		return true;
	}
	DecreaseLife();
	return false;
}