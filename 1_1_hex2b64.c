#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cryptopals.h"

#define INPUT "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
#define OUTPUT "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"

int main ( int argc, char **argv )
{
	puts( "START" );

	hexDump( INPUT, strlen( INPUT ) );

	unsigned char *hex = hexStringToHexBytes( INPUT );

	hexDump( hex, strlen( hex ) );

	char *output = hexBytesToBase64String( hex, strlen( INPUT ) / 2 );
	hexDump( output, strlen( output ) );

	if ( strcmp( output, OUTPUT ) == 0 )
		puts( "Created expected output." );
	else
		puts( "Actual output differs from expected output." );

	free( output );
	output = NULL;

	free( hex );
	hex = NULL;

	puts( "END" );
	return 0;
}
