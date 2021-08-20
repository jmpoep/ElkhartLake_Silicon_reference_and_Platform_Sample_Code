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
# Some basic definitions.
#--------------------------------------------------------------------
ROOTPATH                                = ..\..
BINARYNAME                              = CRCPM32

#--------------------------------------------------------------------
# Directory Declarations
#--------------------------------------------------------------------
CPUSRC16DIR=$(ROOTPATH)\CPU\SRC16
OUT16DIR=$(ROOTPATH)\OUT16
TOOLSDIR=$(ROOTPATH)\BUILD\TOOLS

#--------------------------------------------------------------------
# Assembler, Compiler and Linker Flags
#--------------------------------------------------------------------
H2INC           = $(TOOLSDIR)\bin\h2inc
H2INCFLAGS      = /C /Zp1 /WIN32 /nologo

AS              = ml
A16FLAGS        = /nologo /Zp1 /Sa /c /omf /I$(OUT16DIR) /Fo"$(OUT16DIR)\\" /Fl"$(OUT16DIR)\\"

LINK16          = $(TOOLSDIR)\bin\LINK16.EXE
LINK16FLAGS     = /nologo /MAP

TOBINARY        = $(TOOLSDIR)\bin\EXE2BIN.EXE

#--------------------------------------------------------------------
# Inference Rules
#--------------------------------------------------------------------
{$(CPUSRC16DIR)}.asm{$(OUT16DIR)}.obj:
        $(AS) $(A16FLAGS) $<

{$(OUT16DIR)}.obj{$(OUT16DIR)}.exe:
        $(LINK16) $(LINK16FLAGS) $(LINK16OBJS), $(OUT16DIR)\$(BINARYNAME).EXE, $(OUT16DIR)\$(BINARYNAME).MAP;

{$(OUT16DIR)}.exe{$(OUT16DIR)}.bin:
        $(TOBINARY) $(OUT16DIR)\$(BINARYNAME).EXE $(OUT16DIR)\$(BINARYNAME).BIN

#--------------------------------------------------------------------
# Object File Dependencies List
#--------------------------------------------------------------------

LINK16OBJS      =       $(OUT16DIR)\crcpm32.obj

LINK16DEPS      =


#--------------------------------------------------------------------
# All the targets...
#--------------------------------------------------------------------
ALL:    TARGETDIRECTORIES BINS16BIT

TARGETDIRECTORIES:
        @echo MKDIRing Target Directories...
        @if not exist $(OUT16DIR) mkdir $(OUT16DIR)

BINS16BIT: $(LINK16DEPS) $(LINK16OBJS) LINK16EXE CREATEBINARY padin_f.txt
        fwpad.exe ..\..\out16\crcpm32.bin 65520 
#	copy /b ..\..\out16\crcpm32.bin+far_jump.bin ..\..\out16\F000.BIN
	copy /b ..\..\out16\crcpm32.bin+near_jump.bin ..\..\out16\F000.BIN

#
# We need this rule (although we have inference rule for asm->obj),
# because we have to recompile crcpm32.asm if PE entry point was changed.
# Actually peentry.inc is generated on every build, even if PE entry point
# is the same as before (possible place for optimization...)
#
$(OUT16DIR)\crcpm32.obj: $(CPUSRC16DIR)\crcpm32.asm $(OUT16DIR)\peentry.inc
        $(AS) $(A16FLAGS) $(CPUSRC16DIR)\crcpm32.asm
        
LINK16EXE:
        $(LINK16) $(LINK16FLAGS) $(LINK16OBJS), $(OUT16DIR)\$(BINARYNAME).EXE, $(OUT16DIR)\$(BINARYNAME).MAP;

CREATEBINARY:
        $(TOBINARY) $(OUT16DIR)\$(BINARYNAME).EXE $(OUT16DIR)\$(BINARYNAME).BIN

CLEAN:
        -@echo  Removing directory $(OUT16DIR)
        -@if exist $(OUT16DIR) rd $(OUT16DIR) /S /Q
