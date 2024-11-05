//
// Created by stupi on 03.11.2024.
//

#ifndef HEALTHCERT_H
#define HEALTHCERT_H
#include <string>

using namespace std;

class HealthCert {
public:
    long get_id() const;

    void set_id(long id);

    string get_number() const;

    void set_number(const string &number);

    string get_receipt_date() const;

    void set_receipt_date(const string &receipt_date);

private:
    long id;
    string number;
    string receipt_date;
};


#endif //HEALTHCERT_H
