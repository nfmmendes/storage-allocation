#ifndef H_LIST
#define H_LIST

#include "MapCod.h"
#include <vector>

class List
{
private:
	static MapCod _map_cod;

	int _id_list;
	long long int _cost;
	std::vector<int> _products;

public:
	List();
	List(int id);
	~List();

	void addProduct(int id_product);
	void setCost(int cost);
	long long int getCost() const;

	const std::vector<int> & getProducts() const;
	const MapCod & getMapCod() const;

	static int addCod(const std::string & cod);
};

#endif
