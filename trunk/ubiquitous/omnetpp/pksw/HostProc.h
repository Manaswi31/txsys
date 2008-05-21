
#ifndef __HostProc_H
#define __HostProc_H

#include "packet_m.h"
#include <deque>

class HostProc : public cSimpleModule
{
  private:
    // Statistics
    long numForwarded;
    int destAddr;
    double txRate;
    std::deque<Packet> pkQueue; 

   protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif

