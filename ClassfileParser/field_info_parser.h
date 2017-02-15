#ifndef __FIELD_INFO_PARSER_H__
#define __FIELD_INFO_PARSER_H__

#include <fstream>
#include "types.h"

field_info * parse_field ( ifstream & ifs, ClassFile ** c );


#endif /* __FIELD_INFO_PARSER_H__ */