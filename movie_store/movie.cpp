#include "movie.h"
#include "customer.h"
#include <iostream>
#include <limits>
#include <chrono>
#include <thread>


void ListMovies(const movie(&movies)[movies_max], const int& movies_count) {
    int MovieNum = 1;
    if (movies_count != 0) {
        for (int i = 0;i <= movies_count;i++) {
            std::cout << MovieNum << ". " << movies[i].Name << std::endl;
            std::cout << "\tprice: " << movies[i].price << " EGP" << std::endl;
            std::cout << "\trating:" << movies[i].rating << std::endl;
            std::cout << "\trented: " << movies[i].RentedCount << " times" << std::endl;
            if (movies[i].rented) {
                std::cout << "\trented status: " << "rented" << std::endl;
            }
            else {
                std::cout << "\trented status: " << "not rented" << std::endl;
            }
            std::cout << "\n";
            MovieNum++;
        }
    }
    else {
        std::cerr << "no movies to display, please add a movie first" << std::endl;
    }
}

//will always be called before renting and sometimes separately
void ListUnrented(const movie(&movies)[movies_max], const int& movies_count) {
    int MovieNum = 1;
    if (movies_count != 0) {
        for (int i = 0;i <= movies_count;i++) {
            if (!movies[i].rented) {
                std::cout << MovieNum << ". " << movies[i].Name << std::endl;
                MovieNum++;
            }
        }
        if (MovieNum == 1) { //meaning there are movies on the system but no movies were displayed, aka they are all rented 
            std::cerr << "there are currently no available movies to rent" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            // main_menu();
        }
    }else {
        std::cerr << "there are currently no movies on the system, please add a movie first" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        //exit to main menu main_menu();
    }
}


double rate(movie& movie) { //using a weighted rating algorithm
    std::cout << "on a scale from 1 to 5, how much would you rate this movie?: ";
    int Rating;
    bool ValidRating = false;
    double FinalRating = 0.0;
    int a, b, c, d, e;
    while (!ValidRating) {
        Rating = 0;
        a = 0;
        b = 0;
        c = 0;
        d = 0;
        e = 0;
        std::cin >> Rating;
        if (std::cin.good() && Rating >= 1 && Rating <= 5) {
            ValidRating = true;
        }
        else {
            std::cerr << "Invalid Rating. Please enter a whole number between 1 and 5.\n";
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (!movie.AllRatings.size() == 0) {
            for (int i : movie.AllRatings) {
                switch (i)
                {
                case 1:
                    a++;
                    break;
                case 2:
                    b++;
                    break;
                case 3:
                    c++;
                    break;
                case 4:
                    d++;
                    break;
                case 5:
                    e++;
                    break;
                default:
                    std::cerr << "error in the ratings vector, please contact your IT provider" << std::endl;
                    break;
                }
            }
        }
        switch (Rating)
        {
        case 1:
            a++;
            break;
        case 2:
            b++;
            break;
        case 3:
            c++;
            break;
        case 4:
            d++;
            break;
        case 5:
            e++;
            break;
        default:
            break;
        }
    }
    FinalRating = (a * 1 + b * 2 + c * 3 + d * 4 + e * 5) / (a + b + c + d + e);
    std::cout << "\nthank you for your review!! " << std::endl;
    return FinalRating;
}




void rent() {
    bool CustomerFound = false, repeat = true;
    int selected;
    std::string name;
    ListUnrented(movies, movies_count);

}


