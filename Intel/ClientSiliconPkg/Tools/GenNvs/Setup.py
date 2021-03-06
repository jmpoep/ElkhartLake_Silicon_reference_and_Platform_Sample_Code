### @file
# Script to generate .exe executable file.
#
# Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
#
# This program and the accompanying materials are licensed and made available under
# the terms and conditions of the BSD License which accompanies this distribution.
# The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
##


from distutils.core import setup
import py2exe


setup (
    console = ['GenNvs.py'],
    zipfile = None,
    optimize = 2,
    options = {
              'py2exe':{
                      'excludes': ['email',
                                   'ssl',
                                   'pyreadline',
                                   'random',
                                   'socket',
                                   'unittest',
                                   'urllib',
                                   'urlparse',
                                   'ftplib',
                                   'httplib',
                                   'logging',
                                   'md5'
                      ]
              }
    }
)
