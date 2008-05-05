#ifndef __APPSINK_H
#define __APPSINK_H

class AppSink : public cSimpleModule
{
  private:
    // Statistics
    long numReceived;
    cOutVector pkReceivedVector;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif

