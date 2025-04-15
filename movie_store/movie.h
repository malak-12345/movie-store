#pragma once
#include <string>
#include <vector>

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

std::vector<movie> movies;

//void ListMovies(const std::vector<movie>& movies);
double rate(movie& movie);
void ListUnrented(std::vector<movie>& movies);