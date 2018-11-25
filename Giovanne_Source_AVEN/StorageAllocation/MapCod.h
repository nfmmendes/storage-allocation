#ifndef H_MAPCOD
#define H_MAPCOD

#include <map>
#include <vector>
#include <iostream>

class MapCod
{
private:
	std::map<std::string, int> _cod_to_id;
	std::vector<std::string> _id_to_cod;

public:
	MapCod();
	~MapCod();

	int addCod(const std::string & cod);
	std::string getCod(int id) const;
	int getId(std::string cod) const;
};

#endif // !H_MAPCOD
