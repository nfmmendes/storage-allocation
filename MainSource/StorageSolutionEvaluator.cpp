#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include<set>
#include<vector>
#include<map>
#include<algorithm>
#include<stdexcept> 
#include "Cell.h"
#include "Vertex.h"
#include "Arc.h"
#include "DistanceMatrix.h"
#include "OptimizationParameters.h"
#include "StorageSolutionEvaluator.h"
#include "WarehouseToGraphConverter.h"
#include "TSP.h"
#include "Order.h"
#include "Block.h"
using namespace std;
using namespace QuickTSP;


/**
 *
 */
StorageSolutionEvaluator::StorageSolutionEvaluator(const StorageSolutionEvaluator &sto){
	this->routesByVertexAndSize = sto.routesByVertexAndSize;
	
	this->distances = sto.distances;
	this->optimizationConstraints = sto.optimizationConstraints;

	for(auto & [key, value] : sto.vertexByCellPosition)
		vertexByCellPosition[key] = value; 

	for(auto &[key,value] : sto.closestStartPoint)	this->closestStartPoint[key] = value;
	for(auto &[key, value] : sto.closestEndPoint)	this->closestEndPoint[key] = value;
	InitializeIsolatedFamilies();

	for(auto &[key,value] : sto.shelfById)
		this->shelfById[key] = value; 

	for(auto &[key, value] : sto.shelfIdsSetByBlockName)
		for(auto & ID : value)
			this->shelfIdsSetByBlockName[key].insert(ID);
}

/**
 *
 */
StorageSolutionEvaluator::StorageSolutionEvaluator(DistanceMatrix<Vertex> * distances, map<Position, Vertex> &vertexByPosition,
												   vector<Block> &blocks, const OptimizationConstraints & constraints){
	
	this->distances = distances;
	this->optimizationConstraints = constraints;
	InitializeClosestDeliveryPoint();

	for(auto & [key, value] : vertexByPosition)
		vertexByCellPosition[key] = value; 
	InitializeIsolatedFamilies();

	for(unsigned int i=0; i<blocks.size(); i++){
		vector<Shelf> shelves = blocks[i].getShelves();
		for(auto & shelf : shelves){
			this->shelfById[shelf.getId()] = shelf;
			this->shelfIdsSetByBlockName[blocks[i].getName()].insert(shelf.getId());
		}
	}
	 
}

/**
 *
 */
void StorageSolutionEvaluator::InitializeIsolatedFamilies(){
	 
	weaklyIsolatedFamilies.clear(); 
	stronglyIsolatedFamilies.clear(); 
	prohibitionsByProduct.clear(); 

	vector<IsolatedFamily> isolatedFamilies = this->optimizationConstraints.getIsolatedFamilies();
	for(auto &item: isolatedFamilies){	
		if(item.getForce() == WEAK_ISOLATION) 
			weaklyIsolatedFamilies.insert(item.getCode()); 
		else  
			stronglyIsolatedFamilies.insert(item.getCode());
	}		 
 
	vector<ProductAllocationProhibitions> prohibitions = this->optimizationConstraints.getProductAllocationProhibitions();  
	for(auto &item : prohibitions) 
		prohibitionsByProduct[item.getProduct().getName()] = item;

}


/**
 *
 */
StorageSolutionEvaluator & StorageSolutionEvaluator::operator=(const StorageSolutionEvaluator &other){
	this->routesByVertexAndSize = other.routesByVertexAndSize;
	
	this->distances = other.distances;
	this->optimizationConstraints = other.optimizationConstraints;

	for(auto & [key, value] : other.vertexByCellPosition)
		vertexByCellPosition[key] = value; 
 
	this->closestStartPoint.clear();  
	this->closestEndPoint.clear();
	for(auto &[key,value] : other.closestStartPoint)	this->closestStartPoint[key] = value;
	for(auto &[key, value] : other.closestEndPoint)		this->closestEndPoint[key] = value;
	InitializeIsolatedFamilies();
	 
	this->shelfIdsSetByBlockName.clear(); 
	this->shelfById.clear();
	for(auto &[key,value] : other.shelfById)
		this->shelfById[key] = value; 

	for(auto &[key, value] : other.shelfIdsSetByBlockName)
		for(auto & ID : value)
			this->shelfIdsSetByBlockName[key].insert(ID);
	return *this;
}


/**
 * Set the closest expedition point of each storage point in both senses, storage -> expedition, expedition -> storage
 **/
void StorageSolutionEvaluator::InitializeClosestDeliveryPoint(){
	
	vector<Vertex> storagePoints;  
	vector<Vertex> expeditionPoints; 
	vector<Vertex> allVertexes = distances->getKeys(); 
	
	for(Vertex &vertex : allVertexes){
		if(vertex.getType() == WarehouseToGraphConverter::EXPEDITION_POINT_VERTEX){
			expeditionPoints.push_back(vertex);
		}else{ //All the non expedition points in this case are storage points (TEST IT)
			storagePoints.push_back(vertex);
		}
	}

	cout<<"****** Storage points : "<<storagePoints.size()<<endl; 
	closestStartPoint.clear();
	closestEndPoint.clear(); 
	
	for(unsigned int i=0;i<storagePoints.size();i++){
		double minStartDistance = 1e100;
		double minEndDistance = 1e100; 
		Vertex bestStart, bestEnd; 

		for(unsigned int j=0;j<expeditionPoints.size();j++){
			double startDistance = distances->getDistance(expeditionPoints[j], storagePoints[i]);
			double endDistance = distances->getDistance(storagePoints[i], expeditionPoints[j]); 

			if(startDistance < minStartDistance){
				minStartDistance = startDistance; 
				bestStart = expeditionPoints[j]; 
			}
			
			if(endDistance < minEndDistance){
				minEndDistance = endDistance; 
				bestEnd = expeditionPoints[j]; 
			}
		}
		
		closestStartPoint[storagePoints[i]] = bestStart;
		closestEndPoint[storagePoints[i] ] = bestEnd; 
		
	}	

}

/**
 *
 **/
double StorageSolutionEvaluator::evaluatePenaltyDeltaByProhibition(const Product &first, const Cell &firstCell, const Product &second, const Cell &secondCell){	
	auto firstResult = prohibitionsByProduct.find(first.getName());  
	auto secondResult = prohibitionsByProduct.find(second.getName());  
 
	if(firstResult == prohibitionsByProduct.end() && secondResult == prohibitionsByProduct.end()) 
		return 0; 
  
	double firstCurrentPenalty, secondCurrentPenalty, firstNewPenalty, secondNewPenalty;  
	firstCurrentPenalty = secondCurrentPenalty = firstNewPenalty = secondNewPenalty = 0;   

	if(firstResult != prohibitionsByProduct.end()){ 
		ProductAllocationProhibitions firstProhibition = prohibitionsByProduct[first.getName()];
		vector<Cell> prohibitedCells = firstProhibition.getForbiddenCells();
		vector<Shelf> prohibitedShelves = firstProhibition.getForbiddenShelves();
		vector<Block> prohibitedBlocks = firstProhibition.getForbiddenBlocks();

		for(unsigned int i=0; i<prohibitedCells.size(); i++){
			if(prohibitedCells[i].getCode() == firstCell.getCode() )
				firstCurrentPenalty += 8000; 
			if(prohibitedCells[i].getCode() == secondCell.getCode() )
				firstNewPenalty += 8000;
		}
	} 
 
	if(secondResult != prohibitionsByProduct.end()){ 
		ProductAllocationProhibitions secondProhibition = prohibitionsByProduct[second.getName()];
		vector<Cell> prohibitedCells = secondProhibition.getForbiddenCells();
		vector<Shelf> prohibitedShelves = secondProhibition.getForbiddenShelves();
		vector<Block> prohibitedBlocks = secondProhibition.getForbiddenBlocks();


		for(unsigned int i=0; i<prohibitedCells.size(); i++){
			if(prohibitedCells[i].getCode() == secondCell.getCode() )
				secondCurrentPenalty += 8000; 
			if(prohibitedCells[i].getCode() == firstCell.getCode() )
				secondNewPenalty += 8000;
		}
	} 
 
	return (firstNewPenalty + secondNewPenalty) - (firstCurrentPenalty + secondCurrentPenalty); 
}
	
/**	
 *	Evaluate the penalty delta caused by a swap between two products. In this function is supposed a valid swap, so 	
 *	strongly isolated families or strong allocation prohibitions will cause a exception 
 **/
double StorageSolutionEvaluator::evaluatePenaltyDelta(MapAllocation & allocations,const Product &first,const Product &second){
	pair<Cell, int> firstPosition =  allocations[first]; 	
	pair<Cell, int> secondPosition = allocations[second];		
	Cell firstCell = firstPosition.first; 	
	Cell secondCell = secondPosition.first; 
	double delta = 0.0; 		
	
	//Check prohibition 	
	evaluatePenaltyDeltaByProhibition(first, firstCell, second, secondCell);	

	//Check isolation	
	if(first.getType() == second.getType())	
		return 0; 	

	auto isolatedFamilies = this->optimizationConstraints.getIsolatedFamilies(); 		
	bool firstIsStronglyIsolated = stronglyIsolatedFamilies.find(first.getType()) != stronglyIsolatedFamilies.end(); 
	bool secondIsStronglyIsolated = stronglyIsolatedFamilies.find(second.getType()) != stronglyIsolatedFamilies.end();

	if(firstIsStronglyIsolated || secondIsStronglyIsolated )
		std::invalid_argument("There are strongly isolated products");
	bool isFirstIsolated = weaklyIsolatedFamilies.find(first.getType()) != weaklyIsolatedFamilies.end(); 
	bool isSecondIsolated =  weaklyIsolatedFamilies.find(second.getType()) != weaklyIsolatedFamilies.end();
	
	if(isFirstIsolated && isSecondIsolated)
		return 0;

	//Check cell delta
	if(firstCell.getCode() != secondCell.getCode() && (firstCell.getLevels() > 1 || secondCell.getLevels() > 1) ){	
		
	}	
}

/**
 *
 **/
double StorageSolutionEvaluator::getBetterRouteWithTwoPoints(vector<Vertex>& vertexes){
	
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
double StorageSolutionEvaluator::DoFullEvaluationWithTSP(vector<PickingRoute> &vertexesVisits){

	TSP tsp(*distances); 
	vector<pair<Product, double> > items; 
	vector<Vertex> storagePoints; 
	double penalty = 0.0; 
	double totalDistance =0.0;
	
	for(unsigned int i=0;i< vertexesVisits.size();i++){
		
		vector<Vertex> vertexes = vertexesVisits[i].first; 
		storagePoints.clear(); 
		 
		if(items.size() == 1) {
			
			Vertex location = vertexes[0]; 
			Vertex begin = closestStartPoint[location];
			Vertex end =   closestEndPoint[location] ; 
			vertexesVisits[i].second = this->distances->getDistance(begin, location) + this->distances->getDistance(location, end); 
			totalDistance += vertexesVisits[i].second; 
			
		}else if(items.size() == 2){
			vertexesVisits[i].second = this->getBetterRouteWithTwoPoints(vertexes);
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
 **/
double StorageSolutionEvaluator::DoRouteEvaluation(vector<Vertex> & route){

	TSP tsp(*distances); 
	vector<pair<Product, double> > items; 
	double penalty = 0.0; 
	double totalDistance =0.0;
	
	pair<double, vector<Vertex> > routeEvaluation; 
	if(route.size() == 1){
		Vertex location = route[0]; 
		Vertex begin = closestStartPoint[ location ];
		Vertex end =   closestEndPoint[ location ] ; 
		totalDistance = this->distances->getDistance(begin, location) + this->distances->getDistance(location, end);

	}else if(route.size() == 2){
		totalDistance = this->getBetterRouteWithTwoPoints(route);	
	}if(route.size() < 6) //This is just a limit to use the brute force TSP algorithm
		routeEvaluation = tsp.bruteForceTSP(route, closestStartPoint, closestEndPoint); 
	else if(route.size() < 12) //This is a limit to use 
		routeEvaluation = tsp.quickLocalSearchTSP(route, closestStartPoint, closestEndPoint);
	else //All the other cases will use a closest neighbor inserction procedure 
		routeEvaluation = tsp.closestNeighborTSP(route, closestStartPoint, closestEndPoint);

	totalDistance += routeEvaluation.first; 		
	
	return totalDistance+penalty; 
}

/**
 *
 */ 
double StorageSolutionEvaluator::DoRouteEstimation(vector<Vertex> & solution){
	//int solutionSize = solution.size();
	//cout<<solutionValue<<endl;
	for(unsigned int i=0; i< solution.size(); i++){
		
	}
	
	
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


/**
 * 
 * */
PickingRoute StorageSolutionEvaluator::getVertexes(vector<Position> &positions){
	PickingRoute value; 
	for(unsigned int i=0; i<positions.size(); i++){
		if(this->vertexByCellPosition.find(positions[i]) != this->vertexByCellPosition.end())
			value.first.push_back(this->vertexByCellPosition[positions[i]]);
	}

	return value; 
}



Vertex StorageSolutionEvaluator::getVertex(Position &position){
	return this->vertexByCellPosition[position];
}

