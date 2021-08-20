## @ RebaseAndPatchFspBinBaseAddress.py
#
# Copyright (c) 2016 - 2017, Intel Corporation. All rights reserved.<BR>
# This program and the accompanying materials are licensed and made available under
# the terms and conditions of the BSD License that accompanies this distribution.
# The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php.
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
##
import os
import sys
import re
import subprocess

if len(sys.argv) != 7:
  print "RebaseAndPatchFspBinBaseAddress.py - Error in number of arguments received"
  print "Usage - RebaseAndPatchFspBinBaseAddress.py <Build Target - DEBUG/RELEASE> <FlashMap file path> <FspBinPkg Folder> <Fsp.fd file name> <Dsc file path to be patched> <pad_offset for Fsp-S Base Address>"
  exit(1)

buildTarget       = sys.argv[1].upper()
flashMapName      = sys.argv[2]
fspBinPath        = sys.argv[3]
fspBinFile        = sys.argv[4]
targetDscFile     = sys.argv[5]
fvOffset          = long(sys.argv[6], 16)
fspBinFileRebased = "Fsp_Rebased.fd"

#
# Make sure argument passed or valid
#
if not (buildTarget in "DEBUG" or buildTarget in "RELEASE") :
  print "WARNING!  " + str(buildTarget) + " is not a valid build target"
  exit(1)
if not os.path.exists(flashMapName):
  print "WARNING!  " + str(flashMapName) + " is not found."
  exit(1)
fspBinFilePath = fspBinPath + "\\" + fspBinFile
if not os.path.exists(fspBinFilePath):
  print "WARNING!  " + str(fspBinFilePath) + " is not found."
  exit(1)
if not os.path.exists(targetDscFile):
  print "WARNING!  " + str(targetDscFile) + " is not found."
  exit(1)
ext_file = str(os.path.splitext(targetDscFile)[-1]).lower()
if ext_file != ".dsc":
  print "WARNING!  " + str(targetDscFile) + " is not a dsc file"
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
  if "PcdFlashFvFspsOffset" in line:
    fspSBaseOffset = long(line.split("=")[1].split()[0], 16)
  if "PcdFlashFvFspmtOffset" in line:
    fspTBaseOffset = long(line.split("=")[1].split()[0], 16)
file.close()

#
# Get FSP-T Size, in order to calculate the FSP-M Base. Used SplitFspBin.py script
# to dump the header, and get the ImageSize of FSP-T section
#
if "PYTHON_HOME" in os.environ:
  PythonHome = os.environ['PYTHON_HOME']
  PythonPath = PythonHome + "\\" + "Python.exe"
else:
  PythonPath = sys.executable

Process = subprocess.Popen(PythonPath + " Edk2\IntelFsp2Pkg\Tools\SplitFspBin.py info -f" + fspBinFilePath, stdout=subprocess.PIPE)
Output = Process.communicate()[0]
FsptInfo = Output.rsplit("FSP_T", 1);
for line in FsptInfo[1].split("\n"):
  if "ImageSize" in line:
    fspTSize = long(line.split("=")[1], 16)
    break

# Calculate FSP-S/M/T base address, to which re-base has to be done. Note: FSP-M will be below FSP-T, to get the benefit of cache for low LLC SKU
fspSBaseAddress = flashBase + fspSBaseOffset + fvOffset
fspTBaseAddress = flashBase + fspTBaseOffset
fspMBaseAddress = flashBase + fspTBaseOffset + fspTSize

#
# Re-base FSP bin file to new address and save it as fspBinFileRebased using SplitFspBin.py
#
rebaseArguments = fspBinFilePath + " -c s m t -b " + str(hex(fspSBaseAddress).rstrip("L")) + " " + str(hex(fspMBaseAddress).rstrip("L")) + " " + str(hex(fspTBaseAddress).rstrip("L")) + " -o" + fspBinPath + " -n " + fspBinFileRebased
os.system(PythonPath + " Edk2\IntelFsp2Pkg\Tools\SplitFspBin.py rebase -f" + rebaseArguments)

#
# Split FSP bin to FSP-S/M/T segments
#
splitArguments = fspBinPath + "\\" + fspBinFileRebased + " -o " + fspBinPath + " -n Fsp_Rebased.fd"
os.system(PythonPath + " Edk2\IntelFsp2Pkg\Tools\SplitFspBin.py split -f" + splitArguments)

#
# Patch dsc file with the re-based FSP-S/M/T address, so internally build will use the same.
#
DscFile  = open(targetDscFile, "r")
DscLines = DscFile.readlines()
DscFile.close()
DscContent = []
for line in DscLines:
  DscContent.append(line)
DscFile = open(targetDscFile,"w")
for index in range(len(DscContent)):
  DscLine = DscContent[index]
  Match = re.match("([\s_a-zA-Z0-9]+).Pcd(Fspt|Fspm|Fsps)BaseAddress",DscLine)
  if Match:
    DscLine = Match.group(1) + ".Pcd" + Match.group(2) + "BaseAddress|0x"
    if Match.group(2) == 'Fspt':
      BaseAddrStr = str(hex(fspTBaseAddress)[2:]).zfill(8).upper().rstrip('L')
    elif Match.group(2) == 'Fspm':
      BaseAddrStr = str(hex(fspMBaseAddress)[2:]).zfill(8).upper().rstrip('L')
    elif Match.group(2) == 'Fsps':
      BaseAddrStr = str(hex(fspSBaseAddress)[2:]).zfill(8).upper().rstrip('L')
    DscLine = DscLine + BaseAddrStr + "\n"
  DscFile.writelines(DscLine)
DscFile.close()
exit(0)
