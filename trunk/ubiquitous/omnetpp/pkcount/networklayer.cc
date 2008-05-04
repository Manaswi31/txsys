//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2005 Andras Varga
// Copyright (C) 2005 Ahmet Sekercioglu
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//
// $Id: networklayer.cc,v 1.7 2007/08/31 04:59:40 ahmet Exp $

#include <map>
#include <omnetpp.h>
#include "packet_m.h"


class NetworkLayer : public cSimpleModule
{
  private:
    int myAddress;
    bool router;

    typedef std::map<int,int> RoutingTable; // destaddr --> port
    RoutingTable rtable;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    void initializeRoutingTable();
};

Define_Module(NetworkLayer);

void NetworkLayer::initialize()
{
  myAddress = parentModule()->par("address");

  WATCH(myAddress);

  // Am I part of a router or not?
  if (strcmp("router", parentModule()->name()) == 0) {
    router = true;
  } else {
    router = false;
  }

  initializeRoutingTable();
}

void NetworkLayer::handleMessage(cMessage *msg)
{
  Packet *pk = check_and_cast<Packet *>(msg);
  int destAddr = pk->getDestAddr();
  
  if (destAddr == myAddress) {
    if (router) { // Routers don't have an application layer.
      ev << "Packet discarded: " << pk->name() << endl;
      delete pk;
    } else {
      ev << "Delivery of packet to higher layer: " << pk->name() << endl;
      send(pk,"localOut");
    }
    return;
  }
  
  RoutingTable::iterator it = rtable.find(destAddr);

  if (it == rtable.end()) {
    ev << "Address " << destAddr << " unreachable, discarding packet " << pk->name() << endl;
    delete pk;
    return;
  }

  if (pk->getSrcAddr() == -1) {
    // Application layer has forwarded this packet to the network layer.
    char pkname[40];
    sprintf(pkname,"pk-%d-to-%d", myAddress, pk->getDestAddr());
    pk->setSrcAddr(myAddress); 
    pk->setName(pkname);
  } 
  int outGateId = (*it).second;
  ev << simTime() << " Forwarding packet " << pk->name() << " on gate id = " << outGateId << endl;
  pk->setHopCount(pk->getHopCount()+1);
  send(pk, outGateId);
}

void NetworkLayer::initializeRoutingTable() 
{
  // We use OMNeT++'s built-in Dijkstra shortest path algorithm implementation
  // on the network topology graph. 
  cTopology *topo = new cTopology("topo");
  
  // Extract the topology. We are only interested in hosts and routers.
  topo->extractByModuleType("Host", "Router", NULL);

  ev << parentModule()->fullName() << " (addr = " << myAddress << "): cTopology found " << topo->nodes() << " nodes\n";
  
  // Let's find the representation of the compound module 
  // containing this networklayer module in the topology
  // (it is either a router or a host)
  cTopology::Node *thisNode = topo->nodeFor(parentModule());
  
  // find and store next hops
  for (int i = 0; i < topo->nodes(); i++) {
    if (topo->node(i) == thisNode) continue; // skip ourselves

    // Find shortest paths from all nodes to the target node `topo->node(i)'
    // (i.e. run Dijkstra, result will be stored in the cTopology object).
    topo->unweightedSingleShortestPathsTo(topo->node(i)); 
    
    if (thisNode->paths() == 0) continue; // This node is not connected to
                                          // any other node.

    // thisNode->path(0) is the cTopology link from this node to
    // the next node along the lowest cost route which takes us to 
    // the target node `topo->node(i)'.
    // We will, first, find the "out" gate of our host/router linked to 
    // this path.
    cGate *parentModuleGate = thisNode->path(0)->localGate();
    // Find which server is connected to this gate.
    cModule *serverModule = parentModuleGate->fromGate()->ownerModule();
    // And the queue connected to this server
    cModule *outputQueueModule = serverModule->gate("in")->fromGate()->ownerModule();
    // And then find which gate of us (we are networklayer module) 
    // connects to this queue.
    // We will forward all packets (addressed to the target node) to this gate.
    int gateId = outputQueueModule->gate("in")->fromGate()->id();
    
    // What was the address of the target node?
    int address = topo->node(i)->module()->par("address");

    // Update the routing table: address --> gateId
    rtable[address] = gateId;
    ev << "  towards address " << address << " gateId is " << gateId << endl;
  }
  ev << " " << endl;
  delete topo;
}

void NetworkLayer::finish()
{
  RoutingTable::iterator it;

  int dest_address = (*it).first;
  int outGateId = (*it).second;

  ev << parentModule()->fullName() << " final routing table:" << endl;
  ev << "  destination\tnext hop" << endl;
  ev << "    address" << endl;
  ev << "  -----------\t--------" << endl;
  for(it = rtable.begin(); it != rtable.end(); it++) {
    dest_address = (*it).first;
    outGateId = (*it).second; 
    // (Keep network diagram close-by if you get confused about the following
    // information, observing the connections on the diagram will help.)
    // We will now follow the path to find the nextHopModule.
    // 
    // OutGateId is the ID of the local gate connected to the
    // outputQueueModule.  serverModule services the
    // outputQueueModule.  serverModule is connected to the gate
    // connected to the nextHopModule towards the destination node
    // module.
    cGate *outGate = gate(outGateId);
    cModule *outputQueueModule = outGate->toGate()->ownerModule();
    cModule *serverModule = outputQueueModule->gate("out")->toGate()->ownerModule();
    cGate *parentModuleGate = serverModule->gate("out")->toGate();
    cModule *nextHopModule = parentModuleGate->toGate()->ownerModule();
    ev << "       " << dest_address << "\t" << nextHopModule->fullName() << endl;
  }
  ev << " " << endl;

}

// TODO
// for "release quality" code, one should check if eg. the queue's "in" gate
// is actually connected,that is, fromGate() is not a NULL pointer.
// otherwise it may crash if the router is assembled incorrectly
