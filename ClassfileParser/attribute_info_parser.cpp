#include "attribute_info_parser.h"
#include "common.h"

#include <iostream>
#include <fstream>


attribute_info * parse_attribute ( ifstream & ifs, ClassFile ** c )
{
	attribute_info * ret = new attribute_info;
	unsigned char tmp [4];

	cout << "Attribute position: " << ifs . tellg () << endl;

	ifs . read ( (char *) tmp, 2 );
	ret -> attribute_name_index = cstrToUint16_t ( tmp );
	ifs . read ( (char *) tmp, 4 );
	ret -> attribute_length = cstrToUint32_t ( tmp );

	cout << "Attribute name index: " << ret -> attribute_name_index << endl;
	string name = utf8ToString ( (CONSTANT_Utf8_info *)((*c) -> constant_pool [ret -> attribute_name_index - 1] -> info) );

	if ( !name . compare ( "ConstantValue" ) )
		ret -> attribute_type = parse_ConstantValue ( ifs, c );
	else if ( !name . compare ( "Code" ) )
		ret -> attribute_type = parse_Code ( ifs, c );
	else
	{
		cerr << "\tAttribute " << name << " not implemented, skipping " << ret -> attribute_length << " bytes." << endl;
		for ( uint32_t i = 0; i < ret -> attribute_length; i++ )
			ifs . read ( (char *) tmp, 1 );
	}

	return ret;
}

ConstantValue_attribute	* parse_ConstantValue ( ifstream & ifs, ClassFile ** c )
{
	cout << "Parsing ConstantValue attribute." << endl;
	ConstantValue_attribute * ret = new ConstantValue_attribute;
	unsigned char tmp [2];
	ifs . read ( (char *) tmp, 2 );
	ret -> constantvalue_index = cstrToUint16_t ( tmp );

	return ret;
}

Code_attribute	* parse_Code ( ifstream & ifs, ClassFile ** c )
{
	cout << "Parsing Code attribute." << endl;
	Code_attribute * ret = new Code_attribute;
	unsigned char tmp [4];
	ifs . read ( (char *) tmp, 2 );
	ret -> max_stack = cstrToUint16_t ( tmp );
	ifs . read ( (char *) tmp, 2 );
	ret -> max_locals = cstrToUint16_t ( tmp );
	ifs . read ( (char *) tmp, 4 );
	ret -> code_length = cstrToUint32_t ( tmp );
	ret -> code = new uint8_t [ ret -> code_length ];

	cout << endl << endl << "Instructions:" << endl;
	for ( uint32_t i = 0; i < ret -> code_length; i++ )
	{
		ifs . read ( (char *) tmp, 1 );
		ret -> code [i] = tmp [0];
	}
	
	ifs . read ( (char *) tmp, 2 );
	uint16_t exception_table_length = cstrToUint16_t ( tmp );

	for ( uint16_t i = 0; i < exception_table_length; i++ )
		ifs . read ( (char *) tmp, 1 );

	ifs . read ( (char *) tmp, 2 );
	ret -> attributes_count = cstrToUint16_t ( tmp );

	ret -> attributes = new attribute_info *[ret -> attributes_count];
	
	for ( uint16_t i = 0; i < ret -> attributes_count; i++ )
		ret -> attributes [i] = parse_attribute ( ifs, c );

	instructionsToText ( ret );

	return ret;
}

/*

struct Code_attribute : ATTRIBUTE_Type
{
    uint16_t 				max_stack;
    uint16_t 				max_locals;
    uint32_t 				code_length;
    uint8_t   			  * code;						//	[code_length]
    uint16_t 				exception_table_length;
    exception_table 	  * exception_table; 			//	[exception_table_length]
    uint16_t 				attributes_count;
    attribute_info 		  * attributes;					//	[attributes_count]
};

*/