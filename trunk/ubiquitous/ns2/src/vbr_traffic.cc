/* -*-	Mode:C++; c-basic-offset:8; tab-width:8; indent-tabs-mode:t -*- */


#include "random.h"
#include "trafgen.h"
#include "ranvar.h"
#include <iostream>
using namespace std;

//type of random distribution
 enum vbrIntvlDistr
 {
     VBR_INTVL_UNIFORM = 1,
     VBR_INTVL_NORMAL,
     VBR_INTVL_EXPO
 };

class VBR_Traffic : public TrafficGenerator 
{
 public:
	VBR_Traffic();
	virtual double next_interval(int&);
	//HACK so that udp agent knows interpacket arrival time within a burst
	inline double interval() { return (interval_); }
 protected:
	virtual void start();
	void init();
	double rate_;     /* send rate(bps) during ON duration  */
	double interval_; /* packet inter-arrival time(sec) during burst  */
	int random_; //type of random distribution
	int seqno_;
	int maxpkts_;
	double para1_; //expectation of the random interval; in case of unifrom distribution, it's the lower bound
	double para2_; //variance of the random interval; in case of unifrom distribution, it's the upper bound
	int verbose;
};


static class VBRTrafficClass : public TclClass 
{
 public:
	VBRTrafficClass() : TclClass("Application/Traffic/VBR") {}
	TclObject* create(int, const char*const*) 
	{
		return (new VBR_Traffic());
	}
} class_vbr_traffic;

VBR_Traffic::VBR_Traffic() : seqno_(0)
{
	bind_bw("rate_", &rate_);
	bind("random_", &random_);
	bind("packetSize_", &size_);
	bind("maxpkts_", &maxpkts_);
	bind("para1_",  &para1_);
	bind("para2_", &para2_);
	bind("verbose", &verbose);
}

void VBR_Traffic::init()
{
        // compute inter-packet interval
	interval_ = (double)(size_ << 3)/(double)rate_;
	if (agent_) {
		if (agent_->get_pkttype() != PT_TCP &&
 		    agent_->get_pkttype() != PT_TFRC)
			agent_->set_pkttype(PT_VBR);
	}
}

void VBR_Traffic::start()
{
        init();
        running_ = 1;
        timeout();
}

double VBR_Traffic::next_interval(int& size)
{
	//interval_ = (double)(size_ << 3)/(double)rate_;
	double t = interval_;
	switch (random_) {
	    case VBR_INTVL_UNIFORM : {
		t = Random::uniform(para1_, para2_);

		//for debug
		if (verbose >=2 )
		    cout << "Generating uniform distribution." << endl;

	        break;
	    } case VBR_INTVL_NORMAL : {
		t = Random::normal(para1_, para2_);

		//for debug
		if (verbose >= 2)
		{
		    cout << "normal output: " << t << endl;
		}
		else if (verbose >= 1)
		    cout << "Generating normal distribution." << endl;

	        break;
	    } case VBR_INTVL_EXPO : {
		t = Random::exponential(para1_);

		//for debug
		if (verbose >= 2) {
		    cout << "exponential output: " << t << endl;
		} else if (verbose >= 1)
		    cout << "Generating exponential distribution." << endl;
	        break;
	    }
	    default :
	    ;
	} //switch case

	size = size_;
	if (++seqno_ < maxpkts_) {
	    if (verbose >=2 )
		cout << "Returning random interval" << endl;
	    return(t);
	}
	else return(-1);
}

