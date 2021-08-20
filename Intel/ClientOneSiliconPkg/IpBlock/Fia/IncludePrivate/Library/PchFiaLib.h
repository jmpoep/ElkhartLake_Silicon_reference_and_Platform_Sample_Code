/** @file
  Header file for PchFiaLib.
  FIA functions will not work when HOST SAI is POSTBOOT_SAI as FIA
  registers are accessible for host only with HOSTIA_BOOT_SAI and HOSTIA_SMM_SAI

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#ifndef _PCH_FIA_LIB_H_
#define _PCH_FIA_LIB_H_

#include <Ppi/SiPolicy.h>

#define PCH_FIA_NO_CLKREQ  0xFF

/**
  Checks if a given PCIe lane is assigned any FIA lane

  @param[in]  RpIndex      PCIe root port index
  @param[in]  RpLaneIndex  Root port lane index within given root port

  @return  TRUE if given PCIe lane is assigned a FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaIsPcieRootPortLaneConnected (
  IN UINT32  RpIndex,
  IN UINT32  RpLaneIndex
  );

/**
  Checks if a given SATA port is assigned any FIA lane

  @param[in] SataCtrlIndex  SATA controller index
  @param[in] SataPortIndex  SATA port index

  @return TRUE if given SATA port is assigned a FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaIsSataPortConnected (
  IN UINT32  SataCtrlIndex,
  IN UINT32  SataPortIndex
  );

/**
  Checks if a given USB3 port is assigned any FIA lane

  @param[in]  Usb3PortIndex  USB3 port index

  @return TRUE if given USB3 port is assigned a FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaIsUsb3PortConnected (
  IN UINT32  Usb3PortIndex
  );

/**
  Check if UFS lane is assigned a FIA lane

  @param[in] UfsControllerIndex  UFS controller index
  @param[in] UfsLaneIndex        Lane index local to given UFS controller

  @retval TRUE   UFS lane is assigned a FIA lane
  @retval FALSE  UFS lane is not assigned any FIA lane
**/
BOOLEAN
PchFiaIsUfsLaneConnected (
  IN UINT32  UfsControllerIndex,
  IN UINT32  UfsLaneIndex
  );


/**
  Check if TSN lane is assigned a FIA lane and returns the FIA Lane

  @param[in]  TsnPortIndex  TSN Controller Port Index
  @param[out] TsnLaneIndex  Lane Index of the TSN Controller Port

  @retval TRUE  TSN lane is assigned a FIA lane
  @retval FALSE  TSN lane is not assigned any FIA lane
**/
BOOLEAN
PchFiaGetTsnLaneNum (
  IN UINT32  TsnPortIndex,
  IN UINT8   *TsnLaneIndex
  );

/**
  Returns GbE over PCIe port number when GbE is enabled

  @return PCIe root port number(1- based), 0 if GbE over PCIe is disabled
**/
UINT32
PchFiaGetGbePortNumber (
  VOID
  );

/**
  Returns a FIA lane number for a given PCIe lane.

  @param[in]  PciePhysicalLane  Index of the PCIe lane
  @param[out] LaneNum           Pointer to the variable that stores lane number.
                                The output value is only valid if this function returns TRUE.

  @return TRUE if given PciePhysicalLane owns FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaGetPcieLaneNum (
  IN  UINT32  PciePhysicalLane,
  OUT UINT8   *LaneNum
  );

/**
  Returns a FIA lane number for a given PCIe root port
  This function handles PCIe lane reversal internaly.

  @param[in]  RpIndex       PCIe root port index
  @param[in]  RpLaneIndex   Root port lane index within given root port
  @param[out] LaneNum       Pointer to the variable that stores lane number.
                            The output value is only valid if this function returns TRUE.

  @return TRUE if given RpLane owns FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaGetPcieRootPortLaneNum (
  IN  UINT32  RpIndex,
  IN  UINT32  RpLaneIndex,
  OUT UINT8   *LaneNum
  );

/**
  Returns a FIA lane number for a given SATA port.

  @param[in]  SataCtrlIndex  SATA controller index
  @param[in]  SataPortIndex  SATA port index
  @param[out] LaneNum        Pointer to the variable that stores lane number.
                             The output value is only valid if this function returns TRUE.

  @return TRUE if given SATA port owns FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaGetSataLaneNum (
  IN  UINT32  SataCtrlIndex,
  IN  UINT32  SataPortIndex,
  OUT UINT8   *LaneNum
  );

/**
  Returns a FIA lane number for a given USB3 port.

  @param[in]  Usb3PortIndex  USB3 port index
  @param[out] LaneNum        Pointer to the variable that stores lane number.
                             The output value is only valid if this function returns TRUE.

  @return TRUE if given USB3 port owns FIA lane, FALSE otherwise
**/
BOOLEAN
PchFiaGetUsb3LaneNum (
  IN  UINT32  Usb3PortIndex,
  OUT UINT8   *LaneNum
  );

/**
  Print FIA LOS registers.
**/
VOID
PchFiaPrintLosRegisters (
  VOID
  );

/**
  Assigns CLKREQ# to PCH PCIe ports

  @param[in] ClkReqMap      Mapping between PCH PCIe ports and CLKREQ#
  @param[in] ClkReqMapSize  Size of the map
**/
VOID
PchFiaAssignPchPciePortsClkReq (
  IN UINT8  *ClkReqMap,
  IN UINT8  ClkReqMapSize
  );

/**
  Assigns CLKREQ# to CPU PCIe ports

  @param[in] RpIndex        Rootport index
  @param[in] ClkReqNum      Number of the clock
**/
VOID
PchFiaAssignCpuPciePortClkReq (
  IN UINT32       RpIndex,
  IN UINT8        ClkReqNum
  );

/**
Enable CLKREQ# to CPU PCIe ports

@param[in] RpIndex        Rootport index
@param[in] ClkReqNum      Number of the clock
**/
VOID
PchFiaEnableCpuPciePortClkReq (
  IN UINT32       RpIndex,
  IN UINT8        ClkReqNum
  );

/**
  Return the status of the CLKREQ state received with VW msg.

  @param[in] RpIndex  CPU PCIe index.

  @return Status of the CLKREQ.
**/
BOOLEAN
PchFiaGetCpuPcieClkReqStatus (
  IN UINT32  RpIndex
  );
/**
  Configure FIA Orientation Muxing
**/
VOID
PchFiaConfigureOrientationMuxing (
  IN SI_POLICY_PPI *SiPolicyPpi
  );

/**
  Assigns CLKREQ# to GbE

  @param[in]  ClkReqNum  CLKREQ# number
**/
VOID
PchFiaAssignGbeClkReq (
  IN UINT8  ClkReqNum
  );

/**
  Configures lower bound of delay between ClkReq assertion and driving RefClk.
**/
VOID
PchFiaSetClockOutputDelay (
  VOID
  );

/**
  Performs FIA programming required at the end of configuration and locks lockable FIA registers

  @param[in] SiPolicyPpi     Pointer to SI_POLICY_PPI
**/
VOID
PchFiaFinalizeConfigurationAndLock (
  IN SI_POLICY_PPI  *SiPolicy
  );

#endif // _PCH_FIA_LIB_H_
