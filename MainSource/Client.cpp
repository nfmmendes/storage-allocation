#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "Client.h"
using namespace std;


Client::Client(){}

/**
 * Member by member constructor
 **/
Client::Client(string name, string type, pair<double, double> coordinates ){
    this->name = name;
    this->type = type;
    this->coordinates = coordinates;
}

/**
 * Copy constructor
 * @param other Client to be copied 
 */
Client::Client(const Client &other){
    this->name = other.name;
    this->type = other.type;
    this->coordinates = other.coordinates;
}

void Client::setName(string value){ this->name = value;}
void Client::setType(string value){ this->type = value; }
void Client::setCoordinates(pair<double,double> value){ this->coordinates =value; }

string Client::getName(){ return name;}
string Client::setType() { return type;}
pair<double, double> Client::getCoordinates(){ return coordinates;}


/**
 *  Assignment operator
 */
Client & Client::operator=(const Client &other){
    this->name = other.name;
    this->type = other.type;
    this->coordinates = other.coordinates;
    
    return *this;
    }


/**
 * Read the client data writen in a text file 
 * @param fileName Write a file name 
 */
vector<Client> Client::readClientData(string fileName){
    vector<Client> clients;
    pair<double,double> coordinates;
    string _name, _type;
    
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

/**
 *	Read client data including the coordinates of the position where they receave their produts 
 *  @param fileName Name of file where the informations are stored 
 */
vector<Client> Client::readClientDataWithCoordinates(string fileName){
    vector<Client> clients;
    pair<double,double> coordinates;
    string _name, _type;
    
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
