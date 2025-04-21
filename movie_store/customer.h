#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <limits>
#include <sstream>
#include <map>
#include "Howard_Hinnant/include/date/date.h"

#define limit 8
#define customer_max 50

struct Customer
{
    std::string Name, PhoneNumber, Id;
    std::string CurrentlyRentedMovies[limit];
    std::vector<std::string> PreviouslyRentedMovies;
    std::map<std::string, int> rating; // the key is moviename and the value is the rating.
    // Problem that keys must be unique. movie name can be the same??
    // need to make sure the movie name isn't duplicated when adding new movie ---> !isMovieFound();
};


Customer customers[customer_max];
int customers_count = 0;


//-------------------------utilities-----------------------------
std::string generateId();
std::string deleteSpaces(std::string& str);
bool checkPhoneNumber(std::string& PhoneNumber);
bool checkId(std::string& id, Customer c[], int size);
//-------------------------utilities-----------------------------

void listCustomers(Customer customers[], int number_of_customers);
void addNewCustomer(Customer c[], int size);
