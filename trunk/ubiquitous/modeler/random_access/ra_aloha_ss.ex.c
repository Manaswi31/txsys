
static int istrm_hl;
static int istrm_ll;
static int ostrm_hl;
static int ostrm_ll;

void ra_aloha_ss_init(void)
{
    FIN(ra_aloha_ss_init());

    FOUT;
}

void ra_aloha_ss_intrpt_handler(void)
{
    int intrpt_type;
    Packet* pkptr;

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
    Packet* pkptr;
    int istrm;
    char pk_fmt_str[64];
    static Boolean wait_ack_flag = OPC_FALSE;
    static Packet* buf_pkptr;
    static evhandle tr_ack;

    FIN(ra_aloha_ss_intrpt_strm_handler());

    istrm = op_intrpt_strm();
    pkptr = op_pk_get(istrm);

    if (istrm == istrm_hl) {
	if (wait_ack_flag) {
	    op_subq_insert(0, OPC_SUBQ_POS_HEAD);
	    return ;
	}
	buf_pkptr = op_pk_copy(pkptr);
	op_pk_send(pkptr, ostrm_ll);
	tr_ack = op_intrpt_schedule_self(Cur_Time + tr_len_ack, TR_ACK_TO);

    } else if (istrm == istrm_ll) {
	op_pk_format(pkptr, pk_fmt_str);

	if (strcmp(pk_fmt_str, Ra_Aloha_Ack_Pk_Name)==0) {
	    op_pk_destroy(buf_pkptr);
	    //TODO: check whether the timer event is valid
	    op_ev_cancel(tr_ack);

	    //the waiting queue is not empty, scheduing next tx
	    if (!op_subq_empty()) {
		pkptr = ra_aloha_ss_dequeue();
		buf_pkptr = op_pk_copy(pkptr);
		op_pk_send(pkptr, ostrm_ll);
		tr_ack = op_intrpt_schedule_self(Cur_Time + tr_len_ack, TR_ACK_TO);
	    }
	}
	op_pk_send(pkptr, ostrm_hl);

    }

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
	    break;
	case TR_RETX:
	    op_pk_send(buf_pkptr, ostrm_ll);
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
    pkptr = op_subq_dequeue(0);

    FRET (pkptr);
}

/*
void ra_aloha_sche_tx(double time_offset, Packet* pkptr)
{
    FIN(ra_aloha_sche_tx());

    op_intrpt_schedule_self(current_time+time_offset, T_NEXT_TX);


    FOUT;
}
*/

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

void ra_aloha_ss_stats_update(Packet* pkptr)
{
}



