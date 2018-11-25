#include "Ils.h"

using namespace std;

ILS::ILS()
{}

ILS::ILS(const Solution &s)
{
	this->_best_solution = s;
	this->_best_cost = s.getCost();
}

void ILS::run(int amount_randons, int max_iter, double _inner_pert_tx)
{
	Solution s2 = _best_solution;
	pair<int, int> cell1, cell2;

	double step = (_inner_pert_tx - 1) / max_iter;

	s2.evaluate(SIZE_BRUTE_FORCE);
	cout << "ILS init 0 " << s2.getCost() << endl;
	s2.randomLocalSearch(amount_randons);
	cout << "ILS ++ 0 " << s2.getCost() << endl;

	for (int i = 1; i <= max_iter; i++) {
		int qt = int(_best_solution.amountVaos() * (_inner_pert_tx / 100.0));
		_inner_pert_tx -= step;

		while (qt--) {
			s2.randomTwoCell(cell1, cell2);
			s2.swapCell(cell1, cell2);
		}

		s2.evaluate(SIZE_BRUTE_FORCE);
		cout << "ILS init " << i << " " << s2.getCost() << endl;
		s2.randomLocalSearch(amount_randons);
		//s2.firstImprovement();

		if (s2.getCost() < _best_cost) {
			_best_solution = s2;
			_best_cost = s2.getCost();
			cout << "ILS ++ " << i << " " << s2.getCost() << endl;
		}
		else {
			cout << "ILS -- " << i << " " << s2.getCost() << endl;
			s2 = _best_solution;
		}
	}

	_best_solution.evaluate(SIZE_BRUTE_FORCE);
	cout << "ILS endPertubate 9999 " << _best_solution.getCost() << endl;

	_best_solution.firstImprovement();

	cout << "ILS end 9999 " << _best_solution.getCost() << endl;

	_best_cost = _best_solution.getCost();
}

const Solution & ILS::getBestSolution() const
{
	return _best_solution;
}

long long ILS::getBestCost() const
{
	return _best_cost;
}
