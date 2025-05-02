#include "mainmenu.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>


// void load_movies(movie mov[], int mov_count, const std::string& movies){
//     std::ifstream infile(movies);
//     if (infile.is_open()) {
//         infile >> mov_count;
//         for (int i = 0; i < mov_count; i++) {
//             std::getline(infile >> std::ws, mov[i].name); //BTW std::ws gets rid of any leading whitespaces
//             infile >> mov[i].price;
//             infile >> mov[i].fee;
//             infile >> mov[i].rentedCount;
//             infile >> std::boolalpha >> mov[i].rented;
//             std::getline(infile >> std::ws, mov[i].currentRenter);
//             infile >> std::boolalpha >> mov[i].due;
//             // year_month_day read_date;
//             int year, month, day;
//             char del1, del2; 
            
//             if (infile >> year >> del1 >> month >> del2 >> day && year >= 2025 && del1 == '/' && del2 == '/') 
//             {
//                 mov[i].dueDate = date::year(year) / date::month(month) / date::day(day);
//             } 
//             else
//             {
//                 std::cerr << "Wrong format!\n";
//                 continue; 
//             }
//             // std::getline(infile >> std::ws, read_date);
//             //std::getline(infile >> std::ws, mov[i].DueDate);     //fix!!!!!!!!!!!!!!!!!!!!!!!!!!
//             infile >> mov[i].rating;
//             int ratings_size;
//             infile >> ratings_size;
//             mov[i].allRatings.resize(ratings_size);
//             std::string opening_brace;
//             if (std::getline(infile >> std::ws, opening_brace) && opening_brace == "{"){
//                 for(int j = 0; j < ratings_size; j++){
//                     infile >> mov[i].allRatings[j];
//                 }
//                 std::string closing_brace;
//                 std::getline(infile >> std::ws, closing_brace);
//             }
//             else{
//                 std::cerr << "error taking in all ratings vector for movie: " << mov[i].name << std::endl;
//             }
//         }
//         infile.close();
//     }
//     else{
//         std::cerr << "Unable to open file " << movies << " for reading, contact your IT provider" << std::endl;
//     }
// }

customer c[10] = {"loai", "1212121212", "1234", {"movie1"},{},{},{"8673383237229520","123", date::year(2025)/date::month(5)}};
movie m[10] = {"movie1", "loai", 3, 100, 10, 12, 10, true, false, {}, date::year(2025) / 5 / 12};


void save_movies(double cashRegister, movie mov[], int mov_count, const std::string& movies)
{
    std::ofstream outfile(movies);

    if (outfile.is_open()) 
    {
        outfile << cashRegister << std::endl;
        outfile << mov_count << std::endl;
        for (int i = 0; i < mov_count; i++) 
        {
            outfile << mov[i].name << std::endl;
            outfile << mov[i].price << std::endl;
            outfile << mov[i].fee << std::endl;
            outfile << mov[i].rentedCount << std::endl;
            outfile << std::boolalpha << mov[i].rented << std::endl;
            outfile << mov[i].currentRenter << std::endl;
            outfile << std::boolalpha << mov[i].due << std::endl;
            outfile << mov[i].rentalDays << std::endl;
            outfile << mov[i].dueDate << std::endl;
            outfile << mov[i].rating << std::endl;
            outfile << mov[i].allRatings.size() << std::endl;
            outfile << "{" << std::endl;
            for (int rating : mov[i].allRatings) 
            {
                outfile << rating << std::endl;
            }
            outfile << "}" << std::endl;
        }
        outfile.close();
        std::cout << "Data successfully saved"<< std::endl;
    } else {
        std::cerr << "Unable to open file " << movies <<"please try saving manually before terminating the program,\nif the problem persists please contact your IT provider" << std::endl;
    }
}

void save_customers(customer cust[], int cust_count, const std::string& file_name)
{
    
    std::ofstream outfile(file_name);
    if (outfile.is_open()) 
    {
        outfile << cust_count << std::endl;
        for (int i = 0; i < cust_count; i++) 
        {
            outfile << cust[i].id << std::endl;
            outfile << cust[i].name << std::endl;
            outfile << cust[i].phoneNumber << std::endl;
            outfile << cust[i].coins << std::endl;
            outfile << cust[i].SC_balance << std::endl;
            outfile << cust[i].SC_passwrd << std::endl;
            outfile << cust[i].creditcard.cardNumber << std::endl;
            outfile << cust[i].creditcard.ccv << std::endl;
            // outfile << cust[i].creditcard.date << std::endl;
            outfile << std::boolalpha << cust[i].SC << std::endl;
            //________
            outfile << "{" << std::endl;    
            for(int j = 0; j < 8; j++){
                if(!cust[i].currentlyRentedMovies[j].empty()){
                    outfile << cust[i].currentlyRentedMovies[j] << std::endl;
                }
                else{  
                    break;
                }
            }
            outfile << "}" << std::endl;
            //_______
            outfile << cust[i].previouslyRentedMovies.size() << std::endl;
            outfile << "{" << std::endl;
            for (std::string mov : cust[i].previouslyRentedMovies) {
                outfile << mov << std::endl;
            }
            outfile << "}" << std::endl;

        }
        outfile.close();
        std::cout << "Data successfully saved"<< std::endl;
    } 
    else 
    {
        std::cerr << "Unable to open file " << file_name <<"please try saving manually before terminating the program,\nif the problem persists please contact your IT provider" << std::endl;
    }
}


int main()
{
    // save_customers(c,1,"out1.txt");
    // save_movies(10, m, 1, "out2.txt");
    MainMenu(c,10,m,10);
}