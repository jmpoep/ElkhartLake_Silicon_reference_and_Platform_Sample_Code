//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
 Bluetooth HID Parser which is used to implement the report mode
 for hid device support.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/
#include "BluetoothHidParser.h"

// Types of items
#define GET_ITEM_TYPE(x)    ((x >> 2) & 0x3) // Type of item is conveyed in bit 3:2
#define ITEM_MAIN           0x0
#define ITEM_GLOBAL         0x1
#define ITEM_LOCAL          0x2
#define ITEM_RESERVED       0x3

#define GET_TAG(x)            (x >> 4)    // Type of tag is conveyed in bits 7:4
#define GET_LEN(x)            (x & 0x3)   // Figure the number of bytes to leave out
#define DATA_OR_CONSTANT(x)   (x & 0x01)
#define ARRAY_OR_VARIABLE(x)  ((x >> 1 ) & 0x01)
#define ABS_OR_REL(x)         ((x >> 2 ) & 0x01)
#define NOWRAP_OR_WRAP(x)     ((x >> 3 ) & 0x01)
#define LIN_OR_NONLIN(x)      ((x >> 4 ) & 0x01)
#define PREFSTATE_OR_NOT(x)   ((x >> 5 ) & 0x01)
#define NULL_STATE(x)         ((x >> 6 ) & 0x01)
#define NON_VOL_OR_VOL(x)     ((x >> 7 ) & 0x01)
#define BIT_FILED_BUFFBYTE(x) ((x >> 1 ) & 0x01)

#define IS_LONG_ITEM(x)      (((x & 0xf0) == 0xf0) ? 1 : 0) // If an Item is Long Item

// Types of Main Items
#define M_INPUT             0x8
#define M_OUTPUT            0x9
#define M_FEATURE           0xb
#define M_COLLECTION        0xa
#define M_END_COLLECTION    0xc

// Types of Global Items
#define G_USAGE_PAGE        0x0
#define G_LOGICAL_MIN       0x1
#define G_LOGICAL_MAX       0x2
#define G_PHYSICAL_MIN      0x3
#define G_PHYSICAL_MAX      0x4
#define G_UNIT_EXPONENT     0x5
#define G_UNIT              0x6
#define G_REPORT_SIZE       0x7
#define G_REPORT_ID         0x8
#define G_REPORT_COUNT      0x9
#define G_PUSH              0xa
#define G_POP               0xb

// Type of Local items
#define L_USAGE             0x0
#define L_USAGE_MIN         0x1
#define L_USAGE_MAX         0x2
#define L_DESIGNATOR_INDEX  0x3
#define L_DESIGNATOR_MIN    0x4
#define L_DESIGNATOR_MAX    0x5
#define L_STRING_INDEX      0x7
#define L_STRING_MIN        0x8
#define L_STRING_MAX        0x9
#define L_DELIMETER         0xa

// Other defines
#define USAGE_PAGE_DESKTOP  0x01
#define USAGE_KEYBOARD      0x07

STATIC HID_REPORT_FMT CurrentValues;

/**
  Add an item.

  @param[in] BtHidDev  Pointer to Bluetooth HID Device Structure.
  @param[in] Map       The buffer save the report map.
  @param[in] Cur       The cursor position.

**/
STATIC
VOID
AddItem(
  IN BT_HID_DEV *BtHidDev,
  IN UINT8  *Map,
  IN UINT16 Cur
  )
{
  HID_REPORT_FMT *Format;
  Format = AllocateZeroPool(sizeof(HID_REPORT_FMT));
  ASSERT (Format != NULL);

  // Save value
  Format->Signature    = ITEM_SIGNATURE;
  Format->DatConst     = DATA_OR_CONSTANT( Map[Cur + 1] );
  Format->ArrVar       = ARRAY_OR_VARIABLE( Map[Cur + 1] );
  Format->AbsRel       = ABS_OR_REL( Map[Cur + 1] );
  Format->Wrap         = NOWRAP_OR_WRAP( Map[Cur + 1] );
  Format->Linear       = LIN_OR_NONLIN( Map[Cur + 1] );
  Format->Preferred    = PREFSTATE_OR_NOT( Map[Cur + 1] );
  Format->NullPosState = NULL_STATE( Map[Cur + 1] );

  Format->UsageMin     = CurrentValues.UsageMin;
  Format->Usage        = CurrentValues.Usage;
  Format->UsagePage    = CurrentValues.UsagePage;
  Format->UsageMax     = CurrentValues.UsageMax;
  Format->LogicalMin   = CurrentValues.LogicalMin;
  Format->LogicalMax   = CurrentValues.LogicalMax;
  Format->ReportCount  = CurrentValues.ReportCount;
  Format->ReportSize   = CurrentValues.ReportSize;
  Format->ReportId     = CurrentValues.ReportId;
  Format->Type         = CurrentValues.Type;

  // Reset Local Items
  CurrentValues.UsageMin = 0;
  CurrentValues.UsageMax = 0;

  InsertTailList ( &BtHidDev->ReportFormatList, &Format->Link );
  return;
}

/**
  Handle the main item.

  @param[in] BtHidDev  Pointer to Bluetooth HID Device Structure.
  @param[in] Map       The buffer save the report map.
  @param[in] Cur       The cursor position.

**/
STATIC
VOID
MainItemHandler(
  IN BT_HID_DEV *BtHidDev,
  IN UINT8  *Map,
  IN UINT16 *Cur
  )
{
  switch ( GET_TAG(Map[*Cur]) )
  {
    case M_INPUT:
      CurrentValues.Type = M_INPUT;
      AddItem(BtHidDev, Map, *Cur);
      break;

    case M_OUTPUT:
      CurrentValues.Type = M_OUTPUT;
      AddItem(BtHidDev, Map, *Cur);
      break;

    case M_FEATURE:
      break;

    case M_COLLECTION:
      break;

    case M_END_COLLECTION:
      break;
  }

  *Cur += GET_LEN( Map[*Cur] );
}

/**
  Handle the global item.

  @param[in] Map       The buffer save the report map.
  @param[in] Cur       The cursor position.

**/
STATIC
VOID
GlobalItemHandler(
  IN UINT8  *Map,
  IN UINT16 *Cur
  )
{
  switch ( GET_TAG(Map[*Cur]) )
  {
    case G_USAGE_PAGE:
      CurrentValues.UsagePage = Map[*Cur + 1];
      break;

    case G_LOGICAL_MIN:
      CurrentValues.LogicalMin = Map[*Cur + 1];
      break;

    case G_LOGICAL_MAX:
      CurrentValues.LogicalMax = Map[*Cur + 1];
      break;

    case G_PHYSICAL_MIN:
      break;

    case G_PHYSICAL_MAX:
      break;

    case G_UNIT_EXPONENT:
      break;

    case G_UNIT:
      break;

    case G_REPORT_SIZE:
      CurrentValues.ReportSize = Map[*Cur + 1];
      break;

    case G_REPORT_ID:
      CurrentValues.ReportId = Map[*Cur + 1];
      break;

    case G_REPORT_COUNT:
      CurrentValues.ReportCount = Map[*Cur + 1];
      break;

    case G_PUSH:
      break;

    case G_POP:
      break;
  }

  *Cur += GET_LEN( Map[*Cur] );
}

/**
  Handle the local item.

  @param[in] Map       The buffer save the report map.
  @param[in] Cur       The cursor position.

**/
STATIC
VOID
LocalItemHandler(
  IN UINT8  *Map,
  IN UINT16 *Cur
  )
{
  switch ( GET_TAG(Map[*Cur]) )
  {
    case L_USAGE:
      CurrentValues.Usage = Map[*Cur + 1];
      break;

    case L_USAGE_MIN:
      CurrentValues.UsageMin = Map[*Cur + 1];
      break;

    case L_USAGE_MAX:
      CurrentValues.UsageMax = Map[*Cur + 1];
      break;

    case L_DESIGNATOR_INDEX:
      break;

    case L_DESIGNATOR_MIN:
      break;

    case L_DESIGNATOR_MAX:
      break;

    case L_STRING_INDEX:
      break;

    case L_STRING_MIN:
      break;

    case L_STRING_MAX:
      break;
  }

  *Cur += GET_LEN( Map[*Cur] );
}

/**
  Report Map Parser Function for the Report Mde Operation of Bluetooth HID devices

  @param[in]  BtHidDev Pointer to Bluetooth HID Device Structure.

**/
VOID
BtHidParseReportMap (
  IN BT_HID_DEV *BtHidDev
  )
{
  UINT8  *Map;
  UINT16 Cur;
  // set the cursor to the zeroth position
  Cur = 0;
  Map = BtHidDev->ReportMap;

  InitializeListHead (&BtHidDev->ReportFormatList);

  do {

    // Skip long items
    if (IS_LONG_ITEM(Map[Cur])) {
      Cur += Map[Cur + 1];
      continue;
    }

    // Process only the short items
    switch( GET_ITEM_TYPE(Map[Cur]) )
    {
      case ITEM_MAIN: MainItemHandler(BtHidDev, Map, &Cur);
        break;

      case ITEM_GLOBAL: GlobalItemHandler(Map, &Cur);
        break;

      case ITEM_LOCAL: LocalItemHandler(Map, &Cur);
        break;
    }

    // Scan till the end of the map, keep the cursor updated
    Cur ++;
  } while ( Cur < BtHidDev->ReportMapLen );
}

/**
  Fetches the Head of the Link List having the report format structures
  @param[in]  This        A pointer to the BT_HID_DEV_FROM_HID_PROTOCOL
                          instance.
  @param[out] Head Pointer to Report format linked list.

  @retval  EFI_SUCCESS  The function completes successfully.

**/
EFI_STATUS
EFIAPI
BtHidGetReportFormatList (
  IN EDKII_HID_PROTOCOL *This,
  OUT LIST_ENTRY        **Head
  )
{
  BT_HID_DEV *BtHidDev;
  BtHidDev   = BT_HID_DEV_FROM_HID_PROTOCOL (This);
  *Head = &BtHidDev->ReportFormatList;

  return EFI_SUCCESS;
}
