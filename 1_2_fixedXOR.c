#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cryptopals.h"

#define INPUT1 "1c0111001f010100061a024b53535009181c"
#define INPUT2 "686974207468652062756c6c277320657965"
#define OUTPUT "746865206b696420646f6e277420706c6179"

int main ( int argc, char **argv )
{
	puts( "START" );

	unsigned int length = strlen( INPUT2 ) / 2;

	char *in1 = hexStringToHexBytes( INPUT1 );
	char *in2 = hexStringToHexBytes( INPUT2 );
	char *xor = fixedLengthXOR( in1, in2, length );
	char *out = hexBytesToHexString( xor, length );

	hexDump( in1, length );
	hexDump( in2, length );
	hexDump( xor, length );
	
	if ( strcmp( out, OUTPUT ) == 0 )
		puts( "Created expected output." );
	else
		puts( "Actual output differs from expected output." );

	free( in1 );
	free( in2 );
	free( xor );
	free( out );

	in1 = NULL;
	in2 = NULL;
	xor = NULL;
	out = NULL;

	puts( "END" );
	return 0;
}
