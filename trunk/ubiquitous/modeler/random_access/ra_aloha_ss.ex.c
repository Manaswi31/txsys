
#include "ra.h" 
//#include <opnet.h>
extern double tr_len_retx;

struct SS_SVar
{
    int istrm_hl;
    int istrm_ll;
    int ostrm_hl;
    int ostrm_ll;
    Stathandle sh_thru_bits;
    Stathandle sh_load_bits;
//    Evhandle tr_ack;
};

static struct SS_SVar* svptr;

/*
static int istrm_hl;
static int istrm_ll;
static int ostrm_hl;
static int ostrm_ll;
*/

static Packet* buf_pkptr; //the copy of the appending packet that is on the fly

void ra_aloha_ss_init(void)
{
//    FIN(ra_aloha_ss_init());

    /*
     *
     * stream    :  MAC [0] -> rt_0 [0]
     * stream    :  MAC [1] -> sink [0]
     * stream    :  rr_0 [0] -> MAC [0]
     * stream    :  traffic [0] -> MAC [1]
     */
    svptr = (struct SS_SVar*) op_prg_mem_alloc(sizeof (struct SS_SVar));

    svptr->istrm_hl=1;
    svptr->istrm_ll=0;
    svptr->ostrm_hl=1;
    svptr->ostrm_ll=0;

    svptr->sh_load_bits = op_stat_reg("ALOHA SS.Load(bits/sec)", OPC_STAT_INDEX_NONE, OPC_STAT_LOCAL);
    svptr->sh_thru_bits = op_stat_reg("ALOHA SS.Throughput(bits/sec)", OPC_STAT_INDEX_NONE, OPC_STAT_LOCAL);

 //   FOUT;
}

void ra_aloha_ss_intrpt_handler(void)
{
    int intrpt_type;
    //Packet* pkptr;

    FIN(ra_aloha_ss_intrpt_handler());

    intrpt_type = op_intrpt_type();

    switch (intrpt_type)  {
	case OPC_INTRPT_STRM:
	    ra_aloha_ss_intrpt_strm_handler();
	    break;

	case OPC_INTRPT_SELF:
	    ra_aloha_ss_intrpt_self_handler();
	    break;
	default:
	    break;
    }


    FOUT;
}

void ra_aloha_ss_intrpt_strm_handler(void)
{
    Packet* sduptr;
    Packet* pduptr;
    int istrm;
    char pk_fmt_str[64];
    static Boolean wait_ack_flag = OPC_FALSE;
    static Evhandle tr_ack;

    FIN(ra_aloha_ss_intrpt_strm_handler());

    istrm = op_intrpt_strm();

    if (istrm == svptr->istrm_hl) {
	sduptr = op_pk_get(istrm);
	if (wait_ack_flag) {
	    //What will happen if the subq overflows?
	    op_subq_pk_insert(0, sduptr, OPC_QPOS_TAIL);

	    if (op_prg_odb_ltrace_active("aloha")) {
		op_prg_odb_print_major("Queueing a data packet.", OPC_NIL);
	    }

	    FOUT ;
	}
	buf_pkptr = op_pk_copy(sduptr);
	pduptr = op_pk_create_fmt(Ra_Aloha_Data_Pk_Name );

	op_stat_write(svptr->sh_load_bits, op_pk_total_size_get(sduptr));
	op_stat_write(svptr->sh_load_bits, 0.0);

	op_pk_nfd_set_pkt(pduptr, "Data", sduptr);
	op_pk_send(pduptr, svptr->ostrm_ll);

	tr_ack = op_intrpt_schedule_self(Cur_Time + tr_len_ack, TR_ACK_TO);
	wait_ack_flag = OPC_TRUE;

	if (op_prg_odb_ltrace_active("aloha")) {
	    op_prg_odb_print_major("Sending a data packet.", OPC_NIL);
	}
    } else if (istrm == svptr->istrm_ll) {
	pduptr = op_pk_get(istrm);
	op_pk_format(pduptr, pk_fmt_str);

	if (strcmp(pk_fmt_str, Ra_Aloha_Ack_Pk_Name)==0) {

	    wait_ack_flag = OPC_FALSE;
	    op_ev_cancel(tr_ack);
	    //op_ev_cancel(svptr->tr_ack);

	    op_stat_write(svptr->sh_thru_bits, op_pk_total_size_get(pduptr));
	    op_stat_write(svptr->sh_thru_bits, 0.0);

	    op_pk_destroy(buf_pkptr);
	    //TODO: check whether the timer event is valid

	    //the waiting queue is not empty, scheduing next tx
	    if (!op_subq_empty(0)) {
		sduptr = ra_aloha_ss_dequeue();
		buf_pkptr = op_pk_copy(sduptr);
		pduptr = op_pk_create_fmt(Ra_Aloha_Data_Pk_Name );
		op_pk_nfd_set(pduptr, "Data", sduptr);
		op_pk_send(pduptr, svptr->ostrm_ll);
		op_pk_send(pduptr, svptr->ostrm_ll);
		tr_ack = op_intrpt_schedule_self(Cur_Time + tr_len_ack, TR_ACK_TO);
	    }
	}

	op_pk_send(pduptr, svptr->ostrm_hl);
    } //istrm_ll

    FOUT;
}


void ra_aloha_ss_intrpt_self_handler(void)
{
    int evcode;

    FIN(ra_aloha_ss_intrpt_self_handler());

    evcode = op_intrpt_code();

    switch (evcode) {
	case TR_ACK_TO:
	    ra_aloha_ss_sche_retx(tr_len_retx);
	    if (op_prg_odb_ltrace_active("aloha")) {
		op_prg_odb_print_major("Timeout.", OPC_NIL);
	    }
	    break;
	case TR_RETX:
	    op_pk_send(buf_pkptr, svptr->ostrm_ll);
	    break;
	default:
	    break;
    }

    FOUT;
}

void ra_aloha_ss_sche_retx(double time_offset)
{

    static int retx_times = 0;

    FIN(ra_aloha_ss_sche_retx);

    op_intrpt_schedule_self(Cur_Time+time_offset, TR_RETX);
    if (retx_times++ > max_retx_times) {
	errh_print(Err_Cause_Max_Retx_Exceed);
    };


    FOUT;
}



Packet* ra_aloha_ss_dequeue(void)
{
    Packet* pkptr;

    FIN(ra_aloha_ss_dequeue());

    //if (op_subq_empty()) return;
    //
    pkptr = op_subq_pk_remove(0, OPC_QPOS_HEAD);

    FRET (pkptr);
}

void errh_print(enum Err_Cause err_cause)
{
    switch (err_cause) {
	case (Err_Cause_Max_Retx_Exceed) :
	    op_prg_odb_print_major("Max Retransmission times exceeds.", OPC_NIL);
	    break;
	default:
	    break;
    }
}

/*
void ra_aloha_ss_stats_update(Packet* pkptr, )
{
    FIN(ra_aloha_ss_stats_update);


    FOUT;
}
*/

/*
void ra_aloha_ss_debug_trace ()
{
    FIN(ra_aloha_ss_debug_trace );

    FOUT;
}
*/


