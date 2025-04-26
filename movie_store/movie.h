#pragma once
#include "customer.h"
#define movies_max 100



struct movie {
    std::string Name, CurrentRenter = "";
    double rating = 0, price, fee; //renting price and fee are per day
    int RentedCount = 0;
    bool rented = false, due = false;
    std::vector<int> AllRatings;
    date::year_month_day DueDate;
};


// movie movies[movies_max];


//-------------------------utilities-----------------------------
bool isCustomerFound(Customer customers[], int customers_count ,std::string& id); // done
int getCustomerIndex(Customer customers[], int customers_count, std::string& id); // done
bool isMovieFound(movie movies[], int movies_count, std::string& movieName); // done
int getMovieIndex(movie movies[], int movies_count, std::string& movieName); // done
bool isMovieRentedByCustomer(Customer customers[], int customers_count ,std::string& id, std::string& movieName); // done
bool isFull(Customer customers[], int customerIndex); // done
int getMoviesCount(movie movies[], int size_of_movies); // done
//-------------------------utilities-----------------------------


void ListMovies(movie movies[],int movies_count); // done
void listRented(movie movies[], int movies_count); // done 
int ListUnrented(movie movies[], int movies_count); // done

bool rate(movie movies[], int movies_count, std::string& movieName, 
    Customer customers[], int customers_count ,std::string& id); // done

bool editRating(movie movies[], int movies_count, std::string& movieName,
    Customer customers[], int customers_count, std::string& id); // done

void rent(Customer customers[],int num_of_customers, movie movies[], int num_of_movies);
void return_movie(Customer customer[], int cust_num, movie mov[], int mov_num);
int validate_due(movie& movie, bool isDateChanged, sys_days new_date);
void ListDueAccounts(movie mov[], int num_of_movies, Customer cust[], int num_of_customers, bool isDateChanged, sys_days new_date);

void MainMenu(Customer customers[], int size_of_customers, movie movies[], int size_of_movies); 
