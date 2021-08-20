# @file
#  Makefile for Memory Reference Code (MRC) mini-BIOS.

#@copyright
#  Copyright (c) 2004 - 2019 Intel Corporation. All rights reserved.
#  This software and associated documentation (if any) is furnished
#  under a license and may only be used or copied in accordance
#  with the terms of the license. Except as permitted by such
#  license, no part of this software or documentation may be
#  reproduced, stored in a retrieval system, or transmitted in any
#  form or by any means without the express written consent of
#  Intel Corporation.
#
#  This file contains an 'Intel Peripheral Driver' and uniquely
#  identified as "Intel Reference Module" and is
#  licensed for Intel CPUs and chipsets under the terms of your
#  license agreement with Intel or your vendor.  This file may
#  be modified by the user, subject to additional terms of the
#  license agreement.

#--------------------------------------------------------------------
# A dummy pseudo-target just so it is the first in the file.
# Now, NMAKE is the same as NMAKE ALL. This is just for developer
# convenience, such that all source and object files appear at the
# top of this file for easy modification.
#--------------------------------------------------------------------
DUMMY: ALL

#--------------------------------------------------------------------
# Build flags
#--------------------------------------------------------------------
CREATE_OBJ32_OUTPUT       = 0
MRC_FLAG_BDAT_SUPPORT     = 1    # 0 - turn off BDAT support, 1 - turn on BDAT support
MEMORY_DOWN_SUPPORT       = 1    # 0 - turn off MEMORY_DOWN, 1 - turn on MEMORY_DOWN
ROM_SIZE                  = 1    # 1 - 1MB, 2 - 2MB
RELEASE                   = 0    # 0 - Disable compile optimizations, 1 - Enable compile optimizations
PCH_UART                  = 1    # 0 - Use Legacy Serial UART, 1 - Use PCH Serial UART

!IF "$(RELEASE)" == "1"
MRC_FLAG_DEBUG_MSG        = 0    # No debug messages in release build
!ELSE
MRC_FLAG_DEBUG_MSG        = 1    # Print MRC debug messages.
!ENDIF
#
# Project flags.  These change depending on the product and are only validated in the released setting.
# 0 - Remove project specific code.  1 - Enable project specific code.
#
ICL_FLAG_SUPPORT = 1
#
# Project flags End
#

#
# Combine all the flags into one variable.
#
MAKE_FLAGS  = MRC_FLAG_BDAT_SUPPORT=$(MRC_FLAG_BDAT_SUPPORT) MRC_FLAG_DEBUG_MSG=$(MRC_FLAG_DEBUG_MSG)
MAKE_FLAGS  = $(MAKE_FLAGS) MEMORY_DOWN_SUPPORT=$(MEMORY_DOWN_SUPPORT)
MAKE_FLAGS  = $(MAKE_FLAGS) RELEASE=$(RELEASE) ICL_FLAG_SUPPORT=$(ICL_FLAG_SUPPORT) PCH_UART=$(PCH_UART)

#--------------------------------------------------------------------
# Reference Code Object Files.
#--------------------------------------------------------------------

MRCLINK32OBJS = \
        $(OUT32DIR)\mrc.lib \
        $(OUT32DIR)\spd.lib

OEMLINK32OBJS = \
        $(OUT32DIR)\MrcOemPlatform.obj \
        $(OUT32DIR)\MrcSetup.obj \
        $(OUT32DIR)\Io.obj \
        $(OUT32DIR)\MemoryUtils.obj \
        $(OUT32DIR)\Smb.obj \
        $(OUT32DIR)\PostCodeSpi.obj \
!IF "$(PCH_UART)" == "1"
        $(OUT32DIR)\GpioLib.obj \
        $(OUT32DIR)\GpioNativeLib.obj \
        $(OUT32DIR)\GpioNativePrivateLib.obj \
#        $(OUT32DIR)\GpioNativePrivateLibIcl.obj \
        $(OUT32DIR)\GpioNativePrivateLibVer3.obj \
        $(OUT32DIR)\GpioPrivateLib.obj \
#        $(OUT32DIR)\GpioPrivateLibIcl.obj \
        $(OUT32DIR)\GpioPrivateLibVer3.obj \
        $(OUT32DIR)\PchInfoLibIcl.obj \
        $(OUT32DIR)\PchPcrLib.obj \
        $(OUT32DIR)\PchPsfPrivateLib.obj \
        $(OUT32DIR)\PchPsfPrivateLibIcl.obj \
        $(OUT32DIR)\PchSerialIoLib.obj \
        $(OUT32DIR)\PchSerialIoLibIcl.obj \
        $(OUT32DIR)\PciSegmentLib.obj \
        $(OUT32DIR)\PeiDxeSmmPchSerialIoUartLib.obj \
!ENDIF
        $(OUT32DIR)\uart16550.obj \
        $(OUT32DIR)\spi.obj \

CPULINK32OBJS = \
        $(OUT32DIR)\crcstart.obj \
        $(OUT32DIR)\crcinit.obj \
        $(OUT32DIR)\crcsetup.obj \
        $(OUT32DIR)\crcoemhook.obj

LINK32OBJS = \
        $(OEMLINK32OBJS) \
        $(CPULINK32OBJS) \
        $(MRCLINK32OBJS)

#--------------------------------------------------------------------
# Some basic definitions.
#--------------------------------------------------------------------
ROOTPATH                 = ..
REFCODEDLLNAME           = BINITDLL
REFCODEBINARYNAME        = BIOSINIT
BIOSIMAGENAME            = BIOS

!IF "$(ROM_SIZE)" == "1"
REFCODEBASEADDRESS       = 0xfff00000
ROM_PADDING              = 983040       # 1MB minus 64KB
!ELSE
REFCODEBASEADDRESS       = 0xffe00000
ROM_PADDING              = 2031616      # 2MB minus 64KB
!ENDIF

REFCODEENTRYLABEL        = CrcSetup

#--------------------------------------------------------------------
# Directory Declarations
#--------------------------------------------------------------------
BUILDDIR                 = $(ROOTPATH)\BUILD
CPUDIR                   = $(ROOTPATH)\CPU
CPUSRC16DIR              = $(CPUDIR)\SRC16
CPUSRC32DIR              = $(CPUDIR)\SRC32
MRCSRC32DIR              = $(ROOTPATH)\MEMORY
OUT16DIR                 = $(ROOTPATH)\OUT16
OUT32DIR                 = $(ROOTPATH)\OUT32
TOOLSDIR                 = $(BUILDDIR)\TOOLS
FEPDIR                   = $(TOOLSDIR)\FepRestricted
PLACEPEDIR               = $(TOOLSDIR)\PlacePeRestricted

#--------------------------------------------------------------------
# Compiler and Linker Flags
#--------------------------------------------------------------------
LINK32                   = link
LINK32FLAGS              = /nologo /incremental:no /align:32 /nodefaultlib /subsystem:console /opt:ref \
                           /merge:.rdata=.data /entry:$(REFCODEENTRYLABEL)  /pdb:$(OUT32DIR)\$(REFCODEDLLNAME).pdb \
                           /map:$(OUT32DIR)\$(REFCODEDLLNAME).map /out:$(OUT32DIR)\$(REFCODEDLLNAME).bin /DLL /ORDER:@LINKORDER.TXT
!IF "$(RELEASE)" == "1"
!ELSE
LINK32FLAGS = $(LINK32FLAGS) /debug
!ENDIF

#--------------------------------------------------------------------
# All the targets...
#--------------------------------------------------------------------
ALL:    TARGETDIRECTORIES BUILDBIN BIOS_IMAGE

TARGETDIRECTORIES:
        @echo MKDIRing Target Directories...
        @if not exist $(OUT32DIR) mkdir $(OUT32DIR)
        @if not exist $(OUT16DIR) mkdir $(OUT16DIR)
        @if not exist $(TOOLSDIR)\Bin mkdir $(TOOLSDIR)\Bin

BINS16BIT:
        @echo Invoking build for 16-bit CPU RC...
        @cd $(CPUSRC16DIR)
        @nmake /nologo /f CpuRc16.mak
        @cd ..\$(BUILDDIR)

REFCODEBINARY:
        @echo Invoking build for MRC...
        @cd $(MRCSRC32DIR)
        @nmake /nologo /f MiniMrc.mak $(MAKE_FLAGS)
        @cd $(BUILDDIR)

        @echo Invoking build for 32-bit CPU RC...
        @cd $(CPUSRC32DIR)
        @nmake /nologo /f CpuRc32.mak CONFIG=$(CONFIG) ROM_SIZE=$(ROM_SIZE)
        @cd ..\$(BUILDDIR)

#--------------------------------------------------------------------
# BIOS_IMAGE
#--------------------------------------------------------------------
BIOS_IMAGE: $(BIOSIMAGENAME).BIN
    -@echo BIOS_IMAGE completed...

MAKEPE: $(OUT32DIR)\$(REFCODEDLLNAME).BIN
    -@echo MAKEPE completed...

$(OUT32DIR)\$(REFCODEDLLNAME).BIN: REFCODEBINARY
    @Echo Make PE...
    @echo Linking all 32-bit Modules into one BIOS Module...
    -@copy <<file1 linkorder.txt
CrcSetup
<<nokeep
    $(LINK32) $(LINK32FLAGS) $(LINK32OBJS)
    -@if exist linkorder.txt erase linkorder.txt

FINDPEENTRY:
    $(TOOLSDIR)\Bin\FindEntryPoint $(OUT32DIR)\$(REFCODEDLLNAME).EFI > $(OUT16DIR)\peentry.inc

PLACEPE:
    copy $(OUT32DIR)\$(REFCODEDLLNAME).BIN $(OUT32DIR)\$(REFCODEBINARYNAME).BIN
    $(TOOLSDIR)\Bin\PlacePE $(OUT32DIR)\$(REFCODEDLLNAME).BIN $(OUT32DIR)\$(REFCODEBINARYNAME).BIN $(REFCODEBASEADDRESS)
    if exist $(OUT32DIR)\$(REFCODEDLLNAME).EFI del $(OUT32DIR)\$(REFCODEDLLNAME).EFI
    ren $(OUT32DIR)\$(REFCODEBINARYNAME).BIN $(REFCODEDLLNAME).EFI

$(BIOSIMAGENAME).BIN: MAKEPE PLACEPE FINDPEENTRY BINS16BIT
    @echo Concatenating 32-bit binaries...
    copy /y /b $(OUT32DIR)\$(REFCODEDLLNAME).EFI $(OUT32DIR)\padded.bin
    fwpad.exe $(OUT32DIR)\padded.bin $(ROM_PADDING)
    copy /y /b $(OUT32DIR)\padded.bin + $(OUT16DIR)\f000.bin ..\..\$(BIOSIMAGENAME).BIN
!IF "$(CREATE_OBJ32_OUTPUT)" == "1"
    perl $(TOOLSDIR)\Bin2Obj32\Bin2Obj32.pl $(BIOSIMAGENAME).BIN $(BIOSIMAGENAME).OBJ
!ENDIF
    @if exist padded.bin del padded.bin
    @echo ----------------------------------------------------------
    @echo BUILD COMPLETE
    @echo BIOS Image File....................: $(BIOSIMAGENAME).BIN
    @echo Reference Code Image File..........: $(OUT32DIR)\$(REFCODEDLLNAME).EFI
    @echo ----------------------------------------------------------
    @echo Entry point into Reference Code:
    @$(TOOLSDIR)\Bin\FindEntryPoint $(OUT32DIR)\$(REFCODEDLLNAME).EFI
    @echo ----------------------------------------------------------
    -@findstr /b /i /r "[0-9]*[,][0-9]*[,][0-9]*[,][0-9].*ICL" ..\..\LibraryPrivate\PeiMemoryInitLib\Source\Include\MrcVersion.h

#--------------------------------------------------------------------
# CLEAN
#--------------------------------------------------------------------
CLEAN:  CLEANTOOLS CLEANMRC
    -@echo  Deleting $(BIOSIMAGENAME).BIN
    -@if exist ..\..\$(BIOSIMAGENAME).BIN erase ..\..\$(BIOSIMAGENAME).BIN

    -@echo  Deleting $(BIOSIMAGENAME).OBJ
    -@if exist $(BIOSIMAGENAME).OBJ erase $(BIOSIMAGENAME).OBJ

    -@echo  Deleting build.log
    -@if exist build.log erase build.log

    -@if exist ..\..\Restricted\MrcVisualStudio\VS2015\.vs              rmdir /s /q ..\..\Restricted\MrcVisualStudio\VS2015\.vs
    -@if exist ..\..\Restricted\MrcVisualStudio\VS2015\Debug            rmdir /s /q ..\..\Restricted\MrcVisualStudio\VS2015\Debug
    -@if exist ..\..\Restricted\MrcVisualStudio\VS2015\StubMrc\Debug    rmdir /s /q ..\..\Restricted\MrcVisualStudio\VS2015\StubMrc\Debug
    -@if exist ..\..\Restricted\MrcVisualStudio\VS2015\StubServer\Debug rmdir /s /q ..\..\Restricted\MrcVisualStudio\VS2015\StubServer\Debug
    -@if exist ..\..\Restricted\MrcVisualStudio\VS2015\StubMrc\IntOutputSave.bin     del ..\..\Restricted\MrcVisualStudio\VS2015\StubMrc\IntOutputSave.bin
    -@if exist ..\..\Restricted\MrcVisualStudio\VS2015\StubMrc\MrcDataCsvFile.csv    del ..\..\Restricted\MrcVisualStudio\VS2015\StubMrc\MrcDataCsvFile.csv
    -@if exist ..\..\Restricted\MrcVisualStudio\VS2015\StubMrc\MrcParametersSave.bin del ..\..\Restricted\MrcVisualStudio\VS2015\StubMrc\MrcParametersSave.bin
    -@if exist ..\..\Restricted\MrcVisualStudio\VS2015\StubMrc\train.log             del ..\..\Restricted\MrcVisualStudio\VS2015\StubMrc\train.log
    -@if exist ..\..\Restricted\MrcVisualStudio\VS2015\StubMrc\train_clean.log       del ..\..\Restricted\MrcVisualStudio\VS2015\StubMrc\train_clean.log

CLEANMRC:
    @cd $(CPUSRC16DIR)
    @nmake /nologo /f CpuRc16.mak clean
    @cd ..\$(BUILDDIR)

    @cd $(CPUSRC32DIR)
    @nmake /nologo /f CpuRc32.mak clean CONFIG=$(CONFIG)
    @cd ..\$(BUILDDIR)

    @cd $(MRCSRC32DIR)
    @nmake /nologo /f MiniMrc.mak clean
    @cd $(BUILDDIR)

#--------------------------------------------------------------------
# Tools, tools, tools. Add your new tools, if any, below this.
# Remember to copy tool into $(TOOLSDIR)\Bin as the last step!
#--------------------------------------------------------------------
BUILDBIN:
    @if not exist $(TOOLSDIR)\Bin\7z.dll      copy $(TOOLSDIR)\BinRestricted\7z.dll      $(TOOLSDIR)\Bin
    @if not exist $(TOOLSDIR)\Bin\7z.exe      copy $(TOOLSDIR)\BinRestricted\7z.exe      $(TOOLSDIR)\Bin
    @if not exist $(TOOLSDIR)\Bin\exe2bin.exe copy $(TOOLSDIR)\BinRestricted\exe2bin.exe $(TOOLSDIR)\Bin
    @if not exist $(TOOLSDIR)\Bin\h2inc.err   copy $(TOOLSDIR)\BinRestricted\h2inc.err   $(TOOLSDIR)\Bin
    @if not exist $(TOOLSDIR)\Bin\h2inc.exe   copy $(TOOLSDIR)\BinRestricted\h2inc.exe   $(TOOLSDIR)\Bin
    @if not exist $(TOOLSDIR)\Bin\link16.exe  copy $(TOOLSDIR)\BinRestricted\link16.exe  $(TOOLSDIR)\Bin

BUILDFEP: $(TOOLSDIR)\Bin\FindEntryPoint.exe

$(TOOLSDIR)\Bin\FindEntryPoint.exe: $(FEPDIR)\Release\FindEntryPoint.exe

$(FEPDIR)\Release\FindEntryPoint.exe:
    @echo Making $(TOOLSDIR)\Bin\FindEntryPoint.exe...
    -@cd $(FEPDIR)
    @if exist FindEntryPoint.mak nmake /nologo /f FindEntryPoint.mak CFG="FindEntryPoint - Win32 Release"
    -@cd ..\..\$(BUILDDIR)
    -@copy $(TOOLSDIR)\FindEntryPoint.exe $(TOOLSDIR)\Bin\.
    -@copy $(FEPDIR)\Release\FindEntryPoint.exe $(TOOLSDIR)\Bin\.

BUILDPLACEPE: $(TOOLSDIR)\Bin\PlacePE.exe

$(TOOLSDIR)\Bin\PlacePE.exe: $(PLACEPEDIR)\Release\PlacePE.exe

$(PLACEPEDIR)\Release\PlacePE.exe:
    @echo Making $(TOOLSDIR)\Bin\PlacePE.exe...
    -@cd $(PLACEPEDIR)
    @if exist PlacePE.mak nmake /nologo /f PlacePE.mak CFG="PLACEPE - Win32 Release"
    -@cd ..\..\$(BUILDDIR)
    -@copy $(TOOLSDIR)\PlacePE.exe $(TOOLSDIR)\Bin\.
    -@copy $(PLACEPEDIR)\Release\PlacePE.exe $(TOOLSDIR)\Bin\.

#--------------------------------------------------------------------
# To clean tools, call .MAK file of each tool with "clean" parameter.
# Remember to enter the tool source directory before and cd..\.. after!
#--------------------------------------------------------------------
CLEANTOOLS:
    @if exist $(TOOLSDIR)\Bin\7z.dll      del $(TOOLSDIR)\Bin\7z.dll
    @if exist $(TOOLSDIR)\Bin\7z.exe      del $(TOOLSDIR)\Bin\7z.exe
    @if exist $(TOOLSDIR)\Bin\exe2bin.exe del $(TOOLSDIR)\Bin\exe2bin.exe
    @if exist $(TOOLSDIR)\Bin\h2inc.err   del $(TOOLSDIR)\Bin\h2inc.err
    @if exist $(TOOLSDIR)\Bin\h2inc.exe   del $(TOOLSDIR)\Bin\h2inc.exe
    @if exist $(TOOLSDIR)\Bin\link16.exe  del $(TOOLSDIR)\Bin\link16.exe

    -@cd $(FEPDIR)
    @if exist FindEntryPoint.mak nmake /nologo /f FindEntryPoint.mak CFG="FindEntryPoint - Win32 Release" clean
    -@attrib -r Release /S > nul
    -@rd Release /S /Q > nul
    -@cd ..\..\$(BUILDDIR)

    -@cd $(PLACEPEDIR)
    @if exist $(PLACEPEDIR) nmake /nologo /f PlacePE.mak CFG="PLACEPE - Win32 Release" clean
    -@attrib -r Release /S > nul
    -@rd Release /S /Q > nul
    -@cd ..\..\$(BUILDDIR)
