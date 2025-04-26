#pragma once
#include "movie.h"

std::string checkCredentials(std::string& login, std::string& passwrd);
void deleteCustomer(Customer customers[], int& customers_count, std::string& id);
void deleteMovie(movie movies[], int num_of_movies, std::string& name);
std::string login();
bool ChangeDate(sys_days& new_date);
void addNewCustomer(Customer customers[], int& customers_count);
void add_movie(movie movies[]);