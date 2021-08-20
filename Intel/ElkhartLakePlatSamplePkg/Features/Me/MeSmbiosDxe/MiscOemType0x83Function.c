/**@file
  Type 131: ME SMBIOS Structure.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include "MeSmbios.h"
#include "SetupVariable.h"
#include "OemSetup.h"
#include <Library/PciSegmentLib.h>
#include <Library/GbeLib.h>
#include <Register/Msr.h>
#include <Register/PchRegs.h>
#include <Register/PchRegsLpc.h>
#include <TrustedDeviceSetup.h>

/**
  This function makes boot time changes to the contents of the MiscOemType0x83Data.

  @param[in] RecordType          Type of record to be processed from the Data Table.
                                 mMiscSubclassDataTable[].RecordType
  @param[in] RecordLen           pointer to the size of static RecordData from the Data Table.
                                 mMiscSubclassDataTable[].RecordLen
  @param[in] RecordData          Pointer to copy of RecordData from the Data Table.  Changes made
                                 to this copy will be written to the Data Hub but will not alter
                                 the contents of the static Data Table.
  @param[in] LogRecordData       Set *LogRecordData to TRUE to log RecordData to Data Hub.
                                 Set *LogRecordData to FALSE when there is no more data to log.

  @retval EFI_SUCCESS            All parameters were valid and *RecordData and *LogRecordData have been set.
  @retval EFI_UNSUPPORTED        Unexpected RecordType value.
  @retval EFI_INVALID_PARAMETER  One of the following parameter conditions was true:
                                    RecordLen was NULL.
                                    RecordData was NULL.
                                    LogRecordData was NULL.
**/
MISC_SUBCLASS_TABLE_FUNCTION (MiscOemType0x83)
{
  EFI_STATUS                                Status;
  UINT64                                    Ia32FeatureControl;
  CPUID_VERSION_INFO_ECX                    Ecx;
  SETUP_CPU_FEATURES                        SetupCpuFeatures;
  UINT32                                    MeMode;
  SETUP_VOLATILE_DATA                       SetupVolatileData;
  UINTN                                     VariableSize = 0;
  MEBX_PROTOCOL                             *MebxProtocol;
  HECI_PROTOCOL                             *Heci;
  EFI_SMBIOS_PROTOCOL                       *Smbios;
  TRUSTED_DEVICE_SETUP_PROTOCOL             *TrustedDeviceSetupProtocol;

  ZeroMem (&SetupVolatileData, sizeof (SETUP_VOLATILE_DATA));

  Status = gBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, (VOID**)&Smbios);
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "Could not locate SMBIOS protocol.  %r\n", Status));
    return Status;
  }

  //
  // First check for invalid parameters.
  //
  if ((RecordLen == NULL) || (RecordData == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Then check for unsupported RecordType.
  //
  if (RecordType != MISC_OEM_TYPE_0x83_RECORD_NUMBER) {
    return EFI_UNSUPPORTED;
  }

  DEBUG ((DEBUG_INFO, "MiscOemType0x83 entry \n"));

  //
  // Locate HECI protocol to use it for ME info, HECI messaging
  // If HECI not found register callback for it to update data
  //
  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID**) &Heci
                  );
  if (!(EFI_ERROR (Status))) {
    ZeroMem (&((MISC_OEM_TYPE_0x83*)RecordData)->MeCapabilities, sizeof (ME_CAP));

    Heci->GetMeMode (&MeMode);
    if (MeMode == ME_MODE_NORMAL) {
      Status = MbpGetMeFwInfo (&((MISC_OEM_TYPE_0x83 *)RecordData)->MeCapabilities);
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }
  }

  Ia32FeatureControl = AsmReadMsr64(MSR_IA32_FEATURE_CONTROL);
  AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, &Ecx.Uint32, NULL);

  //
  // CPU
  //
  ((MISC_OEM_TYPE_0x83*)RecordData)->CpuCapabilities.VMXState = (UINT32)(RShiftU64(Ia32FeatureControl, 2));
  ((MISC_OEM_TYPE_0x83*)RecordData)->CpuCapabilities.SMXState = (UINT32)(RShiftU64(Ia32FeatureControl, 1));

  if (Ecx.Bits.SMX == 1) {
    ((MISC_OEM_TYPE_0x83*)RecordData)->CpuCapabilities.LtTxtCap = 1;
  } else {
    ((MISC_OEM_TYPE_0x83*)RecordData)->CpuCapabilities.LtTxtCap = 0;
  }

  if ((Ia32FeatureControl & TXT_OPT_IN_VMX_AND_SMX_MSR_VALUE) == TXT_OPT_IN_VMX_AND_SMX_MSR_VALUE) {
    ((MISC_OEM_TYPE_0x83*)RecordData)->CpuCapabilities.LtTxtEnabled = 1;
  } else {
    ((MISC_OEM_TYPE_0x83*)RecordData)->CpuCapabilities.LtTxtEnabled = 0;
  }

  if (Ecx.Bits.VMX == 1) {
    ((MISC_OEM_TYPE_0x83*)RecordData)->CpuCapabilities.VTxCap = 1;
  } else {
    ((MISC_OEM_TYPE_0x83*)RecordData)->CpuCapabilities.VTxCap = 0;
  }
  ((MISC_OEM_TYPE_0x83*)RecordData)->CpuCapabilities.VTxEnabled = (UINT32)(RShiftU64(Ia32FeatureControl, 2));

  //
  // MEBx Version
  //
  // Allocate RAM to put MEBx 16 bit real mode binary data at
  // based on size returned above.
  //
  // Locate MEBx protocol to get MEBx version information.
  //
  Status = gBS->LocateProtocol (&gMebxProtocolGuid, NULL, (VOID**) &MebxProtocol);
  if (!EFI_ERROR (Status)) {
    ((MISC_OEM_TYPE_0x83*)RecordData)->MebxVersion.Major  = MebxProtocol->MebxVersion.Major;
    ((MISC_OEM_TYPE_0x83*)RecordData)->MebxVersion.Minor  = MebxProtocol->MebxVersion.Minor;
    ((MISC_OEM_TYPE_0x83*)RecordData)->MebxVersion.Hotfix = MebxProtocol->MebxVersion.Hotfix;
    ((MISC_OEM_TYPE_0x83*)RecordData)->MebxVersion.Build  = MebxProtocol->MebxVersion.Build;
  }

  //
  // Pch
  //
  ((MISC_OEM_TYPE_0x83*)RecordData)->PchCapabilities.FunctionNumber = PCI_FUNCTION_NUMBER_PCH_LPC;
  ((MISC_OEM_TYPE_0x83*)RecordData)->PchCapabilities.DeviceNumber = PCI_DEVICE_NUMBER_PCH_LPC;
  ((MISC_OEM_TYPE_0x83*)RecordData)->PchCapabilities.BusNumber = DEFAULT_PCI_BUS_NUMBER_PCH;
  ((MISC_OEM_TYPE_0x83*)RecordData)->PchCapabilities.DeviceID = PciSegmentRead16 (
                                                                  PCI_SEGMENT_LIB_ADDRESS (
                                                                    DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                                                                    DEFAULT_PCI_BUS_NUMBER_PCH,
                                                                    PCI_DEVICE_NUMBER_PCH_LPC,
                                                                    PCI_FUNCTION_NUMBER_PCH_LPC,
                                                                    PCI_DEVICE_ID_OFFSET
                                                                    )
                                                                  );

  //
  // NetworkDevice
  //
  ((MISC_OEM_TYPE_0x83*)RecordData)->NetworkDevice.FunctionNumber = GbeFuncNumber (); //[2:0] PCI Device Function Number of Wired LAN
  ((MISC_OEM_TYPE_0x83*)RecordData)->NetworkDevice.DeviceNumber = GbeDevNumber ();     //[7:3] PCI Device Device Number of Wired LAN
  ((MISC_OEM_TYPE_0x83*)RecordData)->NetworkDevice.BusNumber = DEFAULT_PCI_BUS_NUMBER_PCH;       //[15:8] PCI Device Bus Number of Wired LAN
  ((MISC_OEM_TYPE_0x83*)RecordData)->NetworkDevice.DeviceID = PciSegmentRead16 (
                                                                PCI_SEGMENT_LIB_ADDRESS (
                                                                  DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                                                                  DEFAULT_PCI_BUS_NUMBER_PCH,
                                                                  GbeDevNumber (),
                                                                  GbeFuncNumber (),
                                                                  PCI_DEVICE_ID_OFFSET
                                                                  )
                                                                );

  //
  // BIOS
  //
  VariableSize = sizeof (SETUP_CPU_FEATURES);
  Status = gRT->GetVariable (
                  L"SetupCpuFeatures",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SetupCpuFeatures
                  );
  if (!EFI_ERROR (Status)) {
    if (SetupCpuFeatures.VTAvailable) {
      ((MISC_OEM_TYPE_0x83*)RecordData)->BiosCapabilities.VTxSupport = 1;
    }
    if (SetupCpuFeatures.TXTAvailable) {
      ((MISC_OEM_TYPE_0x83*)RecordData)->BiosCapabilities.TxtSupport = 1;
    }
  }

  ((MISC_OEM_TYPE_0x83*)RecordData)->BiosCapabilities.Reserved1 = 0;
  ((MISC_OEM_TYPE_0x83*)RecordData)->BiosCapabilities.Reserved2 = 0;

  Status = gBS->LocateProtocol(&gTrustedDeviceSetupMainProtocolGuid, NULL, (VOID **)&TrustedDeviceSetupProtocol);
  if (!EFI_ERROR (Status)) {
    TrustedDeviceSetupProtocol->SmbiosTrustedDeviceSetupCapabilities ((VOID *)&(((MISC_OEM_TYPE_0x83*)RecordData)->BiosCapabilities));
  }
  VariableSize = sizeof(SETUP_VOLATILE_DATA);
  Status = gRT->GetVariable (
                  L"SetupVolatileData",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SetupVolatileData
                  );
  if (!EFI_ERROR (Status)) {
    if (SetupVolatileData.VTdAvailable) {
      ((MISC_OEM_TYPE_0x83*)RecordData)->BiosCapabilities.VTdSupport = 1;  //Set to BIOS setup option display, not to feature enabled/disabled value
    } else {
      ((MISC_OEM_TYPE_0x83*)RecordData)->BiosCapabilities.VTdSupport = 0;  //Set to BIOS setup option display, not to feature enabled/disabled value
    }
  }

  DEBUG ((DEBUG_INFO, "MiscOemType0x83 exit \n"));
  return EFI_SUCCESS;
}

/* eof - MiscOemType0x83Function.c */
