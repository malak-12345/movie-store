#include "admin.h"
#include "customer.h"
#include "movie.h"

Customer c[10] = {"loai", "1212121212", "1234", {"movie1", "movie2"}};
movie m[10] = {"movie1", "loai", 3, 100, 10, 12, true};

int main()
{
    MainMenu(c,10,m,10);
}