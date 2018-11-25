#ifndef H_WAREHOUSE
#define H_WAREHOUSE

#include "Globals.h"
#include "Block.h"
#include "Shelf.h"
#include "Cell.h"
#include "Product.h"
#include "Functions.h"
#include "Graph.h"
#include "Path_Heuristic.h"
#include "MapCod.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>

class Warehouse
{
private:
	std::vector<Block> _blocks;
	std::vector<Shelf> _shelfs;
	std::vector<Cell> _cells;
	std::vector<Product> _products;
	std::vector<std::vector<int>> _vertex_has_cells;
	Graph _graph;

	MapCod _map_products;

	std::unordered_map<int, int> cache_routes;
	int _amount_vaos;

public:
	Warehouse();
	~Warehouse();

	void addBlock(const Block &b);
	void addShelf(const Shelf &s);
	void addCell(const Cell &c);
	void addProduct(const Product &p);

	const std::vector<Block> & getBlocks() const;
	const std::vector<Shelf> & getShelfs() const;
	const std::vector<Cell> & getCells() const;
	const std::vector<Product> & getProducts() const;
	const std::vector<std::vector<int>> & getVertexHasCells() const;
	const Graph & getGraph() const;

	const MapCod & getMapProducts() const;

	int getAmountVaos() const;

	void readWarehouse(std::string DIR_PRODUCTS);

	int bestPathCost(std::vector<int> &v, int bruteForceSize);
	void addListToProduct(int id_product, int id_list);
	void addCellsToVertex();

	void print(char separator);
};

#endif
