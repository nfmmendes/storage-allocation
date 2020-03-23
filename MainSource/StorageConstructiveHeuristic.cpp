

StorageConstructiveHeuristic::StorageConstructiveHeuristic(vector<Product> & prods, Warehouse &wh,DistanceMatrix<Vertex> distMatrix,
														   vector<Order> &orders, OptimizationConstraints &cons){
	this->distanceMatrix = &distMatrix; 
	this->warehouse = &wh; 
	this->orders= orders; 
	this->constraints = cons; 
	this->products = prods; 													   
															   
}

bool StorageConstructiveHeuristic::StopCriteriaReached(){
	
	
}


void EvaluateSolution(AbstractSolution * solution){
	
	
	TSP tsp(distanceMatrix); 
	for(unsigned int i=0;i< orders.size();i++){
		auto items = orders[i].getOrderItems(); 
		
	}
		
	
}