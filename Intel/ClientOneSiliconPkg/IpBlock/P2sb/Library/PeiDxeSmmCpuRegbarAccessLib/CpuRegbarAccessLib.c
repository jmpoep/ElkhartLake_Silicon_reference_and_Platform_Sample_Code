/** @file
  CPU REGBAR ACCESS library.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/CpuRegbarAccessLib.h>

/**
  Definition for REGBAR address
  The REGBAR address is used for the CPU IP's SB register access
**/
#define CPU_REGBAR_ADDRESS(Pid, Offset)    (PcdGet32(PcdRegBarBaseAddress) | ((UINT8)(Pid) << 16) | (UINT16)(Offset))

/**
  Read REGBAR register.
  It returns REGBAR register and size in 8bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
  @param[in]  Offset           Register offset of this Port ID

  @retval     UINT64           REGBAR register value.
**/
UINT64
CpuRegbarRead64 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset
  )
{
  UINT8    Pid;

  Pid = CpuSbDevicePid;
  if (Pid != INVALID_PID)
    return ((UINT64) MmioRead32 (CPU_REGBAR_ADDRESS (Pid, Offset)) + LShiftU64 ((UINT64) MmioRead32 (CPU_REGBAR_ADDRESS (Pid, Offset+4)), 32));
  else
    return INVALID_DATA_64;
}


/**
  Read REGBAR register.
  It returns REGBAR register and size in 4bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
  @param[in]  Offset              Register offset of this Port ID

  @retval     UINT32           REGBAR register value.
**/
UINT32
CpuRegbarRead32 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset
  )
{
  UINT8    Pid;

  Pid = CpuSbDevicePid;
  if (Pid != INVALID_PID)
    return MmioRead32 (CPU_REGBAR_ADDRESS (Pid, Offset));
  else
    return INVALID_DATA_32;
}

/**
  Read REGBAR register.
  It returns REGBAR register and size in 2bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
  @param[in]  Offset           Register offset of this Port ID

  @retval     UINT16           REGBAR register value.
**/
UINT16
CpuRegbarRead16 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset
  )
{
  UINT8    Pid;

  Pid = CpuSbDevicePid;
  if (Pid != INVALID_PID)
    return MmioRead16 (CPU_REGBAR_ADDRESS (Pid, Offset));
  else
    return INVALID_DATA_16;
}

/**
  Read REGBAR register.
  It returns REGBAR register and size in 1bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
  @param[in]  Offset           Register offset of this Port ID

  @retval     UINT8            REGBAR regsiter value
**/
UINT8
CpuRegbarRead8 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset
  )
{
  UINT8    Pid;

  Pid = CpuSbDevicePid;
  if (Pid != INVALID_PID)
    return MmioRead8 (CPU_REGBAR_ADDRESS (Pid, Offset));
  else
    return INVALID_DATA_8;
}


/**
  Write REGBAR register.
  It programs REGBAR register and size in 8bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  Data             Input Data. Must be the same size as Size parameter.

  @retval     UINT64           Value written to register
**/
UINT64
CpuRegbarWrite64 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT64                            Data
  )
{
  UINT8       Pid;

  Pid = CpuSbDevicePid;
  if (Pid != INVALID_PID) {
    MmioWrite32 (CPU_REGBAR_ADDRESS (Pid, Offset) + 4, (UINT32) RShiftU64 (Data, 32));
    MmioWrite32 (CPU_REGBAR_ADDRESS (Pid, Offset), (UINT32) Data);
    return Data;
  }
  else
    return INVALID_DATA_64;
}


/**
  Write REGBAR register.
  It programs REGBAR register and size in 4bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  Data             Input Data. Must be the same size as Size parameter.

  @retval     UINT32           Value written to register
**/
UINT32
CpuRegbarWrite32 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT32                            Data
  )
{
  UINT8    Pid;

  Pid = CpuSbDevicePid;
  if (Pid != INVALID_PID)
    return MmioWrite32 (CPU_REGBAR_ADDRESS (Pid, Offset), Data);
  else
    return INVALID_DATA_32;
}

/**
  Write REGBAR register.
  It programs REGBAR register and size in 2bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  Data             Input Data. Must be the same size as Size parameter.

  @retval     UINT16           Value written to register
**/
UINT16
CpuRegbarWrite16 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT16                            Data
  )
{
  UINT8    Pid;

  Pid = CpuSbDevicePid;
  if (Pid != INVALID_PID)
    return MmioWrite16 (CPU_REGBAR_ADDRESS (Pid, Offset), Data);
  else
    return INVALID_DATA_16;
}

/**
  Write REGBAR register.
  It programs REGBAR register and size in 1bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  Data             Input Data. Must be the same size as Size parameter.

  @retval     UINT8            Value written to register
**/
UINT8
CpuRegbarWrite8 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT8                             Data
  )
{
  UINT8    Pid;

  Pid = CpuSbDevicePid;
  if (Pid != INVALID_PID)
    return MmioWrite8 (CPU_REGBAR_ADDRESS (Pid, Offset), Data);
  else
    return INVALID_DATA_8;
}

/**
  Write REGBAR register.
  It programs REGBAR register and size in 4bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  OrData           OR Data. Must be the same size as Size parameter.

  @retval     UINT32           Value written to register

**/
UINT32
CpuRegbarOr32 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT32                            OrData
  )
{
  return CpuRegbarWrite32 (CpuSbDevicePid, Offset, CpuRegbarRead32(CpuSbDevicePid, Offset) | OrData);
}

/**
  Write REGBAR register.
  It programs REGBAR register and size in 2bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  OrData           OR Data. Must be the same size as Size parameter.

  @retval     UINT16           Value written to register

**/
UINT16
CpuRegbarOr16 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT16                            OrData
  )
{
  return CpuRegbarWrite16 (CpuSbDevicePid, Offset, CpuRegbarRead8(CpuSbDevicePid, Offset) | OrData);
}

/**
  Write REGBAR register.
  It programs REGBAR register and size in 1bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  OrData           OR Data. Must be the same size as Size parameter.

  @retval     UINT8            Value written to register

**/
UINT8
CpuRegbarOr8(
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT8                             OrData
  )
{
  return CpuRegbarWrite8 (CpuSbDevicePid, Offset, CpuRegbarRead8(CpuSbDevicePid, Offset) | OrData);
}

/**
  Performs a bitwise AND of a 32-bit data.
  It programs REGBAR register and size in 4bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevice      CPU SB Device
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  AndData          And Data. Must be the same size as Size parameter.

  @retval     UINT32           Value written to register

**/
UINT32
CpuRegbarAnd32 (
  IN  CPU_SB_DEVICE_PID                     CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT32                            AndData
  )
{
  return CpuRegbarWrite32 (CpuSbDevicePid, Offset, CpuRegbarRead32 (CpuSbDevicePid, Offset) & AndData);
}

/**
  Performs a bitwise AND of a 16-bit data.
  It programs REGBAR register and size in 2bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevice      CPU SB Device
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  AndData          And Data. Must be the same size as Size parameter.

  @retval     UINT16           Value written to register

**/
UINT16
CpuRegbarAnd16 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT16                            AndData
  )
{
  return CpuRegbarWrite16 (CpuSbDevicePid, Offset, CpuRegbarRead16 (CpuSbDevicePid, Offset) & AndData);
}

/**
  Write REGBAR register.
  It programs REGBAR register and size in 4bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  AndData          AND Data. Must be the same size as Size parameter.
  @param[in]  OrData           OR Data. Must be the same size as Size parameter.

  @retval     UINT32           Value written to register

**/
UINT32
CpuRegbarAndThenOr32 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT32                            AndData,
  IN  UINT32                            OrData
  )
{
  return CpuRegbarWrite32 (CpuSbDevicePid, Offset, (CpuRegbarRead32 (CpuSbDevicePid, Offset) & AndData) | OrData);
}

/**
  Write REGBAR register.
  It programs REGBAR register and size in 2bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  AndData          AND Data. Must be the same size as Size parameter.
  @param[in]  OrData           OR Data. Must be the same size as Size parameter.

  @retval     UINT16           Value written to register

**/
UINT16
CpuRegbarAndThenOr16 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT16                            AndData,
  IN  UINT16                            OrData
  )
{
  return CpuRegbarWrite16 (CpuSbDevicePid, Offset, (CpuRegbarRead16 (CpuSbDevicePid, Offset) & AndData) | OrData);
}

/**
  Write REGBAR register.
  It programs REGBAR register and size in 1bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  AndData          AND Data. Must be the same size as Size parameter.
  @param[in]  OrData           OR Data. Must be the same size as Size parameter.

  @retval     UINT8            Value written to register

**/
UINT8
CpuRegbarAndThenOr8 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT8                             AndData,
  IN  UINT8                             OrData
  )
{
  return CpuRegbarWrite8 (CpuSbDevicePid, Offset, (CpuRegbarRead8 (CpuSbDevicePid, Offset) & AndData) | OrData);
}
