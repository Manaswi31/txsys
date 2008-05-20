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
    cMessage* event;
    if (msg->isSelfMessage()) {
        send(pk, "to_ll");
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
  }
}

void HostProc::finish()
{
  ev << parentModule()->fullName() << "." << fullName() << ":" << endl;
}
