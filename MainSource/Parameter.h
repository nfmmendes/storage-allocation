#ifndef Parameter_h
#define Parameter_h

#include <stdio.h>
#include <iostream>
#include <string>

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
        Parameter(Parameter & other);
        Parametrs(string name, string value);
        Parametrs(string name, int value);
        Parametrs(string name, double value);
        Parametrs(string name, bool value);
    
        void setParameterValue(string value);
        void setParameterValue(double value);
        void setParameterValue(int value);
        void setParameterValue(bool value);
    
        ParameterType getParameterType();
        string getParameterValue();
        int setParameterValue();
        double setParameterValue();
        bool setParameterValue();
}

#endif /* Parameter_hp */
