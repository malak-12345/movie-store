#include "mainmenu.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <limits>
#include "admin.h"
#include "Howard_Hinnant/include/date/date.h"


void mainMenu(customer customers[], int size_of_customers, movie movies[], int size_of_movies)
{ 
    int customers_count = getCustomersCount(customers, size_of_customers);
    int movies_count = getMoviesCount(movies, size_of_movies);
    bool valid = false, isDateChanged = false;
    int choice;
    std::string check;
    
    date::sys_days new_date, today;
    auto now = std::chrono::system_clock::now();
    today = date::floor<date::days>(now);

    date::year_month_day system_date = today;
    
    std::string menu[] = {
        "\n-----------------------------\n",
        "press  1: Rent a movie",
        "press  2: Rate a movie",
        "press  3: Edit a rating",
        "press  4: Return a movie",
        "press  5: List all customers",
        "press  6: Add a customer",
        "press  7: List all movies",
        "press  8: List rented movies",
        "press  9: List unrented movies",
        "press  10: List due accounts",
        "press  11: List top 10 rented movies",
        "press  12: List top 10 rated movies"
    };
    
    check = login();
    while (check == "user" || check == "admin") //infinite loop till log out or termination
    {
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
        
        for(std::string menu : menu)
        {
            std::cout << menu << '\n';
        }
        
        if(check == "user")
        {
            std::cout << "press  13: Log out\n"; // done
        }
        else if (check == "admin") 
        {
            std::cout << "press  13: Add a movie\n"; // done
            std::cout << "press  14: Delete a movie\n"; // done
            std::cout << "press  15: Delete a customer\n"; // done
            std::cout << "press  16: set date manually\n"; // done
            std::cout << "press  17: switch user account\n"; // done
        }
        std::cout << "press  0: Exit\n";
        std::cout << "\nat any point in time, if you wish to go back to main menu enter \"0\"\n";
        std::cout << "-----------------------------\n";
        while (!valid) 
        {
            std::cin >> choice;
            if ((std::cin.good() && choice <= 13 && choice > -1) || (std::cin.good() && check == "admin" && choice <= 17 && choice > -1)) 
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

        switch (choice)
        {
        case 0: // exit
            return;
        case 1: // rent
            rent(customers, customers_count, movies, movies_count, system_date);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        case 2: // rate
        {
            std::string movieName,id;
            do
            {
                std::cout << "Enter movie name: ";
                getline(std::cin, movieName);
                std::transform(movieName.begin(), movieName.end(), movieName.begin(), tolower);
                
                if(!isMovieFound(movies,movies_count,movieName))
                {
                    std::cout << "This film doesn't exist! please try again.\n";
                }

            } while(!isMovieFound(movies,movies_count,movieName));

            do
            {
                std::cout << "Enter customer id: ";
                getline(std::cin, id);
                std::transform(id.begin(), id.end(), id.begin(), toupper); // c# ---> C#
                
                if(!isCustomerFound(customers,customers_count,id))
                {
                    std::cout << "Wrong ID! please try again.\n";
                }
            } while(!isCustomerFound(customers,customers_count,id));

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
                std::transform(movieName.begin(), movieName.end(), movieName.begin(), tolower);
                
                if(!isMovieFound(movies,movies_count,movieName))
                {
                    std::cout << "This film doesn't exist! please try again.\n";
                }
            } while(!isMovieFound(movies,movies_count,movieName));

            do
            {
                std::cout << "Enter customer id: ";
                getline(std::cin, id);
                std::transform(id.begin(), id.end(), id.begin(), toupper); // c# ---> C#
                
                if(!isCustomerFound(customers,customers_count,id))
                {
                    std::cout << "Wrong ID! please try again.\n";
                }
            } while(!isCustomerFound(customers,customers_count,id));

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
                
                if(!isCustomerFound(customers,customers_count,id))
                {
                    std::cout << "This customer doesn't exist! Please try again.\n";
                }
            } while(!isCustomerFound(customers,customers_count,id));
            returnMovie(customers,customers_count,id, movies, movies_count, isDateChanged, new_date);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        }            
        case 5: // list all customer
            listCustomers(customers, customers_count);
            break;
        case 6: // add new customer
            addNewCustomer(customers, size_of_customers, customers_count);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        case 7: // list all movies
            listMovies(movies, movies_count);
            break;
        case 8: // list rented
            listRented(movies, movies_count);
            break;
        case 9: // list unrented
            listUnrented(movies, movies_count);
            break;
        case 10: // list due accounts
            listDueAccounts(movies, movies_count, customers, customers_count, isDateChanged, new_date);
            break;
        case 11: // top 10 rented
            listTopRented(movies, movies_count);
            break;
        case 12: // top 10 rated
            listTopRated(movies, movies_count);
            break;
        case 13: // log out for user --- add new movie for admin.
        {
            if(check == "user")
            {
                check = login();
            }
            else if (check == "admin")
            {
                addNewMovie(movies, size_of_movies, movies_count);
                std::this_thread::sleep_for(std::chrono::seconds(t));
            }
            break;
        }
        case 14: // delete movie
        {
            std::string movieName;
            do
            {
                std::cout << "Enter movie name: ";
                getline(std::cin, movieName);
                std::transform(movieName.begin(), movieName.end(), movieName.begin(), tolower);
                
                if(!isMovieFound(movies,movies_count,movieName))
                {
                    std::cout << "This film doesn't exist! please try again.\n";
                }
            } while(!isMovieFound(movies, movies_count, movieName));
            
            deleteMovie(movies, movies_count, movieName);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        }
        case 15: // delete customer
        {
            std::string id;
            do
            {
                std::cout << "Enter customer id: ";
                getline(std::cin, id);
                std::transform(id.begin(), id.end(), id.begin(), toupper);
                
                if(!isCustomerFound(customers,customers_count,id))
                {
                    std::cout << "This customer doesn't exist! Please try again.\n";
                }
            } while(!isCustomerFound(customers,customers_count,id));
            
            deleteCustomer(customers, customers_count, id);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        }
        case 16:
            isDateChanged = ChangeDate(new_date);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        case 17: // logout for admin
            check = login();
            break;
        default:
            std::cerr << "Validation error in the main menu function, please contact your IT provider\nexiting program in 2 seconds";
            std::this_thread::sleep_for(std::chrono::seconds(t));
            return;
        }
        valid = false; //allows you to retake input from usr
    }
}
