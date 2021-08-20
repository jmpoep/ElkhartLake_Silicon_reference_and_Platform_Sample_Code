#!/bin/bash

## @file
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
#  This file contains a 'Sample Driver' and is licensed as such under the terms
#  of your license agreement with Intel or your vendor. This file may be modified
#  by the user, subject to the additional terms of the license agreement.
#
# @par Specification
##

#
# Define common and platform specific environment variables.
#
cd ../../
export WORKSPACE=`pwd`
export WORKSPACE_CORE=$WORKSPACE/Edk2
export WORKSPACE_CORE_PLATFORM=$WORKSPACE/Edk2Platforms/Platform/Intel
export WORKSPACE_CORE_SILICON=$WORKSPACE/Edk2Platforms/Silicon/Intel
export EDK_TOOLS_PATH=$WORKSPACE_CORE/BaseTools
export WORKSPACE_COMMON=$WORKSPACE/Intel
export WORKSPACE_SILICON=$WORKSPACE/Intel
export WORKSPACE_PLATFORM=$WORKSPACE/Intel
export EFI_SOURCE=$WORKSPACE_CORE

export PLATFORM_PACKAGE=ElkhartLakePlatSamplePkg
export PLATFORM_BOARD_PACKAGE=ElkhartLakeBoardPkg
export PLATFORM_SI_PACKAGE=ClientOneSiliconPkg
export CLIENT_SI_PACKAGE=ClientSiliconPkg
export CLIENT_COMMON_PACKAGE=ClientCommonPkg
export FSP_PKG_NAME=ElkhartLakeFspPkg

PrepRelease=DEBUG
export SILENT_MODE=FALSE
CapsuleBuild=FALSE
export COMPILER=GCC
export TARGET_PLATFORM=ElkhartLake
#
# If NUMBER_OF_PROCESSORS environment variable is uninitialized
#
if [ ! $NUMBER_OF_PROCESSORS ]; then
  if [ "$(uname)" = "Darwin" ]; then
    export NUMBER_OF_PROCESSORS=$(sysctl -n hw.ncpu)
  else
    export NUMBER_OF_PROCESSORS=$(nproc)
  fi
fi
#
# VAR_BUILD_FLAGS contains user build flags, it is not modified by build scripts
#
export EXT_BUILD_FLAGS=$VAR_BUILD_FLAGS
export BUILD_OPTION_PCD
export FSP_BUILD_OPTION_PCD

function PrintUsage {
  echo "Client BIOS build script"
  echo
  echo "$0 [-f FLAG VALUE] [/f FLAG VALUE] [-r] [/r] [r] [s] [c] [rc] [ehl] [edk] [gcc] [clang] [xcode] [cln] [simics]"
  echo
  echo "  r        Build in release mode. Default is debug"
  echo "  s        Build in silent mode."
  echo "  c        Build with CapsuleBuild=TRUE (Debug build). See note 1"
  echo "  rc       Build with CapsuleBuild=TRUE (Release build). See note 1"
  echo "  ehl      To set gSiPkgTokenSpaceGuid.PcdEhlCpuEnable and PcdEhlPchEnable to TRUE. See note 1"
  echo "  edk      To build EDK build (Default is Debug build). See note 1"
  echo "  gcc      Build whole source with GCC.See note 1"
  echo "  clang    Build whole source with CLANG.See note 1"
  echo "  xcode    Build whole source with XCODE.See note 1"
  echo "  cln      Build clean."
  echo "  -f or /f Sets a build flag to the given value,"
  echo "           can be used as many times as desired.  See note 1"
  echo "  -r or /r Useful for faster rebuilds when no changes have been made to .inf files,"
  echo "           skips the generation of makefiles."
  echo
  echo "1) Re-running $0 without these arguments cannot be used for"
  echo "   incremental build. Hence, these inputs must be supplied every time"
  echo "   $0 is run.  For consistent build flags, set VAR_BUILD_FLAGS"
  echo "   prior to $0"
  echo
}

function BuildClean {
  echo "Build Clean"
  echo
  cd $WORKSPACE_CORE/BaseTools/Source/C
  make clean
  rm -fr $WORKSPACE_CORE/BaseTools/Source/C/BpmGen
  rm -fr $WORKSPACE_CORE/BaseTools/Source/C/GenBiosId
  rm -fr $WORKSPACE_CORE/BaseTools/Source/C/KeyEnroll
  rm -fr $WORKSPACE_CORE/BaseTools/BinWrappers/PosixLike/BpmGen
  rm -fr $WORKSPACE_CORE/BaseTools/BinWrappers/PosixLike/GenBiosId
  rm -fr $WORKSPACE_CORE/BaseTools/BinWrappers/PosixLike/KeyEnroll
  rm -fr $WORKSPACE/Build
  rm -fr $WORKSPACE/Conf
  rm -fr $WORKSPACE/RomImages
}

#
# Parse for "cln" in argument to do a build clean
#
for ((i=1 ; i <= $# ; i++)); do
  if [ "${!i}" = "cln" ]; then
    BuildClean
    exit 0
  fi
done

#
#  Set basic environment, execute edksetup.sh
#
if [ ! -d $WORKSPACE/Conf ]; then
   mkdir $WORKSPACE/Conf
fi
. $WORKSPACE_CORE/edksetup.sh BaseTools

#
# Build BaseTools
#
if [ -d $WORKSPACE_CORE/BaseTools/Source/C/bin ]; then

  echo "$WORKSPACE_CORE/BaseTools/Source/C/bin folder exist then skip build BaseTools"
else
  echo "No $WORKSPACE_CORE/BaseTools/Source/C/bin folder then build BaseTools"
  make -C $WORKSPACE_CORE/BaseTools/Source/C
fi
#
#  Build Platform Tools
#
. $WORKSPACE_PLATFORM/$PLATFORM_BOARD_PACKAGE/BuildPlatTools.sh

#
# Update PATH to include tools path.
#
export PATH=$WORKSPACE_CORE/BaseTools/Source/C/bin:$PATH

#
# Add $WORKSPACE, $WORKSPACE_CORE, $WORKSPACE_COMMON, $WORKSPACE/Silicon and $WORKSPACE/Platform in PACKAGES_PATH
#
export PACKAGES_PATH=$WORKSPACE_CORE_SILICON:$WORKSPACE_CORE:$WORKSPACE_CORE_PLATFORM:$WORKSPACE_COMMON:$WORKSPACE_SILICON:$WORKSPACE_PLATFORM
echo "Current PACKAGES_PATH is : $PACKAGES_PATH"

#
# Generate DEC file from SiPkg.dec.template
#
echo "Gnerating DEC file"
cd $WORKSPACE_SILICON/$PLATFORM_SI_PACKAGE
if [ ! SiPkg.dec.template ]; then
    echo "!!! ERROR !!! SiPkg.dec Template file does not exist."
    exit 1
fi
echo "Switching DEC file for $TARGET_PLATFORM"
python gen_dec.py SiPkg.dec.template $TARGET_PLATFORM
echo "SiPkg.dec file generated successfully"


cd $WORKSPACE_PLATFORM/$PLATFORM_BOARD_PACKAGE
# @todo: Add support for FSP build options (fspb, fspw) and pacm
numargs=$#
for ((i=1 ; i <= numargs ; i++)); do
  if [ "$1" = "r" ]; then
    PrepRelease=RELEASE
  elif [ "$1" = "s" ]; then
    export SILENT_MODE=TRUE
  elif [ "$1" = "c" ]; then
    CapsuleBuild=TRUE
  elif [ "$1" = "rc" ]; then
    PrepRelease=RELEASE
    CapsuleBuild=TRUE
  elif [ "$1" = "gcc" ]; then
    export COMPILER=GCC
  elif [ "$1" = "clang" ]; then
    export COMPILER=CLANG
  elif [ "$1" = "xcode" ]; then
    export COMPILER=XCODE


    #
    # Workaround for boot issue - get assertion at "SystemFirmwareDescriptor.efi".
    #
    export BUILD_OPTION_PCD="$BUILD_OPTION_PCD --pcd gPlatformModuleTokenSpaceGuid.PcdCapsuleEnable=FALSE"
  elif [ "$1" = "edk" ]; then
    export BUILD_OPTION_PCD="$BUILD_OPTION_PCD --pcd gSiPkgTokenSpaceGuid.PcdFspBinaryEnable=FALSE"
    export BUILD_OPTION_PCD="$BUILD_OPTION_PCD --pcd gSiPkgTokenSpaceGuid.PcdFspWrapperEnable=FALSE"
  elif [ "$1" = "ehl" ]; then
    export TARGET_PLATFORM=ElkhartLake
    export BUILD_OPTION_PCD="$BUILD_OPTION_PCD --pcd gSiPkgTokenSpaceGuid.PcdEhlCpuEnable=TRUE"
    export BUILD_OPTION_PCD="$BUILD_OPTION_PCD --pcd gSiPkgTokenSpaceGuid.PcdEhlPchEnable=TRUE"
    #
    # @todo: Not yet support FSP.
    #
    #export FSP_BUILD_OPTION_PCD="$FSP_BUILD_OPTION_PCD --pcd gSiPkgTokenSpaceGuid.PcdEhlCpuEnable=TRUE"
    #export FSP_BUILD_OPTION_PCD="$FSP_BUILD_OPTION_PCD --pcd gSiPkgTokenSpaceGuid.PcdEhlPchEnable=TRUE"
  elif [ "$1" = "perf" ]; then
    export BUILD_OPTION_PCD="$BUILD_OPTION_PCD --pcd gMinPlatformPkgTokenSpaceGuid.PcdPerformanceEnable=TRUE"
    export BUILD=P
  elif [ "$1" = "embedded" ]; then
    export BUILD_OPTION_PCD="$BUILD_OPTION_PCD --pcd gSiPkgTokenSpaceGuid.PcdEmbeddedEnable=0x1"
    export EMBEDDED_BUILD=TRUE
    export BIOS_ID_FILE=$BUILD_DIR/BiosIdEmb.env
  elif [ "$1" = "help" ] ||  [ "$1" = "-h" ] || [ "$1" = "/?" ] || [ "$1" = "--help" ]; then
    PrintUsage
    exit 0
  elif [ "$1" = "/f" ] || [ "$1" = "-f" ]; then
    if [ -z "$2" ] || [ -z "$3" ]; then
      PrintUsage
      exit 1
    fi
  elif [ "$1" = "/r" ] || [ "$1" = "-r" ]; then
    export EXT_BUILD_FLAGS="$EXT_BUILD_FLAGS -u"
  elif [ "$1" = "edk2master" ]; then
    export BUILD_OPTION_PCD="$BUILD_OPTION_PCD --pcd gSiPkgTokenSpaceGuid.PcdEdk2MasterEnable=TRUE"
    export FSP_BUILD_OPTION_PCD="$FSP_BUILD_OPTION_PCD --pcd gSiPkgTokenSpaceGuid.PcdEdk2MasterEnable=TRUE"
  elif [ -n "$1" ]; then
    echo "Invalid input argument: $1"
    echo
    PrintUsage
    exit 1
  fi
  shift
done
echo "EXT_BUILD_FLAGS: $EXT_BUILD_FLAGS"
if [ -f Prep.log ]; then
  rm Prep.log
fi

#
# Setup basic environment
#

cd $WORKSPACE

#
# Check tool chain.
#
if [ "$COMPILER" = "GCC" ]; then
  #
  # Detect GCC Tool Chain Version
  #
  GCC_VERSION=$(gcc --version | grep ^gcc | awk '{print $4}' | sed 's/\.[0-9]*$//g')
  if [ "$GCC_VERSION" = "4.5" ]; then
    export TOOL_CHAIN_TAG=GCC45
  elif [ "$GCC_VERSION" = "4.6" ]; then
    export TOOL_CHAIN_TAG=GCC46
  elif [ "$GCC_VERSION" = "4.7" ]; then
    export TOOL_CHAIN_TAG=GCC47
  elif [ "$GCC_VERSION" = "4.8" ]; then
    export TOOL_CHAIN_TAG=GCC48
  elif [ "$GCC_VERSION" = "4.9" ]; then
    export TOOL_CHAIN_TAG=GCC49
  elif [ "$GCC_VERSION" = "5.3" ]; then
    export TOOL_CHAIN_TAG=GCC5
  elif [ "$GCC_VERSION" = "5.4" ]; then
    export TOOL_CHAIN_TAG=GCC5
  else
    echo "Unsupported GCC version!"
    exit 1
  fi
elif [ "$COMPILER" = "CLANG" ]; then
  #
  # Detect CLANG Tool Chain Version
  #
  CLANG_VERSION=$(clang --version | awk '{print $3}' | head -c 5 | sed 's/\.[0-9]*$//g')
  if [ "$CLANG_VERSION" = "3.8" ]; then
    export TOOL_CHAIN_TAG=CLANG38
  else
    echo "Unsupported CLANG version!"
    exit 1
  fi
elif [ "$COMPILER" = "XCODE" ]; then
  #
  # Always assume the latest XCODE
  #
  export TOOL_CHAIN_TAG=XCODE5
fi

#
# Set build TARGET
#
if [ "$PrepRelease" = "DEBUG" ]; then
  export TARGET=DEBUG
  export TARGET_SHORT=D
elif [ "$PrepRelease" = "RELEASE" ]; then
  export TARGET=RELEASE
  export TARGET_SHORT=R
else
  echo
  echo "!!! ERROR !!! Incorrect TARGET option !!!"
  echo
  exit 1
fi

BUILD_DIR="Build/$PLATFORM_BOARD_PACKAGE/$TARGET"
BUILD_DIR+="_$TOOL_CHAIN_TAG"
export BUILD_DIR
export BUILD_X64=$BUILD_DIR/X64
export BUILD_IA32=$BUILD_DIR/IA32
export BIOS_ID_FILE=$BUILD_DIR/BiosId.env

if [ "$CapsuleBuild" = "FALSE" ]; then
  export INTERNAL_BUILD=0

  #
  # Determine BIOS Build Type
  #
  # C - Code Coverage, R - RVP/Restricted, N - Non-Restricted, I - Internal, P - Performance, S - SV, E - SLE
  #

  export BUILD=X
  echo $EXT_BUILD_FLAGS | grep "PERFORMANCE_ENABLE=TRUE"
  if [ $? -eq 0 ]; then
    export BUILD=P
  fi


  #
  # Setup BIOS_SIZE_OPTION if it isn't predefined
  #
  if [ -z "$BIOS_SIZE_OPTION" ]; then
    export BIOS_SIZE_OPTION=-DSIZE_130
  fi
  export EXT_BUILD_FLAGS="$EXT_BUILD_FLAGS $BIOS_SIZE_OPTION"
  echo
  echo "printing the build type ([U]nified, [N]on-Restricted, [I]nternal, [P]erformance, [S]V, SL[E])"
  echo "Build type ($BUILD)"
  echo

fi

cd $WORKSPACE_PLATFORM/$PLATFORM_BOARD_PACKAGE

if [ "$SILENT_MODE" = "TRUE" ]; then
  echo "************************************************************************" > Prep.log
  echo "***********           PreBuild.sh is launched here          ***********" >> Prep.log
  echo "************************************************************************" >> Prep.log
  . PreBuild.sh $PrepRelease $CapsuleBuild >> Prep.log 2>&1
else
  . PreBuild.sh $PrepRelease $CapsuleBuild
fi

if [ $? -ne 0 ]; then
  echo
  echo "!! The EDKII BIOS build has failed in PreBuild.sh!"
  echo
  exit 1
fi

#
# Run the primary build phase
#
. PriBuild.sh
ret=$?
if [ $ret -ne 0 ]; then
  exit $ret
fi
