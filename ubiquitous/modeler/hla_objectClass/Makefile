all: controller_tutorial.exe 
controller_tutorial.obj : controller_tutorial.cpp
    cl /nologo /c /Zi /GX /GR /DHOST_PC_INTEL_WIN32 /DRTI_USES_STD_FSTREAM /DDT_USE_DLL /DSIMC_HLA_DLLEXPORT /Focontroller_tutorial.obj controller_tutorial.cpp
s_hla_stream.obj : s_hla_stream.cpp
    cl /nologo /c /Zi /GX /GR /DHOST_PC_INTEL_WIN32 /DRTI_USES_STD_FSTREAM /DDT_USE_DLL /DSIMC_HLA_DLLEXPORT /I%RTI_HOME%\%RTI_BUILD_TYPE%\include /Fos_hla_stream.obj s_hla_stream.cpp
controller_tutorial.exe: controller_tutorial.obj s_hla_stream.obj 
    cl /nologo /MD /Zi /GX /GR /Fecontroller_tutorial.exe controller_tutorial.obj s_hla_stream.obj /link libRTI-NG.lib libfedtime.lib wsock32.lib
