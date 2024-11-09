#include "HealthCertGateway.h"
#include <sstream>

HealthCertGateway::HealthCertGateway(OdbcTemplate *odbcTemplate) {
    this->odbcTemplate = odbcTemplate;
}

HealthCert HealthCertGateway::insert(string number, string receiptDate) {
    stringstream query;
    query << "INSERT INTO health_cert (number, receipt_date) VALUES ('" << number << "', '" 
          << receiptDate << "') RETURNING id, number, receipt_date;";

    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLCHAR numberBuffer[256];
    SQLCHAR receiptDateBuffer[256];

    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, numberBuffer, sizeof(numberBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, receiptDateBuffer, sizeof(receiptDateBuffer), nullptr);

    SQLFetch(hstmt);

    HealthCert healthCert;
    healthCert.set_id(id$);
    healthCert.set_number(string((char *)numberBuffer));
    healthCert.set_receipt_date(string((char *)receiptDateBuffer));

    return healthCert;
}

optional<HealthCert> HealthCertGateway::findById(long id) {
    stringstream query;
    query << "SELECT id, number, receipt_date FROM health_cert WHERE id = " << id << ";";

    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLCHAR numberBuffer[256];
    SQLCHAR receiptDateBuffer[256];

    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, numberBuffer, sizeof(numberBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, receiptDateBuffer, sizeof(receiptDateBuffer), nullptr);

    SQLRETURN result = SQLFetch(hstmt);
    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        HealthCert healthCert;
        healthCert.set_id(id$);
        healthCert.set_number(string((char *)numberBuffer));
        healthCert.set_receipt_date(string((char *)receiptDateBuffer));
        return healthCert;
    }
    return nullopt;
}

vector<HealthCert> HealthCertGateway::findAll() {
    stringstream query;
    query << "SELECT id, number, receipt_date FROM health_cert;";

    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    vector<HealthCert> healthCerts;

    SQLINTEGER id$;
    SQLCHAR numberBuffer[256];
    SQLCHAR receiptDateBuffer[256];

    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, numberBuffer, sizeof(numberBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, receiptDateBuffer, sizeof(receiptDateBuffer), nullptr);

    SQLRETURN result = SQLFetch(hstmt);
    while (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        HealthCert healthCert;
        healthCert.set_id(id$);
        healthCert.set_number(string((char *)numberBuffer));
        healthCert.set_receipt_date(string((char *)receiptDateBuffer));

        healthCerts.push_back(healthCert);
        result = SQLFetch(hstmt);
    }
    return healthCerts;
}

void HealthCertGateway::remove(long id) {
    stringstream query;
    query << "DELETE FROM health_cert WHERE id = " << id;
    odbcTemplate->executeQuery(query.str());
}

HealthCert HealthCertGateway::update(long id, string number, string receiptDate) {
    stringstream query;
    query << "UPDATE health_cert SET number = '" << number << "', receipt_date = '" << receiptDate 
          << "' WHERE id = " << id 
          << " RETURNING id, number, receipt_date;";

    SQLHSTMT hstmt = odbcTemplate->executeQuery(query.str());

    SQLINTEGER id$;
    SQLCHAR numberBuffer[256];
    SQLCHAR receiptDateBuffer[256];

    SQLBindCol(hstmt, 1, SQL_C_LONG, &id$, sizeof(id$), nullptr);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, numberBuffer, sizeof(numberBuffer), nullptr);
    SQLBindCol(hstmt, 3, SQL_C_CHAR, receiptDateBuffer, sizeof(receiptDateBuffer), nullptr);

    SQLRETURN result = SQLFetch(hstmt);
    if (result == SQL_SUCCESS || result == SQL_SUCCESS_WITH_INFO) {
        HealthCert healthCert;
        healthCert.set_id(id$);
        healthCert.set_number(string((char *)numberBuffer));
        healthCert.set_receipt_date(string((char *)receiptDateBuffer));
        return healthCert;
    }
    throw std::invalid_argument("Invalid health cert id");
}