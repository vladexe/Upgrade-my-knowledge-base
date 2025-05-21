#include <stdio.h>

// char                  1 BYTE 
// unsigned char         1 BYTE
// short                 2 BYTE
// unsigned short        2 BYTE
// int                   4 BYTE on 32/64bit -> 2 BYTE on 16bit
// unsigned int          4 BYTE on 32/64bit -> 2 BYTE on 16bit
// long                  4 BYTE on 32bit -> 8 BYTE on 64bit
// unsigned long         4 BYTE on 32bit -> 8 BYTE on 64bit
// long long             8 BYTE on 32/64bit (specificator for 32bit system 
//                       to align size on both arch to 8 BYTE
// float                 4 BYTE
// double                8 BYTE

int main(void){

	// from -128 to 127
	// why?
	// -128 into binary ->
	// 1. module |-128| = 128 = 1000 0000
	// 2. invert                0111 1111
	// 3. +1                    1000 0000
	//
	// -1 into binary ->
	// 1. module |-1| = 1 = 0000 0001
	// 2. invert            1111 1110
	// 3. +1                1111 1111 
	//
	// First bit in signed variable is 'sign bit'
	//
	//  126, 127, -128, -127, -126 ... -1
	char c;

	// from  0 to 256
	// There is no sign so all bits are values
	// 0000 0001 = 1
	// 1111 0000 = 16 + 32 + 64 + 128 = 240
	unsigned char uc;
	

	// from -32768 to 32767
	// the same logic first bit is 'sign'
	// 32674, 32765, 32766, 32767, -32768, -32767 ... -1
	short s;
	// no 'sign' bit
	// from 0 to 65535
	// 1 BYTE      2 BYTE
	// 1111 1111, 1111 1111 = 65535 
	unsigned short us;


	// all the same but for 4 BYTES
	// from -2 147 483 648 to 2 147 483 647
	int i;
	// without 'sign' 
	// from 0 to 4 294 967 295
	//
	// 1111 1111, 1111 1111, 1111 1111, 1111 1111 = MAX VALUE 
	unsigned int ui;

	// 8/4 BYTE, 1 bit is sign
	long l;
	// 8/4 BYTE no 'sign' bit
	unsigned long ul;

	// 8 BYTE on both 32 and 64bit
	long long ll;


	// 1 bit - sign. 8 bits exponent. 23 bits mantis 
	float f;
	// 1 bit - sign. 11 bits exponent. 52 bits mantis
	double d;

	// Bits: 0 10000010 10100000000000000000000
    //		 ↑    ↑               ↑
    //		sign  exponent       mantissa
	// Implicit normalization  for storing value
	//
	// 6.5 to bin
	// 
	// 6 into binary
	//
	// 6/2 = 0
	// 3/2 = 1
	// 1/2 = 1
	// 
	// Binary 110 = 6
	//
	// 0.5 into binary
	//
	// 0.5 x 2 = 1
	//
	// 6.5 = 110.1 => implicit normalization 1.101  2^2
	// that allows to us skip this 1 bit of information
	// 
	// bias for float is 127 => 111 1111
	// 110.1 => 1.101 => 2bits
	// 127 + 2 => 129 => 1000 0001
	//
	// Sign bit:     0  
	// Exponent:     10000001  
	// Mantissa:     10100000000000000000000

	return 0;
}
