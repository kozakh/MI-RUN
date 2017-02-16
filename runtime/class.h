#ifndef _CLASS_H_
#define _CLASS_H_

#include <map>
#include <vector>

#include "instruction.h"

using namespace std;

class Class
{
	public:
	Class ( const map<int,vector<Instruction>> & codes, 
		    const map<int,vector<Var>> & signatures,  
		    const vector<Var> & constants,           
			const vector<Var> & members );

	const vector<Instruction> * getCode      ( int i ) const;
	const vector<Var>         & getSignature ( int i ) const;
	Var					  	    getConstant  ( int i ) const;
	const vector<Var>         & getMembers   ( )       const;
		
	private:
	map<int,vector<Instruction>> m_Codes;
	map<int,vector<Var>> 		 m_Signatures;
	vector<Var>					 m_Constants;
	vector<Var>         		 m_Members;
};

class ClassPool 
{
	public:
	ClassPool ( const map<int, Class> & classes ); 
	
	const Class & getClass ( int i ) const; 
	
	private:
	map <int, Class> m_Classes;
};

#endif
