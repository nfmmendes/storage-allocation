#ifndef H_GLOBALS
#define H_GLOBALS

#define DELIMITER_CSV "\t"

#include <string>

#define DIR_BLOCKS "Blocos2.txt"
#define DIR_SHELFS "Prateleiras2.txt"
#define DIR_CELLS "Celulas2.txt"

#define SIZE_BRUTE_FORCE 12
#define INFINITE 1<<29
#define CHECK_BIT(var, pos) ((var) & (1<<(pos)))
#define ADD_BIT(var, pos) var | (1<<pos)
#define DEL_BIT(var, pos) var ^ (1<<pos)

#endif // !H_GLOBALS
