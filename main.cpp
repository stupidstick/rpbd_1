#include <iostream>
#include <windows.h>
// #include <sql.h>
// #include <sqlext.h>
// #include "database/OdbcTemplate.h"
#include "database/gateway/DishTypeGateway.h"
// #include "database/gateway/ProductGateway.h"
// #include "database/gateway/RecipeGateway.h"
//
#include "menu/Menu.h"

int main() {
    system("chcp 1251");

    Menu menu = Menu();
    menu.run();
}
