/******************************************************************************/
/*                                                                            */
/* Title  : Header of lcs.c                                                   */
/*                                                                            */
/* Header Name : lcs.h                                                        */
/*                                                                            */
/* Detail :                                                                   */
/* Date   : 2010/9/09                                                         */
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
#include <malloc.h>
#include <sys/stat.h>
#include <ctype.h>

#define CUI_MODE		0
#define GUI_MODE		1

#define NUCLEOTIDE		0
#define AMINOACID		1

#define PARTOFSEQUENCE		0
#define ALLSEQUENCE		1

#define GLOBAL_ALIGNMENT	0
#define LOCAL_ALIGNMENT		1

#define LINER_GAP_SCORE		0
#define AFFINE_GAP_SCORE	1

						/*   v sequence display flag  */
#define V_DISP_FLG	1

						/*   w sequence display flag  */
#define W_DISP_FLG	2

						/* ans sequence display flag  */
#define ANS_DISP_FLG	4

						/* gap sequence display flag  */
#define GAP_DISP_FLG	8

						/* eg  sequence display flag  */
#define EG_DISP_FLG	16

						/* ss  sequence display flag  */
#define SS_DISP_FLG	32

						/* bp  sequence display flag  */
#define	BP_DISP_FLG	64

#define ON	1
#define OFF	0

#define BUFFER_SIZE 1024
#define REPLACESCORE_FILENAME "/etc/blosum62"
#define REPLACE_NUM 25*25


						/* Prameter set               */
int set_lcs_param(
	int  disp_flg,
	int  alignment_mode,	
	int  gapscore_mode,
	int  compare_mode,
	int  sequence_mode,
	long match_num,
	long unmatch_num,
	long d_num,
	long e_num,
	long rs_num
);

						/* Initialize function        */
int lcs(
        char *v,
        char *w,
        long  inum,
        long  jnum
);
						/* Function of main procedure */
int Procedure(
	char *v,
	long inum,
	char *w,
	long jnum,
	long v_lc_from,
	long v_lc_to,
	long w_lc_from,
	long w_lc_to
);
						/* Function of                */
						/* Check for filesize         */
long ChkFileSize( char *filename );
						/* Get sequence data          */
long GetSequence( char *filename, char *buff );
						/* Function of Weighting      */
int WeightingForAminoAcid(
        long inum,
        long jnum,
        char *v,
        char *w,
        char **eg
);

int WeightingForNucleotide(
        long inum,
        long jnum,
        char *v,
        char *w,
        char **eg
);

						/* Number of matches          */
long Matches( long inum, long jnum, char *v, char *w );

						/* Function of                */
						/*        GlobalSimilaryScore */
int GlobalSimilaryScore(
	long inum,
	long jnum,
	char **eg,
	long **ss,
	char **bp
);
						/* Function of                */
						/*        LocalSimilaryScore  */
int LocalSimilaryScore(
	long inum,
	long jnum,
	char **eg,
	long **ss,
	char **bp,
	long *local_inum,
	long *local_jnum
);

						/* Function of Back Traking   */
int BackTracking(
	char *v,
	char *w,
	long inum,
	long jnum,
	char **bp,
	char *v_ans,
	char *w_ans,
	char *ans,
	long *vnum,
	long *wnum,
	long *ansnum,
	char *bp_arr,
	long *bpnum,
	long *inum_from,
	long *jnum_from
);

						/* Function of Print Out      */
int PrintOut(
	char *v,
	char *w,
	char **eg,
	long **ss,
	char **bp,
	char *v_ans,
	char *w_ans,
	char *ans,
	char *bp_arr,
	long  inum,
	long  jnum,
	long  vnum,
	long  wnum,
	long  ansnum,
	long  bpnum,
	long  v_lc_from,
	long  v_lc_to,
	long  w_lc_from,
	long  w_lc_to
);
						/* Function of Print out      */
 						/*          for text view     */
int PrintOutForTextViwe(
	char *v,
	char *w,
	char **eg,
	long **ss,
	char **bp,
	char *v_ans,
	char *w_ans,
	char *ans,
	char *bp_arr,
	long  inum,
	long  jnum,
	long  vnum,
	long  wnum,
	long  ansnum,
	long  bpnum,
	long  v_lc_from,
	long  v_lc_to,
	long  w_lc_from,
	long  w_lc_to
);
						/* Load Replace Score         */
int LoadReplaceScore();
