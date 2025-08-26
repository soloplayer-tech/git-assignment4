#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Recipe {
    string potionName;
    vector<string> ingredients;
    int stock;
};

class RecipeManager {
private:
    vector<Recipe> recipes;

public:
    void addRecipe(const string& name, const vector<string>& ingredients) {
        recipes.push_back({ name, ingredients, 3 });
    }

    Recipe* findByName(const string& name) {
        for (auto& r : recipes) {
            if (r.potionName == name) return &r;
        }
        return nullptr;
    }

    void searchByIngredient(const string& ingredient) {
        bool found = false;
        cout << "[검색 결과 - 재료: " << ingredient << "]\n";
        for (auto& r : recipes) {
            for (auto& ing : r.ingredients) {
                if (ing == ingredient) {
                    cout << "물약: " << r.potionName
                        << " (재고: " << r.stock << ")\n";
                    found = true;
                    break;
                }
            }
        }
        if (!found) cout << "해당 재료를 포함하는 레시피가 없습니다.\n";
    }

    void showAll() {
        cout << "\n[현재 등록된 레시피]\n";
        for (auto& r : recipes) {
            cout << "물약: " << r.potionName << " / 재고: " << r.stock << " / 재료: ";
            for (auto& ing : r.ingredients) cout << ing << " ";
            cout << "\n";
        }
    }
};

class StockManager {
private:
    static const int MAX_STOCK = 3;
    RecipeManager& recipeManager;

public:
    StockManager(RecipeManager& rm) : recipeManager(rm) {}

    void checkStock(const string& name) {
        Recipe* r = recipeManager.findByName(name);
        if (r) {
            cout << r->potionName << " 현재 재고: " << r->stock << "\n";
        }
        else {
            cout << "❌ 해당 이름의 물약이 없습니다.\n";
        }
    }

    void givePotion(const string& name) {
        Recipe* r = recipeManager.findByName(name);
        if (!r) {
            cout << "❌ 해당 이름의 물약이 없습니다.\n";
            return;
        }
        if (r->stock > 0) {
            r->stock--;
            cout << "✅ " << r->potionName << " 지급 완료! 남은 재고: " << r->stock << "\n";
        }
        else {
            cout << "❌ " << r->potionName << " 재고가 부족합니다!\n";
        }
    }

    void returnPotion(const string& name) {
        Recipe* r = recipeManager.findByName(name);
        if (!r) {
            cout << "❌ 해당 이름의 물약이 없습니다.\n";
            return;
        }
        if (r->stock < MAX_STOCK) {
            r->stock++;
            cout << "🔄 " << r->potionName << " 공병 반환 완료! 현재 재고: " << r->stock << "\n";
        }
        else {
            cout << "⚠️ " << r->potionName << " 재고가 이미 최대치(" << MAX_STOCK << ")입니다.\n";
        }
    }
};

int main() {
    RecipeManager recipeManager;
    StockManager stockManager(recipeManager);

    // 초기 레시피 등록
    recipeManager.addRecipe("치유 물약", { "허브", "맑은물" });
    recipeManager.addRecipe("마나 물약", { "마법의가루", "맑은물" });
    recipeManager.addRecipe("힘의 물약", { "괴력버섯", "허브" });

    int choice;
    string name, ingredient;

    while (true) {
        cout << "\n===== 연금술 공방 관리 시스템 =====\n";
        cout << "1. 전체 레시피 보기\n";
        cout << "2. 물약 이름으로 검색\n";
        cout << "3. 재료로 검색\n";
        cout << "4. 재고 확인\n";
        cout << "5. 물약 지급\n";
        cout << "6. 물약 반환\n";
        cout << "0. 종료\n";
        cout << "선택 >> ";
        cin >> choice;

        if (choice == 0) {
            cout << "프로그램을 종료합니다.\n";
            break;
        }

        switch (choice) {
        case 1:
            recipeManager.showAll();
            break;
        case 2:
            cout << "검색할 물약 이름 입력: ";
            cin >> name;
            if (Recipe* r = recipeManager.findByName(name)) {
                cout << "물약: " << r->potionName << " / 재고: " << r->stock << "\n재료: ";
                for (auto& ing : r->ingredients) cout << ing << " ";
                cout << "\n";
            }
            else {
                cout << "❌ 해당 이름의 물약이 없습니다.\n";
            }
            break;
        case 3:
            cout << "검색할 재료 입력: ";
            cin >> ingredient;
            recipeManager.searchByIngredient(ingredient);
            break;
        case 4:
            cout << "재고 확인할 물약 이름 입력: ";
            cin >> name;
            stockManager.checkStock(name);
            break;
        case 5:
            cout << "지급할 물약 이름 입력: ";
            cin >> name;
            stockManager.givePotion(name);
            break;
        case 6:
            cout << "반환할 물약 이름 입력: ";
            cin >> name;
            stockManager.returnPotion(name);
            break;
        default:
            cout << "❌ 잘못된 선택입니다. 다시 입력하세요.\n";
            break;
        }
    }

    return 0;
}
