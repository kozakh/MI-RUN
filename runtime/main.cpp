#include <vector>
#include <deque>

#include "frame.h"
#include "variable.h"
#include "constantpool.h"
#include "instruction.h"

using namespace std;


int main ()
{	
	const map<int,vector<Instruction>> codes = 
	{
		{
			1, //FOR CYCLUS
			{
				{ Opcode :: ILOAD,     { 0 } }, //ILOAD 0
				{ Opcode :: LDC,       { 0 } }, //ILOAD 2 
				{ Opcode :: IADD,      {   } }, //IADD
				{ Opcode :: ISTORE,    { 0 } }, //ISTORE 2
				
				{ Opcode :: ILOAD,     { 0 } }, //ILOAD 0
				{ Opcode :: ILOAD,     { 1 } }, //ILOAD 1 
				{ Opcode :: IF_ICMPNE, { 0 } } //IF_CMPEG 0
			}
		},
		{
			2, //CALCULATOR
			{
				{ Opcode :: ILOAD,  { 0 } }, //ILOAD 0
				{ Opcode :: ILOAD,  { 1 } }, //ILOAD 0
				{ Opcode :: IADD,   {   } }, //IADD
				{ Opcode :: ISTORE, { 2 } }, //ISTORE 2
				
				{ Opcode :: ILOAD,  { 0 } }, //ILOAD 0
				{ Opcode :: ILOAD,  { 1 } }, //ILOAD 0
				{ Opcode :: ISUB,   {   } }, //IADD
				{ Opcode :: ISTORE, { 3 } }, //ISTORE 2
				
				{ Opcode :: ILOAD,  { 0 } }, //ILOAD 0
				{ Opcode :: ILOAD,  { 1 } }, //ILOAD 0
				{ Opcode :: IMUL,   {   } }, //IADD
				{ Opcode :: ISTORE, { 4 } }, //ISTORE 4
				
				{ Opcode :: ILOAD,  { 0 } }, //ILOAD 0
				{ Opcode :: ILOAD,  { 1 } }, //ILOAD 0
				{ Opcode :: IDIV,   {   } }, //IADD
				{ Opcode :: ISTORE, { 5 } }  //ISTORE 2
			}
		},
		{
			3, //FUCKTORIAL
			{
				{ Opcode :: ILOAD,        { 0 } }, // načti x   
				{ Opcode :: LDC,       	  { 0 } }, // načti 1  
				{ Opcode :: IF_ICMPNE, 	  { 5 } }, // srovnej 
				{ Opcode :: LDC,          { 0 } }, // vrať 1
				{ Opcode :: IRETURN,      {   } }, // rovnají se? vrať
	/*5*/		{ Opcode :: ILOAD,        { 0 } }, // načti x
				{ Opcode :: LDC,          { 0 } }, // načti 1
				{ Opcode :: ILOAD,        { 0 } }, // načti x
				{ Opcode :: ISUB,         {   } }, // odečti (ve stacku x-1 a x)
				{ Opcode :: INVOKESTATIC, { 3 } }, // zavolej fact (x-1) 
				{ Opcode :: IMUL,         {   } }, // vynásob fact (x-1) a x
				{ Opcode :: IRETURN,      {   } }  // vrať x * fact (x-1)
			}
		}
	};
		
	const map<int,vector<Var>> signatures 
	{
		{ 1, { { 0 }, { 0 } 							} },
		{ 2, { { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 } } },
		{ 3, { { 0 } 									} }
	}; 
	
	vector<Var> vars   
	{ 
		{ 0 }, { 100 },
	};

	vector<Var> vars2   
	{ 
		{ 127 }, { 128 }, { 0 },
		{ 0   }, { 0   }, { 0 }
	};
	
	vector<Var> vars3 
	{
		{ 10 }
	};

	vector<Var> constants
	{
		{ 1 }
	};

	ConstantPool exampleClass ( codes, signatures, constants ); 

	Var * y = new Var ( Type :: INT, { . m_Int = 0} );
	Frame x ( 3, vars3, &exampleClass, &y ); 
	
	cout << x << endl;

	return 0;	
}
