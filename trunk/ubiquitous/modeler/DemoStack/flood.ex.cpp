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

FloodRTable::FloodRTable()
{
}

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
//class Routing
//////////////////////////////////////////////////////////
Routing::Routing()
{
}

void Routing::initialize()
{
    L3IfData* ifdata;
	int temp;

    /*Receiving remote interrupt from TransNet and do the initialize */

    FIN(Routing::initialize());

    /*transnet delivers the address infomation to routing module*/
    /*extracts the event state and read in the data*/
    ifdata = (L3IfData*) op_ev_state(op_ev_current());
    //_rid = ifdata->addr.L3Address;

	/*
    _modData = (Rte_Module_Data*)op_prg_mem_alloc(sizeof (Rte_Module_Data));
    _modData->rid = (int) ifdata->addr.L3Addr;
	*/
    
    /* I hereby confirm that local variable(in the stack, instead of dynamic memory that is in heap) */
    /* can also be installed as module memory, */
    /* and be extracted intact later by calling op_pro_mod_mem_acess() */
    _modData.rid = (int) ifdata->addr.L3Addr;
    op_pro_modmem_install((void*) &_modData);
    //op_pro_modmem_install((void*)_modData);

    /*Currently only supports flood_rte*/
    rte_prohndl = op_pro_create("flood_rte", OPC_NIL);
    op_pro_invoke(rte_prohndl, OPC_NIL);


    FOUT;
}

//////////////////////////////////////////////////////////
//class FloodRte
//////////////////////////////////////////////////////////

FloodRte::FloodRte()
{ 
    /*
stream    :  routing [0] -> transnet [0]
stream    :  routing [1] -> rt_0 [0]
stream    :  transnet [0] -> routing [0]
stream    :  rr_0 [0] -> routing [1]
    */
    
	//void rtLookUp();
}


void FloodRte::initialize()
{   

    Rte_Module_Data* modData;

    FIN(FloodRte::initialize());

    _seq = 0;

    llIstrm = 1;
    hlIstrm = 0;
    llOstrm = 1;
    hlOstrm = 0;
    _rtable = new FloodRTable();

    modData = (Rte_Module_Data*) op_pro_modmem_access ();
    _rid = modData->rid;

    op_intrpt_type_register (OPC_INTRPT_STRM, op_pro_self());

    FOUT;
}

void FloodRte::procHLPk(Packet* hlpk)
{
    Packet* pk;
    Flood_Rte_Hdr *hdr;
    TransNet::TransNetHdr* tran_hdr;

    FIN(FloodRte::procHLPk());

    /*extract dest address from the fields from transnet header*/

    hdr = (Flood_Rte_Hdr* )op_prg_mem_alloc (sizeof (Flood_Rte_Hdr));
    hdr->seq = _seq++;
    hdr->saddr = _rid;
    op_pk_fd_access_read_only_ptr(hlpk, TransNet::Flood_TransNet_Fd_Ind_Hdr , (const void**) & tran_hdr);
    hdr->daddr = tran_hdr->addr.L3Addr;
    //hdr->daddr = (_rid+1) % g_rid;
    //if (hdr->daddr==0) hdr->daddr = g_rid;

    pk = op_pk_create(Flood_Pk_Hdr_Size );
    op_pk_fd_set_ptr(pk, Flood_Rte_Fd_Ind_Header, hdr, 0, op_prg_mem_copy_create, op_prg_mem_free, sizeof (Flood_Rte_Hdr ));
    op_pk_fd_set_pkt(pk, Flood_Rte_Fd_Ind_Payload, hlpk, -1);
    op_pk_send(pk, llOstrm);

    FOUT;
}

void FloodRte::procLLPk(Packet* pk)
{
    Packet* hlpk;
    Flood_Rte_Hdr *hdr;
    FloodRTEntryIter entry_it ;
    //FloodRTEntry * entry;

    FIN(FloodRte::procLLPk());

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

	/*Encapsulate the fields back into the packet, and send it out again*/
	op_pk_fd_set_ptr(pk, Flood_Rte_Fd_Ind_Header, hdr, \
		0, op_prg_mem_copy_create, op_prg_mem_free, sizeof (Flood_Rte_Hdr ));

	/*If the specified size of a packet field is set to a negative value,*/
	/* the size of the field will be set to the size of the encapsulated packet, */
	/*thus accurately modeling the aggregate packet size.*/
	op_pk_fd_set_pkt(pk, Flood_Rte_Fd_Ind_Payload, hlpk, -1);

	op_pk_send(pk, llOstrm);
    } else if (entry_it->isNewSeq(hdr->seq)) {
	//This isn't the first time, but this is a new seq. Update my table then.
	entry_it->addSeq(hdr->seq);

	/*Encapsulate the fields back into the packet, and send it out again*/
	op_pk_fd_set_ptr(pk, Flood_Rte_Fd_Ind_Header, hdr, \
		0, op_prg_mem_copy_create, op_prg_mem_free, sizeof (Flood_Rte_Hdr ));

	/*If the specified size of a packet field is set to a negative value,*/
	/* the size of the field will be set to the size of the encapsulated packet, */
	/*thus accurately modeling the aggregate packet size.*/
	op_pk_fd_set_pkt(pk, Flood_Rte_Fd_Ind_Payload, hlpk, -1);

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

    FIN(FloodRte::handleMessage());

    if (op_intrpt_strm()==hlIstrm) {
	pk = op_pk_get(hlIstrm);
	procHLPk(pk);
    } else if (op_intrpt_strm()==llIstrm) {
	pk = op_pk_get(llIstrm);
	procLLPk(pk);
    }

    FOUT;
}

//////////////////////////////////////////////////////////
//class TransNet
//////////////////////////////////////////////////////////

TransNet::TransNet()
{
}

TransNet::TransNet(Byte L1addr, Byte L2addr, Byte L3addr, Byte L4addr)  
{
    /*
    stream    :  transnet [0] -> routing [0]
     stream    :  transnet [1] -> traffic [0]
     stream    :  routing [0] -> transnet [0]
     stream    :  traffic [0] -> transnet [1]
     */
    llOstrm = 0;
    hlOstrm = 1;
    llIstrm = 0;
    hlIstrm = 1;
    _addr.L1Addr=L1addr; 
    _addr.L2Addr=L2addr; 
    _addr.L3Addr=L3addr; 
    _addr.L4Addr=L4addr;
}

void TransNet::initialize()
{
    Objid node_objid ;
    Objid addr_comp_objid;
    Objid dest_addr_comp_objid;
    Objid temp_objid;

    FIN(TransNet::initialize());

    llOstrm = 0;
    hlOstrm = 1;
    llIstrm = 0;
    hlIstrm = 1;
 
    _objid = op_id_self();
    node_objid = op_topo_parent(_objid);
    op_ima_obj_attr_get_objid(_objid, "Address", & addr_comp_objid);
    //op_ima_obj_attr_get_objid(_objid, "TransNet.Address", & addr_comp_objid);

    temp_objid = op_topo_child(addr_comp_objid, OPC_OBJTYPE_GENERIC, 0);
    op_ima_obj_attr_get_int32(temp_objid, "L1Address", (int*) & (_addr.L1Addr));
    op_ima_obj_attr_get_int32(temp_objid , "L2Address", (int*)& (_addr.L2Addr));
    op_ima_obj_attr_get_int32(temp_objid , "L3Address", (int*)& (_addr.L3Addr));
    op_ima_obj_attr_get_int32(temp_objid , "L4Address", (int*)& (_addr.L4Addr));

    /*send a remote interrupt to Routing, which will do initialization after receiving this signal*/
    _rte_objid = op_id_from_name(node_objid, OPC_OBJTYPE_PROC, "routing");
    
    L3IfData *ifdata;
    ifdata = new L3IfData;
    ifdata->addr.L1Addr = _addr.L1Addr;
    ifdata->addr.L2Addr = _addr.L2Addr;
    ifdata->addr.L3Addr = _addr.L3Addr;
    op_ev_state_install(ifdata, OPC_NIL);
    op_intrpt_schedule_remote(op_sim_time(), 0, _rte_objid);
    op_ev_state_install(OPC_NIL, OPC_NIL);

    sh_load = op_stat_reg("TransNet.Load (bytes/sec)", OPC_STAT_INDEX_NONE, OPC_STAT_LOCAL);
    sh_traf_sent =  op_stat_reg("TransNet.Traffic Sent (bytes/sec)", OPC_STAT_INDEX_NONE, OPC_STAT_LOCAL);

    FOUT;
}

void TransNet::procHLPk(Packet* hlpk)
{
    Packet* pk;
    TransNetHdr * hdr;

    Packet *pkptr;

    FIN(procHLPk(hlpk));

    pk = op_pk_create(TransNetPkHdrSize);
    hdr = new TransNetHdr;
    hdr->addr.L1Addr = _addr.L1Addr;
    hdr->addr.L2Addr = _addr.L2Addr;
    hdr->addr.L3Addr = _addr.L3Addr;
    hdr->addr.L4Addr = _addr.L4Addr;

    op_pk_fd_set_ptr(pk, Flood_TransNet_Fd_Ind_Hdr, hdr, 0, op_prg_mem_copy_create, op_prg_mem_free, sizeof (TransNetHdr ));
    op_pk_fd_set_pkt(pk, Flood_TransNet_Fd_Ind_Payload , hlpk, -1);

    //op_pk_fd_get_pkt(pk, Flood_TransNet_Fd_Ind_Payload, & pkptr);
    op_stat_write(sh_load, op_pk_total_size_get(hlpk));
    op_stat_write(sh_load, 0.0);
    op_stat_write(sh_traf_sent, op_pk_total_size_get(pk));
    op_stat_write(sh_traf_sent, 0.0);

    op_pk_send(pk, llOstrm);

    FOUT;
}

void TransNet::procLLPk(Packet* pk)
{
    Packet* hlpk;

    FIN(procLLPk(pk));

    op_pk_fd_get_pkt(pk, Flood_TransNet_Fd_Ind_Payload, & hlpk);
    op_pk_destroy(pk);
    op_pk_send(hlpk, hlOstrm);

    FOUT;
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

