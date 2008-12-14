/**
 * mflood-packet.h
 */



#ifndef __mflood_packet_h__
#define __mflood_packet_h__

#include <packet.h>
#include <stdio.h>

#define HDR_MFLOOD_PKT(p) ((struct hdr_mflood*)hdr_mflood::access(p))

struct hdr_mflood {
	u_int32_t seq_;
	static int offset_;
	inline static int & offset() { return offset_; }
	inline static hdr_mflood* access(const Packet *p) {
		return (hdr_mflood*) p->access(offset_);
	}
	inline u_int32_t seq_num() {return seq_;}
};
#endif
