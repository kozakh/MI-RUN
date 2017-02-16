#include "instruction.h"
#include <iomanip>

using namespace std;

const vector<Var> Instruction :: DUMMY;

const map<int, int> Instruction :: OPERANDS_NR = 
{ 
	{ Opcode :: ISTORE,       1 },
	{ Opcode :: ILOAD,        1 },
	{ Opcode :: INVOKESTATIC, 1 },  
	{ Opcode :: INVOKEVIRTUAL,1 },  
	{ Opcode ::	IF_ICMPNE,    1 }, 
	{ Opcode ::	IF_ICMPEQ,    1 }, 
	{ Opcode :: LDC, 	      1 },
	{ Opcode :: NEWARRAY,     1 },
	{ Opcode :: NEW,          1 },
	{ Opcode :: ASTORE,       1 },
	{ Opcode :: ALOAD,        1 },
	{ Opcode :: GETFIELD,     1 },
	{ Opcode :: PUTFIELD,     1 },
	{ Opcode :: GOTO, 		  1 }
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
		throw std::runtime_error ( "Error, bad number of operands for instruction ( " + to_string ( opcode ) + ")" );	
}

Var Instruction :: operator [] ( int i ) const
{ 
	if ( i < 0 || i >= m_OperandsNr )
	{
		cout << "Invalid opcode:" << m_Opcode << endl;	
		throw std::runtime_error ( "Error, bad instruction operand index." );	
	}
	else 
		return m_Operands . at ( i ); 
}


