#ifndef _CONSTANTPOOL_H_
#define _CONSTANTPOOL_H_

#include <map>
#include <vector>

#include "instruction.h"

using namespace std;

class ConstantPool
{
	public:
	ConstantPool ( const map<int,vector<Instruction>> & codes, const map<int,vector<Var>> & signatures, const vector<Var> & constants, const vector<Var> & members );
	ConstantPool ( const map<int,vector<Instruction>> & codes, const map<int,vector<Var>> & signatures, const vector<Var> & constants );

	vector<Instruction> * getCode      ( int i );
	vector<Var>         & getSignature ( int i );
	Var					  getConstant  ( int i );
	Var 				  getMember    ( int i );
	vector<Var> 		& getMembers   ();
		
	private:
	map<int,vector<Instruction>> m_Codes;
	map<int,vector<Var>> 		 m_Signatures;
	vector<Var>					 m_Constants;
	vector<Var>				 	 m_Members;
};

#endif
