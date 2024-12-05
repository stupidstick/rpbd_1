#include "OdbcTemplate.h"

#include <iostream>

string INIT_TABLES = R"(CREATE TABLE IF NOT EXISTS product
(
    id              SERIAL PRIMARY KEY,
    name            TEXT    NOT NULL,
    caloric_content INTEGER NOT NULL,
    weight          INTEGER NOT NULL,
    price           REAL    NOT NULL
);

CREATE TABLE IF NOT EXISTS dish_type
(
    id   SERIAL PRIMARY KEY,
    name TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS dish
(
    id        SERIAL PRIMARY KEY,
    name      TEXT                             NOT NULL,
    weight    INTEGER                          NOT NULL,
    image_url TEXT                             NOT NULL,
    dish_type_id INTEGER REFERENCES dish_type (id) NOT NULL
    );

CREATE TABLE IF NOT EXISTS dish_to_product
(
    id         SERIAL PRIMARY KEY,
    dish_id    INTEGER REFERENCES dish (id)    NOT NULL,
    product_id INTEGER REFERENCES product (id) NOT NULL,
    products_count INTEGER NOT NULL
    );

CREATE TABLE IF NOT EXISTS recipe
(
    id                 SERIAL PRIMARY KEY,
    cooking_time       INTEGER                     NOT NULL,
    cooking_technology TEXT                        NOT NULL,
    dish_id            INTEGER REFERENCES dish (id) NOT NULL
    );

CREATE TABLE IF NOT EXISTS passport
(
    id                     SERIAL PRIMARY KEY,
    first_name             TEXT NOT NULL,
    last_name              TEXT NOT NULL,
    middle_name            TEXT NOT NULL,
    series                 TEXT NOT NULL,
    number                 TEXT NOT NULL,
    department_code        TEXT NOT NULL,
    issuing_authority_name TEXT NOT NULL,
    date_of_issue          DATE NOT NULL
);

CREATE TABLE IF NOT EXISTS health_cert
(
    id           SERIAL PRIMARY KEY,
    number       TEXT NOT NULL,
    receipt_date DATE NOT NULL
);

CREATE TABLE IF NOT EXISTS cook
(
    id             SERIAL PRIMARY KEY,
    address        TEXT                               NOT NULL,
    passport_id    INTEGER REFERENCES passport (id)    NOT NULL,
    health_cert_id INTEGER REFERENCES health_cert (id) NOT NULL
    );

CREATE TABLE IF NOT EXISTS dish_cooking
(
    id             SERIAL PRIMARY KEY,
    servings_count INTEGER                     NOT NULL,
    cooking_date   DATE                        NOT NULL,
    cook_id        INTEGER REFERENCES cook (id) NOT NULL,
    dish_id        INTEGER REFERENCES dish (id) NOT NULL
    );
)";


void handleError(SQLRETURN ret, SQLHANDLE handle, SQLSMALLINT type) {
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        SQLCHAR sqlState[6], errorMsg[1024];
        SQLINTEGER nativeError;
        SQLSMALLINT msgLen;

        SQLGetDiagRec(type, handle, 1, sqlState, &nativeError, errorMsg, sizeof(errorMsg), &msgLen);
        std::cerr << "SQL Error: " << errorMsg << std::endl;
    }
}

OdbcTemplate::OdbcTemplate() {
    SQLCHAR connectionString[] =
            "DRIVER={PostgreSQL ODBC Driver(UNICODE)};SERVER=localhost;DATABASE=catering;UID=catering_application;PWD=catering_application;PORT=5433;";

    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlhenv);
    SQLSetEnvAttr(sqlhenv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, 0);

    SQLAllocHandle(SQL_HANDLE_DBC, sqlhenv, &sqlhdbc);

    const SQLRETURN connectionResult = SQLDriverConnect(sqlhdbc, nullptr, connectionString,
                                                        SQL_NTS, nullptr, 0, NULL,SQL_DRIVER_COMPLETE);

    handleError(connectionResult, sqlhdbc, SQL_HANDLE_DBC);

    if (connectionResult == SQL_SUCCESS || connectionResult == SQL_SUCCESS_WITH_INFO) {
        cout << "Connection to catering database successful" << endl;
    }

    executeQuery(INIT_TABLES);
}

OdbcTemplate::~OdbcTemplate() {
    cout << "Destructor" << endl;
    SQLDisconnect(sqlhdbc);
    SQLFreeHandle(SQL_HANDLE_STMT, sqlhstmt);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlhdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlhenv);
}

SQLHENV OdbcTemplate::get_sqlhenv() const {
    return sqlhenv;
}

SQLHDBC OdbcTemplate::get_sqlhdbc() const {
    return sqlhdbc;
}

SQLHSTMT OdbcTemplate::get_sqlhstmt() const {
    return sqlhstmt;
}

SQLHSTMT OdbcTemplate::executeQuery(const string &query) {
    SQLRETURN sqlreturn = SQLAllocHandle(SQL_HANDLE_STMT, sqlhdbc, &sqlhstmt);
    handleError(sqlreturn, sqlhstmt, SQL_HANDLE_STMT);
    sqlreturn = SQLExecDirect(sqlhstmt, (SQLCHAR *) query.c_str(), SQL_NTS);
    handleError(sqlreturn, sqlhstmt, SQL_HANDLE_STMT);
    return sqlhstmt;
}
