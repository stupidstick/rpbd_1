//
// Created by stupi on 04.11.2024.
//

#include <optional>
#include <vector>

#include "../OdbcTemplate.h"
#include "../entity/Cook.h"

#ifndef COOKGATEWAY_H
#define COOKGATEWAY_H

using namespace std;

class CookGateway {
public:
    CookGateway(OdbcTemplate *odbcTemplate);

    Cook insert(string address, long passportId, long healthCertId);

    optional<Cook> findById(long id);

    vector<Cook> findAll();

    void remove(long id);

    Cook update(long id, string address, long passportId, long healthCertId);

private:
    OdbcTemplate *odbcTemplate;
};


#endif //COOKGATEWAY_H
