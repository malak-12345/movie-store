#include "mainmenu.h"
#include "movie.h"
#include "customer.h"
#include <iostream>
#include "admin.h" // for cashRegister variable

customer c[customers_max];
movie m[movies_max];

int customers_count;
int movies_count;

int main()
{
    // for(std::string mov : c[0].currentlyRentedMovies) std::cout << mov << '\n';
    load_movies(cashRegister, m, movies_count, "movies_data");
    load_customers(c, customers_count, "customers_data");
    
    // for(std::string mov : c[0].currentlyRentedMovies) std::cout << mov << '\n';
    customers_count = getCustomersCount(c, customers_max);
    movies_count = getMoviesCount(m, movies_max);
    std::cout << customers_count << '\n' << movies_count << '\n';
    
    MainMenu(c, customers_max, m, movies_max);
    
    save_movies(cashRegister, m, movies_count, "movies_data");
    save_customers(c, customers_count, "customers_data");
}