//
// Created by stupi on 03.11.2024.
//

#ifndef COOK_H
#define COOK_H
#include <string>

using namespace std;

class Cook {
public:
    long get_id() const;

    void set_id(long id);

    string get_address() const;

    void set_address(const string &address);

    long get_passport_id() const;

    void set_passport_id(long passport_id);

    long get_health_cert_id() const;

    void set_health_cert_id(long health_cert_id);

private:
    long id;
    string address;
    long passportId;
    long healthCertId;
};



#endif //COOK_H
