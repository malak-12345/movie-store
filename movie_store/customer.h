#pragma once
#include <string>
#include <vector>
#include <array>
#define limit 8

struct Customer
{
    std::string Name, PhoneNumber, Id;
    std::string CurrentlyRentedMovies[limit];
    // std::array<std::string, limit> CurrentlyRentedMovies;
    std::vector<std::string> PreviouslyRentedMovies;
};

std::string generateId();
std::string deleteSpaces(std::string& str);

bool checkPhoneNumber(std::string PhoneNumber);
bool checkPhoneNumber2(std::string PhoneNumber);

bool checkId(std::string& id, Customer c[], int size);
void addNewCustomer(Customer c[], int size);