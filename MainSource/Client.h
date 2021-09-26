#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<utility>


///This class represents the main data of a client
///The function of this class is not provide a full and detailed description of a client
///just provide enough data to generate some solutions reports
class Client{
    
    private:
        std::string name;						///< Client name (or address) 
        std::string type;						///< Client type 
        std::pair<double,double> coordinates;	///< Coordinates for product deliveries (optional) 
    
    public:
        Client();
        // Member by member constructor
        Client(std::string name, std::string type,  std::pair<double, double> coordinates );
    
        //Copy constructor
        Client(const Client &other);
    
        //Set functions
        void setName(std::string value);
        void setType(std::string value);
        void setCoordinates(std::pair<double,double> value);
    
        //Get functions
        std::string getName();
        std::string setType();
        std::pair<double, double> getCoordinates();
    
    
        //Assignment operator
        Client & operator=(const Client &other);
        static std::vector<Client> readClientData(std::string fileName);
        static std::vector<Client> readClientDataWithCoordinates(std::string fileName);

};

