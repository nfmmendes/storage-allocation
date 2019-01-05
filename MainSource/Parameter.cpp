#include "Parameter.h"


Parameter::Parameter(){
    
}

Parameter::Parameter(Parameter & other){
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

Parameter::Parametrs(string name, bool value){
    
    this->name = name;
    this->boolValue = value;
    type=ParameterType::_bool_;
}

void Parameter::setName(string value){  this->name = value;}
void Parameter::setParameterValue(string value){    stringValue = value;    type=ParameterType::_string_;}
void Parameter::setParameterValue(double value){    doubleValue = value;    type=ParameterType::_double_;}
void Parameter::setParameterValue(int value){       intValue = value;       type=ParameterType::_int_;}
void Parameter::setParameterValue(bool value){      booelanValue = value;   type=ParameterType::_bool_;}

string getName
ParameterType Parameter::getParameterType() { return type;}
string Parameter::getStringParameterValue() { return stringValue;}
int Parameter::getIntParameterValue()  { return intValue; }
double Parameter::getDoubleParameterValue() { return doubleValue;}
bool Parameter::getBoolParameterValue() { return booleanValue;}
