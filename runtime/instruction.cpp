#include "instruction.h"
#include <iomanip>

using namespace std;

const map<int, int> Instruction :: OPERANDS_NR = 
{ 
	{ Opcode :: ISTORE,       1 },
	{ Opcode :: ILOAD,        1 },
	{ Opcode :: INVOKESTATIC, 1 },  
	{ Opcode ::	IF_ICMPNE,    1 }, 
	{ Opcode :: LDC, 	      1 }
};

/*
istream & Instruction :: Load ( istream & is )
{
	is >> hex >> m_Opcode;
	for ( int i = 0; i < getOperandsNr (); i++ ) 
		is >> m_Operands [i]; 
	return is;
}
*/

Instruction :: Instruction ( int opcode, const vector<Var> & operands ) : m_Opcode ( opcode ), m_Operands ( operands )
{
	try 
	{ 
		m_OperandsNr = OPERANDS_NR . at ( m_Opcode ); 
	}
	catch ( out_of_range & ) 
	{ 
		m_OperandsNr = 0; 
	}
	if ( operands . size () != (unsigned) m_OperandsNr )
		throw std::runtime_error ( "Error, bad number of operands for instruction." );	
}

Var Instruction :: operator [] ( int i ) 
{ 
	if ( i < 0 || i >= m_OperandsNr )
		throw std::runtime_error ( "Error, bad instruction operand index." );	
	
	else 
		return m_Operands . at ( i ); 
}


