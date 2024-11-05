#include <optional>
#include <vector>

#include "../OdbcTemplate.h"
#include "../entity/HealthCert.h"

#ifndef HEALTHCERTGATEWAY_H
#define HEALTHCERTGATEWAY_H


class HealthCertGateway {
public:
    HealthCertGateway(OdbcTemplate *odbcTemplate);

    HealthCert insert(string number, string receiptDate);

    optional<HealthCert> findById(long id);

    vector<HealthCert> findAll();

    void remove(long id);

    HealthCert update(long id, string number, string receiptDate);

private:
    OdbcTemplate *odbcTemplate;
};

#endif //HEALTHCERTGATEWAY_H
