#pragma once
#include "customer.h"
#include "movie.h"
#include "Howard_Hinnant/include/date/date.h"

extern int customers_count;
extern int movies_count;

void displayMenu(std::string version, bool isDateChanged);
int takeInput(std::string version);
void MainMenu(customer customers[], int size_of_customers, movie movies[], int size_of_movies);
