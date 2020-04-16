#include<iostream>
#include<string>
#include<cmath>
#include "Vertex.h"
using namespace std;
using namespace QuickTSP;



Vertex::Vertex(){}
Vertex::Vertex(const Vertex &other){
    this->label = other.label;
    this->type = other.type;
    this->value = other.value;
	
}

Vertex::Vertex(string label, string Type, double value){
    this->label = label;
    this->type = Type;
    this->value = value;
}

void Vertex::setLabel(string value){ this->label = value; }
void Vertex::setType(string value) { this->type = value; }
void Vertex::setValue(double value) { this->value = value; }

string Vertex::getLabel() const { return this->label; }
string Vertex::getType(){ return this->type; }
double Vertex::getValue() { return this->value; }

bool Vertex::operator==(const Vertex & other)const {
    return label == other.label && type == other.type && fabs(value - other.value) <= 0.0000000000001;
}

bool Vertex::operator!=(const Vertex & other){
    return label != other.label || type != other.type || fabs(value - other.value) > 0.0000000000001;
}

Vertex & Vertex::operator=(const Vertex &other){
	this->label = other.label;
    this->type = other.type;
    this->value = other.value;
	return *this; 
}

///This overload allows the use of an object of this class as a key to a map
bool Vertex::operator<(const Vertex &other)const{
    return label+type+to_string(value) < other.label+other.type+to_string(other.value);
}

