#include "customer.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

//-------------------------utilities-----------------------------
std::string generateId() // done
{
    std::string id = "C#";
    srand(time(0)); // changes seed
    for (int i = 1; i <= 4; i++)
    {
        id += std::to_string(rand() % 10); // generates number from 0 -> 9 and adds it
    }
    return id;
}
std::string deleteSpaces(std::string& str) //done
{
    str.erase(remove(str.begin(),str.end(), ' '), str.end());
    return str;
}
bool checkPhoneNumber(std::string& phoneNumber) // done
{
    if (phoneNumber.length() >= 7 && phoneNumber.length() <= 15)
    {
        for(const char& digit : phoneNumber)
        {
            if(!std::isdigit(digit)) return false;
        }
        return true;
    }
    else
    {
        return false;
    }
}
bool checkPhoneNumberRegistered(customer customers[], int customers_count, std::string& phoneNumber) // done
{
    for(int i = 0; i < customers_count; i++)
    {
        if((customers[i].phoneNumber == phoneNumber))
        {
            return true;
        }
    }
    return false;
}
bool checkId(customer customers[], int customer_count, std::string& id) // done
{
    for(int i = 0; i < customer_count; i++)
    {
        if(customers[i].id == id)
        {
            return true;
        }
    }
    return false;
}
int getCustomersCount(customer customers[], int size_of_customers) // get customers count at the beginning of the program
{
    int customers_count = 0;
    for(int i = 0; i < size_of_customers; i++)
    {
        if(!(deleteSpaces(customers[i].name).empty()))
        {
            customers_count++;
        }
    }
    return customers_count;
}
bool isCurrentlyRentedEmpty(customer customers[], int customerIndex) // done
{
    int count = 0;
    for(int i = 0; i < limit; i++)
    {
        if(customers[customerIndex].currentlyRentedMovies[i].empty()) count++; 
    } 
    if(count == limit)
    {
        return true;
    }
    return false;
}
//---------------------------------------------------------------

void addNewCustomer(customer customers[], int size_of_customers, int& customers_count) // done
{
    std::string name, phoneNumber, id;
    do
    {
        std::cout << "Enter Customer name: ";
        getline(std::cin, name);
        if(deleteSpaces(name).empty()) std::cout << "Invalid name!\n";
        
    }while(deleteSpaces(name).empty());
    if(name == "0") return;
    
    do 
    {
        std::cout << "Enter Customer phone: +";
        getline(std::cin, phoneNumber);
        phoneNumber = deleteSpaces(phoneNumber);
        if(phoneNumber == "0") return;
        if(!checkPhoneNumber(phoneNumber))
        {
            std::cout << "Invalid phone number!\n";
            continue;
        }
        else if (checkPhoneNumberRegistered(customers, customers_count, phoneNumber))
        {
            std::cout << "This phone number is already registered!\n";
        }
    } while(!checkPhoneNumber(phoneNumber) || checkPhoneNumberRegistered(customers, customers_count, phoneNumber));
    
    do
    {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // ---> sleep for 1 sec.
        id = generateId();

    } while(checkId(customers, customers_count, id));


    for(int i = 0; i < size_of_customers; i++)
    {
        if(customers[i].name.empty())
        {
            customers[i].name = name;
            customers[i].phoneNumber = phoneNumber;
            customers[i].id = id;
            customers_count++;
            break;
        }   
    }
    std::cout << "Successfully added: " << name << '\n';
}
void displayCustomer(customer customers[], int customers_count, int customerIndex) // done
{
    if(customers_count != 0)
    {
        std::cout << "\n-----------------------------\n\n";
        std::cout << "Name: " << customers[customerIndex].name << '\n';
        std::cout << "Customer ID: " << customers[customerIndex].id << '\n';
        std::cout << "Phone Number: " << customers[customerIndex].phoneNumber << '\n';

        if(!isCurrentlyRentedEmpty(customers, customerIndex))
            {
                std::cout << "Currently Renting: ";
                for (std::string movie : customers[customerIndex].currentlyRentedMovies)
                {
                    if (!movie.empty()) 
                    { 
                        std::cout << movie << " ";
                    }
                }
            }
            else
            {
                std::cout << "Currently Renting: none\n";
            }
            std::cout << "\n";
    
            if (!customers[customerIndex].previouslyRentedMovies.size() == 0)
            {
                std::cout << "Has rented: ";
    
                for (std::string movie : customers[customerIndex].previouslyRentedMovies)
                {
                    std::cout << movie << " ";
                }
                std::cout << '\n';
            }
            std::cout << "\n-----------------------------\n\n";
    }
    else
    {
        std::cout << "There are currently no customers on the system! Please add a customer first.\n";
    }
}
void listCustomers(customer customers[], int customers_count) // done
{
    if(customers_count != 0)
    {
        int num = 1;
        std::cout << "\n-----------------------------\n\n";
        for (int i = 0; i < customers_count; i++)
        {
            std::cout << num << ".\n";
            std::cout << "Name: " << customers[i].name << '\n';
            std::cout << "Customer ID: " << customers[i].id << '\n';
            std::cout << "Phone Number: +" << customers[i].phoneNumber << '\n';

            if(!isCurrentlyRentedEmpty(customers, i))
            {
                std::cout << "Currently Renting: ";
                for (std::string movie : customers[i].currentlyRentedMovies)
                {
                    if (!movie.empty()) 
                    { 
                        std::cout << movie << " ";
                    }
                }
            }
            else
            {
                std::cout << "Currently Renting: none\n";
            }
            std::cout << "\n";
    
            if (!customers[i].previouslyRentedMovies.size() == 0)
            {
                std::cout << "Has rented: ";
    
                for (std::string movie : customers[i].previouslyRentedMovies)
                {
                    std::cout << movie << " ";
                }
                std::cout << "\n";
            }
            std::cout << "\n";
            num++;
        }
        std::cout << "-----------------------------\n";
    }
    else
    {
        std::cout << "There are currently no customers on the system! Please add a customer first.\n";
    }
}
