### @file
# Tool to decode Catalog encoded message.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2019 Intel Corporation.
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


__version__ = "0.4"


import os
import datetime
import sys
import re
import time
import argparse
try:
    import pickle as Pick
except:
    import cPickle as Pick


def GetArgs():
    ArgParser = argparse.ArgumentParser()
    ArgParser.add_argument(
                "-I",
                "--InputFile",
                dest = "InputFile",
                help = ("Specify the absolute or relative path of Log file."),
                required = True)
    ArgParser.add_argument(
                "-O",
                "--OutputFile",
                dest = "OutputFile",
                help = ("Specify the absolute or relative path of decoded Log files. (Default: Decoded.txt)"),
                default = "Decoded.txt")
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


def ReplaceFormatSpecifiers(PrintfFormatStr, FormatSpecifier):
    '''ReplaceFormatSpecifiers() -> (ReplacedPrintfFormatStr)

    This function will replace all format specifiers to FormatSpecifier in PrintfFormatStr.
    '''

    FormatSpecifiersFormat = re.compile(r"%[.\-\+ ,Ll*\d]*[XxdsSacgtrp]+")
    SplittedPrintfFormatStr = FormatSpecifiersFormat.split(PrintfFormatStr)

    ReplacedPrintfFormatStr = ""
    Group = 0
    for String in SplittedPrintfFormatStr:
        ReplacedPrintfFormatStr += String
        if (Group < (len(SplittedPrintfFormatStr) - 1)):
            ReplacedPrintfFormatStr += FormatSpecifier
        Group += 1

    return ReplacedPrintfFormatStr


def Main():
    print("CatalogDecoder ver %s" % __version__)

    Args = GetArgs()

    if(Args.Mode == "4-HEX"):
        KeyLength = 4
        DicFormat = re.compile(r"^[\n\r]*[0-9a-fA-F]{4},", re.M)
        EncodedStrFormat = re.compile(r"\A[\0]*[ ]*S[0-9a-fA-F]{4}")
        EncodedStrFormatRuntimeValue = re.compile(r"@\$")
    elif(Args.Mode == "SHA-1"):
        KeyLength = 40
        DicFormat = re.compile(r"^[\n\r]*[0-9a-fA-F]{40},", re.M)
        EncodedStrFormat = re.compile(r"\A[\0]*[ ]*[0-9a-fA-F]{40}")
        EncodedStrFormatRuntimeValue = re.compile(r"@\$")
    else:
        print("ERROR - Mode: %s is not supported" % Args.Mode)
        exit()

    LogFile = open(Args.InputFile, "r")
    LogFileLines = LogFile.readlines()
    LogFile.close()

    #
    # Prepare dictionary for decoding
    #
    DicFileContent = ""
    DicFile = open(Args.DictionaryFile, "r")
    for Line in DicFile.readlines():
        DicFileContent = DicFileContent + Line
    DicFile.close()
    if(DicFileContent == ""):
        print("ERROR - Dictionary file is empty")
        exit()

    DicList = {}
    DicKeys = DicFormat.findall(DicFileContent) # postfix with comma ","
    DicEncodedStrs = DicFormat.split(DicFileContent)[1:]
    Index = 0
    while(Index < len(DicKeys)):
        Key = DicKeys[Index][:-1] # remove posfix comma
        DicList[Key] = ReplaceFormatSpecifiers(DicEncodedStrs[Index][:-1], "%s") # remove newline symbol
        Index += 1

    #
    # Decode input file to output file
    #
    DecodedStrs = ""
    for Line in LogFileLines:
        try:
            Key = EncodedStrFormat.match(Line).group()[-KeyLength:].lower()
        except:
            #
            # Line was not encoded or is unrecognizable.
            # Write Line to output file as is.
            #
            DecodedStrs += Line[:-1] + "\n"
            continue

        try:
            exec("DecodedStr = DicList[\"%s\"]" % (Key))
        except:
            #
            # Key is not found in dictionary.
            # Write Line to output file as is.
            #
            DecodedStrs += Line
            continue

        SplittedLine = EncodedStrFormat.split(Line, 1)
        if(len(EncodedStrFormat.split(Line, 1)) != 2):
            #
            # No or More than one encoded string is identified.
            # Write Line to output file as is.
            #
            DecodedStrs += Line
            continue

        if not(SplittedLine[1] == "" or SplittedLine[1] == "\n"):
            #
            # Contains encoded string and followed by parameter(s).
            #
            ParametersInLine = EncodedStrFormatRuntimeValue.split(SplittedLine[1])
            Parameters = "\"" + ParametersInLine[0] + "\""
            for Parameter in ParametersInLine[1:-1]:
                if(Parameter != "\n"):
                    Parameters = Parameters + "," + "\"" + Parameter + "\""

            try:
                exec("DecodedStr = DecodedStr %% (%s)" % (Parameters))
            except:
                #
                # Parameter mismatch with dictionary string
                # Write Line to output file as is.
                #
                DecodedStrs += Line
                continue

        DecodedStrs += DecodedStr.lstrip('\"').rstrip('\"').replace("\\\n",'').replace("\\r","\r").replace("\\n","\n").replace("\\t","\t")

    DecodedLogFile = open(Args.OutputFile, "w")
    DecodedLogFile.write(DecodedStrs)
    DecodedLogFile.close()

if __name__ == "__main__":
    Main()
