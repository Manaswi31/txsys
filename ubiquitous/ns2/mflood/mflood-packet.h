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
};

//std::cout << (unsigned) PT_TCP << std::endl;
//extern static const packet_t PT_TCP;
//printf("%d\n", i);
//printf("%d\n", (unsigned) PT_TCP);

//extern static packet_t PT_NTYPE;

//PT_NTYPE = 62;

//static const packet_t PT_MFLOOD = 61;


#endif
