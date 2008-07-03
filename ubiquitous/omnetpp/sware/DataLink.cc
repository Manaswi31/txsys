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
    int evNum = simulation.eventNumber();
    AppPacket* in;
    if (msg->arrivalGateId()==gate("from_hl")->id()) {
	/*This is a packet from higher layer*/
	pendingPk=check_and_cast <AppPacket*> (msg);
	if (waitAckFlag)
	    appPkQueue.push_back(pendingPk);
	else {
	    AppPacket* copyPk = new AppPacket(*pendingPk);
	    SwareDataPk * swareDataPk = new SwareDataPk(); 
	    swareDataPk->encapsulate(copyPk);
	    send(swareDataPk , "to_ll");
	    waitAckFlag = true;
	    ackWaitTimer= new cMessage();
	    scheduleAt(simulation.simTime()+ackWaitDuration, ackWaitTimer);
	}
    } else if (msg->arrivalGateId()==gate("from_ll")->id()) {
	/* This is a packet from lower layer*/
	if (dynamic_cast<SwareDataPk*>(msg) != NULL) {
	    /*This is a Data packet*/
	    SwareDataPk* inPacket = check_and_cast <SwareDataPk*> (msg);
	    AppPacket* appPk = check_and_cast <AppPacket*> (inPacket->decapsulate());
	    send(appPk, "to_hl");
	    delete inPacket;

	    /*Reply with an ACK*/
	    SwareAck *ackPacket = new SwareAck(); 
	    send(ackPacket, "to_ll");
	} else {
	    /* This is an ACK*/
	    SwareAck* ack = check_and_cast <SwareAck*> (msg);
	    delete ack;
	    if (ackWaitTimer) {
		cancelAndDelete(ackWaitTimer);
		if (pendingPk)
		    delete pendingPk;
	    }
	    if (!appPkQueue.empty()) {
		AppPacket* outPacket = appPkQueue.front();
	        appPkQueue.pop_front();
		send(outPacket, "to_ll");
	    }
	}
    }
    else if (msg->isSelfMessage()) {
	/*ACK timeout*/
	SwareDataPk * swareDataPk = new SwareDataPk(); 
	swareDataPk->encapsulate(pendingPk);
	send(swareDataPk , "to_ll");
	ackWaitTimer= new cMessage();
	scheduleAt(simulation.simTime()+ackWaitDuration, ackWaitTimer);

    }
}

void DataLink::handleHlMessage(cMessage & msg)
{
}

void DataLink::finish()
{
}
