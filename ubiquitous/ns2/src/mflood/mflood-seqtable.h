/**
 * mflood-seqtable.h
 *
 */

#ifndef __mflood_seqtable_h__
#define __mflood_seqtable_h__

#include <assert.h>
#include <sys/types.h>
#include <config.h>
#include <lib/bsd-list.h>
#include <scheduler.h>

#define INFINITY 0xff
#define RTE_DOWN 0
#define RTE_UP 1
#define REM_SEQ_COUNT 1000

class MFlood_RTEntry {
	friend class MFlood_RTable;
	friend class MFlood;
public :
	MFlood_RTEntry();
	MFlood_RTEntry(nsaddr_t src, u_int32_t seq);
	bool isNewSeq(u_int32_t seq);
	void addSeq(u_int32_t seq);
protected : 
	LIST_ENTRY(MFlood_RTEntry) rt_link;
	nsaddr_t src_;
	u_int32_t rt_seqnos[REM_SEQ_COUNT];
	u_int32_t  max_seqno;
	u_int32_t  min_seqno;
	u_int16_t  seq_it;
};

class MFlood_RTable {
	friend class MFlood;
public : 
	MFlood_RTable () { LIST_INIT(&rthead); }
	void rt_delete(nsaddr_t id);
	MFlood_RTEntry* rt_lookup(nsaddr_t id);
	void rt_print();
private : 
	LIST_HEAD(, MFlood_RTEntry) rthead;
};
#endif

