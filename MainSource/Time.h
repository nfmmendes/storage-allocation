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
        Time(const Time& other);
        
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
            return "";
        }
    
        ///Add a positive number of hours to the time
        void addHours(int value){ if(value > 0) this->hour += value; this->hour = this->hour%24;    }
    
        ///Subtracts a positive number of hours to the time
        void minusHours(int value){
            value = value%24;
            if(value >0) this->hour -= value;
            this->hour =  this->hour <0? this->hour +24: this->hour;
            
        }
    
    
        void addMinutes(int value){
            if(value =<0)
                return;
            
            value = value%(60*24);
            
            if(this->minute + value >=60)
                addHours((int)(this->minutes+value)/60);
            
            this->minute = (this->minute + value)%60;
        }
    
    
        void minusMinutes(int value){
            if(value =< 0)
                return;
            
            if(this->minute-value<=0){
                minusHours(1+(int)(value-this->minute)/60);
                this->minute -= value%60+60;
            }else
                this->minute -= value;
        }
    
        void addSeconds(int value){
            if(value =<0)
                return;
            
            value=value%(60*60*24);
            
            if(this->second + value >=60)
                addMinutes((int)(this->second+value)/60);
            
            this->second = (this->second + value)%60
        }
    
        void minusSecond(int value){
            if(value =< 0)
                return;
            
            if(this->second-value<=0){
                minusMinutes(1+(int)(value-this->second)/60);
                this->second -= value%60+60;
            }else
                this->second -= value;

            
        }
    
        void addMilliseconds(int value){
            if(value =<0)
                return;
            
            value = value%(1000*60*60*24);
            
            if(this->millisecond + value >=1000)
                addSeconds((int)(this->millisecond+value)/1000);
            
            this->millisecond = (this->millisecond + value)%1000;
            
        }
    
        void minusMilliseconds(int value){
            if(value =<0)
                return;
            
            value = value%(1000*60*60*24);
            
            
            if(this->second-value<=0){
                minusMinutes(1+(int)(value-this->millisecond)/1000);
                this->millisecond -= value%1000+1000;
            }else
                this->millisecond -= value;
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
