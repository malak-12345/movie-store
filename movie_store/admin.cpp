#include "admin.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

std::string ADMIN = "admin";
std::string ADMIN_PSSWRD = "admin";

std::string USER = "user";
std::string USER_PSSWRD = "user";

double cashRegister = 0.0;
auto now = std::chrono::system_clock::now();
date::sys_days new_date, today = date::floor<date::days>(now);
date::year_month_day system_date = today;


std::string checkCredentials(std::string& login, std::string& passwrd) // done
{
    if(login == ADMIN && passwrd == ADMIN_PSSWRD)
    {
        return "admin";
    }
    else if (login == USER && passwrd == USER_PSSWRD)
    {
        return "user";        
    }
    return "";
}

void deleteCustomer(customer customers[], int& customers_count, std::string& id, movie movies[], int movies_count) // done
{
    if(customers_count != 0)
    {
        for (int i = 0; i < customers_count; i++) 
        {
            if (customers[i].id == id) 
            {
                for(int j = 0; j < limit; j++)
                {
                    if(!(customers[i].currentlyRentedMovies[j].empty()))
                    {
                        std::cout << "Return rented movies before deleting!\n";
                        return;
                    }
                }
                std::cout << i << '\n';
                if(i < customers_count-1)
                {
                    customers[i].name = customers[customers_count-1].name;
                    customers[i].phoneNumber = customers[customers_count-1].phoneNumber;
                    customers[i].id = customers[customers_count-1].id;
                    customers[i].previouslyRentedMovies = customers[customers_count-1].previouslyRentedMovies;
                    customers[i].rating = customers[customers_count-1].rating;
                    customers[i].coins = customers[customers_count-1].coins;
                    customers[i].creditcard = customers[customers_count-1].creditcard;
                    customers[i].SC = customers[customers_count-1].SC;
                    customers[i].SC_balance = customers[customers_count-1].SC_balance;
                    customers[i].SC_passwrd = customers[customers_count-1].SC_passwrd;
                    for(int j = 0; j < limit; j++)
                    {
                        customers[i].currentlyRentedMovies[j] = customers[customers_count-1].currentlyRentedMovies[j];
                    }
                    //--------------clear last element--------------
                    customers[customers_count-1].name.clear();
                    customers[customers_count-1].id.clear();
                    customers[customers_count-1].phoneNumber.clear();
                    customers[customers_count-1].previouslyRentedMovies.clear();
                    customers[customers_count-1].rating.clear();
                    customers[customers_count-1].coins = 0;
                    customers[customers_count-1].creditcard.cardNumber.clear();
                    customers[customers_count-1].creditcard.ccv.clear();
                    customers[customers_count-1].creditcard.yy_mm = date::year(3000)/10;
                    customers[customers_count-1].SC = false;
                    customers[customers_count-1].SC_balance = 0;
                    customers[customers_count-1].SC_passwrd.clear();
                    for(int j = 0; j < limit; j++)
                    {
                        customers[customers_count - 1].currentlyRentedMovies[j].clear();
                    }

                    customers_count--;
                }
                else if (i == customers_count-1)
                {
                    customers[i].name.clear();
                    customers[i].id.clear();
                    customers[i].phoneNumber.clear();
                    customers[i].previouslyRentedMovies.clear();
                    customers[i].rating.clear();
                    customers[i].coins = 0;
                    customers[i].creditcard.cardNumber.clear();
                    customers[i].creditcard.ccv.clear();
                    customers[i].creditcard.yy_mm = date::year(3000)/10;
                    customers[i].SC = false;
                    customers[i].SC_balance = 0;
                    customers[i].SC_passwrd.clear();
                    for(int j = 0; j < limit; j++)
                    {
                        customers[i].currentlyRentedMovies[j].clear();
                    }
                    customers_count--;
                }
                else
                {
                    std::cout << "Error in the customer array!\n";
                    break;
                }
                std::cout << "Customer with ID: " << id << " deleted successfully.\n";
                break;
            }
        }
    }
    else
    {
        std::cout << "There are currently no customers on the system!, please add a customer first.\n";
    }
}

void deleteMovie(movie movies[], int& movies_count, std::string& movieName, customer customers[], int customers_count) // done
{
    if(movies_count != 0)
    {
        std::string name;
        for(int i = 0; i < movies_count; i++)
        {
            name = movies[i].name;
            std::transform(name.begin(), name.end(), name.begin(), tolower);
            name = deleteSpaces(name);
            if(name == movieName)
            {
                for(int j = 0; j < customers_count; j++)
                {
                    if(isMovieCurrentlyRentedByCustomer(customers, customers_count, customers[j].id, name))
                    {
                        std::cout << "\ncan't delete movie!\n";
                        std::cout << "This movie is currently rented by: " << customers[j].id << '\n';
                        return;
                    }

                    for(int k = 0; k < customers[j].previouslyRentedMovies.size(); k++)
                    {
                        std::string movie = customers[j].previouslyRentedMovies[k];
                        std::transform(movie.begin(), movie.end(), movie.begin(), tolower);
                        if(deleteSpaces(movie) == name)
                        {
                            customers[j].previouslyRentedMovies[k].append(" (deleted)");
                        }
                    }
                }
                
                if (i < movies_count - 1)
                {
                    movies[i].name = movies[movies_count - 1].name;
                    movies[i].currentRenter = movies[movies_count - 1].currentRenter;
                    movies[i].allRatings = movies[movies_count - 1].allRatings;
                    movies[i].rented = movies[movies_count - 1].rented;
                    movies[i].price = movies[movies_count - 1].price;
                    movies[i].fee = movies[movies_count - 1].fee;
                    movies[i].rating = movies[movies_count - 1].rating;
                    movies[i].rentedCount = movies[movies_count - 1].rentedCount;
                    movies[i].dueDate = movies[movies_count - 1].dueDate;
                    movies[i].due = movies[movies_count - 1].due;
                    movies[i].rentalDays = movies[movies_count - 1].rentalDays;
                    //--------------clear last element--------------
                    movies[movies_count - 1].name.clear();
                    movies[movies_count - 1].currentRenter.clear();
                    movies[movies_count - 1].allRatings.clear();
                    movies[movies_count - 1].rented = false;
                    movies[movies_count - 1].price = 0;
                    movies[movies_count - 1].fee = 0;
                    movies[movies_count - 1].rating = 0;
                    movies[movies_count - 1].rentedCount = 0;
                    movies[movies_count - 1].dueDate = date::year(3000) / date::month(10) / date::day(10);
                    movies[movies_count - 1].due = false;
                    movies[movies_count - 1].rentalDays = 0;
                    movies_count--;
                }
                else if (i == movies_count - 1) 
                {
                    movies[i].name.clear();
                    movies[i].currentRenter.clear();
                    movies[i].allRatings.clear();
                    movies[i].rented = false;
                    movies[i].price = 0;
                    movies[i].fee = 0;
                    movies[i].rating = 0;
                    movies[i].rentedCount = 0;
                    movies[i].dueDate = date::year(3000) / date::month(10) / date::day(10); //default state for empty, not an actual thing in the language i just decided that
                    movies[i].due = false;
                    movies[i].rentalDays = 0;
                    movies_count--;
                }
                else 
                {
                    std::cerr << "Error in the movies array\n";
                    break;
                }
                std::cout << "Movie deleted successfully!\n";
                break;
            }
        }
    }
    else
    {
        std::cout << "There are currently no movies on the system! Please add a movie first.\n";
    }
}

std::string login() // done
{
    std::string login, passwrd;
    do
    {
        std::cout << "Enter username: ";
        std::getline(std::cin, login);
        if (login == "0") return "";
        
        std::cout << "Enter password: ";
        std::getline(std::cin, passwrd);
        if (passwrd == "0") return "";
        
        if(checkCredentials(login, passwrd) == "admin")
        {
            std::cout << "Welcome, " << login << "!\n";
            std::this_thread::sleep_for(std::chrono::seconds(t));
            return "admin";
        }
        else if(checkCredentials(login, passwrd) == "user")
        {
            std::cout << "Welcome, " << login << "!\n";
            std::this_thread::sleep_for(std::chrono::seconds(t));
            return "user";
        }
        else
        {
            std::cout << "Wrong password or username!\n\n";
        }
    } while(checkCredentials(login, passwrd) == "");
}

void addNewMovie(movie movies[], int size_of_movies, int& movies_count) // done
{
    std::string movieName, check;
    double price = 0, fee = 0;
    do
    {
        std::cout << "Enter movie name: ";
        getline(std::cin, movieName);
        check = deleteSpaces(movieName);
        (check.begin(), check.end(), check.begin(), tolower);
        
        if(movieName == "0")
        {
            std::cout << "Returning to main menu!\n";
            std::this_thread::sleep_for(std::chrono::seconds(t));
            return;
        }
        if(isMovieFound(movies,movies_count,check))
        {
            std::cout << "This movie already exists!\n";
            continue;
        }
        std::cout << "\nEnter movie price per day (EGP) : ";
        is_num(price);
        std::cout << "\nEnter due fees per day (EGP) : ";
        is_num(fee);
    } while(isMovieFound(movies,movies_count,check) || check.empty());
    
    for(int i = 0; i < size_of_movies; i++)
    {
        if(movies[i].name.empty())
        {
            movies[i].name = movieName;
            movies[i].price = price;
            movies[i].fee = fee;
            movies_count++;
            std::cout << "Successfully added: " << movieName << '\n';
            return;
        }
    }
    std::cerr << "you have reached maximum movie capacity!!\n"; // if the return doesn't happen, ie there are no empty slots
    std::this_thread::sleep_for(std::chrono::seconds(t));
    std::cout << "Returning to main menu!\n";
}

bool ChangeDate(date::sys_days& new_date) // doesn't allow you to set a date prior to actual current date from system_clock, in order to avoid embezzlement
{
    int y, m, d;
    char delimiter1, delimiter2;
    std::string entered_date;
    std::cout << "do you wish to set date manually y/n?: ";
    if (yes_no()) 
    {
        while (true) //infinite loop till broken by return
        {
            std::cout << "specify date in this exact format yyyy/mm/dd : ";
            getline(std::cin, entered_date);
            std::cin.clear();
            entered_date = deleteSpaces(entered_date);
            if (entered_date == "0") 
            {
                std::cout << "Returning to main menu!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
                return false; //aborts and exits to main menu
            }
            std::istringstream iss(entered_date);
            if (iss >> y >> delimiter1 >> m >> delimiter2 >> d && date::year(y) >= system_date.year() && delimiter1 == '/' && delimiter2 == '/') 
            {
                new_date = date::year(y) / date::month(m) / date::day(d); //converts date::year_month_day to sys_days, thnx to sir Howard Hinnant
                return true;
            }
            else 
            {
                std::cerr << "wrong format or invalid date, please try again\n";
            }
        }
    }
    else 
    {
        std::cout << "Returning to main menu!\n";
        std::this_thread::sleep_for(std::chrono::seconds(t));
        return false; //aborting
    }
}
