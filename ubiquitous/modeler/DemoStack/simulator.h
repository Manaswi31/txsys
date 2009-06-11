//#include ""
#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__
namespace Simulator
{
    class Module
    {
	public: 
	    virtual void send(Packet*);
    };
};


#endif
