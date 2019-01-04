#include<iostream>
#include<string>
#include<cstdlib>
#include "Date.h"
using namespace std;

Date::Date(){ this->day = 1; this->month = 1; this->year = 1990; }
Date::Date(const Date& other){this->day = other.day; this->month=other.month; this->year = other.year;}
int Date::getDay() { return day; }
int Date::getMonth() { return month; }
int Date::getYear() { return year; }

void Date::setDay(int value){ if(value <= 31 && value >= 1) day = value;  validatedate(*this); }
void Date::setMonth(int value){ if(value <= 12 && value >= 1) month= value; validatedate(*this); }
void Date::setYear(int value){ if(value >= 0) year = value; }


void Date::validatedate(Date &date){
    if(month == 1 || month == 3 || month == 5 || month == 7 ||
       month == 8 || month == 10 || month == 12){
        if(day > 31)
            throw("Invalid date (" + date.toString() +") ! The day value must be equals or minor than 31!");
        
    }else if(month == 4 || month == 6 || month == 9 || month == 11){
        
    }else if(month == 2){
        if(day >= 30)
            throw("Invalid date (" + date.toString() +") ! The day value must be equals or minor than 29!");
        else if(year%4 == 0 && (year%100 != 0 || year%400 == 0) && day >29)
            throw("Invalid date (" + date.toString() +") ! The day value must be equals or minor than 29!");
        else if(day >= 29)
            throw("Invalid date (" + date.toString() +") ! The day value must be equals or minor than 28!");
    }
    
    
}


string Date::toString(string format){
    
    if(format == "yyyy/MM/dd")
        return to_string(year) +"/" + to_string(month)+"/" + to_string(day);
    return "";
}


//This function transform a string representing a date in a object
//of Date class. If your data format is not here, feel free to insert it
Date Date::Parse(string date, string format){
    
    Date returned;
    
    if(format == "YYYY/MM/DD"){
        vector<string> split = Util::splitString(date, "/");
        
        returned.setYear(stoi(split[0]));
        returned.setMonth(stoi(split[1]));
        returned.setDay(stoi(split[2]));
        
    }
        
    return returned;
}


Date & Date::operator=(const Date &other){
    this->day = other.day;
    this->year = other.year;
    this->month = other.month;
    return *this;
}

bool Date::operator==(Date &other){
    return this->day == other.day && this->month == other.month && this->year == other.year;
}

bool Date::operator!=(Date &other){
    return this->day != other.day || this->month != other.month || this->year != other.year;
}

bool Date::operator<=(Date &other){
    return year <= other.year || (this->year == other.year && this->month <= other.month) ||
    (this->year == other.year && this->month == other.month && this->day <= other.day);
}

bool Date::operator<(Date &other){
    return year < other.year || (this->year == other.year && this->month < other.month) ||
    (this->year == other.year && this->month == other.month && this->day < other.day);
}

bool Date::operator>=(Date &other){
    return year >= other.year || (this->year == other.year && this->month >= other.month) ||
    (this->year == other.year && this->month == other.month && this->day >= other.day);
}

bool Date::operator>(Date &other){
    return year > other.year || (this->year == other.year && this->month > other.month) ||
    (this->year == other.year && this->month == other.month && this->day > other.day);
}

