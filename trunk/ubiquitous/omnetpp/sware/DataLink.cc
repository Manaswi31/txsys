#include <omnetpp.h>
#include "DataLink.h"

void DataLink::initialize()
{
    ackWaitDuration = 5.0;
    waitAckFlag = false;
   // appPkQueue
}

void DataLink::handleMessage(cMessage *msg)
{
    if (msg->arrivalGateId()==gate("from_hl")->id()) {
	/*This is a packet from higher layer*/
	if (waitAckFlag)
	    appPkQueue.push_back(msg);
	else {
	    pendingPk=check_and_cast <AppPacket*> msg;
	    Packet* copyPk = pendingPk;
	    send(copyPk , "to_ll");
	    cMessage ackWaitTimer = new cMessage();
	    scheduleAt(simulation.simTime()+ackWaitDuration, ackWaitTimer);
	}
    } else if (msg->arrivalGateID()==gate("from_ll")->id()) {
	delete ackWaitTimer;
    }
}
