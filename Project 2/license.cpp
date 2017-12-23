//
//  main.cpp
//  Project 2
//
//  Created by Jon Chon on 10/7/16.
//  Copyright © 2016 Jon Chon. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main() {
    
    string identification;                          //initializing variables
    double revenue;
    string country;
    double licenseFee;
    int flag = 0;
    int countryFlag = 0;
    
    cout.setf(ios::fixed);                          //setting decimals to 3 digits
    cout.precision(3);
    
    cout << "Identification: ";
    getline(cin, identification);
    
    cout << "Expected revenue (in millions): ";
    cin >> revenue;
    
    cout << "Country: ";
    cin.ignore(1000, '\n');
    getline(cin, country);
    if (country == "UAE" || country == "Turkey")    //sets up special condition if country is UAE or Turkey
        countryFlag = 1;
    
    cout << "---" << endl;                          //end of user input
    
    if (revenue <= 20){                             //takes care of the first 20 million
        licenseFee = (0.181 * revenue);
        
    }
    else{
        licenseFee = (0.181 * 20);
        revenue -= 20;
        flag = 1;
    }
    
    if (flag == 1){                                 //takes care of next 30 million
        if (revenue <= 30){
            if (countryFlag == 1){
                licenseFee += (.217 * revenue);
            }
            else{
                licenseFee += (.203 * revenue);
            }
            flag = 0;
        }
        else{
            if (countryFlag == 1){
                licenseFee += (.217 * 30);
            }
            else{
                licenseFee += (.203 * 30);
            }
            revenue -= 30;
        }
    }
    
    if (flag == 1){                                 //takes care of anything over 50 million
        licenseFee += (.23 * revenue);
    }
    
    if (identification == "")                       //Prints the final line
        cout << "You must enter a property identification." << endl;
    else if (revenue < 0)
        cout << "The expected revenue must be nonnegative." << endl;
    else if (country == "")
        cout << "You must enter a country." << endl;
    else
        cout << "The license fee for " << identification << " is $" << licenseFee << " million." << endl;
}
