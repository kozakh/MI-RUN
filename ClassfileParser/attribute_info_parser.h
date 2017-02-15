#ifndef __ATTRIBUTE_INFO_PARSER_H__
#define __ATTRIBUTE_INFO_PARSER_H__

#include <fstream>
#include "types.h"

using namespace std;

attribute_info 				* parse_attribute ( ifstream & ifs, ClassFile ** c );
ConstantValue_attribute		* parse_ConstantValue ( ifstream & ifs, ClassFile ** c );
Code_attribute				* parse_Code ( ifstream & ifs, ClassFile ** c );


#endif /* __ATTRIBUTE_INFO_PARSER_H__ */