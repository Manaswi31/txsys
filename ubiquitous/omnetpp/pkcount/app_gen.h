

#ifndef __APPGEN_H
#define __APPGEN_H

class AppGen : public cSimpleModule
{
  private:
    int pkSize;
    double iaTime;

    cMessage *timeToGenerateAPacket;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif

