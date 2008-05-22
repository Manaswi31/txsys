@echo off
REM
REM Batch file to build controller federate
REM

echo .
echo Building controller object file...
cl /nologo /c /Z7 /Od /GX /GR /DHOST_PC_INTEL_WIN32 /DRTI_USES_STD_FSTREAM /DDT_USE_DLL /DSIMC_HLA_DLLEXPORT /I"%RTI_HOME%\%RTI_BUILD_TYPE%\include" /Focontroller_tutorial.obj controller_tutorial.cpp
echo .
echo Building stream file for interaction parameters...
cl /nologo /c /Z7 /Od /GX /GR /DHOST_PC_INTEL_WIN32 /DRTI_USES_STD_FSTREAM /DDT_USE_DLL /DSIMC_HLA_DLLEXPORT /I. /Fos_hla_stream.obj s_hla_stream.cpp
echo .
echo Building controller executable...
cl /nologo /MD /GX /GR /Fecontroller_tutorial.exe controller_tutorial.obj s_hla_stream.obj /Zi /link libRTI-NG.lib libfedtime.lib wsock32.lib
echo .
