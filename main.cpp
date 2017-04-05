//
//  main.cpp
//  worklog_number_of_days_after_duty_started
//
//  Created by Unname's Macbook on 4/2/17.
//
//

#include <iostream>
#include <map>
#include <array>


int calculate_days_based_on_year_in_between (int start_year, int current_year){
    
    int days_based_on_year = 0;
    for (int year = start_year + 1; year < current_year; year ++){
        if (year%4 == 0 && year%100 != 0){
            days_based_on_year = days_based_on_year + 366;
        }
        else{
            days_based_on_year = days_based_on_year + 365;
        }
    }
    return days_based_on_year;
    
}


int calculate_days_based_on_month_and_day (int start_year, int current_year, int start_month, int current_month, int start_day, int current_day){
    

    //31 days - month
    std::array<int,7> month_31 = {1, 3, 5, 7, 8, 10, 12};
    
    //month table regular year
    std::map<int,int> table_days_month_regular_year;
    
    for (int month = 1; month <= 12; month ++){
        if (std::find(std::begin(month_31), std::end(month_31), month) != std::end(month_31)){
            table_days_month_regular_year[month] = 31;
        }
        else{
            table_days_month_regular_year[month] = 30;
        }
    }
    
    
    //month table leap year
    std::map<int,int> table_days_month_leap_year;
    for (int month = 1; month <= 12; month ++){
        if (std::find(std::begin(month_31), std::end(month_31), month) != std::end(month_31)){
            table_days_month_leap_year[month] = 31;
        }
        else{
            table_days_month_leap_year[month] = 30;
        }
    }
    table_days_month_leap_year[2] = 29;

    
    //if in the same year
    int total_days_same_year = 0;
    if (current_year == start_year){
        if (start_year%4 == 0 && start_year%100 != 0){
            for (int month = start_month + 1; month < current_month; month ++){
                total_days_same_year = total_days_same_year + table_days_month_leap_year[month];
            }
            if (current_month == start_month){
                total_days_same_year = total_days_same_year + current_day - start_day;
            }
            else{
               total_days_same_year = total_days_same_year + (table_days_month_leap_year[start_month] - start_day) + current_day;
            }
        }
        
    else {
        for (int month = start_month + 1; month < current_month; month ++){
            total_days_same_year = total_days_same_year + table_days_month_leap_year[month];
        }
        if (current_month == start_month){
            total_days_same_year = total_days_same_year + current_day - start_day;
        }
        else{
            total_days_same_year = total_days_same_year + (table_days_month_regular_year[start_month] - start_day) + current_day;
        }
    }
        return total_days_same_year;
    }

    
    
    
    //start calculation days for the start year
    int days_for_start_year = 0;
    
    if (start_year%4 == 0 && start_year%100 != 0){
        for (int month = 1; month < start_month - 1; month ++){
            days_for_start_year = table_days_month_leap_year[month] + days_for_start_year;
            }
        
        //total subtracted by days passed
        days_for_start_year = 366 - (days_for_start_year + start_day);
    }
    
    else{
        for (int month = 1; month < start_month - 1; month ++){
            days_for_start_year = table_days_month_regular_year[month] + days_for_start_year;
        }
        
        //total subtracted by days passed
        days_for_start_year = 365 - (days_for_start_year + start_day);
    }

    
    
    
    //start calculation days for the current year
    int days_for_current_year = 0;
    
    if (current_year%4 == 0 && current_year%100 != 0){
        for (int month = 1; month < current_month - 1; month ++){
            days_for_current_year = table_days_month_leap_year[month] + days_for_current_year;
        }
        
        //total
        days_for_current_year = days_for_current_year + current_day;
    }
    
    else{
        for (int month = 1; month < current_month - 1; month ++){
            days_for_current_year = table_days_month_regular_year[month] + days_for_current_year;
        }
        
        //total
        days_for_current_year = days_for_current_year + current_day;
    }
    
    int total_days = days_for_start_year + days_for_current_year;
    
    return total_days;
}

int main (){
    
    std::cout << "please enter the start date MM/DD/YYYY: " << std::endl;
    
    int start_year; //= 2014;
    int start_month; //= 8;
    int start_day; //= 18;
    int current_year; //= 2014;
    int current_month; //= 5;
    int current_day; //= 20;
    
    
    //input starting date
    std::cin >> start_month; // read the day
    if ( std::cin.get() != '/' ) // make sure there is a slash between DD and MM
    {
        std::cout << "expected /\n";
        return 1;
    }
    std::cin >> start_day; // read the month
    if ( std::cin.get() != '/' ) // make sure there is a slash between MM and YYYY
    {
        std::cout << "expected /\n";
        return 1;
    }
    std::cin >> start_year; // read the year
    std::cout << "start date: " << start_month << "/" << start_day << "/" << start_year << "\n";
    
    
    
    
    //input end date
    std::cout << "please enter the current date MM/DD/YYYY: " << std::endl;
    
    
    std::cin >> current_month; // read the day
    if ( std::cin.get() != '/' ) // make sure there is a slash between DD and MM
    {
        std::cout << "expected /\n";
        return 1;
    }
    std::cin >> current_day; // read the month
    if ( std::cin.get() != '/' ) // make sure there is a slash between MM and YYYY
    {
        std::cout << "expected /\n";
        return 1;
    }
    std::cin >> current_year; // read the year
    
    std::cout << "current date: " << current_month << "/" << current_day << "/" << current_year << "\n";
    
    
    //check valid
    if (start_year > current_year) {
        std::cout << "This is not valid input \n";
        return 0;
    }
    if (start_year <= current_year && start_month > current_month){
        std::cout << "This is not valid input \n";
        return 0;
    }
    
    if (start_year <= current_year && start_month <= current_month && start_day > current_day){
        std::cout << "This is not valid input \n";
        return 0;
    }
    
    
    //calculate
    int total_days = calculate_days_based_on_year_in_between (start_year, current_year) +calculate_days_based_on_month_and_day(start_year, current_year, start_month, current_month, start_day,current_day);
    
    std::cout << "This is the " << total_days << "th day" <<'\n';
    return 0;
}
