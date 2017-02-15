#include "heap.h"

using namespace std;

void Heap :: Alloc ( Var & x )
{
	if ( x . m_Type != Type :: REFERENCE && x . m_Type != Type :: ARRAY )
		return;
	
	
	if 		( x . m_Type == Type :: ARRAY )
	{
	/*
		x . m_Val . m_Reference = new vector<Var> (); 
		for ( int i = 0; i < len; i ++ )
		{
			x . push_back ( type );
			m_Heap . push_back ( x . m_Reference );
			
			Alloc ( )
		}
	*/ 
	}
	
	else if ( x . m_Type == Type :: REFERENCE )
	{
	/*
		vector<Var> * prototype;
		
		try
		{
			prototype = & ( x . m_Class -> m_ConstantPool -> getMembers () );
		}
		
		catch ( out_of_range & )
		{
			throw runtime_error ( "Cant find prototype." );
		}
		x . m_Reference = new vector<Var> ( prototype ); 
		m_Heap . push_back ( x . m_Reference );
	*/
	}		
} 

