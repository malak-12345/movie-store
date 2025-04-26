#pragma once
#include "utilities.h"

#define limit 8
#define customer_max 50

struct Customer
{
    std::string Name, PhoneNumber, Id;
    std::string CurrentlyRentedMovies[limit];
    std::vector<std::string> PreviouslyRentedMovies;
    std::map<std::string, int> rating;
    // need to make sure the movie name isn't duplicated when adding new movie ---> !isMovieFound();
};


// Customer customers[customer_max];
// int customers_count = getCustomersCount(); // put it in main.


//-------------------------utilities-----------------------------
std::string generateId();
std::string deleteSpaces(std::string& str);
bool checkPhoneNumber(std::string& PhoneNumber);
bool checkPhoneNumberRegistered(Customer customers[], int customers_count, std::string& PhoneNumber);
bool checkId(Customer customers[], int customers_count, std::string& id);
int getCustomersCount(Customer customers[], int size);
//-------------------------utilities-----------------------------

void listCustomers(Customer customers[], int customers_count);

