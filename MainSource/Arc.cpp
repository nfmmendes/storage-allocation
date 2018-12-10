#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include "Vertex.h"
#include "Arc.h"
using namespace std;
using namespace QuickTSP;

Arc::Arc(){
    
}

Arc::Arc(const Arc &arc){
    this->label = arc.getLabel();
    this->value = arc.getValue();
    this->beginVertex = arc.getBeginVertex();
    this->endVertex = arc.getEndVertex();
}

Arc::Arc(string label, double value, Vertex &begin, Vertex &end){
    this->label = label;
    this->value = value;
    this->beginVertex = begin;
    this->endVertex= end;
}

void Arc::setLabel(string label){
    this->label = label;
}


void Arc::setValue(double value){
    this->value = value;
}

void Arc::setBeginVertex(Vertex& vertex){
    this->beginVertex = vertex;
    
}

void Arc::setEndVertex(Vertex& vertex){
    this->endVertex = vertex;
}


string Arc::getLabel() const { return label; }
double Arc::getValue() const  { return value; }
Vertex Arc::getBeginVertex() const { return beginVertex; }
Vertex Arc::getEndVertex() const  {return endVertex; }
