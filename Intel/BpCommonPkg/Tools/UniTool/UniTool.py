#
# This file contains a 'Sample Driver' and is licensed as such
# under the terms of your license agreement with Intel or your
# vendor.  This file may be modified by the user, subject to
# the additional terms of the license agreement
#
## @file
# UniTool.py v2.2
#
# Copyright (c) 2011 - 2017, Intel Corporation. All rights reserved.
# This software and associated documentation (if any) is furnished
# under a license and may only be used or copied in accordance
# with the terms of the license. Except as permitted by such
# license, no part of this software or documentation may be
# reproduced, stored in a retrieval system, or transmitted in any
# form or by any means without the express written consent of
# Intel Corporation.
#
# Change log:
#
# 2.2 - 04/10/2017
#   - Add UTF8 format uni file support.
#   - Add linux support.
#
# 2.1 - 11/02/2016
#   - Updated to return error if no definition for any string referred by HII question.
#   - Updated to support -q option to check if different HII questions are referring same string token.
#
# 2.0 - 11/25/2014
#   - Updated to support both client and server. Add multiple rootDirectory support.
#
# 1.8 - 04/04/2012
#   - Updated to support 2 excludedDirectory
#
# 1.7 - 11/19/2011
#   - Ignoring strings defined as STRING_TOKEN(0)
#

version = 2.2

import re, sys, os, getopt, string, codecs, fnmatch

# global variable declarations
questionError = False
uqiList = re.compile('^#string[ \t]+([A-Z_0-9]+)[ \t]+#language[ \t]+uqi[ \t\r\n]+"(?:[x\S]{1,2})([0-9a-fA-F]{4,5})"',re.M).findall
allUqis = {}
stringDict = {}
GlobalVarId = {}
options = {}

#**********************************************************************
# description: Prints help information
#
# arguments:   none
#
# returns:     none
#

def usage () :
  sys.exit("Syntax:  %s [-b] [-u] [-l] [-x] [-h] [-d 'rootDirectory1'] [-d 'rootDirectory2'] [-d 'rootDirectory3']... [-q e|w] \
'rootDirectory0' 'uqiFile'|'uqiFileDirectory' ['excludedDirectory1'] ['excludedDirectory2'] ['excludedDirectory3']...\n%s" %
    (os.path.basename(sys.argv[0]),
      """\nFunction will sync up UQI definitions with uni files based on vfi/vfr/hfr/sd/sdi in the tree.\n
Required Arguments:
  'rootdirectory0'       path to root directory
  'uqiFileDirectory'     path to UQI file(UqiList.uni)
  'uqiFile'              UQI file

Options:
  -h                    Show this help
  -b                    Build option returns error if any new UQI needs assigning
                        based on vfi/vfr/hfr/sd/sdi when no -u option is specified
  -u                    Create new UQIs that does not already exist in uqiFile for
                        any string requiring a UQI based on vfi/vfr/hfr/sd/sdi
                        NOTE: 'uqiFile' cannot be readonly!
  -l                    Language deletion option (keeps only English and uqi)
                        moves all UQIs to 'uqiFile'
                        NOTE: Uni files cannot be readonly!
  -x                    Exclude 'rootDirectory'/'excludedDirectory1' &
                        'rootDirectory'/'excludedDirectory2'... from UQI list build
                        NOTE: Cannot be the same as rootDirectory
  -d                    Add multiple root directories to process
  -q                    Print warning(w) or return error(e) if different HII questions
                        are referring same string token

Return error if any duplicated UQI string or value in UQI list or if no definition
for any string referred by HII question when -b or -u is specified

NOTE: Options must be specified before parameters
"""))

#**********************************************************************
# description: Get uni file encoding
#
# arguments:   filename - name of uni file
#
# returns:     utf-8 or utf-16
#
def GetUniFileEncoding(filename):
  #
  # Detect Byte Order Mark at beginning of file.  Default to UTF-8
  #
  Encoding = 'utf-8'

  #
  # Read file
  #
  try:
    UniFile = open(filename, mode='rb')
    FileIn = UniFile.read()
    UniFile.close()
  except:
    return Encoding

  if (FileIn.startswith(codecs.BOM_UTF16_BE) or FileIn.startswith(codecs.BOM_UTF16_LE)):
    Encoding = 'utf-16'


  #print ("%s is encoding with %s format." %(filename, Encoding))
  return Encoding

#**********************************************************************
# description: Parses commandline arguments and options
#              Calls function processUni to build dictionary of strings
#              Calls other functions according to user specified options
#
# arguments:   argv - contains all input from command line
#                   - must contain path to root directory
#                   - may contain options -h, -u, -l, -b or -x before path
#
# returns:     none
#
def main(argv) :
##### Read input arguments and options
  global allUqis, uqiList, questionError
  try:
    opts, args = getopt.getopt(argv[1:], "hulbxd:q:") # each letter is an optional argument
  except getopt.GetoptError:
    usage()
  try:
    dirNameList = [args[0]]
    QuestionOption = None
    for eachOpt in opts:
      if eachOpt[0] == '-d':
        dirNameList.append(eachOpt[1])
      if eachOpt[0] == '-q':
        QuestionOption = eachOpt[1]
        if (QuestionOption != "e") and (QuestionOption != "w"):
          print "\nERROR: invalid option value for -q option\n"
          raise Exception
    destname = args[1]
    if len(args) > 2:
      exDirList = args[2:]
  except:
    usage()

  UpdateUQIs = False
  LangOption = False
  BuildOption = False
  ExcludeOption = False
  exPathList = []

  for o,a in opts:
    if o == "-h":
      usage()
    if o == "-b":
      BuildOption = True
    if o == "-u":
      BuildOption = True
      UpdateUQIs = True
    if o == "-l":
      LangOption = True
    if o == "-x":
      ExcludeOption = True
      try:
        for eachExDir in exDirList:
          for eachRootDir in dirNameList:
            if eachExDir == eachRootDir:
              print "\nERROR: excludedDirectory is same as rootDirectory\n"
              raise Exception
          exPathList.append(eachRootDir + os.sep + eachExDir)
      except:
        usage()

  global options
  options = {'destname':destname, 'dirNameList':dirNameList, 'exPathList':exPathList, 'BuildOption':BuildOption, 'UpdateUQIs':UpdateUQIs,
             'LangOption':LangOption, 'ExcludeOption':ExcludeOption, 'QuestionOption':QuestionOption}
  print ("UQI file: %s" %destname)
  for eachDirName in dirNameList:
    os.path.walk(eachDirName, processUni, None)
  if questionError:
    raise RuntimeError
    return
  if os.path.isdir(options['destname']):
    destFileName = options['destname']+os.sep+'UqiList.uni'
  else:
    destFileName = options['destname']
  if os.path.exists(destFileName) and (destFileName not in allUqis.keys()):
    try:
      Encoding = GetUniFileEncoding (destFileName)
      destFile = codecs.open(destFileName, 'r+', Encoding)
      destFileBuffer = destFile.read()
      destFile.close()
    except IOError,(Errnum,stringErr):
      print "ERROR: " + stringErr
      raise RuntimeError
      return
    allUqis[destFileName]= uqiList(destFileBuffer)
  returnVal = 0
  if BuildOption:
    returnVal = newUqi()
    if (returnVal == 1):
      raise RuntimeError, 'Please fix UQI ERROR(s) above before proceeding.'
    else:
      print "No UQI issues detected\n"
  return

#**********************************************************************
# description: newUqi collects a list of all currently used uqi values in the tree
#              Halt build if any duplicated string or value in UQI list.
#              If -u option was specified, creates new UQIs that does not
#              already exist in uqiFile for any string requiring a UQI.
#
# arguments:   none
#
# returns:     0 on success
#              1 on error - this should cause the build to halt
#

syntax = "S"
syntaxRE = re.compile('#string[ \t]+[A-Z_0-9]+[ \t]+#language[ \t]+uqi[ \t\r\n]+"([x\S]{1,2}).*',re.DOTALL).findall

def newUqi():
  global options, GlobalVarId, allUqis, syntax, syntaxRE
  uqiRange=[]
  uqiStringList=[]
  createUQI=[]
  returnVal  = 0
  BaseNumSpaces = 47 # Used to line up the UQI values in the resulting uqiFile

  # Look for duplication in the current UQIs and collect current range of UQIs
  for path in allUqis.keys():
    for uqiString in allUqis[path]: # path contains the path and filename of each uni file
      #Checks for duplicated strings in UQI list
      for tempString in uqiStringList:
        if tempString == uqiString[0]:
          print ("ERROR: UQI string %s was assigned more than once and will cause corruption!" %uqiString[0])
          print "Delete one occurrence of the string and rerun tool."
          returnVal = 1 #halt build

      uqiStringList.append(uqiString[0])

      #Checks for duplicated UQI values in UQI list
      if int(uqiString[1],16) in uqiRange:
        print ("ERROR: UQI value %04x was assigned more than once and will cause corruption!" %int(uqiString[1],16))
        print "Delete one occurrance of the UQI and rerun tool to create alternate value."
        returnVal = 1 #halt build
      uqiRange.append(int(uqiString[1],16))

  for stringValue in GlobalVarId.keys():
    stringFound = False
    for path in stringDict.keys():
      for uniString in stringDict[path]: # path contains the path and filename of each uni file
        if (stringValue == uniString):
          #print ("Found %s in %s" %(stringValue, path))
          stringFound = True
          break
    if not stringFound:
      print ("ERROR: No definition for %s referred by HII question" %(stringValue))
      returnVal = 1 #halt build

  # Require a UQI for any string in vfr/vfi files
  for stringValue in GlobalVarId.keys():
    # Ignore strings defined as STRING_TOKEN(0)
    if (stringValue != "0"):
      # Check if this string already exists in the UQI list
      if (stringValue not in uqiStringList) and (stringValue not in createUQI):
        createUQI.append(stringValue)
        if not options['UpdateUQIs']:
          print ("ERROR: No UQI for %s referred by HII question" %(stringValue))
          returnVal = 1 # halt build after printing all error messages

  if (returnVal == 1):
    return returnVal

  # Update uqiFile with necessary UQIs
  if options['UpdateUQIs'] and createUQI:
    if os.path.isdir(options['destname']):
      destFileName = options['destname']+os.sep+'UqiList.uni'
    else:
      destFileName = options['destname']
    try:
      Encoding = GetUniFileEncoding (destFileName)
      outputFile = codecs.open(destFileName, 'r+', Encoding)
      platformUQI=outputFile.read()
    except IOError,(Errnum,stringErr):
      print "ERROR: " + stringErr
      if (Errnum==2):
        try:
          outputFile = codecs.open(destFileName, 'w', Encoding)
          print destFileName + " did not exist.  Creating new file."
          platformUQI=''
        except:
          print "Error creating " + destFileName + "."
          return 1
      if (stringErr=="Permission denied"):
        print "\n%s is Readonly.  You must uncheck the ReadOnly attibute to run the -u option.\n" %destFileName
        return 1

    #Determines and sets the UQI number format
    #TODO: there is probably a more elegant way to do this...
    syntaxL = syntaxRE(platformUQI)
    if len(syntaxL) != 0:
      syntax = syntaxL[0]

    # script is reading the file in and writing it back instead of appending because the codecs module
    # automatically adds a BOM wherever you start writing. This caused build failure.
    uqiRange.sort()
    if (uqiRange == []):
      nextUqi = 0
    else:
      nextUqi = uqiRange[len(uqiRange) - 1] + 1

    for stringValue in createUQI:
      print "%s will be assigned a new UQI value" %stringValue
      uqiRange.append(nextUqi)
      #
      # Lines up the UQI values in the resulting uqiFile
      #
      spaces = " "*(BaseNumSpaces - len(stringValue))
      platformUQI += '#string %s%s #language uqi \"%s%04x\"\r\n' %(stringValue,spaces,syntax,nextUqi)
      print ("#string %s%s #language uqi  \"%s%04X\"" %(stringValue, spaces, syntax, nextUqi))
      nextUqi += 1

    outputFile.seek(0)
    outputFile.write(platformUQI)
    outputFile.close()

  return 0


#**********************************************************************
# description: Parses each uni file to collect dictionary of strings
#              Removes additional languages and overwrites current uni files
#              if -l option was specified
#
# arguments:   path - directory location of file including file name
#              filename - name of file to be modified
#
# returns:     error string if failure occurred;
#              none if completed sucessfully
#
# the following are global so that parsefile is quicker

findUniString = re.compile('^#string[ \t]+([A-Z_0-9]+)(?:[ \t\r\n]+#language[ \t]+[a-zA-Z-]{2,5}[ \t\r\n]+".*"[ \t]*[\r]?[\n]?)*',re.M).findall

otherLang = re.compile('^#string[ \t]+[A-Z_0-9]+(?:[ \t\r\n]+#language[ \t]+[a-zA-Z-]{2,5}[ \t\r\n]+".*"[ \t]*[\r]?[\n]?)*',re.M).findall
eachLang = re.compile('[ \t\r\n]+#language[ \t]+([a-zA-Z-]{2,5})[ \t\r\n]+".*"[ \t]*[\r]?[\n]?').findall

uqiStrings = re.compile('^#string[ \t]+[A-Z_0-9]+[ \t]+#language[ \t]+uqi[ \t\r\n]+".*"[ \t]*[\r]?[\n]?',re.M)

def parsefile(path,filename):
  global options, stringDict, allUqis, uqiList, findUniString, otherLang, eachLang, uqiStrings

  FullPath = path+os.sep+filename

  try:
    UniEncoding = GetUniFileEncoding (FullPath)
    UniFile = codecs.open(FullPath, 'r', UniEncoding)
    databuffer = UniFile.read()
    UniFile.close()
  except:
    return ("Error opening " + FullPath + " for reading.")
  writeFile = False

  if os.path.isdir(options['destname']):
    destFileName = options['destname']+os.sep+'UqiList.uni'
  else:
    destFileName = options['destname']

  if options['LangOption']:
    try:
      UqiEncoding = GetUniFileEncoding (destFileName)
      outputFile = codecs.open(destFileName, 'r+', UqiEncoding)
      platformUQI=outputFile.read()
    except IOError,(Errnum,stringErr):
      print "ERROR: " + stringErr
      if (Errnum==2):
        try:
          outputFile = codecs.open(destFileName, 'w', UqiEncoding)
          print destFileName + " did not exist.  Creating new file."
          platformUQI=''
        except:
          return ("Error creating " + destFileName + ".")
      else:
        return ("Error opening " + destFileName + " for appending.")

    if (filename!=string.split(destFileName, os.sep)[-1]):
      Uqis = re.findall(uqiStrings,databuffer)
      if Uqis:
        for uqi in Uqis:
          platformUQI += uqi
        outputFile.seek(0)
        outputFile.write(platformUQI)
        outputFile.close()
      databuffer = re.sub(uqiStrings, '', databuffer)
      if Uqis:
        writeFile = True
        print "Deleted uqis from %s" %FullPath
      stringlist = otherLang(databuffer)
      for stringfound in stringlist:
        thisString = eachLang(stringfound)
        for languageFound in thisString:
          if ((languageFound != 'en') and (languageFound != 'en-US') and (languageFound != 'eng') and (languageFound != 'uqi')):
            databuffer = re.sub(re.escape(stringfound), '', databuffer)
            writeFile = True
            print "Deleted %s from %s" %(languageFound, FullPath)
  if (filename!=string.split(destFileName, os.sep)[-1]):
    #adding strings to dictionary
    stringDict[r'%s' %FullPath]= findUniString(databuffer)
  #adding UQIs to dictionary
  allUqis[r'%s' %FullPath]= uqiList(databuffer)

  if writeFile:
    try:
      UniFile = codecs.open(FullPath, 'w', UniEncoding)
      UniFile.write(databuffer)
      UniFile.close()
    except:
      return ("Error opening " + FullPath + " for writing.")
  return

#**********************************************************************
# description: Searches tree for uni files
#              Calls parsefile to collect dictionary of strings in each uni file
#              Calls searchVfiFile for each vfi or vfr file found
#
# arguments:   argument list is built by os.path.walk function call
#              arg     - None
#              dirname - directory location of files
#              names   - specific files to search in directory
#
# returns:     none
#
def processUni(args,dirname,names) :
  global options
  #Remove excludedDirectory
  if options['ExcludeOption']:
    for eachExDir in options['exPathList']:
      for dir in names:
        if os.path.join(dirname,dir) == eachExDir:
          names.remove(dir)

  for entry in names:
    FullPath = dirname+os.sep+entry
    if fnmatch.fnmatch(FullPath,'*.uni'):
      parsefile(dirname,entry)
    if fnmatch.fnmatch(FullPath,'*.vf*'):
      searchVfiFile(FullPath)
    if fnmatch.fnmatch(FullPath,'*.sd'):
      searchVfiFile(FullPath)
    if fnmatch.fnmatch(FullPath,'*.sdi'):
      searchVfiFile(FullPath)
    if fnmatch.fnmatch(FullPath,'*.hfr'):
      searchVfiFile(FullPath)
  return

#**********************************************************************
# description: Compose a dictionary of all strings that may need UQIs assigned
#              to them and key is the string
#
# arguments:   filename - name of file to search for strings
#
# returns:     none
#

#separate regexes for readability
stringGroups = re.compile('^[ \t]*(?:oneof|numeric|checkbox|orderedlist)[ \t]+varid.+?(?:endoneof|endnumeric|endcheckbox|endorderedlist);', re.DOTALL|re.M).findall
stringVarIds = re.compile('[ \t]*(?:oneof|numeric|checkbox|orderedlist)[ \t]+varid[ \t]*=[ \t]*([a-zA-Z_0-9]+\.[a-zA-Z_0-9]+)').findall
stringTokens = re.compile('prompt[ \t]*=[ \t]*STRING_TOKEN[ \t]*\(([a-zA-Z_0-9]+)\)').findall

def searchVfiFile(filename) :
  global options, GlobalVarId, stringGroups, stringVarIds, stringTokens, questionError
  try:
    vfiFile = open(filename, 'r')
    databuffer=vfiFile.read()
    vfiFile.close()

    # Finds specified lines in file
    vfiStringGroup = stringGroups(databuffer)

    # Searches for prompts within specified lines
    for eachGroup in vfiStringGroup:
      for eachString in stringTokens(eachGroup):
        # Ignore strings defined as STRING_TOKEN(0), STRING_TOKEN(STR_EMPTY) or STRING_TOKEN(STR_NULL)
        if (eachString != "0") and (eachString != "STR_EMPTY") and (eachString != "STR_NULL"):
          if not GlobalVarId.has_key(eachString):
            GlobalVarId[eachString]=stringVarIds(eachGroup)
          else:
            if (GlobalVarId[eachString][0] != stringVarIds(eachGroup)[0]):
              if options['QuestionOption']:
                if options['QuestionOption'] == "e":
                  questionError = True
                  print ("ERROR:"),
                if options['QuestionOption'] == "w":
                  print ("WARNING:"),
                print ("%s referred by different HII questions(%s and %s)" %(eachString, GlobalVarId[eachString][0], stringVarIds(eachGroup)[0]))
  except:
    print ("Error opening file at %s for reading." %filename)

if __name__ == '__main__' :
  print "UniTool v%s" %version
  sys.exit(main(sys.argv))
