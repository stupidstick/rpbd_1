//
// Created by stupi on 03.11.2024.
//

#include "DishToProductGateway.h"

#include <sstream>

DishToProductGateway::DishToProductGateway(OdbcTemplate *odbcTemplate) {
    this->odbcTemplate = odbcTemplate;
}

DishToProduct DishToProductGateway::insert(long dishId, long productId) {
    stringstream query;
    query << "INSERT INTO dish_to_product (dish_id, product_id) VALUES (" << dishId << ", " << productId <<
            ") RETURNING id, dish_id, product_id;";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLINTEGER dishId$;
    SQLINTEGER productId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_LONG, &dishId$, sizeof(dishId$), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &productId$, sizeof(productId$), nullptr);
    SQLFetch(hstmt);

    DishToProduct dishToProduct = DishToProduct();
    dishToProduct.set_id(id$);
    dishToProduct.set_dish_id(dishId$);
    dishToProduct.set_product_id(productId$);
    return dishToProduct;
}

optional<DishToProduct> DishToProductGateway::findById(long id) {
    stringstream query;
    query << "SELECT id, dish_id, product_id FROM dish_to_product WHERE id = " << id << ";";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLINTEGER dishId$;
    SQLINTEGER productId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_LONG, &dishId$, sizeof(dishId$), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &productId$, sizeof(productId$), nullptr);

    SQLRETURN result = SQLFetch(hstmt);
    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        DishToProduct dishToProduct = DishToProduct();
        dishToProduct.set_id(id$);
        dishToProduct.set_dish_id(dishId$);
        dishToProduct.set_product_id(productId$);
        return dishToProduct;
    }
    return nullopt;
}

vector<DishToProduct> DishToProductGateway::findAll() {
    stringstream query;
    query << "SELECT id, dish_id, product_id FROM dish_to_product;";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    vector<DishToProduct> dish_to_product_list = vector<DishToProduct>();

    SQLINTEGER id$;
    SQLINTEGER dishId$;
    SQLINTEGER productId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_LONG, &dishId$, sizeof(dishId$), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &productId$, sizeof(productId$), nullptr);

    SQLRETURN result = SQLFetch(hstmt);
    while (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        DishToProduct dishToProduct = DishToProduct();
        dishToProduct.set_id(id$);
        dishToProduct.set_dish_id(dishId$);
        dishToProduct.set_product_id(productId$);

        dish_to_product_list.push_back(dishToProduct);
        result = SQLFetch(hstmt);
    }
    return dish_to_product_list;
}

void DishToProductGateway::remove(long id) {
    stringstream query;
    query << "DELETE FROM dish_to_product WHERE id = " << id << ";";
    odbcTemplate->executeQuery(query.str());
}

DishToProduct DishToProductGateway::update(long id, long dishId, long productId) {
    stringstream query;
    query << "UPDATE dish_to_product SET dish_id = " << dishId << ", product_id = " << productId << ";";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLINTEGER dishId$;
    SQLINTEGER productId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_LONG, &dishId$, sizeof(dishId$), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &productId$, sizeof(productId$), nullptr);

    SQLRETURN result = SQLFetch(hstmt);
    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        DishToProduct dishToProduct = DishToProduct();
        dishToProduct.set_id(id$);
        dishToProduct.set_dish_id(dishId$);
        dishToProduct.set_product_id(productId$);
        return dishToProduct;
    }
    throw std::invalid_argument("Invalid id");
}
