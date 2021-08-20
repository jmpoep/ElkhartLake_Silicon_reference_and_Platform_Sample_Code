@REM @file
@REM
@REM @copyright
@REM  INTEL CONFIDENTIAL
@REM  Copyright 2013 - 2017 Intel Corporation.
@REM
@REM  The source code contained or described herein and all documents related to the
@REM  source code ("Material") are owned by Intel Corporation or its suppliers or
@REM  licensors. Title to the Material remains with Intel Corporation or its suppliers
@REM  and licensors. The Material may contain trade secrets and proprietary and
@REM  confidential information of Intel Corporation and its suppliers and licensors,
@REM  and is protected by worldwide copyright and trade secret laws and treaty
@REM  provisions. No part of the Material may be used, copied, reproduced, modified,
@REM  published, uploaded, posted, transmitted, distributed, or disclosed in any way
@REM  without Intel's prior express written permission.
@REM
@REM  No license under any patent, copyright, trade secret or other intellectual
@REM  property right is granted to or conferred upon you by disclosure or delivery
@REM  of the Materials, either expressly, by implication, inducement, estoppel or
@REM  otherwise. Any license under such intellectual property rights must be
@REM  express and approved by Intel in writing.
@REM
@REM  Unless otherwise agreed by Intel in writing, you may not remove or alter
@REM  this notice or any other notice embedded in Materials by Intel or
@REM  Intel's suppliers or licensors in any way.
@REM
@REM  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
@REM  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
@REM  the terms of your license agreement with Intel or your vendor. This file may
@REM  be modified by the user, subject to additional terms of the license agreement.
@REM
@REM @par Specification
@REM


IF "%1" == "2015" GOTO VS2015
IF "%1" == "2013" GOTO VS2013
IF "%1" == "2012" GOTO VS2012
IF "%1" == "2010" GOTO VS2010
IF "%1" == "2008" GOTO VS2008

:VS2015
REM We look for VS2015
IF NOT "%VS140COMNTOOLS%" == "" (
  IF EXIST "%VS140COMNTOOLS%\vsvars32.bat" (
    CALL "%VS140COMNTOOLS%\vsvars32.bat"
    GOTO PREPDONE
  )
)
IF NOT "%1" == "" GOTO FAILDONE

:VS2013
REM We look for VS2013
IF NOT "%VS120COMNTOOLS%" == "" (
  IF EXIST "%VS120COMNTOOLS%\vsvars32.bat" (
    CALL "%VS120COMNTOOLS%\vsvars32.bat"
    GOTO PREPDONE
  )
)
IF NOT "%1" == "" GOTO FAILDONE

:VS2012
REM We look for VS2012
IF NOT "%VS110COMNTOOLS%" == "" (
  IF EXIST "%VS110COMNTOOLS%\vsvars32.bat" (
    CALL "%VS110COMNTOOLS%\vsvars32.bat"
    GOTO PREPDONE
  )
)
IF NOT "%1" == "" GOTO FAILDONE

:VS2010
REM We look for VS2010
IF NOT "%VS100COMNTOOLS%" == "" (
  IF EXIST "%VS100COMNTOOLS%\vsvars32.bat" (
    CALL "%VS100COMNTOOLS%\vsvars32.bat"
    GOTO PREPDONE
  )
)
IF NOT "%1" == "" GOTO FAILDONE

:VS2008
REM We look for VS2008
IF NOT "%VS90COMNTOOLS%" == "" (
  IF EXIST "%VS90COMNTOOLS%\vsvars32.bat" (
    CALL "%VS90COMNTOOLS%\vsvars32.bat"
    GOTO PREPDONE
  )
)
IF NOT "%1" == "" GOTO FAILDONE

REM If environment variable VS*COMNTOOLS doesn't exist, try looking in default install locations.

REM We look for VS2015 running on Windows 7.
IF EXIST "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\vsvars32.bat" (
  CALL "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\vsvars32.bat"
  GOTO PREPDONE
)

REM We look for VS2015 running on Windows XP.
IF EXIST "C:\Program Files\Microsoft Visual Studio 14.0\Common7\Tools\vsvars32.bat" (
  CALL "C:\Program Files\Microsoft Visual Studio 14.0\Common7\Tools\vsvars32.bat"
  GOTO PREPDONE
)

REM We look for VS2013 running on Windows 7.
IF EXIST "C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\vsvars32.bat" (
  CALL "C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\vsvars32.bat"
  GOTO PREPDONE
)

REM We look for VS2013 running on Windows XP.
IF EXIST "C:\Program Files\Microsoft Visual Studio 12.0\Common7\Tools\vsvars32.bat" (
  CALL "C:\Program Files\Microsoft Visual Studio 12.0\Common7\Tools\vsvars32.bat"
  GOTO PREPDONE
)

REM We look for VS2012 running on Windows 7.
IF EXIST "C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat" (
  CALL "C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat"
  GOTO PREPDONE
)

REM We look for VS2012 running on Windows XP.
IF EXIST "C:\Program Files\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat" (
  CALL "C:\Program Files\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat"
  GOTO PREPDONE
)

REM We look for VS2010 running on Windows 7.
IF EXIST "C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\Tools\vsvars32.bat" (
  CALL "C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\Tools\vsvars32.bat"
  GOTO PREPDONE
)

REM We look for VS2010 running on Windows XP.
IF EXIST "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vsvars32.bat" (
  CALL "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vsvars32.bat"
  GOTO PREPDONE
)

REM We look for VS2008 running on Windows 7.
IF EXIST "C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\Tools\vsvars32.bat" (
  CALL "C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\Tools\vsvars32.bat"
  GOTO PREPDONE
)

REM We look for VS2008 running on Windows XP.
IF EXIST "C:\Program Files\Microsoft Visual Studio 9.0\Common7\Tools\vsvars32.bat" (
  CALL "C:\Program Files\Microsoft Visual Studio 9.0\Common7\Tools\vsvars32.bat"
  GOTO PREPDONE
)

:FAILDONE
@ECHO !!!!FAIL!!!! Unable to prepare to build mini BIOS. Can not find vsvars32.bat.
GOTO ALLDONE

:PREPDONE
SET PERL_PATH="C:\Perl\bin"
PATH=%PATH%;%cd%\Build\Tools\Bin;%PERL_PATH%;%cd%\BUILD\TOOLS
CD Build
@ECHO .
@ECHO Ready to build mini BIOS. Execute Build.bat to build or Cln.bat to remove built files.
@ECHO %CD%
@ECHO .

:ALLDONE
