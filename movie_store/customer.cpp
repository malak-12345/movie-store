#include "customer.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <fstream>
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
    for (int i = 0; i < size_of_customers; i++)
    {
        if (customers[i].name != "none")
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


void save_customers(customer cust[], int cust_count, const std::string& file_name) {
    std::ofstream outfile(file_name);

    if (outfile.is_open()) {
        outfile << cust_count << std::endl;
        for (int i = 0; i < cust_count; i++) {
            outfile << cust[i].id << std::endl;
            outfile << cust[i].name << std::endl;
            outfile << cust[i].phoneNumber << std::endl;
            outfile << cust[i].coins << std::endl;
            outfile << std::boolalpha << cust[i].SC << std::endl;
            outfile << cust[i].SC_balance << std::endl;
            outfile << cust[i].SC_passwrd << std::endl;
            outfile << cust[i].creditcard.cardNumber << std::endl;
            outfile << cust[i].creditcard.ccv << std::endl;
            outfile << cust[i].creditcard.yy_mm << std::endl;
            //_________
            outfile << cust[i].previouslyRentedMovies.size() << std::endl;
            outfile << "{" << std::endl;
            for (std::string movie : cust[i].previouslyRentedMovies) {
                outfile << movie << std::endl;
            }
            outfile << "}" << std::endl;
            //__________
            outfile << "{" << std::endl;
            for (int j = 0; j < 8; j++) {
                outfile << cust[i].currentlyRentedMovies[j] << std::endl;
            }
            outfile << "}" << std::endl;
            //__________

            outfile << cust[i].rating.size() << std::endl;
            outfile << "{" << std::endl;
            for (const auto& pair : cust[i].rating) {
                outfile << pair.first << " " << pair.second << "\n";
            }
            outfile << "}" << std::endl;
            //__________
        }
        outfile.close();
        std::cout << "Data successfully saved" << std::endl;
    }
    else {
        std::cerr << "Unable to open file " << file_name << "please try saving manually before terminating the program,\nif the problem persists please contact your IT provider" << std::endl;
    }
}



void load_customers(customer cust[], int cust_count, const std::string& file_name) {
    std::ifstream infile(file_name);
    if (infile.is_open()) {
        infile >> cust_count;
        for (int i = 0; i < cust_count; i++) {
            std::getline(infile >> std::ws, cust[i].id);
            std::getline(infile >> std::ws, cust[i].name);
            std::getline(infile >> std::ws, cust[i].phoneNumber);
            infile >> cust[i].coins;
            infile >> std::boolalpha >> cust[i].SC;
            infile >> cust[i].SC_balance;
            std::getline(infile >> std::ws, cust[i].SC_passwrd);
            std::getline(infile >> std::ws, cust[i].creditcard.cardNumber);
            std::getline(infile >> std::ws, cust[i].creditcard.ccv);
            //________________________
            std::string date_str;
            int y, m, d;
            char delimiter1, delimiter2;
            infile >> date_str;
            std::istringstream iss(date_str);
            if (iss >> y >> delimiter1 >> m >> delimiter2 >> d && delimiter1 == '-' && delimiter2 == '-')
            {
                cust[i].creditcard.yy_mm = date::year(y) / date::month(m) / date::day(d);
            }
            else
            {
                std::cerr << "wrong date format, while reading customer: " << cust[i].id << std::endl;
            }
            //__________________________
            int previouslyRentedMovies_size;
            infile >> previouslyRentedMovies_size;
            cust[i].previouslyRentedMovies.resize(previouslyRentedMovies_size);
            std::string opening_brace1;
            if (std::getline(infile >> std::ws, opening_brace1) && opening_brace1 == "{") {
                for (int j = 0; j < previouslyRentedMovies_size; j++) {
                    std::getline(infile >> std::ws, cust[i].previouslyRentedMovies[j]);
                }
                std::string closing_brace1;
                std::getline(infile >> std::ws, closing_brace1);
            }
            else {
                std::cerr << "error taking in previouslyRentedMovies vector for customer: " << cust[i].id << std::endl;
            }
            //___________
            std::string opening_brace2;
            if (std::getline(infile >> std::ws, opening_brace2) && opening_brace2 == "{") {
                for (int j = 0; j < 8; j++) {
                    std::getline(infile >> std::ws, cust[i].currentlyRentedMovies[j]);
                }
                std::string closing_brace2;
                std::getline(infile >> std::ws, closing_brace2);
            }
            else {
                std::cerr << "error taking in currently rented movies for customer: " << cust[i].id << std::endl;
            }
            //___________

            int rating_size;
            infile >> rating_size;
            std::string opening_brace3;
            std::string key;
            int value;
            if (std::getline(infile >> std::ws, opening_brace3) && opening_brace3 == "{") {
                for (int j = 0; j < rating_size; j++) {
                    infile >> key >> value;
                }
                std::string closing_brace3;
                std::getline(infile >> std::ws, closing_brace3);
            }
            else {
                std::cerr << "error taking in rating map for customer: " << cust[i].id << std::endl;
            }
        }
        infile.close();
    }
    else {
        std::cerr << "Unable to open file " << file_name << " for reading, contact your IT provider" << std::endl;
    }
}