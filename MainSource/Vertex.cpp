#include<iostream>
#include<string>
#include<cmath>
#include "Vertex.h"
using namespace QuickTSP;

Vertex::Vertex(){
    this->value = 0; 
    this->label = "";
    this->type = "";
}
Vertex::Vertex(const Vertex &other){
    this->label = other.label;
    this->type = other.type;
    this->value = other.value;
	
}

Vertex::Vertex(const string& label, const string& type, double value){
    this->label = label;
    this->type = type;
    this->value = value;
}

void Vertex::setLabel(string value){ this->label = value; }
void Vertex::setType(string value) { this->type = value; }

const string& Vertex::getLabel() const { return this->label; }
const string& Vertex::getType() const { return this->type; }
double Vertex::getValue() const { return this->value; }

bool Vertex::operator==(const Vertex & other)const {
    return label == other.label && type == other.type && fabs(value-other.value) < 0.000001;
}

bool Vertex::operator!=(const Vertex & other) const{
    return label != other.label || type != other.type || fabs(value-other.value) > 0.000001;
}

Vertex & Vertex::operator=(const Vertex &other){
	
	this->label = other.label;
    this->type = other.type;
    this->value = other.value;
	
	return *this; 
}

///This overload allows the use of an object of this class as a key to a map
bool Vertex::operator<(const Vertex &other)const{
    auto concatA = label+type;
    auto concatB = other.label+other.type;
    if(concatA < concatB)
        return true;

    return concatA == concatB && value < other.value;
}

