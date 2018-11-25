#include "MapCod.h"

using namespace std;

MapCod::MapCod()
{
}


MapCod::~MapCod()
{
}

int MapCod::addCod(const std::string & cod)
{
	auto it = _cod_to_id.find(cod);

	if (it == _cod_to_id.end()) {
		_cod_to_id[cod] = int(_id_to_cod.size());
		_id_to_cod.push_back(cod);
		it = _cod_to_id.find(cod);
	}

	return it->second;
}

std::string MapCod::getCod(int id) const
{
	if (id < 0 || id >= int(_id_to_cod.size())) {
		cout << "Invalide index: " << id << " - " << _id_to_cod.size() << endl;
		cout << "File: " << __FILE__ << endl;
		cout << "Line: " << __LINE__ << endl;
		system("pause");
		exit(0);
	}

	return _id_to_cod[id];
}

int MapCod::getId(string cod) const
{
	auto it = _cod_to_id.find(cod);

	if (it == _cod_to_id.end()) {
		return -1;
	}

	return it->second;
}
