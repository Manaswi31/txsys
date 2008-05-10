
#ifndef __SwitchProc_H
#define __SwitchProc_H

class SwitchProc : public cSimpleModule
{
  private:
    // Statistics
    long numForwarded;

   protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif

