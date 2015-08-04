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
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

#include "neuron.h"

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
/* Title  : Free memory                                                       */
/* Function Name : alloc_neuron                                               */
/*                                                                            */
/* Detail : Free memory                                                       */
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
/* Title  : Create Neurons                                                    */
/* Function Name : create_neuron                                              */
/*                                                                            */
/* Detail : create synapse                                                    */
/* Date   : 2015/05/28                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long num   : Number of Neuron                                     */
/*          long links : Number of links for other neurons                    */
/*                                                                            */
/* Output : Terminte Normal : Pointer of neuron , Error : NULL                */
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
		(n[cnt].init)( n, links );
	}
						/* Return neuron pointer      */
	return n;
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
/* Input  : long num   : Number of Neuron                                     */
/*          long links : Number of links for other neurons                    */
/*                                                                            */
/* Output : Terminte Normal : Pointer of neuron , Error : NULL                */
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
	}

	for( j = 0; j < j_num; j++ ){
						/* Set weit for back          */
		nj[j].wb = w;
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
