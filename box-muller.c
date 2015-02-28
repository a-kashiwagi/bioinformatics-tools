/******************************************************************************/
/*                                                                            */
/* Title  : Gaussian Distribution from Box-Muller Method                      */
/* Program Name : box-muller.c                                                */
/*                                                                            */
/* Detail : Calculate a gaussian distribution by the box-muller method.       */
/* Date   : 2015.02.28                                                        */
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
#include <time.h>
#include <math.h>
					/* Using the Mersenne Twister         */
#include "MT.h"

#define TRIALS 10000

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
					/* Init for mersenne twister          */
	init_genrand((unsigned)time(NULL));

					/* Init system rand function          */
	srand(time(NULL));
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
	//return (double)(rand() % (int)((max - min + 1) + min));
}

/******************************************************************************/
/*                                                                            */
/* Title  : Sampling an uniform nubmers                                       */
/* Function Name : sampling()                                                 */
/*                                                                            */
/* Detail : Sampling an uniform numbers from (-1) to (+1)                     */
/* Date   : 2015.02.28                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : void                                                              */
/*                                                                            */
/* Output : double : uniform numbers from (-1) to (+1)                        */
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

double sampling(){

	double num;
					/* Uniform numbers 0 to 1             */
	num = uniform(0,999999999) * 0.000000001;

					/* Transfar (-1) to (+1)              */
	num = 2 * num - 1;

	return num;
}

/******************************************************************************/
/*                                                                            */
/* Title  : main function                                                     */
/* Function Name : main()                                                     */
/*                                                                            */
/* Detail : main function of box-muller method                                */
/* Date   : 2015.02.28                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  :  int   argc : argument count                                      */
/*        : char **argc : argument values                                     */
/*                                                                            */
/* Output : Normal terminate 0                                                */
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

int main(int argc, char **argv){

	int cnt;
	double z1[TRIALS];
	double z2[TRIALS];
	double y1[TRIALS];
	double y2[TRIALS];
	double rr;
					/* Init rand function                 */
	init_rand();

	cnt = 0;

	while(cnt < TRIALS){
					/* Sampling z1 and z2                 */
		z1[cnt] = sampling();
		z2[cnt] = sampling();
					/* (r)^2 = (z1)^2 + (z2)^2            */
		rr = pow(z1[cnt],2) + pow(z2[cnt],2);

		if( rr > 1 ){
					/* Check for (r)^2 <= 1               */
			continue;
		}
					/* Calculate y1 and y2                */
		y1[cnt] = z1[cnt] * pow(( -2 * log( rr ) ) / ( rr ),0.5);
		y2[cnt] = z2[cnt] * pow(( -2 * log( rr ) ) / ( rr ),0.5);

					/* Print out                          */
		printf("%.12f,%.12f,%.12f,%.12f\n",
			z1[cnt],z2[cnt],y1[cnt],y2[cnt]);
		cnt++;
					/* Increment counter                  */
	}

	exit(0);
}

