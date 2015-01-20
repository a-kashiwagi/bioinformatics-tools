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
#include <pthread.h>
#include <omp.h>

#define LOOP 1
#define BUFFER_SIZE 1024
#define THREADS 32
						/* Structure of humming num   */
typedef struct humming_t {
	char *str;				/* Sequence string            */
	long humming_score;			/* Score of humming range     */
	long humming_num;			/* Number of equality score   */
} HS;
						/* Structure for              */
						/*      threads arguments     */
typedef struct _threads_argments{
	char *seq;
	long seq_num;
	long src_cnt;
	long lmer;
	long lmt;
	HS *hs;
} thread_args;
						/* Functions                  */
long ChkFileSize( char *filename );
int GetSequence( char *filename, char *buff );

//__declspec( target(mic) ) void *threading_procedure( void *in_args );

void *threading_procedure( void *in_args ){

	thread_args *args;			/* Pointer for arguments      */
	char *lmer_src;				/* Source of lmer string      */
	char *lmer_trg;				/* Target of lmer string      */
	long  lmer_num;				/* Number of lmer             */
	long humming_now;			/* Current humming range      */
	long humming_bigst;			/* Biggest humming range      */
	long humming_cnt;			/* Counter of                 */
	long trg_cnt;				/* Counter of target          */
	long cnt;				/* Counter                    */
						/* Set pointer for arguments  */
	args = (thread_args *)in_args;

	#pragma offload target(mic) in(args : length(1) alloc_if(1) free_if(0))
						/* Malloc for lmer source     */
	lmer_src = malloc( sizeof(char) * args->lmer );
	if( lmer_src == NULL ){
		printf("Can not allocate memory.\n");
		exit(-1);
	}
						/* Malloc for lmer target     */
	lmer_trg = malloc( sizeof(char) * args->lmer );
	if( lmer_trg == NULL ){
		printf("Can not allocate memory.\n");
		exit(-1);
	}

	strncpy( lmer_src, &args->seq[args->src_cnt], args->lmer );

						/* Get source sequence        */

						/* Reset values               */
	humming_bigst = 0;
	args->hs[args->src_cnt].humming_score = 0;
	args->hs[args->src_cnt].humming_num = 0;
						/* Set lmer                   */
	strcpy( args->hs[args->src_cnt].str, lmer_src );

	#pragma omp parallel for
	for( trg_cnt = 0; trg_cnt < args->seq_num - args->lmer; trg_cnt++ ){
						/* Loop for target sequence   */

		if( args->src_cnt == trg_cnt ){
						/* Continue to                */
						/*          equality sequence */
			continue;
		}
						/* Get target lmer            */
		strncpy( lmer_trg, &args->seq[trg_cnt], args->lmer );

						/* Reset humming number       */
		humming_now = 0;
						/* Calculate to humming range */
		for(	humming_cnt = 0;
			humming_cnt < args->lmer;
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
			args->hs[args->src_cnt].humming_score = humming_now;
			args->hs[args->src_cnt].humming_num = 1;

		}else if( humming_now == humming_bigst ){

			args->hs[args->src_cnt].humming_num++;
						/* Find to equality score,    */
						/*     then increment counter */
		}
	}

						/* Check for limit            */
	if( args->hs[args->src_cnt].humming_score >= args->lmt ){
						/* Output to stdio            */
		printf(	"%ld,%ld,%s,%ld,%ld\n",
			args->src_cnt + 1,
			args->src_cnt + args->lmer,
			args->hs[args->src_cnt].str,
			args->hs[args->src_cnt].humming_score,
			args->hs[args->src_cnt].humming_num
		);
	}
						/* Free to memory             */
						/*          for lmer source   */
	free( lmer_src );
						/* Free to memory             */
						/*          for lmer source   */
	free( lmer_trg );

	//return;
}
						/* Function of main()         */
int main(int argc, char *argv[]){

	pthread_t *thread;			/* Pointer for thread ID      */
	thread_args *args;			/* Pointer                    */
						/*       for thread arguments */
	int *status;				/* Pointer for thread status  */
	int threads_cnt;			/* Counter for threads        */

	int ret;				/* Number of return           */
	long cnt;				/* Counter                    */
	long lmer;				/* Number of lmer             */
	long lmt;				/* Limit to score             */
	long ctn;				/* Continue from this         */
	char filename[BUFFER_SIZE];		/* Sequence fine name         */
	long filesize;				/* Size of file               */
	char *endptr;				/* endptr in strtol()         */
	char *seq;				/* Sequence string            */
	long seq_num;				/* Number of sequence         */
	long src_cnt;				/* Counter of source          */
						/*      calculating humming   */
	HS *hs;					/* Structure of humming num   */

	lmer = 9;
	lmt  = 0;
	ctn  = 0;
						/* Allocate to threads memory */

						/* Thread ID                  */
	thread = (pthread_t *)malloc( sizeof(pthread_t) * THREADS );
	if( thread == NULL ){
		printf("Can not allocate memory.\n");
		exit(-1);
	}

						/* Thread arguments           */
	args = (thread_args *)malloc( sizeof(thread_args) * THREADS );
	if( args == NULL ){
		printf("Can not allocate memory.\n");
		exit(-1);
	}

						/* Thread status              */
	status = (int *)malloc( sizeof(int) * THREADS );
	if( status == NULL ){
		printf("Can not allocate memory.\n");
		exit(-1);
	}

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
		seq = malloc( sizeof(int) * filesize );
		if( seq == NULL ){
			printf("Can not allocate memory.\n");
			exit(-1);
		}
						/* Set sequence number        */
		seq_num = filesize;
						/* Malloc for                 */
						/*       structure of humming */
		hs = malloc( sizeof(HS) * seq_num );

		for( cnt = 0; cnt < seq_num; cnt++ ){
						/* Malloc for hs[x].str       */
			hs[cnt].str = malloc( sizeof(char) * lmer );
		}
	}else{
						/* Case of void               */
		printf("File is void.\n");
		exit(1);
	}
						/* Get sequence               */
	ret = GetSequence( filename, seq );

						/* Find to motif              */

						/* Initialize for threads     */
	for( threads_cnt = 0; threads_cnt < THREADS; threads_cnt++ ){
		thread[threads_cnt] = -1;
		status[threads_cnt] = 0;
	}

	src_cnt = ctn;
						/* Sequences loop             */
	while(LOOP){
						/* Call calculation procedure */
						/*           by threading     */

		if( src_cnt >= seq_num - lmer ){
						/* Case of exit from loop     */
			break;
		}
						/* Threads loop               */
		for(	threads_cnt = 0;
			(threads_cnt < THREADS) && (src_cnt < seq_num - lmer);
			threads_cnt++
		){
						/* Synchronous threads        */
			if( thread[threads_cnt] != -1 ){
						/* Wait for a completed thread*/
				ret = pthread_join(
					thread[threads_cnt],
					(void *)&status
				);
						/* Error terminate            */
				if( ret != 0 ){
					printf( "Thread(%ld) ",threads_cnt );
					printf( "error terminated.\n" );
				}
						/* Detach thread              */
				pthread_detach( thread[threads_cnt] );
			}
						/* Set arguments              */
			args[threads_cnt].seq = seq;
			args[threads_cnt].seq_num = seq_num;
			args[threads_cnt].src_cnt = src_cnt;
			args[threads_cnt].lmer = lmer;
			args[threads_cnt].lmt = lmt;
			args[threads_cnt].hs = hs;

						/* Create to thread           */
			ret = (int)pthread_create(
				&thread[threads_cnt],
				NULL,
				&threading_procedure,
				&args[threads_cnt]
			);

			if( ret != 0 ){
						/* Error of create_thread()   */
				printf(	"Thread(%ld) create failed.\n",
					src_cnt
				);

				break;
			}
						/* Increment counter          */
			src_cnt++;
		}
	}
						/* Synchronous threads        */
	for( threads_cnt = 0; threads_cnt < THREADS; threads_cnt++ ){

						/* Wait for a completed thread*/
		ret = pthread_join(
			thread[threads_cnt],
			(void *)&status
		);
						/* Error terminate            */
		if( ret != 0 ){
			printf( "Thread(%ld) error terminated.\n",threads_cnt );
		}
						/* Detach thread              */
		pthread_detach( thread[threads_cnt] );
	}
						/* Free to memory             */
						/*      for humming structure */
	for( cnt = 0; cnt < args->seq_num; cnt++ ){
		free( hs[cnt].str );
	}
	free( hs );
						/* Free to memory for sequence*/
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


