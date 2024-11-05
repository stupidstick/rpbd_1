//
// Created by stupi on 03.11.2024.
//

#include <optional>
#include <vector>

#include "../OdbcTemplate.h"
#include "../entity/Dish.h"

#ifndef DISHGATEWAY_H
#define DISHGATEWAY_H


class DishGateway {
public:
    DishGateway(OdbcTemplate *odbcTemplate);

    Dish insert(string name, long weight, string imageUrl, long dishTypeId);

    optional<Dish> findById(long id);

    vector<Dish> findAll();

    void remove(long id);

    Dish update(long id, string name, long weight, string imageUrl, long dishTypeId);

private:
    OdbcTemplate *odbcTemplate;
};


#endif //DISHGATEWAY_H
