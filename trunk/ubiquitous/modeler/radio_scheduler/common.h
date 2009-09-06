/**
 * common.h
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include <assert.h>
#include <list>
#include <opnet.h>
#include <oms_dist_support.h>

//#define std::queue <Packet*> 

namespace txsys
{

    static const int INFINITY_ =  0xff;
    static const int MaxSeqNum = 1000;

    /*public data structures*/
    struct RLCStatusPDU
    {
	int seqNumber;
    };

    
   class SimpleProcess 
   {
       protected:
	   virtual void initialize() = 0;
	   virtual void handleMessage()=0;
	   virtual void finalize() = 0;
   };

   //class RLCEntity;
   class RLCProc : public SimpleProcess
   {
       //friend class RLCEntity
       public:
	   virtual void initialize();
	   virtual void handleMessage();
	   virtual void finalize();
       private:
	   int iStrmHL;
	   int iStrmLL;
	   int oStrmHL;
	   int oStrmLL;
	   RLCEntity* rlcEntity;
   } ;

   class RLCEntity
   {
       public: 
	   virtual void initialize(int oStrmLL_, int oStrmHL_);
	   virtual void handleMessage();
	   virtual void handleStatusPDU();
	   virtual void finalize();
       protected:
	   RLCProc* rlcProc;
	   int oStrmLL;
	   int oStrmHL;
	   int seqNumber;
	   std::queue <Packet*> txBuffer;
	   std::queue <Packet*> rxBuffer;
   };
   
   class MAChsProc : public SimpleProcess
   {
   };

}; //namesapce txsys

#endif


