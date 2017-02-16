#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <iostream>
#include <deque>
#include <vector>
#include <map>

#include "variable.h"

using namespace std;

struct Op
{
	static constexpr int 	 INT = 0;
	static constexpr float FLOAT = 0.0;
	static constexpr char   CHAR = '0';
	//static constexpr Var X { Type :: ARRAY, { . m_Int = 0 } };
};

enum Opcode
{
	LDC    = 0x12, 
	POP    = 0x57,
	
	ISTORE = 0x36,
	ILOAD  = 0x15,
	
	IADD   = 0x60,
	ISUB   = 0x64, 
	IMUL   = 0x68,
	IDIV   = 0x6C,	
	DUP    = 0x59,
	SWAP   = 0x5F,
	
	INVOKESTATIC  = 0xB8,	
	INVOKEVIRTUAL = 0xB6,
	
//	if_icmpeq
	IF_ICMPEQ = 0x9F,
	IF_ICMPNE = 0xA0,
	GOTO      = 0xA7,
//  if_icmpgt = 0xA3
//  if_icmpge = 0xA2
//  if_icmple = 0xA4
//  if_icmplt = 0xA1

	IRETURN = 0xAC, 
	
	NEWARRAY = 0xBC,
	ARRAYLENGTH = 0xBE,
	NEW      = 0xBB,
	
	ASTORE 	 = 0x3A,
	ALOAD    = 0x19,
	
	CASTORE  = 0x34,
	CALOAD   = 0x55,
	
	IASTORE    = 0x4F,
	IALOAD     = 0x2E,
	
	BREAKPOINT = 0xCA,

	GETFIELD = 0xB4,
	PUTFIELD = 0xB5,

	COUT    = 0xCB,
	GC 		= 0xCD
};

struct Instruction
{
	const static map<int, int> OPERANDS_NR;

	const static vector<Var> DUMMY;

	Instruction ( int m_Opcode, const vector<Var> & operands = DUMMY );
	
	Var operator [] ( int index ) const; 
	istream & Load ( istream & is );

	int m_Opcode;
	int m_OperandsNr;
	vector<Var> m_Operands;
};

#endif
