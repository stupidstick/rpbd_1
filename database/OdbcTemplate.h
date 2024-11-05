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

    SQLHENV get_sqlhenv() const;

    SQLHDBC get_sqlhdbc() const;

    SQLHSTMT get_sqlhstmt() const;

private:
    SQLHENV sqlhenv = nullptr;
    SQLHDBC sqlhdbc = nullptr;
    SQLHSTMT sqlhstmt = nullptr;
};


#endif
