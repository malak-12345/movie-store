#pragma once
#include <string>
#include "customer.h"

struct movie; // forward declaration to fix movie is not found

bool isDigit(std::string& str); // done

bool validateCCV(std::string& ccv); // done
bool isCreditCardRegistered(customer customers[], int customers_count, std::string& creditCard); // done
//Luhn algorithm
bool validateCreditCard(std::string& creditCard); // done

void addCreditCard(customer customers[], int customers_count, std::string& id, bool isDateChanged); // done
void create_SC(customer cust[], int customers_count, std::string& id);
void set_SC_passwrd(customer cust[], int customers_count, std::string& id);
void charge_SC(customer cust[], int customers_count, std::string& id);
int generate_coins();
double amount2pay(movie& mov, bool isDateChanged, date::sys_days new_date);
bool pay(double& cashRegister, customer customers[], int customers_count, 
         std::string& id, movie& mov, bool isDateChanged, date::sys_days new_date);
//bool pay(customer customers[], int customers_count, std::string& id);
