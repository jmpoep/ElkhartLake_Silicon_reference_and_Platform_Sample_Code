@REM This file contains a 'Sample Driver' and is licensed as such
@REM under the terms of your license agreement with Intel or your
@REM vendor.  This file may be modified by the user, subject to
@REM the additional terms of the license agreement
@REM
@REM
@REM
@REM Copyright (c) 2011 - 2016, Intel Corporation. All rights reserved.
@REM This software and associated documentation (if any) is furnished
@REM under a license and may only be used or copied in accordance
@REM with the terms of the license. Except as permitted by such
@REM license, no part of this software or documentation may be
@REM reproduced, stored in a retrieval system, or transmitted in any
@REM form or by any means without the express written consent of
@REM Intel Corporation.

@setlocal
@set MODULES=encodings.cp437,encodings.gbk,encodings.utf_16,encodings.utf_8,encodings.utf_16_le,encodings.latin_1,encodings.ascii

if not defined PYTHON_FREEZER_PATH (
  @echo.
  @echo !!! ERROR !!! PYTHON_FREEZER_PATH is not defined. !!!
  @echo.
  @goto end
  )

if exist %PYTHON_FREEZER_PATH%\cxfreeze (
  @rem Using cx_Freeze 4.2.3 with Python 2.7.3
  @set FREEZE=%PYTHON_FREEZER_PATH%\cxfreeze
  )

if exist %PYTHON_FREEZER_PATH%\FreezePython.exe (
  @rem Using cx_Freeze 3.0.3 with Python 2.5.4
  @set FREEZE=%PYTHON_FREEZER_PATH%\FreezePython.exe
  )

if not defined FREEZE (
  @echo.
  @echo !!! ERROR !!! Freeze Tool is not installed. !!!
  @echo.
  @goto end
  )

@del *.pyd
@del *.dll
@del *.exe
%FREEZE% --include-modules=%MODULES% --install-dir=. UniTool.py

:end