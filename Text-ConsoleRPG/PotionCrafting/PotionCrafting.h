#pragma once

#include <string>
#include <vector>

// 레시피 1개.
// 같은 재료가 2개 필요하면 materials 목록에 2번 넣는다.
struct CraftRecipe {
    std::vector<std::string> materials;
    std::string resultName;
    int resultCount = 1;
};

// 재료 1종의 보유 정보
struct MaterialInfo {
    std::string name;
    int count = 0;
};

// 제작 1회 결과
struct CraftResult {
    bool success = false;

    std::string resultName;                   // success == true일 때만 유효
    int resultCount = 0;
    std::vector<std::string> usedMaterials;   // 실제로 소모한 재료
};

class PotionCrafting {
public:
    // 전체 레시피 목록
    static const std::vector<CraftRecipe>& RecipeList();

    // 지금 인벤토리로 만들 수 있는 레시피 번호 목록
    static std::vector<int> CraftableRecipes();

    // 인벤토리에 있는 재료(parts) 목록
    static std::vector<MaterialInfo> OwnedMaterials();

    // 레시피 먼저 선택하는 방식
    static CraftResult CraftByRecipe(int recipeIndex);

    // 재료 먼저 선택하는 방식.
    static CraftResult CraftByMaterials(const std::vector<std::string>& materials);

    // 입력 수신 전용 (검증/재입력은 game.cpp가 반복 호출로 처리)
    static int ReadIntInput();
};