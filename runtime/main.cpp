#include <vector>
#include <deque>

#include "frame.h"
#include "variable.h"
#include "constantpool.h"
#include "instruction.h"
#include "heap.h"


using namespace std;

struct Operand
{
	static constexpr int 	 INT = 0;
	static constexpr float FLOAT = 0.0;
	static constexpr char   CHAR = '0';
	
};

int main ()
{	

	const map<int,vector<Instruction>> codes = 
	{
		{
			1, //FOR CYCLUS
			{
				{ ILOAD,     { 0 } }, //ILOAD 0
				{ LDC,       { 0 } }, //ILOAD 2 
				{ IADD,      {   } }, //IADD
				{ ISTORE,    { 0 } }, //ISTORE 2
				
				{ ILOAD,     { 0 } }, //ILOAD 0
				{ ILOAD,     { 1 } }, //ILOAD 1 
				{ IF_ICMPNE, { 0 } } //IF_CMPEG 0
			}
		},
		{
			2, //CALCULATOR
			{
				{ ILOAD,  { 0 } }, //ILOAD 0
				{ ILOAD,  { 1 } }, //ILOAD 0
				{ IADD,   {   } }, //IADD
				{ ISTORE, { 2 } }, //ISTORE 2
				
				{ ILOAD,  { 0 } }, //ILOAD 0
				{ ILOAD,  { 1 } }, //ILOAD 0
				{ ISUB,   {   } }, //IADD
				{ ISTORE, { 3 } }, //ISTORE 2
				
				{ ILOAD,  { 0 } }, //ILOAD 0
				{ ILOAD,  { 1 } }, //ILOAD 0
				{ IMUL,   {   } }, //IADD
				{ ISTORE, { 4 } }, //ISTORE 4
				
				{ ILOAD,  { 0 } }, //ILOAD 0
				{ ILOAD,  { 1 } }, //ILOAD 0
				{ IDIV,   {   } }, //IADD
				{ ISTORE, { 5 } }  //ISTORE 2
			}
		},
		{
			3, //FUCKTORIAL
			{
				{ ILOAD,        { 0 } }, // načti x   
				{ LDC,       	{ 0 } }, // načti 1  
				{ IF_ICMPNE, 	{ 5 } }, // srovnej 
				{ LDC,          { 0 } }, // vrať 1
				{ IRETURN,      {   } }, // rovnají se? vrať
	/*5*/		{ ILOAD,        { 0 } }, // načti x
				{ LDC,          { 0 } }, // načti 1
				{ ILOAD,        { 0 } }, // načti x
				{ ISUB,         {   } }, // odečti (ve stacku x-1 a x)
				{ INVOKESTATIC, { 3 } }, // zavolej fact (x-1) 
				{ IMUL,         {   } }, // vynásob fact (x-1) a x
				{ IRETURN,      {   } }  // vrať x * fact (x-1)
			}
			
		},
		{
			4,
			{
				{ ILOAD,    { 0 } }, //na stack velikost pole
				{ NEWARRAY, { INT } }  //nové pole
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
	Frame x ( 4, vars3, &exampleClass, &y ); 
	
	cout << x << endl;

	return 0;	
}
