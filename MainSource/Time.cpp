#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include "Time.h"
#include "Util.h"
using namespace std;


Time::Time(){
    this->millisecond = 0;
    this->second = 0;
    this->minute = 0;
    this->hour = 0;
}

Time::Time(unsigned short int hour, unsigned short int minute, unsigned short int second, unsigned short millisecond){
    this->hour = hour;
    this->second = second;
    this->minute = minute;
    this->millisecond = millisecond;
}

Time::Time(const Time& other){
    this->millisecond = other.millisecond;
    this->second = other.second;
    this->minute = other.minute;
    this->hour = other.hour;
}

int Time::getSecond(){ return second; }
int Time::getMinute(){ return minute; }
int Time::getHour(){ return hour; }
int Time::getMillisecond() { return millisecond; }

void Time::setSecond(int value){ if(value < 60 && value >= 0) second = value;  }
void Time::setMinute(int value){ if(value < 60 && value >= 0) minute= value;  }
void Time::setHour(int value){ if(value < 24 && value >= 0) hour = value; }
void Time::setMillisecond(int value) { if (value <= 999 && value >= 0) millisecond = value; }


string Time::toString(string format){
    
    if(format == "HH:MM:SS")
        return to_string(hour) +":" + to_string(minute)+":" + to_string(second);
    return "";
}

///Add a positive number of hours to the time
void Time::addHours(int value){ if(value > 0) this->hour += value; this->hour = this->hour%24;    }

///Subtracts a positive number of hours to the time
void Time::minusHours(int value){
    value = value%24;
    if(value >0) this->hour -= value;
    this->hour =  this->hour <0? this->hour +24: this->hour;
    
}


void Time::addMinutes(int value){
    if(value <=0)
        return;
    
    value = value%(60*24);
    
    if(this->minute + value >=60)
        addHours((int)(this->minute+value)/60);
    
    this->minute = (this->minute + value)%60;
}


void Time::minusMinutes(int value){
    if(value <= 0)
        return;
    
    if(this->minute-value<=0){
        minusHours(1+(int)(value-this->minute)/60);
        this->minute -= value%60+60;
    }else
        this->minute -= value;
}

void Time::addSeconds(int value){
    if(value <=0)
        return;
    
    value=value%(60*60*24);
    
    if(this->second + value >=60)
        addMinutes((int)(this->second+value)/60);
    
    this->second = (this->second + value)%60;
}

void Time::minusSecond(int value){
    if(value <= 0)
        return;
    
    if(this->second-value<=0){
        minusMinutes(1+(int)(value-this->second)/60);
        this->second -= value%60+60;
    }else
        this->second -= value;
}

void Time::addMilliseconds(int value){
    if(value <=0)
        return;
    
    value = value%(1000*60*60*24);
    
    if(this->millisecond + value >=1000)
        addSeconds((int)(this->millisecond+value)/1000);
    
    this->millisecond = (this->millisecond + value)%1000;
    
}

void Time::minusMilliseconds(int value){
    if(value <=0)
        return;
    
    value = value%(1000*60*60*24);
    
    
    if(this->second-value<=0){
        minusMinutes(1+(int)(value-this->millisecond)/1000);
        this->millisecond -= value%1000+1000;
    }else
        this->millisecond -= value;
}

Time Time::Parse(string time, string format){
    Time returned;
    size_t pos = 0;
    
    if(format == "HH:MM:SS.mmmm"){
        vector<string> firstSplit;
		Util::splitString(firstSplit, time,":");
        string last = firstSplit[firstSplit.size()-1];
        vector<string> secondSplit;
		Util::splitString(secondSplit,time, ".");
        
        if(firstSplit.size() == 3){
            returned.setHour(stoi(firstSplit[0]) );
            returned.setMinute(stoi(firstSplit[1]));
            
            if(secondSplit.size() == 1)
                returned.setSecond(stoi(secondSplit[0]));
            if(secondSplit.size() == 2)
                returned.setMillisecond(stoi(secondSplit[1]));
        }
    }else if(format =="HH:MM:SS"){
        vector<string> firstSplit;

		Util::splitString(firstSplit,time,":");
        
        if(firstSplit.size() == 3){
            returned.setHour(stoi(firstSplit[0]) );
            returned.setMinute(stoi(firstSplit[1]));
            returned.setSecond(stoi(firstSplit[2]));
        }
        
    }else if(format == "HH:MM:SS AM/PM"){
		cout<<"*"<<pos<<endl;
		/*
        vector<string> firstSplit;
		Util::splitString(firstSplit,time,":");
        
        if(firstSplit.size()==3){
            if((pos = time.find("PM")) != std::string::npos || (pos = time.find("pm")) != std::string::npos)
                returned.setHour(stoi(firstSplit[0])%12+12);
            else
                returned.setHour(stoi(firstSplit[0])%12);
            
            returned.setMinute(stoi(firstSplit[1]));
            
            vector<string> secondSplit;
			//Corrigir isso depois
			//Util::splitString(secondSplit,firstSplit[2]," ");
            returned.setSecond(stoi(secondSplit[0]));
        }
     */   
    }
    
    return returned;
    
}


bool Time::operator==(Time &other){
    return this->second == other.second && this->minute == other.minute &&
    this->hour == other.hour && this->millisecond == other.millisecond;
    
}

bool Time::operator!=(Time &other){
    return this->second != other.second || this->minute != other.minute ||
    this->hour != other.hour || this->millisecond != other.millisecond;
}

bool Time::operator<=(Time &other){
    return hour <= other.hour || (this->hour == other.hour && this->minute <= other.minute) ||
    (this->hour == other.hour && this->minute == other.minute && this->second <= other.second) ||
    (this->hour == other.hour && this->minute == other.minute &&
     this->second == other.second && this->millisecond <= other.millisecond);
}

bool Time::operator<(Time &other){
    return hour < other.hour || (this->hour == other.hour && this->minute < other.minute) ||
    (this->hour == other.hour && this->minute == other.minute && this->second < other.second) ||
    (this->hour == other.hour && this->minute == other.minute &&
     this->second == other.second && this->millisecond < other.millisecond);
}

bool Time::operator>=(Time &other){
    return hour >= other.hour || (this->hour == other.hour && this->minute >= other.minute) ||
    (this->hour == other.hour && this->minute == other.minute && this->second >= other.second) ||
    (this->hour == other.hour && this->minute == other.minute &&
     this->second == other.second && this->millisecond >= other.millisecond);
}

bool Time::operator>(Time &other){
    return hour > other.hour || (this->hour == other.hour && this->minute > other.minute) ||
    (this->hour == other.hour && this->minute == other.minute && this->second > other.second) ||
    (this->hour == other.hour && this->minute == other.minute &&
     this->second == other.second && this->millisecond > other.millisecond);
    }
