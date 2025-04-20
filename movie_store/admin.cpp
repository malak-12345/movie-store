#include "admin.h"

std::string ADMIN = "admin";
std::string ADMIN_PSSWRD = "admin"; // very safe ;) __ i can see😂

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

void deleteMovie(movie movies[], int movies_count, std::string name)
{
    for(int i = 0; i< movies_count; i++)
    {
        if(movies[i].Name == name)
        {
            if (i < movies_count-1) {
                movies[i].Name = movies[movies_count - 1].Name;
                movies[i].CurrentRenter = movies[movies_count - 1].CurrentRenter;
                movies[i].AllRatings = movies[movies_count - 1].AllRatings;
                movies[i].rented = movies[movies_count - 1].rented;
                movies[i].price = movies[movies_count - 1].price;
                movies[i].fee = movies[movies_count - 1].fee;
                movies[i].rating = movies[movies_count - 1].rating;
                movies[i].RentedCount = movies[movies_count - 1].RentedCount;
                movies[i].DueDate = movies[movies_count - 1].DueDate;
                movies[i].due = movies[movies_count - 1].due;
                //----------------
                movies[movies_count - 1].Name.clear();
                movies[movies_count - 1].CurrentRenter.clear();
                movies[movies_count - 1].AllRatings.clear();
                movies[movies_count - 1].rented = false;
                movies[movies_count - 1].price = 0;
                movies[movies_count - 1].fee = 0;
                movies[movies_count - 1].rating = 0;
                movies[movies_count - 1].RentedCount = 0;
                movies[movies_count - 1].DueDate = date::year(1000) / date::month(10) / date::day(10);
                movies[movies_count - 1].due = false;
                movies_count--;
            }
            else if (i = movies_count - 1) {
                movies[i].Name.clear();
                movies[i].CurrentRenter.clear();
                movies[i].AllRatings.clear();
                movies[i].rented = false;
                movies[i].price = 0;
                movies[i].fee = 0;
                movies[i].rating = 0;
                movies[i].RentedCount = 0;
                movies[i].DueDate = date::year(1000) / date::month(10) / date::day(10); //default state for empty, not an actual thing in the language i just decided that
                movies[i].due = false;
                movies_count--;
            }
            else {
                std::cerr << "error in the movies array, please contact your IT provider";
            }
            break;
        }
    }
}

int login()
{
    std::string login, passwrd;
    do
    {
        std::cout << "Enter username: ";
        getline(std::cin, login);
        if (login == "0") return 0;
        
        std::cout << "Enter password: ";
        getline(std::cin, passwrd);
        if (passwrd == "0") return 0;
        
        if(checkCredentials(login, passwrd) == "admin")
        {
            std::cout << "Welcome, " << login << "!\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return 1;
        }
        else if(checkCredentials(login, passwrd) == "user")
        {
            std::cout << "Welcome, " << login << "!\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return 2;
        }
        else
        {
            std::cout << "Wrong password or username\n";
        }
    } while(checkCredentials(login, passwrd) == "");
}

void ChangeDate() {

}