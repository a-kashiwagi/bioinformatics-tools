/******************************************************************************/
/*                                                                            */
/* Title  : Hidden Markov Model - Learning procedure                          */
/* Program Name : hmm_learn.c                                                 */
/*                                                                            */
/* Detail : Learning procedure of Hidden Markov Model                         */
/* Date   : 2010/0902                                                         */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2011/02/05                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Modify to both nucleotide and amino acid.                         */
/*                                                                            */
/* Date   : 2011/03/24                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Modify to module for LCS                                          */
/*                                                                            */
/* Date   : 2015/04/18                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Add procedure that a prescan order.                               */
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
#include <ctype.h>
#include <math.h>

#include "hmm.h"
#include "lcs.h"

						/* Number of char             */
						/*         for processing     */
int processing_char_num;
						/* Character set              */
						/*         for processing     */
char processing_char_set[MAX_CHAR_SET_NUM + 1];

/******************************************************************************/
/*                                                                            */
/* Title  : Function of initialize to hmm procedures                          */
/* function Name : init_hmm_procedure()                                       */
/*                                                                            */
/* Detail : Initialize to hmm procedure                                       */
/* Date   : 2011/03/24                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : int  : alignment mode [ 0:AMINOACID or 1:NUCLEOTIDE ]             */
/*                                                                            */
/* Output : int  : alignment mode [ 0:AMINOACID or 1:NUCLEOTIDE ]             */
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

int init_hmm_procedure( int mode ){
						/* Set global value           */

						/* aliginment_mode is         */
						/*       declared in hmm.h    */
	alignment_mode = mode;
						/* Check for arguments        */
	if( alignment_mode == AMINOACID ){
						/* Amino Acid mode            */

		processing_char_num = AMINO_ACID_NUM;
						/* Set number of              */
						/*        character set       */
		strcpy( processing_char_set, AMINO_ACID_ONE_CHAR );
						/* Set character set          */

		processing_char_set[AMINO_ACID_NUM] = '\0';
						/* Set terminator             */

	}else{
						/* Nucleotide mode            */

		processing_char_num = NUCLEOTIDE_NUM;
						/* Set number of              */
						/*        character set       */
		strcpy( processing_char_set, NUCLEOTIDE_ONE_CHAR );
						/* Set character set          */

		processing_char_set[NUCLEOTIDE_NUM] = '\0';
						/* Set terminator             */
	}
						/* Return alignment_mode      */
	return( alignment_mode );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Function of Hidden Markov Model - malloc tr array set procedure   */
/* function Name : init_tr_set()                                              */
/*                                                                            */
/* Detail : Procedure of malloc tr array set                                  */
/* Date   : 2011/03/08                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : void  :                                                           */
/*                                                                            */
/* Output : TRNS * : Pointer of allocated tr array set                        */
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

TRNS *init_tr_set( void ){
						/* Counter                    */
	long cnt;
						/* Pointer of TRNS            */
	TRNS *tr;

						/* Allocate TRNS array        */
	tr = malloc( sizeof(TRNS) * processing_char_num );
	if( tr == NULL ){
		return NULL;
	}
						/* Initialize each TRNS array */
	for( cnt = 0; cnt < processing_char_num; cnt++ ){
		init_tr(
			&tr[cnt],
			processing_char_set,
			processing_char_num
		);
	}
						/* Return TRNS pointer        */
	return( tr );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Function of Hidden Markov Model - free tr array set procedure     */
/* function Name : free_tr_set()                                              */
/*                                                                            */
/* Detail : Procedure of free tr array set                                    */
/* Date   : 2011/03/08                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : TRNS * : Pointer of TRNS[] array set                              */
/*                                                                            */
/* Output : TRNS * : NULL Pointer                                             */
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

TRNS *free_tr_set( TRNS *tr ){
						/* Counter                    */
	long cnt;

						/* Free tr.characters         */
	for( cnt = 0; cnt < processing_char_num; cnt++ ){
		//tr[cnt].free( &tr[cnt] );
		free_tr( &tr[cnt] );
	}
						/* Free tr array              */
	free( tr );
						/* Return NULL                */
	return( NULL );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Function of Hidden Markov Model - Learning procedure              */
/* function Name : hmm_learn()                                                */
/*                                                                            */
/* Detail : Procedure of hmm_learn                                            */
/* Date   : 2010/09/02                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *in_sequence  : Target sequence                              */
/*          TRNS *tr           : Pointer of TRNS structure                    */
/*                                                                            */
/* Output : int : Normal terminate [0]                                        */
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
int hmm_learn( char *in_sequence, TRNS *tr ){

	int   in_char;				/* Input character            */
	int   last_char;			/* Last character             */
	long  cnt;				/* Counter                    */
	long  cursor;				/* Counter of currsor         */

						/* Initialize                 */
	last_char = '\0';			/* Reset last character       */

	cursor = 0;				/* Reset cursor counter       */

						/* Get a character            */
	in_char = in_sequence[cursor++];

	while( in_char != '\0' ){
						/* Transfer to upper          */
		in_char = toupper( in_char );
						/* Loop for each characters   */
		for( cnt = 0; cnt < processing_char_num; cnt++ ){

						/* Check for character        */
			if( last_char == (int)processing_char_set[cnt] ){

						/* Count to transition        */
				from_x( &tr[cnt], in_char );
				break;
			}
		}
						/* Store last character       */
		last_char = in_char;
						/* Get a next character       */
		in_char = in_sequence[cursor++];
	}
						/* Normal terminate          */
	return(0);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Function of Hidden Markov Model - Scan procedure                  */
/* Function Name : hmm_scn_global()                                           */
/*                                                                            */
/* Detail : Scan procedure of Hidden Markov Model for global search           */
/* Date   : 2011/02/01                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *in_sequence  : Target sequence                              */
/*          TRNS *target_tr    : Pointer of target TRNS structure             */
/*          double range       : Range                                        */
/*          long *ans_start    : Pointer of start position for answer         */
/*          long *ans_end      : Pointer of end   position for answer         */
/*          double *ans_hmm    : Pointer of hmm number for answer             */
/*                                                                            */
/* Output : int : Normal terminate [0]                                        */
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

int hmm_scn_global(
	char *in_sequence,
	TRNS *target_tr,
	double range,
	long *ans_start,
	long *ans_end,
	double *ans_hmm
){
						/* Input character from stdin */
	int in_char;
						/* Inputed last character     */
	int last_char;
						/* Sequence                   */
	char *sequence;
						/* Sequence length            */
	long length;
						/* Offset cnt                 */
	long offset;
						/* Nubmer of hmm              */
	double hmm_number;
						/* Counter of current         */
	long current_cnt;
						/* Counter                    */
	int cnt;
						/* Counter for in_char        */
    	long cursor;

						/* Number for minimum         */
	double minimum_hmm_number;
						/* for hmm_number             */
	long   minimum_current_cnt;
						/* for current_cnt            */
	long   minimum_offset;
						/* for offset                 */

						/* Structure for compare      */

						/* For calculated target hmm  */
	TRNS_FOR_CMP *target_tf_cmp;
						/* For calculate source hmm   */
	TRNS *source_tr;

						/* Allocate memory            */
						/*         to TRNS            */
	source_tr = malloc( sizeof(TRNS) * processing_char_num );
	if( source_tr == NULL ){
		return 1;
	}

						/* Initialize TRNS            */
	for( cnt = 0; cnt < processing_char_num; cnt++ ){
						/* Allocate memory to each    */
						/*    TRNS.characters         */
		init_tr(
			&source_tr[cnt],
			processing_char_set,
			processing_char_num
		);
	}
						/* Data load from hmm file    */
						/* Allocate memory            */
						/*         to TRNS_FOR_CMP    */
	target_tf_cmp = malloc( sizeof(TRNS_FOR_CMP) * processing_char_num );
	if( target_tf_cmp == NULL ){
		return 1;
	}
						/* Initialize TRNS_FOR_CMP    */
	for( cnt = 0; cnt < processing_char_num; cnt++ ){
						/* Allocate memory to each    */
						/*    TRNS_FOR_CMP.characters */
		init_tf_cmp(
			&target_tf_cmp[cnt],
			processing_char_set,
			processing_char_num
		);
	}
						/* Data load from tr         */
						/*           to TRNS_FOR_CMP */
	length = load_hmm_data(
		target_tr,
		target_tf_cmp
	);
						/* Because length is 1 start. */
						/* (not 0 start)              */
	length += 1;
						/* Initializeing array        */

						/* Counter of current         */
	current_cnt = 0;
						/* Initializeing last_char    */
	last_char = 0;
						/* Initializeing cursor       */
    	cursor = 0;
						/* Memory allocate            */
						/*         for sequence array */
	sequence = malloc( sizeof(char) * (length + 1) );
	if( sequence == NULL ){
		return 1;
	}
						/* Set null terminater        */
	sequence[length] = '\0';
						/* Pre loop that get part of  */
						/* sequence array from STDIN  */

	in_char = in_sequence[cursor++];
						/* Get a character from stdin */

	while( in_char != '\0' && current_cnt < (length - 1) ){

						/* Transfer to upper char     */
		in_char = toupper( in_char );
						/* Set in_char                */
						/*      to sequence array     */
		sequence[current_cnt] = in_char;

						/* Get a next character       */
		in_char = in_sequence[cursor++];
						/* Increment                  */
		current_cnt++;
	}
						/* Set offset                 */
	offset = current_cnt;
						/* Case of short sequence     */
	if( (length - 1) > current_cnt ){
						/*    Modify number of length */
		length = current_cnt + 1;
	}

						/* Init minimum_hmm_number    */
	minimum_hmm_number = range;
						/* Init minimum_current_cnt   */
	minimum_current_cnt = -1;
						/* Main loop                  */
	do{
						/* Transfer to upper char     */
		in_char = toupper( in_char );

						/* Set in_char                */
						/*     to sequence array      */
		sequence[offset] = in_char;
						/* Increment offset counter   */
		offset++;

		if( offset > (length - 1) ){
						/* If offset became tail of   */
						/* array then offset is 0     */
			offset = 0;
		}
						/* Calculate hmm of sequence  */
		calc_hmm(
			sequence,
			length,
			offset,
			source_tr
		);
						/* Case of Match              */
		hmm_number = hmm_cmp(
			range,
			source_tr,
			target_tf_cmp
		);
						/* Change to absolute nubmer  */
		hmm_number = fabs( hmm_number );

						/* Store minimum numbers      */
		if( hmm_number <= minimum_hmm_number ){

			minimum_hmm_number = hmm_number;
						/* Number of hmm              */

			minimum_current_cnt = current_cnt;
						/* Number of current count    */

			minimum_offset = offset;
						/* Number of offset           */
		}
						/* Store last character       */
		last_char = in_char;
						/* Get a next character       */
		in_char = in_sequence[cursor++];
						/* Increment current counter  */
		current_cnt++;

	} while( in_char != '\0' );
						/* Print out                  */
	if( minimum_current_cnt != -1 ){
						/* Start, End, HMM number     */
		/* debug write
		printf("%ld,%ld,%.12f\n",
			(minimum_current_cnt + 1) - (length - 1),
			(minimum_current_cnt + 1),
			minimum_hmm_number
		);
		*/
						/* Start position             */
	    	*ans_start = (minimum_current_cnt + 1) - (length - 1);
	    					/* End position               */
	    	*ans_end = minimum_current_cnt + 1;
	    					/* HMM number                 */
	    	*ans_hmm = minimum_hmm_number;
	}else{
	    					/* Can not find               */
	     	*ans_start = -1;
	    	*ans_end   = -1;
	    	*ans_hmm   = -1;
	}
						/* Free to memory             */

						/* For target_tf_cmp          */
	for( cnt = 0; cnt < processing_char_num; cnt++ ){
		free_tf_cmp( &target_tf_cmp[cnt] );
	}

	free( target_tf_cmp );

						/* For source_tr              */
	for( cnt = 0; cnt < processing_char_num; cnt++ ){
		free_tr( &source_tr[cnt] );
	}

	free( source_tr );
						/* For sequence               */
	free( sequence );
						/* Normal terminate           */
    	return(0);
}


/******************************************************************************/
/*                                                                            */
/* Title  : Function of Hidden Markov Model - Scan procedure                  */
/* Function Name : hmm_scn_local()                                            */
/*                                                                            */
/* Detail : Scan procedure of Hidden Markov Model for local search            */
/* Date   : 2011/02/01                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *in_sequence  : Target sequence                              */
/*          TRNS *tr           : Pointer of TRNS structure                    */
/*          double range       : Range                                        */
/*          long start         : Number of strat position                     */
/*          long end           : Number of end   position                     */
/*          long *ans_start    : Pointer of start position for answer         */
/*          long *ans_end      : Pointer of end   position for answer         */
/*          double *ans_hmm    : Pointer of hmm number for answer             */
/*                                                                            */
/* Output : int : Normal terminate [0]                                        */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2015/04/18                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Add procedure that a prescan order                                */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int hmm_scn_local(
    char *in_sequence,
    TRNS *tr,
    double range,
    long start,
    long end,
    long *ans_start,
    long *ans_end,
    double *ans_hmm,
    double *prescan_orders_p,
    long *prescan_hmm_s_loc_p,
    long *prescan_hmm_e_loc_p
){
						/* Input character from stdin */
	int in_char;
						/* Inputed last character     */
	int last_char;
						/* Sequence                   */
	char *sequence;
						/* Sequence length            */
	long length;
						/* Length of addtional        */
	long length_add;
						/* Nubmer of hmm              */
	double hmm_number;
						/* Counter of current         */
	long current_cnt;
						/* Counter                    */
	long cnt;
						/* Number for minimum         */
	double minimum_hmm_number;
						/* for hmm_number             */
	long minimum_current_cnt;
						/* for current_cnt            */
	long current_loc;
						/* Location of current        */
	long limit_loc;
						/* location of limit          */
	double hmm_order[PRESCNRANK];
	long   hmm_s_loc[PRESCNRANK];
	long   hmm_e_loc[PRESCNRANK];

	long order_cnt;
	long shift_cnt;
						/* Structure for compare      */
	TRNS_FOR_CMP *tf_cmp;
						/* Allocate memory            */
						/*         to TRNS_FOR_CMP    */
	tf_cmp = malloc( sizeof(TRNS_FOR_CMP) * processing_char_num );
	if( tf_cmp == NULL ){
		return 1;
	}
						/* Initialize TRNS_FOR_CMP    */
	for( cnt = 0; cnt < processing_char_num; cnt++ ){
						/* Allocate memory to each    */
						/*    TRNS_FOR_CMP.characters */
		init_tf_cmp(
			&tf_cmp[cnt],
			processing_char_set,
			processing_char_num
		);
	}
						/* Data load from hmm file    */
    	length = load_hmm_data(
		tr,
		tf_cmp
	);
						/* Because length is 1 start. */
						/* (not 0 start)              */
	length += 1;
						/* Addtional 30[%]            */
	length_add = end - (start - 1);
						/* Initializeing array        */

						/* Counter of current         */
	current_cnt = 0;
						/* Initializeing last_char    */
	last_char = 0;
						/* Memory allocate            */
						/*         for sequence array */
	sequence = malloc( sizeof(char) * (length_add + 1) );
	if( sequence == NULL ){
		return 1;
	}
						/* Set null terminater        */
	sequence[length_add] = '\0';
						/* Pre loop that get part of  */
						/* sequence array from STDIN  */
	for( current_cnt = 0; current_cnt < start; current_cnt++ ){
		in_char = in_sequence[current_cnt++];
	}
						/* Get a character from stdin */
	cnt = 0;
	while( in_char != '\0' && current_cnt < (start + length_add) ){

						/* Transfer to upper char     */
		in_char = toupper( in_char );
						/* Set in_char                */
						/*      to sequence array     */
		sequence[cnt] = in_char;
		cnt++;
						/* Get a next character       */
		in_char = in_sequence[current_cnt++];
						/* Increment                  */
		current_cnt++;
	}
						/* Sequence tarminate         */
	sequence[cnt] = '\0';
						/* Case of short sequence     */
	if( (length_add - 1) > current_cnt ){
						/*    Modify number of length */
		length_add = current_cnt + 1;
	}
						/* Init minimum_hmm_number    */
	minimum_hmm_number = range;
	memset(hmm_order, 0, sizeof(double) * PRESCNRANK);
	memset(hmm_s_loc,  0, sizeof(long)   * PRESCNRANK);
	memset(hmm_e_loc,  0, sizeof(long)   * PRESCNRANK);
	hmm_order[0] = range;
	current_loc = 0;

	/*
	for( order_cnt = 0; order_cnt < PRESCNRANK; order_cnt++ ){

		printf("hmm_order[%d]:%f sloc[%d]:%ld eloc[%d]:%ld\n",
			order_cnt,hmm_order[order_cnt],
			order_cnt,hmm_s_loc[order_cnt],
			order_cnt,hmm_e_loc[order_cnt]
		);
	}
	*/
						/* Init minimum_current_cnt   */
	minimum_current_cnt = -1;
						/* Calculate location of limit*/
	limit_loc = floorl((double)length_add * 0.7);
						/* Reset count                */
	cnt = 0;
						/* Main loop                  */
	do{
						/* Calculate hmm of sequence  */
		calc_hmm(
			&sequence[cnt],
			length_add - cnt,
			0,
			tr
		);
						/* Case of Match              */
		hmm_number = hmm_cmp(
			range,
			tr,
			tf_cmp
		);
						/* Change to absolute nubmer  */
		hmm_number = fabs( hmm_number );

						/* Store minimum numbers      */
		for( order_cnt = 0; order_cnt < PRESCNRANK - 1; order_cnt++ ){

			// if( hmm_number <= minimum_hmm_number )
			if( hmm_number < hmm_order[order_cnt] ){

				for( shift_cnt = PRESCNRANK - 2;
				     shift_cnt >= order_cnt;
				     shift_cnt-- ){

					hmm_order[shift_cnt + 1]
						= hmm_order[shift_cnt];

					hmm_s_loc[shift_cnt + 1]
						= hmm_s_loc[shift_cnt];

					hmm_e_loc[shift_cnt + 1]
						= hmm_e_loc[shift_cnt];
				}

				//minimum_hmm_number = hmm_number;
						/* Number of hmm              */
				break;
			}
		}

		//printf("%ld %f %ld\n",order_cnt,hmm_number,current_loc);

						/* Number of current count    */
		minimum_current_cnt = cnt;
		hmm_order[order_cnt] = hmm_number;
		hmm_s_loc[order_cnt] = start + current_loc;
		hmm_e_loc[order_cnt] = end;
		// hmm_loc[order_cnt] = current_loc;
						/* Increment counter          */
		cnt++;
						/* Calculate current location */
		current_loc = floorl((double)length_add - (double)cnt);

	} while( current_loc > limit_loc );

	memcpy( prescan_orders_p,   hmm_order, sizeof(double) * PRESCNRANK );
	memcpy( prescan_hmm_s_loc_p, hmm_s_loc,  sizeof(long)   * PRESCNRANK );
	memcpy( prescan_hmm_e_loc_p, hmm_e_loc,  sizeof(long)   * PRESCNRANK );

	/*
	for( order_cnt = 0; order_cnt < PRESCNRANK; order_cnt++ ){

		printf("hmm_order[%d]:%f sloc[%d]:%ld eloc[%d]:%ld\n",
			order_cnt,hmm_order[order_cnt],
			order_cnt,hmm_s_loc[order_cnt],
			order_cnt,hmm_e_loc[order_cnt]
		);
	}
	*/

	minimum_hmm_number = hmm_order[0];
	//minimum_current_loc = hmm_s_loc[0];
						/* Print out                  */
	if( minimum_current_cnt != -1 ){
						/* Start, End, HMM number     */
		/* debug write
		printf("%ld,%ld,%.12f\n",
			start + minimum_current_cnt,
			end,
			minimum_hmm_number
		);
	     	*/
	    					/* Start position             */
	    	// *ans_start = start + minimum_current_cnt;
	    	*ans_start = hmm_s_loc[0];
	    					/* End position               */
	    	// *ans_end = end;
		*ans_end = hmm_e_loc[0];
	    					/* HMM number                 */
	    	// *ans_hmm = minimum_hmm_number;
	    	*ans_hmm = hmm_order[0];
	}else{
	    					/* Can not find               */
	    	*ans_start = -1;
	    	*ans_end = -1;
	    	*ans_hmm = -1;
	}
						/* Free to memory             */
	for( cnt = 0; cnt < processing_char_num; cnt++ ){
		free_tf_cmp( &tf_cmp[cnt] );
	}

	free( tf_cmp );
						/* Normal terminate           */
	return(0);
}
