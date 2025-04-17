#pragma once
#include <string>
#include <vector>
#include "customer.h"
#define movies_max 100
struct date {
    int year, month, day;
};


struct movie {
    std::string Name, CurrentRenter;
    double rating = 0, price, fee; //renting price and fee are per day
    int RentedCount = 0;
    bool rented = false;
    std::vector<int> AllRatings;
    date DueDate;
};

movie movies[movies_max];
int movies_count = sizeof(movies) / sizeof(movies[0]);


void ListMovies(const movie(&movies)[movies_max],int& movies_count);
double rate(movie& movie);
void ListUnrented(movie(&movies)[movies_max],const int& movies_count);
void Rent(movie(&movies)[movies_max], int movies_count), Customer (&customers)[customer_max]);