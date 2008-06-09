#include <omnetpp.h>
#include <DataLink.h>

void DataLink::initialize()
{
}

void DataLink::handleMessage(cMessage *msg)
{
    if (msg->arrivalGateID()==gate("from_hl")->id())
}
