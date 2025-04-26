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

void deleteMovie(movie movies[], int movies_count, std::string& name)
{
    for(int i = 0; i< movies_count; i++)
    {
        if (i < movies_count - 1) {
            movies[i].Name = movies[movies_count - 1].Name;
            movies[i].CurrentRenter = movies[movies_count - 1].CurrentRenter;
            movies[i].AllRatings = movies[movies_count - 1].AllRatings;
            movies[i].rented = movies[movies_count - 1].rented;
            movies[i].price = movies[movies_count - 1].price;
            movies[i].fee = movies[movies_count - 1].fee;
            movies[i].rating = movies[movies_count - 1].rating;
            movies[i].RentedCount = movies[movies_count - 1].RentedCount;
            movies[i].DueDate = movies[movies_count - 1].DueDate;
            movies[i].due = movies[movies_count - 1].due;
            //----------------
            movies[movies_count - 1].Name.clear();
            movies[movies_count - 1].CurrentRenter.clear();
            movies[movies_count - 1].AllRatings.clear();
            movies[movies_count - 1].rented = false;
            movies[movies_count - 1].price = 0;
            movies[movies_count - 1].fee = 0;
            movies[movies_count - 1].rating = 0;
            movies[movies_count - 1].RentedCount = 0;
            movies[movies_count - 1].DueDate = date::year(3000) / date::month(10) / date::day(10);
            movies[movies_count - 1].due = false;
            movies_count--;
        }
        else if (i = movies_count - 1) {
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
            movies_count--;
            std::cout << "Movie : "<< name << " deleted successfully\n";
            break;
        }
        else {
            std::cerr << "error in the movies array, please contact your IT provider";
        }
        break;
    }
}

std::string login()
{
    std::string login, passwrd;
    do
    {
        std::cout << "Enter username: ";
        std::getline(std::cin, login);
        if (login == "0") return "";
        
        std::cout << "Enter password: ";
        std::getline(std::cin, passwrd);
        if (passwrd == "0") return "";
        
        if(checkCredentials(login, passwrd) == "admin")
        {
            std::cout << "Welcome, " << login << "!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return "admin";
        }
        else if(checkCredentials(login, passwrd) == "user")
        {
            std::cout << "Welcome, " << login << "!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return "user";
        }
        else
        {
            std::cout << "Wrong password or username\n";
        }
    } while(checkCredentials(login, passwrd) == "");
}

void add_movie(movie movies[]) {
    std::string name;
    double price, fee;
    std::cout << "enter movie name: ";
    getline(std::cin, name);
    std::transform(name.begin(), name.end(), name.begin(), tolower);
    std::cout << "\nenter movie price per day: ";
    is_num(price);
    std::cout << "\nenter due fees per day: ";
    is_num(fee);
}

void addNewCustomer(Customer customers[], int& customers_count) {
    std::string name, phonenum, id;
    std::cout << "Enter Customer name: ";
    getline(std::cin, name);
    std::transform(name.begin(), name.end(), name.begin(), tolower);

    do
    {
        std::cout << "Enter Customer phone: +";
        getline(std::cin, phonenum);

        if (!checkPhoneNumber(phonenum))
        {
            std::cout << "Invalid phone number!\n";
        }
        else if (checkPhoneNumberRegistered(customers, customers_count, phonenum))
        {
            std::cout << "This phone number is already registered!\n";
        }

    } while (!checkPhoneNumber(phonenum) && !checkPhoneNumberRegistered(customers, customers_count, phonenum));

    do
    {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // ---> sleep for 1 sec.
        id = generateId();

    } while (checkId(customers, customers_count, id));


    for (int i = 0; i < customers_count; i++) {
        if (customers[i].Name.empty())
        {
            customers[i].Name = name;
            customers[i].PhoneNumber = phonenum;
            customers[i].Id = id;
            customers_count++;
            break;
        }
    }
}

// to do while debugging: fix this shitty double enter
// in main menu add,   bool isDateChanged, and sys_days new_date 
bool ChangeDate(sys_days& new_date) {
    int y, m, d;
    char delimiter1, delimiter2;
    std::string entered_date;
    std::cout << "do you wish to set date manually y/n?: ";
    if (yes_no()) {
        while (true) //infinite loop till broken by return
        {
            std::cout << "specify date in this exact format yyyy/mm/dd : ";
            getline(std::cin, entered_date);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (entered_date == "0") return false; //aborts and exits to main menu
            std::istringstream iss(entered_date);
            if (iss >> y >> delimiter1 >> m >> delimiter2 >> d && delimiter1 == '/' && delimiter2 == '/') {
                new_date = year(y) / month(m) / day(d); //converts date::year_month_day to sys_fays, thnx to sir Howard Hinnant
                return true;
            }
            else {
                std::cerr << "wrong format or invalid date, please try again" << std::endl;
            }
        }
    }
    else {
        return false; //aborting
    }
}