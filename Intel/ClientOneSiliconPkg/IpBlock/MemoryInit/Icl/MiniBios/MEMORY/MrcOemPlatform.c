/** @file
  This file contains platform related functions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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

// Include files
#include "MrcTypes.h"
#include "MrcInterface.h"
#include "MemoryUtils.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcReset.h"
#include "MrcOemPlatform.h"
#include "PlatformBoardId.h"
#include "Library/PchPcrLib.h"
#include "Register/PchRegsLpc.h"
#include "Register/PchRegsLpcIcl.h"
#include "Register/PchRegsPcr.h"
#include "Register/PchRegsPsf.h"
#include "Register/PchRegsPsfIcl.h"
#include "Register/PsfRegsVer3.h"
#include "Register/PchRegsPmc.h"
#include "ConfigBlock.h"
#include "MrcMalloc.h"

// MrcSave data is stored here in Flash
#define MRC_SAVE_DATA_FLASH_PTR   0xFFD00000

#define MAX_SPD_PAGE_COUNT (2)
#define MAX_SPD_PAGE_SIZE  (256)
#define MAX_SPD_SIZE       (MAX_SPD_PAGE_SIZE * MAX_SPD_PAGE_COUNT)
#define SPD_PAGE_ADDRESS_0 (0x6C)
#define SPD_PAGE_ADDRESS_1 (0x6E)
#define isprint(a)         (((a) >= ' ') && ((a) <= '~') ? (a) : 0)
#define CPU_FAMILY_MASK    0xFFFFFFF0
#define PCIEBAR_ADDRESS    0xC0000000

#ifdef MRC_DEBUG_PRINT
extern const char CcdString[];
#endif // MRC_DEBUG_PRINT
extern
void
MmioReadCount (
  void
  );
extern
void
MmioWriteCount (
  void
  );
extern
UINT32
MrcCPUStepGet (
  void
  );
extern
UINT32
EFIAPI
PostCode (
  IN UINT32  Value
  );

#pragma pack (push, 1)
// The following section contains board-specific CMD/CTL/CLK and DQ/DQS mapping, needed for LPDDR4

// DQByteMap[0] - ClkDQByteMap:
//                        Entry[0] maps which CPU bytes are attached to DRAM that uses CLK0.
//                        Entry[1] maps which CPU bytes are attached to DRAM that uses CLK1.
// DQByteMap[1] - CmdDQByteMap:
//                        Entry[0] maps which CPU bytes are attached to DRAM that uses CAA.
//                        Entry[1] maps which CPU bytes are attached to DRAM that uses CAB.
// DQByteMap[2] - CtlDQByteMap: Always program to [0xFF, 0] since we have 1 CTL / rank
// DQ byte mapping to CMD/CTL/CLK, from the CPU side

// DQ byte mapping to CMD/CTL/CLK, from the CPU side
// Used for all ICL LPDDR4 boards
const UINT8 DqByteMapIcl[2][3][2] = {
  // Channel 0:
  {
    { 0x0F, 0xF0 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
    { 0x0F, 0xF0 }, // Cmd CAA goes to Bytes[3:0], CAB goes to Bytes[7:4]
    { 0xFF, 0x00 }  // CTL (CS) goes to all bytes
  },
  // Channel 1:
  {
    { 0x0F, 0xF0 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
    { 0x0F, 0xF0 }, // Cmd CAA goes to Bytes[3:0], CAB goes to Bytes[7:4]
    { 0xFF, 0x00 }  // CTL (CS) goes to all bytes
  }
};


//
// ICL-U LPDDR4 Type-4 RVP DQS byte swizzling between CPU and DRAM
//
const UINT8 DqsMapCpu2DramIclULp4Type4Rvp[2][8] = {
  { 2, 3, 0, 1, 7, 6, 4, 5 }, // Channel 0
  { 1, 0, 3, 2, 5, 4, 7, 6 }  // Channel 1
};

//
// ICL-U LPDDR4 Type-3 RVP DQS byte swizzling between CPU and DRAM
//
const UINT8 DqsMapCpu2DramIclULp4Type3Rvp[2][8] = {
  { 2, 3, 1, 0, 7, 6, 4, 5 }, // Channel 0
  { 1, 0, 3, 2, 5, 4, 7, 6 }  // Channel 1
};

//
// ICL-Y LPDDR4 Type-4 and Type-4 PnP RVP DQS byte swizzling between CPU and DRAM
//
const UINT8 DqsMapCpu2DramIclYLp4Rvp[2][8] = {
  { 0, 1, 2, 3, 4, 5, 6, 7 }, // Channel 0
  { 0, 1, 2, 3, 5, 4, 7, 6 }  // Channel 1
};

//
// ICL-U LPDDR4 Type-4 PD RVP (BOM_ID = 6) DQS byte swizzling between CPU and DRAM (BoardIdIclULp4Type4Tcpd)
//
const UINT8 DqsMapCpu2DramIclULp4TcpdBomId6Rvp[2][8] = {
  { 0, 1, 2, 3, 4, 5, 6, 7 }, // Channel 0
  { 0, 1, 2, 3, 4, 5, 6, 7 }  // Channel 1
};

//
// ICL-U LPDDR4 Type-4 PD RVP (FAB_ID = 1) DQS byte swizzling between CPU and DRAM (BoardIdIclULp4Type4Tcpd)
//
const UINT8 DqsMapCpu2DramIclULp4Type4TcpdFabId1Rvp[2][8] = {
  { 2, 3, 0, 1, 6, 5, 4, 7 }, // Channel 0
  { 1, 0, 3, 2, 5, 4, 7, 6 }  // Channel 1
};

//
// ICL-Y LPDDR4 RVP respin (FAB_ID = 3) DQS byte swizzling between CPU and DRAM (BoardIdIclYLp4Type4Tlc & BoardIdIclYLp4PnpType4Tlc)
//
const UINT8 DqsMapCpu2DramIclYLp4Type4TlcFabId3Rvp[2][8] = {
  { 0, 2, 1, 3, 4, 5, 6, 7 }, // Ch 0
  { 1, 2, 3, 0, 5, 4, 7, 6 }  // Ch 1
};

//
// ICL-Y LPDDR4 RVPC DQS byte swizzling between CPU and DRAM
//
const UINT8 DqsMapCpu2DramIclYLp4RvpC[2][8] = {
  { 0, 1, 2, 3, 4, 5, 7, 6 }, // Channel 0
  { 0, 1, 2, 3, 4, 5, 7, 6 }  // Channel 1
};


//
// ICL-YN RVP LP4 DQS byte swizzling between CPU and DRAM
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 DqsMapCpu2DramIclYNLp4[2][8] = {
  { 0, 2, 1, 3, 5, 7, 4, 6 }, // Channel 0
  { 0, 2, 1, 3, 5, 7, 4, 6 }, // Channel 1
};

//
// ICL-U SDS ERB board DQS byte swizzling between CPU and DRAM
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 DqsMapCpu2DramIclUSdsLp4[2][8] = {
  { 2, 3, 0, 1, 4, 5, 7, 6 }, // Channel 0
  { 2, 3, 0, 1, 6, 7, 4, 5 }  // Channel 1
};

//
// KSL-I LPDDR4 Type-4 RVP DQS byte swizzling between CPU and DRAM
//
const UINT8 DqsMapCpu2DramKslILp4Type4Rvp[2][8] = {
  { 2, 1, 0, 3, 6, 5, 4, 7 }, // Channel 0
  { 2, 1, 0, 3, 6, 5, 4, 7 }, // Channel 1
};


//
// EHL LPDDR4 Type-4 RVP DQS byte swizzling between CPU and DRAM
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 DqsMapCpu2DramEhlLp4Type4Rvp[2][8] = {
  { 3, 0, 1, 2, 7, 4, 5, 6 }, // Channel 0
  { 3, 0, 1, 2, 7, 4, 5, 6 }  // Channel 1
};

//
// EHL LPDDR4x ERB DQS byte swizzling between CPU and DRAM
//
const UINT8 DqsMapCpu2DramEhlULp4Type4Erb[2][8] = {
  { 0, 3, 2, 1, 7, 5, 4, 6 }, // Channel 0
  { 3, 1, 2, 0, 4, 7, 6, 5 }  // Channel 1
};

//
// EHL LPDDR4x RVP DQS byte swizzling between CPU and DRAM
//
const UINT8 DqsMapCpu2DramEhlULp4Type4Rvp[2][8] = {
  { 0, 3, 2, 1, 7, 5, 4, 6 }, // Channel 0
  { 3, 1, 2, 0, 4, 7, 6, 5 }  // Channel 1
};





#pragma pack (pop)

/**
  Read the SPD data over the SMBus, at the specified SPD address, starting at
  the specified starting offset and read the given amount of data.

  @param[in, out] Inputs - Mrc Inputs structure
  @param[in] SpdAddress  - SPD SMBUS address
  @param[in, out] Buffer - Buffer to store the data.
  @param[in] Start       - Starting SPD offset
  @param[in] Size        - The number of bytes of data to read and also the size of the buffer.
  @param[in, out] Page   - The final page that is being pointed to.

  @retval mrcSuccess if the read is successful, otherwise mrcDimmNotExist, which
  @retval indicates that no slots are populated.
**/
static
MrcStatus
DoSpdRead (
  IN OUT MrcInput *const Inputs,
  IN     const UINT8     SpdAddress,
  IN OUT UINT8 *const    Buffer,
  IN     const UINT16    Start,
  IN           UINT16    Size,
  IN OUT UINT8           *Page
  )
{
  MrcStatus Status;
  BOOLEAN   PageUpdate;
  UINT16    Count;
  UINT16    Index;

  Status = mrcFail;
  if ((Buffer != NULL) && (Start < MAX_SPD_SIZE) && ((Start + Size) < MAX_SPD_SIZE)) {
    Count = 0;
    PageUpdate = FALSE;
    while (Size--) {
      Index = Start + Count;
      if ((Index / MAX_SPD_PAGE_SIZE) != *Page) {
        *Page = (UINT8) (Index / MAX_SPD_PAGE_SIZE);
        PageUpdate = TRUE;
      }
      Index %= MAX_SPD_PAGE_SIZE;
      if (PageUpdate == TRUE) {
        PageUpdate = FALSE;
        MrcOemSmbusWrite8 (Inputs->SmbusBaseAddress, (*Page == 0) ? SPD_PAGE_ADDRESS_0 : SPD_PAGE_ADDRESS_1, 0, 0);
      }
      Status = MrcOemSmbusRead8 (Inputs->SmbusBaseAddress, SpdAddress, (UINT8) Index, &Buffer[Count]);
      if (mrcSuccess != Status) {
        break;
      }
      Count++;
    }
  }
  return (Status);
}

/**
  See if there is valid XMP SPD data.

  @param[in] Debug    - Mrc debug structure.
  @param[in, out] Spd - Mrc SPD structure.
  @param[in] XmpStart - The current offset in the SPD.

  @retval TRUE if valid, FALSE in not.
**/
static
BOOLEAN
VerifyXmp (
  IN MrcDebug          *Debug,
  IN OUT MrcSpd *const Spd,
  IN const UINT16      XmpStart
  )
{
  SPD_EXTREME_MEMORY_PROFILE_HEADER_2_0  *Header2;
  BOOLEAN                                 Xmp;

  Xmp = FALSE;

  switch (((UINT8 *)Spd)[2]) {
    case MRC_SPD_DDR4_SDRAM_TYPE_NUMBER:
      Header2 = &Spd->Ddr4.EndUser.Xmp.Header;
      if (XmpStart == ((UINTN) (Header2) - (UINTN) Spd)) {
        Xmp = TRUE;
        if ((Header2->XmpRevision.Data) == 0x20) {
          return (TRUE);
        } else {
          Header2->XmpId            = 0;
          Header2->XmpOrgConf.Data  = 0;
          Header2->XmpRevision.Data = 0;
        }
      }
      break;

    case MRC_SPD_LPDDR4_SDRAM_TYPE_NUMBER:
    case MRC_SPD_LPDDR4X_SDRAM_TYPE_NUMBER:
      // No XMP Support for LPDDR4
      return (TRUE);
      break;

    default:
      return (FALSE);
  }
  if (!Xmp) {
    return (TRUE);
  }
  return (FALSE);
}

/**
  Read the SPD data over the SMBus, for all DIMM slots and copy the data to the MrcData structure.
  The SPD data locations read is controlled by the current boot mode.

  @param[in] BootMode     - Mrc Boot Mode
  @param[in, out] MrcData - Mrc global data structure

  @retval mrcSuccess if the read is successful, otherwise mrcDimmNotExist, which
  @retval indicates that no slots are populated.
**/
MrcStatus
GetSpdData (
  IN     const MRC_BOOT_MODE  BootMode,
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput              *Inputs;
  MrcDebug              *Debug;
  MrcControllerIn       *ControllerIn;
  MrcChannelIn          *ChannelIn;
  MrcDimmIn             *DimmIn;
  UINT8                 *Buffer;
  const MrcSpdOffsetTable  *Tbl;
  const MrcSpdOffsetTable  *TableSelect;
  MrcStatus             Status;
  UINT16                Offset;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT8                 Count;
  UINT8                 Index;
  UINT8                 Stop;
  UINT8                 Page;

  Inputs = &MrcData->Inputs;
  Debug  = &MrcData->Outputs.Debug;
  Count  = 0;
  Page   = (UINT8) (~0);
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerIn = &Inputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn = &ControllerIn->Channel[Channel];
      if (ChannelIn->Status == CHANNEL_PRESENT) {
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          Status  = mrcSuccess;
          DimmIn  = &ChannelIn->Dimm[Dimm];
          if ((DimmIn->Status == DIMM_ENABLED) || (DimmIn->Status == DIMM_DISABLED)) {
            Buffer = (UINT8 *) &DimmIn->Spd.Data;
            if (DimmIn->SpdAddress > 0) {
              Status |= DoSpdRead (Inputs, DimmIn->SpdAddress, &Buffer[2], 2, 1, &Page);
              if (Status != mrcSuccess) {
                Buffer[2] = 0;
              }
              switch (Buffer[2]) {
                case MRC_SPD_DDR4_SDRAM_TYPE_NUMBER:
                default:
                  TableSelect = MrcSpdDdr4Table;
                  Stop = (sizeof (MrcSpdDdr4Table) / sizeof (MrcSpdOffsetTable));
                  break;

                case MRC_SPD_LPDDR4_SDRAM_TYPE_NUMBER:
                case MRC_SPD_LPDDR4X_SDRAM_TYPE_NUMBER:
                  TableSelect = MrcSpdLpddrTable;
                  Stop = (sizeof (MrcSpdLpddrTable) / sizeof (MrcSpdOffsetTable));
                  break;
              }
              for (Index = 0; (Status == mrcSuccess) && (Index < Stop); Index++) {
                Tbl = &TableSelect[Index];
                if ((1 << BootMode) & Tbl->BootMode) {
                  Status = DoSpdRead (
                             Inputs,
                             DimmIn->SpdAddress,
                             &Buffer[Tbl->Start],
                             Tbl->Start,
                             Tbl->End - Tbl->Start + 1,
                             &Page
                             );
                  if (Status == mrcSuccess) {
                    for (Offset = Tbl->Start; Offset <= Tbl->End; Offset++) {
                      DimmIn->Spd.SpdValid[Offset / CHAR_BITS] |= 1 << (Offset % CHAR_BITS);
                    }
                    if (bmCold == BootMode) {
                      if (FALSE == VerifyXmp (Debug, (MrcSpd *) Buffer, Tbl->Start)) {
                        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VerifyXmp FALSE\n");
                        break;
                      }
                    }
                  } else {
                    MRC_DEBUG_MSG (
                      Debug,
                      MSG_LEVEL_WARNING,
                      "ERROR! Fail to read SMB DimmAddress %Xh Offset %Xh - %Xh\n",
                      DimmIn->SpdAddress,
                      Tbl->Start,
                      Tbl->End
                      );
                  } // if (Status...
                } // if (((1 << BootMode)...
              }  // for (Index...
            }  else { // if (DimmIn->SpdAddress > 0), 0 = MemoryDown, see EnableMemoryDown()
              Status = mrcSuccess;
            }

            if (Status == mrcSuccess) {
              Count++;
            } else {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "DIMM is not populated on channel %u, slot %u\n", Channel, Dimm);
            } // if (Status...
          }  // if (DimmIn->Status == DIMM_ENABLED)
        }  // for (Dimm...
      }  // if (ChannelIn->Status...
    }  // for (Channel...
  }  // for (Controller...
  return ((Count > 0) ? mrcSuccess : mrcDimmNotExist);
}

/**
  8 bit I/O port read.

  @param[in] IoAddress - The I/O port read address.

  @retval The value read.
**/
UINT8
MrcOemInPort8 (
  IN const UINT32 IoAddress
  )
{
  return IoRead8 (IoAddress);
}

/**
  8 bit I/O port write.

  @param[in] IoAddress - The I/O port read address.
  @param[in] Data      - The value to write.

  @retval Nothing.
**/
void
MrcOemOutPort8 (
  IN const UINT32 IoAddress,
  IN const UINT8  Data
  )
{
  IoWrite8 (IoAddress, Data);
}

/**
  16 bit I/O port read.

  @param[in] IoAddress - The I/O port read address.

  @retval The value read.
**/
UINT16
MrcOemInPort16 (
  IN const UINT32 IoAddress
  )
{
  return IoRead16 (IoAddress);
}

/**
  16 bit I/O port write.

  @param[in] IoAddress - The I/O port read address.
  @param[in] Data      - The value to write.

  @retval Nothing.
**/
void
MrcOemOutPort16 (
  IN const UINT32 IoAddress,
  IN const UINT16 Data
  )
{
  IoWrite16 (IoAddress, Data);
}

/**
  32 bit I/O port read.

  @param[in] IoAddress - The I/O port read address.

  @retval The value read.
**/
UINT32
MrcOemInPort32 (
  IN const UINT32 IoAddress
  )
{
  return IoRead32 (IoAddress);
}

/**

  32 bit I/O port write.

  @param[in] IoAddress - The I/O port read address.
  @param[in] Data      - The value to write.

  @retval Nothing.
**/
void
MrcOemOutPort32 (
  IN const UINT32 IoAddress,
  IN const UINT32 Data
  )
{
  IoWrite32 (IoAddress, Data);
}

/**
  The PCI index address.

  @retval The PCI index address.
**/
UINT16
MrcOemPciIndex (
  void
  )
{
  return 0xCF8;
}

/**
  The PCI data address.

  @retval The PCI data address.
**/
UINT16
MrcOemPciData (
  void
  )
{
  return 0xCFC;
}

/**
  Calculate the PCI device address for the given Bus/Device/Function/Offset.

  @param[in] Bus      - PCI bus
  @param[in] Device   - PCI device
  @param[in] Function - PCI function
  @param[in] Offset   - Offset

  @retval The PCI device address.
**/
UINT32
GetPciDeviceAddress (
  IN const UINT8 Bus,
  IN const UINT8 Device,
  IN const UINT8 Function,
  IN const UINT8 Offset
  )
{
  return (
    ((UINT32) ((Bus)      & 0xFF) << 16) |
    ((UINT32) ((Device)   & 0x1F) << 11) |
    ((UINT32) ((Function) & 0x07) << 8)  |
    ((UINT32) ((Offset)   & 0xFF) << 0)  |
    (1UL << 31));
}

/**
  Calculate the PCIE device address for the given Bus/Device/Function/Offset.

  @param[in] Bus      - PCI bus
  @param[in] Device   - PCI device
  @param[in] Function - PCI function
  @param[in] Offset   - Offset

   The PCIE device address.

  @retval The PCIe device address
**/
UINT32
GetPcieDeviceAddress (
  IN const UINT8 Bus,
  IN const UINT8 Device,
  IN const UINT8 Function,
  IN const UINT8 Offset
  )
{
  return ((UINT32) Bus << 20) + ((UINT32) Device << 15) + ((UINT32) Function << 12) + ((UINT32) Offset << 0);
}

/**
  Check if RTC date and time update is in progress and wait util it's finished.
  We have at least 244us when "update in progress bit" is seen as low to
  perform an operation on the RTC.

  @retval Zero on timeout or non-zero and RTC is ready for transaction.
**/
UINT32
CheckUpdateComplete (
  void
  )
{
  UINT32 Timeout;

  // Wait until RTC "update in progress" bit goes low.
  Timeout = 0x0FFFFF;
  do {
    MrcOemOutPort8 (R_RTC_IO_INDEX, CMOS_REGA);
    if ((MrcOemInPort8 (R_RTC_IO_TARGET) & RTC_UPDATE_IN_PROGRESS) != RTC_UPDATE_IN_PROGRESS) {
      break;
    }
  } while (--Timeout > 0);

  return Timeout;
}

/**
  Initializes the RTC.

  @retval Nothing.
**/
void
InitRtc (
  void
  )
{
  MrcOemOutPort8 (R_RTC_IO_INDEX, CMOS_REGB);
  MrcOemOutPort8 (R_RTC_IO_TARGET, RTC_HOLD | RTC_MODE_24HOUR);

  MrcOemOutPort8 (R_RTC_IO_INDEX, CMOS_REGA);
  MrcOemOutPort8 (R_RTC_IO_TARGET, RTC_CLOCK_DIVIDER | RTC_RATE_SELECT);

  MrcOemOutPort8 (R_RTC_IO_INDEX, CMOS_REGC);
  MrcOemInPort8 (R_RTC_IO_TARGET);

  MrcOemOutPort8 (R_RTC_IO_INDEX, CMOS_REGD);
  MrcOemInPort8 (R_RTC_IO_TARGET);

  MrcOemOutPort8 (R_RTC_IO_INDEX, CMOS_REGB);
  MrcOemOutPort8 (R_RTC_IO_TARGET, RTC_MODE_24HOUR);

  return;
}

/**
  Read specific RTC/CMOS RAM

  @param[in] Location        Point to RTC/CMOS RAM offset for read

  @retval The data of specific location in RTC/CMOS RAM.
**/
UINT8
RtcRead (
  IN const UINT8 Location
  )
{
  UINT8  RtcIndexPort;
  UINT8  RtcDataPort;

  // CMOS access registers (using alternative access not to handle NMI bit)
  if (Location < RTC_BANK_SIZE) {
    // First bank
    RtcIndexPort  = R_RTC_IO_INDEX_ALT;
    RtcDataPort   = R_RTC_IO_TARGET_ALT;
  } else {
    // Second bank
    RtcIndexPort  = R_RTC_IO_EXT_INDEX_ALT;
    RtcDataPort   = R_RTC_IO_EXT_TARGET_ALT;
  }

  MrcOemOutPort8 (RtcIndexPort, Location & RTC_INDEX_MASK);
  return MrcOemInPort8 (RtcDataPort);
}

/**
  Returns the current time, as determined by reading the Real Time Clock (RTC) on the platform.
  Since RTC time is stored in BCD, convert each value to binary.

  @param[out] Seconds       - The current second (0-59).
  @param[out] Minutes       - The current minute (0-59).
  @param[out] Hours         - The current hour (0-23).
  @param[out] DayOfMonth    - The current day of the month (1-31).
  @param[out] Month         - The current month (1-12).
  @param[out] Year          - The current year (2000-2099).

  @retval Nothing.
**/
void
GetRtcTime (
  OUT UINT8  *const Seconds,
  OUT UINT8  *const Minutes,
  OUT UINT8  *const Hours,
  OUT UINT8  *const DayOfMonth,
  OUT UINT8  *const Month,
  OUT UINT16 *const Year
  )
{
  if (0 == CheckUpdateComplete ()) {
    InitRtc ();
  }
  // Read seconds
  MrcOemOutPort8 (R_RTC_IO_INDEX, RTC_SECONDS);
  *Seconds = MrcOemInPort8 (R_RTC_IO_TARGET);

  // Read minutes
  MrcOemOutPort8 (R_RTC_IO_INDEX, RTC_MINUTES);
  *Minutes = MrcOemInPort8 (R_RTC_IO_TARGET);

  // Read hours
  MrcOemOutPort8 (R_RTC_IO_INDEX, RTC_HOURS);
  *Hours = MrcOemInPort8 (R_RTC_IO_TARGET);

  // Read day of month
  MrcOemOutPort8 (R_RTC_IO_INDEX, RTC_DAY_OF_MONTH);
  *DayOfMonth = MrcOemInPort8 (R_RTC_IO_TARGET);

  // Read month
  MrcOemOutPort8 (R_RTC_IO_INDEX, RTC_MONTH);
  *Month = MrcOemInPort8 (R_RTC_IO_TARGET);

  // Read year and add current century.
  MrcOemOutPort8 (R_RTC_IO_INDEX, RTC_YEAR);
  *Year = MrcOemInPort8 (R_RTC_IO_TARGET);

  *Seconds    = BCD2BINARY (*Seconds);
  *Minutes    = BCD2BINARY (*Minutes);
  *Hours      = BCD2BINARY (*Hours);
  *DayOfMonth = BCD2BINARY (*DayOfMonth);
  *Month      = BCD2BINARY (*Month);
  *Year       = BCD2BINARY (*Year) + CENTURY_OFFSET;
}

/**
  Write specific RTC/CMOS RAM

  @param[in] Location        Point to RTC/CMOS RAM offset for write
  @param[in] Value           The data that will be written to RTC/CMOS RAM
**/
void
RtcWrite (
  IN const UINT8 Location,
  IN const UINT8 Value
  )
{
  UINT8  RtcIndexPort;
  UINT8  RtcDataPort;

  // CMOS access registers (using alternative access not to handle NMI bit)
  if (Location < RTC_BANK_SIZE) {
    // First bank
    RtcIndexPort  = R_RTC_IO_INDEX_ALT;
    RtcDataPort   = R_RTC_IO_TARGET_ALT;
  } else {
    // Second bank
    RtcIndexPort  = R_RTC_IO_EXT_INDEX_ALT;
    RtcDataPort   = R_RTC_IO_EXT_TARGET_ALT;
  }

  MrcOemOutPort8 (RtcIndexPort, Location & RTC_INDEX_MASK);
  MrcOemOutPort8 (RtcDataPort, Value);
}

/**
  Read word from specific RTC/CMOS RAM

  @param[in] Location        Point to RTC/CMOS RAM offset for read

  @retval The data of specific location in RTC/CMOS RAM.
**/
UINT16
RtcRead16 (
  IN const UINT8 Location
  )
{
  return RtcRead (Location) | (RtcRead (Location + 1) << 8);
}

/**
  Write word to specific RTC/CMOS RAM

  @param[in] Location        Point to RTC/CMOS RAM offset for write
  @param[in] Value           The data that will be written to RTC/CMOS RAM
**/
void
RtcWrite16 (
  IN const UINT8   Location,
  IN const UINT16  Value
  )
{
  RtcWrite (Location, (UINT8) Value);
  RtcWrite (Location + 1, (UINT8) (Value >> 8));
}

/**
  Gets CPU ratio

  @retval Cpu ratio.
**/
UINT32
MrcGetCpuRatio (
  void
  )
{
  PCU_CR_PLATFORM_INFO_STRUCT Msr;

  Msr.Data = ReadMsr64 (PCU_CR_PLATFORM_INFO);
  return (Msr.Bits.MAX_NON_TURBO_LIM_RATIO);
}

/**
  Gets CPU current time.

  @param[in] GlobalData - Pointer to global MRC data struct.

  @retval The current CPU time in milliseconds.
**/
UINT64
GetCpuTime (
  IN VOID     *GlobalData
  )
{
  MrcParameters   *MrcData;
  UINT64          TimeBase;

  MrcData = (MrcParameters *) GlobalData;

  TimeBase = (MrcData->Inputs.BClkFrequency / 1000) * MrcGetCpuRatio (); //In Millisec
  TimeBase = ((TimeBase == 0) ? 0 : MrcOemMemoryDivideU64ByU64 (AsmReadTsc (), TimeBase));


  return TimeBase;
}

/**
  Gets CPU current time.

  @param[in] GlobalData - Pointer to global MRC data struct.

  @retval The current CPU time in microseconds.
**/
UINT64
MrcOemGetCpuTimeMicroSec (
  IN VOID     *GlobalData
  )
{
  MrcParameters   *MrcData;
  UINT64          TimeBase;

  MrcData = (MrcParameters *) GlobalData;

  TimeBase = ((MrcData->Inputs.TscTimeBase == 0) ? 0 : MrcOemMemoryDivideU64ByU64 (AsmReadTsc (), MrcData->Inputs.TscTimeBase)); // In [us]


  return TimeBase;
}

/**
  Gets CPU current time.

  @param[in] GlobalData - Pointer to global MRC data struct.

  @retval The current CPU time in nanoseconds.
**/
UINT64
MrcOemGetCpuTimeNanoSec (
  IN VOID     *GlobalData
  )
{
  MrcParameters   *MrcData;
  UINT64          TimeBase;

  MrcData = (MrcParameters *) GlobalData;

  TimeBase = ((MrcData->Inputs.TscTimeBase == 0) ? 0 : MrcOemMemoryDivideU64ByU64 (MrcOemMemoryMultiplyU64ByU32 (AsmReadTsc (), 1000), MrcData->Inputs.TscTimeBase)); // In [ns]


  return TimeBase;
}

/**
  Copy the specified number of memory bytes, a byte at a time, from the
  specified source to the specified destination.

  @param[in, out] Dest      - Destination pointer.
  @param[in]      Src       - Source pointer.
  @param[in]      NumBytes  - The number of bytes to copy.

  @retval Nothing.
**/
void
MrcOemMemoryCpy (
  IN OUT UINT8 *Dest,
  IN UINT8     *Src,
  IN UINT32    NumBytes
  )
{
  CopyMem (Dest, Src, NumBytes);
}

/**
  Sets the specified number of memory bytes, a byte at a time, at the
  specified destination.

  @param[in, out] Dest      - Destination pointer.
  @param[in]      Value     - The value to set.
  @param[in]      NumBytes  - The number of bytes to set.

  @retval Nothing.
**/
void
MrcOemMemorySet (
  IN OUT UINT8 *Dest,
  IN UINT32    NumBytes,
  IN UINT32    Value
  )
{
  SetMem ((UINT8 *) Dest, NumBytes, (UINT8) Value);
}

/**
  Sets the specified number of memory dwords, a dword at a time, at the
  specified destination.

  @param[in, out] Dest      - Destination pointer.
  @param[in]      Value     - The value to set.
  @param[in]      NumWords  - The number of dwords to set.

  @retval Nothing.
**/
void
SetMemWord (
  IN OUT UINT16    *Dest,
  IN UINT32        NumWords,
  IN const UINT16  Value
  )
{
  while (0 != NumWords--) {
    *Dest++ = Value;
  }

  return;
}

/**
  Sets the specified number of memory dwords, a dword at a time, at the
  specified destination.

  @param[in, out] Dest      - Destination pointer.
  @param[in]      Value     - The value to set.
  @param[in]      NumDwords - The number of dwords to set.

  @retval Nothing.
**/
void
SetMemDword (
  IN OUT UINT32    *Dest,
  IN UINT32        NumDwords,
  IN const UINT32  Value
  )
{
  while (0 != NumDwords--) {
    *Dest++ = Value;
  }

  return;
}

/**
  Read 64 bits from the Memory Mapped I/O space.
  Use MMX instruction for atomic access, because some MC registers have side effect.

  @param[in] Address - Memory mapped I/O address.

  @retval The 64 bit value read from the memory mapped I/O space.
**/
UINT64
SaMmioRead64 (
  IN  UINT32 Address
  )
{
  UINT64 *MmioOffset;
  UINT64 *Pointer;
  UINT64 MmxSave;
  UINT64 Value;

  MmxSave    = 0;
  MmioOffset = (UINT64 *) Address;
  Pointer    = &Value;
#if defined __GNUC__  // GCC compiler
  __asm__ __volatile__ (
   "movq   %%mm0,%[MmxSave]\n\
    mov    %[MmioOffset],%%edi\n\
    movq   %%ds:(%%edi),%%mm0\n\
    mov    %[Pointer],%%edi\n\
    movq   %%mm0,%%ds:(%%edi)\n\
    movq   %[MmxSave],%%mm0\n\
    emms"
  : [MmxSave]"=m"(MmxSave), [Pointer]"=m"(Pointer)
  : [MmioOffset]"m"(MmioOffset)
  : "%edi"
  );
#else // MSFT compiler
  ASM {
    ; Save mm0
    movq  MmxSave, mm0
    mov   edi, MmioOffset
    movq  mm0, QWORD PTR DS:[edi]
    mov   edi, Pointer
    movq  QWORD PTR DS:[edi], mm0

    ; Restore mm0
    movq  mm0, MmxSave
    emms                     ; Exit mmx Instruction
  }
#endif // __GNUC__
  return (Value);
}

/**
  Write 64 bits to the Memory Mapped I/O space.
  Use MMX instruction for atomic access, because some MC registers have side effect.

  @param[in] Address - Memory mapped I/O address.
  @param[in] Value   - The value to write.

  @retval The 64 bit value written to the memory mapped I/O space.
**/
UINT64
SaMmioWrite64 (
  IN UINT32 Address,
  IN UINT64 Value
  )
{
  UINT64 MmxSave;
  UINT64 *MmioOffset;

  MmxSave    = 0;
  MmioOffset = (UINT64 *) (Address);

#if defined __GNUC__  // GCC compiler
  __asm__ __volatile__ (
   "movq   %%mm0,%[MmxSave]\n\
    mov    %[MmioOffset],%%edi\n\
    movq   %[Value],%%mm0\n\
    movq   %%mm0,%%ds:(%%edi)\n\
    movq   %[MmxSave],%%mm0\n\
    emms"
  :
  : [MmxSave]"m"(MmxSave), [MmioOffset]"m"(MmioOffset), [Value]"m"(Value)
  : "%edi"
  );
#else //MSFT compiler
  ASM {
    ; Save mm0
    movq  MmxSave, mm0
    mov   edi, MmioOffset
    movq  mm0, Value
    movq  QWORD PTR DS:[edi], mm0

    ; Restore mm0
    movq  mm0, MmxSave
    emms                     ; Exit mmx Instruction
  }
#endif // __GNUC__
  return (Value);
}

/**
  Shift the specified data value left by the specified count.

  @param[in] Data            - 64 bit number to shift left.
  @param[in] Count           - Number of bits to shift (0..63)

  @retval The number of bits shifted left.
**/
UINT64
MrcOemMemoryLeftShiftU64 (
  IN const UINT64 Data,
  IN const UINT8  Count
  )
{
  return LShiftU64 (Data, Count);
}

/**
  Shift the specified data value Right by the specified count.

  @param[in] Data            - UINT64 number to shift
  @param[in] Count           - number of bits to shift (0..63)

  @retval Returns the shifted UINT64 value.
**/
UINT64
MrcOemMemoryRightShiftU64 (
  IN const UINT64 Data,
  IN const UINT8  Count
  )
{
  return RShiftU64 (Data, Count);
}

/**
  this function Multiply UINT64 with a UINT32 number. Result is <= 64 bits
  need to be port for OEM platform requirements.

  @param[in] Multiplicand  - UINT64 number to be multiplied with
  @param[in] Multiplier - UINT32 number to multiply

  @retval The input data value shifted right by count.
**/
UINT64
MrcOemMemoryMultiplyU64ByU32 (
  IN const UINT64 Multiplicand,
  IN const UINT32 Multiplier
  )
{
  return MultU64x32 (Multiplicand, Multiplier);
}

/**
  Divide UINT64 with a UINT64 number. Result is <= 32 bits

  @param[in] Dividend  - UINT64 number to be multiplied with
  @param[in] Divisor - UINT32 number to multiply

  @retval Returns the quotient result of UINT32 value.
**/
UINT64
MrcOemMemoryDivideU64ByU64 (
  IN const UINT64 Dividend,
  IN const UINT64 Divisor
  )
{
  return (DivU64x64Remainder (Dividend, Divisor, NULL));
}

/**
  Read 64 bits from the Memory Mapped I/O space.

  @param[in] Address - The address of the MMIO location.

  @retval The 64-bit value read from the Memory Mapped I/O space.
**/
UINT64
MrcOemMmioRead64 (
  IN  UINT32 Address
  )
{
  MmioReadCount ();
  return (SaMmioRead64 (Address));
}

/**
  Read 32 bits from the Memory Mapped I/O space.

  @param[in]  Offset      - Offset from the specified base address.

  @retval The 32 bit value read from the Memory Mapped I/O space.
**/
UINT32
MrcOemMmioRead32 (
  IN  UINT32 Offset
  )
{
  MmioReadCount ();
  return (*((volatile UINT32 *) (Offset)));
}

/**
  Read 16 bits from the Memory Mapped I/O space.

  @param[in]  Offset      - Offset from the specified base address.

  @retval The 16 bit value read from the Memory Mapped I/O space.
**/
UINT16
MrcOemMmioRead16 (
  IN  UINT32 Offset
  )
{
  MmioReadCount ();
  return (*((volatile UINT16 *) (Offset)));
}

/**
  Read 8 bits from the Memory Mapped I/O space.

  @param[in]  Offset      - Offset from the specified base address.

  @retval The 8 bit value read from the Memory Mapped I/O space.
**/
UINT8
MrcOemMmioRead8 (
  IN  UINT32 Offset
  )
{
  MmioReadCount ();
  return (*((volatile UINT8 *) (Offset)));
}

/**
  Write 64 bits to the Memory Mapped I/O space.

  @param[in] Address - The address of the MMIO location.
  @param[in] Value   - The value to write.

  @retval Nothing.
**/
UINT64
MrcOemMmioWrite64 (
  IN UINT32 Address,
  IN UINT64 Value
  )
{
  MmioWriteCount ();
  return (SaMmioWrite64 (Address, Value));
}

/**
  Write 32 bits to the Memory Mapped I/O space.

  @param[in] Offset      - Offset from the specified base address.
  @param[in] Value       - The value to write.

  @retval Nothing.
**/
UINT32
MrcOemMmioWrite32 (
  IN UINT32 Offset,
  IN UINT32 Value
  )
{
  (*((volatile UINT32 *) (Offset))) = Value;
  MmioWriteCount ();
  return (Value);
}

/**
  Write 16 bits to the Memory Mapped I/O space.

  @param[in] Offset      - Offset from the specified base address.
  @param[in] Value       - The value to write.

  @retval Nothing.
**/
UINT16
MrcOemMmioWrite16 (
  IN UINT32 Offset,
  IN UINT16 Value
  )
{
  (*((volatile UINT16 *) (Offset))) = Value;
  MmioWriteCount ();
  return (Value);
}

/**
  Write 8 bits to the Memory Mapped I/O space.

  @param[in] Offset      - Offset from the specified base address.
  @param[in] Value       - The value to write.

  @retval Nothing.
**/
UINT8
MrcOemMmioWrite8 (
  IN UINT32 Offset,
  IN UINT8  Value
  )
{
  (*((volatile UINT8 *) (Offset))) = Value;
  MmioWriteCount ();
  return (Value);
}

/**
  Gets a number from the CPU's random number generator.

  @param[in] Nothing

  @retval Random number or zero if random number is not generated or is invalid.
**/
static
UINT32
RandomNumber (
  void
  )
{
  UINT32 Random;

  //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Generating Random number...\n");
  // Assembly instruction to read CPU's random number generator
  // Instruction is only available 100k cycles after reset
  // rdrand eax
  // db 0Fh, 0C7h, 0F0h
#if defined __GNUC__  // GCC compiler
  __asm__ __volatile__ (
    "\n\t clc"
    "\n\t 1:"
    "\n\t .byte 0x0F, 0xC7, 0xF0"
    "\n\t movl %%eax, %[Random]"
    "\n\t jnc 1b"
    : [Random] "=m" (Random)
    );
#else //MSFT compiler
  ASM {
    clc
    tryAgain:
    _emit   0x0F
    _emit   0xC7
    _emit   0xF0
    mov     Random, eax
    jnc     tryAgain        ; CF will be set if valid number was generated
  }
#endif // __GNUC__
  //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Exiting Random number: %08Xh\n", Random);

  return (Random);
}

/**
  Generates a 32-bit random number.

  if Rand is NULL, then ASSERT().

  @param[out] Rand     Buffer pointer to store the 32-bit random value.

  @retval TRUE         Random number generated successfully.
  @retval FALSE        Failed to generate the random number.

**/
BOOLEAN
GetRandomNumber32 (
  OUT     UINT32                    *Rand
  )
{
  UINT32 Random;
  UINT32 Retry;

  Random = 0;
  /// Exclude zero case, although it is still valid, but not preferred for scrambler seed application
  for (Retry = 100000; ((Retry != 0) && (Random == 0)); --Retry) {
    Random = RandomNumber ();
  }

  *Rand = Random;

  if (Random == 0) {
    return FALSE;
  } else {
    return TRUE;
  }
}

/**
  Assembly code to read an MSR

  @param[in] Address

  @retval The MSR value.
**/
static
UINT64
AsmReadMsr (
  UINT32 Address
  )
{
#ifdef __GNUC__  // GCC compiler
  UINT32 LowData;
  UINT32 HighData;

  __asm__ __volatile__ (
    "rdmsr"
    : "=a" (LowData),   // %0
      "=d" (HighData)   // %1
    : "c"  (Address)    // %2
    );

  return (((UINT64) HighData) << 32) | LowData;
#else
  // Assembly instruction to read MSR
  union {
    UINT64 Data;
    UINT32 Data32[2];
  } Buffer;
  UINT32 DataEdx;
  UINT32 DataEax;

  ASM {
    mov     ecx, Address
    rdmsr
    mov     DataEax, eax
    mov     DataEdx, edx
  }
  Buffer.Data32[0] = DataEax;
  Buffer.Data32[1] = DataEdx;
  return (Buffer.Data);
#endif
}

/**
  Read an MSR

  @param[in] Address

  @retval The MSR value.
**/
UINT64
ReadMsr64 (
  UINT32 Address
  )
{
  return (AsmReadMsr (Address));
}

/**
  Assembly code to write an MSR

  @param[in] Address
  @param[in] Data

  @retval Nothing.
**/
static
void
AsmWriteMsr (
  UINT32 Address,
  UINT64 Data
  )
{
#ifdef __GNUC__  // GCC compiler
  UINT32 LowData;
  UINT32 HighData;

  LowData  = (UINT32) (Data);
  HighData = (UINT32) (Data >> 32);

  __asm__ __volatile__ (
    "wrmsr"
    :
    : "c" (Address),
      "a" (LowData),
      "d" (HighData)
    );
#else
  union {
    UINT64 Data;
    UINT32 Data32[2];
  } Buffer;
  UINT32 DataEdx;
  UINT32 DataEax;

  Buffer.Data = Data;
  DataEax = Buffer.Data32[0];
  DataEdx = Buffer.Data32[1];
  // Assembly instruction to read MSR
  ASM {
    mov     ecx, Address
    mov     eax, DataEax
    mov     edx, DataEdx
    wrmsr
  }
#endif
  return;
}

/**
  Write an MSR

  @param[in] Address
  @param[in] Data

  @retval Data written to MSR
**/
UINT64
WriteMsr64 (
  UINT32 Address,
  UINT64 Data
  )
{
  AsmWriteMsr (Address, Data);
  return Data;
}

/**
  Initialize GPIO

  @param[in]  MrcData - Include all MRC global data
**/
void
MrcOemGpioInit (
  MrcParameters *const  MrcData
  )
{
  const MrcInput  *Inputs;
  UINT32          PciEBaseAddress;

  Inputs          = &MrcData->Inputs;
  PciEBaseAddress = Inputs->PciEBaseAddress;
  MrcOemMmioRead16 (PciEBaseAddress + GetPcieDeviceAddress (0, PCI_DEVICE_NUMBER_PCH_LPC, PCI_FUNCTION_NUMBER_PCH_LPC, 0));
  // Initialize DRAM_RESET pin here if needed
}

/**
  Assert or deassert DRAM_RESET# pin; this is used in JEDEC Reset.

  @param[in] PciEBaseAddress  - PCI express base address.
  @param[in] ResetValue       - desired value of DRAM_RESET#. 1 - reset deasserted, 0 - reset asserted.
**/
void
MrcOemDramReset (
  UINT32 PciEBaseAddress,
  UINT32 ResetValue
  )
{
  UINT32  MmioBase;
  UINT32  PmCfg2;
  UINT32  Cfg2Offset;

  if (MrcGetPchGeneration () == ICL_PCH) {
    // Read PWRMBASE from PSF3 PMC space BAR0
    if (MrcGetPchSeries () == PCH_LP) {
      MmioBase = MrcOemMmioRead32 (PCH_PCR_ADDRESS (PID_PSF3, R_ICL_PCH_LP_PSF3_PCR_T0_SHDW_PMC_REG_BASE + R_PCH_PSFX_PCR_T0_SHDW_BAR0));
      if ((MrcCPUStepGet() & CPU_FAMILY_MASK) == cmEHL) {
        MmioBase = MrcOemMmioRead32 (PCH_PCR_ADDRESS (PID_PSF3, R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_PMC_REG_BASE + R_PCH_PSFX_PCR_T0_SHDW_BAR0));
      }
    } else if (MrcGetPchSeries () == PCH_H) {
      MmioBase = MrcOemMmioRead32 (PCH_PCR_ADDRESS (PID_PSF3, R_ICL_PCH_H_PSF3_PCR_T0_SHDW_PMC_REG_BASE + R_PCH_PSFX_PCR_T0_SHDW_BAR0));
    } else { // PCH-N
      MmioBase = MrcOemMmioRead32 (PCH_PCR_ADDRESS (PID_PSF3, R_ICL_PCH_N_PSF3_PCR_T0_SHDW_PMC_REG_BASE + R_PCH_PSFX_PCR_T0_SHDW_BAR0));
    }
    Cfg2Offset = R_PMC_PWRM_CFG2;
  } else {
    // Unknown PCH Type.
    MrcOemMmioWrite32 (0xFED15D10, 0xDEADBEEF);
    return;
  }
  // Set DRAM RESET# value via PCH register
  PmCfg2 = MrcOemMmioRead32 (MmioBase + Cfg2Offset);
  PmCfg2 &= ~(B_PMC_PWRM_CFG2_DRAM_RESET_CTL);
  PmCfg2 |= (ResetValue << 26);
  MrcOemMmioWrite32 (MmioBase + Cfg2Offset, PmCfg2);

  return;
}

/**
  Wait for at least the given number of nanoseconds.

  @param[in] MrcData   - Include all MRC global data.
  @param[in] DelayNs   - time to wait in [ns], up to 2^32 [ns] = 4.29 seconds

  @retval Nothing
**/
void
MrcOemDelayNs (
  IN MrcParameters *const MrcData,
  IN UINT32               DelayNs
  )
{

  UINT64             Start;
  volatile UINT64    Finish;
  UINT64             Now;
  BOOLEAN            Done;

  Start  = MrcOemGetCpuTimeNanoSec (MrcData);
  Finish = Start + DelayNs;
  Done   = FALSE;

  do {
    Now = MrcOemGetCpuTimeNanoSec (MrcData);
    if (Finish > Start) {
      if (Now >= Finish) {
        Done = TRUE;
      }
    } else {
      if ((Now < Start) && (Now >= Finish)) {
        Done = TRUE;
      }
    }
  } while (Done == FALSE);
}

/**
  Gets the current memory voltage (VDD).

  @param[in] GlobalData - Pointer to global MRC data struct.
  @param[in] DefaultVdd - Default Vdd for the given platform.

  @retval The current memory voltage (VDD), in millivolts. 0 means platform default.
**/
UINT32
GetMemoryVdd (
  IN VOID     *GlobalData,
  IN UINT32   DefaultVdd
  )
{
  MrcParameters   *MrcData;
  UINT32          CurrentVoltage;
  MrcData = (MrcParameters *) GlobalData;
  CurrentVoltage = DefaultVdd;
  return CurrentVoltage;
}

/**
  Sets the memory voltage (VDD) to the specified value.

  @param[in] GlobalData - Pointer to global MRC data struct.
  @param[in] DefaultVdd - Default Vdd for the given platform.
  @param[in] Voltage    - The new memory voltage to set.

  @retval The actual memory voltage (VDD), in millivolts, that is closest to what the caller passed in.
**/
UINT32
SetMemoryVdd (
  IN VOID     *GlobalData,
  IN UINT32   DefaultVdd,
  IN UINT32   Voltage
  )
{
  MrcParameters   *MrcData;
  MrcData = (MrcParameters *) GlobalData;
  return Voltage;
}

/**
  This function is used by the Mini-BIOS to do dedicated task during the MRC.

  @param[in]  MrcData          - Pointer to MRC global data.
  @param[in]  OemStatusCommand - A command that indicates the task to perform.
  @param[out] Status           - Pointer to status varible to updated as needed.

  @retval The status of the task.
**/
MrcStatus
CheckPoint (
  IN MrcParameters        *MrcData,
  IN MrcOemStatusCommand  OemStatusCommand,
  OUT MrcStatus           *Status
  )
{

  return (mrcSuccess);
}

/**
  This function display on port 80 number.
  It can be different debug interface.
  This function can be use for any debug ability according to OEM requirements.

  @param[in] MrcData            - Mrc Global Data
  @param[in] DisplayDebugNumber - the number to display on port 80.

  @retval Nothing
**/
void
MrcOemDebugHook (
  IN MrcParameters *MrcData,
  IN UINT16        DisplayDebugNumber
  )
{
  MrcDebug  *Debug;
  UINT16    BreakCmos;
  BOOLEAN   MessagePrinted;

  Debug                          = &MrcData->Outputs.Debug;
  Debug->PostCode[MRC_POST_CODE] = DisplayDebugNumber;
  MrcOemOutPort16 (0x80, DisplayDebugNumber);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Post Code: %Xh\n", DisplayDebugNumber);

  PostCode ((UINT32) DisplayDebugNumber);

  // Put the Port80 code also here:
  MrcWriteCR (MrcData, BIOS_POST_CODE_PCU_REG, DisplayDebugNumber);

  // Check if we should break on this post code.
  MessagePrinted = FALSE;
  do {
    BreakCmos = (RtcRead (MRC_POST_CODE_HIGH_BYTE_ADDR) << 8) | RtcRead (MRC_POST_CODE_LOW_BYTE_ADDR);
    if ((DisplayDebugNumber == BreakCmos) && !MessagePrinted) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "------------------------------------------\n");
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "-- Stopped on CMOS POST code breakpoint --\n");
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "------------------------------------------\n");
      MessagePrinted = TRUE;
    }
  } while (DisplayDebugNumber == BreakCmos);

  return;
}

#if (defined MEMORY_DOWN_SUPPORT && (MEMORY_DOWN_SUPPORT > 0))

/******************************************************************************
  Memory down configuration code starts here.
  Add SPD, and channel/slot population settings here.

  Even though this is a memory down configuration, the MRC needs to know how
  the memory appears to the controller, so indicate here which channels are
  populated. Also, the MRC needs to know which slots are valid, even though
  there are technically no physical slots in a memory down configuration.
  The MRC also needs a valid SPD data for the configuration.
******************************************************************************/

/// For LPDDR4 boards, we have a dual channel, single slot configuration
/// with the same memory configuration in each channel.
const MemorySlotStatus Lpddr4SlotStatus[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL] = {
  MEMORY_DOWN_ONLY,                     ///< Channel 0, Slot 0
  MEMORY_ABSENT,                        ///< Channel 0, Slot 1
  MEMORY_DOWN_ONLY,                     ///< Channel 1, Slot 0
  MEMORY_ABSENT,                        ///< Channel 1, Slot 1
};

// LPDDR4X 432b 16Gb die, QDP 2x16
// Samsung K3UH7H70MM-JGCJ
// 3733, 32-34-34-79
// 2 ranks per channel, 1 SDRAMs per rank, 4x16Gb = 8GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4xQdp16Gb432bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x11,                                 ///< 1   SPD Revision 1.1
  0x11,                                 ///< 2   DRAM Type: LPDDR4x SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x16,                                 ///< 4   8 Banks, no bank groups, 16 Gb SDRAM density
  0x21,                                 ///< 5   16 Row bits, 10 Column bits
  0xB4,                                 ///< 6   Non-Monolithic DRAM Device, 4 dies, 2 Channels per die, Signal Loading not specified
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x0A,                                 ///< 12  Module Organization: 2 Ranks, x16 Device Width per Channel
  0x22,                                 ///< 13  Module Memory Bus width: 2 Channels, 32 bits channel width, no ECC
  0x00,                                 ///< 14  Module Thermal Sensor: none
  0x00,                                 ///< 15  Extended Module Type: Reserved
  0x48,                                 ///< 16  Signal Loading: Data/Strobe/Mask: 2 loads, CAC: 2 loads, CS: 1 load
  0x00,                                 ///< 17  MTB = 0.125ns, FTB = 1 ps
  0x05,                                 ///< 18  tCKAVGmin = 0.536 ns (LPDDR4-3733)
  0x0F,                                 ///< 19  tCKAVGmax = 1.875 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x54,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20
  0x01,                                 ///< 22  CAS Latencies supported (Third Byte) : 32
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x8A,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.14 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xC0,                                 ///< 29  tRFCab = 280 ns (16 Gb dual-channel die)
  0x08,                                 ///< 30  tRFCab MSB
  0x60,                                 ///< 31  tRFCpb = 140 ns (16 Gb dual-channel die)
  0x04,                                 ///< 32  tRFCpb MSB
  0, 0, 0, 0, 0, 0, 0,                  ///< 33 - 39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 40 - 49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 60 - 69
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 70 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 110 - 119
  0x00,                                 ///< 120 FTB for Row precharge time per bank (tRPpb) = 18 ns
  0x00,                                 ///< 121 FTB for Row precharge time for all banks (tRPab) = 21 ns
  0x00,                                 ///< 122 FTB for Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0x92,                                 ///< 123 FTB for tAAmin = 17.14 ns (FTB = -0.11 ns)
  0x00,                                 ///< 124 FTB for tCKAVGmax = 1.875 ns (FTB = 0 ns)
  0xA7,                                 ///< 125 FTB for tCKAVGmin = 0.536 ns (FTB = -.089 ns) (LPDDR4-3733)
  0x00,                                 ///< 126 CRC A
  0x00,                                 ///< 127 CRC B
  0, 0,                                 ///< 128 - 129
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 130 - 139
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 140 - 149
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 150 - 159
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 160 - 169
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 170 - 179
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 180 - 189
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 190 - 199
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 200 - 209
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 210 - 219
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 220 - 229
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 230 - 239
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 240 - 249
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 250 - 259
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 260 - 269
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 270 - 279
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 280 - 289
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 290 - 299
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 300 - 309
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 310 - 319
  0x00,                                 ///< 320 Module Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 321 Module Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 322 Module Manufacturing Location
  0x00,                                 ///< 323 Module Manufacturing Date Year
  0x00,                                 ///< 324 Module Manufacturing Date Week
  0x43,                                 ///< 325 Module Serial Number A
  0x00,                                 ///< 326 Module Serial Number B
  0x00,                                 ///< 327 Module Serial Number C
  0x00,                                 ///< 328 Module Serial Number D
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 329 - 333 Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 334 - 338 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 339 - 343 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 344 - 348 Module Part Number
  0x00,                                 ///< 349 Module Revision Code
  0x80,                                 ///< 350 DRAM Manufacturer ID Code, Least Significant Byte
  0xCE,                                 ///< 351 DRAM Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 352 DRAM Stepping
  0, 0, 0, 0, 0, 0, 0,                  ///< 353 - 359
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 360 - 369
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 370 - 379
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 380 - 389
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 390 - 399
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 400 - 409
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 410 - 419
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 420 - 429
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 430 - 439
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 440 - 449
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 450 - 459
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 460 - 469
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 470 - 479
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 480 - 489
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 490 - 499
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 500 - 509
  0, 0                                  ///< 510 - 511
};

// LPDDR4 200b 8Gb die, DDP, 2 channels per die, x16
// Samsung K4F6E304Hx-MGCJ
// or Hynix H9HCNNNBUUxLHR-NMx
// or Micron MT53B512M32D2NP-053
// 3733, 32-34-34-79
// 2 ranks per channel, 2 SDRAMs per channel, 2x2x8Gb = 4GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4Ddp8Gb200bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x11,                                 ///< 1   SPD Revision 1.1
  0x10,                                 ///< 2   DRAM Type: LPDDR4 SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x19,                                 ///< 5   15 Row bits, 10 Column bits
  0x94,                                 ///< 6   Non-Monolithic DRAM Device, 2 dies, 2 Channels per die, Signal Loading not specified
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x0A,                                 ///< 12  Module Organization: 2 Ranks, x16 Device Width per Channel
  0x22,                                 ///< 13  Module Memory Bus width: 2 Channels, 32 bits channel width, no ECC
  0x00,                                 ///< 14  Module Thermal Sensor: none
  0x00,                                 ///< 15  Extended Module Type: Reserved
  0x00,                                 ///< 16  Signal Loading: not specified
  0x00,                                 ///< 17  MTB = 0.125ns, FTB = 1 ps
  0x05,                                 ///< 18  tCKAVGmin = 0.536 ns (LPDDR4-3733)
  0x0F,                                 ///< 19  tCKAVGmax = 1.875 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x54,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20
  0x01,                                 ///< 22  CAS Latencies supported (Third Byte) : 32
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x8A,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.14 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xA0,                                 ///< 29  tRFCab = 180 ns (8 Gb dual-channel die)
  0x05,                                 ///< 30  tRFCab MSB
  0xD0,                                 ///< 31  tRFCpb = 90 ns (8 Gb dual-channel die)
  0x02,                                 ///< 32  tRFCpb MSB
  0, 0, 0, 0, 0, 0, 0,                  ///< 33 - 39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 40 - 49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 60 - 69
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 70 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 110 - 119
  0x00,                                 ///< 120 FTB for Row precharge time per bank (tRPpb) = 18 ns
  0x00,                                 ///< 121 FTB for Row precharge time for all banks (tRPab) = 21 ns
  0x00,                                 ///< 122 FTB for Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0x92,                                 ///< 123 FTB for tAAmin = 17.14 ns
  0x00,                                 ///< 124 FTB for tCKAVGmax = 1.875 ns
  0xA7,                                 ///< 125 FTB for tCKAVGmin = 0.536 ns (LPDDR4-3733)
  0x00,                                 ///< 126 CRC A
  0x00,                                 ///< 127 CRC B
  0, 0,                                 ///< 128 - 129
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 130 - 139
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 140 - 149
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 150 - 159
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 160 - 169
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 170 - 179
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 180 - 189
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 190 - 199
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 200 - 209
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 210 - 219
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 220 - 229
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 230 - 239
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 240 - 249
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 250 - 259
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 260 - 269
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 270 - 279
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 280 - 289
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 290 - 299
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 300 - 309
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 310 - 319
  0x00,                                 ///< 320 Module Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 321 Module Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 322 Module Manufacturing Location
  0x00,                                 ///< 323 Module Manufacturing Date Year
  0x00,                                 ///< 324 Module Manufacturing Date Week
  0x20,                                 ///< 325 Module Serial Number A
  0x00,                                 ///< 326 Module Serial Number B
  0x00,                                 ///< 327 Module Serial Number C
  0x00,                                 ///< 328 Module Serial Number D
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 329 - 333 Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 334 - 338 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 339 - 343 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 344 - 348 Module Part Number
  0x00,                                 ///< 349 Module Revision Code
  0x00,                                 ///< 350 DRAM Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 351 DRAM Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 352 DRAM Stepping
  0, 0, 0, 0, 0, 0, 0,                  ///< 353 - 359
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 360 - 369
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 370 - 379
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 380 - 389
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 390 - 399
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 400 - 409
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 410 - 419
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 420 - 429
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 430 - 439
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 440 - 449
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 450 - 459
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 460 - 469
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 470 - 479
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 480 - 489
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 490 - 499
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 500 - 509
  0, 0                                  ///< 510 - 511
};

// LPDDR4X 556b 8Gb die, QDP, 1 channel per die, x16
// Micron MT53D512M64D4RQ-053
// 3733, 32-34-34-79
// 1 rank per channel, 1 SDRAMs per channel, 1x4x8Gb = 4GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4xQdp8Gb556bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x11,                                 ///< 1   SPD Revision 1.1
  0x11,                                 ///< 2   DRAM Type: LPDDR4x SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x21,                                 ///< 5   16 Row bits, 10 Column bits
  0xB0,                                 ///< 6   Non-Monolithic DRAM Device, 4 dies, 1 Channels per die, Signal Loading not specified
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x02,                                 ///< 12  Module Organization: 1 Ranks, x16 Device Width per Channel
  0x22,                                 ///< 13  Module Memory Bus width: 2 Channels, 32 bits channel width, no ECC
  0x00,                                 ///< 14  Module Thermal Sensor: none
  0x00,                                 ///< 15  Extended Module Type: Reserved
  0x00,                                 ///< 16  Signal Loading: Not Specific
  0x00,                                 ///< 17  MTB = 0.125ns, FTB = 1 ps
  0x05,                                 ///< 18  tCKAVGmin = 0.536 ns (LPDDR4-3733)
  0x0F,                                 ///< 19  tCKAVGmax = 1.875 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x54,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20
  0x01,                                 ///< 22  CAS Latencies supported (Third Byte) : 32
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x8A,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.14 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xC0,                                 ///< 29  tRFCab = 280 ns (16 Gb dual-channel die)
  0x08,                                 ///< 30  tRFCab MSB
  0x60,                                 ///< 31  tRFCpb = 140 ns (16 Gb dual-channel die)
  0x04,                                 ///< 32  tRFCpb MSB
  0, 0, 0, 0, 0, 0, 0,                  ///< 33 - 39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 40 - 49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 60 - 69
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 70 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 110 - 119
  0x00,                                 ///< 120 FTB for Row precharge time per bank (tRPpb) = 18 ns
  0x00,                                 ///< 121 FTB for Row precharge time for all banks (tRPab) = 21 ns
  0x00,                                 ///< 122 FTB for Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0x92,                                 ///< 123 FTB for tAAmin = 17.14 ns (FTB = -0.11 ns)
  0x00,                                 ///< 124 FTB for tCKAVGmax = 1.875 ns (FTB = 0 ns)
  0xA7,                                 ///< 125 FTB for tCKAVGmin = 0.536 ns (FTB = -.089 ns) (LPDDR4-3733)
  0x00,                                 ///< 126 CRC A
  0x00,                                 ///< 127 CRC B
  0, 0,                                 ///< 128 - 129
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 130 - 139
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 140 - 149
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 150 - 159
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 160 - 169
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 170 - 179
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 180 - 189
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 190 - 199
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 200 - 209
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 210 - 219
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 220 - 229
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 230 - 239
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 240 - 249
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 250 - 259
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 260 - 269
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 270 - 279
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 280 - 289
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 290 - 299
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 300 - 309
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 310 - 319
  0x00,                                 ///< 320 Module Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 321 Module Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 322 Module Manufacturing Location
  0x00,                                 ///< 323 Module Manufacturing Date Year
  0x00,                                 ///< 324 Module Manufacturing Date Week
  0x56,                                 ///< 325 Module Serial Number A
  0x00,                                 ///< 326 Module Serial Number B
  0x00,                                 ///< 327 Module Serial Number C
  0x00,                                 ///< 328 Module Serial Number D
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 329 - 333 Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 334 - 338 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 339 - 343 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 344 - 348 Module Part Number
  0x00,                                 ///< 349 Module Revision Code
  0x00,                                 ///< 350 DRAM Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 351 DRAM Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 352 DRAM Stepping
  0, 0, 0, 0, 0, 0, 0,                  ///< 353 - 359
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 360 - 369
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 370 - 379
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 380 - 389
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 390 - 399
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 400 - 409
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 410 - 419
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 420 - 429
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 430 - 439
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 440 - 449
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 450 - 459
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 460 - 469
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 470 - 479
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 480 - 489
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 490 - 499
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 500 - 509
  0, 0                                  ///< 510 - 511
};

// LPDDR4X 200b 8Gb die, DDP, 1 channel per die, x16
// Hynix H9HCNNNBKMMLHR-NEE
// Micron MT53D512M32D2NP-046
// 4267, 36-39-39-90
// 1 rank per channel, 2 SDRAMs per channel, 2x2x8Gb = 4GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4xDdp8Gb200bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x11,                                 ///< 1   SPD Revision 1.1
  0x11,                                 ///< 2   DRAM Type: LPDDR4X SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x21,                                 ///< 5   16 Row bits, 10 Column bits
  0x90,                                 ///< 6   Non-Monolithic DRAM Device, 2 dies, 1 Channel per die, Signal Loading not specified
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x02,                                 ///< 12  Module Organization: 1 Rank, x16 Device Width per Channel
  0x22,                                 ///< 13  Module Memory Bus width: 2 Channels, 32 bits channel width, no ECC
  0x00,                                 ///< 14  Module Thermal Sensor: none
  0x00,                                 ///< 15  Extended Module Type: Reserved
  0x00,                                 ///< 16  Signal Loading: not specified
  0x00,                                 ///< 17  MTB = 0.125ns, FTB = 1 ps
  0x04,                                 ///< 18  tCKAVGmin = 0.469 ns (LPDDR4-4267)
  0x0F,                                 ///< 19  tCKAVGmax = 1.875 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x54,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20
  0x05,                                 ///< 22  CAS Latencies supported (Third Byte) : 36, 32
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x87,                                 ///< 24  Minimum CAS Latency (tAAmin) = 16.875 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xC0,                                 ///< 29  tRFCab = 280 ns (8 Gb single-channel die)
  0x08,                                 ///< 30  tRFCab MSB
  0x60,                                 ///< 31  tRFCpb = 140 ns (8 Gb single-channel die)
  0x04,                                 ///< 32  tRFCpb MSB
  0, 0, 0, 0, 0, 0, 0,                  ///< 33 - 39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 40 - 49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 60 - 69
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 70 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 110 - 119
  0x00,                                 ///< 120 FTB for Row precharge time per bank (tRPpb) = 18 ns
  0x00,                                 ///< 121 FTB for Row precharge time for all banks (tRPab) = 21 ns
  0x00,                                 ///< 122 FTB for Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0x00,                                 ///< 123 FTB for tAAmin = 16.875 ns
  0x00,                                 ///< 124 FTB for tCKAVGmax = 1.875 ns
  0xE1,                                 ///< 125 FTB for tCKAVGmin = 0.469 ns (LPDDR4-4267)
  0x00,                                 ///< 126 CRC A
  0x00,                                 ///< 127 CRC B
  0, 0,                                 ///< 128 - 129
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 130 - 139
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 140 - 149
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 150 - 159
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 160 - 169
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 170 - 179
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 180 - 189
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 190 - 199
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 200 - 209
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 210 - 219
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 220 - 229
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 230 - 239
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 240 - 249
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 250 - 259
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 260 - 269
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 270 - 279
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 280 - 289
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 290 - 299
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 300 - 309
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 310 - 319
  0x00,                                 ///< 320 Module Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 321 Module Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 322 Module Manufacturing Location
  0x00,                                 ///< 323 Module Manufacturing Date Year
  0x00,                                 ///< 324 Module Manufacturing Date Week
  0x20,                                 ///< 325 Module ID: Module Serial Number
  0x00,                                 ///< 326 Module Serial Number B
  0x00,                                 ///< 327 Module Serial Number C
  0x00,                                 ///< 328 Module Serial Number D
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 329 - 333 Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 334 - 338 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 339 - 343 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 344 - 348 Module Part Number
  0x00,                                 ///< 349 Module Revision Code
  0x00,                                 ///< 350 DRAM Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 351 DRAM Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 352 DRAM Stepping
  0, 0, 0, 0, 0, 0, 0,                  ///< 353 - 359
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 360 - 369
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 370 - 379
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 380 - 389
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 390 - 399
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 400 - 409
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 410 - 419
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 420 - 429
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 430 - 439
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 440 - 449
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 450 - 459
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 460 - 469
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 470 - 479
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 480 - 489
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 490 - 499
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 500 - 509
  0, 0                                  ///< 510 - 511
};

// LPDDR4X 200b 8Gb die, QDP, 1 channel per die, x16
// Hynix H9HCNNNCPMMLHR-NEE
// Micron MT53D1024M32D4NP-046
// 4267, 36-39-39-90
// 2 ranks per channel, 2 SDRAMs per channel, 2x4x8Gb = 8GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4xQdp8Gb200bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x11,                                 ///< 1   SPD Revision 1.1
  0x11,                                 ///< 2   DRAM Type: LPDDR4x SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x21,                                 ///< 5   16 Row bits, 10 Column bits
  0xB0,                                 ///< 6   Non-Monolithic DRAM Device, 4 dies, 1 Channel per die, Signal Loading not specified
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x0A,                                 ///< 12  Module Organization: 2 Ranks, x16 Device Width per Channel
  0x22,                                 ///< 13  Module Memory Bus width: 2 Channels, 32 bits channel width, no ECC
  0x00,                                 ///< 14  Module Thermal Sensor: none
  0x00,                                 ///< 15  Extended Module Type: Reserved
  0x00,                                 ///< 16  Signal Loading: not specified
  0x00,                                 ///< 17  MTB = 0.125ns, FTB = 1 ps
  0x04,                                 ///< 18  tCKAVGmin = 0.469 ns (LPDDR4-4267)
  0x0F,                                 ///< 19  tCKAVGmax = 1.875 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x54,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20
  0x05,                                 ///< 22  CAS Latencies supported (Third Byte) : 36, 32
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x87,                                 ///< 24  Minimum CAS Latency (tAAmin) = 16.875 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xC0,                                 ///< 29  tRFCab = 280 ns (8 Gb single-channel die)
  0x08,                                 ///< 30  tRFCab MSB
  0x60,                                 ///< 31  tRFCpb = 140 ns (8 Gb single-channel die)
  0x04,                                 ///< 32  tRFCpb MSB
  0, 0, 0, 0, 0, 0, 0,                  ///< 33 - 39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 40 - 49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 60 - 69
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 70 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 110 - 119
  0x00,                                 ///< 120 FTB for Row precharge time per bank (tRPpb) = 18 ns
  0x00,                                 ///< 121 FTB for Row precharge time for all banks (tRPab) = 21 ns
  0x00,                                 ///< 122 FTB for Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0x00,                                 ///< 123 FTB for tAAmin = 16.875 ns
  0x00,                                 ///< 124 FTB for tCKAVGmax = 1.875 ns
  0xE1,                                 ///< 125 FTB for tCKAVGmin = 0.469 ns (LPDDR4-4267)
  0x00,                                 ///< 126 CRC A
  0x00,                                 ///< 127 CRC B
  0, 0,                                 ///< 128 - 129
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 130 - 139
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 140 - 149
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 150 - 159
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 160 - 169
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 170 - 179
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 180 - 189
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 190 - 199
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 200 - 209
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 210 - 219
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 220 - 229
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 230 - 239
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 240 - 249
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 250 - 259
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 260 - 269
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 270 - 279
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 280 - 289
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 290 - 299
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 300 - 309
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 310 - 319
  0x00,                                 ///< 320 Module Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 321 Module Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 322 Module Manufacturing Location
  0x00,                                 ///< 323 Module Manufacturing Date Year
  0x00,                                 ///< 324 Module Manufacturing Date Week
  0x20,                                 ///< 325 Module ID: Module Serial Number
  0x00,                                 ///< 326 Module Serial Number B
  0x00,                                 ///< 327 Module Serial Number C
  0x00,                                 ///< 328 Module Serial Number D
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 329 - 333 Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 334 - 338 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 339 - 343 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 344 - 348 Module Part Number
  0x00,                                 ///< 349 Module Revision Code
  0x00,                                 ///< 350 DRAM Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 351 DRAM Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 352 DRAM Stepping
  0, 0, 0, 0, 0, 0, 0,                  ///< 353 - 359
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 360 - 369
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 370 - 379
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 380 - 389
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 390 - 399
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 400 - 409
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 410 - 419
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 420 - 429
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 430 - 439
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 440 - 449
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 450 - 459
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 460 - 469
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 470 - 479
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 480 - 489
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 490 - 499
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 500 - 509
  0, 0                                  ///< 510 - 511
};

// LPDDR4X 200b 16Gb die, DDP, 2 channels per die, x16
// Samsung K4UBE3D4Ax-MGCL
// 4267, 36-39-39-90
// 2 ranks per channel, 2 SDRAMs per channel, 2x2x16Gb = 8GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4xDdp16Gb200bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x11,                                 ///< 1   SPD Revision 1.1
  0x11,                                 ///< 2   DRAM Type: LPDDR4x SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x16,                                 ///< 4   8 Banks, no bank groups, 16 Gb SDRAM density
  0x21,                                 ///< 5   16 Row bits, 10 Column bits
  0x94,                                 ///< 6   Non-Monolithic DRAM Device, 2 dies, 2 Channels per die, Signal Loading not specified
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x0A,                                 ///< 12  Module Organization: 2 Ranks, x16 Device Width per Channel
  0x22,                                 ///< 13  Module Memory Bus width: 2 Channels, 32 bits channel width, no ECC
  0x00,                                 ///< 14  Module Thermal Sensor: none
  0x00,                                 ///< 15  Extended Module Type: Reserved
  0x00,                                 ///< 16  Signal Loading: not specified
  0x00,                                 ///< 17  MTB = 0.125ns, FTB = 1 ps
  0x04,                                 ///< 18  tCKAVGmin = 0.469 ns (LPDDR4-4267)
  0x0F,                                 ///< 19  tCKAVGmax = 1.875 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x54,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20
  0x05,                                 ///< 22  CAS Latencies supported (Third Byte) : 36, 32
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x8C,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.5 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xC0,                                 ///< 29  tRFCab = 280 ns (16 Gb dual-channel die)
  0x08,                                 ///< 30  tRFCab MSB
  0x60,                                 ///< 31  tRFCpb = 140 ns (16 Gb dual-channel die)
  0x04,                                 ///< 32  tRFCpb MSB
  0, 0, 0, 0, 0, 0, 0,                  ///< 33 - 39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 40 - 49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 60 - 69
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 70 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 110 - 119
  0x00,                                 ///< 120 FTB for Row precharge time per bank (tRPpb) = 18 ns
  0x00,                                 ///< 121 FTB for Row precharge time for all banks (tRPab) = 21 ns
  0x00,                                 ///< 122 FTB for Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0x00,                                 ///< 123 FTB for tAAmin = 17.5 ns
  0x00,                                 ///< 124 FTB for tCKAVGmax = 1.875 ns
  0xE1,                                 ///< 125 FTB for tCKAVGmin = 0.469 ns (LPDDR4-4267)
  0x00,                                 ///< 126 CRC A
  0x00,                                 ///< 127 CRC B
  0, 0,                                 ///< 128 - 129
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 130 - 139
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 140 - 149
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 150 - 159
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 160 - 169
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 170 - 179
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 180 - 189
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 190 - 199
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 200 - 209
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 210 - 219
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 220 - 229
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 230 - 239
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 240 - 249
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 250 - 259
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 260 - 269
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 270 - 279
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 280 - 289
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 290 - 299
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 300 - 309
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 310 - 319
  0x00,                                 ///< 320 Module Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 321 Module Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 322 Module Manufacturing Location
  0x00,                                 ///< 323 Module Manufacturing Date Year
  0x00,                                 ///< 324 Module Manufacturing Date Week
  0x20,                                 ///< 325 Module ID: Module Serial Number
  0x00,                                 ///< 326 Module Serial Number B
  0x00,                                 ///< 327 Module Serial Number C
  0x00,                                 ///< 328 Module Serial Number D
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 329 - 333 Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 334 - 338 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 339 - 343 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 344 - 348 Module Part Number
  0x00,                                 ///< 349 Module Revision Code
  0x00,                                 ///< 350 DRAM Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 351 DRAM Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 352 DRAM Stepping
  0, 0, 0, 0, 0, 0, 0,                  ///< 353 - 359
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 360 - 369
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 370 - 379
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 380 - 389
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 390 - 399
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 400 - 409
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 410 - 419
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 420 - 429
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 430 - 439
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 440 - 449
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 450 - 459
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 460 - 469
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 470 - 479
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 480 - 489
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 490 - 499
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 500 - 509
  0, 0                                  ///< 510 - 511
};

/**
  Copies information from the Memory Down SPD structure to the SPD Input structure
  in the Host structure.

  Setting the SpdBaseAddress to zero means this slot has a memory down configuration.
  For systems that have both memory down and slots, it is recommended to have the
  memory down in the slot position farthest from the controller.

  @param[in, out] MrcData - MRC Host Input structure.
  @param[in]      SpdIn   - Pointer to the Memory Down SPD structure to copy.
  @param[in]      Slot    - Pointer to the Memory Down MemorySlotStatus structure.
  @param[in]      SpdSize - Size of the SPD structure to limit MemoryCpy.

  @retval - Nothing.
**/
void
CopyMemoryDownSpd (
  IN OUT MrcParameters *const    MrcData,
  IN     const UINT8             *SpdIn[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL],
  IN     const MemorySlotStatus  *Slot,
  IN     UINT16                  SpdSize
  )
{
  MrcInput  *Inputs;
  MrcDimmIn *DimmIn;
  MrcOutput *Outputs;
  MrcDebug  *Debug;
  UINT8     Channel;
  UINT8     Dimm;

  if (SpdIn == NULL || Slot == NULL || SpdSize == 0) {
    return;
  }

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++, Slot++) {
      DimmIn = &Inputs->Controller[0].Channel[Channel].Dimm[Dimm];
      switch (*Slot) {
      case MEMORY_DOWN_ONLY:
        DimmIn->SpdAddress  = 0;
        // Check user request to disable DIMM/rank pair.
        if (DimmIn->Status != DIMM_DISABLED) {
          DimmIn->Status = DIMM_ENABLED;
          MrcOemMemoryCpy ((UINT8 *) &DimmIn->Spd.Data, (UINT8 *) SpdIn[Channel][Dimm], SpdSize);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Memory down present on channel %u, dimm %u\n", Channel, Dimm);
        } else {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Memory down absent on channel %u, dimm %u\n", Channel, Dimm);
        }
        break;

      case MEMORY_ABSENT:
        DimmIn->Status      = DIMM_DISABLED;
        DimmIn->SpdAddress  = 0;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Memory down absent on channel %u, dimm %u\n", Channel, Dimm);
        break;

      case MEMORY_SLOT_ONLY:
      default:
        break;
      }
    }
  }

  return;
}

/**
  Enables Memory Down support and sets SPD data for all DIMMs needing support.

  @param[in] MrcData    - MRC global data structure.
  @param[in] BoardId    - The ID of the board.
  @param[in] FabId      - The FAB ID of the board.
  @param[in] BomId      - The BOM ID of the board.
  @param[in] SpdPresent - SPD is present or memory is down.

  @retval Nothing
**/
void
EnableMemoryDown (
  IN MrcParameters *const MrcData,
  IN const UINT16         BoardId,
  IN UINT16               FabId,
  IN UINT16               BomId,
  IN const BOOLEAN        SpdPresent
  )
{
  MrcInput                *Inputs;
  const UINT8             *SpdIn[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
  const MemorySlotStatus  *Slot;
  UINT16                  SpdSize;
  UINT8                   Channel;
  UINT8                   Dimm;
  UINT32                  CpuModel;

  Inputs  = &MrcData->Inputs;
  Channel = 0;
  Dimm    = 0;
  SpdSize = 0;
  Slot    = NULL;
  CpuModel = (MrcCPUStepGet() & CPU_FAMILY_MASK);

  switch (BoardId) {
    // Add additional boards that support memory down here.
    case BoardIdIclULp4Type4:
    case BoardIdIclULp4Type4Tcpd:
    case BoardIdIclULp4Type3:
    case BoardIdIclYLp4Type4:
    case BoardIdIclYLp4Type4Tlc:
    case BoardIdIclYLp4PnpType4:
    case BoardIdIclYLp4PnpType4Tlc:
      if (!SpdPresent) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            if (BomId == BomIdIclLp4SolderDownLp4x) {
              SpdIn[Channel][Dimm] = mLpddr4xQdp8Gb200bSpd;
            } else {
              SpdIn[Channel][Dimm] = mLpddr4Ddp8Gb200bSpd;
            }
          }
        }
        Slot = (const MemorySlotStatus *) &Lpddr4SlotStatus[0][0];
        SpdSize = sizeof (mLpddr4Ddp8Gb200bSpd);
      }
      break;

    case BoardIdIclYRvpC:
      // No SpdPresent indication; always use internal SPD
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          SpdIn[Channel][Dimm] = mLpddr4xQdp16Gb432bSpd;
        }
      }
      Slot = (const MemorySlotStatus *) &Lpddr4SlotStatus[0][0];
      SpdSize = sizeof (mLpddr4xQdp16Gb432bSpd);
      break;


    case BoardIdIclUSds:
      // SDS doesn't have SpdPresent indication; always use internal SPD
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          if ((BoardId == BoardIdIclUSds) && ((FabId == FabIdIclUSdsLp4xFabId2) || (FabId == FabIdIclUSdsLp4xFabId3))) {
            SpdIn[Channel][Dimm] = mLpddr4xDdp8Gb200bSpd;   // SDS Fab2/3 uses LP4X
          } else {
            SpdIn[Channel][Dimm] = mLpddr4Ddp8Gb200bSpd;
          }
        }
      }
      Slot = (const MemorySlotStatus *) &Lpddr4SlotStatus[0][0];
      SpdSize = sizeof (mLpddr4Ddp8Gb200bSpd);
      break;

    case BoardIdKslILp4Type4Rvp:
      if (!SpdPresent) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            SpdIn[Channel][Dimm] = mLpddr4xDdp16Gb200bSpd;
          }
        }
        Slot = (const MemorySlotStatus *) &Lpddr4SlotStatus[0][0];
        SpdSize = sizeof (mLpddr4xDdp16Gb200bSpd);
      }
      break;

    case BoardIdIclYNRvp:
      if (!SpdPresent) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            SpdIn[Channel][Dimm] = mLpddr4xQdp8Gb556bSpd;
          }
        }
        Slot = (const MemorySlotStatus *) &Lpddr4SlotStatus[0][0];
        SpdSize = sizeof (mLpddr4xQdp8Gb556bSpd);
      }
      break;

    case BoardIdIclUNRvp:
    case BoardIdEhlLp4xType3Crb:
      if (!SpdPresent) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            if (BomId == BomIdIclUNLp4xSingleRank) {
              SpdIn[Channel][Dimm] = mLpddr4xDdp8Gb200bSpd;  // Single-rank memory
            } else if (BomId == BomIdEhlLp4xType4Main) {
              SpdIn[Channel][Dimm] = mLpddr4xDdp8Gb200bSpd;
            } else {
              SpdIn[Channel][Dimm] = mLpddr4xDdp16Gb200bSpd;
            }
          }
        }
        Slot = (const MemorySlotStatus *) &Lpddr4SlotStatus[0][0];
        SpdSize = sizeof (mLpddr4xDdp16Gb200bSpd);
      }
      break;

    // The default case means the board ID was not recognized.  Instead
    // we set Slot = NULL thus forcing us to read from the SPD.
    default:
      Slot  = NULL;
  }

  if (CpuModel == cmEHL) {
    switch (BoardId) {
      // Add additional boards that support memory down here.
      case BoardIdEhlLp4xType4Erb:
      case BoardIdEhlLp4xType4Rvp1:
      case BoardIdEhlLp4xType3Crb:
      case BoardIdJslLp4xErb:
      case BoardIdJslLp4xType4Rvp1:
      case 0x23:
        if (!SpdPresent) {
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
              SpdIn[Channel][Dimm] = mLpddr4xDdp8Gb200bSpd;
            }
          }
          Slot = (const MemorySlotStatus *) &Lpddr4SlotStatus[0][0];
          SpdSize = sizeof (mLpddr4xDdp8Gb200bSpd);
        }
        break;
      // The default case means the board ID was not recognized.  Instead
      // we set Slot = NULL thus forcing us to read from the SPD.
      default:
        Slot  = NULL;
    }
  }


  CopyMemoryDownSpd (MrcData, SpdIn, Slot, SpdSize);

  return;
}
#endif // MEMORY_DOWN_SUPPORT

/**
  Initialize the board-specific CMD/CTL/CLK and DQ/DQS mapping for LPDDR.

  @param[in, out] MrcData - MRC global data structure.
  @param[in]      BoardId - The ID of the board.
  @param[in]      FabId   - The FAB ID of the board.
  @param[in]      BomId   - The BOM ID of the board.
**/
void
MrcOemLpddrBoardMapping (
  IN MrcParameters *const MrcData,
  IN UINT16              BoardId,
  IN UINT16              FabId,
  IN UINT16              BomId
  )
{
  MrcDebug        *Debug;
  MrcInput        *Inputs;
  MrcControllerIn *ControllerIn;
  MrcChannelIn    *ChannelIn0;
  MrcChannelIn    *ChannelIn1;
  UINT8           *DqByteMapCh0;
  UINT8           *DqByteMapCh1;
  UINT8           *DqsMapCpu2Dram;
  UINT8           *DqsMapCpu2DramCh0;
  UINT8           *DqsMapCpu2DramCh1;
  UINT8           *DqMapCpu2DramCh0;
  UINT8           *DqMapCpu2DramCh1;
  UINT32          Channel;
  UINT32          Byte;
  UINT32          CpuModel;
  char            *BoardName;
  char            *ErrorFlag;

  Inputs = &MrcData->Inputs;
  Debug  = &MrcData->Outputs.Debug;
  CpuModel = (MrcCPUStepGet() & CPU_FAMILY_MASK);
  ErrorFlag = NULL;

  //Check whether it is an LPDDR4 board
    case cmEHL:
      if (!((BoardId == BoardIdEhlLp4xType4Rvp1)   ||
            (BoardId == BoardIdEhlLp4xType3Crb)
           )) {
        ErrorFlag = "EHL";
      }
      break;
      if (!((BoardId == BoardIdIclULp4Type4)       ||
            (BoardId == BoardIdIclULp4Type4Tcpd)   ||
            (BoardId == BoardIdIclULp4Type3)       ||
            (BoardId == BoardIdIclYLp4Type4)       ||
            (BoardId == BoardIdIclYLp4Type4Tlc)    ||
            (BoardId == BoardIdIclYLp4PnpType4)    ||
            (BoardId == BoardIdIclYLp4PnpType4Tlc) ||
            (BoardId == BoardIdIclUSds)            ||
            (BoardId == BoardIdIclYRvpC)           ||
            (BoardId == BoardIdKslILp4Type4Rvp)    ||
            (BoardId == BoardIdIclYNRvp)           ||
            (BoardId == BoardIdIclUNRvp)           ||
            (BoardId == BoardIdEhlLp4xType3Crb)
           )) {
        ErrorFlag = "ICL";
      }
  if ( ErrorFlag != NULL ){
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s: Not an LPDDR4 board! BoardId = 0x%x\n", ErrorFlag, BoardId);
    return;
  }

  ControllerIn      = &Inputs->Controller[0];
  ChannelIn0        = &ControllerIn->Channel[0];
  ChannelIn1        = &ControllerIn->Channel[1];
  DqByteMapCh0      = NULL;
  DqByteMapCh1      = NULL;
  DqsMapCpu2Dram    = NULL;
  DqsMapCpu2DramCh0 = NULL;
  DqsMapCpu2DramCh1 = NULL;
  DqMapCpu2DramCh0  = NULL;
  DqMapCpu2DramCh1  = NULL;

  // CKE to Rank mapping:       CKE  | 0 1 2 3
  // (same on both channels)    --------------
  //                            Rank | 0 1 0 1
  Inputs->CkeRankMapping = 0xAA;

  BoardName = "";
  switch (BoardId) {
    case BoardIdIclULp4Type4:
      BoardName = "ICL-U LPDDR4 Type-4 RVP";
      break;
    case BoardIdIclULp4Type4Tcpd:
      if (BomId == BomIdIclULp4Type4TcpdBomId6) {
        BoardName = "ICL-U LPDDR4 Type-4 PD RVP with LP4 Probing Interposer";
      } else {
        BoardName = "ICL-U LPDDR4 Type-4 PD RVP";
      }
      break;
    case BoardIdIclULp4Type3:
      BoardName = "ICL-U LPDDR4 Type-3 RVP";
      break;
    case BoardIdIclYLp4Type4:
      BoardName = "ICL-Y LPDDR4 Type-4 RVP";
      break;
    case BoardIdIclYLp4Type4Tlc:
      BoardName = "ICL-Y LPDDR4 Type-4 RVP (TLC Update)";
      break;
    case BoardIdIclYLp4PnpType4:
      BoardName = "ICL-Y LPDDR4 PnP RVP";
      break;
    case BoardIdIclYLp4PnpType4Tlc:
      BoardName = "ICL-Y LPDDR4 PnP RVP (TLC Update)";
      break;
    case BoardIdIclUSds:
      BoardName = "ICL-U LPDDR4 SDS";
      break;
    case BoardIdIclYRvpC:
      BoardName = "ICL-Y LPDDR4 RVPC";
      break;
    case BoardIdKslILp4Type4Rvp:
      BoardName = "KSL-I LPDDR4 Type-4 RVP";
      break;
    case BoardIdIclYNRvp:
      BoardName = "ICL-YN LPDDR4 RVP";
      break;
    case BoardIdIclUNRvp:
      BoardName = "ICL-UN LPDDR4 RVP";
      break;
    default:
      ErrorFlag = "ICL";
      break;
  }

  if (CpuModel == cmEHL) {
    ErrorFlag = NULL;
    switch (BoardId) {
      case BoardIdEhlLp4xType4Erb:
        BoardName = "EHL LPDDR4/x ERB";
        break;
      case BoardIdEhlLp4xType4Rvp1:
        BoardName = "EHL LPDDR4/x RVP1";
        break;
      case BoardIdEhlLp4xType3Crb:
        BoardName = "EHL LPDDR4/x CRB";
        break;
      case BoardIdJslLp4xErb:
        BoardName = "JSL LPDDR4 ERB with EHL CPU";
        break;
      case BoardIdJslLp4xType4Rvp1:
        BoardName = "JSL LPDDR4 on EHL RVP1";
        Inputs->DisableDimmChannel[1] = 0x3; // Workaround for JSL Interposer Subchannel 3 CMD Line swapped issue
        break;
      case 0x23:
        BoardName = "!!!JSL 0x23 LPDDR4 ERB with EHL CPU";
        break;
      default:
        ErrorFlag = "EHL";
        break;
    }
  }

  if ( ErrorFlag != NULL ){
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s: Unknown board! BoardId = 0x%x\n",  ErrorFlag, BoardId);
    MRC_DEADLOOP ();
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Detected board: %s\n", BoardName);

  // Setting the default DQ Byte Map. It may be overriden to board specific settings below.
  DqByteMapCh0 = (UINT8 *) DqByteMapIcl[0];
  DqByteMapCh1 = (UINT8 *) DqByteMapIcl[1];

  switch (BoardId) {
    case BoardIdIclULp4Type4:
    case BoardIdIclUNRvp:
      DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramIclULp4Type4Rvp[0];
      DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramIclULp4Type4Rvp[1];
      break;

    case BoardIdIclULp4Type4Tcpd:
      if (BomId == BomIdIclULp4Type4TcpdBomId6) {
        DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramIclULp4TcpdBomId6Rvp[0];
        DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramIclULp4TcpdBomId6Rvp[1];
      } else {
        DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramIclULp4Type4Rvp[0];
        DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramIclULp4Type4Rvp[1];
      }
      if (FabId == FabIdIclULp4Type4TcpdFabId1) {
        DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramIclULp4Type4TcpdFabId1Rvp[0];
        DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramIclULp4Type4TcpdFabId1Rvp[1];
      }
      break;

    case BoardIdIclULp4Type3:
      DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramIclULp4Type3Rvp[0];
      DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramIclULp4Type3Rvp[1];
      break;

    case BoardIdIclYLp4Type4:
    case BoardIdIclYLp4PnpType4:
      DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramIclYLp4Rvp[0];
      DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramIclYLp4Rvp[1];
      break;

    case BoardIdIclYLp4Type4Tlc:
    case BoardIdIclYLp4PnpType4Tlc:
      if (FabId == FabIdIclYLp4Type4TlcFabId3) {
        DqsMapCpu2DramCh0 = (UINT8 *)DqsMapCpu2DramIclYLp4Type4TlcFabId3Rvp[0];
        DqsMapCpu2DramCh1 = (UINT8 *)DqsMapCpu2DramIclYLp4Type4TlcFabId3Rvp[1];
      } else {
        DqsMapCpu2DramCh0 = (UINT8 *)DqsMapCpu2DramIclYLp4Rvp[0];
        DqsMapCpu2DramCh1 = (UINT8 *)DqsMapCpu2DramIclYLp4Rvp[1];
      }
      break;

    case BoardIdIclUSds:
      DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramIclUSdsLp4[0];
      DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramIclUSdsLp4[1];
      break;

    case BoardIdIclYRvpC:
      DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramIclYLp4RvpC[0];
      DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramIclYLp4RvpC[1];
      break;

    case BoardIdKslILp4Type4Rvp:
      DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramKslILp4Type4Rvp[0];
      DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramKslILp4Type4Rvp[1];
      break;

    case BoardIdIclYNRvp:
      DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramIclYNLp4[0];
      DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramIclYNLp4[1];
      break;


    case BoardIdEhlLp4xType3Crb:
      DqsMapCpu2DramCh0 = (UINT8 *)DqsMapCpu2DramEhlLp4Type4Rvp[0];
      DqsMapCpu2DramCh1 = (UINT8 *)DqsMapCpu2DramEhlLp4Type4Rvp[1];
      break;

    default:
      ErrorFlag = "ICL";
      break;
  }

  if (CpuModel == cmEHL) {
    ErrorFlag = NULL;
    switch (BoardId) {

      case BoardIdEhlLp4xType4Erb:
      case BoardIdEhlLp4xType4Rvp1:
      case BoardIdEhlLp4xType3Crb:
      case BoardIdJslLp4xType4Rvp1:
        DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramEhlLp4Type4Rvp[0];
        DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramEhlLp4Type4Rvp[1];
        break;

      case BoardIdJslLp4xErb:
      case 0x23:
        DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramJslLp4xErb[0];
        DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramJslLp4xErb[1];
        break;

      default:
        ErrorFlag = "EHL";
        break;
    }
  }
  if ( ErrorFlag != NULL ){
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s: DQS mapping is not provided! BoardId = 0x%x\n",  ErrorFlag, BoardId);
    MRC_DEADLOOP ();
  }


  // DQ byte mapping to CMD/CTL/CLK
  if (DqByteMapCh0 != NULL) {
    MrcOemMemoryCpy ((UINT8 *) ChannelIn0->DQByteMap, DqByteMapCh0, sizeof (ChannelIn0->DQByteMap));
  }
  if (DqByteMapCh1 != NULL) {
    MrcOemMemoryCpy ((UINT8 *) ChannelIn1->DQByteMap, DqByteMapCh1, sizeof (ChannelIn1->DQByteMap));
  }

  // DQS byte swizzling between CPU and DRAM
  if (DqsMapCpu2DramCh0 != NULL) {
    MrcOemMemoryCpy (ChannelIn0->DqsMapCpu2Dram, DqsMapCpu2DramCh0, sizeof (ChannelIn0->DqsMapCpu2Dram));
  }
  if (DqsMapCpu2DramCh1 != NULL) {
    MrcOemMemoryCpy (ChannelIn1->DqsMapCpu2Dram, DqsMapCpu2DramCh1, sizeof (ChannelIn1->DqsMapCpu2Dram));
  }

  // DQ bit swizzling between CPU and DRAM
  if (DqMapCpu2DramCh0 != NULL) {
    MrcOemMemoryCpy ((UINT8 *) ChannelIn0->DqMapCpu2Dram, DqMapCpu2DramCh0, sizeof (ChannelIn0->DqMapCpu2Dram));
  }
  if (DqMapCpu2DramCh1 != NULL) {
    MrcOemMemoryCpy ((UINT8 *) ChannelIn1->DqMapCpu2Dram, DqMapCpu2DramCh1, sizeof (ChannelIn1->DqMapCpu2Dram));
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    DqsMapCpu2Dram = ControllerIn->Channel[Channel].DqsMapCpu2Dram;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Ch %d DqsMapCpu2Dram: ", Channel);
    for (Byte = 0; Byte < 8; Byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%d ", DqsMapCpu2Dram[Byte]);
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n");
  }
}

/**
  Initialize the board-specific RCOMP values.

  @param[in, out] MrcData - MRC global data structure.
  @param[in]      BoardId - The ID of the board.
**/
void
MrcOemRcompValues (
  IN OUT MrcParameters *const MrcData,
  IN     UINT16               BoardId
  )
{
  MrcInput  *Inputs;
  const UINT16 *RcompResistor;       // Reference RCOMP resistors on motherboard
  const UINT16 *RcompTarget;         // RCOMP target values for DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv

  Inputs = &MrcData->Inputs;

  RcompResistor = NULL;
  RcompTarget   = NULL;
  // Set the on-board RCOMP resistors and RCOMP target values for DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv
  // These values are for ULT/ULX LPDDR
  if (RcompResistor != NULL) {
    MrcOemMemoryCpy ((UINT8 *) Inputs->RcompResistor, (UINT8 *) RcompResistor, sizeof (MrcData->Inputs.RcompResistor));
  }
  if (RcompTarget != NULL) {
    MrcOemMemoryCpy ((UINT8 *) Inputs->RcompTarget,   (UINT8 *) RcompTarget,   sizeof (MrcData->Inputs.RcompTarget));
  }
}

/**
  Perform a byte read from the specified SMBus device address.

  @param[in] SmbusBaseAddress   - The SMBus base address.
  @param[in] SmBusDeviceAddress - SMBus device address to read from.
  @param[in] Offset             - Byte offset to read from.
  @param[out] Value             - Location to store read value.

  @retval mrcSuccess if the read is successful, otherwise mrcFail and the read data is set to zero.
**/
MrcStatus
MrcOemSmbusRead8 (
  IN const UINT32  SmbusBaseAddress,
  IN const UINT8   SmBusDeviceAddress,
  IN const UINT8   Offset,
  OUT UINT8 *const Value
  )
{
  MrcStatus     Status;
  RETURN_STATUS EfiStatus;

  *Value = SmBusReadDataByte (SmBusDeviceAddress | ((UINT32) Offset << 8), &EfiStatus);
  if (EfiStatus == RETURN_SUCCESS) {
    Status = mrcSuccess;
  } else {
    Status = mrcFail;
    *Value = 0;
  }

  return Status;
}

/**
  Perform a byte write to the specified SMBus device address.

  @param[in] SmbusBaseAddress   - The SMBus base address.
  @param[in] SmBusDeviceAddress - SMBus device address to write to.
  @param[in] Offset             - Byte offset to write to.
  @param[in] Value              - The value to write.

  @retval mrcSuccess if the write is successful, otherwise mrcFail.
**/
MrcStatus
MrcOemSmbusWrite8 (
  IN const UINT32  SmbusBaseAddress,
  IN const UINT8   SmBusDeviceAddress,
  IN const UINT8   Offset,
  IN UINT8         Value
  )
{

  MrcStatus     Status;
  RETURN_STATUS EfiStatus;

  SmBusWriteDataByte (SmBusDeviceAddress | ((UINT32) Offset << 8), Value, &EfiStatus);
  Status = (EfiStatus == RETURN_SUCCESS) ? mrcSuccess : mrcFail;
  return Status;
}

/**
  Perform a word read from the specified SMBus device address.

  @param[in] SmbusBaseAddress   - The SMBus base address.
  @param[in] SmBusDeviceAddress - SMBus device address to read from.
  @param[in] Offset             - Offset to read from.
  @param[out] Value             - Location to store read value.

  @retval mrcSuccess if the read is successful, otherwise mrcFail and the read data is set to zero.
**/
MrcStatus
MrcOemSmbusRead16 (
  IN const UINT32   SmbusBaseAddress,
  IN const UINT8    SmBusDeviceAddress,
  IN const UINT8    Offset,
  OUT UINT16 *const Value
  )
{
  MrcStatus     Status;
  RETURN_STATUS EfiStatus;

  *Value = SmBusReadDataWord (SmBusDeviceAddress | ((UINT32) Offset << 8), &EfiStatus);
  if (EfiStatus == RETURN_SUCCESS) {
    Status = mrcSuccess;
  } else {
    Status = mrcFail;
    *Value = 0;
  }

  return Status;
}

/**
  Perform a word write to the specified SMBus device address.

  @param[in] SmbusBaseAddress   - The SMBus base address.
  @param[in] SmBusDeviceAddress - SMBus device address to write to.
  @param[in] Offset             - Offset to write to.
  @param[in] Value              - The value to write.

  @retval mrcSuccess if the write is successful, otherwise mrcFail.
**/
MrcStatus
MrcOemSmbusWrite16 (
  IN const UINT32  SmbusBaseAddress,
  IN const UINT8   SmBusDeviceAddress,
  IN const UINT8   Offset,
  IN UINT16        Value
  )
{
  MrcStatus     Status;
  RETURN_STATUS EfiStatus;

  SmBusWriteDataWord (SmBusDeviceAddress | ((UINT32) Offset << 8), Value, &EfiStatus);
  Status = (EfiStatus == RETURN_SUCCESS) ? mrcSuccess : mrcFail;
  return Status;
}

/**
  Get the current PCH type.

  @retval PCH_GENERATION, see PchInfoLib.h
**/
PCH_GENERATION
MrcGetPchGeneration (
  void
  )
{
  return ICL_PCH;
}

/**
  Get the current PCH Series.

  @retval PCH_SERIES, see PchInfoLib.h
**/
PCH_SERIES
MrcGetPchSeries (
  void
  )
{
  UINT16      LpcDeviceId;

  MrcOemOutPort32 (MrcOemPciIndex (), GetPciDeviceAddress (0, PCI_DEVICE_NUMBER_PCH_LPC, PCI_FUNCTION_NUMBER_PCH_LPC, 0));
  LpcDeviceId = (MrcOemInPort32 (MrcOemPciData ()) >> 16) & 0xFFFF;

  switch (LpcDeviceId & B_LPC_CFG_DID) {
    case V_LPC_CFG_DID_ICL_H:
      return PCH_H;

    case V_LPC_CFG_DID_ICL_LP:
    case V_LPC_CFG_DID_EHL_LP:
      return PCH_LP;

    case V_LPC_CFG_DID_ICL_N:
      return PCH_N;

    default:
      return PCH_UNKNOWN_SERIES;
  }
}

/**
  Check if this is PCH H series

  @retval TRUE                It's PCH H series
  @retval FALSE               It's not PCH H series
**/
BOOLEAN
IsPchH (
  VOID
  )
{
  return (MrcGetPchSeries () == PCH_H);
}

/**
  Check if this is PCH LP series

  @retval TRUE                It's PCH LP series
  @retval FALSE               It's not PCH LP series
**/
BOOLEAN
IsPchLp (
  VOID
  )
{
  return (MrcGetPchSeries () == PCH_LP);
}

/**
  Check if this is PCH N series

  @retval TRUE                It's PCH N series
  @retval FALSE               It's not PCH N series
**/
BOOLEAN
IsPchN (
  VOID
  )
{
  return (MrcGetPchSeries () == PCH_N);
}

/**
  Disable PCIe root ports on PCH.
  See PchDisableRootPort() in PCH RC.

  @param[in] MrcData - Mrc global data structure
**/
VOID
MrcDisablePciePorts (
  IN MrcParameters *const MrcData
  )
{
  UINT32 Data32;
  UINT32 Offset;

  // PCIe RP IOSF Sideband register offset R_PCH_PCR_SPX_PCD 0x00[19:16], depending on the port that is Function Disabled
  // Access it by offset 0x02[4:0] to avoid RWO bit
  MrcOemMmioWrite8 (PCH_PCR_ADDRESS (PID_SPA, 0x02), 0x0F);
  MrcOemMmioWrite8 (PCH_PCR_ADDRESS (PID_SPB, 0x02), 0x0F);
  MrcOemMmioWrite8 (PCH_PCR_ADDRESS (PID_SPC, 0x02), 0x0F);
  MrcOemMmioWrite8 (PCH_PCR_ADDRESS (PID_SPD, 0x02), 0x0F);
  MrcOemMmioWrite8 (PCH_PCR_ADDRESS (PID_SPE, 0x02), 0x0F);
  MrcOemMmioWrite8 (PCH_PCR_ADDRESS (PID_SPF, 0x02), 0x0F);

  // Then disable the ports in PSF
  // R_ICL_PCH_H_PSF6_PCR_T1_SHDW_PCIE01_REG_BASE + R_PCH_PSFX_PCR_T1_SHDW_PCIEN, set bit [8] = B_PCH_PSFX_PCR_T1_SHDW_PCIEN_FUNDIS

  if (IsPchLp ()) {
    for (Offset = R_ICL_PCH_LP_PSF1_PCR_T1_SHDW_PCIE01_RS0_REG_BASE; Offset <= R_ICL_PCH_LP_PSF1_PCR_T1_SHDW_PCIE16_RS0_REG_BASE; Offset += 0x100) {
      Data32 = MrcOemMmioRead32 (PCH_PCR_ADDRESS (PID_PSF1, Offset + R_PCH_PSFX_PCR_T1_SHDW_PCIEN));
      MrcOemMmioWrite32 (PCH_PCR_ADDRESS (PID_PSF1, Offset + R_PCH_PSFX_PCR_T1_SHDW_PCIEN), Data32 | MRC_BIT8);
    }
  }

  if (IsPchH ()) {
    for (Offset = R_ICL_PCH_H_PSF1_PCR_T1_SHDW_PCIE01_RS0_REG_BASE; Offset <= R_ICL_PCH_H_PSF1_PCR_T1_SHDW_PCIE24_RS0_REG_BASE; Offset += 0x80) {
      Data32 = MrcOemMmioRead32 (PCH_PCR_ADDRESS (PID_PSF1, Offset + R_PCH_PSFX_PCR_T1_SHDW_PCIEN));
      MrcOemMmioWrite32 (PCH_PCR_ADDRESS (PID_PSF1, Offset + R_PCH_PSFX_PCR_T1_SHDW_PCIEN), Data32 | MRC_BIT8);
    }
  }

  if (IsPchN ()) {
    for (Offset = R_ICL_PCH_N_PSF1_PCR_T1_SHDW_PCIE01_RS0_REG_BASE; Offset <= R_ICL_PCH_N_PSF1_PCR_T1_SHDW_PCIE08_RS0_REG_BASE; Offset += 0x100) {
      Data32 = MrcOemMmioRead32 (PCH_PCR_ADDRESS (PID_PSF1, Offset + R_PCH_PSFX_PCR_T1_SHDW_PCIEN));
      MrcOemMmioWrite32 (PCH_PCR_ADDRESS (PID_PSF1, Offset + R_PCH_PSFX_PCR_T1_SHDW_PCIEN), Data32 | MRC_BIT8);
    }
  }
}

/*
  Check on the processor if PRMRR is supported.

  @param[in]  Size  - PRMRR size requested in MB.  Must be natural size (2^x).

  @retval Size in MB.  0 if unsupported.
*/
UINT32
MrcCheckPrmrrSupport (
  MrcParameters *MrcData,
  UINT32        PrmrrSize
  )
{
  UINT32 ReturnSize  = 0;
  /// PRMRR configuration enabled, MSR IA32_MTRRCAP (FEh) [12] == 1
  MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "MSR_IA32_MTRRCAP: 0x%x\n", ReadMsr64 (MSR_IA32_MTRRCAP));
  if ((ReadMsr64 (MSR_IA32_MTRRCAP) & MRC_BIT12) != 0) {
    /// Check if PRMRR setup size is not supported.
    /// Bits 0 through 31 indicate which sizes are supported. Each bit represents one size.
    /// A bit at position n indicates whether size 2^(n+20) bytes is supported
    MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "MSR_PRMRR_VALID_CONFIG: 0x%x\n", ReadMsr64 (MSR_PRMRR_VALID_CONFIG));
    if ((ReadMsr64 (MSR_PRMRR_VALID_CONFIG) & PrmrrSize) != 0){
      ReturnSize = PrmrrSize;
    }
  }
  return ReturnSize;
}

/**
  Sets PRMRR Core Lock & Config bits, and PRMRR core MSR for
  BSP thread core

  @param[in] PrmrrBase - PRMRR base that was allocated
  @param[in] PrmrrSize - PRMRR size that was allocated
**/

VOID
MrcSetCorePrmrr (
  UINT32 PrmrrBase,
  UINT32 PrmrrSize
  )
{
  UINT64 PrmrrMask;

  if ((ReadMsr64 (MSR_IA32_MTRRCAP) & MRC_BIT12) != 0) {
    /// Mask setting have to be set in bits [39:12] other bits bits [64:40] need to be zero
    /// Setting bits [64:40] will cause the BIOS to hung
    PrmrrMask = V_MSR_PRMRR_MASK & (~((UINT64) (PrmrrSize - 1)));

    /// If PRMRR size is 0, only need to set bit lock on MSR 0x1f5
    if (PrmrrSize == 0) {
      if (!(ReadMsr64 (MSR_PRMRR_MASK) & B_MSR_PRMRR_MASK_L_MASK)) {
        /// Need to lock mask MSRs even if PRMRR size is zero
        WriteMsr64 (MSR_PRMRR_MASK, B_MSR_PRMRR_MASK_L_MASK);
      }
    } else {
      /// Set the CORE PRMRR base and mask MSRs and set PRMRR mask lock and Config bits
      if (!(ReadMsr64 (MSR_PRMRR_MASK) & B_MSR_PRMRR_MASK_L_MASK)) {
        WriteMsr64 (MSR_PRMRR_BASE_0, PrmrrBase | CACHE_WRITEBACK | B_MSR_PRMRR_BASE_0_CONFIGURED_MASK);
        WriteMsr64 (MSR_PRMRR_MASK, PrmrrMask | B_MSR_PRMRR_MASK_L_MASK);
      }
    }
  }
}


/**
  Set a GPIO value to indicate "End of BIOS POST" to BMC on a UP server board (Zumba Beach).
  Otherwise BMC will shutdown the board after 7 minutes.

**/
VOID
MrcUpServerSendEndOfPost (
  VOID
  )
{
  // Set GPIO_SKL_H_GPP_B20 "Low"
  // GpioPadModeGpio, GpioHostOwnDefault, GpioDirOut, GpioOutLow, GpioIntDis, GpioResetNormal, GpioTermNone
  MrcOemMmioWrite32 (PCH_PCR_ADDRESS (PID_GPIOCOM0, 0x560), 0x80000200); // PADCFG DW0
  MrcOemMmioWrite32 (PCH_PCR_ADDRESS (PID_GPIOCOM0, 0x564), 0);          // PADCFG DW1
}

MrcStatus
PollMailboxReady (
  IN UINT32 MailboxType
  )
{
  MrcStatus               Status;
  UINT16                  StallCount;
  UINT8                   RunBusyBit;
  UINT64                  MsrData;
  UINT32                  MchBar;
  OC_MAILBOX_FULL         OcMailboxFull;
  PCODE_MAILBOX_INTERFACE PcodeMailboxInterface;
#ifdef MRC_MINIBIOS_BUILD
  UINT32                  Start;
#endif

  Status = mrcSuccess;
  StallCount = 0;
  RunBusyBit = 1;

  MrcOemOutPort32 (0xCF8, GetPciDeviceAddress (0, 0, 0, MCHBAR_0_0_0_PCI_REG));
  MchBar = MrcOemInPort32 (0xCFC) & ~MRC_BIT0;

  do {
    switch (MailboxType) {
      case MAILBOX_TYPE_PCODE:
        /// Read the MMIO run/busy state
        PcodeMailboxInterface.InterfaceData = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET);
        RunBusyBit = (UINT8) PcodeMailboxInterface.Fields.RunBusy;
        break;

      case MAILBOX_TYPE_OC:
        /// Read the OC mailbox run/busy state
        MsrData = ReadMsr64 (OC_MAILBOX_MSR);
        MrcOemMemoryCpy ((UINT8 *) &OcMailboxFull.Data, (UINT8 *) &MsrData, sizeof(OcMailboxFull));
        RunBusyBit = OcMailboxFull.Interface.Fields.RunBusy;
        break;
      default:
        break;
    }
    // Wait for 1us
#ifdef MRC_MINIBIOS_BUILD
    for (Start = 0; Start < (MAILBOX_WAIT_STALL * 20); Start++) {
      // Just perform Dummy reads to CPU CR
      MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);
    }
#else
    PchPmTimerStall (MAILBOX_WAIT_STALL);
#endif
    StallCount++;
  }
  while ((RunBusyBit == 1) && (StallCount < MAILBOX_WAIT_TIMEOUT));

  if ((RunBusyBit == 1) && (StallCount == MAILBOX_WAIT_TIMEOUT)) {
    Status = mrcFail;
  }

  return Status;
}

/*
  Write CPU Mailbox.

  @param[in]  MailboxType    - CPU mailbox type
  @param[in]  MailboxCommand - CPU mailbox command
  @param[in]  MailboxData    - CPU mailbox data
  @param[out] MailboxStatus  - Completion Code
*/
MrcStatus
MailboxWrite (
  IN UINT32  MailboxType,
  IN UINT32  MailboxCommand,
  IN UINT32  MailboxData,
  OUT UINT32 *MailboxStatus
  )
{
  MrcStatus          Status;
  UINT64             MsrData;
  UINT32             MchBar;
  OC_MAILBOX_FULL    OcMailboxFull;
  OC_MAILBOX_FULL    OcMailboxFullVerify;
  PCODE_MAILBOX_FULL PcodeMailboxFull;
  PCODE_MAILBOX_FULL PcodeMailboxFullVerify;
#ifdef MRC_MINIBIOS_BUILD
  UINT32             Start;
#endif

  ///  Poll the run/busy to ensure the interface is available
  Status = PollMailboxReady (MailboxType);
  if (Status != mrcSuccess) {
    return Status;
  }

  MrcOemOutPort32 (0xCF8, GetPciDeviceAddress (0, 0, 0, MCHBAR_0_0_0_PCI_REG));
  MchBar = MrcOemInPort32 (0xCFC) & ~MRC_BIT0;

  switch (MailboxType) {
    case MAILBOX_TYPE_PCODE:
      /// Copy in Mailbox data and write the PCODE mailbox DATA field
      PcodeMailboxFull.Interface.InterfaceData = MailboxCommand;
      PcodeMailboxFull.Data = MailboxData;
      MrcOemMmioWrite32 (MchBar + PCODE_MAILBOX_DATA_OFFSET, PcodeMailboxFull.Data);

      /// Set the Run/Busy bit to signal mailbox data is ready to process
      PcodeMailboxFull.Interface.Fields.RunBusy = 1;
      MrcOemMmioWrite32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET, PcodeMailboxFull.Interface.InterfaceData);

      /// Poll run/busy to indicate the completion of write request
      PollMailboxReady (MailboxType);

      /// Read the BIOS PCODE mailbox to verify write completion success.
      /// Mailbox protocol requires software to read back the interface twice
      /// to ensure the read results are consistent.
      PcodeMailboxFull.Interface.InterfaceData = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET);
      PcodeMailboxFull.Data = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);

#ifdef MRC_MINIBIOS_BUILD
      for (Start = 0; Start < (MAILBOX_READ_TIMEOUT * 20); Start++) {
        // Just perform Dummy reads to CPU CR
        MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);
      }
#else
      PchPmTimerStall (MAILBOX_READ_TIMEOUT);
#endif
      /// Read twice to verify data is consistent
      PcodeMailboxFullVerify.Interface.InterfaceData = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET);
      PcodeMailboxFullVerify.Data = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);

      /// If the data is inconsistent, we cannot trust the results
      if (PcodeMailboxFull.Interface.InterfaceData != PcodeMailboxFullVerify.Interface.InterfaceData) {
        if (PcodeMailboxFull.Data  != PcodeMailboxFullVerify.Data) {
          return mrcFail;
        }
      }

      ///  Copy PCODE mailbox completion code
      *MailboxStatus = (UINT32) PcodeMailboxFull.Interface.Fields.Command;
      break;

    case MAILBOX_TYPE_OC:
      /// Set the Run/Busy bit to signal mailbox data is ready to process
      OcMailboxFull.Interface.InterfaceData = MailboxCommand;
      OcMailboxFull.Data = MailboxData;
      OcMailboxFull.Interface.Fields.RunBusy = 1;
      MrcOemMemoryCpy ((UINT8 *) &MsrData, (UINT8 *) &OcMailboxFull, sizeof(MsrData));

      /// Write mailbox command to OC mailbox
      WriteMsr64 (OC_MAILBOX_MSR, MsrData);

      /// Poll run/busy to indicate the completion of write request
      PollMailboxReady (MailboxType);

      /// Read the mailbox command from OC mailbox. Read twice to ensure data.
      MsrData = ReadMsr64 (OC_MAILBOX_MSR);
      MrcOemMemoryCpy ((UINT8 *) &OcMailboxFull, (UINT8 *) &MsrData, sizeof(OcMailboxFull));

#ifdef MRC_MINIBIOS_BUILD
      for (Start = 0; Start < (MAILBOX_READ_TIMEOUT * 20); Start++) {
        // Just perform Dummy reads to CPU CR
        MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);
      }
#else
      PchPmTimerStall (MAILBOX_READ_TIMEOUT);
#endif

      MsrData = ReadMsr64 (OC_MAILBOX_MSR);
      MrcOemMemoryCpy ((UINT8 *) &OcMailboxFullVerify, (UINT8 *) &MsrData, sizeof(OcMailboxFullVerify));

      /// If the data is inconsistent, we cannot trust the results
      if (OcMailboxFull.Interface.InterfaceData != OcMailboxFullVerify.Interface.InterfaceData) {
        if (OcMailboxFull.Data != OcMailboxFullVerify.Data) {
          return mrcFail;
        }
      }

      ///  Copy Overclocking mailbox completion code and read results
      *MailboxStatus = OcMailboxFull.Interface.Fields.CommandCompletion;
      break;

    default:
      Status = mrcFail;
      break;
  }

  return mrcFail;
}

/*
  Read CPU Mailbox.

  @param[in]  MailboxType    - CPU mailbox type
  @param[in]  MailboxCommand - CPU mailbox command
  @param[out] MailboxDataPtr - CPU mailbox data pointer
  @param[out] MailboxStatus  - Completion Code
*/
MrcStatus
MailboxRead (
  IN  UINT32  MailboxType,
  IN  UINT32  MailboxCommand,
  OUT UINT32  *MailboxDataPtr,
  OUT UINT32  *MailboxStatus
  )
{
  MrcStatus          Status;
  UINT64             MsrData;
  UINT32             MchBar;
  PCODE_MAILBOX_FULL PcodeMailboxFull;
  PCODE_MAILBOX_FULL PcodeMailboxFullVerify;
  OC_MAILBOX_FULL    OcMailboxFull;
  OC_MAILBOX_FULL    OcMailboxFullVerify;
#ifdef MRC_MINIBIOS_BUILD
  UINT32             Start;
#endif

  ///  Poll the run/busy to ensure the interface is available
  Status = PollMailboxReady (MailboxType);
  if (Status != mrcSuccess) {
    return Status;
  }

  MrcOemOutPort32 (0xCF8, GetPciDeviceAddress (0, 0, 0, MCHBAR_0_0_0_PCI_REG));
  MchBar = MrcOemInPort32 (0xCFC) & ~MRC_BIT0;

  switch (MailboxType) {
    case MAILBOX_TYPE_PCODE:
      /// Write the PCODE mailbox read request.
      /// Read requests only require a write to the PCODE interface mailbox.
      /// The read results will be updated in the data mailbox.
      PcodeMailboxFull.Interface.InterfaceData = MailboxCommand;
      PcodeMailboxFull.Interface.Fields.RunBusy = 1;
      MrcOemMmioWrite32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET, PcodeMailboxFull.Interface.InterfaceData);

      /// Poll run/busy to indicate the completion of read request
      PollMailboxReady (MailboxType);

      /// Read the BIOS PCODE mailbox to verify read completion success.
      /// Mailbox protocol requires software to read back the interface twice
      /// to ensure the read results are consistent.
      PcodeMailboxFull.Interface.InterfaceData = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET);
      PcodeMailboxFull.Data = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);

#ifdef MRC_MINIBIOS_BUILD
      for (Start = 0; Start < (MAILBOX_READ_TIMEOUT * 20); Start++) {
        // Just perform Dummy reads to CPU CR
        MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);
      }
#else
      PchPmTimerStall (MAILBOX_READ_TIMEOUT);
#endif
      /// Read twice to verify data is consistent
      PcodeMailboxFullVerify.Interface.InterfaceData = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET);
      PcodeMailboxFullVerify.Data = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);

      /// If the data is inconsistent, we cannot trust the results
      if (PcodeMailboxFull.Interface.InterfaceData != PcodeMailboxFullVerify.Interface.InterfaceData) {
        if (PcodeMailboxFull.Data  != PcodeMailboxFullVerify.Data) {
          return mrcFail;
        }
      }

      ///  Copy PCODE mailbox completion code and read results
      *MailboxStatus = (UINT32) PcodeMailboxFull.Interface.InterfaceData;
      MrcOemMemoryCpy ((UINT8 *) MailboxDataPtr, (UINT8 *) &PcodeMailboxFull.Data, sizeof(UINT32));
      break;

    case MAILBOX_TYPE_OC:
      /// Set the Run/Busy bit to signal mailbox data is ready to process
      OcMailboxFull.Interface.InterfaceData = MailboxCommand;
      OcMailboxFull.Data = *MailboxDataPtr;
      OcMailboxFull.Interface.Fields.RunBusy = 1;
      MrcOemMemoryCpy ((UINT8 *)&MsrData, (UINT8 *) &OcMailboxFull, sizeof(MsrData));

      /// Write mailbox command to OC mailbox
      WriteMsr64 (OC_MAILBOX_MSR, MsrData);

      /// Poll run/busy to indicate the completion of write request
      PollMailboxReady (MailboxType);

      /// Read the OC mailbox to verify read completion success.
      /// Mailbox protocol requires software to read back the interface twice
      /// to ensure the read results are consistent.
      MsrData = ReadMsr64 (OC_MAILBOX_MSR);
      MrcOemMemoryCpy ((UINT8 *) &OcMailboxFull, (UINT8 *) &MsrData, sizeof(OcMailboxFull));

#ifdef MRC_MINIBIOS_BUILD
      for (Start = 0; Start < (MAILBOX_READ_TIMEOUT * 20); Start++) {
        // Just perform Dummy reads to CPU CR
        MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);
      }
#else
      PchPmTimerStall (MAILBOX_READ_TIMEOUT);
#endif
      MsrData = ReadMsr64 (OC_MAILBOX_MSR);
      MrcOemMemoryCpy ((UINT8 *) &OcMailboxFullVerify, (UINT8 *) &MsrData, sizeof(OcMailboxFullVerify));

      /// If the data is inconsistent, we cannot trust the results
      if (OcMailboxFull.Interface.InterfaceData != OcMailboxFullVerify.Interface.InterfaceData) {
        if (OcMailboxFull.Data != OcMailboxFullVerify.Data) {
          return mrcFail;
        }
      }

      ///  Copy Overclocking mailbox completion code and read results
      *MailboxStatus = OcMailboxFull.Interface.Fields.CommandCompletion;
      MrcOemMemoryCpy ((UINT8 *) MailboxDataPtr, (UINT8 *) &OcMailboxFull.Data, sizeof(UINT32));
      break;

    default:
      Status = mrcFail;
      break;
  }

  return Status;
}

/**
  This function checks to see if the MrcSave was saved.

  @retval BOOLEAN - TRUE if MrcSave exists, otherwise FALSE.
**/
BOOLEAN
MrcSaveExists (
  void
  )
{
  return TRUE;
}

/**
  Get MrcSave data.
  Stub mode - get from file.
  MiniBios  - get from flash.

  @param[in, out] SavePtr     - MrcSave address
  @param[in]      BufferSize  - MrcSave size
**/
void
MrcGetMrcSaveData (
  OUT UINT8  *SavePtr,
  IN  UINT32 BufferSize
  )
{
  MrcOemMemoryCpy (SavePtr, (UINT8 *) MRC_SAVE_DATA_FLASH_PTR, BufferSize);
}

/**
  This procedure will get PCIE address

  @param[in] Bus                  Pci Bus Number
  @param[in] Device               Pci Device Number
  @param[in] Function             Pci Function Number

  @retval PCIE address
**/
UINTN
MmPciBase (
  IN UINT32                       Bus,
  IN UINT32                       Device,
  IN UINT32                       Function
  )
{
  // Note that PCIEXBAR is hard-coded !
  return ((UINTN) PCIEBAR_ADDRESS + (UINTN) (Bus << 20) + (UINTN) (Device << 15) + (UINTN) (Function << 12));
}

UINT32
MmioRead32 (
  IN      UINTN                     Address
  )
{
  return MrcOemMmioRead32 (Address);
}

UINT32
MmioWrite32 (
  IN      UINTN                     Address,
  IN      UINT32                    Value
  )
{
  MrcOemMmioWrite32 (Address, Value);
  return Value;
}

UINT32
MmioOr32 (
  IN      UINTN                     Address,
  IN      UINT32                    OrData
  )
{
  return MrcOemMmioWrite32 (Address, MrcOemMmioRead32 (Address) | OrData);
}

UINT16
MmioOr16 (
  IN      UINTN                     Address,
  IN      UINT16                    OrData
  )
{
  return MrcOemMmioWrite16 (Address, MrcOemMmioRead16 (Address) | OrData);
}

UINT8
MmioOr8 (
  IN      UINTN                     Address,
  IN      UINT8                     OrData
  )
{
  return MrcOemMmioWrite8 (Address, MrcOemMmioRead8 (Address) | OrData);
}

UINT32
MmioAndThenOr32 (
  IN      UINTN                     Address,
  IN      UINT32                    AndData,
  IN      UINT32                    OrData
  )
{
  return MrcOemMmioWrite32 (Address, (MrcOemMmioRead32 (Address) & AndData) | OrData);
}

UINT16
MmioRead16 (
  IN      UINTN                     Address
  )
{
  return MrcOemMmioRead16 (Address);
}

UINT16
MmioWrite16 (
  IN      UINTN                     Address,
  IN      UINT16                    Value
  )
{
  MrcOemMmioWrite16 (Address, Value);
  return Value;
}

UINT16
MmioAndThenOr16 (
  IN      UINTN                     Address,
  IN      UINT16                    AndData,
  IN      UINT16                    OrData
  )
{
  return MrcOemMmioWrite16 (Address, (MrcOemMmioRead16 (Address) & AndData) | OrData);
}

UINT8
MmioRead8 (
  IN      UINTN                     Address
  )
{
  return MrcOemMmioRead8 (Address);
}

UINT8
MmioWrite8 (
  IN      UINTN                     Address,
  IN      UINT8                     Value
  )
{
  MrcOemMmioWrite8 (Address, Value);
  return Value;
}

VOID
ZeroMem (
  OUT VOID *Buffer,
  IN  UINTN  Length
  )
{
  MrcOemMemorySet (Buffer, Length, 0);
}

#ifdef BDAT_SUPPORT
/**
  This function returns a pointer to the allocated hand off buffer.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in, out] Hob         - A pointer to where to store the pointer to the allocated data buffer.
  @param[in]      BlockSize   - The size of the buffer to get.
  @param[in]      Guid        - The GUID to assign to the HOB.

  @retval EFI_SUCCESS - Hob is successfully built.
  @retval Others      - Error occurred while creating the Hob.
**/
EFI_STATUS
MrcGetHobForDataStorage (
  IN OUT MrcParameters *const     MrcData,
  IN OUT VOID                     **Hob,
  IN     UINT16                   BlockSize,
  IN     EFI_GUID                 *Guid
  )
{
  EFI_HOB_GUID_TYPE *Buffer;

  // Status = PeiServicesCreateHob (EFI_HOB_TYPE_GUID_EXTENSION, BlockSize, Hob);
  // if (EFI_ERROR (Status)) {
  //   return Status;
  // }
  *Hob = MrcHeapMalloc (MrcData, BlockSize);
  if (*Hob == NULL) {
    return mrcFail;
  }
  Buffer = (EFI_HOB_GUID_TYPE *) *Hob;
  Buffer->Header.HobType = EFI_HOB_TYPE_GUID_EXTENSION;
  Buffer->Header.HobLength = BlockSize;

  MrcOemMemoryCpy ((UINT8 *) &(Buffer->Name), (UINT8 *) Guid, sizeof (EFI_GUID));
  ZeroMem ((VOID *) ((UINT32) Buffer + sizeof (EFI_HOB_GUID_TYPE)), BlockSize - sizeof (EFI_HOB_GUID_TYPE));
  return mrcSuccess;
}

/**
  Finds the BDAT Schema List HOB if it exists.  If it does not exist, creates it

  @param[in, out] MrcData       - Include all MRC global data.
  @param[out] BdatSchemaListHob - Pointer to Schema List Hob, by reference

  @retval EFI_SUCCESS - Hob was successfully found or built.
  @retval Others      - Error occurred while creating or finding the Hob.
**/
EFI_STATUS
MrcGetBdatSchemaListHob (
  IN OUT MrcParameters *const      MrcData,
  OUT    MRC_BDAT_SCHEMA_LIST_HOB  **BdatSchemaListHob
  )
{
  EFI_STATUS               Status;
  MRC_BDAT_SCHEMA_LIST_HOB *Buffer;

  Status = MrcGetHobForDataStorage (
             MrcData,
             (VOID **) &Buffer,
             sizeof (MRC_BDAT_SCHEMA_LIST_HOB),
             (EFI_GUID*) &gMrcSchemaListHobGuid
             );
  if (Status == mrcSuccess) {
    *BdatSchemaListHob = Buffer;
  }

  return Status;
}
#endif // BDAT_SUPPORT
