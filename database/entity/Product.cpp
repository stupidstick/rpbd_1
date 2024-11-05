//
// Created by stupi on 30.10.2024.
//

#include "Product.h"

long Product::get_id() const {
    return id;
}

void Product::set_id(long id) {
    this->id = id;
}

std::string Product::get_name() const {
    return name;
}

void Product::set_name(const std::string &name) {
    this->name = name;
}

long Product::get_caloric_content() const {
    return caloricContent;
}

void Product::set_caloric_content(long caloric_content) {
    caloricContent = caloric_content;
}

long Product::get_weight() const {
    return weight;
}

void Product::set_weight(long weight) {
    this->weight = weight;
}

double Product::get_price() const {
    return price;
}

void Product::set_price(double price) {
    this->price = price;
}
