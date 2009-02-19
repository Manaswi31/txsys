#VERBOSE = -verbose_mk

# OPNET 14.0 currently using:
# On Solaris: DMSO RTI 1.3NGv6 for SunPro 5 or MaK RTI 2.x or 3.x
# SunPro compilation options for controller
#CC=CC
#CONT_COMP_OS = -mt
#CONT_LIBS_OS = -lposix4

# On Linux: MaK RTI 2.x or 3.x
CC=cl
CONT_COMP_OS = -m32 -Wno-deprecated
CONT_LIBS_OS = 

CONT_COMP = -g $(CONT_COMP_OS) -DRTI_USES_STD_FSTREAM -DDT_USE_DLL

# built controller_tutorial
all: controller_tutorial 

# simulation is built using op_mksim 

# controller_tutorial uses s_hla_stream.s1_hlao for packing/unpacking
controller_tutorial: controller_tutorial.o s_hla_stream.o
	$(CC) -g $(CONT_COMP_OS) -o controller_tutorial controller_tutorial.o s_hla_stream.o -L$(RTI_HOME)/$(RTI_BUILD_TYPE)/lib -lRTI-NG -lfedtime $(CONT_LIBS_OS) -lpthread

controller_tutorial.o: controller_tutorial.cpp
	$(CC) -c $(CONT_COMP) -I$(RTI_HOME)/$(RTI_BUILD_TYPE)/include -o controller_tutorial.o controller_tutorial.cpp

s_hla_stream.o: s_hla_stream.cpp
	$(CC) -c $(CONT_COMP) -I. s_hla_stream.cpp -o s_hla_stream.o

clean:
	rm -f *.o *~ core *.s1.* *.ov *.a *.si.c *.pr.c controller_tutorial
