#include "mainmenu.h"


customer c[10] = {"loai", "1212121212", "1234", {"movie1"}};
movie m[10] = {"movie1", "loai", 3, 100, 10, 12, true, false, {}, date::year(2025) / date::month(5) / date::day(3)};

int main()
{
    mainMenu(c,10,m,10);
}