#include "utilities.h"


//-------------------------general-----------------------------
void is_num(int& input) 
{
	while(true)
	{
		std::cin >> input;
		if (std::cin.fail()) 
		{
			std::cout << "Invalid input. Please try again: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else 
		{
			return;
		}
	}
}
void is_num(double& input)
{
	while (true)
	{
		std::cin >> input;
		if (std::cin.fail())
		{
			std::cout << "Invalid input. Please try again: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else 
		{
			return;
		}
	}
}
bool yes_no() 
{
	char ans;
	do 
	{
		std::cin >> ans;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (std::cin.fail()) 
		{
			std::cerr << "Input error occurred.\n";
			continue;
		}
		else if (!(ans == 'y' || ans == 'Y' || ans == 'n' || ans == 'N')) 
		{
			std::cout << "Invalid input, please enter a valid choice" << std::endl;
		}
	} while (std::cin.fail() || !(ans == 'y' || ans == 'Y' || ans == 'n' || ans == 'N'));
	
	if (ans == 'y' || ans == 'Y') 
	{
		return true;
	}
	else 
	{
		return false; //abort 
	}
}






//-------------------------Movies-----------------------------
//-------------------------Customers-----------------------------


//-------------------------Date-----------------------------
//bool enter_date(date::year_month_day ) { // in date::year_month_day
//}
