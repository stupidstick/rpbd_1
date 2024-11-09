//
// Created by stupi on 06.11.2024.
//

#include "DateStringValidator.h"
#include <iostream>
#include <string>

using namespace std;

bool DateStringValidator::validateDate(const std::string &date_str) {
    // Check the length of the date string
    if (date_str.length() != 10) {
        return false;
    }

    // Check the format of the date string
    if (date_str[4] != '-' || date_str[7] != '-') {
        return false;
    }

    // Extract the year, month, and day and store it in integers
    int year, month, day;
    try {
        year = std::stoi(date_str.substr(0, 4));
        month = std::stoi(date_str.substr(5, 2));
        day = std::stoi(date_str.substr(8, 2));
    } catch (std::invalid_argument &) {
        return false;
    }

    if (year < 1 || year > 9999) {
        return false;
    }

    if (month < 1 || month > 12) {
        return false;
    }

    if (day < 1 || day > 31) {
        return false;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            return false;
        }
    }

    if (month == 2) {
        if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
            if (day > 29) {
                return false;
            }
        } else {
            if (day > 28) {
                return false;
            }
        }
    }

    return true;
}
