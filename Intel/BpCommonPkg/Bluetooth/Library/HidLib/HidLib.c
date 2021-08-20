//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  The library provides HID Class standard and specific requests defined
  in HID Specification

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include <Library/HidLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>

#define EFI_ATTRIBUTE_START_NOTIFY          0x1B
#define EFI_ATTRIBUTE_START_INDICATE        0x1D
#define EFI_ATTRIBUTE_START_STOP_NOTIFY     0x00
#define EFI_ATTRIBUTE_START_STOP_INDICATE   0x00

/**
  Set the idle rate of the specified BT HID report.

  Submit a BT set HID report idle request for the BT device specified by HID,
  Interface, and ReportId, and set the idle rate to the value specified by Duration.

  @param  Hid         A pointer to the HID Protocol instance for the specific BT target.
  @param  ReportId    The identifier of the report to retrieve.
  @param  Duration    The idle rate to set for the specified BT target.

  @retval  EFI_SUCCESS       The request executed successfully.
  @retval  EFI_TIMEOUT       A timeout occurred executing the request.
  @retval  EFI_DEVICE_ERROR  The request failed due to a device error.

**/
EFI_STATUS
EFIAPI
HidSetIdleRequest (
  IN  EDKII_HID_PROTOCOL                *Hid,
  IN  UINT8                             ReportId,
  IN  UINT8                             Duration
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Get the idle rate of the specified BT HID report.

  Submit a BT get HID report idle request for the BT device specified by HID,
  Interface, and ReportId, and return the ide rate in Duration.


  @param  Hid         A pointer to the HID Protocol instance for the specific BT target.
  @param  ReportId    The identifier of the report to retrieve.
  @param  Duration    A pointer to the idle rate retrieved from the specified BT target.

  @retval  EFI_SUCCESS       The request executed successfully.
  @retval  EFI_TIMEOUT       A timeout occurred executing the request.
  @retval  EFI_DEVICE_ERROR  The request failed due to a device error.

**/
EFI_STATUS
EFIAPI
HidGetIdleRequest (
  IN  EDKII_HID_PROTOCOL                *Hid,
  IN  UINT8                             ReportId,
  OUT UINT8                             *Duration
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Set the report descriptor of the specified BT HID interface.

  Submit a BT set HID report request for the BT device specified by HID,
  Interface, ReportId, and ReportType, and set the report descriptor using the
  buffer specified by ReportLength and Report.

  @param  Hid         A pointer to the HID Protocol instance for the specific BT target.
  @param  ReportId      The identifier of the report to retrieve.
  @param  ReportType    The type of report to retrieve.
  @param  ReportLength  The size, in bytes, of Report.
  @param  Report        A pointer to the report descriptor buffer to set.

  @retval  EFI_SUCCESS       The request executed successfully.
  @retval  EFI_TIMEOUT       A timeout occurred executing the request.
  @retval  EFI_DEVICE_ERROR  The request failed due to a device error.

**/
EFI_STATUS
EFIAPI
HidSetReportRequest (
  IN EDKII_HID_PROTOCOL                 *Hid,
  IN UINT8                              ReportId,
  IN UINT8                              ReportType,
  IN UINT16                             ReportLen,
  IN UINT8                              *Report
  )
{
  EFI_STATUS                Status;

  Status = Hid->SendRequest (
                  Hid,
                  EdkiiHidRequestSetReport,
                  (UINT16) ((ReportType << 8) | ReportId),
                  ReportLen,
                  Report
                  );
  return Status;
}

/**
  Get the report descriptor of the specified BT HID interface.

  Submit a BT get HID report request for the BT device specified by HID,
  Interface, ReportId, and ReportType, and return the report in the buffer
  specified by Report.

  @param  Hid           A pointer to the HID Protocol instance for the specific BT target.
  @param  ReportId      The identifier of the report to retrieve.
  @param  ReportType    The type of report to retrieve.
  @param  ReportLength  The size, in bytes, of Report.
  @param  Report        A pointer to the buffer to store the report descriptor.

  @retval  EFI_SUCCESS           The request executed successfully.
  @retval  EFI_OUT_OF_RESOURCES  The request could not be completed because the
                                 buffer specified by ReportLength and Report is not
                                 large enough to hold the result of the request.
  @retval  EFI_TIMEOUT           A timeout occurred executing the request.
  @retval  EFI_DEVICE_ERROR      The request failed due to a device error.

**/
EFI_STATUS
EFIAPI
HidGetReportRequest (
  IN  EDKII_HID_PROTOCOL                *Hid,
  IN  UINT8                             ReportId,
  IN  UINT8                             ReportType,
  IN  UINT16                            ReportLen,
  OUT UINT8                             *Report
  )
{
  EFI_STATUS                Status;

  Status = Hid->SendRequest (
                  Hid,
                  EdkiiHidRequestGetReport,
                  (UINT16) ((ReportType << 8) | ReportId),
                  ReportLen,
                  Report
                  );
  return Status;
}

/**
  Asks the specific BT HID target to start sending updated values of
  characteristic.

  @param[in]  Hid  A pointer to the HID Protocol instance for the specific BT
                   target.

  @retval  Other  A value from other functions.

**/
EFI_STATUS
EFIAPI
HidStartNotification (
  IN  EDKII_HID_PROTOCOL                *Hid
  )
{
  return Hid->SetNotification (Hid, EFI_ATTRIBUTE_START_NOTIFY);
}

/**
  Asks the specific BT HID target to stop sending updated values of
  characteristic.

  @param[in]  Hid  A pointer to the HID Protocol instance for the specific BT
                   target.

  @retval  Other  A value from other functions.

**/
EFI_STATUS
EFIAPI
HidStopNotification (
  IN  EDKII_HID_PROTOCOL                *Hid
  )
{
  return Hid->SetNotification (Hid, EFI_ATTRIBUTE_START_STOP_NOTIFY);
}

/**
  Get report mode map.

  @param[in]      Hid           A pointer to the HID Protocol instance for the specific BT
                                target.
  @param[in,out]  ReportMapLen  The buffer size save the report map.
  @param[out]     ReportMap     The buffer save the report map.

  @retval  Other  A value from other functions.

**/
EFI_STATUS
EFIAPI
HidGetReportMap (
  IN EDKII_HID_PROTOCOL                 *Hid,
  IN OUT UINT16                         *ReportMapLen,
  OUT UINT8                             *ReportMap
  )
{
  EFI_STATUS                Status;

  Status = Hid->SendRequest (
                  Hid,
                  EdkiiHidRequestGetReportMap,
                  0,
                  *ReportMapLen,
                  ReportMap
                  );
  return Status;
}

/**
  Get the report refer descriptor.

  @param[in]  Hid  A pointer to the HID Protocol instance for the specific BT
                   target.

  @retval  Other  A value from other functions.

**/
EFI_STATUS
EFIAPI
HidGetReportReferDesc (
  IN EDKII_HID_PROTOCOL                 *Hid
  )
{
  EFI_STATUS                Status;

  Status = Hid->SendRequest (
                  Hid,
      EdkiiHidRequestGetReportReferDesc,
                  0,
                  0,
                  NULL
                  );
  return Status;
}
