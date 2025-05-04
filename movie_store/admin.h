#pragma once
#include <string>
#include "movie.h"
#include "customer.h"
#include "Howard_Hinnant/include/date/date.h"


#define t 1

extern double cashRegister;
extern date::sys_days new_date, today;
extern date::year_month_day system_date;

std::string checkCredentials(std::string& login, std::string& passwrd); // done
void deleteCustomer(customer customers[], int& customers_count, std::string& id, movie movies[], int movies_count); // done
void deleteMovie(movie movies[], int& movies_count, std::string& movieName, customer customers[], int customers_count); // done
std::string login(); // done
void addNewMovie(movie movies[], int size_of_movies, int& movies_count); // done
bool ChangeDate(date::sys_days& new_date);
