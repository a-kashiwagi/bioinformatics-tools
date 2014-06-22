/******************************************************************************/
/*                                                                            */
/* Title  : Hidden Markov Model - Transition structures                       */
/* Program Name : hmm.c                                                       */
/*                                                                            */
/* Detail : Transition structure of Hidden Markov Model                       */
/* Date   : 2011/02/06                                                        */
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
#include <string.h>
#include <math.h>

#include "hmm.h"

/******************************************************************************/
/*                                                                            */
/* Title  : Calculate to total value in TRNS structure                        */
/* Function Name : tr_total()                                                 */
/*                                                                            */
/* Detail : Calculate to total each amino acid value in TRNS structure        */
/* Date   : 2011/02/01                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : TRNS *tr : target TRNS pointer                                    */
/* Output : double   : answer                                                 */
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
long total_tr( TRNS *tr ){
						/* Counter                    */
	int cnt;
						/* Calculate each amino acid  */
						/*                and return  */
	tr->total = 0;

	for( cnt = 0; cnt < tr->num; cnt++ ){

		tr->total += tr->characters[cnt];
	}

	return( tr->total );
}

/******************************************************************************/
/*                                                                            */
/* Title  : reset to TRNS structure                                           */
/* Function Name : reset_tr()                                                 */
/*                                                                            */
/* Detail : reset to each value in TRNS structure                             */
/* Date   : 2011/02/01                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : TRNS *tr : target TRNS pointer                                    */
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

void reset_tr( TRNS *tr ){
						/* Counter                    */
	int cnt;
						/* reset to each value        */
	for( cnt = 0; cnt < tr->num; cnt++ ){
		tr->characters[cnt] = 0;
	}
						/* reset total                */
	tr->total = 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Free to TRNS structure                                            */
/* Function Name : free_tr()                                                  */
/*                                                                            */
/* Detail : Free to each value in TRNS structure                              */
/* Date   : 2011/02/08                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : TRNS *tr : target TRNS pointer                                    */
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
void free_tr( TRNS *tr ){
						/* Free to memory             */
	free( tr->characters );
	tr->characters = NULL;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Initialize to TRNS structure                                      */
/* Function Name : init_tr()                                                  */
/*                                                                            */
/* Detail : Initialize to each value in TRNS structure                        */
/* Date   : 2011/02/08                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : TRNS *tr : target TRNS pointer                                    */
/*          char *processing_char_set : Pointer of processing character set   */
/*          long processing_char_num : Number of processing characters        */
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
void init_tr(
	TRNS *tr,
	char *processing_char_set,
	long processing_char_num
){
						/* Set character set          */
	tr->character_set = processing_char_set;
						/* Set number of character    */
	tr->num = processing_char_num;

						/* Allocate memory            */
						/*     to each TRNS.character */
	tr->characters = malloc( sizeof(long) * processing_char_num );

						/* Reset TRNS                 */
	reset_tr( tr );
						/* Set address of function    */
	tr->reset = reset_tr;
						/* Address of reset_tr()      */

	tr->calc_total = total_tr;
						/* Address of total_tr()      */

	tr->free = free_tr;
						/* Address of free_tr()       */
}

/******************************************************************************/
/*                                                                            */
/* Title  : reset to TRNS_FOR_CMP structure                                   */
/* Function Name : reset_tf_cmp()                                             */
/*                                                                            */
/* Detail : reset to each value in TRNS_FOR_CMP structure                     */
/* Date   : 2011/01/27                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : TRNS *tf_form_cmp : target TRNS_FOR_CMP pointer                   */
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
void reset_tf_cmp( TRNS_FOR_CMP *tf_cmp ){
						/* Counter                    */
	int cnt;
						/* reset to each value        */
	for( cnt = 0; cnt < tf_cmp->num; cnt++ ){
		tf_cmp->characters[cnt] = 0;
	}
}

/******************************************************************************/
/*                                                                            */
/* Title  : Free to TRNS_FOR_CMP structure                                    */
/* Function Name : free_tf_cmp()                                              */
/*                                                                            */
/* Detail : Free to each value in TRNS_FOR_CMP structure                      */
/* Date   : 2011/02/08                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : TRNS *tf_cmp : target TRNS_FOR_CMP pointer                        */
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
void free_tf_cmp( TRNS_FOR_CMP *tf_cmp ){
						/* Free to memory             */
	free( tf_cmp->characters );
	tf_cmp->characters = NULL;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Initialize to TRNS_FOR_CMP structure                              */
/* Function Name : init_tf_cmp()                                              */
/*                                                                            */
/* Detail : Initialize to each value in TRNS_FOR_CMP structure                */
/* Date   : 2011/02/08                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : TRNS *tf_cmp : target TRNS_FOR_CMP pointer                        */
/*          char *processing_char_set : Pointer of processing character set   */
/*          long processing_char_num : Number of processing characters        */
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
void init_tf_cmp(
	TRNS_FOR_CMP *tf_cmp,
	char *processing_char_set,
	long processing_char_num
){
						/* Set character set          */
	tf_cmp->character_set = processing_char_set;
						/* Set number of character    */
	tf_cmp->num = processing_char_num;
						/* Allocate memory to each    */
						/* TRNS_FOR_CMP.character     */
	tf_cmp->characters = malloc( sizeof(double) * processing_char_num );

						/* Reset TRNS_FOR_CMP         */
	reset_tf_cmp( tf_cmp );
						/* Set address of function    */
	tf_cmp->reset = reset_tf_cmp;
						/* Address of reset_tf_cmp()  */

	tf_cmp->free = free_tf_cmp;
						/* Address of free_tf_cmp()   */
}

/******************************************************************************/
/*                                                                            */
/* Title  : Transition from a,t,g,c                                           */
/* function Name : from_x()                                                   */
/*                                                                            */
/* Detail : Transition from each character to each character                  */
/* Date   : 2010/09/02                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : TRNS *tr : target TRNS structure pointer                          */
/*        : int to   : transition to acid                                     */
/* Output : int : Normal terminate : 0                                        */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2011/02/05                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Modify to both nucleotide and amino acid.                         */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/
int from_x( TRNS *tr, int to ){
						/* Counter                    */
	int cnt;
						/* Loop for each characters   */
	for( cnt = 0; cnt < tr->num; cnt++ ){
						/* Check for a character      */
		if( to == (int)tr->character_set[cnt] ){
						/* Increment counter          */
			tr->characters[cnt]++;
			break;
		}
	}
						/* Normal return              */
	return(0);
}

/******************************************************************************/
/*                                                                            */
/* Title  : print trns structure                                              */
/* function Name : print_trns()                                               */
/*                                                                            */
/* Detail : print trns structure                                              */
/* Date   : 2011/02/05                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : TRNS tr[] : Pointer of TRNS array                                 */
/* Output : void      : count of transition                                   */
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
void print_trns( TRNS *tr ){
						/* Counter                    */
	int cnt;

						/* Loop for each characters   */
	for( cnt = 0; cnt < tr->num - 1; cnt++ ){
						/* Output each counters       */
		printf( "%ld,", tr->characters[cnt] );
	}
						/* Output last counter        */
	printf( "%ld\n", tr->characters[cnt] );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Calculate rate of hmm                                             */
/* Function Name : rate_hmm()                                                 */
/*                                                                            */
/* Detail : Calculate rate of hmm of each amino acid                          */
/* Date   : 2011/01/28                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : FILE **       : Pointer of opened file pointer                    */
/*          TRNS_FOR_CMP *: Pointer of TRNS_FOR_CMP                           */
/* Output : long          : Summary of count                                  */
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

long rate_hmm_from_file( FILE **in_fp, TRNS_FOR_CMP *tf_cmp ){

						/* File pointer               */
	FILE *fp;
						/* long array for Amino Acid  */
	long characters[tf_cmp->num];
						/* Summary                    */
	long sum;
						/* Counter                    */ 
	int cnt;
						/* Return                     */
	int ret;

						/* Set fp from argument       */
	fp = *in_fp;

						/* Load line 1                */
	for( cnt = 0; cnt < tf_cmp->num - 1; cnt++ ){

		ret = fscanf( fp, "%ld,",&characters[cnt] );
	}

	ret = fscanf( fp, "%ld\n", &characters[tf_cmp->num - 1] );

						/* Calculate total            */
	sum = 0;

	for( cnt = 0; cnt < tf_cmp->num; cnt++ ){
		sum += characters[cnt];
	}
						/* Case of sum is zero        */
	if( sum == 0 ){
		return( sum );
	}
						/* Calculate hmm value        */
	for( cnt = 0; cnt < tf_cmp->num; cnt++ ){

		tf_cmp->characters[cnt] = (double)characters[cnt] / (double)sum;
	}

	return( sum );
}

long rate_hmm( TRNS *tr, TRNS_FOR_CMP *tf_cmp ){
						/* Summary                    */
	long sum;
						/* Counter                    */ 
	int cnt;

						/* Calculate total            */
	sum = 0;

	for( cnt = 0; cnt < tf_cmp->num; cnt++ ){
		sum += tr->characters[cnt];
	}
						/* Case of sum is zero        */
	if( sum == 0 ){
		return( sum );
	}
						/* Calculate hmm value        */
	for( cnt = 0; cnt < tf_cmp->num; cnt++ ){

		tf_cmp->characters[cnt]
			= (double)tr->characters[cnt] / (double)sum;
	}

	return( sum );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Load data of hmm : generated from hmm_learn                       */
/* Function Name : load_hmm_data                                              */
/*                                                                            */
/* Detail : Load data of Hidden Markov Model and Calculate                    */
/* Date   : 2011/02/01                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *filename : hmm data file name                               */
/*        : TRNS_FOR_CMP tf_cmp[] : Pointer of array of TRNS_FOR_CMP          */
/* Output : long           : Summary of count                                 */
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

long load_hmm_data_from_file(
	char *filename,
	TRNS_FOR_CMP tf_cmp[]
){
						/* Counter                    */
	long cnt;
						/* Number of processing char  */
	long processing_char_num;
						/* File pointer for input     */
	FILE *fp;
						/* Summary                    */
	long sum;

						/* File open                  */
	fp = fopen( filename, "r" );
	if( fp == NULL ){
						/* File can not open          */
		return(1);
	}
						/* Set processing char number */
	processing_char_num = tf_cmp[0].num;
						/* Initialize sum             */
	sum = 0;
						/* Calculate hmm value        */
	for( cnt = 0; cnt < processing_char_num; cnt++ ){

		sum += rate_hmm_from_file( &fp, &tf_cmp[cnt] );
	}

						/* File close                 */
	fclose( fp );
						/* Normal terminate           */
	return(sum);
}

long load_hmm_data(
	TRNS tr[],
	TRNS_FOR_CMP tf_cmp[]
){
						/* Counter                    */
	long cnt;

						/* Number of processing char  */
	long processing_char_num;
						/* Summary                    */
	long sum;
						/* Set processing char number */
	processing_char_num = tf_cmp[0].num;
						/* Initialize sum             */
	sum = 0;
						/* Calculate hmm value        */
	for( cnt = 0; cnt < processing_char_num; cnt++ ){

		sum += rate_hmm( &tr[cnt], &tf_cmp[cnt] );
	}
						/* Normal terminate           */
	return(sum);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Compare TRNS stracture                                            */
/* Function Name : tr_tf_cmp                                                  */
/*                                                                            */
/* Detail : Compare TRNS stracture by range                                   */
/* Date   : 2011/02/01                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : double range      : Tolerance                                     */
/*          TRNS *tr          : Working number of hmm                         */
/*          TRNS_FOR_CMP *cmp : Loaded nubmer of hmm                          */
/* Output : Match rate                                                        */
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

double tr_tf_cmp( double range, TRNS *tr, TRNS_FOR_CMP *tf_cmp ){

	int cnt;
						/* HMM value each acid        */
	double current_characters[tr->num];

	double average;
						/* Match counter              */
	int match_cnt;

						/* Calculate total            */
	total_tr( tr );
						/* Calculate each hmm value   */
	if( tr->total != 0 ){

		for( cnt = 0; cnt < tr->num; cnt++ ){
			current_characters[cnt]
				= (double)tr->characters[cnt]
				/ (double)tr->total;
		}

	}else{
						/* Case of denominator zero   */
		for( cnt = 0; cnt < tr->num; cnt++ ){
			current_characters[cnt] = 0;
		}
	}
						/* Calculate different value  */
						/*              tr and tf_cmp */
	for( cnt = 0; cnt < tf_cmp->num; cnt++ ){

		if( current_characters[cnt] == tf_cmp->characters[cnt] ){

						/* Case of equal              */
			current_characters[cnt] = 0;

		}else if( tf_cmp->characters[cnt] != 0 ){

						/* Case of normal(calculate)  */
			current_characters[cnt]
				= 1 - ( current_characters[cnt]
				/ tf_cmp->characters[cnt] );
		}else{
						/* Case of denominator zero   */
			current_characters[cnt] = 1;
		}
	}
						/* Calculate average          */
	average = 0;

	for( cnt = 0; cnt < tf_cmp->num; cnt++ ){
						/* Summary with absolute      */
		average += fabs( current_characters[cnt] );
	}

	average = average / (double)tf_cmp->num;

						/* return                     */
	return( average );

						/* Set match counter          */
	match_cnt = 0;

	for( cnt = 0; cnt < tf_cmp->num; cnt++ ){

						/* Compare each amino acid    */
		if( fabs( current_characters[cnt] ) <= range ){
						/* Match                      */
			match_cnt++;
		}
	}
						/* Return match count         */
	return( 1 - ((double)match_cnt / (double)tf_cmp->num) );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Compare all hmm value                                             */
/* Function Name : hmm_cmp                                                    */
/*                                                                            */
/* Detail : Compare all hmm value                                             */
/* Date   : 2011/02/01                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : double range          : tolerance                                 */
/*          TRNS tr[]             : Pointer of array of TRNS structure        */
/*                                  for each amino                            */
/*          TRNS_FOR_CMP tf_cmp[] : Pointer of array of TRNS_FOR_CMP structure*/
/*                                  for each amino                            */
/* Output : double                : Match rate                                */
/*                                                                            */
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

double hmm_cmp(
	double range,
	TRNS tr[],
	TRNS_FOR_CMP tf_cmp[]
){
						/* Loop counter               */
	long cnt;
						/* Number of processing char  */
	long processing_char_num;
						/* Number of average          */
	double average;

						/* Set processing char number */
	processing_char_num = tr[0].num;
						/* Initialize average         */
	average = 0;
						/* Compare hmm number         */
						/* and calculate              */
						/*     average of differences */
	for( cnt = 0; cnt < processing_char_num; cnt++ ){
						/* Summary of each amino acid */
		average += fabs(
			tr_tf_cmp( range,
				&tr[cnt],
				&tf_cmp[cnt]
			)
		);
	}

						/* Calculate average          */
	average = average / (double)processing_char_num;

						/* Return with average        */
	return( average );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Calculate hmm of sequence array                                   */
/* Function Name : calc_hmm                                                   */
/*                                                                            */
/* Detail : Calculate hmm of sequence array                                   */
/* Date   : 2011/02/01                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *sequence : target sequence                                  */
/*          long length    : Length of sequence                               */
/*          long offset    : Start of calculate in sequence                   */
/*          TRNS tr[]      : Pointer of array of TRNS structure               */
/*                                                                            */
/* Output : void                                                              */
/*                                                                            */
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

void calc_hmm(
	char *sequence,
	long length,
	long offset,
	TRNS from_tr[]
){
						/* General purpose counter    */
	long match_cnt;
						/* Number of processing char  */
	long processing_char_num;
						/* Character set              */
						/*       for processing       */
	char *processing_char_set;
						/* Last character(from)       */
	int from_char;
						/* Current character(to)      */
	int to_char;
						/* Loop counger               */
	int cnt;

						/* Set processing char number */
	processing_char_num = from_tr[0].num;
						/* Set processing char set    */
	processing_char_set = from_tr[0].character_set;
						/* Reset each TRNS            */
	for( cnt = 0; cnt < processing_char_num; cnt++ ){
		reset_tr( &from_tr[cnt] );
	}
						/* Start from offset          */
	match_cnt = offset;
						/* Decrement length           */
						/* because counter start of 0 */
	length -= 1;
						/* Init last_char             */
	from_char = 0;

	while(1){
						/* Get processing character   */
		to_char = sequence[match_cnt];

		for( cnt = 0; cnt < processing_char_num; cnt++ ){

			if( from_char == (int)processing_char_set[cnt] ){
						/* Call function of           */
						/*       counted transition   */
				from_x( &from_tr[cnt], to_char );
				break;
			}
		}
						/* Store current character    */
		from_char = to_char;

						/* Loop from offset           */
						/*        to offset - 1       */
		if( match_cnt < length ){
						/* Counter increment          */
			match_cnt++;
		}else{
						/* If counter come to tail    */
						/* then counter is top        */
			match_cnt = 0;
		}
						/* When counter became offset */
						/* then loop end              */
						/* (that one rotation)        */
		if( match_cnt == offset ){
			break;
		}
	}
}

/******************************************************************************/
/*                                                                            */
/* Title  : Print TRNS_FOR_CMP                                                */
/* Function Name : print_trns_for_cmp                                         */
/*                                                                            */
/* Detail : prinit_trns_for_cmp                                               */
/* Date   : 2011/02/06                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *TRNS_FOR_CMP : Pointer of TRNS_FOR_CMP                      */
/*                                                                            */
/* Output : void                                                              */
/*                                                                            */
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
void print_trns_for_cmp( TRNS_FOR_CMP *tf_cmp ){

	int cnt;

	for( cnt = 0; cnt < tf_cmp->num - 1; cnt++ ){
		printf("%.12f,",tf_cmp->characters[cnt]);
	}

	printf("%.12f\n",tf_cmp->characters[tf_cmp->num]);
}
