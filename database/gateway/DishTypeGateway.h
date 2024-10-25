#ifndef DISHTYPEGATEWAY_H
#define DISHTYPEGATEWAY_H
#include "../OdbcTemplate.h"
#include "DishType"

class DishTypeGateway {
public:
    DishTypeGateway(OdbcTemplate);

    ~DishTypeGateway();

    DishType insertDishType(string dishType);

    void findAllDishTypes();
};


#endif //DISHTYPEGATEWAY_H
