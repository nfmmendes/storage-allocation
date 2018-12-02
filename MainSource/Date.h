#ifndef DATE_H
#define DATE_H

#include<iostream>
#include<string>
#include<cstdlib>
using namespace std; 



class Date{
    
    private:
        int day;
        int month;
        int year;
        const string monthName[13] = {"", "January", "February", "March", "April", "May", "June", "July", 
                                   "August", "September", "October", "November", "December"};
        
    public:
        int getDay() { return day; } 
        int getMonth() { return month; }
        int getYear() { return year; }
        
        void setDay(int value){ if(value <= 31 && value >= 1) day = value;  validatedate(*this); } 
        void setMonth(int value){ if(value <= 12 && value >= 1) month= value; validatedate(*this); }
        void setYear(int value){ if(value >= 0) year = value; }
        
        
        void validatedate(Date &date){
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
        
        string toString(string format="yyyy/MM/dd"){
            
            if(format == "yyyy/MM/dd")
                return to_string(year) +"/" + to_string(month)+"/" + to_string(day);
            
        }
        
        bool operator==(Date &other){
            return this->day == other.day && this->month == other.month && this->year == other.year;
        }
        
        bool operator!=(Date &other){
            return this->day != other.day || this->month != other.month || this->year != other.year;
        }
        
        bool operator<=(Date &other){
            return year <= other.year || (this->year == other.year && this->month <= other.month) ||
                   (this->year == other.year && this->month == other.month && this->day <= other.day);     
        }
        
        bool operator<(Date &other){
                return year < other.year || (this->year == other.year && this->month < other.month) ||
                   (this->year == other.year && this->month == other.month && this->day < other.day); 
        }
        
        bool operator>=(Date &other){
            return year >= other.year || (this->year == other.year && this->month >= other.month) ||
                   (this->year == other.year && this->month == other.month && this->day >= other.day);     
        }
        
        bool operator>(Date &other){
                return year > other.year || (this->year == other.year && this->month > other.month) ||
                   (this->year == other.year && this->month == other.month && this->day > other.day); 
        }
        

};

#endif