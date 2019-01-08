#ifndef Parameter_h
#define Parameter_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum ParameterType { _string_, _double_, _int_, _bool_};

class Parameter{
    
    private:
        string name;
        string stringValue;
        double doubleValue;
        int intValue;
        bool booleanValue;
        ParameterType type;
    
    public:
        Parameter();
        Parameter(const Parameter & other);
        Parameter(string name, string value);
        Parameter(string name, int value);
        Parameter(string name, double value);
        Parameter(string name, bool value);
    
        void setParameterValue(string value);
        void setParameterValue(double value);
        void setParameterValue(int value);
        void setParameterValue(bool value);
        void setName(string name);
        static vector<Parameter> readParametersData(string fileName);
    
        ParameterType getParameterType();
        string getName();
        bool getBoolParameterValue();
        int getIntParameterValue();
        double getDoubleParameterValue();
        string getStringParameterValue();
};

#endif /* Parameter_hp */
