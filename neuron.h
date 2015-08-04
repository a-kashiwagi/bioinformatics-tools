/******************************************************************************/
/*                                                                            */
/* Title  : Neuron Class - header file                                        */
/* Program Name : neuron.h                                                    */
/*                                                                            */
/* Detail : Header file of Neuron Class                                       */
/* Date   : 2015/05/28                                                        */
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

#ifndef _NEURON_H_DEFINED

#include <stdio.h>
#include <malloc.h>
						/* Neuron Structure           */
typedef struct neuron {

	double  u;
						/* Value of internal          */
	double *w;
						/* Weight                     */
	double  a;
						/* Bias for visible unit      */
	double da;
						/* Delta of bias for v unit   */
	double  b;
						/* Bias for hidden unit       */
	double db;
						/* Delta of bias for h unit   */
	long w_len;
						/* Length of weight (Links)   */
	double bias;
						/* Bias                       */
	double **wf;
						/* Weight for front           */
	double **dwf;
						/* Delta of weight for front  */
	long wf_len;
						/* Length of front weight     */
	double **wb;
						/* Weight for back            */
	double **dwb;
						/* Delta of weight for back   */
	long wb_len;
						/* Length of back weight      */

	int (*init   )( struct neuron *n, long len);
						/* Pointer for init()         */
	int (*alloc_w)( struct neuron *n );
						/* Pointer for alloc_w()      */
	int (*free   )( struct neuron *n );
						/* Pointer for free()         */
	int (*calc   )( struct neuron *n );
						/* Pointer for calc()         */
	int (*learn  )( struct neuron *n );
						/* Pointer for learn()        */
} NEURON_T;

int  init_neuron( NEURON_T *n, long len );
int alloc_neuron( NEURON_T *n );
int  free_neuron( NEURON_T *n );

NEURON_T *create_neuron( long num, long links );
double  **create_synapse( NEURON_T *ni, long i, NEURON_T *nj, long j );

#define _NEURON_H_DEFINED
#endif
