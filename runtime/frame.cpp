#include "frame.h"
#include <iostream>

using namespace std;

Frame :: Frame ( int i, const vector<Var> & vars, ConstantPool * constantPool, Frame * parent )
: 	
	m_Vars 			( vars ),
	m_ConstantPool 	( constantPool ),
	m_Parent 		( parent ),
	m_ReturnAddress ( NULL ),
	m_Code 			( m_ConstantPool -> getCode ( i )  ),
	m_PC 			( m_Code -> begin () )
{ 
	cout << * this << endl;
	
	while ( m_PC != m_Code -> end () )
	{	
		auto prev = m_PC;
		Process ( * m_PC );
		
		StackTrace ();
		
		if ( prev == m_PC )
			++ m_PC;
	}
}

Frame :: Frame ( int i, const vector<Var> & vars, ConstantPool * constantPool, Var ** returnAddress ) 
: 	
	m_Vars 			( vars ),
	m_ConstantPool 	( constantPool ),
	m_Parent 		( NULL ),
	m_ReturnAddress ( returnAddress ),
	m_Code 			( m_ConstantPool -> getCode ( i )  ),
	m_PC 			( m_Code -> begin () )
{ 
	cout << * this << endl;
	
	while ( m_PC != m_Code -> end () )
	{	
		auto prev = m_PC;
		Process ( * m_PC );
		
		StackTrace ();
		
		if ( prev == m_PC )
			++ m_PC;
	}
}
 
void Frame :: StackTrace ()
{
	cout << "Trace: ";
	for ( auto i : m_Stack )
		cout << i . m_Val . m_Int << " "; 
	cout << endl;
}
 
 
void Frame :: Process ( Instruction & instr )
{
	Var op1, op2, rv;
	switch ( instr . m_Opcode )
	{	
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
			cout << "Stored " << m_Vars [ instr [0] . m_Val . m_Int ] << " into local variable " << instr [0] . m_Val . m_Int << " (istore)"<< endl;
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
			cout << "Pushed " << m_Stack . back () << " into stack (iload)" << endl; 
			break;
		}
		
		//ldc
		case Opcode :: LDC:
		{
			m_Stack . push_back ( m_ConstantPool -> getConstant ( instr [0] . m_Val . m_Int ) );
			cout << "Pushed " << m_Stack . back () << " into stack (ldc)" << endl; 
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
				cout << "Pushed " << m_Stack . back () << " into stack (iadd)" << endl; 
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
				cout << "Pushed " << m_Stack . back () << " into stack (isub)" << endl; 
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
				cout << "Pushed " << m_Stack . back () << " into stack (imult)" << endl; 
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
				cout << "Pushed " << m_Stack . back () << " into stack (idiv)" << endl; 
				break;
			}
			else throw runtime_error ( "Bad operand types (idiv)." );
		}

		case Opcode :: INVOKESTATIC :
		{
			vector<Var> signature = m_ConstantPool -> getSignature ( instr [0] . m_Val . m_Int );
			Var param;
			 
			for ( unsigned i = 0; i < signature . size (); i ++ )
			{
				param = m_Stack . back (); 
				m_Stack . pop_back ();
				if ( param . m_Type != signature . at (i) . m_Type )
					throw runtime_error ( "Bad parameters passed to function. (invokestatic)\n");
				signature . at (i) = param;
			}
			cout << "Invoked new method." << endl;
		    StackTrace ();

			
			Var * rv = NULL;
			
			Frame ( instr [0] . m_Val . m_Int, signature, m_ConstantPool, this );
			
			if ( rv )
				m_Stack . push_back ( *rv );
			
			delete rv;
					
			cout << "Method ended" << endl;
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
					cout << "Jumping at " << instr [0] . m_Val . m_Int << " (fi_icmpne)" << endl;
					m_PC = m_Code -> begin () + instr [0] . m_Val . m_Int;
				}
				else 
					cout << "Not jumping. (fi_icmpne)" << endl;
				break;
			}
			else throw runtime_error ( "Bad operand types (if_icmpne)." );
		}
		default:
		{
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
	

