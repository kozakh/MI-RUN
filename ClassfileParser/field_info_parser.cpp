#include "field_info_parser.h"
#include "common.h"
#include "attribute_info_parser.h"

field_info * parse_field ( ifstream & ifs, ClassFile ** c )
{
	field_info * ret = new field_info;
	unsigned char tmp [4];

	ifs . read ( (char *) tmp, 2 );
	ret -> access_flags = cstrToUint16_t ( tmp );
	ifs . read ( (char *) tmp, 2 );
	ret -> name_index = cstrToUint16_t ( tmp );
	ifs . read ( (char *) tmp, 2 );
	ret -> descriptor_index = cstrToUint16_t ( tmp );
	ifs . read ( (char *) tmp, 2 );
	ret -> attributes_count = cstrToUint16_t ( tmp );
	cout << "The field has " << ret -> attributes_count << " attributes." << endl;
	ret -> attributes = new attribute_info* [ret -> attributes_count];
	for ( uint16_t i = 0; i < ret -> attributes_count; i++ )
		ret -> attributes [i] = parse_attribute ( ifs, c );

	return ret;
}