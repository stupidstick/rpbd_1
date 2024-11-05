//
// Created by stupi on 03.11.2024.
//

#include "HealthCert.h"

long HealthCert::get_id() const {
    return id;
}

void HealthCert::set_id(long id) {
    this->id = id;
}

string HealthCert::get_number() const {
    return number;
}

void HealthCert::set_number(const string &number) {
    this->number = number;
}

string HealthCert::get_receipt_date() const {
    return receipt_date;
}

void HealthCert::set_receipt_date(const string &receipt_date) {
    this->receipt_date = receipt_date;
}
