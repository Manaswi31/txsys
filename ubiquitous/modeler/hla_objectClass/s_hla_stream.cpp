/* s_hla_stream.cpp */
/* Implementation file for Sim_Hla_Stream class */

/****************************************/
/*        Copyright (c) 1999-2006       */
/*     by OPNET Technologies, Inc.      */
/*      (A Delaware Corporation)        */
/*   7255 Woodmont Av., Suite 250       */
/*         Bethesda, MD, U.S.A.         */
/*          All Rights Reserved.        */
/****************************************/

#include "s_hla_stream.hpp"

// If this file is used for an external program, make sure the
// special macros used for simulations are ignored
#if !defined (SIMC_HLA_BUILD_DLL)
#  define FIN(x)
#  define FOUT return;
#  define FRET(x) return (x);
#  define VOSC_NIL (0L)
#else
	// This is in the context of an opnet simulation, include
	// appropriate definitions
extern "C" {
#  include "vos.h"
	VOS_EXT_DECS
}
#endif

// For short/long host<->network data conversion
#if !defined (HOST_PC_INTEL_WIN32)
#  include <sys/types.h>
#  include <netinet/in.h>
#else
#  include <winsock2.h>
#endif
#include <string.h> // for memcpy

// **************** Sim_Hla_Stream ***************

Sim_Hla_Stream::Sim_Hla_Stream (unsigned long min_size, unsigned long add_size)
	throw (Sim_Hla_Stream_Exception)
	: offset (0), 
	  increment (add_size), 
	  buffer ((char *)NULL),
	  buffer_size (min_size),
	  buffer_owned (1)
	{
	// PURPOSE : allocate an initial buffer for packing of 'min_size'
	// REQUIRES: none
	// EFFECTS : none

	FIN (Sim_Hla_Stream ::Sim_Hla_Stream (min_size, add_size));

	if (min_size)
		{
		buffer = new char [min_size];
		if (buffer == (char *)NULL)
			throw Sim_Hla_Stream_Exception ();
		}

	FOUT;
	}


void
Sim_Hla_Stream::reset (unsigned long min_size, unsigned long add_size)
	throw (Sim_Hla_Stream_Exception)
	{
	// PURPOSE : reset stream to empty buffer of min_size
	// REQUIRES: none
	// EFFECTS : old buffer destroyed

	FIN (Sim_Hla_Stream::reset (min_size, add_size));

	clear ();

	if (min_size)
		{
		buffer = new char [min_size];
		if (buffer == (char *)NULL)
			throw Sim_Hla_Stream_Exception ();
		}
	else
		buffer = (char *)NULL;

	offset = 0;
	increment = add_size;
	buffer_size = min_size;
	buffer_owned = 1;

	FOUT;
	}


void
Sim_Hla_Stream::reset (char * data, unsigned long size) throw ()
	{
	// PURPOSE : reset stream to data block specified
	// REQUIRES: none
	// EFFECTS : none

	FIN (Sim_Hla_Stream::reset (data, size));

	clear ();
	offset = 0;
	buffer = data;
	increment = 0;
	buffer_size = size;
	buffer_owned = 0;

	FOUT;
	}


void
Sim_Hla_Stream::pack (void * data, unsigned long size) throw (Sim_Hla_Stream_Exception)
	{
	// PURPOSE : add 'data' of length 'size' to stream
	// REQUIRES: none
	// EFFECTS : stream buffer expanded if needed and possible
	//           throws if not enough space left in buffer and
	//           can't expand it

	FIN (Sim_Hla_Stream::pack (data, size));

	if (offset+size > buffer_size)
		{
		// Need more space
		if (!buffer_owned)
			throw Sim_Hla_Stream_Exception ();

		// Figure out how much to ask for
		unsigned long new_size = buffer_size + increment;
		while (new_size < offset+size)
			new_size += increment;

		// Try to get that much space
		char * new_buffer = new char [new_size];
		if (new_buffer == (char *)NULL)
			throw Sim_Hla_Stream_Exception ();

		// Copy old data
		memcpy (new_buffer, buffer, offset);

		// switch buffers
		delete [] buffer;
		buffer = new_buffer;
		buffer_size = new_size;
		}

	// add new data to buffer
	memcpy (buffer+offset, data, size);
	offset += size;

	FOUT;
	}


void
Sim_Hla_Stream::unpack (void * data, unsigned long size) throw (Sim_Hla_Stream_Exception)
	{
	// PURPOSE : extract 'size' characters from buffer, stored in 'data'
	// REQUIRES: none
	// EFFECTS : throws exception if not enough data in buffer

	FIN (Sim_Hla_Stream::unpack (data, size));

	// check data is available
	if (offset+size > buffer_size)
		throw Sim_Hla_Stream_Exception ();

	// transfer requested data
	memcpy ((char *)data, buffer+offset, size);

	// move past transfered data
	offset += size;

	FOUT;
	}


const char * 
Sim_Hla_Istream::extract_string () throw (Sim_Hla_Stream_Exception)
	{
	// PURPOSE : Return address of string in packed buffer
	// REQUIRES: none
	// EFFECTS : throw if string not null-terminated

	FIN (Sim_Hla_Istream::extract_string ());

	const char * result = (const char *)(buffer+offset);
	while (offset < buffer_size)
		{
		if (!*(buffer+offset))
			{
			// do not forget to skip the end of string
			++offset;
			FRET (result);
			}
		++offset;
		}
	// run out of data without encountering end of string
	throw Sim_Hla_Stream_Exception ();
#if defined (HOST_PC_INTEL_WIN32)
    // not reached, but @(*#$ compiler whines otherwise
    FRET ((const char *)VOSC_NIL);
#endif
	}


// **************** Packing operators ***************


#if (defined (HOST_PC_INTEL_WIN32) && (_MSC_VER >= 1100))
Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, bool b) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator << (Sim_Hla_Ostream &, bool));

	int value = (b ? 1 : 0);

	os << value;

	FRET (os);
	}
#endif

Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, unsigned short us) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator << (Sim_Hla_Ostream &, unsigned short));

#if !defined (HOST_SUN_SPARC_SOLAR)
	// convert data to network order
	us = (unsigned short)htons ((unsigned short)us);
#endif

	// pack data in buffer
	os.pack ((void *)&us, sizeof (us));

	FRET (os);
	}


Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, short s) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator << (Sim_Hla_Ostream &, short));

#if !defined (HOST_SUN_SPARC_SOLAR)
	// convert data to network order
	s = (short)htons ((unsigned short)s);
#endif

	// pack data in buffer
	os.pack ((void *)&s, sizeof (s));

	FRET (os);
	}


Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, int i) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator << (Sim_Hla_Ostream &, int));

#if !defined (HOST_SUN_SPARC_SOLAR)
	// convert data to network order
	i = (int)htonl ((unsigned long)i);
#endif

	// pack data in buffer
	os.pack ((void *)&i, sizeof (i));

	FRET (os);
	}


Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, unsigned long ul) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator << (Sim_Hla_Ostream &, unsigned long));

#if !defined (HOST_SUN_SPARC_SOLAR)
	// convert data to network order
	ul = (unsigned long)htonl ((unsigned long)ul);
#endif

	// pack data in buffer
	os.pack ((void *)&ul, sizeof (ul));

	FRET (os);
	}


Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, long l) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator << (Sim_Hla_Ostream &, long));

#if !defined (HOST_SUN_SPARC_SOLAR)
	// convert data to network order
	l = (long)htonl ((unsigned long)l);
#endif

	// pack data in buffer
	os.pack ((void *)&l, sizeof (l));

	FRET (os);
	}


#if defined (HOST_PC_INTEL_WIN32)

Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, __int64 i64) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator << (Sim_Hla_Ostream &, __int64));

	// convert data to network order
	__int64 no;
	*((unsigned long *)&no) = htonl (*(((unsigned long *)&i64)+1));
	*(((unsigned long *)&no)+1) = htonl (*((unsigned long *)&i64));
	
	// pack data in buffer
	os.pack ((void *)&no, sizeof (no));

	FRET (os);
	}

#else

Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, long long ll) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator << (Sim_Hla_Ostream &, long long));

	// Solaris/Sparc already in network order
#if !defined (HOST_SUN_SPARC_SOLAR)
	long long lln;
	*((unsigned long *)&lln) = htonl (*(((unsigned long *)&ll)+1));
	*(((unsigned long *)&lln)+1) = htonl (*((unsigned long *)&ll));
	os.pack ((void *)&lln, sizeof (lln));
#else	
	// pack data in buffer
	os.pack ((void *)&ll, sizeof (ll));
#endif

	FRET (os);
	}


Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, unsigned long long ull) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator << (Sim_Hla_Ostream &, unsigned long long));

	// Solaris/Sparc already in network order
#if !defined (HOST_SUN_SPARC_SOLAR)
	long long ulln;
	*((unsigned long *)&ulln) = htonl (*(((unsigned long *)&ull)+1));
	*(((unsigned long *)&ulln)+1) = htonl (*((unsigned long *)&ull));
	os.pack ((void *)&ulln, sizeof (ulln));
#else	
	// pack data in buffer
	os.pack ((void *)&ull, sizeof (ull));
#endif

	FRET (os);
	}

#endif


Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, float f) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator << (Sim_Hla_Ostream &, float ));

	// convert data to network order
#if !defined (HOST_SUN_SPARC_SOLAR)
	*((unsigned long *)&f) = htonl (*((unsigned long *)&f));
#else
	// Solaris/Sparc already in network order
#endif

	// pack data in buffer
	os.pack ((void *)&f, sizeof (f));

	FRET (os);
	}


Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, double d) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator << (Sim_Hla_Ostream &, double ));

	// convert data to network order
#if !defined (HOST_SUN_SPARC_SOLAR)
	double no;
	*((unsigned long *)&no) = htonl (*(((unsigned long *)&d)+1));
	*(((unsigned long *)&no)+1) = htonl (*((unsigned long *)&d));
	// pack data in buffer
	os.pack ((void *)&no, sizeof (no));
#else
	// Solaris/Sparc already in network order
	// pack data in buffer
	os.pack ((void *)&d, sizeof (d));
#endif

	FRET (os);
	}


Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, char c) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator << (Sim_Hla_Ostream &, char ));

	os.pack ((void *)&c, sizeof (c));
	FRET (os);
	}


Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, unsigned char uc) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator << (Sim_Hla_Ostream &, unsigned char ));

	os.pack ((void *)&uc, sizeof (uc));
	FRET (os);
	}


Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, const char * s) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator << (Sim_Hla_Ostream &, const char * ));

	os.pack ((void *)s, strlen (s)+1);
	FRET (os);
	}


// **************** Unpacking operators ***************

#if (defined (HOST_PC_INTEL_WIN32) && (_MSC_VER >= 1100))
Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, bool & b) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator >> (Sim_Hla_Istream &, bool &));

	int value;

	is >> value;

	b = value == 1;

	FRET (is);
	}
#endif

Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, unsigned short & us) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator >> (Sim_Hla_Istream &, unsigned short &));

#if !defined (HOST_SUN_SPARC_SOLAR)
	// Extract data from buffer
	unsigned short no;
	is.unpack ((void *)&no, sizeof (no));

	// Convert to host order
	us = (unsigned short)ntohs ((unsigned short)no);
#else
	is.unpack ((void *)&us, sizeof (us));
#endif

	FRET (is);
	}


Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, short & s) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator >> (Sim_Hla_Istream &, short &));

#if !defined (HOST_SUN_SPARC_SOLAR)
	// Extract data from buffer
	short no;
	is.unpack ((void *)&no, sizeof (no));

	// Convert to host order
	s = (short)ntohs ((unsigned short)no);
#else
	is.unpack ((void *)&s, sizeof (s));
#endif

	FRET (is);
	}


Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, int & i) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator >> (Sim_Hla_Istream &, int &));

#if !defined (HOST_SUN_SPARC_SOLAR)
	// Extract data from buffer
	int no;
	is.unpack ((void *)&no, sizeof (no));

	// Convert to host order
	i = (int)ntohl ((unsigned long)no);
#else
	is.unpack ((void *)&i, sizeof (i));
#endif

	FRET (is);
	}


Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, unsigned long & ul) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator >> (Sim_Hla_Istream &, unsigned long &));

#if !defined (HOST_SUN_SPARC_SOLAR)
	// Extract data from buffer
	unsigned long no;
	is.unpack ((void *)&no, sizeof (no));

	// Convert to host order
	ul = (unsigned long)ntohl ((unsigned long)no);
#else
	is.unpack ((void *)&ul, sizeof (ul));
#endif

	FRET (is);
	}


Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, long & l) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator >> (Sim_Hla_Istream &, long &));

#if !defined (HOST_SUN_SPARC_SOLAR)
	// Extract data from buffer
	long no;
	is.unpack ((void *)&no, sizeof (no));

	// Convert to host order
	l = (long)ntohl ((unsigned long)no);
#else
	is.unpack ((void *)&l, sizeof (l));
#endif

	FRET (is);
	}


#if defined (HOST_PC_INTEL_WIN32)

Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, __int64 & i64) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator >> (Sim_Hla_Istream &, __int64 &));

	// Extract data from buffer
	__int64 no;
	is.unpack ((void *)&no, sizeof (no));

	// Convert to host order
	*((unsigned long *)&i64) = ntohl (*(((unsigned long *)&no)+1));
	*(((unsigned long *)&i64)+1) = ntohl (*((unsigned long *)&no));

	FRET (is);
	}

#else

Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, long long & ll) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator >> (Sim_Hla_Istream &, long long &));

	// Solaris/Sparc already in network order
#if !defined (HOST_SUN_SPARC_SOLAR)	
	long long lln;
	is.unpack ((void *)&lln, sizeof (lln));

	// Convert to host order
	*((unsigned long *)&ll) = ntohl (*(((unsigned long *)&lln)+1));
	*(((unsigned long *)&ll)+1) = ntohl (*((unsigned long *)&lln));
#else
	// Extract data from buffer
	is.unpack ((void *)&ll, sizeof (ll));
#endif

	FRET (is);
	}


Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, unsigned long long & ull) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator >> (Sim_Hla_Istream &, unsigned long long &));

	// Solaris/Sparc already in network order
	
#if !defined (HOST_SUN_SPARC_SOLAR)	
	long long ulln;
	is.unpack ((void *)&ulln, sizeof (ulln));

	// Convert to host order
	*((unsigned long *)&ull) = ntohl (*(((unsigned long *)&ulln)+1));
	*(((unsigned long *)&ull)+1) = ntohl (*((unsigned long *)&ulln));
#else
	// Extract data from buffer
	is.unpack ((void *)&ull, sizeof (ull));
#endif

	FRET (is);
	}

#endif


Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, float & f) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator >> (Sim_Hla_Istream &, float &));

#if !defined (HOST_SUN_SPARC_SOLAR)
	// Extract data from buffer
	float no;
	is.unpack ((void *)&no, sizeof (no));

	// Convert to host order
	*((unsigned long *)&f) = ntohl (*((unsigned long *)&no));
#else
	// Solaris/Sparc already in host order
	is.unpack ((void *)&f, sizeof (f));
#endif

	FRET (is);
	}


Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, double & d) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator >> (Sim_Hla_Istream &, double &));

#if !defined (HOST_SUN_SPARC_SOLAR)
	// Extract data from buffer
	float no;
	is.unpack ((void *)&no, sizeof (no));

	// Convert to host order
	*((unsigned long *)&d) = ntohl (*(((unsigned long *)&no)+1));
	*(((unsigned long *)&d)+1) = ntohl (*((unsigned long *)&no));

#else
	// Solaris/Sparc already in host order
	is.unpack ((void *)&d, sizeof (d));
#endif

	FRET (is);
	}


Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, char & c) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator >> (Sim_Hla_Istream &, char &));

	is.unpack ((void *)&c, sizeof (c));
	FRET (is);
	}


Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, unsigned char & uc) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator >> (Sim_Hla_Istream &, unsigned char &));

	is.unpack ((void *)&uc, sizeof (uc));
	FRET (is);
	}


Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, const char * & s) throw (Sim_Hla_Stream_Exception)
	{
	FIN (operator >> (Sim_Hla_Istream &, const char * &));

	s = is.extract_string ();
	FRET (is);
	}

