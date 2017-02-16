#include "heap.h"
#include <algorithm>

using namespace std;

set<vector<Var>*> Heap :: m_Heap;
 
void Heap :: Alloc ( Var & x, const ClassPool & classPool )
{
	if ( x . m_Type != Type :: REFERENCE && x . m_Type != Type :: ARRAY )
		return;
		
	if 		( x . m_Type == Type :: ARRAY )
	{
		x . m_Val . m_Array . m_Members = new vector<Var> ( x . m_Val . m_Array . m_Len ); 
		
		for ( auto i  = x . m_Val . m_Array . m_Members -> begin (); 
				   i != x . m_Val . m_Array . m_Members -> end ();   ++ i )
			(*i) . m_Type = x . m_Val . m_Array . m_Type; 
		
		m_Heap . insert ( x . m_Val . m_Array . m_Members );
	
		cout << "HEAP: Allocated new field." << endl;
		
		//cout << x << endl;
	}
	
	else if ( x . m_Type == Type :: REFERENCE )
	{
		
		const vector<Var> * prototype = NULL;
		try
		{
			prototype = & (classPool . getClass ( x . m_Val . m_Reference . m_Class ) . getMembers ());
			/*
			cout << "!!!!!!!!!!!" << endl;
			for ( int i  = 0; i < prototype -> size (); i ++ )
				cout << (*prototype) [0] << " ";
			cout << endl;	
			*/
		}
		
		catch ( out_of_range & )
		{
			throw runtime_error ( "Cant find class." );
		}
		
		x . m_Val . m_Reference . m_Members = new vector<Var> ( * prototype ); 
		m_Heap . insert ( x . m_Val . m_Reference . m_Members );
	}		
} 

void Heap :: Gc ( const Frame & frame )
{
	set<vector<Var>*> reachable;
	
	const Frame * current = & frame;
	
	while ( current )
	{
		for ( int i = 0; i < current -> m_Vars . size (); i ++ )
		{
			if 		( current -> m_Vars [i] . m_Type == Type :: ARRAY 
				   && current -> m_Vars [i] . m_Val . m_Array . m_Members )
			{
				reachable . insert ( current -> m_Vars [i] . m_Val . m_Array . m_Members );
			} 
			 
			else if ( current -> m_Vars [i] . m_Type == Type :: REFERENCE  
				   && current -> m_Vars [i] . m_Val . m_Reference . m_Members )
			{
				reachable . insert ( current -> m_Vars [i] . m_Val . m_Reference . m_Members );
			} 
		}
		for ( auto i : current -> m_Stack )
		{
			if 		( i . m_Type == Type :: ARRAY 
				   && i . m_Val . m_Array . m_Members )
			{
				reachable . insert ( i . m_Val . m_Array . m_Members );
			} 
			 
			else if ( i . m_Type == Type :: REFERENCE  
				   && i . m_Val . m_Reference . m_Members )
			{
				reachable . insert ( i . m_Val . m_Reference . m_Members );
			} 
		}
		current = current -> m_Parent;
	}
	
	set<vector<Var> *> diff;
	 
	set_difference ( m_Heap . begin (), m_Heap . end (), reachable . begin (), reachable . end (), inserter ( diff, diff . end () ) );  
	
	cout << "GC:" << endl;
	for ( auto i : diff )
	{
		cout << "(";
		for ( auto j = i -> begin (); j != i -> end (); ++ j )
		{
			cout << *j; 
			auto k = j; 
			if ( ++ k != i -> end () ) 
				cout << " "; 
		}
		cout << ") ";
		m_Heap . erase ( i );
		delete i;
	}

	cout << endl << "**********" << endl; 
}
