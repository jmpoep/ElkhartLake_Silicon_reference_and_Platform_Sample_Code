/** @file
  This file contains GPIO routines for RC usage

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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
#include "MrcOemPlatform.h"
#include <Library/GpioLib.h>
#include <Library/GpioNativeLib.h>
#include <Private/Library/GpioPrivateLib.h>
#include <Pch/Library/PeiDxeSmmGpioLib/GpioLibrary.h>
#include <Private/GpioNativePads.h>
#include <Register/PchRegsPcr.h>

#include "GpioNativePrivateLibInternal.h"

/**
  This procedure is used to check if GpioPad is valid for certain chipset

  @param[in]  GpioPad             GPIO pad

  @retval TRUE                    This pin is valid on this chipset
          FALSE                   Incorrect pin
**/
BOOLEAN
GpioIsCorrectPadForThisChipset (
  IN  GPIO_PAD        GpioPad
  )
{
  return ((GPIO_GET_CHIPSET_ID (GpioPad) == GpioGetThisChipsetId ()) &&
         (GpioGetGroupIndexFromGpioPad (GpioPad) < GpioGetNumberOfGroups ()));
}

/**
  This procedure will get value of selected gpio register

  @param[in]  Group               GPIO group number
  @param[in]  Offset              GPIO register offset
  @param[out] RegVal              Value of gpio register

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid group or pad number
**/
EFI_STATUS
GpioGetReg (
  IN  GPIO_GROUP              Group,
  IN  UINT32                  Offset,
  OUT UINT32                  *RegVal
  )
{
  CONST GPIO_GROUP_INFO  *GpioGroupInfo;
  UINT32                 GpioGroupInfoLength;
  UINT32                 GroupIndex;

  GroupIndex = GpioGetGroupIndexFromGroup (Group);
  GpioGroupInfo = GpioGetGroupInfoTable (&GpioGroupInfoLength);
  //
  // Check if group argument exceeds GPIO GROUP INFO array
  //
  if ((UINTN) GroupIndex >= GpioGroupInfoLength) {
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  *RegVal = MmioRead32 (PCH_PCR_ADDRESS (GpioGroupInfo[GroupIndex].Community, Offset));

  return EFI_SUCCESS;
}

/**
  This procedure will set value of selected gpio register

  @param[in] Group               GPIO group number
  @param[in] Offset              GPIO register offset
  @param[in] RegVal              Value of gpio register

  @retval EFI_SUCCESS            The function completed successfully
  @retval EFI_INVALID_PARAMETER  Invalid group or pad number
**/
EFI_STATUS
GpioSetReg (
  IN GPIO_GROUP              Group,
  IN UINT32                  Offset,
  IN UINT32                  RegVal
  )
{
  CONST GPIO_GROUP_INFO  *GpioGroupInfo;
  UINT32                 GpioGroupInfoLength;
  UINT32                 GroupIndex;

  GroupIndex = GpioGetGroupIndexFromGroup (Group);
  GpioGroupInfo = GpioGetGroupInfoTable (&GpioGroupInfoLength);
  //
  // Check if group argument exceeds GPIO GROUP INFO array
  //
  if ((UINTN) GroupIndex >= GpioGroupInfoLength) {
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  MmioWrite32 (PCH_PCR_ADDRESS (GpioGroupInfo[GroupIndex].Community, Offset), RegVal);

  return EFI_SUCCESS;
}

/**
  This procedure is used by PchSmiDispatcher and will return information
  needed to register GPI SMI.

  @param[in]  Index                   GPI SMI number
  @param[out] GpioPin                 GPIO pin
  @param[out] GpiSmiBitOffset         GPI SMI bit position within GpiSmi Registers
  @param[out] GpiHostSwOwnRegAddress  Address of HOSTSW_OWN register
  @param[out] GpiSmiStsRegAddress     Address of GPI SMI status register

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid group or pad number
**/
EFI_STATUS
GpioGetPadAndSmiRegs (
  IN UINT32            Index,
  OUT GPIO_PAD         *GpioPin,
  OUT UINT8            *GpiSmiBitOffset,
  OUT UINT32           *GpiHostSwOwnRegAddress,
  OUT UINT32           *GpiSmiStsRegAddress
  )
{
  UINT32                 GroupIndex;
  UINT32                 PadNumber;
  CONST GPIO_GROUP_INFO  *GpioGroupInfo;
  GPIO_GROUP             GpioGroup;
  UINT32                 GpioGroupInfoLength;
  UINT32                 SmiStsRegOffset;
  UINT32                 HostSwOwnRegOffset;
  GPIO_PAD_OWN           PadOwnVal;

  GpioGroupInfo = GpioGetGroupInfoTable (&GpioGroupInfoLength);

  PadNumber = 0;
  GroupIndex = 0;
  for (GroupIndex = 0; GroupIndex < GpioGroupInfoLength; GroupIndex++) {
    PadNumber = Index;
    if (PadNumber < GpioGroupInfo[GroupIndex].PadPerGroup) {
      //
      // Found group and pad number
      //
      break;
    }
    Index = Index - GpioGroupInfo[GroupIndex].PadPerGroup;
  }

  //
  // Check if legal pad number
  //
  if (PadNumber >= GpioGroupInfo[GroupIndex].PadPerGroup){
    return EFI_INVALID_PARAMETER;
  }

  //
  // Check if selected group has GPI SMI Enable and Status registers
  //
  if (GpioGroupInfo[GroupIndex].SmiEnOffset == NO_REGISTER_FOR_PROPERTY) {
    return EFI_INVALID_PARAMETER;
  }

  GpioGroup = GpioGetGroupFromGroupIndex (GroupIndex);
  *GpioPin = GpioGetGpioPadFromGroupAndPadNumber (GpioGroup, PadNumber);

  DEBUG_CODE_BEGIN ();
  //
  // Check if selected GPIO Pad is not owned by CSME/ISH/IE
  //
  GpioGetPadOwnership (*GpioPin, &PadOwnVal);
  if (PadOwnVal != GpioPadOwnHost) {
    DEBUG ((DEBUG_ERROR, "GPIO ERROR: %a not owned by host!\n", GpioName (*GpioPin)));
    return EFI_INVALID_PARAMETER;
  }
  DEBUG_CODE_END ();

  *GpiSmiBitOffset = (UINT8)(PadNumber % 32);

  HostSwOwnRegOffset = GpioGroupInfo[GroupIndex].HostOwnOffset + (PadNumber / 32) * 0x4;
  *GpiHostSwOwnRegAddress = PCH_PCR_ADDRESS (GpioGroupInfo[GroupIndex].Community, HostSwOwnRegOffset);

  SmiStsRegOffset = GpioGroupInfo[GroupIndex].SmiStsOffset + (PadNumber / 32) * 0x4;
  *GpiSmiStsRegAddress = PCH_PCR_ADDRESS (GpioGroupInfo[GroupIndex].Community, SmiStsRegOffset);

  return EFI_SUCCESS;
}

/**
  This procedure will set GPIO Driver IRQ number

  @param[in]  Irq                 Irq number

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid IRQ number
**/
EFI_STATUS
GpioSetIrq (
  IN  UINT8          Irq
  )
{
  UINT32       Data32And;
  UINT32       Data32Or;
  PCH_SBI_PID  *GpioComSbiIds;
  UINT32       NoOfGpioComs;
  UINT32       GpioComIndex;

  Data32And = (UINT32)~(B_GPIO_PCR_MISCCFG_IRQ_ROUTE);
  Data32Or  = (UINT32)Irq << N_GPIO_PCR_MISCCFG_IRQ_ROUTE;

  NoOfGpioComs = GpioGetComSbiPortIds (&GpioComSbiIds);

  //
  // Program MISCCFG register for each community
  //
  for (GpioComIndex = 0; GpioComIndex < NoOfGpioComs; GpioComIndex++) {
    MmioAndThenOr32 (
      PCH_PCR_ADDRESS (GpioComSbiIds[GpioComIndex], R_GPIO_PCR_MISCCFG),
      Data32And,
      Data32Or
      );
  }

  return EFI_SUCCESS;
}

/**
  This procedure will return Port ID of GPIO Community from GpioPad

  @param[in] GpioPad            GpioPad

  @retval GpioCommunityPortId   Port ID of GPIO Community
**/
UINT8
GpioGetGpioCommunityPortIdFromGpioPad (
  IN GPIO_PAD        GpioPad
  )
{
  CONST GPIO_GROUP_INFO  *GpioGroupInfo;
  UINT32                 GpioGroupInfoLength;
  UINT32                 GroupIndex;

  GroupIndex = GpioGetGroupIndexFromGpioPad (GpioPad);

  GpioGroupInfo = GpioGetGroupInfoTable (&GpioGroupInfoLength);

  return GpioGroupInfo[GroupIndex].Community;
}

/**
  This procedure will return PadCfg address from GpioPad

  @param[in] GpioPad            GpioPad

  @retval GpioPadCfgAddress     PadCfg Address of GpioPad
**/
UINT32
GpioGetGpioPadCfgAddressFromGpioPad (
  IN GPIO_PAD        GpioPad
  )
{
  UINT32                 PadCfgRegAddress;
  CONST GPIO_GROUP_INFO  *GpioGroupInfo;
  UINT32                 GpioGroupInfoLength;
  UINT32                 GroupIndex;
  UINT32                 PadNumber;

  GroupIndex = GpioGetGroupIndexFromGpioPad (GpioPad);
  PadNumber = GpioGetPadNumberFromGpioPad (GpioPad);

  GpioGroupInfo = GpioGetGroupInfoTable (&GpioGroupInfoLength);

  //
  // Create Pad Configuration register offset
  //
  PadCfgRegAddress = GpioGroupInfo[GroupIndex].PadCfgOffset + S_GPIO_PCR_PADCFG * PadNumber;

  return PadCfgRegAddress;
}


/**
  This procedure will check if GpioPad is owned by host.

  @param[in] GpioPad       GPIO pad

  @retval TRUE             GPIO pad is owned by host
  @retval FALSE            GPIO pad is not owned by host and should not be used with GPIO lib API
**/
BOOLEAN
GpioIsPadHostOwned (
  IN GPIO_PAD             GpioPad
  )
{
  GPIO_PAD_OWN         PadOwnVal;

  //
  // Check if selected GPIO Pad is not owned by CSME/ISH
  // If GPIO is not owned by Host all access to PadCfg will be dropped
  //
  GpioGetPadOwnership (GpioPad, &PadOwnVal);
  if (PadOwnVal != GpioPadOwnHost) {
    DEBUG ((DEBUG_ERROR, "GPIO ERROR: %a is not owned by host!\n", GpioName (GpioPad)));
    return FALSE;
  }

  return TRUE;
}

/**
  This procedure will check if GpioPad argument is valid.
  Function will check below conditions:
   - GpioPad represents a pad for current PCH
   - GpioPad belongs to valid GpioGroup
   - GPIO PadNumber is not greater than number of pads for this group

  @param[in] GpioPad       GPIO pad

  @retval TRUE             GPIO pad is valid and can be used with GPIO lib API
  @retval FALSE            GPIO pad is invalid and cannot be used with GPIO lib API
**/
BOOLEAN
GpioIsPadValid (
  IN GPIO_PAD             GpioPad
  )
{
  CONST GPIO_GROUP_INFO  *GpioGroupInfo;
  UINT32                 GpioGroupInfoLength;
  UINT32                 PadNumber;

  if (!GpioIsCorrectPadForThisChipset (GpioPad)) {
    DEBUG ((DEBUG_ERROR, "GPIO ERROR: Incorrect GpioPad (0x%08x) used on this chipset!\n", GpioPad));
    goto Error;
  }

  GpioGroupInfo = GpioGetGroupInfoTable (&GpioGroupInfoLength);

  //
  // Check if legal pin number
  //
  PadNumber = GpioGetPadNumberFromGpioPad (GpioPad);
  if (PadNumber >= GpioGroupInfo[GpioGetGroupIndexFromGpioPad (GpioPad)].PadPerGroup) {
    DEBUG ((DEBUG_ERROR, "GPIO ERROR: Pin number (%d) exceeds possible range for this group\n", PadNumber));
    goto Error;
  }

  return TRUE;
Error:
  ASSERT (FALSE);
  return FALSE;
}

/**
  This procedure will read GPIO Pad Configuration register

  @param[in] GpioPad          GPIO pad
  @param[in] DwReg            Choose PADCFG register: 0:DW0, 1:DW1

  @retval PadCfgRegValue      PADCFG_DWx value
**/
UINT32
GpioReadPadCfgReg (
  IN GPIO_PAD             GpioPad,
  IN UINT8                DwReg
  )
{
  UINT32                 PadCfgReg;
  CONST GPIO_GROUP_INFO  *GpioGroupInfo;
  UINT32                 GpioGroupInfoLength;
  UINT32                 GroupIndex;
  UINT32                 PadNumber;

  GroupIndex = GpioGetGroupIndexFromGpioPad (GpioPad);
  PadNumber = GpioGetPadNumberFromGpioPad (GpioPad);

  GpioGroupInfo = GpioGetGroupInfoTable (&GpioGroupInfoLength);

  //
  // Create Pad Configuration register offset
  //
  PadCfgReg = GpioGroupInfo[GroupIndex].PadCfgOffset + S_GPIO_PCR_PADCFG * PadNumber + 0x4 * DwReg;

  return MmioRead32 (PCH_PCR_ADDRESS (GpioGroupInfo[GroupIndex].Community, PadCfgReg));
}

/**
  This procedure will write or read GPIO Pad Configuration register

  @param[in] GpioPad              GPIO pad
  @param[in] DwReg                Choose PADCFG register: 0:DW0, 1:DW1
  @param[in] PadCfgAndMask        Mask to be AND'ed with PADCFG reg value
  @param[in] PadCfgOrMask         Mask to be OR'ed with PADCFG reg value

  @retval none
**/
VOID
GpioWritePadCfgReg (
  IN GPIO_PAD             GpioPad,
  IN UINT8                DwReg,
  IN UINT32               PadCfgAndMask,
  IN UINT32               PadCfgOrMask
  )
{
  UINT32                 PadCfgReg;
  CONST GPIO_GROUP_INFO  *GpioGroupInfo;
  UINT32                 GpioGroupInfoLength;
  UINT32                 GroupIndex;
  UINT32                 PadNumber;
  UINT32                 PadCfgLock;
  UINT32                 PadCfgLockTx;

  PadCfgLock = 0;
  PadCfgLockTx = 0;
#ifndef MRC_MINIBIOS_BUILD
  //
  // Check if Pad Configuration (except output state) is to be changed.
  // If AND and OR masks will indicate that configuration fields (other than output control)
  // are to be modified it means that there is a need to perform an unlock (if set)
  //
  if ((~PadCfgAndMask | PadCfgOrMask) & (UINT32)~B_GPIO_PCR_TX_STATE) {
    GpioGetPadCfgLock (GpioPad, &PadCfgLock);
    if (PadCfgLock) {
      GpioUnlockPadCfg (GpioPad);
    }
  }

  //
  // Check if Pad Output state is to be changed
  // If AND and OR masks will indicate that output control
  // is to be modified it means that there is a need to perform an unlock (if set)
  //
  if ((~PadCfgAndMask | PadCfgOrMask) & B_GPIO_PCR_TX_STATE) {
    GpioGetPadCfgLockTx (GpioPad, &PadCfgLockTx);
    if (PadCfgLockTx) {
      GpioUnlockPadCfgTx (GpioPad);
    }
  }
#endif // MRC_MINIBIOS_BUILD
  GroupIndex = GpioGetGroupIndexFromGpioPad (GpioPad);
  PadNumber = GpioGetPadNumberFromGpioPad (GpioPad);

  GpioGroupInfo = GpioGetGroupInfoTable (&GpioGroupInfoLength);

  //
  // Create Pad Configuration register offset
  //
  PadCfgReg = GpioGroupInfo[GroupIndex].PadCfgOffset + S_GPIO_PCR_PADCFG * PadNumber + 0x4 * DwReg;

  MmioAndThenOr32 (
    PCH_PCR_ADDRESS (GpioGroupInfo[GroupIndex].Community, PadCfgReg),
    PadCfgAndMask,
    PadCfgOrMask
    );
#ifndef MRC_MINIBIOS_BUILD
  if (PadCfgLock) {
    GpioLockPadCfg (GpioPad);
  }
  if (PadCfgLockTx) {
    GpioLockPadCfgTx (GpioPad);
  }
#endif // MRC_MINIBIOS_BUILD
}

/**
  This procedure will set GPIO mode

  @param[in]  GpioPad             GPIO pad
  @param[in]  PadModeValue        GPIO pad mode value

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid group or pad number
**/
EFI_STATUS
GpioSetPadMode (
  IN GPIO_PAD                GpioPad,
  IN GPIO_PAD_MODE           PadModeValue
  )
{
  UINT32               PadCfgOrMask;

  if (!GpioIsPadValid (GpioPad)) {
    return EFI_INVALID_PARAMETER;
  }

  if (!GpioIsPadHostOwned (GpioPad)) {
    return EFI_UNSUPPORTED;
  }

  if (PadModeValue != (GPIO_PAD_MODE)GpioHardwareDefault) {

    PadCfgOrMask = (((PadModeValue & B_GPIO_PAD_MODE_MASK) >> (N_GPIO_PAD_MODE_BIT_POS + 1)) << N_GPIO_PCR_PAD_MODE);

    GpioWritePadCfgReg (
      GpioPad,
      0,
      (UINT32)~B_GPIO_PCR_PAD_MODE,
      PadCfgOrMask
      );
  }

  return EFI_SUCCESS;
}

/**
  This procedure will set GPIO pad to native mode.
  To be used if no other settings are to be configured when enabling native mode.

  @param[in]  GpioNativePad       GPIO Pad with native mode information

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid group or pad number
**/
EFI_STATUS
GpioSetNativePad (
  IN GPIO_NATIVE_PAD  GpioNativePad
  )
{
  return GpioSetPadMode (GpioNativePad, GPIO_NATIVE_GET_PAD_MODE (GpioNativePad));
}

/**
  This procedure will get GPIO native pad based on provided native function and platform muxing selection (if needed).

  @param[in]  PadFunction         PadMode for a specific native signal. Please refer to GpioNativePads.h
  @param[in]  PinMux              GPIO Native pin mux platform config.
                                  This argument is optional and needs to be
                                  provided only if feature can be enabled
                                  on multiple pads

  @retval  NativePad              GPIO pad with encoded native function
**/
GPIO_NATIVE_PAD
GpioGetNativePadByFunctionAndPinMux (
  IN UINT32  PadFunction,
  IN UINT32  PinMux
  )
{
  GPIO_NATIVE_PAD GpioNativePad;

  GpioNativePad = GpioGetNativePadByFunction (PadFunction);

  if (GpioNativePad != GPIO_PAD_NONE) {
    //
    // For situations where native signal can be enabled only on
    // a single pad then PinMux argument should be set to 0.
    //
    ASSERT (PinMux == GPIO_PAD_NONE);
  } else {
    //
    // If native signal can be enabled on multiple pads
    // then PinMux argument needs to be configured to platform specific value
    //
    GpioNativePad = PinMux;
  }

  //
  // GpioNativePad must contain value that can be used only for a single native function signal.
  // If its value doesn't match native function type or it exceeded its range
  // below assert will catch it.
  //
  if ((GPIO_NATIVE_GET_FUNCTION (GpioNativePad) != GPIO_NATIVE_FUNCTION_GET_VALUE (PadFunction)) ||
      (GPIO_NATIVE_GET_FUNCTION (GpioNativePad) > GPIO_NATIVE_FUNCTION_GET_MAX (PadFunction))) {
    DEBUG ((DEBUG_ERROR, "GPIO ERROR: PadFunction = 0x%08x, GpioNativePad = 0x%08x\n", PadFunction, GpioNativePad));
    ASSERT (FALSE);
    return GPIO_PAD_NONE;
  }

  return GpioNativePad;
}

/**
  This procedure will set GPIO pad to native function based on provided native function
  and platform muxing selection (if needed).

  @param[in]  PadFunction         PadMode for a specific native signal. Please refer to GpioNativePads.h
  @param[in]  PinMux              GPIO Native pin mux platform config.
                                  This argument is optional and needs to be
                                  provided only if feature can be enabled
                                  on multiple pads

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid group or pad number
**/
EFI_STATUS
GpioSetNativePadByFunction (
  IN UINT32  PadFunction,
  IN UINT32  PinMux
  )
{
  GPIO_NATIVE_PAD GpioNativePad;

  GpioNativePad = GpioGetNativePadByFunctionAndPinMux (PadFunction, PinMux);

  if (GpioNativePad != GPIO_PAD_NONE) {
    return GpioSetPadMode (GpioNativePad, GPIO_NATIVE_GET_PAD_MODE (GpioNativePad));
  } else {
    return EFI_INVALID_PARAMETER;
  }
}

/**
  This procedure will get GPIO mode

  @param[in]  GpioPad             GPIO pad
  @param[out] PadModeValue        GPIO pad mode value

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid GpioPad
**/
EFI_STATUS
GpioGetPadMode (
  IN  GPIO_PAD                 GpioPad,
  OUT GPIO_PAD_MODE            *PadModeValue
  )
{
  UINT32        PadCfgRegValue;

  if (!GpioIsPadValid (GpioPad)) {
    return EFI_INVALID_PARAMETER;
  }

  if (!GpioIsPadHostOwned (GpioPad)) {
    return EFI_UNSUPPORTED;
  }

  PadCfgRegValue = GpioReadPadCfgReg (GpioPad, 0);

  *PadModeValue = (GPIO_PAD_MODE)(((PadCfgRegValue & B_GPIO_PCR_PAD_MODE) >> (N_GPIO_PCR_PAD_MODE - (N_GPIO_PAD_MODE_BIT_POS + 1))) | (0x1 << N_GPIO_PAD_MODE_BIT_POS));

  return EFI_SUCCESS;
}

/**
  The function performs GPIO Power Management programming.
**/
VOID
GpioConfigurePm (
  VOID
  )
{
  UINT32       Data32Or;
  UINT32       Data32And;
  PCH_SBI_PID  *GpioComSbiIds;
  UINT32       NoOfGpioComs;
  UINT32       GpioComIndex;

  Data32And = (UINT32)~0,
  //
  // Enable MISCCFG.GPSIDEDPCGEn, MISCCFG.GPRCOMPCDLCGEn, MISCCFG.GPRTCDLCGEn,
  // MISCCFG.GPDLCGEn and MISCCFG.GPDPCGEn for GPIO communities
  //
  Data32Or = (B_GPIO_PCR_MISCCFG_GPSIDEDPCGEN |
              B_GPIO_PCR_MISCCFG_GPRCOMPCDLCGEN |
              B_GPIO_PCR_MISCCFG_GPRTCDLCGEN |
              B_GPIO_PCR_MISCCFG_GPDLCGEN |
              B_GPIO_PCR_MISCCFG_GPDPCGEN);

  NoOfGpioComs = GpioGetComSbiPortIds (&GpioComSbiIds);

  //
  // Configure Clock Gating in each community
  //
  for (GpioComIndex = 0; GpioComIndex < NoOfGpioComs; GpioComIndex++) {
    MmioAndThenOr32 (
      PCH_PCR_ADDRESS (GpioComSbiIds[GpioComIndex], R_GPIO_PCR_MISCCFG),
      Data32And,
      Data32Or
      );
  }
}

/**
  This procedure is used to unlock all GPIO pads.
  This function can only be called when platform is still in HOSTIA_BOOT_SAI.
**/
#ifndef MRC_MINIBIOS_BUILD
VOID
GpioUnlockAllPads (
  VOID
  )
{
  UINT32         DwNum;
  UINT32         GroupIndex;
  UINT32         NumberOfGroups;
  GPIO_GROUP     Group;
  UINT32         LockValue;
  EFI_STATUS     Status;

  NumberOfGroups = GpioGetNumberOfGroups ();

  for (GroupIndex = 0; GroupIndex < NumberOfGroups; GroupIndex++) {
    Group = GpioGetGroupFromGroupIndex (GroupIndex);
    for (DwNum = 0; DwNum <= GPIO_GET_DW_NUM (GpioGetPadPerGroup (Group)); DwNum++) {

      GpioGetPadCfgLockForGroupDw (Group, DwNum, &LockValue);

      if (LockValue) {
        Status = GpioUnlockPadCfgForGroupDw (Group, DwNum, ~0u);
        ASSERT_EFI_ERROR (Status);
      }

      GpioGetPadCfgLockTxForGroupDw (Group, DwNum, &LockValue);

      if (LockValue) {
        Status = GpioUnlockPadCfgTxForGroupDw (Group, DwNum, ~0u);
        ASSERT_EFI_ERROR (Status);
      }
    }
  }
}
#endif // MRC_MINIBIOS_BUILD
/**
  Generates GPIO name from GpioPad
  This function returns pointer to the static buffer

  @param[in] GpioPad  GpioPad

  @retval CHAR8*  Pointer to the gpio name string
**/
CHAR8*
GpioName (
  IN GPIO_PAD  GpioPad
  )
{
#ifdef MRC_MINIBIOS_BUILD
  return NULL;
#else
  return GpioGetPadName (GpioPad, GpioGetStaticNameBuffer (), GPIO_NAME_LENGTH_MAX);
#endif
}

/**
  Generates GPIO name from GpioNativePad
  This function returns pointer to the static buffer.

  @param[in] GpioNativePad  GpioNativePad

  @retval CHAR8*  Pointer to the GPIO name
**/
CHAR8*
GpioPinMuxName (
  IN GPIO_NATIVE_PAD  GpioNativePad
  )
{
  if (GpioNativePad == GPIO_PAD_NONE) {
    return "No muxing";
  } else {
    return GpioName (GpioNativePad);
  }
}

//
// For GPIO debounce feature glitch filter clock is used
// which in CNL is driven by RTC clock with f = 32kHz (T = 31.25us)
//
#define GPIO_DEB_CLK_PERIOD_IN_NS  31250

/**
  This procedure enables debounce feature on a selected pad configured in input mode
  Debounce time can be specified in microseconds. GPIO HW supports only certain values
  according to below formula:
   DebounceTime = (2 ^ PADCFG_DW2.DEBOUNCE)*(glitch filter clock period).
  RTC clock with f = 32 KHz is used for glitch filter.
   DebounceTime = (2 ^ PADCFG_DW2.DEBOUNCE)*(31.25 us).
  Supported DebounceTime values are following:
   DebounceTime = 0 -> Debounce feature disabled
   DebounceTime > 0 && < 250us -> Not supported
   DebounceTime = 250us - 1024000us -> Supported range (DebounceTime = 250us * 2^n)
  For values not supported by GPIO HW, function will round down
  to closest supported

  @param[in] GpioPad              GPIO pad
  @param[in, out] DebounceTime    Debounce Time in microseconds
                                  If Debounce Time = 0, Debouncer feature will be disabled
                                  Function will set DebounceTime argument to rounded supported value

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid GpioPad or unsupported DebounceDuration value
  @retval EFI_UNSUPPORTED         GpioPad is not owned by host
**/
EFI_STATUS
GpioSetDebounceTimer (
  IN GPIO_PAD                  GpioPad,
  IN OUT UINT32                *DebounceTime
  )
{
  UINT32   DebounceEnable;
  UINT32   DebounceValue;
  UINT32   InRangeDebounceTime;
  UINT32   SupportedDebounceTime;
  UINT32   Temp;
  BOOLEAN  SupportedValue;

  if (!GpioIsPadValid (GpioPad)) {
    return EFI_INVALID_PARAMETER;
  }

  if (!GpioIsPadHostOwned (GpioPad)) {
    return EFI_UNSUPPORTED;
  }

  if (*DebounceTime > 1024000) {
    InRangeDebounceTime = 1024000;
    SupportedValue = FALSE;
  } else if ((*DebounceTime < 250) && (*DebounceTime > 0)) {
    InRangeDebounceTime = 0;
    SupportedValue = FALSE;
  } else {
    InRangeDebounceTime = *DebounceTime;
    SupportedValue = TRUE;
  }

  //
  // DebounceValue = log2 (InRangeDebounceTime * f_deb_clk)
  //
  DebounceValue = 0;
  Temp = InRangeDebounceTime * 1000 / GPIO_DEB_CLK_PERIOD_IN_NS;

  //
  // Check if any rounding occurred
  //
  if (InRangeDebounceTime != (Temp * GPIO_DEB_CLK_PERIOD_IN_NS / 1000)) {
    SupportedValue = FALSE;
  }

  //
  // Check if value is power of 2
  //
  if ((Temp != 0) && ((Temp & (Temp - 1)) != 0)) {
    SupportedValue = FALSE;
  }

  //
  // DebounceValue = log2 (Temp)
  //
  while (Temp > 1) {
    Temp >>= 1;
    DebounceValue++;
  }

  if (DebounceValue > 0) {
    DebounceEnable = B_GPIO_PCR_DEBEN;
    SupportedDebounceTime = (1 << DebounceValue) * GPIO_DEB_CLK_PERIOD_IN_NS / 1000;
  } else {
    DebounceEnable = 0;
    SupportedDebounceTime = 0;
  }

  GpioWritePadCfgReg (
    GpioPad,
    2,
    (UINT32)~(B_GPIO_PCR_DEBOUNCE | B_GPIO_PCR_DEBEN),
    (DebounceValue << N_GPIO_PCR_DEBOUNCE) | DebounceEnable
    );

  if (!SupportedValue) {
    DEBUG ((DEBUG_WARN, "GPIO WARNING: %a %dus debounce time rounded down to %dus\n",
            GpioName (GpioPad),
            *DebounceTime,
            SupportedDebounceTime));
  }

  *DebounceTime = SupportedDebounceTime;

  return EFI_SUCCESS;
}
