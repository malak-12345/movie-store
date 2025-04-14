#include "customer.h"
#include <iostream>
#include <algorithm>

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

std::string deleteSpaces(std::string str)
{
    str.erase(remove(str.begin(),str.end(), ' '), str.end());
    return str;
}

bool checkPhoneNumber(std::string PhoneNumber)
{
    char digits[10] = {'0','1','2','3','4','5','6','7','8','9'};

    PhoneNumber = deleteSpaces(PhoneNumber);
    // std::cout << PhoneNumber << '\n';
    // std::cout << PhoneNumber.length() << '\n';

    if(PhoneNumber.length()>=5 && PhoneNumber.length()<=15)
    {
        for(int i=0; i<PhoneNumber.length(); i++)
        {
            bool isDigit = false;
            
            // std::cout << "Outer loop:" << PhoneNumber[i] << '\n';
            // std::cout << sizeof(PhoneNumber[i]) << '\n';
            
            for(int j=0; j<10; j++)
            {
                // std::cout << "i: " << i << "j: " << j << '\n';
                if(PhoneNumber[i] == digits[j])
                {
                    // std::cout << "Inner loop:" << digits[j] << '\n';
                    isDigit = true;
                    break;
                }
            }
        
            if(!isDigit)
            {
                // std::cout << "not a digit\n";
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
  
}

void addNewCustomer()
{
    
}