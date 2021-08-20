## @file
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2008 - 2019 Intel Corporation.
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
#  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
#  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
#  the terms of your license agreement with Intel or your vendor. This file may
#  be modified by the user, subject to additional terms of the license agreement.
#
# @par Specification
##
#!/bin/sh



FSP_PKG_NAME=ElkhartLakeFspPkg
FSP_PKG_CONF_NAME=ElkhartLakeFspPkgConfig
FSP_BIN_PKG_NAME=ElkhartLakeFspBinPkg
PLATFORM_SI_PACKAGE=ClientOneSiliconPkg
FSP_T_UPD_GUID=34686CA3-34F9-4901-B82A-BA630F0714C6
FSP_M_UPD_GUID=39A250DB-E465-4DD1-A2AC-E2BD3C0E2385
FSP_S_UPD_GUID=CAE3605B-5B34-4C85-B3D7-27D54273C40F
ErrorCode=0

function USAGE()
{
  echo
  echo  "$0 \[GCC \| CLANG\]\[-h \| -? \| -r32 \| -tr32 \| -d32 \| -clean\] \[ElkhartLake\(Optional\)\]"
  echo
  return 1
}

function Clean(){
  echo Removing Build and Conf directories ...
  if [ -d $WORKSPACE/Build ]
   then
    rm -r $WORKSPACE/Build
  fi
  if [ -d $WORKSPACE/Conf ]
    then
     rm  -r $WORKSPACE/Conf
  fi
  if [ -f *.log ]
   then
    rm *.log
  fi
  WORKSPACE=
  EDK_TOOLS_PATH=
  return 0
}


function  PreBuildFail(){
  if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspUpd.h ]
   then
    rm  $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspUpd.h
  fi
  if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FsptUpd.h ]
   then
    rm  $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FsptUpd.h
  fi
  if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspmUpd.h ]
   then
    rm  $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspmUpd.h
  fi
  if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspsUpd.h ]
   then
    rm  $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspsUpd.h
  fi
  #/q /f
  return 0
}

function PreBuildRet(){
  set $1=0
  echo End of PreBuild ...
  echo
  return 0
}


function CopyBin(){
 if [ -f $1/*.efi ]
  then
   cp $1/*.efi   $2
   #/D /U /Y > NUL
 fi
 if [ -f $1/*.inf ]
   then
     cp $1/*.inf   $2
   #/D /U /Y > NUL
 fi
 if [ -f $1/*.depex ]
   then
    cp $1/*.depex $2
   #/D /U /Y > NUL
 fi
}

function PreBuild(){

  cp $WORKSPACE_SILICON/$PLATFORM_SI_PACKAGE/Pch/Include/GpioConfig.h $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include/GpioConfig.h

  cp $WORKSPACE_SILICON/$PLATFORM_SI_PACKAGE/SystemAgent/Include/MemInfoHob.h $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include/MemInfoHob.h

  cp $WORKSPACE_COMMON/ClientSiliconPkg/Include/SmbiosCacheInfoHob.h $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include/SmbiosCacheInfoHob.h

  cp $WORKSPACE_COMMON/ClientSiliconPkg/Include/SmbiosProcessorInfoHob.h $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include/SmbiosProcessorInfoHob.h

  cp $WORKSPACE_COMMON/ClientSiliconPkg/Include/FirmwareVersionInfoHob.h $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include/FirmwareVersionInfoHob.h

  python Edk2/IntelFsp2Pkg/Tools/GenCfgOpt.py UPDTXT \
     $WORKSPACE_SILICON/$FSP_PKG_NAME/$FSP_PKG_NAME.dsc \
     $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV \
     $BD_MACRO $FSP_BUILD_OPTION_PCD

  error=$?
  if [ $error -eq "256" ]
   then
    echo  DSC is not changed, no need to recreate MAP and BIN file
  else
   if [ $error -eq "1" ]
    then
     echo Error in generating UPD TXT file
     return 1
   fi

  echo UPD TXT file was generated successfully !

  echo Generate VPD Header File ...
  rm  $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_T_UPD_GUID.bin \
            $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_T_UPD_GUID.map
 #2>nul

  rm  $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_M_UPD_GUID.bin \
            $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_M_UPD_GUID.map
 #2>nul

  rm  $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_S_UPD_GUID.bin \
            $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_S_UPD_GUID.map
 #2>nul

  BPDG -o $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_T_UPD_GUID.bin \
       -m $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_T_UPD_GUID.map \
        $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_T_UPD_GUID.txt

      if [ $? -eq "1" ]
       then
       return 1
      fi

  BPDG -o $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_M_UPD_GUID.bin \
       -m $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_M_UPD_GUID.map \
        $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_M_UPD_GUID.txt

      if [ $? -eq "1" ]
       then
       return 1
      fi

  BPDG -o $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_S_UPD_GUID.bin \
       -m $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_S_UPD_GUID.map \
        $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_S_UPD_GUID.txt

      if [ $? -eq "1" ]
       then
       return 1
      fi
  fi

  python Edk2/IntelFsp2Pkg/Tools/GenCfgOpt.py HEADER \
         $WORKSPACE_SILICON/$FSP_PKG_NAME/$FSP_PKG_NAME.dsc \
         $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV \
         $WORKSPACE_SILICON/$FSP_PKG_NAME/Include/BootLoaderPlatformData.h \
         $BD_MACRO $FSP_BUILD_OPTION_PCD

  error=$?
  if [ $error -eq "256" ]
   then
    echo
    # No need to recreate header file
   else
      if [ $error -eq "1" ]
       then
        echo Error in generating Header file
        return 1
      fi

    echo Vpd header file was generated successfully !

    echo Generate BSF File ...
    python Edk2/IntelFsp2Pkg/Tools/GenCfgOpt.py GENBSF \
         $WORKSPACE_SILICON/$FSP_PKG_NAME/$FSP_PKG_NAME.dsc \
         $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV \
         $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Fsp.bsf \
         $BD_MACRO $FSP_BUILD_OPTION_PCD

    if [ $? -eq "1" ]
       then
        echo Error in generating BSF file
        return 1
    fi

    echo BSF file was generated successfully !
    if [ -f $WORKSPACE_SILICON/$FSP_PKG_NAME/Include/FspUpd.h ]
      then chmod +w $WORKSPACE_SILICON/$FSP_PKG_NAME/Include/FspUpd.h
    fi
    if [ -f $WORKSPACE_SILICON/$FSP_PKG_NAME/Include/FsptUpd.h ]
      then chmod +w $WORKSPACE_SILICON/$FSP_PKG_NAME/Include/FsptUpd.h
    fi
    if [ -f $WORKSPACE_SILICON/$FSP_PKG_NAME/Include/FspmUpd.h ]
      then chmod +w $WORKSPACE_SILICON/$FSP_PKG_NAME/Include/FspmUpd.h
    fi
    if [ -f $WORKSPACE_SILICON/$FSP_PKG_NAME/Include/FspsUpd.h ]
      then chmod +w $WORKSPACE_SILICON/$FSP_PKG_NAME/Include/FspsUpd.h
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspUpd.h ]
     then
      cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspUpd.h  $WORKSPACE_SILICON/$FSP_PKG_NAME/Include/FspUpd.h
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FsptUpd.h ]
     then
      cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FsptUpd.h  $WORKSPACE_SILICON/$FSP_PKG_NAME/Include/FsptUpd.h
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspmUpd.h ]
     then
      cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspmUpd.h  $WORKSPACE_SILICON/$FSP_PKG_NAME/Include/FspmUpd.h
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspsUpd.h ]
     then
      cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspsUpd.h  $WORKSPACE_SILICON/$FSP_PKG_NAME/Include/FspsUpd.h
    fi
  fi
}


function PostBuild(){
  echo Start of PostBuild ...
  echo Get UTC time as build time.
  ORIGINAL_PATH=$PWD
  cd $WORKSPACE_SILICON/$FSP_PKG_NAME/Tools/GetUtcDateTime
  YYYY=$(python GetUtcDateTime.py --year)
  MMDD=$(python GetUtcDateTime.py --date)
  HHMM=$(python GetUtcDateTime.py --time)

  echo $YYYY
  echo $MMDD
  echo $HHMM
  cd $ORIGINAL_PATH

  echo Patch FSP-T Image ...
   #
   # @todo Change FSP.fd to Fsp.fd
   #
   python $WORKSPACE_CORE/IntelFsp2Pkg/Tools/PatchFv.py \
     $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV \
     FSP-T:FSP \
     "0x0000,            _BASE_FSP-T_,                                                                                       @Temporary Base" \
     "<[0x0000]>+0x00AC, [<[0x0000]>+0x0020],                                                                                @FSP-T Size" \
     "<[0x0000]>+0x00B0, [0x0000],                                                                                           @FSP-T Base" \
     "<[0x0000]>+0x00B4, ([<[0x0000]>+0x00B4] & 0xFFFFFFFF) | 0x0001,                                                        @FSP-T Image Attribute" \
     "<[0x0000]>+0x00B6, ([<[0x0000]>+0x00B6] & 0xFFFF0FFC) | 0x1000 | $FSP_BUILD_TYPE | $FSP_RELEASE_TYPE,                  @FSP-T Component Attribute" \
     "<[0x0000]>+0x00B8, 70BCF6A5-FFB1-47D8-B1AE-EFE5508E23EA:0x1C - <[0x0000]>,                                             @FSP-T CFG Offset" \
     "<[0x0000]>+0x00BC, [70BCF6A5-FFB1-47D8-B1AE-EFE5508E23EA:0x14] & 0xFFFFFF - 0x001C,                                    @FSP-T CFG Size" \
     "<[0x0000]>+0x00C4, FspSecCoreT:_TempRamInitApi - [0x0000],                                                             @TempRamInit API" \
     "<[0x0000]>+0x00FC, 0x$YYYY,                                                                                            @BuildTimeStamp" \
     "<[0x0000]>+0x0100, 0x$MMDD,                                                                                            @BuildTimeStamp" \
     "<[0x0000]>+0x0104, 0x$HHMM,                                                                                            @BuildTimeStamp" \
     "0x0000,            0x00000000,                                                                                         @Restore the value" \
     "FspSecCoreT:_FspInfoHeaderRelativeOff, FspSecCoreT:_AsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-T Header Offset" \
     "FspSecCoreT:_SiFspInfoHeaderRelativeOff, FspSecCoreT:_SiAsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-T Header Offset"

  echo Patch FSP-M Image ...
   #
   # @todo Change FSP.fd to Fsp.fd
   #
   python $WORKSPACE_CORE/IntelFsp2Pkg/Tools/PatchFv.py \
     $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV \
     FSP-M:FSP \
     "0x0000,            _BASE_FSP-M_,                                                                                       @Temporary Base" \
     "<[0x0000]>+0x00AC, [<[0x0000]>+0x0020],                                                                                @FSP-M Size" \
     "<[0x0000]>+0x00B0, [0x0000],                                                                                           @FSP-M Base" \
     "<[0x0000]>+0x00B4, ([<[0x0000]>+0x00B4] & 0xFFFFFFFF) | 0x0001,                                                        @FSP-M Image Attribute" \
     "<[0x0000]>+0x00B6, ([<[0x0000]>+0x00B6] & 0xFFFF0FFC) | 0x2000 | $FSP_BUILD_TYPE | $FSP_RELEASE_TYPE,                  @FSP-M Component Attribute" \
     "<[0x0000]>+0x00B8, D5B86AEA-6AF7-40D4-8014-982301BC3D89:0x1C - <[0x0000]>,                                             @FSP-M CFG Offset" \
     "<[0x0000]>+0x00BC, [D5B86AEA-6AF7-40D4-8014-982301BC3D89:0x14] & 0xFFFFFF - 0x001C,                                    @FSP-M CFG Size" \
     "<[0x0000]>+0x00D0, FspSecCoreM:_FspMemoryInitApi - [0x0000],                                                           @MemoryInitApi API" \
     "<[0x0000]>+0x00D4, FspSecCoreM:_TempRamExitApi - [0x0000],                                                             @TempRamExit API" \
     "<[0x0000]>+0x00FC, 0x$YYYY,                                                                                            @BuildTimeStamp" \
     "<[0x0000]>+0x0100, 0x$MMDD,                                                                                            @BuildTimeStamp" \
     "<[0x0000]>+0x0104, 0x$HHMM,                                                                                            @BuildTimeStamp" \
     "FspSecCoreM:_FspPeiCoreEntryOff, PeiCore:__ModuleEntryPoint - [0x0000],                                                @PeiCore Entry" \
     "0x0000,            0x00000000,                                                                                         @Restore the value" \
     "FspSecCoreM:_FspInfoHeaderRelativeOff, FspSecCoreM:_AsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-M Header Offset" \
     "FspGlobalDataInitPei:_FspInfoHeaderRelativeOff, FspGlobalDataInitPei:_AsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-M Header Offset"


  echo Patch FSP-S Image ...
   #
   # @todo Change FSP.fd to Fsp.fd
   #
   python $WORKSPACE_CORE/IntelFsp2Pkg/Tools/PatchFv.py \
     $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV \
     FSP-S:FSP \
     "0x0000,            _BASE_FSP-S_,                                                                                       @Temporary Base" \
     "<[0x0000]>+0x00AC, [<[0x0000]>+0x0020],                                                                                @FSP-S Size" \
     "<[0x0000]>+0x00B0, [0x0000],                                                                                           @FSP-S Base" \
     "<[0x0000]>+0x00B4, ([<[0x0000]>+0x00B4] & 0xFFFFFFFF) | 0x0001,                                                        @FSP-S Image Attribute" \
     "<[0x0000]>+0x00B6, ([<[0x0000]>+0x00B6] & 0xFFFF0FFC) | 0x3000 | $FSP_BUILD_TYPE | $FSP_RELEASE_TYPE,                  @FSP-S Component Attribute" \
     "<[0x0000]>+0x00B8, E3CD9B18-998C-4F76-B65E-98B154E5446F:0x1C - <[0x0000]>,                                             @FSP-S CFG Offset" \
     "<[0x0000]>+0x00BC, [E3CD9B18-998C-4F76-B65E-98B154E5446F:0x14] & 0xFFFFFF - 0x001C,                                    @FSP-S CFG Size" \
     "<[0x0000]>+0x00D8, FspSecCoreS:_FspSiliconInitApi - [0x0000],                                                          @SiliconInit API" \
     "<[0x0000]>+0x00CC, FspSecCoreS:_NotifyPhaseApi - [0x0000],                                                             @NotifyPhase API" \
     "<[0x0000]>+0x00FC, 0x$YYYY,                                                                                            @BuildTimeStamp" \
     "<[0x0000]>+0x0100, 0x$MMDD,                                                                                            @BuildTimeStamp" \
     "<[0x0000]>+0x0104, 0x$HHMM,                                                                                            @BuildTimeStamp" \
     "0x0000,            0x00000000,                                                                                         @Restore the value" \
     "FspSecCoreS:_FspInfoHeaderRelativeOff, FspSecCoreS:_AsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-S Header Offset"

}

function  Build32(){


   make -C $WORKSPACE_CORE/BaseTools/Source/C
   chmod +w $WORKSPACE_SILICON/$FSP_PKG_NAME/$FSP_PKG_NAME.dsc

   build -m $FSP_PKG_NAME/FspHeader/FspHeader.inf $BD_ARGS $FSP_BUILD_OPTION_PCD
   if [ $? -ne 0 ]
   then
     exit 1
   fi

   PreBuild $*

   if [ $? -eq 1 ]
   then
     exit 1
   fi

   build $BD_ARGS $FSP_BUILD_OPTION_PCD
   if [ $? -ne 0 ]
   then
     exit 1
   fi
   PostBuild
   if [ $? -ne 0 ]
   then
     exit 1
   fi
}

function ReleaseTypeTest32(){
  BD_TARGET=RELEASE
  BD_MACRO="-D TARGET="$BD_TARGET" -D CFG_OUTDIR="$OUT_DIR
  DSCFILE="-p "$FSP_PKG_NAME/$FSP_PKG_NAME.dsc #" -y ReleaseBuild32Log.log"
  BD_ARGS=$DSCFILE" -b RELEASE "$BD_MACRO" -a IA32 -a X64 -n 1 -t "$TOOL_CHAIN
  FSP_BUILD_TYPE=0x0001
  FSP_RELEASE_TYPE=0x0000
  Build32 $*
}

function ReleaseBuild32(){
  BD_TARGET=RELEASE
  BD_MACRO="-D TARGET="$BD_TARGET" -D CFG_OUTDIR="$OUT_DIR
  DSCFILE="-p "$FSP_PKG_NAME/$FSP_PKG_NAME.dsc #" -y ReleaseBuild32Log.log"
  BD_ARGS=$DSCFILE" -b RELEASE "$BD_MACRO" -a IA32 -a X64 -n 1 -t "$TOOL_CHAIN
  FSP_BUILD_TYPE=0x0001
  FSP_RELEASE_TYPE=0x0002
  Build32 $*
}

function DebugBuild32(){
  BD_TARGET=DEBUG
  BD_MACRO="-D TARGET="$BD_TARGET" -D CFG_DEBUG=1 -D DEBUG_BIOS_ENABLE=TRUE -D CFG_OUTDIR="$OUT_DIR
  DSCFILE="-p "$FSP_PKG_NAME/$FSP_PKG_NAME.dsc   #" -y DebugBuild32Log.log"
  #echo $DSCFILE
  BD_ARGS=$DSCFILE" -b DEBUG "$BD_MACRO" -a IA32 -a X64 -n 1 -t "$TOOL_CHAIN
  FSP_BUILD_TYPE=0x0000
  FSP_RELEASE_TYPE=0x0000
  Build32 $*
}

function CopyFspBinaryToBinPkg(){
    echo Copy FSP binary to $FSP_BIN_PKG_NAME

    if [ -f $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Fsp.bsf ]
      then chmod +w $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Fsp.bsf
    fi
    if [ -f $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Fsp.fd ]
      then chmod +w $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Fsp.fd
    fi

    cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FSP.fd $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Fsp.fd

    if [ -f $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include/FspUpd.h ]
      then chmod +w $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include/FspUpd.h
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspUpd.h ]
      then cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspUpd.h $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include
    fi
    if [ -f $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include/FsptUpd.h ]
      then chmod +w $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include/FsptUpd.h
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FsptUpd.h ]
      then cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FsptUpd.h $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include
    fi
    if [ -f $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include/FspmUpd.h ]
      then chmod +w $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include/FspmUpd.h
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspmUpd.h ]
      then cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspmUpd.h $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include
    fi
    if [ -f $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include/FspsUpd.h ]
      then chmod +w $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include/FspsUpd.h
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspsUpd.h ]
      then cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspsUpd.h $WORKSPACE_SILICON/$FSP_BIN_PKG_NAME/Include
    fi
}

cd $WORKSPACE

OUT_DIR=$WORKSPACE/Build

#
# Add $WORKSPACE/Silicon and $WORKSPACE_CORE in PACKAGES_PATH
#
export WORKSPACE_CORE_SILICON=$WORKSPACE/Edk2Platforms/Silicon/Intel
export PACKAGES_PATH=$WORKSPACE_SILICON:$WORKSPACE_CORE_SILICON:$WORKSPACE_CORE:$WORKSPACE_COMMON
echo "Current PACKAGES_PATH is : $PACKAGES_PATH"

if [ "$3" = "ElkhartLake" ]; then
  echo Default ElkhartLake build
  export FSP_BUILD_OPTION_PCD="$FSP_BUILD_OPTION_PCD --pcd gSiPkgTokenSpaceGuid.PcdIclCpuEnable=TRUE"
  export FSP_BUILD_OPTION_PCD="$FSP_BUILD_OPTION_PCD --pcd gSiPkgTokenSpaceGuid.PcdEhlCpuEnable=TRUE"
  export FSP_BUILD_OPTION_PCD="$FSP_BUILD_OPTION_PCD --pcd gSiPkgTokenSpaceGuid.PcdIclPchEnable=FALSE"
  export FSP_BUILD_OPTION_PCD="$FSP_BUILD_OPTION_PCD --pcd gSiPkgTokenSpaceGuid.PcdEhlPchEnable=TRUE"
  echo Target cpu is ElkhartLake. Build on $FSP_PKG_NAME
  echo Target cpu is ElkhartLake. Build on $FSP_PKG_NAME
fi

#
# Generating SiPkg DEC
#
echo Generating SiPkg DEC ....
SIPKG_DEC=$WORKSPACE_SILICON/ClientOneSiliconPkg/SiPkg.dec
if [ ! -e "$SIPKG_DEC".template ]; then
  echo Error: SiPkg.dec Template not found. Halting build...
  exit 1
fi
if [ -e $SIPKG_DEC ]; then
  chmod +w $SIPKG_DEC
fi
if [ "$3" = "IceLake" ]; then
  echo You chose IceLake build option
  python $WORKSPACE_SILICON/ClientOneSiliconPkg/gen_dec.py "$SIPKG_DEC".template IceLake
  echo Switching SiPkg DEC file to IceLake
else
  echo Default ElkhartLake build
  python $WORKSPACE_SILICON/ClientOneSiliconPkg/gen_dec.py "$SIPKG_DEC".template ElkhartLake
  echo Switching SiPkg DEC file to ElkhartLake
fi
echo $SIPKG_DEC generation completed.
echo .

if [ "$1" = "GCC" ]; then
#
# Detect GCC Tool Chain Version
#
GCC_VERSION=$(gcc -dumpversion|sed 's/^\([0-9]\.[0-9]\).*/\1/')
if [ "$GCC_VERSION" = "4.5" ]; then
  export TOOL_CHAIN=GCC45
elif [ "$GCC_VERSION" = "4.6" ]; then
  export TOOL_CHAIN=GCC46
elif [ "$GCC_VERSION" = "4.7" ]; then
  export TOOL_CHAIN=GCC47
elif [ "$GCC_VERSION" = "4.8" ]; then
  export TOOL_CHAIN=GCC48
elif [ "$GCC_VERSION" = "4.9" ]; then
  export TOOL_CHAIN=GCC49
elif [ "$GCC_VERSION" = "5.3" ]; then
  export TOOL_CHAIN=GCC5
elif [ "$GCC_VERSION" = "5.4" ]; then
  export TOOL_CHAIN=GCC5
else
  echo "Unsupported GCC version!"
  exit 1
fi
#
# Toolchain information
#
gcc -v
fi

if [ "$1" = "CLANG" ]; then
#
# Detect CLANG Tool Chain Version
#
CLANG_VERSION=$(clang --version | awk '{print $4}' | head -c 5 | sed 's/\.[0-9]*$//g')
#
# @todo these define for current teamcity Clang, will remove below define only keep clang3.8
#
if [ "$CLANG_VERSION" = "3.4" ]; then
  export TOOL_CHAIN=CLANG
elif [ "$CLANG_VERSION" = "3.5" ]; then
  export TOOL_CHAIN=CLANG
elif [ "$CLANG_VERSION" = "3.6" ]; then
  export TOOL_CHAIN=CLANG
elif [ "$CLANG_VERSION" = "3.7" ]; then
  export TOOL_CHAIN=CLANG
elif [ "$CLANG_VERSION" = "3.8" ]; then
  export TOOL_CHAIN=CLANG38
else
  echo "Unsupported CLANG version!"
  exit 1
fi
#
# Toolchain information
#
clang --version
fi

if [ -z "${TOOL_CHAIN}" ]; then
  export TOOL_CHAIN=$1
fi

if [ "$2" = "-clean" ]
 then
  Clean
elif [ "$2" = "-r32" ]
then
  ReleaseBuild32
  CopyFspBinaryToBinPkg
elif [ "$2" = "-tr32" ]
 then
  ReleaseTypeTest32
  CopyFspBinaryToBinPkg
elif [ "$2" = "-d32" ]
 then
   DebugBuild32
   CopyFspBinaryToBinPkg
elif [ -z "$2" ]
 then
   DebugBuild32
else
  echo
  echo  ERROR: $2 is not valid parameter.
  USAGE
fi
