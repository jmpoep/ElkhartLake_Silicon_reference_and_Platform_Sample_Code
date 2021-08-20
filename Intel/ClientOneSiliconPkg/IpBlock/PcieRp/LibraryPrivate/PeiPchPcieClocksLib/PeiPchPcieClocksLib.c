/** @file
  This file contains functions that initialize PCI Express clock sources in PCH.

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

#include <Ppi/SiPolicy.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiPchPcieClocksLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchPcrLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/PchFiaLib.h>
#include <Library/TimerLib.h>
PCH_PCIE_CLOCK *mClockPolicy = NULL;

/**
  Retrieves and returns PCIe Clocks Policy.
  After 1st call the result is cached to speed up following requests.

  @retval  pointer to PCIe Clocks Policy
**/
STATIC
PCH_PCIE_CLOCK*
GetClocksPolicy (
  VOID
  )
{
  EFI_STATUS                         Status;
  SI_PREMEM_POLICY_PPI               *SiPreMemPolicyPpi;
  PCH_PCIE_RP_PREMEM_CONFIG          *PchPciePeiPreMemConfig;

  if (mClockPolicy == NULL) {
    //
    // Get Policy settings through the SiPolicy PPI
    //
    Status = PeiServicesLocatePpi (
               &gSiPreMemPolicyPpiGuid,
               0,
               NULL,
               (VOID **) &SiPreMemPolicyPpi
               );
    ASSERT_EFI_ERROR (Status);
    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gPcieRpPreMemConfigGuid, (VOID *) &PchPciePeiPreMemConfig);
    ASSERT_EFI_ERROR (Status);
    mClockPolicy = &(PchPciePeiPreMemConfig->PcieClock[0]);
  }
  return mClockPolicy;
}

/**
  Get the virtual wire CLKREQ message index for CPU PCIe root port.
  This step is neccessary since there is no explicit hardware indexing
  for PEG root ports. For instance PEG60 which is treated by BIOS as
  CPU root port 1 is advertising itself as CPU root port 3 on virtual wire
  message.

  @note: This function can be in PEG library to indicate the mapping.

  @param[in] RpIndex  CPU PCIe root port index

  @retval Root port index given root port uses in virtual wire CLKREQ message
**/
STATIC
UINT32
GetCpuRpVirtualWireClkReqIndex (
  IN UINT32  RpIndex
  )
{
  switch (RpIndex) {
    case 0:
      return 3; // PEG60
    case 1:
      return 0; // PEG10
    case 2:
      return 1; // PEG11
    case 3:
      return 2; // PEG12
    default:
      ASSERT  (FALSE);
      return 0;
  }
}

/**
  Assign CLKREQ# to PCH PCIe ports
**/
VOID
PchConfigurePchPciePortsClkReqMapping (
  VOID
  )
{
  UINT8  MaxPciePortNum;
  UINT8  PortIndex;
  UINT8  ClkReqMap[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8  ClkReqNum;

  MaxPciePortNum = GetPchMaxPciePortNum ();
  ASSERT (MaxPciePortNum <= PCH_MAX_PCIE_ROOT_PORTS);

  for (PortIndex = 0; PortIndex < MaxPciePortNum; PortIndex++) {
    ClkReqNum = FindClkReqForUsage (PchClockUsagePchPcie0 + PortIndex);
    if (ClkReqNum == PCH_PCIE_NO_SUCH_CLOCK) {
      ClkReqMap[PortIndex] = PCH_FIA_NO_CLKREQ;
    } else {
      ClkReqMap[PortIndex] = ClkReqNum;
    }
  }

  PchFiaAssignPchPciePortsClkReq (ClkReqMap, MaxPciePortNum);
}

/**
  Configure CLK REQ for given CPU PCIe port
  If given port has a clock source assigned and that clock source has a clock request signal,
  then the corresponding GPIO pad is configured into ClkReq mode

  @param[in]  RpIndex  RootPort Index
**/
VOID
PchConfigureCpuPciePortClkReqMapping (
  IN UINT32  RpIndex
  )
{
  UINT8  ClkReqNum;
  UINT32  CpuPcieVwClkReqIndex;

  ClkReqNum = FindClkReqForUsage (PchClockUsageCpuPcie0 + RpIndex);
  if (ClkReqNum == PCH_PCIE_NO_SUCH_CLOCK) {
    ClkReqNum = PCH_FIA_NO_CLKREQ;
  }
  CpuPcieVwClkReqIndex = GetCpuRpVirtualWireClkReqIndex (RpIndex);
  PchFiaAssignCpuPciePortClkReq (CpuPcieVwClkReqIndex, ClkReqNum);
}

/**
Enable CLK REQ for given CPU PCIe port
If given port has a clock source assigned and that clock source has a clock request signal,
then the corresponding GPIO pad is configured into ClkReq mode

@param[in]  RpIndex  RootPort Index
**/
VOID
PchEnableCpuPciePortClkReqMapping (
IN UINT32  RpIndex
)
{
  UINT8  ClkReqNum;
  UINT32  CpuPcieVwClkReqIndex;
  DEBUG((DEBUG_INFO, "PchEnableCpuPciePortClkReqMapping Entry\n"));

  ClkReqNum = FindClkReqForUsage(PchClockUsageCpuPcie0 + RpIndex);
  if (ClkReqNum == PCH_PCIE_NO_SUCH_CLOCK) {
    ClkReqNum = PCH_FIA_NO_CLKREQ;
  }
  CpuPcieVwClkReqIndex = GetCpuRpVirtualWireClkReqIndex (RpIndex);
  PchFiaEnableCpuPciePortClkReq (CpuPcieVwClkReqIndex, ClkReqNum);
  DEBUG ((DEBUG_INFO, "PchEnableCpuPciePortClkReqMapping Exit\n"));
}


/**
  Disable CLKREQ message flow for CPU PCIe root port.

  @param[in] RpIndex  CPU PCIe root port index
**/
VOID
PchDisableCpuPciePortClkReq (
  IN UINT32  RpIndex
  )
{
  UINT32  CpuPcieVwClkReqIndex;

  CpuPcieVwClkReqIndex = GetCpuRpVirtualWireClkReqIndex (RpIndex);
  PchFiaAssignCpuPciePortClkReq (CpuPcieVwClkReqIndex, PCH_FIA_NO_CLKREQ);
}

/**
  Get the status of the CPU PCIe CLKREQ

  @param[in] RpIndex  Index of the CPU PCIe root port

  @retval  Status of CPU PCIe CLKREQ
**/
BOOLEAN
PchGetCpuPcieClkReqStatus (
  IN UINT32  RpIndex
  )
{
  UINT32  CpuPcieVwClkReqIndex;

  CpuPcieVwClkReqIndex = GetCpuRpVirtualWireClkReqIndex (RpIndex);
  return PchFiaGetCpuPcieClkReqStatus (CpuPcieVwClkReqIndex);
}

/**
  Assign CLKREQ# to GbE
**/
VOID
PchConfigureGbeClkReqMapping (
  VOID
  )
{
  UINT8  ClkReqNum;

  ClkReqNum = FindClkReqForUsage (PchClockUsageLan);
  if (ClkReqNum == PCH_PCIE_NO_SUCH_CLOCK) {
    PchFiaAssignGbeClkReq (PCH_FIA_NO_CLKREQ);
  } else {
    PchFiaAssignGbeClkReq (ClkReqNum);
  }
}

/**
  Assign CLKREQ# to controllers
  Assignment is based on the platform policy.
**/
VOID
PchConfigureClkreqMapping (
  VOID
  )
{
  PchConfigurePchPciePortsClkReqMapping ();
  PchConfigureGbeClkReqMapping ();
}

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
  )
{
  UINT32      ClkReqNumber;
  GPIO_PAD    ClkReqPad;
  GPIO_CONFIG PadConfig;
  EFI_STATUS  Status;
  UINT32      GpioValue;

  ClkReqNumber = FindClkReqForUsage (ClockUsage);
  if (ClkReqNumber == PCH_PCIE_NO_SUCH_CLOCK || ClkReqNumber >= GetPchMaxPcieClockNum ()) {
    return EFI_UNSUPPORTED;
  }
  ClkReqPad = GpioGetClkreqPad (ClkReqNumber);

  ZeroMem (&PadConfig, sizeof (PadConfig));
  PadConfig.PadMode      = GpioPadModeGpio;
  PadConfig.Direction    = GpioDirIn;
  GpioSetPadConfig (ClkReqPad, &PadConfig);
  //
  // Wait some time to make sure GPIO pad was reconfigured and its input value propagated to internal logic
  //
  MicroSecondDelay (5);

  Status = GpioGetInputValue (ClkReqPad, &GpioValue);
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }
  if (GpioValue != 0) {
    return EFI_DEVICE_ERROR;
  }
  return EFI_SUCCESS;
}

/**
  Checks if given PCIe port is assigned with Clock Request signal

  @param[in]  ClockUsage  type and number of PCIe port to check ClkReq for
  @retval     TRUE        there's a ClkReq pad corresponding to given Port
  @retval     FALSE       there's no ClkReq pad corresponding to given Port
**/
BOOLEAN
IsClkReqAssigned (
  PCH_PCIE_CLOCK_USAGE ClockUsage
  )
{
  UINT32 ClkNumber;
  UINT32 ClkReqNumber;

  ClkNumber = ClockUsageToClockNumber (GetClocksPolicy (), ClockUsage);
  if (ClkNumber == PCH_PCIE_NO_SUCH_CLOCK) {
    return FALSE;
  }
  ClkReqNumber = ClockNumberToClkReqNumber (GetClocksPolicy (), ClkNumber);
  if (ClkReqNumber == PCH_PCIE_NO_SUCH_CLOCK) {
    return FALSE;
  }
  return TRUE;
}

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
  )
{
  UINT32 ClkNumber;
  UINT32 ClkReqNumber;

  ClkNumber = ClockUsageToClockNumber (GetClocksPolicy (), ClockUsage);
  if (ClkNumber == PCH_PCIE_NO_SUCH_CLOCK) {
    return EFI_UNSUPPORTED;
  }
  ClkReqNumber = ClockNumberToClkReqNumber (GetClocksPolicy (), ClkNumber);
  if (ClkReqNumber == PCH_PCIE_NO_SUCH_CLOCK || ClkReqNumber >= GetPchMaxPcieClockNum ()) {
    return EFI_UNSUPPORTED;
  }
  GpioEnableClkreq (ClkReqNumber);
  return EFI_SUCCESS;
}

/**
  Disables one PCIe clock.

  @param[in] ClockUsage    type and number of PCIe port for which Clock should be disabled
**/
VOID
DisableClock (
  PCH_PCIE_CLOCK_USAGE ClockUsage
  )
{
  UINT32 ClkNumber;

  ClkNumber = ClockUsageToClockNumber (GetClocksPolicy (), ClockUsage);
  if (ClkNumber == PCH_PCIE_NO_SUCH_CLOCK) {
    return;
  }
  PmcSetPcieClockEnableMask ((BIT0 << ClkNumber), 0);
}

/**
  Disables all PCIe clocks which are not used according to Policy
**/
VOID
DisableUnusedPcieClocks (
  VOID
  )
{
  UINT32          Index;
  PCH_PCIE_CLOCK* ClocksPolicy;

  ClocksPolicy = GetClocksPolicy ();
  for (Index = 0; Index < GetPchMaxPcieClockNum (); Index++) {
    if (ClocksPolicy[Index].Usage == PchClockUsageNotUsed) {
      PmcSetPcieClockEnableMask ( (BIT0 << Index), 0);
    }
  }
}

/**
  This function scans PCH PCIE configuration and finds CLK_REQ signal that corresponds to given usage.

  @param[in]  ClockUsage   purpose of this CLK_SRC signal, either root port index or LAN
  @retval     number of CLK_REQ signal if any is assigned, PCH_PCIE_NO_SUCH_CLOCK otherwise
**/
UINT8
FindClkReqForUsage (
  PCH_PCIE_CLOCK_USAGE  ClockUsage
  )
{
  UINT32 Index;
  PCH_PCIE_CLOCK* ClocksPolicy;

  ClocksPolicy = GetClocksPolicy ();
  for (Index = 0; Index < GetPchMaxPcieClockNum (); Index++) {
    if (ClocksPolicy[Index].Usage == ClockUsage) {
      if (ClocksPolicy[Index].ClkReq < GetPchMaxPcieClockNum ()) {
        return ClocksPolicy[Index].ClkReq;
      } else {
        return PCH_PCIE_NO_SUCH_CLOCK;
      }
    }
  }
  return PCH_PCIE_NO_SUCH_CLOCK;
}

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
  )
{
  UINT8 Index;

  for (Index = 0; Index < GetPchMaxPcieClockNum (); Index++) {
    if (ClocksPolicy[Index].Usage == ClockUsage) {
      return Index;
    }
  }
  return 0xFF;
}

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
  )
{
  if (ClocksPolicy[ClkSrcNumber].ClkReq < GetPchMaxPcieClockNum ()) {
    return ClocksPolicy[ClkSrcNumber].ClkReq;
  } else {
    return PCH_PCIE_NO_SUCH_CLOCK;
  }
}

