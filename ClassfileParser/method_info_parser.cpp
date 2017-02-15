#include "method_info_parser.h"
#include "common.h"
#include "attribute_info_parser.h"

method_info * parse_method ( ifstream & ifs, ClassFile ** c )
{
	method_info * ret = new method_info;
	unsigned char tmp [2];

	ifs . read ( (char *) tmp, 2 );
	ret -> access_flags = cstrToUint16_t ( tmp );
	ifs . read ( (char *) tmp, 2 );
	ret -> name_index = cstrToUint16_t ( tmp );
	ifs . read ( (char *) tmp, 2 );
	ret -> descriptor_index = cstrToUint16_t ( tmp );
	ifs . read ( (char *) tmp, 2 );
	ret -> attributes_count = cstrToUint16_t ( tmp );
	cout << "The method has " << ret -> attributes_count << " attributes." << endl;
	ret -> attributes = new attribute_info* [ret -> attributes_count];
	for ( uint16_t i = 0; i < ret -> attributes_count; i++ )
		ret -> attributes [i] = parse_attribute ( ifs, c );

	return ret;
}
