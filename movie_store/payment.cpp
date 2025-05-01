#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <thread>
#include <chrono>
#include <iomanip>
#include "payment.h"
#include "movie.h"
#include "Howard_Hinnant/include/date/date.h"



bool isDigit(std::string& str) // done
{
    for(const char& digit : str)
    {
        if(!std::isdigit(digit)) return false;
    }
    return true;
}

bool validateCCV(std::string& ccv) // done
{
    if(ccv.length() < 5 && ccv.length() > 2)
    {
        for(const char digit : ccv)
        {
            if(!std::isdigit(digit)) return false;
        }
        return true;
    }
    
    return false;
} 

//Luhn algorithm
bool validateCreditCard(std::string& creditCard) // done
{
    if(isDigit(creditCard) && ((creditCard.length() == 15) || (creditCard.length() == 16))) 
    {
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
    }

    return false;
}

bool isCreditCardRegistered(customer customers[], int customers_count, std::string& creditCard) // done
{
    if(!creditCard.empty())
    {
        for(int i = 0; i < customers_count; i++)
        {
            if(customers[i].creditcard.cardNumber == creditCard) return true;
        }
    }
    return false;
}

void addCreditCard(customer customers[], int customers_count, std::string& id) // done
{
    int customerIndex = getCustomerIndex(customers, customers_count, id);
    std::string card, ccv, date;
    do
    {
        std::cout << "Enter your credit card number: ";
        getline(std::cin, card);
        std::cin.clear();
        card = deleteSpaces(card);

        if(card == "0") return;
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
        std::cin.clear();
        ccv = deleteSpaces(ccv);
        
        if(ccv == "0") return;
        if(!validateCCV(ccv)) 
        {
            std::cout << "Invalid CCV!\n";
        }
    } while(!validateCCV(ccv));

    date::sys_days today;
    auto now = std::chrono::system_clock::now();
    today = date::floor<date::days>(now);
    date::year_month_day system_date = today;

    date::year y;
    date::month m;
    date::year_month yy_mm;
    int y_val, m_val;
    char del;
    bool valid = false;
    while(!valid)
    {
        std::cout << "Enter expiry date: year/month: ";
        getline(std::cin, date);
        std::cin.clear();
        date = deleteSpaces(date);

        if(date == "0") return;

        std::istringstream iss(date);
        if(iss >> std::setw(2) >> y_val >> del >> std::setw(2) >> m_val && (del == '/'))
        {
            y = date::year(y_val);
            y += date::years(2000);
            m = date::month(m_val);
            if(m.ok())
            {
                yy_mm = y / m;
            }
            else
            {
                std::cout << "Wrong date or format!\n";
                valid = false;
                continue;
            }
        }
        else
        {
            std::cout << "Wrong date or format!\n";
            valid = false;
            continue;
        }
        
        if(yy_mm.year() >= system_date.year())
        {
            std::cout << yy_mm << '\n';
            valid = true;
        }
        else
        {
            std::cout << "Wrong date!\n";
            valid = false;
        }
    }

    customers[customerIndex].creditcard.cardNumber = card;
    customers[customerIndex].creditcard.ccv = ccv;
    customers[customerIndex].creditcard.yy_mm = yy_mm;
    std::cout << "Successfully added credit card\n\n";
}

bool pay(customer customers[], int customers_count, std::string& id)
{
    int customerIndex = getCustomerIndex(customers, customers_count, id);
    int ans;
    std::string ccv, date;
    std::cout << "1. cash\n2. credit card\n";
    do
    {
        is_num(ans);
        if(ans == 0) return false;
        if(ans == 1)
        {
            std::cout << "Opening cash register!\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        else if(ans == 2)
        {
            if(!customers[customerIndex].creditcard.cardNumber.empty())
            {
                std::cout << "Paying with: " << customers[customerIndex].creditcard.cardNumber << '\n';
                do
                {
                    std::cout << "Enter ccv: ";
                    getline(std::cin, ccv);
                    std::cin.clear();
                    ccv = deleteSpaces(ccv);
                    
                    if(ccv == "0") return false; // exiting to main menu
                    if(customers[customerIndex].creditcard.ccv != ccv)
                    {
                        std::cout << "Wrong ccv!\n";
                    }
                } while(customers[customerIndex].creditcard.ccv != ccv);
                
                date::year_month yy_mm;
                date::year y;
                date::month m;
                int y_val, m_val;
                char del;
                do
                {
                    std::cout << "Enter expiry date: year/month: ";
                    
                    getline(std::cin, date);
                    std::cin.clear();
                    date = deleteSpaces(date);

                    if(ccv == "0") return false;
                    
                    std::istringstream iss(date);
                    if(iss >> std::setw(2) >> y_val >> del >> std::setw(2) >> m_val && del=='/')
                    {
                        y = date::year(y_val);
                        y += date::years(2000);
                        m = date::month(m_val);
                        if(m.ok())
                        {
                            yy_mm = y / m;
                            if(yy_mm == customers[customerIndex].creditcard.yy_mm)
                            {
                                std::cout << "Transaction completed!\n\n";
                            }
                        }
                        else
                        {
                            std::cout << "Wrong date or format!\n";
                        }
                    }
                } while(yy_mm != customers[customerIndex].creditcard.yy_mm);    
            }
            else
            {
                std::cout << "You don't have a credit card. Do you want to enter? (y/n): ";
                if(yes_no())
                {
                    addCreditCard(customers, customers_count, id);
                    std::cout << "Transaction completed!\n\n";
                }
                else
                {
                    return false; // exiting to main menu
                }
            }
        }
    } while (ans != 1 && ans != 2);
    return true; // continuing
}