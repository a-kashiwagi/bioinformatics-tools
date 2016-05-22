/******************************************************************************/
/*                                                                            */
/* Title  : A Program of a shuffling merge                                    */
/* Program Name : shuffle.c                                                   */
/*                                                                            */
/* Detail : This program is a shuffling and merge to two files                */
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

#define BUFFSIZE 1024000

int main(int argc, char *argv[]){
					// File pointer
	FILE *left_fp;
	FILE *right_fp;
					// Return values
	char *left_ret;
	char *right_ret;
					// Uniform
	double uni;
					// Shuffling rate
	double rate;
					// Buffer for a line
	char str[BUFFSIZE];

					// Init randome
	srand(time(NULL));

	if( (argc < 4) || (strcmp( argv[1], "-h" ) == 0) ){

		printf("Usage: shuffle file1_rate file1 file2\n");
		exit(-1);
	}
					// Get a number of rate
	rate = atof( argv[1] );

	left_fp = fopen( argv[2], "r" );
					// Open file1
	if( left_fp == NULL ){
		exit(-1);
	}

	right_fp = fopen( argv[3], "r" );
					// Open file2
	if( right_fp == NULL ){
		exit(-1);
	}
	
	uni = (double)(rand() % 1000001) * 0.000001;
					// Generate a random number

	left_ret = fgets( str, BUFFSIZE, left_fp );
	if((left_ret != NULL) && (uni <= rate)){

		printf("%s", str);
					// Get a line from file1
	}

	right_ret = fgets( str, BUFFSIZE, right_fp );
	if((right_ret != NULL) && (uni > rate)){

		printf("%s",str);
					// Get a line from file2
	}
	
	while( left_ret != NULL || right_ret != NULL ){

		uni = (double)(rand() % 1000001) * 0.000001;
					// Generate a random number

		if((left_ret != NULL) && (uni <= rate)){

			left_ret = fgets( str, BUFFSIZE, left_fp );
			printf("%s", str);
					// Get a line from file1
		}

		if((right_ret != NULL) && (uni > rate)){

			right_ret = fgets( str, BUFFSIZE, right_fp );
			printf("%s",str);
					// Get a line from file2
		}
	}
					// Close files
	fclose(  left_fp );
	fclose( right_fp );

	exit(0);
}
