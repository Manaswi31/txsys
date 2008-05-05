#include <vector>
#include <omnetpp.h>
#include "packet_m.h"
#include "app_gen.h"


// Generates traffic for the network.
Define_Module(AppGen);

void AppGen::initialize()
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

void AppGen::handleMessage(cMessage *msg)
{
  // Time to create and send a packet. 
  if (ev.isGUI()) parentModule()->bubble("Sending a packet");
      numSent++;

  // Display the number of packets sent.
  char buf[40];
  sprintf(buf, "sent: %ld", numSent);
  displayString().setTagArg("t", 0, buf);

  // Prepare a packet.
  // Application layer does not know the node address yet (hence -1)
  char pkname[40];
  Packet *pk = new Packet();
  send(pk,"out_strm");
  
  // Schedule an event for sending the next packet.
  iaTime = par("iaTime");
  scheduleAt(simTime()+iaTime, timeToGenerateAPacket);
}

void AppGen::finish()
{
  ev << parentModule()->fullName() << "." << fullName() << ":" << endl;
  ev << "  pks. sent:     " << numSent << endl;
  ev << " " << endl;

  recordScalar("#sent", numSent);
}

