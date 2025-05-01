#include "movie.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <thread>
#include <chrono>
#include <sstream>


//-------------------------utilities-----------------------------
bool isCustomerFound(customer customers[], int customers_count ,std::string& id) // done
{
    for(int i = 0; i < customers_count; i++)
    {
        if(customers[i].id == id) return true;
    }
    return false;
}
int getCustomerIndex(customer customers[], int customers_count, std::string& id) // done
{
    int customerIndex = 0;
    for(int i = 0; i < customers_count; i++)
    {
        if(customers[i].id == id)
        {
            return customerIndex;
        }
        customerIndex++;
    }
}
bool isMovieFound(movie movies[], int movies_count, std::string& movieName) // done
{
    for(int i = 0; i < movies_count; i++)
    {
        if(movies[i].name == movieName) return true;
    }
    return false;
} 
int getMovieIndex(movie movies[], int movies_count, std::string& movieName) // done
{
    int movieIndex = 0;
    for(int i = 0; i < movies_count; i++)
    {
        if(movies[i].name == movieName)
        {
            return movieIndex;
        }
        movieIndex++;
    }
}
bool isMovieRentedByCustomer(customer customers[], int customers_count ,std::string& id, std::string& movieName) // done
{
    int customerIndex = getCustomerIndex(customers, customers_count, id);
    for (int i = 0; i < limit; i++)
    {
        if(customers[customerIndex].currentlyRentedMovies[i] == movieName) return true;
    }
    
    return false;
}
int getMoviesCount(movie movies[], int size_of_movies) // done
{
    if(size_of_movies != 0)
    {
        int movies_count = 0;
        for (int i = 0; i < size_of_movies; i++)
        {
            if(!movies[i].name.empty())
            {
                movies_count++;
            }
        }
        return movies_count;
    }
    else
    {
        std::cout << "There are currently no movies on the system! Please add a movie first.\n";
    }
}
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
            std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
		else if (!((tolower(ans) == 'y') || (tolower(ans) == 'n'))) 
		{
			std::cout << "Invalid input, please enter a valid choice: ";
		}
	} while (std::cin.fail() || !((tolower(ans) == 'y') || (tolower(ans) == 'n')));
	
	if (tolower(ans) == 'y')
	{
		return true;
	}
	else
	{
		return false; //abort 
	}
}
//-------------------------utilities-----------------------------


void listMovies(movie movies[], int movies_count) // done
{
    if(movies_count != 0)
    {
        int MovieNum = 1;
        std::cout << "\n-----------------------------\n";
        for (int i = 0; i < movies_count; i++) 
        {
            std::cout << MovieNum << ". " << movies[i].name << '\n';
            std::cout << "\tprice: " << movies[i].price << " EGP" << '\n';
            std::cout << "\trented: " << movies[i].rentedCount << " times" << '\n';
            if (!movies[i].allRatings.empty()) 
            {
                std::cout << "\trating:" << movies[i].rating << '\n';
            }
            else 
            {
                std::cout << "\trating: has not been rated yet\n";
            }
            if (movies[i].rented) 
            {
                std::cout << "\trented status: " << "rented\n";
            }
            else
            {
                std::cout << "\trented status: " << "not rented\n";
            }
            std::cout << '\n';
            MovieNum++;
        }
        std::cout << "-----------------------------\n";
    }
    else
    {
        std::cout << "There are currently no movies on the system! Please add a movie first.\n";
    }
}

void listRented(movie movies[], int movies_count) // done
{
    if(movies_count != 0)
    {
        int movieNum = 1;
        std::cout << "\n-----------------------------\n";
        for (int i = 0; i < movies_count; i++)
        {
            if(movies[i].rented)
            {
                std::cout << movieNum << ". \n";
                std::cout << "Movie name: " << movies[i].name << '\n';
                std::cout << "Rented by :" << movies[i].currentRenter << '\n';
                movieNum++;
            }
        }
        if(movieNum == 1) std::cout << "There are no rented movies at the moment!\n";
        std::cout << "-----------------------------\n";
    }
    else
    {
        std::cout << "There are currently no movies on the system! Please add a movie first.\n";
    }
}

int listUnrented(movie movies[], int movies_count) // done
{
    int MovieNum = 1;
    if (movies_count != 0) 
    {
        std::cout << "\n-----------------------------\n";
        for (int i = 0; i < movies_count; i++) 
        {
            if (!movies[i].rented) 
            {
                std::cout << MovieNum << ". " << movies[i].name << '\n';
                MovieNum++;
            }
        }
        if (MovieNum == 1) //meaning there are movies on the system but no movies were displayed, aka they are all rented 
        { 
            std::cerr << "There are currently no available movies to rent.\n";
        }
        std::cout << "-----------------------------\n";
    }
    else 
    {
        std::cerr << "there are currently no movies on the system! Please add a movie first.\n";
    }
    return MovieNum;
}


bool rate(movie movies[], int movies_count, std::string& movieName, 
            customer customers[], int customers_count ,std::string& id) // done
{
    int customerIndex = getCustomerIndex(customers, customers_count, id);
    
    if (isMovieRentedByCustomer(customers, customers_count, id, movieName))
    {
        if(!customers[customerIndex].rating.count(movieName))
        {
            int rating = 0, a = 0, b = 0, c = 0, d = 0, e = 0;
            int movieIndex = getMovieIndex(movies, movies_count, movieName);
            std::cout << "\n\nRating: " << movieName << "\n\n";
            std::cout << "1: *\n" <<
                         "2: **\n" <<
                         "3: ***\n" <<
                         "4: ****\n" <<
                         "5: *****\n\n";
            
            std::cout << "Pick a rating from above: ";
            std::cin >> rating;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            switch (rating)
            {
            case 0:
                return false;
            case 1:
                movies[movieIndex].allRatings.push_back(1);
                customers[customerIndex].rating.insert({movieName, 1}); 
                break;                    
            case 2:
                movies[movieIndex].allRatings.push_back(2);
                customers[customerIndex].rating.insert({movieName, 2});  
                break;                    
            case 3:
                movies[movieIndex].allRatings.push_back(3);
                customers[customerIndex].rating.insert({movieName, 3}); 
                break;                    
            case 4:
                movies[movieIndex].allRatings.push_back(4);
                customers[customerIndex].rating.insert({movieName, 4}); 
                break;                    
            case 5:
                movies[movieIndex].allRatings.push_back(5);
                customers[customerIndex].rating.insert({movieName, 5}); 
                break;
            
            default:
                std::cout << "Wrong rating! please pick a rating from above!\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                return false;
            }
            std::cout << "Thanks for your rating!\n";

            if (!movies[movieIndex].allRatings.empty())
            {
                for (int i : movies[movieIndex].allRatings)
                {
                    switch (i)
                    {
                    case 1:
                        a++;
                        break;
                    case 2:
                        b++;
                        break;
                    case 3:
                        c++;
                        break;
                    case 4:
                        d++;
                        break;
                    case 5:
                        e++;
                        break;
                    default:
                        std::cerr << "Error in the ratings vector or the calcrating function, please contact your IT provider\n";
                        break;
                    }
                }
                movies[movieIndex].rating = (a * 1 + b * 2 + c * 3 + d * 4 + e * 5) / (a + b + c + d + e);
            }
            else
            {
                movies[movieIndex].rating = rating;
            }
        }
        else
        {
            std::cout << "This movie is already rated! Please edit your rating.\n";
        }
    } 
    else 
    {
        std::cout << "This movie isn't rented by the customer! Rent it please before rating it.\n";
    }
    return true; // for main menu
}

bool editRating(movie movies[], int movies_count, std::string& movieName,
                customer customers[], int customers_count, std::string& id) // done
{
    int customerIndex = getCustomerIndex(customers, customers_count, id);
    
    if (isMovieRentedByCustomer(customers, customers_count, id, movieName))
    {
        if(customers[customerIndex].rating.count(movieName))
        {
            int rating = 0;
            int movieIndex = getMovieIndex(movies, movies_count, movieName);
            std::cout << "\n\nRating: " << movieName << "\n\n";
            std::cout << "1: *\n" <<
                         "2: **\n" <<
                         "3: ***\n" <<
                         "4: ****\n" <<
                         "5: *****\n\n";
            
            std::cout << "Pick a rating from above: ";
            std::cin >> rating;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if(rating == 0) return false;
            if (rating >= 1 && rating <= 5)
            {
                //update allRatings vector
                for(int i = 0; i < movies[movieIndex].allRatings.size(); i++)
                {
                    if (movies[movieIndex].allRatings[i] == customers[customerIndex].rating.at(movieName))
                    {
                        movies[movieIndex].allRatings[i] = rating;
                        break;
                    }
                }
                customers[customerIndex].rating.at(movieName) = rating;
                std::cout << "Thanks for your rating!\n";
            }
            else
            {
                std::cout << "Wrong rating! please pick a rating from above!\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                return false; // for main menu
            }
        }
        else
        {
            std::cout << "This movie isn't rated before please rate it!\n";
        }
    }
    else
    {
        std::cout << "This movie isn't rented by the customer! Rent it please before rating it.\n";
    }
    return true; // for main menu
}


void rent(customer customers[], int customers_count, movie movies[], int movies_count, date::year_month_day system_date)
{
    bool repeat = true, date_good = false;
    int selected, customerIndex, match = 1;
    std::string name, id, entered_date;
    int y, m, d;
    char delimiter1, delimiter2;

    std::cout << "\n\n";
    int unrented_movies_count = listUnrented(movies, movies_count);
    if(unrented_movies_count == 1) return;

    do
    {
        std::cout << "Enter customer id: ";
        std::getline(std::cin, id);
        std::cin.clear();
        std::transform(id.begin(), id.end(), id.begin(), toupper); // c# ---> C#
        
        if (id == "0") return; //exit to main menu, note:the user will be notified at the begining of the program that entering 0 takes you back to main menu
        if (isCustomerFound(customers, customers_count, id))
        {
            customerIndex = getCustomerIndex(customers, customers_count, id);
            name = customers[customerIndex].name;
        }
        else
        {
            std::cerr << "Wrong id, please try again\n";
        }
    } while (!isCustomerFound(customers, customers_count, id));

    std::cout << "Pick a movie number: ";
    while (repeat)
    {
        std::cin >> selected;
        if (selected == 0) return; //exit to main menu, note:the user will be notified at the begining of the program that entering 0 takes you back to main menu
        if (std::cin.good() && selected < unrented_movies_count && selected > 0) 
        {
            repeat = false;
        }
        else 
        {
            std::cerr << "Invalid choice. Please select a valid movie number: ";
            repeat = true;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    for (int i = 0; i < movies_count; i++)
    {
        if (!movies[i].rented && match == selected)
        {
            std::cout << "movie: " << movies[i].name << '\n';
            std::cout << "\tprice per day: " << movies[i].price << " EGP\n";
            std::cout << "\toverdue fee per day: " << movies[i].fee << " EGP\n";
            std::cout << "\tmovie rating:" << movies[i].rating << '\n';
            std::cout << "\thas been rented: " << movies[i].rentedCount << " times\n\n";
            std::cout << "today is: " << system_date << '\n';
            while (!date_good)/*incomplete fail safe*/ 
            {
                std::cout << "specify return date in this exact format yyyy/mm/dd : ";
                getline(std::cin, entered_date);
                std::cin.clear();
                if (entered_date == "0") return; //aborts and exits to main menu

                std::istringstream iss(entered_date);
                if (iss >> y >> delimiter1 >> m >> delimiter2 >> d && delimiter1 == '/' && delimiter2 == '/') //this is correct don't worry
                {
                    movies[i].dueDate = date::year(y) / date::month(m) / date::day(d);
                    if(movies[i].dueDate >= system_date)
                    {
                        date_good = true;
                    }
                    else {
                        std::cerr << "entered return date is invalid, please try again\n";
                        date_good = false;
                    }
                }
                else
                {
                    std::cerr << "entered return date is invalid, please try again\n";
                    date_good = false;
                }
            }
            if (isCurrentlyRentedEmpty(customers, customerIndex))
            {
                for (int k = 0; k < limit; k++)
                {
                    if (customers[customerIndex].currentlyRentedMovies[k].empty())
                    {
                        customers[customerIndex].currentlyRentedMovies[k] = movies[i].name;
                        movies[i].rented = true;
                        movies[i].rentedCount++;
                        movies[i].currentRenter = name;
                        return;
                    }
                }            
            }
            else
            {
                std::cout << "You have reached your renting limit! return one or more movies!\n";
                return;
            }
        }
        else if (!movies[i].rented) //but match doesnt = selected
        {
            match++;
        }
    }
}

void returnMovie(customer customers[], int customers_count, std::string& id, movie movies[], int movies_count, 
    bool isDateChanged, date::sys_days new_date) // done
{
    int num = 1, movieIndex, ans, diff, index = 0;
    double cash;
    std::string movieName;
    int customerIndex = getCustomerIndex(customers, customers_count, id);

    if(!isCurrentlyRentedEmpty(customers, customerIndex))
    {
        for (std::string movie : customers[customerIndex].currentlyRentedMovies)
        {
            if(!movie.empty())
            {
                std::cout << num << ". " << movie << '\n';
                num++;
            }
        }
        do
        {
            std::cout << "Enter number of the movie you wish to return: ";
            is_num(ans);
            if(ans == 0) return;
            if ((ans <= num) && (ans > 0))
            {
                num = 1;
                for (std::string movie : customers[customerIndex].currentlyRentedMovies)
                {
                    if(!movie.empty())
                    {
                        if(ans == num)
                        {
                            movieName = movie;
                            break;
                        }
                        num++;
                    }
                    index++;
                }
    
                movieIndex = getMovieIndex(movies, movies_count, movieName);
                diff = validateDue(movies[movieIndex], isDateChanged, new_date);
                if (movies[movieIndex].due) 
                {
                    cash = movies[movieIndex].price + movies[movieIndex].fee * diff;
                    std::cout << "considering that the movie is due: " << diff << " days, the amount to pay is: " << cash << '\n';  
                }
                else 
                {
                    cash = movies[movieIndex].price;
                    std::cout << "amount to pay is: " << cash << '\n';
                }
                std::cout << "(this is in an italian accent)\n";
                std::cout << "pay up or else? y/n: ";
                if (yes_no()) 
                {
                    if(!pay(customers, customers_count, id)) 
                    {
                        std::cout << "Canceling transaction!\n";
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        return;
                    }    
                }
                else 
                {
                    std::cout << "you have a beautiful family, it'd be a shame if anything happens to them.\nyou sure you still don't want to pay up? y/n: ";
                    if (yes_no()) 
                    {
                        std::cout << "Smart lad, say hi to your family for me\n";
                        if(!pay(customers, customers_count, id)) 
                        {
                            std::cout << "Canceling transaction!\n";
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            return;
                        }    
                    }
                    else 
                    {
                        std::cout << "Remember that it was YOU who made this choice\n";
                        return;
                    }
                }
                std::cout << "Would you like to rate the movie? y/n: ";
                if (yes_no())
                {
                    bool check = rate(movies, movies_count, movieName, customers, customers_count, id);
                    
                    while (!check)
                    {
                        check = rate(movies, movies_count, movieName, customers, customers_count, id);
                    }
                }
                movies[movieIndex].rented = false;
                movies[movieIndex].currentRenter.clear();
                movies[movieIndex].due = false;
                movies[movieIndex].dueDate = date::year(3000) / date::month(10) / date::day(10);
                customers[customerIndex].currentlyRentedMovies[index].clear();
                customers[customerIndex].previouslyRentedMovies.push_back(movies[movieIndex].name);
            }
            else 
            {
                std::cerr << "Invalid choice, please try again\n";
            }
        } while((ans > num) || (ans <= 0));
    }
    else
    {
        std::cout << "You don't have rented movies to return!\n";
    }
 
}

void listTopRated(movie movies[], int movies_count) //using insertion sort, listing top 10 rated
{
    movie copy[movies_max];
    std::copy(movies, movies+movies_count, copy);

    for (int i = 1; i < movies_count; i++) 
    {
        movie key = copy[i];
        int j = i - 1;
        while (j >= 0 && copy[j].rating < key.rating)
        {
            copy[j + 1] = copy[j];
            j--;
        }
        copy[j+1] = key;
    }

    int num = 1;
    for (int k = 0; k < movies_count; k++)
    {
        if(k < 10)
        {
            std::cout << num << ". " << copy[k].name << '\n';
            num++;
        }
        
    }
}

void listTopRented(movie movies[], int movies_count) //using insertion sort, listing top 10 rented
{
    movie copy[movies_max];
    std::copy(movies, movies + movies_count, copy);
    
    for (int i = 1; i < movies_count; i++)
    {
        movie key = copy[i];
        int j = i - 1;
        while (j >= 0 && copy[j].rentedCount < key.rentedCount)
        {
            copy[j + 1] = copy[j];
            j--;
        }
        copy[j + 1] = key;
    }

    int num = 1;
    for (int k = 0; k < movies_count; k++)
    {
        if(k < 10)
        {
            std::cout << num << ". " << copy[k].name << '\n';
            num++;
        }
    }
}


int validateDue(movie& movie, bool isDateChanged, date::sys_days new_date) // done
{
    date::sys_days today, due = movie.dueDate;
    if (isDateChanged) 
    {
        today = new_date;
    }
    else 
    {
        auto now = std::chrono::system_clock::now(); // return current system date
        today = date::floor<date::days>(now);
    }
    
    auto today_n = today.time_since_epoch(); // diff in days from 1970 to present for ex. 20205d, (d) for days
    int today_int = today_n.count(); // convert it to int --> 20205d --> 20205
    
    auto due_n = due.time_since_epoch();
    int due_int = due_n.count();
    int diff = 0;
    
    if (today > due)
    {
        movie.due = true;
        diff = today_int - due_int;
        return diff;
    }
    else 
    {
        movie.due = false;
        return 0;
    }
}

int calc_rental_days(movie& movie, bool isDateChanged, date::sys_days new_date)
{
    date::sys_days today, due = movie.dueDate;
    if (isDateChanged)
    {
        today = new_date;
    }
    else
    {
        auto now = std::chrono::system_clock::now(); // return current system date
        today = date::floor<date::days>(now);
    }

    auto today_n = today.time_since_epoch(); // diff in days from 1970 to present for ex. 20205d, (d) for days
    int today_int = today_n.count(); // convert it to int --> 20205d --> 20205

    auto due_n = due.time_since_epoch();
    int due_int = due_n.count();
    int diff = 0;

    diff = due_int - today_int;
    if (diff == 0) return 1; //if rented till the end of the day, counts as a day
    else {
    return diff;
    }
}

void listDueAccounts(movie movies[],int movies_count, customer customers[], int customers_count, 
                        bool isDateChanged, date::sys_days new_date) // done
{ //note for when u r debugging dummy, it updates the accounts right before listing them, no earlier
    int num = 1;
    std::cout << "\n-----------------------------\n";   
    for (int i = 0; i < movies_count; i++)
    {
        int days_due = validateDue(movies[i], isDateChanged, new_date);
        if (movies[i].due == true)
        {
            for (int j = 0; j < customers_count; j++)
            {
                if (movies[i].currentRenter == customers[j].name)
                {
                    std::cout << num << ". " << customers[j].name << '\n';
                    std::cout << "id: " << customers[j].id << '\n';
                    std::cout << "phone number: " << customers[j].phoneNumber << '\n';
                    std::cout << "due movie: " << movies[i].name << '\n';
                    std::cout << "movie was due: " << days_due << " days ago.\n";
                    std::cout << "due fees up till now: " << days_due * movies[i].fee << "\n\n";
                }
            }
            num++;
        }
    }
    if(num == 1) std::cout << "There are no due accounts!\n";
    std::cout << "-----------------------------\n";
}