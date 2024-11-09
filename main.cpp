#include <iostream>
#include <windows.h>
// #include <sql.h>
// #include <sqlext.h>
// #include "database/OdbcTemplate.h"
#include "database/gateway/DishTypeGateway.h"
// #include "database/gateway/ProductGateway.h"
// #include "database/gateway/RecipeGateway.h"
//
#include <chrono>
#include <iomanip>

#include "menu/Menu.h"
#include "utils/DateStringValidator.h"

int main() {
    system("chcp 1251");

    cout << DateStringValidator::validateDate("2021-02-29");

    Menu menu = Menu();
    menu.run();
}
