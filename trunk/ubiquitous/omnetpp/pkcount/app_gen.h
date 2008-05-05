

#ifndef __APPGEN_H
#define __APPGEN_H

class AppGen : public cSimpleModule
{
  private:
    int pkSize;
    double iaTime;

    // Statistics
    long numSent;

    std::vector<int> destAddresses;
    cMessage *timeToGenerateAPacket;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif

