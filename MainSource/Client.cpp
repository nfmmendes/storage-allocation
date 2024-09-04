#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "Client.h"
using namespace std;


Client::Client(){}

Client::Client(string name, string type, pair<double, double> coordinates ){
    this->name = name;
    this->type = type;
    this->coordinates = coordinates;
}

Client::Client(const Client &other){
    this->name = other.name;
    this->type = other.type;
    this->coordinates = other.coordinates;
}

string Client::getName(){ return name;}
string Client::getType() { return type;}
pair<double, double> Client::getCoordinates(){ return coordinates;}


Client & Client::operator=(const Client &other){
    this->name = other.name;
    this->type = other.type;
    this->coordinates = other.coordinates;
    
    return *this;
}
