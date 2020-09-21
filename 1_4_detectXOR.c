#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cryptopals.h"

#define FILENAME "4.txt"

int main ( int argc, char **argv )
{
	unsigned int lines, 
		     byteLength,
		     best,
		     score,
		     *allScores;
	unsigned char *allKeys;
	char **input = loadFileToStrings( FILENAME, &lines ),
	     **hex   = malloc( sizeof( unsigned char * ) * lines ),
	     *output = NULL,
	     *temp   = NULL;

	byteLength = strlen( input[ 0 ] ) / 2;

	for ( int i = 0; i < lines; i++ )
		hex[ i ] = hexStringToHexBytes( input[ i ] );

	allScores = malloc( sizeof( unsigned int ) * lines );
	allKeys = malloc( sizeof( unsigned char ) * lines );

	for ( int i = 0; i < lines; i++ )
	{
		score = 0;
		allScores[ i ] = 0;
		
		for ( int j = 0; j < 0x100; j++ )
		{
			temp = singleByteXOR( hex[ i ], j, byteLength );
			score = plaintextScore( temp );
			if ( score > allScores[ i ] )
			{
				allScores[ i ] = score;
				allKeys[ i ] = j;
			}

			free( temp );
			temp = NULL;
		}
	}

	best = 0;
	score = 0;
	for ( int i = 0; i < lines; i++ )
		if ( allScores[ i ] > score )
		{
			score = allScores[ i ];
			best = i;
		}

	printf( "Best guess: %d, key: 0x%02X\n", best, allKeys[ best ] );
	output = singleByteXOR( hex[ best ], allKeys[ best ], byteLength );
	hexDump( hex[ best ], byteLength );
	hexDump( output, byteLength );

	for ( int i = 0; i < lines; i++ )
	{
		free( input[ i ] );
		input[ i ] = NULL;
		free( hex[ i ] );
		hex[ i ] = NULL;
	}
	free( input );
	input = NULL;
	free( hex );
	hex = NULL;
	free( output );
	output = NULL;


	return 0;
}
