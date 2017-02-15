#ifndef _HEAP_H_
#define _HEAP_H_

#include "variable.h"
#include <vector>

using namespace std;

class Heap
{
	public:
	void Alloc ( Var & x );
	
	void Gc ();
	
	private:
	static vector<vector<Var>*> m_Heap;
};

#endif
