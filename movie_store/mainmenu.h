#pragma once
#include "customer.h"
#include "movie.h"
#include "Howard_Hinnant/include/date/date.h"

extern date::sys_days system_date;
extern double cashRegister;
extern int customers_count;
extern int movies_count;
extern double cashRegister;
void displayMenu(std::string version, date::sys_days system_date);
int takeInput(std::string version);
void MainMenu(customer customers[], int size_of_customers, movie movies[], int size_of_movies);