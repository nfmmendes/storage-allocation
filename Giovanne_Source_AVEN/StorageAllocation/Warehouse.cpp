#include "Warehouse.h"

using namespace std;

Warehouse::Warehouse()
{
}

Warehouse::~Warehouse()
{
}

void Warehouse::addBlock(const Block & b)
{
	_blocks.push_back(b);
}

void Warehouse::addShelf(const Shelf & s)
{
	_shelfs.push_back(s);
}

void Warehouse::addCell(const Cell & c)
{
	_cells.push_back(c);
}

void Warehouse::addProduct(const Product & p)
{
	_products.push_back(p);
}

void Warehouse::readWarehouse(string DIR_PRODUCTS)
{
	int i;
	string line, cod;
	_amount_vaos = 0;

	//Read Products
	ifstream file_products(DIR_PRODUCTS);
	getline(file_products, line);
	size_t id;
	for (getline(file_products, line); line != "" && line[0] != EOF; getline(file_products, line)) {
		cod = sSplit(line, DELIMITER_CSV)[1];
		id = _map_products.addCod(cod);

		if (id >= _products.size())
			for (size_t i = _products.size(); i <= id; i++) {
				addProduct(Product(i, cod));
			}
	}
	file_products.close();

	//Read Blocks
	ifstream file_blocks(DIR_BLOCKS);
	getline(file_blocks, line);
	for (getline(file_blocks, line); line != "" && line[0] != EOF; getline(file_blocks, line)) {
		addBlock(Block(sSplit(line, DELIMITER_CSV)));
	}
	file_blocks.close();

	//Read Shelfs
	ifstream file_shelfs(DIR_SHELFS);
	i = 0;
	getline(file_shelfs, line);
	for (getline(file_shelfs, line); line != "" && line[0] != EOF; getline(file_shelfs, line)) {
		addShelf(Shelf(sSplit(line, DELIMITER_CSV)));
		_blocks[_shelfs[i].getIdBlock()].addRangeShelfs(i);
		i++;
	}
	file_shelfs.close();

	for (size_t j = 0, v = 1; j < _shelfs.size(); j++) {
		_shelfs[j].addVertex(v);
		v += 3;
		if (_shelfs[j].getLines() == 2)
			_shelfs[j].addVertex(v);

		if (j + 1 < _shelfs.size() && _shelfs[j].getPos().getX() != _shelfs[j + 1].getPos().getX())
			v += 3;
	}

	//Read Cells
	ifstream file_cells(DIR_CELLS);
	i = 0;
	getline(file_cells, line);
	for (getline(file_cells, line); line != "" && line[0] != EOF; getline(file_cells, line)) {
		addCell(Cell(sSplit(line, DELIMITER_CSV)));
		_shelfs[_cells[i].getIdShelf()].addRangeCells(i);
		i++;
	}
	file_cells.close();

	//Define which edge access the cell
	for (size_t j = 0; j < _shelfs.size(); j++)
		_shelfs[j].setVertexCells(_cells);

	_graph = Graph(_shelfs);

	addCellsToVertex();

	for (auto cell : _cells) {
		_amount_vaos += cell.getLevels();
	}
}

/// Gets the path cost given a warehouse configuration and a sequence of pickings (integers)
/// @param v2 Sequence
/// @param wh Warehouse configuration
/// @return The cost of the path
int Warehouse::bestPathCost(vector<int>& v, int bruteForceSize)
{
	int bit_mask = 0;
	for (int it : v)
		bit_mask |= 1 << (it / 3);

	auto it = cache_routes.find(bit_mask);
	if (it != cache_routes.end())
		return it->second;

	int min_cost = INFINITE;

	int size = v.size();
	if (size <= 5 && size <= bruteForceSize) {
		sort(v.begin(), v.end());
		do {
			int value = _graph.pathCost(v);
			if (value < min_cost) {
				min_cost = value;
			}
		} while (next_permutation(v.begin(), v.end()));		//Test all sequences (???)
	}
	else if (size <= bruteForceSize) {
		min_cost = _graph.pathCostMitm(v);
	}
	else {
		//cout << "AQUI EH LENTIDAO: " << v.size() << endl;
		min_cost = Path_Heuristic::getBestCost(v, &_graph);
	}

	cache_routes[bit_mask] = min_cost;
	return min_cost;
}

void Warehouse::addListToProduct(int id_product, int id_list)
{
	_products[id_product].addList(id_list);
}

void Warehouse::addCellsToVertex()
{
	size_t vertex;

	for (size_t i = 0; i < _cells.size(); i++) {
		vertex = _cells[i].getVertex() / 3;
		if (vertex >= _vertex_has_cells.size())
			_vertex_has_cells.push_back(vector<int>());

		_vertex_has_cells[vertex].push_back(i);
	}
}

void Warehouse::print(char sep)
{
	printf("Num products: %lu%c", _products.size(), sep);
	printf("Num blocks: %lu%c", _blocks.size(), sep);
	printf("Num shelfs: %lu%c", _shelfs.size(), sep);
	printf("Num cells: %lu\n", _cells.size());
}

const vector<Block> & Warehouse::getBlocks() const
{
	return _blocks;
}

const vector<Shelf> & Warehouse::getShelfs() const
{
	return _shelfs;
}

const vector<Cell> & Warehouse::getCells() const
{
	return _cells;
}

const vector<Product> & Warehouse::getProducts() const
{
	return _products;
}

const std::vector<std::vector<int>>& Warehouse::getVertexHasCells() const
{
	return _vertex_has_cells;
}

const Graph & Warehouse::getGraph() const
{
	return _graph;
}

const MapCod & Warehouse::getMapProducts() const
{
	return _map_products;
}

int Warehouse::getAmountVaos() const
{
	return _amount_vaos;
}
