#include "Globals.h"
#include "Warehouse.h"
#include "Solution.h"
#include "Analysis.h"
#include "Allocation_heuristic.h"
#include "Ils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;

void timeRandomGreedy(int n);
void genetic(int size_init, int generations);
void compareCostAnalysisCost(int n);
void compareGreedys();
Solution ils(int randons, int iter, double tx);
void localSearch();
void firstImprovement();

int main(int argc, char* argv[]) {
	srand((unsigned int)(std::time(nullptr)));

	if (stoi(argv[1]) == 0) {
		if (argc < 7) {
			cout << "Invalid parameters" << endl;
			exit(0);
		}

		string DIR_PRODUCTS = argv[2];
		string DIR_ORDERS = argv[2];
		string DIR_SOLUTION = argv[3];
		int amount_randons = stoi(argv[4]);
		int amount_ils = stoi(argv[5]);
		int percent_ils = stoi(argv[6]);

		Warehouse warehouse;
		warehouse.readWarehouse(DIR_PRODUCTS);
		Solution::setWarehouse(&warehouse);
		Solution::setLists(DIR_ORDERS);
		Solution::makeMostRequests();
		//Solution::makeCorrelation(3, 5);

		//genetic(40, 200);
		//timeRandomGreedy(500);
		//compareCostAnalysisCost(20);
		//compareGreedys();
		//localSearch();
		//firstImprovement();
		Solution s = ils(amount_randons, amount_ils, percent_ils);

		s.printFile(DIR_SOLUTION);

		Solution greedy;
		greedy.greedySolution();
		greedy.evaluate(SIZE_BRUTE_FORCE);
		greedy.printFile(DIR_SOLUTION + "_GREEDY");
	}
	else if (stoi(argv[1]) == 1) {
		if (argc < 4) {
			cout << "Invalid parameters" << endl;
			exit(0);
		}

		string PATH_INST = argv[2];
		string PATH_SOLUTION = argv[3];

		Warehouse warehouse;
		warehouse.readWarehouse(PATH_INST +"/"+ PATH_INST +".inst");
		Solution::setWarehouse(&warehouse);
		Solution::setLists(PATH_INST + "/" + PATH_INST + ".inst");

		Solution s;
		s.readSolutionProducts(PATH_SOLUTION + "/solucao");
		s.evaluate(SIZE_BRUTE_FORCE);
		cout << s.getCost() << " ";

		s.readSolutionProducts(PATH_SOLUTION + "/solucao_GREEDY");
		s.evaluate(SIZE_BRUTE_FORCE);
		cout << s.getCost() << endl;
	}

	return 0;
}

void firstImprovement() {
	using namespace std::chrono;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	Solution s;
	s.greedySolution();
	s.evaluate(SIZE_BRUTE_FORCE);
	long long int cost = s.getCost();

	Solution s2;
	s2.greedySolution();
	s2.evaluate(SIZE_BRUTE_FORCE);
	cout << "Inicio: " << s2.getCost() << endl;
	s2.firstImprovement();
	cout << s2.isValid() << endl;
	long long int cost2 = s2.getCost();

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	std::cout << "It took me " << time_span.count() << " seconds." << endl;

	printf("Greedy 1: %lld - %.2lf%% best\n", cost, ((max(cost, cost2) - cost) * 100.0) / max(cost, cost2));
	printf("First Improvment: %lld - %.2lf%% best\n", cost2, ((max(cost, cost2) - cost2) * 100.0) / max(cost, cost2));
}

void localSearch() {
	using namespace std::chrono;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	Solution s;
	s.greedySolution();
	s.evaluate(SIZE_BRUTE_FORCE);

	long long int cost = s.getCost();
	long long int cost2 = 1ll << 60;

	cout << s.getCost() << " - " << s.isValid() << endl;
	for (int i = 0; i < 20; i++) {
		Solution s1 = s;
		s1.evaluate(SIZE_BRUTE_FORCE);
		s1.randomLocalSearch(10000);

		cout << s1.getCost() << " - " << s.isValid() << endl;
		cost2 = min(cost2, s1.getCost());
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	std::cout << "It took me " << time_span.count() << " seconds." << endl;

	printf("Greedy 1: %lld - %.2lf%% best\n", cost, ((max(cost, cost2) - cost) * 100.0) / max(cost, cost2));
	printf("Local Search: %lld - %.2lf%% best\n", cost2, ((max(cost, cost2) - cost2) * 100.0) / max(cost, cost2));
}

Solution ils(int randons, int iter, double tx) {
	using namespace std::chrono;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	Solution s;
	s.greedySolution();
	s.evaluate(SIZE_BRUTE_FORCE);
	cout << "GREEDY " << s.getCost() << endl;
	long long cost = s.getCost();

	ILS ils_solution(s);
	ils_solution.run(randons, iter, tx);
	long long cost2 = ils_solution.getBestCost();

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	cout << "---------------------------" << endl;
	std::cout << "TIME " << time_span.count() << endl;
	cout << "INIT " << cost << endl;
	cout << "FINAL " << cost2 << endl;
	printf("PERCENT %.2lf%%\n", double(((max(cost, cost2) - cost2) * 100.0) / max(cost, cost2)));

	return ils_solution.getBestSolution();
}

void genetic(int size_init, int generations) {
	Allocation_heuristic ah;
	ah.initPopulation(size_init);
	ah.run(generations);
	cout << "Best solution cost [GENETIC]: " << ah.getBestCost() << endl;
}

void compareGreedys() {
	Solution a;
	Solution b;
	a.greedySolution();
	b.greedySolution2();

	for (size_t i = 0; i < a.getCells().size(); i++) {
		for (size_t j = 0; j < a.getCells()[i].size(); j++) {
			cout << "(" << i << ", " << j << "): " << a.getCells()[i][j] << " - " << b.getCells()[i][j] << endl;
		}
	}

	a.evaluate(SIZE_BRUTE_FORCE);
	cout << "Greedy 1 (Actual): " << a.getCost() << " - " << ((max(a.getCost(), b.getCost()) - a.getCost()) * 100) / max(a.getCost(), b.getCost()) << "% more efficente" << endl;

	b.evaluate(SIZE_BRUTE_FORCE);
	cout << "Greedy 2 (Analysis): " << b.getCost() << " - " << ((max(a.getCost(), b.getCost()) - b.getCost()) * 100) / max(a.getCost(), b.getCost()) << "% more efficente" << endl;
}

void timeRandomGreedy(int n) {
	using namespace std::chrono;

	vector<Solution> ss1(n);
	vector<Solution> ss2(n);

	for (int i = 0; i < n; i++) {
		ss1[i].randomSolution();
		ss2[i].greedySolution();
	}

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		ss1[i].evaluate(SIZE_BRUTE_FORCE);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		ss2[i].evaluate(SIZE_BRUTE_FORCE);
	}
	high_resolution_clock::time_point t4 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	duration<double> time_span2 = duration_cast<duration<double>>(t4 - t3);

	std::cout << "It took me " << time_span.count() << " seconds." << endl;
	std::cout << "It took me " << time_span2.count() << " seconds." << endl;
}

void compareCostAnalysisCost(int n) {
	vector<Solution> teste(n);

	long long int maxiC = -1;
	long long int maxiA = -1;

	long long int miniC = 1ll << 62;
	long long int miniA = 1ll << 62;

	for (size_t i = 0; i < teste.size(); i++) {
		teste[i].randomSolution();
		teste[i].evaluate(SIZE_BRUTE_FORCE);
		teste[i].evaluateAnalysis();
		maxiC = max(maxiC, teste[i].getCost());
		maxiA = max(maxiA, teste[i].getCostAnalysis());

		miniC = min(miniC, teste[i].getCost());
		miniA = min(miniA, teste[i].getCostAnalysis());
	}

	cout << "worst - Best" << endl;
	cout << maxiC << " " << miniC << endl;
	cout << maxiA << " " << miniA << endl;

	maxiC -= miniC;
	maxiA -= miniA;

	sort(teste.begin(), teste.end());

	cout << endl << "Cost - Analysis Cost" << endl;
	for (size_t i = 0; i < teste.size(); i++) {
		cout << double(teste[i].getCost() - miniC) / double(maxiC) << "\t" << double(teste[i].getCostAnalysis() - miniA) / double(maxiA) << endl;
	}
}
