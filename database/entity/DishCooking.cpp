//
// Created by stupi on 04.11.2024.
//

#include "DishCooking.h"

long DishCooking::get_id() const {
    return id;
}

void DishCooking::set_id(long id) {
    this->id = id;
}

long DishCooking::get_servings_count() const {
    return servingsCount;
}

void DishCooking::set_servings_count(long servings_count) {
    servingsCount = servings_count;
}

std::string DishCooking::get_cooking_date() const {
    return cookingDate;
}

void DishCooking::set_cooking_date(const std::string &cooking_date) {
    cookingDate = cooking_date;
}

long DishCooking::get_cook_id() const {
    return cookId;
}

void DishCooking::set_cook_id(long cook_id) {
    cookId = cook_id;
}

long DishCooking::get_dish_id() const {
    return dishId;
}

void DishCooking::set_dish_id(long dish_id) {
    dishId = dish_id;
}
