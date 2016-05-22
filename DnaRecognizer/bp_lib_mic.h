/******************************************************************************/
/*                                                                            */
/* Title  : Library of Neural Network by Backpropagation algorism             */
/* Program Name : bp_lib_mic.h                                                */
/*                                                                            */
/* Detail : Library of a backpropagation algorism for neural network for mic  */
/* Date   : 2015.12.02                                                        */
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

#ifndef _BP_LIB_MIC_H_DEFINED

					// Constant for sigmoid function
#define ETA 0.01
					// Learning rate
#define THETA 0.0000001
					// Stabilizer
#define PERSISTENT_T 1
#define EPSILON 0.0000001

#define BUFFSIZE 1024000

#define PRECISION_A pow(10,+9)
#define PRECISION_B pow(10,-9)

#define NON_RESET       0
#define RESET           1


__declspec( target(mic) ) int calc_forward(
        NEURON_P **np,
        long phase,
        long in_num,
        long out_num
);

__declspec( target(mic) ) int calc_delta_of_out(
        NEURON_P **np,
        long phase,
        long out_num,
        double *teach
);

__declspec( target(mic) ) int calc_delta(
        NEURON_P **np,
        long phase,
        long in_num,
        long out_num
);

__declspec( target(mic) ) int calc_delta_w(
        NEURON_P **np,
        long phase,
        long in_num,
        long out_num
);

__declspec( target(mic) ) int init_bp(
        NEURON_P *np,
        long wb_num,
        long wf_num,
        int reset_flg
);

__declspec( target(mic) ) int learn_bp(
        NEURON_P **np,
        long phase_num,
        double *t
);

#define _BP_LIB_MIC_H_DEFINED
#endif

