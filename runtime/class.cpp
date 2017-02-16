#include "class.h"

using namespace std;

Class :: Class ( const map<int,vector<Instruction>> & codes, 
                 const map<int,vector<Var>> 	    & signatures, 
                 const vector<Var>				    & constants, 
				 const vector<Var>				    & members		
               ) 
			   : m_Codes      ( codes ), 
				 m_Signatures ( signatures ),
				 m_Constants  ( constants  ),
				 m_Members    ( members ) 
{}

const vector<Var> & Class :: getSignature ( int i ) const
{
	const vector<Var> * signature = NULL;
	try 
	{	
		signature = & ( m_Signatures . at ( i ) );
	}
	catch ( out_of_range & )
	{
		throw runtime_error ( "Cant find invoked method signature." );
	}
	return * signature;
}

Var Class :: getConstant ( int i ) const
{
	Var constant;
	try 
	{	
		constant = m_Constants . at ( i );
	}
	catch ( out_of_range & )
	{
		throw runtime_error ( "Cant find constant." );
	}
	return constant;
}

const vector<Var> & Class :: getMembers () const
{ 
	return m_Members; 
}

const vector<Instruction> * Class :: getCode ( int i ) const
{
	const vector<Instruction> * code = NULL;
	try 
	{	
		code = & ( m_Codes . at ( i ) );
	}
	catch ( out_of_range & )
	{
		throw runtime_error ( "Cant find invoked method code." );
	}
	return code;
}

 
ClassPool :: ClassPool ( const map<int, Class> & classes ) : m_Classes ( classes ) {}

const Class & ClassPool :: getClass ( int i ) const
{
	const Class * _class = NULL;
	try 
	{	
		_class = & ( m_Classes . at ( i ) );
	}
	catch ( out_of_range & )
	{
		throw runtime_error ( "Cant find class." );
	}
	return * _class;
} 
	
