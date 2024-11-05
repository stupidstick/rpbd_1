//
// Created by stupi on 01.11.2024.
//

#include <optional>
#include <vector>

#include "../OdbcTemplate.h"
#include "../entity/Product.h"

#ifndef PRODUCTGATEWAY_H
#define PRODUCTGATEWAY_H


class ProductGateway {
public:
    ProductGateway(OdbcTemplate *odbcTemplate);

    Product insert(string name, long caloricContent, long weight, double price);

    optional<Product> findById(long id);

    vector<Product> findAll();

    void remove(long id);

    Product update(long id, string name, long caloricContent, long weight, double price);

private:
    OdbcTemplate *odbcTemplate;
};


#endif //PRODUCTGATEWAY_H
