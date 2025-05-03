#pragma once
#include <string>
#include <vector>
#include <map>
#include "Howard_Hinnant/include/date/date.h"

#define limit 8
#define customers_max 100

struct creditCard {
    std::string cardNumber, ccv;
    date::year_month yy_mm = date::year(3000) / 10;
};

struct customer
{
    std::string name, phoneNumber, id;
    std::string currentlyRentedMovies[limit];
    std::vector<std::string> previouslyRentedMovies;
    std::map<std::string, int> rating;
    creditCard creditcard;
    double coins = 0, SC_balance = 0;
    bool SC = false;
    std::string SC_passwrd;
};


//-------------------------utilities-----------------------------
std::string generateId(); // done
std::string deleteSpaces(std::string str); // done
bool checkPhoneNumber(std::string& phoneNumber); // done
bool checkPhoneNumberRegistered(customer customers[], int customers_count, std::string& phoneNumber); // done
bool checkId(customer customers[], int customers_count, std::string& id); // done
int getCustomersCount(customer customers[], int size_of_customers); // done
std::string isCurrentlyRentedAvailable(customer customers[], int customerIndex); // done
bool file_empty(std::ifstream& file);
int getMonthNum(std::string& mon); // done
//---------------------------------------------------------------

void listCustomers(customer customers[], int customers_count); // done
void displayCustomer(customer customers[], int customers_count, int customerIndex); // done
void addNewCustomer(customer customers[], int size_of_customers, int& customers_count); // done
void save_customers(customer customers[], int customers_count, const std::string& file_name); // done
void load_customers(customer customers[], int& customers_count, const std::string& file_name); // done