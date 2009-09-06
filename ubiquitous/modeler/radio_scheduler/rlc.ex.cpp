#include "common.h"

using namespace txsys;
void RLCProc::initialize()
{
    rlcEntity = new RLCEntity();
    rlcEntity->initialize(this);
}

void RLCProc::handelStrmIntrpt()
{
    Packet* pkptr;
    int istrm;

    istrm = op_intrpt_strm();
    pkptr = op_pk_get(istrm);

    if (istrm==iStrmHL) {
	handleHLPk(pkptr);
    } else if (istrm==iStrmLL) {
	handleLLPk(pkptr);
    }

}

void RLCProc::handleHLPk(Packet* SDU)
{
    rlcEntity->handleHLPk(SDU);
}

void RLCProc::handleLLPk(Packet* PDU)
{
    rlcEntity->handleLLPk(PDU);
}

void RLCProc::handelMessage()
{
    int intrptType;

    intrptType=op_intrpt_type();

    switch (intrptType) {
    case OPC_INTRPT_STRM:
	handelStrmIntrpt();
	break;
    }
}

//class RLCEntity

void RLCEntity::initialize(int oStrmLL_, int oStrmHL_);
{
    oStrmLL = oStrmLL_;
    oStrmHL = oStrmHL_;
    seqNumber = 0;
}

void RLCEntity::handleLLPk(Packet* PDU)
{
    Packet* SDU;

    /**/
    op_pk_nfd_get_pk(PDU, "PU", &SDU);
    //op_pk_nfd_get_ptr(PDU, "Status", &status);
    op_pk_send(SDU, oStrmHL);
}


void RLCEntity::handleHLPk(Packet* SDU)
{
    Packet* pduPkptr;

    pduPkptr = op_pk_creat_fmt("rlc");
    op_pk_nfd_set_pkt(pduPkptr, "PU", SDU);
    //op_pk
    
}





