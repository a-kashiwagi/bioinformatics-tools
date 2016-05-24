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
/* Computations were partially performed on the NIG supercomputer             */
/* at ROIS National Institute of Genetics.                                    */
/*                                                                            */
/* Copyright(c)2015 Akihiro Kashiwagi All Rights Reserved                     */
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

#ifndef _NEURON_MIC_H_DEFINED
						/* Includes                   */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
						/* Neuron Structure           */
__declspec( target(mic) ) typedef struct neuron_t {

	double  z;
						/* Value of output            */
	double  u;
						/* Value of internal          */
	double *w;
						/* Weight                     */
	double *a;
						/* Bias for visible unit      */
	double da;
						/* Delta of bias for v unit   */
	double *b;
						/* Bias for hidden unit       */
	double db;
						/* Delta of bias for h unit   */
	double  d;
						/* Delta of weight            */
	double dw;
						/* Length of weight           */
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

	int (*init   )( struct neuron_t *n, long len);
						/* Pointer for init()         */
	int (*alloc_w)( struct neuron_t *n );
						/* Pointer for alloc_w()      */
	int (*free   )( struct neuron_t *n );
						/* Pointer for free()         */
	int (*calc   )( struct neuron_t *n );
						/* Pointer for calc()         */
	int (*learn  )( struct neuron_t *n );
						/* Pointer for learn()        */
} NEURON_T;

__declspec( target(mic) ) typedef struct neuron_p {

	NEURON_T *p;
	long num;

} NEURON_P;

__declspec( target(mic) ) int  init_neuron( NEURON_T *n, long len );

__declspec( target(mic) ) int alloc_neuron( NEURON_T *n );

__declspec( target(mic) ) int  free_neuron( NEURON_T *n );

__declspec( target(mic) ) NEURON_T *create_neuron( long num, long links );
__declspec( target(mic) ) double  **create_synapse( NEURON_T *ni, long i, NEURON_T *nj, long j );

#define _NEURON_MIC_H_DEFINED
#endif
