//
// Created by stupi on 03.11.2024.
//

#include <optional>
#include <vector>

#include "../OdbcTemplate.h"
#include "../entity/DishToProduct.h"

#ifndef DISHTOPRODUCTGATEWAY_H
#define DISHTOPRODUCTGATEWAY_H

class DishToProductGateway {
public:
    DishToProductGateway(OdbcTemplate *odbcTemplate);

    DishToProduct insert(long dishId, long productId, long productsCount);

    optional<DishToProduct> findById(long id);

    vector<DishToProduct> findAll();

    void remove(long id);

    DishToProduct update(long id, long dishId, long productId, long productsCount);

private:
    OdbcTemplate *odbcTemplate;
};

#endif //DISHTOPRODUCTGATEWAY_H