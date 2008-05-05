#include <vector>
#include <omnetpp.h>
#include "packet_m.h"
#include "app_sink.h"

Define_Module(AppSink);

void AppSink::initialize()
{
  numReceived = 0;
  
  WATCH(numReceived);


  pkReceivedVector.setName("Received packet number:");
}

void AppSink::handleMessage(cMessage *msg)
{
  // Handle incoming packet
  Packet *pk = check_and_cast<Packet *>(msg);
  if (ev.isGUI()) parentModule()->bubble("Arrived");
  numReceived++;

  // Display the number of packets received.
  char buf[40];
  sprintf(buf, "rcvd: %ld", numReceived);
  displayString().setTagArg("t", 0, buf);
  pkReceivedVector.record(numReceived);

  delete pk;
}

void AppSink::finish()
{
  ev << parentModule()->fullName() << "." << fullName() << ":" << endl;
  ev << "  pks. received: " << numReceived << endl;
  ev << " " << endl;
}

