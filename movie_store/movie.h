#pragma once
#include <string>
#include <vector>
#include "customer.h"
#include "payment.h"
#include "Howard_Hinnant/include/date/date.h"

#define movies_max 100


struct movie {
    std::string name, currentRenter = "none";
    double price, fee, rating; //renting price and fee are per day
    int rentedCount;
    bool rented = false, due = false;
    std::vector<int> allRatings;
    date::year_month_day dueDate = date::year(3000) / date::month(10) / date::day(10);
};

//-------------------------utilities-----------------------------
bool isCustomerFound(customer customers[], int customers_count ,std::string& id); // done
int getCustomerIndex(customer customers[], int customers_count, std::string& id); // done
bool isMovieFound(movie movies[], int movies_count, std::string& movieName); // done
int getMovieIndex(movie movies[], int movies_count, std::string& movieName); // done
bool isMovieRentedByCustomer(customer customers[], int customers_count ,std::string& id, std::string& movieName); // done
int getMoviesCount(movie movies[], int size_of_movies); // done
void is_num(int& input); // done
void is_num(double& input); // done
bool yes_no(); // done
//----------------------------------------------------------------

void listMovies(movie movies[], int movies_count); // done
void listRented(movie movies[], int movies_count); // done 
int listUnrented(movie movies[], int movies_count); // done

bool rate(movie movies[], int movies_count, std::string& movieName, 
    customer customers[], int customers_count ,std::string& id); // done

bool editRating(movie movies[], int movies_count, std::string& movieName,
    customer customers[], int customers_count, std::string& id); // done

void rent(customer customers[], int customers_count, movie movies[], int movies_count, 
    date::year_month_day system_date);

void returnMovie(customer customers[], int customers_count, std::string& id, movie movies[], 
    int movies_count, bool isDateChanged, date::sys_days new_date); // done

int validateDue(movie& movie, bool isDateChanged, date::sys_days new_date); // done

void listDueAccounts(movie movies[], int movies_count, customer customers[], int customers_count, 
    bool isDateChanged, date::sys_days new_date); //done

    
void listTopRated(movie movies[], int movies_count);
    
void listTopRented(movie movies[], int movies_count);