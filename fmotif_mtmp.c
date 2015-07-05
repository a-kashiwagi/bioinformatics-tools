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

#define LOOP 1
#define BUFFER_SIZE 1024
#define THREADS 40
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
						/* Malloc for lmer source     */
	lmer_src = malloc( sizeof(char) * args->lmer + 1 );
	if( lmer_src == NULL ){
		printf("Can not allocate memory.\n");
		exit(-1);
	}
						/* Malloc for lmer target     */
	lmer_trg = malloc( sizeof(char) * args->lmer + 1 );
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

	/*
	printf("src_cnt:[%ld] seq_num:[%ld] lmer:[%ld] lmt:[%ld]\n",
		args->src_cnt,args->seq_num,args->lmer,args->lmt);
	*/

	for( trg_cnt = 0; trg_cnt < args->seq_num - args->lmer; trg_cnt++ ){
						/* Loop for target sequence   */

		if( args->src_cnt == trg_cnt ){
						/* Continue to                */
						/*          equality sequence */
			continue;
		}
						/* Get target lmer            */
		strncpy( lmer_trg, &args->seq[trg_cnt], args->lmer );
		lmer_trg[args->lmer] = '\0';

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
						/* Check for limit            */
		if( humming_now >= args->lmt ){
						/* Output to stdout           */
			printf(	"%ld,%ld,%ld,%s,%ld,%ld\n",
				args->src_cnt + 1,
				trg_cnt + 1,
				trg_cnt + args->lmer,
				lmer_trg,
				humming_now,
				1
			);
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
						/* Output to stdout           */
		printf(	"0,%ld,%ld,%s,%ld,%ld\n",
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

	return;
}
						/* Function of main()         */
int main(int argc, char *argv[]){
						/* Return value               */
	int ret;

	long cnt;				/* Counter                    */
	long lmer;				/* Number of lmer             */
	long lmt;				/* Limit to score             */
	long ctn;				/* Continue from this         */
	long siz;				/* Size of calculation        */
	long spl;				/* Spilit of calculation      */
	char qsub_flg;				/* Qsub mode                  */
	char filename[BUFFER_SIZE];		/* Sequence fine name         */
	char outputfilename[BUFFER_SIZE];	/* Output file name           */
	char commandfilename[BUFFER_SIZE];	/* Command file name          */
	char startfilename[BUFFER_SIZE];	/* Start file name            */
	FILE *fp_cmd;				/* File pointer for cmd file  */
        FILE *fp_start;				/* File pointer for start file*/
	char cmd[BUFFER_SIZE];			/* Command string             */
	char buf1[BUFFER_SIZE];			/* Buffer for command string1 */
	char buf2[BUFFER_SIZE];			/* Buffer for command string2 */
	char *endptr;				/* Pointer for strtol()       */
	long filesize;				/* File size of sequence      */
	int  status;				/* Status of fork()           */

						/* Initialize parameter       */
	lmer =  9;
	lmt  =  0;
	ctn  =  0;
	siz  = -1;
	spl  =  0;
	qsub_flg = 0;
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
				if( *endptr != '\0' || ctn == 0 ){
						/* Error                      */
					printf("Invalid number for -ctn.\n");
					exit(-1);
				}
				ctn--;
						/* Get calculate size num     */
			}else if( strcmp( argv[cnt], "-siz" ) == 0 ){

				siz = strtol( argv[cnt + 1], &endptr, 0);
				if( *endptr != '\0' ){
						/* Error                      */
					printf("Invalid number for -siz.\n");
					exit(-1);
				}
						/* Get split num              */
			}else if( strcmp( argv[cnt], "-spl" ) == 0 ){

				spl = strtol( argv[cnt + 1], &endptr, 0);
				if( *endptr != '\0' ){
						/* Error                      */
					printf("Invalid number for -spl.\n");
					exit(-1);
				}
						/* Get file name              */
				if( (cnt + 2) != (argc - 1) ){
					strcpy( outputfilename, argv[cnt + 2] );
				}else{
					printf("Can't find an output filename");
					printf(" or a sequence filename.\n");
				}
						/* qsub mode                  */
			}else if( strcmp( argv[cnt], "-qsub" ) == 0 ){
						/* qsub ON                    */
				qsub_flg = 1;
			}
		}
						/* Get fine name              */
		strcpy( filename, argv[argc - 1] );

	}else{
						/* Not enough arguments       */
		printf("  Usage: fmotif_mtmp [ Options ] seqence_filename\n");
		printf("Options:\n");
		printf("  -qsub        : output qsub command shell\n");
		printf("  -lmer number : set lmer - default 9\n");
		printf("  -lmt  number : set lower limit of lmer");
		printf(" - default 0\n");
		printf("  -ctn  number : set continue from this - default 0\n");
		printf("  -spl  number output_filename\n");
		printf("               : set split number");
		printf(" and an output filename\n");
		printf("\n");

		exit(0);
	}
						/* Get file size              */
	filesize = ChkFileSize( filename );

	if( spl == 0 ){
						/* Case of non split          */
		processing_procedure(filename,filesize,lmer,lmt,ctn,siz);

	}else if( qsub_flg == 1){
						/* Make start.sh filename     */
		sprintf(startfilename,"%s_start.sh",outputfilename);
						/* Open start.sh file         */
		fp_start = fopen(startfilename,"w");
		if( fp_start == NULL ){
			printf( "Can't open start file.[%s]\n",
				startfilename
			);
			exit(-1);
		}
		fprintf(fp_start,"#! /bin/sh\n\n");
						/* Case of multi processing   */

						/* Calculating splited size   */
		siz = filesize / spl;
						/* Initialize start count num */
		ctn = 1;
						/* Loop for fork()            */
		for( cnt = spl; cnt > 0; cnt-- ){

			if( ctn >= lmer ){
						/* Subtract lmer from ctn     */
				ctn -= lmer;
			}

			if( cnt == 1 ){
						/* Add a number of reminder   */
				siz = (filesize - ctn) + 1;
			}
						/* Make command for fork()    */
			sprintf(cmd,
				"%s%s -lmer %ld -lmt %ld -ctn %ld -siz %ld %s > %s",
				"/home/a-kashiwagi/bin/",argv[0], lmer, lmt,
				ctn, siz, filename, outputfilename
			);
						/* Add a starting count       */
			sprintf(buf1,"_%%0%dld",(int)log10(filesize)+1);
			sprintf(buf2,buf1,ctn);
						/* Join with cmd and count    */
			strcat(cmd,buf2);
						/* Case of                    */
						/*   a make of command files  */
			sprintf(commandfilename,
				"%s%s.sh",
				outputfilename,
				buf2
			);
						/* Output start.sh command    */
			//fprintf(fp_start,"qsub -l month -l medium %s\n",
			fprintf(fp_start,"qsub -pe def_slot 2 %s\n",
				commandfilename
			);
						/* Open command file          */
			fp_cmd = fopen(commandfilename,"w");
			if( fp_cmd == NULL ){
				printf( "Can't open commandfile.[%s]\n",
					commandfilename
				);
				exit(-1);
			}
						/* Output each command        */
			fprintf(fp_cmd,"#! /bin/sh\n");
			fprintf(fp_cmd,"#$ -S /bin/sh\n");
			fprintf(fp_cmd,"\n");
			fprintf(fp_cmd,"echo -n \"start:\"\n");
			fprintf(fp_cmd,"date");
			fprintf(fp_cmd,"\n");

			fprintf(fp_cmd,"%s\n",cmd);

			fprintf(fp_cmd,"\n");
			fprintf(fp_cmd,"echo -n \"end:\"\n");
			fprintf(fp_cmd,"date\n");
						/* Close command file         */
			fclose(fp_cmd);
						/* Add a number of size       */
			ctn += siz;
		}
						/* Close start.sh file        */
		fclose(fp_start);

	}else{
						/* Case of multi processing   */

						/* Calculating splited size   */
		siz = filesize / spl;
						/* Initialize start count num */
		ctn = 1;
						/* Loop for fork()            */
		for( cnt = spl; cnt > 0; cnt-- ){

			if( ctn >= lmer ){
						/* Subtract lmer from ctn     */
				ctn -= lmer;
			}

			if( cnt == 1 ){
						/* Add a number of reminder   */
				siz = (filesize - ctn) + 1;
			}
						/* Make command for fork()    */
			sprintf(cmd,
				"%s -lmer %ld -lmt %ld -ctn %ld -siz %ld %s > %s",
				argv[0], lmer, lmt, ctn, siz,
				filename, outputfilename
			);
						/* Add a starting count       */
			sprintf(buf1,"_%%0%dld",(int)log10(filesize)+1);
			sprintf(buf2,buf1,ctn);
						/* Join with cmd and count    */
			strcat(cmd,buf2);
						/* Fork()                     */
			switch( fork() ){
						/* Case of normal             */
				case  0:
					execlp( "sh", "sh", "-c", cmd, NULL );
					printf("execvp was failed.\n");
					exit(-1);
					break;
						/* Case of error              */
				case -1:
					printf("Fork(%d) was failed.\n",cnt);
					exit(-1);
			
				default:
					break;
			}
						/* Add a number of size       */
			ctn += siz;
		}
						/* Wait for                   */
						/*        an end of process   */
		wait(&status);
	}
						/* Normal terminate           */
	exit(0);
}

int processing_procedure(
	char *filename,
	long filesize,
	long lmer,
	long lmt,
	long ctn,
	long size
){
	pthread_t *thread;			/* Pointer for thread ID      */
	thread_args *args;			/* Pointer                    */
						/*       for thread arguments */
	int *status;				/* Pointer for thread status  */
	int threads_cnt;			/* Counter for threads        */

	int ret;				/* Number of return           */
	long cnt;				/* Counter                    */
	char *endptr;				/* endptr in strtol()         */
	char *seq;				/* Sequence string            */
	long seq_num;				/* Number of sequence         */
	long src_cnt;				/* Counter of source          */
						/*      calculating humming   */
	HS *hs;					/* Structure of humming num   */

	/*
	printf("filename:[%s] filesize:[%ld] lmer:[%ld] ",
		filename,filesize,lmer
	);
	printf("lmt:[%ld] ctn:[%ld] size:[%ld]\n",
		lmt,ctn,size
	);
	*/

	if( filesize != 0 ){
						/* Malloc for sequence        */
		seq = (char *)malloc( sizeof(int) * filesize );
		if( seq == NULL ){
			printf("Can not allocate memory.\n");
			exit(-1);
		}
						/* Get sequence               */
		ret = GetSequence( filename, seq );

						/* Malloc for                 */
						/*       structure of humming */
		hs = malloc( sizeof(HS) * filesize );

		for( cnt = 0; cnt < filesize; cnt++ ){
						/* Malloc for hs[x].str       */
			hs[cnt].str = malloc( sizeof(char) * lmer + 1 );
		}
	}else{
						/* Case of void               */
		printf("File is void.\n");
		exit(1);
	}
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
						/* Find to motif              */

						/* Initialize for threads     */
	for( threads_cnt = 0; threads_cnt < THREADS; threads_cnt++ ){
		thread[threads_cnt] = -1;
		status[threads_cnt] = 0;
	}

	src_cnt = ctn;

	if( size >= 0 ){
		seq_num = ctn + size;
	}else{
		seq_num = filesize;
	}

	/*
	printf("ctn:[%ld] size:[%ld] seq_num:[%ld] src_cnt:[%ld]\n",
		ctn,size,seq_num,src_cnt
	);
	*/
						/* Sequences loop             */
	while(LOOP){
						/* Call calculation procedure */
						/*           by threading     */
		if( src_cnt >= (seq_num - lmer) ){
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
					printf( "Thread(%d) ",threads_cnt );
					printf( "error terminated.\n" );
				}
						/* Detach thread              */
				pthread_detach( thread[threads_cnt] );
			}
						/* Set arguments              */
			args[threads_cnt].seq = seq;
			//args[threads_cnt].seq_num = seq_num;
			args[threads_cnt].seq_num = filesize; 
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
			// debug
			//break;
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
			printf( "Thread(%d) error terminated.\n",threads_cnt );
		}
						/* Detach thread              */
		pthread_detach( thread[threads_cnt] );
	}
						/* Free to memory             */
						/*      for humming structure */
	for( cnt = 0; cnt < filesize; cnt++ ){
		free( hs[cnt].str );
	}
	free( hs );
						/* Free to memory for sequence*/
	free( seq );
						/* Normal terminate           */
	return 0;
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


