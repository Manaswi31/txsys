/* s_hla_stream.hpp */
/* Interface header for class used to */
/* pack/unpack data for attributes and parameters */
/* with host <-> network data conversion */

/****************************************/
/*        Copyright (c) 1999            */
/*          by MIL 3, Inc.              */
/*      (A Delaware Corporation)        */
/*  3400 International Drive,  N.W.     */
/*      Washington, D.C., U.S.A.        */
/*          All Rights Reserved.        */
/****************************************/

#ifndef HDR_S_HLA_STREAM_HPP
#define HDR_S_HLA_STREAM_HPP

// No include of other pieces of OPNET hla support
// since this code can be used by external programs

#if (!defined (HOST_PC_INTEL_WIN32))
#  include <strstream.h>
// unix don't have to battle the concept of DLL IMPORT/EXPORT
#  define S_HLA_DLLEXPORT

#else
#  include <strstream>

// Visual C++ does not deal very gracefully with exception
// signatures containing actual exceptions
// It simply ignores them with a warning
// But the warning can also be turned off
#  pragma warning (disable: 4290)

// Make sure the symbols are exported so that other process models can
// access them
// Similarly, applications using that file should define SIMC_HLA_DLLEXPORT
// to avoid seeing Visual C++ complain about local symbol being imported
#  if defined (SIMC_HLA_DLLEXPORT)
#    define S_HLA_DLLEXPORT __declspec (dllexport)
#  else
#    define S_HLA_DLLEXPORT __declspec (dllimport)
#  endif

#endif
#include <stdlib.h> // for NULL

// thrown by Sim_Hla_Stream when error occurs
// note: different naming convention than other Sim_Hla Exceptions
// since might be used in program not using rest of Sim_Hla items
class S_HLA_DLLEXPORT Sim_Hla_Stream_Exception
	{
public:
	Sim_Hla_Stream_Exception () {}
	~Sim_Hla_Stream_Exception () throw () {}
	};

// This class packs data after converting it from
// host to network representation,
// and unpacks data after converting it back to
// host representation

class S_HLA_DLLEXPORT Sim_Hla_Stream
	{
public:
	enum
		{
		Initial_Buffer_Size = 128,
		Buffer_Growth_Amount = 128
		};

protected:
	/* Constructors */
	// Empty stream for packing, 'min_size' is the inital buffer size
	// 'add_size' is the increment amount when more space is needed
	// while packing
	Sim_Hla_Stream (unsigned long min_size = Initial_Buffer_Size,
		unsigned long add_size = Buffer_Growth_Amount)
		throw (Sim_Hla_Stream_Exception);
	
	// Provided buffer of 'size' chars for packing or extraction
	// (no growth allowed when packing)
	Sim_Hla_Stream (char * data, unsigned long size) throw ()
		: offset (0), buffer (data), increment (0),
		  buffer_size (size), buffer_owned (0)
	{ }

public:
	/* Destructor */
	~Sim_Hla_Stream () throw () { clear (); }

	/* Accessors */
	unsigned long amount () const throw () { return offset; }

	const char * data () const throw () { return buffer; }

	/* Mutators */
	// Add 'data' of length 'size' to stream
	void pack (void * data, unsigned long size) throw (Sim_Hla_Stream_Exception);

	// Extract 'size' bytes from stream, to store in 'data'
	void unpack (void * data, unsigned long size) throw (Sim_Hla_Stream_Exception);

	// Reset to blank state
	void reset (char * data, unsigned long size) throw ();
	
protected:
	unsigned short	buffer_owned;
	unsigned long	offset;
	char *			buffer;
	unsigned long	increment;
	unsigned long	buffer_size;

	// Reset to blank state
	void reset (unsigned long min_size, unsigned long add_size)
		throw (Sim_Hla_Stream_Exception);

	void clear () throw ()
		{ if (buffer_owned && (buffer != (char *)NULL)) delete [] buffer; }
	};


// For packing
class S_HLA_DLLEXPORT Sim_Hla_Ostream : public Sim_Hla_Stream
	{
public:
	enum
		{
		Initial_Buffer_Size = 128,
		Buffer_Growth_Amount = 128
		};

	/* Constructors */
	// Empty stream for packing, 'min_size' is the inital buffer size
	// 'add_size' is the increment amount when more space is needed
	// while packing
	Sim_Hla_Ostream (unsigned long min_size = Initial_Buffer_Size,
		unsigned long add_size = Buffer_Growth_Amount)
		throw (Sim_Hla_Stream_Exception)
		: Sim_Hla_Stream (min_size, add_size)
	{ }
	
	// Provided buffer of 'size' chars for packing 
	// (no growth allowed when packing)
	Sim_Hla_Ostream (char * data, unsigned long size) throw ()
		: Sim_Hla_Stream (data, size)
	{ }

	// Reset to blank state
	void reset (unsigned long min_size = Initial_Buffer_Size,
		unsigned long add_size = Buffer_Growth_Amount)
		throw (Sim_Hla_Stream_Exception)
		{ Sim_Hla_Stream::reset (min_size, add_size); }
	};


// For unpacking
class S_HLA_DLLEXPORT Sim_Hla_Istream : public Sim_Hla_Stream
	{
public:
	Sim_Hla_Istream (char * data, unsigned long data_size) throw ()
		: Sim_Hla_Stream (data, data_size)
	{ }

	~Sim_Hla_Istream () throw () { }

	friend S_HLA_DLLEXPORT Sim_Hla_Istream &
	operator >> (Sim_Hla_Istream &, const char * &) throw (Sim_Hla_Stream_Exception);

private:
	const char * extract_string () throw (Sim_Hla_Stream_Exception);
	};



// Packing operators
// Throw if not enough space remaining in fixed size buffer
// or if buffer couldn't be expanded when needed

// Visual C++ 5.0 has 'bool' as a separate type
#if (defined (HOST_PC_INTEL_WIN32) && (_MSC_VER >= 1100))
S_HLA_DLLEXPORT Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, bool b)                 
	throw (Sim_Hla_Stream_Exception);
#endif

S_HLA_DLLEXPORT Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, unsigned short us)      
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, short s)                
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, int i)                  
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, unsigned long ul)       
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, long l)                 
	throw (Sim_Hla_Stream_Exception);

#if defined (HOST_PC_INTEL_WIN32)
S_HLA_DLLEXPORT Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, __int64 i64)            
	throw (Sim_Hla_Stream_Exception);
#else
S_HLA_DLLEXPORT Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, long long ll)           
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, unsigned long long ull) 
	throw (Sim_Hla_Stream_Exception);
#endif

S_HLA_DLLEXPORT Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, float f)                
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, double d)               
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, char c)                 
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, unsigned char uc)       
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Ostream &
operator << (Sim_Hla_Ostream & os, const char * s)         
	throw (Sim_Hla_Stream_Exception);


// Unpacking operators
// Throw if not enough data in buffer

// Visual C++ 5.0 has 'bool' as a separate type
#if (defined (HOST_PC_INTEL_WIN32) && (_MSC_VER >= 1100))
S_HLA_DLLEXPORT Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, bool & b)                 
	throw (Sim_Hla_Stream_Exception);
#endif

S_HLA_DLLEXPORT Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, unsigned short & us)      
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, short & s)                
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, int & i)                  
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, unsigned long & ul)       
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, long & l)                 
	throw (Sim_Hla_Stream_Exception);

#if defined (HOST_PC_INTEL_WIN32)
S_HLA_DLLEXPORT Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, __int64 & i64)            
	throw (Sim_Hla_Stream_Exception);
#else
S_HLA_DLLEXPORT Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, long long & ll)           
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, unsigned long long & ull) 
	throw (Sim_Hla_Stream_Exception);
#endif

S_HLA_DLLEXPORT Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, float & f)                
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, double & d)               
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, char & c)                 
	throw (Sim_Hla_Stream_Exception);

S_HLA_DLLEXPORT Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, unsigned char & uc)       
	throw (Sim_Hla_Stream_Exception);

// set 's' to beginning of string in buffer
// string data must be copied to survive destruction
// of Sim_Hla_Istream
S_HLA_DLLEXPORT Sim_Hla_Istream &
operator >> (Sim_Hla_Istream & is, const char * & s)         
	throw (Sim_Hla_Stream_Exception);
#endif /* HDR_S_HLA_STREAM_HPP */
