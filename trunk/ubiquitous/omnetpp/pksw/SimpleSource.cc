// $Id: app_gen.cc,v 1.7 2007/08/31 04:40:07 ahmet Exp $";

#include <vector>
#include <omnetpp.h>
#include "packet_m.h"
#include "SimpleSource.h"


// Generates traffic for the network.
Define_Module(SimpleSource);

void SimpleSource::initialize()
{
  numSent = 0;
  
  WATCH(pkSize);
  WATCH(iaTime);
  WATCH(numSent);

   // Schedule an event for sending the first packet.
  timeToGenerateAPacket = new cMessage("timeToGenerateAPacket");
  iaTime = par("iaTime");
  scheduleAt(iaTime, timeToGenerateAPacket);
}

void SimpleSource::handleMessage(cMessage *msg)
{
  // Time to create and send a packet. 
  if (ev.isGUI()) parentModule()->bubble("Sending a packet");
  numSent++;

  pkSize = par("pkSize");
  
  // Display the number of packets sent.
  char buf[40];
  sprintf(buf, "sent: %ld", numSent);
  displayString().setTagArg("t", 0, buf);

  // Prepare a packet.
  // Application layer does not know the node address yet (hence -1)
  /*
  char pkname[40];
  sprintf(pkname,"pk-(%d)-to-%d-#%ld", -1, destAddress, numSent);
  ev << simTime() << " generating a packet " << pkname << endl;
  Packet *pk = new Packet(pkname);
  */
  Packet *pk = new Packet();
  pk->setLength(pkSize);
  pk->setTimestamp();
  send(pk,"out");
  
  // Schedule an event for sending the next packet.
  iaTime = par("iaTime");
  scheduleAt(simTime()+iaTime, timeToGenerateAPacket);
}

void SimpleSource::finish()
{
  ev << parentModule()->fullName() << "." << fullName() << ":" << endl;
  ev << "  pks. sent:     " << numSent << endl;
  ev << " " << endl;

  recordScalar("#sent", numSent);
}

