#ifndef __TYPES_H__
#define __TYPES_H__

#include <iostream>
#include <stdint.h>

using namespace std;

struct cp_info;
struct field_info;
struct method_info;
struct attribute_info;


struct ClassFile
{
    uint32_t             magic;
    uint16_t             minor_version;
    uint16_t             major_version;
    uint16_t             constant_pool_count;
    cp_info        	  ** constant_pool;					/*	constant_pool [constant_pool_count - 1]	*/
    uint16_t             access_flags;
    uint16_t             this_class;
    uint16_t             super_class;
    uint16_t             interfaces_count;
    uint16_t           * interfaces;					/*	interfaces [interfaces_count]	*/
    uint16_t             fields_count;
    field_info     	  ** fields;						/*	fields [fields_count]	*/
    uint16_t             methods_count;
    method_info    	  ** methods;						/*	methods [methods_count]	*/
    uint16_t             attributes_count;
    attribute_info 	  ** attributes;					/*	attributes [attributes_count]	*/

    friend ostream 	   & operator << ( ostream & os, const ClassFile & c );
    string 				 toString () const;
};

enum CONSTANT_Type_tag
{
	CONSTANT_Class = 7,
	CONSTANT_Fieldref = 9,
	CONSTANT_Methodref = 10,
	CONSTANT_InterfaceMethodref = 11,
	CONSTANT_String = 8,
	CONSTANT_Integer = 3,
	CONSTANT_Float = 4,
	CONSTANT_Long = 5,
	CONSTANT_Double = 6,
	CONSTANT_NameAndType = 12,
	CONSTANT_Utf8 = 1,
	CONSTANT_MethodHandle = 15,
	CONSTANT_MethodType = 16,
	CONSTANT_InvokeDynamic = 18
};

struct CONSTANT_Type_info
{
};

struct cp_info
{
	CONSTANT_Type_tag 		tag;
	CONSTANT_Type_info 	  *	info;
};

struct ATTRIBUTE_Type
{
};

struct attribute_info
{
    uint16_t 				attribute_name_index;
    uint32_t 				attribute_length;
    ATTRIBUTE_Type 		  * attribute_type;
};

struct field_info
{
    uint16_t             	access_flags;
    uint16_t             	name_index;
    uint16_t             	descriptor_index;
    uint16_t             	attributes_count;
    attribute_info  	 ** attributes;					//	[attributes_count]
};

struct method_info
{
    uint16_t         	    access_flags;
    uint16_t         	    name_index;
    uint16_t         	    descriptor_index;
    uint16_t         	    attributes_count;
    attribute_info 	 	 ** attributes;					/*	attributes [attributes_count]	*/
};

struct CONSTANT_Class_info : CONSTANT_Type_info
{
	uint16_t 	name_index;
};

struct CONSTANT_Fieldref_info : CONSTANT_Type_info
{
	uint16_t 	class_index;
	uint16_t 	name_and_type_index;
};

struct CONSTANT_Methodref_info : CONSTANT_Type_info
{
	uint16_t 	class_index;
	uint16_t 	name_and_type_index;
};

struct CONSTANT_InterfaceMethodref_info : CONSTANT_Type_info
{
	uint16_t 	class_index;
	uint16_t 	name_and_type_index;
};

struct CONSTANT_String_info : CONSTANT_Type_info
{
	uint16_t 	string_index;
};

struct CONSTANT_Integer_info : CONSTANT_Type_info
{
	uint32_t 	bytes;
};

struct CONSTANT_Float_info : CONSTANT_Type_info
{
	uint32_t 	bytes;
};

struct CONSTANT_Long_info : CONSTANT_Type_info
{
	uint32_t 	high_bytes;
	uint32_t 	low_bytes;
};

struct CONSTANT_Double_info : CONSTANT_Type_info
{
	uint32_t 	high_bytes;
	uint32_t 	low_bytes;
};

struct CONSTANT_NameAndType_info : CONSTANT_Type_info
{
	uint16_t 	name_index;
	uint16_t 	descriptor_index;
};

struct CONSTANT_Utf8_info : CONSTANT_Type_info
{
	uint16_t 	length;
	uint8_t   * bytes;
};

struct CONSTANT_MethodHandle_info : CONSTANT_Type_info
{
	uint8_t  	reference_kind;
	uint16_t 	reference_index;
};

struct CONSTANT_MethodType_info : CONSTANT_Type_info
{
	uint16_t 	descriptor_index;
};

struct CONSTANT_InvokeDynamic_info : CONSTANT_Type_info
{
	uint16_t 	bootstrap_method_attr_index;
	uint16_t 	name_and_type_index;
};
/*	NOT IMPLEMENTED
struct exception_table
{
	uint16_t 	start_pc;
	uint16_t 	end_pc;
	uint16_t 	handler_pc;
	uint16_t 	catch_type;
};
*/
struct ConstantValue_attribute : ATTRIBUTE_Type
{
	uint16_t				constantvalue_index;
};

struct Code_attribute : ATTRIBUTE_Type
{
    uint16_t 				max_stack;
    uint16_t 				max_locals;
    uint32_t 				code_length;
    uint8_t   			  * code;						//	[code_length]
/*  uint16_t 				exception_table_length;											NOT IMPLEMENTED		*/
/*	exception_table 	  * exception_table; 			//	[exception_table_length]		NOT IMPLEMENTED		*/
    uint16_t 				attributes_count;
    attribute_info 		 ** attributes;					//	[attributes_count]
};
/*	NOT IMPLEMENTED
struct StackMapTable_attribute : ATTRIBUTE_Type
{
};

struct Exceptions_attribute : ATTRIBUTE_Type
{
};

struct BootstrapMethods_attribute : ATTRIBUTE_Type
{
};
*/
#endif /*__TYPES_H__*/