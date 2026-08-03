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
        { { "슬라임 부산물", "슬라임 부산물" }, "힐링 포션", 1 },
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
