#ifndef __CONSTANT_TYPE_INFO_H__
#define __CONSTANT_TYPE_INFO_H__
#include <stdint.h>

struct cp_info
{
	CONSTANT_Type_tag 		tag;
	CONSTANT_Type_info *	info;
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

#endif /*__CONSTANT_TYPE_INFO_H__*/