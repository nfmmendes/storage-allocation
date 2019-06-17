#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "Client.h"
using namespace std;


Client::Client(){}

// Member by member constructor
Client::Client(string name, string type, pair<double, double> coordinates ){
    this->name = name;
    this->type = type;
    this->coordinates = coordinates;
}

//Copy constructor
Client::Client(const Client &other){
    this->name = other.name;
    this->type = other.type;
    this->coordinates = other.coordinates;
}

//Set functions
void Client::setName(string value){ this->name = value;}
void Client::setType(string value){ this->type = value; }
void Client::setCoordinates(pair<double,double> value){ this->coordinates =value; }

//Get functions
string Client::getName(){ return name;}
string Client::setType() { return type;}
pair<double, double> Client::getCoordinates(){ return coordinates;}


//Assignment operator
Client & Client::operator=(const Client &other){
    this->name = other.name;
    this->type = other.type;
    this->coordinates = other.coordinates;
    
    return *this;
    }





vector<Client> Client::readClientData(string fileName){
    vector<Client> clients;
    pair<double,double> coordinates;
    string _name, _type;
    long int ID;
    
    ifstream file;
    file.open(fileName,ios::in);
    
    int numClients;
    file>>numClients;
    
    for(int i=0; i<numClients; i++){
        file>>_name>>_type;
        clients.push_back(Client(_name,_type, coordinates));
    }
    
    return clients;
}

vector<Client> Client::readClientDataWithoutCoordinates(string fileName){
    vector<Client> clients;
    pair<double,double> coordinates;
    string _name, _type;
    long int ID;
    
    ifstream file;
    file.open(fileName,ios::in);
    
    int numClients;
    file>>numClients;
    
    for(int i=0; i<numClients; i++){
        file>>_name>>_type>>coordinates.first>>coordinates.second;
        clients.push_back(Client(_name,_type, coordinates));
    }
    
    return clients;
    
}
