/** @file
  CPU TXT PreMemory Config Block.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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

@par Specification Reference:
**/
#ifndef _CPU_TXT_CONFIG_H_
#define _CPU_TXT_CONFIG_H_

#define CPU_TXT_PREMEM_CONFIG_REVISION 1

extern EFI_GUID gCpuTxtPreMemConfigGuid;

#pragma pack (push,1)

/**
  CPU TXT PreMemory Configuration Structure.
  @note <b>Optional.</b> These policies will be ignored if CPU_SECURITY_PREMEM_CONFIG -> Txt is disabled, or PeiTxtLibNull is used.

  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  UINT32                SinitMemorySize;          ///< Size of SINIT module if installed in flash part. Zero otherwise.
  UINT32                TxtHeapMemorySize;        ///< Size of memory reserved for TXT Heap. This memory is used by MLE.
  UINT32                TxtDprMemorySize;         ///< Size of DPR protected memory reserved for Intel TXT component.
  EFI_PHYSICAL_ADDRESS  TxtDprMemoryBase;         ///< Base address of DPR protected memory reserved for Intel TXT component.
  UINT64                TxtLcpPdSize;             ///< Size of Platform Default Launch Control Policy data if installed in flash part. Zero otherwise.
  EFI_PHYSICAL_ADDRESS  TxtLcpPdBase;             ///< Base address of Platform Default Launch Control Policy data if installed in flash part. Zero otherwise.
  EFI_PHYSICAL_ADDRESS  ApStartupBase;            ///< Base address of TXT AP Startup code
  EFI_PHYSICAL_ADDRESS  BiosAcmBase;              ///< Base address of BIOS ACM in flash part
  UINT32                BiosAcmSize;              ///< Size of ACM Binary.
  UINT32                TgaSize;                  ///< Size of Trusted Graphics Aperture if supported by chipset.
  UINT32                IsTPMPresence;
} CPU_TXT_PREMEM_CONFIG;

#pragma pack (pop)

#endif // _CPU_TXT_CONFIG_H_
