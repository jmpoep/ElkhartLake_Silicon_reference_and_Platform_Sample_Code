# @file
#  Makefile for Memory Reference Code (MRC) mini-BIOS.

#@copyright
#  Copyright (c) 2004 - 2018 Intel Corporation. All rights reserved.
#  This software and associated documentation (if any) is furnished
#  under a license and may only be used or copied in accordance
#  with the terms of the license. Except as permitted by such
#  license, no part of this software or documentation may be
#  reproduced, stored in a retrieval system, or transmitted in any
#  form or by any means without the express written consent of
#  Intel Corporation.

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
# Memory Reference Code Object Files.
#--------------------------------------------------------------------

MRC_CPGC20_OBJ = \
        $(OUT32DIR)\Cpgc20Patterns.obj \
        $(OUT32DIR)\Cpgc20TestCtl.obj

MRC_CPGC_OBJ = \
        $(OUT32DIR)\MrcCpgcApi.obj \
        $(MRC_CPGC20_OBJ)

MRC_MEMORY_TYPES_OBJ = \
        $(OUT32DIR)\MrcDdrCommon.obj \
        $(OUT32DIR)\MrcLpddr5.obj \
        $(OUT32DIR)\MrcLpddr4.obj \
        $(OUT32DIR)\MrcDdr4.obj \
        $(OUT32DIR)\MrcMemoryApi.obj

MRC_CHIP_OBJ = \
        $(OUT32DIR)\MrcChipApi.obj

MRC_DDRIO_OBJ = \
        $(OUT32DIR)\MrcDdrIoConfig.obj

MRC_HAL_OBJ = \
        $(OUT32DIR)\MrcCpgcOffsets.obj \
        $(OUT32DIR)\MrcDdrIoOffsets.obj \
        $(OUT32DIR)\MrcHalRegisterAccess.obj \
        $(OUT32DIR)\MrcMcOffsets.obj \
        $(OUT32DIR)\MrcRegisterCache.obj

MRCLINK32OBJS = \
        $(OUT32DIR)\MrcBdat.obj \
        $(OUT32DIR)\MrcDebugPrint.obj \
        $(OUT32DIR)\MrcGeneral.obj \
        $(OUT32DIR)\MrcInterpreter.obj \
        $(OUT32DIR)\MrcMemoryScrub.obj \
        $(OUT32DIR)\MrcSaveRestore.obj \
        $(OUT32DIR)\MrcStartMemoryConfiguration.obj \
        $(OUT32DIR)\MrcAddressDecodeConfiguration.obj \
        $(OUT32DIR)\MrcMaintenance.obj \
        $(OUT32DIR)\MrcPowerModes.obj \
        $(OUT32DIR)\MrcRefreshConfiguration.obj \
        $(OUT32DIR)\MrcSchedulerParameters.obj \
        $(OUT32DIR)\MrcTimingConfiguration.obj \
        $(OUT32DIR)\MrcReadDqDqs.obj \
        $(OUT32DIR)\MrcReadReceiveEnable.obj \
        $(OUT32DIR)\MrcCommandTraining.obj \
        $(OUT32DIR)\MrcCommon.obj \
        $(OUT32DIR)\MrcCrosser.obj \
        $(OUT32DIR)\MrcDdr3.obj \
        $(OUT32DIR)\MrcGears.obj \
        $(OUT32DIR)\MrcIoControl.obj \
        $(OUT32DIR)\MrcMalloc.obj \
        $(OUT32DIR)\MrcMcConfiguration.obj \
        $(OUT32DIR)\MrcMemoryMap.obj \
        $(OUT32DIR)\MrcReset.obj \
        $(OUT32DIR)\MrcWriteDqDqs.obj \
        $(OUT32DIR)\MrcWriteLeveling.obj \
        $(MRC_CPGC_OBJ) \
        $(MRC_CHIP_OBJ) \
        $(MRC_DDRIO_OBJ) \
        $(MRC_HAL_OBJ) \
        $(MRC_MEMORY_TYPES_OBJ)

SPDLINK32OBJS = \
        $(OUT32DIR)\MrcSpdProcessing.obj

LINK32OBJS = \
        $(OUT32DIR)\MrcOemPlatform.obj \
        $(OUT32DIR)\MrcSetup.obj \
        $(OUT32DIR)\Io.obj \
        $(OUT32DIR)\MemoryUtils.obj \
        $(OUT32DIR)\Smb.obj \
!IF "$(PCH_UART)" == "1"
        $(OUT32DIR)\GpioLib.obj \
        $(OUT32DIR)\GpioNativeLib.obj \
        $(OUT32DIR)\GpioNativePrivateLib.obj \
        $(OUT32DIR)\GpioNativePrivateLibIcl.obj \
        $(OUT32DIR)\GpioPrivateLib.obj \
        $(OUT32DIR)\GpioPrivateLibIcl.obj \
        $(OUT32DIR)\PchPcrLib.obj \
        $(OUT32DIR)\PchPsfPrivateLib.obj \
        $(OUT32DIR)\PchPsfPrivateLibIcl.obj \
        $(OUT32DIR)\PchSerialIoLib.obj \
        $(OUT32DIR)\PchSerialIoLibIcl.obj \
        $(OUT32DIR)\PciSegmentLib.obj \
        $(OUT32DIR)\PeiDxeSmmPchSerialIoUartLib.obj \
!ENDIF
        $(OUT32DIR)\uart16550.obj \


#--------------------------------------------------------------------
# Some basic definitions.
#--------------------------------------------------------------------
ROOTPATH                = ..
MRC_ROOTPATH            = ..\..\LibraryPrivate\PeiMemoryInitLib
MRC_ROOT_INCLUDE        = ..\..\Include
MRC_COMMON              = ..\Common
MRC_MAIN                = $(MRC_ROOTPATH)\Source
MRC_API                 = $(MRC_MAIN)\Api
MRC_CHIP                = $(MRC_MAIN)\Chip
MRC_DDRIO               = $(MRC_CHIP)\DdrIo
MRC_CPGC_API            = $(MRC_MAIN)\Cpgc
MRC_CPGC20              = $(MRC_CPGC_API)\Cpgc20
MRC_HAL                 = $(MRC_MAIN)\Hal
MRC_INCLUDES            = $(MRC_MAIN)\Include
MRC_INCREGS             = $(MRC_MAIN)\Include\MrcRegisters
MRC_MEMORY_TYPES        = $(MRC_MAIN)\MemoryTypes
MRC_MC_INIT             = $(MRC_MAIN)\McConfiguration
MRC_READ_TRAINING       = $(MRC_MAIN)\ReadTraining
MRC_SERVICES            = $(MRC_MAIN)\Services
MRC_SPD_PROCESSING      = $(MRC_MAIN)\SpdProcessing
MRC_SSA                 = $(MRC_MAIN)\Ssa
MRC_SSA_INCLUDES        = $(MRC_MAIN)\Ssa\Include
MRC_WRITE_TRAINING      = $(MRC_MAIN)\WriteTraining

#
# Project Specific Paths.
#
MRC_INCLUDES_TGL                = $(MRC_INCREGS)\Tigerlake
#
#
#

#--------------------------------------------------------------------
# Directory Declarations
#--------------------------------------------------------------------
MRCSRC32DIR                     = $(ROOTPATH)\MEMORY
OUT32DIR                        = $(ROOTPATH)\OUT32
CPUSRC32DIR                     = $(ROOTPATH)\CPU\SRC32

#--------------------------------------------------------------------
# Inference Rules
#--------------------------------------------------------------------

{$(MRC_API)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_CHIP)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_DDRIO)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_COMMON)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_CPGC_API)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_CPGC20)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_HAL)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_MC_INIT)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_MEMORY_TYPES)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_READ_TRAINING)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_ROOTPATH)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_SERVICES)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_SPD_PROCESSING)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_WRITE_TRAINING)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRCSRC32DIR)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

#--------------------------------------------------------------------
# Compiler and Linker Flags
#--------------------------------------------------------------------
C = cl

#
# Warning Disables:
#   /wd4668 - "'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'"
#     Similar to -Wundef (http://msdn.microsoft.com/en-us/library/4dt9kyhy.aspx)
#
#   /wd5045 - Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
#     Warning C5045 lets you see what patterns in your code cause a Spectre mitigation, such as an LFENCE, to be inserted when the /Qspectre compiler option is specified.
#
CFLAGS = /Zp1 /Wall /WX /EHsc /GF /Gy /Gs262144 /c /Zi /MP /X /GS- /nologo /FAsc /wd4214 /wd4711 /wd4668 /wd5045

#
# Debug build:   compiler optimizations disabled
# Release build: compiler optimizations enabled
#
!IF "$(RELEASE)" == "1"
CFLAGS = $(CFLAGS) /O1ib2s
!ELSE
CFLAGS = $(CFLAGS) /Od
!ENDIF

CFLAGS = $(CFLAGS) /Fd$(OUT32DIR)\\ /Fo$(OUT32DIR)\\
CFLAGS = $(CFLAGS) /Fa$(OUT32DIR)\ASM\\ -I$(CPUSRC32DIR) -I$(MRCSRC32DIR) -I$(MRC_COMMON)
CFLAGS = $(CFLAGS) -I$(MRC_ROOT_INCLUDE) -I$(MRC_API) -I$(MRC_HAL) -I$(MRC_INCLUDES)
CFLAGS = $(CFLAGS) -I$(MRC_INCREGS) -I$(MRC_MC_INIT) -I$(MRC_READ_TRAINING) -I$(MRC_SERVICES) -I$(MRC_SPD_PROCESSING)
CFLAGS = $(CFLAGS) -I$(MRC_SSA) -I$(MRC_SSA_INCLUDES) -I$(MRC_WRITE_TRAINING) -I$(MRC_MEMORY_TYPES)
CFLAGS = $(CFLAGS) -I$(MRC_CPGC_API) -I$(MRC_CPGC20) -I$(MRC_CHIP) -I$(MRC_DDRIO)
CFLAGS = $(CFLAGS) -I$(MRC_ROOTPATH)
CFLAGS = $(CFLAGS) /DMRC_MINIBIOS_BUILD

#
# Project Specific CFLAGS: Defines and Include Path
#
!IF "$(TGL_FLAG_SUPPORT)" == "1"
CFLAGS = $(CFLAGS) /DTGL_FLAG  -I$(MRC_INCLUDES_TGL)
!ENDIF
#
# Project Specific CFLAGS End.
#

!IF "$(MRC_FLAG_DEBUG_MSG)" == "0"
CFLAGS = $(CFLAGS) /DMDEPKG_NDEBUG
!ENDIF

!IF "$(MRC_FLAG_BDAT_SUPPORT)" == "1"
CFLAGS = $(CFLAGS) /DBDAT_SUPPORT
!ENDIF

!IF "$(MEMORY_DOWN_SUPPORT)" == "1"
CFLAGS = $(CFLAGS) /DMEMORY_DOWN_SUPPORT=1
!ENDIF

!IF "$(PCH_UART)" == "1"
CFLAGS = $(CFLAGS) /DPCH_UART=1
!ENDIF

#--------------------------------------------------------------------
# Object File Dependencies List
#--------------------------------------------------------------------


#--------------------------------------------------------------------
# Library Flags
#--------------------------------------------------------------------
LIB = lib
LIBFLAGS =

#--------------------------------------------------------------------
# All the targets...
#--------------------------------------------------------------------
ALL:    TARGETDIRECTORIES $(LINK32OBJS) $(MRCLINK32OBJS) $(SPDLINK32OBJS)
        LIB $(LIBFLAGS) /OUT:$(OUT32DIR)\mrc.lib $(MRCLINK32OBJS)
        LIB $(LIBFLAGS) /OUT:$(OUT32DIR)\spd.lib $(SPDLINK32OBJS)

TARGETDIRECTORIES:
        @echo Creating Target Directories...
        @if not exist $(OUT32DIR) mkdir $(OUT32DIR)
        @if not exist $(OUT32DIR)\ASM mkdir $(OUT32DIR)\ASM

DEBUGSOURCE:
        @echo Copying $(MRCSRC32DIR) to $(OUT32DIR)
        @copy $(MRCSRC32DIR) $(OUT32DIR) > nul
        @echo MRC compilation end

CLEAN:
        -@echo  Removing directory $(OUT32DIR)
        -@if exist $(OUT32DIR) rd $(OUT32DIR) /S /Q

        -@echo Removing .obj, .pdb and .idb files in the $(MRCSRC32DIR) directory...
        -@if exist vc*.pdb               erase vc*.pdb
        -@if exist vc*.idb               erase vc*.idb
        -@if exist $(MRCSRC32DIR)\*.obj  erase $(MRCSRC32DIR)\*.obj
