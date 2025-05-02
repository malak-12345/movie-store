#include "mainmenu.h"
#include "movie.h"
#include "admin.h"
#include "customer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>




customer c[10] = {"loai", "1212121212", "1234", {"movie1"},{},{},{"8673383237229520","123", date::year(2025)/date::month(5)}};
movie m[10] = {"movie1", "loai", 3, 100, 10, 12, true, false, {}, /*date::year(2025) / date::month(5) / date::day(3)*/};



int main()
{
    // auto m = date::month(7);
    // std::cout << m.ok() << '\n';

    //load_movies(cashRegister, m, mov_count, "movies");
    MainMenu(c,10,m,10);
    //save_movies(cashRegister, m, mov_count, "movies");
}