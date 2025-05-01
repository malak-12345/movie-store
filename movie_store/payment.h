#pragma once
#include <string>
#include "customer.h"


bool isDigit(std::string& str); // done

bool validateCCV(std::string& ccv); // done
bool isCreditCardRegistered(customer customers[], int customers_count, std::string& creditCard); // done
//Luhn algorithm
bool validateCreditCard(std::string& creditCard); // done

void addCreditCard(customer customers[], int customers_count, std::string& id); // done
bool pay(customer customers[], int customers_count, std::string& id);
