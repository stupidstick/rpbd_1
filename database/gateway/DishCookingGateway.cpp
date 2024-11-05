#include "DishCookingGateway.h"
#include <sstream>

DishCookingGateway::DishCookingGateway(OdbcTemplate *odbcTemplate) {
    this->odbcTemplate = odbcTemplate;
}

DishCooking DishCookingGateway::insert(long servingsCount, string cookingDate, long cookId, long dishId) {
    stringstream query;
    query << "INSERT INTO dish_cooking (servings_count, cooking_date, cook_id, dish_id) VALUES ("
          << servingsCount << ", '" << cookingDate << "', " << cookId << ", " << dishId
          << ") RETURNING id, servings_count, cooking_date, cook_id, dish_id;";

    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLINTEGER servingsCount$;
    SQLCHAR cookingDateBuffer[256];
    SQLINTEGER cookId$;
    SQLINTEGER dishId$;

    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_LONG, &servingsCount$, sizeof(servingsCount$), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, cookingDateBuffer, sizeof(cookingDateBuffer), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_LONG, &cookId$, sizeof(cookId$), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_LONG, &dishId$, sizeof(dishId$), nullptr);

    SQLFetch(hstmt);

    DishCooking dishCooking;
    dishCooking.set_id(id$);
    dishCooking.set_servings_count(servingsCount$);
    dishCooking.set_cooking_date(string((char *)cookingDateBuffer));
    dishCooking.set_cook_id(cookId$);
    dishCooking.set_dish_id(dishId$);

    return dishCooking;
}

optional<DishCooking> DishCookingGateway::findById(long id) {
    stringstream query;
    query << "SELECT id, servings_count, cooking_date, cook_id, dish_id FROM dish_cooking WHERE id = " << id << ";";

    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLINTEGER servingsCount$;
    SQLCHAR cookingDateBuffer[256];
    SQLINTEGER cookId$;
    SQLINTEGER dishId$;

    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_LONG, &servingsCount$, sizeof(servingsCount$), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, cookingDateBuffer, sizeof(cookingDateBuffer), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_LONG, &cookId$, sizeof(cookId$), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_LONG, &dishId$, sizeof(dishId$), nullptr);

    SQLRETURN result = SQLFetch(hstmt);
    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        DishCooking dishCooking;
        dishCooking.set_id(id$);
        dishCooking.set_servings_count(servingsCount$);
        dishCooking.set_cooking_date(string((char *)cookingDateBuffer));
        dishCooking.set_cook_id(cookId$);
        dishCooking.set_dish_id(dishId$);
        return dishCooking;
    }
    return nullopt;
}

vector<DishCooking> DishCookingGateway::findAll() {
    stringstream query;
    query << "SELECT id, servings_count, cooking_date, cook_id, dish_id FROM dish_cooking;";

    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    vector<DishCooking> dishCookings;

    SQLINTEGER id$;
    SQLINTEGER servingsCount$;
    SQLCHAR cookingDateBuffer[256];
    SQLINTEGER cookId$;
    SQLINTEGER dishId$;

    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_LONG, &servingsCount$, sizeof(servingsCount$), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, cookingDateBuffer, sizeof(cookingDateBuffer), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_LONG, &cookId$, sizeof(cookId$), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_LONG, &dishId$, sizeof(dishId$), nullptr);

    SQLRETURN result = SQLFetch(hstmt);
    while (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        DishCooking dishCooking;
        dishCooking.set_id(id$);
        dishCooking.set_servings_count(servingsCount$);
        dishCooking.set_cooking_date(string((char *)cookingDateBuffer));
        dishCooking.set_cook_id(cookId$);
        dishCooking.set_dish_id(dishId$);

        dishCookings.push_back(dishCooking);
        result = SQLFetch(hstmt);
    }
    return dishCookings;
}

void DishCookingGateway::remove(long id) {
    stringstream query;
    query << "DELETE FROM dish_cooking WHERE id = " << id;
    odbcTemplate->executeQuery(query.str());
}

DishCooking DishCookingGateway::update(long id, long servingsCount, string cookingDate, long cookId, long dishId) {
    stringstream query;
    query << "UPDATE dish_cooking SET servings_count = " << servingsCount << ", cooking_date = '"
          << cookingDate << "', cook_id = " << cookId << ", dish_id = " << dishId
          << " WHERE id = " << id
          << " RETURNING id, servings_count, cooking_date, cook_id, dish_id;";

    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLINTEGER servingsCount$;
    SQLCHAR cookingDateBuffer[256];
    SQLINTEGER cookId$;
    SQLINTEGER dishId$;

    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_LONG, &servingsCount$, sizeof(servingsCount$), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, cookingDateBuffer, sizeof(cookingDateBuffer), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_LONG, &cookId$, sizeof(cookId$), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_LONG, &dishId$, sizeof(dishId$), nullptr);

    SQLRETURN result = SQLFetch(hstmt);
    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        DishCooking dishCooking;
        dishCooking.set_id(id$);
        dishCooking.set_servings_count(servingsCount$);
        dishCooking.set_cooking_date(string((char *)cookingDateBuffer));
        dishCooking.set_cook_id(cookId$);
        dishCooking.set_dish_id(dishId$);
        return dishCooking;
    }
    throw std::invalid_argument("Invalid id");
}