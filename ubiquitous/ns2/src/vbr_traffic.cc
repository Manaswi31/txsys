/* -*-	Mode:C++; c-basic-offset:8; tab-width:8; indent-tabs-mode:t -*- */


#include "random.h"
#include "trafgen.h"
#include "ranvar.h"
//#include <math>
#include <iostream>
using namespace std;

//type of random distribution
 enum vbrIntvlDistr
 {
     CBR_INTVL_UNIFORM = 1,
     CBR_INTVL_NORMAL,
     CBR_INTVL_EXPO
 };

class VBR_Traffic : public TrafficGenerator {
 public:
	VBR_Traffic();
	virtual double next_interval(int&);
	//HACK so that udp agent knows interpacket arrival time within a burst
	inline double interval() { return (interval_); }
 protected:
	virtual void start();
	void init();
	double rate_;     /* send rate during on time (bps) */
	double interval_; /* packet inter-arrival time during burst (sec) */
	int random_; //type of random distribution
	int seqno_;
	int maxpkts_;
	double para1_; //expectation of the random interval; in case of unifrom distribution, it's the lower bound
	double para2_; //variance of the random interval; in case of unifrom distribution, it's the upper bound
	int verbose;
};


static class VBRTrafficClass : public TclClass {
 public:
	VBRTrafficClass() : TclClass("Application/Traffic/VBR") {}
	TclObject* create(int, const char*const*) {
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
	if (agent_)
		if (agent_->get_pkttype() != PT_TCP &&
 		    agent_->get_pkttype() != PT_TFRC)
			agent_->set_pkttype(PT_CBR);
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
	switch (random_)
	{
	    case CBR_INTVL_UNIFORM :
	    {
		t = Random::uniform(para1_, para2_);

		//for debug
		if (verbose >=2 )
		    cout << "Generating uniform distribution." << endl;

	        break;
	    }
	    case CBR_INTVL_NORMAL :
	    {
		t = Random::normal(para1_, para2_);

		//for debug
		if (verbose >= 2)
		{
		    cout << "normal output: " << t << endl;
		}
		else if (verbose >= 1)
		    cout << "Generating normal distribution." << endl;

	        break;
	    }
	    case CBR_INTVL_EXPO :
	    {
		t = Random::exponential(para1_);

		//for debug
		if (verbose >= 2)
		{
		    cout << "exponential output: " << t << endl;
		}
		else if (verbose >= 1)
		    cout << "Generating exponential distribution." << endl;

	        break;
	    }
	    default :
	    ;
	}
	size = size_;
	if (++seqno_ < maxpkts_)
	{
	    if (verbose >=2 )
		cout << "Returning random interval" << endl;
		return(t);
	}
	else
		return(-1);
}

/*
 * Copyright (c) Xerox Corporation 1997. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Linking this file statically or dynamically with other modules is making
 * a combined work based on this file.  Thus, the terms and conditions of
 * the GNU General Public License cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of this file
 * give you permission to combine this file with free software programs or
 * libraries that are released under the GNU LGPL and with code included in
 * the standard release of ns-2 under the Apache 2.0 license or under
 * otherwise-compatible licenses with advertising requirements (or modified
 * versions of such code, with unchanged license).  You may copy and
 * distribute such a system following the terms of the GNU GPL for this
 * file and the licenses of the other code concerned, provided that you
 * include the source code of that other code when and as the GNU GPL
 * requires distribution of source code.
 *
 * Note that people who make modified versions of this file are not
 * obligated to grant this special exception for their modified versions;
 * it is their choice whether to do so.  The GNU General Public License
 * gives permission to release a modified version without this exception;
 * this exception also makes it possible to release a modified version
 * which carries forward this exception.
 */
