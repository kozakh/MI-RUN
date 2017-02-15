#include "heap.h"

using namespace std;

vector<vector<Var>*> Heap :: m_Heap;

void Heap :: Alloc ( Var & x )
{
	if ( x . m_Type != Type :: REFERENCE && x . m_Type != Type :: ARRAY )
		return;
		
	if 		( x . m_Type == Type :: ARRAY )
	{
		x . m_Val . m_Array . m_Members = new vector<Var> ( x . m_Val . m_Array . m_Len ); 
		
		//cout << "Allocating field of len:  " << x . m_Val . m_Array . m_Len << endl;
		//cout << "Allocating field of type: " << x . m_Val . m_Array . m_Type << endl;
		
		for ( auto i  = x . m_Val . m_Array . m_Members -> begin (); 
				   i != x . m_Val . m_Array . m_Members -> end ();   ++ i )
			(*i) . m_Type = x . m_Val . m_Array . m_Type; 
		
		m_Heap . push_back ( x . m_Val . m_Array . m_Members );
	
		cout << "Allocated new field" << endl;
		
		cout << x << endl;
	}
	
	else if ( x . m_Type == Type :: REFERENCE )
	{
		vector<Var> * prototype = NULL;
		try
		{
		//	prototype = & ( x . m_Class -> m_ConstantPool -> getMembers () );
		}
		
		catch ( out_of_range & )
		{
			throw runtime_error ( "Cant find prototype." );
		}
		x . m_Val . m_Reference . m_Members = new vector<Var> ( * prototype ); 
		
		for ( auto i  = x . m_Val . m_Reference . m_Members -> begin (); 
		           i != x . m_Val . m_Reference . m_Members -> end ();   ++ i )
		{
				Alloc ( *i );
		}
		
		m_Heap . push_back ( x . m_Val . m_Reference . m_Members );
	}		
} 

