/**
 * flood.h
 */

#ifndef __FLOOD_H__
#define __FLOOD_H__

//transnet/routing/mac

#include <assert.h>
#include <list>
#include <opnet.h>

static const int INFINITY =  0xff;
static const int MaxSeqNum = 1000;

/*Rotuer ID Type*/
typedef int Rid;
typedef char Byte;
typedef unsigned seq_t;
class FloodRTEntry;
typedef std::list <FloodRTEntry>::iterator FloodRTEntryIter;

typedef struct
{
 int dummy;
} L3IfData; //

typedef struct
{
    Byte L1Addr;
    Byte L2Addr;
    Byte L3Addr; //local
    Byte L4Addr; //for application, i.e., a port
} Address;

class FloodRTEntry
{
    //friend class FloodRTable;
    public:
	FloodRTEntry();
	FloodRTEntry(Rid src, seq_t seq);
	bool isNewSeq (seq_t seq);
	void addSeq(seq_t);
	Rid getSRid();

   protected:
	Rid _sRid;
	seq_t maxSeqNum_;
	seq_t minSeqNum_;
	unsigned seq_it;
	seq_t rtSeqNum[MaxSeqNum]; /*an array to store the sequence number for other peers*/
};


class FloodRTable
{
    public:
	FloodRTable();
	void rtDelete(Rid toDel);
	bool rtLookUp(Rid toFind);
	void rtInsert(Rid rid, seq_t seq);
    private:
	std::list <FloodRTEntry> rTable;
} ;

class FloodRte
{
    public:
	FloodRte();
	void init();
	//encap();
	//send();
	void procHLPk(Packet*);
	void procLLPk(Packet*);
	void handleMessage();
    private:
	typedef struct
	{
	    int seq;
	    Rid saddr;
	    Rid daddr;
	} Flood_Rte_Hdr;

	typedef enum
	{
	    Flood_Rte_Fd_Ind_Header = 1,
	    Flood_Rte_Fd_Ind_Payload
	} Flood_Rte_Pk_Fd_Ind;

	const static int Flood_Pk_Hdr_Size = 160; //in bits
	int llOstrm ;
	int hlOstrm ; 
	int llIstrm ;
	int hlIstrm ;
	Packet* curPk;
	int _seq;
	Rid _rid;
	FloodRTable* _rtable;
} ;

class TransNet
{
    public :
	TransNet();
	TransNet(Byte L1addr, Byte L2addr, Byte L3addr, Byte l4addr);
	void procLLPk(Packet*);
	void procHLPk(Packet*);
	void handleMessage();
    private:
	const static int TransNetPkHdrSize = 20; //in bits
	
	typedef enum {
	    Flood_TransNet_Fd_Ind_Hdr = 1
	    , Flood_TransNet_Fd_Ind_Payload 
	} Flood_TransNet_Pk_Fd_Ind;

	typedef struct {
	    Address addr;
	} TransNetHdr;

	Address _addr;
	int llOstrm ;
	int hlOstrm ; 
	int llIstrm ;
	int hlIstrm ;
} ;


#endif
