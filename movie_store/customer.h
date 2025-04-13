#include <string>
#include <vector>
#define limit 8

struct Customer{
    std::string Name, PhoneNumber;
    int Id;
    std::string CurrentlyRentedMovies[limit];
    std::vector<std::string> PreviouslyRentedMovies;
};

int generateId();
void addNewCustomer(); // TODO: takes an array of Customer
