#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <iostream>
#include <deque>
#include <vector>
#include <map>

#include "variable.h"

using namespace std;

enum Opcode
{
	LDC    = 0x12, 
	
	ISTORE = 0x36,
	ILOAD  = 0x15,
	
	IADD   = 0x60,
	ISUB   = 0x64, 
	IMUL   = 0x68,
	IDIV   = 0x6c,	
	
	INVOKESTATIC = 0xBA,	
	
//	if_icmpeq
	IF_ICMPNE = 0x9F,
//  if_icmpgt = 0xA3
//  if_icmpge = 0xA2
//  if_icmple = 0xA4
//  if_icmplt = 0xA1

	IRETURN = 0xAC, 
	
	NEWARRAY = 0xBC,
	ASTORE 	 = 0x3A,
	ALOAD    = 0x19
};

struct Instruction
{
	const static map<int, int> OPERANDS_NR;

	Instruction ( int m_Opcode, const vector<Var> & operands );
	
	Var operator [] ( int index ); 
	istream & Load ( istream & is );

	int m_Opcode;
	int m_OperandsNr;
	vector<Var> m_Operands;
};

#endif
