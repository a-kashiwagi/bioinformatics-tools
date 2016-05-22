/******************************************************************************/
/*                                                                            */
/* Title  : Convert from DNA to Four bit pattern                              */
/* Program Name : Dna2Bit                                                     */
/*                                                                            */
/* Detail : Input DNA Output messagenger RNA                                  */
/* Date   : 2015/10/29                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : stdin                                                             */
/* Output : stdout                                                            */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/
#include <stdio.h>
#include <ctype.h>

int main(){
					// Input char
	int in_char;
					// Get a char
	in_char = fgetc( stdin );

	while( in_char != EOF ){
					// To upper
		in_char = toupper( in_char );

					// Transfer to a bit string
		switch( in_char ){

			case 'A':
				fprintf( stdout,"1,0,0,0" );
				break;

			case 'T':
				fprintf( stdout,"0,1,0,0" );
				break;

			case 'G':
				fprintf( stdout,"0,0,1,0" );
				break;

			case 'C':
				fprintf( stdout,"0,0,0,1" );
				break;

			default:
				fputc( in_char, stdout );
				break;
		}
					// Get a next char
		in_char = fgetc( stdin );

		if( in_char == '\n' ){
					// Case of LF
			fputc( in_char, stdout );

					// Get a next char
			in_char = fgetc( stdin );

		}else if( in_char != EOF ){
					// Put a comma
			fputc( ',', stdout );
		}
	}
}
