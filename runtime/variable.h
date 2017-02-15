#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include <iostream>

using namespace std;

enum Type
{
	CHAR,
	INT,
	FLOAT,
	FIELD,
	REFERENCE
};
/*
struct Ref
{
	ConstantPool * m_Class;
	vector<Var> *  m_Data;
}
*/

union Value
{
	char 	m_Char;
	int 	m_Int;
	float	m_Float;
	//Ref     m_Reference;	
};

struct Var
{
	int   m_Type;
	Value m_Val;
	
	Var () = default;
	
	Var ( int type, Value val );
	
	Var ( bool val );
	Var ( int val );
	Var ( char val );
	Var ( float val );
};

ostream & operator << ( ostream & os, const Var & x );

#endif
