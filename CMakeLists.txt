cmake_minimum_required(VERSION 3.29)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

find_package(ODBC REQUIRED)

add_executable(untitled main.cpp
        database/OdbcTemplate.cpp
        database/OdbcTemplate.h
        database/entity/DishType.cpp
        database/entity/DishType.h
        database/entity/Product.cpp
        database/entity/Product.h
        database/entity/Dish.cpp
        database/entity/Dish.h
        database/entity/Recipe.cpp
        database/entity/Recipe.h
        database/gateway/DishTypeGateway.cpp
        database/gateway/DishTypeGateway.h
        database/gateway/ProductGateway.cpp
        database/gateway/ProductGateway.h
        database/gateway/RecipeGateway.cpp
        database/gateway/RecipeGateway.h
        database/gateway/DishGateway.cpp
        database/gateway/DishGateway.h
        database/entity/DIshToProduct.cpp
        database/entity/DIshToProduct.h
        database/gateway/DishToProductGateway.cpp
        database/gateway/DishToProductGateway.h
        database/entity/Passport.cpp
        database/entity/Passport.h
        database/entity/HealthCert.cpp
        database/entity/HealthCert.h
        database/entity/Cook.cpp
        database/entity/Cook.h
        database/entity/DishCooking.cpp
        database/entity/DishCooking.h
        database/gateway/CookGateway.cpp
        database/gateway/CookGateway.h
        database/gateway/PassportGateway.cpp
        database/gateway/PassportGateway.h
        database/gateway/HealthCertGateway.cpp
        database/gateway/HealthCertGateway.h
        database/gateway/DishCookingGateway.cpp
        database/gateway/DishCookingGateway.h
        menu/Menu.cpp
        menu/Menu.h
        utils/DateStringValidator.cpp
        utils/DateStringValidator.h
)

target_link_libraries(untitled ${ODBC_LIBRARIES})