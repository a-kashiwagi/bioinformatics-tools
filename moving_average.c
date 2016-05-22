/******************************************************************************/
/*                                                                            */
/* Title  : Calculate a moving average                                        */
/* Program Name : moving_average                                              */
/*                                                                            */
/* Detail : Create                                                            */
/* Date   : 2016.05.21                                                        */
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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<math.h>

					// Structure for buffer
typedef struct _col{
					// Sequence number
        long seq;
					// Value for true
        double val_true;
					// Value for false
        double val_false;
} COL;
					// Delimiter
#define DELIM ","

int main( int argc, char *argv[] ){
					// Average
          long average_num;
					// Summary of true
        double summary_true;
					// Summary of false
        double summary_false;
					// Counter
        long cnt;
					// Counter for average
        long avg_cnt;
					// Cursor for output
        long output_cur;
					// Current row
        char cur[256];
					// Buffer for calculate
         COL *dat;
					// Token for strtok
        char *token;

					// Check for arguments
	if( argc < 2 ){
		printf("Usage: stdin | moving_average average_colmn\n");
		exit(-1);
	}
					// Get an average column
        average_num = atol(argv[1]);
					// Allocate a loop buffer memory
        dat = (COL *)malloc( sizeof(COL) * (long)average_num );

					// Counter reset
        cnt = 0;
					// Pre loop
        while( gets(cur) != NULL ){
					// Get a first column
                token = strtok( cur, DELIM );
                dat[cnt].seq = atol(token);

					// Get a second column
                token = strtok( NULL, DELIM );
                dat[cnt].val_true = (double)atof(token);

					// Get a third column
                token = strtok( NULL, DELIM );
                dat[cnt].val_false = (double)atof(token);

                if( cnt == (average_num - 2) ){
					// End of loop
                        break;
                }
					// Counter increment
                cnt += 1;
        }
					// Decrement counter
        cnt = average_num - 1;
					// Get a number of currsor for output
        output_cur = floor(average_num / 2) - 1;

					// Main loop
        while( gets(cur) != NULL ){
					// Get a first column
                token = strtok( cur, DELIM );
                dat[cnt].seq = atol(token);

					// Get a second column
                token = strtok( NULL, DELIM );
                dat[cnt].val_true = (double)atof(token);

					// Get a third column
                token = strtok( NULL, DELIM );
                dat[cnt].val_false = (double)atof(token);

					// Reset for summary
                summary_true  = 0;
                summary_false = 0;

                for(avg_cnt = 0; avg_cnt < average_num; avg_cnt++ ){

					// Calculate summary
                        summary_true  += dat[avg_cnt].val_true;
                        summary_false += dat[avg_cnt].val_false;
                }

					// Output result
                printf("%ld,%.12lf,%.12lf\n",
                        dat[output_cur].seq,
                        summary_true  / (double)average_num,
                        summary_false / (double)average_num
                );

                if( cnt == (average_num - 1) ){

					// Counter reset
                        cnt = 0;
                }else{
					// Counter increment
                        cnt += 1;
                }

                if( output_cur == (average_num - 1) ){

					// Counter for current cursor reset
                        output_cur = 0;
                }else{
					// Counter for Current cursor increment
                        output_cur += 1;
                }
        }
}
