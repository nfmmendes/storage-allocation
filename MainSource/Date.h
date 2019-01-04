#ifndef DATE_H
#define DATE_H

#include<iostream>
#include<string>
#include<cstdlib>
using namespace std; 

const string monthName[13] = {"", "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"};

///Class to represent the date (without time)
///The aritmetic operations ware not implemented yet
class Date{
    
    private:
        int day;
        int month;
        int year;
    
        
    public:
        Date();
        Date(const Date& other);
        int getDay();
        int getMonth();
        int getYear();
    
        void setDay(int value);
        void setMonth(int value);
        void setYear(int value);
    
    
        void validatedate(Date &date);
    
    
        string toString(string format="yyyy/MM/dd");
    
        static Date Parse(string date, string format);
        Date &operator=(const Date &other);
        bool operator==(Date &other);
        bool operator!=(Date &other);
        bool operator<=(Date &other);
        bool operator<(Date &other);
        bool operator>=(Date &other);
        bool operator>(Date &other);
        

};

#endif
