#include "variable.h"
#include <vector>

using namespace std;

class Heap
{
	void Alloc ( Var & x );
	
	void Gc ();
	
	private:
	static vector<vector<Var>> * m_Heap;
};
