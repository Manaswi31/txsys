
#include <vector>
#include <omnetpp.h>
#include "packet_m.h"
#include "SwitchProc.h"

Define_Module(SwitchProc);

void SwitchProc::initialize()
{
  
}

void SwitchProc::handleMessage(cMessage *msg)
{
  // Handle incoming packet
  int dest;
  Packet *pk = check_and_cast<Packet *>(msg);
  if (ev.isGUI()) parentModule()->bubble("Arrived");

  //SwitchProc the packets based on their "destination" field
  dest = pk->getDestAddr(); 
  send(pk, "out", dest);

  delete pk;
}

void SwitchProc::finish()
{
  ev << parentModule()->fullName() << "." << fullName() << ":" << endl;
}

