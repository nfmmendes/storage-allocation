#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include "Date.h"
#include "Util.h"
using namespace std;

Date::Date(){ this->day = 1; this->month = 1; this->year = 1990; }
Date::Date(const Date& other){this->day = other.day; this->month=other.month; this->year = other.year;}
int Date::getDay() { return day; }
int Date::getMonth() { return month; }
int Date::getYear() { return year; }

void Date::setDay(int value){ if(value <= 31 && value >= 1) day = value;  this->validateDate(); }
void Date::setMonth(int value){ if(value <= 12 && value >= 1) month= value; this->validateDate(); }
void Date::setYear(int value){ if(value >= 0) year = value; }

/**
 * Control if the data is valid or not based on the month and year (to leap years)
 */
void Date::validateDate(){
    if(month == 1 || month == 3 || month == 5 || month == 7 ||
       month == 8 || month == 10 || month == 12){
        if(day > 31)
            throw("Invalid date (" + this->toString() +") ! The day value must be equals or minor than 31!");
        
    }else if(month == 4 || month == 6 || month == 9 || month == 11){
        
    }else if(month == 2){
        if(day >= 30)
            throw("Invalid date (" + this->toString() +") ! The day value must be equals or minor than 29!");
        else if(year%4 == 0 && (year%100 != 0 || year%400 == 0) && day >29)
            throw("Invalid date (" + this->toString() +") ! The day value must be equals or minor than 29!");
        else if(day >= 29)
            throw("Invalid date (" + this->toString() +") ! The day value must be equals or minor than 28!");
    }
}

/**
 *	Transform a date in a string with a given format
 *  @date format Date string format (yyyy/MM/dd , dd/mm/yy, etc...) 
 */
string Date::toString(string format){
    
    if(format == "yyyy/MM/dd")
        return to_string(year) +"/" + to_string(month)+"/" + to_string(day);
    return "";
}


//This function transform a string representing a date in a object
//of Date class. If your data format is not here, feel free to insert it
Date Date::Parse(string date, string format){
    
    Date returned;
    
    if(format == "yyyy-MM-dd"){
        vector<string> split;
		Util::splitString(split, date, "-");
        //cout<<split[0];
        returned.setYear(stoi(split[0]));
        
		if(split[1][0] != '0')
			returned.setMonth(stoi(split[1]));
		else
			returned.setMonth(stoi(split[1].substr(1,1)));
	
		
		if(split[2][0] != '0')
			returned.setDay(stoi(split[2]));
		else
			returned.setDay(stoi(split[2].substr(1,1)));
        
    }else if(format == "yyyy/MM/dd"){
        vector<string> split;
		Util::splitString(split, date, "/");
        //cout<<split[0];
        returned.setYear(stoi(split[0]));
        
		if(split[1][0] != '0')
			returned.setMonth(stoi(split[1]));
		else
			returned.setMonth(stoi(split[1].substr(1,1)));
	
		
		if(split[2][0] != '0')
			returned.setDay(stoi(split[2]));
		else
			returned.setDay(stoi(split[2].substr(1,1)));
        
    }
        
    return returned;
}

/**
 *
 */
Date & Date::operator=(const Date &other){
    this->day = other.day;
    this->year = other.year;
    this->month = other.month;
    return *this;
}

/**
 * Equals operator overload 
 * @param other The object in the right hand size of the operator
 */
bool Date::operator==(Date &other){
    return this->day == other.day && this->month == other.month && this->year == other.year;
}

/**
 * Not equal operator overload 
 * @param other The object in the right hand size of the operator
 */
bool Date::operator!=(Date &other){
    return this->day != other.day || this->month != other.month || this->year != other.year;
}

/**
 * Less than or equal operator overload 
 * @param other The object in the right hand size of the operator
 */
bool Date::operator<=(Date &other){
    return year <= other.year || (this->year == other.year && this->month <= other.month) ||
    (this->year == other.year && this->month == other.month && this->day <= other.day);
}

/**
 *	Less than operator overload 
 * @param other The object in the right hand size of the operator
 */
bool Date::operator<(Date &other){
    return year < other.year || (this->year == other.year && this->month < other.month) ||
    (this->year == other.year && this->month == other.month && this->day < other.day);
}

/**
 *Greater than or equal operator 
 * @param other The object in the right hand size of the operator
 */
bool Date::operator>=(Date &other){
    return year >= other.year || (this->year == other.year && this->month >= other.month) ||
    (this->year == other.year && this->month == other.month && this->day >= other.day);
}

/**
 * Greater than operator overload 
 */
bool Date::operator>(Date &other){
    return year > other.year || (this->year == other.year && this->month > other.month) ||
    (this->year == other.year && this->month == other.month && this->day > other.day);
}

