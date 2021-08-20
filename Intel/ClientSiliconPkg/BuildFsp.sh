## @file
# @copyright
#  Copyright (c) 2008 - 2019 Intel Corporation All rights reserved
#  This software and associated documentation (if any) is furnished
#  under a license and may only be used or copied in accordance
#  with the terms of the license. Except as permitted by such
#  license, no part of this software or documentation may be
#  reproduced, stored in a retrieval system, or transmitted in any
#  form or by any means without the express written consent of
#  Intel Corporation.
#  This file contains an 'Intel Peripheral Driver' and is
#  licensed for Intel CPUs and chipsets under the terms of your
#  license agreement with Intel or your vendor.  This file may
#  be modified by the user, subject to additional terms of the
#  license agreement
##
#!/bin/sh

if [ -z "${WORKSPACE}" ]; then
export WORKSPACE=`pwd`
fi

if [ -z "${WORKSPACE_CORE}" ]; then
export WORKSPACE_CORE=$WORKSPACE/Edk2
fi

if [ -z "${WORKSPACE_COMMON}" ]; then
export WORKSPACE_COMMON=$WORKSPACE/Intel
fi

if [ -z "${WORKSPACE_SILICON}" ]; then
export WORKSPACE_SILICON=$WORKSPACE/Intel
fi

export EdkSetup=$WORKSPACE_CORE/edksetup.sh
export EDK_TOOLS_PATH=$WORKSPACE_CORE/BaseTools

#
# Print usage and exit
#
function USAGE()
{

  echo  "=============================================================================================================================="
  echo  "=    Supported platform list:                                                                                                ="
  echo  "=    All                                                                                                                     ="
  echo  "=============================================================================================================================="
  echo  "=============================================================================================================================="
  echo  "=    Supported Compiler list:                                                                                                ="
  echo  "=    GCC                                                                                                                     ="
  echo  "=    CLANG                                                                                                                   ="
  echo  "=============================================================================================================================="
  echo  "=============================================================================================================================="
  echo  "= Usage: BuildFsp.sh [package name] [platform name ^optional] [Compiler name] [-h \| -? \| -r32 \| -tr32 \| -d32 \| -clean\] ="
  echo  "=============================================================================================================================="
  echo  "=============================================================================================================================="
  echo  "= Example build CoffeeLake form CannonLakeFspPkg:                                                                            ="
  echo  "=    ./Intel/ClientSiliconPkg/BuildFsp.sh CannonLake CoffeeLake GCC -d32                                                     ="
  echo  "= Example build CannonLake form CannonLakeFspPkg:                                                                            ="
  echo  "=    ./Intel/ClientSiliconPkg/BuildFsp.sh CannonLake GCC -d32                                                                ="
  echo  "=============================================================================================================================="
  echo  "= By default BuildFsp assumes below paths when executing:                                                                    ="
  echo  "=   /Edk2/                 : FSP required open source packages                                                               ="
  echo  "=   /Intel/                : Rest of the FSP required packages                                                               ="
  echo  "=   /Python27              : Should be installed for supporting FSP build script                                             ="
  echo  "=   /nasm                  : Should be installed for building FSP                                                            ="
  echo  "=============================================================================================================================="
  echo
  exit 1
}

if [ $1 = "-?" ]; then
  USAGE
fi
if [ $1 = "-h" ]; then
  USAGE
fi

if [ ! -d $WORKSPACE/Conf ]
then
   mkdir $WORKSPACE/Conf
fi
. $EdkSetup BaseTools

FSP_PKG_NAME=$1FspPkg

#
# Is FSP package exist
#
if [ -e $WORKSPACE_SILICON/$FSP_PKG_NAME/BuildFv.sh ]; then
  echo  "The current FSP Package is : $FSP_PKG_NAME"
else
  echo
  echo  "Unsupported FSP Package !!"
  echo
  USAGE
  exit 1
fi

cd $WORKSPACE_SILICON/$FSP_PKG_NAME
bash ./BuildFv.sh $2 $3 $4
if [ $? -ne 0 ]
then
 exit 1
fi

echo
