#include "mainmenu.h"
#include "movie.h"
#include "admin.h"
#include "customer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

extern double cashRegister;
customer c[customer_max];
movie m[movies_max];
//customer c[10] = {"loai", "1212121212", "1234", {"movie1"},{},{},{"8673383237229520","123", date::year(2025)/date::month(5)}};
//movie m[10] = {"movie1", "loai", 3, 100, 10, 12, 10, true, false, {}, date::year(2025) / 5 / 12};
//c[5].name = "lol";
int customers_count;
int movies_count;
int main()
{
    c[0].name = "loai";
    load_movies(cashRegister, m, movies_count, "movies_data");
    load_customers(c, customers_count, "customers_data");
    customers_count = getCustomersCount(c, customer_max);
    movies_count = getMoviesCount(m, movies_max);
    MainMenu(c, customer_max, m, movies_max);
    save_movies(cashRegister, m, movies_count, "movies_data");
    save_customers(c, customers_count, "customers_data");
}