#include "movie.h"
#include "customer.h"
using namespace date;
using namespace std::chrono;

void ListMovies(const movie movies[], const int& movies_count) {
    int MovieNum = 1;
    if (movies_count != 0) {
        for (int i = 0;i <= movies_count;i++) {
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
    else {
        std::cerr << "no movies to display, please add a movie first" << std::endl;
    }
}

//will always be called before renting and sometimes separately
int ListUnrented(const movie movies[], const int& movies_count) {
    int MovieNum = 1;
    if (movies_count != 0) {
        for (int i = 0;i <= movies_count;i++) {
            if (!movies[i].rented) {
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


double rate(movie& movie) { //using a weighted rating algorithm
    int Rating;
    bool ValidRating = false;
    double FinalRating = 0.0;
    int a, b, c, d, e;
    std::cout << "on a scale from 1 to 5, how much would you rate this movie?: ";
    while (!ValidRating) {
        //Rating = 0;
        a = 0;
        b = 0;
        c = 0;
        d = 0;
        e = 0;
        std::cin >> Rating;
        if (Rating == 0) return; //exit to main menu, note:the user will be notified at the begining of the program that entering 0 takes you back to main menu
        if (std::cin.good() && Rating > 0 && Rating < 6) {
            ValidRating = true;
        }
        else {
            std::cerr << "Invalid Rating. Please enter a whole number between 1 and 5.\n";
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
        if (!movie.AllRatings.size() == 0) {
            for (int i : movie.AllRatings) {
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
        }
        switch (Rating)
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
            break;
        }
    FinalRating = (a * 1 + b * 2 + c * 3 + d * 4 + e * 5) / (a + b + c + d + e);
    std::cout << "\nthank you for your review!!! " << std::endl;
    return FinalRating;
}




void Rent(Customer cust[], int movies_count, movie movies[]){
    bool CustomerFound = false, repeat = true, date_good=false;
    int selected,customer, match = 1, unrented_movies_count = ListUnrented(movies, movies_count);
    std::string name, id;
    std::string entered_date;
    char delimiter1, delimiter2;
    int y, m, d;
    year_month_day today = year_month_day{ floor<days>(system_clock::now()) };
    std::cout << "\n\n";
    ListUnrented(movies, movies_count);
    while (!CustomerFound) {
        std::cout << "enter customer id: ";
        std::getline(std::cin, id);
        if (id == "0") return; //exit to main menu, note:the user will be notified at the begining of the program that entering 0 takes you back to main menu
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int i = 0; i < customers_count;i++) {
            if (cust[i].Id == id) {
                CustomerFound = true;
                name = cust[i].Name;
                customer = i;
                break;
            }
            else {
                std::cerr << "wrong name or id, please try again\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            }
        }
    }
    std::cout << "pick a movie number: ";
    while (repeat) {
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
    for (int i = 0; i < movies_count;i++) {
        if (!movies[i].rented && match == selected) {
            std::cout << "movie:   " << movies[i].Name << std::endl;
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
            movies[i].rented = true;
            movies[i].RentedCount++;
            movies[i].CurrentRenter = name;
            cust[customer].CurrentlyRentedMovies[cust[customer].CurrentlyRentedMovies_count] = movies[i].Name;
            cust[customer].PreviouslyRentedMovies.push_back(movies[i].Name);
        }
        if (!movies[i].rented) {
            match++;
        }
    }
}

date::day validate_due(movie& movie) {

}

void ListDueAccounts(movie(&mov)[movies_max])
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