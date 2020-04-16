#include "Parameter.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;



Parameter::Parameter(){
    
}

Parameter::Parameter(const Parameter & other){
    this->name = other.name;
    this->stringValue = other.stringValue;
    this->intValue = other.intValue;
    this->doubleValue = other.doubleValue;
    this->booleanValue = other.booleanValue;
    this->type = other.type;
}

Parameter::Parameter(string name, string value){
    this->name = name;
    this->stringValue = value;
    type=ParameterType::_string_;
}

Parameter::Parameter(string name, int value){
    
    this->name = name;
    this->intValue = value;
    type=ParameterType::_int_;
}

Parameter::Parameter(string name, double value){
    
    this->name = name;
    this->doubleValue = value;
    type=ParameterType::_double_;
    
}

Parameter::Parameter(string name, bool value){
    
    this->name = name;
    this->booleanValue = value;
    type=ParameterType::_bool_;
}

void Parameter::setName(string value){  this->name = value;}
void Parameter::setParameterValue(string value){    stringValue = value;    type=ParameterType::_string_;}
void Parameter::setParameterValue(double value){    doubleValue = value;    type=ParameterType::_double_;}
void Parameter::setParameterValue(int value){       intValue = value;       type=ParameterType::_int_;}
void Parameter::setParameterValue(bool value){      booleanValue = value;   type=ParameterType::_bool_;}

string Parameter::getName(){ return name;}
ParameterType Parameter::getParameterType() { return type;}
string Parameter::getStringParameterValue() { return stringValue;}
int Parameter::getIntParameterValue()  { return intValue; }
double Parameter::getDoubleParameterValue() { return doubleValue;}
bool Parameter::getBoolParameterValue() { return booleanValue;}


vector<Parameter> Parameter::readParametersData(string fileName){
    
    vector<Parameter> returned;
    int numParameters;
    string sValue, pType, name;
    ifstream file;
    
    file.open(fileName,ios::in);
    
    file>>numParameters;
    
    for(int i=0;i<numParameters; i++){
        file>>name>>pType>>sValue;
        
        if(pType == "string")
            returned.push_back(Parameter(name, sValue));
        else if(pType == "int")
            returned.push_back(Parameter(name, stoi(sValue)));
        else if(pType== "bool")
            returned.push_back(Parameter(name, (sValue == "true"|| sValue == "TRUE"|| sValue== "True") ? true: false));
        else if(pType == "double")
            returned.push_back(Parameter(name, stof(sValue)));

    }
    return returned;
    
}
