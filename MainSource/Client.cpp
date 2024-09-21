#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "Client.h"

Client::Client(){}

Client::Client(const string& name, const string& type, const pair<double, double>& coordinates ){
    this->name = name;
    this->type = type;
    this->coordinates = coordinates;
}

Client::Client(const Client &other){
    name = other.name;
    type = other.type;
    coordinates = other.coordinates;
}

const string& Client::getName() const { return name;}
const string& Client::getType() const { return type;}
const pair<double, double>& Client::getCoordinates() const { return coordinates;}


Client & Client::operator=(const Client &other){
    name = other.name;
    type = other.type;
    coordinates = other.coordinates;
    
    return *this;
}
