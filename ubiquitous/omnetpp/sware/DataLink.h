#ifndef __DATA_LINK_H
#define __DATA_LINK_H

class DataLink : public cSimpleModule
{
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif
