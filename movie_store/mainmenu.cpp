#include "mainmenu.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>
#include <limits>
#include "admin.h"
#include "payment.h"

void displayMenu(std::string version, date::sys_days today, bool isDateChanged, date::sys_days new_date)
{ 
    std::string menu[] = {
        "\n-----------------------------\n",
        "press  1: Rent a movie",
        "press  2: Rate a movie",
        "press  3: Edit a rating",
        "press  4: Return a movie",
        "press  5: List all customers",
        "press  6: display a customer",
        "press  7: Add a customer",
        "press  8: List all movies",
        "press  9: List rented movies",
        "press  10: List unrented movies",
        "press  11: List due accounts",
        "press  12: List top 10 rented movies",
        "press  13: List top 10 rated movies"
    };

    if (isDateChanged)
    {
        using namespace date;
        std::cout << "\n\ncurrent date: " << new_date;
    }
    else 
    {
        using namespace date;
        std::cout << "\n\ncurrent date: " << today;
    }

    if(version == "admin") std::cout << "\n\n" << "Cash: "<< cashRegister << " EGP\n";
    for(std::string menu : menu)
    {
        std::cout << menu << '\n';
    }

    if(version == "user")
    {
        std::cout << "press  14: Log out\n"; // done
    }
    else if (version == "admin") 
    {
        std::cout << "press  14: Add a movie\n"; // done
        std::cout << "press  15: Delete a movie\n"; // done
        std::cout << "press  16: Delete a customer\n"; // done
        std::cout << "press  17: set date manually\n"; // done
        std::cout << "press  18: withdraw\n";
        std::cout << "press  19: switch user account\n"; // done
    }
    std::cout << "press  0: Exit\n";
    std::cout << "\nat any point in time, if you wish to go back to main menu enter \"0\"\n";
    std::cout << "-----------------------------\n";
}
int takeInput(std::string version)
{
    bool valid = false;
    int choice;
    while (!valid) 
    {
        std::cin >> choice;
        if ((std::cin.good() && choice <= 14 && choice > -1) || (std::cin.good() && version == "admin" && choice <= 19 && choice > -1)) 
        {
            valid = true;
        }
        else 
        {
            std::cerr << "Invalid choice. Please enter a valid choice: ";
            valid = false;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return choice;
}

void MainMenu(customer customers[], int size_of_customers, movie movies[], int size_of_movies)
{
    extern int customers_count;
    extern int movies_count;
    bool isDateChanged = false;
    std::string version;
    
    version = login();
    while(version == "user" || version == "admin")
    {
        displayMenu(version, today, isDateChanged, new_date);

        switch (takeInput(version))
        {
        case 0: // exit
            return;
        case 1: // rent
        {
            std::string id;
            do
            {
                std::cout << "Enter customer id: ";
                std::getline(std::cin, id);
                id = deleteSpaces(id);
                std::transform(id.begin(), id.end(), id.begin(), toupper); // c# ---> C#
                
                if (id == "0") break; //exit to main menu, note:the user will be notified at the begining of the program that entering 0 takes you back to main menu
                if (!isCustomerFound(customers, customers_count, id))
                {
                    std::cerr << "Wrong id, please try again\n";
                }
            } while (!isCustomerFound(customers, customers_count, id));
            if(id == "0") break;

            rent(customers, customers_count, movies, movies_count, system_date, isDateChanged, new_date, id);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        } 
        case 2: // rate
        {
            std::string movieName,id;
            do
            {
                std::cout << "Enter movie name: ";
                getline(std::cin, movieName);
                movieName = deleteSpaces(movieName);
                std::transform(movieName.begin(), movieName.end(), movieName.begin(), tolower);
                
                if(movieName == "0") break;
                if(!isMovieFound(movies,movies_count,movieName))
                {
                    std::cout << "This film doesn't exist! please try again.\n";
                }

            } while(!isMovieFound(movies,movies_count,movieName));
            if(movieName == "0") break;

            do
            {
                std::cout << "Enter customer id: ";
                getline(std::cin, id);
                id = deleteSpaces(id);
                std::transform(id.begin(), id.end(), id.begin(), toupper); // c# ---> C#
                
                if(id == "0") break;
                if(!isCustomerFound(customers,customers_count,id))
                {
                    std::cout << "Wrong ID! please try again.\n";
                }
            } while(!isCustomerFound(customers,customers_count,id));
            if(id == "0") break;

            bool done = rate(movies,movies_count,movieName, customers,customers_count,id);
            while (!done)
            {
                done = rate(movies,movies_count,movieName, customers,customers_count,id);
            }
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        }
        case 3: // edit rate
        {
            std::string movieName,id;
            do
            {
                std::cout << "Enter movie name: ";
                getline(std::cin, movieName);
                movieName = deleteSpaces(movieName);
                std::transform(movieName.begin(), movieName.end(), movieName.begin(), tolower);
                
                if(movieName == "0") break;
                if(!isMovieFound(movies,movies_count,movieName))
                {
                    std::cout << "This film doesn't exist! please try again.\n";
                }
            } while(!isMovieFound(movies,movies_count,movieName));
            if(movieName == "0") break;

            do
            {
                std::cout << "Enter customer id: ";
                getline(std::cin, id);
                id = deleteSpaces(id);
                std::transform(id.begin(), id.end(), id.begin(), toupper); // c# ---> C#
                
                if(id == "0") break;
                if(!isCustomerFound(customers,customers_count,id))
                {
                    std::cout << "Wrong ID! please try again.\n";
                }
            } while(!isCustomerFound(customers,customers_count,id));
            if(id == "0") break;

            bool done = editRating(movies,movies_count,movieName, customers,customers_count,id); 
            while(!done)
            {
                done = editRating(movies,movies_count,movieName, customers,customers_count,id);
            }
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        }
        case 4: // return a movie
        {
            std::string id;
            do
            {
                std::cout << "Enter customer id: ";
                getline(std::cin, id);
                std::transform(id.begin(), id.end(), id.begin(), toupper);
                
                if(id == "0") break;
                if(!isCustomerFound(customers,customers_count,id))
                {
                    std::cout << "This customer doesn't exist! Please try again.\n";
                }
            } while(!isCustomerFound(customers,customers_count,id));
            if(id == "0") break;
            returnMovie(cashRegister, customers, customers_count, id, movies, movies_count, isDateChanged, new_date);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        }            
        case 5: // list all customer
            listCustomers(customers, customers_count);
            break;
        case 6: // display a customer
        {
            std::string id;
            do
            {
                std::cout << "Enter customer id: ";
                getline(std::cin, id);
                id = deleteSpaces(id);
                std::transform(id.begin(), id.end(), id.begin(), toupper);
                
                if(id == "0") break;
                if(!isCustomerFound(customers,customers_count,id))
                {
                    std::cout << "This customer doesn't exist! Please try again.\n";
                }
            } while(!isCustomerFound(customers,customers_count,id));
            if(id == "0") break;
            
            int customerIndex = getCustomerIndex(customers, customers_count, id);
            displayCustomer(customers, customers_count, customerIndex);
            break;
        }    
        case 7: // add new customer
            addNewCustomer(customers, size_of_customers, customers_count);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        case 8: // list all movies
            listMovies(movies, movies_count);
            break;
        case 9: // list rented
            listRented(movies, movies_count);
            break;
        case 10: // list unrented
            listUnrented(movies, movies_count);
            break;
        case 11: // list due accounts
            listDueAccounts(movies, movies_count, customers, customers_count, isDateChanged, new_date);
            break;
        case 12: // top 10 rented
            listTopRented(movies, movies_count);
            break;
        case 13: // top 10 rated
            listTopRated(movies, movies_count);
            break;
        case 14: // log out for user --- add new movie for admin.
        {
            if(version == "user")
            {
                version = login();
            }
            else if (version == "admin")
            {
                addNewMovie(movies, size_of_movies, movies_count);
                std::this_thread::sleep_for(std::chrono::seconds(t));
            }
            break;
        }
        case 15: // delete movie
        {
            std::string movieName;
            do
            {
                std::cout << "Enter movie name: ";
                getline(std::cin, movieName);
                movieName = deleteSpaces(movieName);
                std::transform(movieName.begin(), movieName.end(), movieName.begin(), tolower);
                
                if(movieName == "0") break;
                if(!isMovieFound(movies,movies_count,movieName))
                {
                    std::cout << "This film doesn't exist! please try again.\n";
                }
            } while(!isMovieFound(movies, movies_count, movieName));
            if(movieName == "0") break;
            
            deleteMovie(movies, movies_count, movieName);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        }
        case 16: // delete customer
        {
            std::string id;
            do
            {
                std::cout << "Enter customer id: ";
                getline(std::cin, id);
                id = deleteSpaces(id);
                std::transform(id.begin(), id.end(), id.begin(), toupper);
                
                if(id == "0") break;
                if(!isCustomerFound(customers,customers_count,id))
                {
                    std::cout << "This customer doesn't exist! Please try again.\n";
                }
            } while(!isCustomerFound(customers,customers_count,id));
            if(id == "0") break;
            
            deleteCustomer(customers, customers_count, id);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        }
        case 17: // change date
            isDateChanged = ChangeDate(new_date);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        case 18: // withdraw
        {
            double amount;
            do
            {
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amount;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                if(amount == 0) break;
                if(amount > cashRegister) std::cout << "Not enough balance! Please try again.\n";
            } while(amount > cashRegister);
            if(amount == 0) break;
            
            std::this_thread::sleep_for(std::chrono::seconds(t));
            cashRegister -= amount;
            std::cout << "Successfully withdrawn: " << amount << " EGP\n";
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        }
        case 19: // logout for admin
            version = login();
            break;
        default:
            std::cerr << "Validation error in the main menu function, please contact your IT provider\nexiting program in 2 seconds"; //TODO: Change Line.
            std::this_thread::sleep_for(std::chrono::seconds(t));
            return;
        }
    }
}
