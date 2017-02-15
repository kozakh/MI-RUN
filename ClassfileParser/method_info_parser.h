#ifndef __METHOD_INFO_PARSER_H__
#define __METHOD_INFO_PARSER_H__

#include <fstream>
#include "types.h"

method_info * parse_method ( ifstream & ifs, ClassFile ** c );


#endif /* __METHOD_INFO_PARSER_H__ */