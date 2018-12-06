#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include<fstream>
#include "Vertex.h"
#include "Transition.h"
#include "HananGraph.h"
#include "PathUnity.h"
using namespace std;
using namespace QuickTSP;

PathUnity::PathUnity(){}
PathUnity::PathUnity(const PathUnity &other){
    this->beginVertex = other.beginVertex;
    this->endVertex = other.endVertex;
    this->transition = other.transition;
}

PathUnity::PathUnity(Vertex &begin, Vertex &end, Transition &transition){
    this->beginVertex = begin;
    this->endVertex = end;
    this->transition = transition;
}

void PathUnity::setBeginVertex(Vertex &value) { this->beginVertex = value; }
void PathUnity::setEndVertex(Vertex &value){ this->endVertex = value; }
void PathUnity::setHananTransition(Transition &value) { this->transition = value; }

Vertex & PathUnity::getBeginVertex() { return this->beginVertex; }
Vertex & PathUnity::getEndVertex() { return this->endVertex; }
Transition & PathUnity::getTransition() { return this->transition; }
