#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include "Vertex.h"
#include "Arc.h"
using namespace std;
using namespace QuickTSP;

Arc::Arc(const Arc &arc){
    this->label = arc.getLabel();
    this->value = arc.getValue();
    this->beginVertex = arc.getBeginVertex();
    this->endVertex = arc.getEndVertex();
}

Arc::Arc(string label, double value, Vertex &begin, Vertex &end, bool directed){
    this->label = label;
    this->value = value;
    this->beginVertex = begin;
    this->endVertex= end;
    this->directed = directed;
}

const string& Arc::getLabel() const { return label; }
double Arc::getValue() const  { return value; }
const Vertex& Arc::getBeginVertex() const { return beginVertex; }
const Vertex& Arc::getEndVertex() const  {return endVertex; }

Arc& Arc::operator=(const Arc & other)
{
    this->label = other.label;
    this->value = other.value;
    this->beginVertex = other.beginVertex;
    this->endVertex = other.endVertex;

    return *this;
}

bool Arc::operator==(const Arc &other)const {
    return this->label == other.label && this->value == other.value &&
            this->beginVertex == other.beginVertex && this->endVertex  == other.endVertex;
}

bool Arc::operator<(const Arc &other)const{
    if(this->label != other.label)
        return this->label < other.label;
    else
        return this->value < other.value;
}
