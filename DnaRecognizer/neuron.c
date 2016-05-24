/******************************************************************************/
/*                                                                            */
/* Title  : Neuron Class - Methods                                            */
/* Program Name : neuron.c                                                    */
/*                                                                            */
/* Detail : Methods of Neuron Class                                           */
/* Date   : 2015/05/28                                                        */
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

#include <zlib.h>
#include "neuron.h"
//#include "neuron_mic.h"

/******************************************************************************/
/*                                                                            */
/* Title  : Initialize neuron                                                 */
/* Function Name : init_neuron                                                */
/*                                                                            */
/* Detail : Init method                                                       */
/* Date   : 2015/05/28                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : NEURON_T *n : Neuron pointer for mine                             */
/*          long len    : Length of neuron (Number of neuron)                 */
/*                                                                            */
/* Output : Terminte Normal : 0 , Error : -1                                  */
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

int init_neuron( NEURON_T *n, long len ){
						/* Return value               */
	int ret;
						/* Set length of w            */
	n->w_len = len;
	n->wf_len = 0;
	n->wb_len = 0;
						/* Set bias pointer           */
	n->a = &(n->bias);
	n->b = &(n->bias);
						/* Memory allocate for w      */
	ret = (n->alloc_w)( n );
	if( ret != 0 ){
						/* Error Terminate            */
		return -1;
	}
						/* Normal Terminate           */
	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Allocate memory                                                   */
/* Function Name : alloc_neuron                                               */
/*                                                                            */
/* Detail : Allocate memory                                                   */
/* Date   : 2015/05/28                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : NEURON_T *n : Neuron pointer for mine                             */
/*                                                                            */
/* Output : Terminte Normal : 0 , Error : -1                                  */
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

int alloc_neuron( NEURON_T *n ){
						/* Memory allocate for w      */
	n->w = (double *)malloc( sizeof(double) * n->w_len );
	if( n->w == NULL ){
						/* Error Terminate            */
		return -1;
	}
						/* Normal Terminate           */
	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Free memory for NEURON_T                                          */
/* Function Name : free_neuron                                                */
/*                                                                            */
/* Detail : Free memory for NEURON_T                                          */
/* Date   : 2015/05/28                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : NEURON_T *n : Neuron pointer for mine                             */
/*                                                                            */
/* Output : Terminte Normal : 0 , Error : -1                                  */
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

int free_neuron( NEURON_T *n ){

	if( n->w != NULL ){
						/* Free memory                */
		free( n->w );
		n->w = NULL;

	}else{
						/* Error Terminate            */
		return -1;
	}
						/* Normal Terminate           */
	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Free memory for NEURON_P                                          */
/* Function Name : free_neurons                                               */
/*                                                                            */
/* Detail : Free memory for NEURON_P                                          */
/* Date   : 2015/09/04                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : NEURON_P *n : NEURON_P pointer                                    */
/*                                                                            */
/* Output : Terminte Normal : 0 , Error : -1                                  */
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

int free_neurons( NEURON_P *np ){

	long cnt;
	NEURON_T *n;

	if( np->p == NULL ){

		return -1;
	}else{
		n = np->p;
	}

	for( cnt = 0; cnt < np->num; cnt++ ){

		( n[cnt].free )( &n[cnt] );
	}

	free( np->p );
	np->p = NULL;

	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Create Neuron                                                     */
/* Function Name : create_neuron                                              */
/*                                                                            */
/* Detail : create neuron                                                     */
/* Date   : 2015/05/28                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long num   : Number of Neuron                                     */
/*          long links : Number of links for other neurons                    */
/*                                                                            */
/* Output : Terminte Normal : Pointer of NEURON_T , Error : NULL              */
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

NEURON_T *create_neuron( long num, long links ) {
						/* Loop counter               */
	long cnt;
						/* Pointer for neuron         */
	NEURON_T *n;
						/* Memory allocate for neuron */
	n = (NEURON_T *)malloc( sizeof( NEURON_T ) * num );
	if( n == NULL ){
						/* Error terminate            */
		return NULL;
	}

	for( cnt = 0; cnt < num; cnt++ ){
						/* Set function pointer       */
		n[cnt].init    =  init_neuron;
		n[cnt].alloc_w = alloc_neuron;
		n[cnt].free    =  free_neuron;
						/* Init neuron                */
		(n[cnt].init)( &n[cnt], links );
	}
						/* Return neuron pointer      */
	return n;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Create Neurons                                                    */
/* Function Name : create_neurons                                             */
/*                                                                            */
/* Detail : create neurons                                                    */
/* Date   : 2015/09/03                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long num   : Number of Neuron                                     */
/*          long links : Number of links for other neurons                    */
/*                                                                            */
/* Output : Terminte Normal : Pointer of NEURON_P , Error : NULL              */
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

NEURON_P *create_neurons( NEURON_P *np, long num, long links ) {

	np->p   = create_neuron( num, links );
	np->num = num;
						/* Return NEURON_P pointer    */
	return np;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Create Synapse                                                    */
/* Function Name : create_synapse                                             */
/*                                                                            */
/* Detail : create synapse                                                    */
/* Date   : 2015/05/28                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : NEURON_P *ni : NEUTON_P pointer  side i                           */
/*        : long i_num   : Synapse number of side i                           */
/*        : NEURON_P *nj : NEURON_P pointer  side j                           */
/*        : long j_num   : Synapse number of side j                           */
/*                                                                            */
/* Output : Terminte Normal : Pointer of weight , Error : NULL                */
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

double **create_synapse(
	NEURON_T *ni, long i_num,
	NEURON_T *nj, long j_num
){
						/* i side neuron counter      */
	long i;
						/* j side neuron counter      */
	long j;
						/* Value of weit              */
	double **w;
						/* Allocate memory for        */
						/*      a two demention array */
	w = (double **)malloc( sizeof(double *) * i_num );
	if( w == NULL ){
		return NULL;
	}

	for( i = 0; i < i_num; i++ ){
						/* Allocate memory i          */
		w[i] = (double *)malloc( sizeof(double) * j_num );
		if( w[i] == NULL ){
			return NULL;
		}
	}

	for( i = 0; i < i_num; i++ ){
						/* Set weit for forward       */
		ni[i].wf = w;
		ni[i].wf_len = j_num;
	}

	for( j = 0; j < j_num; j++ ){
						/* Set weit for back          */
		nj[j].wb = w;
		nj[j].wb_len = i_num;
	}
						/* Allocate memory for delta  */
						/*   of a two demention array */
	w = (double **)malloc( sizeof(double *) * i_num );
	if( w == NULL ){
		return NULL;
	}

	for( i = 0; i < i_num; i++ ){
						/* Allocate memory i          */
		w[i] = (double *)malloc( sizeof(double) * j_num );
		if( w[i] == NULL ){
			return NULL;
		}
	}

	for( i = 0; i < i_num; i++ ){
						/* Set weit for forward       */
		ni[i].dwf = w;
	}

	for( j = 0; j < j_num; j++ ){
						/* Set weit for back          */
		nj[j].dwb = w;
	}

	return w;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Create Synapses                                                   */
/* Function Name : create_synapses                                            */
/*                                                                            */
/* Detail : create synapses                                                   */
/* Date   : 2015/09/04                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : NEURON_P *ni : NEUTON_P pointer side i                            */
/*        : NEURON_P *nj : NEURON_P pointer side j                            */
/*                                                                            */
/* Output : Terminte Normal : Pointer of weight , Error : NULL                */
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

double **create_synapses( NEURON_P *ni, NEURON_P *nj ){

	return create_synapse( ni->p, ni->num, nj->p, nj->num );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Load neurons parameters                                           */
/* Function Name : load_neuron                                                */
/*                                                                            */
/* Detail : Load neurons parameters                                           */
/* Date   : 2015/09/04                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : FILE     *fp  : File pointer                                      */
/*        : NEURON_P *n   : NEURON_P pointer                                  */
/*                                                                            */
/* Output : Terminte Normal : 0 , Error : != 0                                */
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

int load_neuron( FILE *fp, NEURON_P *np ){

	long unit_cnt;
	long      cnt;
	long     icnt;
	long     jcnt;
	long     kcnt;
	char str[4096000];
	char *token;

	NEURON_T *n;
	long unit_num;

	if( np->p == NULL ){

		return -1;
	}else{
		n = np->p;
		unit_num = np->num;
	}

	fgets( str, 4096000, fp );

	token = strtok( str, "," );
	if( token == NULL ){
		return 1;
	}

	for( unit_cnt = 0; unit_cnt < unit_num - 1; unit_cnt++ ){

						// Set z (01)
		n[unit_cnt].z = atof( token );

						// Set u (02)
		token = strtok( NULL, "," );
		if( token == NULL ){
			return 2;
		}
		n[unit_cnt].u = atof( token );
						// Set a (03)
		token = strtok( NULL, "," );
		if( token == NULL ){
			return 3;
		}
		*(n[unit_cnt].a) = atof( token );
						// Set da (04)
		token = strtok( NULL, "," );
		if( token == NULL ){
			return 4;
		}
		n[unit_cnt].da = atof( token );
						// Set b (05)
		token = strtok( NULL, "," );
		if( token == NULL ){
			return 5;
		}
		*(n[unit_cnt].b) = atof( token );
						// Set db (06)
		token = strtok( NULL, "," );
		if( token == NULL ){
			return 6;
		}
		n[unit_cnt].db = atof( token );
						// Set d (07)
		token = strtok( NULL, "," );
		if( token == NULL ){
			return 7;
		}
		n[unit_cnt].d = atof( token );
						// Set dw (08)
		token = strtok( NULL, "," );
		if( token == NULL ){
			return 8;
		}
		n[unit_cnt].dw = atof( token );
						// Set bias (09)
		token = strtok( NULL, "," );
		if( token == NULL ){
			return 9;
		}
		n[unit_cnt].bias = atof( token );
						// Set w_len (10)
		token = strtok( NULL, "," );
		if( token == NULL ){
			return 10;
		}
		n[unit_cnt].w_len = atol( token );
						// Set wf_len (11)
		token = strtok( NULL, "," );
		if( token == NULL ){
			return 11;
		}
		n[unit_cnt].wf_len = atol( token );
						// Set wb_len (12)
		token = strtok( NULL, "," );
		if( token == NULL ){
			return 12;
		}
		n[unit_cnt].wb_len = atol( token );

		for( cnt = 0; cnt < n[unit_cnt].w_len; cnt++ ){

						// Set wb_len
			token = strtok( NULL, "," );
			if( token == NULL ){
				return 13;
			}
			n[unit_cnt].w[cnt] = atof( token );
		}

		for( jcnt = 0; jcnt < unit_num; jcnt++ ){
			for( kcnt = 0; kcnt < n[unit_cnt].wf_len; kcnt++ ){

						// Set wb_len
				token = strtok( NULL, "," );
				if( token == NULL ){
					return 14;
				}
				n[unit_cnt].wf[jcnt][kcnt] = atof( token );
			}
		}

		for( jcnt = 0; jcnt < unit_num; jcnt++ ){
			for( kcnt = 0; kcnt < n[unit_cnt].wf_len; kcnt++ ){

						// Set wb_len
				token = strtok( NULL, "," );
				if( token == NULL ){
					return 15;
				}
				n[unit_cnt].dwf[jcnt][kcnt] = atof( token );
			}
		}

		for( jcnt = 0; jcnt < unit_num; jcnt++ ){
			for( icnt = 0; icnt < n[unit_cnt].wb_len; icnt++ ){

						// Set wb_len
				token = strtok( NULL, "," );
				if( token == NULL ){
					return 16;
				}
				n[unit_cnt].wb[icnt][jcnt] = atof( token );
			}
		}

		for( jcnt = 0; jcnt < unit_num; jcnt++ ){
			for( icnt = 0; icnt < n[unit_cnt].wb_len; icnt++ ){

						// Set wb_len
				token = strtok( NULL, "," );
				if( token == NULL ){
					return 17;
				}
				n[unit_cnt].dwb[icnt][jcnt] = atof( token );
			}
		}
						// Next line
		fgets( str, 4096000, fp );

		token = strtok( str, "," );
		if( token == NULL ){
			exit(0);
			return -1;
		}
	}

	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Load neurons parameters for binary                                */
/* Function Name : load_neuron_b                                              */
/*                                                                            */
/* Detail : Load neurons parameters for binary                                */
/* Date   : 2016/01/22                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : FILE     *fp  : File pointer                                      */
/*        : NEURON_P *np  : NEURON_P pointer                                  */
/*                                                                            */
/* Output : Terminte Normal : 0 , Error : -1                                  */
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

int load_neuron_b( FILE *fp, NEURON_P *np ){

	long unit_cnt;
	long      cnt;
	long     icnt;
	long     jcnt;
	long     kcnt;

	NEURON_T *n;
	long unit_num;

	if( np->p == NULL ){

		return -1;
	}else{
		n = np->p;
		unit_num = np->num;
	}

	for( unit_cnt = 0; unit_cnt < unit_num; unit_cnt++ ){

						// Set z (01)

		//n[unit_cnt].z = atof( token );
		fread( &(n[unit_cnt].z), sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("z:%f\n",n[unit_cnt].z);
						// Set u (02)
		//token = strtok( NULL, "," );
		//if( token == NULL ){
		//	exit(0);
		//	return -1;
		//}
		//n[unit_cnt].u = atof( token );
		fread( &(n[unit_cnt].u), sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("u:%f\n",n[unit_cnt].u);
						// Set a (03)
		//token = strtok( NULL, "," );
		//if( token == NULL ){
		//	exit(0);
		//	return -1;
		//}
		//*(n[unit_cnt].a) = atof( token );
		fread( &(n[unit_cnt].a), sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("a:%f\n",n[unit_cnt].a);
						// Set da (04)
		//token = strtok( NULL, "," );
		//if( token == NULL ){
		//	exit(0);
		//	return -1;
		//}
		//n[unit_cnt].da = atof( token );
		fread( &(n[unit_cnt].da), sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("da:%f\n",n[unit_cnt].da);
						// Set b (05)
		//token = strtok( NULL, "," );
		//if( token == NULL ){
		//	exit(0);
		//	return -1;
		//}
		//*(n[unit_cnt].b) = atof( token );
		fread( &(*(n[unit_cnt].b)), sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("b:%f\n",*(n[unit_cnt].b));
						// Set db (06)
		//token = strtok( NULL, "," );
		//if( token == NULL ){
		//	exit(0);
		//	return -1;
		//}
		//n[unit_cnt].db = atof( token );
		fread( &(n[unit_cnt].db), sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("db:%f\n",n[unit_cnt].db);
						// Set d (07)
		//token = strtok( NULL, "," );
		//if( token == NULL ){
		//	exit(0);
		//	return -1;
		//}
		//n[unit_cnt].d = atof( token );
		fread( &(n[unit_cnt].d), sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("d:%f\n",n[unit_cnt].d);
						// Set dw (08)
		//token = strtok( NULL, "," );
		//if( token == NULL ){
		//	exit(0);
		//	return -1;
		//}
		//n[unit_cnt].dw = atof( token );
		fread( &(n[unit_cnt].dw), sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("dw:%f\n",n[unit_cnt].dw);
						// Set bias (09)
		//token = strtok( NULL, "," );
		//if( token == NULL ){
		//	exit(0);
		//	return -1;
		//}
		//n[unit_cnt].bias = atof( token );
		fread( &(n[unit_cnt].bias), sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("bias:%f\n",n[unit_cnt].bias);
						// Set w_len (10)
		//token = strtok( NULL, "," );
		//if( token == NULL ){
		//	exit(0);
		//	return -1;
		//}
		//n[unit_cnt].w_len = atol( token );
		fread( &(n[unit_cnt].w_len), sizeof(long), 1, fp );

		//if(unit_cnt == 0) printf("w_len:%ld\n",n[unit_cnt].w_len);
						// Set wf_len (11)
		//token = strtok( NULL, "," );
		//if( token == NULL ){
		//	exit(0);
		//	return -1;
		//}
		//n[unit_cnt].wf_len = atol( token );
		fread( &(n[unit_cnt].wf_len), sizeof(long), 1, fp );

		//if(unit_cnt == 0) printf("wf_len:%ld\n",n[unit_cnt].wf_len);
						// Set wb_len (12)
		//token = strtok( NULL, "," );
		//if( token == NULL ){
		//	exit(0);
		//	return -1;
		//}
		//n[unit_cnt].wb_len = atol( token );
		fread( &(n[unit_cnt].wb_len), sizeof(long), 1, fp );

		//if(unit_cnt == 0) printf("wb_len:%ld\n",n[unit_cnt].wb_len);

		for( cnt = 0; cnt < n[unit_cnt].w_len; cnt++ ){

						// Set wb_len
			//token = strtok( NULL, "," );
			//if( token == NULL ){
			//	exit(0);
			//	return -1;
			//}
			//n[unit_cnt].w[cnt] = atof( token );
			fread( &(n[unit_cnt].w[cnt]), sizeof(double), 1, fp );

			//if(unit_cnt == 0)
			//	printf("w[%ld]:%f\n",
			//		cnt,
			//		n[unit_cnt].w[cnt]
			//	);
		}

		for( jcnt = 0; jcnt < unit_num; jcnt++ ){
			for( kcnt = 0; kcnt < n[unit_cnt].wf_len; kcnt++ ){

						// Set wb_len
				//token = strtok( NULL, "," );
				//if( token == NULL ){
				//	exit(0);
				//	return -1;
				//}
				//n[unit_cnt].wf[jcnt][kcnt] = atof( token );
				fread( &(n[unit_cnt].wf[jcnt][kcnt]),
					sizeof(double), 1, fp );

				//if(unit_cnt == 0)
				//	printf("wf[%ld][%ld]:%f\n",
				//		jcnt,
				//		kcnt,
				//		n[unit_cnt].wf[jcnt][kcnt]
				//	);
			}
		}

		for( jcnt = 0; jcnt < unit_num; jcnt++ ){
			for( kcnt = 0; kcnt < n[unit_cnt].wf_len; kcnt++ ){

						// Set wb_len
				//token = strtok( NULL, "," );
				//if( token == NULL ){
				//	exit(0);
				//	return -1;
				//}
				//n[unit_cnt].dwf[jcnt][kcnt] = atof( token );
				fread( &(n[unit_cnt].dwf[jcnt][kcnt]),
					sizeof(double), 1, fp );

				//if(unit_cnt == 0)
				//	printf("dwf[%ld][%ld]:%f\n",
				//		jcnt,
				//		kcnt,
				//		n[unit_cnt].dwf[jcnt][kcnt]
				//	);
			}
		}

		for( jcnt = 0; jcnt < unit_num; jcnt++ ){
			for( icnt = 0; icnt < n[unit_cnt].wb_len; icnt++ ){

						// Set wb_len
				//token = strtok( NULL, "," );
				//if( token == NULL ){
				//	exit(0);
				//	return -1;
				//}
				//n[unit_cnt].wb[icnt][jcnt] = atof( token );
				fread( &(n[unit_cnt].wb[icnt][jcnt]),
					sizeof(double), 1, fp );

				//if(unit_cnt == 0)
				//	printf("wb[%ld][%ld]:%f\n",
				//		icnt,
				//		jcnt,
				//		n[unit_cnt].wb[icnt][jcnt]
				//	);
			}
		}

		for( jcnt = 0; jcnt < unit_num; jcnt++ ){
			for( icnt = 0; icnt < n[unit_cnt].wb_len; icnt++ ){

						// Set wb_len
				//token = strtok( NULL, "," );
				//if( token == NULL ){
				//	exit(0);
				//	return -1;
				//}
				//n[unit_cnt].dwb[icnt][jcnt] = atof( token );
				fread( &(n[unit_cnt].dwb[icnt][jcnt]),
					sizeof(double), 1, fp );

				//if(unit_cnt == 0)
				//	printf("dwb[%ld][%ld]:%f\n",
				//		icnt,
				//		jcnt,
				//		n[unit_cnt].dwb[icnt][jcnt]
				//	);
			}
		}
	}

	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Load neurons parameters for gzip complessing                      */
/* Function Name : load_neuron_z                                              */
/*                                                                            */
/* Detail : Load neurons parameters for gzip complessing                      */
/* Date   : 2016/01/22                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : gzFile    fp  : File pointer of gzFile                            */
/*        : NEURON_P *np  : NEURON_P pointer                                  */
/*                                                                            */
/* Output : Terminte Normal : 0 , Error : != 0                                */
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

int load_neuron_z( gzFile fp, NEURON_P *np ){

	long unit_cnt;
	long      cnt;
	long     icnt;
	long     jcnt;
	long     kcnt;

	NEURON_T *n;
	long unit_num;
	int ret;

	if( np->p == NULL ){

		return -1;
	}else{
		n = np->p;
		unit_num = np->num;
	}

	for( unit_cnt = 0; unit_cnt < unit_num; unit_cnt++ ){

						// Set z (01)

		ret = gzread( fp, &(n[unit_cnt].z), sizeof(double) );
		if( ret != sizeof(double) ){

			return 1;
		}
						// Set u (02)

		ret = gzread( fp, &(n[unit_cnt].u), sizeof(double) );
		if( ret != sizeof(double) ){

			return 2;
		}
						// Set a (03)

		ret = gzread( fp, &(n[unit_cnt].a), sizeof(double) );
		if( ret != sizeof(double) ){

			return 3;
		}
						// Set da (04)

		ret = gzread( fp, &(n[unit_cnt].da), sizeof(double) );
		if( ret != sizeof(double) ){

			return 4;
		}
						// Set b (05)

		ret = gzread( fp, &(*(n[unit_cnt].b)), sizeof(double) );
		if( ret != sizeof(double) ){

			return 5;
		}
						// Set db (06)

		ret = gzread( fp, &(n[unit_cnt].db), sizeof(double) );
		if( ret != sizeof(double) ){
			return 6;
		}
						// Set d (07)

		ret = gzread( fp, &(n[unit_cnt].d), sizeof(double) );
		if( ret != sizeof(double) ){

			return 7;
		}
						// Set dw (08)

		ret = gzread( fp, &(n[unit_cnt].dw), sizeof(double) );
		if( ret != sizeof(double) ){

			return 8;
		}
						// Set bias (09)

		ret = gzread( fp, &(n[unit_cnt].bias), sizeof(double) );
		if( ret != sizeof(double) ){

			return 9;
		}
						// Set w_len (10)

		ret = gzread( fp, &(n[unit_cnt].w_len), sizeof(long) );
		if( ret != sizeof(long) ){

			return 10;
		}
						// Set wf_len (11)

		ret = gzread( fp, &(n[unit_cnt].wf_len), sizeof(long) );
		if( ret != sizeof(long) ){

			return 11;
		}
						// Set wb_len (12)

		ret = gzread( fp, &(n[unit_cnt].wb_len), sizeof(long) );
		if( ret != sizeof(long) ){

			return 12;
		}

		for( cnt = 0; cnt < n[unit_cnt].w_len; cnt++ ){

						// Set wb_len (13)
			ret = gzread( fp, &(n[unit_cnt].w[cnt]), sizeof(double) );
			if( ret != sizeof(double) ){

				return 13;
			}
		}

		for( jcnt = 0; jcnt < unit_num; jcnt++ ){
			for( kcnt = 0; kcnt < n[unit_cnt].wf_len; kcnt++ ){

						// Set wb_len (14)
				ret = gzread(
					fp,
					&(n[unit_cnt].wf[jcnt][kcnt]),
					sizeof(double)
				);

				if( ret != sizeof(double) ){

					return 14;
				}
			}
		}

		for( jcnt = 0; jcnt < unit_num; jcnt++ ){
			for( kcnt = 0; kcnt < n[unit_cnt].wf_len; kcnt++ ){

						// Set wb_len (15)
				ret = gzread(
					fp,
					&(n[unit_cnt].dwf[jcnt][kcnt]),
					sizeof(double)
				);

				if( ret != sizeof(double) ){

					return 15;
				}
			}
		}

		for( jcnt = 0; jcnt < unit_num; jcnt++ ){
			for( icnt = 0; icnt < n[unit_cnt].wb_len; icnt++ ){

						// Set wb_len (16)
				ret = gzread(
					fp,
					&(n[unit_cnt].wb[icnt][jcnt]),
					sizeof(double)
				);

				if( ret != sizeof(double) ){

					return 16;
				}
			}
		}

		for( jcnt = 0; jcnt < unit_num; jcnt++ ){
			for( icnt = 0; icnt < n[unit_cnt].wb_len; icnt++ ){

						// Set wb_len (17)
				ret = gzread(
					fp,
					&(n[unit_cnt].dwb[icnt][jcnt]),
					sizeof(double)
				);

				if( ret != sizeof(double) ){

					return 17;
				}
			}
		}
	}

	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Save neurons parameters                                           */
/* Function Name : save_neuron                                                */
/*                                                                            */
/* Detail : Save neurons parameters                                           */
/* Date   : 2015/09/04                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : FILE     *fp  : File pointer                                      */
/*        : NEURON_P *np  : NEURON_P pointer                                  */
/*                                                                            */
/* Output : Terminte Normal : 0 , Error : != 0                                */
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

int save_neuron( FILE *fp, NEURON_P *np ){

	long      cnt;
	long     icnt;
	long     jcnt;
	long     kcnt;
	long unit_cnt;

	long wlen;
	long ilen;
	long jlen;
	long klen;

	NEURON_T *n;
	long unit_num;

	if( np->p == NULL ){

		return -1;
	}else{
		n = np->p;
		unit_num = np->num;
	}

	for( unit_cnt = 0; unit_cnt < unit_num; unit_cnt++ ){

		fprintf( fp, "%.12f,",   n[unit_cnt].z      );
		fprintf( fp, "%.12f,",   n[unit_cnt].u      );
		fprintf( fp, "%.12f,", *(n[unit_cnt].a)     );
		fprintf( fp, "%.12f,",   n[unit_cnt].da     );
		fprintf( fp, "%.12f,", *(n[unit_cnt].b)     );
		fprintf( fp, "%.12f,",   n[unit_cnt].db     );
		fprintf( fp, "%.12f,",   n[unit_cnt].d      );
		fprintf( fp, "%.12f,",   n[unit_cnt].dw     );
		fprintf( fp, "%.12f,",   n[unit_cnt].bias   );
		fprintf( fp, "%ld,"  ,   n[unit_cnt].w_len  );
		fprintf( fp, "%ld,"  ,   n[unit_cnt].wf_len );
		fprintf( fp, "%ld"   ,   n[unit_cnt].wb_len );

		wlen = (long)n[unit_cnt].w_len;
		klen = (long)n[unit_cnt].wf_len;
		jlen = unit_num;
		ilen = (long)n[unit_cnt].wb_len;

		for( cnt = 0; cnt < wlen; cnt++ ){
			fprintf( fp, ",%.12f", n[unit_cnt].w[cnt] );
		}

		for( jcnt = 0; jcnt < jlen; jcnt++ ){
			for( kcnt = 0; kcnt < klen; kcnt++ ){
				fprintf( fp, ",%.12f",
					n[unit_cnt].wf[jcnt][kcnt]
				);
			}
		}

		for( jcnt = 0; jcnt < jlen; jcnt++ ){
			for( kcnt = 0; kcnt < klen; kcnt++ ){
				fprintf( fp, ",%.12f",
					n[unit_cnt].dwf[jcnt][kcnt]
				);
			}
		}

		for( jcnt = 0; jcnt < jlen; jcnt++ ){
			for( icnt = 0; icnt < ilen; icnt++ ){
				fprintf( fp, ",%.12f",
					n[unit_cnt].wb[icnt][jcnt]
				);
			}
		}

		for( jcnt = 0; jcnt < jlen; jcnt++ ){
			for( icnt = 0; icnt < ilen; icnt++ ){
				fprintf( fp, ",%.12f",
					n[unit_cnt].dwb[icnt][jcnt]
				);
			}
		}

		fprintf( fp, "\n" );
	}

	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Save neurons parameters for binary                                */
/* Function Name : save_neuron_b                                              */
/*                                                                            */
/* Detail : Save neurons parameters for binary                                */
/* Date   : 2016/01/22                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : FILE     *fp  : File pointer                                      */
/*        : NEURON_P *np  : NEURON_P pointer                                  */
/*                                                                            */
/* Output : Terminte Normal : 0 , Error : -1                                  */
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

int save_neuron_b( FILE *fp, NEURON_P *np ){

	long      cnt;
	long     icnt;
	long     jcnt;
	long     kcnt;
	long unit_cnt;

	long wlen;
	long ilen;
	long jlen;
	long klen;

	NEURON_T *n;
	long unit_num;

	if( np->p == NULL ){

		return -1;
	}else{
		n = np->p;
		unit_num = np->num;
	}

	for( unit_cnt = 0; unit_cnt < unit_num; unit_cnt++ ){

		//fprintf( fp, "%.12f,",   n[unit_cnt].z      );
		fwrite( &n[unit_cnt].z, sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("z:%f\n",n[unit_cnt].z);

		//fprintf( fp, "%.12f,",   n[unit_cnt].u      );
		fwrite( &n[unit_cnt].u, sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("u:%f\n",n[unit_cnt].u);

		//fprintf( fp, "%.12f,", *(n[unit_cnt].a)     );
		fwrite( &n[unit_cnt].a, sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("a:%f\n",n[unit_cnt].a);

		//fprintf( fp, "%.12f,",   n[unit_cnt].da     );
		fwrite( &n[unit_cnt].da, sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("da:%f\n",n[unit_cnt].da);

		//fprintf( fp, "%.12f,", *(n[unit_cnt].b)     );
		fwrite( &(*(n[unit_cnt].b)), sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("b:%f\n",*(n[unit_cnt].b));

		//fprintf( fp, "%.12f,",   n[unit_cnt].db     );
		fwrite( &n[unit_cnt].db, sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("db:%f\n",n[unit_cnt].db);

		//fprintf( fp, "%.12f,",   n[unit_cnt].d      );
		fwrite( &n[unit_cnt].d, sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("d:%f\n",n[unit_cnt].d);

		//fprintf( fp, "%.12f,",   n[unit_cnt].dw     );
		fwrite( &n[unit_cnt].dw, sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("dw:%f\n",n[unit_cnt].dw);

		//fprintf( fp, "%.12f,",   n[unit_cnt].bias   );
		fwrite( &n[unit_cnt].bias, sizeof(double), 1, fp );

		//if(unit_cnt == 0) printf("bias:%f\n",n[unit_cnt].bias);

		//fprintf( fp, "%ld,"  ,   n[unit_cnt].w_len  );
		fwrite( &n[unit_cnt].w_len, sizeof(long), 1, fp );

		//if(unit_cnt == 0) printf("w_len:%ld\n",n[unit_cnt].w_len);

		//fprintf( fp, "%ld,"  ,   n[unit_cnt].wf_len );
		fwrite( &n[unit_cnt].wf_len, sizeof(long), 1, fp );

		//if(unit_cnt == 0) printf("wf_len:%ld\n",n[unit_cnt].wf_len);

		//fprintf( fp, "%ld"   ,   n[unit_cnt].wb_len );
		fwrite( &n[unit_cnt].wb_len, sizeof(long), 1, fp );

		//if(unit_cnt == 0) printf("wb_len:%ld\n",n[unit_cnt].wb_len);

		wlen = (long)n[unit_cnt].w_len;
		klen = (long)n[unit_cnt].wf_len;
		jlen = unit_num;
		ilen = (long)n[unit_cnt].wb_len;

		for( cnt = 0; cnt < wlen; cnt++ ){
			//fprintf( fp, ",%.12f", n[unit_cnt].w[cnt] );
			fwrite( &n[unit_cnt].w[cnt], sizeof(double), 1, fp );

			//if(unit_cnt == 0) printf("w[%ld]:%f\n",cnt, n[unit_cnt].w[cnt]);
		}

		for( jcnt = 0; jcnt < jlen; jcnt++ ){
			for( kcnt = 0; kcnt < klen; kcnt++ ){
				//fprintf( fp, ",%.12f",
				//	n[unit_cnt].wf[jcnt][kcnt]
				//);
				fwrite( &n[unit_cnt].wf[jcnt][kcnt],
					sizeof(double), 1, fp
				);

				//if(unit_cnt == 0)
				//	printf("wf[%ld][%ld]:%f\n",
				//		jcnt, kcnt,
				//		n[unit_cnt].wf[jcnt][kcnt]
				//	);
			}
		}

		for( jcnt = 0; jcnt < jlen; jcnt++ ){
			for( kcnt = 0; kcnt < klen; kcnt++ ){
				//fprintf( fp, ",%.12f",
				//	n[unit_cnt].dwf[jcnt][kcnt]
				//);
				fwrite( &n[unit_cnt].dwf[jcnt][kcnt],
					sizeof(double), 1, fp
				);

				//if(unit_cnt == 0)
				//	printf("dwf[%ld][%ld]:%f\n",
				//		jcnt, kcnt,
				//		n[unit_cnt].dwf[jcnt][kcnt]
				//	);
			}
		}

		for( jcnt = 0; jcnt < jlen; jcnt++ ){
			for( icnt = 0; icnt < ilen; icnt++ ){
				//fprintf( fp, ",%.12f",
				//	n[unit_cnt].wb[icnt][jcnt]
				//);
				fwrite( &n[unit_cnt].wb[icnt][jcnt],
					sizeof(double), 1, fp
				);

				//if(unit_cnt == 0)
				//	printf("wb[%ld][%ld]:%f\n",
				//		icnt, jcnt,
				//		n[unit_cnt].wb[icnt][jcnt]
				//	);
			}
		}

		for( jcnt = 0; jcnt < jlen; jcnt++ ){
			for( icnt = 0; icnt < ilen; icnt++ ){
				//fprintf( fp, ",%.12f",
				//	n[unit_cnt].dwb[icnt][jcnt]
				//);
				fwrite( &n[unit_cnt].dwb[icnt][jcnt],
					sizeof(double), 1, fp
				);

				//if(unit_cnt == 0)
				//	printf("dwb[%ld][%ld]:%f\n",
				//		icnt, jcnt,
				//		n[unit_cnt].dwb[icnt][jcnt]
				//	);
			}
		}
	}

	return 0;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Save neurons parameters for gzip compressing                      */
/* Function Name : save_neuron_z                                              */
/*                                                                            */
/* Detail : Save neurons parameters for gzip compressing                      */
/* Date   : 2016/01/22                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : gzFile   *fp  : File pointer of gzip                              */
/*        : NEURON_P *np  : NEURON_P pointer                                  */
/*                                                                            */
/* Output : Terminte Normal : 0 , Error : != 0                                */
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

int save_neuron_z( gzFile fp, NEURON_P *np ){

	long      cnt;
	long     icnt;
	long     jcnt;
	long     kcnt;
	long unit_cnt;

	long wlen;
	long ilen;
	long jlen;
	long klen;

	NEURON_T *n;
	long unit_num;
	int ret;

	if( np->p == NULL ){

		return -1;
	}else{
		n = np->p;
		unit_num = np->num;
	}

	for( unit_cnt = 0; unit_cnt < unit_num; unit_cnt++ ){

						// Set z (01)

		ret = gzwrite( fp, &n[unit_cnt].z, sizeof(double) );
		if( ret != sizeof(double) ){

			return 1;
		}
						// Set u (02)

		ret = gzwrite( fp, &n[unit_cnt].u, sizeof(double) );
		if( ret != sizeof(double) ){

			return 2;
		}
						// Set a (03)

		ret = gzwrite( fp, &n[unit_cnt].a, sizeof(double) );
		if( ret != sizeof(double) ){

			return 3;
		}
						// Set da (03)

		ret = gzwrite( fp, &n[unit_cnt].da, sizeof(double) );
		if( ret != sizeof(double) ){

			return 4;
		}
						// Set b (04)

		ret = gzwrite( fp, &(*(n[unit_cnt].b)), sizeof(double) );
		if( ret != sizeof(double) ){

			return 5;
		}
						// Set db (06)

		ret = gzwrite( fp, &n[unit_cnt].db, sizeof(double) );
		if( ret != sizeof(double) ){

			return 6;
		}
						// Set d (07)

		ret = gzwrite( fp, &n[unit_cnt].d, sizeof(double) );
		if( ret != sizeof(double) ){

			return 7;
		}
						// Set dw (08)

		ret = gzwrite( fp, &n[unit_cnt].dw, sizeof(double) );
		if( ret != sizeof(double) ){

			return 8;
		}
						// Set dw (09)

		ret = gzwrite( fp, &n[unit_cnt].bias, sizeof(double) );
		if( ret != sizeof(double) ){

			return 9;
		}
						// Set w_len (10)

		ret = gzwrite( fp, &n[unit_cnt].w_len, sizeof(long) );
		if( ret != sizeof(long) ){

			return 10;
		}
						// Set wf_len (11)

		ret = gzwrite( fp, &n[unit_cnt].wf_len, sizeof(long) );
		if( ret != sizeof(long) ){

			return 11;
		}
						// Set wb_len (12)

		ret = gzwrite( fp, &n[unit_cnt].wb_len, sizeof(long) );
		if( ret != sizeof(long) ){

			return 12;
		}

		wlen = (long)n[unit_cnt].w_len;
		klen = (long)n[unit_cnt].wf_len;
		jlen = unit_num;
		ilen = (long)n[unit_cnt].wb_len;

		for( cnt = 0; cnt < wlen; cnt++ ){

						// Set w (13)

			ret = gzwrite( fp, &n[unit_cnt].w[cnt], sizeof(double) );
			if( ret != sizeof(double) ){

				return 13;
			}
		}

		for( jcnt = 0; jcnt < jlen; jcnt++ ){
			for( kcnt = 0; kcnt < klen; kcnt++ ){

						// Set wf (14)

				ret = gzwrite( fp, &n[unit_cnt].wf[jcnt][kcnt],
					sizeof(double)
				);

				if( ret != sizeof(double) ){

					return 14;
				}
			}
		}

		for( jcnt = 0; jcnt < jlen; jcnt++ ){
			for( kcnt = 0; kcnt < klen; kcnt++ ){

						// Set wb_len (15)

				ret = gzwrite( fp, &n[unit_cnt].dwf[jcnt][kcnt],
					sizeof(double)
				);

				if( ret != sizeof(double) ){

					return 15;
				}
			}
		}

		for( jcnt = 0; jcnt < jlen; jcnt++ ){
			for( icnt = 0; icnt < ilen; icnt++ ){

						// Set wb_len (16)

				ret = gzwrite( fp, &n[unit_cnt].wb[icnt][jcnt],
					sizeof(double)
				);

				if( ret != sizeof(double) ){

					return 16;
				}
			}
		}

		for( jcnt = 0; jcnt < jlen; jcnt++ ){
			for( icnt = 0; icnt < ilen; icnt++ ){

						// Set wb_len (17)

				ret = gzwrite( fp, &n[unit_cnt].dwb[icnt][jcnt],
					sizeof(double)
				);

				if( ret != sizeof(double) ){

					return 17;
				}
			}
		}
	}

	return 0;
}

/*
#define V_NUM 5
/*
#define V_NUM 5
#define H_NUM 3

int main(){

	long cnt;

	NEURON_T *nv = create_neuron( V_NUM, H_NUM );
	NEURON_T *nh = create_neuron( H_NUM, V_NUM );

	  double **w = create_synapse( nv, V_NUM, nh, H_NUM );

	nv->wf[0][0] = 0.12345;
	nv->wf[4][2] = 0.9876;

	nh->wb[0][0] = 9.12345;
	nh->wb[4][2] = 9.98765;

	printf("nv->wf[0][0]=%f\n",nv->wf[0][0]);
	printf("nv->wf[4][2]=%f\n",nv->wf[4][2]);

	printf("nh->wb[0][0]=%f\n",nh->wb[0][0]);
	printf("nh->wb[4][2]=%f\n",nh->wb[4][2]);

	for( cnt = 0; cnt < V_NUM; cnt++ ){

		(nv[cnt].free)( &nv[cnt] );
	}

	for( cnt = 0; cnt < H_NUM; cnt++ ){

		(nh[cnt].free)( &nh[cnt] );
	}
}
*/
