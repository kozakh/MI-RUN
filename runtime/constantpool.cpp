#include "constantpool.h"

using namespace std;

ConstantPool :: ConstantPool ( const map<int,vector<Instruction>> & codes, 
                               const map<int,vector<Var>> 	      & signatures, 
                               const vector<Var>				  & constants,
                               const vector<Var>				  & members ) 
                               : m_Codes      ( codes ),
								 m_Signatures ( signatures ),
								 m_Constants  ( constants  ),
								 m_Members    ( members )
{}

ConstantPool :: ConstantPool ( const map<int,vector<Instruction>> & codes,
		 					   const map<int,vector<Var>> 		  & signatures,
		 					   const vector<Var> 				  & constants )
		 					   : m_Codes	  ( codes ),
		 					     m_Signatures ( signatures ),
		 					     m_Constants  ( constants )
{}


vector<Var> & ConstantPool :: getSignature ( int i )
{
	vector<Var> * signature = NULL;
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

Var ConstantPool :: getConstant ( int i )
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

Var ConstantPool :: getMember ( int i )
{
	Var member;
	try
	{
		member = m_Members . at ( i );
	}
	catch ( out_of_range & )
	{
		throw runtime_error ( "Cant find member." );
	}

	return member;
}

vector<Var> & ConstantPool :: getMembers   ()
{
	return m_Members;
}

vector<Instruction> * ConstantPool :: getCode ( int i ) 
{
	vector<Instruction> * code = NULL;
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
