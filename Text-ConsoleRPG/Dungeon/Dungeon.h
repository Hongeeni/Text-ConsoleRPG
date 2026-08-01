#pragma once

#include <string>
#include <random>
#include <array>
#include "DungeonType.h"
#include "AltarEvent.h"
#include "FountainEvent.h"
#include "TreasureRoomEvent.h"

class Player;

enum class DungeonEvent { Monster, Treasure, Shop, Altar, Fountain, BossFound };

struct DefeatResult {
    int goldLost = 0;
    int itemsLost = 0;
};

struct AdvanceResult {
    DungeonEvent event = DungeonEvent::Monster;
    bool playerDefeated = false;
    DefeatResult defeat;      // playerDefeated == true일 때만 유효

    TreasureResult treasure;  // event == Treasure일 때만 유효
    AltarResult altar;        // event == Altar일 때만 유효
    FountainResult fountain;  // event == Fountain일 때만 유효
};

struct EscapeResult {
    bool success = false;
    bool playerDefeated = false; // 실패 시 몬스터 조우로 이어짐
    DefeatResult defeat;
};

struct BossRoomResult {
    bool correctAnswer = false;
    bool cleared = false;
    bool playerDefeated = false;
    DefeatResult defeat;
};

// 이 클래스는 입력 수신(ReadIntInput/ReadLineInput)과 순수 로직/데이터만 담당한다.
// 문자열 메시지를 만들거나 반환하지 않는다 - 모든 결과는 구조체(값/플래그)로만 전달하며,
// 그 값을 어떤 문구로 화면에 보여줄지는 전적으로 game.cpp/log.cpp가 결정한다.
class Dungeon {
public:
    explicit Dungeon(DungeonType type);

    std::string GetName() const; // 던전 이름표(식별용 데이터, 메시지 아님)
    bool IsBossFound() const;
    bool IsExitRequested() const;
    static bool IsCleared(DungeonType type);

    AdvanceResult Advance(Player& player);
    EscapeResult TryEscape(Player& player);
    BossRoomResult EnterBossRoom(const std::string& answer, Player& player);

    static int ReadIntInput();
    static std::string ReadLineInput();

private:
    DungeonType type_;
    bool bossFound_ = false;
    bool exitRequested_ = false;
    std::mt19937 rng_{ std::random_device{}() };

    int escapeFailPercent_ = 20;

    static std::array<bool, 3> s_cleared;

    std::string GetShopName() const;
    std::string GetBossRoomAnswer() const;

    DungeonEvent RollEvent();
    AdvanceResult Resolve(DungeonEvent e, Player& player);

    struct MonsterFightOutcome {
        bool playerDefeated = false;
        DefeatResult defeat;
    };
    MonsterFightOutcome FightMonster(Player& player);

    DefeatResult OnDefeat(Player& player);
    bool IsPlayerAlive(Player& player) const;
};
