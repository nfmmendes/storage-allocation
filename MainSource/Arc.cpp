#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include "Vertex.h"
#include "Arc.h"
using namespace std;
using namespace QuickTSP;

/**
 *	Empty constructor
 */
Arc::Arc(){
    
}

/**
 *	Copy constructor 
 */
Arc::Arc(const Arc &arc){
    this->label = arc.getLabel();
    this->value = arc.getValue();
    this->beginVertex = arc.getBeginVertex();
    this->endVertex = arc.getEndVertex();
}

/**
 *	Constructor by member 
 */
Arc::Arc(string label, double value, Vertex &begin, Vertex &end, bool directed){
    this->label = label;
    this->value = value;
    this->beginVertex = begin;
    this->endVertex= end;
    this->directed = directed;
}

/**
 * Set the arc value 
 */
void Arc::setLabel(string label){
    this->label = label;
}

/**
 *	Set arc value 
 */
void Arc::setValue(double value){
    this->value = value;
}

/**
 *	Set the begin of arc with a vertex 
 */
void Arc::setBeginVertex(Vertex& vertex){
    this->beginVertex = vertex;
    
}

/**
 * Set the end of arc with a vertex 
 */
void Arc::setEndVertex(Vertex& vertex){
    this->endVertex = vertex;
}


string Arc::getLabel() const { return label; }
double Arc::getValue() const  { return value; }
Vertex Arc::getBeginVertex() const { return beginVertex; }
Vertex Arc::getEndVertex() const  {return endVertex; }

/**
 *	Assign operator overload 
 */
Arc& Arc::operator=(const Arc & other)
{
    this->label = other.label;
    this->value = other.value;
    this->beginVertex = other.beginVertex;
    this->endVertex = other.endVertex;

    return *this;
}

/**
 *	Equals overload operator. Two arcs are equals if and only if their labels, values and 
 *  extremities are the same  
 */
bool Arc::operator==(const Arc &other)const {
    return this->label == other.label && this->value == other.value &&
            this->beginVertex == other.beginVertex && this->endVertex  == other.endVertex;
}

/**
 * 
 */ 
bool Arc::operator<(const Arc &other)const{
    if(this->label != other.label)
        return this->label < other.label;
    else
        return this->value < other.value;
}
