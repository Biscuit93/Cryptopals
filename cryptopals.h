/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Takes a byte and returns the ASCII base64 character.                      *
 * i.e. 0x07 -> 'H'                                                          *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
unsigned char byteToBase64Char ( unsigned char byte );


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Takes a string of two bytes representing a hex byte and returns the value *
 * represented by it.                                                        *
 * i.e. "7F" -> 0x7F                                                         *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
unsigned char hexCharsToHexValue ( unsigned char *byte );


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Takes a string of characters representing bytes and returns an array of   *
 * values represented by them.                                               *
 * i.e. "1A2B3C4D5E6F" -> { 0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F }             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
unsigned char *hexStringToHexBytes ( char *str );


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Takes an array of bytes and returns an ASCII representation as a string.  *
 * i.e. { 0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F } -> "1A2B3C4D5E6F"             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char *hexBytesToHexString ( unsigned char *str, unsigned int len );


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Takes a value between 0x0 and 0xF and returns the ASCII character that    *
 * represents it. Parameter upper controls case of returned character.       *
 * i.e. 0x5 -> '5'                                                           *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char hexValueToHexChar ( unsigned char hex, int upper );


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Takes an array of at most three bytes and returns a string of four base64 *
 * characters.                                                               *
 * i.e. { 0x49, 0x27, 0x6D } -> "SSdt"                                       *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char *hexTripleToBase64Quad ( unsigned char *hex, unsigned int len );


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Takes an array of bytes and returns its base64 representation as a string.*
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char *hexBytesToBase64String ( unsigned char *hex, unsigned int len );


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Takes two equal sized arrays of bytes and returns their XOR result.       *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
unsigned char *fixedLengthXOR ( unsigned char *in1, unsigned char *in2, 
                                unsigned int len );


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Takes an array of bytes and XORs the bytes against a single key byte.     *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
unsigned char *singleByteXOR ( unsigned char *in, unsigned char key, 
                               unsigned int len );


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Takes a string and scores it based on the frequency of common letters.    *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
unsigned int plaintextScore ( char *in );


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Replaces the given character if it is a control character.                *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char sanitizeASCII ( char c );


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Prints a hex dump.                                                        *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void hexDump ( unsigned char *str, unsigned int len );

