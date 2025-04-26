#pragma once
#include "movie.h"
// #include "utilities.h"

std::string checkCredentials(std::string& login, std::string& passwrd); // done
void deleteCustomer(Customer customers[], int& customers_count, std::string& id); // done
void deleteMovie(movie movies[], int& movies_count, std::string& name);
std::string login(); // done
bool ChangeDate(sys_days& new_date);
void add_movie(movie movies[]);