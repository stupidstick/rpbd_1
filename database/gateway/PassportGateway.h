//
// Created by stupi on 04.11.2024.
//

#include <optional>
#include <vector>

#include "../OdbcTemplate.h"
#include "../entity/Passport.h"

#ifndef PASSPORTGATEWAY_H
#define PASSPORTGATEWAY_H

class PassportGateway {
public:
    PassportGateway(OdbcTemplate *odbcTemplate);

    Passport insert(string firstName, string lastName, string middleName, string series, string number,
                    string department_code, string issuer_authority_name, string date_of_issue);

    optional<Passport> findById(long id);

    vector<Passport> findAll();

    void remove(long id);

    Passport update(long id, string firstName, string lastName, string middleName, string series, string number,
                    string department_code, string issuer_authority_name, string date_of_issue);

private:
    OdbcTemplate *odbcTemplate;
};

#endif //PASSPORTGATEWAY_H
