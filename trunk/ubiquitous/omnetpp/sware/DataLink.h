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
    virtual void handleHlMessage(cMessage & msg);
private:
    std::deque <AppPacket*> appPkQueue;
    bool waitAckFlag;
    bool debugFlag;
    cMessage * ackWaitTimer;
    AppPacket* pendingPk;
    double ackWaitDuration;
    cOutVector qLenOV;
    cOutVector loadOutVector;
    cOutVector thrpOutVector;
};

#endif
