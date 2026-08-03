#include "AltarEvent.h"
#include "Player.h"

#include <random>
#include <algorithm>
#include <vector>

namespace {
    std::mt19937& Rng() {
        static std::mt19937 rng{ std::random_device{}() };
        return rng;
    }

    const int kStatUp = 2;
    const int kStatDown = 1;
    const int kMaxHpUp = 10;

    enum Effect {
        HealHp, HealMp, PowerUp, DefenseUp, CriticalUp, SpeedUp, MaxHpUp,
        DamageHp, DrainMp, PowerDown, SpeedDown,
        Nothing,
    };

    const std::vector<double> kWeights = {
        13.0,  // HealHp
        11.0,  // HealMp
         8.0,  // PowerUp
         8.0,  // DefenseUp
         6.0,  // CriticalUp
         5.0,  // SpeedUp
         4.0,  // MaxHpUp

        14.0,  // DamageHp
        13.0,  // DrainMp
         3.0,  // PowerDown
         3.0,  // SpeedDown

        12.0,  // Nothing
    };
}

AltarResult AltarEvent::Trigger(Player& player) {
    AltarResult result;

    std::discrete_distribution<int> dist(kWeights.begin(), kWeights.end());
    const Effect effect = static_cast<Effect>(dist(Rng()));

    switch (effect) {

        // ---- 축복 ----

    case HealHp: {
        int heal = std::min(player.GetMaxHp() / 4,
            player.GetMaxHp() - player.GetCurrentHp());
        if (heal > 0) {
            player.HpRecovery(heal);
            result.blessed = true;
            result.target = "체력";
            result.amount = heal;
        }
        break;
    }

    case HealMp: {
        int heal = std::min(player.GetMaxMp() / 2,
            player.GetMaxMp() - player.GetCurrentMp());
        if (heal > 0) {
            player.MpRecovery(heal);
            result.blessed = true;
            result.target = "마나";
            result.amount = heal;
        }
        break;
    }

    case PowerUp:
        player.SetPower(player.GetPower() + kStatUp);
        result.blessed = true;
        result.target = "공격력";
        result.amount = kStatUp;
        break;

    case DefenseUp:
        player.SetDefense(player.GetDefense() + kStatUp);
        result.blessed = true;
        result.target = "방어력";
        result.amount = kStatUp;
        break;

    case CriticalUp:
        player.SetCritical(player.GetCritical() + kStatUp);
        result.blessed = true;
        result.target = "치명타";
        result.amount = kStatUp;
        break;

    case SpeedUp:
        player.SetSpeed(player.GetSpeed() + kStatUp);
        result.blessed = true;
        result.target = "속도";
        result.amount = kStatUp;
        break;

    case MaxHpUp:
        player.SetHp(player.GetCurrentHp(), player.GetMaxHp() + kMaxHpUp);
        result.blessed = true;
        result.target = "최대 체력";
        result.amount = kMaxHpUp;
        break;

        // ---- 저주 ----

    case DamageHp: {
        int damage = std::max(1, player.GetCurrentHp() / 4);
        damage = std::min(damage, player.GetCurrentHp() - 1);
        if (damage > 0) {
            player.GetDamage(damage);
            result.target = "체력";
            result.amount = damage;
        }
        break;
    }

    case DrainMp: {
        int drain = player.GetCurrentMp() / 2;
        if (drain > 0) {
            player.SetMp(player.GetCurrentMp() - drain);
            result.target = "마나";
            result.amount = drain;
        }
        break;
    }

    case PowerDown:
        player.SetPower(player.GetPower() - kStatDown);
        result.target = "공격력";
        result.amount = kStatDown;
        break;

    case SpeedDown:
        player.SetSpeed(player.GetSpeed() - kStatDown);
        result.target = "속도";
        result.amount = kStatDown;
        break;

        // ---- 무반응 ----

    case Nothing:
    default:
        break;
    }

    return result;
}