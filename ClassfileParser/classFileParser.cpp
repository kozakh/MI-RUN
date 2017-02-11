#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "constant_type_info.h"
#include "constant_type_info_parser.h"
#include "common.h"

using namespace std;

struct attribute_info
{
    uint16_t 			 attribute_name_index;
    uint32_t 			 attribute_length;
    uint8_t  		   * info;							/*	info [attribute_length]	*/
};

struct field_info
{
    uint16_t             access_flags;
    uint16_t             name_index;
    uint16_t             descriptor_index;
    uint16_t             attributes_count;
    attribute_info 	   * attributes;					/*	attributes [attributes_count]	*/
};

struct method_info
{
    uint16_t             access_flags;
    uint16_t             name_index;
    uint16_t             descriptor_index;
    uint16_t             attributes_count;
    attribute_info 	   * attributes;					/*	attributes [attributes_count]	*/
};

struct ClassFile
{
    uint32_t             magic;
    uint16_t             minor_version;
    uint16_t             major_version;
    uint16_t             constant_pool_count;
    cp_info        	   * constant_pool;					/*	constant_pool [constant_pool_count - 1]	*/
    uint16_t             access_flags;
    uint16_t             this_class;
    uint16_t             super_class;
    uint16_t             interfaces_count;
    uint16_t           * interfaces;					/*	interfaces [interfaces_count]	*/
    uint16_t             fields_count;
    field_info     	   * fields;						/*	fields [fields_count]	*/
    uint16_t             methods_count;
    method_info    	   * methods;						/*	methods [methods_count]	*/
    uint16_t             attributes_count;
    attribute_info 	   * attributes;					/*	attributes [attributes_count]	*/

    friend ostream 	   & operator << ( ostream & os, const ClassFile & c );
    string 				 toString () const;
};

ostream & operator << ( ostream & os, const ClassFile & c )
{
	os << c . magic << " " << c . minor_version << " " << c . major_version << " ";
	os << c . constant_pool_count;
	return os;
}

string ClassFile::toString () const
{
	string ret = "";
	ret += to_string ( magic ) + " " + to_string ( major_version ) + " " + to_string ( minor_version );

	return ret;
}

void parseConstantPool ( ifstream & ifs, ClassFile ** c )
{
	unsigned char * tmp = new unsigned char [5];
	unsigned char c;

	for ( int i = 0; i < (*c) -> constant_pool_count - 1; i++ )
	{
		ifs . get ( (char) c );
		(*c) -> constant_pool [i] . tag = c;
		while 
	}

	delete[] tmp;
}

void classFileParser ( ifstream & ifs, ClassFile ** c )
{
	if ( !(*c) )
		*c = new ClassFile;

	unsigned char * tmp = new unsigned char [5];
	tmp[4] = '\0';
	ifs . get ( (char *) tmp, 5 );

	(*c) -> magic = cstrToUInt ( tmp, 4 );

	ifs . get ( (char *) tmp, 3 );
	(*c) -> minor_version = cstrToUInt ( tmp, 2 );

	ifs . get ( (char *) tmp, 3 );
	(*c) -> major_version = cstrToUInt ( tmp, 2 );

	ifs . get ( (char *) tmp, 3 );
	(*c) -> constant_pool_count = cstrToUInt ( tmp, 2 );

	(*c) -> constant_pool = new cp_info [constant_pool_count - 1];
	

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

	classFileParser ( ifs, &c );

	cout << hex << dec << (*c) << endl;

	ifs . close ();
	delete c;

	return 0;
}
