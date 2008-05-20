
#ifndef __HostProc_H
#define __HostProc_H

class HostProc : public cSimpleModule
{
  private:
    // Statistics
    long numForwarded;
    int destAddr;
    double txRate;

   protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif

