#ifndef _FRAME_H_
#define _FRAME_H_

#include <deque>
#include <vector>
#include "instruction.h"
#include "variable.h"
#include "constantpool.h"

using namespace std;

class Frame
{
public:
			Frame ( int i, const vector<Var> & vars, ConstantPool * constantPool, Frame * parent );
			Frame ( int i, const vector<Var> & vars, ConstantPool * constantPool, Var ** returnAddress );
	void 	Process ( Instruction & instr );
	void 	StackTrace ();
	
private:
	vector<Var> 					m_Vars;
	deque <Var> 					m_Stack;
	ConstantPool				  * m_ConstantPool;
	
	vector<Instruction> *		  	m_Code; 
	vector<Instruction>::iterator 	m_PC;
	Frame 						  * m_Parent;
	Var 						 ** m_ReturnAddress;

	 
	friend ostream & operator << ( ostream & os, const Frame & x );
};

ostream & operator << ( ostream & os, const Frame & x );

#endif
