#include <vector>
#include <deque>

#include "frame.h"
#include "variable.h"
#include "class.h"
#include "instruction.h"
#include "heap.h"


using namespace std;

const ClassPool classPool  
(
	{
		//CLASSES
		{
			1, //CALCULATOR
			{
				//METHODS
				{
					{
						1, //FUCKTORIAL
						{
							{ ILOAD,        { 0 } }, // načti x   
							{ LDC,       	{ 0 } }, // načti 1  
							{ IF_ICMPNE, 	{ 5 } }, // srovnej 
							{ LDC,          { 0 } }, // vrať 1
							{ IRETURN,            }, // rovnají se? vrať
							{ ILOAD,        { 0 } }, // načti x
							{ LDC,          { 0 } }, // načti 1
							{ ILOAD,        { 0 } }, // načti x
							{ ISUB,               }, // odečti (ve stacku x-1 a x)
							{ INVOKESTATIC, { 1 } }, // zavolej fact (x-1) 
							{ IMUL,               }, // vynásob fact (x-1) a x
							{ IRETURN             }  // vrať x * fact (x-1)
						}
					},
					{
						2,	
						{
							{ LDC,      { 2 } },
							{ NEW,      { 1 } },
							{ POP,            },
							{ NEW,      { 1 } },
							{ COUT,           },
							//{ POP,            },
							{ NEW,      { 1 } },
							{ ASTORE,   { 1 } },
							{ ALOAD,    { 1 } },
							{ PUTFIELD, { 0 } },
						}
					},
					{
						3,
						{
							{ LDC,        { 3 } },	// načtu 0
							{ DUP				},	//	0 0
							{ DUP				},	//	0 0 0
							{ ALOAD, 	  { 0 } },	//	A 0 0 0
							{ ARRAYLENGTH 		},	//	<L> 0 0 0
							{ IF_ICMPEQ,  { 25 }},	// 0 0
							{ ALOAD, 	  { 0 } },	// A 0 0
							{ IALOAD			},	// <I> 0
							{ ISTORE,	  { 1 } },	//	0		----	break	--
							{ LDC, 		  { 0 } },	//	1 0
							{ IADD 				},	//	1
							{ DUP				},	//	1 1
							{ DUP				},	//	1 1 1
							{ DUP				},	//	1 1 1 1
							{ ALOAD, 	  { 0 } },	//	R 1 1 1 1
							{ ARRAYLENGTH 		},	//	<L> 1 1 1 1
							{ IF_ICMPEQ,  { 25 }},	//  1 1 1
							{ ALOAD, 	  { 0 } },	// A 1 1 1
							{ IALOAD			},	// <I> 1 1
							{ ILOAD, 	  { 1 } },	// <I> <I> 1 1
							{ IADD				},	//	<I> 1 1
							{ SWAP				},	//	1 <I> 1
							{ ALOAD,	  { 0 } },	//	A 1 <I> 1
							{ IASTORE			},	//	1
							{ GOTO,       { 1 } },
							{ BREAKPOINT        },
						}
					}
				},
				//SIGNATURES
				{ 
					{ 1, { { Op::INT } } },
					{ 2, { { Op::INT } , Var ( Type :: REFERENCE, { 0 } ) } }, 
					//{ 3, { { Var ( Type :: ARRAY, { 0 } ) } } },
					{ 3, { { Var ( Type :: ARRAY, { 0 } ) }, { Op::INT } } }
				},
				// CONSTANTS
				{ 
					{ 1 }, { 5 }, { 9 }, { 0 }
				},
				// MEMBERS
				{ 
					{ 3 }, { Op::INT }	
				}
			}
		},
		{
			2, // NAME
			{
				// METHODS
				{
					{
						1, //NEW
						{
							{ ALOAD, { 0 } },
							{ ALOAD, { 1 } },
							{ PUTFIELD, { 1 } },
							{ ALOAD, { 0 } },
							{ ALOAD, { 2 } },
							{ PUTFIELD, { 2 } },
							{ GETFIELD, { 0 } },
							{ GETFIELD, { 1 } },
							{ BREAKPOINT }	
						}	
					},
					//OUTPUT
					{
						2,
						{
						
						}
					}
				},
				//SIGNATURES
				{
					{
						1, //INIT
						{
							Var ( Type :: REFERENCE,  { 1 } ), //THIS
							Var ( Type :: ARRAY, { 0 } ), 	  //NAME
							Var ( Type :: ARRAY, { 0 } )  	  //SURNAME	 
						}	
					},	
					{
						2,
						{}
					}
				},
				//CONSTANTS
				{
					
				},
				//MEMBERS
				{
					Var ( Type :: ARRAY,   {0} ), 
					Var ( Type :: ARRAY,   {0} )
				}
			}
		}
	}
);	

int main ()
{	
	/*
	const vector<Var> args = { 5, Var ( Type :: REFERENCE, { 0 } ) };
	const vector<Var> args2 = { Var ( Type :: REFERENCE, { 0 } ) };
	const vector<Var> args3 = { Var ( Type :: REFERENCE, { 0 } ) };
	args3 [0] . m_Val . m_Array . m_Len = 10;
	args3 [0] . m_Val . m_Array . m_Members = new vector <Var> ( args3 [0] . m_Array . m_Len );
	for ( int i = 0; i < args3 [0] . m_Array . m_Len; i++ )
		args3 [0] . m_Val . m_Array . m_Members [i] = i;
	*/
	/*
	Var 			  * rv =  new Var ( INT );
	
	Frame x ( 1, 4, args3, classPool, &rv );

	cout << "RV: " << rv -> m_Val . m_Int << endl;
	*/
	/*
	Var string1 ( Type :: ARRAY, { 1 } );
	string1 . m_Val . m_Array . m_Members = new vector<Var> { 7, 3, 3, 7 };
	string1 . m_Val . m_Array . m_Type = Type :: INT;
	string1 . m_Val . m_Array . m_Len = 4;

	vector<Var> { string1, string1 };
*/
	Var array1 ( Type :: ARRAY, { 0 } );
	array1 . m_Val . m_Array . m_Members = new vector<Var> { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	array1 . m_Val . m_Array . m_Type = Type :: INT;
	array1 . m_Val . m_Array . m_Len = 20;

	Var local ( Type :: INT, { 0 } );
	vector<Var> psAttr { array1, local };

	Var * rv =  new Var ( INT );
	
	Frame x ( 1, 3, psAttr, classPool, &rv );

	cout << "RV: " << rv -> m_Val . m_Int << endl;
	

	return 0;	
}
