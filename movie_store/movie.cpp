#include "movie.h"
#include "customer.h"
#include <iostream>
#include <limits>
#include <chrono>
#include <thread>


void ListMovies(const movie(&movies)[], const int& movies_count) {
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
int ListUnrented(const movie(&movies)[], const int& movies_count) {
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
    return MovieNum;
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
    std::cout << "\nthank you for your review!!! " << std::endl;
    return FinalRating;
}




void Rent(Customer(&cust)[], int movies_count, movie(&movies)[]){
    bool CustomerFound = false, repeat = true;
    int selected,customer ,segment_count = 3,  match = 1, unrented_movies_count = ListUnrented(movies, movies_count);
    char delimiter = '/';
    std::string name, id, enterd_date;
    ListUnrented(movies, movies_count);
    while (!CustomerFound) {
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        std::cout << "enter customer name: "; //"if you wish to go back enter '0', otherwise..." add a way to navigate
        std::getline(std::cin, name);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "enter customer id: ";
        std::getline(std::cin, id);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int i = 0; i < customers_count;i++) {
            if (cust[i].Id == id && cust[i].Name == name || /*is admin*/) {
                CustomerFound = true;
                customer = i;
                break;
            }
            else {
                std::cerr << "wrong name or id, please try again\n";
            }
        }
    }
    std::cout << "pick a movie number: ";
    while (repeat) {
        std::cin >> selected;
        if (std::cin.good() && selected < unrented_movies_count && selected > 0) {
            repeat = false;
        }
        else {
            std::cerr << "Invalid choice. Please select a valid movie number: ";
            repeat = true;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    for (int i = 0; i < movies_count;i++) {
        if (!movies[i].rented && match == selected) {
            std::cout << "movie:   " << movies[i].Name << std::endl;
            std::cout << "\tprice per day: " << movies[i].price << " EGP" << std::endl;
            std::cout << "\toverdue fee per day: " << movies[i].fee << " EGP" << std::endl;
            std::cout << "\tmovie rating:" << movies[i].rating << std::endl;
            std::cout << "\thas been rented: " << movies[i].RentedCount << " times" << std::endl;
            std::cout << "today is: "<</*date*/ <<std::endl;
            std::cout << "specify due date in this exact format yy/mm/dd : ";
            //std::istringstream iss(enterd_date);     fix
            //std::getline(std::cin, enterd_date);

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            movies[i].rented = true;
            movies[i].RentedCount ++;
            movies[i].CurrentRenter = name;
            for (int j = 0;j < customers_count;j++) {
                if (cust[customer].Id == id) {
                    cust[customer].CurrentlyRentedMovies[CurrentlyRentedMovies_count] = movies[i].Name;
                    cust[customer].PreviouslyRentedMovies.push_back(movies[i].Name);
                }
            }
        }
        if (!movies[i].rented) {
            match++;
        }
    }
}





