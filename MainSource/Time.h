#pragma once

#include<iostream>
#include<string>
#include<cstdlib>


class Time{

    private:
        int second;
        int minute;
        int hour;
        int millisecond;
        
    public:
        Time();
        Time(const Time& other);
        Time(unsigned short int hour, unsigned short int minute, unsigned short int second=0, unsigned short millisecond = 0);
        
        int getSecond();
        int getMinute();
        int getHour();
        int getMillisecond();
            
        void setSecond(int value);
        void setMinute(int value);
        void setHour(int value);
        void setMillisecond(int value);
            
            
        std::string toString(std::string format="HH:mm:ss");
        
        void addHours(int value);
        void minusHours(int value);
        void addMinutes(int value);
        void minusMinutes(int value);
        void addSeconds(int value);
        void minusSecond(int value);
        void addMilliseconds(int value);
        void minusMilliseconds(int value);
    
        static Time Parse(std::string time, std::string format);
        bool operator==(Time &other);
        bool operator!=(Time &other);
        bool operator<=(Time &other);
        bool operator<(Time &other);
        bool operator>=(Time &other);
        bool operator>(Time &other);
        
};
