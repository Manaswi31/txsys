#include "flood.h"

FloodRTEntry::FloodRTEntry()
{
    for (int i = 0; i<MaxSeqNum; i++) 
	rtSeqNum[i] = 0xffffffff;
}

FloodRTEntry::FloodRTEntry(Rid src, seq_t seq)
    : src_(src), 
    maxSeq_(seq), 
    minSeq_(0), 
    rtSeqNum[0](seq)
{
    for (int i=0; i<MaxSeqNum; i++) rtSeqNum[i] = 0xffffffff;

}

bool FloodRTEntry::isNewSeq(seq_t seq)
{
    if (seq > maxSeq_) return true;
    else if (seq < minSeq_) return false;
    for (int i=0; i<MaxSeqNum; i++) {
	if (seq==rtSeqNum[i]) return false;
    }
    return true;
}


void FloodRTEntry::addSeq(seq_t seq)
{
    if (seq < minSeq_) return; /*This is a past seq_num, ignore it*/
    else if (seq > maxSeq_) maxSeq_ = seq;
}

FloodRTEntry FloodRTable::rtLoopUp(Rid id)
{
    list<int>::interator it ;
    for (it= rTable.begin(); it!=rTable.end();it++) {
	if (it->src_==id) break;
    }
    return *it;

}

void FloodRTable::rtDelete(Rid id)
{
    FloodRTEntry * rt = rtLoopUp(id);
    if (rt != NULL) {
    }
}


//EOF

