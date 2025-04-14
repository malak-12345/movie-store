#include <string>
#include <vector>
#define limit 8

struct Customer
{
    std::string Name, PhoneNumber, Id;
    std::string CurrentlyRentedMovies[limit];
    std::vector<std::string> PreviouslyRentedMovies;
};

std::string generateId();
std::string deleteSpaces(std::string str);
bool checkPhoneNumber(std::string PhoneNumber);
void addNewCustomer(); // TODO: takes an array of Customer
