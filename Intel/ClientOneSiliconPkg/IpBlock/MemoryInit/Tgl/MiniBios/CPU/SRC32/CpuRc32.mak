# @file
#  Makefile for Memory Reference Code (MRC) mini-BIOS.

#@copyright
#  Copyright (c) 2007 - 2013 Intel Corporation. All rights reserved.
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
DUMMY:  ALL

#--------------------------------------------------------------------
# Reference Code Object Files.
#--------------------------------------------------------------------
LINK32OBJS = \
  $(OUT32DIR)\crcstart.obj \
  $(OUT32DIR)\crcinit.obj \
  $(OUT32DIR)\crcsetup.obj \
  $(OUT32DIR)\crcoemhook.obj

#--------------------------------------------------------------------
# Some basic definitions.
#--------------------------------------------------------------------
ROOTPATH = ..\..

#--------------------------------------------------------------------
# Directory Declarations
#--------------------------------------------------------------------
CPUSRC32DIR = $(ROOTPATH)\CPU\SRC32
UCODEDIR    = $(ROOTPATH)\CPU\UCODE
MRCSRC32DIR = $(ROOTPATH)\MEMORY
OUT32DIR    = $(ROOTPATH)\OUT32
TOOLSDIR    = $(ROOTPATH)\BUILD\TOOLS

#--------------------------------------------------------------------
# Inference Rules
#--------------------------------------------------------------------

{$(CSIPLATFORMINCDIR)}.c{$(OUT32DIR)}.obj::
        $(C) $(CFLAGS) $<

{$(CSISRC32DIR)}.c{$(OUT32DIR)}.obj::
        $(C) $(CFLAGS) $<

{$(CPUSRC32DIR)}.c{$(OUT32DIR)}.obj::
        $(C) $(CFLAGS) $<

{$(CPUSRC32DIR)}.asm{$(OUT32DIR)}.obj:
        $(AS) $(A32FLAGS) $<

#--------------------------------------------------------------------
# Compiler and Linker Flags
#--------------------------------------------------------------------
C                = cl
CFLAGS           = /Zp1 /Wall /WX /EHsc /GF /Gy /Gs32768 /c /Zi /Gm /Od /X /GS- /nologo /FAs
CFLAGS           = $(CFLAGS) /Fd$(OUT32DIR)\\ /Fo$(OUT32DIR)\\ 
CFLAGS           = $(CFLAGS) /Fa$(OUT32DIR)\\-I. -I$(MRCSRC32DIR)
CFLAGS           = $(CFLAGS) -DCPU_RC_32_MAK
!IF "$(CONFIG)" != ""
CFLAGS           = $(CFLAGS) -D$(CONFIG)
!ELSE
CFLAGS           = $(CFLAGS) -DCONFIG_MEMORY -DCONFIG_CSI
!ENDIF

AS               = ml
A32FLAGS         = /nologo /Zp1 /Sa /c /coff /Zi /I$(OUT32DIR) /I$(UCODEDIR) 
A32FLAGS         = $(A32FLAGS) /Fo"$(OUT32DIR)\\" /Fl"$(OUT32DIR)\\"
!IF "$(CONFIG)" != ""
A32FLAGS         = $(A32FLAGS) -D$(CONFIG)
!ELSE
A32FLAGS         = $(A32FLAGS) -DCONFIG_MEMORY -DCONFIG_CSI -DROM_SIZE=$(ROM_SIZE)
!ENDIF
H2INC            = $(TOOLSDIR)\bin\h2inc
H2INCFLAGS       = /C /Zp1 /WIN32 /nologo -DCPU_RC_32_MAK

#--------------------------------------------------------------------
# Object File Dependencies List
#--------------------------------------------------------------------

LINKDEPS         = $(OUT32DIR)\crc.i 
#!IF "$(CONFIG)" != "CONFIG_CSI"
#LINKDEPS         = $(LINKDEPS) $(OUT32DIR)\ddrmrc.i 
#!ENDIF
#!IF "$(CONFIG)" != "CONFIG_MEMORY"
#LINKDEPS         = $(LINKDEPS) $(OUT32DIR)\csi.i
#!ENDIF

#--------------------------------------------------------------------
# All the targets...
#--------------------------------------------------------------------
ALL:    TARGETDIRECTORIES $(LINKDEPS) $(LINK32OBJS)

TARGETDIRECTORIES:
  @echo Creating Target Directories...
  @if not exist $(OUT32DIR) mkdir $(OUT32DIR)

DEBUGSOURCE:
  @echo Copying $(CPUSRC32DIR) to $(OUT32DIR)
  @copy $(CPUSRC32DIR) $(OUT32DIR) > nul

$(OUT32DIR)\crc.i: $(CPUSRC32DIR)\crc.h
  set _include=%include%
  set include=
  $(H2INC) $(H2INCFLAGS) /Fa$(OUT32DIR)\crc.i $(CPUSRC32DIR)\crc.h
  set _include=%include%
  set _include=

CLEAN:
  -@echo  Removing directory $(OUT32DIR)
  -@if exist $(OUT32DIR) rd $(OUT32DIR) /S /Q

  -@echo Removing .pdb and .idb files in the $(SRC32DIR) directory...
  -@if exist vc*.pdb  erase vc*.pdb
  -@if exist vc*.idb  erase vc*.idb
