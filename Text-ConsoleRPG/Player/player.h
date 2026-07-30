#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <unordered_map>
#include <string>

class Player {
protected:
    std::string player_name = "Nameless";
    std::string player_job = "Farmer";

    std::unordered_map<std::string, int> player_level = { {"current_level", 1}, {"max_level", 10} };
    std::unordered_map<std::string, int> player_exp = { {"current_exp", 0}, {"max_exp", 100} };
    std::unordered_map<std::string, int> player_hp = { {"current_hp", 200}, {"max_hp", 200} };
    std::unordered_map<std::string, int> player_mp = { {"current_mp", 200}, {"max_mp", 200} };
    std::unordered_map<std::string, int> player_status = { {"attack", 30}, {"defense", 30}, {"critical", 10}, {"speed", 10} };

    int player_gold = 0;

public:
    Player();

    // Setter
    void SetPlayerName(std::string new_player_name);
    void SetPlayerJob(std::string new_player_job);
    void SetPlayerLevel(int new_current_level);
    void SetPlayerLevel(int new_current_level, int new_max_level);
    void SetPlayerExp(int new_current_exp);
    void SetPlayerExp(int new_current_exp, int new_max_exp);
    void SetPlayerHp(int new_current_hp);
    void SetPlayerHp(int new_current_hp, int new_max_hp);
    void SetPlayerMp(int new_current_hp);
    void SetPlayerMp(int new_current_hp, int new_max_hp);
    void SetPlayerGold(int new_player_gold);

    // Getter
    const std::string GetPlayerName(void);
    const std::string GetPlayerJob(void);
    const std::unordered_map<std::string, int> GetPlayerLevel(void);
    const std::unordered_map<std::string, int> GetPlayerExp(void);
    const std::unordered_map<std::string, int> GetPlayerHp(void);
    const std::unordered_map<std::string, int> GetPlayerMp(void);
    const std::unordered_map<std::string, int> GetPlayerStatus(void);
    const int GetPlayerGold(void);

    //void PrintStatus();
    //bool IsAlive();
    void PlayerAttack(int mp_reduction_amount);
    void PlayerDamage(int hp_reduction_amount);
    void HpRecovery(int hp_increase_amount);
    void MpRecovery(int mp_increase_amount);
    void GainExp(int exp_increase_amount);
    //void ChooseJob(JobType job);
    void AddGold(int add_amount);
    void DecreaseGold(int decrease_amount);
    //bool SpendGold(int amount);                // 골드 부족하면 false

private:
    void PlayerLevelUp(void);
};

#endif
