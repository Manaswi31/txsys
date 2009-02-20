all: controller_thru.exe 
controller_thru.exe: controller_thru.obj s_hla_stream.obj 
    cl /nologo /MD /Zi /GX /GR /Fecontroller_thru.exe controller_thru.obj s_hla_stream.obj /link libRTI-NG.lib libfedtime.lib wsock32.lib
controller_thru.obj : controller_thru.cpp
    cl /nologo /c /Zi /GX /GR /DHOST_PC_INTEL_WIN32 /DRTI_USES_STD_FSTREAM /DDT_USE_DLL /DSIMC_HLA_DLLEXPORT /I%RTI_HOME%\%RTI_BUILD_TYPE%\include /Focontroller_thru.obj controller_thru.cpp
s_hla_stream.obj : s_hla_stream.cpp
    cl /nologo /c /Zi /GX /GR /DHOST_PC_INTEL_WIN32 /DRTI_USES_STD_FSTREAM /DDT_USE_DLL /DSIMC_HLA_DLLEXPORT /I%RTI_HOME%\%RTI_BUILD_TYPE%\include /Fos_hla_stream.obj s_hla_stream.cpp
