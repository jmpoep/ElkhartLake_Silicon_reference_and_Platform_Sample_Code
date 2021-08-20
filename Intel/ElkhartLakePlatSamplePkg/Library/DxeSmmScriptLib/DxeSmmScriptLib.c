/** @file
  Thunk implementation for SmmScriptLib.

  SmmScriptLib in the Framework implementation saves the S3 Boot Script during SMM runtime.
  This thunk implementation utilizes the SmmSaveState Protocol.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2016 Intel Corporation.

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
#include "DxeSmmScriptLib.h"

GLOBAL_REMOVE_IF_UNREFERENCED EFI_S3_SMM_SAVE_STATE_PROTOCOL  *mS3SmmSaveState = NULL;

//extern EFI_SMM_SYSTEM_TABLE2    *gSmst;

/**
  Internal function to add IO write opcode to the table.

  @param  Marker                The variable argument list to get the opcode
                                and associated attributes.

  @retval EFI_OUT_OF_RESOURCES  Not enough resource to do operation.
  @retval EFI_SUCCESS           Opcode is added.

**/
EFI_STATUS
BootScriptIoWrite (
  IN VA_LIST                  Marker
  )
{
  EFI_BOOT_SCRIPT_WIDTH Width;
  UINT64                Address;
  UINTN                 Count;
  UINT8                 *Buffer;

  Width       = VA_ARG (Marker, EFI_BOOT_SCRIPT_WIDTH);
  Address     = VA_ARG (Marker, UINT64);
  Count       = VA_ARG (Marker, UINTN);
  Buffer      = VA_ARG (Marker, UINT8 *);

  return mS3SmmSaveState->Write (
                        mS3SmmSaveState,
                        EFI_BOOT_SCRIPT_IO_WRITE_OPCODE,
                        Width,
                        Address,
                        Count,
                        Buffer
                        );
}
/**
  Internal function to add IO read/write opcode to the table.

  @param  Marker                The variable argument list to get the opcode
                                and associated attributes.

  @retval EFI_OUT_OF_RESOURCES  Not enough resource to do operation.
  @retval EFI_SUCCESS           Opcode is added.

**/
EFI_STATUS
BootScriptIoReadWrite (
  IN VA_LIST                       Marker
  )
{
  EFI_BOOT_SCRIPT_WIDTH Width;
  UINT64                Address;
  UINT8                 *Data;
  UINT8                 *DataMask;

  Width       = VA_ARG (Marker, EFI_BOOT_SCRIPT_WIDTH);
  Address     = VA_ARG (Marker, UINT64);
  Data        = VA_ARG (Marker, UINT8 *);
  DataMask    = VA_ARG (Marker, UINT8 *);

  return mS3SmmSaveState->Write (
                         mS3SmmSaveState,
                         EFI_BOOT_SCRIPT_IO_READ_WRITE_OPCODE,
                         Width,
                         Address,
                         Data,
                         DataMask
                         );
}
/**
  Internal function to add memory read/write opcode to the table.

  @param  Marker                The variable argument list to get the opcode
                                and associated attributes.

  @retval EFI_OUT_OF_RESOURCES  Not enough resource to do operation.
  @retval EFI_SUCCESS           Opcode is added.

**/
EFI_STATUS
BootScriptMemReadWrite (
  IN VA_LIST                       Marker
  )
{
  EFI_BOOT_SCRIPT_WIDTH Width;
  UINT64                Address;
  UINT8                 *Data;
  UINT8                 *DataMask;

  Width       = VA_ARG (Marker, EFI_BOOT_SCRIPT_WIDTH);
  Address     = VA_ARG (Marker, UINT64);
  Data        = VA_ARG (Marker, UINT8 *);
  DataMask    = VA_ARG (Marker, UINT8 *);

  return mS3SmmSaveState->Write (
                        mS3SmmSaveState,
                        EFI_BOOT_SCRIPT_MEM_READ_WRITE_OPCODE,
                        Width,
                        Address,
                        Data,
                        DataMask
                        );
}
/**
  Internal function to PciCfg read/write opcode to the table.

  @param  Marker                The variable argument list to get the opcode
                                and associated attributes.

  @retval EFI_OUT_OF_RESOURCES  Not enough resource to do operation.
  @retval EFI_SUCCESS           Opcode is added.

**/
EFI_STATUS
BootScriptPciCfgReadWrite (
  IN VA_LIST                       Marker
  )
{
  EFI_BOOT_SCRIPT_WIDTH Width;
  UINT64                Address;
  UINT8                 *Data;
  UINT8                 *DataMask;

  Width       = VA_ARG (Marker, EFI_BOOT_SCRIPT_WIDTH);
  Address     = VA_ARG (Marker, UINT64);
  Data        = VA_ARG (Marker, UINT8 *);
  DataMask    = VA_ARG (Marker, UINT8 *);

  return mS3SmmSaveState->Write (
                          mS3SmmSaveState,
                          EFI_BOOT_SCRIPT_PCI_CONFIG_READ_WRITE_OPCODE,
                          Width,
                          Address,
                          Data,
                          DataMask
                         );
}
/**
  Internal function to add PciCfg write opcode to the table.

  @param  Marker                The variable argument list to get the opcode
                                and associated attributes.

  @retval EFI_OUT_OF_RESOURCES  Not enough resource to do operation.
  @retval EFI_SUCCESS           Opcode is added.

**/
EFI_STATUS
BootScriptPciCfgWrite (
  IN VA_LIST                     Marker
  )
{
  EFI_BOOT_SCRIPT_WIDTH Width;
  UINT64                Address;
  UINTN                 Count;
  UINT8                 *Buffer;

  Width       = VA_ARG (Marker, EFI_BOOT_SCRIPT_WIDTH);
  Address     = VA_ARG (Marker, UINT64);
  Count       = VA_ARG (Marker, UINTN);
  Buffer      = VA_ARG (Marker, UINT8 *);

  return  mS3SmmSaveState->Write (
                        mS3SmmSaveState,
                        EFI_BOOT_SCRIPT_PCI_CONFIG_WRITE_OPCODE,
                        Width,
                        Address,
                        Count,
                        Buffer
                        );
}
/**
  Internal function to add stall opcode to the table.

  @param  Marker                The variable argument list to get the opcode
                                and associated attributes.

  @retval EFI_OUT_OF_RESOURCES  Not enough resource to do operation.
  @retval EFI_SUCCESS           Opcode is added.

**/
EFI_STATUS
BootScriptStall (
  IN VA_LIST                       Marker
  )
{
  UINT32                Duration;

  Duration    = VA_ARG (Marker, UINT32);

  return mS3SmmSaveState->Write (
                          mS3SmmSaveState,
                          EFI_BOOT_SCRIPT_STALL_OPCODE,
                          Duration
                         );
}
/**
  Internal function to add Save jmp address according to DISPATCH_OPCODE.
  We ignore "Context" parameter

  @param  Marker                The variable argument list to get the opcode
                                and associated attributes.

  @retval EFI_OUT_OF_RESOURCES  Not enough resource to do operation.
  @retval EFI_SUCCESS           Opcode is added.

**/
EFI_STATUS
BootScriptDispatch (
  IN VA_LIST                       Marker
  )
{
  VOID        *EntryPoint;

  EntryPoint = (VOID*)(UINTN)VA_ARG (Marker, EFI_PHYSICAL_ADDRESS);
  return mS3SmmSaveState->Write (
                          mS3SmmSaveState,
                          EFI_BOOT_SCRIPT_DISPATCH_OPCODE,
                          EntryPoint
                         );
}
/**
  Internal function to add memory write opcode to the table.

  @param  Marker                The variable argument list to get the opcode
                                and associated attributes.

  @retval EFI_OUT_OF_RESOURCES  Not enough resource to do operation.
  @retval EFI_SUCCESS           Opcode is added.

**/
EFI_STATUS
BootScriptMemWrite (
  IN VA_LIST                       Marker
  )
{
  EFI_BOOT_SCRIPT_WIDTH Width;
  UINT64                Address;
  UINTN                 Count;
  UINT8                 *Buffer;

  Width       = VA_ARG (Marker, EFI_BOOT_SCRIPT_WIDTH);
  Address     = VA_ARG (Marker, UINT64);
  Count       = VA_ARG (Marker, UINTN);
  Buffer      = VA_ARG (Marker, UINT8 *);

  return mS3SmmSaveState->Write (
                        mS3SmmSaveState,
                        EFI_BOOT_SCRIPT_MEM_WRITE_OPCODE,
                        Width,
                        Address,
                        Count,
                        Buffer
                        );
}
/**
  Adds a record into a specified Framework boot script table.

  This function is used to store a boot script record into a given boot
  script table in SMM runtime. The parameter is the same with definitionin BootScriptSave Protocol.

  @param  ScriptTable           Pointer to the script table to write to. In the thunk implementation, this parameter is ignored
                                since the boot script table is maintained by BootScriptLib.
  @param  Type                  Not used.
  @param  OpCode                The operation code (opcode) number.
  @param  ...                   Argument list that is specific to each opcode.

  @retval EFI_SUCCESS           The operation succeeded. A record was added into the
                                specified script table.
  @retval EFI_INVALID_PARAMETER The parameter is illegal or the given boot script is not supported.
                                If the opcode is unknow or not supported because of the PCD
                                Feature Flags.
  @retval EFI_OUT_OF_RESOURCES  There is insufficient memory to store the boot script.
**/
EFI_STATUS
EFIAPI
SmmBootScriptWrite (
  IN OUT   EFI_SMM_SCRIPT_TABLE        *ScriptTable,
  IN       UINTN                       Type,
  IN       UINT16                      OpCode,
  ...
  )
{
  EFI_STATUS  Status;
  VA_LIST     Marker;

  if (mS3SmmSaveState == NULL) {
    return EFI_UNSUPPORTED;
  }

  //
  // Build script according to opcode
  //
  switch (OpCode) {

  case EFI_BOOT_SCRIPT_IO_WRITE_OPCODE:
    VA_START (Marker, OpCode);
    Status = BootScriptIoWrite (Marker);
    VA_END (Marker);
    break;

  case EFI_BOOT_SCRIPT_IO_READ_WRITE_OPCODE:
    VA_START (Marker, OpCode);
    Status = BootScriptIoReadWrite (Marker);
    VA_END (Marker);
    break;

  case EFI_BOOT_SCRIPT_MEM_READ_WRITE_OPCODE:
    VA_START (Marker, OpCode);
    Status = BootScriptMemReadWrite (Marker);
    VA_END (Marker);
    break;

  case EFI_BOOT_SCRIPT_PCI_CONFIG_READ_WRITE_OPCODE:
    VA_START (Marker, OpCode);
    Status = BootScriptPciCfgReadWrite (Marker);
    VA_END (Marker);
    break;

  case EFI_BOOT_SCRIPT_STALL_OPCODE:
    VA_START (Marker, OpCode);
    Status = BootScriptStall (Marker);
    VA_END (Marker);
    break;

  case EFI_BOOT_SCRIPT_DISPATCH_OPCODE:
    VA_START (Marker, OpCode);
    Status = BootScriptDispatch (Marker);
    VA_END (Marker);
    break;


  case EFI_BOOT_SCRIPT_PCI_CONFIG_WRITE_OPCODE:
    VA_START (Marker, OpCode);
    Status = BootScriptPciCfgWrite (Marker);
    VA_END (Marker);
    break;

  case EFI_BOOT_SCRIPT_MEM_WRITE_OPCODE:
    VA_START (Marker, OpCode);
    Status = BootScriptMemWrite (Marker);
    VA_END (Marker);
    break;

  default:
    Status = EFI_INVALID_PARAMETER;
    break;
  }

  return Status;
}
/**
  Intialize Boot Script table.

  This function should be called in SMM mode. The Thunk implementation is try to
  locate SmmSaveState protocol.

  @param  SystemTable         Pointer to the EFI sytem table
  @param  SmmScriptTablePages The expected ScriptTable page number
  @param  SmmScriptTableBase  The returned ScriptTable base address

  @retval EFI_OUT_OF_RESOURCES    No resource to do the initialization.
  @retval EFI_SUCCESS             Function has completed successfully.

**/
EFI_STATUS
EFIAPI
InitializeSmmScriptLib (
  IN  EFI_SYSTEM_TABLE     *SystemTable,
  IN  UINTN                SmmScriptTablePages,
  OUT EFI_PHYSICAL_ADDRESS *SmmScriptTableBase
  )
{
  EFI_STATUS        Status;

  //
  // The boot Script table is maintained by DxeBootScript Lib. so there is no need to
  // allocate the table here and directly return zero
  //
  if (SmmScriptTableBase == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  *SmmScriptTableBase = 0;

  //
  // Locate Smm S3 Save State protocol to do the boot script save operation.
  //
  Status = gSmst->SmmLocateProtocol (
                                 &gEfiS3SmmSaveStateProtocolGuid,
                                  NULL,
                                 (VOID**)&mS3SmmSaveState
                                );
  return Status;
}
/**
  Create Boot Script table.

  It will be ignored and just return EFI_SUCCESS since the boot script table is
  maintained by DxeBootScriptLib. Create Table is not needed.

  @param  ScriptTable     Pointer to the boot script table to create.
  @param  Type            The type of table to creat.


  @retval EFI_SUCCESS     Function has completed successfully.

**/
EFI_STATUS
EFIAPI
SmmBootScriptCreateTable (
  IN OUT   EFI_SMM_SCRIPT_TABLE        *ScriptTable,
  IN       UINTN                       Type
  )
{
  return EFI_SUCCESS;
}
/**
  Close Boot Script table.

  It will be ignored and just return EFI_SUCCESS since the boot script table
  is maintained by DxeBootScriptLib.

  @param  ScriptTableBase    Pointer to the boot script table to create.
  @param  ScriptTablePtr     Pointer to the script table to write to.
  @param  Type               The type of table to creat.

  @retval EFI_SUCCESS        Function has completed successfully.

**/
EFI_STATUS
EFIAPI
SmmBootScriptCloseTable (
  IN EFI_SMM_SCRIPT_TABLE        ScriptTableBase,
  IN EFI_SMM_SCRIPT_TABLE        ScriptTablePtr,
  IN UINTN                       Type
  )
{
  return EFI_SUCCESS;
}
