#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>

namespace PlayerInfo {
    enum StatusType {
        current_level,
        current_life,
        current_exp,
        max_exp,
        current_hp,
        max_hp,
        current_mp,
        max_mp,
        power,
        defense,
        critical,
        speed,
    };
}

enum class JobType {
    Warrior,
    Mage
};

class Player {
protected:
    //PlayerLog log;

    // Constant
    const int kMaxLevel = 10;
    const int kMaxLife = 3;
    const int kMaxGold = 99999;
    const int kAttackCost = 15;
    const int kSkillCost = 20;

    // Variable
    std::string name = "Nameless";
    std::string job = "Farmer";
    std::vector<int> status = { 1, 3, 0, 100, 200, 200, 200, 200, 10, 10, 10, 10 };
    bool arousal = false;
    int gold = 0;

public:
    // Constructor
    Player(void);

    // Setter
    void SetName(std::string new_player_name);
    void SetJob(std::string new_player_job);
    void SetStatus(std::vector<int> new_status);
    void SetLevel(int new_current_level);
    void SetLife(int new_current_life);
    void SetExp(int new_current_exp);
    void SetExp(int new_current_exp, int new_max_exp);
    void SetHp(int new_current_hp);
    void SetHp(int new_current_hp, int new_max_hp);
    void SetMp(int new_current_mp);
    void SetMp(int new_current_mp, int new_max_mp);
    void SetPower(int new_player_power);
    void SetDefense(int new_player_defense);
    void SetCritical(int new_player_critical);
    void SetSpeed(int new_player_speed);

    void SetArousal(bool new_arousal);
    void SetGold(int new_player_gold);

    // Getter
    const std::string GetName(void);
    const std::string GetJob(void);
    const std::vector<int> GetStatus(void);
    const int GetCurrentLevel(void);
    const int GetCurrentLife(void);
    const int GetCurrentExp(void);
    const int GetMaxExp(void);
    const int GetCurrentHp(void);
    const int GetMaxHp(void);
    const int GetCurrentMp(void);
    const int GetMaxMp(void);
    const int GetPower(void);
    const int GetDefense(void);
    const int GetCritical(void);
    const int GetSpeed(void);

    const bool GetArousal(void);
    const int GetGold(void);

    // Constant Value Getter
    const int GetMaxLevel(void);
    const int GetMaxLife(void);
    const int GetMaxGold(void);
    const int GetAttackCost(void);
    const int GetSkillCost(void);

    // Player Function
    void PlayerAwaken(void);

    bool ToAttack(int mp_reduction_amount);
    bool GetDamage(int hp_reduction_amount);
    void HpRecovery(int hp_increase_amount);
    void MpRecovery(int mp_increase_amount);
    void GainExp(int exp_increase_amount);

    // Gold Function
    void AddGold(int add_amount);
    void DecreaseGold(int decrease_amount);

    ~Player(void);

private:
    // Private Player Function
    void LevelUp(void);
    void DecreaseLife(void);
    bool IsAlive(int current_hp);
};

#endif
