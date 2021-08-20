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

#ifdef SSA_FLAG
#include "MrcSsaInitialize.h"
#endif

// MrcSave data is stored here in Flash
#define MRC_SAVE_DATA_FLASH_PTR   0xFFD00000

#define SPD_PAGE_ADDRESS_0 (0x6C)
#define SPD_PAGE_ADDRESS_1 (0x6E)
#define isprint(a)         (((a) >= ' ') && ((a) <= '~') ? (a) : 0)
// @todo: Update MiniBIOS to take BCLK as an input parameter.
#define MRC_SYSTEM_BCLK (100)

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

#pragma pack (push, 1)
// The following section contains board-specific DQ/DQS mapping, needed for LPDDR

//
// TGL-U LPDDR4 RVP5 DQS byte and bit swizzing between CPU and DRAM
//
const UINT8 DqsMapCpu2DramTglULp4Rvp5[8][2] = {
  // Ch 0     1         2         3
  { 0, 1 }, { 1, 0 }, { 0, 1 }, { 1, 0 }, // Controller 0
  { 1, 0 }, { 0, 1 }, { 0, 1 }, { 1, 0 }  // Controller 1
};

const UINT8 DqMapCpu2DramTglULp4Rvp5[8][2][8] = {
  //Controller 0
  {{  0,  1,  6,  7,  3,  2,  5,  4 },   // Byte 0
   { 15,  8,  9, 14, 12, 11, 10, 13 }},  // Byte 1
  {{ 11, 12,  8, 15,  9, 14, 10, 13 },   // Byte 2
   {  3,  4,  7,  0,  6,  1,  5,  2 }},  // Byte 3
  {{  4,  5,  3,  2,  7,  1,  0,  6 },   // Byte 4
   { 11, 10, 12, 13,  8,  9, 14, 15 }},  // Byte 5
  {{ 12, 11,  8, 13, 14, 15,  9, 10 },   // Byte 6
   {  4,  7,  3,  2,  1,  6,  0,  5 }},  // Byte 7
  //Controller 1
  {{ 11, 10,  9,  8, 12, 13, 15, 14 },   // Byte 0  ChB!
   {  4,  5,  6,  7,  3,  2,  0,  1 }},  // Byte 1  ChB!
  {{  0,  7,  1,  6,  3,  5,  2,  4 },   // Byte 2
   {  9,  8, 10, 11, 14, 15, 13, 12 }},  // Byte 3
  {{  4,  5,  6,  1,  3,  2,  7,  0 },   // Byte 4
   { 10, 13, 12, 11, 14,  9, 15,  8 }},  // Byte 5
  {{ 10, 12,  9, 15,  8, 11, 13, 14 },   // Byte 6
   {  3,  4,  1,  2,  6,  0,  5,  7 }}   // Byte 7
};

//
// TGL-U LPDDR4 AEP DQS byte and bit swizzing between CPU and DRAM
//
const UINT8 DqsMapCpu2DramTglULp4Aep[8][2] = {
  // Ch 0     1         2         3
  { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 },  //controller 0
  { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 }   //controller 1
};

const UINT8 DqMapCpu2DramTglULp4Aep[8][2][8] = {
  //Controller 0
  {{  0,  1,  3,  2,  4,  5,  6,  7 },   // Byte 0
   { 12, 13, 14, 15, 11, 10,  9,  8 }},  // Byte 1
  {{  4,  2,  5,  3,  6,  1,  7,  0 },   // Byte 2
   { 10,  8,  9, 11, 15, 12, 14, 13 }},  // Byte 3
  {{  3,  2,  1,  0,  4,  5,  6,  7 },   // Byte 4
   { 12, 13, 14, 15, 11, 10,  9,  8 }},  // Byte 5
  {{  7,  0,  1,  6,  5,  4,  2,  3 },   // Byte 6
   { 15, 14,  8,  9, 10, 12, 11, 13 }},  // Byte 7
  //Controller 1
  {{  3,  2,  1,  0,  4,  5,  6,  7},    // Byte 0
   { 12, 13, 14, 15, 11, 10,  9,  8 }},  // Byte 1
  {{  3,  4,  2,  5,  0,  6,  1,  7 },   // Byte 2
   { 13, 12, 11, 10, 14, 15,  9,  8 }},  // Byte 3
  {{  3,  2,  1,  0,  7,  4,  5,  6 },   // Byte 4
   { 15, 14, 13, 12,  8,  9, 10, 11 }},  // Byte 5
  {{  3,  4,  2,  5,  1,  0,  7,  6 },   // Byte 6
   { 15, 14,  9,  8, 12, 10, 11, 13 }}   // Byte 7
};

// TGL-U LPDDR5 DQS byte swizzling between CPU and DRAM
const UINT8 DqsMapCpu2DramBoardIdTglULp5Type4[8][2] = {
  // Ch 0 1 2 3
  { 0, 1 }, { 1, 0 }, { 0, 1 }, { 0, 1 }, // Controller 0
  { 0, 1 }, { 1, 0 }, { 0, 1 }, { 0, 1 }  // Controller 1
};

GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 DqMapCpu2DramBoardIdTglULp5Type4[8][2][8] = {
  //Controller 0
  {{  0,  1,  2,  3,  6,  4,  7,  5 },   // Byte 0, ch0
  {  13, 14, 12, 11,  8, 15, 10,  9 }},  // Byte 1, ch0
  {{ 15, 14, 13, 12, 10,  8, 11,  9 },   // Byte 1, ch1
  {   6,  0,  1,  5,  2,  7,  3,  4 }},  // Byte 0, ch1
  {{  0,  1,  7,  2,  5,  4,  6,  3 },   // Byte 0, ch2
  {  12, 15, 14, 13,  8,  9, 10, 11 }},  // Byte 1, ch2
  {{  6,  0,  1,  5,  7,  4,  2,  3 },   // Byte 0, ch3
  {  14, 13,  8,  9, 10, 15, 11, 12 }},  // Byte 1, ch3
  //Controller 1
  {{  3,  0,  1,  2,  6,  5,  4,  7 },   // Byte 0
  {  11, 12, 13, 14,  8, 15,  9, 10 }},  // Byte 1
  {{ 13, 10, 12, 11, 15,  8, 14,  9 },   // Byte 2
  {   3,  2,  7,  4,  1,  0,  5,  6 }},  // Byte 3
  {{  0,  1,  7,  2,  5,  3,  6,  4 },   // Byte 4
  {  15, 12, 13, 14, 10, 11,  9,  8 }},  // Byte 5
  {{  3,  4,  2,  7,  1,  0,  6,  5 },   // Byte 6
  {  14, 13,  9,  8, 12, 10, 11, 15 }}   // Byte 7
};

const UINT8 DqsMapCpu2DramLpNoSwizzle[4][2] = {
  // Ch 0       1       2       3
        {0,1},  {0,1},  {0,1},  {0,1} // Controller 0
};

// DQ bit swizzling between CPU and DRAM
UINT8 DqMapCpu2DramLpNoSwizzle[2][8] = {
  {  0,  1,  2,  3,  4,  5,  6,  7 },  // Byte 0
  {  8,  9, 10, 11, 12, 13, 14, 15 }   // Byte 1
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
    case MRC_SPD_LPDDR5_SDRAM_TYPE_NUMBER:
      // No XMP Support for LPDDR3/4
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
#pragma pack (push, 1)
  typedef struct {
    UINT16 Start;
    UINT16 End;
    UINT8  BootMode;
    UINT8  Profile;
  } SpdOffsetTable;
#pragma pack (pop)
  static const SpdOffsetTable Ddr4Table[] = {
    {   0,               1,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    {   2,               2,           (1 << bmCold) | (1 << bmFast),                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    {   3,              40,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 117,             131,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { SPD4_MANUF_START, SPD4_MANUF_END, (1 << bmCold) | (1 << bmWarm) | (1 << bmFast), (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 329,             348,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
#if (SUPPORT_SPD_CRC == SUPPORT)
    {  32,             119,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 126,             255,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 349,             383,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
#endif
    { 384,             387,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 388,             389,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 393,             431,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 440,             478,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
  };
  static const SpdOffsetTable LpddrTable[] = {
    {   0,               1,               (1 << bmCold),                                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    {   2,               2,               (1 << bmCold) | (1 << bmFast),                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    {   3,              32,               (1 << bmCold),                                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 120,             130,               (1 << bmCold),                                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { SPDLP_MANUF_START, SPDLP_MANUF_END, (1 << bmCold) | (1 << bmWarm) | (1 << bmFast), (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 329,             383,               (1 << bmCold),                                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) }
  };
  MrcInput              *Inputs;
  MrcDebug              *Debug;
  MrcControllerIn       *ControllerIn;
  MrcChannelIn          *ChannelIn;
  MrcDimmIn             *DimmIn;
  UINT8                 *Buffer;
  const SpdOffsetTable  *Tbl;
  const SpdOffsetTable  *TableSelect;
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
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
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
                  TableSelect = Ddr4Table;
                  Stop = (sizeof (Ddr4Table) / sizeof (SpdOffsetTable));
                  break;

                case MRC_SPD_LPDDR4_SDRAM_TYPE_NUMBER:
                case MRC_SPD_LPDDR4X_SDRAM_TYPE_NUMBER:
                case MRC_SPD_LPDDR5_SDRAM_TYPE_NUMBER:
                  TableSelect = LpddrTable;
                  Stop = (sizeof (LpddrTable) / sizeof (SpdOffsetTable));
                  break;
              }
              for (Index = 0; (Status == mrcSuccess) && (Index < Stop); Index++) {
                Tbl = &TableSelect[Index];
                if (((1 << BootMode) & Tbl->BootMode) && ((1 << Inputs->MemoryProfile) & Tbl->Profile)) {
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
                        MRC_DEBUG_MSG (
                          Debug,
                          MSG_LEVEL_NOTE,
                          "VerifyXmp FALSE\n"
                          );
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

  @retval The current CPU time in milliseconds.
**/
UINT64
GetCpuTime (
  void
  )
{
  UINT64 TimeBase;
  TimeBase = (1000 * MRC_SYSTEM_BCLK) * MrcGetCpuRatio (); //In Millisec
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
  Sets CpuModel and CpuStepping in MrcData based on CpuModelStep.

  @param[out] MrcData     - The Mrc Host data structure
  @param[in]  CpuModel    - The CPU Family Model.
  @param[in]  CpuStepping - The CPU Stepping.

  @retval mrcSuccess if the model and stepping is found.  Otherwise mrcFail
**/
MrcStatus
MrcSetCpuInformation (
  OUT MrcParameters  *MrcData,
  IN  MrcCpuModel    CpuModel,
  IN  MrcCpuStepping CpuStepping
  )
{
  const MRC_FUNCTION  *MrcCall;
  MrcInput            *Inputs;
  MrcDebug            *Debug;
  MrcStatus           Status;
  char                *Step;
  UINT64              Revision;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcFail;

  Inputs->CpuFamily   = cfMax;
  Inputs->TestEngine  = MrcTeMax;
  Step = NULL;

  //MRC host structure is Byte set to 0.  So Inputs->[DtHalo,Mobile] is FALSE by default
  switch (CpuModel) {
    case cmTGL_ULX_ULT:
      Inputs->CpuModel = cmTGL_ULX_ULT;
      Inputs->CpuFamily = cfTgl;
      Inputs->TestEngine = MrcTeCpgc20;
      Inputs->UlxUlt = TRUE;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TigerLake ULT/ULX:");

      switch (CpuStepping) {
        case csTglA0:
          Inputs->CpuStepping = csTglA0;
          Inputs->A0 = TRUE;
          Step = "A0";
          break;

        case csTglB0:
          Inputs->CpuStepping = csTglB0;
          Inputs->B0 = TRUE;
          Step = "B0";
          break;

        default:
          Inputs->CpuStepping = csTglUlxUltLast;
          break;
      }
      Status = mrcSuccess;
      break;

    case cmTGL_DT_HALO:
      Inputs->CpuModel = cmTGL_DT_HALO;
      Inputs->CpuFamily = cfTgl;
      Inputs->TestEngine = MrcTeCpgc20;
      Inputs->DtHalo = TRUE;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TigerLake DT/HALO:");

      switch (CpuStepping) {
        case csTglP0:
          Inputs->CpuStepping = csTglP0;
          Step = "P0";
          break;

        case csTglQ0:
          Inputs->CpuStepping = csTglQ0;
          Step = "Q0";
          break;

        default:
          Inputs->CpuStepping = csTglDtHaloLast;
          break;
      }

      Status = mrcSuccess;
      break;
  }

  if (Status == mrcSuccess) {
    if (Step != NULL) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Stepping %s\n", Step);
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\nWARNING: Unknown CPU stepping, using MRC for last known step = %Xh\n", Inputs->CpuStepping);
    }
  }

  Revision = MrcCall->MrcReadMsr64 (MSR_IA32_BIOS_SIGN_ID);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Microcode Update: 0x%08X\n", (UINT32) (MrcCall->MrcRightShift64 (Revision, 32)));

  return Status;
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

  MmioBase = PCH_PWRM_BASE_ADDRESS;
  Cfg2Offset = R_CNL_PCH_PMC_PWRM_CFG2;
  // Set DRAM RESET# value via PCH register
  PmCfg2 = MrcOemMmioRead32 (MmioBase + Cfg2Offset);
  PmCfg2 &= ~(B_PMC_PWRM_CFG2_DRAM_RESET_CTL);
  PmCfg2 |= (ResetValue << N_PMC_PWRM_CFG2_DRAM_RESET_CTL);
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
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Post Code: %Xh\n", DisplayDebugNumber);

  MrcOemOutPort16 (0x80, DisplayDebugNumber);
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
/// Example board support
#define EXAMPLE_BOARD_SUPPORT 0
#if (defined EXAMPLE_BOARD_SUPPORT && (EXAMPLE_BOARD_SUPPORT > 0))
/// For this example board, we have a dual channel, single slot configuration
/// with the same memory configuration in each channel (DDR3).
const MemorySlotStatus ExampleSlotStatus[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL] = {
  MEMORY_DOWN_ONLY,                     ///< Channel 0, Slot 0
  MEMORY_ABSENT,                        ///< Channel 0, Slot 1
  MEMORY_DOWN_ONLY,                     ///< Channel 1, Slot 0
  MEMORY_ABSENT,                        ///< Channel 1, Slot 1
};

const UINT8 ExampleSpd[] = {
  0x92,                                 ///< 0   Number of Serial PD Bytes Written / SPD Device Size / CRC Coverage 1, 2
  0x10,                                 ///< 1   SPD Revision
  0x0B,                                 ///< 2   DRAM Device Type
  0x03,                                 ///< 3   Module Type
  0x02,                                 ///< 4   SDRAM Density and Banks
  0x11,                                 ///< 5   SDRAM Addressing
  0x00,                                 ///< 6   Module Nominal Voltage
  0x09,                                 ///< 7   Module Organization
  0x03,                                 ///< 8   Module Memory Bus Width
  0x52,                                 ///< 9   Fine Timebase (FTB) Dividend / Divisor
  0x01,                                 ///< 10  Medium Timebase (MTB) Dividend
  0x08,                                 ///< 11  Medium Timebase (MTB) Divisor
  0x0A,                                 ///< 12  SDRAM Minimum Cycle Time (tCKmin)
  0x00,                                 ///< 13  Reserved0
  0xFE,                                 ///< 14  CAS Latencies Supported, Least Significant Byte
  0x00,                                 ///< 15  CAS Latencies Supported, Most Significant Byte
  0x69,                                 ///< 16  Minimum CAS Latency Time (tAAmin)
  0x78,                                 ///< 17  Minimum Write Recovery Time (tWRmin)
  0x69,                                 ///< 18  Minimum RAS# to CAS# Delay Time (tRCDmin)
  0x30,                                 ///< 19  Minimum Row Active to Row Active Delay Time (tRRDmin)
  0x69,                                 ///< 20  Minimum Row Precharge Delay Time (tRPmin)
  0x11,                                 ///< 21  Upper Nibbles for tRAS and tRC
  0x18,                                 ///< 22  Minimum Active to Precharge Delay Time (tRASmin), Least Significant Byte
  0x81,                                 ///< 23  Minimum Active to Active/Refresh Delay Time (tRCmin), Least Significant Byte
  0x70,                                 ///< 24  Minimum Refresh Recovery Delay Time (tRFCmin), Least Significant Byte
  0x03,                                 ///< 25  Minimum Refresh Recovery Delay Time (tRFCmin), Most Significant Byte
  0x3C,                                 ///< 26  Minimum Internal Write to Read Command Delay Time (tWTRmin)
  0x3C,                                 ///< 27  Minimum Internal Read to Precharge Command Delay Time (tRTPmin)
  0x00,                                 ///< 28  Upper Nibble for tFAW
  0xF0,                                 ///< 29  Minimum Four Activate Window Delay Time (tFAWmin)
  0x83,                                 ///< 30  SDRAM Optional Features
  0x01,                                 ///< 31  SDRAMThermalAndRefreshOptions
  0x00,                                 ///< 32  ModuleThermalSensor
  0x00,                                 ///< 33  SDRAM Device Type
  0x00,                                 ///< 34  Fine Offset for SDRAM Minimum Cycle Time (tCKmin)
  0x00,                                 ///< 35  Fine Offset for Minimum CAS Latency Time (tAAmin)
  0x00,                                 ///< 36  Fine Offset for Minimum RAS# to CAS# Delay Time (tRCDmin)
  0x00,                                 ///< 37  Fine Offset for Minimum Row Precharge Delay Time (tRPmin)
  0x00,                                 ///< 38  Fine Offset for Minimum Active to Active/Refresh Delay Time (tRCmin)
  0x00,                                 ///< 39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 40 - 49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
  0, 0,                                 ///< 60 - 61
  0x45,                                 ///< 62  Reference Raw Card Used
  0x00,                                 ///< 63  Address Mapping from Edge Connector to DRAM
  0x00,                                 ///< 64  ThermalHeatSpreaderSolution
  0, 0, 0, 0, 0,                        ///< 65 - 69
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 70 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
  0, 0, 0, 0, 0, 0, 0,                  ///< 110 - 116
  0x80,                                 ///< 117 Module Manufacturer ID Code, Least Significant Byte
  0xCE,                                 ///< 118 Module Manufacturer ID Code, Most Significant Byte
  0x01,                                 ///< 119 Module Manufacturing Location
  0x11,                                 ///< 120 Module Manufacturing Date Year
  0x02,                                 ///< 121 Module Manufacturing Date creation work week
  0x44,                                 ///< 122 Module Serial Number A
  0x0A,                                 ///< 123 Module Serial Number B
  0x83,                                 ///< 124 Module Serial Number C
  0x0C,                                 ///< 125 Module Serial Number D
  0xA5,                                 ///< 126 CRC A
  0x50                                  ///< 127 CRC B
};
#endif // EXAMPLE_BOARD_SUPPORT

const MemorySlotStatus TigerlakeSdsSlotStatus[MAX_CONTROLLER][MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL] = {
  //Controller 0
  {
  {MEMORY_DOWN_ONLY,                     ///< Channel 0, Slot 0
  MEMORY_ABSENT},                        ///< Channel 0, Slot 1
  {MEMORY_DOWN_ONLY,                     ///< Channel 1, Slot 0
  MEMORY_ABSENT},                        ///< Channel 1, Slot 1
  {MEMORY_DOWN_ONLY,                     ///< Channel 2, Slot 0
  MEMORY_ABSENT},                        ///< Channel 2, Slot 1
  {MEMORY_DOWN_ONLY,                     ///< Channel 3, Slot 0
  MEMORY_ABSENT}                        ///< Channel 3, Slot 1
  },
  //Controller 1
  {
  {MEMORY_DOWN_ONLY,                     ///< Channel 0, Slot 0
  MEMORY_ABSENT},                        ///< Channel 0, Slot 1
  {MEMORY_DOWN_ONLY,                     ///< Channel 1, Slot 0
  MEMORY_ABSENT},                        ///< Channel 1, Slot 1
  {MEMORY_DOWN_ONLY,                     ///< Channel 2, Slot 0
  MEMORY_ABSENT},                        ///< Channel 2, Slot 1
  {MEMORY_DOWN_ONLY,                     ///< Channel 3, Slot 0
  MEMORY_ABSENT}                         ///< Channel 3, Slot 1
  }
};

// LPDDR4 200b 8Gb die, DDP
// Samsung K4U6E304AC-MGCJ
// Hynix
// Micron
// 3200, 28-29-29-68
// 2 ranks per channel, 2 SDRAMs per rank, 4x8Gb = 4GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4xDdp8Gb200bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x10,                                 ///< 1   SPD Revision 1.0
  0x11,                                 ///< 2   DRAM Type: LPDDR4x SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x19,                                 ///< 5   15 Rows, 10 Columns
  0x95,                                 ///< 6   Non-Monolithic DRAM Device, 2 die, 2 Channels per package, Signal Loading Matrix 1
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
  0x05,                                 ///< 18  tCKAVGmin = 0.625 ns (LPDDR4-3200)
  0xFF,                                 ///< 19  tCKAVGmax = 32.002 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x55,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20, 16
  0x00,                                 ///< 22  CAS Latencies supported (Third Byte) :
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x8C,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.5 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xA0,                                 ///< 29  tRFCab = 180 ns (8 Gb)
  0x05,                                 ///< 30  tRFCab MSB
  0xD0,                                 ///< 31  tRFCpb = 90 ns (8 Gb)
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
  0x00,                                 ///< 123 FTB for tAAmin = 17.5 ns
  0x7F,                                 ///< 124 FTB for tCKAVGmax = 32.002 ns
  0x00,                                 ///< 125 FTB for tCKAVGmin = 0.625 ns (LPDDR4-3200)
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
  0x55,                                 ///< 325 Module Serial Number A
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

// LPDDR4x 432b 8Gb die, ODP
// Samsung K3UH7H70MMc-K3UH7H70MM
// Hynix
// Micron
// 3733, 28-29-29-68
// 2 ranks per channel, 2 SDRAMs per rank, 4x8Gb = 4GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4xDdp8Gb432bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x10,                                 ///< 1   SPD Revision 1.0
  0x11,                                 ///< 2   DRAM Type: LPDDR4x SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x21,                                 ///< 5   16 Rows, 10 Columns
  0xF9,                                 ///< 6   Non-Monolithic DRAM Device, 8 die, 4 Channels per package, Signal Loading Matrix 1
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x00,                                 ///< 9   Other SDRAM Optional Features: Post package repair not supported,Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x0A,                                 ///< 12  Module Organization: 2 Ranks, x16 Device Width per Channel
  0x22,                                 ///< 13  Module Memory Bus width: 2 Channels, 32 bits channel width, no ECC
  0x00,                                 ///< 14  Module Thermal Sensor: none
  0x00,                                 ///< 15  Extended Module Type: Reserved
  0x48,                                 ///< 16  Signal Loading: 2 loads on Data/Strobe/Mask, 2 Loads on Command/Address/Control/Clock
  0x00,                                 ///< 17  MTB = 0.125ns, FTB = 1 ps
  0x05,                                 ///< 18  tCKAVGmin = 0.536 ns (MTB = 0.625 ns) (LPDDR4-3733)
  0x0F,                                 ///< 19  tCKAVGmax = 1.875 ns (MTB = 1.875ns)
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x54,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20
  0x01,                                 ///< 22  CAS Latencies supported (Third Byte) : 32
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x8A,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.14 ns (MTB = 17.25ns)
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xC0,                                 ///< 29  tRFCab = 280 ns (6/8 Gb)
  0x08,                                 ///< 30  tRFCab MSB
  0x60,                                 ///< 31  tRFCpb = 140 ns (6/8 Gb)
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
  0x6A,                                 ///< 126 CRC A
  0x64,                                 ///< 127 CRC B
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
  0x55,                                 ///< 325 Module Serial Number A
  0x00,                                 ///< 326 Module Serial Number B
  0x00,                                 ///< 327 Module Serial Number C
  0x00,                                 ///< 328 Module Serial Number D
  0x4B, 0x33, 0x55, 0x48, 0x37,         ///< 329 - 333 Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x48, 0x37, 0x30, 0x4D, 0x4D,         ///< 334 - 338 Module Part Number
  0x2D, 0x4A, 0x47, 0x43, 0x4A,         ///< 339 - 343 Module Part Number
  0x00, 0x00, 0x00, 0x00, 0x00,         ///< 344 - 348 Module Part Number
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

// LPDDR4 200b 8Gb die, DDP
// Samsung K4F6E304Hx-MGCH
// Hynix   H9HCNNNBUUxLHR-NLx
// Micron  MT53B512M32D2NP-062
// 3200, 28-29-29-68
// 2 ranks per channel, 2 SDRAMs per rank, 4x8Gb = 4GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4Ddp8Gb200bSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x10,                                 ///< 1   SPD Revision 1.0
  0x10,                                 ///< 2   DRAM Type: LPDDR4 SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x19,                                 ///< 5   15 Rows, 10 Columns
  0x95,                                 ///< 6   Non-Monolithic DRAM Device, 2 die, 2 Channels per package, Signal Loading Matrix 1
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
  0x05,                                 ///< 18  tCKAVGmin = 0.625 ns (LPDDR4-3200)
  0xFF,                                 ///< 19  tCKAVGmax = 32.002 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x55,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20, 16
  0x00,                                 ///< 22  CAS Latencies supported (Third Byte) :
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x8C,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.5 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xA0,                                 ///< 29  tRFCab = 180 ns (8 Gb)
  0x05,                                 ///< 30  tRFCab MSB
  0xD0,                                 ///< 31  tRFCpb = 90 ns (8 Gb)
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
  0x00,                                 ///< 123 FTB for tAAmin = 17.5 ns
  0x7F,                                 ///< 124 FTB for tCKAVGmax = 32.002 ns
  0x00,                                 ///< 125 FTB for tCKAVGmin = 0.625 ns (LPDDR4-3200)
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
  0x55,                                 ///< 325 Module Serial Number A
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


// LPDDR5 5500MHz 496b 8Gb die, ODP 2Rx16
// SKHynix VT8TH019C1
// 16 Row bits, 10 Column bits, 8 Banks
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr5xQdp8Gb496bSpd[] = {
  // ************************************
  // Placeholder need correct SPD for LP5
  // ************************************
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x10,                                 ///< 1   SPD Revision 1.0
  0x12,                                 ///< 2   DRAM Type: LPDDR4x SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x21,                                 ///< 5   16 Rows, 10 Columns
  0xF8,                                 ///< 6   Non-Monolithic DRAM Device, 8 die, 4 Channels per package, Signal Loading Matrix 1
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x0A,                                 ///< 12  Module Organization: 2 Ranks, x16 Device Width per Channel
  0x01,                                 ///< 13  Module Memory Bus width: 1 Channels, 16 bits channel width, no ECC
  0x00,                                 ///< 14  Module Thermal Sensor: none
  0x00,                                 ///< 15  Extended Module Type: Reserved
  0x48,                                 ///< 16  Signal Loading: Data/Strobe/Mask: 2 loads, CAC: 2 loads, CS: 1 load
  0x00,                                 ///< 17  MTB = 0.125ns, FTB = 1 ps
  0x0C,                                 ///< 18  tCKAVGmin = 1.455 ns (LPDDR5-5500)
  0xFF,                                 ///< 19  tCKAVGmax = 32.002 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x55,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20, 16
  0x00,                                 ///< 22  CAS Latencies supported (Third Byte) :
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x8C,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.5 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x98,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 19 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPpb) = 18 ns
  0xC0,                                 ///< 29  tRFCab = 280 ns (8 Gb quad-channel die)
  0x08,                                 ///< 30  tRFCab MSB
  0x60,                                 ///< 31  tRFCpb = 140 ns (8 Gb quad-channel die)
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
  0x00,                                 ///< 122 FTB for Minimum RAS-to-CAS delay (tRCDmin) = 19 ns
  0x00,                                 ///< 123 FTB for tAAmin = 17.5 ns
  0x7F,                                 ///< 124 FTB for tCKAVGmax = 32.002 ns
  0xD3,                                 ///< 125 FTB for tCKAVGmin = 1.455 ns (LPDDR5-5500)
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

// LPDDR5 5500MHz 496b 12Gb die, ODP 1Rx16
// Samsung K3LK3K30CM-BGCN
// 16 Row bits, 10 Column bits, 8 Banks
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr5xQdp12Gb496bSpd[] = {
  // ************************************
  // Placeholder need correct SPD for LP5
  // ************************************
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x10,                                 ///< 1   SPD Revision 1.0
  0x12,                                 ///< 2   DRAM Type: LPDDR4x SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x88,                                 ///< 4   8 Banks, no bank groups, 12 Gb SDRAM density
  0x29,                                 ///< 5   17 Rows, 10 Columns
  0xB0,                                 ///< 6   Non-Monolithic DRAM Device, 4 die, 1 Channels per package, Signal Loading Matrix 1
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x02,                                 ///< 12  Module Organization: 1 Ranks, x16 Device Width per Channel
  0x01,                                 ///< 13  Module Memory Bus width: 1 Channels, 16 bits channel width, no ECC
  0x00,                                 ///< 14  Module Thermal Sensor: none
  0x00,                                 ///< 15  Extended Module Type: Reserved
  0x48,                                 ///< 16  Signal Loading: Data/Strobe/Mask: 2 loads, CAC: 2 loads, CS: 1 load
  0x00,                                 ///< 17  MTB = 0.125ns, FTB = 1 ps
  0x0C,                                 ///< 18  tCKAVGmin = 1.455 ns (LPDDR5-5500)
  0xFF,                                 ///< 19  tCKAVGmax = 32.002 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x55,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20, 16
  0x00,                                 ///< 22  CAS Latencies supported (Third Byte) :
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x8C,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.5 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x98,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 19 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPpb) = 18 ns
  0xC0,                                 ///< 29  tRFCab = 280 ns (8 Gb quad-channel die)
  0x08,                                 ///< 30  tRFCab MSB
  0x60,                                 ///< 31  tRFCpb = 140 ns (8 Gb quad-channel die)
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
  0x00,                                 ///< 122 FTB for Minimum RAS-to-CAS delay (tRCDmin) = 19 ns
  0x00,                                 ///< 123 FTB for tAAmin = 17.5 ns
  0x7F,                                 ///< 124 FTB for tCKAVGmax = 32.002 ns
  0xD3,                                 ///< 125 FTB for tCKAVGmin = 1.455 ns (LPDDR5-5500)
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

GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4Ddp16Gb200b1r4267Spd[] = {
  0x23,                                 ///< 0 384 SPD bytes used, 512 total
  0x10,                                 ///< 1 SPD Revision 1.0
  0x11,                                 ///< 2 DRAM Type: LPDDR4X SDRAM
  0x0E,                                 ///< 3 Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4 8 Banks, no bank groups, 8 Gb SDRAM density
  0x19,                                 ///< 5 15 Rows, 10 Columns
  0x95,                                 ///< 6 Non-Monolithic DRAM Device, 2 die, 2 Channels per package, Signal Loading Matrix 1
  0x08,                                 ///< 7 SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8 SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9 Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10 Reserved
  0x00,                                 ///< 11 Module Nominal Voltage: Reserved
  0x02,                                 ///< 12 Module Organization: 1 Ranks, x16 Device Width per Channel
  0x21,                                 ///< 13 Module Memory Bus width: 2 Channels, 16 bits channel width, no ECC
  0x00,                                 ///< 14 Module Thermal Sensor: none
  0x00,                                 ///< 15 Extended Module Type: Reserved
  0x48,                                 ///< 16 Signal Loading: Data/Strobe/Mask: 2 loads, CAC: 2 loads, CS: 1 load
  0x00,                                 ///< 17 MTB = 0.125ns, FTB = 1 ps
  0x04,                                 ///< 18  tCKAVGmin = 0.469 ns (LPDDR4-4267)
  0xFF,                                 ///< 19  tCKAVGmax = 32.002 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x55,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20, 16
  0x00,                                 ///< 22  CAS Latencies supported (Third Byte) :
  0x00,                                 ///< 23 CAS Latencies supported (Fourth Byte):
  0x8C,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.5 ns
  0x00,                                 ///< 25 Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26 Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27 Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28 Minimum row precharge time (tRPmin) = 18 ns
  0x90,                                 ///< 29 tRFCab = 210 ns (16 Gb dual-channel die)
  0x06,                                 ///< 30 tRFCab MSB
  0xD0,                                 ///< 31 tRFCpb = 90 ns (16 Gb dual-channel die)
  0x02,                                 ///< 32 tRFCpb MSB
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
  0x7F,                                 ///< 124 FTB for tCKAVGmax = 32.002 ns
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
  0x55,                                 ///< 325 Module Serial Number A
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

GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4Ddp16Gb200b1r3200Spd[] = {
  0x23,                                 ///< 0 384 SPD bytes used, 512 total
  0x10,                                 ///< 1 SPD Revision 1.0
  0x11,                                 ///< 2 DRAM Type: LPDDR4X SDRAM
  0x0E,                                 ///< 3 Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4 8 Banks, no bank groups, 8 Gb SDRAM density
  0x19,                                 ///< 5 15 Rows, 10 Columns
  0x95,                                 ///< 6 Non-Monolithic DRAM Device, 2 die, 2 Channels per package, Signal Loading Matrix 1
  0x08,                                 ///< 7 SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8 SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9 Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10 Reserved
  0x00,                                 ///< 11 Module Nominal Voltage: Reserved
  0x02,                                 ///< 12 Module Organization: 1 Ranks, x16 Device Width per Channel
  0x21,                                 ///< 13 Module Memory Bus width: 2 Channels, 16 bits channel width, no ECC
  0x00,                                 ///< 14 Module Thermal Sensor: none
  0x00,                                 ///< 15 Extended Module Type: Reserved
  0x48,                                 ///< 16 Signal Loading: Data/Strobe/Mask: 2 loads, CAC: 2 loads, CS: 1 load
  0x00,                                 ///< 17 MTB = 0.125ns, FTB = 1 ps
  0x05,                                 ///< 18  tCKAVGmin = 0.625 ns (LPDDR4-3200)
  0xFF,                                 ///< 19  tCKAVGmax = 32.002 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x55,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20, 16
  0x00,                                 ///< 22  CAS Latencies supported (Third Byte) :
  0x00,                                 ///< 23 CAS Latencies supported (Fourth Byte):
  0x8C,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.5 ns
  0x00,                                 ///< 25 Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26 Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27 Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28 Minimum row precharge time (tRPmin) = 18 ns
  0x90,                                 ///< 29 tRFCab = 210 ns (16 Gb dual-channel die)
  0x06,                                 ///< 30 tRFCab MSB
  0xD0,                                 ///< 31 tRFCpb = 90 ns (16 Gb dual-channel die)
  0x02,                                 ///< 32 tRFCpb MSB
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
  0x7F,                                 ///< 124 FTB for tCKAVGmax = 32.002 ns
  0x00,                                 ///< 125 FTB for tCKAVGmin = 0.625 ns (LPDDR4-3200)
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
  0x55,                                 ///< 325 Module Serial Number A
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


// LPDDR4 200b 8Gb die, DDP
// Samsung K4F6E304Hx-MGCH
// Hynix   H9HCNNNBUUxLHR-NLx
// Micron  MT53B512M32D2NP-062
// 3200, 28-29-29-68
// 2 ranks per channel, 2 SDRAMs per rank, 4x8Gb = 4GB total per channel
// Modified for single sub-channel, hence 2GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mLpddr4Ddp8Gb200bSingleSubchSpd[] = {
  0x23,                                 ///< 0   384 SPD bytes used, 512 total
  0x10,                                 ///< 1   SPD Revision 1.0
  0x10,                                 ///< 2   DRAM Type: LPDDR4 SDRAM
  0x0E,                                 ///< 3   Module Type: Not Hybrid (DRAM only) / Non-DIMM Solution (on-board DRAM)
  0x15,                                 ///< 4   8 Banks, no bank groups, 8 Gb SDRAM density
  0x19,                                 ///< 5   15 Rows, 10 Columns
  0x95,                                 ///< 6   Non-Monolithic DRAM Device, 2 die, 2 Channels per package, Signal Loading Matrix 1
  0x08,                                 ///< 7   SDRAM Optional Features: tMAW = 8192 * tREFI, Unlimited MAC
  0x00,                                 ///< 8   SDRAM Thermal / Refresh options: Reserved
  0x40,                                 ///< 9   Other SDRAM Optional Features: Post package repair supported, one row per bank group, Soft PPR not supported
  0x00,                                 ///< 10  Reserved
  0x00,                                 ///< 11  Module Nominal Voltage: Reserved
  0x0A,                                 ///< 12  Module Organization: 2 Ranks, x16 Device Width per Channel
  0x02,                                 ///< 13  Module Memory Bus width: 1 Channel, 32 bits channel width, no ECC
  0x00,                                 ///< 14  Module Thermal Sensor: none
  0x00,                                 ///< 15  Extended Module Type: Reserved
  0x48,                                 ///< 16  Signal Loading: Data/Strobe/Mask: 2 loads, CAC: 2 loads, CS: 1 load
  0x00,                                 ///< 17  MTB = 0.125ns, FTB = 1 ps
  0x05,                                 ///< 18  tCKAVGmin = 0.625 ns (LPDDR4-3200)
  0xFF,                                 ///< 19  tCKAVGmax = 32.002 ns
  0x92,                                 ///< 20  CAS Latencies supported (First Byte) : 14, 10, 6
  0x55,                                 ///< 21  CAS Latencies supported (Second Byte): 28, 24, 20, 16
  0x00,                                 ///< 22  CAS Latencies supported (Third Byte) :
  0x00,                                 ///< 23  CAS Latencies supported (Fourth Byte):
  0x8C,                                 ///< 24  Minimum CAS Latency (tAAmin) = 17.5 ns
  0x00,                                 ///< 25  Read and Write Latency Set options: Write Latency Set A and DBI-Read Disabled
  0x90,                                 ///< 26  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8,                                 ///< 27  Row precharge time for all banks (tRPab) = 21 ns
  0x90,                                 ///< 28  Minimum row precharge time (tRPmin) = 18 ns
  0xA0,                                 ///< 29  tRFCab = 180 ns (8 Gb)
  0x05,                                 ///< 30  tRFCab MSB
  0xD0,                                 ///< 31  tRFCpb = 90 ns (8 Gb)
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
  0x00,                                 ///< 123 FTB for tAAmin = 17.5 ns
  0x7F,                                 ///< 124 FTB for tCKAVGmax = 32.002 ns
  0x00,                                 ///< 125 FTB for tCKAVGmin = 0.625 ns (LPDDR4-3200)
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
  0x55,                                 ///< 325 Module Serial Number A
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
  IN     const UINT8             *SpdIn[MAX_CONTROLLER][MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL],
  IN     const MemorySlotStatus  *Slot,
  IN     UINT16                  SpdSize
  )
{
  MrcInput  *Inputs;
  MrcDimmIn *DimmIn;
  MrcOutput *Outputs;
  MrcDebug  *Debug;
  UINT8     Controller;
  UINT8     Channel;
  UINT8     Dimm;

  if (SpdIn == NULL || Slot == NULL || SpdSize == 0) {
    return;
  }

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++, Slot++) {
        DimmIn = &Inputs->Controller[Controller].Channel[Channel].Dimm[Dimm];
        switch (*Slot) {
        case MEMORY_DOWN_ONLY:
          DimmIn->SpdAddress  = 0;
          // Check user request to disable DIMM/rank pair.
          if (DimmIn->Status != DIMM_DISABLED) {
            DimmIn->Status = DIMM_ENABLED;
          MrcOemMemoryCpy ((UINT8 *) &DimmIn->Spd.Data, (UINT8 *) SpdIn[Controller][Channel][Dimm], SpdSize);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Memory down present on controller %u, channel %u, dimm %u\n", Controller, Channel, Dimm);
          } else {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Memory down absent on controller %u, channel %u, dimm %u\n", Controller, Channel, Dimm);
          }
          break;

        case MEMORY_ABSENT:
          DimmIn->Status      = DIMM_DISABLED;
          DimmIn->SpdAddress  = 0;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Memory down absent on controller %u, channel %u, dimm %u\n", Controller, Channel, Dimm);
          break;

        case MEMORY_SLOT_ONLY:
        default:
          break;
        }
      }
    }
  }

  return;
}

/**
  Enables Memory Down support and sets SPD data for all DIMMs needing support.

  @param[in] MrcData    - MRC global data structure.
  @param[in] BoardId    - The ID of the board.
  @param[in] SpdPresent - SPD is present or memory is down.

  @retval Nothing
**/
void
EnableMemoryDown (
  IN MrcParameters *const MrcData,
  IN const UINT16         BoardId,
  IN const BOOLEAN        SpdPresent
  )
{
  MrcInput                *Inputs;
  const UINT8             *SpdIn[MAX_CONTROLLER][MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
  const MemorySlotStatus  *Slot;
  UINT16                  SpdSize;
  UINT8                   Controller;
  UINT8                   Channel;
  UINT8                   Dimm;

  Inputs  = &MrcData->Inputs;
  Channel = 0;
  Dimm    = 0;
  SpdSize = 0;
  Slot    = NULL;

  switch (BoardId) {
#if (defined EXAMPLE_BOARD_SUPPORT && (EXAMPLE_BOARD_SUPPORT > 0))
    case 0:
      // BoardIdExample:
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            SpdIn[Controller][Channel][Dimm] = ExampleSpd;
          }
        }
      }

      Slot = (const MemorySlotStatus *) &ExampleSlotStatus[0][0];
      SpdSize = sizeof(ExampleSpd);
      break;
#endif // EXAMPLE_BOARD_SUPPORT

    // Add additional boards that support memory down here.

    case BoardIdTglULp4Type4:
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          SpdIn[Controller][Channel][0] = mLpddr4Ddp16Gb200b1r4267Spd;
        }
      }
      Slot = (const MemorySlotStatus *) &TigerlakeSdsSlotStatus[0][0][0];
      SpdSize = sizeof (mLpddr4Ddp16Gb200b1r4267Spd);
      break;

    case BoardIdTglULp5Type4:
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          SpdIn[Controller][Channel][0] = mLpddr5xQdp12Gb496bSpd;
        }
      }
      Slot = (const MemorySlotStatus *) &TigerlakeSdsSlotStatus[0][0][0];
      SpdSize = sizeof (mLpddr5xQdp12Gb496bSpd);
      break;

    // The default case means the board ID was not recognized.  Instead
    // we set Slot = NULL thus forcing us to read from the SPD.
    default:
      Slot  = NULL;
  }

  CopyMemoryDownSpd (MrcData, SpdIn, Slot, SpdSize);

  return;
}
#endif // MEMORY_DOWN_SUPPORT

/**
  Initialize the board-specific CMD/CTL/CLK and DQ/DQS mapping for LPDDR3.

  @param[in, out] MrcData - MRC global data structure.
  @param[in]      BoardId - The ID of the board.

**/
void
MrcOemLpddrBoardMapping (
  IN MrcParameters *const MrcData,
  IN UINT16        BoardId
  )
{
  MrcDebug        *Debug;
  MrcInput        *Inputs;
  MrcChannelIn    *ChannelIn;
  UINT32          Controller;
  UINT32          Channel;
  UINT32          Byte;
  UINT32          Bit;
  UINT8           *DqsMapCpu2Dram;
  UINT8           *DqsMapCpu2DramMcCh[MAX_CONTROLLER][MAX_CHANNEL];
  UINT8           *DqMapCpu2DramMcCh[MAX_CONTROLLER][MAX_CHANNEL];
  char            *BoardName;

  Inputs = &MrcData->Inputs;
  Debug  = &MrcData->Outputs.Debug;
  if (!((BoardId == BoardIdTglULp4Type4)  ||
        (BoardId == BoardIdTglULp5Type4)  ||
        (BoardId == BoardIdTglYLp4Type4)  ||
        (BoardId == BoardIdTglULp4Aep)
       )) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Not an LPDDR board! BoardId = 0x%x\n", BoardId);
    return;
  }
  DqsMapCpu2Dram    = NULL;
  // Set array to 0
  MrcOemMemorySet ((UINT8 *) DqsMapCpu2DramMcCh, sizeof (DqsMapCpu2DramMcCh), 0);
  MrcOemMemorySet ((UINT8 *) DqMapCpu2DramMcCh, sizeof (DqMapCpu2DramMcCh), 0);

  BoardName = "";
  switch (BoardId) {
    case BoardIdTglULp4Type4:
      BoardName = "TGL-U LPDDR4 Type-4 RVP";
      break;

    case BoardIdTglULp5Type4:
      BoardName = "TGL-U LPDDR5 Type-4 RVP";
      break;

    case BoardIdTglYLp4Type4:
      BoardName = "TGL-Y LPDDR4 Type-4 RVP";
      break;

    case BoardIdTglULp4Aep:
      BoardName = "TGL-U LPDDR4 EAP";
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Unknown board! BoardId = 0x%x\n", BoardId);
      MRC_DEADLOOP ();
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Detected board: %s\n", BoardName);

  switch (BoardId) {
    case BoardIdTglULp4Type4:
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          DqsMapCpu2DramMcCh[Controller][Channel] = (UINT8 *) DqsMapCpu2DramTglULp4Rvp5[Controller * MAX_CHANNEL + Channel];
          DqMapCpu2DramMcCh[Controller][Channel] = (UINT8 *) DqMapCpu2DramTglULp4Rvp5[Controller * MAX_CHANNEL + Channel];
        }
      }
      break;

    case BoardIdTglULp4Aep:
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          DqsMapCpu2DramMcCh[Controller][Channel] = (UINT8 *) DqsMapCpu2DramTglULp4Aep[Controller * MAX_CHANNEL + Channel];
          DqMapCpu2DramMcCh[Controller][Channel] = (UINT8 *) DqMapCpu2DramTglULp4Aep[Controller * MAX_CHANNEL + Channel];
        }
      }
      break;

    case BoardIdTglULp5Type4:
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          DqsMapCpu2DramMcCh[Controller][Channel] = (UINT8 *) DqsMapCpu2DramBoardIdTglULp5Type4[Controller * MAX_CHANNEL + Channel];
          DqMapCpu2DramMcCh[Controller][Channel] = (UINT8 *) DqMapCpu2DramBoardIdTglULp5Type4[Controller * MAX_CHANNEL + Channel];
        }
      }
      break;

    case BoardIdIclUSds:
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          DqsMapCpu2DramMcCh[Controller][Channel] = (UINT8 *) DqsMapCpu2DramLpNoSwizzle[0];
        }
      }
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "DQS mapping is not provided! BoardId = 0x%x\n", BoardId);
      MRC_DEADLOOP ();
  }


  // DQS byte swizzling between CPU and DRAM
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn = &Inputs->Controller[Controller].Channel[Channel];
      DqsMapCpu2Dram = ChannelIn->DqsMapCpu2Dram;
      if (DqsMapCpu2DramMcCh[Controller][Channel] != NULL) {
        MrcOemMemoryCpy ((UINT8 *) DqsMapCpu2Dram, DqsMapCpu2DramMcCh[Controller][Channel], sizeof (DqsMapCpu2Dram));
      }
      if (DqMapCpu2DramMcCh[Controller][Channel] != NULL) {
        MrcOemMemoryCpy ((UINT8 *) ChannelIn->DqMapCpu2Dram, DqMapCpu2DramMcCh[Controller][Channel], sizeof (ChannelIn->DqMapCpu2Dram));
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Mc%u.Ch%u DqsMapCpu2Dram: ", Controller, Channel);
      for (Byte = 0; Byte < MAX_BYTE_IN_LP_CHANNEL; Byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%d ", DqsMapCpu2Dram[Byte]);
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "DqMapCpu2Dram: ");
      for (Byte = 0; Byte < MAX_BYTE_IN_LP_CHANNEL; Byte++) {
        for (Bit = 0; Bit < MAX_BITS; Bit++) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%d ", ChannelIn->DqMapCpu2Dram[Byte][Bit]);
        }
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n");
    }
  }
}

/**
  Initialize the board-specific RCOMP values.

  @param[in, out] MrcData - MRC global data structure.
**/
void
MrcOemRcompValues (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput  *Inputs;
  const UINT16 *RcompResistor;       // Reference RCOMP resistors on motherboard
  const UINT16 *RcompTarget;         // RCOMP target values for DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv

  Inputs = &MrcData->Inputs;

  RcompResistor = NULL;
  RcompTarget   = NULL;
  // Set the on-board RCOMP resistors and RCOMP target values for DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv
  // These values are for ULT/ULX LPDDR3
  if (RcompResistor != NULL) {
     Inputs->RcompResistor = *RcompResistor;
  }
  if (RcompTarget != NULL) {
    MrcOemMemoryCpy ((UINT8 *) Inputs->RcompTarget, (UINT8 *) RcompTarget, sizeof (MrcData->Inputs.RcompTarget));
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
  UINT64 PrmrrBase,
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
  Perform Total Memory Encryption initialization.

  @param[in] TmeEnable      - TME policy enable
  @param[in] TmeExcludeBase - Base physical address to be excluded for TME encryption
  @param[in] TmeExcludeSize - Size of range to be excluded from TME encryption

  @retval VOID - No value to return
**/
VOID
MrcTmeInit (
  IN UINT32 TmeEnable,
  IN UINT64 TmeExcludeBase,
  IN UINT64 TmeExcludeSize
  )
{
  UINT64            TmeCapability;
  UINT64            TmeActivate;
  EFI_STATUS        Status;
  UINT32            TmeSupported;

  TmeCapability = 0;
  TmeActivate   = 0;
  Status        = 0;
  TmeSupported  = 0;

  ///
  /// Verify TME supported through CPUID.7.0.ECX.13
#ifdef __GNUC__  // GCC compiler
  //@todo:
#else
  ASM {
    mov   ecx, 7
    cpuid
    and   ecx, MRC_BIT13
    shr   ecx, 13
    mov   TmeSupported, ecx
  }
#endif // __GNUC__
  if (!((BOOLEAN) TmeSupported)) {
    return;
  }

  ///
  /// Read IA32_TME_CAPABILITY MSR (981H) to determine supported encryption policy
  /// ICL currently only supports AES-XTS
  ///
  TmeCapability = ReadMsr64 (MSR_IA32_TME_CAPABILITY);

  if (TmeCapability & B_TME_CAPABILITY_AES_XTS) {
    ///
    /// Set TME policy - BIT[7:4]
    ///
    TmeActivate |= (UINT64)(V_TME_ACTIVATE_TME_POLICY_AES_XTS << N_TME_ACTIVATE_TME_POLICY_OFFSET);
  } else {
    return;
  }

  if (TmeEnable) {
    ///
    /// Set TME enable - BIT[1]
    ///
    TmeActivate |= B_TME_ACTIVATE_TME_ENABLE;

    ///
    /// Configure IA32_TME_EXCLUDE_MASK (983H) with TME Mask and Enable bit
    ///
    if (TmeExcludeSize != 0) {
      WriteMsr64 (MSR_IA32_TME_EXCLUDE_MASK, TmeExcludeSize | B_TME_EXCLUDE_MASK_ENABLE);
    }

    ///
    /// Configure IA32_TME_EXCLUDE_BASE (984H) with TME Base
    ///
    if (TmeExcludeBase != 0) {
      WriteMsr64 (MSR_IA32_TME_EXCLUDE_BASE, TmeExcludeBase);
    }

    ///
    /// Set TME Key Select and Save Key
    /// Please note: MiniBios does not support system S3 flow. Please see TmeInit () in CpuInitPeim.c for complete flow
    /// Key Select - BIT[2]
    ///   - Clear for cold/warm boot to create new TME keys
    /// Save Key For Standby - BIT[3]
    ///   - Set for cold/warm boot to save key into storage
    ///
    TmeActivate &= ~B_TME_ACTIVATE_KEY_SELECT;
    TmeActivate |= B_TME_ACTIVATE_SAVE_KEY;

    ///
    /// Configure IA32_TME_ACTIVATE MSR (982H) with TME Enable, Key Select, Save Key, and TME Policy
    /// Lock [BIT0] will be set upon successful WRMSR for IA32_TME_ACTIVATE.
    ///   - First SMI will also set the Lock
    ///   - This will also lock IA32_TME_EXCLUDE_MASK and IA32_TME_EXCLUDE_BASE
    ///
    WriteMsr64 (MSR_IA32_TME_ACTIVATE, TmeActivate);
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

  @param[in, out] MrcData - MRC global data structure.

  @retval BOOLEAN - TRUE if MrcSave exists, otherwise FALSE.
**/
BOOLEAN
MrcSaveExists (
  IN OUT MrcParameters *const MrcData
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
  return (0xE0000000 + (UINTN) (Bus << 20) + (UINTN) (Device << 15) + (UINTN) (Function << 12));
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
