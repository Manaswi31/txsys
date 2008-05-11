/* Process model C form file: bpsk_sink.pr.c */
/* Portions of this file copyright 1992-2004 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char bpsk_sink_pr_c [] = "MIL_3_Tfile_Hdr_ 105A 30A modeler 7 482715BE 482715BE 1 xp Administrator 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 a09 1                                                                                                                                                                                                                                                                                                                                                                                                          ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

#include <stdio.h>

/* End of Header Block */


#if !defined (VOSD_NO_FIN)
#undef	BIN
#undef	BOUT
#define	BIN		FIN_LOCAL_FIELD(_op_last_line_passed) = __LINE__ - _op_block_origin;
#define	BOUT	BIN
#define	BINIT	FIN_LOCAL_FIELD(_op_last_line_passed) = 0; _op_block_origin = __LINE__;
#else
#define	BINIT
#endif /* #if !defined (VOSD_NO_FIN) */



/* State variable definitions */
typedef struct
	{
	/* Internal state tracking for FSM */
	FSM_SYS_STATE
	/* State Variables */
	Distribution *	         		dist_ptr                                        ;
	} bpsk_sink_state;

#define pr_state_ptr            		((bpsk_sink_state*) (OP_SIM_CONTEXT_PTR->mod_state_ptr))
#define dist_ptr                		pr_state_ptr->dist_ptr

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#if defined (OPD_PARALLEL)
#  define FIN_PREAMBLE_DEC	bpsk_sink_state *op_sv_ptr; OpT_Sim_Context * tcontext_ptr;
#  define FIN_PREAMBLE_CODE	\
		if (VosS_Mt_Perform_Lock) \
			VOS_THREAD_SPECIFIC_DATA_GET (VosI_Globals.simi_mt_context_data_key, tcontext_ptr, SimT_Context *); \
		else \
			tcontext_ptr = VosI_Globals.simi_sequential_context_ptr; \
		op_sv_ptr = ((bpsk_sink_state *)(tcontext_ptr->mod_state_ptr));
#else
#  define FIN_PREAMBLE_DEC	bpsk_sink_state *op_sv_ptr;
#  define FIN_PREAMBLE_CODE	op_sv_ptr = pr_state_ptr;
#endif


/* No Function Block */


#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ };
#endif

/* Undefine optional tracing in FIN/FOUT/FRET */
/* The FSM has its own tracing code and the other */
/* functions should not have any tracing.		  */
#undef FIN_TRACING
#define FIN_TRACING

#undef FOUTRET_TRACING
#define FOUTRET_TRACING

#if defined (__cplusplus)
extern "C" {
#endif
	void bpsk_sink (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype bpsk_sink_init (int * init_block_ptr);
	VosT_Address bpsk_sink_alloc (VOS_THREAD_INDEX_ARG_COMMA VosT_Obtype, int);
	void bpsk_sink_diag (OP_SIM_CONTEXT_ARG_OPT);
	void bpsk_sink_terminate (OP_SIM_CONTEXT_ARG_OPT);
	void bpsk_sink_svar (void *, const char *, void **);


	VosT_Obtype Vos_Define_Object_Prstate (const char * _op_name, unsigned int _op_size);
	VosT_Address Vos_Alloc_Object_MT (VOS_THREAD_INDEX_ARG_COMMA VosT_Obtype _op_ob_hndl);
	VosT_Fun_Status Vos_Poolmem_Dealloc_MT (VOS_THREAD_INDEX_ARG_COMMA VosT_Address _op_ob_ptr);
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
bpsk_sink (OP_SIM_CONTEXT_ARG_OPT)
	{

#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (bpsk_sink ());
		{
		/* Temporary Variables */
		FILE* fptr;
		int temp_array[1024];
		/* End of Temporary Variables */


		FSM_ENTER_NO_VARS ("bpsk_sink")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (Init) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "Init", "bpsk_sink [Init enter execs]")
				FSM_PROFILE_SECTION_IN ("bpsk_sink [Init enter execs]", state0_enter_exec)
				{
				dist_ptr = op_dist_load("uniform_int", 0, 1);
				fptr = fopen("f:\\bpsk_sink", "w");
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (Init) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "Init", "bpsk_sink [Init exit execs]")


			/** state (Init) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "Init", "Idle")
				/*---------------------------------------------------------*/



			/** state (Idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "Idle", state1_enter_exec, "bpsk_sink [Idle enter execs]")
				FSM_PROFILE_SECTION_IN ("bpsk_sink [Idle enter execs]", state1_enter_exec)
				{
				int i;
				for (i = 0; i<256; i++)
					{
					temp_array[i] = op_dist_outcome(dist_ptr);
					}
				fwrite(temp_array, sizeof (int), 256, fptr);
				fclose(fptr);
				}
				FSM_PROFILE_SECTION_OUT (state1_enter_exec)

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"bpsk_sink")


			/** state (Idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "Idle", "bpsk_sink [Idle exit execs]")


			/** state (Idle) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "Idle", "Pk_Arrived")
				/*---------------------------------------------------------*/



			/** state (Pk_Arrived) enter executives **/
			FSM_STATE_ENTER_FORCED (2, "Pk_Arrived", state2_enter_exec, "bpsk_sink [Pk_Arrived enter execs]")
				FSM_PROFILE_SECTION_IN ("bpsk_sink [Pk_Arrived enter execs]", state2_enter_exec)
				{
				op_prg_text_output("sink: %lf", op_dist_outcome(dist_ptr));
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** state (Pk_Arrived) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "Pk_Arrived", "bpsk_sink [Pk_Arrived exit execs]")


			/** state (Pk_Arrived) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "Pk_Arrived", "Idle")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"bpsk_sink")
		}
	}




void
bpsk_sink_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
bpsk_sink_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

#if !defined (VOSD_NO_FIN)
	int _op_block_origin = __LINE__;
#endif

	FIN_MT (bpsk_sink_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc_MT (OP_SIM_CONTEXT_THREAD_INDEX_COMMA pr_state_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in bpsk_sink_svar function. */
#undef dist_ptr

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
bpsk_sink_init (int * init_block_ptr)
	{

#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (bpsk_sink_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (bpsk_sink)",
		sizeof (bpsk_sink_state));
	*init_block_ptr = 0;

	FRET (obtype)
	}

VosT_Address
bpsk_sink_alloc (VOS_THREAD_INDEX_ARG_COMMA VosT_Obtype obtype, int init_block)
	{

#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	bpsk_sink_state * ptr;
	FIN_MT (bpsk_sink_alloc (obtype))

	ptr = (bpsk_sink_state *)Vos_Alloc_Object_MT (VOS_THREAD_INDEX_COMMA obtype);
	if (ptr != OPC_NIL)
		ptr->_op_current_block = init_block;
	FRET ((VosT_Address)ptr)
	}



void
bpsk_sink_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	bpsk_sink_state		*prs_ptr;

	FIN_MT (bpsk_sink_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (bpsk_sink_state *)gen_ptr;

	if (strcmp ("dist_ptr" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->dist_ptr);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

