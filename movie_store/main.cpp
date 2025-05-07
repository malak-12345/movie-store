#include "mainmenu.h"
#include "movie.h"
#include "customer.h"
#include "admin.h" // system_date, cashRegister
#include <iostream>

// customer c[customers_max] = {
//     {/*name*/ "Loai Mohammed", 
//      /*phone*/ "201111111111", 
//      /*ID*/ "C#1111", 
//      /*currently rented*/ {"Batman 2023", {}, {}, {}, {}, "The Flash"}, 
//      /*previously rented*/ {}, 
//      /*rating*/ {{"Batman 2023",4}},
//      /*credit card*/{"1718038092639310","123",date::year(2025)/5},
//      /*coins*/ 5, 
//      /*SC*/ 0,
//      /*has SC?*/ false,
//      /*psswrd*/ ""},
    
//     {/*name*/ "Hussein Elfiky", 
//      /*phone*/ "202222222222", 
//      /*ID*/ "C#2222", 
//      /*currently rented*/ {"The Avengers"},
//      /*previously rented*/ {}, 
//      /*rating*/ {{}},
//      /*credit card*/{},
//      /*coins*/ 10, 
//      /*SC*/ 200,
//      /*has SC?*/ true,
//      /*psswrd*/ "password"},
    
//     {/*name*/ "Afeef Mohammed", 
//      /*phone*/ "203333333333", 
//      /*ID*/ "C#3333", 
//      /*currently rented*/ {}, 
//      /*previously rented*/ {}, 
//      /*rating*/ {{}},
//      /*credit card*/{},
//      /*coins*/ 3, 
//      /*SC*/ 0,
//      /*has SC?*/ false,
//      /*psswrd*/ ""},

//     {/*name*/ "Hamim Essa", 
//      /*phone*/ "204444444444", 
//      /*ID*/ "C#4444", 
//      /*currently rented*/ {"The Terminator"}, 
//      /*previously rented*/ {}, 
//      /*rating*/ {{}},
//      /*credit card*/{},
//      /*coins*/ 8, 
//      /*SC*/ 0,
//      /*has SC?*/ false,
//      /*psswrd*/ ""},

//     {/*name*/ "Murtadi Samaha", 
//      /*phone*/ "205555555555", 
//      /*ID*/ "C#5555", 
//      /*currently rented*/ {}, 
//      /*previously rented*/ {"Superman IV"}, 
//      /*rating*/ {{}},
//      /*credit card*/{},
//      /*coins*/ 2, 
//      /*SC*/ 0,
//      /*has SC?*/ false,
//      /*psswrd*/ ""},
        
//     {/*name*/ "Mazin Attia", 
//      /*phone*/ "206666666666", 
//      /*ID*/ "C#6666", 
//      /*currently rented*/ {}, 
//      /*previously rented*/ {"Avatar"}, 
//      /*rating*/ {{}},
//      /*credit card*/{},
//      /*coins*/ 1, 
//      /*SC*/ 0,
//      /*has SC?*/ false,
//      /*psswrd*/ ""}
    
//     /* ----template---- */
//     // {/*name*/ "", 
//     //  /*phone*/ "", 
//     //  /*ID*/ "", 
//     //  /*currently rented*/ {}, 
//     //  /*previously rented*/ {}, 
//     //  /*rating*/ {{}},
//     //  /*credit card*/{},
//     //  /*coins*/ 0, 
//     //  /*SC*/ 0,
//     //  /*has SC?*/ false,
//     //  /*psswrd*/},
// };

// movie m[movies_max] = {
//     /*template: */
//     //{"name",   "renter",   /*price*/0,   /*fee*/0,   /*rating*/0,   /*rent count*/0,   /*rental days*/0,   /*rented?*/false,   /*due?*/false,   /*allratings*/{0,},   /*due date*/   date::year(2025)/1/1},
//     /*--------*/
//     {"Batman 2023",   "Loai Mohammed",   /*price*/90,   /*fee*/10,   /*rating*/4,   /*rent count*/10,   /*rental days*/12,   /*rented?*/true,   /*due?*/false,   /*allratings*/{4},   /*due date*/ date::year(2025)/5/15},
//     {"The Flash",      "Loai Mohammed",  /*price*/35,   /*fee*/5,    /*rating*/4,   /*rent count*/8,    /*rental days*/17,    /*rented?*/true,  /*due?*/false,   /*allratings*/{4},   /*due date*/ date::year(2025)/5/20},
//     {"Titanic",        "",               /*price*/50,   /*fee*/10,   /*rating*/4,   /*rent count*/8,    /*rental days*/0,    /*rented?*/false,  /*due?*/false,   /*allratings*/{4},   /*due date*/},
//     {"Jurassic Park",  "",               /*price*/25,   /*fee*/5,    /*rating*/5,   /*rent count*/10,   /*rental days*/0,    /*rented?*/false,  /*due?*/false,   /*allratings*/{5},   /*due date*/},
//     {"The Avengers",   "Hussein Elfiky", /*price*/40,   /*fee*/10,   /*rating*/5,   /*rent count*/6,    /*rental days*/28,    /*rented?*/true,  /*due?*/false,   /*allratings*/{5},   /*due date*/ date::year(2025)/5/30},
//     {"Superman IV",    "",               /*price*/45,   /*fee*/10,   /*rating*/4,   /*rent count*/7,    /*rental days*/0,    /*rented?*/false,  /*due?*/false,   /*allratings*/{4},   /*due date*/},
//     {"The Terminator", "Hamim Essa",     /*price*/20,   /*fee*/5,    /*rating*/4,   /*rent count*/7,    /*rental days*/28,    /*rented?*/true,  /*due?*/false,   /*allratings*/{4},   /*due date*/ date::year(2025)/5/30},
//     {"Gladiator 2000", "",               /*price*/55,   /*fee*/10,   /*rating*/5,   /*rent count*/6,    /*rental days*/0,    /*rented?*/false,  /*due?*/false,   /*allratings*/{5},   /*due date*/},
//     {"Avatar",         "",               /*price*/60,   /*fee*/10,   /*rating*/4,   /*rent count*/5,    /*rental days*/0,    /*rented?*/false,  /*due?*/false,   /*allratings*/{4},   /*due date*/},
//     {"Spiderman",      "",               /*price*/70,   /*fee*/10,   /*rating*/4,   /*rent count*/9,    /*rental days*/0,    /*rented?*/false,  /*due?*/false,   /*allratings*/{4},   /*due date*/}
// };

customer c[customers_max];

movie m[movies_max];

int main()
{
    load_movies(cashRegister, m, movies_count, "movies_data");
    load_customers(c, customers_count, "customers_data");
    
    customers_count = getCustomersCount(c, customers_max);
    movies_count = getMoviesCount(m, movies_max);
    std::cout << "Number of customers: " << customers_count << '\n';
    std::cout << "Number of movies: " << movies_count << '\n';
    
    MainMenu(c, customers_max, m, movies_max);
    
    save_movies(cashRegister, m, movies_count, "movies_data");
    save_customers(c, customers_count, "customers_data");
}