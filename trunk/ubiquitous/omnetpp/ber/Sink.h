

#ifndef __Sink_H
#define __Sink_H

class Sink : public cSimpleModule
{
  private:
    // Statistics
    long numReceived;
    long numErrorPk;
    cLongHistogram hopCountStats;
    cOutVector hopCountVector;
    cDoubleHistogram pkDelayStats;
    cDoubleHistogram perStats;
    cOutVector pkDelayVector;
    cLongHistogram pkSizeStats;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif

