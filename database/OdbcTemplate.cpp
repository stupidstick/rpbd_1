#include "OdbcTemplate.h"

#include <iostream>

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
            "DRIVER={PostgreSQL ODBC Driver(UNICODE)};SERVER=localhost;DATABASE=postgres;UID=postgres;PWD=admin;PORT=5432;";

    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlhenv);
    SQLSetEnvAttr(sqlhenv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, 0);

    SQLAllocHandle(SQL_HANDLE_DBC, sqlhenv, &sqlhdbc);

    const SQLRETURN connectionResult = SQLDriverConnect(sqlhdbc, nullptr, connectionString,
                                                        SQL_NTS, nullptr, 0, NULL,SQL_DRIVER_COMPLETE);

    handleError(connectionResult, sqlhdbc, SQL_HANDLE_DBC);

    if (connectionResult == SQL_SUCCESS || connectionResult == SQL_SUCCESS_WITH_INFO) {
        cout << "Connection to catering database successful" << endl;
    }
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
    // SQLFreeStmt(sqlhstmt, SQL_CLOSE);
    SQLRETURN sqlreturn = SQLAllocHandle(SQL_HANDLE_STMT, sqlhdbc, &sqlhstmt);
    handleError(sqlreturn, sqlhstmt, SQL_HANDLE_STMT);
    sqlreturn = SQLExecDirect(sqlhstmt, (SQLCHAR *) query.c_str(), SQL_NTS);
    handleError(sqlreturn, sqlhstmt, SQL_HANDLE_STMT);
    return sqlhstmt;
}
