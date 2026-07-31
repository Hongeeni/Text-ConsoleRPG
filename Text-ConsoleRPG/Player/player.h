#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

class Player {
protected:
    std::string player_name = "Nameless";
    std::string player_job = "Unemployed";

    int player_current_level = 1;
    int player_current_life = 3;
    int player_current_exp = 0;
    int player_max_exp = 100;
    int player_current_hp = 200;
    int player_max_hp = 200;
    int player_current_mp = 200;
    int player_max_mp = 200;
    int player_attack = 30;
    int player_defense = 30;
    int player_critical = 10;
    int player_speed = 10;
    int player_gold = 0;

    // Construct Value
    const int player_max_level = 10;
    const int kMaxExpIncreaseAmount = (player_max_exp * 3) / 2;
    const int kAttackCost = 15;
    const int player_max_life = 3;

public:
    Player(Player* player_info = nullptr);

    // Setter
    void SetPlayerName(std::string new_player_name);
    void SetPlayerJob(std::string new_player_job);
    void SetPlayerLevel(int new_current_level);
    void SetPlayerLife(int new_current_life);
    void SetPlayerExp(int new_current_exp);
    void SetPlayerExp(int new_current_exp, int new_max_exp);
    void SetPlayerHp(int new_current_hp);
    void SetPlayerHp(int new_current_hp, int new_max_hp);
    void SetPlayerMp(int new_current_mp);
    void SetPlayerMp(int new_current_mp, int new_max_mp);
    void SetPlayerAttack(int new_player_attack);
    void SetPlayerDefense(int new_player_defense);
    void SetPlayerCritical(int new_player_critical);
    void SetPlayerSpeed(int new_player_speed);
    void SetPlayerGold(int new_player_gold);

    // Getter
    const std::string GetPlayerName(void);
    const std::string GetPlayerJob(void);
    const int GetPlayerCurrentLevel(void);
    const int GetPlayerCurrentLife(void);
    const int GetPlayerCurrentExp(void);
    const int GetPlayerMaxExp(void);
    const int GetPlayerCurrentHp(void);
    const int GetPlayerMaxHp(void);
    const int GetPlayerCurrentMp(void);
    const int GetPlayerMaxMp(void);
    const int GetPlayrerAttack(void);
    const int GetPlayrerDefense(void);
    const int GetPlayrerCritical(void);
    const int GetPlayrerSpeed(void);
    const int GetPlayerGold(void);

    // Construct Value Getter
    const int GetMaxExpIncreaseAmount(void);
    const int GetAttackCost(void);
    const int GetPlayerMaxLevel(void);
    const int GetPlayerMaxLife(void);

    // Player Function
    bool PlayerAttack(int mp_reduction_amount);
    bool PlayerDamage(int hp_reduction_amount);
    void HpRecovery(int hp_increase_amount);
    void MpRecovery(int mp_increase_amount);
    void GainExp(int exp_increase_amount);

    // Gold Function
    void AddGold(int add_amount);
    void DecreaseGold(int decrease_amount);
    //bool SpendGold(int amount);                // 골드 부족하면 false

    // 소멸자를 순수 가상함수로 선언
    virtual ~Player(void) = 0;

private:
    // Private Player Function
    void PlayerLevelUp(void);
    void DecreaseLife(void);
    bool IsAlive(int current_hp);
};

#endif
