#include "PassportGateway.h"
#include <sstream>

PassportGateway::PassportGateway(OdbcTemplate *odbcTemplate) {
    this->odbcTemplate = odbcTemplate;
}

Passport PassportGateway::insert(string firstName, string lastName, string middleName, string series, string number,
                                 string department_code, string issuer_authority_name, string date_of_issue) {
    stringstream query;
    query << "INSERT INTO passport (first_name, last_name, middle_name, series, number, department_code, "
            << "issuing_authority_name, date_of_issue) VALUES ('" << firstName << "', '" << lastName << "', '"
            << middleName << "', '" << series << "', '" << number << "', '" << department_code << "', '"
            << issuer_authority_name << "', '" << date_of_issue << "') RETURNING id, first_name, last_name, "
            << "middle_name, series, number, department_code, issuing_authority_name, date_of_issue;";

    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLCHAR firstNameBuffer[256];
    SQLCHAR lastNameBuffer[256];
    SQLCHAR middleNameBuffer[256];
    SQLCHAR seriesBuffer[256];
    SQLCHAR numberBuffer[256];
    SQLCHAR departmentCodeBuffer[256];
    SQLCHAR issuerAuthorityNameBuffer[256];
    SQLCHAR dateOfIssueBuffer[256];

    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, firstNameBuffer, sizeof(firstNameBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, lastNameBuffer, sizeof(lastNameBuffer), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_CHAR, middleNameBuffer, sizeof(middleNameBuffer), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_CHAR, seriesBuffer, sizeof(seriesBuffer), nullptr);
    SQLBindCol(hstmt, 6, SQL_C_CHAR, numberBuffer, sizeof(numberBuffer), nullptr);
    SQLBindCol(hstmt, 7, SQL_C_CHAR, departmentCodeBuffer, sizeof(departmentCodeBuffer), nullptr);
    SQLBindCol(hstmt, 8, SQL_C_CHAR, issuerAuthorityNameBuffer, sizeof(issuerAuthorityNameBuffer), nullptr);
    SQLBindCol(hstmt, 9, SQL_C_CHAR, dateOfIssueBuffer, sizeof(dateOfIssueBuffer), nullptr);

    SQLFetch(hstmt);

    Passport passport;
    passport.set_id(id$);
    passport.set_first_name(string((char *) firstNameBuffer));
    passport.set_last_name(string((char *) lastNameBuffer));
    passport.set_middle_name(string((char *) middleNameBuffer));
    passport.set_series(string((char *) seriesBuffer));
    passport.set_number(string((char *) numberBuffer));
    passport.set_departmnet_code(string((char *) departmentCodeBuffer));
    passport.set_issuer_authority_name(string((char *) issuerAuthorityNameBuffer));
    passport.set_date_of_issue(string((char *) dateOfIssueBuffer));

    return passport;
}

optional<Passport> PassportGateway::findById(long id) {
    stringstream query;
    query << "SELECT id, first_name, last_name, middle_name, series, number, department_code, "
            << "issuing_authority_name, date_of_issue FROM passport WHERE id = " << id << ";";

    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLCHAR firstNameBuffer[256];
    SQLCHAR lastNameBuffer[256];
    SQLCHAR middleNameBuffer[256];
    SQLCHAR seriesBuffer[256];
    SQLCHAR numberBuffer[256];
    SQLCHAR departmentCodeBuffer[256];
    SQLCHAR issuerAuthorityNameBuffer[256];
    SQLCHAR dateOfIssueBuffer[256];

    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, firstNameBuffer, sizeof(firstNameBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, lastNameBuffer, sizeof(lastNameBuffer), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_CHAR, middleNameBuffer, sizeof(middleNameBuffer), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_CHAR, seriesBuffer, sizeof(seriesBuffer), nullptr);
    SQLBindCol(hstmt, 6, SQL_C_CHAR, numberBuffer, sizeof(numberBuffer), nullptr);
    SQLBindCol(hstmt, 7, SQL_C_CHAR, departmentCodeBuffer, sizeof(departmentCodeBuffer), nullptr);
    SQLBindCol(hstmt, 8, SQL_C_CHAR, issuerAuthorityNameBuffer, sizeof(issuerAuthorityNameBuffer), nullptr);
    SQLBindCol(hstmt, 9, SQL_C_CHAR, dateOfIssueBuffer, sizeof(dateOfIssueBuffer), nullptr);

    SQLRETURN result = SQLFetch(hstmt);
    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        Passport passport;
        passport.set_id(id$);
        passport.set_first_name(string((char *) firstNameBuffer));
        passport.set_last_name(string((char *) lastNameBuffer));
        passport.set_middle_name(string((char *) middleNameBuffer));
        passport.set_series(string((char *) seriesBuffer));
        passport.set_number(string((char *) numberBuffer));
        passport.set_departmnet_code(string((char *) departmentCodeBuffer));
        passport.set_issuer_authority_name(string((char *) issuerAuthorityNameBuffer));
        passport.set_date_of_issue(string((char *) dateOfIssueBuffer));
        return passport;
    }
    return nullopt;
}

vector<Passport> PassportGateway::findAll() {
    stringstream query;
    query << "SELECT id, first_name, last_name, middle_name, series, number, department_code, "
            << "issuing_authority_name, date_of_issue FROM passport;";

    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    vector<Passport> passports;

    SQLINTEGER id$;
    SQLCHAR firstNameBuffer[256];
    SQLCHAR lastNameBuffer[256];
    SQLCHAR middleNameBuffer[256];
    SQLCHAR seriesBuffer[256];
    SQLCHAR numberBuffer[256];
    SQLCHAR departmentCodeBuffer[256];
    SQLCHAR issuerAuthorityNameBuffer[256];
    SQLCHAR dateOfIssueBuffer[256];

    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, firstNameBuffer, sizeof(firstNameBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, lastNameBuffer, sizeof(lastNameBuffer), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_CHAR, middleNameBuffer, sizeof(middleNameBuffer), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_CHAR, seriesBuffer, sizeof(seriesBuffer), nullptr);
    SQLBindCol(hstmt, 6, SQL_C_CHAR, numberBuffer, sizeof(numberBuffer), nullptr);
    SQLBindCol(hstmt, 7, SQL_C_CHAR, departmentCodeBuffer, sizeof(departmentCodeBuffer), nullptr);
    SQLBindCol(hstmt, 8, SQL_C_CHAR, issuerAuthorityNameBuffer, sizeof(issuerAuthorityNameBuffer), nullptr);
    SQLBindCol(hstmt, 9, SQL_C_CHAR, dateOfIssueBuffer, sizeof(dateOfIssueBuffer), nullptr);

    SQLRETURN result = SQLFetch(hstmt);
    while (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        Passport passport;
        passport.set_id(id$);
        passport.set_first_name(string((char *) firstNameBuffer));
        passport.set_last_name(string((char *) lastNameBuffer));
        passport.set_middle_name(string((char *) middleNameBuffer));
        passport.set_series(string((char *) seriesBuffer));
        passport.set_number(string((char *) numberBuffer));
        passport.set_departmnet_code(string((char *) departmentCodeBuffer));
        passport.set_issuer_authority_name(string((char *) issuerAuthorityNameBuffer));
        passport.set_date_of_issue(string((char *) dateOfIssueBuffer));

        passports.push_back(passport);
        result = SQLFetch(hstmt);
    }
    return passports;
}

void PassportGateway::remove(long id) {
    stringstream query;
    query << "DELETE FROM passport WHERE id = " << id;
    odbcTemplate->executeQuery(query.str());
}

Passport PassportGateway::update(long id, string firstName, string lastName, string middleName, string series,
                                 string number, string department_code, string issuer_authority_name,
                                 string date_of_issue) {
    stringstream query;
    query << "UPDATE passport SET first_name = '" << firstName << "', last_name = '" << lastName << "', "
            << "middle_name = '" << middleName << "', series = '" << series << "', number = '" << number << "', "
            << "department_code = '" << department_code << "', issuing_authority_name = '" << issuer_authority_name <<
            "', "
            << "date_of_issue = '" << date_of_issue << "' WHERE id = " << id
            << " RETURNING id, first_name, last_name, middle_name, series, number, department_code, "
            << "issuing_authority_name, date_of_issue;";

    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLCHAR firstNameBuffer[256];
    SQLCHAR lastNameBuffer[256];
    SQLCHAR middleNameBuffer[256];
    SQLCHAR seriesBuffer[256];
    SQLCHAR numberBuffer[256];
    SQLCHAR departmentCodeBuffer[256];
    SQLCHAR issuerAuthorityNameBuffer[256];
    SQLCHAR dateOfIssueBuffer[256];

    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, firstNameBuffer, sizeof(firstNameBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, lastNameBuffer, sizeof(lastNameBuffer), nullptr);
    SQLBindCol(hstmt, 4, SQL_C_CHAR, middleNameBuffer, sizeof(middleNameBuffer), nullptr);
    SQLBindCol(hstmt, 5, SQL_C_CHAR, seriesBuffer, sizeof(seriesBuffer), nullptr);
    SQLBindCol(hstmt, 6, SQL_C_CHAR, numberBuffer, sizeof(numberBuffer), nullptr);
    SQLBindCol(hstmt, 7, SQL_C_CHAR, departmentCodeBuffer, sizeof(departmentCodeBuffer), nullptr);
    SQLBindCol(hstmt, 8, SQL_C_CHAR, issuerAuthorityNameBuffer, sizeof(issuerAuthorityNameBuffer), nullptr);
    SQLBindCol(hstmt, 9, SQL_C_CHAR, dateOfIssueBuffer, sizeof(dateOfIssueBuffer), nullptr);

    SQLRETURN result = SQLFetch(hstmt);
    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        Passport passport;
        passport.set_id(id$);
        passport.set_first_name(string((char *) firstNameBuffer));
        passport.set_last_name(string((char *) lastNameBuffer));
        passport.set_middle_name(string((char *) middleNameBuffer));
        passport.set_series(string((char *) seriesBuffer));
        passport.set_number(string((char *) numberBuffer));
        passport.set_departmnet_code(string((char *) departmentCodeBuffer));
        passport.set_issuer_authority_name(string((char *) issuerAuthorityNameBuffer));
        passport.set_date_of_issue(string((char *) dateOfIssueBuffer));
        return passport;
    }
    throw std::invalid_argument("Invalid passport id");
}
