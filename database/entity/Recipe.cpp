//
// Created by stupi on 30.10.2024.
//

#include "Recipe.h"

long Recipe::get_id() const {
    return id;
}

void Recipe::set_id(long id) {
    this->id = id;
}

long Recipe::get_cooking_time() const {
    return cookingTime;
}

void Recipe::set_cooking_time(long cooking_time) {
    cookingTime = cooking_time;
}

std::string Recipe::get_cooking_technology() const {
    return cookingTechnology;
}

void Recipe::set_cooking_technology(const std::string &cooking_technology) {
    cookingTechnology = cooking_technology;
}

long Recipe::get_dish_id() const {
    return dishId;
}

void Recipe::set_dish_id(long dish_id) {
    dishId = dish_id;
}
