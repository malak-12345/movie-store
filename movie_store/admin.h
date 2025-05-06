#pragma once
#include <string>
#include "movie.h"
#include "customer.h"
#include "Howard_Hinnant/include/date/date.h"

#define t 1


extern date::sys_days system_date;
extern double cashRegister;

std::string checkCredentials(std::string& login, std::string& passwrd); // done
void deleteCustomer(customer customers[], int& customers_count, std::string& id); // done
void deleteMovie(movie movies[], int& movies_count, std::string& movieName, customer customers[], int customers_count); // done
std::string login(); // done
void ChangeDate();
