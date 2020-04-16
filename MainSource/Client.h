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
        string name;						///< Client name (or address) 
        string type;						///< Client type 
        pair<double,double> coordinates;	///< Coordinates for product deliveries (optional) 
    
    public:
        Client();
        // Member by member constructor
        Client(string name, string type,  pair<double, double> coordinates );
    
        //Copy constructor
        Client(const Client &other);
    
        //Set functions
        void setName(string value);
        void setType(string value);
        void setCoordinates(pair<double,double> value);
    
        //Get functions
        string getName();
        string setType();
        pair<double, double> getCoordinates();
    
    
        //Assignment operator
        Client & operator=(const Client &other);
        static vector<Client> readClientData(string fileName);
        static vector<Client> readClientDataWithCoordinates(string fileName);

};


#endif
