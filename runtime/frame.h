#ifndef _FRAME_H_
#define _FRAME_H_

#include <deque>
#include <vector>
#include "instruction.h"
#include "variable.h"
#include "class.h"
#include "heap.h"

using namespace std;

class Heap;

class Frame
{
	public:
			Frame ( int _class, int method, const vector<Var> & vars, const ClassPool & classPool, Frame * parent        );
			Frame ( int _class, int method, const vector<Var> & vars, const ClassPool & classPool, Var ** returnAddress  );
	void 	Process ( const Instruction & instr );
	void 	Trace ();
	
	private:
	vector<Var> 						m_Vars;
	deque <Var> 						m_Stack;
	
	int                                 m_Class;
	const ClassPool &			  		m_ClassPool;
	
	const vector<Instruction> *		  	m_Code; 
	vector<Instruction>::const_iterator m_PC;
	Var 						     ** m_ReturnAddress;
	
	Frame 						  	  * m_Parent;
	static Heap 						m_Heap;
	 
	friend ostream & operator << ( ostream & os, const Frame & x );
	friend class Heap;
};

ostream & operator << ( ostream & os, const Frame & x );

#endif
