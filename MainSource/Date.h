#pragma once

#include<iostream>
#include<string>
#include<cstdlib>

const std::string monthName[13] = {"", "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"};

/**
 * Class to represent the date (without time)
 * The aritmetic operations ware not implemented yet
 */
class Date{
    
    private:
        int day;		///< Day 
        int month;		///< Month
        int year;		///< Year 
        
    public:
        Date();
        Date(const Date& other);
        int getDay();
        int getMonth();
        int getYear();
    
        void setDay(int value);
        void setMonth(int value);
        void setYear(int value);
    
        void validateDate();
    
        std::string toString(std::string format="yyyy/MM/dd");
    
        static Date Parse(std::string date, std::string format);
        Date &operator=(const Date &other);
        bool operator==(Date &other);
        bool operator!=(Date &other);
        bool operator<=(Date &other);
        bool operator<(Date &other);
        bool operator>=(Date &other);
        bool operator>(Date &other);
};
