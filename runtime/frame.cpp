#include "frame.h"
#include <iostream>

using namespace std;

Heap Frame :: m_Heap;

Frame :: Frame ( int _class, int method, const vector<Var> & vars, const ClassPool & classPool, Frame * parent )
: 	
	m_Vars 			( vars ),
	
	m_Class         ( _class ),
	m_ClassPool 	( classPool ),
	
	m_Code 			( m_ClassPool . getClass ( _class ) . getCode ( method ) ),
	m_PC 			( m_Code -> begin () ),
	
	m_ReturnAddress ( NULL ),
	m_Parent 		( parent )

{ 
	//cout << * this << endl;
	
	while ( m_PC != m_Code -> end () )
	{	
		auto prev = m_PC;
		Process ( * m_PC );
			
		if ( prev == m_PC )
			++ m_PC;
	}
}

Frame :: Frame ( int _class, int method, const vector<Var> & vars, const ClassPool & classPool, Var ** returnAddress ) 
: 	
	m_Vars 			( vars ),
	
	m_Class         ( _class ),
	m_ClassPool 	( classPool ),
	
	m_Code 			( m_ClassPool . getClass ( _class ) . getCode ( method ) ),
	m_PC 			( m_Code -> begin () ),
	
	m_ReturnAddress ( returnAddress ),
	m_Parent 		( NULL )

{ 
	//cout << * this << endl;
	
	while ( m_PC != m_Code -> end () )
	{	
		auto prev = m_PC;
		Process ( * m_PC );
		
		if ( prev == m_PC )
			++ m_PC;
	}
}
 
void Frame :: Trace ()
{
	cout << "++++++++++" << endl;
	cout << "STACK:    " << endl;
	for ( auto i : m_Stack )
		cout << i << endl;	 
	cout << "VARIABLES:" << endl;
	for ( auto i : m_Vars )
		cout << i << endl;	 
	cout << "----------" << endl;	
}
	
 
void Frame :: Process ( const Instruction & instr )
{
	Var op1, op2, op3, rv;
	switch ( instr . m_Opcode )
	{	
		case Opcode :: BREAKPOINT :
		{
			Trace ();
			m_Heap . Gc ( *this );
			break;
		}
		
		case Opcode :: POP :
		{
			m_Stack . pop_back ();
			break;
		}
		
		case Opcode :: NEW :
		{
			rv = Var ( Type :: REFERENCE, { 0 } );
			
			if ( instr [0] . m_Type != Type :: INT  )
				throw runtime_error ( "Length of array must be int (newarray)." );

			rv . m_Val . m_Reference . m_Class = instr [0] . m_Val . m_Int;	
			m_Heap . Alloc ( rv, m_ClassPool );	
			m_Stack . push_back ( rv );
			break;
		}
		
		case Opcode :: GETFIELD :
		{
			if ( m_Stack . back () . m_Type != Type :: REFERENCE )
				throw runtime_error ( "Not found reference on stack. (getfield)" );
			
			if ( instr [0] . m_Type != Type :: INT )
				throw runtime_error ( "Member index must be int." );

			op1 = m_Stack . back ();
			m_Stack . pop_back ();

			if ( op1 . m_Val . m_Reference . m_Members -> size () <= instr [0] . m_Val . m_Int ) 
				throw runtime_error ( "Member index out of range." );
				
			
			m_Stack . push_back ( (*(op1 . m_Val . m_Reference . m_Members)) [instr [0] . m_Val . m_Int] ); 
			break;
		}
		
		case Opcode :: PUTFIELD :
		{
			if ( m_Stack . back () . m_Type != Type :: REFERENCE )
				throw runtime_error ( "Not found reference on stack. (putfield)" );
			
			if ( instr [0] . m_Type != Type :: INT )
				throw runtime_error ( "Member index must be int." );

			op1 = m_Stack . back ();
			m_Stack . pop_back ();
		
			if ( op1 . m_Val . m_Reference . m_Members -> size () <= instr [0] . m_Val . m_Int ) 
				throw runtime_error ( "Member index out of range." );	
				
			if ( (*(op1 . m_Val . m_Reference . m_Members))[instr [0] . m_Val . m_Int] . m_Type  != m_Stack . back () . m_Type )
				throw runtime_error ( "Invalid type assignment." );	
			
			op2 = m_Stack . back ();
			m_Stack . pop_back ();
			
			(*(op1 . m_Val . m_Reference . m_Members))[instr [0] . m_Val . m_Int] = op2;
		
			break;
		}
		
		
		//newarray
		case Opcode :: NEWARRAY:
		{
			rv = Var ( Type :: ARRAY, { 0 } );
			
			if ( m_Stack . back () . m_Type != Type :: INT )
				throw runtime_error ( "Length of array must be int (newarray)." );
			
			rv . m_Val . m_Array . m_Len  = m_Stack . back () . m_Val . m_Int;
			rv . m_Val . m_Array . m_Type = instr [0] . m_Type;
			m_Stack . pop_back ();
			m_Heap . Alloc ( rv, m_ClassPool );
			m_Stack . push_back ( rv );
			//cout << "[NEW ARRAY]: " << m_Stack . back () << endl;   	
			break;
		}
		
		case Opcode :: ARRAYLENGTH :
		{
			if ( m_Stack . back () . m_Type != Type :: ARRAY )
				throw runtime_error ( "Not found array on stack. (arraylength)" );
			op1 = m_Stack . back ();
			m_Stack . pop_back ();
			
			m_Stack . push_back ( op1 . m_Val . m_Array . m_Len );
			break;
		}
		case Opcode :: IALOAD :
		{
			op1 = m_Stack . back (); //ARRAY
			m_Stack . pop_back ();    
			op2 = m_Stack . back (); //INDEX
			m_Stack . pop_back ();    
			if ( op1 . m_Type != Type :: ARRAY   || op2 . m_Type != Type :: INT 
			  || op1 . m_Val . m_Array . m_Type != Type :: INT )
				   	throw runtime_error ( "Operands of invalid type (iaload)." );
			
			else
			{
				if ( op2 . m_Val . m_Int >= op1 . m_Val . m_Array . m_Len )
					throw runtime_error ( "Index out of range (iaload)." );
				else
				{
				 	m_Stack . push_back ( (*(op1 . m_Val . m_Array . m_Members)) [op2 . m_Val . m_Int] ); 
				//	cout << "MODIFIED FIELD: " << op1 << endl;
					break;
				}
			}
			
			break;
		}
		
		case Opcode :: IASTORE :
		{
			op1 = m_Stack . back (); //ARRAY
			m_Stack . pop_back ();    
			op2 = m_Stack . back (); //INDEX
			m_Stack . pop_back ();    
			op3 = m_Stack . back (); //VALUE
			m_Stack . pop_back ();
			
			if ( op1 . m_Type != Type :: ARRAY   || op2 . m_Type           != Type :: INT 
			  || op3 . m_Type != Type :: INT     || op1 . m_Val . m_Array . m_Type != Type :: INT )
			   	throw runtime_error ( "Operands of invalid type (iastore)." );
			
			else
			{
				if ( op2 . m_Val . m_Int >= op1 . m_Val . m_Array . m_Len )
					throw runtime_error ( "Index out of range (iastore)." );
				else
				{
					(*(op1 . m_Val . m_Array . m_Members)) [op2 . m_Val . m_Int] = op3 . m_Val . m_Int; 
				//	cout << "MODIFIED FIELD: " << op1 << endl;
					break;
				}
			}
		}
		
		case Opcode :: ASTORE:
		{
			//cout << "Vars size:" << m_Vars . size () << endl;
			if ( (unsigned) instr [0] . m_Val . m_Int >= m_Vars . size () )
			{
				cout << instr [0] . m_Val . m_Int << endl;
				throw runtime_error ( "Local variables index out of range (astore)." );
			}
			if ( m_Vars [ instr [0] . m_Val . m_Int ] . m_Type != Type :: REFERENCE
			  && m_Vars [ instr [0] . m_Val . m_Int ] . m_Type != Type :: ARRAY )
			{	
				cout << instr [0] . m_Val . m_Int << endl;	
				throw runtime_error ( "Local variable of invalid type (astore)." );
			}
			m_Vars [ instr [0] . m_Val . m_Int ] = m_Stack . back (); 
			m_Stack . pop_back ();
			
			//cout << "Stored " << m_Vars [ instr [0] . m_Val . m_Int ] << " into local variable " << instr [0] . m_Val . m_Int << " (astore)"<< endl;
			break;
		}
		
		case Opcode :: ALOAD:
		{
			if ( (unsigned) instr [0] . m_Val . m_Int >= m_Vars . size () )
				throw runtime_error ( "Local variables index out of range (aload)." );
			
			if ( m_Vars [ instr [0] . m_Val . m_Int ] . m_Type != Type :: REFERENCE 
			  && m_Vars [ instr [0] . m_Val . m_Int ] . m_Type != Type :: ARRAY )
				throw runtime_error ( "Local variable of invalid type (aload)." );

			m_Stack . push_back ( m_Vars [ instr [0] . m_Val . m_Int ] );
			//cout << "Pushed " << m_Stack . back () << " into stack (aload)" << endl; 
			break;
		}
		
		//istore
		case Opcode :: ISTORE:
		{
			//cout << "Vars size:" << m_Vars . size () << endl;
			if ( (unsigned) instr [0] . m_Val . m_Int >= m_Vars . size () )
				throw runtime_error ( "Local variables index out of range (istore)." );
			
			if ( m_Vars [ instr [0] . m_Val . m_Int ] . m_Type != Type :: INT )
				throw runtime_error ( "Local variable of invalid type (istore)." );

			m_Vars [ instr [0] . m_Val . m_Int ] = m_Stack . back (); 
			
			m_Stack . pop_back ();
			//cout << "Stored " << m_Vars [ instr [0] . m_Val . m_Int ] << " into local variable " << instr [0] . m_Val . m_Int << " (istore)"<< endl;
			break;
		}
		
		//iload		
		case Opcode :: ILOAD:
		{
			if ( (unsigned) instr [0] . m_Val . m_Int >= m_Vars . size () )
				throw runtime_error ( "Local variables index out of range (iload)." );
			
			if ( m_Vars [ instr [0] . m_Val . m_Int ] . m_Type != Type :: INT )
				throw runtime_error ( "Local variable of invalid type (iload)." );

			m_Stack . push_back ( m_Vars [ instr [0] . m_Val . m_Int ] );
			//cout << "Pushed " << m_Stack . back () << " into stack (iload)" << endl; 
			break;
		}
		
		//ldc
		case Opcode :: LDC:
		{
			m_Stack . push_back ( m_ClassPool . getClass ( m_Class ) . getConstant ( instr [0] . m_Val . m_Int ) );
			//cout << "Pushed " << m_Stack . back () << " into stack (ldc)" << endl; 
			break;
		}
		
		//iadd
		case Opcode :: IADD:
		{
			op1 = m_Stack . back ();
			m_Stack . pop_back ();
			op2 = m_Stack . back ();
			m_Stack . pop_back ();

			if ( op1 . m_Type == op2 . m_Type && op2 . m_Type == Type :: INT )
			{
				rv = Var ( Type :: INT, { . m_Int = op1 . m_Val . m_Int + op2 . m_Val. m_Int } );
				m_Stack . push_back ( rv );
				//cout << "Pushed " << m_Stack . back () << " into stack (iadd)" << endl; 
				break;
			}
			else throw runtime_error ( "Bad operand types (iadd)." );
		}

			//isub
		case Opcode :: ISUB:
		{
			op1 = m_Stack . back ();
			m_Stack . pop_back ();
			op2 = m_Stack . back ();
			m_Stack . pop_back ();

			if ( op1 . m_Type == op2 . m_Type && op2 . m_Type == Type :: INT )
			{
				rv = Var ( Type :: INT, { . m_Int = op1 . m_Val . m_Int - op2 . m_Val. m_Int } );
				m_Stack . push_back ( rv );
				//cout << "Pushed " << m_Stack . back () << " into stack (isub)" << endl; 
				break;
			}
			else throw runtime_error ( "Bad operand types (isub)." );
		}

		//imult
		case Opcode :: IMUL:
		{
			op1 = m_Stack . back ();
			m_Stack . pop_back ();
			op2 = m_Stack . back ();
			m_Stack . pop_back ();

			if ( op1 . m_Type == op2 . m_Type && op2 . m_Type == Type :: INT )
			{
				rv = Var ( Type :: INT, { . m_Int = op1 . m_Val . m_Int * op2 . m_Val. m_Int } );
				m_Stack . push_back ( rv );
				//cout << "Pushed " << m_Stack . back () << " into stack (imult)" << endl; 
				break;
			}
			else throw runtime_error ( "Bad operand types (imult)." );
		}

		//idiv
		case Opcode :: IDIV:
		{
			op1 = m_Stack . back ();
			m_Stack . pop_back ();
			op2 = m_Stack . back ();
			m_Stack . pop_back ();

			if ( op1 . m_Type == op2 . m_Type && op2 . m_Type == Type :: INT )
			{
				rv = Var ( Type :: INT, { . m_Int = op1 . m_Val . m_Int / op2 . m_Val. m_Int } );
				m_Stack . push_back ( rv );
				//cout << "Pushed " << m_Stack . back () << " into stack (idiv)" << endl; 
				break;
			}
			else throw runtime_error ( "Bad operand types (idiv)." );
		}
		
		case Opcode :: DUP : 
		{
			op1 = m_Stack . back ();
			m_Stack . push_back ( op1 );
			break;
		}
		
		case Opcode :: SWAP :
		{
			op1 = m_Stack . back ();
			m_Stack . pop_back ();
			op2 = m_Stack . back ();
			m_Stack . pop_back ();
			
			m_Stack . push_back ( op1 );
			m_Stack . push_back ( op2 );
			break;
		}

		case Opcode :: INVOKEVIRTUAL:	
		case Opcode :: INVOKESTATIC :
		{
			vector<Var> signature = m_ClassPool . getClass ( m_Class ) . getSignature ( instr [0] . m_Val . m_Int );
			Var param;
			 
			for ( unsigned i = 0; i < signature . size (); i ++ )
			{
				param = m_Stack . back (); 
				m_Stack . pop_back ();
				if ( param . m_Type != signature . at (i) . m_Type )
					throw runtime_error ( "Bad parameters passed to function. (invokestatic)\n");
				signature . at (i) = param;
			}
			//cout << "Invoked new method." << endl;
		    //StackTrace ();

			
			Var * rv = NULL;
			
			Frame ( m_Class, instr [0] . m_Val . m_Int, signature, m_ClassPool, this );
			
			if ( rv )
				m_Stack . push_back ( *rv );
			
			delete rv;
					
			//cout << "Method ended" << endl;
			break;
		}
		
		case Opcode :: IRETURN :
		{
			if ( m_Stack . back () . m_Type != Type :: INT )
				throw runtime_error ( "Invalid return value." );
			else
			{	
				if ( m_Parent )
					m_Parent -> m_Stack . push_back ( Var ( m_Stack . back () ) );
				else if ( m_ReturnAddress )
					*m_ReturnAddress = new Var ( m_Stack . back() );
				else
					throw runtime_error ( "No parent or return address to push return value to." );
				m_PC   = m_Code -> end ();
			}
			break;
		}
		
		case Opcode :: IF_ICMPNE :
		{
			op1 = m_Stack . back ();
			m_Stack . pop_back ();
			op2 = m_Stack . back ();
			m_Stack . pop_back ();
			
			if ( op1 . m_Type == op2 . m_Type && op2 . m_Type == Type :: INT )
			{
				if ( op1 . m_Val . m_Int != op2 . m_Val . m_Int )
				{
				//	cout << "Jumping at " << instr [0] . m_Val . m_Int << " (fi_icmpne)" << endl;
					m_PC = m_Code -> begin () + instr [0] . m_Val . m_Int;
				}
					//cout << "Not jumping. (fi_icmpne)" << endl;
				break;
			}
			else throw runtime_error ( "Bad operand types (if_icmpne)." );
		}
		
		case Opcode :: IF_ICMPEQ :
		{
			op1 = m_Stack . back ();
			m_Stack . pop_back ();
			op2 = m_Stack . back ();
			m_Stack . pop_back ();
			
			if ( op1 . m_Type == op2 . m_Type && op2 . m_Type == Type :: INT )
			{
				if ( op1 . m_Val . m_Int == op2 . m_Val . m_Int )
				{
				//	cout << "Jumping at " << instr [0] . m_Val . m_Int << " (fi_icmpne)" << endl;
					m_PC = m_Code -> begin () + instr [0] . m_Val . m_Int;
				}
					//cout << "Not jumping. (fi_icmpne)" << endl;
				break;
			}
			else throw runtime_error ( "Bad operand types (if_icmpne)." );
		}
		
		case Opcode :: GOTO :
		{
			if ( instr [0] . m_Type != Type :: INT )
				throw runtime_error ( "Bad operand types (goto)." );
			m_PC = m_Code -> begin () + instr [0] . m_Val . m_Int;
			break;
		}
	
		case Opcode :: COUT :
		{
			cout << m_Stack . back () << endl;
			m_Stack . pop_back ();
			break; 
		}

		case Opcode :: GC :
		{
			m_Heap . Gc ( *this );
			break;
		}

		default:
		{
			cout << hex << instr . m_Opcode << endl;
			throw runtime_error ( "Unknown instruction. Fuck you." );
		}
	}
}

ostream & operator << ( ostream & os, const Frame & x )
{
	os << "FRAME:" << endl;
	for ( auto i = x . m_Vars . begin (); i != x . m_Vars . end (); ++ i )
		os << *i << endl;
	return os << endl;
}
	

