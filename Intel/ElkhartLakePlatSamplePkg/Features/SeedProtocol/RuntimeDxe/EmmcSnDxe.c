/** @file
  This file contains the Emmc code for Seed Protocol DXE driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

@par Specification

**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include <Protocol/SdMmcPassThru.h>
#include <Protocol/DevicePath.h>
#include <IndustryStandard/Emmc.h>
#include "EmmcSnDxe.h"

/* Take 2.5 seconds as generic time out value, 1 microsecond as unit. */
#define EMMC_GENERIC_TIMEOUT             2500 * 1000

/**
  Send command SELECT_DESELECT_CARD to the EMMC device to select/deselect it.

  Refer to EMMC Electrical Standard Spec 5.1 Section 6.10.4 for details.

  @param[in]  PassThru      A pointer to the EFI_SD_MMC_PASS_THRU_PROTOCOL instance.
  @param[in]  Slot          The slot number of the SD card to send the command to.
  @param[in]  Rca           The relative device address of selected device.

  @retval EFI_SUCCESS       The operation is done correctly.
  @retval Others            The operation fails.

**/
STATIC
EFI_STATUS
EmmcSelect (
  IN EFI_SD_MMC_PASS_THRU_PROTOCOL      *PassThru,
  IN UINT8                              Slot,
  IN UINT16                             Rca
  )
{
  EFI_SD_MMC_COMMAND_BLOCK              SdMmcCmdBlk;
  EFI_SD_MMC_STATUS_BLOCK               SdMmcStatusBlk;
  EFI_SD_MMC_PASS_THRU_COMMAND_PACKET   Packet;
  EFI_STATUS                            Status;

  ZeroMem (&SdMmcCmdBlk, sizeof (SdMmcCmdBlk));
  ZeroMem (&SdMmcStatusBlk, sizeof (SdMmcStatusBlk));
  ZeroMem (&Packet, sizeof (Packet));

  Packet.SdMmcCmdBlk    = &SdMmcCmdBlk;
  Packet.SdMmcStatusBlk = &SdMmcStatusBlk;
  Packet.Timeout        = EMMC_GENERIC_TIMEOUT;

  SdMmcCmdBlk.CommandIndex = EMMC_SELECT_DESELECT_CARD;
  SdMmcCmdBlk.CommandType  = SdMmcCommandTypeAc;
  SdMmcCmdBlk.ResponseType = SdMmcResponseTypeR1;
  SdMmcCmdBlk.CommandArgument = (UINT32)Rca << 16;

  Status = PassThru->PassThru (PassThru, Slot, &Packet, NULL);
  return Status;
}

/**
  Send command SEND_CID to the device to get the CID register data.

  @param[in]  Device            A pointer to the EMMC_DEVICE instance.
  @param[in]  Rca               The relative device address to use.
  @param[out] Cid               The buffer to store the EMMC_CID register data.

  @retval EFI_SUCCESS           The request is executed successfully.
  @retval EFI_OUT_OF_RESOURCES  The request could not be executed due to a lack of resources.
  @retval Others                The request could not be executed successfully.

**/
STATIC
EFI_STATUS
EmmcGetCid (
  IN     EFI_SD_MMC_PASS_THRU_PROTOCOL    *PassThru,
  IN     UINT16                           Rca,
  IN     UINT8                            Slot,
  OUT    EMMC_CID                         *Cid
)
{
  EFI_SD_MMC_COMMAND_BLOCK            SdMmcCmdBlk;
  EFI_SD_MMC_STATUS_BLOCK             SdMmcStatusBlk;
  EFI_SD_MMC_PASS_THRU_COMMAND_PACKET Packet;
  EFI_STATUS                          Status;

  ZeroMem (&SdMmcCmdBlk, sizeof (SdMmcCmdBlk));
  ZeroMem (&SdMmcStatusBlk, sizeof (SdMmcStatusBlk));
  ZeroMem (&Packet, sizeof (Packet));
  ZeroMem (Cid, sizeof (EMMC_CID));

  Packet.SdMmcCmdBlk    = &SdMmcCmdBlk;
  Packet.SdMmcStatusBlk = &SdMmcStatusBlk;
  Packet.Timeout        = EMMC_GENERIC_TIMEOUT;

  SdMmcCmdBlk.CommandIndex = EMMC_SEND_CID;
  SdMmcCmdBlk.CommandType  = SdMmcCommandTypeAc;
  SdMmcCmdBlk.ResponseType = SdMmcResponseTypeR2;
  SdMmcCmdBlk.CommandArgument = (UINT32)Rca << 16;

  Status = PassThru->PassThru (PassThru, Slot, &Packet, NULL);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  CopyMem (((UINT8*)Cid) + 1, &SdMmcStatusBlk.Resp0, sizeof (EMMC_CID) - 1);

  return Status;
}

STATIC
EFI_STATUS
GetEmmcSerialNumber (
  IN     EMMC_CID       *Cid,
  IN OUT UINT8          *SerialNumSize,
     OUT CHAR8          *SerialNum
)
{
  ASSERT (Cid != NULL);
  ASSERT (SerialNumSize != NULL);
  ASSERT (SerialNum != NULL);
  ASSERT (*SerialNumSize >= 15); /* Name:6 Number:8 NULL:1 */

  UINT32  ProductNumberHex;
  UINTN   BufferMaxSie   = *SerialNumSize;
  UINTN   BufferUsedSize = 0;
  UINTN   BufferLeftSize = BufferMaxSie - BufferUsedSize;

  ZeroMem (SerialNum, BufferLeftSize);

  /* Convert serial number to integer */
  ProductNumberHex = Cid->ProductSerialNumber[3] << 24 |
                     Cid->ProductSerialNumber[2] << 16 |
                     Cid->ProductSerialNumber[1] <<  8 |
                     Cid->ProductSerialNumber[0];

  /* Get product name */
  AsciiStrnCpyS (SerialNum, BufferLeftSize, Cid->ProductName, sizeof(Cid->ProductName));

  /* Simics may not populate. Provide test values */
  if (IsSimicsEnvironment()) {
    if (ProductNumberHex == 0) {
      ProductNumberHex = 54321;
    }
    if (SerialNum[0] == 0x00) {
      AsciiStrnCpyS (SerialNum, BufferLeftSize, "Intel-", 6);
    }
  }

  BufferUsedSize = AsciiStrnLenS (SerialNum, BufferMaxSie);
  BufferLeftSize = BufferMaxSie - BufferUsedSize;

  /* Combine product anme and number */
  ASSERT (BufferLeftSize > (2*sizeof (UINT32)));
  AsciiValueToStringS (&SerialNum[BufferUsedSize],
            BufferLeftSize,
            PREFIX_ZERO | RADIX_HEX,
            ProductNumberHex,
            2 * sizeof (UINT32)
            );
  BufferUsedSize = AsciiStrnLenS (SerialNum, BufferMaxSie);
  BufferLeftSize = BufferMaxSie - BufferUsedSize;

  /* *SerialNumSize = (UINT8)BufferUsedSize; */
  ASSERT (BufferLeftSize > 1);
  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
GetNextEmmcSerialNumber (
  IN       EFI_SD_MMC_PASS_THRU_PROTOCOL **PassThru,
  IN  OUT  UINT8                         *Slot,
  IN  OUT  UINT8                         *SerialNumSize,
      OUT  CHAR8                         *SerialNum
)
{
  EFI_STATUS               Status;
  EFI_DEVICE_PATH_PROTOCOL *DevicePath;
  EMMC_CID                 Cid;

  /* Initialize if first call */
  if ((*PassThru) == NULL) {
    Status = gBS->LocateProtocol (
                    &gEfiSdMmcPassThruProtocolGuid,
                    NULL,
                    PassThru
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR,"Failed to locate gEfiSdMmcPassThruProtocolGuid Protocol: %r\n",Status));
      return Status;
    }
    *Slot = 0xFF;
  }

  /* Iterate over all slots until serial number found or end reached. */
  do {
    Status = (*PassThru)->GetNextSlot (*PassThru, Slot);
    if (EFI_ERROR (Status)) {
      /* No more slots or another error. Exit */
      return Status;
    }
    DEBUG ((DEBUG_INFO,"Emmc Slot Number : %d\n", *Slot));

    /* Build Device Path to check if the EMMC device present at the slot. */
    Status = (*PassThru)->BuildDevicePath (
                *PassThru,
                *Slot,
                &DevicePath
                );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO,"No card. Skipping\n"));
      continue;
    }
    /* Device path must be freed before return */
    DEBUG ((DEBUG_INFO,"Emmc Device : %x-%x\n", DevicePath->Type, DevicePath->SubType));
    do {
      if (DevicePath->SubType != MSG_EMMC_DP) {
        DEBUG ((DEBUG_INFO,"Incorrect type. Skipping\n"));
        Status = EFI_NOT_FOUND;
        break;
      }

      /*
        Deselect the device to force it enter stby mode before getting CSD register content.
        Note: Don't check return status as some EMMC devices return error but the state has been stby.
      */
      EmmcSelect (*PassThru, *Slot, 0);

      Status = EmmcGetCid (*PassThru, (*Slot) + 1, *Slot, &Cid);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_INFO,"Could not get CID. Skipping\n"));
        break;
      }

      Status = GetEmmcSerialNumber (&Cid, SerialNumSize, SerialNum);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_INFO,"Could not get serial number. Skipping\n"));
        break;
      }

    } while (0);

    /* Put card back into original state (ignore status). */
    EmmcSelect (*PassThru, *Slot, (*Slot) + 1);

    gBS->FreePool (DevicePath);

  } while (EFI_ERROR(Status));

  return Status;
}

/**
  Get firest Emmc device serial number.

  @param[in out]   SerialNumSize      Size of SerialNum buffer on input.
                                      Returns SerialNum size on return.
  @param[out]      SerialNum          Serial number buffer.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_DEVICE_ERROR       The command was unsuccessful.

**/
EFI_STATUS
GetFirstEmmcSerialNumber (
  IN  OUT  UINT8  *SerialNumSize,
  IN  OUT  CHAR8  *SerialNum
)
{
  EFI_STATUS                    Status;
  EFI_SD_MMC_PASS_THRU_PROTOCOL *PassThru = NULL;
  UINT8                         Slot;

  Status = GetNextEmmcSerialNumber (&PassThru, &Slot, SerialNumSize, SerialNum);

  return Status;
}
