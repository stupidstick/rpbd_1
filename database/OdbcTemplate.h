#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string>

using namespace std;

#ifndef ODBCTEMPLATE_H
#define ODBCTEMPLATE_H

class OdbcTemplate {
public:
    OdbcTemplate();

    SQLHSTMT executeQuery(const string &);

    ~OdbcTemplate();

private:
    SQLHENV sqlhenv = nullptr;
    SQLHDBC sqlhdbc = nullptr;
    SQLHSTMT sqlhstmt = nullptr;
};


#endif
