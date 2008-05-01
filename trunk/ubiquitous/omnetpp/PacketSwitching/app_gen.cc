//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2005 Andras Varga
// Copyright (C) 2005-2007 Ahmet Sekercioglu
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//
// $Id: app_gen.cc,v 1.7 2007/08/31 04:40:07 ahmet Exp $";

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
  
  const char *destAddressesPar = par("destAddresses");
  cStringTokenizer tokenizer(destAddressesPar);
  const char *token;
  while ((token = tokenizer.nextToken()) != NULL) {
    destAddresses.push_back(atoi(token));
  }
  
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

  pkSize = par("pkSize");

  // Choose a destination.
  int destAddress = destAddresses[intuniform(0, destAddresses.size()-1)];
  
  // Display the number of packets sent.
  char buf[40];
  sprintf(buf, "sent: %ld", numSent);
  displayString().setTagArg("t", 0, buf);

  // Prepare a packet.
  // Application layer does not know the node address yet (hence -1)
  char pkname[40];
  sprintf(pkname,"pk-(%d)-to-%d-#%ld", -1, destAddress, numSent);
  ev << simTime() << " generating a packet " << pkname << endl;
  Packet *pk = new Packet(pkname);
  pk->setSrcAddr(-1); // Application does not know the source address.
  pk->setDestAddr(destAddress);
  pk->setLength(pkSize);
  pk->setTimestamp();
  send(pk,"out");
  
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

