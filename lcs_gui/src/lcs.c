/******************************************************************************/
/*                                                                            */
/* Title  : Longest Common Subsequence of Dynamic Programming                 */
/*                   by An Introduction to Bioinformatics Algorithms          */
/*                                                                            */
/* Program Name : LCS                                                         */
/*                                                                            */
/* Detail :                                                                   */
/* Date   : 2009/12/02                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/01/20                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added to find a site                                              */
/*                                                                            */
/* Date   : 2010/03/06                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added to local alignment and PrintOut() function                  */
/*                                                                            */
/* Date   : 2010/04/29                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added to Replace score ( blosum )                                 */
/*                                                                            */
/* Date   : 2010/08/22                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added procedure that convert to upper character                   */
/*                                                                            */
/* Date   : 2010/09/15                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Separated GUI and CUI sources                                     */
/*                                                                            */
/* Date   : 2010/09/30                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added arguments to PrintOut,PrintOutForTextView,                  */
/*          that is identites count, rate and score                           */
/*                                                                            */
/* Date   : 2010/10/08                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added procedure that is score chromatography.                     */
/*                                                                            */
/* Date   : 2014/06/10                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : The LCS calculation method changed to a Multi thread procedure.   */
/*                                                                            */
/* Date   : 2014/12/15                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Add parameter that select a dot matrix output                     */
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
#include <malloc.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include "lcs.h"
#include "hmm.h"

						/* Struct for replace score   */
typedef struct replace_score {
						/* v character                */
	char v_cd;

						/* w character                */
	char w_cd;

						/* replace score              */
	double score;

} RPLC_SCR;

RPLC_SCR rs[ REPLACE_NUM ];

						/* Declare grobal array       */

int  disp_flg;					/* Display flag               */
int  alignment_mode;				/* Aligment mode              */
int  gapscore_mode;				/* Gap score mode             */
int  scan_mode;					/* Pre scan mode              */
int  compare_mode;				/* Compare mode               */
int  sequence_mode;				/* Sequence mode              */

int output_mode = GUI_MODE;			/* Output mode CUI:0 / GUI:1  */

long match_num;					/* Number of match            */
long unmatch_num;				/* Number of unmatch          */
long d_num;					/* Number of gap penalty      */
long e_num;					/* Number of                  */
						/*    affine gap penalty      */
long rs_num;					/* Number of Replace score    */
						/*    amplification           */
int matrix_on;					/* Select a dot matrix output */
						/* Number of selected row     */
int region_order;				/*        of RegionCombo      */

/******************************************************************************/
/*                                                                            */
/* Title  : Set parameter for LCS                                             */
/* Function Name : set_lcs_param()                                            */
/*                                                                            */
/* Detail : main procedure of LCS                                             */
/* Date   : 2010/09/9                                                         */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : int  disp_flg       : Display flag                                */
/*          int  alignment_mode : Aligment mode                               */
/*          int  gapscore_mode  : Gap score mode                              */
/*          int  scan_mode      : Pre scan mode                               */
/*          int  compare_mode   : Compare mode                                */
/*          int  sequence_mode  : Sequence mode                               */
/*          int  matrix_on      : Dot matrix output                           */
/*          long match_num      : Number of match                             */
/*          long unmatch_num    : Number of unmatch                           */
/*          long d_num          : Number of gap penalty                       */
/*          long e_num          : Number of affine gap penalty                */
/*          long rs_num         : Number of Replace score amplification       */
/*                                                                            */
/* Output : return value [ 0 : Normal Terminate ]                             */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2014/12/15                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Add parameter that select dot matrix output                       */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int set_lcs_param(
	int  in_disp_flg,
	int  in_alignment_mode,	
	int  in_gapscore_mode,
    	int  in_scan_mode,
	int  in_compare_mode,
	int  in_sequence_mode,
	int  in_matrix_on,
	long in_match_num,
	long in_unmatch_num,
	long in_d_num,
	long in_e_num,
	long in_rs_num,
	int  in_region_order
){


						/* Display flag               */
	disp_flg = in_disp_flg;

						/* Aligment mode              */
	alignment_mode = in_alignment_mode;

						/* Gap score mode             */
	gapscore_mode = in_gapscore_mode;

    						/* Pre scan mode              */
    	scan_mode = in_scan_mode;

						/* Compare mode               */
	compare_mode = in_compare_mode;

						/* Sequence mode              */
	sequence_mode = in_sequence_mode;

						/* Number of match            */
	match_num = in_match_num;

						/* Number of unmatch          */
	unmatch_num = in_unmatch_num;

						/* Number of gap penalty      */
	d_num = in_d_num;

						/* Number of                  */
						/*    affine gap penalty      */
	e_num = in_e_num;

						/* Number of Replace score    */
						/*    amplification           */
	rs_num = in_rs_num;
						/* Select a dot matrix output */
	matrix_on = in_matrix_on;
						/* Number of selected row     */
						/*        of RegionCombo      */
	region_order = in_region_order;

	return(0);
}

/******************************************************************************/
/*                                                                            */
/* Title  : main function for CUI                                             */
/* Function Name : main                                                       */
/*                                                                            */
/* Detail : main function of LCS for Character user interface                 */
/* Date   : 2010/09/09                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : int argc                                                          */
/*          char *argv[]                                                      */
/*                                                                            */
/* Output : return value [ 0 : Normal Terminate ] [ 1 : Error ]               */
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

int cui_main( int argc, char *argv[] ){
						/* Return code                */
	int ret;
						/* Geleral purpose counter    */
	int cnt;
	char *endptr;				/* For strtol return value    */

	char SourceFileName[ 1024 ];		/* File Name of source file   */
	char TargetFileName[ 1024 ];		/* File Name of target file   */
	long SourceFileSize;			/* Size of source file        */
	long TargetFileSize;			/* Size of target file        */
	char *v;				/* Sequence of v              */
	char *w;				/* Sequence of w              */
	long inum;				/* Number of array count of v */
						/*            and             */
						/* File Size of source file   */
						
	long jnum;				/* Number of array count of w */
						/*            and             */
						/* File Size of target file   */

	output_mode = CUI_MODE;			/* Set output mode CUI        */

						/* Check for argument counter */
	if( argc < 3 ){
		fprintf(stderr, "  Usage: lcs");
		fprintf(stderr, " [ Options ] SourceFileName TargetFileName\n");
		fprintf(stderr, "Options:\n");
		fprintf(stderr, "  -cui : Character User Interface mode\n");
		fprintf(stderr, "  -gui : Graphical User Interface mode");
		fprintf(stderr, " - default\n");
		fprintf(stderr, "  -v   : Output v   sequence\n");
		fprintf(stderr, "  -w   : Output w   sequence\n");
		fprintf(stderr, "  -ans : Output ans sequence - default\n");
		fprintf(stderr, "  -gap : Output gap sequence");
		fprintf(stderr, " ( \"+\" Insertion \"-\" Deletion )\n");
		fprintf(stderr, "  -eg  : Output eg  matrix\n");
		fprintf(stderr, "  -ss  : Output ss  matrix\n");
		fprintf(stderr, "  -bp  : Output bp  matrix\n");
		fprintf(stderr, "  -n   : Compare by Nucleotide - default\n");
		fprintf(stderr, "  -a   : Compare by Amino Acid\n");
		fprintf(stderr, "  -part: Compare part of sequence");
		fprintf(stderr, " - default\n");
		fprintf(stderr, "  -all : Compare all sequence\n");
	    	fprintf(stderr, "  -id  : Pre scan by identity match\n");
	    	fprintf(stderr, "  -hmm : Pre scan by hmm - default\n");
		fprintf(stderr, "  -ga  : Global alignment mode - default\n");
		fprintf(stderr, "  -la  : Local  alignment mode\n");
		fprintf(stderr, "  -lg  : Liner gap  score - default\n");
		fprintf(stderr, "  -ag  : Affine gap score\n");
		fprintf(stderr, "  -mn number : Integer number of");
		fprintf(stderr, " match - default %d\n",DEF_MATCH_NUM);
		fprintf(stderr, "  -un number : Integer number of");
		fprintf(stderr, " unmatch - default %d\n",DEF_UNMATCH_NUM);
		fprintf(stderr, "  -dn number : Integer number of");
		fprintf(stderr, " gap penalry - default %d\n",DEF_D_NUM);
		fprintf(stderr, "  -en number : Integer number of");
		fprintf(stderr, " affine gap penalry - default %d\n",DEF_E_NUM);
		fprintf(stderr, "\n");
		exit(1);
						/* Error terminate            */
	}
						/* option flag reset          */
	disp_flg = OFF;
						/* Default alignment mode     */
	alignment_mode = GLOBAL_ALIGNMENT;
						/* Gap score mode             */
	gapscore_mode = LINER_GAP_SCORE;
						/* Pre scan mode              */
    	scan_mode = HMMSCAN;
						/* Compare mode               */
	compare_mode = NUCLEOTIDE;
						/* Sequence mode              */
	sequence_mode = PARTOFSEQUENCE;
						/* Set default number         */
	match_num = DEF_MATCH_NUM;		/* Number of match            */
	unmatch_num = DEF_UNMATCH_NUM;		/* Number of unmatch          */
	d_num = DEF_D_NUM;			/* Number of gap penalty      */
	e_num = DEF_E_NUM;			/* Nubmer of                  */
						/*     affine gap penalty     */
	rs_num = DEF_RS_NUM;			/* Number of Replace score    */
						/*    amplification           */

						/* Set argument counter       */
	cnt = argc;
						/* Copy from argument         */
	cnt--;
	strcpy( TargetFileName, argv[cnt] );
						/* Copy from argument         */
	cnt--;
	strcpy( SourceFileName, argv[cnt] );

	for(; cnt > 0; cnt-- ){

		if( strcmp( argv[cnt], "-n" ) == 0 ){
						/* Nucleotide mode            */
			compare_mode = NUCLEOTIDE;
		
		}else if( strcmp( argv[cnt], "-a" ) == 0 ){
						/* Amino acid mode            */
			compare_mode = AMINOACID;

		}else if( strcmp( argv[cnt], "-all" ) == 0 ){
						/* Compare all sequence       */
			sequence_mode = ALLSEQUENCE;

		}else if( strcmp( argv[cnt], "-part" ) == 0 ){
						/* Compare part of sequence   */
			sequence_mode = PARTOFSEQUENCE;

		}else if( strcmp( argv[cnt], "-id" ) == 0 ){
						/* Pre scan by identity match */
			scan_mode = IDENTSCAN;

		}else if( strcmp( argv[cnt], "-hmm" ) == 0 ){
						/* Pre scan by hmm            */
			scan_mode = HMMSCAN;

		}else if( strcmp( argv[cnt], "-la" ) == 0 ){
						/* Local alignment mode       */
			alignment_mode = LOCAL_ALIGNMENT;
		
		}else if( strcmp( argv[cnt], "-ga" ) == 0 ){
						/* Global alignment mode      */
			alignment_mode = GLOBAL_ALIGNMENT;

		}else if( strcmp( argv[cnt], "-lg" ) == 0 ){
						/* Liner gap score mode       */
			gapscore_mode = LINER_GAP_SCORE;

		}else if( strcmp( argv[cnt], "-ag" ) == 0 ){
						/* Affine gap score mode      */
			gapscore_mode = AFFINE_GAP_SCORE;

		}else if( strcmp( argv[cnt], "-mn" ) == 0 ){
						/* Number of match            */
			match_num = strtol( argv[cnt+1], &endptr, 0 );
			if( *endptr != '\0' ){
				fprintf(stderr,
					"Parameter error to [%s] in [%s %s]\n",
					endptr,argv[cnt],argv[cnt+1]
				);
				exit(1);
			}

		}else if( strcmp( argv[cnt], "-un" ) == 0 ){
						/* Number of unmatch          */
			unmatch_num = strtol( argv[cnt+1], &endptr, 0 );
			if( *endptr != '\0' ){
				fprintf(stderr,
					"Parameter error to [%s] in [%s %s]\n",
					endptr,argv[cnt],argv[cnt+1]
				);
				exit(1);
			}

		}else if( strcmp( argv[cnt], "-dn" ) == 0 ){
						/* Number of gap penalty      */
			d_num = strtol( argv[cnt+1], &endptr, 0 );
			if( *endptr != '\0' ){
				fprintf(stderr,
					"Parameter error to [%s] in [%s %s]\n",
					endptr,argv[cnt],argv[cnt+1]
				);
				exit(1);
			}

		}else if( strcmp( argv[cnt], "-en" ) == 0 ){
						/* Number of                  */
						/*    affine gap penalty      */
			e_num = strtol( argv[cnt+1], &endptr, 0 );
			if( *endptr != '\0' ){
				fprintf(stderr,
					"Parameter error to [%s] in [%s %s]\n",
					endptr,argv[cnt],argv[cnt+1]
				);
				exit(1);
			}

		}else if( strcmp( argv[cnt], "-v" ) == 0 ){
						/* v sequence flag on         */
			disp_flg = disp_flg | V_DISP_FLG;
			
		}else if( strcmp( argv[cnt], "-w" ) == 0 ){
						/* w sequence flag on         */
			disp_flg = disp_flg | W_DISP_FLG;
			
		}else if( strcmp( argv[cnt], "-gap" ) == 0 ){
						/* gap sequence flag on       */
			disp_flg = disp_flg | GAP_DISP_FLG;
		
		}else if( strcmp( argv[cnt], "-eg" ) == 0 ){
						/* eg matrix flag on          */
			disp_flg = disp_flg | EG_DISP_FLG;
		
		}else if( strcmp( argv[cnt], "-ss" ) == 0 ){
						/* ss matrix flag on          */
			disp_flg = disp_flg | SS_DISP_FLG;
		
		}else if( strcmp( argv[cnt], "-bp" ) == 0 ){
						/* bp matrix flag on          */
			disp_flg = disp_flg | BP_DISP_FLG;

		}else if( strcmp( argv[cnt], "-ans" ) == 0 ){
						/* ans sequence flag on       */
			disp_flg = disp_flg | ANS_DISP_FLG;
		}
	}

	if( disp_flg == 0 ){
						/* Default switch             */
		disp_flg = disp_flg | ANS_DISP_FLG;
	}
	
						/* Check for source file size */
	SourceFileSize = ChkFileSize( SourceFileName );
	if( SourceFileSize < 0 ){
						/* Error terminate            */
		fprintf(stderr, "%s file not found.\n", SourceFileName );
		exit(1);
	}

						/* Check for target file size */
	TargetFileSize = ChkFileSize( TargetFileName );
	if( TargetFileSize < 0 ){
						/* Error terminate            */
		fprintf(stderr, "%s file not found.\n", TargetFileName );
		exit(1);
	}

						/* Memory allocate of v and w */
						/* Incriment of jnum,         */
						/*   Footer of NULL.          */
	v = (char *)malloc( sizeof(char) * SourceFileSize + 1);
	if( v == NULL ){

		printf("Can't allocate a v memory.\n");
		return 1;
	}

	w = (char *)malloc( sizeof(char) * TargetFileSize + 1);
	if( w == NULL ){

		printf("Can't allocate a w memory.\n");
		return 1;
	}
	
						/* Zero padding               */
	memset( v, '\0', (sizeof(char) * SourceFileSize) );
	memset( w, '\0', (sizeof(char) * TargetFileSize) );
						/* Get sequence of v          */
	inum = GetSequence( SourceFileName, v );
	if( inum == -1 ){
					
                                         	/* Error terminate            */
		fprintf(
			stderr,
			"Error in getting sequence from %s.\n",
			SourceFileName
		);
		exit(1);
	}
	
						/* Get sequence of w          */
	jnum = GetSequence( TargetFileName, w );
	if( jnum == -1 ){
						/* Error terminate            */
		fprintf(
			stderr,
			"Error in getting sequence from %s.\n",
			TargetFileName
		);
		exit(1);
	}
/*
	set_lcs_param(
	        disp_flg,
		alignment_mode,
		gapscore_mode,
	    	scan_mode,
		compare_mode,
		sequence_mode
		match_num,
		unmatch_num,
		d_num,
		e_num,
		rs_num
	);
*/
						/* Call lcs function          */
	ret = lcs( v, w, inum, jnum );
						/* Normail terminate          */
	exit(ret);
}

/******************************************************************************/
/*                                                                            */
/* Title  : searching a best match parts of inum                              */
/* Function Name : num_best_matches                                           */
/*                                                                            */
/* Detail : searching a best match parts of inum                              */
/* Date   : 2015/03/31                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long inum             : number of i                               */
/*          long jnum             : number of j                               */
/*          char *v               : pointer of v sequence                     */
/*          char *w               : pointer of w sequence                     */
/*          long *humming_order   : order of humming distance                 */
/*          long *humming_v_loc   : location of humming distance              */
/*          long *humming_w_loc   : location of humming distance              */
/*          long *v_lc_from_out   : start location of v                       */
/*          long *w_lc_from_out   : start location of w                       */
/*          long *best_match_out  : number of a best match                    */
/*                                                                            */
/* Output : return value [ 0 : Normal Terminate ] [ 1 : Error ]               */
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

int inum_best_matches(
        long inum,
        long jnum,
        char *v,
        char *w,
        long *humming_order,
        long *humming_v_loc,
        long *humming_w_loc,
	long *v_lc_from_out,
	long *w_lc_from_out,
	long *best_match_out
){
        long cnt;
        long order_cnt;
        long shift_cnt;
        double ret;

        double best_match;
        long v_lc_from;
        long w_lc_from;

	best_match = *best_match_out;
	v_lc_from  = *v_lc_from_out;
	w_lc_from  = *w_lc_from_out;

        for( cnt = 0; cnt < inum; cnt++ ){
                                                // Call to function
                ret = Matches(
                        inum - cnt,
                        jnum,
                        &v[cnt],
                        w
                );

                for( order_cnt = 0; order_cnt < PRESCNRANK - 2; order_cnt++ ){
                                                // Choice biggest match
                                                //  by shift to v
                        if( humming_order[order_cnt] < ret ){

                                for( shift_cnt = PRESCNRANK - 2;
                                     shift_cnt >= order_cnt;
                                     shift_cnt-- ){

                                                // Store match number
                                        best_match = ret;
                                                // Choice sequence
                                        v_lc_from = cnt + 1;
                                        w_lc_from = 1;

                                        humming_order[shift_cnt + 1]
                                                = humming_order[shift_cnt];

                                        humming_v_loc[shift_cnt + 1]
                                                = humming_v_loc[shift_cnt];

                                        humming_w_loc[shift_cnt + 1]
                                                = humming_w_loc[shift_cnt];
                                }

						// Set humming order
                                humming_order[order_cnt] = ret;

						// Set location
                                humming_v_loc[order_cnt] = v_lc_from;
                                humming_w_loc[order_cnt] = w_lc_from;

                                break;
                        }
                }
        }

#ifdef DEBUG

	for( order_cnt = 0; order_cnt < PRESCNRANK; order_cnt++ ){

						// debug write
		printf("%ld,%ld,%ld\n",
			humming_order[order_cnt],
			humming_v_loc[order_cnt],
			humming_w_loc[order_cnt]
		);
	}
#endif
						// Calculate to target number
	*v_lc_from_out = v_lc_from;
	*w_lc_from_out = w_lc_from;
	*best_match_out = best_match;

        return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : searching a best match parts of jnum                              */
/* Function Name : num_best_matches                                           */
/*                                                                            */
/* Detail : searching a best match parts of jnum                              */
/* Date   : 2015/03/31                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long inum             : number of i                               */
/*          long jnum             : number of j                               */
/*          char *v               : pointer of v sequence                     */
/*          char *w               : pointer of w sequence                     */
/*          long *humming_order   : order of humming distance                 */
/*          long *humming_v_loc   : location of humming distance              */
/*          long *humming_w_loc   : location of humming distance              */
/*          long *v_lc_from_out   : start location of v                       */
/*          long *w_lc_from_out   : start location of w                       */
/*          long *best_match_out  : number of a best match                    */
/*                                                                            */
/* Output : return value [ 0 : Normal Terminate ] [ 1 : Error ]               */
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

int jnum_best_matches(
        long inum,
        long jnum,
        char *v,
        char *w,
        long *humming_order,
        long *humming_v_loc,
        long *humming_w_loc,
	long *v_lc_from_out,
	long *w_lc_from_out,
	long *best_match_out
){
        long cnt;
        long order_cnt;
        long shift_cnt;
        double ret;

        double best_match;
        long v_lc_from;
        long w_lc_from;

	best_match = *best_match_out;
	v_lc_from  = *v_lc_from_out;
	w_lc_from  = *w_lc_from_out;

        for( cnt = 0; cnt < jnum; cnt++ ){
                                                // Call to function
                ret = Matches(
                        inum,
                        jnum - cnt,
                        v,
                        &w[cnt]
                );

                for( order_cnt = 0; order_cnt < PRESCNRANK - 2; order_cnt++ ){
                                                // Choice biggest match
                        if( humming_order[order_cnt] < ret ){

                                for( shift_cnt = PRESCNRANK - 2;
                                     shift_cnt >= order_cnt;
                                     shift_cnt-- ){
                                                // Store match number
                                        best_match = ret;
                                                // Choice sequence
                                        v_lc_from = 1;
                                        w_lc_from = cnt + 1;

                                        humming_order[shift_cnt + 1]
                                                = humming_order[shift_cnt];

                                        humming_v_loc[shift_cnt + 1]
                                                = humming_v_loc[shift_cnt];

                                        humming_w_loc[shift_cnt + 1]
                                                = humming_w_loc[shift_cnt];
                                }

                                humming_order[order_cnt] = ret;
                                humming_v_loc[order_cnt] = v_lc_from;
                                humming_w_loc[order_cnt] = w_lc_from;

                                break;
                        }
                }
        }

#ifdef DEGUG

	for( order_cnt = 0; order_cnt < PRESCNRANK; order_cnt++ ){

		printf("%ld,%ld,%ld\n",
			humming_order[order_cnt],
			humming_v_loc[order_cnt],
			humming_w_loc[order_cnt]
		);
	}
#endif
						// Calculate to target number
	*v_lc_from_out = v_lc_from;
	*w_lc_from_out = w_lc_from;
	*best_match_out = best_match;

	return 0;
}


/******************************************************************************/
/*                                                                            */
/* Title  : Function of LCS                                                   */
/* Function Name : lcs                                                        */
/*                                                                            */
/* Detail :                                                                   */
/* Date   : 2009/12/07                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  :                                                                   */
/*                                                                            */
/* Output : return value [ 0 : Normal Terminate ] [ 1 : Error ]               */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/01/17                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added to find a site                                              */
/*                                                                            */
/* Date   : 2010/03/02                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added to alignment mode switch                                    */
/*                                                                            */
/* Date   : 2010/08/15                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Change to array of Source(Target)FileSize                         */
/*                        from inum(jnum) for v(w) array size.                */
/*                                                                            */
/* Date   : 2010/09/09                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Split to main() and lcs()                                         */
/*                                                                            */
/* Date   : 2010/09/15                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added free(v),(w) to all sequence mode                            */
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

int lcs(
        char *v,
        char *w,
        long inum,
        long jnum
){

	long ret;				/* Value of return            */

	long cnt;				/* Counter                    */
	long best_match;			/* Best mactch number         */
	char *target_v_sequence;		/* Target v sequence          */
	char *target_w_sequence;		/* Target w sequence          */
	long target_inum;			/* Target inum                */
	long target_jnum;			/* Target jnum                */

	long v_lc_from;				/* Sequence v location from   */
	long v_lc_to;				/* Sequence v location to     */
	long w_lc_from;				/* Sequence w location from   */
	long w_lc_to;				/* Sequence w location to     */
	TRNS *tr;				/* Pointer of array of        */
						/*          TRNS structure    */
	double hmm_num;				/* HMM number                 */

	long humming_order[PRESCNRANK];
	long humming_v_loc[PRESCNRANK];
	long humming_w_loc[PRESCNRANK];

	long   order_cnt;
	long   shift_cnt;

						/* Check for parameter        */
	if( v == NULL ){
		return -1;
	};

	if( w == NULL ){
		return -1;
	}

	if( inum < 0 ){
		return -1;
	}

	if( jnum < 0 ){
		return -1;
	}
                                                // Prepare threads
	// thread = (pthread_t *)malloc(
	// 	sizeof(pthread_t) * THREADS
	// );
						// Allocate threads memory
	// if( thread == NULL ){
	// 	printf("Can not allocate a thread memory.\n");
	// 	return(-1);
	// }

	// args = (thread_args *)malloc(
	// 	sizeof(thread_args) * THREADS
	// );
						// Allocate arguments memory
	// if( args == NULL ){
	// 	printf("Can not allocate an args memory.\n");
	// 	return(-1);
	// }

	// status = (void **)malloc( sizeof(void *) * THREADS );

						// Allocate status memory
	// if( status == NULL ){
	// 	printf("Can not allocate a status memory.\n");
	// 	return(-1);
	// }
						// Initialize for threads
	// for(	cnt = 0;
	// 	cnt < THREADS;
	// 	cnt++
	// ){
	// 	thread[cnt] = -1;
	// }

#ifdef DEBUG
	// debug write
	printf("In lcs(\n");
	printf("\tv[%s],\n",v);
	printf("\tw[%s],\n",w);
	printf("\tinum[%ld],\n",inum);
	printf("\tjnum[%ld]\n",jnum);
	printf(")\n");

	printf("Other parameters.\n");
	printf( "%d," \
		"alignment_mode[%d]," \
		"gapscore_mode[%d]," \
		"scan_mode[%d]," \
		"compare_mode[%d]," \
		"sequence_mode[%d],\n" \
		"match_num[%d]," \
		"unmatch_num[%d]," \
		"d_num[%d]," \
		"e_num[%d]," \
		"rs_num[%d]\n",
		0,
		alignment_mode,
		gapscore_mode,
		scan_mode,
		compare_mode,
		sequence_mode,
		match_num,
		unmatch_num,
		d_num,
		e_num,
		rs_num
	);
#endif
						/* Case of Amino Acid mode    */
						/*      or Protein mode       */
	if( compare_mode == AMINOACID ){
						/* Load replace score         */
		ret = LoadReplaceScore();
		if( ret != 0 ){
			fprintf( stderr, "%s file can not read.\n",
				REPLACESCORE_FILENAME );
			return(1);
		}
	}
						/* Case of all sequence mode  */
	if( sequence_mode == ALLSEQUENCE ){

#ifdef DEBUG
	// debug write
	fprintf( stderr, "In All sequence mode\n");
	fflush(stderr);
#endif
						/*   (+ 2) mean               */
						/*   Header of space and      */
						/*   Footer of NULL.          */
		target_v_sequence = malloc( (inum) + 2 );
		if( target_v_sequence == NULL ){

			printf("Can't allocate a target_v_sequene memory.\n");
			return 1;
		}

		target_w_sequence = malloc( (jnum) + 2 );
		if( target_w_sequence == NULL ){

			printf("Can't allocate a target_w_sequence memory.\n");
			return 1;
		}

						/* Added to header of space   */
		strcpy( target_v_sequence," ");
		strcpy( target_w_sequence," ");

						/* Cat sequence               */
		strcat( target_v_sequence, v );
						/* Free of memory v           */
		free(v);
	    
		strcat( target_w_sequence, w );
						/* Free of memory w           */
		free(w);
#ifdef DEBUG
		printf("all\n");
		printf("target v :[%s]\n",target_v_sequence);
		printf("target w :[%s]\n",target_w_sequence);
		printf("%ld:%ld\n",inum,jnum);
#endif
						/* Call to function           */
						/*   (+ 1) mean               */
						/*   Header of space          */
		ret = Procedure(
			target_v_sequence,
			inum + 1,
			target_w_sequence,
			jnum + 1,
			1,
			inum,
			1,
			jnum
		);
						/* Case of all sequence mode  */
						/*   is end of here           */
		return(0);
	}

#ifdef DEBUG
	// debug write
	fprintf( stderr, "In Part of sequence mode\n");
	fflush(stderr);
#endif
						/* From here is case of       */
						/* part of sequence mode      */

						/* Scan by Hidden Markov Model*/
	if( scan_mode == HMMSCAN ){

#ifdef DEBUG
	// debug write
	fprintf( stderr, "In hmm scan mode\n");
	fflush(stderr);
#endif
						/* -2 is initialize           */
		if( region_order == -2 ){
						/* Set alignment mode for hmm */
			init_hmm_procedure( alignment_mode );

			tr = NULL;
						/* Initialize to tr array set */
			tr = init_tr_set();
						/* Learning HMM from w        */
			hmm_learn( w, tr );
	    					/* Scan v sequence by HMM(tr) */
			v_lc_from = 0;
			v_lc_to   = 0;
			hmm_num   = 0;

			hmm_scn_global(
				v,
				tr,
				BESTHMM,
				&v_lc_from,
				&v_lc_to,
				&hmm_num
			);
						/* Scan v sequence by HMM(tr) */
	    					/*     at answer of           */
	    					/*         hmm_scn_global()   */
			hmm_scn_local(
				v,
				tr,
				BESTHMM,
				v_lc_from,
				v_lc_to,
				&v_lc_from,
				&v_lc_to,
				&hmm_num,
				prescan_hmm_orders,
				prescan_hmm_s_loc,
				prescan_hmm_e_loc
			);
						/* Free memory of tr array set*/
			tr = free_tr_set( tr );
		}else{

			best_match = prescan_hmm_orders[region_order];
			v_lc_from = prescan_hmm_s_loc[region_order];
			v_lc_to = prescan_hmm_e_loc[region_order];
		}
						/* Calculate to target number */
						/* Set target inum, jnum      */
	    	target_inum = v_lc_to - v_lc_from + 1;
	    	target_jnum = jnum;

	    					/*   (+ 2) mean               */
						/*   Header of space and      */
						/*   Footer of NULL.          */

		target_v_sequence = malloc( (target_inum) + 2 );
		if( target_v_sequence == NULL ){

			printf("Can't allocate a target_v_sequence memory.\n");
			return 1;
		}

		target_w_sequence = malloc( (target_jnum) + 2 );
		if( target_w_sequence == NULL ){

			printf("Can't allocate a target_w_sequence memory.\n");
			return 1;
		}

                                         
						/* Zero padding               */
		memset(
			target_v_sequence,
			'\0',
			(sizeof(char) * target_inum + 2)
		);

		memset(
			target_w_sequence,
			'\0',
			(sizeof(char) * target_jnum + 2)
		);

		target_v_sequence[0] = ' ';	/* Header of space            */

						/* Copy from part of original */
						/* sequence.                  */
						/* v_lc_from array is         */
						/* start at 0                 */

		strncpy( &target_v_sequence[1], &v[v_lc_from - 1], target_inum);

		free(v);			/* Free of memory v           */

		target_w_sequence[0] = ' ';	/* Header of space            */

						/* Copy from part of original */
						/* sequence.                  */
						/* v_lc_from array is         */
						/* start at 0                 */

		strncpy( &target_w_sequence[1], w, jnum );

		free(w);			/* Free of memory w           */

						/* Call to function           */
						/*   (+ 1) mean               */
						/*   Header of space          */
#ifdef DEBUG
		/* debug write */
		printf("Procedure()\n");
		printf("hmm mode\n");
		printf("target v :[%s]\n",target_v_sequence);
		printf("target_inum :%ld\n",target_inum);
		printf("target w :[%s]\n",target_w_sequence);
		printf("target_jnum :%ld\n",target_jnum);
		printf("%ld:%ld\n",inum,jnum);
		printf("v_lc_from :%ld\n",v_lc_from);
		printf("v_lc_to :%ld\n",v_lc_to);
#endif
		ret = Procedure(
			target_v_sequence,
			target_inum + 1,
			target_w_sequence,
			target_jnum + 1,
			v_lc_from,
			v_lc_to,
			1,
			jnum
		);
						/* Case of part of sequence   */
	    					/*     mode by HMM scan       */
	    					/*         is end of here     */
	    	return(0);
	}

#ifdef DEBUG
	// debug write
	fprintf( stderr, "In identify mode\n");
	fflush(stderr);
#endif
						/* -2 is initialize           */
	if( region_order == -2 ){
						/* Check for matches          */
						/*  by shift of v             */
		best_match = 0;
						/* Init memory                */
		memset( humming_order, 0, sizeof(long) * PRESCNRANK );

						/* Search a best matchs       */
						/*                for inum    */
		inum_best_matches(
			inum,
			jnum,
			v,
			w,
			humming_order,
			humming_v_loc,
			humming_w_loc,
			&v_lc_from,
			&w_lc_from,
			&best_match
		);
						/* Search a best matchs       */
						/*                for jnum    */
		jnum_best_matches(
			inum,
			jnum,
			v,
			w,
			humming_order,
			humming_v_loc,
			humming_w_loc,
			&v_lc_from,
			&w_lc_from,
			&best_match
		);
						/* Initialize memorys         */
		memcpy(prescan_orders,humming_order,sizeof(long) * PRESCNRANK);
		memcpy(prescan_v_loc, humming_v_loc,sizeof(long) * PRESCNRANK);
		memcpy(prescan_w_loc, humming_w_loc,sizeof(long) * PRESCNRANK);
#ifdef DEBUG
		for( order_cnt = 0; order_cnt < PRESCNRANK; order_cnt++ ){

			printf("%ld,%ld,%ld\n",
				humming_order[order_cnt],
				humming_v_loc[order_cnt],
				humming_w_loc[order_cnt]
			);
		}
#endif
	}else{

		best_match = prescan_orders[region_order];
		v_lc_from  = prescan_v_loc[region_order];
		w_lc_from  = prescan_w_loc[region_order];
	}
						/* Calculate to target number */
						/*                            */
						/* v_lc_from array is         */
						/* start at 0                 */
						/*                            */
						/* added to number of unmatch */
	if( inum >= jnum ){
		v_lc_to = (v_lc_from - 1) + jnum + (jnum - best_match);
		w_lc_to = (w_lc_from - 1) + jnum + (jnum - best_match);
	}else{
		v_lc_to = (v_lc_from - 1) + inum + (inum - best_match);
		w_lc_to = (w_lc_from - 1) + inum + (inum - best_match);
	}
						/* Case of                    */
						/*    topping sequence number */
	if( v_lc_to > inum ){
		v_lc_to = inum;
	}

	if( w_lc_to > jnum ){
		w_lc_to = jnum;
	}
						/* Calculate to target number */
						/*                            */
						/* v_lc_from array is         */
						/* start at 0                 */
	target_inum = v_lc_to - (v_lc_from - 1);
	target_jnum = w_lc_to - (w_lc_from - 1);

						/*   (+ 2) mean               */ 
						/*   Header of space and      */
						/*   Footer of NULL.          */
	target_v_sequence = malloc( (target_inum) + 2 );
	if( target_v_sequence == NULL ){

		printf("Can not allocate a target_v_sequence memory.");
		printf(" %ld [bytes]\n",
			target_inum + 2
		);
		return 1;
	}

	target_w_sequence = malloc( (target_jnum) + 2 );
	if( target_w_sequence == NULL ){

		printf("Can not allocate a target_w_sequence memory.");
		printf(" %ld [bytes]\n",
			target_jnum + 2
		);
		return 1;
	}
						/* Zero padding               */
	memset( target_v_sequence, '\0', (sizeof(char) * target_inum + 1) );
	memset( target_w_sequence, '\0', (sizeof(char) * target_jnum + 1) );

	target_v_sequence[0] = ' ';		/* Header of space            */

						/* Copy from part of original */
						/* sequence.                  */
						/* v_lc_from array is         */
						/* start at 0                 */
	strncpy( &target_v_sequence[1], &v[v_lc_from - 1], target_inum );
	free(v);				/* Free of memory v           */

	target_w_sequence[0] = ' ';		/* Header of space            */

						/* Copy from part of original */
						/* sequence.                  */
						/* v_lc_from array is         */
						/* start at 0                 */
	strncpy( &target_w_sequence[1], &w[w_lc_from - 1], target_jnum );
	free(w);				/* Free of memory w           */

#ifdef DEBUG
	printf("part\n");
	printf("target v :[%s]\n",target_v_sequence);
	printf("target w :[%s]\n",target_w_sequence);
	printf("best_match : %d\n",best_match);
	printf("v : %d,%d\n", v_lc_from, v_lc_to);
	printf("w : %d,%d\n", w_lc_from, w_lc_to);
	printf("%d:%d\n",target_inum,target_jnum);
#endif
						/* Call to function           */
						/*   (+ 1) mean               */
						/*   Header of space          */
	ret = Procedure(
		target_v_sequence,
		target_inum + 1,
		target_w_sequence,
		target_jnum + 1,
		v_lc_from,
		v_lc_to,
		w_lc_from,
		w_lc_to
	);

#ifdef DEBUG
	/* debug write */
	printf("Leave lcs()\n");
	fflush(stdout);
#endif
						/* v_ans, w_ans, bp_arr       */
	return(0);
}

/******************************************************************************/
/*                                                                            */
/* Title  : main Procedure                                                    */
/* Function Name : Procedure                                                  */
/*                                                                            */
/* Detail : main procedure of LCS                                             */
/* Date   : 2010/01/17                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *v         : sequence of v                                   */
/*          long  inum      : number of v sequence                            */
/*          char *w         : sequence of w                                   */
/*          long  jnum      : number of w sequence                            */
/*          long  v_lc_from : location number of v sequence at start          */
/*          long  v_lc_to   : location number of v sequence at end            */
/*          long  w_lc_from : location number of w sequence at start          */
/*          long  w_lc_to   : location number of v sequence at end            */
/*                                                                            */
/* Output : return value [ 0 : Normal Terminate ] [ 1 : Error ]               */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/02/25                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added to local alignment and sequence number                      */
/*                                                                            */
/* Date   : 2010/04/29                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added to compare mode                                             */
/*                                                                            */
/* Date   : 2010/09/30                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added procedure that is identities count, rate and score.         */
/*                                                                            */
/* Date   : 2010/10/08                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Modify to malloc procedure and added arguments to BackTracking()  */
/*          and PrintOutForTextView() and added array that eg_arr,ss_arr.     */
/*                                                                            */
/* Date   : 2014/06/10                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : The LCS calculation method changed to a Multi thread procedure.   */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int Procedure(
	char *v,
	long inum,
	char *w,
	long jnum,
	long v_lc_from,
	long v_lc_to,
	long w_lc_from,
	long w_lc_to
){

	long cnt;				/* Counter                    */
	long ret;				/* Value of return            */
	
	char **eg;				/* Buffer of Edit Graph       */
	long **ss;				/* Buffer of Similary Score   */
	char **bp;				/* Buffer of Back Tracking    */
	
	char *v_ans;				/* Answer of calculation of v */
	char *w_ans;				/* Answer of calcularion of w */
	char *ans;				/* Answer of LCS              */
	char *eg_arr;				/* Buffer of                  */
						/*     Edit graph pointer     */
	long *ss_arr;				/* Buffer of                  */
						/*     Similary score pointer */
	char *bp_arr;				/* Buffer of                  */
						/*     Back tracking pointer  */

	long  vnum;				/* Number of v array          */
	long  wnum;				/* Number of w array          */
	long  ansnum;				/* Number of anser array      */
	long  egnum;				/* Number of                  */
						/*       Edit graph array     */
	long  ssnum;				/* Number of                  */
						/*       Similary score array */
	long  bpnum;				/* Number of                  */
						/*       Back tracking arrary */
	
	long  inum_from;			/* Number of inum at start    */
	long  jnum_from;			/* Number of jnum at start    */
                                         
	long start_i;
	long start_j;
	long i;					/* Loop counter i             */
	long j;					/* Loop counter i             */
	long n;					/* Load of a thread           */

	long   ident_cnt;			/* Counter of Identify number */
	double ident_rate;			/* Rate of Identify number    */
	long score;				/* Score from blosum          */

	pthread_t *thread;			/* Pointer for thread ID      */
	thread_args *args;			/* Pointer for arguments      */
	void **status;				/* Pointer for thread status  */
	int threads_cnt;			/* Counter for threads        */

	long detach_cnt = 0;
						/* Check for parameter        */
	if( v == NULL ){
		return -1;
	}

	if( inum < 0 ){
		return -1;
	}

	if( w == NULL ){
		return -1;
	}

	if( jnum < 0 ){
		return -1;
	}

	if( v_lc_from < 0 ){
		return -1;
	}

	if( v_lc_to < 0 ){
		return -1;
	}

	if( w_lc_from < 0 ){
		return -1;
	}

	if( w_lc_to < 0 ){
		return -1;
	}

#ifdef DEBUG
	// debug write
	printf("In Procedure(\n");
	printf("\tv[%s]\n",v);
	printf("\tinum[%ld]\n",inum);
	printf("\tw[%s]\n",w);
	printf("\tjnum[%ld]\n",jnum);
	printf("\tv_lc_from[%ld]\n",v_lc_from);
	printf("\tv_lc_from[%ld]\n",v_lc_to);
	printf("\tw_lc_from[%ld]\n",w_lc_from);
	printf("\tw_lc_to[%ld]\n",w_lc_to);
	printf(")\n");
#endif
						/* Memory allocate            */
						/*    of Edit Graph           */
	eg = malloc( sizeof(char *) * inum );
	if( eg == NULL ){

		printf("Can't allocate an eg memory.\n");
		return 1;
	}

	for( i = 0; i < inum; i++ ){
		eg[i] = malloc( sizeof(char) * jnum );
		memset( eg[i], '\0', (sizeof(char) * jnum) );
	}
						/* Memory allocate            */
						/*    of Similary Score       */
	ss = malloc( sizeof(long *) * inum );
	if( ss == NULL ){

		printf("Can't allocate a ss memory.\n");
		return 1;
	}

	for( i = 0; i < inum; i++ ){
		ss[i] = malloc( sizeof(long) * jnum );
		memset( ss[i], '\0', (sizeof(long) * jnum) );
	}
						/* Memory allocate            */
						/*   of Back tracking pointer */
	bp = malloc( sizeof(char *) * inum );
	if( bp == NULL ){

		printf("Can't allocate a bp memory.\n");
		return 1;
	}

	for( i = 0; i < inum; i++ ){
		bp[i] = malloc( sizeof(char) * jnum );
		memset( bp[i], '\0', (sizeof(char) * jnum) );
	}
						/* Prepare threads            */
	thread = (pthread_t *)malloc(
		sizeof(pthread_t) * THREADS
	);
						/* Allocate threads memory    */
	if( thread == NULL ){
		printf("Can not allocate a thread memory.\n");
		return(-1);
	}

	args = (thread_args *)malloc(
		sizeof(thread_args) * THREADS
	);
						/* Allocate arguments memory  */
	if( args == NULL ){
		printf("Can not allocate an args memory.\n");
		return(-1);
	}
						/* Allocate status memory     */
	status = (void **)malloc( sizeof(void *) * THREADS );

	if( status == NULL ){
		printf("Can not allocate a status memory.\n");
		return(-1);
	}
						/* Initialize for threads     */
	for(	threads_cnt = 0;
		threads_cnt < THREADS;
		threads_cnt++
	){
		thread[threads_cnt] = -1;
	}
						/* Initialize for values      */
        start_j = 0;
        start_i = 0;

            cnt = 1;
        start_j = 1;
        start_i = 1;
              j = 0;
              i = 0;

	threads_cnt = 0;
						/* Init Global values         */
	biggest_score = 0;
	local_inum = 0;
	local_jnum = 0;
						/* Initialize for mutex       */
	pthread_mutex_init(&mutex,NULL);

        while( cnt <= (jnum-2) * (inum-2) ){
						/* Load of a thread           */
		n = 0;
						/* Diagonally calling         */
                for( j = start_j, i = start_i;
                     j >= 1 && i <= (inum-2);
                     j--, i++
                ){
						/* Increment a load           */
			n++;
						/* Synchronous threads        */
			if( thread[threads_cnt] != -1 ){

						/* Wait for a completed thread*/
				ret = pthread_join(
					thread[threads_cnt],
					NULL
					//status[threads_cnt]
				);
						/* Error terminate            */
				if( ret != 0 ){
					printf( "Thread(%d) ",threads_cnt);
					printf( "error terminated.\n");
				}
						/* Detach thread              */
				//pthread_detach( thread[threads_cnt] );
				thread[threads_cnt] = -1;
			}
						/* Increments                 */
			cnt++;

			if( ((n % THREAD_NUM) != 0) || (n == 0)){
						/* Case of no create thread   */
				continue;
			}
						/* Set arguments for thread   */
			args[threads_cnt].n = THREAD_NUM;
			args[threads_cnt].i = i + 1;
			args[threads_cnt].j = j - 1;
			args[threads_cnt].type = compare_mode;
			args[threads_cnt].mode = alignment_mode;
			args[threads_cnt].v = v;
			args[threads_cnt].w = w;
			args[threads_cnt].eg = eg;
			args[threads_cnt].ss = ss;
			args[threads_cnt].bp = bp;
			args[threads_cnt].inum = inum - 2;
			args[threads_cnt].jnum = jnum - 2;
	
						/* Create to thread           */
			ret = (int)pthread_create(
				&thread[threads_cnt],
				NULL,
				divide_threads,
				&args[threads_cnt]
			);
						/* Error of create_thread()   */
			if( ret != 0 ){
				printf( "Thread(%d) create failed.\n",
					threads_cnt
				);
				break;
			}
						/* Threads_cnt initialize     */
			if( threads_cnt < THREADS - 1 ){
						/* Next thread                */
				threads_cnt++;
			}else{
						/* Continue                   */
				threads_cnt = 0;
			}
						/* Reset n value              */
			n = 0;
		}
						/* Synchronous threads        */
		if( thread[threads_cnt] != -1 ){

						/* Wait for a completed thread*/
			ret = pthread_join(
				thread[threads_cnt],
				NULL
				//status[threads_cnt]
			);
						/* Error terminate            */
			if( ret != 0 ){
				printf( "Thread(%d) ",threads_cnt);
				printf( "error terminated.\n");
			}
						/* Detach thread              */
			//pthread_detach( thread[threads_cnt] );
			thread[threads_cnt] = -1;
		}
						/* Increments                 */
		if( ((n % THREAD_NUM) != 0) && (n != 0) ){
						/* Set arguments for thread   */
			args[threads_cnt].n = n % THREAD_NUM;
			args[threads_cnt].i = i;
			args[threads_cnt].j = j;
			args[threads_cnt].type = compare_mode;
			args[threads_cnt].mode = alignment_mode;
			args[threads_cnt].v = v;
			args[threads_cnt].w = w;
			args[threads_cnt].eg = eg;
			args[threads_cnt].ss = ss;
			args[threads_cnt].bp = bp;
			args[threads_cnt].inum = inum - 2;
			args[threads_cnt].jnum = jnum - 2;
	
						/* Create to thread           */
			ret = (int)pthread_create(
				&thread[threads_cnt],
				NULL,
				divide_threads,
				&args[threads_cnt]
			);
						/* Error of create_thread()   */
			if( ret != 0 ){
				printf( "Thread(%d) create failed.\n",
					threads_cnt
				);
				break;
			}
						/* Threads_cnt initialize     */
			if( threads_cnt < THREADS - 1 ){
						/* Next thread                */
				threads_cnt++;
			}else{
						/* Continue                   */
				threads_cnt = 0;
			}
		}
						/* Synchronous threads        */
		for( threads_cnt = 0; threads_cnt < THREADS ; threads_cnt++ ){

			if( thread[threads_cnt] == -1 ){
				continue;
			}
						/* Wait for a completed thread*/
			ret = pthread_join(
				thread[threads_cnt],
				NULL
			);
						/* Error terminate            */
			if( ret != 0 ){
				printf( "Thread(%d) error terminated.(%ld)\n",
					threads_cnt,
					ret
				);
			}
#ifdef DEBUG
			else{
				printf("%ld:pthread joined.\n",threads_cnt);
				fflush(stdout);
						// Detach thread
				ret = pthread_detach( thread[threads_cnt] );
				if( ret != 0 ){
					printf("%ld:pthread_detach(%ld)\n",
						detach_cnt,
						ret
					);
					detach_cnt++;
				}
			}
#endif
			thread[threads_cnt] = -1;
		}
#ifdef DEBUG
		printf("all thread joined.\n\n");
		fflush(stdout);
#endif
						/* Initialize counter         */
						/*            for thread      */
		threads_cnt = 0;

                if( start_j < (jnum-2) ){
						/* Increment start j counter  */
                        start_j++;

                }else if( start_i < (inum-2)){
						/* Increment start i counter  */
                        start_i++;
                }
        }
						/* Destroy for mutex          */
	pthread_mutex_destroy(&mutex);

#ifdef DEBUG
	printf("completed pthread procedures.\n");
	fflush(stdout);
#endif
						/* Memory allocate of         */
						/* v_ans, w_ans, ans, bp_arr  */
	if( alignment_mode == GLOBAL_ALIGNMENT ){

#ifdef DEBUG
	// debug write
	fprintf( stderr, "In global alignment mode\n");
#endif
		v_ans  = (char *)malloc((sizeof(char) * (inum + jnum)) + 1 );
		if( v_ans == NULL ){

			printf("Can't allocate a v_ans memory.\n");
			return 1;
		}

		w_ans  = (char *)malloc((sizeof(char) * (inum + jnum)) + 1 );
		if( w_ans == NULL ){

			printf("Can't allocate a w_ans memory.\n");
			return 1;
		}

		ans    = (char *)malloc((sizeof(char) * (inum + jnum)) + 1 );
		if( ans == NULL ){

			printf("Can't allocate a ans memory.\n");
			return 1;
		}

		eg_arr = (char *)malloc((sizeof(char) * (inum + jnum)) + 1 );
		if( eg_arr == NULL ){

			printf("Can't allocate a eg_arr memory.\n");
			return 1;
		}

		ss_arr = (long *)malloc((sizeof(long) * (inum + jnum)) + 1 );
		if( ss_arr == NULL ){

			printf("Can't allocate a ss_arr memory.\n");
			return 1;
		}

		bp_arr = (char *)malloc((sizeof(char) * (inum + jnum)) + 1 );
		if( bp_arr == NULL ){

			printf("Can't allocate a bp_arr memory.\n");
			return 1;
		}

						/* +1 mean footer NULL       */

						/* Zero padding              */
		memset( v_ans, '\0', (sizeof(char) * (inum + jnum)) + 1 );
		memset( w_ans, '\0', (sizeof(char) * (inum + jnum)) + 1 );
		memset(   ans, '\0', (sizeof(char) * (inum + jnum)) + 1 );
		memset( eg_arr,'\0', (sizeof(char) * (inum + jnum)) + 1 );
		memset( ss_arr,  0 , (sizeof(long) * (inum + jnum)) + 1 );
		memset( bp_arr,'\0', (sizeof(char) * (inum + jnum)) + 1 );

	}else{

#ifdef DEBUG
	// debug write
	fprintf( stderr, "In local alignment mode\n");
#endif
		local_inum += 2;
		local_jnum += 2;

		v_ans  = (char *)malloc(
		        (sizeof(char) * (local_inum + local_jnum)) + 1
		);
		if( v_ans == NULL ){

			printf("Can't allocate a v_ans memory.\n");
			return 1;
		}

		w_ans  = (char *)malloc(
		        (sizeof(char) * (local_inum + local_jnum)) + 1
		);
		if( w_ans == NULL ){

			printf("Can't allocate a w_ans memory.\n");
			return 1;
		}

		ans    = (char *)malloc(
		        (sizeof(char) * (local_inum + local_jnum)) + 1
		);
		if( ans == NULL ){

			printf("Can't allocate an ans memory.\n");
			return 1;
		}

		eg_arr = (char *)malloc(
		        (sizeof(char) * (local_inum + local_jnum)) + 1
		);
		if( eg_arr == NULL ){

			printf("Can't allocate a eg_arr memory.\n");
			return 1;
		}

		ss_arr = (long *)malloc(
		        (sizeof(long) * (local_inum + local_jnum)) + 1
		);
		if( ss_arr == NULL ){

			printf("Can't allocate a ss_arr memory.\n");
			return 1;
		}

		bp_arr = (char *)malloc(
		        (sizeof(char) * (local_inum + local_jnum)) + 1
		);
		if( bp_arr == NULL ){

			printf("Can't allocate a bp_arr memory.\n");
			return 1;
		}

						/* +1 mean footer NULL       */

						/* Zero padding              */
		memset( v_ans,
			'\0',
			(sizeof(char) * (local_inum + local_jnum)) + 1
		);
		memset( w_ans,
			'\0',
			(sizeof(char) * (local_inum + local_jnum)) + 1
		);
		memset( ans,
			'\0',
			(sizeof(char) * (local_inum + local_jnum)) + 1
		);
		memset( eg_arr,
			'\0',
			(sizeof(char) * (local_inum + local_jnum)) + 1
		);

		memset( ss_arr,
			0,
			(sizeof(long) * (local_inum + local_jnum)) + 1
		);

		memset( bp_arr,
			'\0',
			(sizeof(char) * (local_inum + local_jnum)) + 1
		);
	}
						/* Output of                 */
						/* Output of SimilaryScore   */

						/* Calculate                 */
						/*  of Back tracking pointer */
	if( alignment_mode == GLOBAL_ALIGNMENT ){

						/* Global Alignment          */
		ret = BackTracking(
			v, w,
			inum, jnum,
			eg,ss,bp,
			v_ans, w_ans, ans,
			&vnum, &wnum, &ansnum,
			eg_arr,	ss_arr,	bp_arr,
			&egnum,	&ssnum,	&bpnum,
			&inum_from, &jnum_from
		);

	}else{
						/* Local Alignment           */
		ret = BackTracking(
			v, w,
			local_inum, local_jnum,
			eg,ss,bp,
			v_ans, w_ans, ans,
			&vnum, &wnum, &ansnum,
			eg_arr,	ss_arr,	bp_arr,
			&egnum,	&ssnum,	&bpnum,
			&inum_from, &jnum_from
		);
						/* Adjustment to sequence    */
						/*  v (from)                 */
		v_lc_from = v_lc_from + inum_from;

						/*  v (to)                   */
		v_lc_to = v_lc_to - (inum - local_inum) - 1;

						/*  w (from)                 */
		w_lc_from = w_lc_from + jnum_from;

						/*  w (to)                   */
		w_lc_to = w_lc_to - (jnum - local_jnum) - 1;
	}

						/* Count to identities       */
	ident_cnt = 0;
	for( cnt = bpnum - 1; cnt >= 0; cnt-- ){
		if( bp_arr[cnt] == '|' ){
			ident_cnt++;
		}
	}
						/* Output of v_ans           */
	ident_rate = (double)ident_cnt / (double)bpnum;

	if( alignment_mode == GLOBAL_ALIGNMENT ){
						/* Get global similarly score*/
		score = ss[inum - 2][jnum - 2];
	}else{
						/* Get local similarly score */
		score = ss[local_inum - 2][local_jnum - 2];
	}

#ifdef DEBUG
	printf("v_ans[%s]\n",&v_ans[1]);
	printf("w_ans[%s]\n",&w_ans[1]);
	printf("ans[%s]\n",&ans[1]);
	printf("eg_arr[%s]\n",&eg_arr[1]);

	printf("ss_arr[");
	for( cnt = 0; cnt < ssnum; cnt++){
		printf("%ld,",cnt);
	}
	printf("]\n");

	printf("bp_arr[%s]\n",&bp_arr[1]);
#endif
						/* Print out                 */	
	if( output_mode == CUI_MODE ){

		ret = PrintOut(
			v, w,
			eg, ss, bp,
			v_ans, w_ans, ans, eg_arr, ss_arr, bp_arr,
			inum, jnum,
			vnum, wnum,
			ansnum, egnum, ssnum, bpnum,
			v_lc_from, v_lc_to,
			w_lc_from, w_lc_to,
		        ident_cnt, ident_rate, score
		);
	}else{	    	    
	        ret = PrintOutForTextView(
			v, w,
			eg, ss, bp,
			v_ans, w_ans, ans, eg_arr, ss_arr, bp_arr,
			inum, jnum,
			vnum, wnum,
			ansnum, egnum, ssnum, bpnum,
			v_lc_from, v_lc_to,
			w_lc_from, w_lc_to,
		        ident_cnt, ident_rate, score,
		        compare_mode,
			sequence_mode,
			scan_mode,
			matrix_on,
			region_order,
			prescan_orders,
			prescan_v_loc,
			prescan_w_loc,
			prescan_hmm_orders,
			prescan_hmm_s_loc,
			prescan_hmm_e_loc
		);
	}
					/* Free of memory Edit Graph         */
	for( i = 0; i < inum; i++ ){
		free(eg[i]);
	}
	free(eg);
					/* Free of memory Similary Score     */
	for( i = 0; i < inum; i++ ){
		free(ss[i]);
	}
	free(ss);
					/* Free of memory                    */
					/*     Back traking pointer          */
	for( i = 0; i < inum; i++ ){
		free(bp[i]);
	}
	free(bp);
					/* Free of memory                    */
					/*    v_ans, w_ans, bp_arr           */
	free(v_ans);
	free(w_ans);
	free(  ans);
	free(eg_arr);
	free(ss_arr);
	free(bp_arr);
	
	return(0);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Print out                                                         */
/* Function Name : PrintOut                                                   */
/*                                                                            */
/* Detail :                                                                   */
/* Date   : 2010/02/25                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  :                                                                   */
/*          char **eg      : Buffer of Edit Graph                             */
/*          long **ss      : Buffer of Similary Score                         */
/*          char **bp      : Buffer of Back Tracking                          */
/*          char *v_ans    : Answer of calculation of v                       */
/*          char *w_ans    : Answer of calcularion of w                       */
/*          char *ans      : Answer of LCS                                    */
/*          char *eg_arr   : Buffer of Edit graph pointer                     */
/*          long *ss_arr   : Buffer of Similary score pointer                 */
/*          char *bp_arr   : Buffer of Back tracking pointer                  */
/*          long  inum     : Number of i array                                */
/*          long  jnum     : Number of j array                                */
/*          long  vnum     : Number of w array                                */
/*          long  wnum     : Number of w array                                */
/*          long  ansnum   : Number of anser array                            */
/*          long  egnum    : Number of Edit graph arrary                      */
/*          long  ssnum    : Number of Similary score arrary                  */
/*          long  bpnum    : Number of Back tracking arrary                   */
/*          long  v_lc_from: location number of v sequence at start           */
/*          long  v_lc_to  : location number of v sequence at end             */
/*          long  w_lc_from: location number of w sequence at start           */
/*          long  w_lc_to  : location number of v sequence at end             */
/*          long   ident_cnt  : Count of identities                           */
/*          double ident_rate : Rate  of identities                           */
/*          long   score      : Similary Score of blosum                      */
/*                                                                            */
/* Output : int : [ 0 : Normal Terminate ]                                    */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/09/30                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added arguments that is identites count, rate and score.          */
/*                                                                            */
/* Date   : 2010/10/08                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added arguments eg_arr,ss_arr,egnum,ssnum.                        */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int PrintOut(
	char *v,
	char *w,
	char **eg,
	long **ss,
	char **bp,
	char *v_ans,
	char *w_ans,
	char *ans,
	char *eg_arr,
	long *ss_arr,
	char *bp_arr,
	long  inum,
	long  jnum,
	long  vnum,
	long  wnum,
	long  ansnum,
	long  egnum,
	long  ssnum,
	long  bpnum,
	long  v_lc_from,
	long  v_lc_to,
	long  w_lc_from,
	long  w_lc_to,
        long  ident_cnt,
        double ident_rate,
        long score
){
	long cnt;				/* Counter                   */
	long i;					/* Loop counter i            */
	long j;					/* Loop counter j            */

	if( disp_flg & V_DISP_FLG ){

		for( cnt = vnum - 1; cnt > 0; cnt-- ){
			fputc( v_ans[cnt], stdout );
		}
						/* Output of sequence number */
		fprintf(stdout,
			",%ld,%ld,%ld,%.2f,%ld\n",
			v_lc_from, v_lc_to, ident_cnt, ident_rate, score / 10
		);
	}
						/* Output of bp_arr          */
	if( disp_flg & GAP_DISP_FLG ){
	
		for( cnt = bpnum - 1; cnt > 0; cnt-- ){
			fputc( bp_arr[cnt], stdout );
		}
						/* Output LF                 */
		fprintf(stdout, "\n");
	}
						/* Output of w_ans           */
	if( disp_flg & W_DISP_FLG ){

		for( cnt = wnum - 1; cnt > 0; cnt-- ){
			fputc( w_ans[cnt], stdout );
		}
						/* Output of sequence number */
		fprintf(stdout,
			",%ld,%ld,%ld,%.2f,%ld\n",
			w_lc_from, w_lc_to, ident_cnt, ident_rate, score / 10
		);
	}
						/* Output of ans             */
	if( disp_flg & ANS_DISP_FLG ){
	
		for( cnt = ansnum - 1; cnt >= 0; cnt-- ){
			fputc( ans[cnt], stdout );
		}
						/* Output of sequence number */
		fprintf(stdout,
			",%ld,%ld,%ld,%.2f,%ld\n",
			v_lc_from, v_lc_to, ident_cnt, ident_rate, score / 10
		);
	}
						/* Output of EditGraph       */
	if( disp_flg & EG_DISP_FLG ){
						/* Header (w sequence)       */
		fprintf(stdout,"v\\w");

		for( j = 1; j < jnum - 1; j++ ){
			fprintf(stdout,",%c",w[j]);
		}				/* -1 mean footer null       */

		fprintf(stdout,"\n");

                for( i = 1; i < inum - 1; i++ ){
						/* Header (v sequence)       */
						/* -1 mean footer null       */
			fprintf(stdout,"%c",v[i]);

			for( j = 1; j < jnum - 1; j++ ){
         
				fprintf(stdout, ",%d",eg[i][j]);
			}
 
			fprintf(stdout, "\n");
		}
	}
						/* Output of SimilaryScore   */
	if( disp_flg & SS_DISP_FLG ){
						/* Header (w sequence)       */
		fprintf(stdout,"v\\w");

		for( j = 1; j < jnum - 1; j++ ){
			fprintf(stdout,",%c",w[j]);
		}				/* -1 mean footer null       */

		fprintf(stdout,"\n");

		for( i = 1; i < inum - 1; i++ ){
						/* Header (v sequence)       */
						/* -1 mean footer null       */
			fprintf(stdout,"%c",v[i]);
            
			for( j = 1; j < jnum - 1; j++ ){
         
				fprintf(stdout, ",%ld",ss[i][j]);
			}
 
			fprintf(stdout, "\n");
		}
	}
						/* Output of                 */
						/*       BacktrackingPointer */
	if( disp_flg & BP_DISP_FLG ){
						/* Header (w sequence)       */
		fprintf(stdout,"v\\w");

		for( j = 1; j < jnum - 1; j++ ){
			fprintf(stdout,",%c",w[j]);
		}				/* -1 mean footer null       */

		fprintf(stdout,"\n");


                for( i = 1; i < inum - 1; i++ ){
						/* Header (v sequence)       */
						/* -1 mean footer null       */
			fprintf(stdout,"%c",v[i]);
            
			for( j = 1; j < jnum - 1; j++ ){
         
				fprintf(stdout, ",%c",bp[i][j]);
			}
 
			fprintf(stdout, "\n");
		}
	}

	return(0);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Check for filesize function                                       */
/* Function Name : ChkFileSize                                                */
/*                                                                            */
/* Detail :                                                                   */
/* Date   : 2009/12/03                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *filename : Target file name                                 */
/*                                                                            */
/* Output : int : [ Byte : Normal Terminate ] [ -1 : Error(file not found)]   */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/10/17                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added st_size "-1" initialize.                                    */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

long ChkFileSize( char *filename ){

	struct stat st;				/* Struct Stat                */

	st.st_size = -1;			/* Initialize st_size         */
	
	stat( filename, &st );			/* Get status                 */
	
	return( st.st_size );                   /* Return file size          */
}

/******************************************************************************/
/*                                                                            */
/* Title  : Get sequence function                                             */
/* Function Name : GetSequence                                                */
/*                                                                            */
/* Detail :                                                                   */
/* Date   : 2009/12/03                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *filename : Target file name                                 */
/*          char *buff : Buffer of data of sequence                           */
/*                                                                            */
/* Output : long : [ Count of loaded charactar : Normal Terminate ]           */
/*                 [ -1                        : Error            ]           */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/08/15                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Change return array type to long from int.                        */
/*                      and return count of loaded charactar.                 */
/*                                                                            */
/* Date   : 2010/08/22                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added procedure that convert to upper character                   */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

long GetSequence( char *filename, char *buff ){

	FILE *fp;				/* File pointer               */
	long cnt;				/* Counter                    */
	long in_char;				/* In character               */
	int head_flg;
	
	fp = fopen( filename, "r" );		/* File open                  */
	if( fp == NULL ){			/* Error                      */
		return(-1);
	}
	
	/* buff[0] = ' '; */			/* Insert space at header     */
	
	in_char = fgetc( fp );			/* Get a character from file  */
	cnt = 0;				/* Counter initialize         */
	head_flg = 0;
	
	while( in_char != EOF ){

		if(in_char != '>' && head_flg == 0 && in_char != '\n'){
	
			in_char = toupper( in_char );
						/* Convert to upper           */
						/* LF skip                    */
			buff[cnt] = in_char;
						/* Copy to buffer             */
			cnt++;			/* Counter increment          */

		}else if(in_char == ">"){

			head_flg = 1;

		}else if(in_char == "\n"){

			head_flg = 0;
		}

		
		in_char = fgetc( fp );		/* Get next character         */
	}

	buff[cnt] = '\0';			/* Set null at footer         */
	
	fclose( fp );				/* File close                 */
	return(cnt + 1);			/* Normal terminate           */
}

/******************************************************************************/
/*                                                                            */
/* Title  : Weighting function for amino acid                                 */
/* Function Name : WeightingForAminoAcid                                      */
/*                                                                            */
/* Detail : function w(x,y) = from blosum file                                */
/* Date   : 2010/04/29                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long  inum : Number of array count of i                           */
/*          long  jnum : Number of array count of j                           */
/*          char *v   : Pointer of array of v                                 */
/*          char *w   : Pointer of array of w                                 */
/*          char **eg : Pointer of array of Edit Graph                        */
/*                                                                            */
/* Output : int : [ 0 : Normal Terminate ]                                    */
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

int WeightingForAminoAcid(
	long inum,
	long jnum,
	char *v,
	char *w,
	char **eg
){

	long i;					/* Loop counter i             */
	long j;					/* Loop counter j             */

	int  cnt;				/* Loop counter               */

#ifdef DEBUG
    	// debug write
	fprintf(
	    stderr,
	    "In WeightingForAminoAcid(%ld,%ld,[%s],[%s],%x)\n",
	    inum,
	    jnum,
	    v,
	    w,
	    eg
	);

	fprintf( stderr, "match_num=%ld\n",match_num);
	fprintf( stderr, "unmatch_num=%ld\n",unmatch_num);
#endif
    
	for( i = 1; i < inum; i++ ){
	
		for( j = 1; j < jnum; j++ ){
						/* Loop for blosum score list */
			for( cnt = 0; cnt < REPLACE_NUM; cnt++ ){
						/* Match v code and w code    */
				if( rs[cnt].v_cd == v[i]
				 && rs[cnt].w_cd == w[j] ){

						/* Set replace score          */
					eg[i][j] = rs[cnt].score;

					break;
				}
			}
		}
	}
	
	return( 0 );				/* Return                     */
}

/******************************************************************************/
/*                                                                            */
/* Title  : Weighting function for Nucleotide                                 */
/* Function Name : WeightingForNucleotide                                     */
/*                                                                            */
/* Detail : function w(x,y) = { match = +1, unmatch = 0 }                     */
/* Date   : 2009/12/02                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long  inum : Number of array count of i                           */
/*          long  jnum : Number of array count of j                           */
/*          char *v   : Pointer of array of v                                 */
/*          char *w   : Pointer of array of w                                 */
/*          char **eg : Pointer of array of Edit Graph                        */
/*                                                                            */
/* Output : int : [ 0 : Normal Terminate ]                                    */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/01/15                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added to Match,Unmatch score                                      */
/*                                                                            */
/* Date   : 2010/02/23                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Modifiy to about score calculation                                */
/*                                                                            */
/* Date   : 2010/02/29                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Change function name                                              */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int WeightingForNucleotide(
	long inum,
	long jnum,
	char *v,
	char *w,
	char **eg
){

	long i;					/* Loop counter i             */
	long j;					/* Loop counter j             */

#ifdef DEBUG
    	// debug write
	fprintf(
	    stderr,
	    "In WeightingForNucleotide(%ld,%ld,[%s],[%s],%x)\n",
	    inum,
	    jnum,
	    v,
	    w,
	    eg
	);

	fprintf( stderr, "match_num=%ld\n",match_num);
	fprintf( stderr, "unmatch_num=%ld\n",unmatch_num);
#endif
    
	for( i = 1; i < inum; i++ ){
	
		for( j = 1; j < jnum; j++ ){
			if( v[i] == w[j] ){
			 			/* Match                      */
			 	eg[i][j] = match_num;
			
			}else{			/* Unmatch                    */
				eg[i][j] = unmatch_num;
			}
		}
	}
	
	return( 0 );				/* Return                     */
}

/******************************************************************************/
/*                                                                            */
/* Title  : Calculate to matches function                                     */
/* Function Name : Matches                                                    */
/*                                                                            */
/* Detail :                                                                   */
/* Date   : 2010/01/17                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long  inum : Number of array count of i                           */
/*          long  jnum : Number of array count of j                           */
/*          char *v   : Pointer of array of v                                 */
/*          char *w   : Pointer of array of w                                 */
/*                                                                            */
/* Output : long match_cnt : Number of match                                  */
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

long Matches( long inum, long jnum, char *v, char *w ){

	long cnt;				/* Loop counter               */
	long end_num;				/* Loop end number            */
	long match_cnt;				/* Match number               */

						/* Loop end number            */
	if( inum >= jnum ){
						/* End is jnum                */
		end_num = jnum;
	}else{
						/* End is inum                */
		end_num = inum;
	}
						/* Counter reset              */
	match_cnt = 0;

	for( cnt = 0; cnt < end_num; cnt++ ){
	
		if( v[cnt] == w[cnt] ){
						/* Match counter increment    */
			match_cnt++;
		}
	}
	
	return( match_cnt );			/* Return                     */
}

/******************************************************************************/
/*                                                                            */
/* Title  : Global similarly score function                                   */
/* Function Name : GlobalSimilaryScore                                        */
/*                                                                            */
/* Detail :                                                                   */
/* Date   : 2010/02/25                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long inum : Number of array count of i                            */
/*          long jnum : Number of array count of j                            */
/*          char **eg : Pointer of array of Edit Graph                        */
/*          long **ss : Pointer of array of Similary Score                    */
/*          char **bp : Pointer of array of Back tracking pointer             */
/*                                                                            */
/* Output : int : [ 0 : Nornal Terminate ]                                    */
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

int GlobalSimilaryScore(
	long inum,
	long jnum,
	char **eg,
	long **ss,
	char **bp
){

	long i;					/* Loop counter               */
	long j;					/* Loop counter               */
	long d;					/* Gap penalty                */
	long e;					/* Affine gap penalty         */
	
	long del_num;				/* Number of deletion         */
	long ins_num;				/* Number of insertion        */
	long mch_num;				/* Number of mach             */

#ifdef DEBUG
	// debug write
	if( gapscore_mode == AFFINE_GAP_SCORE ){
		fprintf( stderr, "In affine gap score mode: ");
		fprintf( stderr, "d_num=%ld,", d_num );
		fprintf( stderr, "e_num=%ld\n", e_num );
	}else{
		fprintf( stderr, "In liner gap score mode: ");
		fprintf( stderr, "d_num=%ld\n", d_num );
	}
#endif

	for( i = 0; i < inum; i++ ){
		ss[i][0] = 0;			/* Initialize i,0             */
	}
	
	for( j = 0; j < jnum; j++ ){
		ss[0][j] = 0;			/* Initialize 0,j             */
	}
	
	d = d_num;				/* Set gap penalty            */
	e = e_num;				/* Set affine gap penalty     */

	for( i = 1; i < inum; i++ ){
	
		for( j = 1; j < jnum; j++ ){
						/* Calculat to score          */

			if( ( bp[i-1][j] == '|' )
				&& ( gapscore_mode == AFFINE_GAP_SCORE )
			){
				del_num = ss[i-1][j] - e;
			}else{
				del_num = ss[i-1][j] - d;
			}

			if( ( bp[i][j-1] == '-' )
				&& ( gapscore_mode == AFFINE_GAP_SCORE )
			){
				ins_num = ss[i][j-1] - e;
			}else{
				ins_num = ss[i][j-1] - d;
			}

			//mch_num = eg[i-1][j-1] + eg[i][j];
			mch_num = ss[i-1][j-1] + eg[i][j];

						/* Choice number of max       */
			if( ( del_num >= ins_num )
				&& ( del_num >= mch_num ) ){

						/* Choice deletion            */
				ss[i][j] = del_num;
				bp[i][j] = '|';

			}else if( ( ins_num >= del_num )
				&& ( ins_num >= mch_num ) ){

						/* Choice insertion           */
				ss[i][j] = ins_num;
				bp[i][j] = '-';

			}else if( ( mch_num >= ins_num )
				&& ( mch_num >= del_num ) ){

						/* Choice mach                */
				ss[i][j] = mch_num;
				bp[i][j] = '\\';
			}
		}
	}
	
	return(0);				/* Return                     */
}

/******************************************************************************/
/*                                                                            */
/* Title  : Local similarly score function                                    */
/* Function Name : LocalSimilaryScore                                         */
/*                                                                            */
/* Detail :                                                                   */
/* Date   : 2010/03/02                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long  inum : Number of array count of i                           */
/*          long  jnum : Number of array count of j                           */
/*          char **eg : Pointer of array of Edit Graph                        */
/*          long **ss : Pointer of array of Similary Score                    */
/*          char **bp : Pointer of array of Back tracking pointer             */
/*          int  *local_inum : Number of array count of i of local alignment  */
/*          int  *local_jnum : Number of array count of j of local alignment  */
/*                                                                            */
/* Output : int : [ 0 : Nornal Terminate ]                                    */
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

int LocalSimilaryScore(
	long inum,
	long jnum,
	char **eg,
	long **ss,
	char **bp,
	long *local_inum,
	long *local_jnum
){

	long i;					/* Loop counter               */
	long j;					/* Loop counter               */
	long d;					/* Gap penalty                */
	long e;					/* Affine Gap penalty         */

	long biggest_score;
	long local_i;
	long local_j;
	
	long del_num;				/* Number of deletion         */
	long ins_num;				/* Number of insertion        */
	long mch_num;				/* Number of mach             */
	
#ifdef DEBUG
	// debug write
	if( gapscore_mode == AFFINE_GAP_SCORE ){
		fprintf( stderr, "In affine gap score mode: ");
		fprintf( stderr, "d_num=%ld,", d_num );
		fprintf( stderr, "e_num=%ld\n", e_num );
	}else{
		fprintf( stderr, "In liner gap score mode: ");
		fprintf( stderr, "d_num=%ld\n", d_num );
	}
#endif

	for( i = 0; i < inum; i++ ){
		ss[i][0] = 0;			/* Initialize i,0             */
	}
	
	for( j = 0; j < jnum; j++ ){
		ss[0][j] = 0;			/* Initialize 0,j             */
	}
	
	d = d_num;				/* Set gap penalty            */
	e = e_num;				/* Set affine gap penalty     */
	biggest_score = 0;

	for( i = 1; i < inum; i++ ){

		for( j = 1; j < jnum; j++ ){
						/* Calculat to score          */

			if( ( bp[i-1][j] == '|' )
				&& ( gapscore_mode == AFFINE_GAP_SCORE )
			){
				del_num = ss[i-1][j] - e;
			}else{
				del_num = ss[i-1][j] - d;
			}

			if( ( bp[i][j-1] == '-' )
				&& ( gapscore_mode == AFFINE_GAP_SCORE )
			){
				ins_num = ss[i][j-1] - e;
			}else{
				ins_num = ss[i][j-1] - d;
			}

			mch_num = ss[i-1][j-1] + eg[i][j];

						/* Choice number of max       */
			if( ( del_num >= ins_num )
				&& ( del_num >= mch_num )
				&& ( del_num >= 0 )
			){

						/* Choice deletion            */
				ss[i][j] = del_num;
				bp[i][j] = '|';

			}else if( ( ins_num >= del_num )
				&& ( ins_num >= mch_num )
				&& ( ins_num >= 0 )
			){

						/* Choice insertion           */
				ss[i][j] = ins_num;
				bp[i][j] = '-';

			}else if( ( mch_num >= ins_num )
				&& ( mch_num >= del_num )
				&& ( mch_num >= 0 )
			){

						/* Choice mach                */
				ss[i][j] = mch_num;
				bp[i][j] = '\\';

			}else {
						/* Choice zero                */
				ss[i][j] = 0;
				bp[i][j] = '*';
			}

			if( biggest_score < ss[i][j] ){
				biggest_score = ss[i][j];
				local_i = i;
				local_j = j;
			}
		}
	}
						/* inum,jnum is start         */
						/* from No.1                  */
	*local_inum = local_i + 1;
	*local_jnum = local_j + 1;
	
	return(0);				/* Return                     */
}

/******************************************************************************/
/*                                                                            */
/* Title  : Back Traking                                                      */
/* Function Name : Calculate Back Tracking                                    */
/*                                                                            */
/* Detail :                                                                   */
/* Date   : 2009/12/02                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char  *v      : Sequence v                                        */
/*          char  *w      : Sequence w                                        */
/*          long   inum   : Number of array count of i for input              */
/*          long   jnum   : Number of array count of j for input              */
/*          char **eg     : Pointer of array of Edit graph Pointer            */
/*          long **ss     : Pointer of array of Similary score Pointer        */
/*          char **bp     : Pointer of array of Back tracking Pointer         */
/*          char  *v_ans  : Number of answer of v                             */
/*          char  *w_ans  : Number of answer of w                             */
/*          char  *ans    : Number of answer                                  */
/*          long  *vnum   : Number of v sequence                              */
/*          long  *wnum   : Number of w sequence                              */
/*          long  *ansnum : Number of ans sequence                            */
/*          char  *eg_arr : Array of Edit graph Pointer                       */
/*          long  *ss_arr : Array of Similary score Pointer                   */
/*          char  *bp_arr : Array of Backtracking Pointer                     */
/*          long  *egnum  : Number of Edit graph Pointer                      */
/*          long  *ssnum  : Number of Similary score Pointer                  */
/*          long  *bpnum  : Number of Backtracking Pointer                    */
/*          long  *inum_from : Number of array counter of i for output        */
/*          long  *jnum_from : Number of array counter of j for output        */
/*                                                                            */
/* Output : int [ 0 : Normal Terminate ]                                      */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/03/02                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Modifiy to about local alignment                                  */
/*                                                                            */
/* Date   : 2010/10/08                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added procedure about eg_arr,ss_arr.                              */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int BackTracking(
	char *v,
	char *w,
	long inum,
	long jnum,
	char **eg,
	long **ss,
	char **bp,
	char *v_ans,
	char *w_ans,
	char *ans,
	long *vnum,
	long *wnum,
	long *ansnum,
	char *eg_arr,
	long *ss_arr,
	char *bp_arr,
	long *egnum,
	long *ssnum,
	long *bpnum,
	long *inum_from,
	long *jnum_from
){

	long i;					/* Loop counter i            */
	long j;					/* Loop counter j            */
	long v_cnt;				/* Counter of v              */
	long w_cnt;				/* Counter of w              */
	long ans_cnt;				/* Counter of answer         */

	long eg_cnt;				/* Countr of                 */
						/*      Edit graph pointer   */
	long ss_cnt;				/* Countr of Similary score  */
						/*                 pointer   */
	long bp_cnt;				/* Countr of                 */
						/*      backtracking pointer */
	
 						/* Counter initialize        */
 	i = inum - 2;
 	j = jnum - 2;
 	
 	v_cnt   = 0;
 	w_cnt   = 0;
 	ans_cnt = 0;

	eg_cnt  = 0;
	ss_cnt  = 0;
 	bp_cnt  = 0;

	long cnt = 0;
						/* Trace to                  */
						/*     back tracking pointer */
	while( ( i > 0 ) || ( j > 0 ) ){
						/* Set eg number             */
		eg_arr[eg_cnt] = eg[i][j];
						/* Counter increment         */
		eg_cnt++;
						/* Set ss number             */
		ss_arr[ss_cnt] = ss[i][j];
						/* Counter increment         */
		ss_cnt++;

		if( bp[i][j] == '\\' ){
						/* Match                     */
						/* Choice to a sequence      */
			v_ans[v_cnt] = v[i];
			w_ans[w_cnt] = w[j];
			ans[ans_cnt] = v[i];
						/* Set back tracking pointer */
			if( v_ans[v_cnt] == w_ans[w_cnt] ){
				bp_arr[bp_cnt] = '|';
			}else{
				bp_arr[bp_cnt] = ' ';
			}
			bp_cnt++;
						/* Counter increment         */
						/*     and decrement         */
			if( i >= 0 ){
				i--;
			}
			if( j >= 0 ){
				j--;
			}
			v_cnt++;
			w_cnt++;
			ans_cnt++;
			
		}else if( bp[i][j] == '|' ){
						/* Deletion                  */
						/* Set deletion character    */
			v_ans[v_cnt] = v[i];
			w_ans[w_cnt] = '-';
			ans[ans_cnt] = '*';
						/* Set back tracking pointer */
			bp_arr[bp_cnt] = '-';
			bp_cnt++;
						/* Counter increment         */
						/*     and decrement         */
			if( i >= 0 ){
				i--;
			}
			v_cnt++;
			w_cnt++;
			ans_cnt++;

		}else if( bp[i][j] == '-' ){
						/* Insertion                 */
						/* Set insertion character   */
			v_ans[v_cnt] = '-';
			w_ans[w_cnt] = w[j];
			ans[ans_cnt] = '*';
						/* Set back tracking pointer */
			bp_arr[bp_cnt] = '+';
			bp_cnt++;
						/* Counter increment         */
						/*     and decrement         */
			if( j >= 0 ){
				j--;
			}
			v_cnt++;
			w_cnt++;
			ans_cnt++;

		}else if( bp[i][j] == '*' ){

			break;

		}else if( j <= 0 ){
						/* Deletion                  */
						/* Set deletion character    */
			v_ans[v_cnt] = v[i];
			w_ans[w_cnt] = '-';
			ans[ans_cnt] = '*';
						/* Set back tracking pointer */
			bp_arr[bp_cnt] = '-';
			bp_cnt++;
						/* Counter increment         */
						/*     and decrement         */
			if( i >= 0 ){
				i--;
			}
			v_cnt++;
			w_cnt++;
			ans_cnt++;

		}else if( i <= 0 ){
						/* Insertion                 */
						/* Set insertion character   */
			v_ans[v_cnt] = '-';
			w_ans[w_cnt] = w[j];
			ans[ans_cnt] = '*';
						/* Set back tracking pointer */
			bp_arr[bp_cnt] = '+';
			bp_cnt++;
						/* Counter increment         */
						/*     and decrement         */
			if( j >= 0 ){
				j--;
			}
			v_cnt++;
			w_cnt++;
			ans_cnt++;
		}
	}
						/* Set null at footer        */
	v_ans[v_cnt]   = '\0';
	w_ans[w_cnt]   = '\0';
	  ans[ans_cnt] = '\0';
	bp_arr[bp_cnt] = '\0';
		
						/* Set return value          */
	*vnum   = v_cnt;
	*wnum   = w_cnt;
	*ansnum = ans_cnt;
	*egnum  = eg_cnt;
	*ssnum  = ss_cnt;
	*bpnum  = bp_cnt;
	*inum_from = i;
	*jnum_from = j;
	
	return(0);				/* Normal Terminate          */
}

/******************************************************************************/
/*                                                                            */
/* Title  : Load replace score                                                */
/* Function Name : LoadReplaceScore                                           */
/*                                                                            */
/* Detail : Make new                                                          */
/*          Load data from replace score file. ex. blosum62 etc               */
/* Date   : 2010/04/29                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : void                                                              */
/*                                                                            */
/* Output : int : return value [ 0:NORMAL, -1:ERROR ]                         */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/08/22                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added procedure that convert to upper                             */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int LoadReplaceScore(){

	FILE *fp;				/* File pointer               */
	char cur[BUFFER_SIZE];			/* Cursor                     */
	int  cur_cnt;				/* Cursor counter             */
	char token_cnt;				/* Token counter              */
	char token_str[BUFFER_SIZE];		/* Token string               */
	char *token;				/* Token pointer              */
	char *endptr;				/* End pointer for strtok     */
	char *ret;				/* Return value for fgets     */
	int  cnt;				/* General purpose counter    */
	
						/* Replace Score File open    */
	fp = fopen( REPLACESCORE_FILENAME, "r" );

	if( fp == NULL  ){
						/* File open error            */

		printf( "%s file not found.\n", REPLACESCORE_FILENAME );
		return( -1 );
	}
						/* Get a line                 */
	ret = fgets( cur, (size_t)BUFFER_SIZE, fp );

	cnt = 0;
	while( cur[cnt] != '\0' ){
						/* Convert to upper           */
		cur[cnt] = toupper( cur[cnt] );
		cnt++;
	}

	cur_cnt = 0;				/* Cursor counter reset       */

	while( ret != NULL ){
						/* Tokenize by comma          */
		token = strtok( cur, "," );
		token_cnt = 0;			/* Token counter reset        */
		
						/* Get a tokenized word       */
		while( token != NULL && token_cnt <= 2){
		
			strcpy( token_str, token );

			switch( token_cnt ){
						/* Token No.0 v code          */
				case 0:
					rs[cur_cnt].v_cd = token_str[0];
					break;
					
						/* Token No.1 w code          */
				case 1:
					rs[cur_cnt].w_cd = token_str[0];
					break;
					
						/* Token No.2 score           */
				case 2:
					rs[cur_cnt].score
						= strtod( token, &endptr );
					rs[cur_cnt].score *= rs_num;
					break;
					
				default:
					break;
			}
						/* Tokenize by comma          */
			token = strtok( NULL, "," );
			token_cnt++;		/* Token counter increment    */
		}
						/* Get a next line            */
		ret = fgets( cur, (size_t)BUFFER_SIZE, fp );

		cnt = 0;
		while( cur[cnt] != '\0' ){
						/* Convert to upper           */
			cur[cnt] = toupper( cur[cnt] );
			cnt++;
		}

		cur_cnt++;			/* Cursor counter increment   */
	}
						/* File close                 */
	fclose( fp );
						/* Normal terminate           */
	return( 0 );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Devide threads                                                    */
/* Function Name : divide_threads                                             */
/*                                                                            */
/* Detail : Create                                                            */
/* Date   : 2014/06/23                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : void *in_args : structure of "thread_arags" for thread arguments  */
/*                                                                            */
/* Output : int : return value [ 0:NORMAL, -1:ERROR ]                         */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2014/06/23                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Changed for the multi thread.                                     */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

void *divide_threads( void *in_args ){

	thread_args *args;

	if( in_args == NULL ){
		return (void *)NULL;
	}

	args = (thread_args *)in_args;

#ifdef DEBUG
	printf("   n:%ld\n", args->n);
	printf("   i:%ld\n", args->i);
	printf("   j:%ld\n", args->j);
	printf("type:%d\n", args->type);
	printf("mode:%d\n", args->mode);
	printf("v:%s\n", args->v);
	printf("w:%s\n", args->w);
	printf("inum:%ld\n", args->inum);
	printf("jnum:%ld\n", args->jnum);
	fflush(stdin);
#endif
						/* Check for parameter        */
						/*       and set arguments    */
	if( args->n < 0 ){
		return (void *)NULL;
	}
						/* Set n                      */
	long n = args->n;

	if( args->i < 0 ){
		return (void *)NULL;
	}
						/* Set i                      */
	long i = args->i;

	if( args->j < 0 ){
		return (void *)NULL;
	}
						/* Set j                      */
	long j = args->j;

	if( args->type != 0 && args->type != 1 ){
		return (void *)NULL;
	}
						/* Set type                   */
	int type = args->type;

	if( args->mode != 0 && args->mode != 1 ){
		return (void *)NULL;
	}
						/* Set mode                   */
	int mode = args->mode;

	if( args->v == NULL ){
		return (void *)NULL;
	}
						/* Set v                      */
	char *v = args->v;

	if( args->w == NULL ){
		return (void *)NULL;
	}
						/* Set w                      */
	char *w = args->w;

	if( args->eg == NULL ){
		return (void *)NULL;
	}
						/* Set eg                     */
	char **eg = args->eg;

	if( args->ss == NULL ){
		return (void *)NULL;
	}
						/* Set ss                     */
	long **ss = args->ss;

	if( args->bp == NULL ){
		return (void *)NULL;
	}
						/* Set bp                     */
	char **bp = args->bp;

	if( args->inum < 0 ){
		return (void *)NULL;
	}
						/* Set inum                   */
	long inum = args->inum;

	if( args->jnum < 0 ) {
		return (void *)NULL;
	}
						/* Set jnum                   */
	long jnum = args->jnum;
						/* Adjust a start point       */
	i = i - n;
	j = j + n;

	for( n; n > 0; n--, j--, i++ ){
						/* Loop of a cell/thread      */
		calc_matrix(
			i,
			j,
			type,
			mode,
			v,
			w,
			eg,
			ss,
			bp,
			inum,
			jnum
		);
	}
}

/******************************************************************************/
/*                                                                            */
/* Title  : Calculate matrix score for multithreads                           */
/* Function Name : calc_matrix                                                */
/*                                                                            */
/* Detail : Create                                                            */
/* Date   : 2014/03/19                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : void *in_args : structure of "thread_arags" for thread arguments  */
/*        : long i        : Location of sell i                                */
/*        : long j        : Location of sell j                                */
/*        : int type      : A Nucleotide or A Amino Acide                     */
/*        : int mode      : A Gloval alignment or A Local alignment           */
/*        : char *v       : Pointer of v                                      */
/*        : char *w       : Pointer of w                                      */
/*        : char **eg     : Pointer of an edit graph                          */
/*        : long **ss     : Pointer of an similarity score                    */
/*        : char **bp     : Pointer of an backtracking                        */
/*        : long inum     : Number of i max                                   */
/*        : long jnum     : Number of j max                                   */
/*                                                                            */
/* Output : int : return value [ 0:NORMAL ]                                   */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2014/04/12                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Changed for the multi thread.                                     */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int calc_matrix(
	long i,
	long j,
	int type,
	int mode,
	char *v,
	char *w,
	char **eg,
	long **ss,
	char **bp,
	long inum,
	long jnum
){
	long cnt;
	long d;
	long e;
	long del_num;
	long ins_num;
	long mch_num;

#ifdef DEBUG
	printf("i:%ld\n",i);
	printf("j:%ld\n",j);
	printf("type:%d\n",type);
	printf("mode:%d\n",mode);
	printf("v:[%s]\n",v);
	printf("w:[%s]\n",w);
	printf("inum:%ld\n",inum);
	printf("jnum:%ld\n",jnum);
#endif
        switch(type){

        case AMINOACID:
                				/* Calculate for weighting of */
						/* amino acid                 */

                for( cnt = 0; cnt < REPLACE_NUM; cnt++ ){

                        if( rs[cnt].v_cd == v[i] 
                         && rs[cnt].w_cd == w[j] ){ 

                                eg[i][j] = rs[cnt].score;
                                break;  
                        }       
                }       

                break;  

        case NUCLEOTIDE:
                				/* Calculate for weighting of */
						/* nucleotide                 */
                if( v[i] == w[j] ){ 

                        eg[i][j] = match_num;
                }else{  

                        eg[i][j] = unmatch_num;
                }       

                break;  

        default:
                break;  
        }       

        d = d_num;                              /* Set gap penalty            */
        e = e_num;                              /* Set affine gap penalty     */

        switch(mode){

        case GLOBAL_ALIGNMENT:
                                                /* Calculat to score          */

                if( ( bp[i-1][j] == '|' )
                  && ( gapscore_mode == AFFINE_GAP_SCORE )
                ){
                        del_num = ss[i-1][j] - e;
                }else{
                        del_num = ss[i-1][j] - d;
                }

                if( ( bp[i][j-1] == '-' )
                  && ( gapscore_mode == AFFINE_GAP_SCORE )
                ){
                        ins_num = ss[i][j-1] - e;
                }else{
                        ins_num = ss[i][j-1] - d;
                }

                mch_num = ss[i-1][j-1] + eg[i][j];

                                                /* Choice number of max       */
                if( ( del_num >= ins_num )
                  && ( del_num >= mch_num ) ){

                                                /* Choice deletion            */
                        ss[i][j] = del_num;
                        bp[i][j] = '|';

                }else if( ( ins_num >= del_num )
                  && ( ins_num >= mch_num ) ){

                                                /* Choice insertion           */
                        ss[i][j] = ins_num;
                        bp[i][j] = '-';

                }else if( ( mch_num >= ins_num )
                  && ( mch_num >= del_num ) ){

                                                /* Choice mach                */
                        ss[i][j] = mch_num;
                        bp[i][j] = '\\';
                }

                break;

        case LOCAL_ALIGNMENT:
                                                /* Calculat to score          */

                if( ( bp[i-1][j] == '|' )
                        && ( gapscore_mode == AFFINE_GAP_SCORE )
                ){
                        del_num = ss[i-1][j] - e;
                }else{
                        del_num = ss[i-1][j] - d;
                }
                if( ( bp[i][j-1] == '-' )
                        && ( gapscore_mode == AFFINE_GAP_SCORE )
                ){
                        ins_num = ss[i][j-1] - e;
                }else{
                        ins_num = ss[i][j-1] - d;
                }

                mch_num = ss[i-1][j-1] + eg[i][j];

                                                /* Choice number of max       */
                if( ( del_num >= ins_num )
                        && ( del_num >= mch_num )
                        && ( del_num >= 0 )
                ){
                                                /* Choice deletion            */
                        ss[i][j] = del_num;
                        bp[i][j] = '|';

                }else if( ( ins_num >= del_num )
                        && ( ins_num >= mch_num )
                        && ( ins_num >= 0 )
                ){
                                                /* Choice insertion           */
                                                /* Choice insertion           */
                        ss[i][j] = ins_num;
                        bp[i][j] = '-';

                }else if( ( mch_num >= ins_num )
                        && ( mch_num >= del_num )
                        && ( mch_num >= 0 )
                ){
                                                /* Choice mach                */
                        ss[i][j] = mch_num;
                        bp[i][j] = '\\';

                }else {
                                                /* Choice zero                */
                        ss[i][j] = 0;
                        bp[i][j] = '*';
                }
						/* Replace biggest score      */
                if( biggest_score < ss[i][j] ){

			pthread_mutex_lock(&mutex);

                        biggest_score = ss[i][j];

			local_inum = i;
			local_jnum = j;

			pthread_mutex_unlock(&mutex);
                }

                break;

        default:
                break;
        }

	return (void *)NULL;
}
