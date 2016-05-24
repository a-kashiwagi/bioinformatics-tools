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

