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
    std::vector<std::string> PreviouslyRentedMovies;
};
int CurrentlyRentedMovies_count = sizeof(CurrentlyRentedMovies) / sizeof(CurrentlyRentedMovies[0]);
Customer customers[customer_max];
int customers_count = sizeof(customers) / sizeof(customers[0]);

std::string generateId();
std::string deleteSpaces(std::string& str);
bool checkPhoneNumber(std::string PhoneNumber);
bool checkPhoneNumber2(std::string PhoneNumber);

bool checkId(std::string& id, Customer c[], int size);

void listCustomers(Customer customers[], int number_of_customers);
void addNewCustomer(Customer c[], int size);
