/**
 * flood.h
 */

#ifndef __flood_h__
#define __flood_h__


#include <assert.h>
#include <list>

static const int INFINITY =  0xff;
static const int MaxSeqNum = 1000;

/*Rotuer ID Type*/
typedef int Rid;
typedef unsigned seq_t;
#define FloodEntryIter (std::list <FloodRTEntry>::iterator) 

class FloodRTEntry
{
    friend class FloodRTable;
    public:
	FloodRTEntry();
	FloodRTEntry(Rid src, seq_t seq);
	bool isNewSeq (seq_t seq);
	void addSeq(seq_t);
	void rtLookUp();

    protected:
	seq_t rtSeqNum[MaxSeqNum]; /*an array to store the sequence number for other peers*/
	seq_t  maxSeqNum_;
	seq_t  minSeqNum_;
	Rid src_;
};

class FloodRTable
{
    public:
	FloodRTable();
	void rtDelete(Rid toDel);
	FloodEntryIter rtLoopUp(Rid toFind);
    private:
	std::list <FloodRTEntry> rTable;
} ;


#endif
