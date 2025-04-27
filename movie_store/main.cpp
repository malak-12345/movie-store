#include "admin.h"


Customer c[10] = {"loai", "1212121212", "1234", {"movie1"}};
movie m[10] = {"movie1", "loai", 3, 100, 10, 12, true, false, {}, 2025_y/5/12};

int main()
{
    MainMenu(c,10,m,10);
}