/** @file
  Implementation of helper functions of XDCI device driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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


#include "XdciUtility.h"

VOID
PrintDeviceDescriptor (
  IN USB_DEVICE_DESCRIPTOR    *DevDesc
  )
{
  DEBUG ((DEBUG_INFO, "--- Device Descriptor ---\n"));
  DEBUG ((DEBUG_INFO, "Length            : 0x%x\n", DevDesc->Length));
  DEBUG ((DEBUG_INFO, "DescriptorType    : 0x%x\n", DevDesc->DescriptorType));
  DEBUG ((DEBUG_INFO, "BcdUSB            : 0x%x\n", DevDesc->BcdUSB));
  DEBUG ((DEBUG_INFO, "DeviceClass       : 0x%x\n", DevDesc->DeviceClass));
  DEBUG ((DEBUG_INFO, "DeviceSubClass    : 0x%x\n", DevDesc->DeviceSubClass));
  DEBUG ((DEBUG_INFO, "DeviceProtocol    : 0x%x\n", DevDesc->DeviceProtocol));
  DEBUG ((DEBUG_INFO, "MaxPacketSize0    : 0x%x\n", DevDesc->MaxPacketSize0));
  DEBUG ((DEBUG_INFO, "IdVendor          : 0x%x\n", DevDesc->IdVendor));
  DEBUG ((DEBUG_INFO, "IdProduct         : 0x%x\n", DevDesc->IdProduct));
  DEBUG ((DEBUG_INFO, "BcdDevice         : 0x%x\n", DevDesc->BcdDevice));
  DEBUG ((DEBUG_INFO, "StrManufacturer   : 0x%x\n", DevDesc->StrManufacturer));
  DEBUG ((DEBUG_INFO, "StrProduct        : 0x%x\n", DevDesc->StrProduct));
  DEBUG ((DEBUG_INFO, "StrSerialNumber   : 0x%x\n", DevDesc->StrSerialNumber));
  DEBUG ((DEBUG_INFO, "NumConfigurations : 0x%x\n", DevDesc->NumConfigurations));
  DEBUG ((DEBUG_INFO, "\n"));
}

VOID
PrintConfigDescriptor (
  IN EFI_USB_CONFIG_DESCRIPTOR    *ConfigDesc
  )
{
  DEBUG ((DEBUG_INFO, "--- Configuration Descriptor ---\n"));
  DEBUG ((DEBUG_INFO, "Length             : 0x%x\n", ConfigDesc->Length));
  DEBUG ((DEBUG_INFO, "DescriptorType     : 0x%x\n", ConfigDesc->DescriptorType));
  DEBUG ((DEBUG_INFO, "TotalLength        : 0x%x\n", ConfigDesc->TotalLength));
  DEBUG ((DEBUG_INFO, "NumInterfaces      : 0x%x\n", ConfigDesc->NumInterfaces));
  DEBUG ((DEBUG_INFO, "ConfigurationValue : 0x%x\n", ConfigDesc->ConfigurationValue));
  DEBUG ((DEBUG_INFO, "Configuration      : 0x%x\n", ConfigDesc->Configuration));
  DEBUG ((DEBUG_INFO, "Attributes         : 0x%x\n", ConfigDesc->Attributes));
  DEBUG ((DEBUG_INFO, "MaxPower           : 0x%x\n", ConfigDesc->MaxPower));
  DEBUG ((DEBUG_INFO, "\n"));
}

VOID
PrintInterfaceDescriptor (
  IN EFI_USB_INTERFACE_DESCRIPTOR    *IfDesc
  )
{
  DEBUG ((DEBUG_INFO, "--- Interface Descriptor ---\n"));
  DEBUG ((DEBUG_INFO, "Length            : 0x%x\n", IfDesc->Length));
  DEBUG ((DEBUG_INFO, "DescriptorType    : 0x%x\n", IfDesc->DescriptorType));
  DEBUG ((DEBUG_INFO, "InterfaceNumber   : 0x%x\n", IfDesc->InterfaceNumber));
  DEBUG ((DEBUG_INFO, "AlternateSetting  : 0x%x\n", IfDesc->AlternateSetting));
  DEBUG ((DEBUG_INFO, "NumEndpoints      : 0x%x\n", IfDesc->NumEndpoints));
  DEBUG ((DEBUG_INFO, "InterfaceClass    : 0x%x\n", IfDesc->InterfaceClass));
  DEBUG ((DEBUG_INFO, "InterfaceSubClass : 0x%x\n", IfDesc->InterfaceSubClass));
  DEBUG ((DEBUG_INFO, "InterfaceProtocol : 0x%x\n", IfDesc->InterfaceProtocol));
  DEBUG ((DEBUG_INFO, "Interface         : 0x%x\n", IfDesc->Interface));
  DEBUG ((DEBUG_INFO, "\n"));
}

VOID
PrintEpDescriptor (
  IN EFI_USB_ENDPOINT_DESCRIPTOR    *EpDesc
  )
{
  DEBUG ((DEBUG_INFO, "--- Endpoint Descriptor ---\n"));
  DEBUG ((DEBUG_INFO, "Length          : 0x%x\n", EpDesc->Length));
  DEBUG ((DEBUG_INFO, "DescriptorType  : 0x%x\n", EpDesc->DescriptorType));
  DEBUG ((DEBUG_INFO, "EndpointAddress : 0x%x\n", EpDesc->EndpointAddress));
  DEBUG ((DEBUG_INFO, "Attributes      : 0x%x\n", EpDesc->Attributes));
  DEBUG ((DEBUG_INFO, "MaxPacketSize   : 0x%x\n", EpDesc->MaxPacketSize));
  DEBUG ((DEBUG_INFO, "Interval        : 0x%x\n", EpDesc->Interval));
  DEBUG ((DEBUG_INFO, "\n"));
}

VOID
PrintEpCompDescriptor (
  IN EFI_USB_ENDPOINT_COMPANION_DESCRIPTOR    *EpDesc
  )
{
  DEBUG ((DEBUG_INFO, "--- Endpoint Companion Descriptor ---\n"));
  DEBUG ((DEBUG_INFO, "Length           : 0x%x\n", EpDesc->Length));
  DEBUG ((DEBUG_INFO, "DescriptorType   : 0x%x\n", EpDesc->DescriptorType));
  DEBUG ((DEBUG_INFO, "MaxBurst         : 0x%x\n", EpDesc->MaxBurst));
  DEBUG ((DEBUG_INFO, "Attributes       : 0x%x\n", EpDesc->Attributes));
  DEBUG ((DEBUG_INFO, "BytesPerInterval : 0x%x\n", EpDesc->BytesPerInterval));
  DEBUG ((DEBUG_INFO, "\n"));
}

VOID
PrintStringDescriptor (
  IN USB_STRING_DESCRIPTOR    *StrDesc
  )
{
  if (StrDesc->Length > 2) {
    DEBUG ((DEBUG_INFO, "--- String Descriptor ---\n"));
    DEBUG ((DEBUG_INFO, "Length         : 0x%x\n", StrDesc->Length));
    DEBUG ((DEBUG_INFO, "DescriptorType : 0x%x\n", StrDesc->DescriptorType));
    DEBUG ((DEBUG_INFO, "String         : %s\n",   StrDesc->LangID));
  }
  DEBUG ((DEBUG_INFO, "\n"));
}

VOID
PrintDeviceRequest (
  IN EFI_USB_DEVICE_REQUEST    *DevReq
  )
{
  DEBUG ((DEBUG_INFO, "--- Device Request ---\n"));
  DEBUG ((DEBUG_INFO, "RequestType : 0x%x\n", DevReq->RequestType));
  DEBUG ((DEBUG_INFO, "Request     : 0x%x\n", DevReq->Request));
  DEBUG ((DEBUG_INFO, "Value       : 0x%x\n", DevReq->Value));
  DEBUG ((DEBUG_INFO, "Index       : 0x%x\n", DevReq->Index));
  DEBUG ((DEBUG_INFO, "Length      : 0x%x\n", DevReq->Length));
  DEBUG ((DEBUG_INFO, "\n"));
}

#ifdef SUPPORT_SUPER_SPEED
VOID
PrintBOSDescriptor (
  IN EFI_USB_BOS_DESCRIPTOR    *BosDesc
  )
{
  DEBUG ((DEBUG_INFO, "--- BOS Descriptor ---\n"));
  DEBUG ((DEBUG_INFO, "Length           : 0x%x\n", BosDesc->Length));
  DEBUG ((DEBUG_INFO, "DescriptorType   : 0x%x\n", BosDesc->DescriptorType));
  DEBUG ((DEBUG_INFO, "TotalLength      : 0x%x\n", BosDesc->TotalLength));
  DEBUG ((DEBUG_INFO, "NumDeviceCaps    : 0x%x\n", BosDesc->NumDeviceCaps));
  DEBUG ((DEBUG_INFO, "\n"));
}
#endif
