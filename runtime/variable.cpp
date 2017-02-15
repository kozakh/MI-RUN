#include "variable.h"

using namespace std;

Var :: Var ( int type, Value val ) : m_Type ( type ), m_Val ( val ) {}

ostream & operator << ( ostream & os, const Var & x )
{
	switch ( x . m_Type )
	{
		case Type :: INT :
		{
			cout << "INT " << x . m_Val . m_Int;
			break;
		}
		default:
		{
			cout << "ERROR:" << x . m_Type << endl;
			throw std::runtime_error ( "Unimplemented operator << for this type."  );
		}
	}
	return os;
}

Var :: Var ( int val )  : m_Type ( Type :: INT ), 		m_Val { . m_Int = val } {}

Var :: Var ( char val ) : m_Type ( Type :: CHAR ), 		m_Val { . m_Char = val } {}

Var :: Var ( float val ) : m_Type ( Type :: FLOAT ), 	m_Val { . m_Float = val } {}

	
