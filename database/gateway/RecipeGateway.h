//
// Created by stupi on 03.11.2024.
//
#include <optional>
#include <vector>

#include "..//entity/Recipe.h"
#include "../OdbcTemplate.h"

#ifndef RECIPEGATEWAY_H
#define RECIPEGATEWAY_H

using namespace std;

class RecipeGateway {
public:
    RecipeGateway(OdbcTemplate *odbcTemplate);

    Recipe insert(long cookingTime, string cookingTechnology, long dishId);

    optional<Recipe> findById(long id);

    vector<Recipe> findAll();

    void remove(long id);

    Recipe update(long id, long cookingTime, string cookingTechnology, long dishId);

private:
    OdbcTemplate *odbcTemplate;
};


#endif //RECIPEGATEWAY_H
