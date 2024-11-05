//
// Created by stupi on 30.10.2024.
//

#ifndef DISH_H
#define DISH_H
#include <string>


class Dish {
public:
    long get_id() const;

    void set_id(long id);

    std::string get_name() const;

    void set_name(const std::string &name);

    long get_weight() const;

    void set_weight(long weight);

    std::string get_url() const;

    void set_url(const std::string &url);

    long get_dish_type_id() const;

    void set_dish_type_id(long dish_type_id);

private:
    long id;
    std::string name;
    long weight;
    std::string imageUrl;
    long dishTypeId;
};



#endif //DISH_H
