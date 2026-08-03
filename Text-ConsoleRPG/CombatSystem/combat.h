#ifndef _COMBAT_H_
#define _COMBAT_H_

#include "Player\Player.h"
#include "Monster\Monster.h"

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
