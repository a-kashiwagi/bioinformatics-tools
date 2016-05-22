/******************************************************************************/
/*                                                                            */
/* Title  : Header of Deep Neural Network for mic                             */
/* Program Name : dnn_lib_mic.h                                               */
/*                                                                            */
/* Detail : About a Backpropagation and a Restricted Boltzmann Machine        */
/*          for mic                                                           */
/*                                                                            */
/* Date   : 2015.12.02                                                        */
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

#ifndef _DNN_LIB_MIC_H_DEFINED
					// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
					// Header of Neurons
//#include "neuron.h"
#include "neuron_mic.h"

#define BUFFSIZE 1024000
#define SIGMOID_ALPHA 1

__declspec( target(mic) ) void init_rand(void);
__declspec( target(mic) ) double uniform(double min, double max);
__declspec( target(mic) ) double sigmoid( double x );
__declspec( target(mic) ) double differented_sigmoid( double u );
__declspec( target(mic) ) double rnormal( double m, double s );

void *load_data(
	char *filename,
	long row_num,
	long col_num
);
					// Load learnig data
void *load_teach(
	char *filename,
	long row_num,
	long col_num
);

#define _DNN_LIB_MIC_H_DEFINED
#endif					// _DNN_LIB_MIC_H_DEFIND

