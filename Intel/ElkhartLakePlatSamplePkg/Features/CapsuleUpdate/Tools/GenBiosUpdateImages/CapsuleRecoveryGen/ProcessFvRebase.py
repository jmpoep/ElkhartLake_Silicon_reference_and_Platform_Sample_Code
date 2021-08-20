## @ ProcessFvRebase.py
#
#@copyright
#  INTEL CONFIDENTIAL
#  Copyright 2018 Intel Corporation.
#
#  The source code contained or described herein and all documents related to the
#  source code ("Material") are owned by Intel Corporation or its suppliers or
#  licensors. Title to the Material remains with Intel Corporation or its suppliers
#  and licensors. The Material may contain trade secrets and proprietary and
#  confidential information of Intel Corporation and its suppliers and licensors,
#  and is protected by worldwide copyright and trade secret laws and treaty
#  provisions. No part of the Material may be used, copied, reproduced, modified,
#  published, uploaded, posted, transmitted, distributed, or disclosed in any way
#  without Intel's prior express written permission.
#
#  No license under any patent, copyright, trade secret or other intellectual
#  property right is granted to or conferred upon you by disclosure or delivery
#  of the Materials, either expressly, by implication, inducement, estoppel or
#  otherwise. Any license under such intellectual property rights must be
#  express and approved by Intel in writing.
#
#  Unless otherwise agreed by Intel in writing, you may not remove or alter
#  this notice or any other notice embedded in Materials by Intel or
#  Intel's suppliers or licensors in any way.
#
#  This file contains a 'Sample Driver' and is licensed as such under the terms
#  of your license agreement with Intel or your vendor. This file may be modified
#  by the user, subject to the additional terms of the license agreement.
#
# @par Specification Reference:
#

import os
import sys
import re
import subprocess

if len(sys.argv) != 9:
  print "ProcessFvRebase.py - Error in number of arguments received"
  print "Usage - ProcessFvRebase.py <Command - FSP/FV> <working Folder> <input file name> <output file name> <FlashMap file path> <CAP file path> <Build Target - DEBUG/RELEASE> <rebase tool path>"
  exit(1)

subCommand        = sys.argv[1].upper()
workPath          = sys.argv[2]
inputFileName     = sys.argv[3]
outputFileName    = sys.argv[4]
flashMapName      = sys.argv[5]
capFileName       = sys.argv[6]
buildTarget       = sys.argv[7].upper()
rebaseTool        = sys.argv[8]

#
# Make sure argument passed or valid
#
if not (subCommand in "FSP" or subCommand in "FV") :
  print "WARNING!  " + str(subCommand) + " is not a valid command"
  exit(1)
if not (buildTarget in "DEBUG" or buildTarget in "RELEASE") :
  print "WARNING!  " + str(buildTarget) + " is not a valid build target"
  exit(1)
if not os.path.exists(flashMapName):
  print "WARNING!  " + str(flashMapName) + " is not found."
  exit(1)
if not os.path.exists(capFileName):
  print "WARNING!  " + str(capFileName) + " is not found."
  exit(1)
if not os.path.exists(rebaseTool):
  print "WARNING!  " + str(rebaseTool) + " is not found."
  exit(1)
BinFilePath = workPath + "\\" + inputFileName
if not os.path.exists(BinFilePath):
  print "WARNING!  " + str(BinFilePath) + " is not found."
  exit(1)

#
# Get the FSP-S / FSP-M-T FV Base Address from Flash Map
#
file = open (flashMapName, "r")
data = file.read ()

# Get the Flash Base Address
flashBase = long(data.split("FLASH_BASE")[1].split("=")[1].split()[0], 16)

# Based on Build Target, select the section in the FlashMap file
if buildTarget in "DEBUG":
  flashmap = data.rsplit("!if $(TARGET) == DEBUG", 1)[1].split("!else")[0]
else:
  flashmap = data.rsplit("!else", 1)[1]

# Get FSP-S & FSP-M-T offset & calculate the base
for line in flashmap.split("\n"):
  if "PcdFlashFvFspmtOffset" in line:
    fspTBaseOffset = long(line.split("=")[1].split()[0], 16)
  if "PcdFlashFvRecovery2Offset" in line:
    FvRecovery2Offset = long(line.split("=")[1].split()[0], 16)
file.close()

#
# Get the Fault tolerance related data
#
file = open (capFileName, "r")
data = file.read ()
faultToleranceOffset = long(data.split("PcdFaultToleranceOffset")[1].split("=")[1].split()[0], 16)
file.close()

print ("ProcessFvRebase!  faultToleranceOffset = %s" % (hex(faultToleranceOffset).rstrip("L")) )

#
# Get FSP-T Size, in order to calculate the FSP-M Base. Used SplitFspBin.py script
# to dump the header, and get the ImageSize of FSP-T section
#
if "PYTHON_HOME" in os.environ:
  PythonHome = os.environ['PYTHON_HOME']
  PythonPath = PythonHome + "\\" + "Python.exe"
else:
  PythonPath = sys.executable

if subCommand == 'FSP' :
    #python FvRebase.py rebase -f FspMt.rom -c t m -b 0xFFA40000 0xFFA4A000 -n fspmt_new.rom

    Process = subprocess.Popen(PythonPath + " "+ rebaseTool + " info -f" + BinFilePath, stdout=subprocess.PIPE)
    Output = Process.communicate()[0]
    FsptInfo = Output.rsplit("FSP_T", 1);
    for line in FsptInfo[1].split("\n"):
        if "ImageSize" in line:
            fspTSize = long(line.split("=")[1], 16)
            break

    # Calculate FSP-S/M/T base address, to which re-base has to be done. Note: FSP-M will be below FSP-T, to get the benefit of cache for low LLC SKU
    fspTBaseAddress = flashBase + fspTBaseOffset
    fspMBaseAddress = flashBase + fspTBaseOffset + fspTSize

    print ("ProcessFvRebase!  BinFilePath = %s" % (BinFilePath) )
    print ("ProcessFvRebase!  fspTBaseAddress = %s, fspMBaseAddress = %s" % (hex(fspTBaseAddress).rstrip("L"), hex(fspMBaseAddress).rstrip("L")) )

    fspTBaseAddress = fspTBaseAddress - faultToleranceOffset
    fspMBaseAddress = fspMBaseAddress - faultToleranceOffset

    print ("ProcessFvRebase!  new fspTBaseAddress = %s, new fspMBaseAddress = %s" % (hex(fspTBaseAddress).rstrip("L"), hex(fspMBaseAddress).rstrip("L")) )

    #
    # Re-base FSP bin file to new address and save it as fspBinFileRebased using SplitFspBin.py
    #
    rebaseArguments = BinFilePath + " -c t m -b " + str(hex(fspTBaseAddress).rstrip("L")) + " " + str(hex(fspMBaseAddress).rstrip("L")) + " -o" + workPath + " -n " + outputFileName
    os.system(PythonPath + " "+ rebaseTool + " rebase -f" + rebaseArguments)

elif subCommand == 'FV':

    FvRecovery2BaseAdress = flashBase + FvRecovery2Offset
    NewFvRecovery2BaseAdress = FvRecovery2BaseAdress - faultToleranceOffset
    print ("ProcessFvRebase!  FvRecovery2BaseAdress = %s, NewFvRecovery2BaseAdress = %s" % (hex(FvRecovery2BaseAdress).rstrip("L"), hex(NewFvRecovery2BaseAdress).rstrip("L")) )

    #FvRebase.py rebaseFv -f Recovery2.rom -a 0xFFD50000 -b 0xFF910000 -n Recovery2_new.rom
    #
    # Re-base Fv Recovery2
    #
    rebaseArguments = BinFilePath + " -a " + str(hex(FvRecovery2BaseAdress).rstrip("L")) + " -b " + str(hex(NewFvRecovery2BaseAdress).rstrip("L")) + " -o" + workPath + " -n " + outputFileName
    os.system(PythonPath + " "+ rebaseTool + " rebaseFv -f" + rebaseArguments)

exit(0)
