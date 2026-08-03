#include "CombatSystem\combat.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>

CombatSystem::CombatSystem(Player& player, Monster& monster)
    : player(player), monster(monster) {
    this->attack_token = player.GetSpeed() - monster.GetSpeed();
}

bool CombatSystem::IsFirstAttack() const {
    srand((unsigned int)time(NULL));
    if (this->attack_token > 0) {
        return (rand() % (2 + this->attack_token));
    }
    else if (this->attack_token < 0) {
        return !(rand() % (2 - this->attack_token));
    }
    if (rand() % 2) {
        return true;
    }
    return false;
}

void CombatSystem::StartBattle(void) {
    bool is_kill_monster = false;
    bool is_kill_player = false;
    this->behavior_token = this->token_maximum;

    do {
        BehaviorType player_input = BehaviorType::basic_attack;
        if (this->IsFirstAttack()) {
            // Player Turn
            while (!this->PlayerBehavior(player_input, is_kill_monster));
            if (is_kill_monster) {
                this->GetResult();
                break;
            }

            // Monster Turn
            if (this->MonsterBehavior(is_kill_player)) {
                //CombatLog.PlayerDeath();
                break;
            }
        }
        else {
            // Monster Turn
            if (this->MonsterBehavior(is_kill_player)) {
                //CombatLog.PlayerDeath();
                break;
            }

            // Player Turn
            while (!this->PlayerBehavior(player_input, is_kill_monster));
            if (is_kill_monster) {
                this->GetResult();
                break;
            }
        }
    } while (!is_kill_monster && !is_kill_player);
}

const int CombatSystem::AttackCalculation(const int attacker_power, const int striker_defense, const int attacker_critical) {
    int damage = (attacker_power - striker_defense);

    srand((unsigned int)time(NULL));
    if ((rand() % 100) < attacker_critical) {
        damage *= 1.5;
    }

    damage = std::max(1, damage);
    //CombatLog.Progress();
    return damage;
}

bool CombatSystem::PlayerBehavior(const BehaviorType now_behavior, bool& kill_monster) {
    if (now_behavior == BehaviorType::use_item) {
        this->behavior_token -= this->use_item_cost;
        // 아이템 사용 처리는 인벤토리 쪽 함수로 연결
    }
    else {
        this->behavior_token -= this->attack_cost;
        int power = player.GetPower();

        if (now_behavior == BehaviorType::skill_attack) {
            if (player.ToAttack(player.GetSkillCost())) {
                power = player.GetPower() * 2;              // (미확정) 스킬 배율
            }
            else {
                player.ToAttack(player.GetAttackCost());
            }
        }

        kill_monster = !(monster.GetDamage(AttackCalculation(power, monster.GetDefence(), player.GetCritical())));
    }
    return (this->behavior_token < 1);
}

bool CombatSystem::MonsterBehavior(bool& kill_player) {
    kill_player = !(player.GetDamage(AttackCalculation(monster.GetPower(), player.GetDefense(), monster.GetCritical())));
    return kill_player;
}

void CombatSystem::GetResult(void) const {
    //CombatLog.PlayerWin();

    //CombatLog.ExpReward();
    player.GainExp(monster.GetRewardExp());
    //CombatLog.GoldReward();
    player.AddGold(monster.GetDropGold());
}