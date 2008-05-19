//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2005 Andras Varga
// Copyright (C) 2005 Ahmet Sekercioglu
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//
// $Id: app_sink.cc,v 1.6 2007/08/31 04:40:07 ahmet Exp $

#include <vector>
#include <omnetpp.h>
#include "packet_m.h"
#include "HostProc.h"

Define_Module(HostProc);

void HostProc::initialize()
{
  
}

void HostProc::handleMessage(cMessage *msg)
{
  // Handle incoming packet
  Packet *pk = check_and_cast<Packet *>(msg);
  //if (ev.isGUI()) parentModule()->bubble("Arrived");

  //HostProc the packets based on their "destination" field
  /*
  if (pk->arrivalGateId()==from_ll) {
      send(pk, "to_hl");
  } else {
      pk->setDestAddr(3);

      send(pk, "to_ll");
  }
  */
  if (pk->arrivalGateId()==gate("from_ll")->id()) {
      send(pk, "to_hl");
  } else {
      pk->setDestAddr(3);

      send(pk, "to_ll");
  }
}

void HostProc::finish()
{
  ev << parentModule()->fullName() << "." << fullName() << ":" << endl;
}

