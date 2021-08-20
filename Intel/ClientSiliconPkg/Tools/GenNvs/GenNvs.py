### @file
# Tool generates ASL related H and ASL file from AHT file.
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


__version__ = "2.4.6"


import sys
import string
import re
import os
import time
import datetime
import argparse

import lex
import yacc

import filecmp


#
# Define tokens, grammars, and error handling for ply.
#
# The following variable, class, function definition will be consumed
# by Python Lex-Yacc (ply). Those definition describe how ply will
# parse AHT file.
#
class ParseNode:
    pass


#
# Define tokens in regular expression
#
tokens = ( # lex parse "tokens"
    "Offset",
    "LineComment",
    "Comma",
    "Ifdef",
    "Else",
    "Endif",
    "Integer",
    "Text",
    "Ignore",
    "LCBracket",
    "RCBracket"
)


def t_LCBracket(t):
    r"{"
    return t


def t_RCBracket(t):
    r"}"
    return t


def t_Offset(t):
    r"Offset\s*\(.*\)"
    t.value = str(t.value)
    return t


def t_Comma(t):
    r"\,"
    return t


def t_Ifdef(t):
    r"(\#ifdef|\#if\sdefined).*\n"
    t.value = str(t.value)
    return t


def t_Else(t):
    r"\#else"
    t.value = str(t.value)
    return t


def t_Endif(t):
    r"\#endif"
    t.value = str(t.value)
    return t


def t_LineComment(t):
    r"//.*\n"
    t.value = str(t.value)
    return t


def t_Integer(t):
    r"[0-9]+"
    t.value = int(t.value)
    return t


def t_Text(t):
    r"[A-Z0-9]+"
    t.value = str(t.value)
    return t


def t_Ignore(t):
    r"(\s)+"


def t_error(t):
    raise TypeError("\nUnknown text\n '%s'!!!!!!!!" % (t.value[:20],))


#
# Define grammars
#
def p_LineBlock(p):
    '''LineBlock : LineBlock OneLine
    | OneLine'''
    p[0] = ParseNode()
    p[0].List = []
    p[0].Type = "LineBlock"
    if(len(p) == 2):
        p[0].List.append(p[1])
    else:
        p[0].List = p[0].List + p[1].List
        p[0].List.append(p[2])


def p_IfBlock(p):
    '''IfBlock : Ifdef LineBlock Endif OneLine
    | Ifdef LineBlock Else LineBlock Endif OneLine'''
    p[0] = ParseNode()
    p[0].Type = "IfBlock"
    if(len(p) == 5):
        p[0].NoElsePart = True
        p[0].Str = p[1]
        p[0].IfPart = p[2]
        p[0].ElsePart = ParseNode()
        p[0].ElsePart.Type = "LineBlock"
        p[0].ElsePart.List = []
        p[0].OneLinePart = p[4]
    else:
        p[0].NoElsePart = False
        p[0].Str = p[1]
        p[0].IfPart = p[2]
        p[0].ElsePart = p[4]
        p[0].OneLinePart = p[6]


def p_OneLine(p):
    '''OneLine : Text Comma Integer Comma LineComment
    | Comma Integer Comma LineComment
    | Offset Comma
    | LineComment
    | LCBracket
    | RCBracket
    | IfBlock'''
    p[0] = ParseNode()
    p[0].Type = "OneLine"
    if(len(p) == 6):
        p[0].SubType = "Variable"
        p[0].Text = p[1]
        p[0].Int = p[3]
        p[0].Str = p[5]
    elif(len(p) == 5):
        p[0].SubType = "Variable"
        p[0].Text = ""
        p[0].Int = p[2]
        p[0].Str = p[4]
    elif(len(p) == 3):
        p[0].SubType = "Offset"
        p[0].Str = p[1]
    else:
        if(p[1] == "{"):
            p[0].SubType = "PureLCBracket"
            p[0].Str = p[1]
        elif(p[1] == "}"):
            p[0].SubType = "PureRCBracket"
            p[0].Str = p[1]
        elif(type(p[1]) == str):
            p[0].SubType = "PureComment"
            p[0].Str = p[1]
        elif(p[1].Type == "IfBlock"):
            p[0] = p[1]
            p[0].SubType = "IfBlock"


def p_error(p): # lex parse "p_error"
    print("Something wrong while parsing!!!!!!!!!!!\n")
    print("List the 10 tokens right after the parsing error:")
    print(yacc.token())
    print(yacc.token())
    print(yacc.token())
    print(yacc.token())
    print(yacc.token())
    print(yacc.token())
    print(yacc.token())
    print(yacc.token())
    print(yacc.token())
    print(yacc.token())
    sys.exit(1)


#
# Main function Supporting definition
#
class OffSetInfo:
    OffsetAccumulator = 0
    OffsetSerialNum = 0

    def __init__(self, OffsetAccumulator, OffsetSerialNum):
        self.OffsetAccumulator = OffsetAccumulator
        self.OffsetSerialNum = OffsetSerialNum


def PreProcess(Form):
    '''PreProcess() -> (Prefix, OperationString, FieldString, Postfix)

    This function will separate content into 4 parts, and return in order:
    i.   Everything before "OperationRegion"
    ii.  Everything between i. and iii.
    iii. Resister definition section (including curly bracket "{" and "}")
    iv.  Everything after iii.
    '''
    OperationStart = Form.find("OperationRegion")
    #find the last \n before "OperationRegion"
    lastn = Form[:OperationStart].rfind('\n')
    FieldStart = OperationStart
    while(FieldStart < len(Form)):
        if(Form[FieldStart] == "{"):
            break
        else:
            FieldStart = FieldStart + 1
    FieldStart = FieldStart + 1
    FieldEnd = Form.rfind("}")
    FieldEnd = FieldEnd + 2
    Prefix = Form[:lastn]
    OperationString = Form[OperationStart:FieldStart]
    FieldString = Form[FieldStart:FieldEnd]
    Postfix = Form[FieldEnd:]

    return (Prefix.split("\n"),
            OperationString.split("\n"),
            FieldString.split("\n"),
            Postfix.split("\n"))


def RestrictedCheck(RestrictedTags, Form):
    '''Terminate program if alien tag is used.

    If [tag]Content, [tag]Begin, [tag]End is found in AHT file,
    terminate program.
    '''
    IsError = False
    Index = 0
    while Index < len(Form):
        for Tag in RestrictedTags:
            if (Form[Index].find(Tag + "Content") != -1 or
                Form[Index].find(Tag + "Begin") != -1 or
                Form[Index].find(Tag + "End") != -1):
                # Error handling
                print ("Error(line" +
                       str(Index + 1) +
                       "):No Tags should be used in AHT file.")
                IsError = True
        Index = Index + 1
    if IsError:
        sys.exit(1)


def GetArgs():
    ArgParser = argparse.ArgumentParser()
    ArgParser.add_argument(
                "-I",
                "--inputFile",
                dest = "InputFile",
                help = ("Specify the absolute or relative path of input file *.AHT."),
                required = True)
    ArgParser.add_argument(
                "-O",
                "--outputRootDirectory",
                dest = "OutputRootDirectory",
                help = ("Specify the absolute path of root directory for output files *.H and *.ASL."))
    ArgParser.add_argument(
                "-R",
                "--restrictedTags",
                dest = "RestrictedTags",
                nargs = "+",
                help = ("Specify the restricted tags."))
    return ArgParser.parse_args()


def Main(argv):
    print("GenNvs ver %s" % __version__)

    Args = GetArgs()
    if Args.RestrictedTags == None:
        #
        # Default check alien tag: ([Restricted|InternalOnly][Content|Begin|End])
        #
        Args.RestrictedTags = ["Restricted", "InternalOnly"]

    print ("Processing:" + Args.InputFile)

    InputFile = open(Args.InputFile, "r")
    Form = InputFile.read()
    InputFile.close()

    RestrictedCheck(Args.RestrictedTags, "".join(Form).split("\n"))

    #
    # Separate content into 4 parts for further process
    #
    PrefixLines, OperationLines, FieldLines, PostfixLines = PreProcess(Form)

    #
    # Prepare output files
    #
    OutASL = PrefixLines[0]
    if(OutASL.startswith("@ASLPATH=")):
        OutASL = OutASL.replace("@ASLPATH=", "").strip()
    else:
        print("Warning: The 1st line should be '@ASLPATH=...'")
        exit(1)

    OutH = PrefixLines[1]
    if(OutH.startswith("@HPATH=")):
        OutH = OutH.replace("@HPATH=", "").strip()
    else:
        print("Warning: The 2nd line should be '@HPATH=...'")
        exit(1)

    OutFileNameASL = os.path.basename(OutASL)
    OutFileNameH = os.path.basename(OutH)
    if Args.OutputRootDirectory != None:
        OutputRootDirectory = Args.OutputRootDirectory
    else:
        #
        # Backward compatible
        #
        OutputRootDirectory = os.curdir
    ASLPath = os.path.join(OutputRootDirectory, os.path.split(OutASL)[0])
    HPath = os.path.join(OutputRootDirectory, os.path.split(OutH)[0])

    if(not os.path.isdir(ASLPath)):
        os.makedirs(ASLPath)
    if(not os.path.isdir(HPath)):
        os.makedirs(HPath)

    if(os.path.isfile(os.path.join(HPath, OutFileNameH))):
        os.chmod(os.path.join(HPath, OutFileNameH), 0o777) # Remove read-only
    if(os.path.isfile(os.path.join(ASLPath, OutFileNameASL))):
        os.chmod(os.path.join(ASLPath, OutFileNameASL), 0o777) # Remove read-only

    #
    # Extract value for output file generation
    #
    #
    # StructureName
    #
    StructureName = PrefixLines[2]
    if(StructureName.startswith("@STRUCTURE_NAME=")):
        StructureName = StructureName.replace("@STRUCTURE_NAME=", "").strip()
    else:
        print("Warning: The 3rd line should be '@STRUCTURE_NAME=...'")
        exit(1)

    #
    # HeaderDefineStr
    #
    HeaderDefineStr = OutFileNameH[:OutFileNameH.rfind(".")]
    Index = 0
    while(Index < len(HeaderDefineStr)):
        if(HeaderDefineStr[Index] >= "A" and HeaderDefineStr[Index] <= "Z"):
            HeaderDefineStr = HeaderDefineStr[:Index] + "_" + HeaderDefineStr[Index:]
            Index = Index + 1
        Index = Index + 1
    HeaderDefineStr = HeaderDefineStr.upper()

    #
    # CopyrightStr
    #
    CopyrightStr = "\n".join(PrefixLines[3:]) # Skip @ASLPATH, @HPATH, and @STRUCTURE_NAME

    #
    # ReminderStr
    #
    ReminderStr = ("//\n" +
                   "// Automatically generated by GenNvs ver " + __version__ + "\n" +
                   "// Please DO NOT modify !!!\n" +
                   "//\n")

    #
    # Parse FieldLines
    #
    StartTime = datetime.datetime.now()
    mylex = lex.lex()
    mylex.input("\n".join(FieldLines))

    Parser = yacc.yacc(errorlog = yacc.NullLogger())
    Result = Parser.parse(input = "\n".join(FieldLines), lexer = mylex)
    EndTime = datetime.datetime.now()
    print("Parsing tree succesfully built.(" + str(EndTime - StartTime) + ")")

    #
    # Generate H file
    #
    ParserOutputFileH = open(os.path.join(HPath, OutFileNameH)+'.temp', "w")
    ParserOutputFileH.write(ReminderStr + "\n" + CopyrightStr + "\n")
    ParserOutputFileH.write("#ifndef " + HeaderDefineStr + "_H_\n")
    ParserOutputFileH.write("#define " + HeaderDefineStr + "_H_\n")
    ParserOutputFileH.write("\n#pragma pack (push,1)\ntypedef struct {\n")
    NewOffsetInfo = OffSetInfo(0, 0)
    PrintLineBlockToH(Result, NewOffsetInfo, ParserOutputFileH)
    ParserOutputFileH.write("} " + StructureName + ";\n")
    ParserOutputFileH.write("\n#pragma pack(pop)\n")
    ParserOutputFileH.write("\n".join(PostfixLines))
    ParserOutputFileH.write("#endif\n")
    ParserOutputFileH.close()
    # if the orignal h file's content is same as the current one
    # than don't generate the new one
    if os.path.isfile(os.path.join(HPath, OutFileNameH)) :
        if filecmp.cmp(os.path.join(HPath, OutFileNameH)+'.temp',os.path.join(HPath, OutFileNameH)):
            os.remove(os.path.join(HPath, OutFileNameH)+'.temp')
        else:
            os.remove(os.path.join(HPath, OutFileNameH))
            os.rename(os.path.join(HPath, OutFileNameH)+'.temp',os.path.join(HPath, OutFileNameH))
    else:
        os.rename(os.path.join(HPath, OutFileNameH)+'.temp',os.path.join(HPath, OutFileNameH))
    print("Header file '" + os.path.join(HPath, OutFileNameH) + "' has been generated automatically.")

    #
    # Generate ASL file
    #
    ParserOutputFileASL = open(os.path.join(ASLPath, OutFileNameASL)+'.temp', "w")
    ParserOutputFileASL.write(ReminderStr + "\n" + CopyrightStr + "\n")
    ParserOutputFileASL.write("\n\n  " + "\n".join(OperationLines))
    NewOffsetInfo = OffSetInfo(0, 0)
    PrintLineBlockToASL(Result, NewOffsetInfo, ParserOutputFileASL)
    ParserOutputFileASL.write("\n".join(PostfixLines))
    ParserOutputFileASL.close()
    # if the orignal asl file's content is same as the current one
    # than don't generate the new one
    if os.path.isfile(os.path.join(ASLPath, OutFileNameASL)) :
        if filecmp.cmp(os.path.join(ASLPath, OutFileNameASL)+'.temp',os.path.join(ASLPath, OutFileNameASL)):
            os.remove(os.path.join(ASLPath, OutFileNameASL)+'.temp')
        else:
            os.remove(os.path.join(ASLPath, OutFileNameASL))
            os.rename(os.path.join(ASLPath, OutFileNameASL)+'.temp',os.path.join(ASLPath, OutFileNameASL))
    else:
        os.rename(os.path.join(ASLPath, OutFileNameASL)+'.temp',os.path.join(ASLPath, OutFileNameASL))
    print("ASL file '" + os.path.join(ASLPath, OutFileNameASL) + "' has been generated automatically.")


def PrintLineBlockToH(LineBlock, OldOffsetInfo, ParserOutputFileH):
    InArray = False
    ArrayName = ""
    ArrayElementSize = 0
    for Line in LineBlock.List:
        if(Line.Type == "OneLine"):
            if(Line.SubType == "Variable"):
                Line.Str = Line.Str.replace("\n", "")
                CombinedStr = Line.Str.replace("///<", "") # incase ///<
                CombinedStr = CombinedStr.replace("///", "")
                CombinedStr = CombinedStr.replace("//", "") # incase only 2 slash
                VariableName = ""
                CommentStr = ""
                if(CombinedStr.find("]") != -1):
                    SplitedStr = CombinedStr.split("]", 1)
                    VariableName = SplitedStr[0].replace(" ", "")
                    VariableName = VariableName.replace("[", "")
                    if(VariableName == ""):
                        VariableName = Line.Text
                    CommentStr = SplitedStr[1].strip()
                else:
                    VariableName = Line.Text
                    CommentStr = CombinedStr.strip()
                if(VariableName == ""):
                    print("No variable name for line end with: " + CombinedStr)
                    sys.exit(1)
                if(Line.Text == ""):
                    Line.Text = "    "
                #
                # if it is an array start
                #
                if(InArray == True and VariableName.find(",") == -1):
                    if(CommentStr != ""):
                        #
                        # "{<51} ///< Offset {<7} {}\n"
                        #
                        ParserOutputFileH.write("{0:<51} ".format(" "))
                        ParserOutputFileH.write("///< Offset ")
                        ParserOutputFileH.write("{0:<7} ".format(OldOffsetInfo.OffsetAccumulator))
                        ParserOutputFileH.write("{0}\n".format(CommentStr))
                    OldOffsetInfo.OffsetAccumulator += ArrayElementSize
                elif(InArray == True and
                     (VariableName.find(",") != -1 or
                      VariableName.find("End") != -1 or
                      VariableName.find("end") != -1 or
                      VariableName.find("END") != -1)):
                    if(CommentStr != ""):
                        #
                        # "{0:<51} ///< Offset {1:<7} {2}\n"
                        #
                        ParserOutputFileH.write("{0:<51} ".format(" "))
                        ParserOutputFileH.write("///< Offset ")
                        ParserOutputFileH.write("{0:<7} ".format(OldOffsetInfo.OffsetAccumulator))
                        ParserOutputFileH.write("{0}\n".format(CommentStr))
                    OldOffsetInfo.OffsetAccumulator += ArrayElementSize
                    InArray = False
                elif(InArray == False and VariableName.find(",") != -1):
                    InArray = True
                    ArrayName = (VariableName.split(",", 1)[0] +
                                 "[" +
                                 VariableName.split(",", 1)[1] +
                                 "];")
                    DeclareStr = "UINT{0}".format(Line.Int)
                    #
                    # "  {0:<8} {1:40} ///< Offset {2:<7} {3}\n"
                    #
                    ParserOutputFileH.write("  {0:<8} ".format(DeclareStr))
                    ParserOutputFileH.write("{0:40} ".format(ArrayName))
                    ParserOutputFileH.write("///< Offset ")
                    # if Commentstr is empty than skip to next line
                    if CommentStr != '':
                        ParserOutputFileH.write("{0:<7} ".format(OldOffsetInfo.OffsetAccumulator))
                    else:
                        ParserOutputFileH.write("{0}".format(OldOffsetInfo.OffsetAccumulator))
                    ParserOutputFileH.write("{0}\n".format(CommentStr))
                    OldOffsetInfo.OffsetAccumulator += int(Line.Int / 8)
                    ArrayElementSize = int(Line.Int / 8)
                else:
                    VariableName = VariableName + ";"
                    DeclareStr = "UINT{0}".format(Line.Int)
                    #
                    # "  {0:<8} {1:40} ///< Offset {2:<7} {3}\n"
                    #
                    ParserOutputFileH.write("  {0:<8} ".format(DeclareStr))
                    ParserOutputFileH.write("{0:40} ".format(VariableName))
                    ParserOutputFileH.write("///< Offset ")
                    # if Commentstr is empty than skip to next line
                    if CommentStr != '':
                        ParserOutputFileH.write("{0:<7} ".format(OldOffsetInfo.OffsetAccumulator))
                    else:
                        ParserOutputFileH.write("{0}".format(OldOffsetInfo.OffsetAccumulator))
                    ParserOutputFileH.write("{0}\n".format(CommentStr))
                    OldOffsetInfo.OffsetAccumulator += int(Line.Int / 8)
            elif(Line.SubType == "Offset"):
                OffsetStr = Line.Str.replace("\n", "")
                OffsetStr = OffsetStr.replace(" ", "")
                OffsetStr = OffsetStr.replace("Offset(", "")
                OffsetStr = OffsetStr.replace(")", "")
                OffsetNum = int(OffsetStr, 0)
                OffsetArraySize = OffsetNum - OldOffsetInfo.OffsetAccumulator
                if(OffsetArraySize >= 0):
                    #
                    # "UINT8    Reserved{0}[{1}];"
                    #
                    ReservedStr = "UINT8    Reserved"
                    ReservedStr += str(OldOffsetInfo.OffsetSerialNum)
                    ReservedStr += "[" + str(OffsetArraySize) + "];"
                    #
                    # "  {0:<49} ///< Offset {1}:{2}\n"
                    #
                    # if OffsetArraySize > 0 than write Reserved offset
                    if OffsetArraySize:
                        ParserOutputFileH.write("  {0:<49} ".format(ReservedStr))
                        ParserOutputFileH.write("///< Offset ")
                        ParserOutputFileH.write("{0}".format(OldOffsetInfo.OffsetAccumulator))
                        ParserOutputFileH.write(":{0}\n".format(OffsetNum - 1))
                        OldOffsetInfo.OffsetSerialNum += 1
                    OldOffsetInfo.OffsetAccumulator = OffsetNum
                else:
                    print("ERROR: Offset overflow: " + Line.Str)
                    sys.exit(1)
            elif(Line.SubType == "PureComment"):
                ParserOutputFileH.write("  " + Line.Str)
        elif(Line.Type == "IfBlock"):
            ParserOutputFileH.write("  " + Line.Str)
            if(Line.OneLinePart.SubType == "PureRCBracket"):
                IfOffsetInfo = OffSetInfo(
                                 OldOffsetInfo.OffsetAccumulator,
                                 OldOffsetInfo.OffsetSerialNum)
                PrintLineBlockToH(Line.IfPart, IfOffsetInfo, ParserOutputFileH)
            elif(Line.OneLinePart.SubType == "Offset"):
                IfOffsetInfo = OffSetInfo(
                                 OldOffsetInfo.OffsetAccumulator,
                                 OldOffsetInfo.OffsetSerialNum)
                PrintLineBlockToH(Line.IfPart, IfOffsetInfo, ParserOutputFileH)
                OffsetStr = Line.OneLinePart.Str.replace("\n", "")
                OffsetStr = OffsetStr.replace(" ", "")
                OffsetStr = OffsetStr.replace("Offset(", "")
                OffsetStr = OffsetStr.replace(")", "")
                OffsetNum = int(OffsetStr, 0)
                OffsetArraySize = OffsetNum - IfOffsetInfo.OffsetAccumulator
                if(OffsetArraySize >= 0):
                    #
                    # "UINT8    Reserved{0}[{1}];"
                    #
                    ReservedStr = "UINT8    Reserved"
                    ReservedStr += str(IfOffsetInfo.OffsetSerialNum)
                    ReservedStr += "[" + str(OffsetArraySize) + "];"
                    #
                    # "  {0:<49} ///< Offset {1}:{2}\n"
                    #
                    # if OffsetArraySize > 0 than write Reserved offset
                    if OffsetArraySize:
                        ParserOutputFileH.write("  {0:<49} ".format(ReservedStr))
                        ParserOutputFileH.write("///< Offset ")
                        ParserOutputFileH.write("{0}".format(IfOffsetInfo.OffsetAccumulator))
                        ParserOutputFileH.write(":{0}\n".format(OffsetNum - 1))
                        OldOffsetInfo.OffsetSerialNum = IfOffsetInfo.OffsetSerialNum + 1
                    #
                    # should not update OffsetAccumulator here
                    #
                else:
                    print("ERROR: Offset overflow: " + Line.OneLinePart.Str)
                    sys.exit(1)
            else:
                print("ERROR: No Offset nor Right Curly Bracket detected after:\n" +
                      Line.Str +
                      "...\n#endif")
                sys.exit(1)

            if(Line.OneLinePart.SubType == "Offset" or Line.NoElsePart == False):
                ParserOutputFileH.write("  #else\n")
                ElseOffsetInfo = OffSetInfo(
                                   OldOffsetInfo.OffsetAccumulator,
                                   OldOffsetInfo.OffsetSerialNum)
                PrintLineBlockToH(Line.ElsePart, ElseOffsetInfo, ParserOutputFileH)
                if(Line.OneLinePart.SubType == "Offset"):
                    OffsetStr = Line.OneLinePart.Str.replace("\n", "")
                    OffsetStr = OffsetStr.replace(" ", "")
                    OffsetStr = OffsetStr.replace("Offset(", "")
                    OffsetStr = OffsetStr.replace(")", "")
                    OffsetNum = int(OffsetStr, 0)
                    OffsetArraySize = OffsetNum - ElseOffsetInfo.OffsetAccumulator
                    if(OffsetArraySize >= 0):
                        #
                        # "UINT8    Reserved{0}[{1}];"
                        #
                        ReservedStr = "UINT8    Reserved"
                        ReservedStr += str(ElseOffsetInfo.OffsetSerialNum)
                        ReservedStr += "[" + str(OffsetArraySize) + "];"
                        #
                        # "  {0:<49} ///< Offset {1}:{2}\n"
                        #
                        # if OffsetArraySize > 0 than write Reserved offset
                        if OffsetArraySize:
                            ParserOutputFileH.write("  {0:<49} ".format(ReservedStr))
                            ParserOutputFileH.write("///< Offset ")
                            ParserOutputFileH.write("{0}".format(ElseOffsetInfo.OffsetAccumulator))
                            ParserOutputFileH.write(":{0}\n".format(OffsetNum - 1))
                            OldOffsetInfo.OffsetSerialNum = ElseOffsetInfo.OffsetSerialNum + 1
                        OldOffsetInfo.OffsetAccumulator = OffsetNum
                    else:
                        print("ERROR: Offset overflow: " + Line.OneLinePart.Str)
                        sys.exit(1)

            ParserOutputFileH.write("  #endif\n")


def PrintLineBlockToASL(LineBlock, OldOffsetInfo, ParserOutputFileASL):
    for Line in LineBlock.List:
        if(Line.Type == "OneLine"):
            if(Line.SubType == "Variable"):
                OffsetStr = "Offset(" + str(OldOffsetInfo.OffsetAccumulator) + "),"
                LSBracket = Line.Str.find("[")
                RSBracket = Line.Str.find("]")
                Line.Str = Line.Str.replace(Line.Str[LSBracket:RSBracket + 1], "")
                Line.Str = Line.Str.replace("//", "").strip()
                Line.Str = "// " + "{0:<15}".format(OffsetStr) + Line.Str
                #
                # "  {0:<15} {1:<5} {2:<3} {3}\n"
                #
                ParserOutputFileASL.write("  {0:<15} ".format(OffsetStr))
                ParserOutputFileASL.write("{0:<5} ".format(Line.Text + ","))
                ParserOutputFileASL.write("{0:<3} ".format(str(Line.Int) + ","))
                ParserOutputFileASL.write("{0}\n".format(Line.Str.strip()))
                OldOffsetInfo.OffsetAccumulator += int(Line.Int / 8)
            elif(Line.SubType == "Offset"):
                OffsetStr = Line.Str.replace("\n", "")
                OffsetStr = OffsetStr.replace(" ", "")
                OffsetStr = OffsetStr.replace("Offset(", "")
                OffsetStr = OffsetStr.replace(")", "")
                OffsetNum = int(OffsetStr, 0)
                #
                # "  {0:<15}{1:11}// Offset({2}) : Offset({3}), Reserved bytes\n"
                #
                ParserOutputFileASL.write("  {0:<15}".format(Line.Str + ","))
                ParserOutputFileASL.write("{0:11}".format(" "))
                ParserOutputFileASL.write("// Offset({0})".format(OldOffsetInfo.OffsetAccumulator))
                ParserOutputFileASL.write(" : Offset({0}), ".format(OffsetNum - 1))
                ParserOutputFileASL.write("Reserved bytes\n")
                OldOffsetInfo.OffsetAccumulator = OffsetNum
            elif(Line.SubType == "PureComment"):
                ParserOutputFileASL.write("  " + Line.Str)
            elif(Line.SubType == "PureLCBracket"):
                ParserOutputFileASL.write(Line.Str + "\n")
            elif(Line.SubType == "PureRCBracket"):
                ParserOutputFileASL.write("  " + Line.Str)
        elif(Line.Type == "IfBlock"):
            ParserOutputFileASL.write("  " + Line.Str)
            IfOffsetInfo = OffSetInfo(
                             OldOffsetInfo.OffsetAccumulator,
                             OldOffsetInfo.OffsetSerialNum)
            PrintLineBlockToASL(Line.IfPart, IfOffsetInfo, ParserOutputFileASL)
            if(Line.NoElsePart == False):
                ParserOutputFileASL.write("  #else\n")
                ElseOffsetInfo = OffSetInfo(
                                   OldOffsetInfo.OffsetAccumulator,
                                   OldOffsetInfo.OffsetSerialNum)
                PrintLineBlockToASL(Line.ElsePart, ElseOffsetInfo, ParserOutputFileASL)
            ParserOutputFileASL.write("  #endif\n")
            if(Line.OneLinePart.SubType == "Offset"):
                OffsetStr = Line.OneLinePart.Str.replace("\n", "")
                OffsetStr = OffsetStr.replace(" ", "")
                OffsetStr = OffsetStr.replace("Offset(", "")
                OffsetStr = OffsetStr.replace(")", "")
                OffsetNum = int(OffsetStr, 0)
                #
                # "  {0:<15}{1:11}// Offset({2}) : Offset({3}), Reserved bytes\n"
                #
                ParserOutputFileASL.write("  {0:<15}".format(Line.OneLinePart.Str + ","))
                ParserOutputFileASL.write("{0:11}".format(" "))
                ParserOutputFileASL.write("// Offset({0}) : ".format(OldOffsetInfo.OffsetAccumulator))
                ParserOutputFileASL.write("Offset({0}), ".format(OffsetNum - 1))
                ParserOutputFileASL.write("Reserved bytes\n")
                OldOffsetInfo.OffsetAccumulator = OffsetNum
            elif(Line.OneLinePart.SubType == "PureRCBracket"):
                ParserOutputFileASL.write("  " + Line.OneLinePart.Str + "\n")


#
# Entry Point
#
if __name__ == "__main__":
    Main(sys.argv[1:])
