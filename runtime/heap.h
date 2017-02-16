#ifndef _HEAP_H_
#define _HEAP_H_

#include <vector>
#include <set>

#include "variable.h"
#include "class.h"
#include "frame.h"


using namespace std;

class Frame;

class Heap
{
	public:
//	Heap ( const ClassPool & classPool );
	
	void Alloc ( Var & x, const ClassPool & classPool );
	
	void Gc ( const Frame & frame );
	
	private:
	static set<vector<Var>*> m_Heap; 
};

#endif
