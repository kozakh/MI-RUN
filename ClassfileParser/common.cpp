#include "common.h"

unsigned int cstrToUInt ( const unsigned char * cstr, unsigned int length )
{
	unsigned int ret = 0;
	for ( unsigned int i = 0; i < length; i++ )
		ret = (ret << 8) + (unsigned int ) cstr [i];

	return ret;
}

uint16_t cstrToUint16_t ( const unsigned char * cstr, unsigned int length = 2 )
{
	uint16_t ret = 0;
	for ( unsigned int i = 0; i < length; i++ )
		ret = (ret << 8) + (uint16_t) cstr [i];

	return ret;
}

uint32_t cstrToUint32_t ( const unsigned char * cstr, unsigned int length = 4 )
{
	uint32_t ret = 0;
	for ( unsigned int i = 0; i < length; i++ )
		ret = (ret << 8) + (unsigned int ) cstr [i];

	return ret;
}