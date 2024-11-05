//
// Created by stupi on 01.11.2024.
//

#include <optional>
#include <vector>

#include "../OdbcTemplate.h"
#include "../entity/DishCooking.h"

class DishCookingGateway {
public:
    DishCookingGateway(OdbcTemplate *odbcTemplate);

    DishCooking insert(long servingsCount, string cookingDate, long cookId, long dishId);

    optional<DishCooking> findById(long id);

    vector<DishCooking> findAll();

    void remove(long id);

    DishCooking update(long id, long servingsCount, string cookingDate, long cookId, long dishId);

private:
    OdbcTemplate *odbcTemplate;
};
