/** @file
  Public include file for CPU definitions and CPU library functions that
  apply to CPUs that fit into an LGA1156 spocket.

  Module Name:  SocketLga1156.h

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification
**/

#ifndef _SOCKET_LGA_1156_H_
#define _SOCKET_LGA_1156_H_

#include <Register/VirtualMsrcommon.h>
#include <Register/Pcucommon.h>
#include <Register/FscpMsrcommon.h>
#include <Register/CoreMsrcommon.h>

#define EFI_CPUID_MONITOR_MWAIT_PARAMS               0x5

//
// Processor Family and Model information.
//
#define NEHALEM_FAMILY_ID             0x06
#define BLOOMFIELD_MODEL_ID           0x1A
#define LYNNFIELD_MODEL_ID            0x1E
#define CLARKDALE_MODEL_ID            0x25
#define TUNNELCREEK_MODEL_ID          0x26
#define NEHALEM_EX_MODEL_ID           0x2E
#define WESTMERE_EX_MODEL_ID          0x2F

#define SANDYBRIDGE_CLIENT_MODEL_ID   0x2A
#define SANDYBRIDGE_SERVER_MODEL_ID   0x2D

#define VALLEYVIEW_MODEL_ID           0x37
#define AVOTON_MODEL_ID               0x4D

#define BROXTON_MODEL_ID              0x5C
#define DENVERTON_MODEL_ID            0x5F

#define IVYBRIDGE_CLIENT_MODEL_ID     0x3A
#define IVYBRIDGE_SERVER_MODEL_ID     0x3E

#define HASWELL_CLIENT_MODEL_ID       0x3C
#define HASWELL_SERVER_MODEL_ID       0x3F

#define SKYLAKE_CLIENT_MODEL_ID       0x4E
#define SKYLAKE_SERVER_MODEL_ID       0x55

#define BROADWELL_ULT_CLIENT_MODEL_ID 0x3D
#define CRYSTALWELL_CLIENT_MODEL_ID   0x46
#define BRYSTALWELL_CLIENT_MODEL_ID   0x47
#define BROADWELL_SERVER_MODEL_ID     0x4F
#define BROADWELL_SERVER_DE_MODEL_ID  0x56

#define IS_NEHALEM_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == BLOOMFIELD_MODEL_ID || \
    ModelId == LYNNFIELD_MODEL_ID || \
    ModelId == CLARKDALE_MODEL_ID \
    ) \
   )

#define IS_NEHALEM_SERVER_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == NEHALEM_EX_MODEL_ID || \
    ModelId == WESTMERE_EX_MODEL_ID \
    ) \
   )

#define IS_TUNNELCREEK_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == TUNNELCREEK_MODEL_ID \
    ) \
   )

#define IS_SANDYBRIDGE_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == SANDYBRIDGE_CLIENT_MODEL_ID || \
    ModelId == SANDYBRIDGE_SERVER_MODEL_ID \
    ) \
   )

#define IS_SANDYBRIDGE_SERVER_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == SANDYBRIDGE_SERVER_MODEL_ID \
    ) \
   )

 #define IS_SILVERMONT_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == VALLEYVIEW_MODEL_ID || \
    ModelId == AVOTON_MODEL_ID \
    ) \
   )

 #define IS_VALLEYVIEW_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == VALLEYVIEW_MODEL_ID \
    ) \
   )

 #define IS_AVOTON_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == AVOTON_MODEL_ID \
    ) \
   )

#define IS_IVYBRIDGE_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == IVYBRIDGE_CLIENT_MODEL_ID || \
    ModelId == IVYBRIDGE_SERVER_MODEL_ID \
    ) \
   )

#define IS_IVYBRIDGE_SERVER_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == IVYBRIDGE_SERVER_MODEL_ID \
    ) \
   )

#define IS_HASWELL_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == HASWELL_CLIENT_MODEL_ID || \
    ModelId == HASWELL_SERVER_MODEL_ID \
    ) \
   )

#define IS_HASWELL_SERVER_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == HASWELL_SERVER_MODEL_ID \
    ) \
   )

#define IS_BROADWELL_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == BROADWELL_ULT_CLIENT_MODEL_ID || \
    ModelId == CRYSTALWELL_CLIENT_MODEL_ID || \
    ModelId == BRYSTALWELL_CLIENT_MODEL_ID || \
    ModelId == BROADWELL_SERVER_MODEL_ID || \
    ModelId == BROADWELL_SERVER_DE_MODEL_ID \
    ) \
   )

#define IS_BROADWELL_SERVER_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
     ModelId == BROADWELL_SERVER_MODEL_ID || \
     ModelId == BROADWELL_SERVER_DE_MODEL_ID \
     ) \
   )

#define IS_SKYLAKE_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == SKYLAKE_CLIENT_MODEL_ID || \
    ModelId == SKYLAKE_SERVER_MODEL_ID \
    ) \
   )

#define IS_SKYLAKE_SERVER_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == SKYLAKE_SERVER_MODEL_ID \
    ) \
   )

#define IS_GOLDMONT_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == BROXTON_MODEL_ID || \
    ModelId == DENVERTON_MODEL_ID \
    ) \
   )

#define IS_DENVERTON_PROC(FamilyId, ModelId) \
  (FamilyId == NEHALEM_FAMILY_ID && \
   ( \
    ModelId == DENVERTON_MODEL_ID \
    ) \
   )

//
// Socket LGA1156 and LGA1366 based MSR definitions.
//
#define MSR_MONITOR_FILTER_SIZE             0x06
#define MSR_CHL_CONTROLS                    0x2D
#define MSR_DCU_MODE                        0x31
#define MSR_SOCKET_ID                       0x39
#define MSR_VLW_CONTROL                     0x4B
#define MSR_QUIESCE_CONTROL                 0x50
#define MSR_PECI_DNSTRM_WRITE_EN            0x54
#define MSR_PMG_CST_CONFIG_CONTROL          0xE2
#define MSR_POWER_MISC                      0x120
#define MSR_CPUID1_FEATURE_MASK             0x130
#define MSR_CPUID80000001_FEATURE_MASK      0x131
#define MSR_PCID_ENABLE_FEATURE             0x13D
#define MSR_MCG_CONTAIN                     0x178
#define MSR_TURBO_POWER_CURRENT_LIMIT       0x1AC
#define MSR_VLW_CAPABILITY                  0x1F0
#define MSR_FERR_CAPABILITY                 0x1F1
#define MSR_SMRR_PHYSBASE                   0x1F2
#define MSR_SMRR_PHYSMASK                   0x1F3
#define MSR_EMRR_PHYSBASE                   0x1F4
#define MSR_EMRR_PHYSMASK                   0x1F5
#define MSR_NO_EVICT_MODE                   0x2E0
#define MSR_UNCORE_CR_MEMLOCK_COMMANDS      0x2E2
#define MSR_UNCORE_CR_UNCORE_MC_CFG_CONTROL 0x2E3
#define MSR_PCIEXBAR_MSR                    0x300
#define MSR_PKG_C3_RESIDENCY                0x3F8
#define MSR_PKG_C6_RESIDENCY                0x3F9
#define MSR_PKG_C7_RESIDENCY                0x3FA
#define MSR_CORE_C3_RESIDENCY               0x3FC
#define MSR_CORE_C6_RESIDENCY               0x3FD
#define MSR_CORE_C7_RESIDENCY               0x3FE

#define MSR_IACORE_RATIOS                   0x66A
#define MSR_IACORE_VIDS                     0x66B
#define MSR_IACORE_TURBO_RATIOS             0x66C
#define MSR_IACORE_TURBO_VIDS               0x66D

#endif
