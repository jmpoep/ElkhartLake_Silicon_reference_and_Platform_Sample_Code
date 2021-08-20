/** @file
  Header file for CPU REGBAR ACCESS library.

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
#ifndef _CPU_REGBAR_ACCESS_LIB_H_
#define _CPU_REGBAR_ACCESS_LIB_H_

#define INVALID_DATA_64  0xFFFFFFFFFFFFFFFF
#define INVALID_DATA_32  0xFFFFFFFF
#define INVALID_DATA_16  0xFFFF
#define INVALID_DATA_8   0xFF
#define INVALID_PID      0xFF

typedef UINT8    CPU_SB_DEVICE_PID;

/**
  Read REGBAR register.
  It returns REGBAR register and size in 8bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid      CPU SB Device Port ID
  @param[in]  Offset              Register offset of this Port ID

  @retval     UINT64           REGBAR register value.
**/
UINT64
CpuRegbarRead64 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset
  );


/**
  Read REGBAR register.
  It returns REGBAR register and size in 4bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid      CPU SB Device Port ID
  @param[in]  Offset              Register offset of this Port ID

  @retval     UINT32           REGBAR register value.
**/
UINT32
CpuRegbarRead32 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset
  );

/**
  Read REGBAR register.
  It returns REGBAR register and size in 2bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid      CPU SB Device Port ID
  @param[in]  Offset              Register offset of this Port ID

  @retval     UINT16           REGBAR register value.
**/
UINT16
CpuRegbarRead16 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset
  );

/**
  Read REGBAR register.
  It returns REGBAR register and size in 1bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid      CPU SB Device Port ID
  @param[in]  Offset              Register offset of this Port ID

  @retval     UINT8            REGBAR regsiter value
**/
UINT8
CpuRegbarRead8 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset
  );

/**
  Write REGBAR register.
  It programs REGBAR register and size in 8bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid      CPU SB Device Port ID
  @param[in]  Offset              Register offset of Port ID.
  @param[in]  Data             Input Data. Must be the same size as Size parameter.

  @retval     UINT64           Value written to register
**/
UINT64
CpuRegbarWrite64 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT64                            Data
  );


/**
  Write REGBAR register.
  It programs REGBAR register and size in 4bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid      CPU SB Device Port ID
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  Data             Input Data. Must be the same size as Size parameter.

  @retval     UINT32           Value written to register
**/
UINT32
CpuRegbarWrite32 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT32                            Data
  );

/**
  Write REGBAR register.
  It programs REGBAR register and size in 2bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid      CPU SB Device Port ID
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  Data             Input Data. Must be the same size as Size parameter.

  @retval     UINT16           Value written to register
**/
UINT16
CpuRegbarWrite16 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT16                            Data
  );

/**
  Write REGBAR register.
  It programs REGBAR register and size in 1bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid      CPU SB Device Port ID
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  Data             Input Data. Must be the same size as Size parameter.

  @retval     UINT8            Value written to register
**/
UINT8
CpuRegbarWrite8 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT8                             Data
  );

/**
  Write REGBAR register.
  It programs REGBAR register and size in 4bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid      CPU SB Device Port ID
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  OrData           OR Data. Must be the same size as Size parameter.

  @retval     UINT32           Value written to register

**/
UINT32
CpuRegbarOr32 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT32                            OrData
  );

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
  );

/**
  Write REGBAR register.
  It programs REGBAR register and size in 1bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid      CPU SB Device Port ID
  @param[in]  Offset           Register offset of Port ID.
  @param[in]  OrData           OR Data. Must be the same size as Size parameter.

  @retval     UINT8            Value written to register

**/
UINT8
CpuRegbarOr8 (
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT8                             OrData
  );

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
  IN  CPU_SB_DEVICE_PID                 CpuSbDevicePid,
  IN  UINT16                            Offset,
  IN  UINT32                            AndData
  );

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
  );

/**
  Write REGBAR register.
  It programs REGBAR register and size in 4bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid      CPU SB Device Port ID
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
  );

/**
  Write REGBAR register.
  It programs REGBAR register and size in 2bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid      CPU SB Device Port ID
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
  );

/**
  Write REGBAR register.
  It programs REGBAR register and size in 1bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  CpuSbDevicePid      CPU SB Device Port ID
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
  );

#endif
