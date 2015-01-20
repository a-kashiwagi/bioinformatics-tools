/******************************************************************************/
/*                                                                            */
/* Title  : Hidden Markov Model by Viterbi Algorithm                          */
/* Program Name : viterbi_log.c                                               */
/*                                                                            */
/* Detail : Hidden Markov Model method by using Viterbi Algorithm             */
/* Date   : 2015/01/20                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
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
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/stat.h>

					/* Common arrays                      */
double *x;				/* Output numbers                     */
char   *pi;				/* Transition states                  */
double *sf;				/* F side transition probability      */
double *sb;				/* B side transition probability      */
long   *bf;				/* F side backtracking                */
long   *bb;				/* B side backtracking                */

/******************************************************************************/
/*                                                                            */
/* Title  : Check for filesize function                                       */
/* Function Name : ChkFileSize                                                */
/*                                                                            */
/* Detail : Return file size                                                  */
/* Date   : 2015/01/20                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *filename : Target file name                                 */
/*                                                                            */
/* Output : int : [ Byte : Normal Terminate ] [ -1 : Error(file not found)]   */
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

long ChkFileSize( char *filename ){

	struct stat st;				/* Struct Stat                */

	st.st_size = -1;			/* Initialize st_size         */

	stat( filename, &st );			/* Get status                 */

	return( st.st_size );			/* Return file size           */
}

/******************************************************************************/
/*                                                                            */
/* Title  : Get output stream                                                 */
/* Function Name : GetFile                                                    */
/*                                                                            */
/* Detail : Get file data                                                     */
/* Date   : 2015/01/20                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *filename : Target file name                                 */
/*          char *buff : Buffer of data of sequence                           */
/*                                                                            */
/* Output : long : [ Count of loaded charactar : Normal Terminate ]           */
/*                 [ -1                        : Error            ]           */
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

long GetFile( char *filename, double *buff ){

	FILE *fp;				/* File pointer               */
	long cnt;				/* Counter                    */
	char in_char;				/* In character               */

	fp = fopen( filename, "r" );		/* File open                  */
	if( fp == NULL ){			/* Error                      */
		return(-1);
	}

	in_char = fgetc( fp );			/* Get a character from file  */
	cnt = 0;				/* Counter initialize         */

	while( in_char != EOF ){

		if( in_char == '0' ){
						/* Set Zero                   */
			buff[cnt] = 0.0;
		}else{
						/* Set One                    */
			buff[cnt] = 1.0;
		}

		in_char = fgetc( fp );		/* Get next character         */

		cnt++;
	}

	fclose( fp );				/* File close                 */
	return(cnt);				/* Normal terminate           */
}

/******************************************************************************/
/*                                                                            */
/* Title  : Return an output probability                                      */
/* Function Name : e                                                          */
/*                                                                            */
/* Detail : return of an output probability                                   */
/* Date   : 2015/01/20                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char pi : transition state F or B                                 */
/*          char  x : output number 0 or 1                                    */
/*                                                                            */
/* Output : double : [ an output probability ]                                */
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

double e(char pi, double x){

	if( pi == 'F' ){
						// Case of Fair
		if( x == 0){
						// 0
			return 0.5;
		}else{
						// 1
			return 0.5;
		}
	
	}else{
						// Case of Bad
		if( x == 0){
						// 0
			return 0.25;
		}else{
						// 1
			return 0.75;
		}
	}
}

/******************************************************************************/
/*                                                                            */
/* Title  : Max function of dynamic programing                                */
/* Function Name : max                                                        */
/*                                                                            */
/* Detail : Calculate max number                                              */
/* Date   : 2015/01/20                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long size : data size                                             */
/*                                                                            */
/* Output : double : [ 0 : Normal Terminate ]                                 */
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

int max(long size){

	long n;
	double from_F;
	double from_B;

	for( n = 0; n < size; n++ ){
						// to F

						// F -> F
		from_F = log( e('F',x[n]) ) + sf[n - 1] + log( 0.9 );

						// B -> F
		from_B = log( e('F',x[n]) ) + sb[n - 1] + log( 0.1 );
		
		if( from_F > from_B ){
						// Set number F to F
			sf[n] = log( e('F',x[n]) ) + from_F;
			bf[n] = 0;

		}else{
						// Set number B to F
			sf[n] = log( e('F',x[n]) ) + from_B;
			bf[n] = 1;
		}
						// to B

						// F -> B
		from_F = log( e('B',x[n]) ) + sf[n - 1] + log( 0.1 );

						// B -> B
		from_B = log( e('B',x[n]) ) + sb[n - 1] + log( 0.9 );

		if( from_F > from_B ){
						// Set number F to B
			sb[n] = log( e('B',x[n]) ) + from_F;
			bb[n] = 0;
		}else{
						// Set number B to B
			sb[n] = log( e('B',x[n]) ) + from_B;
			bb[n] = 1;
		}
	}

	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Backtracking function of dynamic programing                       */
/* Function Name : backtracking                                               */
/*                                                                            */
/* Detail : Calculate backtracking                                            */
/* Date   : 2015/01/20                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long size : data size                                             */
/*                                                                            */
/* Output : double : [ 0 : Normal Terminate ]                                 */
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

int backtracking(long size){

	long n;
	long cur;
						// Initial state
	if( sf[size - 1] > sb[size - 1] ){
						// Start from F
		pi[size - 1] = 'F';
						// Cursor state F
		cur = 0;
	}else{
						// Start from B
		pi[size - 1] = 'B';
						// Cursor state B
		cur = 1;
	}

						// Backtracking loop
	for(n = size - 1; n > 0; n--){

		if( cur == 0 ){
						// Current is F
			if( bf[n] == 0 ){
						// Next state F
				pi[n - 1] = 'F';
						// Cursor state F
				cur = bf[n];
			}else{
						// Next state B
				pi[n - 1] = 'B';
						// Cursor state B
				cur = bb[n];
			}
		}else{
						// Current is B
			if( bb[n] == 0 ){
						// Next state F
				pi[n - 1] = 'F';
						// Cursor state F
				cur = bf[n];
			}else{
						// Next state B
				pi[n - 1] = 'B';
						// Cursor state B
				cur = bb[n];
			}
		}
	}

	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Main function                                                     */
/* Function Name : main                                                       */
/*                                                                            */
/* Detail :                                                                   */
/* Date   : 2015/01/20                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : int    argc : argument count                                      */
/*        : char **argv : argument value                                      */
/*                                                                            */
/* Output : double : [ 0 : Normal Terminate ]                                 */
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

int main( int argc, char **argv ){

	double p;
	long n;
	long size;
	int ret;
						// Get file size
	size = ChkFileSize( argv[1] );
						// Memory allocate 
	 x = malloc( sizeof(double) * size );
	pi = malloc( sizeof(char)   * size );
	sf = malloc( sizeof(double) * size );
	sb = malloc( sizeof(double) * size );
	bf = malloc( sizeof(long)   * size );
	bb = malloc( sizeof(long)   * size );
						// Get file data
	GetFile( argv[1], x );
						// Init
	sf[0] = log( e('F',x[0]) );
	sb[0] = log( e('B',x[0]) );
						// Call max function
	ret = max(size);
						// Call backtracking function
	ret = backtracking(size);

	for(n = 0; n < size; n++){
						// Print out input number
		printf("%.0f",x[n]);
	}
	printf("\n");

	for(n = 0; n < size; n++){
						// Print out output number
		printf("%c",pi[n]);
	}
	printf("\n");
						// Normal Terminate
	exit(0);
}
