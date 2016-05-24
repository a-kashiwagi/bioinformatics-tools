/******************************************************************************/
/*                                                                            */
/* Title  : Header of Deep Neural Network                                     */
/* Program Name : dnn.h                                                       */
/*                                                                            */
/* Detail : About a Backpropagation and a Restricted Boltzmann Machine        */
/* Date   : 2015.08.30                                                        */
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

#ifndef _DNN_LIB_H_DEFINED
					// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#include "neuron.h"			// Header of Neurons
//#include "neuron_mic.h"

#define BUFFSIZE 1024000
#define SIGMOID_ALPHA 1
					// Functions of common
void   init_rand( void );
					// Initialize to rand functions
double uniform( double min, double max );
					// Generate an uniform random numbers
double sigmoid( double x );
					// Sigmoid functions
double differented_sigmoid( double u );
					// Differented Sigmoid functions
double rnormal( double m, double s );
					// Randam Sampling from
					//       a Normal Distribution 

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

#define _DNN_LIB_H_DEFINED
#endif					// _DNN_H_DEFIND

