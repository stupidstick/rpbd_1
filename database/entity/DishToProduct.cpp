//
// Created by stupi on 03.11.2024.
//

#include "DishToProduct.h"

void DishToProduct::set_id(long id) {
    this->id = id;
}

void DishToProduct::set_dish_id(const long dish_id) {
    dishId = dish_id;
}

void DishToProduct::set_product_id(const long product_id) {
    productId = product_id;
}

long DishToProduct::get_id() const {
    return id;
}

long DishToProduct::get_dish_id() const {
    return dishId;
}

long DishToProduct::get_product_id() const {
    return productId;
}

long DishToProduct::get_products_count() const {
    return productsCount;
}

void DishToProduct::set_products_count(const long products_count) {
    this->productsCount = products_count;
}
