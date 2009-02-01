#ifndef __mflood_h__
#define __mflood_h__

#include "mflood-seqtable.h"
#include <sys/types.h>
#include <cmu-trace.h>
#include <priqueue.h>

//#define NOW (Schedule::instance().clock())

#define NETWORK_DIAMETER 16
#define FORWARD_DELAY 0.01
#define NO_DELAY -1.0

class MFlood : public Agent {
    friend class MFlood_RTEntry;
public:
    MFlood(nsaddr_t id);
    void recv(Packet* p, Handler *);
protected:
	int command(int, const char* const*);
	inline int initalized() { return 1 && target_; }
	
	//Route Table Management
	void rt_resolve(Packet* p);
	
	//packet TX routines
	void forward(MFlood_RTEntry * rt, Packet *p, double delay);
	
	nsaddr_t index_;
	
	//Routing Table
	MFlood_RTable rtable_;
	
	Trace* logtarget;
	NsObject* uptarget_;
	NsObject* port_demux_;
	
private:
	u_int32_t myseq_;
    
};
    
    
#endif
