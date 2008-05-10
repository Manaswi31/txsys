
#ifndef __Switch_H
#define __Switch_H

class Switch : public cSimpleModule
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

