/******************************************************************************/
/*                                                                            */
/* Title  : A Common Library of Deep Neural Network                           */
/* Program Name : dnn.c                                                       */
/*                                                                            */
/* Detail : Common functions for calculate a deep neural network              */
/* Date   : 2015.09.01                                                        */
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

					// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "MT.h"
#include "dnn_lib.h"
//#include "dnn_lib_mic.h"

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

				// \[ f(x) = \frac{1}{1+e^{-x \alpha}} \]

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

					// \[ f'(u) = f(u) * (1 - f(u)) \]

	return sigmoid( u ) * ( 1 - sigmoid( u ) );
}

/******************************************************************************/
/*                                                                            */
/* Title  : A Function of load data                                           */
/* Function Name : load_data()                                                */
/*                                                                            */
/* Detail : Load data                                                         */
/* Date   : 2015.08.20                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : non                                                               */
/*                                                                            */
/* Output : Normal Terminate : Pointer of data                                */
/*        : Error  Terminate : NULL                                           */
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

void *load_data( char *filename, long row_num, long col_num ){

	long cnt;
	long row_cnt;
	long col_cnt;
	char *token;
	FILE *fp;
	double *data_p;
	char str[BUFFSIZE];
					// File open
	fp = fopen( filename, "r" );
	if( fp == NULL ){
					// Error return
		return NULL;
	}
					// Allocate memory for rows
	data_p = (double *)malloc( sizeof(double) * row_num * col_num );
	if( data_p == NULL ){
		printf("Can't allocate a learning data memory.\n");
		return NULL;
	}

	for( row_cnt = 0; row_cnt < row_num; row_cnt++ ){

					// Allocate memory for columns
		//data_p[row_cnt]
		//	= (double *)malloc( sizeof(double) * col_num );
		//if( data_p[row_cnt] == NULL ){
		//	printf("Can't allocate a learning data memory.\n");
		//	return NULL;
		//}
					// Get a row
		fgets( str, BUFFSIZE, fp );
		if( fp == NULL ){
			printf("Can't get a line from a learning data file.\n");
					// Error return
			return NULL;
		}
					// Tokenize
		token = strtok( str, "," );
		if( token == NULL ){
			printf("Can't get a first token.\n");
					// Error return
			return NULL;
		}

		/*
		cnt = 0;
		while( token[cnt] == ' ' ){
					// Fast Forward
			cnt++;
		}

		if( token[cnt] == '#' ){
					// This row is commnet line;
			continue;
		}
		*/
					// Set a first number
		data_p[col_num * row_cnt + 0] = atof( token );

		for( col_cnt = 1; col_cnt < col_num; col_cnt++  ){

			token = strtok( NULL, "," );
			if( token == NULL ){
				printf("Can't get a token at [%ld][%ld].\n",
					row_cnt,
					col_cnt
				);
					// Error return
				return NULL;
			}
					// Set a second and later numbers
			//data_p[row_cnt][col_cnt] = atof( token );
			data_p[col_num * row_cnt + col_cnt] = atof( token );
		}
	}
					// File close
	fclose( fp );

	/*
	for( row_cnt = 0; row_cnt < row_num; row_cnt++ ){
		for( col_cnt = 0; col_cnt < col_num; col_cnt++ ){

			printf("%ld,%ld:%f\n",
				row_cnt,
				col_cnt,
				//data_p[row_cnt][col_cnt]
				data_p[(row_num - 1) * row_cnt + col_cnt]
			);
		}
	}
	*/

	return data_p;
}

/******************************************************************************/
/*                                                                            */
/* Title  : A Function of load teach data                                     */
/* Function Name : load_teach()                                               */
/*                                                                            */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

void *load_teach( char *filename, long row_num, long col_num ){

	long cnt;
	long row_cnt;
	long col_cnt;
	char *token;
	FILE *fp;
	double *teach_p;
	char str[BUFFSIZE];
					// File open
	fp = fopen( filename, "r" );
	if( fp == NULL ){
					// Error return
		return NULL;
	}
					// Allocate memory for rows
	teach_p = (double *)malloc( sizeof(double) * row_num * col_num);
	if( teach_p == NULL ){
		printf("Can't allocate a teach data memory.\n");
		return NULL;
	}

	for( row_cnt = 0; row_cnt < row_num; row_cnt++ ){

					// Allocate memory for columns
		//teach_p[row_cnt]
		//	= (double *)malloc( sizeof(double) * col_num );
		//if( teach_p[row_cnt] == NULL ){
		//	printf("Can't allocate a teach data memory.\n");
		//	return NULL;
		//}
					// Get a row
		fgets( str, BUFFSIZE, fp );
		if( fp == NULL ){
					// Error return
			return NULL;
		}
					// Tokenize
		token = strtok( str, "," );
		if( token == NULL ){
					// Error return
			return NULL;
		}

		cnt = 0;
		while( token[cnt] == ' ' ){
					// Fast Forward
			cnt++;
		}

		if( token[cnt] == '#' ){
					// This row is commnet line;
			continue;
		}
					// Set a first number
		teach_p[col_num * row_cnt + 0] = atof( token );

		for( col_cnt = 1; col_cnt < col_num; col_cnt++ ){

					// Tokenize
			token = strtok( NULL, "," );
			if( token == NULL ){
					// Error return
				return NULL;
			}
					// Set a second and later numbers
			teach_p[col_num * row_cnt + col_cnt] = atof( token );
		}
	}
					// File close
	fclose( fp );

	return teach_p;
}

