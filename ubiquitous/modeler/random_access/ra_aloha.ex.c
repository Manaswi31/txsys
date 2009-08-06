
void ra_aloha_ue_intrpt_handler()
{
    int intrpt_type;
    Packet* pkptr;

    FIN(ra_aloha_ue_intrpt_handler());

    intrpt_type = op_intrpt_type();

    switch (intrpt_type)  {
	case OPC_INTRPT_STRM:
	    ra_aloha_ue_intrpt_strm_handler();
	    break;

	case OPC_INTRPT_SELF:
	    ra_aloha_ue_intrpt_self_handler();
	    break;
	default:
	    break;
    }


    pkptr = op_pk_get(op_intrpt_strm());


    FOUT;
}

void ra_aloha_ue_intrpt_strm_handler(void)
{
    Packet* pkptr;
    int istrm_hl;
    int istrm_ll;
    int ostrm_hl;
    int ostrm_ll;
    int istrm;

    FIN(ra_aloha_ue_intrpt_strm_handler());

    istrm = op_intrpt_strm();
    pkptr = op_pk_get(istrm);

    if (istrm == istrm_hl) {
	op_pk_send(pkptr, ostrm_ll);

    } else if (istrm == istrm_ll) {
    }





    FOUT;

}

void ra_aloha_sche_tx(double time_offset, Packet* pkptr)
{
    FIN(ra_aloha_sche_tx());

    op_intrpt_schedule_self(current_time+time_offset, T_NEXT_TX);


    FOUT;
}



