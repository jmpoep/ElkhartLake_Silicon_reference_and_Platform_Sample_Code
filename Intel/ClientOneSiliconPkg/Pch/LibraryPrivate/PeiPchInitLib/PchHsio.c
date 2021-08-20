/** @file
  PCH HSIO Initialization file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

#include <Library/PeiMeLib.h>
#include <BupMsgs.h>
#include "PchInitPei.h"
#include <Library/PeiServicesTablePointerLib.h>
#include <PchHsio.h>
#include <ChipsetInfoHob.h>
#include <Library/ConfigBlockLib.h>
#include <SaPolicyCommon.h>
#include <CpuPciePeiPreMemConfig.h>
#include <Library/DciPrivateLib.h>
#include <Library/PeiHsioLib.h>
#include <Register/PchRegsHsio.h>
#include <MeBiosPayloadHob.h>

GLOBAL_REMOVE_IF_UNREFERENCED const UINT16  mHsioCrc16Table[256] = {
  0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
  0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
  0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
  0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
  0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
  0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
  0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
  0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
  0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
  0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
  0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
  0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
  0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
  0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
  0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
  0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
  0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
  0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
  0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
  0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
  0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
  0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
  0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
  0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
  0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
  0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
  0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
  0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
  0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
  0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
  0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
  0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

/**
  Calculate CRC16 for target data.

  @param[in]  Data              The target data.
  @param[in]  DataSize          The target data size.

  @return UINT16                The CRC16 value.
**/
STATIC
UINT16
PchHsioCalculateCrc16 (
  IN  UINT8   *Data,
  IN  UINTN   DataSize
  )
{
  UINTN   Index;
  UINT8   *Ptr;
  UINT16  Crc;

  Crc = 0;
  for (Index = 0, Ptr = Data; Index < DataSize; Index++, Ptr++) {
    Crc = (Crc >> 8) ^ (mHsioCrc16Table[((UINT8) Crc ^ *Ptr) & 0xFF]);
  }
  return Crc;
}

VOID
PchHsioEnablePcieComplianceMode (
  VOID
  )
{
  UINT32     MaxPcieLanes;
  UINT32     PcieIndex;
  UINT8      HsioLaneNo;
  HSIO_LANE  HsioLane;

  MaxPcieLanes = GetPchMaxPciePortNum ();
  for (PcieIndex = 0; PcieIndex < MaxPcieLanes; ++PcieIndex) {
    if (PchFiaGetPcieLaneNum (PcieIndex, &HsioLaneNo)) {
      DEBUG ((DEBUG_INFO, "PCIe compliance mode for PCIe%d, HSIO%d\n", PcieIndex + 1, HsioLaneNo));
      HsioGetLane (HsioLaneNo, &HsioLane);
      HsioLaneAndThenOr32WithSusWrite (&HsioLane, R_HSIO_PCR_PCS_DWORD4, (UINT32) ~BIT23, 0);
    }
  }
}

/**
  The function programs the Pcie Pll SSC registers.

  @param[in]  SiPolicyPpi        The SI Policy PPI instance
**/
VOID
PchPciePllSscProg (
  IN  SI_POLICY_PPI      *SiPolicyPpi
  )
{
  UINT8                       PciePllSsc;
  EFI_STATUS                  Status;
  PCH_PM_CONFIG               *PmConfig;
  UINT8                       PciePllSscTable[21];

  PciePllSscTable[0] = 0x0;  // 0%
  PciePllSscTable[1] = 0x6;  // 0.1%
  PciePllSscTable[2] = 0xD;  // 0.2%
  PciePllSscTable[3] = 0x14; // 0.3%
  PciePllSscTable[4] = 0x1A; // 0.4%
  PciePllSscTable[5] = 0x21; // 0.5%
  PciePllSscTable[6] = 0x28; // 0.6%
  PciePllSscTable[7] = 0x2E; // 0.7%
  PciePllSscTable[8] = 0x35; // 0.8%
  PciePllSscTable[9] = 0x3C; // 0.9%
  PciePllSscTable[10] = 0x42; // 1.0%
  PciePllSscTable[11] = 0x49; // 1.1%
  PciePllSscTable[12] = 0x50; // 1.2%
  PciePllSscTable[13] = 0x56; // 1.3%
  PciePllSscTable[14] = 0x5D; // 1.4%
  PciePllSscTable[15] = 0x64; // 1.5%
  PciePllSscTable[16] = 0x6A; // 1.6%
  PciePllSscTable[17] = 0x71; // 1.7%
  PciePllSscTable[18] = 0x78; // 1.8%
  PciePllSscTable[19] = 0x7E; // 1.9%
  PciePllSscTable[20] = 0x85; // 2.0%

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);

  if (PmConfig->PciePllSsc == PCIE_PLL_SSC_AUTO) {
    return;
  }

  PciePllSsc = PmConfig->PciePllSsc;
  if (PciePllSsc > MAX_PCIE_PLL_SSC_PERCENT) {
    PciePllSsc = MAX_PCIE_PLL_SSC_PERCENT;
  }

  ///
  /// Step 1:  Clear i_sscen_h to 0b
  ///
  PchPcrAndThenOr32WithSusWrite (
    PID_MODPHY0,
    R_HSIO_PCR_PLL_SSC_DWORD2,
    (UINT32) ~B_HSIO_PCR_PLL_SSC_DWORD2_SSCSEN,
    0
    );

  ///
  /// Step 2:  Write the desired Down Spread % bit values in i_sscstepsize_7_0
  ///
  PchPcrAndThenOr32WithSusWrite (
    PID_MODPHY0,
    R_HSIO_PCR_PLL_SSC_DWORD2,
    (UINT32) ~B_HSIO_PCR_PLL_SSC_DWORD2_SSCSTEPSIZE_7_0,
    (UINT32) (PciePllSscTable[PciePllSsc] << N_HSIO_PCR_PLL_SSC_DWORD2_SSCSTEPSIZE_7_0)
    );

  ///
  /// Step 3:  Set i_ssc_propagate_h to 1b in the LCPLL_CFG1 register
  ///
  PchPcrAndThenOr32WithSusWrite (
    PID_MODPHY0,
    R_HSIO_PCR_PLL_SSC_DWORD3,
    (UINT32) ~B_HSIO_PCR_PLL_SSC_DWORD3_SSC_PROPAGATE,
    (UINT32) B_HSIO_PCR_PLL_SSC_DWORD3_SSC_PROPAGATE
    );

  ///
  /// Step 4:  Set i_sscen_h to 1b
  ///
  PchPcrAndThenOr32WithSusWrite (
    PID_MODPHY0,
    R_HSIO_PCR_PLL_SSC_DWORD2,
    (UINT32) ~B_HSIO_PCR_PLL_SSC_DWORD2_SSCSEN,
    (UINT32) B_HSIO_PCR_PLL_SSC_DWORD2_SSCSEN
    );

  DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, PciePllSsc = 0x%08x\n", PID_MODPHY0, R_HSIO_PCR_PLL_SSC_DWORD2, PchPcrRead32 (PID_MODPHY0, R_HSIO_PCR_PLL_SSC_DWORD2)));
}

/**
  The function programs the Pcie Pll PwrGating registers.
**/
VOID
PchHsioPllPwrGatingProg (
  VOID
  )
{
  ///
  /// Set o_cfg_pwr_gating_ctrl to 1b
  ///
  PchPcrAndThenOr32WithSusWrite (
    PID_MODPHY1,
    R_HSIO_PCR_PLL_DWORD12,
    (UINT32) ~B_HSIO_PCR_PLL_DWORD12_O_CFG_PWR_GATING_CTRL,
    (UINT32) B_HSIO_PCR_PLL_DWORD12_O_CFG_PWR_GATING_CTRL
    );

  ///
  /// Set DWORD15_O_CFG_CMN_DYNCLKGATE_MODE to 11b
  ///
  PchPcrAndThenOr32WithSusWrite (
    PID_MODPHY1,
    R_HSIO_PCR_PLL_DWORD15,
    (UINT32) ~B_HSIO_PCR_PLL_DWORD15_O_CFG_CMN_DYNCLKGATE_MODE_1_0,
    (UINT32) B_HSIO_PCR_PLL_DWORD15_O_CFG_CMN_DYNCLKGATE_MODE_1_0
    );
}

/**
  The function program HSIO registers.

  @param[in] SiPolicyPpi               The SI Policy PPI instance

**/
VOID
PchHsioMiscBiosProg (
  IN  SI_POLICY_PPI    *SiPolicyPpi
  )
{
  EFI_STATUS                            Status;
  PCH_PCIE_CONFIG                       *PcieRpConfig;
  DEBUG ((DEBUG_INFO, "PchHsioMiscBiosProg() Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gPchPcieRpConfigGuid, (VOID *) &PcieRpConfig);
  ASSERT_EFI_ERROR (Status);

  if (PcieRpConfig->ComplianceTestMode) {
    PchHsioEnablePcieComplianceMode ();
  }
  PchPciePllSscProg (SiPolicyPpi);
  PchHsioPllPwrGatingProg ();

  DEBUG ((DEBUG_INFO, "PchHsioMiscBiosProg() End\n"));
}

/**
  Prints Chipset Init Table Version Info.

  @param[in] ChipsetInitVerInfo    Chipset Init Table Version Info
**/
STATIC
VOID
PrintChipsetInitTableVersionInfo (
  IN PCH_HSIO_VER_INFO *ChipsetInitVerInfo
  )
{
  DEBUG_CODE_BEGIN ();

  DEBUG ((DEBUG_INFO, "//Version Information\n"));
  DEBUG ((DEBUG_INFO, "//Current Base CRC: 0x%x\n", ChipsetInitVerInfo->BaseCrc));
  DEBUG ((DEBUG_INFO, "//Current SUS CRC: 0x%x\n", ChipsetInitVerInfo->SusCrc));
  DEBUG ((DEBUG_INFO, "//Current OEM CRC: 0x%x\n", ChipsetInitVerInfo->OemCrc));
  DEBUG ((DEBUG_INFO, "//Version: 0x%x\n", ChipsetInitVerInfo->Version));
  DEBUG ((DEBUG_INFO, "//Product: 0x%x\n", ChipsetInitVerInfo->Product));
  DEBUG ((DEBUG_INFO, "//Base Layer: 0x%x\n", ChipsetInitVerInfo->BaseLayer));
  DEBUG ((DEBUG_INFO, "//Metal Layer: 0x%x\n", ChipsetInitVerInfo->MetalLayer));
  DEBUG ((DEBUG_INFO, "//OEM Version: %x\n", ChipsetInitVerInfo->OemVersion));
  DEBUG ((DEBUG_INFO, "//Debug Mode: %x\n", ChipsetInitVerInfo->DebugMode));
  DEBUG ((DEBUG_INFO, "//OEM CRC Valid: %x\n", ChipsetInitVerInfo->OemCrcValid));
  DEBUG ((DEBUG_INFO, "//SUS CRC Valid: %x\n", ChipsetInitVerInfo->SusCrcValid));
  DEBUG ((DEBUG_INFO, "//Base CRC Valid: %x\n", ChipsetInitVerInfo->BaseCrcValid));

  DEBUG_CODE_END ();
}

/**
  Prints Chipset Init Table Headers.

  @param[in] ChipsetInitHeaderStart   Pointer to the beginning of Header section
**/
STATIC
VOID
PrintChipsetInitTableHeader (
  IN UINT8 *ChipsetInitHeaderStart
  )
{
  DEBUG_CODE_BEGIN ();

  UINT8              Field;
  PCH_HSIO_HDR_FIELD *ChipsetInitHeader;

  ChipsetInitHeader = (PCH_HSIO_HDR_FIELD *)ChipsetInitHeaderStart;
  DEBUG ((DEBUG_INFO, "// Phy Data Group Table (Fixed table with 16 Entries)\n"));

  for (Field = 0; Field < PCH_HSIO_HDR_FIELD_NUM; Field++) {
    DEBUG ((DEBUG_INFO, "//Id: 0x%x, RecordOffset: 0x%x\n",
    ChipsetInitHeader->Id, RECORD_OFFSET (ChipsetInitHeader->RecordOffsetHigh, ChipsetInitHeader->RecordOffsetLow)));
    ChipsetInitHeader++;
  }

  DEBUG_CODE_END ();
}

/**
  Prints Chipset Init Table Payload.

  @param[in] ChipsetInitTableData   Pointer to the beginning of Header section
  @param[in] DataSize               Size of the data to print. Caller must make sure
                                    that the printed data comes from the allocated buffer
**/
STATIC
VOID
PrintChipsetInitTableData (
  IN UINT8  *ChipsetInitTableData,
  IN UINT32 DataSize
  )
{
  DEBUG_CODE_BEGIN ();

  PCH_HSIO_CMD_FIELD *ChipsetInitTableCmdField;
  PCH_HSIO_DATA_CMD  *ChipsetInitTableDataCmd;
  PCH_HSIO_DELAY_CMD *ChipsetInitTableDelayCmd;
  UINT8              *ChipsetInitTableTableEnd;
  UINT8              Field;
  UINT32             EntrySize;

  ChipsetInitTableTableEnd = ChipsetInitTableData + DataSize;

  while (ChipsetInitTableData < ChipsetInitTableTableEnd) {

    ChipsetInitTableCmdField  = (PCH_HSIO_CMD_FIELD *)ChipsetInitTableData;
    switch (ChipsetInitTableCmdField->Command) {
      case PhyCmdSendPosted:
      case PhyCmdSendNonPosted:
        EntrySize = sizeof (PCH_HSIO_DATA_CMD);
        for (Field = 0; Field < EntrySize; Field++) {
          DEBUG ((DEBUG_INFO, "0x%02x, ", ChipsetInitTableData[Field]));
        }
        ChipsetInitTableDataCmd = (PCH_HSIO_DATA_CMD *)ChipsetInitTableData;
        DEBUG ((DEBUG_INFO, "//Command: 0x%x, Size: 0x%x, PID: 0x%x, OpCode: 0x%x, Bar: 0x%x, ",
          ChipsetInitTableDataCmd->CommandField.Command,
          ChipsetInitTableDataCmd->CommandField.Size,
          ChipsetInitTableDataCmd->Pid,
          ChipsetInitTableDataCmd->OpCode,
          ChipsetInitTableDataCmd->Bar));
        DEBUG ((DEBUG_INFO, "FBE: 0x%x, FID: 0x%x, Offset: 0x%x, Value: 0x%x\n",
          ChipsetInitTableDataCmd->Fbe,
          ChipsetInitTableDataCmd->Fid,
          ChipsetInitTableDataCmd->Offset,
          ChipsetInitTableDataCmd->Value));
        break;

      case PhyCmdDoDelay:
        EntrySize = sizeof (PCH_HSIO_DELAY_CMD);
        for (Field = 0; Field < EntrySize; Field++) {
          DEBUG ((DEBUG_INFO, "0x%02x, ", ChipsetInitTableData[Field]));
        }
        ChipsetInitTableDelayCmd = (PCH_HSIO_DELAY_CMD *)ChipsetInitTableData;
        DEBUG ((DEBUG_INFO, "//Command: 0x%x, Size: 0x%x, DelayPeriod: 0x%x, DelayCount: 0x%x, Padding: 0x%x\n",
          ChipsetInitTableDelayCmd->CommandField.Command,
          ChipsetInitTableDelayCmd->CommandField.Size,
          ChipsetInitTableDelayCmd->DelayPeriod,
          ChipsetInitTableDelayCmd->DelayCount,
          ChipsetInitTableDelayCmd->Padding));
        break;

      case PhyCmdEndStruct:
        EntrySize = sizeof (UINT32);
        for (Field = 0; Field < EntrySize; Field++) {
          DEBUG ((DEBUG_INFO, "0x%02x, ", ChipsetInitTableData[Field]));
        }
        DEBUG ((DEBUG_INFO, "//End Table Marker\n"));
        break;

      default:
        DEBUG ((DEBUG_ERROR, "Unexpected command encountered\n"));
        return;
      }
    // Move to the next entry start
    ChipsetInitTableData += EntrySize;
  }
  DEBUG_CODE_END ();
}


/**
  Prints the ChipsetInit table being pushed to CSME.

  @param[in] ChipsetInitTable Pointer to ChipsetInit Table
  @param[in] TableSize        Chipset Init Table size
**/
STATIC
VOID
PrintChipsetInitTable (
  IN PCH_HSIO_CHIPSET_INIT_TABLE *ChipsetInitTable,
  IN UINT32                      TableSize
  )
{
  DEBUG_CODE_BEGIN ();

  DEBUG ((DEBUG_INFO, "//*****************ChipsetInitTable BIOS Table Start*****************\n\n"));
  PrintChipsetInitTableVersionInfo ((PCH_HSIO_VER_INFO *)ChipsetInitTable);

  PrintChipsetInitTableHeader ((UINT8*)&ChipsetInitTable->ChipsetInitHeader);

  DEBUG ((DEBUG_INFO, "// HSIO Command Table\n"));
  PrintChipsetInitTableData ((UINT8*)&ChipsetInitTable->TableData, TableSize - sizeof(PCH_HSIO_CHIPSET_INIT_TABLE));

  DEBUG ((DEBUG_INFO, "//*****************ChipsetInitTable BIOS Table End*****************\n"));

  DEBUG_CODE_END ();
}

/**
  Add entries to the ChipsetInit Table header

  @param[in, out]  ChipsetInitTable  Pointer to the Chipset Init Table
  @param[in]       HeaderId          HSIO Header Id.
  @param[in]       RecordOffset      Record Offset to be populated in the header.

  @retval          EFI_SUCCESS       The function completes successfully
  @retval          EFI_DEVICE_ERROR  The function encounters an error
**/
STATIC
EFI_STATUS
AddHeaderEntry (
  IN OUT PCH_HSIO_CHIPSET_INIT_TABLE *ChipsetInitTable,
  IN UINT8                           HeaderId,
  IN UINT16                          RecordOffset
  )
{
  INT8              Field;
  PCH_HSIO_HDR_FIELD *ChipsetInitHeader;

  for (Field = PCH_HSIO_HDR_FIELD_NUM - 1; Field >= 0; Field--) {
    ChipsetInitHeader = &ChipsetInitTable->ChipsetInitHeader[Field];
    if (ChipsetInitHeader->Id != 0x00 ||
        RECORD_OFFSET (ChipsetInitHeader->RecordOffsetHigh, ChipsetInitHeader->RecordOffsetLow) != 0) {
      if (Field == PCH_HSIO_HDR_FIELD_NUM - 1) {
        ASSERT (FALSE);
        DEBUG ((DEBUG_ERROR, "%a(): All 16 Header Entries are present, no further Header Entry can be added\n", __FUNCTION__));
        return EFI_DEVICE_ERROR;
      }
      ///
      /// Get back to the last empty header and fill it.
      ///
      ChipsetInitHeader++;
      ChipsetInitHeader->Id = HeaderId;
      ChipsetInitHeader->RecordOffsetLow = RecordOffset & 0xF;
      ChipsetInitHeader->RecordOffsetHigh = (RecordOffset  & 0xFF0) >> 4;
      return EFI_SUCCESS;
    }
  }
  ASSERT (FALSE);
  DEBUG ((DEBUG_ERROR, "%a(): No Header Entries present, at least one Header Entry is expected to be non-zero\n", __FUNCTION__));
  return EFI_DEVICE_ERROR;
}

/**
  This function will delete the old SUS tables from Chipset Init Table as required

  @param[in, out] ChipsetInitTable       Pointer to the Chipset Init Table
  @param[in, out] ChipsetInitTableLen    Size of the Chipset Init Table
**/
STATIC
VOID
RemoveOldSusTables (
  IN OUT PCH_HSIO_CHIPSET_INIT_TABLE *ChipsetInitTable,
  IN OUT UINT32                      *ChipsetInitTableLength
  )
{
  UINT8               Field;
  PCH_HSIO_HDR_FIELD  *ChipsetInitHeader;
  UINT16              Usb2MphyRecordOffset;
  UINT8               *TableDataStart;
  UINT8               *SusTableDataStart;

  Usb2MphyRecordOffset = RECORD_OFFSET_UNDEFINED;

  for (Field = 0; Field < PCH_HSIO_HDR_FIELD_NUM; Field++) {
    ChipsetInitHeader = &ChipsetInitTable->ChipsetInitHeader[Field];
    switch (ChipsetInitHeader->Id) {
      case PCH_HSIO_HEADER_ID_USB2_TUNING:
      case PCH_HSIO_HEADER_ID_MODPHY_TUNING:
        Usb2MphyRecordOffset = MIN (Usb2MphyRecordOffset,
                                    RECORD_OFFSET (ChipsetInitHeader->RecordOffsetHigh, ChipsetInitHeader->RecordOffsetLow));
        break;

      case PCH_HSIO_HEADER_ID_END_OF_HEADER:
        break;

      default:
        continue;
    }
    ZeroMem (ChipsetInitHeader, sizeof (PCH_HSIO_HDR_FIELD));
  }

  ///
  /// Find ChipsetInit SUS Table Pointer Offset. It should point
  /// USB2 Tuning or ModPHY tuning depending on which comes first.
  /// Delete and update Chipset Init Table Length.
  ///
  if (Usb2MphyRecordOffset != RECORD_OFFSET_UNDEFINED) {
    TableDataStart = &ChipsetInitTable->TableData[0];
    SusTableDataStart = TableDataStart + Usb2MphyRecordOffset * sizeof (UINT32);
    ZeroMem (SusTableDataStart, ((UINT8*)ChipsetInitTable + *ChipsetInitTableLength) - SusTableDataStart);
    *ChipsetInitTableLength = SusTableDataStart - (UINT8*)ChipsetInitTable;
  }
}

/**
  This function will append the SUS tables to Chipset Init Table as required

  @param[in, out] ChipsetInitTable       Pointer to the Chipset Init Table
  @param[in, out] ChipsetInitTableLen    Size of the Chipset Init Table
  @param[in]      SusTables              Pointer to SUS Table built by BIOS.
  @param[in]      Usb2SusTblSize         USB2 Tuning SUS Table Size.
  @param[in]      ModPhySusTblSize       ModPhy Tuning SUS Table Size.

  @retval         EFI_SUCCESS            SUS Tables appended successfully
  @retval         Other                  Error while adding SUS tables
**/
STATIC
EFI_STATUS
AppendNewSusTables (
  IN OUT PCH_HSIO_CHIPSET_INIT_TABLE *ChipsetInitTable,
  IN OUT UINT32                      *ChipsetInitTableLength,
  IN UINT8                           *SusTables,
  IN UINT32                          Usb2SusTblSize,
  IN UINT32                          ModPhySusTblSize
  )
{
  EFI_STATUS Status;
  UINT8      *TableDataStart;
  UINT8      *SusTableDataStart;
  UINT32     SusTblSize;
  UINT16     RecordOffset;

  Status = EFI_SUCCESS;
  TableDataStart = &ChipsetInitTable->TableData[0];
  SusTableDataStart = (UINT8*)ChipsetInitTable + *ChipsetInitTableLength;

  SusTblSize = Usb2SusTblSize + ModPhySusTblSize;

  if  (*ChipsetInitTableLength + SusTblSize > PCH_HSIO_CHIPSETINIT_TBL_MAX_SIZE) {
    return EFI_BUFFER_TOO_SMALL;
  }

  ///
  /// Append SUS Table to existing ChipsetInit Table
  ///
  CopyMem (SusTableDataStart, SusTables, SusTblSize);
  *ChipsetInitTableLength = *ChipsetInitTableLength + SusTblSize;

  RecordOffset = (UINT16) ((SusTableDataStart - TableDataStart) / sizeof (UINT32));
  ///
  /// Update USB2 Tuning Record Offset
  ///
  if (Usb2SusTblSize) {
    Status = AddHeaderEntry (ChipsetInitTable, PCH_HSIO_HEADER_ID_USB2_TUNING, RecordOffset);
  }
  ///
  /// Update ModPhy Tuning Record Offset
  /// Note: Assumption is that ModPhy Tuning Table is always appended to the end of the tuning table
  ///
  if (ModPhySusTblSize) {
    RecordOffset = RecordOffset + (UINT16)(Usb2SusTblSize / sizeof (UINT32));
    Status = AddHeaderEntry (ChipsetInitTable, PCH_HSIO_HEADER_ID_MODPHY_TUNING, RecordOffset);
  }

  return Status;
}

/**
  This function will delete and append SUS tables as required

  @param[in]      ChipsetInitTable       Pointer to the Chipset Init Table
  @param[in, out] ChipsetInitTableLen    Size of the Chipset Init Table
  @param[in]      SusTables              Pointer to SUS Table built by BIOS.
  @param[in]      Usb2SusTblSize         USB2 Tuning SUS Table Size.
  @param[in]      ModPhySusTblSize       ModPhy Tuning SUS Table Size.

  @retval         EFI_SUCCESS  The function completes successfully
  @retval         others
**/
STATIC
EFI_STATUS
UpdateSusTables (
  IN OUT PCH_HSIO_CHIPSET_INIT_TABLE *ChipsetInitTable,
  IN OUT UINT32                      *ChipsetInitTableLength,
  IN UINT8                           *SusTables,
  IN UINT32                          Usb2SusTblSize,
  IN UINT32                          ModPhySusTblSize
  )
{
  EFI_STATUS                         Status;

  RemoveOldSusTables (ChipsetInitTable, ChipsetInitTableLength);

  if (ChipsetInitTable->ChipsetInitVerInfo.SusCrcValid) {
    AppendNewSusTables (ChipsetInitTable, ChipsetInitTableLength, SusTables, Usb2SusTblSize, ModPhySusTblSize);
  }

  Status = AddHeaderEntry (ChipsetInitTable, PCH_HSIO_HEADER_ID_END_OF_HEADER, 0x00);

  return Status;
}

/**
  This function constructs BIOS SUS tables containing USB2 and ModPhy tuning data.

  @param[out] SusTable            Pointer to constructed SUS Tables
  @param[out] SusCrc              Computed SUS crc
  @param[out] Usb2SusTblSize      Size of the USB2 tuning table
  @param[out] ModPhySusTblSize    Size of the ModPhy tuning table

  @retval EFI_SUCCESS             Sus Tables contructed successfully or no SUS tables generated
  @retval EFI_OUT_OF_RESOURCES    BIOS is not able to Allocate memory
**/
STATIC
EFI_STATUS
ConstructSusTables (
  OUT UINT8   **SusTable,
  OUT UINT16  *SusCrc,
  OUT UINT32  *Usb2SusTblSize,
  OUT UINT32  *ModPhySusTblSize
  )

{
  EFI_STATUS                        Status;
  PCH_HSIO_CHIPSETINIT_SUS_TBL_PPI  *PchHsioChipsetInitSusTblData;
  UINT32                            EndTableMarker;

  *ModPhySusTblSize = 0;
  *Usb2SusTblSize   = 0;
  EndTableMarker    = 0xF;
  *SusCrc           = PCH_HSIO_SUS_CRC_INVALID;

  Status = PeiServicesLocatePpi (&gPchHsioChipsetInitSusTblDataPpiGuid, 0, NULL, (VOID **) &PchHsioChipsetInitSusTblData);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "SUS Table not generated by BIOS\n"));
    return EFI_SUCCESS;
  }

  *Usb2SusTblSize   = PchHsioChipsetInitSusTblData->PchHsioSusUsb2TuningCount   * sizeof (PCH_HSIO_DATA_CMD);
  *ModPhySusTblSize = PchHsioChipsetInitSusTblData->PchHsioSusModPhyTuningCount * sizeof (PCH_HSIO_DATA_CMD);

  ///
  /// Allocate memory for SUS Table
  ///
  *SusTable = AllocateZeroPool (*Usb2SusTblSize + *ModPhySusTblSize + (2 * sizeof (EndTableMarker)));
  if (*SusTable == NULL) {
    DEBUG ((DEBUG_ERROR, "%a(): Could not allocate Memory\n", __FUNCTION__));
    return EFI_OUT_OF_RESOURCES;
  }
  ///
  /// Copy USB2 and ModPhy Tuning tables to the allocate SUS table memory
  ///
  if (*Usb2SusTblSize != 0) {
    CopyMem (*SusTable, (VOID *) PchHsioChipsetInitSusTblData->PchHsioSusUsb2Tuning, *Usb2SusTblSize);
    CopyMem (*SusTable + *Usb2SusTblSize, (VOID *) &EndTableMarker, sizeof (EndTableMarker));
    *Usb2SusTblSize += sizeof (EndTableMarker);
  }
  if (*ModPhySusTblSize != 0) {
    CopyMem (*SusTable + *Usb2SusTblSize, (VOID *) PchHsioChipsetInitSusTblData->PchHsioSusModPhyTuning,  *ModPhySusTblSize);
    CopyMem (*SusTable + *Usb2SusTblSize + *ModPhySusTblSize, (VOID *) &EndTableMarker, sizeof (EndTableMarker));
    *ModPhySusTblSize += sizeof (EndTableMarker);
  }

  *SusCrc = PchHsioCalculateCrc16 ((UINT8 *)PchHsioChipsetInitSusTblData->PchHsioSusCrc,
                                   ((PchHsioChipsetInitSusTblData->PchHsioSusUsb2TuningCount +
                                     PchHsioChipsetInitSusTblData->PchHsioSusModPhyTuningCount)) * sizeof (PCH_HSIO_SUS_CRC));
  DEBUG ((DEBUG_INFO, "BIOS Computed SUS Table CRC: %x\n", *SusCrc));

  return EFI_SUCCESS;
}

/**
  This function checks if the Chipset Init Table held by CSME is the same one as the BIOS one.

  param[in] CsmeChipsetInitVerInfo     Version Info of Chipset Init Table held by CSME
  param[in] BiosChipsetInitVerInfo     Version Info of Chipset Init Table held by BIOS
  param[in] BiosComputedSusCrc         BIOS Computed CRC of the SUS tables

  @retval TRUE                         Tables are identical
  @retval FALSE                        Tables aren' identical
**/
STATIC
BOOLEAN
IsChipsetInitTableMatch (
  IN PCH_HSIO_VER_INFO *CsmeChipsetInitVerInfo,
  IN PCH_HSIO_VER_INFO *BiosChipsetInitVerInfo,
  IN UINT16            BiosComputedSusCrc
  )
{
  if ((CsmeChipsetInitVerInfo->BaseCrc      == BiosChipsetInitVerInfo->BaseCrc) &&
      (CsmeChipsetInitVerInfo->BaseCrcValid == BiosChipsetInitVerInfo->BaseCrcValid) &&
      (CsmeChipsetInitVerInfo->OemCrc       == BiosChipsetInitVerInfo->OemCrc) &&
      (CsmeChipsetInitVerInfo->OemCrcValid  == BiosChipsetInitVerInfo->OemCrcValid) &&
      (CsmeChipsetInitVerInfo->SusCrc       == BiosComputedSusCrc)) {
    return TRUE;
  }
  return FALSE;
}

/**
  This function chcecks if Chipset Init Sync flow is required in the current boot.

  @param[out] CsmeChipsetInitVerInfo  Version Info of Chipset Init Table held by CSME

  @retval TRUE                        Chipset Init sync is supported
  @retval FALSE                       Chipset Init is either not supported or not required.
**/
STATIC
BOOLEAN
IsChipsetInitSyncRequired (
  OUT PCH_HSIO_VER_INFO *CsmeChipsetInitVerInfo
  )
{
  EFI_BOOT_MODE       BootMode;
  ME_BIOS_PAYLOAD_HOB *MbpHob;
  EFI_STATUS          Status;

  ///
  /// GetBootMode, do not perform ChipsetInit Sync check on S3 RESUME
  ///
  Status = PeiServicesGetBootMode (&BootMode);
  if (BootMode == BOOT_ON_S3_RESUME) {
    DEBUG ((DEBUG_INFO, "Chipset Init sync not required on S3 resume\n"));
    return FALSE;
  }

  ///
  /// Get CSME ChipsetInit Version Data from MBP
  ///
  MbpHob = NULL;
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob == NULL) {
    //
    // Skipping ChipsetInitSync.
    // BIOS should not ASSERT if CSME is not healthy and it should able to boot.
    //
    DEBUG ((DEBUG_ERROR, "ChipsetInit Version information not present in MBP data: %r\n", Status));
    return FALSE;
  }

  CopyMem (CsmeChipsetInitVerInfo, (PCH_HSIO_VER_INFO *) MbpHob->MeBiosPayload.MphyData.ChipsetInitVer, sizeof (PCH_HSIO_VER_INFO));

  DEBUG ((DEBUG_INFO, " Get CSME ChipsetInit Version Data from MBP \n"));
  PrintChipsetInitTableVersionInfo (CsmeChipsetInitVerInfo);

  //
  // Old format is not supported.
  //
  if (CsmeChipsetInitVerInfo->OemCrc == 0x0000) {
    ASSERT (FALSE);
    return FALSE;
  }

  ///
  /// Return from function if the DebugMode bit is set
  ///
  if (CsmeChipsetInitVerInfo->DebugMode == 1) {
    DEBUG ((DEBUG_INFO, "Interrupt the flow -> Debug bit set in the Version Information field obtained from CSE\n"));
    return FALSE;
  }

  return TRUE;
}

/**
  This function is used to ensure CSME has the latest Base, OEM and SUS tables.
  A BIOS<->CSME ChipsetInit sync is performed if there is a mismatch.

  @retval EFI_SUCCESS             BIOS and CSME ChipsetInit settings are in sync
  @retval EFI_UNSUPPORTED         ChipsetInit sync not supported
  @retval EFI_OUT_OF_RESOURCES    BIOS is not able to Allocate memory
**/
EFI_STATUS
ChipsetInitSync (
  VOID
  )
{
  EFI_STATUS                        Status;
  SI_POLICY_PPI                     *SiPolicyPpi;
  PCH_HSIO_CONFIG                   *HsioConfig;
  PCH_HSIO_VER_INFO                 *BiosChipsetInitVerInfo;
  PCH_HSIO_VER_INFO                 CsmeChipsetInitVerInfo;
  UINT8                             *SusTables;
  UINT32                            Usb2SusTblSize;
  UINT32                            ModPhySusTblSize;
  UINT16                            BiosComputedSusCrc;
  PCH_HSIO_CHIPSET_INIT_TABLE       *ChipsetInitTable;
  UINT32                            ChipsetInitTableLength;
  CHIPSET_INIT_INFO                 ChipsetInitHobStruct;
  VOID                              *ChipsetInitHobPtr;
  PCH_RESET_DATA                    ResetData;
  BOOLEAN                           IsBiosChipsetInitTable;
  BOOLEAN                           TablesMatched;


  DEBUG ((DEBUG_INFO, "%a() Start\n", __FUNCTION__));

  if (!IsChipsetInitSyncRequired (&CsmeChipsetInitVerInfo)) {
    return EFI_UNSUPPORTED;
  }

  ///
  /// Get Policy settings through the SiPolicy PPI
  ///
  HsioConfig = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SiPolicyPpi is not located! Error: %r\n", Status));
    return EFI_UNSUPPORTED;
  }
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gHsioConfigGuid, (VOID *) &HsioConfig);
  ASSERT_EFI_ERROR (Status);

  SusTables = NULL;
  Status = ConstructSusTables (&SusTables, &BiosComputedSusCrc, &Usb2SusTblSize, &ModPhySusTblSize);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ///
  /// Allocate memory for maximum ChipsetInit Table size
  ///
  ChipsetInitTableLength = PCH_HSIO_CHIPSETINIT_TBL_MAX_SIZE;
  ChipsetInitTable =  AllocateZeroPool (ChipsetInitTableLength);
  if (ChipsetInitTable == NULL) {
    DEBUG ((DEBUG_ERROR, "%a(): Could not allocate Memory\n", __FUNCTION__));
    FreePool (SusTables);
    return EFI_OUT_OF_RESOURCES;
  }

  ///
  /// Determine which Chipset Init Table should be used and fetch the Version structures
  ///
  if ((HsioConfig->ChipsetInitBinPtr == 0) ||
      (HsioConfig->ChipsetInitBinLen == 0)) {
    BiosChipsetInitVerInfo = &CsmeChipsetInitVerInfo;
    IsBiosChipsetInitTable = FALSE;
  } else {
    BiosChipsetInitVerInfo = (PCH_HSIO_VER_INFO *) HsioConfig->ChipsetInitBinPtr;
    IsBiosChipsetInitTable = TRUE;
  }

  ///
  /// Check if all CRCs are identical. If not, retrieve the whole Chipset Init Table either from
  /// CSE or location pointed by the policy and perform the update.
  ///
  TablesMatched = IsChipsetInitTableMatch (&CsmeChipsetInitVerInfo, BiosChipsetInitVerInfo, BiosComputedSusCrc);

  if (!TablesMatched) {
    if (IsBiosChipsetInitTable) {
      DEBUG ((DEBUG_INFO, "Using ChipsetInit Table embedded in BIOS\n"));
      DEBUG ((DEBUG_INFO, "ChipsetInit Binary Location: %x\n", HsioConfig->ChipsetInitBinPtr));
      DEBUG ((DEBUG_INFO, "ChipsetInit Binary Size: %x\n", HsioConfig->ChipsetInitBinLen));
      CopyMem (ChipsetInitTable, (VOID *) HsioConfig->ChipsetInitBinPtr, HsioConfig->ChipsetInitBinLen);
      ChipsetInitTableLength = HsioConfig->ChipsetInitBinLen;
    } else {
      DEBUG ((DEBUG_INFO, "Read ChipsetInit Binary from CSME\n"));
      Status = PeiHeciReadChipsetInitMsg ((UINT8*)ChipsetInitTable, &ChipsetInitTableLength);
    }

    ChipsetInitTable->ChipsetInitVerInfo.SusCrc      = BiosComputedSusCrc;
    ChipsetInitTable->ChipsetInitVerInfo.SusCrcValid = 1;
    Status = UpdateSusTables (ChipsetInitTable, &ChipsetInitTableLength, SusTables, Usb2SusTblSize, ModPhySusTblSize);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "%a(): Error updating SUS table %r\n", __FUNCTION__, Status));
      ASSERT_EFI_ERROR (Status);
    }

    PrintChipsetInitTable (ChipsetInitTable, ChipsetInitTableLength);

    DEBUG ((DEBUG_INFO, "Push Updated ChipsetInit table with CSME\n"));
    Status = PeiHeciWriteChipsetInitMsg ((UINT8*)ChipsetInitTable, ChipsetInitTableLength);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "ChipsetInit Sync Error: %r\n", Status));
      ASSERT_EFI_ERROR (Status);
      return EFI_UNSUPPORTED;
    }

    if (CsmeChipsetInitVerInfo.SusCrcValid == 0) {
      DEBUG ((DEBUG_INFO, "No global reset required\n"));
    } else {
      DEBUG ((DEBUG_INFO, "Trigger global reset\n"));
      CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
      StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
      SiScheduleResetSetType (EfiResetPlatformSpecific, &ResetData);
    }
  } else {
    DEBUG ((DEBUG_INFO, "No ChipsetInit BIOS <-> CSME sync required as all CRCs and Valid bits match\n"));
  }

  //
  // Initialize ChipsetInitHob
  //
  ZeroMem (&ChipsetInitHobStruct, sizeof (CHIPSET_INIT_INFO));
  ChipsetInitHobStruct.Revision    = CHIPSET_INIT_INFO_REVISION;
  ChipsetInitHobStruct.BaseVersion = BiosChipsetInitVerInfo->Version;
  ChipsetInitHobStruct.OemVersion  = BiosChipsetInitVerInfo->OemVersion;
  ChipsetInitHobStruct.BaseCrc     = BiosChipsetInitVerInfo->BaseCrc;
  ChipsetInitHobStruct.SusCrc      = BiosComputedSusCrc;
  ChipsetInitHobStruct.OemCrc      = BiosChipsetInitVerInfo->OemCrc;

  ChipsetInitHobPtr = BuildGuidDataHob (&gChipsetInitHobGuid, &ChipsetInitHobStruct, sizeof (CHIPSET_INIT_INFO));
  ASSERT (ChipsetInitHobPtr != NULL);

  FreePool (ChipsetInitTable);
  FreePool (SusTables);

  DEBUG ((DEBUG_INFO, "%a() End\n", __FUNCTION__));
  return Status;
}

