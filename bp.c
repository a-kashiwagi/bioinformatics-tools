/******************************************************************************/
/*                                                                            */
/* Title  : Neural Network by Backpropagation algorism                        */
/* Program Name : contrastive_divergence.c                                    */
/*                                                                            */
/* Detail : Calculate a backpropagation algorism for neural network           */
/* Date   : 2015.07.23                                                        */
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
#include <stdlib.h>
#include <math.h>

#include "MT.h"
					// Header of Mersenne twister
#include "neuron.h"

#define SIGMOID_ALPHA 1
					// Constant for sigmoid function
#define ETA 0.1
					// Learning rate
#define THETA 0.0000001
					// Stabilizer

/******************************************************************************/
/*                                                                            */
/* Title  : Initialize to rand functions                                      */
/* Function Name : init_rand()                                                */
/*                                                                            */
/* Detail : Initialize to jrand functions using init_gennrand() and srand()   */
/* Date   : 2015.02.28                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : void                                                              */
/*                                                                            */
/* Output : void                                                              */
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

void init_rand(void){

	init_genrand((unsigned)time(NULL));
					// For Mersenne twister
	srand(time(NULL));
					// For Standard C
}

/******************************************************************************/
/*                                                                            */
/* Title  : Generate an uniform random numbers                                */
/* Function Name : uniform()                                                  */
/*                                                                            */
/* Detail : Generate an uniform random numbers by using rand() or mersenne.t. */
/* Date   : 2015.02.28                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : double min : minimum number                                       */
/*        : double max : maximum number                                       */
/*                                                                            */
/* Output : double : uniform numbers from min to max                          */
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

double uniform(double min, double max){

	// Using mersenne twister
	return (double)(genrand_int32() % (int)((max - min + 1) + min));

	// Using rand
	// return (double)(rand() % (int)((max - min + 1) + min));
}

/******************************************************************************/
/*                                                                            */
/* Title  : Sigmoid functions                                                 */
/* Function Name : sigmoid()                                                  */
/*                                                                            */
/* Detail : Calculate Sigmoid Number                                          */
/* Date   : 2015.04.30                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : double x : input number                                           */
/*                                                                            */
/* Output : double   : sigmoid number                                         */
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

double sigmoid( double x ){

        return 1 / (1 + exp( -1 * x * SIGMOID_ALPHA ));
}

/******************************************************************************/
/*                                                                            */
/* Title  : Differented Sigmoid functions                                     */
/* Function Name : differented_sigmoid()                                      */
/*                                                                            */
/* Detail : Calculate Differented Sigmoid Value                               */
/* Date   : 2015.07.23                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : double u : input number                                           */
/*                                                                            */
/* Output : double   : differented sigmoid number                             */
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

double differented_sigmoid( double u ){

	return sigmoid( u ) * ( 1 - sigmoid( u ) );
}

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
/* Input  : NEURON_T **n  : Double Pointer of unit                            */
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

int calc_forward( NEURON_T **n, long phase, long in_num, long out_num ){

						// Counter for loop i,j
	long i;
	long j;
						// Weight for link
	double w;
						// Activated value
	double z;
						// Summary
	double sum;
						// Loop without bias(w0j)
	for( j = 1; j < out_num; j++ ){
						// Initialize
		sum = 0;
						// w0j is instead of bias
		n[phase-1][0].z = 1;
						// Loop with bias(w0j)
		for( i = 0; i < in_num; i++ ){

						// Weight of i to j
			w = n[phase  ][j].wb[i][j];

						// Output of side of i
			z = n[phase-1][i].z;
						// Summary
			sum += w * z;
		}
						// Value of inside
		n[phase][j].u = sum - THETA;
						// Activated value z
		n[phase][j].z = sigmoid( n[phase][j].u );
	}
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
/* Input  : NEURON_T **n  : Double Pointer of unit                            */
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

int calc_delta_of_out( NEURON_T **n, long phase, long out_num, double *teach ){

	long j;

	for( j = 1; j < out_num; j++ ){

						// Difference from teach value
		n[phase][j].d = n[phase][j].z - teach[j];
	}
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
/* Input  : NEURON_T **n  : Double Pointer of unit                            */
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

int calc_delta( NEURON_T **n, long phase, long in_num, long out_num ){

						// Counter for loop i,j
	long j;
	long k;
						// Weight for link
	double w;
						// Difference value
	double d;
						// Differented sigmoid
	double ff;
						// Summary
	double sum;
						// Loop without bias(w0j)
	for( j = 1; j < in_num; j++ ){
						// Initialize
		sum = 0;
						// Loop without bias(w0j)
		for( k = 1; k < out_num; k++ ){
						// Weight of j to k
			w = n[phase+1][k].wb[j][k];

						// Difference value
			d = n[phase+1][k].d;

						// Diffeented activated u
			ff = differented_sigmoid( n[phase][j].u );

						// Summary
			sum += d * w * ff;
		}
						// Set to side of j
		n[phase][j].d = sum;
	}
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
/* Input  : NEURON_T **n  : Double Pointer of unit                            */
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

int calc_delta_w( NEURON_T **n, long phase, long in_num, long out_num ){

						// Counter for loop i,j
	long i;
	long j;
						// Difference value
	double d;
						// Activated value
	double z;
						// Difference for w
	double dw;
						// Loop without bias(w0j)
	for( j = 1; j < out_num; j++ ){
						// Loop without bias(w0j)
		for( i = 1; i < in_num; i++ ){
						// Difference value of j
			d = n[phase  ][j].d;
						// Activated value of i
			z = n[phase-1][i].z;
						// Difference for w
			dw = d * z;		
						// Set to w
			n[phase][j].wb[i][j] -= dw * ETA;		
		}
	}
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

int initialize(
	NEURON_T **n,
	long  in_num,
	long   h_num,
	long out_num
){
					// Loop counter
	long  in_cnt;
	long   h_cnt;
	long out_cnt;

	for( in_cnt = 0; in_cnt < in_num; in_cnt++ ){

					// Initialize u and z of input phase

		n[0][in_cnt].u = (uniform( 0, 20000000 ) * 0.0000001) - 1.0;
		n[0][in_cnt].z = (uniform( 0, 20000000 ) * 0.0000001) - 1.0;
	}

	for( in_cnt = 0; in_cnt < in_num; in_cnt++ ){

		for( h_cnt = 0; h_cnt < h_num; h_cnt++ ){

					// Initialize w(for backward)
					// of input to hidden phase

			n[1][h_cnt].wb[in_cnt][h_cnt]
				= (uniform( 0, 20000000 ) * 0.0000001) - 1.0;
		}
	}

	for( h_cnt = 0; h_cnt < h_num; h_cnt++ ){

					// Initialize u and z of hidden phase

		n[1][h_cnt].u = (uniform( 0, 20000000 ) * 0.0000001) - 1.0;
		n[1][h_cnt].z = (uniform( 0, 20000000 ) * 0.0000001) - 1.0;
	}

	for( h_cnt = 0; h_cnt < h_num; h_cnt++ ){

		for( out_cnt = 0; out_cnt < out_num; out_cnt++ ){

					// Initialize w(for forward)
					// of hidden to output phase

			n[1][h_cnt].wf[h_cnt][out_cnt]
				= (uniform( 0, 20000000 ) * 0.0000001) - 1.0;
		}
	}

	for( out_cnt = 0; out_cnt < out_num; out_cnt++ ){

					// Initialize u and z of output phase

		n[2][out_cnt].u = (uniform( 0, 20000000 ) * 0.0000001) - 1.0;
		n[2][out_cnt].z = (uniform( 0, 20000000 ) * 0.0000001) - 1.0;
	}
					// Normal terminate
	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : A Main Function                                                   */
/* Function Name : main()                                                     */
/*                                                                            */
/* Detail : Initialize a Neurons                                              */
/* Date   : 2015.07.23                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  :                                                                   */
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

#define  IN_MAX 1+6
#define   H_MAX 1+128
#define OUT_MAX 1+6

#define  IN_PHASE 0
#define   H_PHASE 1
#define OUT_PHASE 2

int main(){

	NEURON_T *ni;
	NEURON_T *nh;
	NEURON_T *no;

	NEURON_T *n[3];
	long ret;
	long cnt;

	double data[64][6] = {
		{ 0, 1, 0, 1, 0, 1 }, // T
		{ 0, 1, 1, 1, 0, 1 },
		{ 0, 1, 0, 0, 0, 1 },
		{ 0, 1, 1, 0, 0, 1 },

		{ 0, 1, 0, 1, 1, 1 },
		{ 0, 1, 1, 1, 1, 1 },
		{ 0, 1, 0, 0, 1, 1 },
		{ 0, 1, 1, 0, 1, 1 },

		{ 0, 1, 0, 1, 0, 0 },
		{ 0, 1, 1, 1, 0, 0 },
		{ 0, 1, 0, 0, 0, 0 },
		{ 0, 1, 1, 0, 0, 0 },

		{ 0, 1, 0, 1, 1, 0 },
		{ 0, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 1, 0 },
		{ 0, 1, 1, 0, 1, 0 },

		{ 1, 1, 0, 1, 0, 1 }, // C
		{ 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 0, 1 },

		{ 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 0, 1, 1 },
		{ 1, 1, 1, 0, 1, 1 },

		{ 1, 1, 0, 1, 0, 0 },
		{ 1, 1, 1, 1, 0, 0 },
		{ 1, 1, 0, 0, 0, 0 },
		{ 1, 1, 1, 0, 0, 0 },

		{ 1, 1, 0, 1, 1, 0 },
		{ 1, 1, 1, 1, 1, 0 },
		{ 1, 1, 0, 0, 1, 0 },
		{ 1, 1, 1, 0, 1, 0 },

		{ 0, 0, 0, 1, 0, 1 }, // A
		{ 0, 0, 1, 1, 0, 1 },
		{ 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 1, 0, 0, 1 },

		{ 0, 0, 0, 1, 1, 1 },
		{ 0, 0, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 1, 1 },
		{ 0, 0, 1, 0, 1, 1 },

		{ 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0 },

		{ 0, 0, 0, 1, 1, 0 },
		{ 0, 0, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 1, 0 },
		{ 0, 0, 1, 0, 1, 0 },

		{ 1, 0, 0, 1, 0, 1 }, // G
		{ 1, 0, 1, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 1 },

		{ 1, 0, 0, 1, 1, 1 },
		{ 1, 0, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 1, 1 },
		{ 1, 0, 1, 0, 1, 1 },

		{ 1, 0, 0, 1, 0, 0 },
		{ 1, 0, 1, 1, 0, 0 },
		{ 1, 0, 0, 0, 0, 0 },
		{ 1, 0, 1, 0, 0, 0 },

		{ 1, 0, 0, 1, 1, 0 },
		{ 1, 0, 1, 1, 1, 0 },
		{ 1, 0, 0, 0, 1, 0 },
		{ 1, 0, 1, 0, 1, 0 }
	};

	double teach[64][6]   = {
		{ 0, 0, 1, 1, 1, 0 }, // T
		{ 0, 1, 0, 0, 0, 0 },
		{ 0, 1, 0, 0, 1, 1 },
		{ 0, 0, 0, 1, 0, 1 },

		{ 0, 0, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 0 },
		{ 0, 1, 0, 0, 1, 1 },
		{ 0, 0, 0, 1, 0, 1 },

		{ 0, 0, 1, 0, 1, 1 },
		{ 0, 1, 0, 0, 0, 0 },
		{ 0, 1, 0, 1, 0, 1 },
		{ 0, 1, 0, 1, 0, 1 },

		{ 0, 0, 1, 0, 1, 1 },
		{ 0, 1, 0, 0, 0, 0 },
		{ 0, 1, 0, 1, 0, 1 },
		{ 0, 1, 0, 0, 1, 0 },

		{ 0, 0, 1, 0, 1, 1 }, // C
		{ 0, 0, 1, 1, 1, 1 },
		{ 0, 0, 1, 0, 0, 1 },
		{ 0, 0, 0, 0, 1, 0 },

		{ 0, 0, 1, 0, 1, 1 },
		{ 0, 0, 1, 1, 1, 1 },
		{ 0, 0, 1, 0, 0, 1 },
		{ 0, 0, 0, 0, 1, 0 },

		{ 0, 0, 1, 0, 1, 1 },
		{ 0, 0, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 1, 1 },
		{ 0, 0, 0, 0, 1, 0 },

		{ 0, 0, 1, 0, 1, 1 },
		{ 0, 0, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 1, 1 },
		{ 0, 0, 0, 0, 1, 0 },

		{ 0, 0, 1, 0, 1, 0 }, // A
		{ 0, 1, 0, 0, 0, 1 },
		{ 0, 0, 0, 0, 1, 1 },
		{ 0, 1, 0, 0, 0, 0 },

		{ 0, 0, 1, 0, 1, 0 },
		{ 0, 1, 0, 0, 0, 1 },
		{ 0, 0, 0, 0, 1, 1 },
		{ 0, 1, 0, 0, 0, 0 },

		{ 0, 0, 1, 0, 1, 0 },
		{ 0, 1, 0, 0, 0, 1 },
		{ 0, 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 1, 0 },

		{ 0, 0, 1, 1, 0, 1 },
		{ 0, 1, 0, 0, 0, 1 },
		{ 0, 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 1, 0 },

		{ 0, 1, 0, 1, 0, 0 }, // G
		{ 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 1, 0, 0, 0 },

		{ 0, 1, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 1, 0, 0, 0 },

		{ 0, 1, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 0, 1, 1, 1 },
		{ 0, 0, 1, 0, 0, 0 },

		{ 0, 1, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 0, 1, 1, 1 },
		{ 0, 0, 1, 0, 0, 0 }
	};

	long t_cnt;
	double t[7];
	unsigned char amino_acid_no;
	int amino_cnt;
	char amino_acid;

	ni = create_neuron(  IN_MAX, 0 );
	nh = create_neuron(   H_MAX, 0 );
	no = create_neuron( OUT_MAX, 0 );

	create_synapse( ni, IN_MAX, nh,   H_MAX );
	create_synapse( nh,  H_MAX, no, OUT_MAX );

	n[0] = ni;
	n[1] = nh;
	n[2] = no;

	init_rand();
	initialize( n, IN_MAX, H_MAX, OUT_MAX );

	t_cnt = 0;

	for( cnt = 0; cnt < 64 * 10000; cnt++ ){

		n[0][0].z = 1;
		n[0][1].z = data[t_cnt][0];
		n[0][2].z = data[t_cnt][1];
		n[0][3].z = data[t_cnt][2];
		n[0][4].z = data[t_cnt][3];
		n[0][5].z = data[t_cnt][4];
		n[0][6].z = data[t_cnt][5];

		t[0]     = 1;
		t[1]     = teach[t_cnt][0];
		t[2]     = teach[t_cnt][1];
		t[3]     = teach[t_cnt][2];
		t[4]     = teach[t_cnt][3];
		t[5]     = teach[t_cnt][4];
		t[6]     = teach[t_cnt][5];

		calc_forward( n,   H_PHASE, IN_MAX,   H_MAX );
		calc_forward( n, OUT_PHASE,  H_MAX, OUT_MAX );

		printf( "%02ld,  %.0f,%.0f,%.0f,%.0f,%.0f,%.0f,  %f,%f,%f,%f,%f,%f",
			t_cnt,

			n[0][1].z,
			n[0][2].z,
			n[0][3].z,
			n[0][4].z,
			n[0][5].z,
			n[0][6].z,

			n[2][1].z,
			n[2][2].z,
			n[2][3].z,
			n[2][4].z,
			n[2][5].z,
			n[2][6].z
		);

		amino_acid_no = 0;
		for( amino_cnt = 1; amino_cnt <= 6; amino_cnt++ ){

			if( n[2][amino_cnt].z > 0.7 ){

				amino_acid_no++;
			}

			if( amino_cnt < 6 ){
				amino_acid_no = amino_acid_no << 1;
			}
		}

		switch( amino_acid_no ){

		case 1:
			amino_acid = 'A';
			break;
		case 2:
			amino_acid = 'R';
			break;
		case 3:
			amino_acid = 'N';
			break;
		case 4:
			amino_acid = 'D';
			break;
		case 5:
			amino_acid = 'C';
			break;
		case 6:
			amino_acid = 'Q';
			break;
		case 7:
			amino_acid = 'E';
			break;
		case 8:
			amino_acid = 'G';
			break;
		case 9:
			amino_acid = 'H';
			break;
		case 10:
			amino_acid = 'I';
			break;
		case 11:
			amino_acid = 'L';
			break;
		case 12:
			amino_acid = 'K';
			break;
		case 13:
			amino_acid = 'M';
			break;
		case 14:
			amino_acid = 'F';
			break;
		case 15:
			amino_acid = 'P';
			break;
		case 16:
			amino_acid = 'S';
			break;
		case 17:
			amino_acid = 'T';
			break;
		case 18:
			amino_acid = 'W';
			break;
		case 19:
			amino_acid = 'Y';
			break;
		case 20:
			amino_acid = 'V';
			break;
		case 21:
			amino_acid = '#';
			break;
		default:
			amino_acid = '?';
			break;
		}

		printf(",  %c\n",amino_acid);

		calc_delta_of_out( n, OUT_PHASE, OUT_MAX, t );

		calc_delta( n,  H_PHASE,  H_MAX, OUT_MAX );
		calc_delta( n, IN_PHASE, IN_MAX,   H_MAX );

		calc_delta_w( n, OUT_PHASE,  H_MAX, OUT_MAX );
		calc_delta_w( n,   H_PHASE, IN_MAX,   H_MAX );

		if( t_cnt >= 64-1 ){
			t_cnt = 0;
			printf( "\n");
		}else{
			t_cnt++;
		}

	}

	exit(0);
}
