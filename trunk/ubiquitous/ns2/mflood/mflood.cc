/**
 * mflood.cc
 */


#include "mflood.h"
#include "mflood-packet.h"
#include <random.h>
#include <cmu-trace.h>
#include <iostream>

int hdr_mflood::offset_;

static class MFloodHeaderClass : public PacketHeaderClass {
    public:
	MFloodHeaderClass() : PacketHeaderClass("PacketHeader/MFlood", sizeof (hdr_mflood)) {
	    bind_offset(&hdr_mflood::offset_);
	}
}class_mfloodhdr;


static class MFloodclass: public TclClass {
    public :
	MFloodclass() : TclClass ("Agent/MFlood") {}
	TclObject * create(int argc, const char* const* argv) {
		std::cout<<"*********running**************"<<std::endl;
	    assert(argc==5);
	    return (new MFlood((nsaddr_t) atoi(argv[4])));
	}
}class_rtProtocolMFlood;

int MFlood::command(int argc, const char* const* argv) {
	
	printf("Go!\n");
	
	
    Tcl & tcl = Tcl::instance();
    if (argc==2) {
	if (strncasecmp(argv[1], "id", 2) == 0) {
	    tcl.resultf("%d", index_);
	    return TCL_OK;
	} else if (strcmp(argv[1], "uptarget")==0) {
	    if (uptarget_ !=0)
		tcl.result(uptarget_->name());
	    return (TCL_OK);
	}
    } else if (argc == 3) {
	if (strcmp(argv[1], "index_") == 0) {
	    index_ = atoi(argv[2]);
	    return TCL_OK;
	} else if (strcmp(argv[1], "log-target") == 0 || strcmp(argv[1], "tracetarget") == 0) {
	    logtarget = (Trace *) TclObject::lookup(argv[2]);
	    if (logtarget == 0) return TCL_ERROR;
	    return TCL_OK;
	} else if (strcmp(argv[1], "uptarget")==0) {
	    if (*argv[2]=='\0') {
		target_ = 0;
		return TCL_OK;
	    }
	    uptarget_ = (NsObject*) TclObject::lookup(argv[2]);
	    if (uptarget_ == 0) {
		tcl.resultf("no such object %s", argv[2]);
		return TCL_ERROR;
	    }
	    return TCL_OK;
	} else if (strcmp(argv[1], "port-dmux")==0) {
		TclObject * obj;
		port_demux_ = (NsObject*) obj;
		return TCL_OK;
	}
    }
    return Agent::command(argc, argv);

} //command()

MFlood::MFlood(nsaddr_t id) : Agent(PT_MFLOOD), port_demux_(NULL) {
	index_ = id;
	logtarget = 0;
	myseq_ = 0;
}


void MFlood::rt_resolve(Packet *p) {
	struct hdr_cmn * ch = HDR_CMN(p);
	struct hdr_ip * ih = HDR_IP(p);
	struct hdr_mflood * fh = HDR_MFLOOD_PKT(p);
	MFlood_RTEntry * rt;

	if (rt==NULL) {
		rt = new MFlood_RTEntry(ih->saddr(), fh->seq_);
		LIST_INSERT_HEAD(&rtable_.rthead, rt, rt_link);
		forward(rt, p, FORWARD_DELAY);
	} else if (rt->isNewSeq(fh->seq_)) {
		forward(rt, p, FORWARD_DELAY);
		rt->addSeq(fh->seq_);
	} else {
		drop(p, "LOWSEQ");
	}
}

void MFlood::recv(Packet* p, Handler*) {
	struct hdr_cmn *ch = HDR_CMN(p);
	struct hdr_ip *ih = HDR_IP(p);
	struct hdr_mflood *fh = HDR_MFLOOD_PKT(p);
	assert(initialized());

	if ((ih->saddr()==index_) && (ch->num_forwards()==0)) {
		ch->size() += IP_HDR_LEN;
		ih->ttl_ = NETWORK_DIAMETER;
		fh->seq_ = myseq_++;
		forward((MFlood_RTEntry*)1, p, 0);
		return;
	} else if (ih->saddr()==index_) {
		drop(p, DROP_RTR_ROUTE_LOOP);
		return;
	} else if (ih->saddr() != index_) {
		if (--ih->ttl_==0) {
			drop(p, DROP_RTR_TTL);
			return;
		}
	}
	rt_resolve(p);
}


void MFlood::forward(MFlood_RTEntry* rt, Packet *p, double delay) {
	struct hdr_cmn *ch = HDR_CMN(p);
	struct hdr_ip *ih = HDR_IP(p);
	assert(ih->ttl_>0);
	assert(rt != 0);
	ch->next_hop_ = -1; /*Broadcast address*/
	ch->addr_type() = NS_AF_INET;
	ch->direction() = hdr_cmn::DOWN;
	if (delay>0.0) {
		Scheduler::instance().schedule(target_, p, Random::uniform(delay*2));
	} else {
		Scheduler::instance().schedule(target_, p, 0);
	}
} //forward


