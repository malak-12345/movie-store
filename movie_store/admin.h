#pragma once
#include "movie.h"

std::string checkCredentials(std::string& login, std::string& passwrd);
void deleteCustomer(Customer customers[], int num_of_customers, std::string& id);
void deleteMovie(movie movies[], int num_of_movies, std::string& name);
void changeDate();
int login();