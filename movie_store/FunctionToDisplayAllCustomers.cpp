// Customer customers[];
Customer customers[10] = {{"name1", "11111111111","1234", {"movie1","movie2","movie3"}}, {"name2","22222222222", "5678", {"movie1","movie2","movie3"}}};

void list(Customer customers[], int number_of_customers)
{
    for (int i = 0;i < number_of_customers;i++)
    {
        cout << "Customer ID :" << customers[i].Id << endl;
        cout << "Name :" << customers[i].Name << endl;
        cout << "Phone Number :" << customers[i].PhoneNumber << endl;
        if (customers[i].CurrentlyRentedMovies != "")
        {
            cout << "Currently Renting : " << customers[i].CurrentlyRentedMovies << endl;
        }
        else
        {
            cout << "Currently Renting : 0" << endl;
        }
      
    }
}

void list(Customer customers[], int number_of_customers)
{
    for (int i = 0; i < number_of_customers; i++)
    {
        cout << "Customer ID :" << customers[i].Id << endl;
        cout << "Name :" << customers[i].Name << endl;
        cout << "Phone Number :" << customers[i].PhoneNumber << endl;
        if (!customers[i].CurrentlyRentedMovies[0].empty())
        {
            cout << "Currently Renting : ";
            
            for(int j=0; j<limit; j++)
            {
                if(customers[i].CurrentlyRentedMovies[j].empty()) { cout << "."; break; }
                if(j>0) cout <<", ";
                // cout << '\n';
                cout <<customers[i].CurrentlyRentedMovies[j];
            }
            cout << '\n';
        }
        else
        {
            cout << "Currently Renting : 0" << endl;
        }
      
    }
}
