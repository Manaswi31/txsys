
/* External federate used to test features of HLA-PM */


#include "controller_tutorial.hpp"
#include <fedtime.hh>

#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>

#include <iostream>
#include <iomanip>

#if !defined (_MSC_VER)
#  include <netinet/in.h>
#  include <unistd.h> /* for sleep */
#  include <strstream.h>
#else
#  include <windows.h> /* for Sleep */
#  include <strstream>
#endif

using namespace std;

#include "s_hla_stream.hpp"

/* RTI ambassador shared among the functions of the program */
static RTI::RTIambassador rti_amb;

/* Federate ambassador */
static Master_FA fedAmb;

static int time_regulation_enabled = 0;
static int time_constrained_enabled = 0;

static const char * fedExecName;

static RTI::Boolean timeToQuit = RTI::RTI_FALSE;

static RTIfedTime currentTime (0.0);

static RTIfedTime next_time ()
	{ RTIfedTime lookahead;
	  rti_amb.queryLookahead (lookahead);
	  return currentTime + lookahead.getTime (); }

static RTI::Boolean timeAdvanceOutstanding = RTI::RTI_FALSE;

static RTI::FederateHandle federateId;

// Interarctions
enum OrderAttributes { Bearing, Speed, NbOrderAttributes };
enum ReplyAttributes { Id, ChangeLat, ChangeLong, NbReplyAttributes };

static const char * const orderAttrTypeStr [] =
	{ "bearing", "speed" };
static const char * const replyAttrTypeStr [] =
	{ "id", "change_lat", "change_long" };

static RTI::InteractionClassHandle order_handle;
static RTI::ParameterHandle order_parameters [NbOrderAttributes];
static RTI::InteractionClassHandle reply_handle;
static RTI::ParameterHandle reply_parameters [NbReplyAttributes];

/******* Pending Requests ******/

class PendingRequest
	{
public:
	PendingRequest (void) : next(NULL) {}
	virtual ~PendingRequest (void) {}

	// apply appropriate behavior
	virtual void apply (void) = 0;

	static int empty () { return head == (PendingRequest *)NULL; }

	static void enqueue (PendingRequest * pr);
	static PendingRequest * dequeue ();

private:
	class PendingRequest * next;

	static PendingRequest * head;
	static PendingRequest * tail;

	friend class Master_FA;
	};

PendingRequest * PendingRequest::head = (PendingRequest *)NULL;
PendingRequest * PendingRequest::tail = (PendingRequest *)NULL;

void
PendingRequest::enqueue (PendingRequest * pr)
	{
	if (head == (PendingRequest *)NULL)
		{
		head = pr;
		tail = pr;
		}
	else
		{
		tail->next = pr;
		tail = pr;
		}
	}

PendingRequest *
PendingRequest::dequeue ()
	{
	if (head == (PendingRequest *)NULL)
		return head;
	PendingRequest * result = head;
	head = head->next;
	if (tail == result)
		tail = head;
	return result;
	}

	
class ProvideAttributeValueUpdatePR : public PendingRequest
	{
public:
	ProvideAttributeValueUpdatePR (RTI::ObjectHandle oid,
		const RTI::AttributeHandleSet & attr);

	virtual ~ProvideAttributeValueUpdatePR (void)
		{ if (size) delete [] handleSet; }

	virtual void apply (void);

private:
	RTI::ObjectHandle objid;
	unsigned long size;
	RTI::AttributeHandle * handleSet;
	};


ProvideAttributeValueUpdatePR::ProvideAttributeValueUpdatePR (RTI::ObjectHandle oid,
	const RTI::AttributeHandleSet & attr)
	: objid (oid), size (attr.size ())
	{
	handleSet = new RTI::AttributeHandle [size];
	if (handleSet == NULL)
		{
		cerr << "Unable to create array of attribute handles, can't process attribute update request" << endl;
		size = 0;
		return;
		}
	
	for (int i = 0; i < size; i++)
		{
		handleSet[i] = attr.getHandle (i);
		}
	}

void
ProvideAttributeValueUpdatePR::apply ()
	{
	}


/******* Federate Ambassador **********/

/* Constructor */

Master_FA::Master_FA () : RTI::FederateAmbassador ()
	{ }

/* Destructor */

Master_FA::~Master_FA () throw()
	{ }

/* Services called by the RTI */

////////////////////////////////////
// Federation Management Services //
////////////////////////////////////


////////////////////////////////
// Object Management Services //
////////////////////////////////

void
Master_FA::reflectAttributeValues (RTI::ObjectHandle theObject,
	const RTI::AttributeHandleValuePairSet & theAttributes,
	const RTI::FedTime & theTime,
	const char * theTag,
	RTI::EventRetractionHandle theHandle) 
	throw (
		RTI::ObjectNotKnown,
		RTI::AttributeNotKnown,
		RTI::FederateOwnsAttributes,
		RTI::InvalidFederationTime,
		RTI::FederateInternalError)
	{
	cerr << "Incoming attribute update for unknown object" << endl;
	}

void
Master_FA::receiveInteraction (
	RTI::InteractionClassHandle theInteraction,
	const RTI::ParameterHandleValuePairSet & theParameters,
	const RTI::FedTime & theTime,
	const char * theTag,
	RTI::EventRetractionHandle theHandle)
	throw (
		RTI::InteractionClassNotKnown,
		RTI::InteractionParameterNotKnown,
		RTI::InvalidFederationTime,
		RTI::FederateInternalError)
	{
	RTIfedTime fed_time(theTime);
	cout << "Incoming interaction at time " << fed_time.getTime() << endl;
	if (theInteraction != reply_handle)
		{
		cerr << "Received unknown interaction " << theInteraction << endl;
		return;
		}
	if (theParameters.size() != 3)
		{
		cerr << "Unexpected number of parameters " 
			 << theParameters.size() << endl;
		return;
		}

	// extract values
	RTI::ULong	id;
	RTI::Double	change_lat;
	RTI::Double	change_long;
	unsigned long length;
	RTI::ParameterHandle handle;
    char buffer [20];

	for (unsigned long i = 0; i < 3; i++)
		{
		handle = theParameters.getHandle (i);
		if (handle == reply_parameters [Id])
			{
			theParameters.getValue (i, buffer, length);
			Sim_Hla_Istream is (buffer, length);
			is >> id;
			}
		else if (handle == reply_parameters [ChangeLat])
			{
			theParameters.getValue (i, buffer, length);
			Sim_Hla_Istream is (buffer, length);
			is >> change_lat;
			}
		else if (handle == reply_parameters [ChangeLong])
			{
			theParameters.getValue (i, buffer, length);
			Sim_Hla_Istream is (buffer, length);
			is >> change_long;
			}
		else
			{
			cerr << "Unknown handle " << handle << " for Param #" << i << endl;
			return;
			}
		}
	cout << "Node " << id << " has changed movement at  " 
		 << change_lat << ", " << change_long << endl;
	}

void 
Master_FA::provideAttributeValueUpdate (
	RTI::ObjectHandle theObject,
	const RTI::AttributeHandleSet & theAttributes)
	throw (
		RTI::ObjectNotKnown,
		RTI::AttributeNotKnown,
		RTI::AttributeNotOwned,
		RTI::FederateInternalError)
	{
	PendingRequest::enqueue (new ProvideAttributeValueUpdatePR (theObject, 
		theAttributes));
	}

//////////////////////////////
// Time Management Services //
//////////////////////////////

void
Master_FA::timeRegulationEnabled (const  RTI::FedTime& theFederateTime) 
	throw (RTI::InvalidFederationTime,
		RTI::EnableTimeRegulationWasNotPending,
		RTI::FederateInternalError)
	{
#if 0
	cout << "timeRegulationEnabled called" << endl;
#endif
	time_regulation_enabled = 1;
	}


void
Master_FA::timeConstrainedEnabled (const RTI::FedTime& theFederateTime) 
	throw (RTI::InvalidFederationTime,
		RTI::EnableTimeConstrainedWasNotPending,
		RTI::FederateInternalError)
	{
#if 0
	cout << "timeConstrainedEnabled called" << endl;
#endif
	time_constrained_enabled = 1;
	}

void
Master_FA::timeAdvanceGrant (const RTI::FedTime & theTime)
	throw (
		RTI::InvalidFederationTime,
		RTI::TimeAdvanceWasNotInProgress,
		RTI::FederateInternalError)
	{
	if (!timeAdvanceOutstanding)
		cerr << "timeAdvanceGrant: Unexpected timeAdvanceGrant" << endl;
	else
		{
		timeAdvanceOutstanding = RTI::RTI_FALSE;
		RTIfedTime fed_time (theTime);
//		cout << "*** Time Advance Grant received for time = " << fed_time.getTime() << endl;
		currentTime = fed_time.getTime ();
		}
	}



/******* Federation Management Services ********/

RTI::Boolean
initiate_federation_participation(const char * const federateName)
	{
	short numTries = 0;
	RTIfedTime cur_time;
	RTIfedTime lookahead, start_time;

	// first try to create a federation
    try
		{
		ostrstream fed_file;
		fed_file << fedExecName << ".fed" << ends;
		rti_amb.createFederationExecution(fedExecName, fed_file.str());
		delete [] fed_file.str ();
		}
    catch ( RTI::FederationExecutionAlreadyExists &)
		{
		// Not an error
//		cerr << "Note: Federation execution already exists." << &e << endl;
		}
    catch ( RTI::Exception& e )
		{
		cerr << "Error:" << &e << endl;
  		return RTI::RTI_FALSE;
		}

	// then try to join the appropriate federation
	cerr << "Attempting to join federation..." << endl;
	
	while (numTries < 10) 
		{
	    try
			{
			federateId = rti_amb.joinFederationExecution( 
									(char * const) federateName,
							        (char * const) fedExecName, 
							        &fedAmb); 
			// worked, now set up time management
			break;
			}
    	catch (RTI::FederateAlreadyExecutionMember& e)
			{
			cerr << "Error: " << federateName
	   	         << " already exists in the Federation Execution "
	   	         << fedExecName << "." << endl;
		    cerr << &e << endl;
		    return RTI::RTI_FALSE;
			}
      	catch (RTI::FederationExecutionDoesNotExist &)
			{
#if 0 /* Not really an error */
		    cerr << "Error: " << fedExecName << " Federation Execution "
		         << "does not exist."<< endl;
		 	cerr << "Sleeping for a few seconds ..." << endl;
#endif
#if !defined (_MSC_VER)
			sleep (2);
#else
			Sleep (2000);
#endif
		    ++numTries;
			}
        catch (RTI::CouldNotOpenFED& e)
			{
		    cerr << "Error: The FED file $RTI_CONFIG/" << fedExecName << ".fed"
		         << " could not be opened."
	       		 << endl;
			cerr << &e << endl;
	  		return RTI::RTI_FALSE;
			}      
   	   	catch (RTI::ErrorReadingFED& e)
			{
			cerr << "Error: The FED file $RTI_CONFIG/" << fedExecName << ".fed"
	       		 << " can not be properly read - please check the format."
	       		 << endl;
	  		cerr << &e << endl;
	  		return RTI::RTI_FALSE;
			}
        catch ( RTI::Exception& e )
			{
	  		cerr << "Error:" << &e << endl;
	  		return RTI::RTI_FALSE;
			}
		}
	if (numTries == 10)
		{
		cerr << "Too many attempts to join, giving up" << endl;
		return RTI::RTI_FALSE;
		}

	cout << "Federation joined, attempting to enable time regulation..." << endl;
	// first indicate that this program will be involved
	// in time advances
	try
		{
		lookahead.setEpsilon ();
		//lookahead=0.1;
		start_time.setZero ();
		rti_amb.enableTimeRegulation (start_time, lookahead);
		}
	catch (RTI::Exception & e)
		{
		cerr << "enableTimeRegulation error:" << &e << endl;
		return RTI::RTI_FALSE;
		}

	// Enabling time regulation is asynchronous,
	// wait for callback to inform us of completion of request
	while (!time_regulation_enabled)
		rti_amb.tick (0.05, 0.1);
	rti_amb.queryFederateTime (cur_time);
	currentTime = cur_time.getTime ();
	cout << "Time regulation enabled, RTI time is " << currentTime.getTime () << endl;

	cout << "Attempting to constrain time advances..." << endl;
	// then, have time advances constrained to federation time
	try
		{
		rti_amb.enableTimeConstrained ();
		}
	catch (RTI::Exception & e)
		{
		cerr << "enableTimeConstrained Error:" << &e << endl;
		return RTI::RTI_FALSE;
		}
	
	// Enabling time constrained in asynchronous
	// wait for callback to inform us of completion of request
	while (!time_constrained_enabled)
		rti_amb.tick (0.05, 0.1);
	cout << "Time advances constrained" << endl;
	
	// all done
	return RTI::RTI_TRUE;
	}

void
cease_federation_participation ()
{
	// first resign from the federation
    try
	{
		rti_amb.resignFederationExecution(
					   RTI::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES ); 
	}
    catch ( RTI::Exception& e )
	{
		cerr << "Error:" << &e << endl;
		return;
	}

	// then try to destroy the federation
	try
	{
		rti_amb.destroyFederationExecution ((char * const) fedExecName);
	}
	catch ( RTI::FederatesCurrentlyJoined &)
	{
		// not an error, other federates remaining
	}
	catch ( RTI::Exception & e)
	{
		cerr << "Error:" << &e << endl;
	}
}


/******* Declaration Management Services *****/

void
publish_and_subscribe ()
	{
	unsigned short i;

	// declare two interactions, one published, one subscribed
	order_handle = rti_amb.getInteractionClassHandle ("Order");
	for (i = 0; i < NbOrderAttributes; i++)
		{
		try
			{
			order_parameters [i]
				= rti_amb.getParameterHandle ((char * const)orderAttrTypeStr [i],
					order_handle);
			}
		catch (RTI::Exception & e)
			{
			cerr << "Order param " << orderAttrTypeStr [i] << " causes: " << &e << endl;
			exit (-1);
			}
		}
	rti_amb.publishInteractionClass (order_handle);

	reply_handle = rti_amb.getInteractionClassHandle ("Order_Reply");
	for (i = 0; i < NbReplyAttributes; i++)
		{
		try
			{
			reply_parameters [i]
				= rti_amb.getParameterHandle ((char * const)replyAttrTypeStr [i],
					reply_handle);
			}
		catch (RTI::Exception & e)
			{
			cerr << "Reply param " << replyAttrTypeStr [i] << " causes: " << &e << endl;
			exit (-1);
			}
		}
			
	rti_amb.subscribeInteractionClass (reply_handle);
	}


/****** Object Management Services *******/

/******* Time Management, Attribute Updates, Interactions *********/

double
htond (double host_val)
	{
	double	network_val;
#if defined (_MSC_VER)
	*((unsigned long *)&network_val) = htonl (*(((unsigned long *)&host_val)+1));
	*(((unsigned long *)&network_val)+1) = htonl (*((unsigned long *)&host_val));
#else
	network_val = host_val;
#endif
	return network_val;
	}

void
process_events ()
	{
	char command [200];
	char order [20];
	
	for (;;)
		{
		cout << "[Time: " << currentTime.getTime() << "] Enter command: " << flush;
		gets (command);
		istrstream cmd (command);

		if (command [0] != '\0')
			cmd >> order;
		else
			order [0] = '\0';

		switch (order [0])
			{
			case 'q':
			case 'Q':
				{
				return;
				}
			case 't':
			case 'T':
				{
				double timeToGo;
				cmd >> timeToGo;
				RTIfedTime fedTime (timeToGo);

				do
					{
					rti_amb.nextEventRequest (fedTime);
					timeAdvanceOutstanding = RTI::RTI_TRUE;
					while (timeAdvanceOutstanding)
						rti_amb.tick(0.5,1.0);
					}
				while (currentTime != timeToGo);
				break;
				}
			case 'f':
			case 'F':
				{
				double for_move;
				double bearing, speed;
			
				cmd >> for_move >> bearing >> speed;
				RTIfedTime fed_time (for_move);
			
				if (fed_time < next_time())
					{
					cout << "Time must be at least " << next_time().getTime() << endl;
					}
				else
					{
					RTI::ParameterHandleValuePairSet * iParams;
					double network_order;
					iParams = RTI::ParameterSetFactory::create (2);
					// need to convert to network order
					network_order = htond (bearing);
					iParams->add (order_parameters [Bearing],
						(char *)&network_order,  sizeof (bearing));
					network_order = htond (speed);
					iParams->add (order_parameters [Speed],
						(char *)&network_order, sizeof (speed));
					rti_amb.sendInteraction (order_handle, *iParams, fed_time, "");
					}
				break;
				}
			case '\0':
				{
				break;
				}
			default:
				{
				if (command[0] != 'h' && command[0] != 'H' && command[0] != '?')
					cout << "Unknown command : \"" << command << '"' << endl;
				cout << "Time management:" << endl;
				cout << " t)ime <time>                        : request time advance to <time>" << endl;
				cout << " q)uit                               : terminate program" << endl;
				cout << "Controlling Planes:" << endl;
				cout << " f)ly <time> <bearing> <speed>       : direction/speed for planes at <time>" << endl;
				break;
				}
			}
		// always give RTI some time to do things
		rti_amb.tick(0.05,0.1);

		// Process any pending requests
		while (!PendingRequest::empty ())
			PendingRequest::dequeue()->apply();
		}
	}

/********** MAIN **************/

int
main(int argc, char* argv[])
	{
	if (argc < 2)
		{
		cerr << "Usage : " << argv[0] << " <FederationName>" << endl;
		return 1;
		}

	fedExecName = argv [1];

  	try
		{
    /* join the federation (creating if necessary) and set our time-management
       policies */
    	if (!initiate_federation_participation(argv[0]))
			{
			cerr << "Failed to join federation execution!\n";
			return 1;
			}
    
	    /* exercise the appropriate declaration management services to articulate
	       the capabilities and interests of the federate */
	    publish_and_subscribe ();
	
		process_events ();

		cout << "Done with event loop, leaving the federation" << endl;
		
	    /* resign from the federation execution and attempt to destroy */
	    cease_federation_participation();
		}
	catch (RTI::Exception& e)
		{
	    cerr << "main: unhandled exception from the RTI: " << &e << endl;
	    return 1;
		}
	
	return 0;
	}
