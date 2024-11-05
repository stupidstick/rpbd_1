//
// Created by stupi on 03.11.2024.
//

#include "Passport.h"

long Passport::get_id() const {
    return id;
}

void Passport::set_id(long id) {
    this->id = id;
}

string Passport::get_first_name() const {
    return firstName;
}

void Passport::set_first_name(const string &first_name) {
    firstName = first_name;
}

string Passport::get_last_name() const {
    return lastName;
}

void Passport::set_last_name(const string &last_name) {
    lastName = last_name;
}

string Passport::get_middle_name() const {
    return middleName;
}

void Passport::set_middle_name(const string &middle_name) {
    middleName = middle_name;
}

string Passport::get_series() const {
    return series;
}

void Passport::set_series(const string &series) {
    this->series = series;
}

string Passport::get_number() const {
    return number;
}

void Passport::set_number(const string &number) {
    this->number = number;
}

string Passport::get_departmnet_code() const {
    return departmnet_code;
}

void Passport::set_departmnet_code(const string &departmnet_code) {
    this->departmnet_code = departmnet_code;
}

string Passport::get_issuer_authority_name() const {
    return issuer_authority_name;
}

void Passport::set_issuer_authority_name(const string &issuer_authority_name) {
    this->issuer_authority_name = issuer_authority_name;
}

string Passport::get_date_of_issue() const {
    return date_of_issue;
}

void Passport::set_date_of_issue(const string &date_of_issue) {
    this->date_of_issue = date_of_issue;
}
