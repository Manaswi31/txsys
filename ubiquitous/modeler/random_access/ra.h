
/**
 * @author illidan.modeler@gmail.com
 * dependencies of OPNET Modeler platform:
 * DES engine
 * sub queue support
 * */

#define Cur_Time op_sim_time()

typedef enum
{
    TR_NEXT_TX = 1
    , TR_ACK_TO
} TIMER_TYPE;

#define Ra_Aloha_Ack_Pk_Name "ra_aloha_ack"

extern double tr_len_ack;

Packet* ra_aloha_ue_dequeue(void);
void ra_aloha_ue_sche_retx(double time_offset);
void ra_aloha_ue_intrpt_self_handler(void);
void ra_aloha_ue_intrpt_strm_handler(void);
void ra_aloha_ue_init(void);
void ra_aloha_ue_intrpt_handler(void);




