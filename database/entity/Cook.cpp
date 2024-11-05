//
// Created by stupi on 03.11.2024.
//

#include "Cook.h"

long Cook::get_id() const {
    return id;
}

void Cook::set_id(long id) {
    this->id = id;
}

string Cook::get_address() const {
    return address;
}

void Cook::set_address(const string &address) {
    this->address = address;
}

long Cook::get_passport_id() const {
    return passportId;
}

void Cook::set_passport_id(long passport_id) {
    passportId = passport_id;
}

long Cook::get_health_cert_id() const {
    return healthCertId;
}

void Cook::set_health_cert_id(long health_cert_id) {
    healthCertId = health_cert_id;
}
