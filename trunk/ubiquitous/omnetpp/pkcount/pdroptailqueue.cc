//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2005 Andras Varga
// Copyright (C) 2005-2007 Ahmet Sekercioglu
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//
// $Id: pdroptailqueue.cc,v 1.2 2007/08/31 04:40:07 ahmet Exp $


#include <omnetpp.h>
#include "packet_m.h"
#include "pdroptailqueue.h"

// Passive droptail queue: It does not include a built-in server, a server
// needs to be connected to its output, and only sends a packet to the server if
// the server requests it. 
Define_Module(PDropTailQueue);

PDropTailQueue::~PDropTailQueue()
{
  // Discard the remaining events (if any exists).
}

void PDropTailQueue::initialize()
{
  pkCapacity = par("pkCapacity");
  pkQueue.setName("packet_queue");
  numDiscardedPks = 0;
  qLength = pkQueue.length();
 
  WATCH(qLength);
  WATCH(numDiscardedPks);

  qLengthVector.setName("qLengthVector");
  qLengthStats.setName("qLengthStats");
  qLengthStats.setRangeAutoUpper(0,20,1.5);
}

void PDropTailQueue::handleMessage(cMessage *msg)
{
  // A packet has arrived.
  if (msg->length() == 0) {
    // 0 length packets cause problems since they take 0 seconds to transmit.
    error("Received packet has 0 length.");
    ev << "Discarded the 0 length packet: " << msg->name() << endl;
    delete msg;
    numDiscardedPks++;
  }
  qLength = pkQueue.length();
  if (qLength < pkCapacity) {
    pkQueue.insert(msg);
    if (serverIdle) { 
      // Server previously has requested a packet but we haven't sent one
      // (we didn't have any packets to send). We can send it now.
      msg = (Packet *) pkQueue.pop();
      send(msg,"out");
      serverIdle = false;
    }
  } else {
    ev << "Queue overflow, packet discarded: " << msg->name() << endl;
    delete msg;
    numDiscardedPks++;
  }
  qLengthStats.collect(qLength);
  qLengthVector.record(qLength);
}

void PDropTailQueue::request()
{
    Enter_Method("request()");

    if (!pkQueue.empty()) {
      cMessage *msg = (cMessage *) pkQueue.pop();
      send(msg,"out");
      serverIdle = false;
    } else {
      serverIdle = true; // Server is idle but queue does not have any packets to send.
    }
    //    if (ev.isGUI()) displayString().setTagArg("i",1, queue.empty() ? "" : "cyan");
}

void PDropTailQueue::finish()
{
  ev << parentModule()->fullName() << "." << fullName() << ":" << endl;
  ev << "  queue length, min:    " << qLengthStats.min() << endl;
  ev << "  queue length, max:    " << qLengthStats.max() << endl;
  ev << "  queue length, mean:   " << qLengthStats.mean() << endl;
  ev << "  queue length, stddev: " << qLengthStats.stddev() << endl;
  ev << " " << endl;
  
  qLengthStats.recordScalar("queue length");
  recordScalar("#discardedPks", numDiscardedPks);
}

