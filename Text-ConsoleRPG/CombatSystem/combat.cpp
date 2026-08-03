#include "CombatSystem\combat.h"
#include "Logger\Logger.h"
#include "Inventory\Inventory.h"
#include "Item\Itemdata.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>

CombatSystem::CombatSystem(Player& player, Monster& monster)
    : player(player), monster(monster) {
    this->attack_token = player.GetSpeed() - monster.GetSpeed();
}

bool CombatSystem::IsFirstAttack() {
    const int playerSpeed = player.GetSpeed();
    const int monsterSpeed = monster.GetSpeed();
    const int total = playerSpeed + monsterSpeed;

    if (total <= 0) {
        return true;
    }

    std::bernoulli_distribution dist(static_cast<double>(playerSpeed) / total);
    return dist(rng);
}

BehaviorType CombatSystem::AskPlayerBehavior() {
    BattleMenu(this->behavior_token, player.GetCurrentMp(), player.GetSkillCost());

    int choice = 0;
    std::cin >> choice;

    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return BehaviorType::basic_attack;
    }

    if (choice == 2) return BehaviorType::skill_attack;
    if (choice == 3) return BehaviorType::use_item;
    return BehaviorType::basic_attack;
}

void CombatSystem::PlayerTurn(bool& kill_monster) {
    // 라운드가 시작될 때마다 토큰을 채운다
    this->behavior_token = this->token_maximum;

    while (this->behavior_token >= 1 && monster.IsAlive()) {
        BehaviorType behavior = this->AskPlayerBehavior();

        // PlayerBehavior가 true를 돌려주면 토큰이 바닥난 것 -> 턴 종료
        if (this->PlayerBehavior(behavior, kill_monster)) {
            break;
        }
        if (kill_monster) {
            break;
        }
    }
}

void CombatSystem::StartBattle(void) {
    bool is_kill_monster = false;
    bool is_kill_player = false;

    do {
        if (this->IsFirstAttack()) {
            this->PlayerTurn(is_kill_monster);
            if (is_kill_monster) {
                this->GetResult();
                break;
            }
            if (this->MonsterBehavior(is_kill_player)) {
                break;
            }
        }
        else {
            if (this->MonsterBehavior(is_kill_player)) {
                break;
            }
            this->PlayerTurn(is_kill_monster);
            if (is_kill_monster) {
                this->GetResult();
                break;
            }
        }
    } while (!is_kill_monster && !is_kill_player);
}

const int CombatSystem::AttackCalculation(const int attacker_power, const int striker_defense, const int attacker_critical) {
    std::bernoulli_distribution crit(attacker_critical / 100.0);
    int damage = std::max(1, attacker_power - striker_defense);
    if (crit(rng)) {
        damage = static_cast<int>(damage * 1.5);
    }
    return damage;
}

bool CombatSystem::PlayerBehavior(const BehaviorType now_behavior, bool& kill_monster) {
    if (now_behavior == BehaviorType::use_item) {
        // 포션류만 추려서 보여준다
        std::vector<std::string> potions;
        for (const auto& item : g_player_inventory.ViewInventory()) {
            ItemData data = FindItem(item.name_);
            if (data.found && data.category == "potion") {
                potions.push_back(item.name_);
            }
        }

        if (potions.empty()) {
            std::cout << "사용할 수 있는 아이템이 없습니다.\n";
            return false;   // 토큰을 소모하지 않고 다시 선택하게 한다
        }

        std::cout << "\n[아이템]\n";
        for (size_t i = 0; i < potions.size(); ++i) {
            std::cout << "  " << (i + 1) << ". " << potions[i] << "\n";
        }
        std::cout << "  0. 취소\n선택: ";

        int pick = 0;
        std::cin >> pick;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            pick = 0;
        }
        if (pick < 1 || pick > static_cast<int>(potions.size())) {
            return false;   // 취소. 토큰 소모 없음
        }

        UseItemOnPlayer(g_player_inventory, player, potions[pick - 1]);
        std::cout << "[" << potions[pick - 1] << "]을(를) 사용했습니다.\n";

        this->behavior_token -= this->use_item_cost;
    }

    else {
        this->behavior_token -= this->attack_cost;
        int power = player.GetPower();

        if (now_behavior == BehaviorType::skill_attack) {
            if (player.ToAttack(player.GetSkillCost())) {
                // 마법사는 스킬 위력 3배
                const int multiplier = (player.GetJob() == "Mage") ? 3 : 2;
                power = player.GetPower() * multiplier;
            }
            else {
                std::cout << "마나가 부족해 일반 공격으로 대체됩니다.\n";
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