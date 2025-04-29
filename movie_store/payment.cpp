#include "payment.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

std::string deleteSpaces(std::string& str)
{
    str.erase(remove(str.begin(),str.end(), ' '), str.end());
    return str;
}


//Luhn algorithm
bool validateCreditCard(std::string creditCard)
{
    creditCard = deleteSpaces(creditCard);
    
    std::vector<int> creditCardNum;
    
    for(int i = 0; i < creditCard.length(); i++)
    {
        creditCardNum.push_back((creditCard[i] - '0')); // converts a char into int.
    }
    
    for(int i = creditCard.length() - 2; i >= 0; i -= 2)
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
    
    return false;
}

bool validateCCV(std::string ccv)
{
    ccv = deleteSpaces(ccv);
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
