#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include <iostream>
#include <vector>

//#include "constantpool.h"

using namespace std;

struct Var;

class ConstantPool;

enum Type
{
	CHAR,
	INT,
	FLOAT,
	ARRAY,
	REFERENCE
};

struct Ref
{
	ConstantPool * m_Class;
	vector<Var>  * m_Members;
};

struct Arr
{
	vector<Var> * m_Array;
};

union Val
{
	char 	m_Char;
	int 	m_Int;
	float	m_Float;
	Ref     m_Reference;	
	Arr     m_Array;
};

struct Var
{
	int   	m_Type;
	Val 	m_Val;
	
	Var () = default;
	
	Var ( int type, Val val );
	
	Var ( int   val );
	Var ( char  val );
	Var ( float val );
};

ostream & operator << ( ostream & os, const Var & x );

#endif
