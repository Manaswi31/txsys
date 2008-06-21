#include <omnetpp.h>
#include "DataLink.h"
#include "packet_m.h"

Define_Module(DataLink);

void DataLink::initialize()
{
    ackWaitDuration = 5.0; /*ACK wait timeout duration*/
    waitAckFlag = false;
    ackWaitTimer = NULL;
}

void DataLink::handleMessage(cMessage *msg)
{
    AppPacket* in;
    if (msg->arrivalGateId()==gate("from_hl")->id()) {
	/*This is a packet from higher layer*/
	pendingPk=check_and_cast <AppPacket*> (msg);
	if (waitAckFlag)
	    appPkQueue.push_back(pendingPk);
	else {
	    AppPacket* copyPk = new AppPacket(*pendingPk);
	    send(copyPk , "to_ll");
	    ackWaitTimer= new cMessage();
	    scheduleAt(simulation.simTime()+ackWaitDuration, ackWaitTimer);
	}
    } else if (msg->arrivalGateId()==gate("from_ll")->id()) {
	/* This is a packet from lower layer*/
	if (dynamic_cast<AppPacket*>(msg) != NULL) {
	    SwareDataPk* inPacket = check_and_cast <SwareDataPk*> (msg);
	    send(inPacket, "to_hl");
	    SwareAck *ackPacket = new SwareAck(); 
	    send(ackPacket, "to_ll");
	} else {
	    /* This is an ACK*/
	    if (ackWaitTimer) 
		cancelAndDelete(ackWaitTimer);
	    if (!appPkQueue.empty()) {
		AppPacket* outPacket = appPkQueue.front();
	        appPkQueue.pop_front();
		send(outPacket, "to_ll");
	    }
	}
    }
}

void DataLink::handleHlMessage(cMessage & msg)
{
}

void DataLink::finish()
{
}
