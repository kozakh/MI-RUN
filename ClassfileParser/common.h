#ifndef __COMMON_H__
#define __COMMON_H__

#include <cstdint>
#include <string>
#include <stdexcept>
#include "types.h"

using namespace std;

unsigned int cstrToUInt ( const unsigned char * cstr, unsigned int length );
uint16_t cstrToUint16_t ( const unsigned char * cstr, unsigned int length = 2 );
uint32_t cstrToUint32_t ( const unsigned char * cstr, unsigned int length = 4 );
string utf8ToString 	( CONSTANT_Utf8_info * utf );

void instructionsToText ( Code_attribute * code );

#endif /* __COMMON_H__ */