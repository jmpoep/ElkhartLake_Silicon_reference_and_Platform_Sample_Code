### @file
# parse the input parameter to know src file path and BUILD_DIR path.
# $(PYTHON) $(CATALOGENCODER) -I ${src} -O ${src}.c -D $(BUILD_DIR)\CatalogDataBase.txt
# "$(CC)" $(CC_FLAGS) -o ${dst} $(INC) ${src}.c
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

"""
ReplaceClTool
"""

import sys
import os
import re
import subprocess

CSuffix = '.c'
ClSuffix = 'cl.exe'
CataLogCmd = '      %s %s -I %s -O %s.c -D %s\CatalogDataBase.txt'
CataLog = Python = WorkSpace = ''
env_dict = os.environ
if env_dict.get('CATALOG_ENCODER'):
    CataLog = env_dict.get('CATALOG_ENCODER')
if env_dict.get('PYTHON_COMMAND'):
    Python = env_dict.get('PYTHON_COMMAND')
if env_dict.get('WORKSPACE'):
    WorkSpace = env_dict.get('WORKSPACE')


class CreateCatalog():

    def __init__(self, CmdInfoList):
        self.ClTool = None
        self.BuildDir = None
        self.OriClToolCmd = None
        self.CFileList = []
        self.CmdInfoList = CmdInfoList

    def CmdCatalog(self):
        def CmdShell(Cmd):
            try:
                p = subprocess.Popen(Cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
            except Exception as X:
                print(X)
            finally:
                out = p.communicate()
                subprocess._cleanup()
                p.stdout.close()
                p.stderr.close()

        if self.BuildDir and self.CFileList and self.ClTool and CataLog and Python and WorkSpace:
            for CFile in self.CFileList:
                Cmd = CataLogCmd % (Python, CataLog, CFile, CFile, self.BuildDir)
                CmdShell(Cmd)
                print(Cmd)
            Cmd = ' '.join(self.CmdInfoList)
            CmdShell(Cmd)
            print(Cmd)
        else:
            CmdShell(self.OriClToolCmd)
            print(self.OriClToolCmd)


    def ParserCmdInfo(self):
        BuildDir = None
        CmdInfoList = self.CmdInfoList
        if not CmdInfoList[0].startswith('"') and CmdInfoList[0].endswith(ClSuffix):
           CmdInfoList[0] = '"' + CmdInfoList[0] + '"'
        elif not CmdInfoList[0].startswith('"'):
            ListNum = len(CmdInfoList)
            ClTool = '"'
            for Item in range(ListNum):
                ItemLine = CmdInfoList[Item]
                if not Item:
                    ClTool = ClTool + ItemLine
                elif not ItemLine.endswith(ClSuffix):
                    ClTool = ClTool + ' ' + ItemLine
                else:
                    ClTool = ClTool + ' ' + ItemLine + '"'
                    CmdInfoList = CmdInfoList[Item+1:]
                    CmdInfoList.insert(0,ClTool)
                    break
        self.OriClToolCmd = ' '.join(CmdInfoList)
        ListNum = len(CmdInfoList)
        for Item in range(ListNum):
            ItemLine = CmdInfoList[Item]
            if ItemLine.endswith(ClSuffix+'"'):
                BuildDirOri = CmdInfoList[Item + 1]
                if BuildDirOri.startswith('/Fo'):
                    BuildDir = BuildDirOri[3:]
                elif BuildDirOri == '-O':
                    BuildDir = CmdInfoList[Item + 2]
                if WorkSpace and BuildDir:
                    DirList = [WorkSpace]
                    reg = re.compile(re.escape(WorkSpace), re.IGNORECASE)
                    BuildDir = reg.sub('', BuildDir)
                    BuildList = BuildDir.split(os.sep)
                    if not BuildList[0]:
                        BuildList.pop(0)
                    if len(BuildList) > 3:
                        DirList.extend(BuildList[:3])
                        self.BuildDir = os.sep.join(DirList)
                self.ClTool = ItemLine
            elif ItemLine.lower().endswith(CSuffix):
                self.CFileList.append(ItemLine)
                CmdInfoList[Item] = ''.join([ItemLine, CSuffix])
        self.CmdInfoList = CmdInfoList


def Main():
    CmdInfoList = sys.argv
    if len(CmdInfoList) > 1 and CmdInfoList[1] != '-h':
        CmdInfoList.pop(0)
    else:
        print('ReplaceClTool.py is not implemented')
        exit(0)
    Catalog = CreateCatalog(CmdInfoList)
    Catalog.ParserCmdInfo()
    Catalog.CmdCatalog()


if __name__ == "__main__":
    Main()
