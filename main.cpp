#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include "database/OdbcTemplate.h"

int main() {
    system("chcp 1251");

    OdbcTemplate odbc = OdbcTemplate();

    odbc.executeQuery("SELECT * FROM abobus");



    return 0;
}
