#include "admin.h"
#include <iostream>

std::string ADMIN = "admin";
std::string ADMIN_PSSWRD = "admin"; // very safe ;)

std::string USER = "user";
std::string USER_PSSWRD = "user";

std::string checkCredentials(std::string& login, std::string& passwrd)
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

void deleteCustomer(Customer customers[], int size, std::string id)
{
    // Rahma
}

void deleteMovie(movie movies[], int size, std::string name)
{
    for(int i = 0; i<size; i++)
    {
        if(movies[i].Name == name)
        {
            movies[i].Name.clear();
            movies[i].CurrentRenter.clear();
            movies[i].AllRatings.clear();
            movies[i].rented = false;
            movies[i].price = 0;
            movies[i].fee = 0;
            movies[i].rating = 0;
            movies[i].RentedCount = 0;
            movies[i].DueDate.day = 0;
            movies[i].DueDate.month = 0;
            movies[i].DueDate.year = 0;
        }
        else
        {
            std::cout << "This film doesn't exist\n";
        }
    }
}

void login()
{
    std::string login, passwrd;
    do
    {
        std::cout << "Enter username: ";
        getline(std::cin, login);
        
        std::cout << "Enter password: ";
        getline(std::cin, passwrd);

        if(checkCredentials(login, passwrd) == "admin")
        {
            std::cout << "\nWelcome to admin control panel\n";
            // adminPanel(); ???
            // return "admin"; ??? for main menu?
        }
        else if(checkCredentials(login, passwrd) == "user")
        {
            std::cout << "Welcome, " << login << "!\n";
            // userPanel(); ???
            // return "user"; ??? for main menu?
        }
        else
        {
            std::cout << "Wrong password or username\n";
        }
    } while(checkCredentials(login, passwrd) == "");
}