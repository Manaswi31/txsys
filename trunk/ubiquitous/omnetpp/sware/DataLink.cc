#include <omnetpp.h>
#include "DataLink.h"
#include "packet_m.h"

void DataLink::initialize()
{
    ackWaitDuration = 5.0;
    waitAckFlag = false;
    ackWaitTimer = NULL;
   // appPkQueue
}

void DataLink::handleMessage(cMessage *msg)
{
    AppPacket * inPk=check_and_cast <AppPacket*> (msg);
    if (msg->arrivalGateId()==gate("from_hl")->id()) {
	/*This is a packet from higher layer*/
	if (waitAckFlag)
	    appPkQueue.push_back(inPk);
	else {
	    AppPacket* copyPk = pendingPk;
	    send(copyPk , "to_ll");
	    ackWaitTimer= new cMessage();
	    scheduleAt(simulation.simTime()+ackWaitDuration, ackWaitTimer);
	}
    } else if (msg->arrivalGateId()==gate("from_ll")->id()) {
	/* This is an ACK*/
	delete ackWaitTimer;
    }
}

void DataLink::finish()
{
}
