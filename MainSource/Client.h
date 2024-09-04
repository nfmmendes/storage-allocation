#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<utility>
using std::pair;
using std::string;


/**
 * @brief Class <c> Client <c> represents the main data of a client. This class does not provide
 *        a full and detailed description of a client just provide enough data to generate some 
 *        solutions reports.
 */
class Client{
    
    private:
        string name;						///< Client name (or address) 
        string type;						///< Client type 
        pair<double,double> coordinates;	///< Coordinates for product deliveries (optional) 
    
    public:
        /**
         * @brief Constructor.
         */
        Client();

        /**
         * @brief Constructor.
         * @param name The client name.
         * @param type The client type.
         * @param coordinates The client location coordinates. 
         */
        Client(string name, string type,  std::pair<double, double> coordinates );

        /**
         * @brief Copy constructor.
         * @param other The object to be copied. 
         */
        Client(const Client &other);
        
        /**
         * @brief Get the client name.
         * @return The client name.
         */
        string getName();

        /**
         * @brief Get the client type.
         * @return The client type.
         */
        string getType();

        /**
         * @brief Get the client location coordinates.
         * @return The client location coordinates. 
         */
        pair<double, double> getCoordinates();
    
        /**
         * @brief Assignment operator overide. 
         * @param other The right hand side object. 
         * @return A reference to the modified left side hand object.
         */
        Client & operator=(const Client &other);
};

