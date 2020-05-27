#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include<set>
#include<vector>
#include<map>
#include<algorithm>
#include "Cell.h"
#include "Vertex.h"
#include "Arc.h"
#include "DistanceMatrix.h"
#include "OptimizationParameters.h"
#include "StorageSolutionEvaluator.h"
#include "TSP.h"
#include "Order.h"
using namespace std;
using namespace QuickTSP;

/**
 *
 */
StorageSolutionEvaluator::StorageSolutionEvaluator(){

}



/**
 *
 */
StorageSolutionEvaluator::StorageSolutionEvaluator(const StorageSolutionEvaluator &sto){
	this->routesByVertexAndSize = sto.routesByVertexAndSize;
	this->vertexByCellPosition = sto.vertexByCellPosition;
	this->distances = sto.distances;
}

/**
 *
 */
StorageSolutionEvaluator::StorageSolutionEvaluator(DistanceMatrix<Vertex> * distances){
	
	this->distances = distances;
}

/**
 *
 */
StorageSolutionEvaluator & StorageSolutionEvaluator::operator=(const StorageSolutionEvaluator &other){
	this->routesByVertexAndSize = other.routesByVertexAndSize;
	this->vertexByCellPosition = other.vertexByCellPosition;
	this->distances = other.distances;
	return *this;
}


/**
 *
 **/
double StorageSolutionEvaluator::getBetterRouteWithTwoPoints(vector<Vertex>& vertexes, map<Vertex, Vertex> & closestStartPoint,
															 map<Vertex, Vertex> & closestEndPoint ){
	
	Vertex location = vertexes[0]; 
	Vertex begin = closestStartPoint[location];
	Vertex end =   closestEndPoint[location] ; 
	double dist1 = this->distances->getDistance(begin, location) + this->distances->getDistance(location, end); 
	
	location = vertexes[1]; 
	begin = closestStartPoint[ location  ];
	end =   closestEndPoint[   location  ] ; 
	double dist2 = this->distances->getDistance(begin, location) + this->distances->getDistance(location, end); 
	
	return min(dist1, dist2); 
	
}


/**
 * 
 **/
double StorageSolutionEvaluator::DoFullEvaluationWithTSP(vector<PickingRoute> &vertexesVisits, map<Vertex, Vertex> & closestStartPoint,
														map<Vertex, Vertex> &closestEndPoint){

	TSP tsp(*distances); 
	vector<pair<Product, double> > items; 
	vector<Vertex> storagePoints; 
	double penalty = 0.0; 
	double totalDistance =0.0;
	
	for(unsigned int i=0;i< vertexesVisits.size();i++){
		
		vector<Vertex> vertexes = vertexesVisits[i].first; 
		
		if(items.size() == 1) {
			
			Vertex location = vertexes[0]; 
			Vertex begin = closestStartPoint[location];
			Vertex end =   closestEndPoint[location] ; 
			vertexesVisits[i].second = this->distances->getDistance(begin, location) + this->distances->getDistance(location, end); 
			totalDistance += vertexesVisits[i].second; 
			
		}else if(items.size() == 2){
			vertexesVisits[i].second = this->getBetterRouteWithTwoPoints(vertexes, closestStartPoint, closestEndPoint );
			totalDistance += vertexesVisits[i].second;
			
		}else{
			for(unsigned int j = 0; j<vertexes.size();j++)
				storagePoints.push_back( vertexes[j] );
			
			pair<double, vector<Vertex> > route; 
			//This is just a limit to use the brute force TSP algorithm
			if(storagePoints.size() < OptimizationParameters::ALL_PERMUTATIONS_TSP_THRESHOLD ) 
				route = tsp.bruteForceTSP(storagePoints, closestStartPoint, closestEndPoint); 
			else if(storagePoints.size() < OptimizationParameters::INSERTION_TSP_THRESHOLD)
				route = tsp.quickLocalSearchTSP(storagePoints, closestStartPoint, closestEndPoint);
			else 
				route = tsp.closestNeighborTSP(storagePoints, closestStartPoint, closestEndPoint);
			
			totalDistance += route.first; 
		}
		
	}

	return totalDistance + penalty; 
}
/**
 *
 */
double StorageSolutionEvaluator::DoRouteEvaluation(vector<Vertex> & route){

	
	TSP tsp(*distances); 
	vector<Vertex> bestRoute = route; 
	vector<Vertex> currentRoute = route; 
	double lowestValue = 1e10; 
	
	if(route.size() <= OptimizationParameters::ALL_PERMUTATIONS_TSP_THRESHOLD){
		while(next_permutation(currentRoute.begin()+1, currentRoute.end()-1)){
			double distance = sumDistances(currentRoute); 
			if(lowestValue < distance){
				bestRoute = currentRoute; 
				lowestValue = distance; 
			}
		}
	}else if( route.size() <= OptimizationParameters::INSERTION_TSP_THRESHOLD){
		
	}else{
		
	}
		
	return lowestValue; 
}

/**
 *
 */ 
double StorageSolutionEvaluator::DoRouteEstimation(vector<Vertex> & solution){
	int solutionValue = solution.size();
	cout<<solutionValue<<endl;
	return 0;
}

/**
 *	Get the total distance of a route (sequence of visits)
 *	@param sequence Sequence of points visited 
 *	@return Total distance 
 **/
double StorageSolutionEvaluator::sumDistances(vector<Vertex> &sequence){
	double sum = 0.0;
	int limit = sequence.size() >0 ? sequence.size()-1 : 0; 
	
	for(int i=0;i<limit; i++){
		sum += distances->getDistance(sequence[i], sequence[i+1]); 
	}
	
	return sum; 
}

/**
 * Return how many times each product is required in a list of orders 
 * @param orders List of orders to be analyzed 
 **/
map<Product, int> StorageSolutionEvaluator::getRequestsByProduct(vector<Order> &orders){
	
	map<Product, int> returnedValue; 
	
	for(auto &order : orders){
		vector<pair<Product, double> > orderItems = order.getOrderItems(); 
		for(unsigned int i=0;i<orderItems.size(); i++){
			if(returnedValue.find(orderItems[i].first) == returnedValue.end())
				returnedValue[orderItems[i].first] = 0;
			returnedValue[orderItems[i].first] = 1; 
		}
	}
	return returnedValue; 
}

/**
 * This function searches a vertex list value already calculated
 * @param vertexes Sequence that will be searched
 * @return The vertexes list value found or '-1' otherwise 
 **/
double StorageSolutionEvaluator::searchSequenceOnCache(vector<Vertex> &vertexes){
	
	if(vertexes.size() ==0)
		return -1; 
		
	
	string firstString;  
	Vertex firstVertex; 
	for(unsigned int i=0; i < vertexes.size(); i++){
		string label = vertexes[i].getLabel();
		if(label < firstString){
			firstString = label; 
			firstVertex = vertexes[i]; 
		}
	}
	
	if(routesByVertexAndSize.find(firstVertex) == routesByVertexAndSize.end())
		return -1; 
	
	if(routesByVertexAndSize[firstVertex].find(vertexes.size()) == routesByVertexAndSize[firstVertex].end())
		return -1; 
		
	sort(vertexes.begin(), vertexes.end(), [](Vertex &a, Vertex &b){ return a.getLabel() < b.getLabel(); });
	
	vector<PickingRoute> cachedRoutes = routesByVertexAndSize[firstVertex][vertexes.size()];
	
	for(unsigned int i=0; i<vertexes.size(); i++)
		if(cachedRoutes[i].first[0].getLabel() == firstVertex.getLabel()){
			unsigned j;
			for(j = 1; j<cachedRoutes[i].first.size();j++)
				if(cachedRoutes[i].first[j].getLabel() != vertexes[j].getLabel())
					break;
				
			if(j == cachedRoutes[i].first.size())
				return cachedRoutes[i].second; 
		}
	return -1;
}

