/** @file
  CPU Platform Lib implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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
#include "CpuPlatformLibrary.h"
#include <Library/PciSegmentLib.h>
#include <SaCommonDefinitions.h>
#include <Library/CpuMailboxLib.h>

#define SKIP_MICROCODE_CHECKSUM_CHECK 1

/**
  Return CPU Family ID

  @retval CPU_FAMILY              CPU Family ID
**/
CPU_FAMILY
EFIAPI
GetCpuFamily (
  VOID
  )
{
  EFI_CPUID_REGISTER Cpuid;
  ///
  /// Read the CPUID information
  ///
  AsmCpuid (CPUID_VERSION_INFO, &Cpuid.RegEax, &Cpuid.RegEbx, &Cpuid.RegEcx, &Cpuid.RegEdx);
  return ((CPU_FAMILY) (Cpuid.RegEax & CPUID_FULL_FAMILY_MODEL));
}

/**
  Return Cpu stepping type

  @retval UINT8                   Cpu stepping type
**/
CPU_STEPPING
EFIAPI
GetCpuStepping (
  VOID
  )
{
  EFI_CPUID_REGISTER Cpuid;
  ///
  /// Read the CPUID information
  ///
  AsmCpuid (CPUID_VERSION_INFO, &Cpuid.RegEax, &Cpuid.RegEbx, &Cpuid.RegEcx, &Cpuid.RegEdx);
  return ((CPU_STEPPING) (Cpuid.RegEax & CPUID_FULL_STEPPING));
}

/**
  Return CPU Sku

  @retval UINT8              CPU Sku
**/
UINT8
EFIAPI
GetCpuSku (
  VOID
  )
{
  UINT8              CpuType;
  UINT16             CpuDid;
  UINT32             CpuFamilyModel;
  EFI_CPUID_REGISTER Cpuid;
  BOOLEAN            SkuFound;

  SkuFound  = TRUE;
  CpuType   = EnumCpuUnknown;

  ///
  /// Read the CPUID & DID information
  ///
  AsmCpuid (CPUID_VERSION_INFO, &Cpuid.RegEax, &Cpuid.RegEbx, &Cpuid.RegEcx, &Cpuid.RegEdx);
  CpuFamilyModel = Cpuid.RegEax & CPUID_FULL_FAMILY_MODEL;
  CpuDid = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_DEVICE_ID));

  switch (CpuFamilyModel) {
    case CPUID_FULL_FAMILY_MODEL_ICELAKE_ULT_ULX:
      switch (CpuDid) {
        case V_SA_DEVICE_ID_ICL_MB_ULT_1:    // ULT (4+2)
        case V_SA_DEVICE_ID_ICL_MB_ULT_2:    // ULT (4+3e)
        case V_SA_DEVICE_ID_ICL_MB_ULT_3:    // ULT (2+2)
          CpuType = EnumCpuUlt;
          break;

        case V_SA_DEVICE_ID_ICL_MB_ULX_1:    // ULX (4+2)
        case V_SA_DEVICE_ID_ICL_MB_ULX_2:    // ULX (2+2)
          CpuType = EnumCpuUlx;
          break;

        default:
          SkuFound = FALSE;
          break;
      }
      break;
    case CPUID_FULL_FAMILY_MODEL_ELKHARTLAKE:
      switch (CpuDid) {
        case V_SA_DEVICE_ID_EHL_0:
        case V_SA_DEVICE_ID_EHL_1:
        case V_SA_DEVICE_ID_EHL_2:
        case V_SA_DEVICE_ID_EHL_3:
        case V_SA_DEVICE_ID_EHL_4:
        case V_SA_DEVICE_ID_EHL_5:
        case V_SA_DEVICE_ID_EHL_6:
        case V_SA_DEVICE_ID_EHL_7:
        case V_SA_DEVICE_ID_EHL_8:
        case V_SA_DEVICE_ID_EHL_9:
        case V_SA_DEVICE_ID_EHL_10:
        case V_SA_DEVICE_ID_EHL_11:
        case V_SA_DEVICE_ID_EHL_12:
        case V_SA_DEVICE_ID_EHL_13:
        case V_SA_DEVICE_ID_EHL_14:
        case V_SA_DEVICE_ID_EHL_15:
        case V_SA_DEVICE_ID_EHL_16:
        case V_SA_DEVICE_ID_EHL_17:
        case V_SA_DEVICE_ID_EHL_18:
        case V_SA_DEVICE_ID_EHL_19:
        case V_SA_DEVICE_ID_EHL_20:
        case V_SA_DEVICE_ID_EHL_21:
        case V_SA_DEVICE_ID_EHL_22:
        case V_SA_DEVICE_ID_EHL_23:
          CpuType = EnumCpuUlx;
          break;
        default:
          SkuFound = FALSE;
          break;
      }
      break;
///
///
  }

  //
  // Simics doesn't simulate correct Device ID
  //
  if (IsSimicsEnvironment()) {
    SkuFound = TRUE;
    switch (CpuFamilyModel) {
      case CPUID_FULL_FAMILY_MODEL_ELKHARTLAKE:
        CpuType = EnumCpuUlx;
        DEBUG((DEBUG_WARN, "EHL Rev1 Simics DID W/A for Unsupported CPU SKU: treating as ULT, Device ID: 0x%02X, CPUID: 0x%08X!\n", CpuDid, CpuFamilyModel));
        break;
      case CPUID_FULL_FAMILY_MODEL_JASPERLAKE:
        CpuType = EnumCpuUlx;
        DEBUG((DEBUG_WARN, "JSL Rev2 Simics DID W/A for Unsupported CPU SKU: treating as ULT, Device ID: 0x%02X, CPUID: 0x%08X!\n", CpuDid, CpuFamilyModel));
        break;
    }
  }

  //
  // Simics doesn't simulate correct Device ID
  //
  if (IsSimicsEnvironment()) {
    SkuFound = TRUE;
    switch (CpuFamilyModel) {
      case CPUID_FULL_FAMILY_MODEL_TIGERLAKE_ULT_ULX:
        CpuType = EnumCpuUlt;
        DEBUG((DEBUG_WARN, "TGL Simics DID W/A for Unsupported CPU SKU: treating as ULT!\n"));
        break;
      case CPUID_FULL_FAMILY_MODEL_TIGERLAKE_DT_HALO:
        CpuType = EnumCpuHalo;
        DEBUG((DEBUG_WARN, "TGL Simics DID W/A for Unsupported CPU SKU: treating as HALO!\n"));
        break;
    }
    DEBUG((DEBUG_WARN, "TGL Simics DID W/A for Unsupported CPU SKU, Device ID: 0x%02X, CPUID: 0x%08X!\n", CpuDid, CpuFamilyModel));
  }
  if (!SkuFound) {
    DEBUG ((DEBUG_ERROR, "Unsupported CPU SKU, Device ID: 0x%02X, CPUID: 0x%08X!\n", CpuDid, CpuFamilyModel));
    ASSERT (FALSE);
  }

  return CpuType;
}

/**
  Return if Elixir is present or not
**/
BOOLEAN
IsElixirPresent (
  VOID
  )
{
  UINT32 MailboxCommand;
  UINT32 MailboxData;
  UINT32 MailboxStatus;
  EFI_STATUS Status;
  UINT8  VrId;
  UINT32 ElixirId = 0;
  UINT8 *VendorId;

  VendorId = (UINT8 *) AllocatePool (sizeof (UINT8));
  if (VendorId == NULL) {
    DEBUG ((DEBUG_ERROR, "Failed to allocate VendorId buffer...\n"));
    return FALSE;
  }
  *VendorId = 0;
  VrId = ElixirId ? SVID_REGISTER_VR_ID_VIRTUAL_1 : SVID_REGISTER_VR_ID_VIRTUAL_0;

  MailboxCommand = SVID_GET_REGISTER + (ELIXIR_VENDOR_ID_MAILBOX_ADDRESS << SVID_REGISTER_ADDR_OFFSET) + (VrId << SVID_REGISTER_VR_ID_OFFSET);
  Status = MailboxRead (MAILBOX_TYPE_PCODE, MailboxCommand, &MailboxData, &MailboxStatus);
  if (EFI_ERROR (Status) || EFI_ERROR (MailboxStatus)) {
    DEBUG ((DEBUG_ERROR, "Mailbox Command reading Elixir Springs Vendor ID failed. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
    return 0;
  }

  if (VendorId != NULL) {
    *VendorId = (UINT8) MailboxData;
  }
  if (*VendorId == ELIXIR_VENDOR_ID_INTEL){
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Return CPU Identifier used to identify various CPU types

  @retval CPU_OVERRIDE_IDENTIFIER           CPU Identifier
**/
CPU_OVERRIDE_IDENTIFIER
EFIAPI
GetCpuIdentifier (
  VOID
  )
{
  CPU_OVERRIDE_IDENTIFIER            CpuIdentifier;
  CPU_SKU                            CpuSku;
  UINT16                             PackageTdp;
  UINT16                             PackageTdpWatt;
  UINT16                             TempPackageTdp;
  MSR_REGISTER                       TempMsr;
  MSR_REGISTER                       PackagePowerSkuUnitMsr;
  UINT8                              ProcessorPowerUnit;
  CPU_STEPPING                       CpuStepping;
  UINT16                             CtdpTempRatio;
  UINT16                             ConfigTdpWatt;
  MSR_REGISTER                       CtdpMsr;
  UINT16                             CpuDid;
  CPU_FAMILY                         CpuFamily;

  CpuDid = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS(SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_DEVICE_ID));
  CpuFamily = GetCpuFamily();

  ///
  /// Initialize local variables
  ///
  CpuSku    = GetCpuSku();
  CpuStepping = GetCpuStepping();
  CpuIdentifier = EnumUnknownCpuId;

  ///
  /// Find Package TDP value in 1/100 Watt units
  ///
  TempMsr.Qword                 = AsmReadMsr64 (MSR_PACKAGE_POWER_SKU);
  PackagePowerSkuUnitMsr.Qword  = AsmReadMsr64 (MSR_PACKAGE_POWER_SKU_UNIT);
  CtdpMsr.Qword                 = AsmReadMsr64 (MSR_CONFIG_TDP_LEVEL2);

  ProcessorPowerUnit           = (PackagePowerSkuUnitMsr.Bytes.FirstByte & PACKAGE_POWER_UNIT_MASK);
  if (ProcessorPowerUnit == 0) {
    ProcessorPowerUnit = 1;
  } else {
    ProcessorPowerUnit = (UINT8) LShiftU64 (2, (ProcessorPowerUnit - 1));
    if (IsSimicsEnvironment() && ProcessorPowerUnit == 0) {
      ProcessorPowerUnit = 1;
    }
  }
  TempPackageTdp = (UINT16) (TempMsr.Dwords.Low & PACKAGE_TDP_POWER_MASK);
  PackageTdpWatt = (UINT16) DivU64x32 (TempPackageTdp, ProcessorPowerUnit);

  PackageTdp = (PackageTdpWatt * 100);
  if ((TempPackageTdp % ProcessorPowerUnit) !=0) {
    PackageTdp += ((TempPackageTdp % ProcessorPowerUnit) * 100) / ProcessorPowerUnit;
  }

  CtdpTempRatio = (UINT16) (CtdpMsr.Dwords.Low & PACKAGE_TDP_POWER_MASK);
  ConfigTdpWatt = (UINT16) DivU64x32 (CtdpTempRatio, ProcessorPowerUnit);

  ConfigTdpWatt = (ConfigTdpWatt * 100);

  DEBUG ((DEBUG_INFO, "GetCpuIdentifier() - CpuSku      = 0x%X\n", CpuSku));
  DEBUG ((DEBUG_INFO, "                   - PackageTdp  = %d\n", PackageTdp));
  DEBUG ((DEBUG_INFO, "                   - CpuStepping = %d\n", CpuStepping));

  ///
  /// Logic to determine the CPU Identifier
  ///
  switch(CpuSku) {
    case EnumCpuUlx:
      break;

    case EnumCpuUlt:
      if (CpuFamily == EnumCpuEhl) {
        if (CpuDid == CPU_DEVICE_ID_EHL_1){
            ///
            ///  EHL SKU 1
            ///
            DEBUG ((DEBUG_INFO, "CPU Identifier = Ehl Sku 1 10W\n"));
            CpuIdentifier = EnumEhl10Watt18fMblSku1CpuId;
        } else if (CpuDid == CPU_DEVICE_ID_EHL_2) {
            ///
            ///  EHL SKU 2
            ///
            DEBUG ((DEBUG_INFO, "CPU Identifier = Ehl Sku 2 10W\n"));
            CpuIdentifier = EnumEhl10Watt20fMblSku2CpuId;
        } else if (CpuDid == CPU_DEVICE_ID_EHL_3) {
              ///
              ///  EHL SKU 3
              ///
              DEBUG ((DEBUG_INFO, "CPU Identifier = Ehl Sku 3 6W\n"));
              CpuIdentifier = EnumEhl6Watt12fmblSku3CpuId;
        } else if (CpuDid == CPU_DEVICE_ID_EHL_4) {
            ///
            ///  EHL SKU 4
            ///
            DEBUG ((DEBUG_INFO, "CPU Identifier = Ehl Sku 4 6W\n"));
            CpuIdentifier = EnumEhl6Watt12fmblSku4CpuId;
        } else if (CpuDid == CPU_DEVICE_ID_EHL_5) {
              ///
              ///  EHL SKU 5
              ///
              DEBUG ((DEBUG_INFO, "CPU Identifier = Ehl Sku 5 6W\n"));
              CpuIdentifier = EnumEhl6Watt15fDtSku5CpuId;
        } else if (CpuDid == CPU_DEVICE_ID_EHL_6) {
              ///
              ///  EHL SKU 6
              ///
              DEBUG ((DEBUG_INFO, "CPU Identifier = Ehl Sku 6 9W\n"));
              CpuIdentifier = EnumEhl9Watt17fDtSku6CpuId;
        } else if (CpuDid == CPU_DEVICE_ID_EHL_7) {
            ///
            ///  EHL SKU 7
            ///
            DEBUG ((DEBUG_INFO, "CPU Identifier = Ehl Sku 7 12W\n"));
            CpuIdentifier = EnumEhl12Watt18fDtSku7CpuId;
        } else if (CpuDid == CPU_DEVICE_ID_EHL_8) {
              ///
              ///  EHL SKU 8
              ///
              DEBUG ((DEBUG_INFO, "CPU Identifier = Ehl Sku 8 6W\n"));
              CpuIdentifier = EnumEhl6Watt15fInduSku8CpuId;
        } else if (CpuDid == CPU_DEVICE_ID_EHL_9) {
              ///
              ///  EHL SKU 9
              ///
              DEBUG ((DEBUG_INFO, "CPU Identifier = Ehl Sku 9 9W\n"));
              CpuIdentifier = EnumEhl9Watt17fInduSku9CpuId;
        } else if (CpuDid == CPU_DEVICE_ID_EHL_10) {
            ///
            ///  EHL SKU 10
            ///
            DEBUG ((DEBUG_INFO, "CPU Identifier = Ehl Sku 10 12W\n"));
            CpuIdentifier = EnumEhl12Watt19fInduSku10CpuId;
        } else if (CpuDid == CPU_DEVICE_ID_EHL_11) {
              ///
              ///  EHL SKU 11
              ///
              DEBUG ((DEBUG_INFO, "CPU Identifier = Ehl Sku 11 12W\n"));
              CpuIdentifier = EnumEhl12Watt19fInduSku11CpuId;
        } else if (CpuDid == CPU_DEVICE_ID_EHL_12) {
            ///
            ///  EHL SKU 12
            ///
            DEBUG ((DEBUG_INFO, "CPU Identifier = Ehl Sku 12 4.25W\n"));
            CpuIdentifier = EnumEhl4Watt10fInduSku12CpuId;
        }
      }
      break;

    case EnumCpuHalo:
      break;

    case EnumCpuTrad:
      break;

    default:
      CpuIdentifier = EnumUnknownCpuId;
      break;
    }

  return CpuIdentifier;
}

/**
  Returns the processor microcode revision of the processor installed in the system.

  @retval Processor Microcode Revision
**/
UINT32
GetCpuUcodeRevision (
  VOID
  )
{
  AsmWriteMsr64 (MSR_IA32_BIOS_SIGN_ID, 0);
  AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, NULL, NULL);
  return (UINT32) RShiftU64 (AsmReadMsr64 (MSR_IA32_BIOS_SIGN_ID), 32);
}

/**
  This function checks the MCU revision to decide if BIOS needs to load
  microcode.

  @param[in] MicrocodePointer - Microcode in memory
  @param[in] Revision         - Current CPU microcode revision

  @retval EFI_SUCCESS - BIOS needs to load microcode
  @retval EFI_ABORTED - Don't need to update microcode
**/
EFI_STATUS
CheckMcuRevision (
  IN CPU_MICROCODE_HEADER *MicrocodePointer,
  IN UINT32               Revision
  )
{
  EFI_STATUS Status;
  Status = EFI_ABORTED;

  if ((MicrocodePointer->UpdateRevision & 0x80000000) ||
      (MicrocodePointer->UpdateRevision >= Revision) ||
      (Revision == 0)) {
    Status = EFI_SUCCESS;
  }

  return Status;
}

/**
  Check if this microcode is correct one for processor

  @param[in] Cpuid               - processor CPUID
  @param[in] MicrocodeEntryPoint - entry point of microcode
  @param[in] Revision            - revision of microcode

  @retval CorrectMicrocode if this microcode is correct
**/
BOOLEAN
CheckMicrocode (
  IN UINT32               Cpuid,
  IN CPU_MICROCODE_HEADER *MicrocodeEntryPoint,
  IN UINT32               *Revision
  )
{
  UINT32                              CheckSum32;
  UINT8                               ExtendedIndex;
  MSR_IA32_PLATFORM_ID_REGISTER       Msr;
  UINT32                              ExtendedTableLength;
  UINT32                              ExtendedTableCount;
  BOOLEAN                             CorrectMicrocode;
  CPU_MICROCODE_EXTENDED_TABLE        *ExtendedTable;
  CPU_MICROCODE_EXTENDED_TABLE_HEADER *ExtendedTableHeader;

  CheckSum32          = 0;
  ExtendedTableLength = 0;
  CorrectMicrocode    = FALSE;

  if (MicrocodeEntryPoint == NULL) {
    return FALSE;
  }

  Msr.Uint64 = AsmReadMsr64 (MSR_IA32_PLATFORM_ID);

  ///
  /// Check if the microcode is for the Cpu and the version is newer
  /// and the update can be processed on the platform
  ///
  if ((MicrocodeEntryPoint->HeaderVersion == 0x00000001) &&
      !EFI_ERROR (CheckMcuRevision (MicrocodeEntryPoint, *Revision))
      ) {
    if ((MicrocodeEntryPoint->ProcessorId == Cpuid) && (MicrocodeEntryPoint->ProcessorFlags & (1 << (UINT8) Msr.Bits.PlatformId))) {
    #if SKIP_MICROCODE_CHECKSUM_CHECK
      CheckSum32 = 0;
    #else
      if (MicrocodeEntryPoint->DataSize == 0) {
        CheckSum32 = CalculateSum32 ((UINT32 *) MicrocodeEntryPoint, 2048);
      } else {
        CheckSum32 = CalculateSum32 (
                   (UINT32 *) MicrocodeEntryPoint,
                   MicrocodeEntryPoint->DataSize + sizeof (CPU_MICROCODE_HEADER)
                   );
      }
    #endif
      if (CheckSum32 == 0) {
        CorrectMicrocode = TRUE;
      }
    } else if ((MicrocodeEntryPoint->DataSize != 0)) {
      ///
      /// Check the  Extended Signature if the entended signature exist
      /// Only the data size != 0 the extended signature may exist
      ///
      ExtendedTableLength = MicrocodeEntryPoint->TotalSize - (MicrocodeEntryPoint->DataSize + sizeof (CPU_MICROCODE_HEADER));
      if (ExtendedTableLength != 0) {
        ///
        /// Extended Table exist, check if the CPU in support list
        ///
        ExtendedTableHeader = (CPU_MICROCODE_EXTENDED_TABLE_HEADER *) ((UINT8 *) (MicrocodeEntryPoint) + MicrocodeEntryPoint->DataSize + 48);
        ///
        /// Calulate Extended Checksum
        ///
        if ((ExtendedTableLength % 4) == 0) {
          #if SKIP_MICROCODE_CHECKSUM_CHECK
            CheckSum32 = 0;
          #else
            CheckSum32 = CalculateSum32 ((UINT32 *) ExtendedTableHeader, ExtendedTableLength);
          #endif
          if (CheckSum32 == 0) {
            ///
            /// Checksum correct
            ///
            ExtendedTableCount  = ExtendedTableHeader->ExtendedSignatureCount;
            ExtendedTable       = (CPU_MICROCODE_EXTENDED_TABLE *) (ExtendedTableHeader + 1);
            for (ExtendedIndex = 0; ExtendedIndex < ExtendedTableCount; ExtendedIndex++) {
              ///
              /// Verify Header
              ///
              if ((ExtendedTable->ProcessorSignature == Cpuid) && (ExtendedTable->ProcessorFlag & (1 << (UINT8) Msr.Bits.PlatformId))) {
                #if SKIP_MICROCODE_CHECKSUM_CHECK
                  CheckSum32 = 0;
                #else
                  CheckSum32 = CalculateSum32 (
                             (UINT32 *) ExtendedTable,
                             sizeof (CPU_MICROCODE_EXTENDED_TABLE)
                             );
                #endif
                if (CheckSum32 == 0) {
                  ///
                  /// Find one
                  ///
                  CorrectMicrocode = TRUE;
                  break;
                }
              }

              ExtendedTable++;
            }
          }
        }
      }
    }
  }

  return CorrectMicrocode;
}

/**
  This function is to program Trace Hub ACPI base address to processor's MSR TRACE_HUB_STH_ACPIBAR_BASE.

  @param[in]  TraceHubAcpiBase - Base address of Trace Hub ACPI Base address
**/
VOID
EFIAPI
CpuWriteTraceHubAcpiBase (
  IN UINT64  TraceHubAcpiBase
  )
{
  //
  // Check the pass in Trace Hub ACPI base if 256KB alignment.
  //
  if ((TraceHubAcpiBase & ~(UINT64) B_MSR_NPK_STH_ACPIBAR_BASE_ADDRESS_MASK) != 0) {
    ASSERT ((TraceHubAcpiBase & ~(UINT64) B_MSR_NPK_STH_ACPIBAR_BASE_ADDRESS_MASK) == 0);
    return;
  }

  ///
  /// Set MSR TRACE_HUB_STH_ACPIBAR_BASE[0] LOCK bit for the AET packets to be directed to NPK MMIO.
  ///
  AsmWriteMsr64 (MSR_NPK_STH_ACPIBAR_BASE, TraceHubAcpiBase | B_MSR_NPK_STH_ACPIBAR_BASE_LOCK_MASK);

  return;
}

/**
  Check on the processor if SGX is supported.

  @dot
    digraph G {
      subgraph cluster_c0 {
        node [shape = box];
          b1[label="Read CPUID(EAX=7,ECX=0):EBX[2] \nto check SGX feature" fontsize=12 style=filled color=lightblue];
          b2[label="Return TRUE" fontsize=12 style=filled color=lightblue];
          b3[label="Return FALSE" fontsize=12 style=filled color=lightblue];

        node [shape = ellipse];
          e1[label="Start" fontsize=12 style=filled color=lightblue];
          e2[label="End" fontsize=12 style=filled color=lightblue];

        node [shape = diamond,style=filled,color=lightblue];
          d1[label="Are SGX feature supported and \nPRMRR configuration enabled" fontsize=12];

        label = "IsSgxSupported Flow"; fontsize=15; fontcolor=black; color=lightblue;
        e1 -> b1
        b1 -> d1
        d1 -> b2 [label="Yes" fontsize=9]
        d1 -> b3 [label="No" fontsize=9]
        b2 -> e2
        b3 -> e2

      }
    }
  @enddot

  @retval TRUE  if SGX supported
  @retval FALSE if SGX is not supported
**/
BOOLEAN
IsSgxSupported (
  VOID
  )
{
  EFI_CPUID_REGISTER CpuidRegs;

  //
  // Processor support SGX feature by reading CPUID.(EAX=7,ECX=0):EBX[2]
  //
  AsmCpuidEx (CPUID_STRUCTURED_EXTENDED_FEATURE_FLAGS, 0, &CpuidRegs.RegEax,&CpuidRegs.RegEbx,&CpuidRegs.RegEcx,&CpuidRegs.RegEdx);

  ///
  /// SGX feature is supported only with CPUID.(EAX=7,ECX=0):EBX[2]=1
  /// PRMRR configuration enabled, MSR IA32_MTRRCAP (FEh) [12] == 1
  ///
  if (((CpuidRegs.RegEbx & BIT2)) && (AsmReadMsr64 (MSR_IA32_MTRRCAP) & BIT12)) {
    return TRUE;
  }
  return FALSE;
}

/**
  Detect if this is EHL CPU or not

  @param[in]  None

  @retval TRUE - EHL CPU
  @retval FALSE - Not a EHL CPU
**/
BOOLEAN
IsEHLCpu (
   IN VOID
  )
{

  EFI_CPUID_REGISTER Cpuid;
  CPU_FAMILY         CpuFamilyModel;

  ///
  /// Read the CPUID information
  ///
  AsmCpuid (CPUID_VERSION_INFO, &Cpuid.RegEax, &Cpuid.RegEbx, &Cpuid.RegEcx, &Cpuid.RegEdx);
  CpuFamilyModel = (CPU_FAMILY) (Cpuid.RegEax & CPUID_FULL_FAMILY_MODEL);
  return (CpuFamilyModel == EnumCpuEhl) ? TRUE: FALSE;
}


/**
  Get processor generation

  @retval CPU_GENERATION  Returns the executing thread's processor generation.
**/
CPU_GENERATION
GetCpuGeneration (
  VOID
  )
{
  EFI_CPUID_REGISTER Cpuid;
  CPU_FAMILY         CpuFamilyModel;
  CPU_GENERATION     CpuGeneration;

  ///
  /// Read the CPUID information
  ///
  AsmCpuid (CPUID_VERSION_INFO, &Cpuid.RegEax, &Cpuid.RegEbx, &Cpuid.RegEcx, &Cpuid.RegEdx);
  CpuFamilyModel = (CPU_FAMILY) (Cpuid.RegEax & CPUID_FULL_FAMILY_MODEL);

  switch (CpuFamilyModel) {
    case EnumCpuCflUltUlx:
      CpuGeneration = EnumCflCpu;
      break;
    case EnumCpuIclUltUlx:
    case EnumCpuIclDtHalo:
      CpuGeneration = EnumIclCpu;
      break;
    case EnumCpuJsl:
      CpuGeneration = EnumJslCpu;
      break;
    case EnumCpuEhl:
      CpuGeneration = EnumEhlCpu;
      break;
    case EnumCpuTglUltUlx:
    case EnumCpuTglDtHalo:
      CpuGeneration = EnumTglCpu;
      break;
///
///
    default:
      CpuGeneration = EnumCpuUnknownGeneration;
      ASSERT (FALSE);
      break;
  }

  return CpuGeneration;
}

/**
  Check if this is non-core processor - HT AP thread

  @retval TRUE if this is HT AP thread
  @retval FALSE if this is core thread
**/
BOOLEAN
IsSecondaryThread (
  VOID
  )
{
  CPUID_VERSION_INFO_EDX      CpuidVersionInfoEdx;
  CPUID_EXTENDED_TOPOLOGY_EAX CpuIdExtendedTopologyEax;
  UINT32                      ApicId;
  UINT32                      MaskShift;
  UINT32                      Mask;

  AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, NULL, &CpuidVersionInfoEdx.Uint32);
  if (CpuidVersionInfoEdx.Bits.HTT == 0) {
    return FALSE;
  }

  AsmCpuidEx (
    CPUID_EXTENDED_TOPOLOGY,
    0,  // Sub-leaf 0
    &CpuIdExtendedTopologyEax.Uint32,
    NULL,
    NULL,
    &ApicId
    );

  MaskShift = CpuIdExtendedTopologyEax.Bits.ApicIdShift;
  Mask = ~(0xffffffff << MaskShift);

  return (ApicId & Mask) > 0;
}

/**
  This function returns Number of enabled cores in the package.

  @retval Number of enabled cores in the package.
**/

UINT16
GetEnabledCoreCount (
  VOID
  )
{
  UINT64 MsrValue;

  MsrValue = AsmReadMsr64 (MSR_CORE_THREAD_COUNT);

  return (UINT16) ((UINT32)MsrValue >> N_MSR_CORE_THREAD_COUNT_CORECOUNT_OFFSET);
}

/**
  This function returns Number of enabled Threads in the package.

  @retval Number of enabled threads in the package.
**/
UINT16
GetEnabledThreadCount (
  VOID
  )
{
  UINT64 MsrValue;

  MsrValue = AsmReadMsr64 (MSR_CORE_THREAD_COUNT);

  return (UINT16) ((UINT32)MsrValue >> N_MSR_CORE_THREAD_COUNT_THREADCOUNT_OFFSET);
}

/**
  This function checks for Whiskey Lake CPU presence.

  @retval TRUE  - WHL CPU Stepping W0 or V0 detected
  @retval FALSE - no WHL CPU detected
**/
BOOLEAN
IsWhlCpu (
  VOID
  )
{
  CPU_FAMILY   CpuFamily;
  CpuFamily   = GetCpuFamily ();

  switch (CpuFamily) {
    default:
      return FALSE;
  }
}

/**
  This function checks whether uCode loaded from FIT.

  @retval TRUE  - uCode loaded from FIT successful
  @retval FALSE - Failed on FIT to load uCode
**/
BOOLEAN
IsValiduCodeEntry (
  VOID
  )
{
  MSR_REGISTER TempMsr;
  UINT8        FitEntryType;
  UINT8        FitErrorCode;

  TempMsr.Qword = AsmReadMsr64 (MSR_FIT_BIOS_ERROR);
  FitEntryType = (UINT8) ((TempMsr.Dwords.Low & B_MSR_FIT_BIOS_ERROR_ENTRY_TYPE_MASK) >> N_MSR_FIT_BIOS_ERROR_ENTRY_TYPE_OFFSET);
  FitErrorCode = (UINT8) (TempMsr.Dwords.Low & B_MSR_FIT_BIOS_ERROR_ERROR_CODE_MASK);

  if (FitErrorCode != FIT_SUCCESSFUL) {
    switch (FitEntryType) {
      case FIT_HEADER_ENTRY:
        DEBUG ((DEBUG_ERROR, "uCode Load status: Unexpected Fit header incorrect\n"));
        break;
      case FIT_MICROCODE_UPDATE_ENTRY:
        DEBUG ((DEBUG_ERROR, "uCode Load status: Unexpected microcode update error\n"));
        break;
      case FIT_STARTUP_ACM_ENTRY:
        DEBUG ((DEBUG_ERROR, "uCode Load status: Unexpected startup ACM error\n"));
        break;
      case FIT_GENERAL_CHECKS:
        DEBUG ((DEBUG_ERROR, "uCode Load status: general checks error\n"));
        break;
      default:
        DEBUG ((DEBUG_ERROR, "uCode Load status: Unknown error\n"));
        break;
    }
    return FALSE;
  } else {
     TempMsr.Qword = AsmReadMsr64 (MSR_BIOS_SIGN_ID);
     DEBUG ((DEBUG_INFO, "Valid FIT uCode Found: 0x%08X\n", (UINT32) (TempMsr.Dwords.High)));
     return TRUE;  // FIT_SUCCESSFUL
  }
}

/**
  Is BIOS GUARD enabled.

  @retval TRUE   BIOS GUARD is supported and enabled.
  @retval FALSE  BIOS GUARD is disabled.
**/
BOOLEAN
IsBiosGuardEnabled (
  VOID
  )
{
#if FixedPcdGetBool(PcdBiosGuardEnable) == 1
  if (AsmReadMsr64 (MSR_PLATFORM_INFO) & B_MSR_PLATFORM_INFO_PFAT_ENABLE_MASK) {
    if (AsmReadMsr64 (MSR_PLAT_FRMW_PROT_CTRL) & B_MSR_PLAT_FRMW_PROT_CTRL_PFAT_ENABLE_MASK) {
      return TRUE;
    }
  }
#endif
  return FALSE;
}

/**
 *Detect if FuSa is supported by reading Device ID

  @retval TRUE - Supported
  @retval FALSE - Not Supported
**/
BOOLEAN
IsFusaSupported (
  VOID
  )
{
  UINT16             DeviceId;
  BOOLEAN            FusaSupport;

  FusaSupport = FALSE;

  ///
  /// Read the DID information
  ///
  DeviceId = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_DEVICE_ID));

  if (DeviceId == V_SA_DEVICE_ID_EHL_18) {
    FusaSupport = TRUE;
  }

  return FusaSupport;
}
