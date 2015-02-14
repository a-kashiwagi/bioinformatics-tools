/******************************************************************************/
/*                                                                            */
/* Title  : Forward-Backward Algorithm of HMM                                 */
/* File Name : forward.c                                                      */
/*                                                                            */
/* Detail : Calculate a forward-backward algorithm of Hidden Markov Model     */
/* Date   : 2015.02.08                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : argv[1] : filename  ex.fairbet.txt                                */
/*          argv[2] :   fine_p  ex.0.5                                        */
/*          argv[3] :    bad_p  ex.0.75                                       */
/*          argv[4] : change_p  ex.0.1                                        */
/*                                                                            */
/* Output : (1).No                                                            */
/*          (2).forward  probability of F                                     */
/*          (3).forward  probability of B                                     */
/*          (4).backward probability of F                                     */
/*          (5).backward probability of B                                     */
/*          (6).Probability of F                                              */
/*          (7).Probability of B                                              */
/*          (8).Probability p(x)                                              */
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
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
						/* Input value x              */
double *x;
						/* Transition expression      */
char   *pi;
						/* F of forward               */
double *ff;
						/* B of forward               */
double *fb;
						/* F of backward              */
double *bf;
						/* B of backward              */
double *bb;
						/* Probability p(x)           */
double *p;

#define F 'F'
#define B 'B'
						/* Default values             */
double fp = 0.50;
double bp = 0.75;
double cp = 0.10;

/******************************************************************************/
/*                                                                            */
/* Title  : ChkFileSize                                                       */
/* Function Name : ChkFileSize()                                              */
/*                                                                            */
/* Detail : Get file data                                                     */
/* Date   : 2015.02.10                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *filename : File name                                        */
/*                                                                            */
/* Output : File size                                                         */
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
/* Title  : Get file                                                          */
/* Function Name : GetFile()                                                  */
/*                                                                            */
/* Detail : Get file data                                                     */
/* Date   : 2015.02.10                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char   *filename : File name                                      */
/*          double *buff     : Store to buffer                                */
/*                                                                            */
/* Output : Count of read character                                           */
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
			cnt++;
		}else if( in_char == '1' ){
						/* Set One                    */
			buff[cnt] = 1.0;
			cnt++;
		}	

		in_char = fgetc( fp );		/* Get next character         */
	}

	fclose( fp );				/* File close                 */
	return(cnt);				/* Normal terminate           */
}

/******************************************************************************/
/*                                                                            */
/* Title  : Probability of an output x                                        */
/* Function Name : e()                                                        */
/*                                                                            */
/* Detail : Probability of an output x                                        */
/* Date   : 2015.02.10                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  :   char pi : A current coin that F or                              */
/*          double  x : An output number that 0 or 1                          */
/*                                                                            */
/* Output : double : Probability of an output x                               */
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

	if( pi == F ){
						/* Case of F                  */
		if( x == 0){
						/* Case of x is zero          */
			return 1 - fp;
		}else{
						/* Case of x is one           */
			return fp;
		}
	
	}else{
						/* Case of B                  */
		if( x == 0){
						/* Case of x is zero          */
			return 1 - bp;
		}else{
						/* Case of x is one           */
			return bp;
		}
	}
}

/******************************************************************************/
/*                                                                            */
/* Title  : forward                                                           */
/* Function Name : forward()                                                  */
/*                                                                            */
/* Detail : Calculate a forward algorithm                                     */
/* Date   : 2015.02.10                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long n : Cursor number of n                                       */
/*                                                                            */
/* Output : Normal Terminate : 0                                              */
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

int forward(long n){

	double from_F;
	double from_B;

	// to F
						// F -> F
	from_F = ff[n - 1] * ( 1 - cp );
						// B -> F
	from_B = fb[n - 1] * ( cp );
		
	ff[n]  = e(F,x[n]) * ( from_F + from_B);

	// to B
						// F -> B
	from_F = ff[n - 1] * ( cp );
						// B -> B
	from_B = fb[n - 1] * ( 1 - cp );

	fb[n]  = e(B,x[n]) * ( from_F + from_B );

	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : backward                                                          */
/* Function Name : backward()                                                 */
/*                                                                            */
/* Detail : Calculate a backward algorithm                                    */
/* Date   : 2015.02.10                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long n : Cursor number of n                                       */
/*                                                                            */
/* Output : Normal Terminate : 0                                              */
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

int backward(long n){

	double from_F;
	double from_B;

	// to F
						// F -> F
	from_F = e(F,x[n + 1]) * bf[n + 1] * ( 1 - cp );

						// B -> F
	from_B = e(F,x[n + 1]) * bb[n + 1] * ( cp );
		
	bf[n]  = from_F + from_B;

	// to B
						// F -> B
	from_F = e(B,x[n + 1]) * bf[n + 1] * ( cp );

						// B -> B
	from_B = e(B,x[n + 1]) * bb[n + 1] * ( 1 - cp );

	bb[n]  = from_F + from_B;

	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : main function                                                     */
/* Function Name : main()                                                     */
/*                                                                            */
/* Detail : Start from this function                                          */
/* Date   : 2015.02.10                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : int    argc                                                       */
/*          char **argv                                                       */
/*                                                                            */
/* Output : Normal Terminate : 0                                              */
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

	long n;
	long size;
	int ret;
	char filename[1024];
	double sum;
						/* Check for arguments        */
	if( argc <= 4 ){

		printf("Usage: forward filename fine_p bad_p change_p\n");
		printf("   ex. forward fairbet.txt 0.5 0.75 0.1\n");
		exit(0);
	}
						/* Get arguments              */
	strcpy( filename, argv[1] );
	fp = atof( argv[2] );
	bp = atof( argv[3] );
	cp = atof( argv[4] );
						/* Get filesize               */
	size = ChkFileSize( filename );
	 					/* Memory allocate            */
	 x = malloc( sizeof(double) * size );
	pi = malloc( sizeof(char)   * size );
	ff = malloc( sizeof(double) * size );
	fb = malloc( sizeof(double) * size );
	bf = malloc( sizeof(double) * size );
	bb = malloc( sizeof(double) * size );
	 p = malloc( sizeof(double) * size );
						/* Initialize                 */
	memset(  x, 0, sizeof(double) * size );
	memset( pi, 0, sizeof(char)   * size );
	memset( ff, 0, sizeof(double) * size );
	memset( fb, 0, sizeof(double) * size );
	memset( bf, 0, sizeof(double) * size );
	memset( bb, 0, sizeof(double) * size );
	memset(  p, 0, sizeof(double) * size );
						/* Get file data              */
	size = GetFile( filename, x );
						/* Initialize start array     */
	ff[0] = e(F,x[0]);
	fb[0] = e(B,x[0]);

	for(n = 1; n < size; n++){
						/* Calculate forward          */
		forward(n);
	}
						/* Initialize end array       */
	bf[size - 1] = ff[size - 1];
	bb[size - 1] = fb[size - 1];

	for(n = size - 2; n >= 0; n--){
						/* Calculate backward array   */
		backward(n);
	}

	for(n = 0; n < size; n++){
						/* Calculate p(x)             */
		p[n] = (ff[n]*bf[n])+(fb[n]*bb[n]);
	}

	for(n = 0; n < size; n++){
						/* Print out answer           */
		printf("%d,%e,%e,%e,%e,%e,%e,%e\n",
			n,
			ff[n],
			fb[n],
			bf[n],
			bb[n],
			(ff[n]*bf[n])/p[n],
			(fb[n]*bb[n])/p[n],
			p[n]
		);
	}
						/* Normal Terminate           */
	exit(0);
}

