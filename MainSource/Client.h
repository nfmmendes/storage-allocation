#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<utility>


/**
 * @brief Class <c> Client <c> represents the main data of a client. This class does not provide
 *        a full and detailed description of a client just provide enough data to generate some 
 *        solutions reports.
 */
class Client{
    
    private:
        std::string name;						///< Client name (or address) 
        std::string type;						///< Client type 
        std::pair<double,double> coordinates;	///< Coordinates for product deliveries (optional) 
    
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
        Client(std::string name, std::string type,  std::pair<double, double> coordinates );

        /**
         * @brief Copy constructor.
         * @param other The object to be copied. 
         */
        Client(const Client &other);
        
        /**
         * @brief Get the client name.
         * @return The client name.
         */
        std::string getName();

        /**
         * @brief Get the client type.
         * @return The client type.
         */
        std::string getType();

        /**
         * @brief Get the client location coordinates.
         * @return The client location coordinates. 
         */
        std::pair<double, double> getCoordinates();
    
        /**
         * @brief Assignment operator overide. 
         * @param other The right hand side object. 
         * @return A reference to the modified left side hand object.
         */
        Client & operator=(const Client &other);

        /**
         * @brief Read the client data from file. 
         * @param fileName The name of the file with the client's information. 
         * @return A vector of clients. 
         */
        static std::vector<Client> readClientData(std::string fileName);

        /**
         * @brief Read the client data from file with their location coordinates. 
         * @param fileName The name of the file with the client's information. 
         * @return A vector of clients. 
         */
        static std::vector<Client> readClientDataWithCoordinates(std::string fileName);
};

