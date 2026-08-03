#include "A:\VisualStudio_C++\Text-ConsoleRPG_Solution\Text-ConsoleRPG\Player\player.h"

#include <algorithm>
#include <iostream>
#include <map>

Player::Player(void) {
	// 플레이어에게 이름을 입력받는 Log 함수 필요.
	std::cout << "what's your name?: ";
	std::cin >> this->name;
}

// Setter
void Player::SetName(std::string new_name) {
	this->name = new_name;
}
void Player::SetJob(std::string new_job) {
	this->job = new_job;
}
void Player::SetStatus(std::vector<int> new_status) {
	if (new_status.size() < this->status.size()) {
		for (int vector_index = 0; vector_index < new_status.size(); vector_index++) {
			this->status[vector_index] = new_status[vector_index];
		}
	}
	else {
		for (int vector_index = 0; vector_index < this->status.size(); vector_index++) {
			this->status[vector_index] = new_status[vector_index];
		}
	}
}
void Player::SetLevel(int new_current_level) {
	this->status[PlayerInfo::current_level] = new_current_level;
}
void Player::SetLife(int new_current_life) {
	this->status[PlayerInfo::current_life] = new_current_life;
}
void Player::SetExp(int new_current_exp) {
	this->status[PlayerInfo::current_exp] = new_current_exp;
}
void Player::SetExp(int new_current_exp, int new_max_exp) {
	this->status[PlayerInfo::current_exp] = new_current_exp;
	this->status[PlayerInfo::max_exp] = new_max_exp;
}
void Player::SetHp(int new_current_hp) {
	this->status[PlayerInfo::current_hp] = new_current_hp;
}
void Player::SetHp(int new_current_hp, int new_max_hp) {
	this->status[PlayerInfo::current_hp] = new_current_hp;
	this->status[PlayerInfo::max_hp] = new_max_hp;
}
void Player::SetMp(int new_current_mp) {
	this->status[PlayerInfo::current_mp] = new_current_mp;
}
void Player::SetMp(int new_current_mp, int new_max_mp) {
	this->status[PlayerInfo::current_mp] = new_current_mp;
	this->status[PlayerInfo::max_mp] = new_max_mp;
}
void Player::SetPower(int new_power) {
	this->status[PlayerInfo::power] = new_power;
}
void Player::SetDefense(int new_defense) {
	this->status[PlayerInfo::defense] = new_defense;
}
void Player::SetCritical(int new_critical) {
	this->status[PlayerInfo::critical] = new_critical;
}
void Player::SetSpeed(int new_speed) {
	this->status[PlayerInfo::speed] = new_speed;
}

void Player::SetArousal(bool new_arousal) {
	this->arousal = new_arousal;
}
void Player::SetGold(int new_gold) {
	this->gold = new_gold;
}

// Getter
const std::string Player::GetName(void) {
	return this->name;
}
const std::string Player::GetJob(void) {
	return this->job;
}
const std::vector<int> Player::GetStatus(void) {
	return this->status;
}
const int Player::GetCurrentLevel(void) {
	return this->status[PlayerInfo::current_level];
}
const int Player::GetCurrentLife(void) {
	return this->status[PlayerInfo::current_life];
}
const int Player::GetCurrentExp(void) {
	return this->status[PlayerInfo::current_exp];
}
const int Player::GetMaxExp(void) {
	return this->status[PlayerInfo::max_exp];
}
const int Player::GetCurrentHp(void) {
	return this->status[PlayerInfo::current_hp];
}
const int Player::GetMaxHp(void) {
	return this->status[PlayerInfo::max_hp];
}
const int Player::GetCurrentMp(void) {
	return this->status[PlayerInfo::current_mp];
}
const int Player::GetMaxMp(void) {
	return this->status[PlayerInfo::max_mp];
}
const int Player::GetPower(void) {
	return this->status[PlayerInfo::power];
}
const int Player::GetDefense(void) {
	return this->status[PlayerInfo::defense];
}
const int Player::GetCritical(void) {
	return this->status[PlayerInfo::critical];
}
const int Player::GetSpeed(void) {
	return this->status[PlayerInfo::speed];
}

const bool Player::GetArousal(void) {
	return this->arousal;
}
const int Player::GetGold(void) {
	return this->gold;
}

// Constant Value Getter
const int Player::GetMaxLevel(void) {
	return this->kMaxLevel;
}
const int Player::GetMaxLife(void) {
	return this->kMaxLife;
}
const int Player::GetMaxGold(void) {
	return this->kMaxGold;
}
const int Player::GetAttackCost(void) {
	return this->kAttackCost;
}
const int Player::GetSkillCost(void) {
	return this->kSkillCost;
}

// Player Function
void Player::PlayerAwaken(void) {
	JobType job_type = JobType::Warrior;
	//job_type = PlayerLog.SelectJob();

	if (job_type == JobType::Warrior) {
		this->SetJob("Warrior");
		this->SetDefense(this->GetDefense() + 20);

		this->SetArousal(true);
	}
	else if (job_type == JobType::Mage) {
		this->SetJob("Mage");
		this->SetPower(this->GetPower() + 20);

		this->SetArousal(true);
	}
}

bool Player::ToAttack(int mp_decrease_amount) {
	if ((this->GetCurrentMp() - mp_decrease_amount) >= 0) {
		this->SetMp(this->GetCurrentMp() - mp_decrease_amount);
		return true;
	}
	return false;
}
bool Player::GetDamage(int hp_decrease_amount) {
	this->SetHp(std::max((this->GetCurrentHp() - hp_decrease_amount), 0));
	return this->IsAlive(this->GetCurrentHp());
}
void Player::HpRecovery(int hp_increase_amount) {
	this->SetHp(std::min((this->GetCurrentHp() + hp_increase_amount), this->GetMaxHp()));
}
void Player::MpRecovery(int mp_increase_amount) {
	this->SetMp(std::min((this->GetCurrentMp() + mp_increase_amount), this->GetMaxMp()));
}
void Player::GainExp(int exp_increase_amount) {
	if (this->GetCurrentLevel() < this->GetMaxLevel()) {
		this->SetExp(GetCurrentExp() + exp_increase_amount);
		if ((this->GetCurrentExp() + exp_increase_amount) >= this->GetMaxExp()) {
			this->LevelUp();
		}
	}
}

// Gold Function
void Player::AddGold(int add_amount) {
	this->SetGold(std::min((this->GetGold() + add_amount), this->GetMaxGold()));
}
void Player::DecreaseGold(int decrease_amount) {
	this->SetGold(std::max((this->GetGold() - decrease_amount), 0));
}

Player::~Player(void) {
	std::cout << "The player object was successfully delete." << std::endl;
}

// Private Player Function
void Player::LevelUp(void) {
	int new_max_exp = (status[PlayerInfo::max_exp] * 3) / 2;

	this->SetLevel(std::min(this->GetCurrentLevel() + 1, this->GetMaxLevel()));
	this->SetExp((this->GetCurrentExp() - this->GetMaxExp()), new_max_exp);
	this->SetHp((this->GetMaxHp() * 4) / 3, (this->GetMaxHp() * 4) / 3);
	this->SetMp((this->GetMaxMp() * 4) / 3, (this->GetMaxMp() * 4) / 3);
	this->SetPower((this->GetPower() * 5) / 4);
	this->SetDefense((this->GetDefense() * 5) / 4);
	this->SetCritical(this->GetCritical() + 1);
	this->SetSpeed(this->GetSpeed() + 1);
}
void Player::DecreaseLife(void) {
	this->SetLife(std::max((this->GetCurrentLife() - 1), 0));
}
bool Player::IsAlive(int current_hp) {
	if (current_hp > 1) {
		return true;
	}
	DecreaseLife();
	return false;
}