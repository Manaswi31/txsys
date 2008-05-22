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
    
    Packet *pk = check_and_cast<Packet *>(msg);
    double txDelay = (double)pk->length()/txRate;

    /*a packet is finished with the txDelay wait duration*/
    if (msg->isSelfMessage()) {
        send(pk , "to_ll");
	return;
    }

  //if this is a packet from the network, forward it to upper layer
  //else set its destAddr field, and send it to the network after a duration of txDelay
   if (pk->arrivalGateId()==gate("from_ll")->id()) {
      send(pk, "to_hl");
  } else {
      pk->setDestAddr(destAddr);
      scheduleAt(simulation.simTime()+txDelay, pk); //modeling the transmission delay, txDelay = pkLen/txRate
  }
}

void HostProc::finish()
{
  ev << parentModule()->fullName() << "." << fullName() << ":" << endl;
}

