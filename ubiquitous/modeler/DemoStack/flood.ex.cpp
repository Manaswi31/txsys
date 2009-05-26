#include "flood.h"

FloodRTEntry::FloodRTEntry()
{
    for (int i = 0; i<MaxSeqNum; i++) 
	rtSeqNum[i] = 0xffffffff;
}

FloodRTEntry::FloodRTEntry(Rid src, seq_t seq)
    : src_(src), 
    maxSeqNum_(seq), 
    minSeqNum_(0) 
{
    rtSeqNum[0]=seq;
    for (int i=0; i<MaxSeqNum; i++) rtSeqNum[i] = 0xffffffff;

}

bool FloodRTEntry::isNewSeq(seq_t seq)
{
    if (seq > maxSeqNum_) return true;
    else if (seq < minSeqNum_) return false;
    for (int i=0; i<MaxSeqNum; i++) {
	if (seq==rtSeqNum[i]) return false;
    }
    return true;
}


void FloodRTEntry::addSeq(seq_t seq)
{
    if (seq < minSeqNum_) return; /*This is a past seq_num, ignore it*/
    else if (seq > maxSeqNum_) maxSeqNum_ = seq;
}

FloodEntryIter FloodRTable::rtLoopUp(Rid id)
{
    std::list<FloodRTEntry>::iterator it ;
    for (it= rTable.begin(); it!=rTable.end();it++) {
	if (it->src_==id) break;
    }
    return it;

}

void FloodRTable::rtDelete(Rid id)
{
    FloodEntryIter rt = rtLoopUp(id);
    if (rt != NULL) {
	rTable.erase(rt);
    }
}


//EOF

