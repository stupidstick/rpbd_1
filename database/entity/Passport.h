//
// Created by stupi on 03.11.2024.
//

#ifndef PASSPORT_H
#define PASSPORT_H
#include <string>

using namespace std;

class Passport {
public:
    long get_id() const;

    void set_id(long id);

    string get_first_name() const;

    void set_first_name(const string &first_name);

    string get_last_name() const;

    void set_last_name(const string &last_name);

    string get_middle_name() const;

    void set_middle_name(const string &middle_name);

    string get_series() const;

    void set_series(const string &series);

    string get_number() const;

    void set_number(const string &number);

    string get_departmnet_code() const;

    void set_departmnet_code(const string &departmnet_code);

    string get_issuer_authority_name() const;

    void set_issuer_authority_name(const string &issuer_authority_name);

    string get_date_of_issue() const;

    void set_date_of_issue(const string &date_of_issue);

private:
    long id;
    string firstName;
    string lastName;
    string middleName;
    string series;
    string number;
    string departmnet_code;
    string issuer_authority_name;
    string date_of_issue;
};


#endif //PASSPORT_H
