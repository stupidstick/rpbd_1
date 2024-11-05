//
// Created by stupi on 30.10.2024.
//

#include "DishTypeGateway.h"

#include <optional>
#include <ostream>
#include <sstream>

DishTypeGateway::DishTypeGateway(OdbcTemplate *odbcTemplate) {
    this->odbcTemplate = odbcTemplate;
}

DishType DishTypeGateway::insert(string name) {
    SQLHSTMT hstmt = odbcTemplate->executeQuery(
        (std::string) "INSERT INTO dish_type (name) VALUES ('" + name + "') RETURNING id, name;");
    SQLINTEGER id;
    SQLCHAR nameBuffer[256];
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id, sizeof(id), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), nullptr);
    SQLFetch(hstmt);
    DishType dishType = DishType();
    dishType.set_id(id);
    dishType.set_name(string((char *) nameBuffer));
    return dishType;
}

optional<DishType> DishTypeGateway::findById(long id) {
    stringstream query;
    query << "SELECT id, name FROM dish_type WHERE id = " << id << ";";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());
    SQLINTEGER id$;
    SQLCHAR nameBuffer[256];
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), nullptr);
    SQLRETURN sqlreturn = SQLFetch(hstmt);
    if (sqlreturn == SQL_SUCCESS || sqlreturn == SQL_SUCCESS_WITH_INFO) {
        DishType dishType = DishType();
        dishType.set_id(id$);
        dishType.set_name(string((char *) nameBuffer));
        return dishType;
    }
    return std::nullopt;
}

DishType DishTypeGateway::update(long id, string name) {
    stringstream query;
    query << "UPDATE dish_type SET name = '" << name << "' WHERE id = " << id << " RETURNING id, name;";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());
    SQLCHAR nameBuffer[256];
    SQLBindCol(hstmt, 2, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), nullptr);
    SQLRETURN sqlreturn = SQLFetch(hstmt);
    if (sqlreturn == SQL_SUCCESS || sqlreturn == SQL_SUCCESS_WITH_INFO) {
        DishType dishType = DishType();
        dishType.set_id(id);
        dishType.set_name(string((char *) nameBuffer));
        return dishType;
    }
    throw std::invalid_argument("Invalid id");
}

void DishTypeGateway::remove(long id) {
    stringstream query;
    query << "DELETE FROM dish_type WHERE id = " << id << ";";
    odbcTemplate->executeQuery(query.str());
}

std::vector<DishType> DishTypeGateway::findAll() {
    stringstream query;
    query << "SELECT id, name FROM dish_type;";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());
    std::vector<DishType> dishTypes = std::vector<DishType>();
    SQLINTEGER id;
    SQLCHAR nameBuffer[256];
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id, sizeof(id), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), nullptr);
    SQLRETURN sqlreturn = SQLFetch(hstmt);
    while (sqlreturn == SQL_SUCCESS || sqlreturn == SQL_SUCCESS_WITH_INFO) {
        DishType dishType = DishType();
        dishType.set_id(id);
        dishType.set_name(string((char *) nameBuffer));
        dishTypes.push_back(dishType);
        sqlreturn = SQLFetch(hstmt);
    }
    // SQLFreeStmt(hstmt, SQL_CLOSE);
    return dishTypes;
}
