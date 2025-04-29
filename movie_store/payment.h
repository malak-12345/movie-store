#pragma once
#include <string>

struct creditCard {
    std::string creditCard, ccv, date;
};

std::string deleteSpaces(std::string& str);

//Luhn algorithm
bool validateCreditCard(std::string creditCard);