@REM @file
@REM
@REM @copyright
@REM  INTEL CONFIDENTIAL
@REM  Copyright 2016 - 2017 Intel Corporation.
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

IF "%VS140COMNTOOLS%" == "" (
  call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\vsvars32.bat"
) ELSE (
  call "%VS140COMNTOOLS%\vsvars32.bat"
)

SET PERL_PATH="c:\Perl\bin"
PATH=%PATH%;%cd%\Build\Tools\Bin;%PERL_PATH%;%cd%\BUILD\TOOLS
cd %cd%\BUILD
cmd \c
