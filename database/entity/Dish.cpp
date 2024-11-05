//
// Created by stupi on 30.10.2024.
//

#include "Dish.h"

long Dish::get_id() const {
    return id;
}

void Dish::set_id(long id) {
    this->id = id;
}

std::string Dish::get_name() const {
    return name;
}

void Dish::set_name(const std::string &name) {
    this->name = name;
}

long Dish::get_weight() const {
    return weight;
}

void Dish::set_weight(long weight) {
    this->weight = weight;
}

std::string Dish::get_url() const {
    return imageUrl;
}

void Dish::set_url(const std::string &url) {
    this->imageUrl = url;
}

long Dish::get_dish_type_id() const {
    return dishTypeId;
}

void Dish::set_dish_type_id(long dish_type_id) {
    dishTypeId = dish_type_id;
}
