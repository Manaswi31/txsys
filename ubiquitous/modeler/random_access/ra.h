
/**
 * @author illidan.modeler@gmail.com
 *
 * Dependencies of OPNET Modeler platform:
 * * DES engine
 * * sub queue support
 * * stats recording support
 *
 * */

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

extern double tr_len_ack;

Packet* ra_aloha_ss_dequeue(void);
void ra_aloha_ss_sche_retx(double time_offset);
void ra_aloha_ss_intrpt_self_handler(void);
void ra_aloha_ss_intrpt_strm_handler(void);
void ra_aloha_ss_init(void);
void ra_aloha_ss_intrpt_handler(void);




