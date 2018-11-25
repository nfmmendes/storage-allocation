#ifndef H_PRODUCT
#define H_PRODUCT

#include "Globals.h"
#include "Dimension.h"
#include "MapCod.h"
#include <string>
#include <vector>

class Product
{
private:
	int _id;
	std::string _cod;
	//int _weight;
	//std::string _measurement_unit;
	//std::string _family;
	//Dimension _dim;
	std::vector<int> _lists;

public:
	Product();
	~Product();

	Product(int id, std::string cod);
	Product& operator= (const Product &p);

	int getId() const;
	std::string getCod() const;
	//int getWeight() const;
	//std::string getMeasurement() const;
	//std::string getFamily() const;
	//Dimension getDimension() const;

	void addList(int id_list);

	const std::vector<int> & getLists() const;

	void print(char separator);
};

#endif
