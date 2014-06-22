/******************************************************************************/
/*                                                                            */
/* Title  : Hidden Markov Model - header file                                 */
/* Program Name : hmm.h                                                       */
/*                                                                            */
/* Detail : Header file of Hidden Markov Model                                */
/* Date   : 2011/02/05                                                        */
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

#ifndef _HMM_H_DEFINED
						/* Processing mode            */
#define MODE_AMINO_ACID 0
#define MODE_NUCLEOTIDE 1
						/* Length of char set max     */
#define MAX_CHAR_SET_NUM 23
						/* Array of amino acid        */
#define AMINO_ACID_ONE_CHAR	"FLSYCWPHQRIMTNKVADEG$#%"

						/* Number of amino acid array */
#define AMINO_ACID_NUM 23

						/* Number of Phenylalanine    */
#define Phe	0
						/* Number of Leucine          */
#define Leu	1
						/* Number of Serine           */
#define Ser	2
						/* Number of Tyrosine         */
#define Tyr	3
						/* Number of Cysteine         */
#define Cys	4
						/* Number of Tryptophan       */
#define Trp	5
						/* Number of Proline          */
#define Pro	6
						/* Number of Histidine        */
#define His	7
						/* Number of Glutamine        */
#define Gln	8
						/* Number of Arginine         */
#define Arg	9
						/* Number of Isoleucine       */
#define Ile	10
						/* Number of Methionine       */
#define Met	11
						/* Number of Threonine        */
#define Thr	12
						/* Number of Asparagine       */
#define Asn	13
						/* Number of Lysine           */
#define Lys	14
						/* Number of Valine           */
#define Val	15
						/* Number of Alanine          */
#define Ala	16
						/* Number of AsparagineAcid   */
#define Asp	17
						/* Number of GlutamicAcid     */
#define Glu	18
						/* Number of Glycine          */
#define Gly	19
						/* Number of Ocher            */
#define Och	20
						/* Number of Amber            */
#define Amb	21
						/* Number of Umber            */
#define Umb	22


						/* Array of nucleotide        */
#define NUCLEOTIDE_ONE_CHAR	"ATGCU"
						/* Number of nucleotide array */
#define NUCLEOTIDE_NUM 5
						/* Adenine                    */
#define Adn	0
						/* Thymine                    */
#define Thn	1
						/* Guanine                    */
#define Gun	2
						/* Cytosine                   */
#define Cyn	3
						/* Uracil                     */
#define Url	4

int  alignment_mode;				/* Aligment mode              */

						/* Structure of transition    */
typedef struct transition {
						/* Processing character set   */
	char *character_set;
						/* Number of characters       */
	long num;
						/* Following number of sum    */
						/*         of each transition */
	long *characters;

						/* Number of total            */
	long total;
						/* Pointer of function        */
	void (*reset)(struct transition *tr);
						/* For reset_tr()             */

	long (*calc_total)(struct transition *tr);
						/* For total_tr()             */

	void (*free)(struct transition *);
						/* For free_tr()              */
} TRNS;
						/* Structure of transition    */
						/*                for compare */
typedef struct transition_for_compare {
						/* Processing character set   */
	char *character_set;
						/* Number of characters       */
	long num;
						/* Following number of ratio  */
						/* (each transition sum)      */
						/*     / (all transition sum) */
	double *characters;
						/* Pointer of function        */
	void (*reset)(struct transition_for_compare *);
						/* For reset_tf_cmp()         */

	void (*free)(struct transition_for_compare *);
						/* For free_tr()              */
} TRNS_FOR_CMP;

						/* Function for TRNS structure*/

						/* Initialize TRNS structure  */
void init_tr(
	struct transition *tr,
	char *processing_char_set,
	long processing_char_num
);

						/* Calculate to total         */
						/*     each amino acid value  */
						/*         in TRNS structure  */
long total_tr( TRNS *tr );

						/* Reset to each value        */
						/*         in TRNS structure  */
void reset_tr( TRNS *tr );

						/* Free to each value         */
						/*         in TRNS structure  */
void free_tr( TRNS *tr );

						/* Function for               */
						/*     TRNS_FOR_CMP structure */

						/* Initialize TRNS structure  */
void init_tf_cmp(
	TRNS_FOR_CMP *tf_cmp,
	char *processing_char_set,
	long processing_char_num
);

						/* Reset to each value        */
						/* in TRNS_FOR_CMP structure  */
void reset_tf_cmp( TRNS_FOR_CMP *tf_cmp );

						/* Free to each value         */
						/* in TRNS_FOR_CMP structure  */
void free_tf_cmp( TRNS_FOR_CMP *tf_cmp );

						/* Transition                 */
						/*       from each character  */
						/*         to each character  */
int from_x( TRNS *tr, int to );

						/* Print trns structure       */
void print_trns( TRNS *tr );

						/* Calculate rate of hmm      */
						/*         of each amino acid */
long rate_hmm_from_file( FILE **in_fp, TRNS_FOR_CMP *tf_cmp );
long rate_hmm( TRNS *tr, TRNS_FOR_CMP *tf_cmp );

						/* Load data of Hidden Markov */
						/*        Model and Calculate */
long load_hmm_data_from_file( char *filename, TRNS_FOR_CMP tf_cmp[]);
long load_hmm_data( TRNS tr[], TRNS_FOR_CMP tf_cmp[]);

						/* Compare TRNS stracture     */
						/*                  by range  */
double tr_tf_cmp( double range, TRNS *tr, TRNS_FOR_CMP *tf_cmp );

						/* Compare all hmm value      */
double hmm_cmp( double range, TRNS tr[], TRNS_FOR_CMP tf_cmp[]);

						/* Calculate hmm              */
						/*         of sequence array  */
void calc_hmm( char *sequence, long length, long offset, TRNS from_tr[]);

						/* Prinit_trns_for_cmp        */
void print_trns_for_cmp( TRNS_FOR_CMP *tf_cmp );

#define _HMM_H_DEFINED
#endif
