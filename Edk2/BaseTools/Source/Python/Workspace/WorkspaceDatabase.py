## @file
# This file is used to create a database used by build tool
#
# Copyright (c) 2008 - 2018, Intel Corporation. All rights reserved.<BR>
# (C) Copyright 2016 Hewlett Packard Enterprise Development LP<BR>
# This program and the accompanying materials
# are licensed and made available under the terms and conditions of the BSD License
# which accompanies this distribution.  The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#

##
# Import Modules
#
from __future__ import absolute_import
#import sqlite3                          # CCEO-0018: RoyalParkOverrideContent
from Common.StringUtils import *
from Common.DataType import *
from Common.Misc import *
from types import *

from .MetaDataTable import *
from .MetaFileTable import *
from .MetaFileParser import *

from Workspace.DecBuildData import DecBuildData
from Workspace.DscBuildData import DscBuildData
from Workspace.InfBuildData import InfBuildData

## Database
#
#   This class defined the build database for all modules, packages and platform.
# It will call corresponding parser for the given file if it cannot find it in
# the database.
#
# @param DbPath             Path of database file
# @param GlobalMacros       Global macros used for replacement during file parsing
# @prarm RenewDb=False      Create new database file if it's already there
#
class WorkspaceDatabase(object):

    #
    # internal class used for call corresponding file parser and caching the result
    # to avoid unnecessary re-parsing
    #
    class BuildObjectFactory(object):

        _FILE_TYPE_ = {
            ".inf"  : MODEL_FILE_INF,
            ".dec"  : MODEL_FILE_DEC,
            ".dsc"  : MODEL_FILE_DSC,
        }

        # file parser
        _FILE_PARSER_ = {
            MODEL_FILE_INF  :   InfParser,
            MODEL_FILE_DEC  :   DecParser,
            MODEL_FILE_DSC  :   DscParser,
        }

        # convert to xxxBuildData object
        _GENERATOR_ = {
            MODEL_FILE_INF  :   InfBuildData,
            MODEL_FILE_DEC  :   DecBuildData,
            MODEL_FILE_DSC  :   DscBuildData,
        }

        _CACHE_ = {}    # (FilePath, Arch)  : <object>

        # constructor
        def __init__(self, WorkspaceDb):
            self.WorkspaceDb = WorkspaceDb

        # key = (FilePath, Arch=None)
        def __contains__(self, Key):
            FilePath = Key[0]
            if len(Key) > 1:
                Arch = Key[1]
            else:
                Arch = None
            return (FilePath, Arch) in self._CACHE_

        # key = (FilePath, Arch=None, Target=None, Toochain=None)
        def __getitem__(self, Key):
            FilePath = Key[0]
            KeyLength = len(Key)
            if KeyLength > 1:
                Arch = Key[1]
            else:
                Arch = None
            if KeyLength > 2:
                Target = Key[2]
            else:
                Target = None
            if KeyLength > 3:
                Toolchain = Key[3]
            else:
                Toolchain = None

            # if it's generated before, just return the cached one
            Key = (FilePath, Arch, Target, Toolchain)
            if Key in self._CACHE_:
                return self._CACHE_[Key]

            # check file type
            Ext = FilePath.Type
            if Ext not in self._FILE_TYPE_:
                return None
            FileType = self._FILE_TYPE_[Ext]
            if FileType not in self._GENERATOR_:
                return None

            # get the parser ready for this file
            MetaFile = self._FILE_PARSER_[FileType](
                                FilePath,
                                FileType,
                                Arch,
                                MetaFileStorage(self.WorkspaceDb, FilePath, FileType)   # CCEO-0018: RoyalParkOverrideContent
                                )
            # alwasy do post-process, in case of macros change
            MetaFile.DoPostProcess()
            # object the build is based on
            BuildObject = self._GENERATOR_[FileType](
                                    FilePath,
                                    MetaFile,
                                    self,
                                    Arch,
                                    Target,
                                    Toolchain
                                    )
            self._CACHE_[Key] = BuildObject
            return BuildObject

    # placeholder for file format conversion
    class TransformObjectFactory:
        def __init__(self, WorkspaceDb):
            self.WorkspaceDb = WorkspaceDb

        # key = FilePath, Arch
        def __getitem__(self, Key):
            pass

    ## Constructor of WorkspaceDatabase
    #
    # @param DbPath             Path of database file
    # @param GlobalMacros       Global macros used for replacement during file parsing
    # @prarm RenewDb=False      Create new database file if it's already there
    #
#
# CCEO-0018: RoyalParkOverrideBegin
#
    def __init__(self):
        self.DB = dict()
#
# CCEO-0018: RoyalParkOverrideEnd
#
        # create table for internal uses
#
# CCEO-0018: RoyalParkOverrideBegin
#
        self.TblDataModel = DataClass.MODEL_LIST
        self.TblFile = []
#
# CCEO-0018: RoyalParkOverrideEnd
#
        self.Platform = None

        # conversion object for build or file format conversion purpose
        self.BuildObject = WorkspaceDatabase.BuildObjectFactory(self)
        self.TransformObject = WorkspaceDatabase.TransformObjectFactory(self)
#
# CCEO-0018: RoyalParkOverrideBegin
#
#    ## Check whether workspace database need to be renew.
#    #  The renew reason maybe:
#    #  1) If user force to renew;
#    #  2) If user do not force renew, and
#    #     a) If the time of last modified python source is newer than database file;
#    #     b) If the time of last modified frozen executable file is newer than database file;
#    #
#    #  @param force     User force renew database
#    #  @param DbPath    The absolute path of workspace database file
#    #
#    #  @return Bool value for whether need renew workspace databse
#    #
#    def _CheckWhetherDbNeedRenew (self, force, DbPath):
#        # if database does not exist, we need do nothing
#        if not os.path.exists(DbPath): return False
#
#        # if user force to renew database, then not check whether database is out of date
#        if force: return True
#
#        #
#        # Check the time of last modified source file or build.exe
#        # if is newer than time of database, then database need to be re-created.
#        #
#        timeOfToolModified = 0
#        if hasattr(sys, "frozen"):
#            exePath             = os.path.abspath(sys.executable)
#            timeOfToolModified  = os.stat(exePath).st_mtime
#        else:
#            curPath  = os.path.dirname(__file__) # curPath is the path of WorkspaceDatabase.py
#            rootPath = os.path.split(curPath)[0] # rootPath is root path of python source, such as /BaseTools/Source/Python
#            if rootPath == "" or rootPath is None:
#                EdkLogger.verbose("\nFail to find the root path of build.exe or python sources, so can not \
#determine whether database file is out of date!\n")
#
#            # walk the root path of source or build's binary to get the time last modified.
#
#            for root, dirs, files in os.walk (rootPath):
#                for dir in dirs:
#                    # bypass source control folder
#                    if dir.lower() in [".svn", "_svn", "cvs"]:
#                        dirs.remove(dir)
#
#                for file in files:
#                    ext = os.path.splitext(file)[1]
#                    if ext.lower() == ".py":            # only check .py files
#                        fd = os.stat(os.path.join(root, file))
#                        if timeOfToolModified < fd.st_mtime:
#                            timeOfToolModified = fd.st_mtime
#        if timeOfToolModified > os.stat(DbPath).st_mtime:
#            EdkLogger.verbose("\nWorkspace database is out of data!")
#            return True
#
#        return False
#
#    ## Initialize build database
#    def InitDatabase(self):
#        EdkLogger.verbose("\nInitialize build database started ...")
#
#        #
#        # Create new tables
#        #
#        self.TblDataModel.Create(False)
#        self.TblFile.Create(False)
#
#        #
#        # Initialize table DataModel
#        #
#        self.TblDataModel.InitTable()
#        EdkLogger.verbose("Initialize build database ... DONE!")
#
#    ## Query a table
#    #
#    # @param Table:  The instance of the table to be queried
#    #
#    def QueryTable(self, Table):
#        Table.Query()
#
#    def __del__(self):
#        self.Close()
#
#    ## Close entire database
#    #
#    # Commit all first
#    # Close the connection and cursor
#    #
#    def Close(self):
#        if not self._DbClosedFlag:
#            self.Conn.commit()
#            self.Cur.close()
#            self.Conn.close()
#            self._DbClosedFlag = True
#
    def SetFileTimeStamp(self,FileId,TimeStamp):
        self.TblFile[FileId-1][6] = TimeStamp

    def GetFileTimeStamp(self,FileId):
        return self.TblFile[FileId-1][6]
#
# CCEO-0018: RoyalParkOverrideEnd
#

    ## Summarize all packages in the database
    def GetPackageList(self, Platform, Arch, TargetName, ToolChainTag):
        self.Platform = Platform
        PackageList = []
        Pa = self.BuildObject[self.Platform, Arch, TargetName, ToolChainTag]
        #
        # Get Package related to Modules
        #
        for Module in Pa.Modules:
            ModuleObj = self.BuildObject[Module, Arch, TargetName, ToolChainTag]
            for Package in ModuleObj.Packages:
                if Package not in PackageList:
                    PackageList.append(Package)
        #
        # Get Packages related to Libraries
        #
        for Lib in Pa.LibraryInstances:
            LibObj = self.BuildObject[Lib, Arch, TargetName, ToolChainTag]
            for Package in LibObj.Packages:
                if Package not in PackageList:
                    PackageList.append(Package)

        return PackageList

    ## Summarize all platforms in the database
    def PlatformList(self):
        RetVal = []
        for PlatformFile in [item[3] for item in self.TblFile if item[5] == MODEL_FILE_DSC]:  # CCEO-0018: RoyalParkOverrideContent
            try:
                RetVal.append(self.BuildObject[PathClass(PlatformFile), TAB_COMMON])
            except:
                pass
        return RetVal

    def MapPlatform(self, Dscfile):
        Platform = self.BuildObject[PathClass(Dscfile), TAB_COMMON]
        if Platform is None:
            EdkLogger.error('build', PARSER_ERROR, "Failed to parser DSC file: %s" % Dscfile)
        return Platform

##
#
# This acts like the main() function for the script, unless it is 'import'ed into another
# script.
#
if __name__ == '__main__':
    pass

