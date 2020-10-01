#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cryptopals.h"

#define FILENAME "6.txt"

// UNFINISHED

int main ( int argc, char **argv )
{
	puts( "START" );

	char test1[ 15 ] = "this is a test",
	     test2[ 15 ] = "wokka wokka!!!";

	printf( "Hamming distance: %d\n", hammingDistance( test1, test2, 15 ) );
	
	puts( "END" );
	return 0;
}
