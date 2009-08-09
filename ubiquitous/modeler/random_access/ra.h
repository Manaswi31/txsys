
/**
 * @author illidan.modeler@gmail.com
 *
 * Dependencies of OPNET Modeler platform:
 * * DES engine
 * * Sub queue support : op_pk_subq_...
 * * Stats recording support : op_stat_...
 * * Tracing support : FIN, FOUT, FRET
 *
 * */

#ifndef __RA_H__
#define __RA_H__

#include <opnet.h>
#include <stdio.h>
#include <string.h>

#define Cur_Time op_sim_time()

typedef enum
{
    TR_NEXT_TX = 1
    , TR_ACK_TO //Timeout
    , TR_RETX
} TIMER_TYPE;

enum Err_Cause {
    Err_Cause_Max_Retx_Exceed
} ;

#define Ra_Aloha_Ack_Pk_Name "ra_aloha_ack"
#define Ra_Aloha_Data_Pk_Name "ra_aloha_data"

extern double tr_len_ack;
extern double tr_len_retx;
extern int max_retx_times;

Packet* ra_aloha_ss_dequeue(void);
void ra_aloha_ss_sche_retx(double time_offset);
void ra_aloha_ss_intrpt_self_handler(void);
void ra_aloha_ss_intrpt_strm_handler(void);
void ra_aloha_ss_init(void);
void ra_aloha_ss_intrpt_handler(void);
void errh_print(enum Err_Cause err_cause);

void ra_aloha_bs_intrpt_strm_handler(void);

#endif


