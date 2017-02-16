#include "variable.h"

using namespace std;

Var :: Var ( int type, Val val ) : m_Type ( type ), m_Val ( val ) {
	//cout << "Val = " << val . m_Int << endl; 
	}

ostream & operator << ( ostream & os, const Var & x )
{
	switch ( x . m_Type )
	{
		case Type :: INT :
		{
			cout << x . m_Val . m_Int;
			break;
		}
		case Type :: ARRAY :
		{
			if ( x . m_Val . m_Int ) 
			{
			//cout << "ARRAY [" << x . m_Val . m_Array . m_Len << "]"; //<< endl;
			//cout << "[";
				cout << "(";
				for ( int i = 0; i < x . m_Val . m_Array . m_Len - 1; i ++ )
					cout << (*(x . m_Val . m_Array . m_Members))[i] << " ";
				cout << (*(x . m_Val . m_Array . m_Members))[x . m_Val . m_Array . m_Len - 1] << ")";
			}
			else cout << "(NULL)" << endl;
			break;
		}
		case Type :: REFERENCE :
		{
			//cout << "(" << x . m_Val . m_Reference . m_Members -> size () << ")"; //<< endl;
			if ( x . m_Val . m_Int ) 
			{
				cout << "(";
				for ( int i = 0; i < x . m_Val . m_Reference . m_Members -> size () - 1; i ++ )
				{
					cout << (*(x . m_Val . m_Reference . m_Members))[i] << " ";
				}
				cout << (*(x . m_Val . m_Array . m_Members))[x . m_Val . m_Reference . m_Members -> size () - 1] << ")";
			}	
			else cout << "(NULL)" << endl;
							
			break;
		}
		
		default:
		{
			cout << "ERROR:" << x . m_Type << endl;
			//throw std::runtime_error ( "Unimplemented operator << for this type."  );
		}
	}
	return os;
}

Var :: Var ( int val )  : m_Type ( Type :: INT ), 		m_Val { . m_Int = val } {}

Var :: Var ( char val ) : m_Type ( Type :: CHAR ), 		m_Val { . m_Char = val } {}

Var :: Var ( float val ) : m_Type ( Type :: FLOAT ), 	m_Val { . m_Float = val } {}

	
