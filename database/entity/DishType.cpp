//
// Created by stupi on 30.10.2024.
//

#include "DishType.h"

long DishType::get_id() const {
    return id;
}

void DishType::set_id(long id) {
    this->id = id;
}

std::string DishType::get_name() const {
    return name;
}

void DishType::set_name(const std::string &name) {
    this->name = name;
}
