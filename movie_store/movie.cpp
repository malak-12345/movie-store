#include "admin.h" //thus movie.h and customer.h and date.h are included too

using namespace date;
using namespace std::chrono;

//-------------------------utilities-----------------------------
bool isCustomerFound(Customer customers[], int num_of_customers ,std::string& id)
{
    for(int i = 0; i < num_of_customers; i++)
    {
        if(customers[i].Id == id) return true;
    }
    return false;
}
int getCustomerNum(Customer customers[], int number_of_customers, std::string& id)
{
    int customerNum = 0;
    for(int i = 0; i < number_of_customers; i++)
    {
        if(customers[i].Id == id)
        {
            return customerNum;
        }
        customerNum++;
    }
}
bool isMovieFound(movie movies[], int num_of_movies, std::string& movieName)
{
    for(int i = 0; i < num_of_movies; i++)
    {
        if(movies[i].Name == movieName) return true;
    }
    return false;
} 
int getMovieNum(movie movies[], int num_of_movies, std::string& movieName)
{
    int movieNum = 0;
    for(int i = 0; i < num_of_movies; i++)
    {
        if(movies[i].Name == movieName)
        {
            return movieNum;
        }
        movieNum++;
    }
}
bool isMovieRentedByCustomer(Customer customers[], int num_of_customers ,std::string& id, std::string& movieName)
{
    int customerNum = getCustomerNum(customers, num_of_customers, id);
    for (int i = 0; i < limit; i++)
    {
        if(customers[customerNum].PreviouslyRentedMovies[i] == movieName) return true;
    }
    
    return false;
}
bool isFull(Customer customers[], int customerNum)
{
    for(int i = 0; i < limit; i++)
    {
        if(customers[customerNum].CurrentlyRentedMovies[i].empty()) return true; 
    } 
    
    return false;
}
//-------------------------utilities-----------------------------


void ListMovies(const movie movies[], const int& movies_count) {
    int MovieNum = 1;
    if (movies_count != 0) 
    {
        for (int i = 0; i < movies_count; i++) 
        {
            if(!movies[i].Name.empty())
            {
                std::cout << MovieNum << ". " << movies[i].Name << std::endl;
                std::cout << "\tprice: " << movies[i].price << " EGP" << std::endl;
                std::cout << "\trating:" << movies[i].rating << std::endl;
                std::cout << "\trented: " << movies[i].RentedCount << " times" << std::endl;
                if (movies[i].rented) {
                    std::cout << "\trented status: " << "rented" << std::endl;
                }
                else {
                    std::cout << "\trented status: " << "not rented" << std::endl;
                }
                std::cout << "\n";
                MovieNum++;
            }
        }
    }
    else {
        std::cerr << "no movies to display, please add a movie first" << std::endl;
    }
}
//will always be called before renting and sometimes separately
int ListUnrented(const movie movies[], const int& movies_count) {
    int MovieNum = 1;
    if (movies_count != 0) {
        for (int i = 0; i < movies_count; i++) {
            if (!movies[i].rented && !movies[i].Name.empty()) {
                std::cout << MovieNum << ". " << movies[i].Name << std::endl;
                MovieNum++;
            }
        }
        if (MovieNum == 1) { //meaning there are movies on the system but no movies were displayed, aka they are all rented 
            std::cerr << "there are currently no available movies to rent" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
            // main_menu();
        }
    }else {
        std::cerr << "there are currently no movies on the system, please add a movie first" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        //exit to main menu main_menu();
    }
    return MovieNum;
}

// double rate(movie& movie) { //using a weighted rating algorithm
//     int Rating;
//     bool ValidRating = false;
//     double FinalRating = 0.0;
//     int a, b, c, d, e;
//     std::cout << "on a scale from 1 to 5, how much would you rate this movie?: ";
//     while (!ValidRating) {
//         //Rating = 0;
//         a = 0;
//         b = 0;
//         c = 0;
//         d = 0;
//         e = 0;
//         std::cin >> Rating;
//         if (Rating == 0) return; //exit to main menu, note:the user will be notified at the begining of the program that entering 0 takes you back to main menu
//         if (std::cin.good() && Rating > 0 && Rating < 6) {
//             ValidRating = true;
//         }
//         else {
//             std::cerr << "Invalid Rating. Please enter a whole number between 1 and 5.\n";
//         }
//         std::cin.clear();
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//     }
//         if (!movie.AllRatings.size() == 0) {
//             for (int i : movie.AllRatings) {
//                 switch (i)
//                 {
//                 case 1:
//                     a++;
//                     break;
//                 case 2:
//                     b++;
//                     break;
//                 case 3:
//                     c++;
//                     break;
//                 case 4:
//                     d++;
//                     break;
//                 case 5:
//                     e++;
//                     break;
//                 default:
//                     std::cerr << "error in the ratings vector, please contact your IT provider" << std::endl;
//                     break;
//                 }
//             }
//         }
//         switch (Rating)
//         {
//         case 1:
//             a++;
//             break;
//         case 2:
//             b++;
//             break;
//         case 3:
//             c++;
//             break;
//         case 4:
//             d++;
//             break;
//         case 5:
//             e++;
//             break;
//         default:
//             break;
//         }
//     FinalRating = (a * 1 + b * 2 + c * 3 + d * 4 + e * 5) / (a + b + c + d + e);
//     std::cout << "\nthank you for your review!!! " << std::endl;
//     return FinalRating;
// }

bool rate(movie movies[], int num_of_movies, std::string& movieName, 
          Customer customers[], int num_of_customers ,std::string& id)
{
    if (isMovieRentedByCustomer(customers, num_of_customers, id, movieName))
    {
        int rating = 0;
        int movieNum = getMovieNum(movies, num_of_movies, movieName);
        std::cout << "Rating: " << movieName << "\n\n";
        std::cout << "1: *\n" <<
                     "2: **\n" <<
                     "3: ***\n" <<
                     "4: ****\n" <<
                     "5: *****\n\n";
        
        std::cout << "Pick a rating from above: ";
        std::cin >> rating;
        switch (rating)
        {
        case 1:
            movies[movieNum].AllRatings.push_back(1);
            break;                    
        case 2:
            movies[movieNum].AllRatings.push_back(2);
            break;                    
        case 3:
            movies[movieNum].AllRatings.push_back(3);
            break;                    
        case 4:
            movies[movieNum].AllRatings.push_back(4);
            break;                    
        case 5:
            movies[movieNum].AllRatings.push_back(5);
            break;
        
        default:
            std::cout << "Please pick a right rating\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return false;
        }
    } 
    else 
    {
        std::cout << "This movie isn't rented by the customer!\n";
        return true; // for main menu
    }
    std::cout << "Thanks for your rating!\n";
    return true; // for main menu
}

double calcRatings(movie movies[], int num_of_movies, std::string& movieName)
{
    int a, b, c, d, e;
    int movieNum = getMovieNum(movies, num_of_movies, movieName);
    double FinalRating = 0.0;
        
    if (!movies[movieNum].AllRatings.size() == 0) 
    { 
        for (int i : movies[movieNum].AllRatings) 
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
                std::cerr << "error in the ratings vector, please contact your IT provider" << std::endl;
                break;
            }
        } 
            FinalRating = (a * 1 + b * 2 + c * 3 + d * 4 + e * 5) / (a + b + c + d + e);
            return FinalRating;
    }
    else
    {
        std::cout << "There are no ratings!\n";
        return 0; //for main menu
    }
}

void rent(Customer customers[],int num_of_customers, movie movies[], int num_of_movies)
{
    bool repeat = true, date_good = false;
    int selected,customer, match = 1, unrented_movies_count = ListUnrented(movies, num_of_movies);
    std::string name, id;
    std::string entered_date;
    char delimiter1, delimiter2;
    int y, m, d;
    year_month_day today = year_month_day{ floor<days>(system_clock::now()) };
    
    std::cout << "\n\n";
    ListUnrented(movies, num_of_movies);
    
    do
    {
        std::cout << "enter customer id: ";
        std::getline(std::cin, id);
        if (id == "0") return; //exit to main menu, note:the user will be notified at the begining of the program that entering 0 takes you back to main menu
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::transform(id.begin(), id.end(), id.begin(), toupper); // c# ---> C#
        if (isCustomerFound(customers, num_of_customers, id))
        {
            name = customers[getCustomerNum(customers, num_of_customers, id)].Name;
            customer = getCustomerNum(customers, num_of_customers, id);
        }
        else 
        {
            std::cerr << "wrong id, please try again\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    } while (!isCustomerFound(customers, num_of_customers, id));
    
    std::cout << "pick a movie number: ";
    while (repeat) 
    {
        std::cin >> selected;
        if (selected == 0) return; //exit to main menu, note:the user will be notified at the begining of the program that entering 0 takes you back to main menu
        if (std::cin.good() && selected < unrented_movies_count && selected > 0) {
            repeat = false;
        }
        else {
            std::cerr << "Invalid choice. Please select a valid movie number: ";
            repeat = true;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    for (int i = 0; i < num_of_movies; i++) 
    {
        if (!movies[i].Name.empty() && !movies[i].rented && match == selected)
        {
            std::cout << "movie: " << movies[i].Name << std::endl;
            std::cout << "\tprice per day: " << movies[i].price << " EGP" << std::endl;
            std::cout << "\toverdue fee per day: " << movies[i].fee << " EGP" << std::endl;
            std::cout << "\tmovie rating:" << movies[i].rating << std::endl;
            std::cout << "\thas been rented: " << movies[i].RentedCount << " times" << std::endl;
            std::cout << "today is: "<< today <<std::endl;
            while (!date_good)/*incomplete fail safe*/ {
                std::cout << "specify due date in this exact format yyyy-mm-dd : ";
                getline(std::cin, entered_date);
                if (entered_date == "0") return; //exit to main menu, note:the user will be notified at the begining of the program that entering 0 takes you back to main menu
                std::istringstream iss(entered_date);
                if (iss >> y >> delimiter1 >> m >> delimiter2 >> d && delimiter1 == '/' && delimiter2 == '/') {
                    movies[i].DueDate = year(y) / month(m) / day(d);
                } //note to self: implement fail safe !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            }
            if(isFull(customers, customer))
            {
                for (int k = 0; k < limit; k++)
                {
                    if(customers[customer].CurrentlyRentedMovies[k].empty())
                    {
                        customers[customer].CurrentlyRentedMovies[k] = movies[i].Name;
                        movies[i].rented = true;
                        movies[i].RentedCount++;
                        movies[i].CurrentRenter = name;
                        break;
                    } 
                }
            }
            else
            {
                std::cout << "You have reached your renting limit! return one or more movie!\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                return;
            }
            
            // after he brings back the movie.  ???
            // cust[customer].PreviouslyRentedMovies.push_back(movies[i].Name);
        }
        else if (!movies[i].Name.empty() && !movies[i].rented)
        {
            match++;
        }
    }
}

date::day validate_due(movie& movie) {

}

void ListDueAccounts(movie(&mov)[movies_max], Customer customers[])
{ //fyi it updates the accounts before listing them
    int num = 1;
    for (int i = 0;i < movies_max;i++) {
        validate_due(mov[i]);
    }
    for (int i = 0; i < movies_max;i++) {
        if (mov[i].due = true) {
            int days_due = validate_due(/*args*/);
            for (int j = 0;j < customer_max;j++) {
                if (mov[i].CurrentRenter == cust[j].name) {
                    std::cout << num << "." << cust[j].name << std::endl;
                    std::cout << "id: " << cust[j].Id << std::endl;
                    std::cout << "phone number: " << cust[j].PhoneNumber << std::endl;
                    std::cout << "movie was due: " << days_due << "days ago.\n" << std::endl;
                    std::cout << "due fees: " << days_due * mov[i].fee << std::endl;
                }
            }
            num++;
        }
    }
}




void MainMenu(Customer customers[], int num_of_customers, movie movies[], int num_of_movies) { 
    bool is_admin = false, is_user = false, valid = false;
    int choice, check;
    std::cout << "note that if you wish at any point in time to go back or exit press 0\n";
    check = login();
    if (check == 0) {
        return; //terminate program
    }
    if (check == 1) {
        is_admin = true;
    }
    if (check == 2) {
        is_user = true;
    }
    while (is_admin || is_user) { //infinite loop till log out or termination
        std::cout << "" << std::endl;
        std::cout << "press  1: Rent a movie" << std::endl;
        std::cout << "press  2: Rate a movie" << std::endl;
        std::cout << "press  3: Return a movie" << std::endl;
        std::cout << "press  4: List all customers" << std::endl;
        std::cout << "press  5: Add a customer" << std::endl;
        std::cout << "press  6: List rented movies" << std::endl; //the renter name and id must be displayed
        std::cout << "press  7: List top 10 rented movies" << std::endl;
        std::cout << "press  8: List top 10 rated movies" << std::endl;
        if (is_admin) {
            std::cout << "press  9: Add a movie" << std::endl;
            std::cout << "press  10: Delete a movie" << std::endl;
            std::cout << "press  11: Delete a customer" << std::endl;
            std::cout << "press  12: set date manually" << std::endl;
            std::cout << "press  13: log out" << std::endl;
        }
        std::cout << "press  0: Exit" << std::endl;
        std::cout << "\nat any point in time, if you wish to go back to main menu enter \"0\"" << std::endl;
        while (!valid) {
            std::cin >> choice;
            if ((std::cin.good() && choice <= 8 && choice > -1) || (std::cin.good() && is_admin && choice <= 13 && choice > -1)) {
                valid = true;
            }
            else {
                std::cerr << "Invalid choice. Please enter a valid choice: ";
                valid = false;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice)
        {
        case 0:
            return;
        case 1:
            rent(customers,num_of_customers, movies,num_of_movies);
            break;
        case 2:
        {
            std::string movieName,id;
            std::transform(id.begin(), id.end(), id.begin(), toupper); // c# ---> C#
            std::transform(movieName.begin(), movieName.end(), movieName.begin(), tolower);
            
            do
            {
                std::cout << "Enter movie name: ";
                getline(std::cin, movieName);
                if(!isMovieFound(movies,num_of_movies,movieName))
                {
                    std::cout << "This film doesn't exist! please try again.\n";
                    continue;
                }
                std::cout << "Enter customer id: ";
                getline(std::cin, id);
                if(!isCustomerFound(customers,num_of_customers,id))
                {
                    std::cout << "Wrong ID! please try again.\n";
                    continue;
                }
            } while(!isCustomerFound(customers,num_of_customers,id) || !isMovieFound(movies,num_of_movies,movieName));

            do
            {
                rate(movies,num_of_movies,movieName, customers,num_of_customers,id);
            } while (!rate(movies,num_of_movies,movieName, customers,num_of_customers,id));
            
            std::this_thread::sleep_for(std::chrono::seconds(3));
            break;
        }
        case 3:
            
            break;
        case 4:

            break;
        case 5:
            
            break;
        case 6:
            
            break;
        case 7:

            break;
        case 8:

            break;
        case 9:

            break;
        case 10:

            break;
        case 11:

            break;
        case 12:

            break;
        case 13:
            // is_admin = false
            //reinvoke login
            break;
        default:
            std::cerr << "validation error in the main menu function, please contact your IT provider\nexiting program in 3 seconds";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            return;
        }
        valid = false; //allows you to retake input from usr
    }








}
