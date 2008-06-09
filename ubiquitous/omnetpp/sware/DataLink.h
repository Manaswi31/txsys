#ifndef __DATA_LINK_H
#define __DATA_LINK_H

#include <deque>

class DataLink : public cSimpleModule
{
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
private:
    std::deque <> ;
};

#endif
