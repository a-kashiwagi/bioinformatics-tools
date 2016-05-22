/******************************************************************************/
/*                                                                            */
/* Title  : Extracting sequences from whole genome                            */
/* Program Name : extra_gene                                                  */
/*                                                                            */
/* Detail : Create                                                            */
/* Date   : 2016.05.20                                                        */
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
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/stat.h>

/******************************************************************************/
/*                                                                            */
/* Title  : Check for filesize function                                       */
/* Function Name : ChkFileSize                                                */
/*                                                                            */
/* Detail :                                                                   */
/* Date   : 2009/12/03                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *filename : Target file name                                 */
/*                                                                            */
/* Output : int : [ Byte : Normal Terminate ] [ -1 : Error ]                  */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/06/25                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Modifiy to support for Amino Acid                                 */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/
long ChkFileSize( char *filename ){

        struct stat st;                         /* Struct Stat                */
        
        stat( filename, &st );                  /* Get status                 */
        
        return( st.st_size );                   /* Return file size           */
}

/******************************************************************************/
/*                                                                            */
/* Title  : Get sequence function                                             */
/* Function Name : GetSequence                                                */
/*                                                                            */
/* Detail :                                                                   */
/* Date   : 2009/12/03                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *filename : Target file name                                 */
/*          char *buff : Buffer of data of sequence                           */
/*                                                                            */
/* Output : int : [ 0 : Normal Terminate ] [ -1 : Error ]                     */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/06/25                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Modifiy to support for Amino Acid                                 */
/*                                                                            */
/* Date   : 2010/08/24                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added procedure that convert to upper character                   */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/
int GetSequence( char *filename, char *buff ){

        FILE *fp;                               /* File pointer               */
        long cnt;                               /* Counter                    */
        long in_char;                           /* In character               */
        
        fp = fopen( filename, "r" );            /* File open                  */
        if( fp == NULL ){                       /* Error                      */
                return(-1);
        }
        
        /* buff[0] = ' '; */                    /* Insert space at header     */
        
        in_char = fgetc( fp );                  /* Get a character from file  */
        cnt = 0;                                /* Counter initialize         */
        
        while( in_char != EOF ){

		in_char = toupper( in_char );	/* Convert to upper           */
        
                if( in_char != '\n' ){          /* LF skip                    */
                        buff[cnt] = in_char;    /* Copy to buffer             */
                        cnt++;                  /* Counter increment          */
                }
                
                in_char = fgetc( fp );          /* Get next character         */
        }
        
        buff[cnt] = '\0';                       /* Set null at footer         */
        
        fclose( fp );                           /* File close                 */
        return(0);                              /* Normal terminate           */
}

int main(int argc, char *argv[]){
					// File pointer
	FILE *fp;
					// Return value
	int ret;
					// Counter
	long cnt;
					// Size of sequence
	long sequence_size;
					// Pointer of sequence
	char *sequence;
					// Char of sequence
	char seq_char;
					// Length of sequence
	long seq_len;
					// Counter of sequence
	long seq_cnt;
					// String of row
	char row_str[1024];
					// Token for strtok
	char *token;
					// Start cursor
	long s;
					// End cursor
	long e;
					// Last cursor of start
	long s_last;
					// Last cursor of end
	long e_last;
					// Buffer for output
	char *outbuff;

					// Check for arguments
	if( argc < 3 ){
		printf("cat ORF_position_csv_file | ");
		printf("extra_gene sequence_file unit_length\n");
		exit(-1);
	}
					// Get a length of unit
	seq_len = atol( argv[2] );
					// Get a file size
	sequence_size = ChkFileSize( argv[1] );

					// Allocate memory for sequence
	sequence = (char *)malloc( sequence_size );
	if( sequence == NULL ){
		exit(-1);
	}
					// Get a sequence file
	ret = GetSequence( argv[1], sequence );
	if( ret != 0 ){
		exit(-1);
	}
					// Allocate memory for unit
	outbuff = (char *)malloc( seq_len + 1 );
	if( outbuff == NULL ){
		printf("seq_len:%ld\n");
		exit(-1);
	}
					// Initialize
	s_last = -1;
	e_last = -1;
					// Loop
	while( 1 ){
					// Get a row
		if( fgets( row_str, 1024, stdin ) == NULL ){
			break;
		}

		token = strtok( row_str, "," );
					// Get a first column
		if( token == NULL ){
			break;
		}

		s = atol( token ) - 1;

		token = strtok( NULL, "," );
					// Get a second column
		if( token == NULL ){
			break;
		}

		e = atol( token ) - 1;
					// Get a Non ORF sequences 
		if( (s - e_last) > 1 ){

					// Reset a buffer and counter
			memset( outbuff, 0, seq_len );
			seq_cnt = 0;

			//for( cnt = e_last + 1; cnt < s + seq_len; cnt++ ){
			for( cnt = e_last + 1; cnt < s; cnt++ ){

					// Set next char
				outbuff[seq_cnt] = sequence[cnt];

					// Counter increment
				seq_cnt++;

					// Case of end of line
				if( ((cnt - e_last) % seq_len) == 0 ){

					// Insert LF
					outbuff[seq_len] = '\0';

					// Output sequences

					//fprintf( stdout,
					//	"%ld,%ld,0,1,%s\n",
					//	e_last + 1,s - 1, outbuff );

					fprintf( stdout,
						"%ld, ,%ld,0,1,%s\n",
						e_last + 1 + 1,s - 1 + 1,
						outbuff
					);

					// Reset a buffer and counter
					memset( outbuff, 0, seq_len );
					seq_cnt = 0;
				}
			}
					// Output sequences
			fprintf( stdout,
				"%ld, ,%ld,0,1,%s\n",
				e_last + 1 + 1,s - 1 + 1,
				outbuff
			);
		}
					// Get an ORF sequences 

					// Reset a buffer and counter
		memset( outbuff, 0, seq_len );
		seq_cnt = 0;

		//for( cnt = s; cnt <= e + seq_len; cnt++ ){
		for( cnt = s; cnt <= e; cnt++ ){

					// Set next char
			outbuff[seq_cnt] = sequence[cnt];

					// Counter increment
			seq_cnt++;
					// Case of end of line
			if( ((cnt - s + 1) % seq_len) == 0 ){

					// Insert null
				outbuff[seq_len] = '\0';

					// Output sequences

				//fprintf( stdout, "%ld,%ld,1,0,%s\n",
				//	s,e, outbuff );

				fprintf( stdout, "%ld, ,%ld,1,0,%s\n",
					s + 1,e + 1, outbuff
				);

					// Reset buffer and counter
				memset( outbuff, 0, seq_len );
				seq_cnt = 0;
			}
		}

					// Output sequences
		fprintf( stdout, "%ld, ,%ld,1,0,%s\n",s + 1,e + 1, outbuff );

					// Store last counter
		s_last = s;
		e_last = e;
	}
					// Free memory
	free( sequence );
	free( outbuff );
					// Normal terminate
	exit(0);
}
