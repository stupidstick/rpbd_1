//
// Created by stupi on 04.11.2024.
//

#ifndef DISHCOOKIG_H
#define DISHCOOKIG_H
#include <string>


class DishCooking {
public:
    long get_id() const;

    void set_id(long id);

    long get_servings_count() const;

    void set_servings_count(long servings_count);

    std::string get_cooking_date() const;

    void set_cooking_date(const std::string &cooking_date);

    long get_cook_id() const;

    void set_cook_id(long cook_id);

    long get_dish_id() const;

    void set_dish_id(long dish_id);

private:
    long id;
    long servingsCount;
    std::string cookingDate;
    long cookId;
    long dishId;
};


#endif //DISHCOOKIG_H
