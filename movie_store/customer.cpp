#include "customer.h"

//-------------------------utilities-----------------------------
std::string generateId()
{
    std::string Id = "C#";
    srand(time(0)); // changes seed
    for (int i =1; i<=4; i++)
    {
        Id+= std::to_string(rand()%10); // generates number from 0 -> 9 and adds it
    }
    return Id;
}
std::string deleteSpaces(std::string& str)
{
    str.erase(remove(str.begin(),str.end(), ' '), str.end());
    return str;
}
bool checkPhoneNumber(std::string& PhoneNumber)
{
    PhoneNumber = deleteSpaces(PhoneNumber);
    // std::cout << PhoneNumber.length() << '\n';
    
    if (PhoneNumber.length() >= 7 && PhoneNumber.length() <= 15)
    {
        for(const char& i : PhoneNumber) //int i=0; i<PhoneNumber.length(); i++
        {
            if(!std::isdigit(i))
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}
bool checkId(std::string& id, Customer c[], int size)
{
    for(int i=0; i<size; i++)
    {
        if(c[i].Id == id)
        {
            return false;
        }
    }
    return true;
}
//-------------------------utilities-----------------------------


void addNewCustomer(Customer customers[], int number_of_customers){
    std::string name, phonenum, id;
    std::cout << "Enter Customer name: ";
    getline(std::cin, name);
    std::transform(name.begin(), name.end(), name.begin(), tolower);
    
    do 
    {
        std::cout << "Enter Customer phone: +";
        getline(std::cin, phonenum);
        
        if(!checkPhoneNumber(phonenum))
        {
            std::cout << "Invalid phone number!\n";
        }

    } while(!checkPhoneNumber(phonenum));
    
    do
    {
        id = generateId();
        std::this_thread::sleep_for(std::chrono::seconds(1)); // --->sleep for 1 sec.

    } while(!checkId(id, customers, number_of_customers));


    for(int i=0; i< number_of_customers; i++){
        if(customers[i].Name.empty())
        {
            customers[i].Name = name;
            customers[i].PhoneNumber = phonenum;
            customers[i].Id = id;
            break;
        }   
    }

    // for(int j=0; j<size; j++)
    // {
    //     if(!c[j].Name.empty())
    //     {
    //         std::cout << c[j].Name << '\n';
    //         std::cout << c[j].PhoneNumber << '\n';
    //         std::cout << c[j].Id << '\n';
    //     }
    // }
}
void listCustomers(Customer customers[], int number_of_customers)
{
    int num = 1;
    for (int i = 0; i < number_of_customers; i++)
    {
        if(!customers[i].Name.empty())
        {

            std::cout << "\n-----------------------------\n";
            std::cout << num << ".\n";
            std::cout << "Customer ID: " << customers[i].Id << '\n';
            std::cout << "Name: " << customers[i].Name << '\n';
            std::cout << "Phone Number: " << customers[i].PhoneNumber << '\n';
    
            if (!customers[i].CurrentlyRentedMovies[0].empty())
            {
                std::cout << "Currently Renting: ";
                for (int j = 0; j < limit; j++)
                {
                    if (customers[i].CurrentlyRentedMovies[j].empty()) { std::cout << "."; break; }
                    if (j > 0) { std::cout << ", "; }
                    std::cout << customers[i].CurrentlyRentedMovies[j];
                }
                std::cout << "\n";
            }
            else 
            {
                std::cout << "Currently Renting: none\n";
            }
    
            if (!customers[i].PreviouslyRentedMovies.size() == 0)
            {
                std::cout << "has rented: ";
    
                for (std::string j : customers[i].PreviouslyRentedMovies)
                {
                    if (j.empty()) { std::cout << "."; break; }
                    std::cout << '\n';
                    std::cout << j;
                }
                std::cout << "\n";
            }
            else 
            {
                std::cout << "hasn't rented any movies yet" << std::endl;
            }
            num++;
            std::cout << "-----------------------------\n";
        }
    }
    if (num==1)
    {
        std::cout << "There are no customers! Please add.\n";
    }
}

