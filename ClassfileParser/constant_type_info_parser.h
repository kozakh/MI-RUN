#ifndef __CONSTANT_TYPE_INFO_PARSER_H__
#define __CONSTANT_TYPE_INFO_PARSER_H__

#include "constant_type_info.h"

cp_info * 							parse_constant_type ( ifstream & ifs );
CONSTANT_Class_info * 				parse_Class ( ifstream & ifs );
CONSTANT_Fieldref_info * 			parse_Fieldref ( ifstream & ifs );
CONSTANT_Methodref_info * 			parse_Methodref ( ifstream & ifs );
CONSTANT_InterfaceMethodref_info * 	parse_InterfaceMethodref ( ifstream & ifs );
CONSTANT_String_info * 				parse_String ( ifstream & ifs );
CONSTANT_Integer_info * 			parse_Integer ( ifstream & ifs );
CONSTANT_Float_info * 				parse_Float ( ifstream & ifs );
CONSTANT_Long_info * 				parse_Long ( ifstream & ifs );
CONSTANT_Double_info * 				parse_Double ( ifstream & ifs );
CONSTANT_NameAndType_info * 		parse_NameAndType ( ifstream & ifs );
CONSTANT_Utf8_info * 				parse_Utf8 ( ifstream & ifs );
CONSTANT_MethodHandle_info * 		parse_MethodHandle ( ifstream & ifs );
CONSTANT_MethodType_info * 			parse_MethodType ( ifstream & ifs );
CONSTANT_InvokeDynamic_info * 		parse_InvokeDynamic ( ifstream & ifs );

#endif /*__CONSTANT_TYPE_INFO_PARSER_H__*/