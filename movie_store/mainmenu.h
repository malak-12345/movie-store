#pragma once
#include "customer.h"
#include "movie.h"
#include "Howard_Hinnant/include/date/date.h"

auto now = std::chrono::system_clock::now();
date::sys_days system_date = date::floor<date::days>(now);
extern double cashRegister;
void displayMenu(std::string version, date::sys_days system_date);
int takeInput(std::string version);
void MainMenu(customer customers[], int size_of_customers, movie movies[], int size_of_movies);