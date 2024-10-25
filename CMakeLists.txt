cmake_minimum_required(VERSION 3.29)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

find_package(ODBC REQUIRED)

add_executable(untitled main.cpp
        database/OdbcTemplate.cpp
        database/OdbcTemplate.h
        database/gateway/DishTypeGateway.cpp
        database/gateway/DishTypeGateway.h
        database/entity/DishType.cpp
)

target_link_libraries(untitled ${ODBC_LIBRARIES})