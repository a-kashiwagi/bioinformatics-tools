/******************************************************************************/
/*                                                                            */
/* Title  : A Library of Backpropagation                                      */
/* Program Name : bp_lib.c                                                    */
/*                                                                            */
/* Detail : Calculate a Backpropagation algorism for neural network           */
/* Date   : 2015.10.06                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Computations were partially performed on the NIG supercomputer             */
/* at ROIS National Institute of Genetics.                                    */
/*                                                                            */
/* Copyright(c)2015 Akihiro Kashiwagi All Rights Reserved                     */
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

					// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

#include "dnn_lib.h"
#include "bp_lib.h"
#include "neuron.h"

/******************************************************************************/
/*                                                                            */
/* Title  : Calculate Forward Algorism functions                              */
/* Function Name :calc_forward()                                              */
/*                                                                            */
/* Detail : Calculate Forward Algorism                                        */
/* Date   : 2015.07.23                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : NEURON_P **np : Double Pointer of unit                            */
/*        : long phase    : Number of current phase                           */
/*        : long  in_num  : Number of  input( left side) neurons              */
/*        : long out_num  : Number of output(right side) neurons              */
/*                                                                            */
/* Output : int : Normal Terminate : 0                                        */
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

int calc_forward( NEURON_P **np, long phase, long in_num, long out_num ){

						// Counter for loop i,j
	long i;
	long j;
						// Weight for link
	double w;
						// Activated value
	double z;
						// Summary
	double sum;

	NEURON_T *n_fwd;
	NEURON_T *n_cur;
	NEURON_T *n_bak;

	NEURON_T **n;
	long len;

	len = sizeof( NEURON_T **) * (phase + 1);
	n = (NEURON_T **)malloc( sizeof( NEURON_T **) * (phase + 1) );

	n[phase  ] = np[phase  ]->p;
	n[phase-1] = np[phase-1]->p;
						// Loop without bias(w0j)
	#pragma omp parallel for reduction(+:sum) private(i,w,z)
	for( j = 0; j < out_num; j++ ){

				// \[ u_j = \sum^N_{i = 0} w_{ij} + b_j \]

						// Initialize
		sum = 0;
						// Loop with bias(w0j)
		for( i = 0; i < in_num; i++ ){

						// Weight of i to j
			w = n[phase  ][j].wb[i][j];

						// Output of side of i
			z = n[phase-1][i].z;
						// Summary
			sum += w * z;
		}
						// Add bias
		sum += *(n[phase][j].b);
						// Value of inside
		n[phase][j].u = sum - THETA;
						// Activated value z
		n[phase][j].z = sigmoid( n[phase][j].u );
	}

	free(n);
						// Normal terminate
	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Calculate Delta of output phase functions                         */
/* Function Name :calc_delta_of_out()                                         */
/*                                                                            */
/* Detail : Calculate delta for output phase                                  */
/* Date   : 2015.07.23                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : NEURON_P **np : Double Pointer of unit                            */
/*        : long phase    : Number of current phase                           */
/*        : long out_num  : Number of output(right side) neurons              */
/*        : long *teach   : Data of teaching                                  */
/*                                                                            */
/* Output : int : Normal Terminate : 0                                        */
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

int calc_delta_of_out( NEURON_P **np, long phase, long out_num, double *teach ){

	long j;
	NEURON_T **n;
	long len;

	len = sizeof( NEURON_T **) * (phase + 1);
	n = (NEURON_T **)malloc( sizeof( NEURON_T **) * (phase + 1) );

	n[phase  ] = np[phase  ]->p;
					// \[ d_j^{Phase} = z_j^{Phase}-t_j \]
	#pragma omp parallel for
	for( j = 0; j < out_num; j++ ){

						// Difference from teach value
		n[phase][j].d = n[phase][j].z - teach[j];
	}

	free(n);
						// Normal terminate
	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Calculate Delta(without output phase) functions                   */
/* Function Name :calc_delta()                                                */
/*                                                                            */
/* Detail : Calculate delta                                                   */
/* Date   : 2015.07.23                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : NEURON_P **np : Double Pointer of unit                            */
/*        : long phase    : Number of current phase                           */
/*        : long  in_num  : Number of  input( left side) neurons              */
/*        : long out_num  : Number of output(right side) neurons              */
/*                                                                            */
/* Output : int : Normal Terminate : 0                                        */
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

int calc_delta( NEURON_P **np, long phase, long in_num, long out_num ){

						// Counter for loop i,j
	long j;
	long k;
						// Weight for link
	double w;
						// Bias b
	double b;
						// Difference value
	double d;
						// Differented sigmoid
	double ff;
						// Summary
	double sum;

	NEURON_T **n;
	long len;

	len = sizeof( NEURON_T **) * (phase + 2);
	n = (NEURON_T **)malloc( sizeof( NEURON_T **) * (phase + 2) );

	n[phase+1] = np[phase+1]->p;
	n[phase  ] = np[phase  ]->p;
						// Loop without bias(w0j)
	#pragma omp parallel for private(ff,k,w,d,b)
	for( j = 0; j < in_num; j++ ){

			// \[ d_j^{Phase} = \sum_{kj}^{Phase}
			//    d_k^{Phase+1} w_{kj}^{Phase+1} f'(u_j) \]

						// Initialize
		sum = 0;
						// Loop without bias(w0j)

						// Differented activated u
		ff = differented_sigmoid( n[phase][j].u );

		for( k = 0; k < out_num; k++ ){
						// Weight of j to k
			w = n[phase+1][k].wb[j][k];

						// Difference value
			d = n[phase+1][k].d;

						// Summary
			sum += d * w * ff;
		}
						// Set to side of j
		n[phase][j].d = sum;
						// Bias b

			// \[ db_j^{Phase} = 
			//    d_j^{Phase} db_j^{Phase} f'(u_j) \]

		 b = *(n[phase][j].b);

		 d =   n[phase][j].db;

		//ff = differented_sigmoid( n[phase][j].u );

		n[phase][j].db = d * b * ff;
	}

	free(n);
						// Normal terminate
	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Calculate Δw functions                                            */
/* Function Name :calc_delta_w()                                              */
/*                                                                            */
/* Detail : Calculate Δw                                                      */
/* Date   : 2015.07.23                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : NEURON_P **np : Double Pointer of unit                            */
/*        : long phase    : Number of current phase                           */
/*        : long  in_num  : Number of  input( left side) neurons              */
/*        : long out_num  : Number of output(right side) neurons              */
/*                                                                            */
/* Output : int : Normal Terminate : 0                                        */
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

int calc_delta_w( NEURON_P **np, long phase, long in_num, long out_num ){

						// Counter for loop i,j
	long i;
	long j;
						// Difference value
	double d;
						// Activated value
	double z;
						// Difference for w
	double dw;

	NEURON_T **n;
	long len;

	len = sizeof( NEURON_T **) * (phase + 1);
	n = (NEURON_T **)malloc( sizeof( NEURON_T **) * (phase + 1) );

	n[phase  ] = np[phase  ]->p;
	n[phase-1] = np[phase-1]->p;
						// Loop without bias(w0j)
	#pragma omp parallel for private(i,d,z,dw)
	for( j = 0; j < out_num; j++ ){

					// \[ w_{ij} = w_{ij} \eta
					//    d_j^{Phase} z_i^{Phase-1} \]

						// Loop without bias(w0j)
		for( i = 0; i < in_num; i++ ){
						// Difference value of j
			d = n[phase  ][j].d;
						// Activated value of i
			z = n[phase-1][i].z;
						// Difference for w
			dw = d * z;
						// Set to w
			n[phase][j].wb[i][j] -= dw * ETA;

					// \[ w_{ij} = w_{ij} - \delta w_{ij} \]
		}

		*(n[phase][j].b) -= n[phase][j].db * ETA;
					// \[ b_j^{Phase} =
					//    b_j^{Phase} - db_j^{Phase} \eta \]
	}

	free(n);
						// Normal terminate
	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : A Function of Initialize Neurons                                  */
/* Function Name : initialize()                                               */
/*                                                                            */
/* Detail : Initialize a Neurons                                              */
/* Date   : 2015.07.23                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : NEURON_T **n  : Double Pointer of unit                            */
/*        : long  in_num  : Number of input  neurons                          */
/*        : long   h_num  : Number of hidden neurons                          */
/*        : long out_num  : Number of output neurons                          */
/*        : int reset_flg : Mode   of reset [0 : reset, 1 : non reset]        */
/*                                                                            */
/* Output : int : Normal Terminate : 0                                        */
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

int init_bp(
	NEURON_P *np,
	long wb_num,
	long wf_num,
	int reset_flg 
){
	long wb_cnt;
	long  n_cnt;
	long wf_cnt;

	NEURON_T *n;
	long num;

	n = np->p;
	num = np->num;

	for( n_cnt = 0; n_cnt < num; n_cnt++ ){

					// Initialize u,z
		n[n_cnt].u = (
			uniform( 0, 2 * PRECISION_A ) * 1 * PRECISION_B
		) - 1.0;

		n[n_cnt].z = (
			uniform( 0, 2 * PRECISION_A ) * 1 * PRECISION_B
		) - 1.0;
	}

	if( reset_flg == 0 ){
		return 0;
	}

	for( wb_cnt = 0; wb_cnt < wb_num; wb_cnt++ ){

		for( n_cnt = 0; n_cnt < num; n_cnt++ ){

					// Initialize w(for backward)
					//     of input to hidden phase

			n[n_cnt].wb[wb_cnt][n_cnt] = (
				uniform( 0, 2 * PRECISION_A) * 1 * PRECISION_B
			) - 1.0;
		}
	}

	for( n_cnt = 0; n_cnt < num; n_cnt++ ){

					// Initialize bias of hidden phase
		n[n_cnt].bias = (
			uniform( 0, 2 * PRECISION_A ) * 1 * PRECISION_B
		) - 1.0;
	}

	for( n_cnt = 0; n_cnt < num; n_cnt++ ){

		for( wf_cnt = 0; wf_cnt < wf_num; wf_cnt++ ){

					// Initialize w(for forward)

			n[n_cnt].wf[n_cnt][wf_cnt] = (
				uniform( 0, 2 * PRECISION_A) * 1 * PRECISION_B
			) - 1.0;
		}
	}

	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : A Function of learn for Backpropagation                           */
/* Function Name : learn_bp()                                                 */
/*                                                                            */
/* Detail : A Learning by Backpropagation                                     */
/* Date   : 2015.10.19                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : NEURON_P **n         : Double Pointer of unit                     */
/*        :     long   phase_num : Number of phases                           */
/*        :   double  *t         : Value of teach                             */
/*                                                                            */
/* Output : int : Normal Terminate : 0                                        */
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

int learn_bp( NEURON_P **np, long phase_num, double *t ){

	long phase;
					// Calculation Forward

	for( phase = 1; phase < phase_num; phase++ ){
		calc_forward( np, phase, np[phase-1]->num, np[phase]->num );
	}
					// Calculation Δ for output phase

	calc_delta_of_out( np, phase_num-1, np[phase-1]->num, t );

					// Calculation Δ without output phase

	for( phase = phase_num-2; phase >= 0; phase-- ){
		calc_delta( np, phase, np[phase]->num, np[phase+1]->num );
	}
					// Calculation Δw

	for( phase = phase_num-1; phase >= 1; phase-- ){
		calc_delta_w( np, phase, np[phase-1]->num, np[phase]->num );
	}

	return 0;
}

/*
int init_bp(
	long  in_num,
	NEURON_T *nh,
	long   h_num,
	NEURON_T *no,
	long out_num
){
					// Loop counter
	long  in_cnt;
	long   h_cnt;
	long out_cnt;

	for( in_cnt = 0; in_cnt < in_num; in_cnt++ ){

		for( h_cnt = 0; h_cnt < h_num; h_cnt++ ){

					// Initialize w(for backward)
					// of input to hidden phase

			nh[h_cnt].wb[in_cnt][h_cnt]
				= (uniform( 0, PRECISION_A )
				* PRECISAION_B) - 1.0;
		}
	}

	for( h_cnt = 0; h_cnt < h_num; h_cnt++ ){

					// Initialize u and z of hidden phase

		nh[h_cnt].u = (uniform( 0, PRECISION_A ) * PRECISION_B) - 1.0;
		nh[h_cnt].z = (uniform( 0, PRECISION_A ) * PRECISION_B) - 1.0;
	}

	for( h_cnt = 0; h_cnt < h_num; h_cnt++ ){

		for( out_cnt = 0; out_cnt < out_num; out_cnt++ ){

					// Initialize w(for forward)
					// of hidden to output phase

			nh[h_cnt].wf[h_cnt][out_cnt]
				= (uniform( 0, PRECISION_A )
]				* PRECISION_B) - 1.0;
		}
	}

	for( out_cnt = 0; out_cnt < out_num; out_cnt++ ){

					// Initialize u and z of output phase

		no[out_cnt].u = (uniform( 0, PRECISION_A ) * PRECISION_B) - 1.0;
		no[out_cnt].z = (uniform( 0, PRECISION_A ) * PRECISION_B) - 1.0;
	}
					// Normal terminate
	return 0;
}
*/

