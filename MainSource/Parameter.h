#pragma once

#include <iostream>
#include <string>
#include <vector>

enum ParameterType { _string_, _double_, _int_, _bool_};

class Parameter{
    
    private:
        std::string name;
        std::string stringValue;
        double doubleValue;
        int intValue;
        bool booleanValue;
        ParameterType type;
    
    public:
        Parameter();
        Parameter(const Parameter & other);
        Parameter(std::string name, std::string value);
        Parameter(std::string name, int value);
        Parameter(std::string name, double value);
        Parameter(std::string name, bool value);
    
        void setParameterValue(std::string value);
        void setParameterValue(double value);
        void setParameterValue(int value);
        void setParameterValue(bool value);
        void setName(std::string name);
        static std::vector<Parameter> readParametersData(std::string fileName);
    
        ParameterType getParameterType();
        std::string getName();
        bool getBoolParameterValue();
        int getIntParameterValue();
        double getDoubleParameterValue();
        std::string getStringParameterValue();
};
