//
// Created by stupi on 04.11.2024.
//

#include "CookGateway.h"

#include <sstream>

CookGateway::CookGateway(OdbcTemplate *odbcTemplate) {
    this->odbcTemplate = odbcTemplate;
}

Cook CookGateway::insert(string address, long passportId, long healthCertId) {
    stringstream query;
    query << "INSERT INTO cook (address, passport_id, health_cert_id) VALUES ('" << address << "','" << passportId <<
            "','" << healthCertId << "') RETURNING id, address, passport_id, health_cert_id;";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLCHAR addressBuffer[1024];
    SQLINTEGER passportId$;
    SQLINTEGER healthCertId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, addressBuffer, sizeof(addressBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &passportId$, sizeof(passportId$), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_CHAR, &healthCertId$, sizeof(healthCertId$), nullptr);
    SQLFetch(hstmt);

    Cook cook = Cook();
    cook.set_id(id$);
    cook.set_address(string((char *) addressBuffer));
    cook.set_passport_id(passportId$);
    cook.set_health_cert_id(healthCertId$);
    return cook;
}

optional<Cook> CookGateway::findById(long id) {
    stringstream query;
    query << "SELECT id, address, passport_id, health_cert_id FROM cook WHERE id =" << id << ";";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLCHAR addressBuffer[1024];
    SQLINTEGER passportId$;
    SQLINTEGER healthCertId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, addressBuffer, sizeof(addressBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &passportId$, sizeof(passportId$), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_CHAR, &healthCertId$, sizeof(healthCertId$), nullptr);
    SQLRETURN result = SQLFetch(hstmt);

    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        Cook cook = Cook();
        cook.set_id(id$);
        cook.set_address(string((char *) addressBuffer));
        cook.set_passport_id(passportId$);
        cook.set_health_cert_id(healthCertId$);
        return cook;
    }
    return nullopt;
}

vector<Cook> CookGateway::findAll() {
    stringstream query;
    query << "SELECT id, address, passport_id, health_cert_id FROM cook";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    vector<Cook> cooks = vector<Cook>();

    SQLINTEGER id$;
    SQLCHAR addressBuffer[1024];
    SQLINTEGER passportId$;
    SQLINTEGER healthCertId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, addressBuffer, sizeof(addressBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &passportId$, sizeof(passportId$), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_LONG, &healthCertId$, sizeof(healthCertId$), nullptr);

    SQLRETURN result = SQLFetch(hstmt);
    while (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        Cook cook = Cook();
        cook.set_id(id$);
        cook.set_address(string((char *) addressBuffer));
        cook.set_passport_id(passportId$);
        cook.set_health_cert_id(healthCertId$);

        cooks.push_back(cook);
        result = SQLFetch(hstmt);
    }
    return cooks;
}

void CookGateway::remove(long id) {
    stringstream query;
    query << "DELETE FROM cook WHERE id = " << id << ";";
    odbcTemplate->executeQuery(query.str());
}

Cook CookGateway::update(long id, string address, long passportId, long healthCertId) {
    stringstream query;
    query << "UPDATE cook SET address = '" << address << "', passport_id = " << passportId << ", health_cert_id = " <<
            healthCertId << " WHERE id = " << id << " RETURNING id, address, passport_id, health_cert_id;";
    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLCHAR addressBuffer[1024];
    SQLINTEGER passportId$;
    SQLINTEGER healthCertId$;
    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, addressBuffer, sizeof(addressBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_LONG, &passportId$, sizeof(passportId$), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_LONG, &healthCertId$, sizeof(healthCertId$), nullptr);
    SQLRETURN result = SQLFetch(hstmt);
    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        Cook cook = Cook();
        cook.set_id(id$);
        cook.set_address(string((char *) addressBuffer));
        cook.set_passport_id(passportId$);
        cook.set_health_cert_id(healthCertId$);
        return cook;
    }
    throw std::invalid_argument("Invalid id");
}
