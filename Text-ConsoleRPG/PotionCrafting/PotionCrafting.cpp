#include "PotionCrafting.h"
#include "Inventory.h"
#include "Itemdata.h"

#include <iostream>

namespace {
    std::vector<MaterialInfo> CountMaterials(const std::vector<std::string>& materials) {
        std::vector<MaterialInfo> counted;
        for (const auto& name : materials) {
            bool found = false;
            for (auto& entry : counted) {
                if (entry.name == name) {
                    entry.count++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                counted.push_back(MaterialInfo{ name, 1 });
            }
        }
        return counted;
    }
}

// ---- 레시피 데이터 ----

const std::vector<CraftRecipe>& PotionCrafting::RecipeList() {
    static const std::vector<CraftRecipe> recipes = {
        //   재료 1,       ,  재료 2.            결과 포션, 갯수

        // 포션
        { { "붉은 허브",       "슬라임 부산물" },    "힐링 포션",   1 },
        { { "푸른 허브",       "언데드 부산물" },    "마나 포션",   1 },

        // 무기
        { { "부러진 칼날",     "슬라임 부산물" },    "호미",        1 },
        { { "부러진 칼날",     "언데드 부산물" },    "짧은 검",     1 },
        { { "강철 조각",       "슬라임 부산물" },    "긴 검",       1 },
        { { "강철 조각",       "골렘의 핵" },        "양손검",      1 },
        { { "미스릴 조각",     "골렘의 핵" },        "미스릴 검",   1 },
        { { "미스릴 조각",     "크리처의 심장" },    "전설의 검",   1 },

        // 방어구
        { { "낡은 천 조각",    "슬라임 부산물" },    "얇은 갑옷",   1 },
        { { "가죽 조각",       "슬라임 부산물" },    "가죽 갑옷",   1 },
        { { "강철판",          "슬라임 부산물" },    "사슬 갑옷",   1 },
        { { "강철판",          "골렘의 핵" },        "판금 갑옷",   1 },
        { { "미스릴 조각",     "슬라임 부산물" },    "미스릴 갑옷", 1 },
        { { "미스릴 조각",     "크리처의 심장" },    "전설의 갑옷", 1 },

        { { "낡은 천 조각",    "언데드 부산물" },    "고철 반지",   1 },
        { { "가죽 조각",       "언데드 부산물" },    "순은 반지",   1 },
        { { "강철판",          "언데드 부산물" },    "도금 반지",   1 },
        { { "강철판",          "크리처의 심장" },    "순금 반지",   1 },
        { { "미스릴 조각",     "언데드 부산물" },    "미스릴 반지", 1 },
        { { "미스릴 조각",     "크리처의 심장" },    "전설의 반지", 1 },

        { { "낡은 천 조각",    "골렘의 핵" },        "얇은 방패",   1 },
        { { "가죽 조각",       "골렘의 핵" },        "나무 방패",   1 },
        { { "강철판",          "골렘의 핵" },        "가죽 방패",   1 },
        { { "강철 조각",       "골렘의 핵" },        "사슬 방패",   1 },
        { { "미스릴 조각",     "골렘의 핵" },        "판금 방패",   1 },
        { { "미스릴 조각",     "크리처의 심장" },    "전설의 방패", 1 },

        { { "낡은 천 조각",    "슬라임 부산물" },    "면 장갑",     1 },
        { { "가죽 조각",       "슬라임 부산물" },    "가죽 장갑",   1 },
        { { "가죽 조각",       "언데드 부산물" },    "사슬 장갑",   1 },
        { { "강철판",          "언데드 부산물" },    "판금 장갑",   1 },
        { { "미스릴 조각",     "언데드 부산물" },    "미스릴 장갑", 1 },
        { { "미스릴 조각",     "크리처의 심장" },    "전설의 장갑", 1 },

        { { "낡은 천 조각",    "언데드 부산물" },    "얇은 신발",   1 },
        { { "가죽 조각",       "슬라임 부산물" },    "가죽 신발",   1 },
        { { "강철 조각",       "언데드 부산물" },    "사슬 신발",   1 },
        { { "강철판",          "슬라임 부산물" },    "판금 신발",   1 },
        { { "미스릴 조각",     "슬라임 부산물" },    "미스릴 신발", 1 },
        { { "미스릴 조각",     "크리처의 심장" },    "전설의 신발", 1 },


    };
    return recipes;
}

// ---- 조회 ----

std::vector<int> PotionCrafting::CraftableRecipes() {
    std::vector<int> craftable;
    const auto& recipes = RecipeList();

    for (int i = 0; i < static_cast<int>(recipes.size()); ++i) {
        bool possible = true;
        for (const auto& need : CountMaterials(recipes[i].materials)) {
            if (!CheckItem(g_player_inventory, need.name, need.count)) {
                possible = false;
                break;
            }
        }
        if (possible) {
            craftable.push_back(i);
        }
    }
    return craftable;
}

std::vector<MaterialInfo> PotionCrafting::OwnedMaterials() {
    std::vector<MaterialInfo> owned;

    for (const auto& item : g_player_inventory.ViewInventory()) {
        if (FindItem(item.name_).category == "parts") {
            owned.push_back(MaterialInfo{ item.name_, item.count_ });
        }
    }
    return owned;
}

// ---- 입력 수신 전용 ----

int PotionCrafting::ReadIntInput() {
    int value = 0;
    std::cin >> value;
    return value;
}

// ---- 제작 ----

CraftResult PotionCrafting::CraftByRecipe(int recipeIndex) {
    CraftResult result;

    const auto& recipes = RecipeList();
    if (recipeIndex < 0 || recipeIndex >= static_cast<int>(recipes.size())) {
        return result;   // success = false
    }

    const CraftRecipe& recipe = recipes[recipeIndex];
    const auto needList = CountMaterials(recipe.materials);

    for (const auto& need : needList) {
        if (!CheckItem(g_player_inventory, need.name, need.count)) {
            return result;   // success = false
        }
    }

    for (const auto& need : needList) {
        RemoveItem(g_player_inventory, need.name, need.count);
    }
    AddItem(g_player_inventory, recipe.resultName, recipe.resultCount);

    result.success = true;
    result.resultName = recipe.resultName;
    result.resultCount = recipe.resultCount;
    result.usedMaterials = recipe.materials;
    return result;
}

CraftResult PotionCrafting::CraftByMaterials(const std::vector<std::string>& materials) {
    const auto selected = CountMaterials(materials);
    const auto& recipes = RecipeList();

    for (int i = 0; i < static_cast<int>(recipes.size()); ++i) {
        const auto need = CountMaterials(recipes[i].materials);

        if (selected.size() != need.size()) {
            continue;
        }

        bool match = true;
        for (const auto& pick : selected) {
            bool found = false;
            for (const auto& want : need) {
                if (pick.name == want.name && pick.count == want.count) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                match = false;
                break;
            }
        }

        if (match) {
            return CraftByRecipe(i);
        }
    }

    return CraftResult{};   // 일치하는 레시피 없음 -> success = false
}
