#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cryptopals.h"

#define INPUT "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"
#define KEY "ICE"
#define OUTPUT "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"

int main ( int argc, char **argv )
{
	puts( "START" );

	int i = strlen( INPUT ),
	    k = strlen( KEY );

	char *xor = repeatingKeyXOR( INPUT, KEY, i, k );
	hexDump( xor, i );
	
	char *out = hexBytesToHexString( xor, i );

	if ( strcmp( out, OUTPUT ) == 0 )
		puts( "Created expected output." );
	else
		puts( "Actual output differs from expected output." );

	free( xor );
	free( out );
	xor = NULL;
	out = NULL;

	puts( "END" );
	return 0;
}
