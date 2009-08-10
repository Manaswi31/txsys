#include "ra.h"

struct BS_SVar
{
    int istrm_hl;
    int istrm_ll;
    int ostrm_hl;
    int ostrm_ll;
}; 

static struct BS_SVar * svptr;

/*
static int istrm_hl;
static int istrm_ll;
static int ostrm_hl;
static int ostrm_ll;
*/

void ra_aloha_bs_init(void)
{
    FIN(ra_aloha_bs_init());

    svptr = (struct BS_SVar*) op_prg_mem_alloc(sizeof (struct BS_SVar));
    svptr->istrm_ll=0;
    svptr->ostrm_hl=1;
    svptr->ostrm_ll=0;

    FOUT;
}

void ra_aloha_bs_intrpt_handler(void)
{
    int intrpt_type;
    //Packet* pkptr;

    FIN(ra_aloha_bs_intrpt_handler());

    intrpt_type = op_intrpt_type();

    switch (intrpt_type)  {
	case OPC_INTRPT_STRM:
	    ra_aloha_bs_intrpt_strm_handler();
	    break;
	    /*
	case OPC_INTRPT_SELF:
	    ra_aloha_bs_intrpt_self_handler();
	    break;
	    */
	default:
	    break;
    }


    FOUT;
}

void ra_aloha_bs_intrpt_strm_handler(void)
{
    Packet* pduptr;
    Packet * sduptr;
    Packet* ack_pduptr;
    int istrm;
    int ss_id;
    char pk_fmt_str[64];

    FIN(ra_aloha_bs_intrpt_strm_handler());

    istrm = op_intrpt_strm();
    pduptr = op_pk_get(istrm);

    if (istrm == svptr->istrm_ll) {
	op_pk_format(pduptr, pk_fmt_str);
	if (strcmp(pk_fmt_str, Ra_Aloha_Data_Pk_Name)==0) {
	    op_pk_nfd_get_int32(pduptr, "SS ID", & ss_id);
	    op_pk_nfd_get_pkt(pduptr, "Data", & sduptr);
	    op_pk_send(sduptr , svptr->ostrm_hl);
	    ack_pduptr = op_pk_create_fmt(Ra_Aloha_Ack_Pk_Name);
	    op_pk_nfd_set_int32(ack_pduptr, "SS ID", ss_id);
	    op_pk_send(ack_pduptr , svptr->ostrm_ll);

	    if (op_prg_odb_ltrace_active("aloha")) {
		op_prg_odb_print_major("Sending an ACK.", OPC_NIL);
	    }

	} else {
	    op_pk_destroy(pduptr);
	}
    }

    FOUT;
}

