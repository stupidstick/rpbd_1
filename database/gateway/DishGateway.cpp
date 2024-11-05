//
// Created by stupi on 03.11.2024.
//

#include "DishGateway.h"

#include <sstream>

DishGateway::DishGateway(OdbcTemplate *odbcTemplate) {
    this->odbcTemplate = odbcTemplate;
}

Dish DishGateway::insert(string name, long weight, string imageUrl, long dishTypeId) {
    stringstream query;
    query << "INSERT INTO dish (name, weight, image_url, dish_type_id) VALUES ('" << name << "'," << weight << ",'" <<
            imageUrl << "', " << dishTypeId << ") RETURNING id, name, weight, image_url, dish_type_id;";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLCHAR nameBuffer[256];
    SQLINTEGER weight$;
    SQLCHAR imageUrlBuffer[1024];
    SQLINTEGER dishTypeId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &weight$, sizeof(weight$), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_CHAR, imageUrlBuffer, sizeof(imageUrlBuffer), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_LONG, &dishTypeId$, sizeof(dishTypeId$), nullptr);
    SQLFetch(hstmt);

    Dish dish = Dish();
    dish.set_id(id$);
    dish.set_name(string((char *) nameBuffer));
    dish.set_weight(weight$);
    dish.set_url(string((char *) imageUrlBuffer));
    dish.set_dish_type_id(dishTypeId$);
    return dish;
}

optional<Dish> DishGateway::findById(long id) {
    stringstream query;
    query << "SELECT id, name, weight, image_url, dish_type_id FROM dish WHERE id = " << id << ";";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLCHAR nameBuffer[256];
    SQLINTEGER weight$;
    SQLCHAR imageUrlBuffer[1024];
    SQLINTEGER dishTypeId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &weight$, sizeof(weight$), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_CHAR, imageUrlBuffer, sizeof(imageUrlBuffer), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_LONG, &dishTypeId$, sizeof(dishTypeId$), nullptr);
    SQLRETURN result = SQLFetch(hstmt);
    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        Dish dish = Dish();
        dish.set_id(id$);
        dish.set_name(string((char *) nameBuffer));
        dish.set_weight(weight$);
        dish.set_url(string((char *) imageUrlBuffer));
        dish.set_dish_type_id(dishTypeId$);
        return dish;
    }
    return nullopt;
}

vector<Dish> DishGateway::findAll() {
    stringstream query;
    query << "SELECT id, name, weight, image_url, dish_type_id FROM dish;";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    vector<Dish> dishes = vector<Dish>();

    SQLINTEGER id$;
    SQLCHAR nameBuffer[256];
    SQLINTEGER weight$;
    SQLCHAR imageUrlBuffer[1024];
    SQLINTEGER dishTypeId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &weight$, sizeof(weight$), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_CHAR, imageUrlBuffer, sizeof(imageUrlBuffer), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_LONG, &dishTypeId$, sizeof(dishTypeId$), nullptr);
    SQLRETURN result = SQLFetch(hstmt);
    while (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        Dish dish = Dish();
        dish.set_id(id$);
        dish.set_name(string((char *) nameBuffer));
        dish.set_weight(weight$);
        dish.set_url(string((char *) imageUrlBuffer));
        dish.set_dish_type_id(dishTypeId$);

        dishes.push_back(dish);
        result = SQLFetch(hstmt);
    }
    return dishes;
}

void DishGateway::remove(long id) {
    stringstream query;
    query << "DELETE FROM dish WHERE id = " << id;
    odbcTemplate->executeQuery(query.str());
}

Dish DishGateway::update(long id, string name, long weight, string imageUrl, long dishTypeId) {
    stringstream query;
    query << "UPDATE dish SET name = '" << name << "', weight = " << weight << ", image_url = '" << imageUrl <<
            "', dish_type_id = " << dishTypeId << " WHERE id = " << id <<
            " RETURNING id, name, weight, image_url, dish_type_id;";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLCHAR nameBuffer[256];
    SQLINTEGER weight$;
    SQLCHAR imageUrlBuffer[1024];
    SQLINTEGER dishTypeId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &weight$, sizeof(weight$), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_CHAR, imageUrlBuffer, sizeof(imageUrlBuffer), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_LONG, &dishTypeId$, sizeof(dishTypeId$), nullptr);
    SQLRETURN result = SQLFetch(hstmt);
    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        Dish dish = Dish();
        dish.set_id(id$);
        dish.set_name(string((char *) nameBuffer));
        dish.set_weight(weight$);
        dish.set_url(string((char *) imageUrlBuffer));
        dish.set_dish_type_id(dishTypeId$);
        return dish;
    }
    throw std::invalid_argument("Invalid id");
}
