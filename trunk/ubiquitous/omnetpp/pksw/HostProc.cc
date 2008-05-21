#include <vector>
#include <omnetpp.h>
#include "packet_m.h"
#include "HostProc.h"

Define_Module(HostProc);

void HostProc::initialize()
{
    destAddr = par("destAddr");
    txRate = par("txRate");
}

void HostProc::handleMessage(cMessage *msg)
{
    int index_ = index();
    cMessage* event;
    Packet* pk2send ;
    if (msg->isSelfMessage()) {
	ev << index() << "sending a packet" << endl;
	pk2send = &( pkQueue.front()); 
	if (pk2send==NULL) {
	    ev << "pk2send NULL" << endl;
	}
	pkQueue.pop_front();
        send(pk2send , "to_ll");
	return;
    }
    Packet *pk = check_and_cast<Packet *>(msg);
    double txDelay = (double)pk->length()/txRate;
  // Handle incoming packet


  //if this is a packet from the network, forward it to upper layer
  //else set its destAddr field and send it to the network
   if (pk->arrivalGateId()==gate("from_ll")->id()) {
      send(pk, "to_hl");
  } else {
      pk->setDestAddr(destAddr);
      event = new cMessage();
      scheduleAt(simulation.simTime()+txDelay, event ); //modeling the transmission delay, txDelay = pkLen/txRate
	pkQueue.push_back(*pk);
  }
}

void HostProc::finish()
{
  ev << parentModule()->fullName() << "." << fullName() << ":" << endl;
}

