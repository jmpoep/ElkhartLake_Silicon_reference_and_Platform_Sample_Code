/** @file
  This file contains definitions of Hybrid Graphics information

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#ifndef _HYBRID_GRAPHICS_INFO_H_
#define _HYBRID_GRAPHICS_INFO_H_

///
/// HgMode settings
///
typedef enum {
  HgModeDisabled = 0,
  HgModeReserved,
  HgModeMuxless,
  HgModeDgpu,
  HgModeMax
} HG_MODE;

///
/// Hybrid Graphics defines.
///
#define CONVENTIONAL_MEMORY_TOP 0xA0000 ///< 640 KB
#define BIN_FILE_SIZE_MAX       0x10000

#define OPTION_ROM_SIGNATURE    0xAA55

///
/// PCIe Capability Equates
///
#define PCIE_CAP_ID  0x10

#define GP_ENABLE   1
#define GP_DISABLE  0

#ifndef FALSE
#define FALSE 0
#endif

#ifndef HIGH
#define HIGH  1
#endif

#ifndef LOW
#define LOW 0
#endif

#define HG_DELAY_HOLD_RST    100 * STALL_ONE_MILLI_SECOND
#define HG_DELAY_PWR_ENABLE  300 * STALL_ONE_MILLI_SECOND

#pragma pack(1)
typedef struct {
  UINT16  Signature;  ///< 0xAA55
  UINT8   Reserved[22];
  UINT16  PcirOffset;
} VBIOS_OPTION_ROM_HEADER;
#pragma pack()

#pragma pack(1)
typedef struct {
  UINT32  Signature;  ///< "PCIR"
  UINT16  VendorId;
  UINT16  DeviceId;
  UINT16  Reserved0;
  UINT16  Length;
  UINT8   Revision;
  UINT8   ClassCode[3];
  UINT16  ImageLength;
  UINT16  CodeRevision;
  UINT8   CodeType;
  UINT8   Indicator;
  UINT16  Reserved1;
} VBIOS_PCIR_STRUCTURE;
#pragma pack()



#endif
