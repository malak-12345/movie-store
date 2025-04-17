#pragma once
#include <string>
#include <vector>
<<<<<<< HEAD
#include "Howard_Hinnant/include/date/date.h"
=======
#include <array>
>>>>>>> e62ca82a458e79665f5e4ec5d3ede06f7a4e247e
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
std::string generateId();
std::string deleteSpaces(std::string& str);

bool checkPhoneNumber(std::string PhoneNumber);
bool checkPhoneNumber2(std::string PhoneNumber);

bool checkId(std::string& id, Customer c[], int size);
void addNewCustomer(Customer c[], int size);