#include "common.h"

unsigned int cstrToUInt ( const unsigned char * cstr, unsigned int length )
{
	unsigned int ret = 0;
	for ( unsigned int i = 0; i < length; i++ )
		ret = (ret << 8) + (unsigned int ) cstr [i];

	return ret;
}

uint16_t cstrToUint16_t ( const unsigned char * cstr, unsigned int length )
{
	uint16_t ret = 0;
	for ( unsigned int i = 0; i < length; i++ )
		ret = (ret << 8) + (uint16_t) cstr [i];

	return ret;
}

uint32_t cstrToUint32_t ( const unsigned char * cstr, unsigned int length )
{
	uint32_t ret = 0;
	for ( unsigned int i = 0; i < length; i++ )
		ret = (ret << 8) + (unsigned int ) cstr [i];

	return ret;
}

string utf8ToString ( CONSTANT_Utf8_info * utf )
{
	if ( !utf )
		throw runtime_error ( "The utf parameter is NULL." );
	char * retChar = new char [ utf -> length + 1 ];
	retChar [ utf -> length ] = '\0';

	for ( uint16_t i = 0; i < utf -> length; i++ )
	{
		if ( utf -> bytes && utf -> bytes [i] )
			retChar [i] = utf -> bytes [i];
		else
			throw runtime_error ( "The utf -> bytes parameter is NULL." );
	}

	string ret ( retChar );
	delete[] retChar;

	return ret;
}

void instructionsToText ( Code_attribute * code )
{
	for ( uint32_t i = 0; i < code -> code_length; i++ )
	{
		switch ( (int)code -> code [i] )
		{
			case 9:			cout <<"lconst_0" << endl; break;
			case 10:		cout <<"lconst_1" << endl; break;
			case 50:		cout <<"aaload" << endl; break;
			case 83:		cout <<"aastore" << endl; break;
			case 1:			cout <<"aconst_null" << endl; break;
			case 25:		cout <<"aload" << endl; break;
			case 42:		cout <<"aload_0" << endl; break;
			case 43:		cout <<"aload_1" << endl; break;
			case 44:		cout <<"aload_2" << endl; break;
			case 45:		cout <<"aload_3" << endl; break;
			case 176:		cout <<"areturn" << endl; break;
			case 190:		cout <<"arraylength" << endl; break;
			case 58:		cout <<"astore" << endl; break;
			case 75:		cout <<"astore_0" << endl; break;
			case 76:		cout <<"astore_1" << endl; break;
			case 77:		cout <<"astore_2" << endl; break;
			case 78:		cout <<"astore_3" << endl; break;
			case 191:		cout <<"athrow" << endl; break;
			case 51:		cout <<"baload" << endl; break;
			case 84:		cout <<"bastore" << endl; break;
			case 16:		cout <<"bipush" << endl; break;
			case 52:		cout <<"caload" << endl; break;
			case 85:		cout <<"castore" << endl; break;
			case 192:		cout <<"checkcast" << endl; break;
			case 144:		cout <<"d2f" << endl; break;
			case 142:		cout <<"d2i" << endl; break;
			case 143:		cout <<"d2l" << endl; break;
			case 99:		cout <<"dadd" << endl; break;
			case 49:		cout <<"daload" << endl; break;
			case 82:		cout <<"dastore" << endl; break;
			case 152:		cout <<"dcmpg" << endl; break;
			case 151:		cout <<"dcmpl" << endl; break;
			case 14:		cout <<"dconst_0" << endl; break;
			case 15:		cout <<"dconst_1" << endl; break;
			case 111:		cout <<"ddiv" << endl; break;
			case 24:		cout <<"dload" << endl; break;
			case 38:		cout <<"dload_0" << endl; break;
			case 39:		cout <<"dload_1" << endl; break;
			case 40:		cout <<"dload_2" << endl; break;
			case 41:		cout <<"dload_3" << endl; break;
			case 107:		cout <<"dmul" << endl; break;
			case 119:		cout <<"dneg" << endl; break;
			case 115:		cout <<"drem" << endl; break;
			case 175:		cout <<"dreturn" << endl; break;
			case 57:		cout <<"dstore" << endl; break;
			case 71:		cout <<"dstore_0" << endl; break;
			case 72:		cout <<"dstore_1" << endl; break;
			case 73:		cout <<"dstore_2" << endl; break;
			case 74:		cout <<"dstore_3" << endl; break;
			case 103:		cout <<"dsub" << endl; break;
			case 89:		cout <<"dup" << endl; break;
			case 90:		cout <<"dup_x1" << endl; break;
			case 91:		cout <<"dup_x2" << endl; break;
			case 92:		cout <<"dup2" << endl; break;
			case 93:		cout <<"dup2_x1" << endl; break;
			case 94:		cout <<"dup2_x2" << endl; break;
			case 141:		cout <<"f2d" << endl; break;
			case 139:		cout <<"f2i" << endl; break;
			case 140:		cout <<"f2l" << endl; break;
			case 98:		cout <<"fadd" << endl; break;
			case 48:		cout <<"faload" << endl; break;
			case 81:		cout <<"fastore" << endl; break;
			case 150:		cout <<"fcmpg" << endl; break;
			case 149:		cout <<"fcmpl" << endl; break;
			case 11:		cout <<"fconst_0" << endl; break;
			case 12:		cout <<"fconst_1" << endl; break;
			case 13:		cout <<"fconst_2" << endl; break;
			case 110:		cout <<"fdiv" << endl; break;
			case 23:		cout <<"fload" << endl; break;
			case 34:		cout <<"fload_0" << endl; break;
			case 35:		cout <<"fload_1" << endl; break;
			case 36:		cout <<"fload_2" << endl; break;
			case 37:		cout <<"fload_3" << endl; break;
			case 106:		cout <<"fmul" << endl; break;
			case 118:		cout <<"fneg" << endl; break;
			case 114:		cout <<"frem" << endl; break;
			case 174:		cout <<"freturn" << endl; break;
			case 56:		cout <<"fstore" << endl; break;
			case 67:		cout <<"fstore_0" << endl; break;
			case 68:		cout <<"fstore_1" << endl; break;
			case 69:		cout <<"fstore_2" << endl; break;
			case 70:		cout <<"fstore_3" << endl; break;
			case 102:		cout <<"fsub" << endl; break;
			case 180:		cout <<"getfield" << endl; break;
			case 178:		cout <<"getstatic" << endl; break;
			case 167:		cout <<"goto" << endl; break;
			case 200:		cout <<"goto_w" << endl; break;
			case 145:		cout <<"i2b" << endl; break;
			case 146:		cout <<"i2c" << endl; break;
			case 135:		cout <<"i2d" << endl; break;
			case 134:		cout <<"i2f" << endl; break;
			case 133:		cout <<"i2l" << endl; break;
			case 147:		cout <<"i2s" << endl; break;
			case 96:		cout <<"iadd" << endl; break;
			case 46:		cout <<"iaload" << endl; break;
			case 126:		cout <<"iand" << endl; break;
			case 79:		cout <<"iastore" << endl; break;
			case 2:			cout <<"iconst_m1" << endl; break;
			case 3:			cout <<"iconst_0" << endl; break;
			case 4:			cout <<"iconst_1" << endl; break;
			case 5:			cout <<"iconst_2" << endl; break;
			case 6:			cout <<"iconst_3" << endl; break;
			case 7:			cout <<"iconst_4" << endl; break;
			case 8:			cout <<"iconst_5" << endl; break;
			case 108:		cout <<"idiv" << endl; break;
			case 165:		cout <<"if_acmpeq" << endl; break;
			case 166:		cout <<"if_acmpne" << endl; break;
			case 159:		cout <<"if_icmpeq" << endl; break;
			case 160:		cout <<"if_icmpne" << endl; break;
			case 161:		cout <<"if_icmplt" << endl; break;
			case 162:		cout <<"if_icmpge" << endl; break;
			case 163:		cout <<"if_icmpgt" << endl; break;
			case 164:		cout <<"if_icmple" << endl; break;
			case 153:		cout <<"ifeq" << endl; break;
			case 154:		cout <<"ifne" << endl; break;
			case 155:		cout <<"iflt" << endl; break;
			case 156:		cout <<"ifge" << endl; break;
			case 157:		cout <<"ifgt" << endl; break;
			case 158:		cout <<"ifle" << endl; break;
			case 199:		cout <<"ifnonnull" << endl; break;
			case 198:		cout <<"ifnull" << endl; break;
			case 132:		cout <<"iinc" << endl; break;
			case 21:		cout <<"iload" << endl; break;
			case 26:		cout <<"iload_0" << endl; break;
			case 27:		cout <<"iload_1" << endl; break;
			case 28:		cout <<"iload_2" << endl; break;
			case 29:		cout <<"iload_3" << endl; break;
			case 104:		cout <<"imul" << endl; break;
			case 116:		cout <<"ineg" << endl; break;
			case 193:		cout <<"instanceof" << endl; break;
			case 186:		cout <<"invokedynamic" << endl; break;
			case 185:		cout <<"invokeinterface" << endl; break;
			case 183:		cout <<"invokespecial" << endl; break;
			case 184:		cout <<"invokestatic" << endl; break;
			case 182:		cout <<"invokevirtual" << endl; break;
			case 128:		cout <<"ior" << endl; break;
			case 112:		cout <<"irem" << endl; break;
			case 172:		cout <<"ireturn" << endl; break;
			case 120:		cout <<"ishl" << endl; break;
			case 122:		cout <<"ishr" << endl; break;
			case 54:		cout <<"istore" << endl; break;
			case 59:		cout <<"istore_0" << endl; break;
			case 60:		cout <<"istore_1" << endl; break;
			case 61:		cout <<"istore_2" << endl; break;
			case 62:		cout <<"istore_3" << endl; break;
			case 100:		cout <<"isub" << endl; break;
			case 124:		cout <<"iushr" << endl; break;
			case 130:		cout <<"ixor" << endl; break;
			case 168:		cout <<"jsr" << endl; break;
			case 201:		cout <<"jsr_w" << endl; break;
			case 138:		cout <<"l2d" << endl; break;
			case 137:		cout <<"l2f" << endl; break;
			case 136:		cout <<"l2i" << endl; break;
			case 97:		cout <<"ladd" << endl; break;
			case 47:		cout <<"laload" << endl; break;
			case 127:		cout <<"land" << endl; break;
			case 80:		cout <<"lastore" << endl; break;
			case 148:		cout <<"lcmp" << endl; break;
			case 18:		cout <<"ldc" << endl; break;
			case 19:		cout <<"ldc_w" << endl; break;
			case 20:		cout <<"ldc2_w" << endl; break;
			case 109:		cout <<"ldiv" << endl; break;
			case 22:		cout <<"lload" << endl; break;
			case 30:		cout <<"lload_0" << endl; break;
			case 31:		cout <<"lload_1" << endl; break;
			case 32:		cout <<"lload_2" << endl; break;
			case 33:		cout <<"lload_3" << endl; break;
			case 105:		cout <<"lmul" << endl; break;
			case 117:		cout <<"lneg" << endl; break;
			case 171:		cout <<"lookupswitch" << endl; break;
			case 129:		cout <<"lor" << endl; break;
			case 113:		cout <<"lrem" << endl; break;
			case 173:		cout <<"lreturn" << endl; break;
			case 121:		cout <<"lshl" << endl; break;
			case 123:		cout <<"lshr" << endl; break;
			case 55:		cout <<"lstore" << endl; break;
			case 63:		cout <<"lstore_0" << endl; break;
			case 64:		cout <<"lstore_1" << endl; break;
			case 65:		cout <<"lstore_2" << endl; break;
			case 66:		cout <<"lstore_3" << endl; break;
			case 101:		cout <<"lsub" << endl; break;
			case 125:		cout <<"lushr" << endl; break;
			case 131:		cout <<"lxor" << endl; break;
			case 194:		cout <<"monitorenter" << endl; break;
			case 195:		cout <<"monitorexit" << endl; break;
			case 197:		cout <<"multianewarray" << endl; break;
			case 187:		cout <<"new" << endl; break;
			case 188:		cout <<"newarray" << endl; break;
			case 0:			cout <<"nop" << endl; break;
			case 87:		cout <<"pop" << endl; break;
			case 88:		cout <<"pop2" << endl; break;
			case 181:		cout <<"putfield" << endl; break;
			case 179:		cout <<"putstatic" << endl; break;
			case 169:		cout <<"ret" << endl; break;
			case 177:		cout <<"return" << endl; break;
			case 53:		cout <<"saload" << endl; break;
			case 86:		cout <<"sastore" << endl; break;
			case 17:		cout <<"sipush" << endl; break;
			case 95:		cout <<"swap" << endl; break;
			case 170:		cout <<"tableswitch" << endl; break;
			case 196:		cout <<"wide" << endl; break;
			default:		cout << "Maybe operand?" << endl; break;
		}
	}
}			