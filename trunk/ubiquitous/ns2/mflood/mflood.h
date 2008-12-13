#ifndef __mflood_h__
#define __mflood_h__

#include <sys/types.h>
#include <cmu-trace.h>
#include <priqueue.h>
#include <wireless-mcast/mprflood-seqtable.h>

#define NOW (Schedule::instance().clock())

#define NETWORK_DIAMETER 30
#define NO_DELAY -1.0

class MFlood : public Agent {
    friend class MFlood_RTEntry;
    public MFlood(nsaddr_t id);
    void recv(Packet* p, Handler *);

