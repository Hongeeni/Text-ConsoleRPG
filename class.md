# 텍스트 RPG — 클래스 설계 문서

## 목차
1. 클래스 개요
2. 클래스별 함수 명세
3. 실행 흐름 (호출 관계)
4. 아직 결정 안 된 것

---

## 1. 클래스 개요

### 1순위

| 클래스 | 파일 | 역할 |
|---|---|---|
| Player | Player.h / Player.cpp | 이름·스탯·골드·인벤토리·착용 장비 관리 |
| Monster | Monster.h / Monster.cpp | 몬스터 한 마리의 전투 데이터 생성/관리 |
| Item (Consumable/EquipmentItem/Material) | Item.h / Item.cpp | 아이템 기반 클래스 + 소비/장비/재료 3종 상속 |
| CombatSystem | CombatSystem.h / CombatSystem.cpp | 전투 한 판 진행 |
| Dungeon | Dungeon.h / Dungeon.cpp | 던전 진행 + 랜덤 이벤트 |
| Inventory | Inventory.h / Inventory.cpp | 보유 아이템 목록 관리 |

### 2순위

| 클래스 | 파일 | 역할 |
|---|---|---|
| EquipmentManager | EquipmentManager.h / EquipmentManager.cpp | 장비 착용/해제/교체 메뉴 |
| PotionCrafting | PotionCrafting.h / PotionCrafting.cpp | 포션 제작 |
| Shop | Shop.h / Shop.cpp | 아이템 구매/판매 |
| Logger | Logger.h / Logger.cpp | 이벤트 로그, 몬스터 처치 집계 |
| Game | Game.h / Game.cpp (+ main.cpp) | 전체 게임 흐름 관리 |

---

## 2. 클래스별 함수 명세

### 1순위

#### Player
```cpp
class Player {
public:
    Player(string name);                       // 이름 받아 레벨1 기본 스탯으로 초기화
    void PrintStatus();                        // 상태창 출력
    bool IsAlive();
    void TakeDamage(int amount);
    void Heal(int amount);
    void GainExp(int amount);                  // 100 도달 시 내부에서 자동 LevelUp
    void ChooseJob(JobType job);               // 레벨3 도달 시 호출
    void AddGold(int amount);
    bool SpendGold(int amount);                // 골드 부족하면 false
    Inventory& GetInventory();
    void EquipItem(EquipmentSlot slot, EquipmentItem* item);
    void UnequipItem(EquipmentSlot slot);
    EquipmentItem* GetEquippedItem(EquipmentSlot slot);
    // Getter: GetName, GetLevel, GetHP, GetMaxHP, GetMana, GetMaxMana,
    //         GetAttack, GetDefense, GetCritical, GetSpeed, GetExp, GetGold
private:
    void LevelUp();                            // GainExp 내부에서만 호출, 외부 직접 호출 금지
    // 멤버: name, job, level, hp/maxHp, mana/maxMana, attack, defense, critical,
    //       speed, exp, gold, Inventory inventory, map<EquipmentSlot,EquipmentItem*> equipped
};
```

#### Monster
```cpp
class Monster {
public:
    static Monster CreateForDungeon(DungeonType type, int playerLevel);
    // 체력 (Lv*20~Lv*30), 공격력 (Lv*5~Lv*10) 범위 랜덤 생성
    bool IsAlive();
    void TakeDamage(int amount);
    // Getter: GetName, GetHP, GetAttack, GetSpeed
private:
    Monster(string name, int hp, int attack, int speed); // private, 팩토리로만 생성
};
```

#### Item / Consumable / EquipmentItem / Material
```cpp
class Item {
public:
    Item(string name, ItemType type, int price);
    virtual ~Item();
    // Getter: GetName, GetType, GetPrice
};
class Consumable : public Item {
public:
    Consumable(string name, int price, ConsumableEffect effect, int value);
    void ApplyEffect(Player& player);   // 체력+50 또는 공격력+10(전투 한정) 적용
};
class EquipmentItem : public Item {
public:
    EquipmentItem(string name, int price, EquipmentSlot slot, int statBonus);
    // Getter: GetSlot, GetStatBonus
};
class Material : public Item {
public:
    Material(string name, int price);   // 포션 재료용, 별도 함수 없음
};
```

#### CombatSystem
```cpp
class CombatSystem {
public:
    void StartBattle(Player& player, Monster& monster);  // 유일한 public 진입점
private:
    bool DecideFirstTurn(Player& player, Monster& monster);   // 속도 비교, 동률=랜덤
    void ExecutePlayerTurn(Player& player, Monster& monster, PlayerAction action);
    void ExecuteMonsterTurn(Monster& monster, Player& player); // 항상 자동 공격
    int CalculateDamage(int attackerAtk, int defenderDef, int critical); // 공식 미정
    bool TryEscape(Player& player);            // 확률 공식 미정
    void ApplyVictoryReward(Player& player);   // 경험치50, 골드10~20, 아이템30%
    void HandleDefeat(Player& player);         // 게임오버 처리
};
```

#### Dungeon
```cpp
class Dungeon {
public:
    Dungeon(DungeonType type);                      // 슬라임/좀비/골렘 중 하나로 고정
    void EnterProgressionLoop(Player& player);      // 전진/인벤토리/던전상점/탈출 루프
    Shop CreateDungeonShop();                       // 가격 1.5배 상점 생성
private:
    void TriggerRandomEvent(Player& player);        // 몬스터조우/보물상자 등
    Monster GenerateMonster(int playerLevel);       // 던전 타입에 맞는 몬스터 생성
};
```

#### Inventory
```cpp
class Inventory {
public:
    ~Inventory();                               // 보유 아이템 메모리 해제
    void AddItem(Item* item);
    void RemoveItem(int index);
    void Display();
    void UseItem(int index, Player& player);    // 소비 아이템만 처리 후 제거
    vector<Item*> GetMaterials();               // Material 타입만 필터링
    const vector<Item*>& GetItems();
};
```

### 2순위

#### EquipmentManager
```cpp
class EquipmentManager {
public:
    void DisplayMenu(Player& player);
    void SelectSlotItem(Player& player, int itemIndex);
    // 착용중인 걸 선택=해제 / 동일 슬롯의 다른 장비 선택=자동 교체 / 미착용 선택=착용
};
```

#### PotionCrafting
```cpp
struct Recipe {
    vector<string> requiredMaterialNames;
    string resultPotionName;
};
class PotionCrafting {
public:
    void DisplayMenu(Inventory& inventory);                       // 보유 재료만 출력
    void CraftFromRecipe(int recipeIndex, Player& player);        // 레시피 먼저 선택
    void CraftFromMaterials(vector<int> materialIndices, Player& player); // 재료 먼저 선택
private:
    PotionQuality RollQuality();   // 미흡/평범/잘만들어짐 랜덤 결정
};
```

#### Shop
```cpp
class Shop {
public:
    Shop(bool isDungeonShop = false);   // true면 가격 1.5배
    ~Shop();
    void DisplayMenu(Player& player);
    void BuyItem(Player& player, int itemIndex);
    void SellItem(Player& player, int itemIndex);
private:
    int GetAdjustedPrice(Item* item);   // 던전상점 여부에 따라 가격 계산
};
```

#### Logger
```cpp
class Logger {
public:
    static void Log(string message);              // 공격/피해/아이템사용/골드획득 등 출력
    static void RecordKill(string monsterName);
    static void PrintKillSummary();                // 몬스터별 처치 수 출력
};
```

#### Game
```cpp
class Game {
public:
    ~Game();
    void Run();                    // main()에서 호출되는 유일한 진입점
private:
    void ShowStartMenu();
    void CreateCharacter();        // 이름 검증(5자 이하 영문) + Player 생성 + 프롤로그 출력
    void RunTutorialBattle();
    void ShowMainMenu();           // 1~5, 0 선택 루프
};
```

---

## 3. 실행 흐름 (호출 관계)

팀원이 각자 클래스를 나눠 구현해도 실제로 이어붙였을 때 문제가 안 생기도록, 누가 누구를 호출하는지 전체 흐름을 순서대로 정리했습니다.

```
main()
  -> Game::Run()
       -> ShowStartMenu()                        게임 시작 / 종료 선택
       -> CreateCharacter()                      Player 객체 생성
       -> RunTutorialBattle()
              -> CombatSystem::StartBattle(player, monster)
       -> ShowMainMenu()   [0 선택 전까지 반복]

              1. 던전입장
                   -> Dungeon dungeon(선택한 타입)
                   -> dungeon.EnterProgressionLoop(player)   [탈출 전까지 반복]
                          1.전진 -> TriggerRandomEvent(player)
                                 (몬스터 조우 시) GenerateMonster()
                                 -> CombatSystem::StartBattle(player, monster)
                          2.인벤토리 -> player.GetInventory().Display() / UseItem(idx, player)
                          3.던전상점 -> dungeon.CreateDungeonShop()
                                 -> Shop::DisplayMenu / BuyItem / SellItem
                          4.탈출 -> 메인 메뉴로 복귀

              2. 인벤토리 -> player.GetInventory().Display() / UseItem(idx, player)

              3. 장비 -> EquipmentManager::DisplayMenu(player) / SelectSlotItem(player, idx)

              4. 포션제작 -> PotionCrafting::DisplayMenu(player.GetInventory())
                             -> CraftFromRecipe(idx, player) 또는 CraftFromMaterials(idxs, player)

              5. 상점이용 -> Shop shop(false) -> DisplayMenu / BuyItem / SellItem

              0. 종료 -> 프로그램 종료
```

### 데이터 소유 규칙 (충돌 방지)
- **Player가 직접 소유**하는 데이터: Inventory(값 멤버), 착용 장비(`map<EquipmentSlot, EquipmentItem*>`)
- 그 외 클래스(CombatSystem, Dungeon, Shop, EquipmentManager, PotionCrafting, Logger)는 **상태를 갖지 않고** `Player&` / `Monster&`를 받아서 그 안의 값만 바꿉니다. 전투나 상점 관련 데이터를 여러 클래스가 각자 따로 들고 있다가 서로 어긋나는 일을 방지하기 위한 규칙입니다.

### 작업 순서 제안 (병렬 작업 충돌 최소화)
1. **Item.h / Player.h / Monster.h** — 나머지 모든 클래스가 참조하는 기반이라, 제일 먼저 선언부(인터페이스)만이라도 확정해서 팀에 공유
2. 위 3개 헤더만 있으면 **CombatSystem / Dungeon / Inventory / EquipmentManager / PotionCrafting / Shop / Logger는 병렬 작업 가능**
3. **Game / main.cpp**는 나머지 클래스 인터페이스가 어느 정도 정해진 뒤 제일 마지막에 연결

---

## 4. 아직 결정 안 된 것
- 직업 종류/효과
- 데미지 계산 공식 (방어력·크리티컬 반영 방식)
- 도망 성공 확률 공식
- 레벨업 시 마나/방어력/크리티컬/속도 증가치
- 장비 슬롯 종류/개수, 스탯 보너스 방식
- 몬스터 속도 기준값
