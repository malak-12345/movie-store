#pragma once
#include <string>
#include <vector>
#include "customer.h"
#include "payment.h"
#include "Howard_Hinnant/include/date/date.h"

#define movies_max 100


struct movie {
    std::string name, currentRenter;
    double price = 0, fee = 0, rating = 0; //renting price and fee are per day
    int rentedCount = 0, rentalDays = 0;
    bool rented = false, due = false;
    std::vector<int> allRatings;
    date::year_month_day dueDate = date::year(3000) / date::month(10) / date::day(10);
};

//-------------------------utilities-----------------------------
bool isCustomerFound(customer customers[], int customers_count ,std::string& id); // done
int getCustomerIndex(customer customers[], int customers_count, std::string& id); // done
bool isMovieFound(movie movies[], int movies_count, std::string& movieName); // done
int getMovieIndex(movie movies[], int movies_count, std::string& movieName); // done
bool isMovieCurrentlyRentedByCustomer(customer customers[], int customers_count ,std::string& id, std::string& movieName); // done
bool isMoviePreviouslyRentedByCustomer(customer customers[], int customerIndex, std::string& movieName); // done
int getMoviesCount(movie movies[], int size_of_movies); // done
void is_num(int& input); // done
void is_num(double& input); // done
bool yes_no(); // done
//----------------------------------------------------------------

void listMovies(movie movies[], int movies_count); // done

void listRented(movie movies[], int movies_count); // done 

int listUnrented(movie movies[], int movies_count); // done

void calc_rating(movie& movie); // done

bool rate(movie movies[], int movies_count, std::string& movieName, 
          customer customers[], int customers_count ,std::string& id); 

bool editRating(movie movies[], int movies_count, std::string& movieName,
                customer customers[], int customers_count, std::string& id);

void rent(customer customers[], int customers_count, movie movies[], int movies_count, std::string& id); // 

void returnMovie(double& cashRegister, customer customers[], int customers_count, std::string& id, movie movies[], int movies_count); // 

int validateDue(movie& movie); // 

int calc_rental_days(movie& movie); // 

void listDueAccounts(movie movies[], int movies_count, customer customers[], int customers_count); // 

void listTopRated(movie movies[], int movies_count); 

void addNewMovie(movie movies[], int size_of_movies, int& movies_count); // done
    
void listTopRented(movie movies[], int movies_count);

void save_movies(double cashRegister, movie movies[], int movies_count, const std::string& file_name);

void load_movies(double& cashRegister, movie movies[], int& movies_count, const std::string& file_name);

