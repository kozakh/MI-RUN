#include "constant_type_info_parser.h"
#include "types.h"
#include "common.h"
#include <stdexcept>

cp_info * parse_constant_type ( ifstream & ifs )
{
	unsigned char tag = ifs . get ();
	//ifs . get ( (char *) tag, 1 );

	CONSTANT_Type_info * info;

	cout << "tag: " << (int)tag << endl;

	switch ( tag )
	{
		case CONSTANT_Class 				: info = parse_Class ( ifs ); break;
		case CONSTANT_Fieldref 				: info = parse_Fieldref ( ifs ); break;
		case CONSTANT_Methodref 			: info = parse_Methodref ( ifs ); break;
		case CONSTANT_InterfaceMethodref 	: info = parse_InterfaceMethodref ( ifs ); break;
		case CONSTANT_String 				: info = parse_String ( ifs ); break;
		case CONSTANT_Integer 				: info = parse_Integer ( ifs ); break;
		case CONSTANT_Float 				: info = parse_Float ( ifs ); break;
		case CONSTANT_Long 					: info = parse_Long ( ifs ); break;
		case CONSTANT_Double 				: info = parse_Double ( ifs ); break;
		case CONSTANT_NameAndType 			: info = parse_NameAndType ( ifs ); break;
		case CONSTANT_Utf8 					: info = parse_Utf8 ( ifs ); break;
		case CONSTANT_MethodHandle 			: info = parse_MethodHandle ( ifs ); break;
		case CONSTANT_MethodType 			: info = parse_MethodType ( ifs ); break;
		case CONSTANT_InvokeDynamic 		: info = parse_InvokeDynamic ( ifs ); break;
		default 							: throw runtime_error ( "Invalid constant type tag: " + to_string ( tag ) );
	}

	cp_info * ret = new cp_info;
	ret -> tag = (CONSTANT_Type_tag) tag;
	ret -> info = info;

	return ret;
}

CONSTANT_Class_info * parse_Class ( ifstream & ifs )
{
	CONSTANT_Class_info * ret = new CONSTANT_Class_info;
	unsigned char tmp [2];
	ifs . read ( (char *) tmp, 2 );
	ret -> name_index = cstrToUint16_t ( tmp );

	return ret;
}

CONSTANT_Fieldref_info * parse_Fieldref ( ifstream & ifs )
{
	CONSTANT_Fieldref_info * ret = new CONSTANT_Fieldref_info;
	unsigned char tmp [2];
	ifs . read ( (char *) tmp, 2 );
	ret -> class_index = cstrToUint16_t ( tmp );
	ifs . read ( (char *) tmp, 2 );
	ret -> name_and_type_index = cstrToUint16_t ( tmp );

	return ret;
}

CONSTANT_Methodref_info * parse_Methodref ( ifstream & ifs )
{
	CONSTANT_Methodref_info * ret = new CONSTANT_Methodref_info;
	unsigned char tmp [2];
	ifs . read ( (char *) tmp, 2 );
	ret -> class_index = cstrToUint16_t ( tmp );
	ifs . read ( (char *) tmp, 2 );
	ret -> name_and_type_index = cstrToUint16_t ( tmp );

	return ret;
}

CONSTANT_InterfaceMethodref_info * parse_InterfaceMethodref ( ifstream & ifs )
{
	CONSTANT_InterfaceMethodref_info * ret = new CONSTANT_InterfaceMethodref_info;
	unsigned char tmp [2];
	ifs . read ( (char *) tmp, 2 );
	ret -> class_index = cstrToUint16_t ( tmp );
	ifs . read ( (char *) tmp, 2 );
	ret -> name_and_type_index = cstrToUint16_t ( tmp );

	return ret;
}

CONSTANT_String_info * parse_String ( ifstream & ifs )
{
	CONSTANT_String_info * ret = new CONSTANT_String_info;
	unsigned char tmp [2];
	ifs . read ( (char *) tmp, 2 );
	ret -> string_index = cstrToUint16_t ( tmp );

	return ret;
}

CONSTANT_Integer_info * parse_Integer ( ifstream & ifs )
{
	CONSTANT_Integer_info * ret = new CONSTANT_Integer_info;
	unsigned char tmp [4];
	ifs . read ( (char *) tmp, 4 );
	ret -> bytes = cstrToUint32_t ( tmp );

	return ret;
}

CONSTANT_Float_info * parse_Float ( ifstream & ifs )
{
	CONSTANT_Float_info * ret = new CONSTANT_Float_info;
	unsigned char tmp [4];
	ifs . read ( (char *) tmp, 4 );
	ret -> bytes = cstrToUint32_t ( tmp );

	return ret;
}

CONSTANT_Long_info * parse_Long ( ifstream & ifs )
{
	CONSTANT_Long_info * ret = new CONSTANT_Long_info;
	unsigned char tmp [4];
	ifs . read ( (char *) tmp, 4 );
	ret -> high_bytes = cstrToUint32_t ( tmp );			//	TODO Check endianness
	ifs . read ( (char *) tmp, 4 );
	ret -> low_bytes = 	cstrToUint32_t ( tmp );

	return ret;
}

CONSTANT_Double_info * parse_Double ( ifstream & ifs )
{
	CONSTANT_Double_info * ret = new CONSTANT_Double_info;
	unsigned char tmp [4];
	ifs . read ( (char *) tmp, 4 );
	ret -> high_bytes = cstrToUint32_t ( tmp );			//	TODO Check endianness
	ifs . read ( (char *) tmp, 4 );
	ret -> low_bytes = cstrToUint32_t ( tmp );

	return ret;
}

CONSTANT_NameAndType_info * parse_NameAndType ( ifstream & ifs )
{
	CONSTANT_NameAndType_info * ret = new CONSTANT_NameAndType_info;
	unsigned char tmp [2];
	ifs . read ( (char *) tmp, 2 );
	ret -> name_index = cstrToUint16_t ( tmp );
	ifs . read ( (char *) tmp, 2 );
	ret -> descriptor_index = cstrToUint16_t ( tmp );

	return ret;
}

CONSTANT_Utf8_info * parse_Utf8 ( ifstream & ifs )
{
	CONSTANT_Utf8_info * ret = new CONSTANT_Utf8_info;
	unsigned char tmp [2];
	ifs . read ( (char *) tmp, 2 );
	ret -> length = cstrToUint16_t ( tmp );
	ret -> bytes = new uint8_t [ret -> length];
	for ( uint16_t i = 0; i < ret -> length; i++ )
	{
		ifs . read ( (char *) tmp, 1 );
		cout << (char) tmp [0];
		ret -> bytes [i] = tmp [0];
	}
	cout << endl;

	return ret;
}

CONSTANT_MethodHandle_info * parse_MethodHandle ( ifstream & ifs )
{
	CONSTANT_MethodHandle_info * ret = new CONSTANT_MethodHandle_info;
	unsigned char tmp [2];
	ifs . read ( (char *) tmp, 1 );
	ret -> reference_kind = tmp [0];
	ifs . read ( (char *) tmp, 2 );
	ret -> reference_index = cstrToUint16_t ( tmp );

	return ret;
}

CONSTANT_MethodType_info * parse_MethodType ( ifstream & ifs )
{
	CONSTANT_MethodType_info * ret = new CONSTANT_MethodType_info;
	unsigned char tmp [2];
	ifs . read ( (char *) tmp, 2 );
	ret -> descriptor_index = cstrToUint16_t ( tmp );

	return ret;
}

CONSTANT_InvokeDynamic_info * parse_InvokeDynamic ( ifstream & ifs )
{
	CONSTANT_InvokeDynamic_info * ret = new CONSTANT_InvokeDynamic_info;
	unsigned char tmp [2];
	ifs . read ( (char *) tmp, 2 );
	ret -> bootstrap_method_attr_index = cstrToUint16_t ( tmp );
	ifs . read ( (char *) tmp, 2 );
	ret -> name_and_type_index = cstrToUint16_t ( tmp );

	return ret;
}
