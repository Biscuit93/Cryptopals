#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cryptopals.h"

unsigned char byteToBase64Char ( unsigned char byte )
{
	if ( byte >= 0 && byte < 26 )
		return 'A' + ( byte - 0 );
	if ( byte >= 26 && byte < 52 )
		return 'a' + ( byte - 26 );
	if ( byte >= 52 && byte < 62 )
		return '0' + ( byte - 52 );
	if ( byte == 62 )
		return '+';
	if ( byte == 63 )
		return '/';

	puts( "Attempted to convert invalid byte into base64." );
	return -1;
}

unsigned char hexCharsToHexValue ( unsigned char *byte )
{
	unsigned char result = 0;

	int i = 0;

	do 
	{
		result *= 0x10;

		if ( *( byte + i ) >= '0' && *( byte + i ) <= '9' )
			result += *( byte + i ) - '0';
		else if ( *( byte + i ) >= 'A' && *( byte + i ) <= 'F' )
			result += *( byte + i ) - 'A' + 0xA;
		else if ( *( byte + i ) >= 'a' && *( byte + i ) <= 'f' )
			result += *( byte + i ) - 'a' + 0xA;
		else
			puts( "Attempted to convert invalid character into hex." );
	}
	while ( i++ < 1 );

	return result;
}

unsigned char *hexStringToHexBytes ( char *str )
{
	if ( !str )
		return NULL;

	unsigned char *result = NULL;
	
	int in_length  = strlen( str );
	int out_length = in_length / 2;

	result = malloc( sizeof( unsigned char ) * out_length );

	unsigned char *ptr1 = str,
		      *ptr2 = result;

	while ( *ptr1 )
	{
		*( ptr2++ ) = hexCharsToHexValue( ptr1 );
		ptr1 += 2;
	}

	return result;
}

char hexValueToHexChar ( unsigned char hex, int upper )
{
	if ( hex >= 0x0 && hex <= 0x9 )
		return '0' + hex;
	if ( hex >= 0xA && hex <= 0xF )
	{
		if ( upper )
			return 'A' + ( hex - 0xA );
		else
			return 'a' + ( hex - 0xA );
	}

	puts( "Attempted to convert an invalid value into a hex character." );
	return -1;
}

char *hexBytesToHexString ( unsigned char *bytes, unsigned int len )
{
	unsigned int out_length = ( len * 2 ) + 1;

	char *result = malloc( sizeof( char ) * out_length ),
	     *ptr    = result;

	for ( int i = 0; i < len; i++ )
	{
		*ptr++ = hexValueToHexChar( bytes[ i ] / 0x10, 0 );
		*ptr++ = hexValueToHexChar( bytes[ i ] % 0x10, 0 );
	}
	*ptr = '\0';

	return result;
}

char *hexTripleToBase64Quad ( unsigned char *hex, unsigned int len )
{
	if ( *hex == '\0' )
	{
		puts( "Tried to pass zero-length string to be converted to base64." );
		return NULL;
	}
	char *result = malloc( sizeof( char ) * 5 );
	
	switch ( len )
	{
		case 1:
			result[ 0 ] = ( ( hex[ 0 ] & 0xFC ) >> 2 );
			result[ 1 ] = ( ( hex[ 0 ] & 0x03 ) << 4 );
			result[ 2 ] = -1;	
			result[ 3 ] = -1;
		break;
		case 2:
			result[ 0 ] = ( ( hex[ 0 ] & 0xFC ) >> 2 );
			result[ 1 ] = ( ( hex[ 0 ] & 0x03 ) << 4 )
			            | ( ( hex[ 1 ] & 0xF0 ) >> 4 );
			result[ 2 ] = ( ( hex[ 1 ] & 0x0F ) << 2 );
			result[ 3 ] = -1;
		break;
		case 3:
			result[ 0 ] = ( ( hex[ 0 ] & 0xFC ) >> 2 );
			result[ 1 ] = ( ( hex[ 0 ] & 0x03 ) << 4 )
			            | ( ( hex[ 1 ] & 0xF0 ) >> 4 );
			result[ 2 ] = ( ( hex[ 1 ] & 0x0F ) << 2 )
			            | ( ( hex[ 2 ] & 0xC0 ) >> 6 );
			result[ 3 ] = ( ( hex[ 2 ] & 0x3F ) >> 0 );
		break;
		default:
			free( result );
			result = NULL;
			puts( "Attempted to convert a hex triple of invalid length." );
			return NULL;
		break;
	}

	for ( int i = 0; i < 4; i++ )
		if ( result[ i ] != -1 )
			result[ i ] = byteToBase64Char( result[ i ] );
		else
			result[ i ] = '=';
	result[ 4 ] = '\0';

	return result;
}

char *hexBytesToBase64String ( unsigned char *hex, unsigned int len )
{
	char *result = NULL,
	     *temp   = NULL;

	int out_length = len * 1.4,
	    index      = 0,
	    left       = len;

	result = malloc( sizeof( char ) * out_length );
	result[ 0 ] = '\0';

	while ( index < len )
	{
		temp = hexTripleToBase64Quad( hex + index, 
		                              ( left > 3 ) ? 3 : left ); 
		strcat( result, temp );
		free( temp );
		temp = NULL;
		index += 3;
		left -= 3;
	}

	return result;
}

unsigned char *fixedLengthXOR ( unsigned char *in1, unsigned char *in2, 
                                unsigned int len )
{
	unsigned char *result = malloc( sizeof( unsigned char ) * len );

	int i = 0;
	do
		result[ i ] = in1[ i ] ^ in2[ i ];
	while ( ++i < len );

	return result;
}

unsigned char *singleByteXOR ( unsigned char *in, unsigned char key, 
                               unsigned int len )
{
	unsigned char *result = malloc( sizeof( unsigned char ) * len );

	int i = 0;
	do 
		result[ i ] = in[ i ] ^ key;
	while ( ++i < len );

	return result;
}

unsigned int plaintextScore ( char *in )
{
	unsigned int score = 0,
	             length = strlen( in );
	static const char FREQUENCY[ 26 ] = "etaoinshrdlcumwfgypbvkjxqz";
	static const char PAIRS[ 26 ] =     "thheaninerndreedesouthhaen";
	
	for ( int i = 0; i < length; i++ )
	{
		for ( int j = 0; j < 26; j++ )
		{
			if ( in[ i ] == FREQUENCY[ j ] 
			   || in[ i ] == FREQUENCY[ j ] - 32 )
				score += 26 - j;
		}
		if ( i < length - 1 )
			for ( int j = 0; j < 26; j += 2 )
			{
				if ( ( in[ i ] == PAIRS[ j ] 
				   || in[ i ] == PAIRS[ j ] - 32 )
				   && ( in[ i + 1 ] == PAIRS[ j + 1 ] 
				   || in[ i + 1 ] == PAIRS[ j + 1 ] - 32 ) )
					score += 26 + ( 26 - j );
			}
	}
	return score;
}

char sanitizeASCII ( char c )
{
	if ( c >= 32 && c <= 126 )
		return c;
	else
		return '.';
}

void hexDump ( unsigned char *str, unsigned int len )
{
	if ( !str )
	{
		puts( "Attempted to hex dump null addressed string." );
		return;
	}

	if ( *str == '\0' )
	{
		puts( "Attempted to hex dump string of zero length." );
		return;
	}
	
	int row    = 0,
	    column = 0,
	    index  = 0;

	unsigned char *ptr = str;
	char line[ 0x11 ] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

	puts( "" );

	printf( "      |" );
	for ( int i = 0; i < 0x10; i++ )
		printf( "  %01X", i );
	puts( " |" );

	printf( "------+" );
	for ( int i = 0; i < 0x10; i++ )
		printf( "---" );
	puts( "-+------------------" );

	printf( " %03XX |", row );

	while ( index < len )
	{
		printf( " %02X", *ptr );
		line[ column ] = sanitizeASCII( *ptr );
		if ( ++column % 0x10 == 0 )
		{
			column = 0;
			printf( " | %s\n", line );
			for ( int i = 0; i < 0x10; i++ )
				line[ i ] = '\0';
			
			if ( index + 1 < len )
				printf( " %03XX |", ++row );
		}
		ptr++;
		index++;
	}

	if ( column % 0x10 != 0 )
	{
		while ( column++ % 0x10 != 0 )
			printf( "   " );
		printf( " | %s\n", line );
	}

	puts( "" );
}

char **loadFileToStrings ( char *file, unsigned int *strCount )
{
	FILE *fptr = NULL;
	char c;
	char **result = NULL;
	unsigned int lines = 1,
	             length = 1,
		     countLength = 1;

	if ( ( fptr = fopen( file, "r" ) ) == NULL )
		printf( "Error opening file %s.\n", file );

	while ( !feof( fptr ) )
	{
		if ( countLength )
			length++;
		if ( fgetc( fptr ) == '\n' )
		{
			countLength = 0;
			lines++;
		}

	}

	*strCount = lines;
	result = malloc( sizeof( char * ) * lines );
	for ( int i = 0; i < lines; i++ )
		result[ i ] = malloc( sizeof( char ) * length );
	lines = 0;

	fseek( fptr, 0, SEEK_SET );

	while ( !feof( fptr ) )
		fscanf( fptr, "%s", result[ lines++ ] );

	fclose( fptr );
	fptr = NULL;

	return result;
}
