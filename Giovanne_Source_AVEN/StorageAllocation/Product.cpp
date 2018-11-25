#include "Product.h"

using namespace std;

/// Class constructor
Product::Product()
{
}


///Class destructor
Product::~Product()
{
}

Product::Product(int id, std::string cod)
{
	_id = id;
	_cod = cod;
}

/// Operator = overload (assignment overload)
/// @param newValue Updated value 
Product & Product::operator=(const Product & newValue)
{
	_id = newValue._id;
	_cod = newValue._cod;
	//_weight = newValue._weight;
	//_measurement_unit = newValue._measurement_unit;
	//_family = newValue._family;
	//_dim = newValue._dim;
	_lists = newValue._lists;

	return *this;
}

int Product::getId() const
{
	return _id;
}

string Product::getCod() const
{
	return _cod;
}

/*
int Product::getWeight() const
{
	return _weight;
}

string Product::getMeasurement() const
{
	return _measurement_unit;
}

string Product::getFamily() const
{
	return _family;
}

Dimension Product::getDimension() const
{
	return _dim;
}
*/

void Product::addList(int id_list)
{
	_lists.push_back(id_list);
}

const std::vector<int>& Product::getLists() const
{
	return _lists;
}

void Product::print(char sep)
{
	printf("ID: %d%c", _id, sep);
	//printf("Weight: %d%c", _weight, sep);
	//printf("Dimension: ");
	//_dim.print();
	//printf("%c", sep);
	//printf("Family: %s%c", _family.c_str(), sep);
	//printf("Measurement: %s%c\n", _measurement_unit.c_str(), sep);
}
