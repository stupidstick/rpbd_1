#ifndef MENU_H
#define MENU_H
#include <functional>

#include "../database/gateway/CookGateway.h"
#include "../database/gateway/DishCookingGateway.h"
#include "../database/gateway/DishGateway.h"
#include "../database/gateway/DishToProductGateway.h"
#include "../database/gateway/DishTypeGateway.h"
#include "../database/gateway/HealthCertGateway.h"
#include "../database/gateway/PassportGateway.h"
#include "../database/gateway/ProductGateway.h"
#include "../database/gateway/RecipeGateway.h"

using namespace std;

class Menu {
public:
    Menu();
    ~Menu();
    void run();
private:
    OdbcTemplate* odbcTemplate;
    CookGateway* cookGateway;
    DishCookingGateway* dishCookingGateway;
    DishGateway* dishGateway;
    DishToProductGateway* dishToProductGateway;
    DishTypeGateway* dishTypeGateway;
    HealthCertGateway* healthCertGateway;
    PassportGateway* passportGateway;
    ProductGateway* productGateway;
    RecipeGateway* recipeGateway;

    int readAction();

    void runDishTypeMenu();

    void runDishMenu();

    void runRecipeMenu();

    void runProductsMenu();

    static void paginate(int size, const function<void(int)> &func);
};


#endif //MENU_H
