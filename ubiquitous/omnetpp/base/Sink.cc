

#include <vector>
#include <omnetpp.h>
#include "packet_m.h"
#include "Sink.h"

Define_Module(Sink);

void Sink::initialize()
{
  numReceived = 0;

  WATCH(numReceived);

  hopCountVector.setName("hopCountVector");
  hopCountStats.setName("hopCountStats");
  hopCountStats.setRangeAutoUpper(0,20,1.5);

  pkDelayVector.setName("pkDelayVector");
  pkDelayStats.setName("pkDelayStats");
  // pkDelayStats.setRangeAutoUpper(0,20,1.5);

  pkSizeStats.setName("pkSizeStats");
  // pkSizeStats.setRangeAutoUpper(0,20,1.5);
}

void Sink::handleMessage(cMessage *msg)
{
  // Handle incoming packet
  AppPacket *pk = check_and_cast<AppPacket *>(msg);
  if (ev.isGUI()) parentModule()->bubble("Arrived");
    numReceived++;

  // Display the number of packets received.
  char buf[40];
  sprintf(buf, "rcvd: %ld", numReceived);
  displayString().setTagArg("t", 0, buf);

  //ev << simTime() << " received packet " << pk->name() << " after " << pk->getHopCount() << "hops" << endl;
  //ev << simTime() << " received packet " << pk->name() << " after " << pk->getHopCount() << "hops" << endl;
  pkDelayVector.record(simTime() - pk->timestamp());
  pkDelayStats.collect(simTime() - pk->timestamp());
  pkSizeStats.collect(pk->length());

  delete pk;
}

void Sink::finish()
{
  ev << parentModule()->fullName() << "." << fullName() << ":" << endl;
  ev << "  pks. received: " << numReceived << endl;

  ev << "  hop count, min:    " << hopCountStats.min() << endl;
  ev << "  hop count, max:    " << hopCountStats.max() << endl;
  ev << "  hop count, mean:   " << hopCountStats.mean() << endl;
  ev << "  hop count, stddev: " << hopCountStats.stddev() << endl;

  ev << "  pk. delay, min:    " << pkDelayStats.min() << endl;
  ev << "  pk. delay, max:    " << pkDelayStats.max() << endl;
  ev << "  pk. delay, mean:   " << pkDelayStats.mean() << endl;
  ev << "  pk. delay, stddev: " << pkDelayStats.stddev() << endl;

  ev << "  pk. size, min:    " << pkSizeStats.min() << endl;
  ev << "  pk. size, max:    " << pkSizeStats.max() << endl;
  ev << "  pk. size, mean:   " << pkSizeStats.mean() << endl;
  ev << "  pk. size, stddev: " << pkSizeStats.stddev() << endl;
  ev << " " << endl;

  recordScalar("#received", numReceived);
  hopCountStats.recordScalar("hop count");
  pkDelayStats.recordScalar("pk delay");
  pkSizeStats.recordScalar("pk size");
}

