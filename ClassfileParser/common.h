#ifndef __COMMON_H__
#define __COMMON_H__

#include <cstdint>

unsigned int cstrToUInt ( const unsigned char * cstr, unsigned int length );
uint16_t cstrToUint16_t ( const unsigned char * cstr, unsigned int length = 2 );
uint32_t cstrToUint32_t ( const unsigned char * cstr, unsigned int length = 4 );


#endif /* __COMMON_H__ */