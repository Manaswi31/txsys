#include <omnetpp.h>
#include "DataLink.h"
#include "packet_m.h"

Define_Module(DataLink);

void DataLink::initialize()
{
    ackWaitDuration = 5.0; /*ACK wait timeout duration*/
    waitAckFlag = false;
    debugFlag = true;
    ackWaitTimer = NULL;

    qLenOV.setName("Queue length");
}

void DataLink::handleMessage(cMessage *msg)
{
    int evNum = simulation.eventNumber();
    AppPacket* in;
    if (msg->arrivalGateId()==gate("from_hl")->id()) {
	/*This is a packet from higher layer*/
	pendingPk=check_and_cast <AppPacket*> (msg);
	if (waitAckFlag) {
	    appPkQueue.push_back(pendingPk);
	    pendingPk = NULL;
	    qLenOV.record(appPkQueue.size());
	} else {
	    /*Encapulate app packets and send it down*/
	    AppPacket* copyPk = new AppPacket(*pendingPk);
	    SwareDataPk * swareDataPk = new SwareDataPk(); 
	    swareDataPk->encapsulate(copyPk);
	    send(swareDataPk , "to_ll");

	    /*Set ACK timer and flag*/
	    waitAckFlag = true;
	    ackWaitTimer= new cMessage("ackWaitTimer");
	    scheduleAt(simulation.simTime()+ackWaitDuration, ackWaitTimer);
	}
    } else if (msg->arrivalGateId()==gate("from_ll")->id()) {
	/* This is a packet from lower layer*/
	if (dynamic_cast<SwareDataPk*>(msg) != NULL) {
	    /*This is a Data packet*/
	    SwareDataPk* inPacket = check_and_cast <SwareDataPk*> (msg);
	    cMessage * payload = inPacket->decapsulate();
	    AppPacket* appPk = check_and_cast <AppPacket*> (payload);
	    //AppPacket* appPk = (AppPacket*) (payload);
	    //thrpOutVector.record(appPk->length());
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
		/*Cancel ACK timer and flag*/
		cancelAndDelete(ackWaitTimer);
		waitAckFlag = false;

		if (pendingPk)
		    delete pendingPk;
	    }
	    if (!appPkQueue.empty()) {
		AppPacket* appPacket = appPkQueue.front();
	        appPkQueue.pop_front();
		qLenOV.record(appPkQueue.size());
		SwareDataPk* swareDataPk = new SwareDataPk();
		swareDataPk->encapsulate(appPacket);
		send(swareDataPk , "to_ll");

		waitAckFlag = true;
		ackWaitTimer = new cMessage("ackWaitTimer");
		scheduleAt(simulation.simTime() + ackWaitDuration, ackWaitTimer);
	    }
	}
    }
    else if (msg->isSelfMessage()) {
	/*ACK timeout*/
	if (debugFlag) {
	    ev << "ACK Timeout" << endl;
	}
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
