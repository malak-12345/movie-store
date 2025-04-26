#include "admin.h" //thus movie.h and customer.h and date.h are included too


//-------------------------utilities-----------------------------
bool isCustomerFound(Customer customers[], int customers_count ,std::string& id) // done
{
    for(int i = 0; i < customers_count; i++)
    {
        if(customers[i].Id == id) return true;
    }
    return false;
}
int getCustomerIndex(Customer customers[], int customers_count, std::string& id) // done
{
    int customerIndex = 0;
    for(int i = 0; i < customers_count; i++)
    {
        if(customers[i].Id == id)
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
        if(movies[i].Name == movieName) return true;
    }
    return false;
} 
int getMovieIndex(movie movies[], int movies_count, std::string& movieName) // done
{
    int movieIndex = 0;
    for(int i = 0; i < movies_count; i++)
    {
        if(movies[i].Name == movieName)
        {
            return movieIndex;
        }
        movieIndex++;
    }
}
bool isMovieRentedByCustomer(Customer customers[], int customers_count ,std::string& id, std::string& movieName) // done
{
    int customerIndex = getCustomerIndex(customers, customers_count, id);
    for (int i = 0; i < limit; i++)
    {
        if(customers[customerIndex].CurrentlyRentedMovies[i] == movieName) return true;
    }
    
    return false;
}
bool isFull(Customer customers[], int customerIndex) // done
{
    for(int i = 0; i < limit; i++)
    {
        if(customers[customerIndex].CurrentlyRentedMovies[i].empty()) return true; 
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
            if(!movies[i].Name.empty())
            {
                movies_count++;
            }
        }
        return movies_count;
    }
    else
    {
        std::cout << "There are currently no movies on the system!, please add a movie first.\n";
    }
}
//-------------------------utilities-----------------------------


void ListMovies(movie movies[], int movies_count) // done
{
    if(movies_count != 0)
    {
        int MovieNum = 1;
        for (int i = 0; i < movies_count; i++) 
        {
            std::cout << "\n-----------------------------\n";
            std::cout << MovieNum << ". " << movies[i].Name << '\n';
            std::cout << "\tprice: " << movies[i].price << " EGP" << '\n';
            std::cout << "\trented: " << movies[i].RentedCount << " times" << '\n';
            if (movies[i].AllRatings.empty()) 
            {
            std::cout << "\trating: has not been rated yet\n";
            }
            else 
            {
                std::cout << "\trating:" << movies[i].rating << '\n';
            }
            if (movies[i].rented) 
            {
                std::cout << "\trented status: " << "rented\n";
            }
            else
            {
                std::cout << "\trented status: " << "not rented\n";
            }
            std::cout << "-----------------------------\n";
            MovieNum++;
        }
    }
    else
    {
        std::cout << "There are currently no movies on the system!, please add a movie first.\n";
    }
}

void listRented(movie movies[], int movies_count) // done
{
    for (int i=0; i < movies_count; i++)
    {
        if(movies[i].rented)
        {
            std::cout << "\n-----------------------------\n";
            std::cout << "Movie name: " << movies[i].Name << '\n';
            std::cout << "Rented by :" << movies[i].CurrentRenter << '\n';
            std::cout << "-----------------------------\n";
        }
    }
}

int ListUnrented(movie movies[], int movies_count) // done
{
    int MovieNum = 1;
    if (movies_count != 0) 
    {
        for (int i = 0; i < movies_count; i++) 
        {
            if (!movies[i].rented) 
            {
                std::cout << MovieNum << ". " << movies[i].Name << '\n';
                MovieNum++;
            }
        }
        if (MovieNum == 1) //meaning there are movies on the system but no movies were displayed, aka they are all rented 
        { 
            std::cerr << "There are currently no available movies to rent.\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    else 
    {
        std::cerr << "there are currently no movies on the system!, please add a movie first.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    return MovieNum;
}


bool rate(movie movies[], int movies_count, std::string& movieName, 
            Customer customers[], int customers_count ,std::string& id) // done
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
            case 1:
                movies[movieIndex].AllRatings.push_back(1);
                customers[customerIndex].rating.insert({movieName, 1}); 
                break;                    
            case 2:
                movies[movieIndex].AllRatings.push_back(2);
                customers[customerIndex].rating.insert({movieName, 2});  
                break;                    
            case 3:
                movies[movieIndex].AllRatings.push_back(3);
                customers[customerIndex].rating.insert({movieName, 3}); 
                break;                    
            case 4:
                movies[movieIndex].AllRatings.push_back(4);
                customers[customerIndex].rating.insert({movieName, 4}); 
                break;                    
            case 5:
                movies[movieIndex].AllRatings.push_back(5);
                customers[customerIndex].rating.insert({movieName, 5}); 
                break;
            
            default:
                std::cout << "Wrong rating! please pick a rating from above!\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                return false;
            }
            if (!movies[movieIndex].AllRatings.empty())
            {
                for (int i : movies[movieIndex].AllRatings)
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
                return true; //for main menu
            }
        } 
        else
        {
            std::cout << "This movie is already rated! Please edit your rating.\n";
            return true;    
        }
    } 
    else 
    {
        std::cout << "This movie isn't rented by the customer! Rent it please before rating it.\n";
        return true; // for main menu
    }
    std::cout << "Thanks for your rating!\n";
    return true; // for main menu
}

bool editRating(movie movies[], int movies_count, std::string& movieName,
                Customer customers[], int customers_count, std::string& id) // done
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
            if (rating >= 1 && rating <= 5)
            {
                //update allRatings vector
                for(int i = 0; i < movies[movieIndex].AllRatings.size(); i++)
                {
                    if (movies[movieIndex].AllRatings[i] == customers[customerIndex].rating.at(movieName))
                    {
                        movies[movieIndex].AllRatings[i] = rating;
                        break;
                    }
                }
                customers[customerIndex].rating.at(movieName) = rating;
                std::cout << "Thanks for your rating!\n"; 
                return true; // for main menu
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
            return true;
        }
    }
    else
    {
        std::cout << "This movie isn't rented by the customer! Rent it please before rating it.\n";
        return true; // for main menu
    }
}


// void rent(Customer customers[],int num_of_customers, movie movies[], int num_of_movies)
// {
//     bool repeat = true, date_good = false;
//     int selected,customer, match = 1, unrented_movies_count = ListUnrented(movies, num_of_movies);
//     std::string name, id;
//     std::string entered_date;
//     char delimiter1, delimiter2;
//     int y, m, d;
//     year_month_day today = year_month_day{ floor<days>(system_clock::now()) };
    
//     std::cout << "\n\n";
//     ListUnrented(movies, num_of_movies);
    
//     do
//     {
//         std::cout << "enter customer id: ";
//         std::getline(std::cin, id);
//         if (id == "0") return; //exit to main menu, note:the user will be notified at the begining of the program that entering 0 takes you back to main menu
//         std::cin.clear();
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
//         std::transform(id.begin(), id.end(), id.begin(), toupper); // c# ---> C#
//         if (isCustomerFound(customers, num_of_customers, id))
//         {
//             name = customers[getCustomerNum(customers, num_of_customers, id)].Name;
//             customer = getCustomerNum(customers, num_of_customers, id);
//         }
//         else 
//         {
//             std::cerr << "wrong id, please try again\n";
//             std::this_thread::sleep_for(std::chrono::seconds(3));
//         }
//     } while (!isCustomerFound(customers, num_of_customers, id));
    
//     std::cout << "pick a movie number: ";
//     while (repeat) 
//     {
//         std::cin >> selected;
//         if (selected == 0) return; //exit to main menu, note:the user will be notified at the begining of the program that entering 0 takes you back to main menu
//         if (std::cin.good() && selected < unrented_movies_count && selected > 0) {
//             repeat = false;
//         }
//         else {
//             std::cerr << "Invalid choice. Please select a valid movie number: ";
//             repeat = true;
//         }
//         std::cin.clear();
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//     }
//     for (int i = 0; i < num_of_movies; i++) 
//     {
//         if (!movies[i].Name.empty() && !movies[i].rented && match == selected)
//         {
//             std::cout << "movie: " << movies[i].Name << std::endl;
//             std::cout << "\tprice per day: " << movies[i].price << " EGP" << std::endl;
//             std::cout << "\toverdue fee per day: " << movies[i].fee << " EGP" << std::endl;
//             std::cout << "\tmovie rating:" << movies[i].rating << std::endl;
//             std::cout << "\thas been rented: " << movies[i].RentedCount << " times" << std::endl;
//             std::cout << "today is: "<< today <<std::endl;
//             while (!date_good)/*incomplete fail safe*/ {
//                 std::cout << "specify due date in this exact format yyyy-mm-dd : ";
//                 getline(std::cin, entered_date);
//                 if (entered_date == "0") return; //exit to main menu, note:the user will be notified at the begining of the program that entering 0 takes you back to main menu
//                 std::istringstream iss(entered_date);
//                 if (iss >> y >> delimiter1 >> m >> delimiter2 >> d && delimiter1 == '/' && delimiter2 == '/') {
//                     movies[i].DueDate = year(y) / month(m) / day(d);
//                 } //note to self: implement fail safe !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//             }
//             if(isFull(customers, customer))
//             {
//                 for (int k = 0; k < limit; k++)
//                 {
//                     if(customers[customer].CurrentlyRentedMovies[k].empty())
//                     {
//                         customers[customer].CurrentlyRentedMovies[k] = movies[i].Name;
//                         movies[i].rented = true;
//                         movies[i].RentedCount++;
//                         movies[i].CurrentRenter = name;
//                         break;
//                     } 
//                 }
//                 movies[i].rented = true;
//                 movies[i].RentedCount++;
//                 movies[i].CurrentRenter = name;
//                 movies_count++;
//             }
//             else
//             {
//                 std::cout << "You have reached your renting limit! return one or more movie!\n";
//                 std::this_thread::sleep_for(std::chrono::seconds(2));
//                 return;
//             }
            
//             // after he brings back the movie.  ???
//             // cust[customer].PreviouslyRentedMovies.push_back(movies[i].Name);
//         }
//         else if (!movies[i].Name.empty() && !movies[i].rented)
//         {
//             match++;
//         }
//     }
// }

//  void return_movie(Customer customer[], int cust_num, movie mov[], int mov_num) {
//      int num = 1, index, ans;
//      std::string movieName, ans, id;
//      for (std::string i : customer[cust_num].CurrentlyRentedMovies) {
//          std::cout << num << "." << i << std::endl;
//          num++;
//      }
//      std::cout << "enter number of the movie you wish to return: ";
//      if (is_num(ans) && ans < 9 && ans > 0) {
//         movieName = customer[cust_num].CurrentlyRentedMovies[ans - 1];
//         index = getMovieIndex(mov, mov_num, movieName);
//         mov[index].rented = false;
//         mov[index].CurrentRenter.clear();
//         mov[index].due = false;
//         mov[index].DueDate = date::year(3000) / date::month(10) / date::day(10);
//         customer[cust_num].CurrentlyRentedMovies[ans-1].clear();
//         std::cout << "would you like to rate the movie? y/n: ";
//         if (yes_no()) {
//             do
//             {
//                 rate(mov, mov_num, movieName, customer, cust_num, id);
//             } while (!rate(mov, mov_num, movieName, customer, cust_num, id));
//         }
//         else {
//             return; //back to main menu
//         }
//      }
//  }

int validate_due(movie& movie, bool isDateChanged, sys_days new_date) {
    auto now = std::chrono::system_clock::now();
    sys_days today;
    if (isDateChanged) {
        today = new_date;
    }
    else {
        today = floor<days>(now);
    }
    sys_days due = movie.DueDate;
    auto today_n = today.time_since_epoch();
    int today_int = today_n.count();
    auto due_n = due.time_since_epoch();
    int due_int = due_n.count();
    int diff=0;
    if (today > due) {
        movie.due = true;
        diff = today_int - due_int;
        return diff;
    }
    else {
        movie.due = false;
        return 0;
    }
}

 void ListDueAccounts(movie mov[],int num_of_movies, Customer cust[], int num_of_customers, bool isDateChanged, sys_days new_date)
 { //note for when u r debugging dummy, it updates the accounts right before listing them, no earlier
     int num = 1;
     for (int i = 0; i < num_of_movies;i++) {
         int days_due = validate_due(mov[i], isDateChanged, new_date);
         if (mov[i].due = true) {
             for (int j = 0;j < num_of_customers;j++) {
                 if (mov[i].CurrentRenter == cust[j].Name) {
                     std::cout << num << "." << cust[j].Name << std::endl;
                     std::cout << "id: " << cust[j].Id << std::endl;
                     std::cout << "phone number: " << cust[j].PhoneNumber << std::endl;
                     std::cout << "due movie: " << mov[i].Name << std::endl;
                     std::cout << "movie was due: " << days_due << "days ago.\n" << std::endl;
                     std::cout << "due fees up till now: " << days_due * mov[i].fee << std::endl;
                 }
             }
             num++;
         }
     }
 }




void MainMenu(Customer customers[], int size_of_customers, movie movies[], int size_of_movies) 
{ 
    int customers_count = getCustomersCount(customers, size_of_customers);
    int movies_count = getMoviesCount(movies, size_of_movies);
    bool valid = false,isDateChanged = false;
    int choice;
    sys_days new_date, today;
    auto now = std::chrono::system_clock::now();
    today = floor<days>(now);
    std::string check;
    
    std::string menu[] = {
        "\n-----------------------------\n",
        "press  1: Rent a movie",
        "press  2: Rate a movie",
        "press  3: Edit a rating",
        "press  4: Return a movie",
        "press  5: List all customers",
        "press  6: Add a customer",
        "press  7: List all movies",
        "press  8: List rented movies",
        "press  9: List unrented movies",
        "press  10: List top 10 rented movies",
        "press  11: List top 10 rated movies"
    };
    const int menuSize = sizeof(menu)/sizeof(menu[0]);
    
    check = login();
    while (check=="user" || check=="admin") { //infinite loop till log out or termination
        if (isDateChanged) {
            std::cout << "\ncurrent date: " << new_date;
        }
        else {
            std::cout << "\n\ncurrent date: " << today;
        }
        
        for(int i = 0; i < menuSize; i++)
        {
            std::cout << menu[i] << '\n';
        }
        if(check=="user")
        {
            std::cout << "press  12: Log out\n"; // done
        }
        else if (check=="admin") 
        {
            std::cout << "press  12: Add a movie\n";
            std::cout << "press  13: Delete a movie\n"; // done
            std::cout << "press  14: Delete a customer\n"; // done
            std::cout << "press  15: set date manually\n";
            std::cout << "press  16: switch user account\n"; // done
        }
        std::cout << "press  0: Exit\n";
        std::cout << "\nat any point in time, if you wish to go back to main menu enter \"0\"\n";
        std::cout << "-----------------------------\n";
        while (!valid) 
        {
            std::cin >> choice;
            if ((std::cin.good() && choice <= 12 && choice > -1) || (std::cin.good() && check=="admin" && choice <= 16 && choice > -1)) 
            {
                valid = true;
            }
            else 
            {
                std::cerr << "Invalid choice. Please enter a valid choice: ";
                valid = false;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice)
        {
        case 0: // exit
            return;
        case 1: // rent
            // rent(customers,num_of_customers, movies,num_of_movies);
            break;
        case 2: // rate
        {
            std::string movieName,id;
            std::transform(id.begin(), id.end(), id.begin(), toupper); // c# ---> C#
            std::transform(movieName.begin(), movieName.end(), movieName.begin(), tolower);
            
            do
            {
                std::cout << "Enter movie name: ";
                getline(std::cin, movieName);
                if(!isMovieFound(movies,movies_count,movieName))
                {
                    std::cout << "This film doesn't exist! please try again.\n";
                    continue;
                }
                std::cout << "Enter customer id: ";
                getline(std::cin, id);
                if(!isCustomerFound(customers,customers_count,id))
                {
                    std::cout << "Wrong ID! please try again.\n";
                }
            } while(!isCustomerFound(customers,customers_count,id) || !isMovieFound(movies,movies_count,movieName));

            bool done = rate(movies,movies_count,movieName, customers,customers_count,id);
            while (!done)
            {
                done = rate(movies,movies_count,movieName, customers,customers_count,id);
            }
            
            std::this_thread::sleep_for(std::chrono::seconds(3));
            break;
        }
        case 3: // edit rate
        {
            std::string movieName,id;
            std::transform(id.begin(), id.end(), id.begin(), toupper); // c# ---> C#
            std::transform(movieName.begin(), movieName.end(), movieName.begin(), tolower);
            
            do
            {
                std::cout << "Enter movie name: ";
                getline(std::cin, movieName);
                if(!isMovieFound(movies,movies_count,movieName))
                {
                    std::cout << "This film doesn't exist! please try again.\n";
                    continue;
                }
                std::cout << "Enter customer id: ";
                getline(std::cin, id);
                if(!isCustomerFound(customers,customers_count,id))
                {
                    std::cout << "Wrong ID! please try again.\n";
                }
            } while(!isCustomerFound(customers,customers_count,id) || !isMovieFound(movies,movies_count,movieName));

            bool done = editRating(movies,movies_count,movieName, customers,customers_count,id); 
            while(!done)
            {
                done = editRating(movies,movies_count,movieName, customers,customers_count,id);
            }
            std::this_thread::sleep_for(std::chrono::seconds(3));
            break;
        }
        case 4: // return a movie
            break;
        case 5: // list all customer
            listCustomers(customers, customers_count);
            break;
        case 6: // add new customer
            addNewCustomer(customers, size_of_customers, customers_count);
            break;
        case 7: // list all movies
            ListMovies(movies, movies_count);
            break;
        case 8: // list rented
            listRented(movies, movies_count);
            break;
        case 9: // list unrented
            ListUnrented(movies, movies_count);
            break;
        case 10: // top 10 rented
            break;
        case 11: // top 10 rated
            break;
        case 12: // log out for user --- add new movie for admin.
        {
            if(check=="user")
            {
                check = login();
            }
            else if (check=="admin")
            {
                // add new movie
            }
            break;
        }
        case 13: // delete movie
        {
            std::string movieName;
            std::transform(movieName.begin(), movieName.end(), movieName.begin(), tolower);
            do
            {
                std::cout << "Enter movie name: ";
                getline(std::cin, movieName);
                if(!isMovieFound(movies,movies_count,movieName))
                {
                    std::cout << "This film doesn't exist! please try again.\n";
                }
            } while(!isMovieFound(movies, movies_count, movieName));
            
            deleteMovie(movies, movies_count, movieName);
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }
        case 14: // delete customer
        {
            std::string id;
            std::transform(id.begin(), id.end(), id.begin(), toupper);
            do
            {
                std::cout << "Enter customer id: ";
                getline(std::cin, id);
                if(!isCustomerFound(customers,customers_count,id))
                {
                    std::cout << "This customer doesn't exist! Please try again.\n";
                }
            } while(!isCustomerFound(customers,customers_count,id));
            
            deleteCustomer(customers, customers_count, id);
            std::this_thread::sleep_for(std::chrono::seconds(3));
            break;
        }
        case 15: // done
            isDateChanged = ChangeDate(new_date);
            break;
        case 16: // logout for admin
            check = login();
            break;
        default:
            std::cerr << "Validation error in the main menu function, please contact your IT provider\nexiting program in 3 seconds";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            return;
        }
        valid = false; //allows you to retake input from usr
    }
}
