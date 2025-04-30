#pragma once
#include <string>
#include <vector>
#include <map>
#include "payment.h"

#define limit 8
#define customer_max 50

struct customer
{
    std::string name, phoneNumber, id;
    std::string currentlyRentedMovies[limit];
    std::vector<std::string> previouslyRentedMovies;
    std::map<std::string, int> rating;
    creditCard creditcard;
};


//-------------------------utilities-----------------------------
std::string generateId(); // done
std::string deleteSpaces(std::string& str); // done
bool checkPhoneNumber(std::string& phoneNumber); // done
bool checkPhoneNumberRegistered(customer customers[], int customers_count, std::string& phoneNumber); // done
bool checkId(customer customers[], int customers_count, std::string& id); // done
int getCustomersCount(customer customers[], int size_of_customers); // done
bool isCurrentlyRentedFull(customer customers[], int customerIndex); // done
//---------------------------------------------------------------

void listCustomers(customer customers[], int customers_count); // done
void addNewCustomer(customer customers[], int size_of_customers, int& customers_count); // done
