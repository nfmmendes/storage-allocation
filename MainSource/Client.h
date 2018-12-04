#ifndef CLIENT_H
#define CLIENT_H

#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<map>
#include<algorithm>
#include<utility>
using namespace std;


///This class represents the main data of a client
///The function of this class is not provide a full and detailed description of a client
///just provide enough data to generate some solutions reports
class Client{
    
    private:
        string name;
        long int Id;
        string type;
        pair<double,double> coordinates;
    
    public:
        Client(){}
    
        // Member by member constructor
        Client(string name, string type, long int idClient, pair<double, double> coordinates ){
            this->name = name;
            this->type = type;
            this->Id = idClient;
            this->coordinates = coordinates;
        }
    
        //Copy constructor
        Client(const Client &other){
            this->name = other.name;
            this->Id = other.Id;
            this->type = other.type;
            this->coordinates = other.coordinates;
        }
    
        //Set functions
        void setName(string value){ this->name = value;}
        void setId(long int value){ if(value>0) this->Id = value;}
        void setType(string value){ this->type = value; }
        void setCoordinates(pair<double,double> value){ this->coordinates =value; }
    
        //Get functions
        string getName(){ return name;}
        long int getId() { return Id;}
        string setType() { return type;}
        pair<double, double> getCoordinates(){ return coordinates;}
    
    
        //Assignment operator
        Client & operator=(const Client &other){
            return Client(other.name, other.type, other.Id, other.coordinates);
        }

};


#endif
