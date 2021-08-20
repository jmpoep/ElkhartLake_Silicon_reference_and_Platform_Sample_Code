/** @file
  This file contains functions that initialize PCI Express clock sources in PCH.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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
#ifndef _PEI_PCH_PCIE_CLOCKS_LIB_H_
#define _PEI_PCH_PCIE_CLOCKS_LIB_H_

#include <ConfigBlock.h>
#include <PchPcieRpConfig.h>

/**
  This function assigns a CLKREQ# signal to PCI Express ports and GbE.
  Each enabled ports must have distinct CLKREQ# pin assigned before power management features are enabled.

  Assignment is based on the platform policy with assumption that unused ports will be disabled
  before enabling power management on remaining ports.
**/
VOID
PchConfigureClkreqMapping (
  VOID
  );

/**
  Checks current state of ClkReq GPIO pad that was assigned to given port.
  This function returns error when port has no Clock or ClkReq assigned
  or if GPIO pad is not owned by BIOS. If there's no error, pad's current input value is returned.

  @param[in] ClockUsage     PCIe port for which ClkReq must be checked
  @retval EFI_UNSUPPORTED   no ClkReq assigned or input value can't be read
  @retval EFI_DEVICE_ERROR  wrong pad state, high
  @retval EFI_SUCCESS       ClkReq is in correct state, low
**/
EFI_STATUS
CheckClkReq (
  PCH_PCIE_CLOCK_USAGE ClockUsage
  );


/**
  Checks if given PCIe port is assigned with Clock Request signal

  @param[in]  ClockUsage  type and number of PCIe port to check ClkReq for
  @retval     TRUE        there's a ClkReq pad corresponding to given Port
  @retval     FALSE       there's no ClkReq pad corresponding to given Port
**/
BOOLEAN
IsClkReqAssigned (
  PCH_PCIE_CLOCK_USAGE ClockUsage
  );


/**
  Enables CLK REQ for given PCIe port
  If given port has a clock source assigned and that clock source has a clock request signal,
  then the corresponding GPIO pad is configured into ClkReq mode

  @param[in]  ClockUsage      type and number of PCIe port
  @retval     EFI_SUCCESS     Clock Request was successfully enabled
  @retval     EFI_UNSUPPORTED there's no ClkReq pad corresponding to given Port
**/
EFI_STATUS
EnableClkReq (
  PCH_PCIE_CLOCK_USAGE ClockUsage
  );


/**
  Disables one PCIe clock.

  @param[in] ClockUsage    type and number of PCIe port for which Clock should be disabled
**/
VOID
DisableClock (
  PCH_PCIE_CLOCK_USAGE ClockUsage
  );


/**
  Disables all PCIe clocks which are not used according to Policy
**/
VOID
DisableUnusedPcieClocks (
  VOID
  );


/**
  This function scans PCH PCIE configuration and finds CLK_REQ signal that corresponds to given usage.

  @param[in]  ClockUsage   purpose of this CLK_SRC signal, either root port index or LAN
  @retval     number of CLK_REQ signal if any is assigned, PCH_PCIE_NO_SUCH_CLOCK otherwise
**/
UINT8
FindClkReqForUsage (
  PCH_PCIE_CLOCK_USAGE  ClockUsage
  );


/**
  This function scans PCH PCIE configuration and finds clock number that corresponds to given usage.
  If there's no clock assigned, it will return PCH_PCIE_NO_SUCH_CLOCK

  @param[in]  ClocksPolicy  PCIe clocks configuration policy structure
  @param[in]  ClockUsage   user of clock, either PCH PCIe port, CPU PCIe port or LAN
  @retval     number of clock if any is assigned, PCH_PCIE_NO_SUCH_CLOCK otherwise
**/
UINT8
ClockUsageToClockNumber (
  CONST PCH_PCIE_CLOCK* ClocksPolicy,
  PCH_PCIE_CLOCK_USAGE  ClockUsage
  );


/**
  This function scans PCH PCIE configuration and finds Clock Request signal that corresponds to given Clock Source.
  If there's no CLK_REQ, it will return 0xFF

  @param[in]  ClocksPolicy  PCIe clocks configuration policy structure
  @param[in]  ClkSrcNumber  purpose of this CLK_SRC signal, either PCH PCIe port, CPU PCIe port or LAN
  @retval     number of CLK_REQ signal if any is assigned, PCH_PCIE_NO_SUCH_CLOCK otherwise
**/
UINT8
ClockNumberToClkReqNumber (
  CONST PCH_PCIE_CLOCK* ClocksPolicy,
  UINT32                ClkSrcNumber
  );

/**
  Configure CLK REQ for given CPU PCIe port
  If given port has a clock source assigned and that clock source has a clock request signal,
  then the corresponding GPIO pad is configured into ClkReq mode

  @param[in]  RpIndex  RootPort Index
**/
VOID
PchConfigureCpuPciePortClkReqMapping (
  IN  UINT32  RpIndex
  );

/**
Enable CLK REQ for given CPU PCIe port
If given port has a clock source assigned and that clock source has a clock request signal,
then the corresponding GPIO pad is configured into ClkReq mode

@param[in]  RpIndex  RootPort Index
**/
VOID
PchEnableCpuPciePortClkReqMapping(
IN  UINT32  RpIndex
);

/**
  Disable CLKREQ message flow for CPU PCIe root port.

  @param[in] RpIndex  CPU PCIe root port index
**/
VOID
PchDisableCpuPciePortClkReq (
  IN UINT32  RpIndex
  );

/**
  Get the status of the CPU PCIe CLKREQ

  @param[in] RpIndex  Index of the CPU PCIe root port

  @retval  Status of CPU PCIe CLKREQ
**/
BOOLEAN
PchGetCpuPcieClkReqStatus (
  IN UINT32  RpIndex
  );

#endif
