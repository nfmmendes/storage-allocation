#ifndef H_ILS
#define H_ILS

#include "Globals.h"
#include "Solution.h"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

class ILS {
private:
	Solution _best_solution;
	long long _best_cost;

public:

	ILS();
	ILS(const Solution &s);

	void run(int amount_randons, int max_iter, double _inner_pert_tx);

	const Solution & getBestSolution() const;
	long long getBestCost() const;

};

#endif
