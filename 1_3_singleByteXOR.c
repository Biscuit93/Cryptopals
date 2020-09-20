#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cryptopals.h"

#define INPUT "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"

int main ( int argc, char **argv )
{
	unsigned char *input = hexStringToHexBytes( INPUT );
	unsigned int length = strlen( INPUT ) / 2;
	unsigned int score = 0;
	unsigned int bestScore = 0;
	unsigned char key = '\0';
	unsigned char **xors = NULL;

	xors = malloc( sizeof( unsigned char * ) * 0x100 );
	for ( int i = 0; i < 0x100; i++ )
	{
		xors[ i ] = singleByteXOR( input, i, length );
		score = plaintextScore( xors[ i ] );
		if ( score > bestScore ) 
		{
			bestScore = score;
			key = i;
		}
	}

	hexDump( input, length );
	hexDump( xors[ key ], length );
	printf( "Key = 0x%02X\n", key );

	for ( int i = 0; i < 0x100; i++ )
	{
		free( xors[ i ] );
		xors[ i ] = NULL;
	}
	free( xors );
	xors = NULL;

	free( input );
	input = NULL;

	return 0;
}
