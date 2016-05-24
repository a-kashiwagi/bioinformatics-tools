/******************************************************************************/
/*                                                                            */
/* Title  : Neural Network for DNA Recognize                                  */
/* Program Name : dna_recognizer.c                                            */
/*                                                                            */
/* Detail : Calculate a Neural Network for DNA Recoginze by Backpropagation   */
/* Date   : 2015.11.03                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Computations were partially performed on the NIG supercomputer             */
/* at ROIS National Institute of Genetics.                                    */
/*                                                                            */
/* Copyright(c)2015 Akihiro Kashiwagi All Right Reserved                      */
/*                                                                            */
/* This software is freeware and shareware.                                   */
/* and case of business use, Please 10[%] part of profit pay for me.          */
/* because I must eat bread every day.(see Genesis 3:19)                      */
/* please you will inquire to me about detail information.                    */
/*                                                                            */
/* e-mail: a-kashiwagi@mippi-mail.com                                         */
/*                                                                            */
/* and I thanks for YHWH GOD, your creation is wonderful.                     */
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
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <zlib.h>
					// Header of Mersenne twister
//#include "dnn.h"

#include "dnn_lib.h"
//#include "neuron.h"
#include "bp_lib.h"

//#include "dnn_lib_mic.h"
//#include "neuron_mic.h"
//#include "bp_lib_mic.h"
					// Stabilizer
#define  IN_MAX 48
#define   M_MAX 12
#define OUT_MAX 2
					// Phase Number
#define  IN_PHASE 0
#define   M_PHASE 1
#define OUT_PHASE 2

#define ETA 0.01
#define PERSISTENT_T 1
#define EPSILON 0.0000001

#define BUFFSIZE 1024000

#define INITIAL_FILE	"init_minibatch"
#define  RESULT_FILE	"result_minibatch"
#define SUFFIX		".dat"

/*
__declspec( target(mic) ) int dna_recognize(
	long  in_max,
	long   m_max,
	long out_max,
	double *data_arr,
	long    data_row_num,
	double *teach_arr,
	long    teach_row_num,
	long    learn_times,
	long	result_no,
	long	interval
);

__declspec( target(mic) ) int output(
	double *data,
	NEURON_P **np,
	double *t,
	long learn_cnt,
	long in_max
);
*/

/******************************************************************************/
/*                                                                            */
/* Title  : A Main Function                                                   */
/* Function Name : main()                                                     */
/*                                                                            */
/* Detail : Calculate a Neural Network for DNA Recognize                      */
/* Date   : 2015.11.03                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : int argc    : argument counter                                    */
/*        : char **argv : argument values                                     */
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

	int ret;
					// Pointer for a learning data
	double *data;
					// Pointer for a teach data
	double *teach;
					// Buffer
	char buff[1024];
					// For Arguments
	long learn_times;
					// Number of a learn times
	char unit_num[1024];
					// Number of a neuron unit
	char data_file[1024];
					// Name of learning data file name
	long data_row_num;
					// Number of row of learning data
	char teach_file[1024];
					// Name of teach data file name
	long teach_row_num;
					// Name of init data file name
	char init_file[1024];
					// Number of row of teach data
	long result_no;
					// Number of interval
	long interval;
					// Flag of stream mode
	int stream_mode;
					// Cursor of argv
	int cur;
					// Number of neurons
	long  in_max;
	long   m_max;
	long out_max;
					// Initialize arguments
	  learn_times = -1;
	       in_max = -1;
		m_max = -1;
	      out_max = -1;
	 data_file[0] = '\0';
	 data_row_num = -1;
	teach_file[0] = '\0';
	teach_row_num = -1;
	    result_no = -1;
	     interval = -1;
	  stream_mode =  0;
	sprintf( init_file, "%s%s", INITIAL_FILE, SUFFIX );

					// Get arguments
	for( cur = 1; cur < argc; cur++ ){
 
		if( strncmp( argv[cur], "-h", strlen(argv[cur]) ) == 0 ){
			if( cur < argc - 1 ) cur++;

			printf("\n");
			printf("  Usage: dna_recognizer_zip ");
			printf("-init   -u number\n");
			printf("         dna_recognizer_zip ");
			printf("-detect -u number [-i number]\n");
			printf("         dna_recognizer_zip ");
			printf("-learn  -u number [-i number] [-t number]\n");
			printf("                                   ");
			printf(" -r number -data  filename row-number\n");
			printf("                                   ");
			printf("           -teach filename row-number\n\n");
			printf("         dna_recognizer_zip ");
			printf("-stream -detect -u number [-i number]\n");
			printf("         dna_recognizer_zip ");
			printf("-stream -learn  -u number [-i number]");
			printf(" [-t number]\n");
			printf("                                   ");
			printf(" -r number -teach filename row-number\n");
			printf("Options:\n");
			printf("	-h\t\t: Help\n");
			printf("	-init\t");
			printf("	: Make an init data file.\n");

			printf("	-detect\t");
			printf("	: Detect mode.\n");

			printf("	-learn\t");
			printf("	: Learning mode.\n");

			printf("	-stream\t");
			printf("	: Stream mode.\n");

			printf("	-u number");
			printf("	: Set number of unit.\n");

			printf("	-ui number");
			printf("	: Set number of input unit. ");

			printf("	-uh number");
			printf("	: Set number of hidden unit. ");
			printf(" Default (unit number) * 2.\n");

			printf("	-uo number");
			printf("	: Set number of output unit. ");
			printf(" Default [%ld].\n",OUT_MAX);

			printf("	-i number");
			printf("	: Set number of interval. ");
			printf(" Default an unit number.\n");

			printf("	-t number");
			printf("	: Set number of learning times.\n");

			printf("	-r number");
			printf("	: Set number of result.\n\n");

			printf("	-teach filename row-number\n\t\t");
			printf("	: Set a teach filename and ");
			printf("that a row number.\n\n");

			printf("	-init_file filename\n\t\t");
			printf("	: Set an init filename.\n\n");

			printf("\tCopyright(c) 2016 Akihiro Kashiwagi");
			printf(" e-mail: a-kashiwagi@mippi-mail.com\n\n");

			exit(0);
		}

		if( strcmp( argv[cur], "-init" ) == 0 ){

					// Initialize mode
			result_no = -1;

			continue;
		}

		if( strcmp( argv[cur], "-detect" ) == 0 ){

					// Detect mode
			learn_times = 0;
			result_no = 0;

			continue;
		}

		if( strcmp( argv[cur], "-learn" ) == 0 ){

					// Learning mode
			learn_times = 1;

			continue;
		}

		if( strcmp( argv[cur], "-stream" ) == 0 ){

					// Stream mode
			stream_mode = 1;

			continue;
		}

		if( strcmp( argv[cur], "-t" ) == 0 ){
			if( cur < argc - 1 ) cur++;
					// Get a learn times
			learn_times = atol( argv[cur] );
			continue;
		}

		if( strcmp( argv[cur], "-u" ) == 0 ){
			if( cur < argc - 1 ) cur++;
					// Get a unit number
			strncpy( unit_num, argv[cur], 1024 );
			in_max = atol( unit_num );
			continue;
		}

		if( strcmp( argv[cur], "-ui" ) == 0 ){
			if( cur < argc - 1 ) cur++;
					// Get a unit number
			strncpy( unit_num, argv[cur], 1024 );
			in_max = atol( unit_num );
			continue;
		}

		if( strcmp( argv[cur], "-uh" ) == 0 ){
			if( cur < argc - 1 ) cur++;
					// Get a unit number
			strncpy( unit_num, argv[cur], 1024 );
			m_max = atol( unit_num );
			continue;
		}

		if( strcmp( argv[cur], "-uo" ) == 0 ){
			if( cur < argc - 1 ) cur++;
					// Get a unit number
			strncpy( unit_num, argv[cur], 1024 );
			out_max = atol( unit_num );
			continue;
		}

		if( strcmp( argv[cur], "-i" ) == 0 ){
			if( cur < argc - 1 ) cur++;
					// Get an interval
			interval = atol( argv[cur] );
			continue;
		}

		if( strcmp( argv[cur], "-data" ) == 0 ){
			if( cur < argc - 1 ) cur++;
					// Get a learning data file name
			strncpy( data_file, argv[cur], 1024 );
			if( cur < argc - 1 ) cur++;
					// Get a number of row of data file
			data_row_num = atol( argv[cur] );
			continue;
		}

		if( strcmp( argv[cur], "-teach" ) == 0 ){
			if( cur < argc - 1 ) cur++;
					// Get a teach data file name
			strncpy( teach_file, argv[cur], 1024 );
			if( cur < argc - 1 ) cur++;
					// Get a number of row of teach file
			teach_row_num = atol( argv[cur] );
			continue;
		}

		if( strcmp( argv[cur], "-init_file" ) == 0 ){
			if( cur < argc - 1 ) cur++;
					// Get a teach data file name
			strncpy( init_file, argv[cur], 1024 );
			if( cur < argc - 1 ) cur++;

			continue;
		}

		if( strcmp( argv[cur], "-r" ) == 0 ){
			if( cur < argc - 1 ) cur++;
					// Get a result file number
			result_no = atol( argv[cur] );
			continue;
		}
	}

	if( in_max <= 0 ){
					// Check for "-u" option
		printf("Do you set an unit nubmer?\n");
		exit(-1);
	}

	if( m_max == -1 ){
					// Set a number of hidden unit
		//m_max = (long)floor( ((double)in_max + 0.5) / 2);
		m_max = (long)floor( ((double)in_max + 1) * 2);
	}

	if( out_max == -1 ){
					// Set a number of output unit
		out_max = OUT_MAX;
	}

	if( interval == -1 ){
					// Set default interval
		interval = in_max / 4;
	}

	 data = NULL;
	teach = NULL;

	if( data_file[0] != '\0' ){

		if( data_row_num == -1 ){

			printf("Do you set a row number of data file?\n");
			exit(-1);
		}

		fprintf(stderr,"data_file: %s\n", data_file);
		fprintf(stderr,"data_row_num: %ld\n", data_row_num);
		fprintf(stderr,"in_max: %ld\n", in_max);

		data = (double *)load_data ( data_file, data_row_num, in_max );
					// Get a learning data
		if( data == NULL ){
			printf( "Can't load a learning data from [%s].\n",
				data_file
			);

			return -1;
		}
	}

	if( teach_file[0] != '\0' ){

		if( teach_row_num == -1 ){

			printf("Do you set a row number of teach file?\n");
			exit(-1);
		}

		if( stream_mode == 1 ){
					// Case of stream mode
			teach = (double *)load_teach(
				teach_file, teach_row_num, out_max + 2
			);
		}else{
					// Case of not stream mode
			teach = (double *)load_teach(
				teach_file, teach_row_num, out_max
			);
		}
					// Get a teach data
		if( teach == NULL ){
			printf("Can't load a teach data from [%s].\n",
				teach_file
			);

			return -1;
		}
	}
					// Call dna_recognize function
	//omp_set_num_threads_target(TARGET_MIC,0,60);
	//#pragma offload target(mic) \
	//in(  data: length(  data_row_num *  in_max )) \
	//in( teach: length( teach_row_num * out_max ))
	ret = dna_recognize(
		 in_max,
		  m_max,
		out_max,
		data,
		data_row_num,
		teach,
		teach_row_num,
		init_file,
		learn_times,
		result_no,
		interval,
		stream_mode
	);
					// Free memorys
	if( data != NULL ){
		free( data  );
		data = NULL;
	}

	if( teach != NULL ){
		free( teach );
		teach = NULL;
	}

	exit(0);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Get teach data for case of streaming learning                     */
/* Function Name : get_teach_data()                                           */
/*                                                                            */
/* Detail : Get teach data for case of streaming learning                     */
/* Date   : 2016.01.25                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : double *teach          : Pointer of teach data                    */
/*        :   long  teach_row_num  : Number of    row of teach data           */
/*        :   long  teach_col_num  : Number of column of teach data           */
/*        :   long  sequence_no    : Number of current sequence               */
/*        :   long  sequence_length: Number of sequence length                */
/*        : double *ret_teach_data : Pointer of teach data for return         */
/*                                                                            */
/* Output : double * : Pointer of teach data for return                       */
/*        : NULL     : Error                                                  */
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

double *get_teach_data(
	double *teach,
	long teach_row_num,
	long teach_col_num,
	long sequence_no,
	long sequence_length,
	double *ret_teach_data
){
					// Cursor
	long cur;
					// Start position
	long start;
					// End   position
	long end;
					// Find flag
	int find_flg;
					// Find row
	long find_head;
	long find_tail;
					// Init number
	find_head = -1;
	find_tail = -1;
					// Loop of cursor
	for( cur = 0; cur < teach_row_num; cur++ ){

					// Get a position nubmers start & end
		start = teach[(teach_col_num + 2) * cur + 0];
		  end = teach[(teach_col_num + 2) * cur + 1];

		if(	   (start <= sequence_no)
			&& (  end >= sequence_no)
			&& find_head == -1
		){
					// Find a match row
			find_head = cur;
		}

		if(	   (start <= sequence_no + sequence_length)
			&& (  end >= sequence_no + sequence_length)
			&& find_tail == -1
		){
					// Find a match row
			find_tail = cur;
		}

		if( find_head != -1 && find_tail != -1 ){
					// Exit conditions
			break;
		}
	}

	if( find_head == -1 || find_tail == -1 ){
					// Case of not found
		return NULL;
	}

	if(	teach[(teach_col_num + 2) * find_head + 2] ==
		teach[(teach_col_num + 2) * find_tail + 2] &&
		teach[(teach_col_num + 2) * find_head + 3] ==
		teach[(teach_col_num + 2) * find_tail + 3] ){

					// Set return values
		ret_teach_data[0] = teach[(teach_col_num + 2) * cur + 2];
		ret_teach_data[1] = teach[(teach_col_num + 2) * cur + 3];
	}else{
		return NULL;
	}

					// Normal Terminate
	return ret_teach_data;
}

/******************************************************************************/
/*                                                                            */
/* Title  : A Function of DNA Recognize                                       */
/* Function Name : dna_recogniez()                                            */
/*                                                                            */
/* Detail : Neural Network for DNA Recognize                                  */
/* Date   : 2015.10.28                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long    in_max      : Number of neuron unit of  input phase       */
/*        : long     m_max      : Number of neuron unit of hidden phase       */
/*        : long   out_max      : Number of neuron unit of output phase       */
/*        : double *in_data     : Pointer of Input Data (two dim)             */
/*        : long   data_row_num : Number of row of input data                 */
/*        : double *teach       : Pointer of Teach Data (two dim)             */
/*        : long  teach_row_num : Number of row of input data                 */
/*        : char *init_file     : Pointer of init Data                        */
/*        : long  learn_time    : Number of learn times                       */
/*        : long  result_no     : Number of added result file name            */
/*        : long  interval      : Number of step interval                     */
/*        : int   stream_mode   : Flag of stream mode                         */
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

int dna_recognize(
	  long   in_max,
	  long    m_max,
	  long  out_max,
	  double *in_data,
	  long    data_row_num,
	  double *teach,
	  long    teach_row_num,
	  char	 *init_file,
	  long    learn_times,
	  long	  result_no,
	  long	  interval,
	  int     stream_mode
){
					// Phase 01
	NEURON_P npi_unit;
					// Phase 02
	NEURON_P nph_unit;
					// Phase 03
	NEURON_P npo_unit;
					// Pointer for each phases
	NEURON_P *n[3];
					// Teach data
	double t[out_max];
					// Learn flag
	int learn_flg;
					// Counter
	long cnt;
					// for phase
	long phase;
					// for data
	long data_cnt;
					// for teach
	long teach_cnt;
					// for learn
	long learn_cnt;
					// Retern value for create_synapse
	double **ret;
					// Retern value for other functions
	int err;
					// Return value for get_teach_data()
	double *ret_p;
					// File pointer for gz
	gzFile fp;
					// File name
	char file_name[1024];
					// Number of unit
	long unit_num;
					// #define UNIT_NUM 4

					// Number of digit
	long digit_num;
					// #define DIGIT_NUM 12+2

	double *data;
					// Buffer
	double *buff;
					// Value
	char	val[12+2];
					// Counter of value
	long	val_cnt;
					// Counter of unit
	long	unit_cnt;
					// EOF flag
	int	eof_flg;
					// Interval of learning and detect
	//long	interval;
					// Set interval
	//interval = 25;

	 unit_num = 4;
	digit_num = 12+2;
					// Create Neurons

	npi_unit.p   = create_neuron(  in_max, 0 );
					// for input phase
	if( npi_unit.p == NULL ){
		return -1;
	}
					// Set number of neuron unit
	npi_unit.num =  in_max;

	nph_unit.p   = create_neuron(   m_max, 0 );
					// for hidden phase
	if( nph_unit.p == NULL ){
		return -1;
	}
					// Set number of neuron unit
	nph_unit.num =   m_max;

	npo_unit.p   = create_neuron( out_max, 0 );
					// for output phase
	if( npo_unit.p == NULL ){
		return -1;
	}
					// Set number of neuron unit
	npo_unit.num = out_max;

					// Create Synapses

	ret = create_synapse( npi_unit.p, in_max, nph_unit.p, m_max );
					// for between input and hidden pahses
	if( ret == NULL ){
		return -1;
	}

	ret = create_synapse( nph_unit.p,  m_max, npo_unit.p, out_max );
					// for between hidden and output phases
	if( ret == NULL ){
		return -1;
	}
					// Set to pointer array
	n[0] = &npi_unit;
	n[1] = &nph_unit;
	n[2] = &npo_unit;
					// Initialize
	init_rand();

	if( result_no < 0 ){
					// Case of initialize

					// Initialize neuron for backpropagetion
		init_bp( &npi_unit,      0,   m_max, RESET );
		init_bp( &nph_unit, in_max, out_max, RESET );
		init_bp( &npo_unit,  m_max,       0, RESET );

					// Make init data filename
		sprintf( file_name, "%s", init_file );

					// Open init data file
		fp = gzopen( file_name, "wb6f" );
		if( fp == NULL ){
			printf("Can't open a initial file.\n" );
			return -1;
		}
					// Save initialized neuron parameter
		err = save_neuron_z( fp, &npi_unit );
		if( err != 0 ){
			printf("Can not save a input neuron");
			printf(" parameter at (%ld).\n",err);

			return -1;
		}

		err = save_neuron_z( fp, &nph_unit );
		if( err != 0 ){
			printf("Can not save a hidden neuron");
			printf(" parameter at (%ld).\n",err);

			return -1;
		}

		err = save_neuron_z( fp, &npo_unit );
		if( err != 0 ){
			printf("Can not save a output neuron");
			printf(" parameter at (%ld).\n",err);

			return -1;
		}

		gzclose( fp );
					// Normal Terminate
		return 0;

	}else{
					// Case of learning ro detect

					// Make init data filename
		sprintf( file_name, "%s", init_file );

					// Open init data file
		fp = gzopen( file_name, "rb6f" );
		if( fp == NULL ){
			printf("Can't open a initial file.\n");
			return -1;
		}

					// Load initialized neuron parameter
		err = load_neuron_z( fp, &npi_unit );
		if( err != 0 ){
			printf("Can not load a input neuron");
			printf(" parameter at (%ld).\n",err);

			return -1;
		}

		err = load_neuron_z( fp, &nph_unit );
		if( err != 0 ){
			printf("Can not load a hidden neuron");
			printf(" parameter at (%ld).\n",err);

			return -1;
		}

		err = load_neuron_z( fp, &npo_unit );
		if( err != 0 ){
			printf("Can not load an output neuron");
			printf(" parameter at (%ld).\n",err);

			return -1;
		}

					// Close
		gzclose( fp );

		//init_bp( &npi_unit,      0,   m_max, NON_RESET );
		//init_bp( &nph_unit, in_max, out_max, NON_RESET );
		//init_bp( &npo_unit,  m_max,       0, NON_RESET );
	}

					// Learning by Backpropagation
	if( learn_times == 0 ){
					// Case of detect mode
		learn_flg   = 0;
		learn_times = 1;
	}else{
					// Case of learning mode
		learn_flg = 1;
	}

	if( stream_mode != 1 ){
					// Not stream mode
		learn_cnt = 0;

		for( cnt = 0; cnt < teach_row_num * learn_times; cnt++ ){

					// Set Learning data

			for( data_cnt = 0; data_cnt < in_max; data_cnt++ ){

				npi_unit.p[data_cnt].z
					= in_data[in_max * learn_cnt +  data_cnt];
			}
					// Set Teach data

			for( teach_cnt = 0; teach_cnt < out_max; teach_cnt++ ){

				t[teach_cnt]
					= teach[out_max * learn_cnt + teach_cnt];
			}
					// Case of not learning mode
			if( learn_flg == 0 ){ 

				for( phase = 1; phase < 3; phase++ ){

					calc_forward(
						n,
						phase,
						n[phase-1]->num,
						n[phase]->num
					);
				}

				output( in_data, n, t, learn_cnt, in_max );
				learn_cnt++;

				continue;
			}else{
					// Case of learning mode
				learn_bp( &n, 3, &t );
				learn_cnt++;
			}

			if( learn_cnt >= teach_row_num ){

					// Reset learning count
				learn_cnt = 0;

					// Test calculation for debug

				for( data_cnt = 0; data_cnt < in_max; data_cnt++ ){

					// Set input data

					npi_unit.p[data_cnt].z
						= in_data[in_max
						* learn_cnt
						+ data_cnt];
				}

				for(	teach_cnt = 0;
					teach_cnt < out_max;
					teach_cnt++
				){
					// Set teach data

					t[teach_cnt]
						= teach[out_max
						* learn_cnt
						+ teach_cnt];
				}

				for( phase = 1; phase < 3; phase++ ){

					// Calculate to forward

					calc_forward(
						n,
						phase,
						n[phase-1]->num,
						n[phase]->num
					);
				}

					// Output for debug

				output( in_data, n, t, data_row_num - 1, in_max );
			}
		}
	}
					// Initialize stream mode
	data = NULL;
	buff = NULL;

	if( stream_mode == 1 ){
					// Memory allocate for data and buffer
		data = (double *)malloc( sizeof(double) * in_max );
		buff = (double *)malloc( sizeof(double) * in_max );
	
					// Initialize allocated memory
		memset( data, 0, sizeof( double ) * in_max );
		memset( buff, 0, sizeof( double ) * in_max );

					// Init flag and counter
		eof_flg = 0;
		learn_cnt = 0;
	}
					// Loop of stream mode
	while( stream_mode == 1 && eof_flg != 1 ){
					// Case of a first time
		if( learn_cnt == 0 ){
					// Get a data for an input units

			for(	data_cnt = 0;
				data_cnt < in_max - (unit_num * interval);
				data_cnt++
			){
					// Get a comma separated values

				for(	val_cnt = 0;
					val_cnt < digit_num;
					val_cnt++
				){
					// Get a character
					val[val_cnt] = fgetc( stdin );

					// Case of EOF
					if( val[val_cnt] == EOF ){

						eof_flg = 1;
						break;

					// Case of comma
					}else if( val[val_cnt] == ',' ){

						break;
					}
				}
					// Set a NULL
				val[val_cnt] = '\0';

					// Transfer double from char
				data[data_cnt] = atof( val );
			}
					// Set an initial counter
			learn_cnt = 1;

			printf("UNIT_NUM * interval = %ld\n",unit_num * interval);
			printf("interval: %ld\n", interval);
			printf("in_max: %ld\n", in_max);
			fflush( stdout );

					// Prepare a first procedure
			memcpy( &buff[unit_num * interval], &data[0],
				sizeof( double ) * (in_max - (unit_num * interval))
			);
		}

					// Copy a data of latter half
		memcpy( &data[0], &buff[unit_num * interval],
			sizeof( double ) * (in_max - (unit_num * interval)) );

					// Get a data for an input units
		for(	unit_cnt = 0;
			unit_cnt < (unit_num * interval);
			unit_cnt++
		){
					// Get a comma separated values
			for( val_cnt = 0; val_cnt < digit_num; val_cnt++ ){

					// Get a comma separated values
				val[val_cnt] = fgetc( stdin );

					// Case of EOF
				if( val[val_cnt] == EOF ){

					eof_flg = 1;
					break;

					// Case of comma
				}else if( val[val_cnt] == ',' ){

					break;
				}
			}
					// Set a NULL
			val[val_cnt] = '\0';

					// Case of reset
			if( strcmp( val, "RESET" ) == 0 ){

					// Counter reset
				learn_cnt = 0;
				 unit_cnt = 0;

					// Break of procedure
				break;
			}
					// Transfer double from char
			data[in_max - (unit_num * interval) + unit_cnt]
				= atof( val );
		}

		if( learn_cnt == 0 ){
					// Case of reset
			continue;
		}
					// Store data
		memcpy( &buff[0], &data[0], sizeof( double ) * in_max );

					// Set a Learning data and a Teach data

		for( data_cnt = 0; data_cnt < in_max; data_cnt++ ){

			npi_unit.p[data_cnt].z = data[data_cnt];
			//	=  data[in_max * learn_cnt +  data_cnt];
		}

		if( learn_flg == 0 ){
					// Case of detect

			for( phase = 1; phase < 3; phase++ ){

				calc_forward(
					n,
					phase,
					n[phase-1]->num,
					n[phase]->num
				);
			}
					// Set dummy teach data
			t[0] = -1;
			t[1] = -1;
					// Output a result
			output( data, n, t, learn_cnt, in_max );

			learn_cnt += interval;

			continue;
		}else{
					// Case of learning

					// Search and get a teach data
			ret_p = get_teach_data(
				teach,
				teach_row_num,
				out_max,
				learn_cnt,
				(in_max / unit_num),
				t
			);
					// Case of not found
			if( ret_p == NULL ){
				t[0] = -1;
				t[1] = -1;
			}

			printf("%ld,%f,%f\n",learn_cnt,t[0],t[1]);

			if( ret_p != NULL ){

				learn_bp( &n, 3, &t );
			}

			learn_cnt += interval;
		}

		/*
					// A test calculation for debug

		if( learn_cnt >= teach_row_num ){

			learn_cnt = 0;
					// Reset learning count

			for( data_cnt = 0; data_cnt < in_max; data_cnt++ ){

					// Prepare an input data

				npi_unit.p[data_cnt].z
					=  data[in_max * learn_cnt +  data_cnt];
			}

			for( teach_cnt = 0; teach_cnt < out_max; teach_cnt++ ){

					// Prepare a teach data

				t[teach_cnt]
					= teach[(out_max + 2)
					* learn_cnt + teach_cnt + 2];
			}

			for( phase = 1; phase < 3; phase++ ){

					// Detect
				calc_forward(
					n,
					phase,
					n[phase-1]->num,
					n[phase]->num
				);
			}
			output( data, n, t, data_row_num - 1, in_max );
		}
		*/

		cnt++;
	}

	if( learn_flg == 1 ){
					// Make a result filename
		sprintf( file_name, "%s%03ld%s", RESULT_FILE, result_no, SUFFIX );

					// Open a result file
		fp = gzopen( file_name, "wb6f" );
		if( fp == NULL ){
			printf("Can't open a result file.[%s]\n", file_name );
		}
					// Save a calculated neuron parameters
		err = save_neuron_z( fp, &npi_unit );
		if( err != 0 ){
			printf("Can not save a input neuron");
			printf(" parameter at (%ld).\n",err);

			return -1;
		}

		err = save_neuron_z( fp, &nph_unit );
		if( err != 0 ){
			printf("Can not save a hidden neuron");
			printf(" parameter at (%ld).\n",err);

			return -1;
		}

		err = save_neuron_z( fp, &npo_unit );
		if( err != 0 ){
			printf("Can not save a output neuron");
			printf(" parameter at (%ld).\n",err);

			return -1;
		}
					// Close
			gzclose( fp );
	}

					// Free neurons
	for( cnt = 0; cnt < in_max; cnt++ ){

		(npi_unit.p [cnt].free)( &npi_unit.p[cnt] );
	}

	for( cnt = 0; cnt < m_max; cnt++ ){

		(nph_unit.p [cnt].free)( &nph_unit.p[cnt] );
	}

	for( cnt = 0; cnt < out_max; cnt++ ){

		(npo_unit.p [cnt].free)( &nph_unit.p[cnt] );
	}

	if( data != NULL ){
		free( data );
		data = NULL;
	}

	if( buff != NULL ){
		free( buff );
		buff = NULL;
	}
					// Normal Terminate
	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : A Function of print-out answers                                   */
/* Function Name : print_out()                                                */
/*                                                                            */
/* Detail : Pirnt-out answers                                                 */
/* Date   : 2015.06.25                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : void                                                              */
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

int output(
	double *data,
	NEURON_P **np,
	double *t,
	long learn_cnt,
	long in_max
){
					// Counter of amino
		long amino_cnt;
					// Value of amino acid
		long amino_acid;
					// Number of amino acid
		long amino_acid_no;
					// String of amino acid
		char amino_acid_str[40];
					// General purpose counter
		int cnt;
					// Pointer of neuron
		NEURON_T **n;
					// Instance of neuron
		n = (NEURON_T **)malloc( sizeof(NEURON_T **) * (2+1) );

		//NEURON_T *n[10];
					// Set a pointer of each phases
		n[0] = np[0]->p;
		n[1] = np[1]->p;
		n[2] = np[2]->p;

					// No.
		printf( "%ld,  ", learn_cnt );

		/*
					// Number of an input phase
		printf( "%02ld,  %.0f,%.0f,%.0f,%.0f,%.0f,%.0f, ",
			learn_cnt,

			data[learn_cnt][0],
			data[learn_cnt][1],
			data[learn_cnt][2],
			data[learn_cnt][3],
			data[learn_cnt][4],
			data[learn_cnt][5]
		);
					// Dealing with amino acid
		for( cnt = 0; cnt < in_max; cnt += 4 ){

			if( data[in_max * learn_cnt + cnt+0] == 1 ){

				printf("A,");

				continue;
			}

			if( data[in_max * learn_cnt + cnt+1] == 1 ){

				printf("T,");

				continue;
			}

			if( data[in_max * learn_cnt + cnt+2] == 1 ){

				printf("G,");

				continue;
			}

			if( data[in_max * learn_cnt + cnt+3] == 1 ){

				printf("C,");

				continue;
			}

			printf("X,");
		}
		*/

		/*
					// Number of an output of input phase
		printf( "  %.0f,%.0f,%.0f,%.0f,%.0f,%.0f,",

			n[0][0].z,
			n[0][1].z,
			n[0][2].z,
			n[0][3].z,
			n[0][4].z,
			n[0][5].z
		);
		*/

		/*
					// Number of a teach data
		printf( "  %.0f,%.0f,",

			t[0],
			t[1]
		);
		*/
					// Number of an output phase
		printf( "  %.12f,%.12f",

			n[2][0].z,
			n[2][1].z
		);

		printf("\n");

		if( n != NULL ){
					// Free memorys
			free(n);
		}

		fflush( stdout );
}

int print_out(
	NEURON_T *nv_unit,
	NEURON_T *nh_unit,
	NEURON_T *nv_data,
	NEURON_T *nh_data,
	NEURON_T *nv_model,
	NEURON_T *nh_model,
	long v_num,
	long h_num
){

	long cnt;
	long v_cnt;
	long h_cnt;
	double mean;
	double min;
	double max;
					// Print-out a and w of visible side
	printf("nv_unit[no],a,w1,w2,,,\n");

	mean = 0;

	for( v_cnt = 0; v_cnt < v_num; v_cnt++ ){
		for( h_cnt = 0; h_cnt < h_num; h_cnt++ ){
			mean += nv_unit[v_cnt].wf[v_cnt][h_cnt];
		}
	}

	mean /= (double)(v_num * h_num);

	for( v_cnt = 0; v_cnt < v_num; v_cnt++ ){

		printf("%ld,%f\n",
			v_cnt, *(nv_unit[v_cnt].a)
		);

		for( h_cnt = 0; h_cnt < h_num; h_cnt++ ){

			printf("%.1f",nv_unit[v_cnt].wf[v_cnt][h_cnt]-mean);

			if( fmod((double)h_cnt+1,5) == 0 ){
				printf("\n");
			}else{
				printf(",");
			}
		}

		printf("\n");
	}

	printf("\n");
					// Print-out b and w of hidden side
	printf("nh_unit[no],b,w1,w2,,,\n");

	mean = 0;

	for( h_cnt = 0; h_cnt < h_num; h_cnt++ ){
		for( v_cnt = 0; v_cnt < v_num; v_cnt++ ){
			mean += nh_unit[h_cnt].wb[v_cnt][h_cnt];
		}
	}

	mean /= (double)(h_num * v_num);

	for( h_cnt = 0; h_cnt < h_num; h_cnt++ ){

		printf("%ld,%f\n",
			h_cnt, *(nh_unit[h_cnt].b)
		);

		for( v_cnt = 0; v_cnt < v_num; v_cnt++ ){

			printf("%.1f",nh_unit[h_cnt].wb[v_cnt][h_cnt]-mean);

			if( fmod((double)v_cnt+1,5) == 0 ){
				printf("\n");
			}else{
				printf(",");
			}
		}

		printf("\n");
	}

	printf("\n");
					// Calculate Mean of h
	mean = 0;
	max = nh_unit[0].u;
	min = nh_unit[0].u;

	for( h_cnt = 0; h_cnt < h_num; h_cnt++ ){

		mean += nh_unit[h_cnt].u;

		if( max < nh_unit[h_cnt].u ){
			max = nh_unit[h_cnt].u;
		}

		if( min > nh_unit[h_cnt].u ){
			min = nh_unit[h_cnt].u;
		}
	}

	mean /= (double)h_num;
					// Value of hidden unit

	for( h_cnt = 0; h_cnt < h_num; h_cnt++ ){

		printf("h_unit[%ld],%.6f\n",
			h_cnt,
			(nh_unit[h_cnt].u - min) / (max - min)
		);
	}

	printf("\n");
					// Calculate Mean of v
	mean = 0;
	max = nv_unit[0].u;
	min = nv_unit[0].u;

	for( v_cnt = 0; v_cnt < v_num; v_cnt++ ){

		mean += nv_unit[v_cnt].u;

		if( max < nv_unit[v_cnt].u ){
			max = nv_unit[v_cnt].u;
		}

		if( min > nv_unit[v_cnt].u ){
			min = nv_unit[v_cnt].u;
		}
	}

	mean /= (double)v_num;
					// Print-out visible values

	for( v_cnt = 0; v_cnt < v_num; v_cnt++ ){

		printf("v_unit[%ld],%.6f\n",
			v_cnt,
			(nv_unit[v_cnt].u - min) / (max - min)
		);
	}

	return 0;
}
