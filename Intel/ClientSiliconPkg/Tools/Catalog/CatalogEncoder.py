### @file
# Tool to generate encoded source file for Catalog usage.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2016 - 2019 Intel Corporation.
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
#  This file contains 'Framework Code' and is licensed as such under the terms
#  of your license agreement with Intel or your vendor. This file may not be 
#  modified, except as allowed by additional terms of your license agreement.
#
# @par Specification Reference:
#
# @par Glossary:
###


__version__ = "0.5"


import os
import datetime
import sys
import re
import time
import argparse
import hashlib
try:
    import pickle as Pick
except:
    import cPickle as Pick
import win32file
import win32api


DicList = {}
OldDicList = {}
KeyNumber = 0x1001
TempKeyNumber = 0x0000


def GetArgs():
    ArgParser = argparse.ArgumentParser()
    ArgParser.add_argument(
                "-I",
                "--InputFile",
                dest = "InputFile",
                help = ("Specify the absolute or relative path of source file."),
                required = True)
    ArgParser.add_argument(
                "-O",
                "--OutputFile",
                dest = "OutputFile",
                help = ("Specify the absolute or relative path of encoded source file."),
                required = True)
    ArgParser.add_argument(
                "-D",
                "--DictionaryFile",
                dest = "DictionaryFile",
                help = ("Specify the absolute or relative path of Dictionary file."),
                required = True)
    ArgParser.add_argument(
                "-M",
                "--Mode",
                dest = "Mode",
                help = ("Specify encode mode: 4-HEX, or SHA-1. (Default: 4-HEX)"),
                default = "4-HEX")
    return ArgParser.parse_args()


def ChangePercent(PrecentStr):
    global DicList
    global OldDicList
    global KeyNumber
    global TempKeyNumber

    FindSameString = False
    PrecentStr = PrecentStr.rstrip()

    for TempData in list(OldDicList.items()):
        if(TempData[1] == PrecentStr):
            FindSameString = True
            TempKeyNumber = int(TempData[0], 16)
            break
    if(FindSameString == False):
        for TempData in list(DicList.items()):
            if(TempData[1] == PrecentStr):
                FindSameString = True
                TempKeyNumber = int(TempData[0], 16)
                break
    if(FindSameString == False):
        NumberStr = '%x'%KeyNumber
        DicList[NumberStr] = PrecentStr
        TempKeyNumber = KeyNumber
        KeyNumber += 1
    ReturnStr = ""
    P3 = re.compile(r'%[.\-\+ ,Ll*\d]*[XxdsSacgtrp]+')
    for M21 in P3.findall(PrecentStr):
        ReturnStr = ReturnStr + M21 + '@$'
    return ReturnStr


def ChangeDebugString(DebugStr):
    global KeyNumber
    global TempKeyNumber

    if(DebugStr.lower().find('\\\"') != -1 and
       DebugStr.lower().find('\\\"))') == -1):
        DebugStr = DebugStr.replace('\\\"',"")

    ReturnStr = ""
    P2 = re.compile(r"(?:\"[^\"]*\"\s*)+\s*")
    Result=P2.findall(DebugStr)

    Result1=P2.split(DebugStr, 1)
    ReturnStr = Result1[0] + "\"S%x"+ ChangePercent(Result[0]) + "\\n\"" + (", 0x%x" % TempKeyNumber) + Result1[1]

    return ReturnStr


def EncodeFormatStringSha1(FormatString):
    '''EncodeFormatStringSha1() -> (EncodedFormatString, Mapping)

    This function will encode FormatSting without surrounding double qoute.
    '''

    FormatString = FormatString[1:-1] # Remove Double quote
    Key = hashlib.sha1(FormatString).hexdigest()
    Mapping = {Key: FormatString.replace("\\\n", "")} # Backslash character (\) immediately followed by a new-line character

    FormatSpecifiersFormat = re.compile(r"%[.\-\+ ,Ll*\d]*[XxdsSacgtrp]+")
    EncodedFormatString = "\"" + Key # Add back Double quote
    for FormatSpecifier in FormatSpecifiersFormat.findall(FormatString):
        EncodedFormatString += FormatSpecifier + '@$'
    EncodedFormatString += "\\n\""  # Add back Double quote, and newline

    return (EncodedFormatString, Mapping)


def EncodeDebugStringSha1(DebugStr):
    if(DebugStr.lower().find('\\\"') != -1 and
       DebugStr.lower().find('\\\"))') == -1):
        DebugStr = DebugStr.replace('\\\"',"")

    FormatStringER = re.compile(r"(\"[^\"]*\")+\s*")
    FormatStrings = FormatStringER.findall(DebugStr)

    FormatString = FormatStrings[0]

    SplitDebugStr = DebugStr.split(FormatString, 1)
    (EncodedFormatString, Mapping) = EncodeFormatStringSha1 (FormatString)
    ReturnStr = SplitDebugStr[0] + EncodedFormatString + SplitDebugStr[1]

    return (ReturnStr, Mapping)


def UpdateDictionarySha1(DictionaryFile, DicsSha1):
    '''UpdateDictionarySha1() -> ()

    This function 
    '''

    while True:
        #
        # Get DicFile, if don't have accesss, wait and try again; if don't have the file, create a new file.
        #
        try:
            DicFile = win32file.CreateFile(DictionaryFile, win32file.GENERIC_READ|win32file.GENERIC_WRITE, 0, None, win32file.OPEN_EXISTING, 0, None)
            break
        except Exception as ErrorValue:
            if(ErrorValue[0] == 2 and ErrorValue[1] == r"CreateFile" or ErrorValue[2] == "The system cannot find the file specified."):
                DicFile = win32file.CreateFile(DictionaryFile, win32file.GENERIC_READ|win32file.GENERIC_WRITE, 0, None, win32file.CREATE_NEW, 0, None)
                break
            if(ErrorValue[0] == 32 and ErrorValue[1]==r"CreateFile" or ErrorValue[2]=="The process cannot access the file because it is being used by another process."):
                win32api.Sleep(1)
            print("Waiting to acquire '%s' access" % DictionaryFile)
    
    (Status, DicFileLines) = win32file.ReadFile(DicFile, win32file.GetFileSize(DicFile))

    #
    # Construct Dictionary from input Dictionary File
    #
    DicData = {}
    if(DicFileLines != ""):
        DicFormat = re.compile(r"^[0-9a-fA-F]{40},", re.MULTILINE)
        DicKeys = DicFormat.findall(DicFileLines) # Include comma
        DicMappingStrs = DicFormat.split(DicFileLines)[1:] # First one is null
        Index = 0
        while(Index < len(DicKeys)):
            DicData.update({DicKeys[Index][:-1]: DicMappingStrs[Index][:-1]}) # Remove comman in key; nextline symblo in value
            Index += 1

    #
    # Leave new encoding, compare to Dictionary, in DicsSha1
    #
    for Key in sorted(DicsSha1):
        try:
            if(DicData[Key] == DicsSha1[Key]):
                del DicsSha1[Key]
            else:
                print("ERROR - Incorrect encoding found in Dictionary")
                exit()
        except KeyError:
            continue
    
    #
    # Write new encoding into Dictionary File
    #
    NewDicData = ""
    for Data in sorted(DicsSha1):
        NewDicData += Data + "," + DicsSha1[Data] + "\n"
    (Status, ByteWritten) = win32file.WriteFile(DicFile, NewDicData)


def Main():
    global DicList
    global OldDicList
    global KeyNumber
    global TempKeyNumber

    print("CatalogEncoder ver %s" % __version__)

    Args = GetArgs()

    SrcFile = open(Args.InputFile,'r')
    SrcFileLines = SrcFile.readlines()
    SrcFile.close()

    SrcFileContent = ""
    Index = 0
    while(Index < len(SrcFileLines)):
        SrcFileContent += SrcFileLines[Index]
        Index = Index + 1

    EncodedSrcFileContent = ""
    DebugMacroER = re.compile(r"\s*DEBUG\s*\(\s*\(\s*[|\s\w]+[\s,]*\"[^\"]*\"[^;]*;")
    DebugMacroMatchedData = DebugMacroER.findall(SrcFileContent)
    if(len(DebugMacroMatchedData) == 0):
        #
        # No Debug macro found
        #
        EncodedSrcFileContent = SrcFileContent
    else:
        if(Args.Mode == "4-HEX"):
            while True:
                #
                # Get DicFile, if don't have accesss, wait and try again; if don't have the file, create a new file.
                #
                try:
                    DicFile = win32file.CreateFile(Args.DictionaryFile, win32file.GENERIC_READ|win32file.GENERIC_WRITE, 0, None, win32file.OPEN_EXISTING, 0, None)
                    break
                except Exception as ErrorValue:
                    if(ErrorValue[0] == 2 and ErrorValue[1] == r"CreateFile" or ErrorValue[2] == "The system cannot find the file specified."):
                        DicFile = win32file.CreateFile(Args.DictionaryFile, win32file.GENERIC_READ|win32file.GENERIC_WRITE, 0, None, win32file.CREATE_NEW, 0, None)
                        break
                    if(ErrorValue[0] == 32 and ErrorValue[1]==r"CreateFile" or ErrorValue[2]=="The process cannot access the file because it is being used by another process."):
                        win32api.Sleep(1)
                    print("Waiting to acquire '%s' access" % Args.DictionaryFile)
            
            (Status, DicFileLines) = win32file.ReadFile(DicFile, win32file.GetFileSize(DicFile))

            if(DicFileLines == ""):
                KeyNumber = 0x1001
            else:
                DicFormat = re.compile(r"^[\n\r]*[0-9a-fA-F]{4},", re.M)
                DicKeyNumbers = DicFormat.findall(DicFileLines)
                DicEncodedStrs = DicFormat.split(DicFileLines)[1:]
                KeyNumber = int(DicKeyNumbers[-1].split(",")[0].strip(), 16) + 1
                Index = 0
                while(Index < len(DicKeyNumbers)):
                    TempStr = DicKeyNumbers[Index].split(",")[0].strip()
                    OldDicList[TempStr] = DicEncodedStrs[Index][:-1]
                    Index += 1

            Paragraph = 0
            for NoDebugMacroDatum in DebugMacroER.split(SrcFileContent):
                TempKeyNumber = 0
                EncodedSrcFileContent += NoDebugMacroDatum
                if(Paragraph < len(DebugMacroMatchedData)):
                    EncodedSrcFileContent += ChangeDebugString(DebugMacroMatchedData[Paragraph])
                Paragraph += 1

            SortedDic = sorted(list(DicList.items()), key=lambda DicList:DicList[0])
            SortedDicData = ""
            for Data in SortedDic:
                SortedDicData = SortedDicData + Data[0] + "," + Data[1] + "\n"
            (Status, ByteWritten) = win32file.WriteFile(DicFile, SortedDicData)
            win32file.CloseHandle(DicFile)

        elif(Args.Mode == "SHA-1"):
            Paragraph = 0
            DicsSha1 = {}
            DicSha1 = {}
            for NoDebugMacroDatum in DebugMacroER.split(SrcFileContent):
                EncodedSrcFileContent += NoDebugMacroDatum
                if(Paragraph < len(DebugMacroMatchedData)):
                    (EncodedStr, DicSha1) = EncodeDebugStringSha1(DebugMacroMatchedData[Paragraph])
                    EncodedSrcFileContent += EncodedStr
                    DicsSha1.update(DicSha1)
                Paragraph += 1

            UpdateDictionarySha1 (Args.DictionaryFile, DicsSha1)

        else:
            print("ERROR - Mode: %s is not supported" % Args.Mode)
            exit()

    CurrentEncodedSrcFileContent = ''
    if os.path.isfile(Args.OutputFile):
        EncodedSrcFile = open(Args.OutputFile, 'r')
        CurrentEncodedSrcFileLines = EncodedSrcFile.readlines()
        Index = 0
        while(Index < len(CurrentEncodedSrcFileLines)):
            CurrentEncodedSrcFileContent += CurrentEncodedSrcFileLines[Index]
            Index = Index + 1

    if CurrentEncodedSrcFileContent != EncodedSrcFileContent:
        EncodedSrcFile = open(Args.OutputFile, 'w')
        EncodedSrcFile.write(EncodedSrcFileContent)
        EncodedSrcFile.close()

if __name__ == "__main__":
    Main()
