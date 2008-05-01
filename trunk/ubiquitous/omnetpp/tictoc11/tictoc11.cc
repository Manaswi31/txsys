#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "tictoc11_m.h"

class Txc11:public cSimpleModule
{
    private:
	long numSent;
	long numReceived;
    protected:
	virtual TicTocMsg11 *generateMessage();
	virtual void forwardMessage(TicTocMsg11 * msg);
	virtual void updateDisplay();

	virtual void initialize();
	virtual void handleMessage(cMessage * msg);
};

Define_Module(Txc11);

void Txc11::initialize()
{
    numSent = 0;
    numReceived = 0;
    WATCH(numSent);
    WATCH(numReceived);

    if (index()==0) {
	TicTocMsg11 *msg = generateMessage();
	scheduleAt(0.0, msg);
    }
}

void Txc11::handleMessage(cMessage * msg)
{
    TicTocMsg11 * ttmsg = check_and_cast<TicTocMsg11*> (msg);
    if (ttmsg->getDestination()==index()) {
	int hopcount = ttmsg->getHopCount();
	ev << "Message" << ttmsg << "arrived after" <<< hopcount <<"hops.\n";
	numReceived++;
	bubbule("ARRIVED, starting new one!");

	ev << "Generating another message:";
	TicTocMsg11 * newmsg = generateMessage();
	ev << newmsg << endl;
	forwardMessage(newmsg);

	if (ev.GUI())
	    updateDisplay();
    }
    else {
	forwardMessage(ttmsg);
    }
}

TicTocMsg11 *Txc11::generateMessage()
{
    // Produce source and destination addresses.
    int src = index();   // our module index
    int n = size();      // module vector size
    int dest = intuniform(0,n-2);
    if (dest>=src) dest++;

    char msgname[20];
    sprintf(msgname, "tic-%d-to-%d", src, dest);

    // Create message object and set source and destination field.
    TicTocMsg11 *msg = new TicTocMsg11(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

void Txc11::forwardMessage(TicTocMsg11 *msg)
{
    // Increment hop count.
    msg->setHopCount(msg->getHopCount()+1);

    // Same routing as before: random gate.
    int n = gate("out")->size();
    int k = intuniform(0,n-1);

    ev << "Forwarding message " << msg << " on port out[" << k << "]\n";
    send(msg, "out", k);
}

void Txc11::updateDisplay()
{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    displayString().setTagArg("t",0,buf);
}


