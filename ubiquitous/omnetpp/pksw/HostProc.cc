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
#include "Switch.h"

Define_Module(Switch);

void Switch::initialize()
{
  
}

void Switch::handleMessage(cMessage *msg)
{
  // Handle incoming packet
  Packet *pk = check_and_cast<Packet *>(msg);
  if (ev.isGUI()) parentModule()->bubble("Arrived");

  //Switch the packets based on their "destination" field

  delete pk;
}

void Switch::finish()
{
  ev << parentModule()->fullName() << "." << fullName() << ":" << endl;
}

