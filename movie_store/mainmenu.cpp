#include "mainmenu.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>
#include <limits>
#include "admin.h" // contains system_date, cashRegister
#include "payment.h"
using namespace date;

int customers_count;
int movies_count;

void displayMenu(std::string version)
{ 
    std::string menu[] = {
        "\n-----------------------------\n",
        "press  1:  Rent a movie",
        "press  2:  Rate a movie",
        "press  3:  Edit a rating",
        "press  4:  Return a movie",
        "press  5:  List all customers",
        "press  6:  display a customer",
        "press  7:  Add a customer",
        "press  8:  List all movies",
        "press  9:  List rented movies",
        "press  10: List unrented movies",
        "press  11: List due accounts",
        "press  12: List top 10 rented movies",
        "press  13: List top 10 rated movies",
        "press  14: Add a movie",
        "press  15: Payment options"
    };
    std::cout << "\n\ncurrent date: " << system_date;

    if(version == "admin") std::cout << "\n\n" << "Cash: "<< cashRegister << " EGP\n";
    for(std::string menu : menu)
    {
        std::cout << menu << '\n';
    }

    if(version == "user")
    {
        std::cout << "press  16: Log out\n"; // done
    }
    else if (version == "admin") 
    {
        std::cout << "press  16: Delete a movie\n"; // done
        std::cout << "press  17: Delete a customer\n"; // done
        std::cout << "press  18: set date manually\n"; // done
        std::cout << "press  19: withdraw\n"; // done
        std::cout << "press  20: switch user account\n"; // done
    }
    std::cout << "press  0:  Exit\n";
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
        if ((std::cin.good() && choice < 17 && choice > -1) || (std::cin.good() && version == "admin" && choice < 21 && choice > -1)) 
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
    std::string version;
    
    version = login();
    while(version == "user" || version == "admin")
    {
        displayMenu(version);

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
                std::transform(id.begin(), id.end(), id.begin(), toupper); // c# ---> C

                if (id == "0") break;   
                if (!isCustomerFound(customers, customers_count, id))
                {
                    std::cerr << "Wrong id, please try again\n";
                }
            } while (!isCustomerFound(customers, customers_count, id));
            if(id == "0")
            {
                std::cout << "Returning to main menu!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
                break;
            }
            rent(customers, customers_count, movies, movies_count, id);
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
            if(movieName == "0") 
            {
                std::cout << "Returning to main menu!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
                break;
            }

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
            if(id == "0")
            {
                std::cout << "Returning to main menu!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
                break;
            }

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
            if(movieName == "0")
            {
                std::cout << "Returning to main menu!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
                break;
            }

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
            if(id == "0")
            {
                std::cout << "Returning to main menu!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
                break;
            }

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
                id = deleteSpaces(id);
                std::transform(id.begin(), id.end(), id.begin(), toupper);
                
                if(id == "0") break;
                if(!isCustomerFound(customers,customers_count,id))
                {
                    std::cout << "This customer doesn't exist! Please try again.\n";
                }
            } while(!isCustomerFound(customers,customers_count,id));
            if(id == "0")
            {
                std::cout << "Returning to main menu!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
                break;
            }
            
            returnMovie(cashRegister, customers, customers_count, id, movies, movies_count);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        }            
        case 5: // list all customer
            listCustomers(customers, customers_count);
            std::this_thread::sleep_for(std::chrono::seconds(t));
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
            if(id == "0")
            {
                std::cout << "Returning to main menu!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
                break;
            }
            
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
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        case 9: // list rented
            listRented(movies, movies_count);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        case 10: // list unrented
            listUnrented(movies, movies_count);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        case 11: // list due accounts
            listDueAccounts(movies, movies_count, customers, customers_count);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        case 12: // top 10 rented
            listTopRented(movies, movies_count);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        case 13: // top 10 rated
            listTopRated(movies, movies_count);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        case 14: //add new movie
        {   
            addNewMovie(movies, size_of_movies,movies_count);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        }
        case 15: // payment options
        {
            int choice;
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
            if(id == "0")
            {
                std::cout << "Returning to main menu!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
                break;
            }
            int customerIndex = getCustomerIndex(customers, customers_count, id);
            
            do
            {
                std::cout << "1. Add credit card\n"
                          << "2. Create SC\n"
                          << "3. Reset SC password\n\n";
                std::cout << "Enter choice: ";
                is_num(choice);
                switch (choice)
                {
                case 0:
                    std::cout << "Returning to main menu!\n";
                    std::this_thread::sleep_for(std::chrono::seconds(t));
                    break;
                case 1:
                {
                    if(customers[customerIndex].creditcard.cardNumber.empty())
                    {
                        addCreditCard(customers, customers_count, id);
                    }
                    else
                    {
                        std::cout << "this customer already has a credit card!\n";
                    }
                    break;
                }
                case 2:
                {
                    if(!customers[customerIndex].SC)
                    {
                        create_SC(customers, customers_count, id);
                    }
                    else
                    {
                        std::cout << "this customer already has a SC!\n";
                    }
                    break;
                }
                case 3:
                {
                    if(customers[customerIndex].SC)
                    {
                        reset_SC_passwrd(customers, customers_count, id);
                    }
                    else
                    {
                        std::cout << "this customer doesn't have a SC!\n";
                    }
                    break;
                }
                default:
                    std::cout << "Invalid choice!\n\n";
                    break;
                }
            } while(choice > 3 || choice <= -1);
            break;
        }
        case 16: // delete movie for admin --- log out for user
        {
            if (version == "user")
            {
                version = login();
            }
            else if (version == "admin")
            {
                std::string movieName;
                do
                {
                    std::cout << "Enter movie name: ";
                    getline(std::cin, movieName);
                    movieName = deleteSpaces(movieName);
                    std::transform(movieName.begin(), movieName.end(), movieName.begin(), tolower);

                    if (movieName == "0") break;
                    if (!isMovieFound(movies, movies_count, movieName))
                    {
                        std::cout << "This film doesn't exist! please try again.\n";
                    }
                } while (!isMovieFound(movies, movies_count, movieName));
                if (movieName == "0")
                {
                    std::cout << "Returning to main menu!\n";
                    std::this_thread::sleep_for(std::chrono::seconds(t));
                    break;
                }

                deleteMovie(movies, movies_count, movieName, customers, customers_count);
                std::this_thread::sleep_for(std::chrono::seconds(t));
            }
            break;
        }
        case 17: // delete customer
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
            if(id == "0")
            {
                std::cout << "Returning to main menu!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
                break;
            }
            
            deleteCustomer(customers, customers_count, id);
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        }
        case 18: // change date
            ChangeDate();
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        case 19: // withdraw
        {
            double amount;
            do
            {
                std::cout << "Enter amount to withdraw: ";
                is_num(amount);                
                if(amount == 0) break;
                if(amount > cashRegister) std::cout << "Not enough balance! Please try again.\n";
            } while(amount > cashRegister);
            if(amount == 0)
            {
                std::cout << "Returning to main menu!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
                break;
            }
            
            std::this_thread::sleep_for(std::chrono::seconds(t));
            cashRegister -= amount;
            std::cout << "Successfully withdrawn: " << amount << " EGP\n";
            std::this_thread::sleep_for(std::chrono::seconds(t));
            break;
        }
        case 20: // logout for admin
            version = login();
            break;
        default:
            std::cerr << "Validation error in the main menu function, please contact your IT provider\nexiting program in 2 seconds"; //TODO: Change Line.
            std::this_thread::sleep_for(std::chrono::seconds(t));
            return;
        }
    }
}
