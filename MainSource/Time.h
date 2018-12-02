#ifndef TIME_H
#define TIME_H

#include<iostream>
#include<string>
#include<cstdlib>
using namespace std; 


class Time{

    private:
        int second;
        int minute;
        int hour;
        int millisecond;
        
    public:
        int getSecond(){ return second; }
        int getMinute(){ return minute; }
        int getHour(){ return hour; }
        int getMillisecond() { return millisecond; } 
        
        void setSecond(int value){ if(value < 60 && value >= 0) second = value;  } 
        void setMinute(int value){ if(value < 60 && value >= 0) minute= value;  }
        void setHour(int value){ if(value < 24 && value >= 0) hour = value; }
        void setMillisecond(int value) { if (value <= 999 && value >= 0) millisecond = value; }
        
        
        string toString(string format="HH:mm:ss"){
            
            if(format == "HH:mm:ss")
                return to_string(hour) +"/" + to_string(minute)+"/" + to_string(second);
            
        }
        
        bool operator==(Time &other){
            return this->second == other.second && this->minute == other.minute && 
                   this->hour == other.hour && this->millisecond == other.millisecond;
                    
        }
        
        bool operator!=(Time &other){
            return this->second != other.second || this->minute != other.minute ||
                   this->hour != other.hour || this->millisecond != other.millisecond;
        }
        
        bool operator<=(Time &other){
            return hour <= other.hour || (this->hour == other.hour && this->minute <= other.minute) ||
                   (this->hour == other.hour && this->minute == other.minute && this->second <= other.second) ||
                   (this->hour == other.hour && this->minute == other.minute && 
                    this->second == other.second && this->millisecond <= other.millisecond);     
        }
        
        bool operator<(Time &other){
            return hour < other.hour || (this->hour == other.hour && this->minute < other.minute) ||
               (this->hour == other.hour && this->minute == other.minute && this->second < other.second) ||
               (this->hour == other.hour && this->minute == other.minute && 
                this->second == other.second && this->millisecond < other.millisecond);    
        }
        
        bool operator>=(Time &other){
            return hour >= other.hour || (this->hour == other.hour && this->minute >= other.minute) ||
               (this->hour == other.hour && this->minute == other.minute && this->second >= other.second) ||
               (this->hour == other.hour && this->minute == other.minute && 
                this->second == other.second && this->millisecond >= other.millisecond);     
        }
        
        bool operator>(Time &other){
            return hour > other.hour || (this->hour == other.hour && this->minute > other.minute) ||
                   (this->hour == other.hour && this->minute == other.minute && this->second > other.second) ||
                   (this->hour == other.hour && this->minute == other.minute && 
                    this->second == other.second && this->millisecond > other.millisecond);     
        }
        
};

#endif