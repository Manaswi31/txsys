#ifndef __DATA_LINK_H
#define __DATA_LINK_H

#include <deque>
#include "packet_m.h"

class DataLink : public cSimpleModule
{
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
private:
    std::deque <AppPacket*> appPkQueue;
    bool waitAckFlag;
    cMessage * ackWaitTimer;
    AppPacket* pendingPk;
    double ackWaitDuration;
};

#endif
