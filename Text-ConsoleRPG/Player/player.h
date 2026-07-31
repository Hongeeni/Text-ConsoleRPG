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

    std::map<std::string, unsigned short> player_level = { {"current_level", 1}, {"max_level", 10} };
    std::map<std::string, unsigned short> player_exp = { {"current_exp", 0}, {"max_exp", 100} };
    std::map<std::string, unsigned short> player_life = { {"current_life", 3}, {"max_life", 3} };
    std::map<std::string, unsigned short> player_hp = { {"current_hp", 200}, {"max_hp", 200} };
    std::map<std::string, unsigned short> player_mp = { {"current_mp", 200}, {"max_mp", 200} };
    std::map<std::string, unsigned short> player_status = { {"attack", 30}, {"defense", 30}, {"critical", 10}, {"speed", 10} };

    const unsigned short kMaxExpIncreaseAmount = (player_exp.at("max_exp") * 3) / 2;
    const unsigned short kAttackCost = 15;
    const unsigned short kEmpty = 0;
    unsigned short player_gold = 0;

public:
    Player(const std::string new_player_name, const std::map<std::string, unsigned short> new_player_status);

    // Setter
    void SetPlayerName(std::string new_player_name);
    void SetPlayerJob(std::string new_player_job);
    void SetPlayerLevel(unsigned short new_current_level);
    void SetPlayerLevel(unsigned short new_current_level, unsigned short new_max_level);
    void SetPlayerExp(unsigned short new_current_exp);
    void SetPlayerExp(unsigned short new_current_exp, unsigned short new_max_exp);
    void SetPlayerLife(unsigned short new_current_life);
    void SetPlayerLife(unsigned short new_current_life, unsigned short new_max_exp);
    void SetPlayerHp(unsigned short new_current_hp);
    void SetPlayerHp(unsigned short new_current_hp, unsigned short new_max_hp);
    void SetPlayerMp(unsigned short new_current_hp);
    void SetPlayerMp(unsigned short new_current_hp, unsigned short new_max_hp);
    void SetPlayerGold(unsigned short new_player_gold);

    // Getter
    const std::string GetPlayerName(void);
    const std::string GetPlayerJob(void);
    const std::map<std::string, unsigned short> GetPlayerLevel(void);
    const std::map<std::string, unsigned short> GetPlayerExp(void);
    const std::map<std::string, unsigned short> GetPlayerLife(void);
    const std::map<std::string, unsigned short> GetPlayerHp(void);
    const std::map<std::string, unsigned short> GetPlayerMp(void);
    const std::map<std::string, unsigned short> GetPlayerStatus(void);
    const unsigned short GetMaxExpIncreaseAmount(void);
    const unsigned short GetAttackCost(void);
    const unsigned short GetPlayerGold(void);

    // Player Function
    bool PlayerAttack(unsigned short mp_reduction_amount);
    bool PlayerDamage(unsigned short hp_reduction_amount);
    void HpRecovery(unsigned short hp_increase_amount);
    void MpRecovery(unsigned short mp_increase_amount);
    void GainExp(unsigned short exp_increase_amount);

    // Gold Function
    void AddGold(unsigned short add_amount);
    void DecreaseGold(unsigned short decrease_amount);
    //bool SpendGold(int amount);                // 골드 부족하면 false

    // 소멸자를 순수 가상함수로 선언
    virtual ~Player(void) = 0;

private:
    // Private Player Function
    void PlayerLevelUp(void);
    void DecreaseLife(void);
    bool IsAlive(unsigned short current_hp);
};

#endif
