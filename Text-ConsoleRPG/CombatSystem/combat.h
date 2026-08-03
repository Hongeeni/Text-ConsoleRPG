#ifndef _COMBAT_H_
#define _COMBAT_H_

//#include "monster.h"
#include "player.h"

#include <random>

class Monster {
protected:
    std::string monster_name = "Nameless";

    int current_hp = 200;
    int max_hp = 200;
    int power = 30;
    int defense = 30;
    int critical = 10;
    int speed = 10;

    int gain_exp = 10;
    int gain_gold = 10;

public:
    const int GetCurrentHp() {
        return this->current_hp;
    }
    const int GetPower() {
        return this->power;
    }
    const int GetDefense() {
        return this->defense;
    }
    const int GetCritical() {
        return this->critical;
    }
    const int GetSpeed() {
        return this->speed;
    }

    const int GetExp() {
        return this->gain_exp;
    }
    const int GetGold() {
        return this->gain_gold;
    }

    bool GetDamage(int hp_decrease_amount) {
        return false;
    }
};

enum class BehaviorType {
    use_item,
    basic_attack,
    skill_attack
};

class CombatSystem {
public:
    CombatSystem(Player& player, Monster& monster);
    void StartBattle(void);

private:
    Player& player;
    Monster& monster;

    static const char token_maximum = 2;
    static const char use_item_cost = 1;
    static const char attack_cost = 2;

    char  behavior_token = 0;
    bool is_first_attack = false;
    int attack_token = 0;

    bool IsFirstAttack(void) const;
    bool PlayerBehavior(const BehaviorType now_behavior, bool& kill_monster);
    bool MonsterBehavior(bool& kill_player);

    const int AttackCalculation(const int attacker_power, const int striker_defense, const int attacker_critical);
    void GetResult(void) const;
};

#endif
