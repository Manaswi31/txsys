#include "flood.h"

static int g_rid = 0;

FloodRTEntry::FloodRTEntry()
{
    for (int i = 0; i<MaxSeqNum; i++) 
	rtSeqNum[i] = 0xffffffff;
}

FloodRTEntry::FloodRTEntry(Rid src, seq_t seq)
    : _sRid(src), 
    maxSeqNum_(seq), 
    minSeqNum_(0) ,
    seq_it (0)
{
    rtSeqNum[0]=seq;
    for (int i=0; i<MaxSeqNum; i++) rtSeqNum[i] = 0xffffffff;

}

bool FloodRTEntry::isNewSeq(seq_t seq)
{
    if (seq > maxSeqNum_) return true;
    else if (seq < minSeqNum_) return false;
    for (int i=0; i<MaxSeqNum; i++) {
	if (seq==rtSeqNum[i]) return false;
    }
    return true;
}


void FloodRTEntry::addSeq(seq_t seq)
{
    rtSeqNum[seq_it] = seq;
    seq_it++;
    if (seq < minSeqNum_) return; /*This is a past seq_num, ignore it*/
    else if (seq > maxSeqNum_) maxSeqNum_ = seq;
}

Rid FloodRTEntry::getSRid() {
    return _sRid;
}

//////////////////////////////////////////////////////////
//class FloodRTable
//////////////////////////////////////////////////////////

bool FloodRTable::rtLookUp(Rid id)
{
    std::list<FloodRTEntry>::iterator it ;
    for (it= rTable.begin(); it!=rTable.end();it++) {
	if (it->getSRid()==id) break;
    }
    return (it!=rTable.end() ? true : false);
}

void FloodRTable::rtInsert(Rid rid, seq_t seq)
{
    FloodRTEntryIter it;
    //FloodRTEntry * entry = new FloodRTEntry(rid, seq);
    FloodRTEntry entry(rid, seq);
    for (it=rTable.begin(); it!=rTable.end(); it++) {
	if (it->getSRid() < rid) {
	}

	rTable.insert(it, entry);
    }
}

void FloodRTable::rtDelete(Rid id)
{
    FloodRTEntryIter it ;
    for (it = rTable.begin(); it!=rTable.end(); it++) {
	if (id==it->getSRid()) {rTable.erase(it); break;}
    }

    /*
    if (rt != rTable.end()) {
	rTable.erase(rt);
    }
    */
}

//////////////////////////////////////////////////////////
//class FloodRte
//////////////////////////////////////////////////////////

FloodRte::FloodRte() : _seq(0)
{ 
	//void rtLookUp();
    llIstrm = 0;
    hlIstrm = 1;
    llOstrm = 0;
    hlIstrm = 1;
    _rtable = new FloodRTable();
    _rid = g_rid++;

}


void FloodRte::init()
{
}

void FloodRte::procHLPk(Packet* hlpk)
{
    Packet* pk;
    Flood_Rte_Hdr *hdr;

    hdr = (Flood_Rte_Hdr* )op_prg_mem_alloc (sizeof (Flood_Rte_Hdr));
    hdr->seq = _seq++;
    hdr->saddr = _rid;
    hdr->daddr = (_rid+1) % g_rid;
    if (hdr->daddr==0) hdr->daddr = g_rid;

    pk = op_pk_create(Flood_Pk_Hdr_Size );
    op_pk_fd_set_ptr(pk, Flood_Rte_Fd_Ind_Header, hdr, 0, op_prg_mem_copy_create, op_prg_mem_free, sizeof (Flood_Rte_Hdr ));
    op_pk_fd_set_pkt(pk, Flood_Rte_Fd_Ind_Payload, hlpk, -1);
    op_pk_send(pk, llOstrm);
}

void FloodRte::procLLPk(Packet* pk)
{
    Packet* hlpk;
    Flood_Rte_Hdr *hdr;
    FloodRTEntryIter entry_it ;
    //FloodRTEntry * entry;

    op_pk_fd_get_ptr(pk, Flood_Rte_Fd_Ind_Header, (void**)&hdr);
    op_pk_fd_get_pkt(pk,Flood_Rte_Fd_Ind_Payload, & hlpk);

    //this is a route loop
    if (hdr->saddr==_rid) {
	op_pk_destroy(hlpk);
	op_pk_destroy(pk);
	FOUT;
    }

    //this packet is destined to me
    if (hdr->daddr==_rid) {
	op_pk_destroy(pk);
	op_pk_send(hlpk, hlOstrm);
	FOUT;
    }

    //to forward the packet
    if (!(_rtable->rtLookUp(hdr->saddr))) {
	//I receive packet from this node for the first time, create an entry for it.
	//entry = new FloodRTEntry(hdr->saddr, hdr->seq);
	_rtable->rtInsert(hdr->saddr, hdr->seq);
	op_pk_send(pk, llOstrm);
    } else if (entry_it->isNewSeq(hdr->seq)) {
	//This isn't the first time, but this is a new seq. Update my table then.
	entry_it->addSeq(hdr->seq);
	op_pk_send(pk, llOstrm);
    } else {
	//this is a past packet
	op_pk_destroy(pk);
	op_pk_destroy(hlpk);
    }
    FOUT;
}

void FloodRte::handleMessage()
{
    Packet* pk;
    if (op_intrpt_strm()==hlIstrm) {
	pk = op_pk_get(hlIstrm);
	procHLPk(pk);
    } else if (op_intrpt_strm()==llIstrm) {
	pk = op_pk_get(llIstrm);
	procLLPk(pk);
    }
}

TransNet::TransNet(Byte L1addr, Byte L2addr, Byte L3addr, Byte L4addr)  
{
    _addr.L1Addr=L1addr; 
    _addr.L2Addr=L2addr; 
    _addr.L3Addr=L3addr; 
    _addr.L4Addr=L4addr;
}

void TransNet::procHLPk(Packet* hlpk)
{
    Packet* pk;
    TransNetHdr * hdr;
    pk = op_pk_create(TransNetPkHdrSize);
    hdr = new TransNetHdr;
    hdr->addr.L1Addr = _addr.L1Addr;
    hdr->addr.L2Addr = _addr.L2Addr;
    hdr->addr.L3Addr = _addr.L3Addr;
    hdr->addr.L4Addr = _addr.L4Addr;

    op_pk_fd_set_ptr(pk, Flood_TransNet_Fd_Ind_Hdr, hdr, 0, op_prg_mem_copy_create, op_prg_mem_free, sizeof (TransNetHdr ));
    op_pk_fd_set_pkt(pk, Flood_TransNet_Fd_Ind_Payload , hlpk, -1);

    op_pk_send(pk, llOstrm);
}

void TransNet::procLLPk(Packet* pk)
{
    Packet* hlpk;
    op_pk_fd_get_pkt(pk, Flood_TransNet_Fd_Ind_Payload, & hlpk);
    op_pk_destroy(pk);
    op_pk_send(hlpk, hlOstrm);
}

void TransNet::handleMessage()
{
    Packet* pk;
    if (op_intrpt_strm()==hlIstrm) {
	pk = op_pk_get(hlIstrm);
	procHLPk(pk);
    } else if (op_intrpt_strm()==llIstrm) {
	pk = op_pk_get(llIstrm);
	procLLPk(pk);
    }
}

//EOF

