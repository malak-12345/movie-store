#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "payment.h"
#include "movie.h"

bool validateCCV(std::string& ccv) // done
{
    if(ccv.length() < 5)
    {
        for(const char digit : ccv)
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
bool isDigit(std::string& str) // done
{
    for(const char& digit : str)
    {
        if(!std::isdigit(digit)) return false;
    }
    return true;
}

//Luhn algorithm
bool validateCreditCard(std::string& creditCard) // done
{
    if(isDigit(creditCard))
    {
        std::vector<int> creditCardNum;
        for(int i = 0; i < creditCard.length(); i++)
        {
            creditCardNum.push_back((creditCard[i] - '0')); // converts a char into int.
        }
        
        for(size_t i = creditCard.length() - 2; i >= 0; i -= 2)
        {
            int temp = creditCardNum[i];
            temp *= 2;
            if(temp > 9) temp = (temp % 10) + 1; // if its 10 or greater split it into two digits and add it ex(18) ---> 1 + 8 = 9.
            creditCardNum[i] = temp;
        }
    
        int total = 0;
    
        for(int num : creditCardNum)
        {
            total += num;
        }
    
        if(total % 10 == 0) return true;
    }

    return false;
}

bool isCreditCardRegistered(customer customers[], int customers_count, std::string& creditCard) // done
{
    for(int i = 0; i < customers_count; i++)
    {
        if(customers[i].creditcard.cardNumber == creditCard) return true;
    }
    return false;
}

void addCreditCard(customer customers[], int customers_count, std::string& id) // done
{
    int customerIndex = getCustomerIndex(customers, customers_count, id);
    std::string card, ccv, date;
    int y, m;
    char del;
    do
    {
        std::cout << "Enter your credit card number: ";
        getline(std::cin, card);
        card = deleteSpaces(card);

        if(!validateCreditCard(card))
        {
            std::cout << "Invalid credit card!\n";
            continue;
        }
        else if(isCreditCardRegistered(customers, customers_count, card))
        {
            std::cout << "This credit card is already registered!\n";
        }
    } while(!validateCreditCard(card) || isCreditCardRegistered(customers, customers_count, card));

    do
    {
        std::cout << "Enter CCV: ";
        getline(std::cin, ccv);
        ccv = deleteSpaces(ccv);
        
        if(!validateCCV(ccv)) 
        {
            std::cout << "Invalid CCV!\n";
        }
    } while(!validateCCV(ccv));

    do
    {
        std::cout << "Enter year/month: ";
        getline(std::cin, date);
        std::cin.clear();
        
        date = deleteSpaces(date);
        std::istringstream iss(date);
        if(iss >> y >> del >> m && (y >= 2025 || y >= 25) && (m > 0 && m <= 12) && (del == '/'))
        {   
            date = y + del + m;
        }
        else
        {
            std::cout << "Wrong date or format!\n";
        }
    } while((!(y >= 2025) || !(y >= 25)) || (!(m > 0) || !(m <= 12)) || (!(del == '/')));

    customers[customerIndex].creditcard.cardNumber = card;
    customers[customerIndex].creditcard.ccv = ccv;
    customers[customerIndex].creditcard.date = date;
    std::cout << "Successfully added credit card\n\n";
}

