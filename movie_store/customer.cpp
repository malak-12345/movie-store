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
std::string deleteSpaces(std::string str) //done
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
        if (!(customers[i].name.empty()))
        {
            customers_count++;
        }
    }
    return customers_count;
}
std::string isCurrentlyRentedAvailable(customer customers[], int customerIndex) // done
{
    int count = 0;
    for(std::string movie : customers[customerIndex].currentlyRentedMovies)
    {
        if(movie.empty()) count++;
    } 
    if (count == 0) return "full";
    else if (count == limit) return "empty";
    return "available";
}
bool file_empty(std::ifstream& file) 
{
    if (file.peek() == std::ifstream::traits_type::eof() || file.peek() == 0) 
    {
        return true; // peeks at first character without touching it, if it equals eof (aka file is empty/ u reached its end) it returns true
    }
    else 
    {
        return false;
    }
}//btw eof stands for end of file
int getCurrentlyRentedSize(customer customers[], int customerIndex) // done
{
    int count = 0;
    for(std::string movie : customers[customerIndex].currentlyRentedMovies)
    {
        if(!movie.empty()) count++;
    }
    return count;
}
int getMonthNum(std::string& mon) // done
{
    std::string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sept", "Oct", "Nov", "Dec"};
    int monthNum = 1;
    for (std::string mons : months)
    {
        if(mon == mons)
        {
            return monthNum;
        }
        monthNum++;
    }
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

        if(isCurrentlyRentedAvailable(customers, customerIndex) != "empty")
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
            std::cout << "Currently Renting: nothing\n";
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

            if(isCurrentlyRentedAvailable(customers, i) != "empty")
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
                std::cout << "Currently Renting: nothing\n";
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

void save_customers(customer customers[], int customers_count, const std::string& file_name) // done
{
    std::ofstream outfile(file_name);

    if (outfile.is_open()) 
    {
        outfile << customers_count << std::endl;
        for (int i = 0; i < customers_count; i++) 
        {
            outfile << customers[i].name << std::endl;
            outfile << customers[i].id << std::endl;
            outfile << customers[i].phoneNumber << std::endl;
            outfile << customers[i].coins << std::endl;
            outfile << std::boolalpha << customers[i].SC << std::endl;
            outfile << customers[i].SC_balance << std::endl;
            outfile << customers[i].SC_passwrd << std::endl;
            outfile << customers[i].creditcard.cardNumber << std::endl;
            outfile << customers[i].creditcard.ccv << std::endl;
            outfile << customers[i].creditcard.yy_mm << std::endl;
            //_________
            //Currently rented
            outfile << getCurrentlyRentedSize(customers,i) << std::endl; // very important!!!!!!!!
            outfile << "{" << std::endl;
            for (std::string movie : customers[i].currentlyRentedMovies)
            {
                if(!movie.empty()) outfile << movie << std::endl;
            }
            outfile << "}" << std::endl;
            //_________
            //Previously rented
            outfile << customers[i].previouslyRentedMovies.size() << std::endl;
            outfile << "{" << std::endl;
            for (std::string movie : customers[i].previouslyRentedMovies) 
            {
                outfile << movie << std::endl;
            }
            outfile << "}" << std::endl;
            //_________
            //Rating map
            outfile << customers[i].rating.size() << std::endl;
            outfile << "{" << std::endl;
            for (const auto& pair : customers[i].rating) 
            {
                outfile << pair.first << std::endl << pair.second << std::endl;
            }
            outfile << "}" << std::endl;
            //_________
        }
        outfile.close();
        std::cout << "Customers Data successfully saved" << std::endl;
    }
    else 
    {
        std::cerr << "Unable to open file " << file_name << "please try saving manually before terminating the program,\nif the problem persists please contact your IT provider" << std::endl;
    }
}

void load_customers(customer customers[], int& customers_count, const std::string& file_name) // done
{
    std::ifstream infile(file_name);
    if (infile.is_open()) 
    {
        if (file_empty(infile)) 
        {
            std::cerr << "no customer data to load\n";
            return;
        }
    
        infile >> customers_count; // customers_count
        infile.clear();
        infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (int i = 0; i < customers_count; i++)
        {
            std::getline(infile, customers[i].name);
            std::getline(infile, customers[i].id);
            std::getline(infile, customers[i].phoneNumber);
            infile >> customers[i].coins;
            infile.clear();
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            infile >> std::boolalpha >> customers[i].SC;
            infile.clear();
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            infile >> customers[i].SC_balance;
            infile.clear();
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::getline(infile, customers[i].SC_passwrd); // because SC_passwrd can be empty string so std::ws it will take previous value
            // std::cout << "password: " <<customers[i].SC_passwrd << '\n'; // test
            std::getline(infile, customers[i].creditcard.cardNumber);
            std::getline(infile, customers[i].creditcard.ccv);
            //_________
            // expiry date of credit card yy_mm
            std::string date_str, mon;
            int y;
            char delimiter;
            std::getline(infile, date_str);
            std::istringstream iss(date_str);
            
            if (iss >> y >> delimiter >> mon && delimiter == '/')
            {

                customers[i].creditcard.yy_mm = date::year(y) / date::month(getMonthNum(mon));
            }
            else
            {
                std::cerr << "wrong date format, while reading customer: " << customers[i].id << std::endl;
            }
            //_________
            // Currently rented
            int currentlyRentedMovies_size;
            infile >> currentlyRentedMovies_size;
            infile.clear();
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::string opening_brace2;
            if (std::getline(infile, opening_brace2) && opening_brace2 == "{") 
            {
                for (int j = 0; j < currentlyRentedMovies_size; j++)
                {
                    std::getline(infile, customers[i].currentlyRentedMovies[j]);
                }
                std::string closing_brace2;
                std::getline(infile, closing_brace2);
            }
            else 
            {
                std::cerr << "error taking in currently rented movies for customer: " << customers[i].id << std::endl;
            }
            //_________
            // Previously rented
            int previouslyRentedMovies_size;
            infile >> previouslyRentedMovies_size;
            infile.clear();
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::string opening_brace1;
            if (std::getline(infile, opening_brace1) && opening_brace1 == "{") 
            {
                for (int j = 0; j < previouslyRentedMovies_size; j++)
                {
                    std::getline(infile, customers[i].previouslyRentedMovies[j]); 
                }
                std::string closing_brace1;
                std::getline(infile, closing_brace1);
            }
            else 
            {
                std::cerr << "error taking in previouslyRentedMovies vector for customersomer: " << customers[i].id << std::endl;
            }
            //___________
            // Rating map
            int rating_size;
            infile >> rating_size;
            infile.clear();
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // very important!!!!!!!

            std::string opening_brace3;

            if (std::getline(infile, opening_brace3) && opening_brace3 == "{") 
            {
                for (int j = 0; j < rating_size; j++) 
                {
                    std::string key;
                    int value;
                    std::getline(infile, key);
                    
                    infile >> value;
                    infile.clear();
                    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    customers[i].rating[key] = value;
                }
                std::string closing_brace3;
                std::getline(infile, closing_brace3);
            }
            else 
            {
                std::cerr << "error taking in rating map for customer: " << customers[i].id << std::endl;
            }
        }
        infile.close();
        std::cout << "loaded customers successfully\n";
    }
    else 
    {
        std::cerr << "Unable to open file " << file_name << " for reading\n";
    }
}