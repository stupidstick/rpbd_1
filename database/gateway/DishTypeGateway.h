//
// Created by stupi on 30.10.2024.
//

#ifndef DISHTYPEGATEWAY_H
#define DISHTYPEGATEWAY_H
#include <optional>
#include <vector>

#include "../OdbcTemplate.h"
#include "../entity/DishType.h"


class DishTypeGateway {
public:
    DishTypeGateway(OdbcTemplate *odbc_template);

    DishType insert(string name);

    optional<DishType> findById(long id);

    DishType update(long id, string name);

    void remove(long id);

    std::vector<DishType> findAll();

private:
    OdbcTemplate *odbcTemplate;
};


#endif //DISHTYPEGATEWAY_H
