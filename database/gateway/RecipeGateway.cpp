//
// Created by stupi on 03.11.2024.
//

#include "RecipeGateway.h"
#include <sstream>

RecipeGateway::RecipeGateway(OdbcTemplate *odbcTemplate) {
    this->odbcTemplate = odbcTemplate;
}

Recipe RecipeGateway::insert(long cookingTime, string cookingTechnology, long dishId) {
    stringstream query;
    query << "INSERT INTO recipe (cooking_time, cooking_technology, dish_id) VALUES(" << cookingTime << ",'" <<
            cookingTechnology << "'," << dishId << ") RETURNING id, cooking_time, cooking_technology, dish_id;";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLINTEGER cookingTime$;
    SQLCHAR cookingTechnologyBuffer[2000];
    SQLINTEGER dishId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_LONG, &cookingTime$, sizeof(cookingTime$), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, cookingTechnologyBuffer, sizeof(cookingTechnologyBuffer), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_LONG, &dishId$, sizeof(dishId$), nullptr);
    SQLFetch(hstmt);

    Recipe recipe = Recipe();
    recipe.set_id(id$);
    recipe.set_cooking_time(cookingTime$);
    recipe.set_cooking_technology(string((char *) cookingTechnologyBuffer));
    recipe.set_dish_id(dishId$);
    return recipe;
}

optional<Recipe> RecipeGateway::findById(long id) {
    stringstream query;
    query << "SELECT id, cooking_time, cooking_technology, dish_id FROM recipe WHERE id = " << id << ";";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLINTEGER cookingTime$;
    SQLCHAR cookingTechnologyBuffer[2000];
    SQLINTEGER dishId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_LONG, &cookingTime$, sizeof(cookingTime$), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, cookingTechnologyBuffer, sizeof(cookingTechnologyBuffer), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_LONG, &dishId$, sizeof(dishId$), nullptr);
    SQLRETURN result = SQLFetch(hstmt);
    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        Recipe recipe = Recipe();
        recipe.set_id(id$);
        recipe.set_cooking_time(cookingTime$);
        recipe.set_cooking_technology(string((char *) cookingTechnologyBuffer));
        recipe.set_dish_id(dishId$);
        return recipe;
    }
    return std::nullopt;
}

vector<Recipe> RecipeGateway::findAll() {
    stringstream query;
    query << "SELECT id, cooking_time, cooking_technology, dish_id FROM recipe;";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    vector<Recipe> recipes = vector<Recipe>();

    SQLINTEGER id$;
    SQLINTEGER cookingTime$;
    SQLCHAR cookingTechnologyBuffer[2000];
    SQLINTEGER dishId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_LONG, &cookingTime$, sizeof(cookingTime$), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, cookingTechnologyBuffer, sizeof(cookingTechnologyBuffer), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_LONG, &dishId$, sizeof(dishId$), nullptr);
    SQLRETURN result = SQLFetch(hstmt);
    while (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        Recipe recipe = Recipe();
        recipe.set_id(id$);
        recipe.set_cooking_time(cookingTime$);
        recipe.set_cooking_technology(string((char *) cookingTechnologyBuffer));
        recipe.set_dish_id(dishId$);

        recipes.push_back(recipe);
        result = SQLFetch(hstmt);
    }
    return recipes;
}

void RecipeGateway::remove(long id) {
    stringstream query;
    query << "DELETE FROM recipe WHERE id = " << id << ";";
    odbcTemplate->executeQuery(query.str());
}

Recipe RecipeGateway::update(long id, long cookingTime, string cookingTechnology, long dishId) {
    stringstream query;
    query << "UPDATE recipe SET cooking_time = " << cookingTime << ", cooking_technology = '" << cookingTechnology << "', dish_id = " << dishId << " RETURNING id, cooking_time, cooking_technology, dish_id;";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLINTEGER cookingTime$;
    SQLCHAR cookingTechnologyBuffer[2000];
    SQLINTEGER dishId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_LONG, &cookingTime$, sizeof(cookingTime$), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, cookingTechnologyBuffer, sizeof(cookingTechnologyBuffer), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_LONG, &dishId$, sizeof(dishId$), nullptr);
    SQLRETURN result = SQLFetch(hstmt);
    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        Recipe recipe = Recipe();
        recipe.set_id(id$);
        recipe.set_cooking_time(cookingTime$);
        recipe.set_cooking_technology(string((char *) cookingTechnologyBuffer));
        recipe.set_dish_id(dishId$);
        return recipe;
    }
    throw std::invalid_argument("Invalid id");
}
