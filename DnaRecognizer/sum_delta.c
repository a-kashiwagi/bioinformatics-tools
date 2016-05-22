/******************************************************************************/
/*                                                                            */
/* Title  : Summary an each delta values in minibatch files                   */
/* Program Name : sum_delta.c                                                 */
/*                                                                            */
/* Detail : Summary an each delta values in minibach files                    */
/* Date   : 2015.11.03                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Copyright(c)2015 Akihiro Kashiwagi All Right Reserved                      */
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

//#include "dnn.h"

#include "dnn_lib.h"
#include "neuron.h"
#include "bp_lib.h"
					// For case of use Xeon Phi
//#include "dnn_lib_mic.h"
//#include "neuron_mic.h"
//#include "bp_lib_mic.h"
					// Default unit number
#define  IN_MAX 48
#define   M_MAX 12
#define OUT_MAX 2
					// Phase Number
#define  IN_PHASE 0
#define   M_PHASE 1
#define OUT_PHASE 2
					// Parameter of DNN
#define ETA 0.01
#define PERSISTENT_T 1
#define EPSILON 0.0000001
					// Buffer size
#define BUFFSIZE 1024000
					// Structure of sum delta
int sum_delta(
	  long  in_max,
	  long   m_max,
	  long out_max,
	  char *init_file,
	  long    data_row_num,
	  char *result_file,
	  long    teach_row_num,
	  long    learn_times,
	  long	  result_max
);

/*
__declspec( target(mic) ) int dna_recognize(
	  long  in_max,
	  long   m_max,
	  long out_max,
	  double *data_arr,
	  long    data_row_num,
	  double *teach_arr,
	  long    teach_row_num,
	  long    learn_times
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
/* Title  : Summary an each delta values in minibatch files                   */
/* Function Name : main()                                                     */
/*                                                                            */
/* Detail : Summary an each delta values in minibatch files                   */
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

					// For Arguments
	long learn_times;
					// Number of a learn times
	char unit_num[1024];
					// Number of a neuron unit
	char init_file[1024];
					// Name of learning data file name
	long data_row_num;
					// Number of row of learning data
	char result_file[1024];
					// Name of teach data file name
	long teach_row_num;
					// Number of row of teach data
	long result_max;
					// Number of neurons
	long  in_max;
	long   m_max;
	long out_max;

	if( argc < 7 ){
					// Check for arguments number
		exit(-1);
	}
					// Get a learn times
	learn_times = atol( argv[1] );

					// Get a unit number
	strncpy( unit_num, argv[2], 1024 );
	in_max = atol( unit_num );
					// Set a number of hidden unit
	m_max = (long)floor( ((double)in_max + 0.5) / 2);
	// m_max = (long)floor( ((double)in_max + 1) * 2);

					// Get a learning data file name
	strncpy(  init_file, argv[3], 1024 );
					// Get a number of row of learning data
	data_row_num = atol( argv[4] );

					// Get a teach data file name
	strncpy( result_file, argv[5], 1024 );
					// Get a number of row of teach data
	teach_row_num = atol( argv[6] );

	result_max = atol( argv[7] );
					// Set a number of output unit
	out_max = OUT_MAX;
					// Call dna_recognize function
	//omp_set_num_threads_target(TARGET_MIC,0,60);
	//#pragma offload target(mic) \
	//in(  data: length(  data_row_num *  in_max )) \
	//in( teach: length( teach_row_num * out_max ))
	ret = sum_delta(
		 in_max,
		  m_max,
		out_max,
		init_file,
		 data_row_num,
		result_file,
		 teach_row_num,
		learn_times,
		result_max
	);
					// Free memorys
	free( data  );
	free( teach );

	exit(0);
}

/******************************************************************************/
/*                                                                            */
/* Title  : A Function of calculate a sum of delta                            */
/* Function Name : sum_delta()                                                */
/*                                                                            */
/* Detail : A calculate a sum of delta from inital file and result file       */
/* Date   : 2015.12.10                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long    in_max      : Number of neuron unit of  input phase       */
/*        : long     m_max      : Number of neuron unit of hidden phase       */
/*        : long   out_max      : Number of neuron unit of output phase       */
/*        : char *init_file     : Init file name                              */
/*        : long data_row_num   : Number of row of input learn data           */
/*        : char *result_file   : Result file name                            */
/*        : long  teach_row_num : Number of row of input teach data           */
/*        : long  result_max    : Number of result file (Number of split)     */
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

int sum_delta(
	long   in_max,
	long    m_max,
	long  out_max,
	char *init_file,
	long  data_row_num,
	char *result_file,
	long  teach_row_num,
	long  learn_times,
	long  result_max
){
					// Phase 01(init)
	NEURON_P init_npi_unit;
					// Phase 02(init)
	NEURON_P init_nph_unit;
					// Phase 03(init)
	NEURON_P init_npo_unit;

					// Phase 01(result)
	NEURON_P result_npi_unit;
					// Phase 02(result)
	NEURON_P result_nph_unit;
					// Phase 03(result)
	NEURON_P result_npo_unit;

					// Phase 01(result)
	NEURON_P calc_npi_unit;
					// Phase 02(result)
	NEURON_P calc_nph_unit;
					// Phase 03(result)
	NEURON_P calc_npo_unit;
					// Counter
	long cnt;
					// Retern value for create_synapse
	double **ret;
					// File pointer
	FILE *fp;
					// Counters
	long  n_cnt;
	long wf_cnt;
	long wb_cnt;
	long    num;
	long wf_num;
	long wb_num;
					// Buffer of filename
	char file_name[1024];
					// Create Neurons

	init_npi_unit.p   = create_neuron(  in_max, 0 );
					// for input phase
	if( init_npi_unit.p == NULL ){
		return -1;
	}
					// Set number of neuron unit
	init_npi_unit.num =  in_max;

	init_nph_unit.p   = create_neuron(   m_max, 0 );
					// for hidden phase
	if( init_nph_unit.p == NULL ){
		return -1;
	}
					// Set number of neuron unit
	init_nph_unit.num =   m_max;

	init_npo_unit.p   = create_neuron( out_max, 0 );
					// for output phase
	if( init_npo_unit.p == NULL ){
		return -1;
	}
					// Set number of neuron unit
	init_npo_unit.num = out_max;

					// Create Synapses

	ret = create_synapse( init_npi_unit.p, in_max, init_nph_unit.p, m_max );
					// for between input and hidden pahses
	if( ret == NULL ){
		return -1;
	}

	ret = create_synapse( init_nph_unit.p,  m_max, init_npo_unit.p, out_max );
					// for between hidden and output phases
	if( ret == NULL ){
		return -1;
	}

					// Initialize
	init_rand();

	fp = fopen( init_file, "r" );
	if( fp == NULL ){
		printf("Can't open a initial file.\n" );
	}
					// Load init data
	load_neuron( fp, &init_npi_unit );
	load_neuron( fp, &init_nph_unit );
	load_neuron( fp, &init_npo_unit );

	fclose( fp );
					// Create Neurons

	result_npi_unit.p   = create_neuron(  in_max, 0 );
					// for input phase
	if( result_npi_unit.p == NULL ){
		return -1;
	}
					// Set number of neuron unit
	result_npi_unit.num =  in_max;

	result_nph_unit.p   = create_neuron(   m_max, 0 );
					// for hidden phase
	if( result_nph_unit.p == NULL ){
		return -1;
	}
					// Set number of neuron unit
	result_nph_unit.num =   m_max;

	result_npo_unit.p   = create_neuron( out_max, 0 );
					// for output phase
	if( result_npo_unit.p == NULL ){
		return -1;
	}
					// Set number of neuron unit
	result_npo_unit.num = out_max;

					// Create Synapses

	ret = create_synapse( result_npi_unit.p, in_max, result_nph_unit.p, m_max );
					// for between input and hidden pahses
	if( ret == NULL ){
		return -1;
	}

	ret = create_synapse( result_nph_unit.p,  m_max, result_npo_unit.p, out_max );
					// for between hidden and output phases
	if( ret == NULL ){
		return -1;
	}

					// Create Neurons

	calc_npi_unit.p   = create_neuron(  in_max, 0 );
					// for input phase
	if( calc_npi_unit.p == NULL ){
		return -1;
	}
					// Set number of neuron unit
	calc_npi_unit.num =  in_max;

	calc_nph_unit.p   = create_neuron(   m_max, 0 );
					// for hidden phase
	if( calc_nph_unit.p == NULL ){
		return -1;
	}
					// Set number of neuron unit
	calc_nph_unit.num =   m_max;

	calc_npo_unit.p   = create_neuron( out_max, 0 );
					// for output phase
	if( calc_npo_unit.p == NULL ){
		return -1;
	}
					// Set number of neuron unit
	calc_npo_unit.num = out_max;

					// Create Synapses

	ret = create_synapse( calc_npi_unit.p, in_max, calc_nph_unit.p, m_max );
					// for between input and hidden pahses
	if( ret == NULL ){
		return -1;
	}

	ret = create_synapse( calc_nph_unit.p,  m_max, calc_npo_unit.p, out_max );
					// for between hidden and output phases
	if( ret == NULL ){
		return -1;
	}

					// Loop of each result files
	for( cnt = 0; cnt < result_max; cnt++ ){

		sprintf( file_name, "%s%03ld.dat", result_file, cnt );

		fp = fopen( file_name, "r" );
		if( fp == NULL ){
			printf("Can't open a result file.[%s]\n", file_name );
		}
					// Load result file
		load_neuron( fp, &result_npi_unit );
		load_neuron( fp, &result_nph_unit );
		load_neuron( fp, &result_npo_unit );

		fclose( fp );
					// Set number of wb units
		wb_num = init_npi_unit.num;
		   num = init_nph_unit.num;

					// Summary Δw(for backward) values
		for( wb_cnt = 0; wb_cnt < wb_num; wb_cnt++ ){

			for( n_cnt = 0; n_cnt < num; n_cnt++ ){

				if( cnt == 0 ){
					  calc_nph_unit.p[n_cnt].wb[wb_cnt][n_cnt] = 0;
				}

				// Calculate Δw(for backward)
				//     of input to hidden phase

				  calc_nph_unit.p[n_cnt].wb[wb_cnt][n_cnt] +=
				result_nph_unit.p[n_cnt].wb[wb_cnt][n_cnt] -
				  init_nph_unit.p[n_cnt].wb[wb_cnt][n_cnt];

				if( cnt == result_max - 1 ){
					result_nph_unit.p[n_cnt].wb[wb_cnt][n_cnt]
					= init_nph_unit.p[n_cnt].wb[wb_cnt][n_cnt]
					+ calc_nph_unit.p[n_cnt].wb[wb_cnt][n_cnt];
				}
			}
		}
					// Set number of b units
		num = init_nph_unit.num;

					// Summary Δb(for hidden phase) values
		for( n_cnt = 0; n_cnt < num; n_cnt++ ){

			if( cnt == 0 ){
				*(calc_nph_unit.p[n_cnt].b) = 0;
			}

					// Calculate Δb(for hidden phase)

			*(  calc_nph_unit.p[n_cnt].b) +=
			*(result_nph_unit.p[n_cnt].b) -
			*(  init_nph_unit.p[n_cnt].b);

			if( cnt == result_max - 1 ){
				*(result_nph_unit.p[n_cnt].b)
				= *(init_nph_unit.p[n_cnt].b)
				+ *(calc_nph_unit.p[n_cnt].b);
			}
		}
					// Set number of wf units
		wf_num = init_npo_unit.num;
		   num = init_nph_unit.num;

					// Summary Δw(for forward) values
		for( n_cnt = 0; n_cnt < num; n_cnt++ ){

			for( wf_cnt = 0; wf_cnt < wf_num; wf_cnt++ ){

				if( cnt == 0 ){
					  calc_nph_unit.p[n_cnt].wf[n_cnt][wf_cnt] = 0;
				}

				// Calculate Δw(for forward)

				  calc_nph_unit.p[n_cnt].wf[n_cnt][wf_cnt] +=
				result_nph_unit.p[n_cnt].wf[n_cnt][wf_cnt] -
				  init_nph_unit.p[n_cnt].wf[n_cnt][wf_cnt];

				if( cnt == result_max - 1 ){
					result_nph_unit.p[n_cnt].wf[n_cnt][wf_cnt]
					= init_nph_unit.p[n_cnt].wf[n_cnt][wf_cnt]
					+ calc_nph_unit.p[n_cnt].wf[n_cnt][wf_cnt];
				}
			}
		}
					// Set number of delta b units
		num = init_npo_unit.num;

					// Summary Δb values
		for( n_cnt = 0; n_cnt < num; n_cnt++ ){

			if( cnt == 0 ){
				*(calc_npo_unit.p[n_cnt].b) = 0;
			}

				// Calculate Δb(for input phase)

			*(  calc_npo_unit.p[n_cnt].b) +=
			*(result_npo_unit.p[n_cnt].b) -
			*(  init_npo_unit.p[n_cnt].b);

			if( cnt == result_max - 1 ){
				*(result_npo_unit.p[n_cnt].b)
				= *(init_npo_unit.p[n_cnt].b)
				+ *(calc_npo_unit.p[n_cnt].b);
			}
		}
	}
					// Output result data
	fp = fopen( "delta_minibatch.dat", "w" );
	if( fp == NULL ){
		printf("Can't open a delta file for write.\n" );
	}
					// Save delta values
	save_neuron( fp, &calc_npi_unit );
	save_neuron( fp, &calc_nph_unit );
	save_neuron( fp, &calc_npo_unit );

	fclose( fp );

	fp = fopen( "sum_minibatch.dat", "w" );
	if( fp == NULL ){
		printf("Can't open a sum file for write.\n" );
	}
					// Save summary values
	save_neuron( fp, &result_npi_unit );
	save_neuron( fp, &result_nph_unit );
	save_neuron( fp, &result_npo_unit );

	fclose( fp );
					// Free neurons
	for( cnt = 0; cnt < in_max; cnt++ ){

		(  init_npi_unit.p [cnt].free)(   &init_npi_unit.p[cnt] );
		(result_npi_unit.p [cnt].free)( &result_npi_unit.p[cnt] );
	}

	for( cnt = 0; cnt < m_max; cnt++ ){

		(  init_nph_unit.p [cnt].free)(   &init_nph_unit.p[cnt] );
		(result_nph_unit.p [cnt].free)( &result_nph_unit.p[cnt] );
	}

	for( cnt = 0; cnt < out_max; cnt++ ){

		(  init_npo_unit.p [cnt].free)(   &init_nph_unit.p[cnt] );
		(result_npo_unit.p [cnt].free)( &result_nph_unit.p[cnt] );
	}

	return 0;
}
