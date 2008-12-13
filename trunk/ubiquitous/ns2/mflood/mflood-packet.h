/**
 * mflood-packet.h
 */

#ifndef __mflood_packet_h__
#define __mflood_packet_h__

#define HDR_FLOOD(p) ((struct hdr_mflood*)hdr_mflood::access(p))

struct hdr_mflood {
	u_int32_t seq_;
	static int offset_;
	inline static int & offset() { return offset_; }
	inline static hdr_mflood* access(const Packet *p) {
		return (hdr_mflood*) p->access(offset_);
	}
};
#endif
