#include "admin.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

std::string ADMIN = "admin";
std::string ADMIN_PSSWRD = "admin";

std::string USER = "user";
std::string USER_PSSWRD = "user";

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

void deleteCustomer(customer customers[], int& customers_count, std::string& id) // done
{
    if(customers_count != 0)
    {
        for (int i = 0; i < customers_count; i++) 
        {
            if (customers[i].id == id) 
            {
                if(i < customers_count-1)
                {
                    customers[i].name = customers[customers_count-1].name;
                    customers[i].phoneNumber = customers[customers_count-1].phoneNumber;
                    customers[i].id = customers[customers_count-1].id;
                    customers[i].previouslyRentedMovies = customers[customers_count-1].previouslyRentedMovies;
                    for(int j = 0; j < limit; j++)
                    {
                        customers[i].currentlyRentedMovies[j] = customers[customers_count-1].currentlyRentedMovies[j];
                    }
                    
                    customers[customers_count-1].name.clear();
                    customers[customers_count-1].id.clear();
                    customers[customers_count-1].phoneNumber.clear();
                    customers[customers_count-1].previouslyRentedMovies.clear();
                    for(int j = 0; j < limit; j++)
                    {
                        customers[customers_count-1].currentlyRentedMovies[j].clear();
                    }
                    customers_count--;
                }
                else if (i == customers_count-1)
                {
                    customers[i].name.clear();
                    customers[i].id.clear();
                    customers[i].phoneNumber.clear();
                    customers[i].previouslyRentedMovies.clear();
                    for(int j = 0; j < limit; j++)
                    {
                        customers[i].currentlyRentedMovies[j].clear();
                    }
                    customers_count--;
                }
                else
                {
                    std::cout << "Error in the customer array, please contact your IT provider\n";
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

void deleteMovie(movie movies[], int& movies_count, std::string& movieName) // done
{
    if(movies_count != 0)
    {
        for(int i = 0; i < movies_count; i++)
        {
            if(movies[i].name == movieName)
            {
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
                    //----------------
                    movies[movies_count - 1].name.clear();
                    movies[movies_count - 1].currentRenter.clear();
                    movies[movies_count - 1].allRatings.clear();
                    movies[movies_count - 1].rented = false;
                    movies[movies_count - 1].price = 0;
                    movies[movies_count - 1].fee = 0;
                    movies[movies_count - 1].rating = 0;
                    movies[movies_count - 1].rentedCount = 0;
                    movies[movies_count - 1].dueDate = date::year(1000) / date::month(10) / date::day(10);
                    movies[movies_count - 1].due = false;
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
                    movies[i].dueDate = date::year(1000) / date::month(10) / date::day(10); //default state for empty, not an actual thing in the language i just decided that
                    movies[i].due = false;
                    movies_count--;
                }
                else 
                {
                    std::cerr << "Error in the movies array, please contact your IT provider";
                    break;
                }
                std::cout << "Movie : "<< movieName << " deleted successfully\n";
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
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return "admin";
        }
        else if(checkCredentials(login, passwrd) == "user")
        {
            std::cout << "Welcome, " << login << "!\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
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
    std::string movieName;
    double price, fee;
    do
    {
        std::cout << "Enter movie name: ";
        getline(std::cin, movieName);
        std::transform(movieName.begin(), movieName.end(), movieName.begin(), tolower);
        if(isMovieFound(movies,movies_count,movieName))
        {
            std::cout << "This film is already exist!\n";
            continue;
        }
        std::cout << "\nEnter movie price per day(EGP) : ";
        is_num(price);
        std::cout << "\nEnter due fees per day (EGP) : ";
        is_num(fee);
    } while(isMovieFound(movies,movies_count,movieName));
    
    for(int i = 0; i < size_of_movies; i++)
    {
        if(movies[i].name.empty())
        {
            movies[i].name = movieName;
            movies[i].price = price;
            movies[i].fee = fee;
            movies_count++;
            break;
        }
    }
    std::cout << "Successfully added: " << movieName << '\n';
}

bool ChangeDate(date::sys_days& new_date) // done
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
            if (entered_date == "0") return false; //aborts and exits to main menu
            
            std::istringstream iss(entered_date);
            if (iss >> y >> delimiter1 >> m >> delimiter2 >> d && y >= 2025 && delimiter1 == '/' && delimiter2 == '/') 
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
        return false; //aborting
    }
}
