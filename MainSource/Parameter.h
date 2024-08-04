#pragma once

#include <iostream>
#include <string>
#include <vector>

enum ParameterType { _string_, _double_, _int_, _bool_};

/**
 * @brief The class Parameter holds and handler a optimization parameter with its value. 
 */
class Parameter{
    
    private:
        std::string name;
        std::string stringValue;
        double doubleValue;
        int intValue;
        bool booleanValue;
        ParameterType type;
    
    public:
        /**
         * @brief Constructor.
         */
        Parameter();

        /**
         * @brief Copy constructor.
         * @param other The source object.
         */
        Parameter(const Parameter & other);

        /**
         * @brief Constructor.
         * @param name The parameter name.
         * @param value The parameter value. 
         */
        Parameter(std::string name, std::string value);

        /**
         * @brief Constructor. 
         * @param name The parameter name.
         * @param value The parameter value. 
         */
        Parameter(std::string name, int value);

        /**
         * @brief Constructor.
         * @param name The parameter name.
         * @param value The parameter value. 
         */
        Parameter(std::string name, double value);

        /**
         * @brief Constructor.
         * @param name The parameter name.
         * @param value The parameter value. 
         */
        Parameter(std::string name, bool value);
    
        /**
         * @brief Set the parameter value
         * @param value The parameter value. 
         */
        void setParameterValue(std::string value);

        /**
         * @brief Set the parameter value.
         * @param value The parameter value. 
         */
        void setParameterValue(double value);

        /**
         * @brief Set the parameter value.
         * @param value The parameter value. 
         */
        void setParameterValue(int value);

        /**
         * @brief Set the parameter value.
         * @param value The parameter value. 
         */
        void setParameterValue(bool value);

        /**
         * @brief Set the parameter name. 
         * @param name The paremeter name. 
         */
        void setName(std::string name);

        /**
         * @brief Read the parameters data from file.
         * @param fileName The file name.
         * @return The list of parameters read. 
         */
        static std::vector<Parameter> readParametersData(std::string fileName);
    
        /**
         * @brief Get the parameter type.
         * @return The parameter type. 
         */
        ParameterType getParameterType();
        
        /**
         * @brief Get the parameter name.
         * @return The parameter name.
         */
        std::string getName();

        /**
         * @brief Get the parameter bool value.
         * @return The parameter null value. 
         */
        bool getBoolParameterValue();

        /**
         * @brief The the parameter int value.
         * @return The param int value. 
         */
        int getIntParameterValue();

        /**
         * @brief Get the parameter double value.
         * @return The parameter double value.
         */
        double getDoubleParameterValue();

        /**
         * @brief Get the paramater string value. 
         * @return The param string value. 
         */
        std::string getStringParameterValue();
};
