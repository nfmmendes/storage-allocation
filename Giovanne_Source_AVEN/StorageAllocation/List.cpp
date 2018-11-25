#include "List.h"

using namespace std;

MapCod List::_map_cod;

List::List()
{
	_id_list = -1;
}

List::List(int id)
{
	_id_list = id;
}

List::~List()
{
}

void List::addProduct(int id_product)
{
	_products.push_back(id_product);
}

void List::setCost(int cost)
{
	_cost = cost;
}

long long int List::getCost() const
{
	return _cost;
}

const std::vector<int>& List::getProducts() const
{
	return _products;
}

const MapCod & List::getMapCod() const
{
	return _map_cod;
}

int List::addCod(const std::string & cod)
{
	return _map_cod.addCod(cod);
}
