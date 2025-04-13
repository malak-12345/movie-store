#include "customer.h"

std::string generateId(){
    std::string Id = "C#";
    srand(time(0)); // changes seed
    for (int i =1; i<=10; i++){
        Id+= std::to_string(rand()%10); // generates number from 0 -> 9 and adds it
    }
    
    return Id;
}

void addNewCustomer(){
}