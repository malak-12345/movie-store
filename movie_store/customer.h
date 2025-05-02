#pragma once
#include <string>
#include <vector>
#include <map>
#include "Howard_Hinnant/include/date/date.h"

#define limit 8
#define customer_max 50

struct creditCard {
    std::string cardNumber, ccv;
    date::year_month_day yy_mm = date::year(3000) / date::month(10) / date::day(1);
};

struct customer
{
    std::string name = "none", phoneNumber = "none", id = "none";
    std::string currentlyRentedMovies[limit] = { "none", "none", "none", "none", "none", "none", "none", "none"};
    std::vector<std::string> previouslyRentedMovies;
    std::map<std::string, int> rating;
    creditCard creditcard;
    double coins = 0, SC_balance = 0;
    bool SC = false;
    std::string SC_passwrd = "password";
};


//-------------------------utilities-----------------------------
std::string generateId(); // done
std::string deleteSpaces(std::string& str); // done
bool checkPhoneNumber(std::string& phoneNumber); // done
bool checkPhoneNumberRegistered(customer customers[], int customers_count, std::string& phoneNumber); // done
bool checkId(customer customers[], int customers_count, std::string& id); // done
int getCustomersCount(customer customers[], int size_of_customers); // done
bool isCurrentlyRentedEmpty(customer customers[], int customerIndex); // done
//---------------------------------------------------------------

void listCustomers(customer customers[], int customers_count); // done
void displayCustomer(customer customers[], int customers_count, int customerIndex); // done
void addNewCustomer(customer customers[], int size_of_customers, int& customers_count); // done
