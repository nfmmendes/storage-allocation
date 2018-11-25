#include "Solution.h"

using namespace std;
using json = nlohmann::json;


int Solution::_count;
int Solution::_solution_cached;
vector<List> Solution::_lists;
correlationStructure Solution::_correlation;
mostRequestStructure Solution::_most_request;
Warehouse* Solution::_warehouse;
const int MAX_SEQ_SIZE_BRUTEFORCE_MINPATH = 7;

Solution::Solution()
{
	auto cells = _warehouse->getCells();
	_cells = vector<vector<int>>(cells.size());
	for (size_t i = 0; i < _cells.size(); i++) {
		_cells[i] = vector<int>(cells[i].getLevels(), -1);
	}
	_products = vector<pair<int, int>>(_warehouse->getProducts().size(), make_pair(-1, -1));

	_cost = 0ll;
	_cost_analysis = 0ll;
	_use_cache = false;

	_rand_cod = _count;
	_count++;
}

Solution::~Solution()
{
}

Solution & Solution::operator=(const Solution & s)
{
	_cells = s._cells;
	_products = s._products;
	_cost = s._cost;
	_cost_analysis = s._cost_analysis;
	_use_cache = false;
	_rand_cod = _count;
	_count++;

	return (*this);
}

bool Solution::operator<(const Solution & a) const
{
	return getCost() < a.getCost();
}

bool Solution::operator>(const Solution & a) const
{
	return getCost() > a.getCost();
}

// LEMBRAR DE ATUALIZAR PRODUCTS
void Solution::setCell(int i, int j, int p)
{
	_cells[i][j] = p;
}

// LEMBRAR DE ATUALIZAR CELLS
void Solution::setProduct(int i, pair<int, int> p)
{
	_products[i] = p;
}

void Solution::pertubate(double p, bool its_percentage, pair<int, int> &cell1, pair<int, int> &cell2) // p = how much (in 100) pertubate
{ // change the position between (p/2)% pairs of cells (product, product|empty)
	int qtd_shelfs = _warehouse->getShelfs().size();
	vector <vector<int>> products_shelf(qtd_shelfs);
	int qtd_valid_prod = 0;
	int sizeProducts = _products.size();

	for (int i = 0; i < sizeProducts; i++) {
		if (_products[i].first != -1) {
			products_shelf[_warehouse->getCells()[_products[i].first].getIdShelf()].push_back(i);
			qtd_valid_prod++;
		}
	}

	for (int i = 0; i < sizeProducts; i++) {
		if (products_shelf[i].size() == 0) {
			products_shelf.erase(products_shelf.begin() + i);
			i--;
		}
	}

	int qtd_pert = int(its_percentage ? (p / 100.0 * qtd_valid_prod) / 2.0 : p);

	while (qtd_pert--) {
		cerr << "Vai sortear um numero menor que " << products_shelf.size() << endl;
		int shelf1 = rand() % products_shelf.size();
		cerr << "Sorteou " << shelf1 << endl;
		cerr << "Vai sortear um numero menor que " << qtd_shelfs << endl;
		int shelf2 = rand() % qtd_shelfs;
		cerr << "Sorteou " << shelf2 << endl;

		int i = rand() % products_shelf[shelf1].size();
		int j = (_warehouse->getShelfs()[shelf2].getIniCells() +
			rand() % (_warehouse->getShelfs()[shelf2].getEndCells() - _warehouse->getShelfs()[shelf2].getIniCells() + 1));
		int j2 = rand() % _cells[j].size();

		int prod1 = products_shelf[shelf1][i];
		cell1 = _products[prod1];
		cell2 = make_pair(j, j2);
		swapItem(cell1.first, cell1.second, cell2.first, cell2.second);
	}

}

void Solution::swapCell(pair<int, int> cell1, pair<int, int> cell2)
{
	int p1 = _cells[cell1.first][cell1.second];
	int p2 = _cells[cell2.first][cell2.second];
	swap(_cells[cell1.first][cell1.second], _cells[cell2.first][cell2.second]);

	if (p1 != -1)
		_products[p1] = cell2;
	if (p2 != -1)
		_products[p2] = cell1;

	if (_use_cache) {
		if (p1 != -1)
			_lazy_products.push_back(p1);
		if (p2 != -1)
			_lazy_products.push_back(p2);
	}
}

void Solution::randomTwoCell(pair<int, int>& cell1, pair<int, int>& cell2)
{
	cell1.first = rand() % _cells.size();
	cell1.second = rand() % _cells[cell1.first].size();

	cell2.first = rand() % _cells.size();
	cell2.second = rand() % _cells[cell2.second].size();


	/*
	int nShelfs, shelf1, shelf2;

	nShelfs = _warehouse->getShelfs().size();

	shelf1 = rand() % nShelfs;

	do {
		shelf2 = rand() % nShelfs;
	} while (shelf1 == shelf2);

	cell1.first = _warehouse->getShelfs()[shelf1].getIniCells() + (rand() % _warehouse->getShelfs()[shelf1].getNCells());
	cell1.second = rand() % _cells[cell1.second].size();

	cell2.first = _warehouse->getShelfs()[shelf2].getIniCells() + (rand() % _warehouse->getShelfs()[shelf2].getNCells());
	cell2.second = rand() % _cells[cell2.first].size();
	*/

}

struct lower_cost_first_pq
{
	bool operator()(const pair<pair<int, int>, long long int> &i1, const pair<pair<int, int>, long long int> &i2) const
	{
		return i1.second > i2.second;
	}
};

void Solution::localSearch() {
	priority_queue<pair<pair<int, int>, long long int>, vector<pair<pair<int, int>, long long int>>, lower_cost_first_pq> prods_to_swap;
	set<int> prods_already_swapped;
	long long int cur_cost = this->getCost();
	int qtd_shelfs = _warehouse->getShelfs().size();
	// swap every pair of diferent shelfs
	Solution s2(*this);

	for (int shelf1 = 0; shelf1 < qtd_shelfs; shelf1++) {
		printf("Vai testar prateleira %d\n", shelf1);
		for (int shelf2 = shelf1 + 1; shelf2 < qtd_shelfs; shelf2++) {
			printf("Com prateleira %d\n", shelf2);
			int initial_cell1 = _warehouse->getShelfs()[shelf1].getIniCells();
			int final_cell1 = _warehouse->getShelfs()[shelf1].getEndCells();
			int initial_cell2 = _warehouse->getShelfs()[shelf2].getIniCells();
			int final_cell2 = _warehouse->getShelfs()[shelf2].getEndCells();

			for (int p1 = initial_cell1; p1 < final_cell1; p1++) {
				for (int p2 = initial_cell2; p2 < final_cell2; p2++) {
					for (size_t n1 = 0; n1 < _cells[p1].size(); n1++) {
						for (size_t n2 = 0; n2 < _cells[p2].size(); n2++) {
							if (_cells[p1][n1] != _cells[p2][n2]) { // -1...
								s2.swapProducts(_cells[p1][n1], _cells[p2][n2]);
								s2.evaluate(SIZE_BRUTE_FORCE);
								prods_to_swap.push(make_pair(make_pair(_cells[p1][n1], _cells[p2][n2]), s2.getCost()));
								s2.swapProducts(_cells[p1][n1], _cells[p2][n2]);
							}
						}
					}
				}
			}
		}
	}
	while (prods_to_swap.size() > 0) {
		pair<int, int> cur = prods_to_swap.top().first; prods_to_swap.pop();
		set<int>::iterator it;
		if ((it = prods_already_swapped.find(cur.first)) != prods_already_swapped.end() &&
			(it = prods_already_swapped.find(cur.second)) != prods_already_swapped.end()) {
			prods_already_swapped.insert(cur.first);
			prods_already_swapped.insert(cur.second);
			swapProducts(cur.first, cur.second);
		}
	}
}

void Solution::swapItem(int i, int i2, int j, int j2)
{
	if (_cells[i][i2] != -1) {
		_products[_cells[i][i2]] = make_pair(j, j2);
	}
	if (_cells[j][j2] != -1) {
		_products[_cells[j][j2]] = make_pair(i, i2);
	}

	swap(_cells[i][i2], _cells[j][j2]);
}

void Solution::swapProducts(int i, int j)
{
	int size = _products.size();
	if (i < 0 || j < 0 || i >= size || j >= size) {
		printf("Swap products out of range indexes! (%d, %d)\n", i, j);
	}
	swap(_cells[_products[i].first][_products[i].second], _cells[_products[j].first][_products[j].second]);
	swap(_products[i], _products[j]);
}

pair<int, int> Solution::getProductPosition(int p) const
{
	return _products[p];
}

long long int Solution::getCost() const
{
	return _cost;
}

long long int Solution::getCostAnalysis() const
{
	return _cost_analysis;
}

const vector<vector<int>>& Solution::getCells() const
{
	return _cells;
}

void Solution::randomSolution()
{
	cout << "randomSolution: Depois de trocar a leitura, tem que refazer essa funcao" << endl;
	system("pause");
	exit(0);

	vector<pair<int, int>> open_cells;
	set<int> id_products;
	vector<int> ids_products;
	auto cells = _warehouse->getCells();

	for (auto it : _lists)
		for (auto prod : it.getProducts())
			id_products.insert(prod);
	for (auto it : id_products)
		ids_products.push_back(it);

	int size = cells.size();
	for (int i = 0; i < size; i++)
		for (int j = 0; j < cells[i].getLevels(); j++)
			open_cells.push_back(make_pair(i, j));

	random_shuffle(open_cells.begin(), open_cells.end());
	random_shuffle(ids_products.begin(), ids_products.end());

	size = ids_products.size();
	for (int i = 0; i < size; i++) {
		int pos = rand() % open_cells.size();
		_products[ids_products[i]] = open_cells[pos];
		swap(open_cells[pos], open_cells[open_cells.size() - 1]);
		open_cells.pop_back();
	}
}

void Solution::greedySolution()
{
	size_t pos = 0;
	/*
	 Aloca��o alternando as colunas
	int vv[] = { 0, 42, 252, 294, 84, 336, 126, 378, 168, 420, 210, 462 };
	int vv[] = { 0, 252, 42, 294, 84, 336, 126, 378, 168, 420, 210, 462 };

	for (int k = 0; k < 12; k++) {
		for (size_t i = 0; i < 42; i++) {
			for (size_t j = 0; j < _cells[vv[k] + i].size(); j++) {
				_cells[vv[k] + i][j] = _most_request[pos].first;
				_products[_most_request[pos].first].first = vv[k] + i;
				_products[_most_request[pos].first].second = j;
				pos++;
			}
		}
	}
	*/

	for (size_t i = 0; i < _cells.size(); i++) {
		for (size_t j = 0; j < _cells[i].size(); j++) {
			_cells[i][j] = _most_request[pos].first;
			_products[_most_request[pos].first].first = i;
			_products[_most_request[pos].first].second = j;
			pos++;

			if (pos >= _products.size()) return;
		}
	}
}

int findProduct(int &i, int &j, const vector<pair<int, int>> & _products, const vector<pair<int, vector<int>>> &most_correlation) {
	int size = most_correlation.size();
	int size2;
	for (; i < size; i++) {
		size2 = most_correlation[i].second.size();
		for (; j < size2; j++) {
			if (_products[most_correlation[i].second[j]].first == -1) {
				return most_correlation[i].second[j];
			}
		}
		j = 0;
	}

	return -1;
}

void Solution::greedySolution2()
{
	cout << "randomSolution: Depois de trocar a leitura, tem que refazer essa funcao" << endl;
	system("pause");
	exit(0);

	vector<pair<int, vector<int>>> most_correlation;

	for (size_t ii = 1; ii < _correlation.size(); ii++) {
		cout << ii << "  -  " << _correlation[ii].size() << endl;
		for (auto correlation : _correlation[ii])
			most_correlation.push_back(correlation);
	}
	sort(most_correlation.rbegin(), most_correlation.rend());

	int pos1 = 0;
	int pos2 = 0;
	int product;
	int i, j;
	int size = _cells.size();
	int size2;
	for (i = 0; i < size; i++) {
		size2 = _cells[i].size();
		for (j = 0; j < size2; j++) {
			product = findProduct(pos1, pos2, _products, most_correlation);

			if (product == -1) {
				goto end;
			}

			_cells[i][j] = product;
			_products[product].first = i;
			_products[product].second = j;
		}
	}

end:
	int pos = 0;
	size = _cells.size();
	for (; i < size; i++) {
		size2 = _cells[i].size();
		for (; j < size2; j++) {
			while (_products[_most_request[pos].first].first != -1) {
				pos++;
				if (pos == _most_request.size()) {
					return;

				}
			}

			_cells[i][j] = _most_request[pos].first;
			_products[_most_request[pos].first].first = i;
			_products[_most_request[pos].first].second = j;
		}
		j = 0;
	}
}

bool Solution::isValid()
{
	vector<bool> pruduct_visited(_warehouse->getProducts().size(), false);

	for (size_t i = 0; i < _cells.size(); i++) {
		for (size_t j = 0; j < _cells[i].size(); j++) {
			int product = _cells[i][j];

			if (product == -1)
				continue;

			if (pruduct_visited[product]) {
				return false;
			}

			if (_products[product].first != i || _products[product].second != j) {
				return false;
			}

			pruduct_visited[product] = true;
		}
	}

	return true;
}

void Solution::clear()
{
	for (size_t i = 0; i < _cells.size(); i++)
		for (size_t j = 0; j < _cells[i].size(); j++)
			_cells[i][j] = -1;

	fill(_products.begin(), _products.end(), make_pair(-1, -1));

	_cost = 0ll;
	_cost_analysis = 0ll;
	_use_cache = false;
	_rand_cod = _count;
	_count++;
}

void Solution::setWarehouse(Warehouse * wh)
{
	_warehouse = wh;
}

void Solution::setLists(string DIR_ORDERS)
{
	int id_list, id_product;
	string line;
	vector<string> list;

	//Read Orders
	ifstream file_orders(DIR_ORDERS);
	getline(file_orders, line);

	for (getline(file_orders, line); line != "" && line[0] != EOF; getline(file_orders, line)) {
		list = sSplit(line, DELIMITER_CSV);

		id_list = List::addCod(list[0]);
		id_product = _warehouse->getMapProducts().getId(list[1]);

		if (id_list >= int(_lists.size()))
			for (int i = _lists.size(); i <= id_list; i++)
				_lists.push_back(List(i));

		_lists[id_list].addProduct(id_product);
		_warehouse->addListToProduct(id_product, id_list);
	}

	file_orders.close();
}

const vector<List> & Solution::getLists()
{
	return _lists;
}

void Solution::makeCorrelation(int max_group, int min_correlation)
{
	_correlation = Analysis::correlation(_warehouse->getProducts().size(), _lists, max_group, min_correlation);
}

void Solution::makeMostRequests()
{
	_most_request = Analysis::mostRequest(_warehouse->getProducts().size(), _lists);

}


void Solution::getVerticesList(const vector<int> &l, vector<int> &v)
{
	long long int visited = 0;

	for (size_t i = 0; i < l.size(); i++) {
		int productCell = _products[l[i]].first;
		if (productCell == -1)
			continue;
		int vertex = _warehouse->getCells()[productCell].getVertex();
		if (!((visited) & (1ll << vertex))) {
			v.push_back(vertex);
			visited = visited | (1ll << vertex);
		}
	}
}

vector<int> getBestPath(const vector<int> &v2, const Warehouse &wh)
{
	if (v2.size() <= 7) {
		vector <int> v = v2;
		int min_cost = INFINITE;
		vector<int> route = v;
		do {
			int value = wh.getGraph().pathCost(v);
			if (value < min_cost) {
				min_cost = value;
				route = v;
			}
		} while (next_permutation(v.begin(), v.end()));
		return route;
	}
	else {
		return Path_Heuristic::getBestPath(v2, &wh.getGraph());
	}
}

void Solution::startCacheMe()
{
	_use_cache = false;
	_solution_cached = _rand_cod + 1;
	_lazy_products.clear();
	evaluate(SIZE_BRUTE_FORCE, true);
	_use_cache = true;
	_solution_cached = _rand_cod;
}

void Solution::stopCacheMe()
{
	_use_cache = false;
}

void Solution::printFile(std::string path)
{
	ofstream file;
	file.open(path);

	for (size_t i = 0; i < _products.size(); i++)
		file << _warehouse->getProducts()[i].getCod() << " " << _products[i].first << " " << _products[i].second << endl;
}

void Solution::readSolutionProducts(string path)
{
	clear();

	string line;
	vector<string> cods;
	int id_product, id_cell, level_cell;

	ifstream file_solution(path);
	for (getline(file_solution, line); line != "" && line[0] != EOF; getline(file_solution, line)) {
		cods = sSplit(line, " ");

		id_product = _warehouse->getMapProducts().getId(cods[0]);
		id_cell = stoi(cods[1]);
		level_cell = stoi(cods[2]);
		if (id_product != -1 && id_cell != -1 && level_cell != -1) {
			_products[id_product].first = id_cell;
			_products[id_product].second = level_cell;
			_cells[id_cell][level_cell] = id_product;
		}
	}
	file_solution.close();
}

void Solution::randomLocalSearch(int iterations)
{
	int i;
	long long int best_cost = _cost;

	pair<int, int> cell1, cell2;

	startCacheMe();

	for (i = 0; i < iterations; i++) {
		randomTwoCell(cell1, cell2);
		swapCell(cell1, cell2);

		evaluate(SIZE_BRUTE_FORCE);

		if (getCost() < best_cost) {
			best_cost = _cost;
			//cout << "Random ++ " << best_cost << endl;
			i = -1;
		}
		else {
			swapCell(cell1, cell2);
			evaluate(SIZE_BRUTE_FORCE);
		}
	}

	stopCacheMe();
}

void Solution::firstImprovement()
{
	vector<vector<int>> vertex = _warehouse->getVertexHasCells();
	int limit = vertex.size();

	pair<int, int> cell1, cell2;

	long long int best_cost = _cost;

	startCacheMe();

	bool repeate = true;

	while (repeate) {
		repeate = false;
		for (int vertex1 = 0; vertex1 < limit; vertex1++) {
			for (size_t i = 0; i < vertex[vertex1].size(); i++) {
				cell1.first = vertex[vertex1][i];
				for (size_t level1 = 0; level1 < _cells[cell1.first].size(); level1++) {
					cell1.second = level1;

					for (int vertex2 = vertex1 + 1; vertex2 < limit; vertex2++) {
						for (size_t j = 0; j < vertex[vertex2].size(); j++) {
							cell2.first = vertex[vertex2][j];
							for (size_t level2 = 0; level2 < _cells[cell2.first].size(); level2++) {
								swapCell(cell1, cell2);
								evaluate(SIZE_BRUTE_FORCE);

								if (getCost() < best_cost) {
									best_cost = _cost;
									cout << "First ++ " << best_cost << endl;
									repeate = true;
								}
								else {
									swapCell(cell1, cell2);
									evaluate(SIZE_BRUTE_FORCE);
								}
							}
						}
					}
				}
			}
		}
	}

	stopCacheMe();
}

int Solution::amountVaos() const
{
	return _warehouse->getAmountVaos();
}

/// Function to evaluate a cost of a solution
///
void Solution::evaluate(int bruteForceSize, bool cache_lists)
{
	int result;
	vector <int> v;

	if (_use_cache && _solution_cached == _rand_cod) {
		for (int prod : _lazy_products) {
			for (int list : _warehouse->getProducts()[prod].getLists()) {
				_cost -= _lists[list].getCost();

				v.clear();
				getVerticesList(_lists[list].getProducts(), v);

				result = _warehouse->bestPathCost(v, bruteForceSize);
				_lists[list].setCost(result);

				_cost += (long long)result;
			}
		}

		_lazy_products.clear();
	}
	else {
		_cost = 0;

		for (size_t i = 0; i < _lists.size(); i++) {
			v.clear();
			getVerticesList(_lists[i].getProducts(), v);

			result = _warehouse->bestPathCost(v, bruteForceSize);

			if (cache_lists)
				_lists[i].setCost(result);

			_cost += long long(result);
		}

	}
}

void Solution::evaluateAnalysis()
{
	Point point;
	int productCell, vertex;
	_cost_analysis = 0ll;
	for (size_t i = 0; i < _correlation.size(); i++) {
		for (size_t j = 0; j < _correlation[i].size(); j++) {
			point.setCoords(0, 0, 0);
			for (size_t k = 0; k < _correlation[i][j].second.size(); k++) {
				productCell = getProductPosition(_correlation[i][j].second[k]).first;
				vertex = _warehouse->getCells()[productCell].getVertex();
				point.addPoint(_warehouse->getGraph().getVertex(vertex));
			}
			point.divisionInt(_correlation[i][j].second.size());
			if (i == 1) {
				point.setCoords(0, 0, 0);
			}
			for (size_t k = 0; k < _correlation[i][j].second.size(); k++) {
				productCell = getProductPosition(_correlation[i][j].second[k]).first;
				vertex = _warehouse->getCells()[productCell].getVertex();
				_cost_analysis += (long long int)Point::distance(point, _warehouse->getGraph().getVertex(vertex)) * _correlation[i][j].first * i;
			}
		}
	}
}

/// Get the poisition of the products
const vector<pair<int, int>> & Solution::getProducts() const {
	return _products;
}

/// Converts a pair to a json format
/// @param j Json environment. It will receive the result of the function
/// @param p pair to be converted
void to_json(json &j, const pair<int, int> &p)
{
	j = json{ { "Cell", p.first },{ "Level", p.second } };
}

/// Converts a solution to the json format
/// @param j Json environment
/// @param s Solution to be converted
void to_json(json &j, const Solution &s)
{
	for (size_t i = 0; i < s.getProducts().size(); i++) {
		string aux = "Product " + to_string(i);
		pair<int, int> p = s.getProductPosition(i);
		if (p.first != -1 && p.second != -1) {
			j += json{ aux, s.getProductPosition(i) };
		}
	}
}

/// Return the json of solution translated to a string
/// @return The json environment dump
string Solution::getJson() const
{
	json j = (*this);
	return j.dump();
}
