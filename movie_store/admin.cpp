#include "admin.h"

std::string ADMIN = "admin";
std::string ADMIN_PSSWRD = "admin"; // very safe ;) __ i can see😂

std::string USER = "user";
std::string USER_PSSWRD = "user";

std::string checkCredentials(std::string& login, std::string& passwrd)
{
    if(login == ADMIN && passwrd == ADMIN_PSSWRD)
    {
        return "admin";
    }
    else if (login == USER && passwrd == USER_PSSWRD)
    {
        return "user";        
    }
    return "";
}

void deleteCustomer(Customer customers[], int& customers_count, std::string& id)
{
    if(customers_count != 0)
    {
        for (int i = 0; i < customers_count; i++) 
        {
            if (customers[i].Id == id) 
            {
                if(i < customers_count-1)
                {
                    customers[i].Name == customers[customers_count-1].Name;
                    customers[i].PhoneNumber == customers[customers_count-1].PhoneNumber;
                    customers[i].Id == customers[customers_count-1].Id;
                    customers[i].PreviouslyRentedMovies == customers[customers_count-1].PreviouslyRentedMovies;
                    for(int j = 0; j < limit; j++)
                    {
                        customers[i].CurrentlyRentedMovies[j] == customers[customers_count-1].CurrentlyRentedMovies[j];
                    }
                    
                    customers[customers_count-1].Name.clear();
                    customers[customers_count-1].Id.clear();
                    customers[customers_count-1].PhoneNumber.clear();
                    customers[customers_count-1].PreviouslyRentedMovies.clear();
                    for(int j = 0; j < limit; j++)
                    {
                        customers[customers_count-1].CurrentlyRentedMovies[j].clear();
                    }
                    customers_count--;
                }
                else if (i == customers_count-1)
                {
                    customers[i].Name.clear();
                    customers[i].Id.clear();
                    customers[i].PhoneNumber.clear();
                    customers[i].PreviouslyRentedMovies.clear();
                    for(int j = 0; j < limit; j++)
                    {
                        customers[i].CurrentlyRentedMovies[j].clear();
                    }
                    customers_count--;
                }
                else
                {
                    std::cout << "Error in the customer array, please contact your IT provider\n";
                    break;
                }
                std::cout << "Customer with ID: " << id << " deleted successfully.\n";
                break;
            }
        }
    }
    else
    {
        std::cout << "There are no customers! Please add.\n";
    }
}

void deleteMovie(movie movies[], int num_of_movies, std::string& name)
{
    for(int i = 0; i< num_of_movies; i++)
    {
        if(movies[i].Name == name)
        {
           
            movies[i].Name.clear();
            movies[i].CurrentRenter.clear();
            movies[i].AllRatings.clear();
            movies[i].rented = false;
            movies[i].price = 0;
            movies[i].fee = 0;
            movies[i].rating = 0;
            movies[i].RentedCount = 0;
            movies[i].DueDate = date::year(1000) / date::month(10) / date::day(10); //default state for empty, not an actual thing in the language i just decided that
            movies[i].due = false;
            std::cout << "Movie : "<< name << " deleted successfully\n";
            break;
        }
    }
}

std::string login()
{
    std::string login, passwrd;
    do
    {
        std::cout << "Enter username: ";
        getline(std::cin, login);
        if (login == "0") return "";
        
        std::cout << "Enter password: ";
        getline(std::cin, passwrd);
        if (passwrd == "0") return "";
        
        if(checkCredentials(login, passwrd) == "admin")
        {
            std::cout << "Welcome, " << login << "!\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return "admin";
        }
        else if(checkCredentials(login, passwrd) == "user")
        {
            std::cout << "Welcome, " << login << "!\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return "user";
        }
        else
        {
            std::cout << "Wrong password or username\n";
        }
    } while(checkCredentials(login, passwrd) == "");
}


// in main menu add,   bool isDateChanged, and sys_days new_date 
bool ChangeDate(sys_days& new_date) {
    char ans;
    bool date_good = false;
    std::cout << "do you wish to set date manually y/n?: ";

    do {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::cin.fail()) {
            std::cerr << "Input error occurred." << std::endl;
        }
        else if(!(ans == 'y' || ans == 'Y' || ans == 'n' || ans == 'N')) {
            std::cout << "Invalid input, please enter a valid choice" << std::endl;
        }
        std::cin >> ans;
    }while (std::cin.fail() || !(ans == 'y' || ans == 'Y' || ans == 'n' || ans == 'N'));
    if (ans == 'y' || ans == 'Y') {
        while (!date_good)/*incomplete fail safe*/ {
            std::string entered_date;
            std::cout << "specify date in this exact format yyyy-mm-dd : ";
            getline(std::cin, entered_date);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (entered_date == "0") return; //exit to main menu, note:the user will be notified at the begining of the program that entering 0 takes you back to main menu
            std::istringstream iss(entered_date);
            if (iss >> y >> delimiter1 >> m >> delimiter2 >> d && delimiter1 == '/' && delimiter2 == '/') {
                today = year(y) / month(m) / day(d); //conerts from date::..... to sys_days
                date_good = true;
            }
            else {
                std::cerr << "wrong format or invalid date, please try again"
                    date_good = false;
            }
        }


        return true;
    }
    else {
        return false;
    }
}



void add_movie(movie movies[], int movies_count) {

}