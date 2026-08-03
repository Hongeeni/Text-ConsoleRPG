#pragma once

#include <string>
#include <random>
#include <array>
#include "DungeonType.h"
#include "AltarEvent.h"
#include "FountainEvent.h"
#include "TreasureRoomEvent.h"

class Player;
class Monster;

enum class DungeonEvent { Monster, Treasure, Shop, Altar, Fountain, BossFound };

struct DefeatResult {
    int goldLost = 0;
    int itemsLost = 0;
};

// 전투 1회 결과
struct MonsterFightResult {
    std::string monsterName;
    bool monsterDefeated = false;
    std::string dropName;          // 승리 시 획득한 드랍 아이템 (없으면 빈 문자열)
};

struct AdvanceResult {
    DungeonEvent event = DungeonEvent::Monster;
    bool playerDefeated = false;
    DefeatResult defeat;             // playerDefeated == true일 때만 유효

    MonsterFightResult monster;      // event == Monster일 때만 유효
    TreasureResult treasure;         // event == Treasure일 때만 유효
    AltarResult altar;               // event == Altar일 때만 유효
    FountainResult fountain;         // event == Fountain일 때만 유효
};

struct EscapeResult {
    bool success = false;
    bool playerDefeated = false;     // 탈출 실패 후 전투에서 사망
    MonsterFightResult monster;      // success == false일 때만 유효
    DefeatResult defeat;
};

struct BossRoomResult {
    bool alreadyCleared = false;     // 이미 클리어한 던전이면 true (나머지 값 전부 무효)
    bool correctAnswer = false;
    bool cleared = false;
    bool playerDefeated = false;
    MonsterFightResult monster;      // correctAnswer == true일 때만 유효
    DefeatResult defeat;
};

// 입력 수신과 순수 로직만 담당. 출력은 하지 않는다.
// 결과는 전부 구조체로 반환하며, 화면 표시는 Logger / 전체 흐름은 game.cpp가 담당한다.
class Dungeon {
public:
    explicit Dungeon(DungeonType type);

    std::string GetName() const;
    bool IsBossFound() const;
    bool IsExitRequested() const;
    static bool IsCleared(DungeonType type);

    AdvanceResult Advance(Player& player);
    EscapeResult TryEscape(Player& player);
    BossRoomResult EnterBossRoom(const std::string& answer, Player& player);

    // 입력 수신 전용 (검증/재입력은 game.cpp가 반복 호출로 처리)
    static int ReadIntInput();
    static std::string ReadLineInput();

private:
    DungeonType type_;
    bool bossFound_ = false;
    bool exitRequested_ = false;
    std::mt19937 rng_{ std::random_device{}() };

    int escapeFailPercent_ = 20;

    // 던전 타입별 클리어 여부 (인덱스 = static_cast<int>(DungeonType))
    static std::array<bool, 3> s_cleared;

    std::string GetShopName() const;       // Shop.cpp kShopList()의 실제 이름과 일치해야 함
    std::string GetBossRoomAnswer() const; // 보스방 정답 (미확정)

    DungeonEvent RollEvent();
    AdvanceResult Resolve(DungeonEvent e, Player& player);

    Monster PickBoss() const;                     // 던전당 1마리 고정
    Monster PickNormalMonster();                  // 일반 몬스터 랜덤
    MonsterFightResult FightMonster(Player& player, Monster& monster);

    DefeatResult OnDefeat(Player& player);
    bool IsPlayerAlive(Player& player) const;
};