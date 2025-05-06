#include "movie.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <thread>
#include <chrono>
#include <sstream>
#include <fstream>
#include "admin.h" // contains new_date, today, system_date, cashRegister



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
    std::string name;
    for(int i = 0; i < movies_count; i++)
    {
        name = movies[i].name; 
        std::transform(name.begin(), name.end(), name.begin(), tolower);
        if(deleteSpaces(name) == movieName) return true;
    }
    return false;
} 
int getMovieIndex(movie movies[], int movies_count, std::string& movieName) // done
{
    int movieIndex = 0;
    std::string name;
    for(int i = 0; i < movies_count; i++)
    {
        name = movies[i].name; 
        std::transform(name.begin(), name.end(), name.begin(), tolower);
        if(deleteSpaces(name) == movieName) return movieIndex;
        movieIndex++;
    }
}
bool isMovieCurrentlyRentedByCustomer(customer customers[], int customers_count ,std::string& id, std::string& movieName) // done
{
    int customerIndex = getCustomerIndex(customers, customers_count, id);
    for (std::string movie : customers[customerIndex].currentlyRentedMovies)
    {
        std::transform(movie.begin(), movie.end(), movie.begin(), tolower);
        if(deleteSpaces(movie) == movieName) return true;
    }
    return false;
}
bool isMoviePreviouslyRentedByCustomer(customer customers[], int customerIndex, std::string& movieName)
{
    for(std::string movie : customers[customerIndex].previouslyRentedMovies)
    {
        std::transform(movie.begin(), movie.end(), movie.begin(), tolower);
        movie = deleteSpaces(movie);
        if(movie == movieName) return true;
    }
    return false;
}
int getMoviesCount(movie movies[], int size_of_movies) // done
{
    int movies_count = 0;
    for (int i = 0; i < size_of_movies; i++)
    {
        if(!(movies[i].name.empty())) movies_count++;
    }
    return movies_count;
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
            if (input > -1) {
			    return;
            }
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
            if (input > -1) {
                return;
            }
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
		else if (tolower(ans) != 'y' && tolower(ans) != 'n')
		{
			std::cout << "Invalid input, please enter a valid choice: ";
		}
	} while (std::cin.fail() || ((tolower(ans) != 'y' && tolower(ans) != 'n')));
	
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
            if (movies[i].rating != 0)
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

void calc_rating(movie& movie) // done
{
        double a = 0, b = 0, c = 0, d = 0, e = 0;
        for (int i : movie.allRatings)
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
        movie.rating = (a * 1 + b * 2 + c * 3 + d * 4 + e * 5) / (a + b + c + d + e);
}

bool rate(movie movies[], int movies_count, std::string& movieName, 
          customer customers[], int customers_count ,std::string& id) // done
{
    int customerIndex = getCustomerIndex(customers, customers_count, id);
    
    if (isMoviePreviouslyRentedByCustomer(customers, customerIndex, movieName) || isMovieCurrentlyRentedByCustomer(customers, customers_count, id, movieName))
    {
        int movieIndex = getMovieIndex(movies, movies_count, movieName);
        if(!customers[customerIndex].rating.count(movies[movieIndex].name))
        {
            int rating = 0;
            std::cout << "\n\nRating: " << movies[movieIndex].name << "\n\n";
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
                std::cout << "Returning to main menu!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
                return true;
            case 1:
                movies[movieIndex].allRatings.push_back(1);
                customers[customerIndex].rating.insert({movies[movieIndex].name, 1}); 
                break;                    
            case 2:
                movies[movieIndex].allRatings.push_back(2);
                customers[customerIndex].rating.insert({movies[movieIndex].name, 2});  
                break;                    
            case 3:
                movies[movieIndex].allRatings.push_back(3);
                customers[customerIndex].rating.insert({movies[movieIndex].name, 3}); 
                break;                    
            case 4:
                movies[movieIndex].allRatings.push_back(4);
                customers[customerIndex].rating.insert({movies[movieIndex].name, 4}); 
                break;                    
            case 5:
                movies[movieIndex].allRatings.push_back(5);
                customers[customerIndex].rating.insert({movies[movieIndex].name, 5}); 
                break;
            
            default:
                std::cout << "Wrong rating! please pick a rating from above!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
                return false;
            }
            std::cout << "Thanks for your rating!\n";
            calc_rating(movies[movieIndex]);
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
    
    if (isMoviePreviouslyRentedByCustomer(customers, customerIndex, movieName) || isMovieCurrentlyRentedByCustomer(customers, customers_count, id, movieName))

    {
        int movieIndex = getMovieIndex(movies, movies_count, movieName);
        if(customers[customerIndex].rating.count(movies[movieIndex].name))
        {
            int rating = 0;
            std::cout << "\n\nRating: " << movies[movieIndex].name << "\n\n";
            std::cout << "1: *\n" <<
                         "2: **\n" <<
                         "3: ***\n" <<
                         "4: ****\n" <<
                         "5: *****\n\n";
            
            std::cout << "Pick a rating from above: ";
            std::cin >> rating;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if(rating == 0) 
            {
                std::cout << "Returning to main menu!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
                return true;
            }
            if (rating >= 1 && rating <= 5)
            {
                //update allRatings vector
                for(int i = 0; i < movies[movieIndex].allRatings.size(); i++)
                {
                    if (movies[movieIndex].allRatings[i] == customers[customerIndex].rating.at(movies[movieIndex].name))
                    {
                        movies[movieIndex].allRatings[i] = rating;
                        break;
                    }
                }
                customers[customerIndex].rating.at(movies[movieIndex].name) = rating;
                std::cout << "Thanks for your rating!\n";
                calc_rating(movies[movieIndex]); // calcu new rating
            }
            else
            {
                std::cout << "Wrong rating! please pick a rating from above!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
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

void rent(customer customers[], int customers_count, movie movies[], int movies_count, date::sys_days system_date, std::string& id)
{

    bool repeat = true, date_good = false;
    int selected, match = 1;
    std::string entered_date;
    int y, m, d;
    char delimiter1, delimiter2;
    int customerIndex = getCustomerIndex(customers, customers_count, id);

    std::cout << "\n\n";
    int unrented_movies_count = listUnrented(movies, movies_count);
    if(unrented_movies_count == 1) return;

    std::cout << "Pick a movie number: ";
    while (repeat)
    {
        std::cin >> selected;
        if (selected == 0) 
        {
            std::cout << "Returning to main menu!\n";
            std::this_thread::sleep_for(std::chrono::seconds(t));
            return;
        }
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
            using namespace date;
            std::cout << "movie: " << movies[i].name << '\n';
            std::cout << "\tprice per day: " << movies[i].price << " EGP\n";
            std::cout << "\toverdue fee per day: " << movies[i].fee << " EGP\n";
            std::cout << "\tmovie rating:" << movies[i].rating << '\n';
            std::cout << "\thas been rented: " << movies[i].rentedCount << " times\n\n";
            std::cout << "today is: " << system_date << '\n';
            while (!date_good)
            {
                std::cout << "specify return date in this exact format yyyy/mm/dd : ";
                getline(std::cin, entered_date);
                entered_date = deleteSpaces(entered_date);
                if (entered_date == "0")
                {
                    std::cout << "Returning to main menu!\n";
                    std::this_thread::sleep_for(std::chrono::seconds(t));
                    return;
                }

                std::istringstream iss(entered_date);
                if (iss >> y >> delimiter1 >> m >> delimiter2 >> d && delimiter1 == '/' && delimiter2 == '/') //this is correct don't worry
                {
                    movies[i].dueDate = date::year(y) / date::month(m) / date::day(d);
                    if(movies[i].dueDate >= system_date)
                    {
                        date_good = true;
                    }
                    else
                    {
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
            if (isCurrentlyRentedAvailable(customers, customerIndex) != "full")
            {
                for (int k = 0; k < limit; k++)
                {
                    if (customers[customerIndex].currentlyRentedMovies[k].empty())
                    {
                        customers[customerIndex].currentlyRentedMovies[k] = movies[i].name;
                        movies[i].rented = true;
                        movies[i].rentedCount++;
                        movies[i].rentalDays = calc_rental_days(movies[i], system_date);
                        movies[i].currentRenter = customers[customerIndex].name;
                        std::cout << "Successfully rented: " << movies[i].name << " for " << movies[i].rentalDays << " days\n";
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

void returnMovie(double& cashRegister, customer customers[], int customers_count, std::string& id, movie movies[], int movies_count, date::sys_days system_date) // done
{
    int num = 1, found, movieIndex, ans, index = 0;
    std::string movieName;
    int customerIndex = getCustomerIndex(customers, customers_count, id);

    if(isCurrentlyRentedAvailable(customers, customerIndex) != "empty")
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
            if(ans == 0) 
            {
                std::cout << "Returning to main menu!\n";
                std::this_thread::sleep_for(std::chrono::seconds(t));
                return;
            }
            if ((ans < num) && (ans > 0))
            {
                num = 1; // reset counter to get the selected movie.
                for (std::string movie : customers[customerIndex].currentlyRentedMovies)
                {
                    if(!movie.empty())
                    {
                        if(ans == num)
                        {
                            movieName = movie;
                            found = index;
                        }
                        num++;
                    }
                    index++;
                }
                std::transform(movieName.begin(), movieName.end(), movieName.begin(), tolower);
                movieName = deleteSpaces(movieName);
                movieIndex = getMovieIndex(movies, movies_count, movieName);
                

                std::cout << "(this is in an italian accent)\n";
                std::cout << "pay up or else? y/n: ";
                if (yes_no()) 
                {

                    if(!pay(cashRegister, customers, customers_count, id, movies[movieIndex],system_date)) 
                    {
                        std::cout << "Canceling transaction!\n";
                        std::this_thread::sleep_for(std::chrono::seconds(t));
                        return;
                    }
                    else
                    {
                        movies[movieIndex].rented = false;
                        movies[movieIndex].currentRenter.clear();
                        movies[movieIndex].due = false;
                        movies[movieIndex].rentalDays = 0;
                        movies[movieIndex].dueDate = date::year(3000) / date::month(10) / date::day(10);
                        customers[customerIndex].currentlyRentedMovies[found].clear();
                        customers[customerIndex].coins += generate_coins();
                        if (!isMoviePreviouslyRentedByCustomer(customers, customerIndex, movieName))
                        {
                            customers[customerIndex].previouslyRentedMovies.push_back(movies[movieIndex].name);
                        }
                    }
                }
                else 
                {
                    std::cout << "you have a beautiful family, it'd be a shame if anything happens to them.\nare you going to pay up now? y/n: ";
                    if (yes_no()) 
                    {
                        std::cout << "Smart lad, say hi to your family for me\n";
                        if(!pay(cashRegister ,customers, customers_count, id, movies[movieIndex], system_date))
                        {
                            std::cout << "Canceling transaction!\n";
                            std::this_thread::sleep_for(std::chrono::seconds(t));
                            return;
                        }
                        else {
                            movies[movieIndex].rented = false;
                            movies[movieIndex].currentRenter.clear();
                            movies[movieIndex].due = false;
                            movies[movieIndex].rentalDays = 0;
                            movies[movieIndex].dueDate = date::year(3000) / date::month(10) / date::day(10);
                            customers[customerIndex].currentlyRentedMovies[found].clear();
                            customers[customerIndex].coins += generate_coins();
                            if (!isMoviePreviouslyRentedByCustomer(customers, customerIndex, movieName))
                            {
                                customers[customerIndex].previouslyRentedMovies.push_back(movies[movieIndex].name);
                            }
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
                    if(!customers[customerIndex].rating.count(movies[movieIndex].name))
                    {
                        bool check = rate(movies, movies_count, movieName, customers, customers_count, id);
                        while (!check)
                        {
                            check = rate(movies, movies_count, movieName, customers, customers_count, id);
                        }
                    }
                    else
                    {
                        std::cout << "You already rated this movie! Do you want to edit your rating? y/n: ";
                        if(yes_no())
                        {
                            bool check = editRating(movies, movies_count, movieName, customers, customers_count, id);
                            while (!check)
                            {
                                check = editRating(movies, movies_count, movieName, customers, customers_count, id);
                            }
                        }
                    }
                }

            }
            else 
            {
                std::cerr << "Invalid choice, please try again\n";
            }
        } while((ans >= num) || (ans <= 0));
    }
    else
    {
        std::cout << "You don't have rented movies to return!\n";
    }
}

void addNewMovie(movie movies[], int size_of_movies, int& movies_count) // done 
{
    std::string movieName, check;
    double price = 0, fee = 0;
    do
    {
        std::cout << "Enter movie name: ";
        getline(std::cin, movieName);
        check = deleteSpaces(movieName);
        (check.begin(), check.end(), check.begin(), tolower);
        
        if(movieName == "0")
        {
            std::cout << "Returning to main menu!\n";
            std::this_thread::sleep_for(std::chrono::seconds(t));
            return;
        }
        if(isMovieFound(movies,movies_count,check))
        {
            std::cout << "This movie already exists!\n";
            continue;
        }
        std::cout << "\nEnter movie price per day (EGP) : ";
        is_num(price);
        std::cout << "\nEnter due fees per day (EGP) : ";
        is_num(fee);
    } while(isMovieFound(movies,movies_count,check) || check.empty());
    
    for(int i = 0; i < size_of_movies; i++)
    {
        if(movies[i].name.empty())
        {
            movies[i].name = movieName;
            movies[i].price = price;
            movies[i].fee = fee;
            movies_count++;
            std::cout << "Successfully added: " << movieName << '\n';
            return;
        }
    }
    std::cerr << "you have reached maximum movie capacity!!\n"; // if the return doesn't happen, ie there are no empty slots
    std::this_thread::sleep_for(std::chrono::seconds(t));
    std::cout << "Returning to main menu!\n";
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

int validateDue(movie& movie, date::sys_days system_date) // done
{
    date::sys_days due = movie.dueDate;
    if (system_date > due)
    {
        auto today_n = system_date.time_since_epoch(); // diff in days from 1970 to present for ex. 20205d, (d) for days
        int today_int = today_n.count(); // convert it to int --> 20205d --> 20205
    
        auto due_n = due.time_since_epoch();
        int due_int = due_n.count();
        int diff = 0;

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


int calc_rental_days(movie& movie, date::sys_days system_date) // done
{
    date::sys_days today, due = movie.dueDate;


    auto today_n = system_date.time_since_epoch(); // diff in days from 1970 to present for ex. 20205d, (d) for days
    int today_int = today_n.count(); // convert it to int --> 20205d --> 20205

    auto due_n = due.time_since_epoch();
    int due_int = due_n.count();
    int diff = 0;

    diff = due_int - today_int;
    if (diff == 0) return 1; //if rented till the end of the day, counts as a day
    return diff;
}


void listDueAccounts(movie movies[],int movies_count, customer customers[], int customers_count, date::sys_days system_date) // done
{ //note for when u r debugging dummy, it updates the accounts right before listing them, no earlier
    int num = 1;
    std::cout << "\n-----------------------------\n";   
    for (int i = 0; i < movies_count; i++)
    {
        int days_due = validateDue(movies[i], system_date);
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

void save_movies(double cashRegister, movie movies[], int movies_count, const std::string& file_name) 
{
    std::ofstream outfile(file_name);
    if (outfile.is_open()) 
    {
        outfile << cashRegister << std::endl;
        outfile << movies_count << std::endl;
        for (int i = 0; i < movies_count; i++) 
        {
            outfile << movies[i].name << std::endl;
            outfile << movies[i].price << std::endl;
            outfile << movies[i].fee << std::endl;
            outfile << movies[i].rentedCount << std::endl;
            outfile << std::boolalpha << movies[i].rented << std::endl;
            outfile << movies[i].currentRenter << std::endl;
            outfile << std::boolalpha << movies[i].due << std::endl;
            outfile << movies[i].rentalDays << std::endl;
            outfile << movies[i].dueDate << std::endl;
            outfile << movies[i].rating << std::endl;
            outfile << movies[i].allRatings.size() << std::endl;
            outfile << "{" << std::endl;
            for (int rating : movies[i].allRatings) 
            {
                outfile << rating << std::endl;
            }
            outfile << "}" << std::endl;
        }
        outfile.close();
        std::cout << "Movies Data successfully saved" << std::endl;
    }
    else 
    {
        std::cerr << "Unable to open file " << file_name << " ,contact your IT provider" << std::endl;
    }
}

void load_movies(double& cashRegister, movie movies[], int& mov_count, const std::string& file_name) 
{
    std::ifstream infile(file_name);
    if (infile.is_open()) 
    {
        if (file_empty(infile)) 
        {
            std::cerr << "no movie data to load\n";
            return;
        }
        infile >> cashRegister;
        infile.clear();
        infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        infile >> mov_count;
        infile.clear();
        infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (int i = 0; i < mov_count; i++) 
        {
            std::getline(infile, movies[i].name); //BTW std::ws gets rid of any leading whitespaces
            
            infile >> movies[i].price;
            infile.clear();
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            infile >> movies[i].fee;
            infile.clear();
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            infile >> movies[i].rentedCount;
            infile.clear();
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            infile >> std::boolalpha >> movies[i].rented;
            infile.clear();
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::getline(infile, movies[i].currentRenter); // std::ws causes it to take the previous value which is true or false

            // std::cout << "rented by: "<< movies[i].currentRenter << '\n'; // for testing
            // std::cout << "true: " << movies[i].currentRenter.empty() << '\n'; // it gives not empty with std::ws

            infile >> std::boolalpha >> movies[i].due;
            infile.clear();
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            infile >> movies[i].rentalDays;
            infile.clear();
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //_________________________
            std::string DueDate_str;
            int y, m, d;
            char delimiter1, delimiter2;
            std::getline(infile, DueDate_str);

            std::istringstream iss(DueDate_str);
            if (iss >> y >> delimiter1 >> m >> delimiter2 >> d && delimiter1 == '-' && delimiter2 == '-')
            {
                movies[i].dueDate = date::year(y) / date::month(m) / date::day(d);
            }
            else
            {
                std::cerr << "wrong due date format, while reading movie: " << movies[i].name << std::endl;
            }
            //__________________________
            infile >> movies[i].rating;
            infile.clear();
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            int ratings_size;
            infile >> ratings_size;
            infile.clear();
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            movies[i].allRatings.resize(ratings_size);

            std::string opening_brace;
            if (std::getline(infile, opening_brace) && opening_brace == "{") 
            {
                // movies[i].allRatings.resize(ratings_size);
                for (int j = 0; j < ratings_size; j++) 
                {
                    infile >> movies[i].allRatings[j];
                    infile.clear();
                    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::string closing_brace;
                std::getline(infile, closing_brace);
            }
            else 
            {
                std::cerr << "error taking in all ratings vector for movie: " << movies[i].name << std::endl;
            }
        }
        infile.close();
        std::cout << "loaded movies successfully\n";
    }
    else 
    {
        std::cerr << "Unable to open file " << file_name << " for reading, contact your IT provider" << std::endl;
    }
}