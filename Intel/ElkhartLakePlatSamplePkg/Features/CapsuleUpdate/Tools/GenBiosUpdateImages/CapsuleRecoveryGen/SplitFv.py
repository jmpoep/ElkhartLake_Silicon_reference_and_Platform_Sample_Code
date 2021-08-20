## @ SplitFv.py
#
#@copyright
#  INTEL CONFIDENTIAL
#  Copyright 2018 - 2019 Intel Corporation.
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

import sys
import os
import glob
import fileinput
import struct
import array
import re
import binascii
import argparse

class CapFile:
    def __init__(self, buildTarget, capFileName):
        file = open (capFileName, "r")
        data = file.read ()
        file.close()
        self.faultToleranceOffset = long(data.split("PcdFaultToleranceOffset")[1].split("=")[1].split()[0], 16)

class FlashMap:
    def __init__(self, buildTarget, flashMapFile):
        self.buildTarget = buildTarget
        self.flashMapFile = flashMapFile

    def parseFv(self):
        if not (self.buildTarget in "DEBUG" or self.buildTarget in "RELEASE") :
            print "WARNING!  " + str(self.buildTarget) + " is not a valid build target"
            return
        if not os.path.exists(self.flashMapFile):
            print "WARNING!  " + str(self.flashMapFile) + " is not found."
            return

        #
        # Get the FSP-S / FSP-M-T FV Base Address from Flash Map
        #
        file = open (self.flashMapFile, "r")
        data = file.read ()
        file.close()

        # Get the Flash Base Address
        self.flashBase = long(data.split("FLASH_BASE")[1].split("=")[1].split()[0], 16)
        self.flashSize = long(data.split("FLASH_SIZE")[1].split("=")[1].split()[0], 16)

        # Based on Build Target, select the section in the FlashMap file
        flashmap = data

        # Get FSP-S & FSP-M-T offset & calculate the base
        for line in flashmap.split("\n"):
            if "PcdFlashNvStorageOffset" in line:
                self.nvStorageOffset = long(line.split("=")[1].split()[0], 16)
            if "PcdFlashNvStorageSize" in line:
                self.nvStorageSize = long(line.split("=")[1].split()[0], 16)

                self.FvObbOffset = long(line.split("=")[1].split()[0], 16)
                self.FvObbSize = long(line.split("=")[1].split()[0], 16)

            if "PcdFlashFvFspMOffset" in line:
                self.FvIbbOffset = long(line.split("=")[1].split()[0], 16)
                self.FvIbbSize = self.flashSize - self.FvIbbOffset
                self.FvTopSwapSize = 0x400000
                self.FvTopSwapOffset = self.FvIbbOffset - self.FvTopSwapSize

        self.FvObbOffset = self.nvStorageOffset + self.nvStorageSize

        self.FvObbSize = self.FvIbbOffset - self.FvObbOffset
        if "PcdFlashIbbROffset" in line:
            self.FvObbSize = self.FvIbbOffset - self.FvTopSwapSize - self.FvObbOffset

def SplitFd (binfile, SplitType, fvmap, OutputDir):

  # open BIOS ROM file
  fin = open(binfile, "rb")

  if os.path.getsize (binfile) < fvmap.flashSize:
    print "Not a 10M BIOS %s" % binfile
    return -1

  wholebios = fin.read()
  fin.close()

  filename = os.path.join(OutputDir, "Nvs.rom")
  fout = open(filename, "wb")
  fout.write(wholebios[fvmap.nvStorageOffset:fvmap.nvStorageOffset + fvmap.nvStorageSize])
  fout.close()
  print ("SplitFd!  Nvs.rom is from 0x%08X to 0x%08X" % (fvmap.nvStorageOffset, fvmap.nvStorageOffset + fvmap.nvStorageSize) )

  filename = os.path.join(OutputDir, "Obb.rom")
  fout = open(filename, "wb")
  fout.write(wholebios[fvmap.FvObbOffset:fvmap.FvObbOffset + fvmap.FvObbSize])
  fout.close()
  print ("SplitFd!  Obb.rom is from 0x%08X to 0x%08X" % (fvmap.FvObbOffset, fvmap.FvObbOffset + fvmap.FvObbSize) )

  filename = os.path.join(OutputDir, "Ibb.rom")
  fout = open(filename, "wb")
  fout.write(wholebios[fvmap.FvRecoveryOffset:fvmap.FvRecoveryOffset + fvmap.FvRecoverySize])
  fout.close()
  print ("SplitFd!  Ibb.rom is from 0x%08X to 0x%08X" % (fvmap.FvRecoveryOffset, fvmap.FvRecoveryOffset + fvmap.FvRecoverySize) )

  filename = os.path.join(OutputDir, "Ibb2.rom")  # microcode & binary & FspS & recovery3
  fout = open(filename, "wb")
  fout.write(wholebios[fvmap.IBB2Offset: fvmap.IBB2TailOffset])
  fout.close()
  print ("SplitFd!  Ibb2.rom is from 0x%08X to 0x%08X" % (fvmap.IBB2Offset, fvmap.IBB2TailOffset) )

  filename = os.path.join(OutputDir, "Recovery2.rom") # recovery2
  fout = open(filename, "wb")
  fout.write(wholebios[fvmap.FvRecovery2Offset: fvmap.FvRecovery2Offset + fvmap.FvRecovery2Size])
  fout.close()
  print ("SplitFd!  Recovery2.rom is from 0x%08X to 0x%08X" % (fvmap.FvRecovery2Offset, fvmap.FvRecovery2Offset + fvmap.FvRecovery2Size) )

  filename = os.path.join(OutputDir, "FspMt.rom") # fvmt
  fout = open(filename, "wb")
  fout.write(wholebios[fvmap.FvFspmtOffset: fvmap.FvFspmtOffset + fvmap.FvFspmtSize])
  fout.close()
  print ("SplitFd!  FspMt.rom is from 0x%08X to 0x%08X" % (fvmap.FvFspmtOffset, fvmap.FvFspmtOffset + fvmap.FvFspmtSize) )

  return 0


def MergeFd (SplitType, offset, fvmap, OutFile, OutputDir):

# making BIOS for TopSwap test
  testibbrbios = bytearray (fvmap.flashSize)
  for i in range(len(testibbrbios)):
    testibbrbios[i] = 0xFF
  v = memoryview(testibbrbios)

  ft_offset = offset
  print "MergeFd : offset = 0x%08x" % (ft_offset)

  filename = os.path.join(OutputDir, "Nvs.rom")
  fin = open(filename, "rb")
  fin.readinto (v[0:os.path.getsize (filename)])
  fin.close()

  filename = os.path.join(OutputDir, "Ibb.rom")
  fin = open(filename, "rb")
  fin.readinto (v[fvmap.FvRecoveryOffset:])
  fin.close()
  print ("MergeFd!  Ibb.rom is from 0x%08X" % (fvmap.FvRecoveryOffset) )

  filename = os.path.join(OutputDir, "Ibb2.rom")
  fin = open(filename, "rb")
  fin.readinto (v[fvmap.IBB2Offset - ft_offset:fvmap.IBB2Offset - ft_offset + os.path.getsize (filename)])
  fin.close()
  print ("MergeFd!  Ibb2.rom is from 0x%08X to 0x%08X" % (fvmap.IBB2Offset - ft_offset, fvmap.IBB2Offset - ft_offset + os.path.getsize (filename)) )

  if SplitType == "all":
      print "SplitType is all"

      filename = os.path.join(OutputDir, "Recovery2_new.rom")
      fin = open(filename, "rb")
      fin.readinto (v[fvmap.FvRecovery2Offset - ft_offset:fvmap.FvRecovery2Offset - ft_offset + os.path.getsize (filename)])
      fin.close()
      print ("MergeFd!  Recovery2_new.rom is from 0x%08X to 0x%08X" % (fvmap.FvRecovery2Offset - ft_offset, fvmap.FvRecovery2Offset - ft_offset + os.path.getsize (filename)) )

      filename = os.path.join(OutputDir, "fspmt_new.rom")
      fin = open(filename, "rb")
      fin.readinto (v[fvmap.FvFspmtOffset - ft_offset:fvmap.FvFspmtOffset - ft_offset + os.path.getsize (filename)])
      fin.close()
      print ("MergeFd!  fspmt_new.rom is from 0x%08X to 0x%08X" % (fvmap.FvFspmtOffset - ft_offset, fvmap.FvFspmtOffset - ft_offset + os.path.getsize (filename)) )
  elif SplitType == "seperate":  # not implement yet
      print "SplitType is seperate"
      fin = open("Recovery2_new.rom", "rb")
      fin.readinto (v[fvmap.FvRecovery2Offset - ft_offset:fvmap.FvRecovery2Offset - ft_offset + os.path.getsize ("Recovery2_new.rom")])
      fin.close()
      fin = open("fspmt_new.rom", "rb")
      fin.readinto (v[fvmap.FvFspmtOffset - ft_offset:fvmap.FvFspmtOffset - ft_offset + os.path.getsize ("fspmt_new.rom")])
      fin.close()

  filename = os.path.join(OutputDir, OutFile)
  fout = open(filename, "wb")
  fout.write(testibbrbios)
  fout.close()

  return 0

def changeFvRecovery (InFile, OutFile, OutputDir):

  # open BIOS ROM file
  filename = os.path.join(OutputDir, InFile)
  fin = open(filename, "rb")

  if os.path.getsize (filename) < 0xA00000:
    print "Not a 10M BIOS %s" % filename
    return -1

  wholebios = fin.read()
  fin.close()

  # copy all fd , except IBB1
  filename = os.path.join(OutputDir, "tmp1.rom")
  fout = open(filename, "wb")
  fout.write(wholebios[: 0xA00000 - 0x40000])
  fout.close()


  filename = os.path.join(OutputDir, "Ibb.rom")
  fout = open(filename, "wb")
  fout.write(wholebios[0xA00000 - 0x20000:])
  fout.close()


# making BIOS for TopSwap test
  testibbrbios = bytearray (0xA00000)
  for i in range(len(testibbrbios)):
    testibbrbios[i] = 0xFF
  v = memoryview(testibbrbios)

  filename = os.path.join(OutputDir, "tmp1.rom")
  fin = open(filename, "rb")
  fin.readinto (v[: 0xA00000 - 0x40000])
  fin.close()

  filename = os.path.join(OutputDir, "Ibb.rom")
  fin = open(filename, "rb")
  fin.readinto (v[0xA00000 - 0x40000:])
  fin.close()

  filename = os.path.join(OutputDir, OutFile)
  fout = open(filename, "wb")
  fout.write(testibbrbios)
  fout.close()

  return 0

def UpdateConfigFile (inifile, fvmap, FtOffset, OutputDir):

  # open config file
  fin = open(inifile, "r")
  configfileLines = fin.readlines()
  fin.close()

  ConfigOutputFileName = os.path.join(OutputDir, "BiosUpdateConfigSpi.ini")
  ConfigOutputFile = open(ConfigOutputFileName, "w")

  for line in configfileLines:
    NewLine = line
    if "[BiosObb]" in line:
      BaseAddress = "0x%08X" % (fvmap.FvObbOffset)
      Length      = "0x%08X" % (fvmap.FvObbSize)
      ImageOffset = "0x%08X" % (fvmap.FvObbOffset)
    if "[BiosIbbR]" in line:
      BaseAddress = "0x%08X" % (fvmap.FvTopSwapOffset)
      Length      = "0x%08X" % (fvmap.FvTopSwapSize)
      ImageOffset = "0x%08X" % (fvmap.FvTopSwapOffset)
    if "[BiosIbb]" in line:
      BaseAddress = "0x%08X" % (fvmap.FvIbbOffset)
      Length      = "0x%08X" % (fvmap.FvIbbSize)
      ImageOffset = "0x%08X" % (fvmap.FvIbbOffset)

    if "BaseAddress  =" in line:
      NewLine = "BaseAddress  = " + BaseAddress + "\n"
    if "Length       =" in line:
      NewLine = "Length       = " + Length + "\n"
    if "ImageOffset  =" in line:
      NewLine = "ImageOffset  = " + ImageOffset + "\n"
    ConfigOutputFile.writelines(NewLine)
  ConfigOutputFile.close()

  return 0
###################################################################################################
# Main
###################################################################################################

def main():

    #
    # Add sub command
    #
    parser     = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(title='commands')

    parser_split  = subparsers.add_parser('split',  help='split firmware volumes from fd')
    parser_split.set_defaults(which='split')
    parser_split.add_argument('-f',  '--fd' , dest='InputFd', type=str, help='Input binary file path', required = True)
    parser_split.add_argument('-c',  '--Split Type', choices=['seperate','all'], dest='SplitType', type=str, help='Split FD', default = "['all']", required = True)
    parser_split.add_argument('-t',  '--target', dest='Target', type=str, help='build target', default = 'RELEASE', required = True)
    parser_split.add_argument('-m',  '--mapfile', dest='MapFile', type=str, help='Map file', default = '', required = True)
    parser_split.add_argument('-o',  '--outdir' , dest='OutputDir',  type=str, help='Output directory path', default = '.')

    parser_merge  = subparsers.add_parser('merge',  help='merge firmware volumes to fd')
    parser_merge.set_defaults(which='merge')
    parser_merge.add_argument('-c',  '--Split Type', choices=['seperate','all'], dest='SplitType', type=str, help='Split FD', default = "['all']", required = True)
    parser_merge.add_argument('-n',  '--outfile', dest='OutputFile', type=str, help='output file name', default = '', required = True)
    parser_merge.add_argument('-a',  '--capfile' , dest='CapFile', type=str, help='Cap file', required = True)
    parser_merge.add_argument('-t',  '--target', dest='Target', type=str, help='build target', default = 'RELEASE', required = True)
    parser_merge.add_argument('-m',  '--mapfile', dest='MapFile', type=str, help='Map file', default = '', required = True)
    parser_merge.add_argument('-o',  '--outdir' , dest='OutputDir',  type=str, help='Output directory path', default = '.')

    parser_fvrecovery  = subparsers.add_parser('changefvr',  help='change FvRecovery to backup region')
    parser_fvrecovery.set_defaults(which='changefvr')
    parser_fvrecovery.add_argument('-f',  '--fd' , dest='InputFd', type=str, help='Input binary file path', required = True)
    parser_fvrecovery.add_argument('-n',  '--outfile', dest='OutputFile', type=str, help='output file name', default = '')
    parser_fvrecovery.add_argument('-o',  '--outdir' , dest='OutputDir',  type=str, help='Output directory path', default = '.')

    parser_updateconfig = subparsers.add_parser('updateconfig',  help='Update BiosUpdateConfig.ini by FlashMap')
    parser_updateconfig.set_defaults(which='updateconfig')
    parser_updateconfig.add_argument('-i',  '--ini' , dest='ConfigIni', type=str, help='Input config template file path', required = True)
    parser_updateconfig.add_argument('-t',  '--target', dest='Target', type=str, help='build target', default = 'RELEASE', required = True)
    parser_updateconfig.add_argument('-m',  '--mapfile', dest='MapFile', type=str, help='Map file', default = '', required = True)
    # parser_updateconfig.add_argument('-a',  '--capfile' , dest='CapFile', type=str, help='Cap file', required = True)
    parser_updateconfig.add_argument('-o',  '--outdir' , dest='OutputDir',  type=str, help='Output directory path', default = '.')
    args = parser.parse_args()
    if args.which in ['split', 'changefvr']:
        if not os.path.exists(args.InputFd):
            raise Exception ("ERROR: Could not locate binary file '%s' !" % args.InputFd)

    if hasattr(args, 'Target') and hasattr(args, 'MapFile'):
        mflashMap = FlashMap(args.Target, args.MapFile)
        mflashMap.parseFv()

    if hasattr(args, 'Target') and hasattr(args, 'CapFile'):
        mCapMap = CapFile(args.Target, args.CapFile)
        offset = mCapMap.faultToleranceOffset

    if hasattr(args, 'OutputDir') and not os.path.exists(args.OutputDir):
        raise Exception ("ERROR: Invalid output directory '%s' !" % args.OutputDir)

    if args.which == 'split':
        SplitFd (args.InputFd, args.SplitType, mflashMap, args.OutputDir)
    elif args.which == 'merge':
        MergeFd (args.SplitType, offset, mflashMap, args.OutputFile, args.OutputDir)
    elif args.which == 'changefvr':
        changeFvRecovery (args.InputFd, args.OutputFile, args.OutputDir)
    elif args.which == 'updateconfig':
        UpdateConfigFile (args.ConfigIni, mflashMap, 0x400000, args.OutputDir)
    else:
        pass

    return 0

if __name__ == '__main__':
    sys.exit(main())
