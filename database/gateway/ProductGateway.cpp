//
// Created by stupi on 01.11.2024.
//

#include "ProductGateway.h"

#include <iostream>
#include <sstream>

ProductGateway::ProductGateway(OdbcTemplate *odbcTemplate) {
    this->odbcTemplate = odbcTemplate;
}

Product ProductGateway::insert(string name, long caloricContent, long weight, double price) {
    stringstream query;
    query << "INSERT INTO product (name, caloric_content, weight, price) VALUES ('" << name << "'," << caloricContent <<
            "," << weight << "," << price << ") RETURNING id, name, caloric_content, weight, price;";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id;
    SQLCHAR nameBuffer[256];
    SQLINTEGER caloricContent$;
    SQLINTEGER weight$;
    SQLDOUBLE price$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id, sizeof(id), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &caloricContent$, sizeof(id), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_LONG, &weight$, sizeof(id), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_DOUBLE, &price$, sizeof(id), nullptr);
    SQLFetch(hstmt);

    Product product = Product();
    product.set_id(id);
    product.set_name(string((char *) nameBuffer));
    product.set_caloric_content(caloricContent$);
    product.set_weight(weight$);
    product.set_price(price$);
    return product;
}

optional<Product> ProductGateway::findById(long id) {
    stringstream query;
    query << "SELECT id, name, caloric_content, weight, price FROM product WHERE id = " << id << ";";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLCHAR nameBuffer[256];
    SQLINTEGER caloricContent$;
    SQLINTEGER weight$;
    SQLDOUBLE price$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &caloricContent$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_LONG, &weight$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_DOUBLE, &price$, sizeof(id$), nullptr);
    SQLRETURN result = SQLFetch(hstmt);
    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        Product product = Product();
        product.set_id(id$);
        product.set_name(string((char *) nameBuffer));
        product.set_caloric_content(caloricContent$);
        product.set_weight(weight$);
        product.set_price(price$);
        return product;
    }
    return std::nullopt;
}

vector<Product> ProductGateway::findAll() {
    stringstream query;
    query << "SELECT id, name, caloric_content, weight, price FROM product;";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());
    std::vector<Product> products = std::vector<Product>();
    SQLINTEGER id;
    SQLCHAR nameBuffer[256];
    SQLINTEGER caloricContent$;
    SQLINTEGER weight$;
    SQLDOUBLE price$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id, sizeof(id), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &caloricContent$, sizeof(id), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_LONG, &weight$, sizeof(id), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_DOUBLE, &price$, sizeof(id), nullptr);
    SQLRETURN sqlreturn = SQLFetch(hstmt);
    while (sqlreturn == SQL_SUCCESS || sqlreturn == SQL_SUCCESS_WITH_INFO) {
        Product product = Product();
        product.set_id(id);
        product.set_name(string((char *) nameBuffer));
        product.set_caloric_content(caloricContent$);
        product.set_weight(weight$);
        product.set_price(price$);

        products.push_back(product);
        sqlreturn = SQLFetch(hstmt);
    }
    return products;
}

void ProductGateway::remove(long id) {
    stringstream query;
    query << "DELETE FROM product WHERE id = " << id << ";";
    odbcTemplate->executeQuery(query.str());
}

Product ProductGateway::update(long id, string name, long caloricContent, long weight, double price) {
    stringstream query;
    query << "UPDATE product SET name = '" << name << "', caloric_content = " << caloricContent << ", weight = " << weight
            << ", price = " << price << " WHERE id = " << id << " RETURNING id, name, caloric_content, weight, price;";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLCHAR nameBuffer[256];
    SQLINTEGER caloricContent$;
    SQLINTEGER weight$;
    SQLDOUBLE price$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &caloricContent$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_LONG, &weight$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_DOUBLE, &price$, sizeof(id$), nullptr);
    SQLRETURN result = SQLFetch(hstmt);
    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        Product product = Product();
        product.set_id(id$);
        product.set_name(string((char *) nameBuffer));
        product.set_caloric_content(caloricContent$);
        product.set_weight(weight$);
        product.set_price(price$);
        return product;
    }
    throw std::invalid_argument("Invalid id");
}
