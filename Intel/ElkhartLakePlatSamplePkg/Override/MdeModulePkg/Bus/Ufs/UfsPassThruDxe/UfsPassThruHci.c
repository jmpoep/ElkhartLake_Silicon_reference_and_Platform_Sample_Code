/** @file
  UfsPassThruDxe driver is used to produce EFI_EXT_SCSI_PASS_THRU protocol interface
  for upper layer application to execute UFS-supported SCSI cmds.

  Copyright (c) 2014 - 2019 Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php.

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "UfsPassThru.h"
#include <Library/BootMediaLib.h>

//
// RPPO-LKF-0010: RoyalParkOverrideBegin
//
PHY_DME_DATA SnpsPhyData[] = {
   {  0x802b0000, 0x0, 0x0 },
   {  0x80bf0000, 0x0, 0x1 },
   {  0x80ea0000, 0x0, 0x80 },
   {  0x80f10000, 0x0, 0x4 },
   {  0x00eb0000, 0x0, 0xd },
   {  0x00eb0001, 0x0, 0xd },
   {  0x00eb0004, 0x0, 0x1 },
   {  0x00eb0005, 0x0, 0x1 },
   {  0x00ec0000, 0x0, 0x19 },
   {  0x00ec0001, 0x0, 0x19 },
   {  0x00ec0004, 0x0, 0x19 },
   {  0x00ec0005, 0x0, 0x19 },
   {  0x00f00000, 0x0, 0x12 },
   {  0x00f00001, 0x0, 0x12 },
   {  0x00f00004, 0x0, 0x2 },
   {  0x00f00005, 0x0, 0x2 },
   {  0x00ba0004, 0x0, 0x80 },
   {  0x00ba0005, 0x0, 0x80 },
   {  0x80f30000, 0x0, 0x64 },
   {  0x00f10000, 0x0, 0xd6 },
   {  0x00f10001, 0x0, 0xd6 },
   {  0x80fb0000, 0x0, 0x09 },
   {  0x80f00000, 0x0, 0x00 },
   {  0x80e60000, 0x0, 0x04 },
   {  0x80cd0000, 0x0, 0x02 },
   {  0x00f20004, 0x0, 0x03 },
   {  0x00f20005, 0x0, 0x03 },
   {  0x00bd0004, 0x0, 0x16 },
   {  0x00bd0005, 0x0, 0x16 },
   {  0x00c70004, 0x0, 0x42 },
   {  0x00c70005, 0x0, 0x42 },
   {  0x80f80000, 0x0, 0x00 },
   {  0x00f30004, 0x0, 0xa4 },
   {  0x00f30005, 0x0, 0xa4 },
   {  0x00b40004, 0x0, 0x01 },
   {  0x00b40005, 0x0, 0x01 },
   {  0x00f40004, 0x0, 0x01 },
   {  0x00f40005, 0x0, 0x01 },
   {  0x00e90004, 0x0, 0x28 },
   {  0x00e90005, 0x0, 0x28 },
   {  0x00b50004, 0x0, 0x1e },
   {  0x00b50005, 0x0, 0x1e },
   {  0x00bf0004, 0x0, 0x2f },
   {  0x00bf0005, 0x0, 0x2f },
   {  0x80010004, 0x0, 0x00 },
   {  0x80020004, 0x0, 0x00 },
   {  0x155e0000, 0x0, 0x00 },
   {  0xd0b60000, 0x0, 0x01 },
   {  0xd0850000, 0x0, 0x01 },
   {  0xd0b30000, 0x0, 0x28 },
   {  0xd0b20000, 0x0, 0x0f },
   {  0xd0b40000, 0x0, 0x07 },
   {  0xd0b10000, 0x0, 0x0f },
   {  0xd0b70000, 0x0, 0x1f },
   {  0xd0b50000, 0x0, 0x01 },
//   {  0xd0850000, 0x0, 0x01 } //vs_MphyCfgUpdt
};
//
// RPPO-LKF-0010: OverrideEnd
//
/**
  Read 32bits data from specified UFS MMIO register.

  @param[in]  Private       The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]  Offset        The offset within the UFS Host Controller MMIO space to start
                            the memory operation.
  @param[out] Value         The data buffer to store.

  @retval EFI_TIMEOUT       The operation is time out.
  @retval EFI_SUCCESS       The operation succeeds.
  @retval Others            The operation fails.

**/
EFI_STATUS
UfsMmioRead32 (
  IN     UFS_PASS_THRU_PRIVATE_DATA   *Private,
  IN     UINTN                        Offset,
     OUT UINT32                       *Value
  )
{
  EDKII_UFS_HOST_CONTROLLER_PROTOCOL  *UfsHc;
  EFI_STATUS                          Status;

  UfsHc = Private->UfsHostController;

  Status = UfsHc->Read (UfsHc, EfiUfsHcWidthUint32, Offset, 1, Value);

  return Status;
}

/**
  Write 32bits data to specified UFS MMIO register.

  @param[in] Private        The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in] Offset         The offset within the UFS Host Controller MMIO space to start
                            the memory operation.
  @param[in] Value          The data to write.

  @retval EFI_TIMEOUT       The operation is time out.
  @retval EFI_SUCCESS       The operation succeeds.
  @retval Others            The operation fails.

**/
EFI_STATUS
UfsMmioWrite32 (
  IN  UFS_PASS_THRU_PRIVATE_DATA   *Private,
  IN  UINTN                        Offset,
  IN  UINT32                       Value
  )
{
  EDKII_UFS_HOST_CONTROLLER_PROTOCOL  *UfsHc;
  EFI_STATUS                          Status;

  UfsHc = Private->UfsHostController;

  Status = UfsHc->Write (UfsHc, EfiUfsHcWidthUint32, Offset, 1, &Value);

  return Status;
}

/**
  Wait for the value of the specified system memory set to the test value.

  @param[in]  Private       The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]  Offset        The offset within the UFS Host Controller MMIO space to start
                            the memory operation.
  @param[in]  MaskValue     The mask value of memory.
  @param[in]  TestValue     The test value of memory.
  @param[in]  Timeout       The time out value for wait memory set, uses 100ns as a unit.

  @retval EFI_TIMEOUT       The system memory setting is time out.
  @retval EFI_SUCCESS       The system memory is correct set.
  @retval Others            The operation fails.

**/
EFI_STATUS
UfsWaitMemSet (
  IN  UFS_PASS_THRU_PRIVATE_DATA   *Private,
  IN  UINTN                        Offset,
  IN  UINT32                       MaskValue,
  IN  UINT32                       TestValue,
  IN  UINT64                       Timeout
  )
{
  UINT32     Value;
  UINT64     Delay;
  BOOLEAN    InfiniteWait;
  EFI_STATUS Status;

  if (Timeout == 0) {
    InfiniteWait = TRUE;
  } else {
    InfiniteWait = FALSE;
  }

  Delay = DivU64x32 (Timeout, 10) + 1;

  do {
    //
    // Access PCI MMIO space to see if the value is the tested one.
    //
    Status = UfsMmioRead32 (Private, Offset, &Value);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Value &= MaskValue;

    if (Value == TestValue) {
      return EFI_SUCCESS;
    }

    //
    // Stall for 1 microseconds.
    //
    MicroSecondDelay (1);

    Delay--;

  } while (InfiniteWait || (Delay > 0));
  //
  // RPPO-LKF-0009: OverrideBegin
  //
  DEBUG ((DEBUG_ERROR, "UfsPassThruHci: UfsWaitMemSet: EFI_TIMEOUT \n"));
  //
  // RPPO-LKF-0009: OverrideEnd
  //
  return EFI_TIMEOUT;
}

/**
  Dumps the UFS Host Controller Registers.
  @param[in] Private      The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure
  @param[in] IsFullDump   The boolean variable to specify whether full registers need to be dumped
  @retval EFI_SUCCESS  Successfully switched to fast mode
  @retval others       Failed to switch to fast mode
**/
VOID
UfsDumpHcRegisters(
  IN  UFS_PASS_THRU_PRIVATE_DATA   *Private,
  IN  BOOLEAN                      IsFullDump
  )
{
  UINT32 UfsData;

  if (IsFullDump == TRUE) {
    UfsMmioRead32 (Private, UFS_HC_CAP_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_CAP_OFFSET,        OFFSET = 00h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_VER_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_VER_OFFSET,        OFFSET = 08h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_DDID_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_DDID_OFFSET,       OFFSET = 10h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_PMID_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_PMID_OFFSET,       OFFSET = 14h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_AHIT_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_AHIT_OFFSET,       OFFSET = 18h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_IS_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_IS_OFFSET,         OFFSET = 20h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_IE_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_IE_OFFSET,         OFFSET = 24h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_STATUS_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_STATUS_OFFSET,     OFFSET = 30h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_ENABLE_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_ENABLE_OFFSET,     OFFSET = 34h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UECPA_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UECPA_OFFSET,      OFFSET = 38h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UECDL_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UECDL_OFFSET,      OFFSET = 3Ch, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UECN_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UECN_OFFSET,       OFFSET = 40h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UECT_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UECT_OFFSET,       OFFSET = 44h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UECDME_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UECDME_OFFSET,     OFFSET = 48h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UTRIACR_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTRIACR_OFFSET,    OFFSET = 4Ch, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UTRLBAU_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTRLBAU_OFFSET,    OFFSET = 50h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private,UFS_HC_UTRLBA_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTRLBA_OFFSET ,    OFFSET = 54h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UTRLDBR_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTRLDBR_OFFSET ,   OFFSET = 58h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UTRLCLR_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTRLCLR_OFFSET,    OFFSET = 5Ch, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UTRLRSR_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTRLRSR_OFFSET,    OFFSET = 60h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UTRLCNR_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTRLCNR_OFFSET,    OFFSET = 64h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UTMRLBA_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTMRLBA_OFFSET,    OFFSET = 70h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UTMRLBAU_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTMRLBAU_OFFSET,   OFFSET = 74h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UTMRLDBR_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTMRLDBR_OFFSET,   OFFSET = 78h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UTMRLCLR_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTMRLCLR_OFFSET,   OFFSET = 7Ch, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UTMRLRSR_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTMRLRSR_OFFSET,   OFFSET = 80h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UIC_CMD_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UIC_CMD_OFFSET,    OFFSET = 90h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UCMD_ARG1_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UCMD_ARG1_OFFSET,  OFFSET = 94h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UCMD_ARG2_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UCMD_ARG2_OFFSET,  OFFSET = 98h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UCMD_ARG3_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UCMD_ARG3_OFFSET,  OFFSET = 9Ch, VALUE = 0x%08x\n", UfsData));
  } else {
    UfsMmioRead32 (Private, UFS_HC_IS_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_IS_OFFSET,         OFFSET = 20h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_IE_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_IE_OFFSET,         OFFSET = 24h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_STATUS_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_STATUS_OFFSET,     OFFSET = 30h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_ENABLE_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_ENABLE_OFFSET,     OFFSET = 34h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UECPA_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UECPA_OFFSET,      OFFSET = 38h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UECDL_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UECDL_OFFSET,      OFFSET = 3Ch, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UECN_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UECN_OFFSET,       OFFSET = 40h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UECT_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UECT_OFFSET,       OFFSET = 44h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UECDME_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UECDME_OFFSET,     OFFSET = 48h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UTRLDBR_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTRLDBR_OFFSET ,   OFFSET = 58h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UTRLCLR_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTRLCLR_OFFSET,    OFFSET = 5Ch, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UTRLRSR_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTRLRSR_OFFSET,    OFFSET = 60h, VALUE = 0x%08x\n", UfsData));
    UfsMmioRead32 (Private, UFS_HC_UTRLCNR_OFFSET, &UfsData);
    DEBUG ((DEBUG_INFO, "UFS_HC_UTRLCNR_OFFSET,    OFFSET = 64h, VALUE = 0x%08x\n", UfsData));
  }
}

/**
  Dump UIC command execution result for debugging.

  @param[in]   UicOpcode  The executed UIC opcode.
  @param[in]   Result     The result to be parsed.

**/
VOID
DumpUicCmdExecResult (
  IN  UINT8     UicOpcode,
  IN  UINT8     Result
  )
{
  if (UicOpcode <= UfsUicDmePeerSet) {
    switch (Result) {
      case 0x00:
        break;
      case 0x01:
        DEBUG ((DEBUG_INFO, "UIC configuration command fails - INVALID_MIB_ATTRIBUTE\n"));
        break;
      case 0x02:
        DEBUG ((DEBUG_INFO, "UIC configuration command fails - INVALID_MIB_ATTRIBUTE_VALUE\n"));
        break;
      case 0x03:
        DEBUG ((DEBUG_INFO, "UIC configuration command fails - READ_ONLY_MIB_ATTRIBUTE\n"));
        break;
      case 0x04:
        DEBUG ((DEBUG_INFO, "UIC configuration command fails - WRITE_ONLY_MIB_ATTRIBUTE\n"));
        break;
      case 0x05:
        DEBUG ((DEBUG_INFO, "UIC configuration command fails - BAD_INDEX\n"));
        break;
      case 0x06:
        DEBUG ((DEBUG_INFO, "UIC configuration command fails - LOCKED_MIB_ATTRIBUTE\n"));
        break;
      case 0x07:
        DEBUG ((DEBUG_INFO, "UIC configuration command fails - BAD_TEST_FEATURE_INDEX\n"));
        break;
      case 0x08:
        DEBUG ((DEBUG_INFO, "UIC configuration command fails - PEER_COMMUNICATION_FAILURE\n"));
        break;
      case 0x09:
        DEBUG ((DEBUG_INFO, "UIC configuration command fails - BUSY\n"));
        break;
      case 0x0A:
        DEBUG ((DEBUG_INFO, "UIC configuration command fails - DME_FAILURE\n"));
        break;
      default :
        ASSERT (FALSE);
        break;
    }
  } else {
    switch (Result) {
      case 0x00:
        break;
      case 0x01:
        DEBUG ((DEBUG_INFO, "UIC control command fails - FAILURE\n"));
        break;
      default :
        ASSERT (FALSE);
        break;
    }
  }
}

/**
  Dump QUERY RESPONSE UPIU result for debugging.

  @param[in]   Result  The result to be parsed.

**/
VOID
DumpQueryResponseResult (
  IN  UINT8     Result
  )
{
  switch (Result) {
    case 0xF6:
      DEBUG ((DEBUG_INFO, "Query Response with Parameter Not Readable\n"));
      break;
    case 0xF7:
      DEBUG ((DEBUG_INFO, "Query Response with Parameter Not Writeable\n"));
      break;
    case 0xF8:
      DEBUG ((DEBUG_INFO, "Query Response with Parameter Already Written\n"));
      break;
    case 0xF9:
      DEBUG ((DEBUG_INFO, "Query Response with Invalid Length\n"));
      break;
    case 0xFA:
      DEBUG ((DEBUG_INFO, "Query Response with Invalid Value\n"));
      break;
    case 0xFB:
      DEBUG ((DEBUG_INFO, "Query Response with Invalid Selector\n"));
      break;
    case 0xFC:
      DEBUG ((DEBUG_INFO, "Query Response with Invalid Index\n"));
      break;
    case 0xFD:
      DEBUG ((DEBUG_INFO, "Query Response with Invalid Idn\n"));
      break;
    case 0xFE:
      DEBUG ((DEBUG_INFO, "Query Response with Invalid Opcode\n"));
      break;
    case 0xFF:
      DEBUG ((DEBUG_INFO, "Query Response with General Failure\n"));
      break;
    default :
      ASSERT (FALSE);
      break;
  }
}

/**
  Send a UIC command to the host controller.
  @param[in] Private          The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in] UicOpcode        The opcode of the UIC command.
  @param[in] Arg1             The value for 1st argument of the UIC command.
  @param[in] Arg2             The value for 2nd argument of the UIC command.
  @param[in] Arg3             The value for 3rd argument of the UIC command.
  @param[Out] Value           The value that was read.

  @return EFI_SUCCESS      Successfully execute this UIC command.
  @return EFI_DEVICE_ERROR Fail to execute this UIC command.
**/
EFI_STATUS
UfsExecGetUicCommands (
  IN     UFS_PASS_THRU_PRIVATE_DATA    *Private,
  IN     UINT8                         UicOpcode,
  IN     UINT32                        Arg1,
  IN     UINT32                        Arg2,
  IN     UINT32                        Arg3,
     OUT UINT32                        *Value
  )
{
  EFI_STATUS  Status;
  UINT32      Data;
  Status = UfsMmioRead32 (Private, UFS_HC_IS_OFFSET, &Data);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsExecGetUicCommands: UfsMmioRead32: UFS_HC_IS_OFFSET : ERROR!\n"));
    return Status;
  }
  if ((Data & UFS_HC_IS_UCCS) == UFS_HC_IS_UCCS) {
    //
    // Clear IS.BIT10 UIC Command Completion Status (UCCS) at first.
    //
    Status = UfsMmioWrite32 (Private, UFS_HC_IS_OFFSET, Data);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "UfsExecGetUicCommands: UfsMmioWrite32: UFS_HC_IS_OFFSET : ERROR!\n"));
      return Status;
    }
  }
  //
  // When programming UIC command registers, host software shall set the register UICCMD
  // only after all the UIC command argument registers (UICCMDARG1, UICCMDARG2 and UICCMDARG3)
  // are set.
  //
  Status = UfsMmioWrite32 (Private, UFS_HC_UCMD_ARG1_OFFSET, Arg1);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsExecGetUicCommands: UfsMmioWrite32: UFS_HC_UCMD_ARG1_OFFSET : ERROR!\n"));
    return Status;
  }
  Status = UfsMmioWrite32 (Private, UFS_HC_UCMD_ARG2_OFFSET, Arg2);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsExecGetUicCommands: UfsMmioWrite32: UFS_HC_UCMD_ARG2_OFFSET : ERROR!\n"));
    return Status;
  }
  Status = UfsMmioWrite32 (Private, UFS_HC_UCMD_ARG3_OFFSET, Arg3);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsExecGetUicCommands: UfsMmioWrite32: UFS_HC_UCMD_ARG3_OFFSET : ERROR!\n"));
    return Status;
  }
  //
  // Host software shall only set the UICCMD if HCS.UCRDY is set to 1.
  //
  Status = UfsWaitMemSet (Private, UFS_HC_STATUS_OFFSET, UFS_HC_HCS_UCRDY, UFS_HC_HCS_UCRDY, UFS_TIMEOUT);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsExecGetUicCommands: UfsWaitMemSet UFS_HC_HCS_UCRDY:  ERROR!\n"));
    return Status;
  }
  Status = UfsMmioWrite32 (Private, UFS_HC_UIC_CMD_OFFSET, (UINT32)UicOpcode);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsExecGetUicCommands: UfsMmioWrite32 UFS_HC_UIC_CMD_OFFSET:  ERROR!\n"));
    return Status;
  }
  //
  // UFS 2.0 spec section 5.3.1 Offset:0x20 IS.Bit10 UIC Command Completion Status (UCCS)
  // This bit is set to '1' by the host controller upon completion of a UIC command.
  //
  Status  = UfsWaitMemSet (Private, UFS_HC_IS_OFFSET, UFS_HC_IS_UCCS, UFS_HC_IS_UCCS, UFS_TIMEOUT);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsExecGetUicCommands: UfsWaitMemSet UFS_HC_IS_UCCS:  ERROR!\n"));
    return Status;
  }
  if (UicOpcode != UfsUicDmeReset) {
    Status = UfsMmioRead32 (Private, UFS_HC_UCMD_ARG2_OFFSET, &Data);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "UfsExecGetUicCommands: UfsMmioRead32: UFS_HC_UCMD_ARG2_OFFSET: Error!\n"));
      return Status;
    }
    if ((Data & 0xFF) != 0) {
        DEBUG ((DEBUG_INFO, "UfsExecGetUicCommands: UicOpcode=%x ARG2=%X !\n", UicOpcode, Data));
        DumpUicCmdExecResult (UicOpcode, (UINT8)(Data & 0xFF));
      return EFI_DEVICE_ERROR;
    }
  }
  if ((UicOpcode == UfsUicDmeGet) || (UicOpcode == UfsUicDmePeerGet)) {
    Status = UfsMmioRead32 (Private, UFS_HC_UCMD_ARG3_OFFSET, &Data);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "UfsExecGetUicCommands: UfsMmioRead32: UFS_HC_UCMD_ARG3_OFFSET: Error!\n"));
      return Status;
    }
    *Value = Data;
  }
  return EFI_SUCCESS;
}

/**
  Dumps the link Configuration.
  @param[in] Private The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure
  @retval EFI_SUCCESS  Successfully switched to fast mode
  @retval others       Failed to switch to fast mode
**/
EFI_STATUS
UfsDumpLinkConfig (
  IN UFS_PASS_THRU_PRIVATE_DATA  *Private
  )
{
  EFI_STATUS  Status;
  UINT32      Value;
  UINT32      ActiveTxDataLanes;
  UINT32      ActiveRxDataLanes;

  DEBUG ((DEBUG_INFO, "UfsDumpLinkConfig Entry \n"));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_Local_TX_LCC_Enable, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_Local_TX_LCC_Enable(%x)\n", PA_Local_TX_LCC_Enable));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_Local_TX_LCC_Enable(%x) = %x \n", PA_Local_TX_LCC_Enable, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_Peer_TX_LCC_Enable, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_Peer_TX_LCC_Enable(%x)\n", PA_Peer_TX_LCC_Enable));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_Peer_TX_LCC_Enable(%x) = %x \n", PA_Peer_TX_LCC_Enable, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_MaxRxHSGear, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_MaxRxHSGear(%x)\n", PA_MaxRxHSGear));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_MaxRxHSGear(%x) = %x \n", PA_MaxRxHSGear, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmePeerGet, UFS_UIC_ARG_MIB_SEL (PA_MaxRxHSGear, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmePeerGet PA_MaxRxHSGear(%x)\n", PA_MaxRxHSGear));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmePeerGet PA_MaxRxHSGear(%x) = %x \n", PA_MaxRxHSGear, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_MaxRxPWMGear, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_MaxRxPWMGear(%x)\n", PA_MaxRxPWMGear));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_MaxRxPWMGear(%x) = %x \n", PA_MaxRxPWMGear, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmePeerGet, UFS_UIC_ARG_MIB_SEL (PA_MaxRxPWMGear, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmePeerGet PA_MaxRxPWMGear(%x)\n", PA_MaxRxPWMGear));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmePeerGet PA_MaxRxPWMGear(%x) = %x \n", PA_MaxRxPWMGear, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_AvailTxDataLanes, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_AvailTxDataLanes(%x)\n", PA_AvailTxDataLanes));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_AvailTxDataLanes(%x) = %x \n", PA_AvailTxDataLanes, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_AvailRxDataLanes, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_AvailRxDataLanes(%x)\n", PA_AvailRxDataLanes));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_AvailRxDataLanes(%x) = %x \n", PA_AvailRxDataLanes, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_ConnectedTxDataLanes, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_ConnectedTxDataLanes(%x)\n", PA_ConnectedTxDataLanes));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_ConnectedTxDataLanes(%x) = %x \n", PA_ConnectedTxDataLanes, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_ConnectedRxDataLanes, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_ConnectedRxDataLanes(%x)\n", PA_ConnectedRxDataLanes));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_ConnectedRxDataLanes(%x) = %x \n", PA_ConnectedRxDataLanes, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_ActiveTxDataLanes, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_ActiveTxDataLanes(%x)\n", PA_ActiveTxDataLanes));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_ActiveTxDataLanes(%x) = %x \n", PA_ActiveTxDataLanes, Value));
  ActiveTxDataLanes = Value;
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_ActiveRxDataLanes, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_ActiveRxDataLanes(%x)\n", PA_ActiveRxDataLanes));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_ActiveRxDataLanes(%x) = %x \n", PA_ActiveRxDataLanes, Value));
  ActiveRxDataLanes = Value;
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_TxPWRStatus, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_TxPWRStatus(%x)\n", PA_TxPWRStatus));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_TxPWRStatus(%x) = %x \n", PA_TxPWRStatus, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_RxPWRStatus, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_RxPWRStatus(%x)\n", PA_RxPWRStatus));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_RxPWRStatus(%x) = %x \n", PA_RxPWRStatus, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_TxHsAdaptType, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_TxHsAdaptType(%x)\n", PA_TxHsAdaptType));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_TxHsAdaptType(%x) = %x \n", PA_TxHsAdaptType, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_AdaptTypeInPA_INIT, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_AdaptTypeInPA_INIT(%x)\n", PA_AdaptTypeInPA_INIT));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_AdaptTypeInPA_INIT(%x) = %x \n", PA_AdaptTypeInPA_INIT, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (DL_FC0ProtectionTimeOutVal, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet DL_FC0ProtectionTimeOutVal(%x)\n", DL_FC0ProtectionTimeOutVal));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet DL_FC0ProtectionTimeOutVal(%x) = %x \n", DL_FC0ProtectionTimeOutVal, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (DL_TC0ReplayTimeOutVal, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet DL_TC0ReplayTimeOutVal(%x)\n", DL_TC0ReplayTimeOutVal));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet DL_TC0ReplayTimeOutVal(%x) = %x \n", DL_TC0ReplayTimeOutVal, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (DL_AFC0ReqTimeOutVal, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet DL_AFC0ReqTimeOutVal(%x)\n", DL_AFC0ReqTimeOutVal));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet DL_AFC0ReqTimeOutVal(%x) = %x \n", DL_AFC0ReqTimeOutVal, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_TXGear, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_TXGear(%x)\n", PA_TXGear));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_TXGear(%x) = %x \n", PA_TXGear, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_TxTermination, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_TxTermination(%x)\n", PA_TxTermination));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_TxTermination(%x) = %x \n", PA_TxTermination, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_HSSeries, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_HSSeries(%x)\n", PA_HSSeries));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_HSSeries(%x) = %x \n", PA_HSSeries, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_RXGear, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_RXGear(%x)\n", PA_RXGear));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_RXGear(%x) = %x \n", PA_RXGear, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_RxTermination, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_RxTermination(%x)\n", PA_RxTermination));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_RxTermination(%x) = %x \n", PA_RxTermination, Value));
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_HSSeries, 0), 0, 0, &Value);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_HSSeries(%x)\n", PA_HSSeries));
  }
  DEBUG ((DEBUG_INFO, "UfsUicDmeGet PA_HSSeries(%x) = %x \n", PA_HSSeries, Value));
  DEBUG ((DEBUG_INFO, "UfsDumpLinkConfig Exit \n"));
  return EFI_SUCCESS;
}

/**
  Swap little endian to big endian.

  @param[in, out] Buffer      The data buffer. In input, it contains little endian data.
                              In output, it will become big endian.
  @param[in]      BufferSize  The length of converted data.

**/
VOID
SwapLittleEndianToBigEndian (
  IN OUT UINT8         *Buffer,
  IN     UINT32        BufferSize
  )
{
  UINT32 Index;
  UINT8  Temp;
  UINT32 SwapCount;

  SwapCount = BufferSize / 2;
  for (Index = 0; Index < SwapCount; Index++) {
    Temp = Buffer[Index];
    Buffer[Index] = Buffer[BufferSize - 1 - Index];
    Buffer[BufferSize - 1 - Index] = Temp;
  }
}

/**
  Fill TSF field of QUERY REQUEST UPIU.

  @param[in, out] TsfBase      The base address of TSF field of QUERY REQUEST UPIU.
  @param[in]      Opcode       The opcode of request.
  @param[in]      DescId       The descriptor ID of request.
  @param[in]      Index        The index of request.
  @param[in]      Selector     The selector of request.
  @param[in]      Length       The length of transferred data. The maximum is 4.
  @param[in]      Value        The value of transferred data.

**/
VOID
UfsFillTsfOfQueryReqUpiu (
  IN OUT UTP_UPIU_TSF        *TsfBase,
  IN     UINT8               Opcode,
  IN     UINT8               DescId    OPTIONAL,
  IN     UINT8               Index     OPTIONAL,
  IN     UINT8               Selector  OPTIONAL,
  IN     UINT16              Length    OPTIONAL,
  IN     UINT32              Value     OPTIONAL
  )
{
  ASSERT (TsfBase != NULL);
  ASSERT (Opcode <= UtpQueryFuncOpcodeTogFlag);

  TsfBase->Opcode   = Opcode;
  if (Opcode != UtpQueryFuncOpcodeNop) {
    TsfBase->DescId   = DescId;
    TsfBase->Index    = Index;
    TsfBase->Selector = Selector;

    if ((Opcode == UtpQueryFuncOpcodeRdDesc) || (Opcode == UtpQueryFuncOpcodeWrDesc)) {
      SwapLittleEndianToBigEndian ((UINT8*)&Length, sizeof (Length));
      TsfBase->Length = Length;
    }

    if (Opcode == UtpQueryFuncOpcodeWrAttr) {
      SwapLittleEndianToBigEndian ((UINT8*)&Value, sizeof (Value));
      TsfBase->Value  = Value;
    }
  }
}

/**
  Initialize COMMAND UPIU.

  @param[in, out] Command         The base address of COMMAND UPIU.
  @param[in]      Lun             The Lun on which the SCSI command is executed.
  @param[in]      TaskTag         The task tag of request.
  @param[in]      Cdb             The cdb buffer containing SCSI command.
  @param[in]      CdbLength       The cdb length.
  @param[in]      DataDirection   The direction of data transfer.
  @param[in]      ExpDataTranLen  The expected transfer data length.

  @retval EFI_SUCCESS     The initialization succeed.

**/
EFI_STATUS
UfsInitCommandUpiu (
  IN OUT UTP_COMMAND_UPIU              *Command,
  IN     UINT8                         Lun,
  IN     UINT8                         TaskTag,
  IN     UINT8                         *Cdb,
  IN     UINT8                         CdbLength,
  IN     UFS_DATA_DIRECTION            DataDirection,
  IN     UINT32                        ExpDataTranLen
  )
{
  UINT8                   Flags;

  ASSERT ((Command != NULL) && (Cdb != NULL));

  //
  // Task attribute is hard-coded to Ordered.
  //
  if (DataDirection == UfsDataIn) {
    Flags = BIT0 | BIT6;
  } else if (DataDirection == UfsDataOut) {
    Flags = BIT0 | BIT5;
  } else {
    Flags = BIT0;
  }

  //
  // Fill UTP COMMAND UPIU associated fields.
  //
  Command->TransCode = 0x01;
  Command->Flags     = Flags;
  Command->Lun       = Lun;
  Command->TaskTag   = TaskTag;
  Command->CmdSet    = 0x00;
  SwapLittleEndianToBigEndian ((UINT8*)&ExpDataTranLen, sizeof (ExpDataTranLen));
  Command->ExpDataTranLen = ExpDataTranLen;

  CopyMem (Command->Cdb, Cdb, CdbLength);

  return EFI_SUCCESS;
}

/**
  Initialize UTP PRDT for data transfer.

  @param[in] Prdt         The base address of PRDT.
  @param[in] Buffer       The buffer to be read or written.
  @param[in] BufferSize   The data size to be read or written.

  @retval EFI_SUCCESS     The initialization succeed.

**/
EFI_STATUS
UfsInitUtpPrdt (
  IN  UTP_TR_PRD                       *Prdt,
  IN  VOID                             *Buffer,
  IN  UINT32                           BufferSize
  )
{
  UINT32     PrdtIndex;
  UINT32     RemainingLen;
  UINT8      *Remaining;
  UINTN      PrdtNumber;

  if (BufferSize == 0) {
    return EFI_SUCCESS;
  }

  ASSERT (((UINTN)Buffer & (BIT0 | BIT1)) == 0);

  RemainingLen = BufferSize;
  Remaining    = Buffer;
  PrdtNumber   = (UINTN)DivU64x32 ((UINT64)BufferSize + UFS_MAX_DATA_LEN_PER_PRD - 1, UFS_MAX_DATA_LEN_PER_PRD);

  for (PrdtIndex = 0; PrdtIndex < PrdtNumber; PrdtIndex++) {
    if (RemainingLen < UFS_MAX_DATA_LEN_PER_PRD) {
      Prdt[PrdtIndex].DbCount = (UINT32)RemainingLen - 1;
    } else {
      Prdt[PrdtIndex].DbCount = UFS_MAX_DATA_LEN_PER_PRD - 1;
    }

    Prdt[PrdtIndex].DbAddr  = (UINT32)RShiftU64 ((UINT64)(UINTN)Remaining, 2);
    Prdt[PrdtIndex].DbAddrU = (UINT32)RShiftU64 ((UINT64)(UINTN)Remaining, 32);
    RemainingLen -= UFS_MAX_DATA_LEN_PER_PRD;
    Remaining    += UFS_MAX_DATA_LEN_PER_PRD;
  }

  return EFI_SUCCESS;
}

/**
  Initialize QUERY REQUEST UPIU.

  @param[in, out] QueryReq      The base address of QUERY REQUEST UPIU.
  @param[in]      TaskTag       The task tag of request.
  @param[in]      Opcode        The opcode of request.
  @param[in]      DescId        The descriptor ID of request.
  @param[in]      Index         The index of request.
  @param[in]      Selector      The selector of request.
  @param[in]      DataSize      The data size to be read or written.
  @param[in]      Data          The buffer to be read or written.

  @retval EFI_SUCCESS           The initialization succeed.

**/
EFI_STATUS
UfsInitQueryRequestUpiu (
  IN OUT UTP_QUERY_REQ_UPIU            *QueryReq,
  IN     UINT8                         TaskTag,
  IN     UINT8                         Opcode,
  IN     UINT8                         DescId,
  IN     UINT8                         Index,
  IN     UINT8                         Selector,
  IN     UINTN                         DataSize   OPTIONAL,
  IN     UINT8                         *Data      OPTIONAL
  )
{
  ASSERT (QueryReq != NULL);

  QueryReq->TransCode = 0x16;
  QueryReq->TaskTag   = TaskTag;
  if ((Opcode == UtpQueryFuncOpcodeRdDesc) || (Opcode == UtpQueryFuncOpcodeRdFlag) || (Opcode == UtpQueryFuncOpcodeRdAttr)) {
    QueryReq->QueryFunc = QUERY_FUNC_STD_READ_REQ;
  } else {
    QueryReq->QueryFunc = QUERY_FUNC_STD_WRITE_REQ;
  }

  if (Opcode == UtpQueryFuncOpcodeWrAttr) {
    UfsFillTsfOfQueryReqUpiu (&QueryReq->Tsf, Opcode, DescId, Index, Selector, 0, *(UINT32*)Data);
  } else if ((Opcode == UtpQueryFuncOpcodeRdDesc) || (Opcode == UtpQueryFuncOpcodeWrDesc)) {
    UfsFillTsfOfQueryReqUpiu (&QueryReq->Tsf, Opcode, DescId, Index, Selector, (UINT16)DataSize, 0);
  } else {
    UfsFillTsfOfQueryReqUpiu (&QueryReq->Tsf, Opcode, DescId, Index, Selector, 0, 0);
  }

  if (Opcode == UtpQueryFuncOpcodeWrDesc) {
    CopyMem (QueryReq + 1, Data, DataSize);
  }

  return EFI_SUCCESS;
}

/**
  Allocate COMMAND/RESPONSE UPIU for filling UTP TRD's command descriptor field.

  @param[in]  Private           The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]  Lun               The Lun on which the SCSI command is executed.
  @param[in]  Packet            The pointer to the EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET data structure.
  @param[in]  Trd               The pointer to the UTP Transfer Request Descriptor.
  @param[out] CmdDescHost       A pointer to store the base system memory address of the allocated range.
  @param[out] CmdDescMapping    A resulting value to pass to Unmap().

  @retval EFI_SUCCESS           The creation succeed.
  @retval EFI_DEVICE_ERROR      The creation failed.
  @retval EFI_OUT_OF_RESOURCES  The memory resource is insufficient.

**/
EFI_STATUS
UfsCreateScsiCommandDesc (
  IN     UFS_PASS_THRU_PRIVATE_DATA                  *Private,
  IN     UINT8                                       Lun,
  IN     EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET  *Packet,
  IN     UTP_TRD                                     *Trd,
     OUT VOID                                        **CmdDescHost,
     OUT VOID                                        **CmdDescMapping
  )
{
  UINTN                             TotalLen;
  UINTN                             PrdtNumber;
  UTP_COMMAND_UPIU                  *CommandUpiu;
  EFI_PHYSICAL_ADDRESS              CmdDescPhyAddr;
  EFI_STATUS                        Status;
  UINT32                            DataLen;
  UFS_DATA_DIRECTION                DataDirection;

  ASSERT ((Private != NULL) && (Packet != NULL) && (Trd != NULL));

  if (Packet->DataDirection == EFI_EXT_SCSI_DATA_DIRECTION_READ) {
    DataLen       = Packet->InTransferLength;
    DataDirection = UfsDataIn;
  } else {
    DataLen       = Packet->OutTransferLength;
    DataDirection = UfsDataOut;
  }

  if (DataLen == 0) {
    DataDirection = UfsNoData;
  }

  PrdtNumber = (UINTN)DivU64x32 ((UINT64)DataLen + UFS_MAX_DATA_LEN_PER_PRD - 1, UFS_MAX_DATA_LEN_PER_PRD);

  TotalLen   = ROUNDUP8 (sizeof (UTP_COMMAND_UPIU)) + ROUNDUP8 (sizeof (UTP_RESPONSE_UPIU)) + PrdtNumber * sizeof (UTP_TR_PRD);

  Status = UfsAllocateAlignCommonBuffer (Private, TotalLen, CmdDescHost, &CmdDescPhyAddr, CmdDescMapping);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  CommandUpiu = (UTP_COMMAND_UPIU*)*CmdDescHost;

  UfsInitCommandUpiu (CommandUpiu, Lun, Private->TaskTag++, Packet->Cdb, Packet->CdbLength, DataDirection, DataLen);

  //
  // Fill UTP_TRD associated fields
  // NOTE: Some UFS host controllers request the Response UPIU and the Physical Region Description Table
  // *MUST* be located at a 64-bit aligned boundary.
  //
  Trd->Int    = UFS_INTERRUPT_COMMAND;
  Trd->Dd     = DataDirection;
  Trd->Ct     = UFS_STORAGE_COMMAND_TYPE;
  Trd->Ocs    = UFS_HC_TRD_OCS_INIT_VALUE;
  Trd->UcdBa  = (UINT32)RShiftU64 ((UINT64)CmdDescPhyAddr, 7);
  Trd->UcdBaU = (UINT32)RShiftU64 ((UINT64)CmdDescPhyAddr, 32);
  Trd->RuL    = (UINT16)DivU64x32 ((UINT64)ROUNDUP8 (sizeof (UTP_RESPONSE_UPIU)), sizeof (UINT32));
  Trd->RuO    = (UINT16)DivU64x32 ((UINT64)ROUNDUP8 (sizeof (UTP_COMMAND_UPIU)), sizeof (UINT32));
  Trd->PrdtL  = (UINT16)PrdtNumber;
  Trd->PrdtO  = (UINT16)DivU64x32 ((UINT64)(ROUNDUP8 (sizeof (UTP_COMMAND_UPIU)) + ROUNDUP8 (sizeof (UTP_RESPONSE_UPIU))), sizeof (UINT32));
  return EFI_SUCCESS;
}

/**
  Allocate QUERY REQUEST/QUERY RESPONSE UPIU for filling UTP TRD's command descriptor field.

  @param[in]  Private           The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]  Packet            The pointer to the UFS_DEVICE_MANAGEMENT_REQUEST_PACKET data structure.
  @param[in]  Trd               The pointer to the UTP Transfer Request Descriptor.
  @param[out] CmdDescHost       A pointer to store the base system memory address of the allocated range.
  @param[out] CmdDescMapping    A resulting value to pass to Unmap().

  @retval EFI_SUCCESS           The creation succeed.
  @retval EFI_DEVICE_ERROR      The creation failed.
  @retval EFI_OUT_OF_RESOURCES  The memory resource is insufficient.
  @retval EFI_INVALID_PARAMETER The parameter passed in is invalid.

**/
EFI_STATUS
UfsCreateDMCommandDesc (
  IN     UFS_PASS_THRU_PRIVATE_DATA            *Private,
  IN     UFS_DEVICE_MANAGEMENT_REQUEST_PACKET  *Packet,
  IN     UTP_TRD                               *Trd,
     OUT VOID                                  **CmdDescHost,
     OUT VOID                                  **CmdDescMapping
  )
{
  UINTN                         TotalLen;
  UTP_QUERY_REQ_UPIU            *QueryReqUpiu;
  UINT8                         Opcode;
  UINT32                        DataSize;
  UINT8                         *Data;
  UINT8                         DataDirection;
  EFI_PHYSICAL_ADDRESS          CmdDescPhyAddr;
  EFI_STATUS                    Status;

  ASSERT ((Private != NULL) && (Packet != NULL) && (Trd != NULL));

  Opcode = Packet->Opcode;
  if ((Opcode > UtpQueryFuncOpcodeTogFlag) || (Opcode == UtpQueryFuncOpcodeNop)) {
    return EFI_INVALID_PARAMETER;
  }

  DataDirection = Packet->DataDirection;
  DataSize      = Packet->TransferLength;
  Data          = Packet->DataBuffer;

  if ((Opcode == UtpQueryFuncOpcodeWrDesc) || (Opcode == UtpQueryFuncOpcodeRdDesc)) {
    if (DataSize == 0 || Data == NULL) {
      return EFI_INVALID_PARAMETER;
    }
    TotalLen = ROUNDUP8 (sizeof (UTP_QUERY_REQ_UPIU)) + ROUNDUP8 (sizeof (UTP_QUERY_RESP_UPIU)) + ROUNDUP8 (DataSize);
  } else {
    TotalLen = ROUNDUP8 (sizeof (UTP_QUERY_REQ_UPIU)) + ROUNDUP8 (sizeof (UTP_QUERY_RESP_UPIU));
  }

  Status = UfsAllocateAlignCommonBuffer (Private, TotalLen, CmdDescHost, &CmdDescPhyAddr, CmdDescMapping);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Initialize UTP QUERY REQUEST UPIU
  //
  QueryReqUpiu = (UTP_QUERY_REQ_UPIU*)*CmdDescHost;
  ASSERT (QueryReqUpiu != NULL);
  UfsInitQueryRequestUpiu (
    QueryReqUpiu,
    Private->TaskTag++,
    Opcode,
    Packet->DescId,
    Packet->Index,
    Packet->Selector,
    DataSize,
    Data
    );

  //
  // Fill UTP_TRD associated fields
  // NOTE: Some UFS host controllers request the Query Response UPIU *MUST* be located at a 64-bit aligned boundary.
  //
  Trd->Int    = UFS_INTERRUPT_COMMAND;
  Trd->Dd     = DataDirection;
  Trd->Ct     = UFS_STORAGE_COMMAND_TYPE;
  Trd->Ocs    = UFS_HC_TRD_OCS_INIT_VALUE;
  Trd->UcdBa  = (UINT32)RShiftU64 ((UINT64)CmdDescPhyAddr, 7);
  Trd->UcdBaU = (UINT32)RShiftU64 ((UINT64)CmdDescPhyAddr, 32);
  if (Opcode == UtpQueryFuncOpcodeWrDesc) {
    Trd->RuL  = (UINT16)DivU64x32 ((UINT64)ROUNDUP8 (sizeof (UTP_QUERY_RESP_UPIU)), sizeof (UINT32));
    Trd->RuO  = (UINT16)DivU64x32 ((UINT64)ROUNDUP8 (sizeof (UTP_QUERY_REQ_UPIU)) + ROUNDUP8 (DataSize), sizeof (UINT32));
  } else {
    Trd->RuL  = (UINT16)DivU64x32 ((UINT64)ROUNDUP8 (sizeof (UTP_QUERY_RESP_UPIU)) + ROUNDUP8 (DataSize), sizeof (UINT32));
    Trd->RuO  = (UINT16)DivU64x32 ((UINT64)ROUNDUP8 (sizeof (UTP_QUERY_REQ_UPIU)), sizeof (UINT32));
  }

  return EFI_SUCCESS;
}

/**
  Allocate NOP IN and NOP OUT UPIU for filling UTP TRD's command descriptor field.

  @param[in]  Private           The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]  Trd               The pointer to the UTP Transfer Request Descriptor.
  @param[out] CmdDescHost       A pointer to store the base system memory address of the allocated range.
  @param[out] CmdDescMapping    A resulting value to pass to Unmap().

  @retval EFI_SUCCESS           The creation succeed.
  @retval EFI_DEVICE_ERROR      The creation failed.
  @retval EFI_OUT_OF_RESOURCES  The memory resource is insufficient.

**/
EFI_STATUS
UfsCreateNopCommandDesc (
  IN     UFS_PASS_THRU_PRIVATE_DATA        *Private,
  IN     UTP_TRD                           *Trd,
     OUT VOID                              **CmdDescHost,
     OUT VOID                              **CmdDescMapping
  )
{
  UINTN                    TotalLen;
  UTP_NOP_OUT_UPIU         *NopOutUpiu;
  EFI_STATUS               Status;
  EFI_PHYSICAL_ADDRESS     CmdDescPhyAddr;

  ASSERT ((Private != NULL) && (Trd != NULL));

  TotalLen = ROUNDUP8 (sizeof (UTP_NOP_OUT_UPIU)) + ROUNDUP8 (sizeof (UTP_NOP_IN_UPIU));
  Status   = UfsAllocateAlignCommonBuffer (Private, TotalLen, CmdDescHost, &CmdDescPhyAddr, CmdDescMapping);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  NopOutUpiu = (UTP_NOP_OUT_UPIU*)*CmdDescHost;
  ASSERT (NopOutUpiu != NULL);
  NopOutUpiu->TaskTag = Private->TaskTag++;

  //
  // Fill UTP_TRD associated fields
  // NOTE: Some UFS host controllers request the Nop Out UPIU *MUST* be located at a 64-bit aligned boundary.
  //
  Trd->Int    = UFS_INTERRUPT_COMMAND;
  Trd->Dd     = 0x00;
  Trd->Ct     = UFS_STORAGE_COMMAND_TYPE;
  Trd->Ocs    = UFS_HC_TRD_OCS_INIT_VALUE;
  Trd->UcdBa  = (UINT32)RShiftU64 ((UINT64)CmdDescPhyAddr, 7);
  Trd->UcdBaU = (UINT32)RShiftU64 ((UINT64)CmdDescPhyAddr, 32);
  Trd->RuL    = (UINT16)DivU64x32 ((UINT64)ROUNDUP8 (sizeof (UTP_NOP_IN_UPIU)), sizeof (UINT32));
  Trd->RuO    = (UINT16)DivU64x32 ((UINT64)ROUNDUP8 (sizeof (UTP_NOP_OUT_UPIU)), sizeof (UINT32));

  return EFI_SUCCESS;
}

/**
  Find out available slot in transfer list of a UFS device.

  @param[in]  Private       The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[out] Slot          The available slot.

  @retval EFI_SUCCESS       The available slot was found successfully.
  @retval EFI_NOT_READY     No slot is available at this moment.

**/
EFI_STATUS
UfsFindAvailableSlotInTrl (
  IN     UFS_PASS_THRU_PRIVATE_DATA   *Private,
     OUT UINT8                        *Slot
  )
{
  UINT32           Data;
  EFI_STATUS       Status;

  ASSERT ((Private != NULL) && (Slot != NULL));

  Status  = UfsMmioRead32 (Private, UFS_HC_UTRLDBR_OFFSET, &Data);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // WA: Only use slot #0
  //
  if (((Data & BIT0) == 0) &&
      ((Private->SlotsInUse & BIT0) == 0)) {
    *Slot = 0;
    return EFI_SUCCESS;
  }

  return EFI_NOT_READY;
}

/**
  Find out available slot in task management transfer list of a UFS device.

  @param[in]  Private       The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[out] Slot          The available slot.

  @retval EFI_SUCCESS       The available slot was found successfully.

**/
EFI_STATUS
UfsFindAvailableSlotInTmrl (
  IN     UFS_PASS_THRU_PRIVATE_DATA   *Private,
     OUT UINT8                        *Slot
  )
{
  ASSERT ((Private != NULL) && (Slot != NULL));

  //
  // The simplest algo to always use slot 0.
  // TODO: enhance it to support async transfer with multiple slot.
  //
  *Slot = 0;

  return EFI_SUCCESS;
}
  //
  // RPPO-LKF-0009: OverrideBegin
  //
/**
  Clear utrlcnr bit of the specified slot.

  @param[in]  Private       The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]  Slot          The slot for which it need to be cleared.

**/
EFI_STATUS
UfsClearUtrlcnr (
  IN  UFS_PASS_THRU_PRIVATE_DATA   *Private,
  IN  UINT8                        Slot
  )
{
  UINT32        Data;
  EFI_STATUS    Status;

  if ( Private->Version >= UFS_HC_VER_2_1) {
    Status = UfsMmioRead32 (Private, UFS_HC_UTRLCNR_OFFSET, &Data);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    Status = UfsMmioWrite32 (Private, UFS_HC_UTRLCNR_OFFSET, Data & (BIT0 << Slot));
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }
  return EFI_SUCCESS;
}
  //
  // RPPO-LKF-0009: OverrideEnd
  //
/**
  Start specified slot in transfer list of a UFS device.

  @param[in]  Private       The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]  Slot          The slot to be started.

**/
EFI_STATUS
UfsStartExecCmd (
  IN  UFS_PASS_THRU_PRIVATE_DATA   *Private,
  IN  UINT8                        Slot
  )
{
  UINT32        Data;
  EFI_STATUS    Status;

  Status = UfsMmioRead32 (Private, UFS_HC_UTRLRSR_OFFSET, &Data);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if ((Data & UFS_HC_UTRLRSR) != UFS_HC_UTRLRSR) {
    Status = UfsMmioWrite32 (Private, UFS_HC_UTRLRSR_OFFSET, UFS_HC_UTRLRSR);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  Status = UfsMmioWrite32 (Private, UFS_HC_UTRLDBR_OFFSET, BIT0 << Slot);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Private->SlotsInUse |= BIT0 << Slot;
  Status = UfsMmioRead32(Private, UFS_HC_UTRLDBR_OFFSET, &Data);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  return EFI_SUCCESS;
}

/**
  Stop specified slot in transfer list of a UFS device.

  @param[in]  Private       The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]  Slot          The slot to be stop.

**/
EFI_STATUS
UfsStopExecCmd (
  IN  UFS_PASS_THRU_PRIVATE_DATA   *Private,
  IN  UINT8                        Slot
  )
{
  UINT32        Data;
  EFI_STATUS    Status;

  Status = UfsMmioRead32 (Private, UFS_HC_UTRLDBR_OFFSET, &Data);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if ((Data & (BIT0 << Slot)) != 0) {
    Status = UfsMmioRead32 (Private, UFS_HC_UTRLCLR_OFFSET, &Data);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = UfsMmioWrite32 (Private, UFS_HC_UTRLCLR_OFFSET, Data & ~(BIT0 << Slot));
    if (EFI_ERROR (Status)) {
      return Status;
    }
  //
  // RPPO-LKF-0009: OverrideBegin
  //
    Status = UfsClearUtrlcnr (Private, Slot);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  //
  // RPPO-LKF-0009: OverrideEnd
  //
  }
  Private->SlotsInUse &= ~(BIT0 << Slot);

  return EFI_SUCCESS;
}

/**
  Extracts return data from query response upiu

  @param[in] Packet     Pointer to the UFS_DEVICE_MANAGEMENT_REQUEST_PACKET
  @param[in] QueryResp  Pointer to the query response

  @retval EFI_INVALID_PARAMETER Packet or QueryResp are empty or opcode is invalid
  @retval EFI_SUCCESS           Data extracted
**/
EFI_STATUS
UfsGetReturnDataFromQueryResponse (
  IN UFS_DEVICE_MANAGEMENT_REQUEST_PACKET  *Packet,
  IN UTP_QUERY_RESP_UPIU                   *QueryResp
  )
{
  UINT16  ReturnDataSize;
  UINT32  ReturnData;

  if (Packet == NULL || QueryResp == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  switch (Packet->Opcode) {
    case UtpQueryFuncOpcodeRdDesc:
      ReturnDataSize = QueryResp->Tsf.Length;
      SwapLittleEndianToBigEndian ((UINT8*)&ReturnDataSize, sizeof (UINT16));
      CopyMem (Packet->DataBuffer, (QueryResp + 1), ReturnDataSize);
      Packet->TransferLength = ReturnDataSize;
      break;
    case UtpQueryFuncOpcodeWrDesc:
      ReturnDataSize = QueryResp->Tsf.Length;
      SwapLittleEndianToBigEndian ((UINT8*)&ReturnDataSize, sizeof (UINT16));
      Packet->TransferLength = ReturnDataSize;
      break;
    case UtpQueryFuncOpcodeRdFlag:
    case UtpQueryFuncOpcodeSetFlag:
    case UtpQueryFuncOpcodeClrFlag:
    case UtpQueryFuncOpcodeTogFlag:
      CopyMem (Packet->DataBuffer, &QueryResp->Tsf.Value, sizeof (UINT32));
      break;
    case UtpQueryFuncOpcodeRdAttr:
    case UtpQueryFuncOpcodeWrAttr:
      ReturnData = QueryResp->Tsf.Value;
      SwapLittleEndianToBigEndian ((UINT8*) &ReturnData, sizeof (UINT32));
      CopyMem (Packet->DataBuffer, &ReturnData, sizeof (UINT32));
      break;
    default:
      return EFI_INVALID_PARAMETER;
  }

  return EFI_SUCCESS;
}

/**
  Creates Transfer Request descriptor and sends Query Request to the device

  @param[in] Private Pointer to the UFS_PASS_THRU_PRIVATE_DATA
  @param[in] Packet  Pointer to the UFS_DEVICE_MANAGEMENT_REQUEST_PACKET

  @retval EFI_SUCCESS           The device descriptor was read/written successfully.
  @retval EFI_DEVICE_ERROR      A device error occurred while attempting to r/w the device descriptor.
  @retval EFI_TIMEOUT           A timeout occurred while waiting for the completion of r/w the device descriptor.
**/
EFI_STATUS
UfsSendDmRequestRetry (
  IN UFS_PASS_THRU_PRIVATE_DATA            *Private,
  IN UFS_DEVICE_MANAGEMENT_REQUEST_PACKET  *Packet
  )
{
  UINT8                               Slot;
  UTP_TRD                             *Trd;
  VOID                                *CmdDescHost;
  VOID                                *CmdDescMapping;
  UINT32                              CmdDescSize;
  EDKII_UFS_HOST_CONTROLLER_PROTOCOL  *UfsHc;
  UTP_QUERY_RESP_UPIU                 *QueryResp;
  EFI_STATUS                          Status;
  //
  // Find out which slot of transfer request list is available.
  //
  Status = UfsFindAvailableSlotInTrl (Private, &Slot);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Trd = ((UTP_TRD*)Private->UtpTrlBase) + Slot;
  //
  // Fill transfer request descriptor to this slot.
  //
  Status = UfsCreateDMCommandDesc (Private, Packet, Trd, &CmdDescHost, &CmdDescMapping);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to create DM command descriptor\n"));
    return Status;
  }

  UfsHc       = Private->UfsHostController;
  QueryResp   = (UTP_QUERY_RESP_UPIU*)((UINT8*)CmdDescHost + Trd->RuO * sizeof (UINT32));
  ASSERT (QueryResp != NULL);
  CmdDescSize = Trd->RuO * sizeof (UINT32) + Trd->RuL * sizeof (UINT32);

  //
  // Start to execute the transfer request.
  //
  UfsStartExecCmd (Private, Slot);

  //
  // Wait for the completion of the transfer request.
  //
  Status = UfsWaitMemSet (Private, UFS_HC_UTRLDBR_OFFSET, BIT0 << Slot, 0, Packet->Timeout);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsSendDmRequestRetry: UfsWaitMemSet BIT0 << Slot:  ERROR!\n"));
    goto Exit;
  }
  //
  // RPPO-LKF-0009: OverrideBegin
  //
  Status = UfsClearUtrlcnr (Private, Slot);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // RPPO-LKF-0009: OverrideEnd
  //
  if (Trd->Ocs != 0 || QueryResp->QueryResp != UfsUtpQueryResponseSuccess) {
    DEBUG ((EFI_D_ERROR, "Failed to send query request, OCS = %X, QueryResp = %X\n", Trd->Ocs, QueryResp->QueryResp));
    DumpQueryResponseResult (QueryResp->QueryResp);
    UfsDumpHcRegisters (Private, FALSE);
    DEBUG ((DEBUG_INFO, "Failed to send query request: UFS REGISTER DUMP EXIT-------------------\n" ));
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  Status = UfsGetReturnDataFromQueryResponse (Packet, QueryResp);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Failed to get return data from query response\n"));
    goto Exit;
  }

Exit:
  UfsHc->Flush (UfsHc);

  UfsStopExecCmd (Private, Slot);

  if (CmdDescMapping != NULL) {
    UfsHc->Unmap (UfsHc, CmdDescMapping);
  }
  if (CmdDescHost != NULL) {
    UfsHc->FreeBuffer (UfsHc, EFI_SIZE_TO_PAGES (CmdDescSize), CmdDescHost);
  }

  return Status;

}

/**
  Sends Query Request to the device. Query is sent until device responds correctly or counter runs out

  @param[in] Private Pointer to the UFS_PASS_THRU_PRIVATE_DATA.
  @param[in] Packet  Pointer to the UFS_DEVICE_MANAGEMENT_PACKET.

  @retval EFI_SUCCESS           The device responded correctly to the Query request.
  @retval EFI_DEVICE_ERROR      A device error occurred while waiting for the response from the device.
  @retval EFI_TIMEOUT           A timeout occurred while waiting for the completion of the operation.

**/
EFI_STATUS
UfsSendDmRequest (
  IN UFS_PASS_THRU_PRIVATE_DATA            *Private,
  IN UFS_DEVICE_MANAGEMENT_REQUEST_PACKET  *Packet
  )
{
  EFI_STATUS  Status;
  UINT8       Retry;

  Status = EFI_SUCCESS;
  //
  // RPPO-LKF-0036: OverrideBegin
  //
  for (Retry = 0; Retry < 100; Retry ++) {
    Status = UfsSendDmRequestRetry (Private, Packet);
    if (!EFI_ERROR (Status)) {
      return EFI_SUCCESS;
    }
  }
  //
  // RPPO-LKF-0036: OverrideEnd
  //
  DEBUG ((EFI_D_ERROR, "Failed to get response from the device after %d retries\n", Retry));
  return Status;
}

/**
  Read or write specified device descriptor of a UFS device.

  @param[in]      Private       The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]      Read          The boolean variable to show r/w direction.
  @param[in]      DescId        The ID of device descriptor.
  @param[in]      Index         The Index of device descriptor.
  @param[in]      Selector      The Selector of device descriptor.
  @param[in, out] Descriptor    The buffer of device descriptor to be read or written.
  @param[in]      DescSize      The size of device descriptor buffer.

  @retval EFI_SUCCESS           The device descriptor was read/written successfully.
  @retval EFI_DEVICE_ERROR      A device error occurred while attempting to r/w the device descriptor.
  @retval EFI_TIMEOUT           A timeout occurred while waiting for the completion of r/w the device descriptor.

**/
EFI_STATUS
UfsRwDeviceDesc (
  IN     UFS_PASS_THRU_PRIVATE_DATA   *Private,
  IN     BOOLEAN                      Read,
  IN     UINT8                        DescId,
  IN     UINT8                        Index,
  IN     UINT8                        Selector,
  IN OUT VOID                         *Descriptor,
  IN OUT UINT32                       *DescSize                              // RPPO-LKF-0023: Override
  )
{
  UFS_DEVICE_MANAGEMENT_REQUEST_PACKET Packet;
  EFI_STATUS                            Status;                             // RPPO-LKF-0023: Override

  ZeroMem (&Packet, sizeof (UFS_DEVICE_MANAGEMENT_REQUEST_PACKET));

  if (Read) {
    Packet.DataDirection     = UfsDataIn;
    Packet.Opcode            = UtpQueryFuncOpcodeRdDesc;
  } else {
    Packet.DataDirection     = UfsDataOut;
    Packet.Opcode            = UtpQueryFuncOpcodeWrDesc;
  }
  Packet.DataBuffer          = Descriptor;
  Packet.TransferLength      = *DescSize;
  Packet.DescId              = DescId;
  Packet.Index               = Index;
  Packet.Selector            = Selector;
  Packet.Timeout             = UFS_TIMEOUT;

  //
  // RPPO-LKF-0023: OverrideBegin
  //
  Status = UfsSendDmRequest (Private, &Packet);
  if (EFI_ERROR (Status)) {
    *DescSize = 0;
  } else {
    *DescSize = Packet.TransferLength;
  }

  return Status;
  //
  // RPPO-LKF-0023: OverrideEnd
  //
}

/**
  Read or write specified attribute of a UFS device.

  @param[in]      Private       The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]      Read          The boolean variable to show r/w direction.
  @param[in]      AttrId        The ID of Attribute.
  @param[in]      Index         The Index of Attribute.
  @param[in]      Selector      The Selector of Attribute.
  @param[in, out] Attributes    The value of Attribute to be read or written.

  @retval EFI_SUCCESS           The Attribute was read/written successfully.
  @retval EFI_DEVICE_ERROR      A device error occurred while attempting to r/w the Attribute.
  @retval EFI_TIMEOUT           A timeout occurred while waiting for the completion of r/w the Attribute.

**/
EFI_STATUS
UfsRwAttributes (
  IN     UFS_PASS_THRU_PRIVATE_DATA   *Private,
  IN     BOOLEAN                      Read,
  IN     UINT8                        AttrId,
  IN     UINT8                        Index,
  IN     UINT8                        Selector,
  IN OUT UINT32                       *Attributes
  )
{
  UFS_DEVICE_MANAGEMENT_REQUEST_PACKET Packet;

  ZeroMem (&Packet, sizeof (UFS_DEVICE_MANAGEMENT_REQUEST_PACKET));

  if (Read) {
    Packet.DataDirection     = UfsDataIn;
    Packet.Opcode            = UtpQueryFuncOpcodeRdAttr;
  } else {
    Packet.DataDirection     = UfsDataOut;
    Packet.Opcode            = UtpQueryFuncOpcodeWrAttr;
  }
  Packet.DataBuffer          = Attributes;
  Packet.DescId              = AttrId;
  Packet.Index               = Index;
  Packet.Selector            = Selector;
  Packet.Timeout             = UFS_TIMEOUT;

  return UfsSendDmRequest (Private, &Packet);
}

/**
  Read or write specified flag of a UFS device.

  @param[in]      Private       The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]      Read          The boolean variable to show r/w direction.
  @param[in]      FlagId        The ID of flag to be read or written.
  @param[in, out] Value         The value to set or clear flag.

  @retval EFI_SUCCESS           The flag was read/written successfully.
  @retval EFI_DEVICE_ERROR      A device error occurred while attempting to r/w the flag.
  @retval EFI_TIMEOUT           A timeout occurred while waiting for the completion of r/w the flag.

**/
EFI_STATUS
UfsRwFlags (
  IN     UFS_PASS_THRU_PRIVATE_DATA   *Private,
  IN     BOOLEAN                      Read,
  IN     UINT8                        FlagId,
  IN OUT UINT32                       *Value
  )
{
  UFS_DEVICE_MANAGEMENT_REQUEST_PACKET Packet;

  if (Value == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ZeroMem (&Packet, sizeof (UFS_DEVICE_MANAGEMENT_REQUEST_PACKET));

  if (Read) {
    ASSERT (Value != NULL);
    Packet.DataDirection     = UfsDataIn;
    Packet.Opcode            = UtpQueryFuncOpcodeRdFlag;
  } else {
    Packet.DataDirection     = UfsDataOut;
    if (*Value == 1) {
      Packet.Opcode          = UtpQueryFuncOpcodeSetFlag;
    } else if (*Value == 0) {
      Packet.Opcode          = UtpQueryFuncOpcodeClrFlag;
    } else {
      return EFI_INVALID_PARAMETER;
    }
  }
  Packet.DataBuffer          = Value;
  Packet.DescId              = FlagId;
  Packet.Index               = 0;
  Packet.Selector            = 0;
  Packet.Timeout             = UFS_TIMEOUT;

  return UfsSendDmRequest (Private, &Packet);
}

/**
  Set specified flag to 1 on a UFS device.

  @param[in]  Private           The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]  FlagId            The ID of flag to be set.

  @retval EFI_SUCCESS           The flag was set successfully.
  @retval EFI_DEVICE_ERROR      A device error occurred while attempting to set the flag.
  @retval EFI_TIMEOUT           A timeout occurred while waiting for the completion of setting the flag.

**/
EFI_STATUS
UfsSetFlag (
  IN  UFS_PASS_THRU_PRIVATE_DATA   *Private,
  IN  UINT8                        FlagId
  )
{
  EFI_STATUS             Status;
  UINT32                 Value;

  Value  = 1;
  Status = UfsRwFlags (Private, FALSE, FlagId, &Value);

  return Status;
}

/**
  Clear specified flag to 0 on a UFS device.

  @param[in]  Private           The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]  FlagId            The ID of flag to be cleared.

  @retval EFI_SUCCESS           The flag was cleared successfully.
  @retval EFI_DEVICE_ERROR      A device error occurred while attempting to clear the flag.
  @retval EFI_TIMEOUT           A timeout occurred while waiting for the completion of clearing the flag.

**/
EFI_STATUS
UfsClearFlag (
  IN  UFS_PASS_THRU_PRIVATE_DATA   *Private,
  IN  UINT8                        FlagId
  )
{
  EFI_STATUS             Status;
  UINT32                 Value;

  Value  = 0;
  Status = UfsRwFlags (Private, FALSE, FlagId, &Value);

  return Status;
}

/**
  Read specified flag from a UFS device.

  @param[in]  Private           The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]  FlagId            The ID of flag to be read.
  @param[out] Value             The flag's value.

  @retval EFI_SUCCESS           The flag was read successfully.
  @retval EFI_DEVICE_ERROR      A device error occurred while attempting to read the flag.
  @retval EFI_TIMEOUT           A timeout occurred while waiting for the completion of reading the flag.

**/
EFI_STATUS
UfsReadFlag (
  IN     UFS_PASS_THRU_PRIVATE_DATA   *Private,
  IN     UINT8                        FlagId,
     OUT UINT32                       *Value
  )
{
  EFI_STATUS                           Status;

  Status = UfsRwFlags (Private, TRUE, FlagId, Value);

  return Status;
}

/**
  Sends NOP IN cmd to a UFS device for initialization process request.
  For more details, please refer to UFS 2.0 spec Figure 13.3.

  @param[in]  Private           The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.

  @retval EFI_SUCCESS           The NOP IN command was sent by the host. The NOP OUT response was
                                received successfully.
  @retval EFI_DEVICE_ERROR      A device error occurred while attempting to execute NOP IN command.
  @retval EFI_OUT_OF_RESOURCES  The resource for transfer is not available.
  @retval EFI_TIMEOUT           A timeout occurred while waiting for the NOP IN command to execute.

**/
EFI_STATUS
UfsExecNopCmds (
  IN  UFS_PASS_THRU_PRIVATE_DATA       *Private
  )
{
  EFI_STATUS                           Status;
  UINT8                                Slot;
  UTP_TRD                              *Trd;
  UTP_NOP_IN_UPIU                      *NopInUpiu;
  UINT32                               CmdDescSize;
  VOID                                 *CmdDescHost;
  VOID                                 *CmdDescMapping;
  EDKII_UFS_HOST_CONTROLLER_PROTOCOL   *UfsHc;

  //
  // Find out which slot of transfer request list is available.
  //
  Status = UfsFindAvailableSlotInTrl (Private, &Slot);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Trd    = ((UTP_TRD*)Private->UtpTrlBase) + Slot;
  Status = UfsCreateNopCommandDesc (Private, Trd, &CmdDescHost, &CmdDescMapping);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Check the transfer request result.
  //
  UfsHc       = Private->UfsHostController;
  NopInUpiu   = (UTP_NOP_IN_UPIU*)((UINT8*)CmdDescHost + Trd->RuO * sizeof (UINT32));
  ASSERT (NopInUpiu != NULL);
  CmdDescSize = Trd->RuO * sizeof (UINT32) + Trd->RuL * sizeof (UINT32);

  //
  // Start to execute the transfer request.
  //
  UfsStartExecCmd (Private, Slot);

  //
  // Wait for the completion of the transfer request.
  //
  Status = UfsWaitMemSet (Private, UFS_HC_UTRLDBR_OFFSET, BIT0 << Slot, 0, UFS_TIMEOUT);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsExecNopCmds: UfsWaitMemSet BIT0 << Slot:  ERROR!\n"));
    goto Exit;
  }
  //
  // RPPO-LKF-0009: OverrideBegin
  //
  Status = UfsClearUtrlcnr (Private, Slot);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // RPPO-LKF-0009: OverrideEnd
  //
  if (NopInUpiu->Resp != 0) {
    Status = EFI_DEVICE_ERROR;
  } else {
    Status = EFI_SUCCESS;
  }

Exit:
  UfsHc->Flush (UfsHc);

  UfsStopExecCmd (Private, Slot);

  if (CmdDescMapping != NULL) {
    UfsHc->Unmap (UfsHc, CmdDescMapping);
  }
  if (CmdDescHost != NULL) {
    UfsHc->FreeBuffer (UfsHc, EFI_SIZE_TO_PAGES (CmdDescSize), CmdDescHost);
  }

  return Status;
}

/**
  Sends a UFS-supported SCSI Request Packet to a UFS device that is attached to the UFS host controller.

  @param[in]      Private       The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]      Lun           The LUN of the UFS device to send the SCSI Request Packet.
  @param[in, out] Packet        A pointer to the SCSI Request Packet to send to a specified Lun of the
                                UFS device.
  @param[in]      Event         If nonblocking I/O is not supported then Event is ignored, and blocking
                                I/O is performed. If Event is NULL, then blocking I/O is performed. If
                                Event is not NULL and non blocking I/O is supported, then
                                nonblocking I/O is performed, and Event will be signaled when the
                                SCSI Request Packet completes.

  @retval EFI_SUCCESS           The SCSI Request Packet was sent by the host. For bi-directional
                                commands, InTransferLength bytes were transferred from
                                InDataBuffer. For write and bi-directional commands,
                                OutTransferLength bytes were transferred by
                                OutDataBuffer.
  @retval EFI_DEVICE_ERROR      A device error occurred while attempting to send the SCSI Request
                                Packet.
  @retval EFI_OUT_OF_RESOURCES  The resource for transfer is not available.
  @retval EFI_TIMEOUT           A timeout occurred while waiting for the SCSI Request Packet to execute.

**/
EFI_STATUS
UfsExecScsiCmds (
  IN     UFS_PASS_THRU_PRIVATE_DATA                  *Private,
  IN     UINT8                                       Lun,
  IN OUT EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET  *Packet,
  IN     EFI_EVENT                                   Event    OPTIONAL
  )
{
  EFI_STATUS                           Status;
  UTP_RESPONSE_UPIU                    *Response;
  UINT16                               SenseDataLen;
  UINT32                               ResTranCount;
  VOID                                 *DataBuf;
  EFI_PHYSICAL_ADDRESS                 DataBufPhyAddr;
  UINT32                               DataLen;
  UINTN                                MapLength;
  EDKII_UFS_HOST_CONTROLLER_PROTOCOL   *UfsHc;
  EDKII_UFS_HOST_CONTROLLER_OPERATION  Flag;
  UTP_TR_PRD                           *PrdtBase;
  EFI_TPL                              OldTpl;
  UFS_PASS_THRU_TRANS_REQ              *TransReq;
  BOOLEAN                              IsEmpty;
  //
  // RPPO-LKF-0007: OverrideBegin
  //
  UINT8                                *Cdb;
  //
  // RPPO-LKF-0007: OverrideEnd
  //

  TransReq       = AllocateZeroPool (sizeof (UFS_PASS_THRU_TRANS_REQ));
  if (TransReq == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  TransReq->Signature     = UFS_PASS_THRU_TRANS_REQ_SIG;
  TransReq->TimeoutRemain = Packet->Timeout;
  DataBufPhyAddr = 0;
  UfsHc          = Private->UfsHostController;

  if (Event != NULL) {
    //
    // For async requests, insert it to the Pending async I/O list and return
    //
    TransReq->Lun         = Lun;
    TransReq->Packet      = Packet;
    TransReq->CallerEvent = Event;

    OldTpl = gBS->RaiseTPL (TPL_NOTIFY);
    InsertTailList (&Private->PendingQueue, &TransReq->TransferList);
    gBS->RestoreTPL (OldTpl);
    return EFI_SUCCESS;
  } else {
    //
    // For sync requests, wait asynchronous queues to become empty.
    //
    while (TRUE) {
      OldTpl  = gBS->RaiseTPL (TPL_NOTIFY);
      IsEmpty = (IsListEmpty (&Private->PendingQueue)) && (IsListEmpty (&Private->Queue));
      gBS->RestoreTPL (OldTpl);

      if (IsEmpty) {
        break;
      }

      gBS->Stall (100);
    }
  }

  //
  // Find out which slot of transfer request list is available.
  //
  Status = UfsFindAvailableSlotInTrl (Private, &TransReq->Slot);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  TransReq->Trd = ((UTP_TRD*)Private->UtpTrlBase) + TransReq->Slot;

  //
  // Fill transfer request descriptor to this slot.
  //
  Status = UfsCreateScsiCommandDesc (
             Private,
             Lun,
             Packet,
             TransReq->Trd,
             &TransReq->CmdDescHost,
             &TransReq->CmdDescMapping
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  TransReq->CmdDescSize = TransReq->Trd->PrdtO * sizeof (UINT32) + TransReq->Trd->PrdtL * sizeof (UTP_TR_PRD);

  if (Packet->DataDirection == EFI_EXT_SCSI_DATA_DIRECTION_READ) {
    DataBuf       = Packet->InDataBuffer;
    DataLen       = Packet->InTransferLength;
    Flag          = EdkiiUfsHcOperationBusMasterWrite;
  } else {
    DataBuf       = Packet->OutDataBuffer;
    DataLen       = Packet->OutTransferLength;
    Flag          = EdkiiUfsHcOperationBusMasterRead;
  }

  if (DataLen != 0) {
    MapLength = DataLen;
    Status    = UfsHc->Map (
                         UfsHc,
                         Flag,
                         DataBuf,
                         &MapLength,
                         &DataBufPhyAddr,
                         &TransReq->DataBufMapping
                         );

    if (EFI_ERROR (Status) || (DataLen != MapLength)) {
      goto Exit1;
    }
  }
  //
  // Fill PRDT table of Command UPIU for executed SCSI cmd.
  //
  PrdtBase = (UTP_TR_PRD*)((UINT8*)TransReq->CmdDescHost + ROUNDUP8 (sizeof (UTP_COMMAND_UPIU)) + ROUNDUP8 (sizeof (UTP_RESPONSE_UPIU)));
  ASSERT (PrdtBase != NULL);

  //
  // RPPO-LKF-0007: OverrideBegin
  //
  Cdb = (UINT8*)Packet->Cdb;
  if (Cdb[0] == EFI_SCSI_OP_REQUEST_SENSE) {
    //
    // According to UFS Host Controller Spec(JESD223C), data buffers that are
    // associated with a UTP Transfer Request should be with Dword granularity.
    // But the size of UFS Request Sense Data Response defined in UFS Spec
    // (JESD220C) is 18 bytes, which is not Dword aligned in length.
    // Here, we round-up 'DataLen' to be Dword aligned for a Request Sense
    // command.
    //
    DEBUG ((DEBUG_WARN, "UfsExecScsiCmds: The DataLen [%d] is not dword-aligned, aligning buffer.\n", DataLen));
    DataLen = (DataLen + 3) & (~(BIT0 | BIT1));
  }
  //
  // RPPO-LKF-0007: OverrideEnd
  //
  UfsInitUtpPrdt (PrdtBase, (VOID*)(UINTN)DataBufPhyAddr, DataLen);

  //
  // Start to execute the transfer request.
  //
  UfsStartExecCmd (Private, TransReq->Slot);

  //
  // Wait for the completion of the transfer request.
  //
  Status = UfsWaitMemSet (Private, UFS_HC_UTRLDBR_OFFSET, BIT0 << TransReq->Slot, 0, Packet->Timeout);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsExecScsiCmds: UfsWaitMemSet BIT0 << TransReq->Slot:  ERROR!\n"));
    goto Exit;
  }
  //
  // RPPO-LKF-0009: OverrideBegin
  //
  Status = UfsClearUtrlcnr (Private, TransReq->Slot);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // RPPO-LKF-0009: OverrideEnd
  //
  //
  // Get sense data if exists
  //
  Response     = (UTP_RESPONSE_UPIU*)((UINT8*)TransReq->CmdDescHost + TransReq->Trd->RuO * sizeof (UINT32));
  ASSERT (Response != NULL);
  SenseDataLen = Response->SenseDataLen;
  SwapLittleEndianToBigEndian ((UINT8*)&SenseDataLen, sizeof (UINT16));

  if ((Packet->SenseDataLength != 0) && (Packet->SenseData != NULL)) {
    CopyMem (Packet->SenseData, Response->SenseData, SenseDataLen);
    Packet->SenseDataLength = (UINT8)SenseDataLen;
  }

  //
  // Check the transfer request result.
  //
  Packet->TargetStatus = Response->Status;
  if (Response->Response != 0) {
    DEBUG ((EFI_D_ERROR, "UfsExecScsiCmds() fails with Target Failure\n"));
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (TransReq->Trd->Ocs == 0) {
    if (Packet->DataDirection == EFI_EXT_SCSI_DATA_DIRECTION_READ) {
      if ((Response->Flags & BIT5) == BIT5) {
        ResTranCount = Response->ResTranCount;
        SwapLittleEndianToBigEndian ((UINT8*)&ResTranCount, sizeof (UINT32));
        Packet->InTransferLength -= ResTranCount;
      }
    } else {
      if ((Response->Flags & BIT5) == BIT5) {
        ResTranCount = Response->ResTranCount;
        SwapLittleEndianToBigEndian ((UINT8*)&ResTranCount, sizeof (UINT32));
        Packet->OutTransferLength -= ResTranCount;
      }
    }
  } else {
    Status = EFI_DEVICE_ERROR;
  }

Exit:
  UfsHc->Flush (UfsHc);

  UfsStopExecCmd (Private, TransReq->Slot);

  if (TransReq->DataBufMapping != NULL) {
    UfsHc->Unmap (UfsHc, TransReq->DataBufMapping);
  }

Exit1:
  if (TransReq->CmdDescMapping != NULL) {
    UfsHc->Unmap (UfsHc, TransReq->CmdDescMapping);
  }
  if (TransReq->CmdDescHost != NULL) {
    UfsHc->FreeBuffer (UfsHc, EFI_SIZE_TO_PAGES (TransReq->CmdDescSize), TransReq->CmdDescHost);
  }
  if (TransReq != NULL) {
    FreePool (TransReq);
  }
  return Status;
}


/**
  Send a UIC command to the host controller.

  @param[in] Private          The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in] UicOpcode        The opcode of the UIC command.
  @param[in] Arg1             The value for 1st argument of the UIC command.
  @param[in] Arg2             The value for 2nd argument of the UIC command.
  @param[in] Arg3             The value for 3rd argument of the UIC command.

  @return EFI_SUCCESS      Successfully execute this UIC command.
  @return EFI_DEVICE_ERROR Fail to execute this UIC command.

**/
EFI_STATUS
UfsExecUicCommands (
  IN  UFS_PASS_THRU_PRIVATE_DATA    *Private,
  IN  UINT8                         UicOpcode,
  IN  UINT32                        Arg1,
  IN  UINT32                        Arg2,
  IN  UINT32                        Arg3
  )
{
  EFI_STATUS  Status;
  UINT32      Data;

  Status = UfsMmioRead32 (Private, UFS_HC_IS_OFFSET, &Data);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsPassThruHci: UfsMmioRead32: UFS_HC_IS_OFFSET : ERROR!\n"));
    return Status;
  }

  if ((Data & UFS_HC_IS_UCCS) == UFS_HC_IS_UCCS) {
    //
    // Clear IS.BIT10 UIC Command Completion Status (UCCS) at first.
    //
    Status = UfsMmioWrite32 (Private, UFS_HC_IS_OFFSET, Data);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "UfsPassThruHci: UfsMmioWrite32: UFS_HC_IS_OFFSET : ERROR!\n"));
      return Status;
    }
  }

  //
  // When programming UIC command registers, host software shall set the register UICCMD
  // only after all the UIC command argument registers (UICCMDARG1, UICCMDARG2 and UICCMDARG3)
  // are set.
  //
  Status = UfsMmioWrite32 (Private, UFS_HC_UCMD_ARG1_OFFSET, Arg1);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsPassThruHci: UfsMmioWrite32: UFS_HC_UCMD_ARG1_OFFSET : ERROR!\n"));
    return Status;
  }

  Status = UfsMmioWrite32 (Private, UFS_HC_UCMD_ARG2_OFFSET, Arg2);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsPassThruHci: UfsMmioWrite32: UFS_HC_UCMD_ARG2_OFFSET : ERROR!\n"));
    return Status;
  }

  Status = UfsMmioWrite32 (Private, UFS_HC_UCMD_ARG3_OFFSET, Arg3);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsPassThruHci: UfsMmioWrite32: UFS_HC_UCMD_ARG3_OFFSET : ERROR!\n"));
    return Status;
  }

  //
  // Host software shall only set the UICCMD if HCS.UCRDY is set to 1.
  //
  Status = UfsWaitMemSet (Private, UFS_HC_STATUS_OFFSET, UFS_HC_HCS_UCRDY, UFS_HC_HCS_UCRDY, UFS_TIMEOUT);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsPassThruHci: UfsWaitMemSet UFS_HC_HCS_UCRDY:  ERROR!\n"));
    return Status;
  }

  Status = UfsMmioWrite32 (Private, UFS_HC_UIC_CMD_OFFSET, (UINT32)UicOpcode);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsPassThruHci: UfsMmioWrite32 UFS_HC_UIC_CMD_OFFSET:  ERROR!\n"));
    return Status;
  }

  //
  // UFS 2.0 spec section 5.3.1 Offset:0x20 IS.Bit10 UIC Command Completion Status (UCCS)
  // This bit is set to '1' by the host controller upon completion of a UIC command.
  //
  Status  = UfsWaitMemSet (Private, UFS_HC_IS_OFFSET, UFS_HC_IS_UCCS, UFS_HC_IS_UCCS, UFS_TIMEOUT);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsPassThruHci: UfsWaitMemSet UFS_HC_IS_UCCS:  ERROR!\n"));
    return Status;
  }

  if (UicOpcode != UfsUicDmeReset) {
    Status = UfsMmioRead32 (Private, UFS_HC_UCMD_ARG2_OFFSET, &Data);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "UfsPassThruHci: UicOpcode != UfsUicDmeReset UfsMmioRead32: UFS_HC_UCMD_ARG2_OFFSET: Error!\n"));
      return Status;
    }

    if ((Data & 0xFF) != 0) {
      //DEBUG_CODE_BEGIN();
        DumpUicCmdExecResult (UicOpcode, (UINT8)(Data & 0xFF));
      //DEBUG_CODE_END();
      return EFI_DEVICE_ERROR;
    }
  }

  return EFI_SUCCESS;
}

/**
  Allocate common buffer for host and UFS bus master access simultaneously.

  @param[in]  Private                The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @param[in]  Size                   The length of buffer to be allocated.
  @param[out] CmdDescHost            A pointer to store the base system memory address of the allocated range.
  @param[out] CmdDescPhyAddr         The resulting map address for the UFS bus master to use to access the hosts CmdDescHost.
  @param[out] CmdDescMapping         A resulting value to pass to Unmap().

  @retval EFI_SUCCESS                The common buffer was allocated successfully.
  @retval EFI_DEVICE_ERROR           The allocation fails.
  @retval EFI_OUT_OF_RESOURCES       The memory resource is insufficient.

**/
EFI_STATUS
UfsAllocateAlignCommonBuffer (
  IN     UFS_PASS_THRU_PRIVATE_DATA    *Private,
  IN     UINTN                         Size,
     OUT VOID                          **CmdDescHost,
     OUT EFI_PHYSICAL_ADDRESS          *CmdDescPhyAddr,
     OUT VOID                          **CmdDescMapping
  )
{
  EFI_STATUS                           Status;
  UINTN                                Bytes;
  BOOLEAN                              Is32BitAddr;
  EDKII_UFS_HOST_CONTROLLER_PROTOCOL   *UfsHc;

  if ((Private->Capabilities & UFS_HC_CAP_64ADDR) == UFS_HC_CAP_64ADDR) {
    Is32BitAddr = FALSE;
  } else {
    Is32BitAddr = TRUE;
  }

  UfsHc  = Private->UfsHostController;
  Status = UfsHc->AllocateBuffer (
                    UfsHc,
                    AllocateAnyPages,
                    EfiBootServicesData,
                    EFI_SIZE_TO_PAGES (Size),
                    CmdDescHost,
                    0
                    );
  if (EFI_ERROR (Status)) {
    *CmdDescMapping = NULL;
    *CmdDescHost    = NULL;
    *CmdDescPhyAddr = 0;
    return EFI_OUT_OF_RESOURCES;
  }

  Bytes  = EFI_PAGES_TO_SIZE (EFI_SIZE_TO_PAGES (Size));
  Status = UfsHc->Map (
                    UfsHc,
                    EdkiiUfsHcOperationBusMasterCommonBuffer,
                    *CmdDescHost,
                    &Bytes,
                    CmdDescPhyAddr,
                    CmdDescMapping
                    );

  if (EFI_ERROR (Status) || (Bytes != EFI_PAGES_TO_SIZE (EFI_SIZE_TO_PAGES (Size)))) {
    UfsHc->FreeBuffer (
             UfsHc,
             EFI_PAGES_TO_SIZE (EFI_SIZE_TO_PAGES (Size)),
             *CmdDescHost
             );
    *CmdDescHost = NULL;
    return EFI_OUT_OF_RESOURCES;
  }

  if (Is32BitAddr && ((*CmdDescPhyAddr) > 0x100000000ULL)) {
    //
    // The UFS host controller doesn't support 64bit addressing, so should not get a >4G UFS bus master address.
    //
    UfsHc->Unmap (
             UfsHc,
             *CmdDescMapping
             );
    UfsHc->FreeBuffer (
             UfsHc,
             EFI_PAGES_TO_SIZE (EFI_SIZE_TO_PAGES (Size)),
             *CmdDescHost
             );
    *CmdDescMapping = NULL;
    *CmdDescHost    = NULL;
    return EFI_DEVICE_ERROR;
  }

  ZeroMem (*CmdDescHost, EFI_PAGES_TO_SIZE (EFI_SIZE_TO_PAGES (Size)));
  return EFI_SUCCESS;
}

/**
  Enable the UFS host controller for accessing.

  @param[in] Private                 The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.

  @retval EFI_SUCCESS                The UFS host controller enabling was executed successfully.
  @retval EFI_DEVICE_ERROR           A device error occurred while enabling the UFS host controller.

**/
EFI_STATUS
UfsEnableHostController (
  IN  UFS_PASS_THRU_PRIVATE_DATA     *Private
  )
{
  EFI_STATUS             Status;
  UINT32                 Data;
  DEBUG ((DEBUG_INFO, "UfsEnableHostController:  Entry \n"));
  Status = UfsMmioRead32 (Private, UFS_HC_VER_OFFSET, &Data);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "UfsEnableHostController: UfsMmioRead32 failed for UFS_HC_VER_OFFSET read: Status =%r \n", Status));
    return Status;
  }
  Private->Version = Data & 0x0000FFFF;
  //
  // UFS 2.0 spec section 7.1.1 - Host Controller Initialization
  //
  // Get the current value of the HCE bit of HC register.
  //
  Status = UfsMmioRead32 (Private, UFS_HC_ENABLE_OFFSET, &Data);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if ((Data & UFS_HC_HCE_EN) == UFS_HC_HCE_EN) {
    //
    // RPPO-LKF-0007: OverrideBegin
    //
    //
    // If the UFS host controller has already been enabled by platform, there
    // is no need to re-enable it again. Return EFI_SUCCESS directly.
    //
    DEBUG ((DEBUG_INFO, "UfsEnableHostController:  UFS_HC_HCE_EN set already (silicon RC code or Platform) Exit \n"));
    Private->UfsHcEnabledByPlatform = TRUE;
    return EFI_SUCCESS;
    //
    // RPPO-LKF-0007: OverrideEnd
    //
  }

  //
  // Write a 1 to the HCE register to enable the UFS host controller.
  //
  Status = UfsMmioWrite32 (Private, UFS_HC_ENABLE_OFFSET, UFS_HC_HCE_EN);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Wait until HCE is read as '1' before continuing.
  //
  Status = UfsWaitMemSet (Private, UFS_HC_ENABLE_OFFSET, UFS_HC_HCE_EN, UFS_HC_HCE_EN, UFS_TIMEOUT);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UfsEnableHostController: UfsWaitMemSet UFS_HC_HCE_EN:  ERROR!\n"));
    return EFI_DEVICE_ERROR;
  }
  DEBUG ((DEBUG_INFO, "UfsEnableHostController:  Exit \n"));
  return EFI_SUCCESS;
}
/**
  Reset the UFS host controller.
  @param[in] Private                 The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.
  @retval EFI_SUCCESS                The UFS host controller was reset successfully.
  @retval EFI_DEVICE_ERROR           A device error occurred while resetting the UFS host controller.
**/
EFI_STATUS
UfsResetHostController (
  IN  UFS_PASS_THRU_PRIVATE_DATA     *Private
  )
{
  EFI_STATUS             Status;
  UINT32                 Data;
  //
  // UFS 2.0 spec section 7.1.1 - Host Controller Initialization
  //
  // Reinitialize the UFS host controller if HCE bit of HC register is set.
  //
  Status = UfsMmioRead32 (Private, UFS_HC_ENABLE_OFFSET, &Data);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  if ((Data & UFS_HC_HCE_EN) == UFS_HC_HCE_EN) {
    //
    // Write a 0 to the HCE register at first to disable the host controller.
    //
    Status = UfsMmioWrite32 (Private, UFS_HC_ENABLE_OFFSET, 0);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    //
    // Wait until HCE is read as '0' before continuing.
    //
    Status = UfsWaitMemSet (Private, UFS_HC_ENABLE_OFFSET, UFS_HC_HCE_EN, 0, UFS_TIMEOUT);
    if (EFI_ERROR (Status)) {
      return EFI_DEVICE_ERROR;
    }
  }
  //
  // Write a 1 to the HCE register to enable the UFS host controller.
  //
  Status = UfsMmioWrite32 (Private, UFS_HC_ENABLE_OFFSET, UFS_HC_HCE_EN);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // Wait until HCE is read as '1' before continuing.
  //
  Status = UfsWaitMemSet (Private, UFS_HC_ENABLE_OFFSET, UFS_HC_HCE_EN, UFS_HC_HCE_EN, UFS_TIMEOUT);
  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }
  return EFI_SUCCESS;
}
  //
  // RPPO-LKF-0009: OverrideBegin
  //
/**
  Print UFS HC capabilities.

  @param[in] Private                 The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.

  @retval EFI_SUCCESS                Printed UFS HC capabilities successfully.
  @retval EFI_TIMEOUT                The operation is time out.


**/
EFI_STATUS
UfsPrintHCCapabilities (
  IN  UFS_PASS_THRU_PRIVATE_DATA       *Private
  )
{
  EFI_STATUS             Status;
  UINT32                 Data;

  DEBUG ((DEBUG_INFO, "UfsPrintHCCapabilities: Entry \n"));

  DEBUG ((DEBUG_INFO, " UFS Version [%X] \n", Private->Version));

  Status = UfsMmioRead32 (Private, UFS_HC_CAP_OFFSET, &Data);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "UfsMmioRead32 failed for UFS_HC_CAP_OFFSET read: Status =%r \n",Status));
    return Status;
  }
  DEBUG ((DEBUG_INFO, " UFS_HC_CAP [%X] \n", Data));
  DEBUG ((DEBUG_INFO, " Crypto Support (CS) [%d] \n", (UINT8) (RShiftU64 ((Data & UFS_HC_CAP_CS), 28)) ));
  DEBUG ((DEBUG_INFO, " UICDMETMS [%d] \n", (UINT8) (RShiftU64 ((Data & UFS_HC_CAP_UICDMETMS), 26)) ));
  DEBUG ((DEBUG_INFO, " OODDS [%d] \n", (UINT8) (RShiftU64 ((Data & UFS_HC_CAP_OODDS), 25)) ));
  DEBUG ((DEBUG_INFO, " 64ADDR [%d] \n", (UINT8) (RShiftU64 ((Data & UFS_HC_CAP_64ADDR), 24)) ));
  DEBUG ((DEBUG_INFO, " AUTOH8 [%d] \n", (UINT8) (RShiftU64 ((Data & UFS_HC_CAP_AUTOH8), 23)) ));
  DEBUG ((DEBUG_INFO, " Nutmrs [%d] \n", (UINT8) (RShiftU64 ((Data & UFS_HC_CAP_NUTMRS), 16) + 1)));
  DEBUG ((DEBUG_INFO, " NORTT [%d] \n", (UINT8) (RShiftU64 ((Data & UFS_HC_CAP_NORTT), 8)) ));
  DEBUG ((DEBUG_INFO, " Nutrs  [%d] \n", (UINT8)((Data & UFS_HC_CAP_NUTRS) + 1)));

  DEBUG ((DEBUG_INFO, "UfsPrintHCCapabilities: Exit \n"));
  return EFI_SUCCESS;
}
  //
  // RPPO-LKF-0009: OverrideEnd
  //

/**
  Detect if a UFS device attached.

  @param[in] Private                 The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.

  @retval EFI_SUCCESS                The UFS device detection was executed successfully.
  @retval EFI_NOT_FOUND              Not found a UFS device attached.
  @retval EFI_DEVICE_ERROR           A device error occurred while detecting the UFS device.

**/
EFI_STATUS
UfsDeviceDetection (
  IN  UFS_PASS_THRU_PRIVATE_DATA     *Private
  )
{
  UINTN                  Retry;
  EFI_STATUS             Status;
  UINT32                 Data;
  DEBUG ((DEBUG_INFO, "UfsPassThruHci: UfsDeviceDetection: Entry \n"));

  //
  // RPPO-LKF-0020: OverrideBegin
  //
  if (BootMediaIsUfs ()) {
    Status = UfsMmioRead32 (Private, UFS_HC_STATUS_OFFSET, &Data);
    if (EFI_ERROR (Status)) {
      return EFI_DEVICE_ERROR;
    }

    if ((Data & UFS_HC_HCS_DP) == 1) {
      DEBUG ((EFI_D_INFO,"UFS HCS.DP already set, skip Link up.\n"));
      return EFI_SUCCESS;
    }
  }
  //
  // RPPO-LKF-0020: OverrideEnd
  //
  //
  // Start UFS device detection.
  // Try up to 4 times for establishing data link with device.
  //
  for (Retry = 0; Retry < 4; Retry++) {
    Status = UfsExecUicCommands (Private, UfsUicDmeLinkStartup, 0, 0, 0);
    if (!EFI_ERROR (Status)) {
      //
      // Check value of HCS.DP and make sure that there is a device attached to the Link.
      //
      Status = UfsMmioRead32 (Private, UFS_HC_STATUS_OFFSET, &Data);
      if (EFI_ERROR (Status)) {
        return EFI_DEVICE_ERROR;
      }

      if ((Data & UFS_HC_HCS_DP) == 0) {
        DEBUG ((DEBUG_INFO, "UfsDeviceDetection: Retry=%d UFS_HC_HCS_DP is not set \n", Retry));
        /* Wait for IS.ULSS is set to 1 since IS.ULSS equal 1 indicates that the UFS Device is ready for a link startup
           resend the DME_LINKSTARTUP command only after IS.ULSS has been set to 1. */
        Status = UfsWaitMemSet (Private, UFS_HC_IS_OFFSET, UFS_HC_IS_ULSS, UFS_HC_IS_ULSS, UFS_TIMEOUT);
        if (EFI_ERROR (Status)) {
          DEBUG ((DEBUG_INFO, "UfsDeviceDetection: Retry=%d UFS_HC_HCS_DP and UFS_HC_IS_ULSS are not set \n", Retry));
        }
      } else {
        DEBUG ((DEBUG_INFO, "UfsDeviceDetection: Found an attached UFS device\n"));
        break;
      }
    }
    if (Retry == 2) {
      /* Previous three Dme Link startup attempts failed and hence Reset the Host controller and retry Dme Link startup again.*/
      DEBUG ((DEBUG_INFO, "UfsDeviceDetection: Retry=%d resetting Host Controller \n", Retry));
      Status = UfsResetHostController (Private);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "UfsDeviceDetection: Host Controller Reset Failed, Retry = %d Status = %r\n", Retry, Status));
      }
      /* Every time we reset UFS HC we need to set this attribute */
      UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (PA_Local_TX_LCC_Enable, 0), 0, 0);
    }
  }

  if (Retry == 4) {
    DEBUG ((DEBUG_INFO, "UfsDeviceDetection: DmeLinkStartup failed UFS REGISTER DUMP -------------------\n" ));
    UfsDumpHcRegisters (Private, TRUE);
    DEBUG ((DEBUG_INFO, "UfsDeviceDetection: DmeLinkStartup failed UFS REGISTER DUMP EXIT-------------------\n" ));
    return EFI_NOT_FOUND;
  }
  return EFI_SUCCESS;
}

/**
  Initialize UFS task management request list related h/w context.

  @param[in] Private                 The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.

  @retval EFI_SUCCESS                The UFS task management list was initialzed successfully.
  @retval EFI_DEVICE_ERROR           The initialization fails.

**/
EFI_STATUS
UfsInitTaskManagementRequestList (
  IN  UFS_PASS_THRU_PRIVATE_DATA     *Private
  )
{
  UINT32                 Data;
  UINT8                  Nutmrs;
  VOID                   *CmdDescHost;
  EFI_PHYSICAL_ADDRESS   CmdDescPhyAddr;
  VOID                   *CmdDescMapping;
  EFI_STATUS             Status;

  //
  // Initial h/w and s/w context for future operations.
  //
  CmdDescHost    = NULL;
  CmdDescMapping = NULL;
  CmdDescPhyAddr = 0;

  Status = UfsMmioRead32 (Private, UFS_HC_CAP_OFFSET, &Data);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Private->Capabilities = Data;

  //
  // Allocate and initialize UTP Task Management Request List.
  //
  Nutmrs = (UINT8) (RShiftU64 ((Private->Capabilities & UFS_HC_CAP_NUTMRS), 16) + 1);
  Status = UfsAllocateAlignCommonBuffer (Private, Nutmrs * sizeof (UTP_TMRD), &CmdDescHost, &CmdDescPhyAddr, &CmdDescMapping);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Program the UTP Task Management Request List Base Address and UTP Task Management
  // Request List Base Address with a 64-bit address allocated at step 6.
  //
  Status = UfsMmioWrite32 (Private, UFS_HC_UTMRLBA_OFFSET, (UINT32)(UINTN)CmdDescPhyAddr);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = UfsMmioWrite32 (Private, UFS_HC_UTMRLBAU_OFFSET, (UINT32)RShiftU64 ((UINT64)CmdDescPhyAddr, 32));
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Private->UtpTmrlBase = CmdDescHost;
  Private->Nutmrs      = Nutmrs;
  Private->TmrlMapping = CmdDescMapping;

  //
  // Enable the UTP Task Management Request List by setting the UTP Task Management
  // Request List RunStop Register (UTMRLRSR) to '1'.
  //
  Status = UfsMmioWrite32 (Private, UFS_HC_UTMRLRSR_OFFSET, UFS_HC_UTMRLRSR);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}

/**
  Initialize UFS transfer request list related h/w context.

  @param[in] Private                 The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.

  @retval EFI_SUCCESS                The UFS transfer list was initialzed successfully.
  @retval EFI_DEVICE_ERROR           The initialization fails.

**/
EFI_STATUS
UfsInitTransferRequestList (
  IN  UFS_PASS_THRU_PRIVATE_DATA     *Private
  )
{
  UINT32                 Data;
  UINT8                  Nutrs;
  VOID                   *CmdDescHost;
  EFI_PHYSICAL_ADDRESS   CmdDescPhyAddr;
  VOID                   *CmdDescMapping;
  EFI_STATUS             Status;

  //
  // Initial h/w and s/w context for future operations.
  //
  CmdDescHost    = NULL;
  CmdDescMapping = NULL;
  CmdDescPhyAddr = 0;

  Status = UfsMmioRead32 (Private, UFS_HC_CAP_OFFSET, &Data);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Private->Capabilities = Data;

  //
  // Allocate and initialize UTP Transfer Request List.
  //
  Nutrs  = (UINT8)((Private->Capabilities & UFS_HC_CAP_NUTRS) + 1);
  Status = UfsAllocateAlignCommonBuffer (Private, Nutrs * sizeof (UTP_TRD), &CmdDescHost, &CmdDescPhyAddr, &CmdDescMapping);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Program the UTP Transfer Request List Base Address and UTP Transfer Request List
  // Base Address with a 64-bit address allocated at step 8.
  //
  Status = UfsMmioWrite32 (Private, UFS_HC_UTRLBA_OFFSET, (UINT32)(UINTN)CmdDescPhyAddr);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = UfsMmioWrite32 (Private, UFS_HC_UTRLBAU_OFFSET, (UINT32)RShiftU64 ((UINT64)CmdDescPhyAddr, 32));
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Private->UtpTrlBase = CmdDescHost;
  Private->Nutrs      = Nutrs;
  Private->TrlMapping = CmdDescMapping;

  //
  // Enable the UTP Transfer Request List by setting the UTP Transfer Request List
  // RunStop Register (UTRLRSR) to '1'.
  //
  Status = UfsMmioWrite32 (Private, UFS_HC_UTRLRSR_OFFSET, UFS_HC_UTRLRSR);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}
//
// RPPO-LKF-0010: RoyalParkOverrideBegin
//
/**
  Dump error information of Host controller Layers.

  @param[in] Private                 The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.

**/
VOID
UfsDumpHciStatus (
  IN UFS_PASS_THRU_PRIVATE_DATA  *Private
  )
{
  UINT32  Data32;
  DEBUG ((EFI_D_INFO, "UfsDumpHciStatus Entry \n"));
  UfsMmioRead32 (Private, UFS_HC_UECPA_OFFSET, &Data32);
  DEBUG ((EFI_D_INFO, "PHY Layer error status = %X\n", Data32));
  if (Data32 & BIT31) {
    DEBUG ((EFI_D_INFO, "PHY Layer error status = %X\n", Data32 & 0x1F));
  }
  UfsMmioRead32 (Private, UFS_HC_UECDL_OFFSET, &Data32);
  DEBUG ((EFI_D_INFO, "Data Link Layer error status = %X\n", Data32));
  if (Data32 & BIT31) {
    DEBUG ((EFI_D_INFO, "Data Link Layer error status = %X\n", Data32 & 0x7FFF));
  }
  UfsMmioRead32 (Private, UFS_HC_UECN_OFFSET, &Data32);
  DEBUG ((EFI_D_INFO, "Network Layer error status = %X\n", Data32));
  if (Data32 & BIT31) {
    DEBUG ((EFI_D_INFO, "Network Layer error status = %X\n", Data32 & 0x7));
  }
  UfsMmioRead32 (Private, UFS_HC_UECT_OFFSET, &Data32);
  DEBUG ((EFI_D_INFO, "Transport Layer error status = %X\n", Data32));
  if (Data32 & BIT31) {
    DEBUG ((EFI_D_INFO, "Transport Layer error status = %X\n", Data32 & 0x7F));
  }
  UfsMmioRead32 (Private, UFS_HC_UECDME_OFFSET, &Data32);
  DEBUG ((EFI_D_INFO, "DME error status = %X\n", Data32));
  if (Data32 & BIT31) {
    DEBUG ((EFI_D_INFO, "DME error status = %X\n", Data32 & 0x1));
  }
  DEBUG ((EFI_D_INFO, "UfsDumpHciStatus Exit \n"));
}
/**
  Programs SNPS Phy Layer.

  @param[in] Private                 The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.

  @retval EFI_SUCCESS                Successfully programmed phy layer.
  @retval Others                     A device error occurred while programming phy layer.

**/
EFI_STATUS
UfsProgramSnpsPhy (
  IN UFS_PASS_THRU_PRIVATE_DATA  *Private
  )
{
  EFI_STATUS  Status;
  UINT32 Index;
  UINT32 TableSize = sizeof(SnpsPhyData)/sizeof(PHY_DME_DATA);
  DEBUG ((EFI_D_INFO, "UfsProgramSnpsPhy: Entry TableSize = %X\n", TableSize));
  for ( Index = 0; Index < TableSize; Index++) {
    DEBUG ((EFI_D_INFO, "UfsProgramSnpsPhy: Sending UfsUicDmeSet SnpsPhyData[%d].Arg1 = %X Arg2 =%X Arg3 =%X\n", Index, SnpsPhyData[Index].Arg1.Data32, SnpsPhyData[Index].Arg2.Data32, SnpsPhyData[Index].MIBvalue));
    Status = UfsExecUicCommands (Private, UfsUicDmeSet, SnpsPhyData[Index].Arg1.Data32, SnpsPhyData[Index].Arg2.Data32, SnpsPhyData[Index].MIBvalue);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_INFO, "UfsProgramSnpsPhy: UfsUicDmeSet failed: Status = %X SnpsPhyData[%d].Arg1 = %X Arg2 =%X Arg3 =%X\n", Status, Index, SnpsPhyData[Index].Arg1.Data32, SnpsPhyData[Index].Arg2.Data32, SnpsPhyData[Index].MIBvalue));
    UfsDumpHciStatus (Private);
      break;
    }
  }
  DEBUG ((EFI_D_INFO, "UfsProgramSnpsPhy: Exit Status = %X : Index = %d \n", Status, Index));
  return Status;
}
//
// RPPO-LKF-0010: RoyalParkOverrideEnd
//

/**
  Detects the connected Ufs Lanes and Programs the Active Lanes Attribute.

  @param[in] Private   The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure

  @retval EFI_SUCCESS  Successfully Programmed the lanes
  @retval others       Failed to program the lanes
**/
EFI_STATUS
UfsProgramLanes (
  IN     UFS_PASS_THRU_PRIVATE_DATA  *Private
  )
{
  EFI_STATUS  Status;
  UINT32      ConnectedLanes[] = {0, 0};
  UINT32      ActiveLanes[] = {0, 0};

  //Step 1: Query connected RX lanes and set Active RX Lanes.
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_ConnectedRxDataLanes,0), 0, 0, &ConnectedLanes[UfsRxLane]);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_ConnectedRxDataLanes(%x) \n", PA_ConnectedRxDataLanes));
    return Status;
  }

  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_ActiveRxDataLanes, 0), 0, 0, &ActiveLanes[UfsRxLane]);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_ActiveRxDataLanes(%x) \n", PA_ActiveRxDataLanes));
    return Status;
  }

  if (ActiveLanes[UfsRxLane] < ConnectedLanes[UfsRxLane]) {
    DEBUG ((DEBUG_INFO, "UfsProgramLanes : PA_ActiveRxDataLanes = %x  PA_ConnectedRxDataLanes = %x\n", ActiveLanes[UfsRxLane], ConnectedLanes[UfsRxLane]));
    Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (PA_ActiveRxDataLanes,0), 0, ConnectedLanes[UfsRxLane]);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to set active Rx data lanes\n"));
      return Status;
    }
  }

  //Step 2: Query connected TX lanes and set Active TX Lanes.
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_ConnectedTxDataLanes, 0), 0, 0, &ConnectedLanes[UfsTxLane]);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_ConnectedTxDataLanes(%x)\n", PA_ConnectedTxDataLanes));
    return Status;
  }

  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_ActiveTxDataLanes, 0), 0, 0, &ActiveLanes[UfsTxLane]);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_ActiveTxDataLanes(%x) \n", PA_ActiveTxDataLanes));
    return Status;
  }

  if (ActiveLanes[UfsTxLane] < ConnectedLanes[UfsTxLane]) {
    DEBUG ((DEBUG_INFO, "UfsProgramLanes : PA_ActiveTxDataLanes = %x  PA_ConnectedTxDataLanes = %x\n", ActiveLanes[UfsTxLane], ConnectedLanes[UfsTxLane]));
    Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (PA_ActiveTxDataLanes, 0), 0, ConnectedLanes[UfsTxLane]);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to set active Tx data lanes\n"));
      return Status;
    }
  }

  return Status;
}

/**
  Switches the link to PWM Gear.
  @param[in] Private The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure
  @retval EFI_SUCCESS  Successfully switched to PWM Gear
  @retval others       Failed to switch to PWM Gear
**/
EFI_STATUS
UfsPwmGearSwitch (
  IN UFS_PASS_THRU_PRIVATE_DATA  *Private
  )
{
  EFI_STATUS  Status;
  UINT32      MaxPwmGear[] = {PWM_G1, PWM_G1};

  Status = UfsProgramLanes (Private);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "UfsPwmGearSwitch: Failed to Program UFS Lanes \n"));
    return Status;
  }

  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_MaxRxPWMGear, 0), 0, 0, &MaxPwmGear[UfsRxLane]);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "UfsPwmGearSwitch: Failed to Get UfsUicDmeGet PA_MaxRxPWMGear(%x) \n", PA_MaxRxPWMGear));
    return Status;
  }
  Status = UfsExecGetUicCommands (Private, UfsUicDmePeerGet, UFS_UIC_ARG_MIB_SEL (PA_MaxRxPWMGear, 0), 0, 0, &MaxPwmGear[UfsTxLane]);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "UfsPwmGearSwitch: Failed to Get UfsUicDmePeerGet PA_MaxRxPWMGear(%x) \n", PA_MaxRxPWMGear));
    return Status;
  }

  Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (PA_RXGear, 0), 0, MaxPwmGear[UfsRxLane]);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "UfsPwmGearSwitch: Failed to set UfsUicDmeSet PA_RXGear \n"));
    return Status;
  }
  Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (PA_TXGear, 0), 0, MaxPwmGear[UfsTxLane]);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "UfsPwmGearSwitch: Failed to set UfsUicDmeSet PA_TXGear \n"));
    return Status;
  }

  //
  // Change Power Mode of both directions
  //
  Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (PA_PWRMode, 0), 0, (((SlowAuto_Mode & 0xF) << 4) | (SlowAuto_Mode & 0xF)));
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "UfsPwmGearSwitch: Failed to set PA_PWRMode(%x) \n", PA_PWRMode));
    return Status;
  }
  Status = UfsWaitMemSet (Private, UFS_HC_IS_OFFSET, UFS_HC_IS_UPMS, UFS_HC_IS_UPMS, UFS_TIMEOUT);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "UfsPwmGearSwitch: Failed to switch power mode\n"));
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  Switches the link Power Mode and Gear.

  @param[in] Private The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure

  @retval EFI_SUCCESS  Successfully switched the Power Mode and Gear
  @retval others       Failed to switch the Power Mode and Gear
**/
EFI_STATUS
UfsPowerModeAndGearSwitch (
  IN UFS_PASS_THRU_PRIVATE_DATA  *Private
  )
{
  EFI_STATUS  Status;
  UINT32      PowerMode[] = {Fast_Mode, Fast_Mode};
  UINT32      MaxHsGear[] = {HS_G1, HS_G1};
  UINT32      CurrentHsGear[] = {NO_HS, NO_HS};
  UINT32      MaxPwmGear[] = {PWM_G1, PWM_G1};

  DEBUG ((DEBUG_INFO, "UfsPowerModeAndGearSwitch Entry: \n" ));
  //
  //Step 1: Program Lanes
  //
  Status = UfsProgramLanes (Private);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Program UFS Lanes \n"));
    return Status;
  }
  //
  //Step 2: Query Max HS Gear and Max PWM Gears and if no HS gear, set PowerMode to SlowAuto
  //
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_MaxRxPWMGear, 0), 0, 0, &MaxPwmGear[UfsRxLane]);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_MaxRxPWMGear(%x)\n", PA_MaxRxPWMGear));
    return Status;
  }
  Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_MaxRxHSGear, 0), 0, 0, &MaxHsGear[UfsRxLane]);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmeGet PA_MaxRxHSGear(%x) \n", PA_MaxRxHSGear));
    return Status;
  }
  Status = UfsExecGetUicCommands (Private, UfsUicDmePeerGet, UFS_UIC_ARG_MIB_SEL (PA_MaxRxPWMGear, 0), 0, 0, &MaxPwmGear[UfsTxLane]);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmePeerGet PA_MaxRxPWMGear(%x) \n",PA_MaxRxPWMGear));
    return Status;
  }
  Status = UfsExecGetUicCommands (Private, UfsUicDmePeerGet, UFS_UIC_ARG_MIB_SEL (PA_MaxRxHSGear, 0), 0, 0, &MaxHsGear[UfsTxLane]);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Get UfsUicDmePeerGet PA_MaxRxHSGear(%x) \n", PA_MaxRxHSGear));
    return Status;
  }
  //
  //Step 3: Mark the Power Mode as SlowAuto_Mode or Set FC0, TC0 and AFC0 Timeouts based on MaxHsGear
  //
  if ((NO_HS == MaxHsGear[UfsRxLane]) || (NO_HS == MaxHsGear[UfsTxLane])) {
    PowerMode[UfsRxLane] = SlowAuto_Mode;
    PowerMode[UfsTxLane] = SlowAuto_Mode;
  } else {
    Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (DL_FC0ProtectionTimeOutVal, 0), 0, 0x1FFF);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to set active FC0 protection time out value\n"));
      return Status;
    }
    Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (DL_TC0ReplayTimeOutVal, 0), 0, 0xFFFF);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to set active TC0 replay time out value\n"));
      return Status;
    }
    Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (DL_AFC0ReqTimeOutVal,0), 0, 0x7FFF);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to set active AFC0 req time out value\n"));
      return Status;
    }
    Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (PA_HSSeries, 0), 0, UFS_PA_HS_MODE_B);
    if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to enable rate B\n"));
    return Status;
    }
  }

  DEBUG ((DEBUG_INFO, "PowerMode[UfsRxLane] = %x \n", PowerMode[UfsRxLane]));
  DEBUG ((DEBUG_INFO, "PowerMode[UfsTxLane] = %x \n", PowerMode[UfsTxLane]));
  DEBUG ((DEBUG_INFO, "MaxHsGear[UfsRxLane] = %x \n", MaxHsGear[UfsRxLane]));
  DEBUG ((DEBUG_INFO, "MaxHsGear[UfsTxLane] = %x \n", MaxHsGear[UfsTxLane]));
  DEBUG ((DEBUG_INFO, "MaxPwmGear[UfsRxLane] = %x \n", MaxPwmGear[UfsRxLane]));
  DEBUG ((DEBUG_INFO, "MaxPwmGear[UfsTxLane] = %x \n", MaxPwmGear[UfsTxLane]));

  //
  //Step 4: Set Rx gear, Rx Termination
  //
  if (PowerMode[UfsRxLane] == SlowAuto_Mode) {
    Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (PA_RXGear, 0), 0, MaxPwmGear[UfsRxLane]);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to set UfsUicDmeSet PA_RXGear \n"));
      return Status;
    }
  } else {
    if (MaxHsGear[UfsRxLane] > HS_G3) {
      MaxHsGear[UfsRxLane] = HS_G3;
      DEBUG ((DEBUG_INFO, "Limited MaxHsGear to %x \n", MaxHsGear[UfsRxLane]));
    }
    Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_RXGear, 0), 0, 0, &CurrentHsGear[UfsRxLane]);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to set UfsUicDmeSet PA_RXGear \n"));
      return Status;
    }
    if (CurrentHsGear[UfsRxLane] < MaxHsGear[UfsRxLane]) {
      DEBUG ((DEBUG_INFO, "CurrentHsGear[UfsRxLane] = %x switching to MaxHsGear[UfsRxLane]=%x \n", CurrentHsGear[UfsRxLane], MaxHsGear[UfsRxLane]));
      Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (PA_RXGear, 0), 0, MaxHsGear[UfsRxLane]);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "Failed to set UfsUicDmeSet PA_RXGear \n"));
        return Status;
      }
    }
    Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (PA_RxTermination, 0), 0, 0x1);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to enable Tx termination\n"));
      return Status;
    }
  }
  //
  //Step 5: Set Tx gear, TX Termination
  //
  if (PowerMode[UfsTxLane] == SlowAuto_Mode) {
    Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (PA_TXGear, 0), 0, MaxPwmGear[UfsTxLane]);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to set UfsUicDmeSet PA_TXGear \n"));
      return Status;
    }
  } else {
    if (MaxHsGear[UfsTxLane] > HS_G3) {
      MaxHsGear[UfsTxLane] = HS_G3;
      DEBUG ((DEBUG_INFO, "Limited MaxHsGear to %x \n", MaxHsGear[UfsTxLane]));
    }
    Status = UfsExecGetUicCommands (Private, UfsUicDmeGet, UFS_UIC_ARG_MIB_SEL (PA_TXGear, 0), 0, 0, &CurrentHsGear[UfsTxLane]);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to set UfsUicDmeSet PA_TXGear \n"));
      return Status;
    }
    if (CurrentHsGear[UfsTxLane] < MaxHsGear[UfsRxLane]) {
      DEBUG ((DEBUG_INFO, "CurrentHsGear[UfsTxLane] = %x switching to MaxHsGear[UfsTxLane]=%x \n", CurrentHsGear[UfsTxLane], MaxHsGear[UfsTxLane]));
      Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (PA_TXGear, 0), 0, MaxHsGear[UfsTxLane]);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "Failed to set UfsUicDmeSet PA_TXGear \n"));
        return Status;
      }
    }
    Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (PA_TxTermination, 0), 0, 0x1);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to enable Tx termination\n"));
      return Status;
    }
  }

  //
  // Step 6 Change Power Mode of both directions
  //
  Status = UfsExecUicCommands (Private, UfsUicDmeSet, UFS_UIC_ARG_MIB_SEL (PA_PWRMode, 0), 0, (((PowerMode[UfsRxLane] & 0xF) << 4) | (PowerMode[UfsTxLane] & 0xF)));
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to set PA_PWRMode(%x) \n", PA_PWRMode));
    return Status;
  }

  Status = UfsWaitMemSet (Private, UFS_HC_IS_OFFSET, UFS_HC_IS_UPMS, UFS_HC_IS_UPMS, UFS_TIMEOUT);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to switch power mode\n"));
    return EFI_DEVICE_ERROR;
  }

  DEBUG ((DEBUG_INFO, "Dump LinkConfig After UfsPowerModeAndGearSwitch\n"));
  Status = UfsDumpLinkConfig (Private);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to Dump LinkConfig\n"));
  }

  DEBUG ((DEBUG_INFO, "UfsPowerModeAndGearSwitch Exit\n" ));
  return EFI_SUCCESS;
}

/**
  Initialize the UFS host controller.

  @param[in] Private                 The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.

  @retval EFI_SUCCESS                The Ufs Host Controller is initialized successfully.
  @retval Others                     A device error occurred while initializing the controller.

**/
EFI_STATUS
UfsControllerInit (
  IN  UFS_PASS_THRU_PRIVATE_DATA     *Private
  )
{
  EFI_STATUS             Status;

  Status = UfsEnableHostController (Private);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "UfsControllerInit: Enable Host Controller Fails, Status = %r\n", Status));
    return Status;
  }
  //
  // RPPO-LKF-0009: OverrideBegin
  //
  Status = UfsPrintHCCapabilities (Private);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "UfsControllerInit: UfsPrintHCCapabilities Fails, Status = %r\n", Status));
  return Status;
  }
  //
  // RPPO-LKF-0009: OverrideEnd
  //

  //
  // RPPO-LKF-0010: RoyalParkOverrideBegin
  //
 //PcdBfxHfpgaWorkAroundEnable is for having the HFPGA specific code changes
 //for both Boot from Ufs boot as well as SPI boot
 if (PcdGetBool(PcdBfxHfpgaWorkAroundEnable) == TRUE) {
  DEBUG ((DEBUG_INFO, "UfsControllerInit: calling BootMediaIsUfs !\n"));
  if (!BootMediaIsUfs ()) {
    DEBUG ((DEBUG_INFO, "UfsControllerInit: non UFS boot: calling UfsProgramSnpsPhy !\n"));
    Status = UfsProgramSnpsPhy (Private);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "UfsControllerInit: UfsProgramSnpsPhy Fails, Status = %r\n", Status));
      return Status;
    }
  } else {
    DEBUG ((DEBUG_INFO, "UfsControllerInit: UfsProgramSnpsPhy Phy configured already by CSE as part of UFS boot!\n"));
  }
 }
  //
  // RPPO-LKF-0010: RoyalParkOverrideEnd
  //

  Status = UfsDeviceDetection (Private);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "UfsControllerInit: Device Detection Fails, Status = %r\n", Status));
    //
    // RPPO-LKF-0010: OverrideBegin
    //
    UfsDumpHciStatus (Private);
    //
    // RPPO-LKF-0010: OverrideEnd
    //
    return Status;
  }
  //
  // RPPO-LKF-0038: OverrideBegin
  //
  if (!BootMediaIsUfs ()) {
    Status = UfsPwmGearSwitch (Private);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to switch to PWM gear\n"));
      return Status;
    }
  }
  //
  // RPPO-LKF-0038: OverrideEnd
  //
  Status = UfsInitTaskManagementRequestList (Private);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "UfsControllerInit: Task management list initialization Fails, Status = %r\n", Status));
    return Status;
  }

  Status = UfsInitTransferRequestList (Private);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "UfsControllerInit: Transfer list initialization Fails, Status = %r\n", Status));
    return Status;
  }

  DEBUG ((EFI_D_INFO, "UfsControllerInit Finished\n"));
  return EFI_SUCCESS;
}

/**
  Stop the UFS host controller.

  @param[in] Private                 The pointer to the UFS_PASS_THRU_PRIVATE_DATA data structure.

  @retval EFI_SUCCESS                The Ufs Host Controller is stopped successfully.
  @retval Others                     A device error occurred while stopping the controller.

**/
EFI_STATUS
UfsControllerStop (
  IN  UFS_PASS_THRU_PRIVATE_DATA     *Private
  )
{
  EFI_STATUS             Status;
  UINT32                 Data;

  //
  // Enable the UTP Task Management Request List by setting the UTP Task Management
  // Request List RunStop Register (UTMRLRSR) to '1'.
  //
  Status = UfsMmioWrite32 (Private, UFS_HC_UTMRLRSR_OFFSET, 0);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Enable the UTP Transfer Request List by setting the UTP Transfer Request List
  // RunStop Register (UTRLRSR) to '1'.
  //
  Status = UfsMmioWrite32 (Private, UFS_HC_UTRLRSR_OFFSET, 0);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // RPPO-LKF-0007: OverrideBegin
  //
  //
  // If the UFS host controller is enabled by platform, some optional UIC
  // command might be sent to configure the host controller during
  // initialization (UFS Host Controller Spec JESD223C, Section 7.1.1). In this
  // case, the host controller will not be disabled so that the configuration
  // done by platform can be preserved.
  //
  if (!Private->UfsHcEnabledByPlatform) {
    //
    // Write a 0 to the HCE register in order to disable the host controller.
    //
    Status = UfsMmioRead32 (Private, UFS_HC_ENABLE_OFFSET, &Data);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    ASSERT ((Data & UFS_HC_HCE_EN) == UFS_HC_HCE_EN);

    Status = UfsMmioWrite32 (Private, UFS_HC_ENABLE_OFFSET, 0);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    //
    // Wait until HCE is read as '0' before continuing.
    //
    Status = UfsWaitMemSet (Private, UFS_HC_ENABLE_OFFSET, UFS_HC_HCE_EN, 0, UFS_TIMEOUT);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "UfsControllerStop: UfsWaitMemSet UFS_HC_HCE_EN:  ERROR!\n"));
      return EFI_DEVICE_ERROR;
    }

    DEBUG ((DEBUG_INFO, "UfsController is stopped\n"));
  }
  //
  // RPPO-LKF-0007: OverrideEnd
  //

  return EFI_SUCCESS;
}


/**
  Internal helper function which will signal the caller event and clean up
  resources.

  @param[in] Private   The pointer to the UFS_PASS_THRU_PRIVATE_DATA data
                       structure.
  @param[in] TransReq  The pointer to the UFS_PASS_THRU_TRANS_REQ data
                       structure.

**/
VOID
EFIAPI
SignalCallerEvent (
  IN UFS_PASS_THRU_PRIVATE_DATA      *Private,
  IN UFS_PASS_THRU_TRANS_REQ         *TransReq
  )
{
  EDKII_UFS_HOST_CONTROLLER_PROTOCOL *UfsHc;
  EFI_EVENT                          CallerEvent;

  ASSERT ((Private != NULL) && (TransReq != NULL));

  UfsHc        = Private->UfsHostController;
  CallerEvent  = TransReq->CallerEvent;

  RemoveEntryList (&TransReq->TransferList);

  UfsHc->Flush (UfsHc);

  UfsStopExecCmd (Private, TransReq->Slot);

  if (TransReq->DataBufMapping != NULL) {
    UfsHc->Unmap (UfsHc, TransReq->DataBufMapping);
  }

  if (TransReq->CmdDescMapping != NULL) {
    UfsHc->Unmap (UfsHc, TransReq->CmdDescMapping);
  }
  if (TransReq->CmdDescHost != NULL) {
    UfsHc->FreeBuffer (
             UfsHc,
             EFI_SIZE_TO_PAGES (TransReq->CmdDescSize),
             TransReq->CmdDescHost
             );
  }

  FreePool (TransReq);

  gBS->SignalEvent (CallerEvent);
  return;
}

/**
  Internal helper function which will check for any pending Async requests in the Queue and dispatch
  accordingly.

  @param[in] Private   The pointer to the UFS_PASS_THRU_PRIVATE_DATA data
                       structure.

**/
VOID
DispatchNextPendingRequest (
  IN UFS_PASS_THRU_PRIVATE_DATA    *Private
  )
{
  LIST_ENTRY                                    *Entry;
  UFS_PASS_THRU_TRANS_REQ                       *TransReq;
  EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET    *Packet;
  EDKII_UFS_HOST_CONTROLLER_PROTOCOL            *UfsHc;
  EDKII_UFS_HOST_CONTROLLER_OPERATION           Flag;
  VOID                                          *DataBuf;
  EFI_PHYSICAL_ADDRESS                          DataBufPhyAddr;
  UINT32                                        DataLen;
  UINTN                                         MapLength;
  UTP_TR_PRD                                    *PrdtBase;
  EFI_EVENT                                     CallerEvent;
  EFI_STATUS                                    Status;

  if (IsListEmpty(&Private->PendingQueue)) {
    return;
  }

  Entry    = GetFirstNode (&Private->PendingQueue);
  TransReq = UFS_PASS_THRU_TRANS_REQ_FROM_THIS (Entry);
  Packet   = TransReq->Packet;
  UfsHc    = Private->UfsHostController;

  //
  // Find out which slot of transfer request list is available.
  //
  Status = UfsFindAvailableSlotInTrl (Private, &TransReq->Slot);
  if (EFI_ERROR (Status)) {
    return;
  }

  //
  // After there is available slot, remove the request from the pending list,
  // the function is being called at NOTIFY TPL, so no need to raise TPL here.
  //
  RemoveEntryList (&TransReq->TransferList);

  TransReq->Trd = ((UTP_TRD*)Private->UtpTrlBase) + TransReq->Slot;

  //
  // Fill transfer request descriptor to this slot.
  //
  Status = UfsCreateScsiCommandDesc (
             Private,
             TransReq->Lun,
             Packet,
             TransReq->Trd,
             &TransReq->CmdDescHost,
             &TransReq->CmdDescMapping
             );
  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  TransReq->CmdDescSize = TransReq->Trd->PrdtO * sizeof (UINT32) + TransReq->Trd->PrdtL * sizeof (UTP_TR_PRD);

  if (Packet->DataDirection == EFI_EXT_SCSI_DATA_DIRECTION_READ) {
    DataBuf       = Packet->InDataBuffer;
    DataLen       = Packet->InTransferLength;
    Flag          = EdkiiUfsHcOperationBusMasterWrite;
  } else {
    DataBuf       = Packet->OutDataBuffer;
    DataLen       = Packet->OutTransferLength;
    Flag          = EdkiiUfsHcOperationBusMasterRead;
  }

  if (DataLen != 0) {
    MapLength = DataLen;
    Status    = UfsHc->Map (
                         UfsHc,
                         Flag,
                         DataBuf,
                         &MapLength,
                         &DataBufPhyAddr,
                         &TransReq->DataBufMapping
                         );

    if (EFI_ERROR (Status) || (DataLen != MapLength)) {
      goto ErrorExit;
    }
  }
  //
  // Fill PRDT table of Command UPIU for executed SCSI cmd.
  //
  PrdtBase = (UTP_TR_PRD*)((UINT8*)TransReq->CmdDescHost + ROUNDUP8 (sizeof (UTP_COMMAND_UPIU)) + ROUNDUP8 (sizeof (UTP_RESPONSE_UPIU)));
  ASSERT (PrdtBase != NULL);
  UfsInitUtpPrdt (PrdtBase, (VOID*)(UINTN)DataBufPhyAddr, DataLen);

  //
  // Add the request to the executing list, no need to raise TPL here.
  //
  InsertTailList (&Private->Queue, &TransReq->TransferList);

  //
  // Start to execute the transfer request.
  //
  UfsStartExecCmd (Private, TransReq->Slot);
  return;

ErrorExit:
  CallerEvent = TransReq->CallerEvent;
  //
  // Free resources if fail
  //
  if (TransReq->DataBufMapping != NULL) {
    UfsHc->Unmap (UfsHc, TransReq->DataBufMapping);
  }

  if (TransReq->CmdDescMapping != NULL) {
    UfsHc->Unmap (UfsHc, TransReq->CmdDescMapping);
  }
  if (TransReq->CmdDescHost != NULL) {
    UfsHc->FreeBuffer (UfsHc, EFI_SIZE_TO_PAGES (TransReq->CmdDescSize), TransReq->CmdDescHost);
  }
  if (TransReq != NULL) {
    FreePool (TransReq);
  }
  //
  // Signal caller event
  //
  Packet->HostAdapterStatus = EFI_EXT_SCSI_STATUS_HOST_ADAPTER_PHASE_ERROR;
  gBS->SignalEvent (CallerEvent);
  return;
}

/**
  Call back function when the timer event is signaled.

  @param[in]  Event     The Event this notify function registered to.
  @param[in]  Context   Pointer to the context data registered to the Event.

**/
VOID
EFIAPI
ProcessAsyncTaskList (
  IN EFI_EVENT          Event,
  IN VOID               *Context
  )
{
  UFS_PASS_THRU_PRIVATE_DATA                    *Private;
  LIST_ENTRY                                    *Entry;
  LIST_ENTRY                                    *NextEntry;
  UFS_PASS_THRU_TRANS_REQ                       *TransReq;
  EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET    *Packet;
  UTP_RESPONSE_UPIU                             *Response;
  UINT16                                        SenseDataLen;
  UINT32                                        ResTranCount;
  UINT32                                        SlotsMap;
  UINT32                                        Value;
  EFI_STATUS                                    Status;

  Private   = (UFS_PASS_THRU_PRIVATE_DATA*) Context;
  SlotsMap  = 0;

  //
  // Check the entries in the async I/O queue are done or not.
  //
  if (!IsListEmpty(&Private->Queue)) {
    EFI_LIST_FOR_EACH_SAFE (Entry, NextEntry, &Private->Queue) {
      TransReq  = UFS_PASS_THRU_TRANS_REQ_FROM_THIS (Entry);
      Packet    = TransReq->Packet;

      if ((SlotsMap & (BIT0 << TransReq->Slot)) != 0) {
        return;
      }
      SlotsMap |= BIT0 << TransReq->Slot;

      Status = UfsMmioRead32 (Private, UFS_HC_UTRLDBR_OFFSET, &Value);
      if (EFI_ERROR (Status)) {
        //
        // TODO: Should find/add a proper host adapter return status for this
        // case.
        //
        Packet->HostAdapterStatus = EFI_EXT_SCSI_STATUS_HOST_ADAPTER_PHASE_ERROR;
        DEBUG ((DEBUG_VERBOSE, "ProcessAsyncTaskList(): Signal Event %p UfsMmioRead32() Error.\n", TransReq->CallerEvent));
        SignalCallerEvent (Private, TransReq);
        continue;
      }

      if ((Value & (BIT0 << TransReq->Slot)) != 0) {
        //
        // Scsi cmd not finished yet.
        //
        if (TransReq->TimeoutRemain > UFS_HC_ASYNC_TIMER) {
          TransReq->TimeoutRemain -= UFS_HC_ASYNC_TIMER;
          continue;
        } else {
          //
          // Timeout occurs.
          //
          Packet->HostAdapterStatus = EFI_EXT_SCSI_STATUS_HOST_ADAPTER_TIMEOUT_COMMAND;
          DEBUG ((DEBUG_VERBOSE, "ProcessAsyncTaskList(): Signal Event %p EFI_TIMEOUT.\n", TransReq->CallerEvent));
          SignalCallerEvent (Private, TransReq);
          continue;
        }
      } else {
        //
        // Scsi cmd finished.
        //
        // Get sense data if exists
        //
        Response = (UTP_RESPONSE_UPIU*)((UINT8*)TransReq->CmdDescHost + TransReq->Trd->RuO * sizeof (UINT32));
        ASSERT (Response != NULL);
        SenseDataLen = Response->SenseDataLen;
        SwapLittleEndianToBigEndian ((UINT8*)&SenseDataLen, sizeof (UINT16));

        if ((Packet->SenseDataLength != 0) && (Packet->SenseData != NULL)) {
          CopyMem (Packet->SenseData, Response->SenseData, SenseDataLen);
          Packet->SenseDataLength = (UINT8)SenseDataLen;
        }

        //
        // Check the transfer request result.
        //
        Packet->TargetStatus = Response->Status;
        if (Response->Response != 0) {
          DEBUG ((DEBUG_VERBOSE, "ProcessAsyncTaskList(): Signal Event %p Target Failure.\n", TransReq->CallerEvent));
          SignalCallerEvent (Private, TransReq);
          continue;
        }

        if (TransReq->Trd->Ocs == 0) {
          if (Packet->DataDirection == EFI_EXT_SCSI_DATA_DIRECTION_READ) {
            if ((Response->Flags & BIT5) == BIT5) {
              ResTranCount = Response->ResTranCount;
              SwapLittleEndianToBigEndian ((UINT8*)&ResTranCount, sizeof (UINT32));
              Packet->InTransferLength -= ResTranCount;
            }
          } else {
            if ((Response->Flags & BIT5) == BIT5) {
              ResTranCount = Response->ResTranCount;
              SwapLittleEndianToBigEndian ((UINT8*)&ResTranCount, sizeof (UINT32));
              Packet->OutTransferLength -= ResTranCount;
            }
          }
        } else {
          DEBUG ((DEBUG_VERBOSE, "ProcessAsyncTaskList(): Signal Event %p Target Device Error.\n", TransReq->CallerEvent));
          SignalCallerEvent (Private, TransReq);
          continue;
        }

        DEBUG ((DEBUG_VERBOSE, "ProcessAsyncTaskList(): Signal Event %p Success.\n", TransReq->CallerEvent));
        SignalCallerEvent (Private, TransReq);
      }
    }
  }

  //
  // Dispatch the next pending async request
  //
  DispatchNextPendingRequest (Private);
}

