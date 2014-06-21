/******************************************************************************/
/*                                                                            */
/* Title  : Find to motif                                                     */
/* Program Name : fmotif.c                                                    */
/*                                                                            */
/* Detail : Make new                                                          */
/* Date   : 2010/06/06                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2012/07/27                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Modifiy to threading                                              */
/*                                                                            */
/* Date   : 2014/01/05                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Modifiy for GPGUP                                                 */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>

#include "/home/a-kashiwagi/cuda_by_example/common/book.h"

#define LOOP 1
#define BUFFER_SIZE 1024
#define THREADS 256
#define BLOCKS 1024
						/* Functions                  */
long ChkFileSize( char *filename );
int GetSequence( char *filename, char *buff );

__global__ void threading_procedure(
	char *seq,
	long  seq_num,
	long  src_cnt,
	long  lmer,
	long  lmt,
	long *humming_score,
	long *humming_num,
	char *humming_str
){

	char *lmer_src;				/* Source of lmer string      */
	char *lmer_trg;				/* Target of lmer string      */
	long  lmer_num;				/* Number of lmer             */
	long humming_now;			/* Current humming range      */
	long humming_bigst;			/* Biggest humming range      */
	long humming_cnt;			/* Counter of                 */
	long trg_cnt;				/* Counter of target          */
	long cnt;				/* Counter                    */
	char *str_dest;				/* for local strcpy           */
	char *str_src;                          /* for local strcpy           */

						/* Index for GPUs             */
	src_cnt += threadIdx.x + (blockIdx.x * blockDim.x);
	if( src_cnt >= seq_num - lmer ){
						/* Check for end sequence     */
		return;
	}
						/* Reset values               */
	humming_bigst = 0;
	humming_score[src_cnt] = 0;
	humming_num[src_cnt] = 0;
						/* Get source sequence        */
	lmer_src = &seq[src_cnt];
						/* Set lmer                   */
	str_dest = &humming_str[lmer * src_cnt];
	str_src  = lmer_src;
						/* strcpy                     */
	for(cnt = 0; cnt < lmer; cnt++){
		*str_dest++ = *str_src++;
	}
	//*str_dest = '\0';

	for( trg_cnt = 0; trg_cnt < seq_num - lmer; trg_cnt++ ){
						/* Loop for target sequence   */

		if( src_cnt == trg_cnt ){
						/* Continue to                */
						/*          equality sequence */
			continue;
		}
						/* Get target lmer            */
		lmer_trg = &seq[trg_cnt];

						/* Reset humming number       */
		humming_now = 0;
						/* Calculate to humming range */
		for(	humming_cnt = 0;
			humming_cnt < lmer;
			humming_cnt++
		){
						/* Equality Charactor         */
						/*          source and target */
			if( lmer_src[humming_cnt]
				== lmer_trg[humming_cnt] ){

				humming_now++;
			}			/* Increment counter          */
		}
						/* Find to                    */
						/*      bigger score sequence */
		if( humming_now > humming_bigst ){
						/* Change from last to now    */
			humming_bigst = humming_now;
						/* Store to now number        */
			humming_score[src_cnt] = humming_now;
			humming_num[src_cnt] = 1;

		}else if( humming_now == humming_bigst ){

			humming_num[src_cnt]++;
						/* Find to equality score,    */
						/*     then increment counter */
		}
	}

						/* Check for limit            */
	/*
	if( humming_score[src_cnt] >= lmt ){

		printf(	"%ld,%ld,%s,%ld,%ld\n",
			src_cnt + 1,
			src_cnt + args->lmer,
			args->hs[src_cnt].str,
			args->hs[src_cnt].humming_score,
			args->hs[src_cnt].humming_num
		);
	}
	*/

	return;
}
						/* Function of main()         */
int main(int argc, char *argv[]){

	int ret;				/* Number of return           */
	long cnt;				/* Counter                    */
	long lmer;				/* Number of lmer             */
	long lmt;				/* Limit to score             */
	long ctn;				/* Continue from this         */
	char filename[BUFFER_SIZE];		/* Sequence fine name         */
	long filesize;				/* Size of file               */
	long seq_num;				/* Number of sequence         */
	long src_cnt;				/* Counter of source          */
						/*      calculating humming   */

	long *humming_score;			/* Score of humming range     */
	long *humming_num;			/* Number of equality score   */
	char *humming_str;			/* String of lmer             */
	char *endptr;
	char *seq;

						/* Pointer for GPGPU          */
	char *seq_dev;
						/* For Sequence               */
	long *hscr_dev;
						/* For Humming score          */
	long *hnum_dev;
						/* For Humming number         */
	char *hstr_dev;
						/* For Humming string         */
	lmer = 9;
	lmt  = 0;
	ctn  = 0;
						/* Check for argument         */
	if( argc > 1 ){
		for( cnt = 1; cnt < argc; cnt++ ){

						/* Get lmer                   */
			if( strcmp( argv[cnt], "-lmer" ) == 0 ){

				lmer = strtol( argv[cnt + 1], &endptr, 0);
				if( *endptr != '\0' ){
						/* Error                      */
					printf("Invalid number for -lmer.\n");
					exit(-1);
				}

						/* Get limit score            */
			}else if( strcmp( argv[cnt], "-lmt" ) == 0 ){

				lmt = strtol( argv[cnt + 1], &endptr, 0);
				if( *endptr != '\0' ){
						/* Error                      */
					printf("Invalid number for -lmt.\n");
					exit(-1);
				}

						/* Get continue location num  */
			}else if( strcmp( argv[cnt], "-ctn" ) == 0 ){

				ctn = strtol( argv[cnt + 1], &endptr, 0);
				if( *endptr != '\0' ){
						/* Error                      */
					printf("Invalid number for -ctn.\n");
					exit(-1);
				}
				ctn--;
			}
		}
						/* Get fine name              */
		strcpy( filename, argv[argc - 1] );

	}else{
						/* Not enough arguments       */
		printf("  Usage: fmotif [ Options ] seqence_filename\n");
		printf("Options:\n");
		printf("  -lmer number : set lmer - default 9\n");
		printf("  -lmt  number : set lower limit of lmer");
		printf(" - default 0\n");
		printf("  -ctn  number : set continue from this - default 0\n");
		printf("\n");

		exit(0);
	}
						/* Get file size              */
	filesize = ChkFileSize( filename );
	if( filesize != 0 ){
						/* Malloc for sequence        */
		seq = (char *)malloc( sizeof(int) * filesize );
		if( seq == NULL ){
			printf("Can not allocate memory.\n");
			exit(-1);
		}
						/* Set sequence number        */
		seq_num = filesize;
						/* Malloc for                 */
						/*       structure of humming */
		humming_score = (long *)malloc( sizeof(long) * seq_num);
		humming_num   = (long *)malloc( sizeof(long) * seq_num);
		humming_str   = (char *)malloc( sizeof(char) * lmer * seq_num);

	}else{
						/* Case of void               */
		printf("File is void.\n");
		exit(1);
	}
						/* Get sequence               */
	ret = GetSequence( filename, seq );

						/* Find to motif              */

						/* Set count of start location*/
	src_cnt = ctn;
						/* Memory allocation at GPU   */

	HANDLE_ERROR(cudaMalloc( (void**)&seq_dev,  sizeof(int)  * filesize ));
						/* For sequence               */

	HANDLE_ERROR(cudaMalloc( (void**)&hscr_dev, sizeof(long) * seq_num  ));
						/* For humming score          */

	HANDLE_ERROR(cudaMalloc( (void**)&hnum_dev, sizeof(long) * seq_num  ));
						/* For humming numger         */

	HANDLE_ERROR(
		cudaMalloc( (void**)&hstr_dev, sizeof(long) * lmer * seq_num  )
	);
						/* For humming string         */

						/* Data copy to GPGPU         */
	HANDLE_ERROR(
		cudaMemcpy(
			seq_dev,
			seq,
			sizeof(int) * filesize,
			cudaMemcpyHostToDevice
		)
						/* Sequence                   */
	);

	HANDLE_ERROR(
		cudaMemcpy(
			hscr_dev,
			humming_score,
			sizeof(long) * seq_num,
			cudaMemcpyHostToDevice
		)
						/* Humming score              */
	);

	HANDLE_ERROR(
		cudaMemcpy(
			hnum_dev,
			humming_num,
			sizeof(long) * seq_num,
			cudaMemcpyHostToDevice
		)
						/* Humming number             */
	);

	HANDLE_ERROR(
		cudaMemcpy(
			hstr_dev,
			humming_str,
			sizeof(char) * lmer * seq_num,
			cudaMemcpyHostToDevice
		)
						/* Humming string             */
	);

	while(LOOP){
						/* Call function of GPU side  */
		threading_procedure<<<BLOCKS,THREADS>>>(
			seq_dev,
			seq_num,
			src_cnt,
			lmer,
			lmt,
			hscr_dev,
			hnum_dev,
			hstr_dev
		);

		if(src_cnt >= seq_num - lmer ){
						/* Check end sequence         */
			break;
		}
						/* Set next start location    */
		src_cnt += BLOCKS * THREADS;
	}

						/* Data copy from GPGPU       */
	HANDLE_ERROR(
		cudaMemcpy(
			humming_score,
			hscr_dev,
			sizeof(long) * seq_num,
			cudaMemcpyDeviceToHost
		)
						/* Sequence                   */
	);

	HANDLE_ERROR(
		cudaMemcpy(
			humming_num,
			hnum_dev,
			sizeof(long) * seq_num,
			cudaMemcpyDeviceToHost
		)
						/* Humming number             */
	);

	HANDLE_ERROR(
		cudaMemcpy(
			humming_str,
			hstr_dev,
			sizeof(char) * lmer * seq_num,
			cudaMemcpyDeviceToHost
		)
						/* Humming string             */
	);
						/* Free to GPU memory         */
	HANDLE_ERROR(cudaFree(  seq_dev ));
	HANDLE_ERROR(cudaFree( hscr_dev ));
	HANDLE_ERROR(cudaFree( hnum_dev ));
	HANDLE_ERROR(cudaFree( hstr_dev ));
						/* Output                     */
	long cnt_lmer;

	for(cnt = 0; cnt < seq_num - lmer; cnt++){

		if( !(humming_score[cnt] >= lmt) ){
						/* Check for limit            */
			continue;
		}

		printf("%d,%d,",cnt + 1,cnt + lmer);

		for(cnt_lmer = 0; cnt_lmer < lmer; cnt_lmer++){
			printf("%c",humming_str[(lmer * cnt) + cnt_lmer]);
		}

		printf(",%ld,%ld\n", humming_score[cnt], humming_num[cnt]);
	}
						/* Free to memory             */
	free( humming_score );
	free( humming_num   );
	free( humming_str   );
	free( seq );
						/* Normal terminate           */
	exit(0);
}

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


