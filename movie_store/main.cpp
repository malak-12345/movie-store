#include "mainmenu.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>


void load_movies(movie mov[], int mov_count, const std::string& movies){
    std::ifstream infile(movies);
    if (infile.is_open()) {
        infile >> mov_count;
        for (int i = 0; i < mov_count; i++) {
            std::getline(infile >> std::ws, mov[i].name); //BTW std::ws gets rid of any leading whitespaces
            infile >> mov[i].price;
            infile >> mov[i].fee;
            infile >> mov[i].rentedCount;
            infile >> std::boolalpha >> mov[i].rented;
            std::getline(infile >> std::ws, mov[i].currentRenter);
            infile >> std::boolalpha >> mov[i].due;
            // year_month_day read_date;
            int year, month, day;
            char del1, del2; 
            
            if (infile >> year >> del1 >> month >> del2 >> day && year >= 2025 && del1 == '/' && del2 == '/') 
            {
                mov[i].dueDate = date::year(year) / date::month(month) / date::day(day);
            } 
            else
            {
                std::cerr << "Wrong format!\n";
                continue; 
            }
            // std::getline(infile >> std::ws, read_date);
            //std::getline(infile >> std::ws, mov[i].DueDate);     //fix!!!!!!!!!!!!!!!!!!!!!!!!!!
            infile >> mov[i].rating;
            int ratings_size;
            infile >> ratings_size;
            mov[i].allRatings.resize(ratings_size);
            std::string opening_brace;
            if (std::getline(infile >> std::ws, opening_brace) && opening_brace == "{"){
                for(int j = 0; j < ratings_size; j++){
                    infile >> mov[i].allRatings[j];
                }
                std::string closing_brace;
                std::getline(infile >> std::ws, closing_brace);
            }
            else{
                std::cerr << "error taking in all ratings vector for movie: " << mov[i].name << std::endl;
            }
        }
        infile.close();
    }
    else{
        std::cerr << "Unable to open file " << movies << " for reading, contact your IT provider" << std::endl;
    }
}

customer c[10] = {"loai", "1212121212", "1234", {"movie1"},{},{},{"8673383237229520","123", date::year(2025)/date::month(5)}};
movie m[10] = {"movie1", "loai", 3, 100, 10, 12, true, false, {}, /*date::year(2025) / date::month(5) / date::day(3)*/};



int main()
{
    // auto m = date::month(7);
    // std::cout << m.ok() << '\n';
    MainMenu(c,10,m,10);
}