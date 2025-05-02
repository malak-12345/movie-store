#pragma once
#include "customer.h"
#include "movie.h"
#include "Howard_Hinnant/include/date/date.h"


void displayMenu(std::string version, date::sys_days today, bool isDateChanged, date::sys_days new_date);
int takeInput(std::string version);
void MainMenu(customer customers[], int size_of_customers, movie movies[], int size_of_movies);
