/******************************************************************************/
/*                                                                            */
/* Title  : A two variable Gaussian Distribution by Gibbs Sampling            */
/* Program Name : gibbs.c                                                     */
/*                                                                            */
/* Detail : Calculate a two variable Gaussian Distribution by Gibbs Sampling  */
/*          and using the box-muller method and mersenne twister.             */
/* Date   : 2015.03.07                                                        */
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

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#include "MT.h"

#define TRIALS 400

double  a =  0.8;
double x1 =  0.0;
double x2 =  0.0;

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
/* Title  : Gaussian Distribution from Box-Muller Method                      */      
/* Method Name : gauss()                                                      */      
/*                                                                            */      
/* Detail : Calculate a gaussian distribution by the box-muller method.       */      
/* Date   : 2015.03.07                                                        */      
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

double gauss( double m, double s ){

        double z1;
        double z2;
        double y1;
        double y2;
        double rr;

	while( 1 ){
                                        /* Sampling z1 and z2                 */
        	z1 = sampling();
        	z2 = sampling();
                                        /* (r)^2 = (z1)^2 + (z2)^2            */
        	rr = pow(z1,2) + pow(z2,2);

        	if( rr <= 1 ){
                                        /* Check for (r)^2 <= 1               */
                	break;
        	}
	}
                                        /* Calculate y1 and y2                */
        y1 = z1 * pow(( -2 * log( rr ) ) / ( rr ),0.5);
        // y2 = z2 * pow(( -2 * log( rr ) ) / ( rr ),0.5);

	return sqrt(s) * y1 + m;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Gibbs Sampling and Main function                                  */
/* Method Name : main                                                         */
/*                                                                            */
/* Date   : 2015.03.06                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Replace ------------------------------------------------------------------ */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int main(){

	long cnt;
                                        /* Init rand function                 */
        init_rand();

	for( cnt = 0; cnt < TRIALS; cnt++ ){

		printf("%.12f,%.12f\n",x1,x2);

		//x1 = gauss( a*x2, sqrt(1-a*a) );
		x1 = gauss( a*x2, 1 );

		printf("%.12f,%.12f\n",x1,x2);

		//x2 = gauss( a*x1, sqrt(1-a*a) );
		x2 = gauss( a*x1, 1 );
	}
}
