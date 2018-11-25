#ifndef H_SOLUTION
#define H_SOLUTION

#include "Globals.h"
#include "Warehouse.h"
#include "Path_Heuristic.h"
#include "Analysis.h"
#include "Point.h"
#include "List.h"
#include "json.hpp"

#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <ctime>
#include <cstdlib>
#include <queue>

class Solution
{
private:
	static int _count;
	static std::vector<List> _lists;
	static correlationStructure _correlation;
	static mostRequestStructure _most_request;
	static Warehouse* _warehouse;

	std::vector<std::vector<int>> _cells;
	std::vector<std::pair<int, int>> _products; ///< first = cell, second = level
	long long int _cost;						///< Cost of the solution

	long long int _cost_analysis;


	int _rand_cod;
	bool _use_cache;
	std::vector<int> _lazy_products;
	static int _solution_cached;

	void getVerticesList(const std::vector<int> &l, std::vector<int> &v);

public:
	Solution();
	~Solution();

	Solution& operator= (const Solution &s);
	bool operator < (const Solution &a) const;
	bool operator > (const Solution &a) const;

	void setCell(int i, int j, int p);
	void setProduct(int i, std::pair<int, int> p);
	void swapItem(int i, int j, int i2, int j2);
	void swapProducts(int i, int j);
	void evaluate(int bruteForceSize, bool cache_lists = false);
	void evaluateAnalysis();
	std::pair<int, int> getProductPosition(int p) const;

	long long int getCost() const;
	long long int getCostAnalysis() const;
	const std::vector<std::vector<int>> & getCells() const;
	const std::vector<std::pair<int, int>> & getProducts() const;
	std::string getJson() const;

	void randomSolution();
	void greedySolution();
	void greedySolution2();
	bool isValid();

	void clear();

	void pertubate(double p, bool its_percentage, std::pair<int, int> &c1, std::pair<int, int> &c2); // p = how much (in 100) pertubate
	// change the position between (p/2)% pairs of products
	// can send the number of swap if its_percentage = false

	void localSearch();
	void randomLocalSearch(int iterations);
	void firstImprovement();

	int amountVaos() const;

	void swapCell(std::pair<int, int> cell1, std::pair<int, int> cell2);
	void randomTwoCell(std::pair<int, int> &cell1, std::pair<int, int> &cell2);

	void startCacheMe();
	void stopCacheMe();

	void printFile(std::string path);

	void readSolutionProducts(std::string path);

	static void setWarehouse(Warehouse *wh);
	static void setLists(std::string DIR_ORDERS);
	static const std::vector<List> & getLists();
	static void makeCorrelation(int max_group, int min_correlation);
	static void makeMostRequests();
};

#endif
