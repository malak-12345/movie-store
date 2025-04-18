#pragma once
#include <string>
#include <vector>
#include "Howard_Hinnant/include/date/date.h"
#define limit 8
#define customer_max 50

struct Customer
{
    std::string Name, PhoneNumber, Id;
    std::string CurrentlyRentedMovies[limit];
    // std::array<std::string, limit> CurrentlyRentedMovies;
    std::vector<std::string> PreviouslyRentedMovies;
};

Customer customers[customer_max];
int customers_count = sizeof(customers) / sizeof(customers[0]);
std::string generateId();
std::string deleteSpaces(std::string& str);

bool checkPhoneNumber(std::string PhoneNumber);
bool checkPhoneNumber2(std::string PhoneNumber);
void list_customers(Customer customers[customer_max], int number_of_customers);
bool checkId(std::string& id, Customer c[customer_max], int size);
void addNewCustomer(Customer c[customer_max], int size);