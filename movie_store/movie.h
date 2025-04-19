#pragma once
#include "customer.h"
//#include <string>
//#include <vector>
//#include <iostream>
//#include <limits>
//#include <sstream>
//#include <chrono>
//#include <thread>
#define movies_max 100



struct movie {
    std::string Name, CurrentRenter;
    double rating = 0, price, fee; //renting price and fee are per day
    int RentedCount = 0;
    bool rented = false, due = false;
    std::vector<int> AllRatings;
    date::year_month_day DueDate;
};

movie movies[movies_max];
//int movies_count = sizeof(movies) / sizeof(movies[0]); // = 100 (const)


void ListMovies(const movie movies[],int& movies_count);
double rate(movie& movie);
int ListUnrented(movie movies[],const int& movies_count);
bool isFull(Customer customers[], int customerNum);
void Rent(Customer cust [], int movies_count, movie movies[]);
date::day validate_due(movie movie); //to do
void ListDueAccounts();
void MainMenu(); 
