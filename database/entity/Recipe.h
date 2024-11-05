//
// Created by stupi on 30.10.2024.
//

#ifndef RECIPT_H
#define RECIPT_H
#include <string>


class Recipe {
public:
    long get_id() const;

    void set_id(long id);

    long get_cooking_time() const;

    void set_cooking_time(long cooking_time);

    std::string get_cooking_technology() const;

    void set_cooking_technology(const std::string &cooking_technology);

    long get_dish_id() const;

    void set_dish_id(long dish_id);

private:
    long id;
    long cookingTime;
    std::string cookingTechnology;
    long dishId;
};


#endif //RECIPT_H
