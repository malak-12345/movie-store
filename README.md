# include <iostream>
# include <vector>
# include<string>
# include<ctime>
using namespace std;
struct date {
    int year, month, day;
    bool isAfter(const date& other)
        const {
        if (year != other.year)
            return year > other.year;
        if (month != other.month)
            return month > other.month;
        if (day != other.day)
            return day > other.day;
       }
    };
struct customer 
{
    string name;
    int id;
    string phonenumber;
    vector <string>
        previouslyRentedMovies;
    string CurrentlyRentedMovie;
};

struct movie  
{
  string Name;
    int RentedCount ;
    bool  isrented;
    date DueDate;
    int CurrentCustomerID;
    vector<int> AllRatings;
};
date getCurrentDate()
{
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    return date{ now->tm_mday,now->tm_mon + 1, now->tm_year + 1900 };
}
void listOverdueMoviesAndCustomers(const vector<Movie>& movies, const vector<Customer>& customers, const Date& currentDate) {
    for (const auto& movie : movies) {
        if (movie.isRented && movie.dueDate.isAfter(currentDate)) {
            cout << "Movie: " << movie.name << " is overdue." << std::endl;
            cout << "Due date: " << movie.dueDate.day << "/" << movie.dueDate.month << "/" << movie.dueDate.year << std::endl;
            for (const auto& customer : customers) {
                if (customer.id == movie.currentCustomerID) {
                    cout << "Customer: " << customer.name << " (ID: " << customer.id << ")" << std::endl;
                    cout << "Phone: " << customer.phoneNumber << std::endl;
                    break;
                }
            }
            std::cout << "------------------------" << endl;
        }
    }
}
 if(!found)
 {
    cout << "No overdue movies found." << endl;
 }


int main() {
    
        vector<Customer> customers = {
        {"Ahmed", 1, "01012345678", {"Movie A"}, "Movie B"},
        {"Sara", 2, "01087654321", {"Movie C"}, ""}
    };

   vector<Movie> movies = {
        {"Movie B", 50.0, 4.5, 10, true, {15, 4, 2025}, 1, {5, 4, 5}},
        {"Movie C", 40.0, 4.0, 5, false, {10, 4, 2025}, 0, {4, 4, 4}}
    };

    Date currentDate = getCurrentDate();

    listOverdueMoviesAndCustomers(movies, customers, currentDate);

    return 0;
}

