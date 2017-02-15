#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "constant_type_info_parser.h"
#include "field_info_parser.h"
#include "method_info_parser.h"
#include "attribute_info_parser.h"
#include "common.h"
#include "types.h"

using namespace std;

ostream & operator << ( ostream & os, const ClassFile & c )
{
	os << c . magic << " " << c . minor_version << " " << c . major_version << " ";
	os << c . constant_pool_count;
	return os;
}

string ClassFile::toString () const
{
	string ret = "";
	ret += to_string ( magic ) + " " + to_string ( major_version ) + " " + to_string ( minor_version ) + " " + to_string ( constant_pool_count );

	return ret;
}

void parseConstantPool ( ifstream & ifs, ClassFile ** c )
{
	(*c) -> constant_pool = new cp_info* [(*c) -> constant_pool_count - 1];

	for ( uint16_t i = 0; i < (*c) -> constant_pool_count - 1; i++ )
	{
		cout << "#" << (int) i << "\t";
		(*c) -> constant_pool [i] = parse_constant_type ( ifs );
	}
}

void parseInterfaces ( ifstream & ifs, ClassFile ** c )
{
	cout << "Parsing " << (*c) -> interfaces_count << " interfaces." << endl;
	unsigned char tmp [2];
	(*c) -> interfaces = new uint16_t [(*c) -> interfaces_count];

	for ( uint16_t i = 0; i < (*c) -> interfaces_count; i++ )
	{
		ifs . read ( (char *) tmp, 2 );
		(*c) -> interfaces [i] = cstrToUint16_t ( tmp );
	}
}

void parseFields ( ifstream & ifs, ClassFile ** c )
{
	cout << "Parsing " << (*c) -> fields_count << " fields." << endl;
	(*c) -> fields = new field_info* [(*c) -> fields_count];

	for ( uint16_t i = 0; i < (*c) -> fields_count; i++ )
		(*c) -> fields [i] = parse_field ( ifs, c );
}

void parseMethods ( ifstream & ifs, ClassFile ** c )
{
	cout << "Parsing " << (*c) -> methods_count << " methods." << endl;
	(*c) -> methods = new method_info* [(*c) -> methods_count];

	for ( uint16_t i = 0; i < (*c) -> methods_count; i++ )
		(*c) -> methods [i] = parse_method ( ifs, c );
}

void parseAttributes ( ifstream & ifs, ClassFile ** c )
{
	cout << "Parsing " << (*c) -> attributes_count << " attributes." << endl;
	//(*c) -> attributes = new attribute_info* [(*c) -> attributes_count];
}

void classFileParser ( ifstream & ifs, ClassFile ** c )
{
	if ( !(*c) )
		*c = new ClassFile;

	unsigned char * tmp = new unsigned char [5];
	tmp[4] = '\0';
	ifs . read ( (char *) tmp, 4 );

	(*c) -> magic = cstrToUInt ( tmp, 4 );

	ifs . read ( (char *) tmp, 2 );
	(*c) -> minor_version = cstrToUInt ( tmp, 2 );

	ifs . read ( (char *) tmp, 2 );
	(*c) -> major_version = cstrToUInt ( tmp, 2 );

	ifs . read ( (char *) tmp, 2 );
	(*c) -> constant_pool_count = cstrToUInt ( tmp, 2 );

	cout << hex << dec << (**c) << endl;

	parseConstantPool ( ifs, c );

	ifs . read ( (char *) tmp, 2 );
	(*c) -> access_flags = cstrToUint16_t ( tmp );
	
	ifs . read ( (char *) tmp, 2 );
	(*c) -> this_class = cstrToUint16_t ( tmp );

	ifs . read ( (char *) tmp, 2 );
	(*c) -> super_class = cstrToUint16_t ( tmp );

	ifs . read ( (char *) tmp, 2 );
	(*c) -> interfaces_count = cstrToUint16_t ( tmp );

	parseInterfaces ( ifs, c );

	ifs . read ( (char *) tmp, 2 );
	(*c) -> fields_count = cstrToUint16_t ( tmp );

	parseFields ( ifs, c );

	ifs . read ( (char *) tmp, 2 );
	(*c) -> methods_count = cstrToUint16_t ( tmp );

	parseMethods ( ifs, c );

	ifs . read ( (char *) tmp, 2 );
	(*c) -> attributes_count = cstrToUint16_t ( tmp );

	parseAttributes ( ifs , c );

	delete[] tmp;
}

int main ( int argc, char * argv [] )
{
	ClassFile	* c = NULL;
	ifstream 	  ifs;

	if ( argc < 2 )
	{
		cerr << "Too few arguments!" << endl;
		cerr << "Usage: " << argv[0] << " <class file>" << endl;
		return 1;
	}

	ifs . open ( argv[1], ifstream::in | ifstream::binary );

	try {
		classFileParser ( ifs, &c );
	}
	catch ( runtime_error e )
	{
		cerr << e . what () << endl;
		return 1;
	}

	

	cout << hex << dec << (*c) << endl;

	ifs . close ();
	delete c;

	return 0;
}
