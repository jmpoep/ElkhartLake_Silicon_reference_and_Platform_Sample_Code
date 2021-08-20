## @ RebaseAndPatchFspBinBaseAddress.py
#
# Copyright (c) 2016 - 2019, Intel Corporation. All rights reserved.<BR>
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
  print("RebaseAndPatchFspBinBaseAddress.py - Error in number of arguments received")
  print("Usage - RebaseAndPatchFspBinBaseAddress.py <Build Target - DEBUG/RELEASE> <FlashMap file path> <FspBinPkg Folder> <Fsp.fd file name> <Dsc file path to be patched> <pad_offset for Fsp-S Base Address>")
  exit(1)

buildTarget       = sys.argv[1].upper()
flashMapName      = sys.argv[2]
fspBinPath        = sys.argv[3]
fspBinFile        = sys.argv[4]
targetDscFile     = sys.argv[5]
fvOffset          = int(sys.argv[6], 16)
fspBinFileRebased = "Fsp_Rebased.fd"

#
# Make sure argument passed or valid
#
if not (buildTarget in "DEBUG" or buildTarget in "RELEASE") :
  print("WARNING!  " + str(buildTarget) + " is not a valid build target")
  exit(1)
if not os.path.exists(flashMapName):
  print("WARNING!  " + str(flashMapName) + " is not found.")
  exit(1)
fspBinFilePath = fspBinPath + "\\" + fspBinFile
if not os.path.exists(fspBinFilePath):
  print("WARNING!  " + str(fspBinFilePath) + " is not found.")
  exit(1)
if not os.path.exists(targetDscFile):
  print("WARNING!  " + str(targetDscFile) + " is not found.")
  exit(1)
ext_file = str(os.path.splitext(targetDscFile)[-1]).lower()
if ext_file != ".dsc":
  print("WARNING!  " + str(targetDscFile) + " is not a dsc file")
  exit(1)

#
# Get the FSP-S / FSP-M-T FV Base Address from Flash Map
#
file = open (flashMapName, "r")
data = file.read ()

# Get the Flash Base Address
flashBase = int(data.split("FLASH_BASE")[1].split("=")[1].split()[0], 16)

# Based on Build Target, select the section in the FlashMap file
if buildTarget in "DEBUG":
  flashmap = data.rsplit("!if $(TARGET) == DEBUG", 1)[1].split("!else")[0]
else:
  flashmap = data.rsplit("!else", 1)[1]

#
# Support Pcd Start
#
# FSP-S & FSP-M & FSP-T & Pre-Memory Value
fspSOffset    = 0
fspMOffset    = 0
fspTOffset    = 0
prememOffset  = 0

#
# Find already calculated Pcd value
#
def CheckDuplicatePcd (duppcd):
  if "PcdFlashFvFspSOffset" in duppcd:
    return fspSOffset
  elif "PcdFlashFvFspMOffset" in duppcd:
    return fspMOffset
  elif "PcdFlashFvFspTOffset" in duppcd:
    return fspTOffset
  else:
    return 0
#
# Pcd String to Number
#
def PcdToNum (pcdname):
  retnum = 0
  # for support value, ex: 0x60000
  if "0x" in pcdname:
    retnum = int(pcdname, 16)

  for line in flashmap.split("\n"):
    if pcdname in line.split("=")[0]:
      OffsetOrSize = line.split("=")[1].split()[0]
      if "0x" in OffsetOrSize:
        retnum = int(OffsetOrSize.split()[0], 16)
        break
      else:
        retnum = CheckDuplicatePcd(pcdname)
        break

  return retnum

#
# Calculate FSP-S & FSP-M & FSP-T & Pre-Memory offset
#
def CalculateOffset (operator, sourcestr):
  retcal = 0
  if operator in sourcestr:
    BaseOffset = line.split("=")[1].split(operator)[0].strip().strip('$').strip('(').strip(')').split(".")[1]
    BaseSize   = line.split("=")[1].split(operator)[1].strip().strip('$').strip('(').strip(')').split(".")[1]
    if "+" in operator:
      retcal = PcdToNum(BaseOffset) + PcdToNum(BaseSize)
    elif "-" in operator:
      retcal = PcdToNum(BaseOffset) - PcdToNum(BaseSize)
  else:
    if "$" in sourcestr:
      BaseOffset = line.split("=")[1].strip().strip('$').strip('(').strip(')').split(".")[1]
    else:
      BaseOffset = sourcestr.split()[0]

    retcal = PcdToNum(BaseOffset)

  return retcal

#
# Get FSP-S & FSP-M & FSP-T & Pre-Memory offset Pcd name & operator
# BaseOffset and BaseSize are PCD name
#
def GetPcdOffset (pcdstr, sourcestr):
  retVal = 0
  # Get Operator
  if "+" in sourcestr:
    operator = "+"
  elif "-" in sourcestr:
    operator = "-"
  else:
    operator = "/"

  # calculate PcdOffset
  retVal = CalculateOffset (operator, sourcestr.split("=")[1])
  return retVal

for line in flashmap.split("\n"):
  # FSP-S
  if "PcdFlashFvFspsOffset" in line.split("=")[0]:
    fspSOffset = GetPcdOffset("PcdFlashFvFspsOffset", line)
  # FSP-M
  if "PcdFlashFvFspmOffset" in line.split("=")[0]:
    fspMOffset = GetPcdOffset("PcdFlashFvFspmOffset", line)
  # FSP-T
  if "PcdFlashFvFspmtOffset" in line.split("=")[0]:
    fspTOffset = GetPcdOffset("PcdFlashFvFspmtOffset", line)
  # Pre-Memory
  if "PcdFlashFvPreMemoryOffset" in line.split("=")[0]:
    prememOffset = GetPcdOffset("PcdFlashFvPreMemoryOffset", line)
file.close()
#
# Support Pcd End
#


#
# Get FSP-T Size, in order to calculate the FSP-M Base. Used SplitFspBin.py script
# to dump the header, and get the ImageSize of FSP-T section
#
if "PYTHON_HOME" in os.environ:
  PythonHome = os.environ['PYTHON_HOME']
  PythonPath = PythonHome + "\\" + "Python.exe"
else:
  PythonPath = sys.executable

if "FSP_SPLIT_BIN_PATH" in os.environ:
  FspSplitBinPath = os.environ['FSP_SPLIT_BIN_PATH']
else:
  FspSplitBinPath = "Edk2\IntelFsp2Pkg\Tools\SplitFspBin.py"

Process = subprocess.Popen(PythonPath + " " + FspSplitBinPath + " info -f" + fspBinFilePath, stdout=subprocess.PIPE)
Output = Process.communicate()[0]
FsptInfo = Output.rsplit("FSP_T", 1);
for line in FsptInfo[1].split("\n"):
  if "ImageSize" in line:
    fspTSize = int(line.split("=")[1], 16)
    break

# Calculate FSP-S/M/T base address, to which re-base has to be done. Note: FSP-M will be below FSP-T, to get the benefit of cache for low LLC SKU
fspSBaseAddress = flashBase + fspSOffset + fvOffset
fspTBaseAddress = flashBase + fspTOffset
fspMBaseAddress = flashBase + fspTOffset + fspTSize

#
# Re-base FSP bin file to new address and save it as fspBinFileRebased using SplitFspBin.py
#
rebaseArguments = fspBinFilePath + " -c s m t -b " + str(hex(fspSBaseAddress).rstrip("L")) + " " + str(hex(fspMBaseAddress).rstrip("L")) + " " + str(hex(fspTBaseAddress).rstrip("L")) + " -o" + fspBinPath + " -n " + fspBinFileRebased
os.system(PythonPath + " " + FspSplitBinPath + " rebase -f" + rebaseArguments)

#
# Split FSP bin to FSP-S/M/T segments
#
splitArguments = fspBinPath + "\\" + fspBinFileRebased + " -o " + fspBinPath + " -n Fsp_Rebased.fd"
os.system(PythonPath + " " + FspSplitBinPath + " split -f" + splitArguments)

#
# Patch dsc file with the re-based FSP-S/M/T address, so internally build will use the same.
#
DscFile  = open(targetDscFile, "r")
DscLines = DscFile.readlines()
DscFile.close()
DscContent = []
for line in DscLines:
  DscContent.append(line)
DscFile = open(targetDscFile, "w")
for index in range(len(DscContent)):
  DscLine = DscContent[index]
  Match = re.match("([\s_a-zA-Z0-9]+).Pcd(Fspt|Fspm|Fsps|FixedFspt|FixedFspm|FixedFsps)BaseAddress\|0x", DscLine)
  if Match:
    DscLine = Match.group(1) + ".Pcd" + Match.group(2) + "BaseAddress|0x"
    if Match.group(2) == 'Fspt' or Match.group(2) == 'FixedFspt' :
      BaseAddrStr = str(hex(fspTBaseAddress)[2:]).zfill(8).upper().rstrip('L')
    elif Match.group(2) == 'Fspm' or Match.group(2) == 'FixedFspm' :
      BaseAddrStr = str(hex(fspMBaseAddress)[2:]).zfill(8).upper().rstrip('L')
    elif Match.group(2) == 'Fsps' or Match.group(2) == 'FixedFsps':
      BaseAddrStr = str(hex(fspSBaseAddress)[2:]).zfill(8).upper().rstrip('L')
    DscLine = DscLine + BaseAddrStr + "\n"
  DscFile.writelines(DscLine)
DscFile.close()
exit(0)
