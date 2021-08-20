/** @file
  This file contains the main entry point for the MRC mini-BIOS.

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

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcInterface.h"
#include "MrcCommon.h"
#include "uart16550.h"
#include "spi.h"
#include "McAddress.h"
#include "MrcDebugHook.h"
#include "MrcStartMemoryConfiguration.h"
#include "MrcGeneral.h"
#include "MrcOemPlatform.h"
#include "MemoryUtils.h"
#include "MrcMalloc.h"
#include "MrcInterpreter.h"
#include "Library/PchPcrLib.h"
#include "Library/PchInfoLib.h"
#include "Register/PchRegsPcr.h"
#include "Register/PchRegsLpc.h"
#include "Register/PchRegsDmi.h"

#define MAX_HEAP_SIZE (32 * 1024)

#define REBOOT_TEST 0



#include "EcCommands.h"
#include "PlatformBoardId.h"

//
// CPU Family and Stepping Masks
//
#define CPU_FAMILY_MASK   0xFFFFFFF0
#define CPU_STEPPING_MASK 0x0000000F

//
// Internal module definitions
//
typedef struct {
  UINT32 MmioWritePtr;
  UINT32 MmioReadPtr;
  UINT32 NextAllocation;
} TMallocParams;


typedef struct {
  UINT32 Start;
  UINT32 End;
} TTimeParams;

///
/// Define the MRC SMBUS devices type.
///
typedef enum {
  datOemSpd_0_0,      ///< use for get the device address for channel 0 dimm 0
  datOemSpd_0_1,      ///< use for get the device address for channel 0 dimm 1
  datOemSpd_1_0,      ///< use for get the device address for channel 1 dimm 0
  datOemSpd_1_1,      ///< use for get the device address for channel 1 dimm 1
  datOemVrefWrite_0,  ///< use for get the device address for dimm vref controlled potentiometer channel 0
  datOemVrefWrite_1,  ///< use for get the device address for dimm vref controlled potentiometer channel 1
  datOemVrefRead      ///< use for get the device address for cpu vref controlled potentiometer
} MRC_OemSmbusDeviceType;

const UINT8 MrcDataStringConst[] = "MRCD";
const UINT8 MrcSpdStringConst[]  = "SPD ";

#ifdef BDAT_SUPPORT
// In full BIOS these are defined in SiPkg.dec
EFI_GUID gEfiMemorySchemaGuid         = { 0xCE3F6794, 0x4883, 0x492C, { 0x8D, 0xBA, 0x2F, 0xC0, 0x98, 0x44, 0x77, 0x10 }};
EFI_GUID gMrcSchemaListHobGuid        = { 0x3047C2AC, 0x5E8E, 0x4C55, { 0xA1, 0xCB, 0xEA, 0xAD, 0x0A, 0x88, 0x86, 0x1B }};
EFI_GUID gRmtResultMetadataGuid       = { 0x02CB1552, 0xD659, 0x4232, { 0xB5, 0x1F, 0xCA, 0xB1, 0xE1, 0x1F, 0xCA, 0x87 }};
EFI_GUID gRmtResultColumnsGuid        = { 0x0E60A1EB, 0x331F, 0x42A1, { 0x9D, 0xE7, 0x45, 0x3E, 0x84, 0x76, 0x11, 0x54 }};
EFI_GUID gMargin2DResultMetadataGuid  = { 0x48265582, 0x8E49, 0x4AC7, { 0xAA, 0x06, 0xE1, 0xB9, 0xA7, 0x4C, 0x97, 0x16 }};
EFI_GUID gMargin2DResultColumnsGuid   = { 0x91A449EC, 0x8A4A, 0x4736, { 0xAD, 0x71, 0xA3, 0xF6, 0xF6, 0xD7, 0x52, 0xD9 }};
EFI_GUID gSsaBiosResultsGuid          = { 0x8f4e928,  0xf5f,  0x46d4, { 0x84, 0x10, 0x47, 0x9f, 0xda, 0x27, 0x9d, 0xb6 }};
#endif

//
// Internal functions.
//
static
void
init_malloc(
  CPU_SETUP_OPTIONS *Input
  );

static
UINT8
MrcOemGetSmBusDeviceAddress (
  MrcParameters *const    MrcData,
  UINT16                  BoardId,
  MRC_OemSmbusDeviceType  SmbusDeviceType
  );

extern
UINTN
OemMemoryBase (
  void
  );

BOOLEAN
MrcIsTxtProcessor (
  void
  );

BOOLEAN
MrcIsTxtChipset (
  void
  );

UINT16
MrcGetBoardId (
  MrcParameters *const MrcData,
  UINT16        *const FabId,
  UINT16        *const BomId,
  BOOLEAN       *const SpdPresent
  );

UINT32
MrcCPUStepGet (
  void
  );

void
GPIOBaseEnable (
  void
  );

/**
  Print IA32 exception number / name and CS:EIP that caused the exception.

  @param[in] Exception - exception type number
  @param[in] RegCs     - CS of the exception
  @param[in] RegEip    - EIP of the exception

**/
void
_PrintExceptionDetails (
  UINT32 Exception,
  UINT32 RegCs,
  UINT32 RegEip
  )
{
#ifdef MRC_DEBUG_PRINT
  UINT8 Str[16];
  static const char UnknownStr[] = "Unknown";
  static const char *ExceptionName[20] = {
    "#DE - Divide Error",
    "#DB - Reserved",
    "NMI Interrupt",
    "#BP - Breakpoint",
    "#OF - Overflow",
    "#BR - BOUND Range Exceeded",
    "#UD - Invalid Opcode (Undefined  Opcode)",
    "#NM - Device Not Available (No Math Coprocessor)",
    "#DF - Double Fault",
    "Coprocessor Segment Overrun (reserved)",
    "#TS - Invalid TSS",
    "#NP - Segment Not Present",
    "#SS - Stack-Segment Fault",
    "#GP - General Protection Fault",
    "#PF - Page Fault",
    "Reserved",
    "#MF - x87 FPU Floating-Point Error (Math Fault)",
    "#AC - Alignment Check",
    "#MC - Machine Check",
    "#XM - SIMD floating point exception"
  };

  MrcOemMemorySet (&Str[0], sizeof (Str), 0);
  UartPuts ("!!!! IA32 Exception Type - 0x");
  MrcUintnToStr ((const MRC_FUNCTION *) NULL, Exception, sizeof (UINT32), (char *) &Str[0], 2, MRC_PREFIX_ZERO, 16);
  UartPuts ((const char *) Str);
  UartPuts (": ");

  if (Exception < 20) {
    UartPuts (ExceptionName[Exception]);
  } else {
    UartPuts (UnknownStr);
  }

  UartPuts ("\r\nAt CS:EIP = 0x");
  MrcOemMemorySet (&Str[0], sizeof (Str), 0);
  MrcUintnToStr ((const MRC_FUNCTION *) NULL, RegCs, sizeof (UINT32), (char *) &Str[0], 4, MRC_PREFIX_ZERO, 16);
  UartPuts ((const char *) Str);
  UartPuts (":0x");
  MrcOemMemorySet (&Str[0], sizeof (Str), 0);
  MrcUintnToStr ((const MRC_FUNCTION *) NULL, RegEip, sizeof (UINT32), (char *) &Str[0], 8, MRC_PREFIX_ZERO, 16);
  UartPuts ((const char *) Str);
  UartPuts (" !!!!\r\n");
#endif
}

/**

Routine description:

  Prints the stack depth reached by MiniBIOS.  Called from assembly.
  Assumes this is called after _prepareToCallMemRefCode().
  Todo: If heap is used in MiniBIOS, this causes stack depth function
  to return a value near to full stack size, incorrectly reporting stack usage.

Arguments:

  StackDepth - The amount of stack used

Returns

  Nothing.

**/
void
_printStackDepth (
  UINT32 StackDepth
  )
{
#ifdef MRC_DEBUG_PRINT
  UINT8 Str[16];

  MrcOemMemorySet ((UINT8 *) &Str[0], sizeof (Str), 0);
  MrcUintnToStr ((const MRC_FUNCTION *) NULL, StackDepth, sizeof (UINT32), (char *) &Str[0], 0, 0, 10);
  UartPuts ((const char *) Str);
  UartPuts (" (");
  MrcOemMemorySet ((UINT8 *) &Str[0], sizeof (Str), 0);
  MrcUintnToStr ((const MRC_FUNCTION *) NULL, StackDepth, sizeof (UINT32), (char *) &Str[0], 0, 0, 16);
  UartPuts ((const char *) Str);
  UartPuts ("h)\r\n");
#endif
  return;
}

static
void
Dummy (
  void
  )
{
  return;
}

/**
  Test MrcWait() function by measuring it.

  @param[in] MrcData   - Include all MRC global data.
  @param[in] DelayNs   - time to wait in [ns], up to 2^32 [ns] = 4.29 seconds

  @retval Nothing
**/
void
TestTimer (
  MrcParameters   *MrcData,
  UINT32          DelayNs
  )
{
  MrcDebug  *Debug;
  UINT64    start_time;
  UINT64    finish_time;
  INT64     Delta;
  UINT32    i;

  Debug = &MrcData->Outputs.Debug;

  for (i = 0; i <= 3; i++) {
    start_time   = MrcOemGetCpuTimeNanoSec (MrcData);
    MrcWait (MrcData, DelayNs);
    finish_time  = MrcOemGetCpuTimeNanoSec (MrcData);
    Delta = finish_time - start_time;
    if (i == 0) {
      continue;                   // First iteration brings the code into cache, do not check it
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "--> Delay = %lld ns = %lld us\n", Delta, MrcOemMemoryDivideU64ByU64 (Delta, 1000));
    if ((ABS (Delta - DelayNs)) > 300) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "-------> MrcWait() delay is not correct !!\n");
    }
  }
}

/**
  A small memory test to quickly point out severe memory issues.

  @param[in] MrcData - Pointer to the MRC global data structure

  @retval mrcFail on failure, otherwise mrcSuccess.
**/
MrcStatus
BasicMemoryTest (
  IN MrcParameters * CONST MrcData
  )
{
  MrcDebug       *Debug;
  CONST UINT32    BlockSize = 0x20000;
  volatile UINT8  *Addr;
  UINT8           Pattern;
  UINT8           Value;
  UINTN           LoopCount;
  UINT8           AddressStep;

  Debug = &MrcData->Outputs.Debug;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Basic memtest started.\n");

  // Run in two address step modes:
  //  1. Address step = 1, to focus on single rank traffic.
  //  2. Address step = 64, to focus on rank switches.

  for (AddressStep = 1; AddressStep <= 64; AddressStep += 63) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "AddressStep: %d\n", AddressStep);
    Addr    = 0;
    Pattern = 0;
    while ((UINT32) Addr < BlockSize) {
      *Addr = Pattern++;
      Addr += AddressStep;
    }

    for (LoopCount = 0; LoopCount < 20; LoopCount++) {
      Addr    = 0;
      Pattern = 0;
      while ((UINT32) Addr < BlockSize) {
        Value = *Addr;
        if (Value != Pattern) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR,
            "!!! Basic memtest FAILED !!!\nAddress: %Xh, Expected data: %Xh, Actual data: %Xh.\n",
            Addr,
            Pattern,
            Value
            );
          return mrcFail;
        }
        Addr += AddressStep;
        Pattern++;
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Basic memtest passed.\n");
  return mrcSuccess;
}

UINT32
_prepareToCallMemRefCode (
  CPU_SETUP_OPTIONS *Input
  )
/**

Routine Description:

  Main starting point for the Mini-BIOS MRC.

Arguments:

  Input - Various input options.

Returns:

  mrcSuccess or failure indication.

**/
{
  MrcParameters   *MrcData;
  MrcControllerIn *ControllerIn;
  MrcChannelIn    *ChannelIn;
  MrcDimmIn       *DimmIn;
  MRC_FUNCTION    CallTable;
  MRC_FUNCTION    *MrcCall;
  MrcStatus       Status;
  UINT32          MchBarBaseAddress;
  UINT32          PciEBaseAddress;
  UINT32          SmbusBaseAddress;
  TMallocParams   *MallocParams;
  MrcInput        *Inputs;
  MrcOutput       *Outputs;
  MrcIntOutput    *IntOutputs;
  MrcDebug        *Debug;
  UINT64          MsrData;
  UINT32          CpuModelStep;
  UINT32          DeviceId;
  UINT32          Crc32;
  UINT16          BoardId;
  UINT16          FabId;
  UINT16          BomId;
  UINT16          SAFE;
  UINT16          NS;
  UINT8           Controller;
  UINT8           Channel;
  UINT8           Dimm;
  UINT8           Index;
  BOOLEAN         UlxUlt;
  BOOLEAN         SpdPresent;
  BOOLEAN         TrainingDone;
  UINT32          Data32;
  UINT32          Offset;

  CAPID0_C_0_0_0_PCI_STRUCT Capid0C;

#if REBOOT_TEST
  UINT8           ResetCount;
#endif // REBOOT_TEST
  UINT32 DmiBar;
  PCIE_CR_OPIO_RX_DLL_GLOBAL3_STRUCT  RxDllGlobal3;
  MrcIntOutput  MrcIntGlobalData;
  MrcParameters GlobalData;

  Init16550Uart ();
  PchSpiInit();
  init_malloc (Input);

  MrcOemMemorySet ((UINT8 *) &GlobalData, sizeof (MrcParameters), 0);
  MrcOemMemorySet ((UINT8 *) &MrcIntGlobalData, sizeof (MrcIntOutput), 0);
  MrcData                                 = &GlobalData;
  Inputs                                  = &MrcData->Inputs;
  Inputs->Call.Func                       = &CallTable;
  MrcCall                                 = Inputs->Call.Func;
  IntOutputs                              = &MrcIntGlobalData;
  MrcData->IntOutputs.Internal            = IntOutputs;
  Outputs                                 = &MrcData->Outputs;
  Debug                                   = &Outputs->Debug;
  MrcCall->MrcIoRead8                     = (MRC_IO_READ_8) (&MrcOemInPort8);
  MrcCall->MrcIoRead16                    = (MRC_IO_READ_16) (&MrcOemInPort16);
  MrcCall->MrcIoRead32                    = (MRC_IO_READ_32) (&MrcOemInPort32);
  MrcCall->MrcIoWrite8                    = (MRC_IO_WRITE_8) (&MrcOemOutPort8);
  MrcCall->MrcIoWrite16                   = (MRC_IO_WRITE_16) (&MrcOemOutPort16);
  MrcCall->MrcIoWrite32                   = (MRC_IO_WRITE_32) (&MrcOemOutPort32);
  MrcCall->MrcMmioRead8                   = (MRC_MMIO_READ_8) (&MrcOemMmioRead8);
  MrcCall->MrcMmioRead16                  = (MRC_MMIO_READ_16) (&MrcOemMmioRead16);
  MrcCall->MrcMmioRead32                  = (MRC_MMIO_READ_32) (&MrcOemMmioRead32);
  MrcCall->MrcMmioRead64                  = (MRC_MMIO_READ_64) (&MrcOemMmioRead64);
  MrcCall->MrcMmioWrite8                  = (MRC_MMIO_WRITE_8) (&MrcOemMmioWrite8);
  MrcCall->MrcMmioWrite16                 = (MRC_MMIO_WRITE_16) (&MrcOemMmioWrite16);
  MrcCall->MrcMmioWrite32                 = (MRC_MMIO_WRITE_32) (&MrcOemMmioWrite32);
  MrcCall->MrcMmioWrite64                 = (MRC_MMIO_WRITE_64) (&MrcOemMmioWrite64);
  MrcCall->MrcSmbusRead8                  = (MRC_SMBUS_READ_8) (&SmBusReadDataByte);
  MrcCall->MrcSmbusRead16                 = (MRC_SMBUS_READ_16) (&SmBusReadDataWord);
  MrcCall->MrcSmbusWrite8                 = (MRC_SMBUS_WRITE_8) (&SmBusWriteDataByte);
  MrcCall->MrcSmbusWrite16                = (MRC_SMBUS_WRITE_16) (&SmBusWriteDataWord);
  MrcCall->MrcGetPciDeviceAddress         = (MRC_GET_PCI_DEVICE_ADDRESS) (&GetPciDeviceAddress);
  MrcCall->MrcGetPcieDeviceAddress        = (MRC_GET_PCIE_DEVICE_ADDRESS) (&GetPcieDeviceAddress);
  MrcCall->MrcGetRtcTime                  = (MRC_GET_RTC_TIME) (&GetRtcTime);
  MrcCall->MrcGetCpuTime                  = (MRC_GET_CPU_TIME) (&GetCpuTime);
  MrcCall->MrcCopyMem                     = (MRC_MEMORY_COPY) (&MrcOemMemoryCpy);
  MrcCall->MrcSetMem                      = (MRC_MEMORY_SET_BYTE) (&MrcOemMemorySet);
  MrcCall->MrcSetMemWord                  = (MRC_MEMORY_SET_WORD) (&SetMemWord);
  MrcCall->MrcSetMemDword                 = (MRC_MEMORY_SET_DWORD) (&SetMemDword);
  MrcCall->MrcLeftShift64                 = (MRC_LEFT_SHIFT_64) (&LShiftU64);
  MrcCall->MrcRightShift64                = (MRC_RIGHT_SHIFT_64) (&RShiftU64);
  MrcCall->MrcMultU64x32                  = (MRC_MULT_U64_U32) (&MultU64x32);
  MrcCall->MrcDivU64x64                   = (MRC_DIV_U64_U64) (&DivU64x64Remainder);
  MrcCall->MrcGetSpdData                  = (MRC_GET_SPD_DATA) (&GetSpdData);
  MrcCall->MrcGetRandomNumber             = (MRC_GET_RANDOM_NUMBER) (&GetRandomNumber32);
  MrcCall->MrcCpuMailboxRead              = (MRC_CPU_MAILBOX_READ) (&MailboxRead);
  MrcCall->MrcCpuMailboxWrite             = (MRC_CPU_MAILBOX_WRITE) (&MailboxWrite);
  MrcCall->MrcGetMemoryVdd                = (MRC_GET_MEMORY_VDD) (&GetMemoryVdd);
  MrcCall->MrcSetMemoryVdd                = (MRC_SET_MEMORY_VDD) (&SetMemoryVdd);
  MrcCall->MrcCheckpoint                  = (MRC_CHECKPOINT) (&CheckPoint);
  MrcCall->MrcDebugHook                   = (MRC_DEBUG_HOOK) (&MrcOemDebugHook);
#ifdef MRC_DEBUG_PRINT
  MrcCall->MrcPrintString                 = (MRC_PRINT_STRING) (&MrcPuts);
#else
  MrcCall->MrcPrintString                 = (MRC_PRINT_STRING) (&Dummy);
#endif
  MrcCall->MrcRtcCmos                     = (MRC_GET_RTC_CMOS) (&RtcRead);
  MrcCall->MrcReadMsr64                   = (MRC_MSR_READ_64) (&ReadMsr64);
  MrcCall->MrcWriteMsr64                  = (MRC_MSR_WRITE_64) (&WriteMsr64);
  MrcCall->MrcReturnFromSmc               = (MRC_RETURN_FROM_SMC) (&Dummy);
  MrcCall->MrcDramReset                   = (MRC_DRAM_RESET) (&MrcOemDramReset);
  MrcCall->MrcDelayNs                     = (MRC_DELAY_NS) (&MrcOemDelayNs);
  MrcCall->MrcSetLockPrmrr                = (MRC_SET_LOCK_PRMRR) (&MrcSetCorePrmrr);
  MrcCall->MrcTxtAcheck                   = (MRC_TXT_ACHECK) (&Dummy);
  MrcCall->MrcClearSecretsBit             = (MRC_TXT_CLEAR_SECRETS_BIT) (&Dummy);
  MrcCall->MrcSetPowerDownRequest         = (MRC_TXT_SET_POWER_DOWN_REQUEST) (&Dummy);
  MrcCall->MrcSetGfxMemMap                = (MRC_SET_GFX_MEM_MAP) (&Dummy);
  Inputs->PciIndex                        = 0xCF8;
  Inputs->PciData                         = 0xCFC;
  MrcData->MrcDataSize                    = sizeof (MrcParameters);
  MrcData->Save.Size                      = sizeof (MrcSave);
//  MrcData->Inputs.Size                    = sizeof (MrcInput);
  Outputs->Size                           = sizeof (MrcOutput);
  IntOutputs->Size                        = sizeof (MrcIntOutput);
  MrcCall->MrcCopyMem ((UINT8 *) &MrcData->MrcDataString[0], (UINT8 *) MrcDataStringConst, sizeof (MrcData->MrcDataString));
  SAFE = 0;
  DmiBar = 0;
  RxDllGlobal3.Data = 0;

  Inputs->DebugLevel  = MSG_LEVEL_ALL;  // Everything excluding MSG_LEVEL_TIME
  Inputs->DebugStream = 1;
  // Top of stack at the beginning of MRC - for stack usage calculations.
  // Don't count IDT table and the heap buffer - they are specific to MiniBios.
  Inputs->MrcStackTop.DataN = Input->nem_data_addr + Input->nem_data_size - 21 * 8 - MAX_HEAP_SIZE;

  MRC_DEBUG_MSG_OPEN (MrcData, Inputs->DebugLevel, Inputs->DebugStream, Inputs->SerialBuffer.DataN, Inputs->SerialBufferSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MiniBIOS MRC hello world\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "NemData Address/Size: 0x%x / 0x%x\n",Input->nem_data_addr, Input->nem_data_size);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "TopStackAddr: 0x%x\n", Debug->TopStackAddr.DataN);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Heap: 0x%x\n", Inputs->HeapBase.DataN);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "SerialBuffer: 0x%x, size: 0x%x\n", Inputs->SerialBuffer.DataN, Inputs->SerialBufferSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "sizeof (MrcParameters): %6d\n", sizeof (MrcParameters));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "  sizeof (MrcInput):    %6d\n", sizeof (MrcInput));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "  sizeof (MrcOutput):   %6d\n", sizeof (MrcOutput));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "  sizeof (MrcSave):     %6d\n", sizeof (MrcSave));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "sizeof (MrcIntOutput):  %6d\n", sizeof (MrcIntOutput));

  // Clear the high port80 byte.
  MrcOemOutPort16 (0x80, 0);

  // Check that MCHBAR is programmed
  MrcCall->MrcIoWrite32 (Inputs->PciIndex, MrcCall->MrcGetPciDeviceAddress (0, 0, 0, MCHBAR_0_0_0_PCI_REG));
  MchBarBaseAddress = MrcCall->MrcIoRead32 (Inputs->PciData);

  if ((MchBarBaseAddress & MRC_BIT0) == MRC_BIT0) {
    MchBarBaseAddress &= (~MRC_BIT0);
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MCHBAR is not programmed!\n");
    return mrcFail;
  }

  // Check that PCIEXBAR is programmed
  MrcCall->MrcIoWrite32 (Inputs->PciIndex, MrcCall->MrcGetPciDeviceAddress (0, 0, 0, PCIEXBAR_0_0_0_PCI_REG));
  PciEBaseAddress = MrcCall->MrcIoRead32 (Inputs->PciData);


  if ((PciEBaseAddress & MRC_BIT0) == MRC_BIT0) {
    PciEBaseAddress &= (~MRC_BIT0);
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "PCIEXBAR is not programmed!\n");
    return mrcFail;
  }

  Inputs->MchBarBaseAddress = MchBarBaseAddress;
  Inputs->PciEBaseAddress   = PciEBaseAddress;

  MrcDisablePciePorts (MrcData);
  MrcOemDebugHook (MrcData, MRC_INITIALIZATION_START);

#ifdef BDAT_SUPPORT
  MrcGetHobForDataStorage (MrcData, (VOID **) &Outputs->BdatMemoryHob[0], sizeof (BDAT_MEMORY_DATA_HOB), &gEfiMemorySchemaGuid);
  MrcGetBdatSchemaListHob (MrcData, &Outputs->BdatSchemasHob.Pointer);
#endif

  // Determine the CPU and stepping
  CpuModelStep = MrcCPUStepGet ();
  Inputs->CpuidModel    = CpuModelStep & CPU_FAMILY_MASK;
  Inputs->CpuidStepping = (Inputs->CpuidModel == cmEHL)? csIclUlxUltLast : (CpuModelStep & CPU_STEPPING_MASK);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Cpu Model/Stepping: 0x%x\n", CpuModelStep);
  Status = MrcSetCpuInformation (MrcData, Inputs->CpuidModel, Inputs->CpuidStepping);
  if (Status != mrcSuccess) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_ERROR,
      "ERROR: CPU Family/Model/Step %Xh is not supported.  Continuing as ICL ULX/ULT last known stepping: %Xh.\n",
      CpuModelStep,
      csIclUlxUltLast
      );
    Inputs->CpuModel    = cmICL_ULX_ULT;
    Inputs->CpuStepping = csIclUlxUltLast;
    Inputs->CpuFamily   = cfIcl;
  }
  UlxUlt = (Inputs->CpuModel == cmICL_ULX_ULT);

  // This is needed for MrcWait
  Inputs->BClkFrequency          = BCLK_DEFAULT;
  Inputs->TscTimeBase            = (Inputs->BClkFrequency / 1000 / 1000) * MrcGetCpuRatio (); // In microsec
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "TscTimeBase: %lld\n", Inputs->TscTimeBase);

  // Check that SMBUS Base Address is programmed
  SmbusBaseAddress = GetSmBusBaseAddress ();
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "SmbusBaseAddress = 0x%x\n", SmbusBaseAddress);
  if (SmbusBaseAddress == 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "SMBUS base address is not programmed!\n");
    return mrcFail;
  }
  // Test MrcWait function
  TestTimer (MrcData, MRC_TIMER_1US);  // 1000 ns = 1 us

  GPIOBaseEnable ();
  MrcOemGpioInit (MrcData);
  Inputs->SmbusBaseAddress  = SmbusBaseAddress;

  // Scrambler Support.
  Inputs->ScramblerSupport = TRUE;
  // Remap above 4G Support
  Inputs->RemapEnable            = TRUE;

  Inputs->VddVoltage             = VDD_INVALID;   // Based on SPD
  Inputs->VddSettleWaitTime      = 0;             // Additive latency to the 200us default.  0 us by default

  // Get VccIO value:
  // SKL ULT/ULX: 0.85v/0.95v, according to PCIE_CR_OPIO_RX_DLL_GLOBAL3[31:30]
  // SKL DT/Halo: 0.95v always
  Inputs->VccIomV = 950;
  if (UlxUlt) {
    DmiBar = (MrcCall->MrcMmioRead32 (Inputs->PciEBaseAddress + DMIBAR_0_0_0_PCI_REG)) & ~BIT0;
    if (DmiBar == 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "DMIBAR is not programmed!\n");
      return mrcFail;
    }
    RxDllGlobal3.Data = MrcCall->MrcMmioRead32 (DmiBar + PCIE_CR_OPIO_RX_DLL_GLOBAL3_DMIBAR_REG);
    if (RxDllGlobal3.Bits.select_vccio_level == 0) {
      Inputs->VccIomV = 850;
    }
  }

  // Detect the board type.
  // OEM must fill in correct board type here.
  SpdPresent = TRUE;
  FabId = 0;
  BomId = 0;
  BoardId    = 1;

  // Switch for ECC/Memory Scrubbing test.
  Inputs->CleanMemory = FALSE;
  Inputs->TxtClean    = FALSE;

  // Init the memory map values (only for testing).
  Inputs->MeStolenSize               = 0;            // MB
  Inputs->MmioSize                   = 1024;         // MB
  Inputs->TsegSize                   = 8;            // MB
  Inputs->GraphicsGttSize            = 0;            // MB
  Inputs->GraphicsStolenSize         = 0;            // MB
  Inputs->GfxIsVersatileAcceleration = FALSE;
  Inputs->DprSize                    = 0;            // MB
  Inputs->PrmrrSize                  = MrcCheckPrmrrSupport(MrcData, 128); // MB

  // Init working modes.
  Inputs->MemoryProfile          = STD_PROFILE;
  Inputs->FreqMax                = fNoInit;
  Inputs->EccSupport             = TRUE;
  Inputs->Ibecc                  = FALSE;
  Inputs->IbeccParity            = FALSE;
  Inputs->IbeccOperationMode     = 1;
  for (Index = 0; Index < MAX_IBECC_REGIONS; Index++) {
    Inputs->IbeccProtectedRegionEnable[Index] = FALSE;
    Inputs->IbeccProtectedRegionBase[Index] = 0x0040;
    Inputs->IbeccProtectedRegionMask[Index] = 0x3fff;
  }
  // Safe Configuration was moved to MrcSafeConfig() in MrcGeneral.c.  This is executed in the calltable.
  // This keeps the safe mode configuration uniform between Full and MiniBIOS.
  Inputs->MrcSafeConfig = FALSE;
  Inputs->SafeMode = FALSE;
  if (Inputs->SafeMode) {
    SAFE = 0xFFFF;
  }
  NS = ~SAFE;

  if (Inputs->MemoryProfile == USER_PROFILE) {
    Inputs->Ratio                = 0;  // 0 = Auto, otherwise speed will be ratio times refclk
    Inputs->RefClk               = MRC_REF_CLOCK_133;
  }

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn = &Inputs->Controller[Controller].Channel[Channel];
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmIn = &ChannelIn->Dimm[Dimm];

        DimmIn->Timing.NMode   = 0;
        if (Inputs->MemoryProfile == USER_PROFILE) {
          DimmIn->Timing.tCL     = 0;
          DimmIn->Timing.tCWL    = 0;
          DimmIn->Timing.tFAW    = 0;
          DimmIn->Timing.tRAS    = 0;
          DimmIn->Timing.tRCDtRP = 0;
          DimmIn->Timing.tREFI   = 0;
          DimmIn->Timing.tRFC    = 0;
          DimmIn->Timing.tRRD    = 0;
          DimmIn->Timing.tRTP    = 0;
          DimmIn->Timing.tWR     = 0;
          DimmIn->Timing.tWTR    = 0;
        }
      }
    }
  }


  Inputs->PowerDownMode                 = pdmAuto;         // 0/1/6/0xFF = NO PD/APD/PPD-DLLOFF/Auto
  Inputs->PwdwnIdleCounter              = 0;               // Auto
  Inputs->DisPgCloseIdleTimeout         = 0;               // Page Close Idle Timeout 0 = Enabled, 1 = Disabled

  Inputs->RhPrevention                  = FALSE;           // Row Hammer prevention. All DRAMs are supposed to be RH-free in ICL timeframe.
  Inputs->RhSolution                    = HardwareRhp;     // Type of solution to be used for RHP - 0/1 = HardwareRhp/Refresh2x
  Inputs->RhActProbability              = OneIn2To11;       // Activation probability for Hardware RHP
  Inputs->RankInterleave                = TRUE;            // Enable Rank Interleave. HORI can't be enabled at the same time
  Inputs->EnhancedInterleave            = TRUE;            // Enable Enhanced Interleave.

  Inputs->WeaklockEn                    = TRUE;            // Enable Weak Lock
  Inputs->EnCmdRate                     = 3;               // Valid values are: 0-7

  Inputs->ChHashEnable                  = TRUE;            // Enale/disable CH HASH support
  Inputs->ChHashMask                    = 0x30CC;          // Addr bits[19:6] to include in Channel XOR function.
  Inputs->ChHashInterleaveBit           = 2;               // BIT8 (Valid values are 0-7 for BITS 6 - 13)
  Inputs->ExtendedBankHashing           = TRUE;           // Enable Extended Bank Hashing

  // Options for Thermal settings
  Inputs->EnableExtts                   = 0;
  Inputs->EnableCltm                    = 0;
  Inputs->EnableOltm                    = 0;
  Inputs->EnablePwrDn                   = 1;
  Inputs->EnablePwrDnLpddr              = 1;
  Inputs->Refresh2X                     = 0;
  Inputs->DdrThermalSensor              = 1;        // Enable LPDDR MR4 temperature reads
  Inputs->LockPTMregs                   = 0;

  Inputs->EnergyScaleFact               = 3;
  Inputs->RaplLim2Lock                  = 0;
  Inputs->ThermalEnables.RaplLim2WindX  = 0;
  Inputs->ThermalEnables.RaplLim2WindY  = 0;
  Inputs->RaplLim2Ena                   = 0;
  Inputs->ThermalEnables.RaplLim2Pwr    = 0;
  Inputs->ThermalEnables.RaplLim1WindX  = 0;
  Inputs->ThermalEnables.RaplLim1WindY  = 0;
  Inputs->RaplLim1Ena                   = 0;
  Inputs->ThermalEnables.RaplLim1Pwr    = 0;
  Inputs->RaplPwrFlCh0                  = 0;
  Inputs->RaplPwrFlCh1                  = 0;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      Inputs->ThermalEnables.WarmThreshold[Channel][Dimm] = 0xFF;
      Inputs->ThermalEnables.HotThreshold[Channel][Dimm]  = 0xFF;
      Inputs->ThermalEnables.WarmBudget[Channel][Dimm]    = 0xFF;
      Inputs->ThermalEnables.HotBudget[Channel][Dimm]     = 0xFF;
      Inputs->ThermalEnables.IdleEnergy[Channel][Dimm]    = 0;
      Inputs->ThermalEnables.PdEnergy[Channel][Dimm]      = 0;
      Inputs->ThermalEnables.ActEnergy[Channel][Dimm]     = 0;
      Inputs->ThermalEnables.RdEnergy[Channel][Dimm]      = 0;
      Inputs->ThermalEnables.WrEnergy[Channel][Dimm]      = 0;
    }
  }

  Inputs->SrefCfgEna            = 1;
  Inputs->SrefCfgIdleTmr        = 0x200;
  Inputs->ThrtCkeMinDefeat      = 0;
  Inputs->ThrtCkeMinTmr         = 0x30;
  Inputs->ThrtCkeMinDefeatLpddr = 1;
  Inputs->ThrtCkeMinTmrLpddr    = 0x40;

  Inputs->MemoryTrace           = 0;

  Inputs->AutoSelfRefreshSupport = TRUE;
  Inputs->ExtTemperatureSupport  = TRUE;

  Inputs->MaxRttWr = 0;
  Inputs->ForceSingleRank = FALSE;
  Inputs->ForceSingleSubchannel = FALSE;

  if( UlxUlt && (Inputs->CpuStepping == csIclA0)) {
    Inputs->PerBankRefresh  = FALSE;
  } else {
    Inputs->PerBankRefresh  = TRUE;
  }

  Inputs->Mars = TRUE;

  Inputs->RdTPbdDis       = FALSE;
  Inputs->WrTPbdDis       = FALSE;

  // Options for training steps
//  Inputs->SimicsFlag                  = 1;  // Simics flag disables MRC training.
  Inputs->LpFreqSwitch                = TRUE;
  Inputs->DDR4MAP                     = 0;
  Inputs->TrainingEnables.SOT         = 1;
  Inputs->TrainingEnables.ECT         = 1;
  Inputs->TrainingEnables.RDMPRT      = 0;  // We use ERDMPRTC2D instead
  Inputs->TrainingEnables.RCVET       = 1;
  Inputs->TrainingEnables.JWRL        = 1;
  Inputs->TrainingEnables.ERDMPRTC2D  = 1;
  Inputs->TrainingEnables.EWRTC2D     = 1;
  Inputs->TrainingEnables.ERDTC2D     = 1;
  Inputs->TrainingEnables.WRTC1D      = 1;
  Inputs->TrainingEnables.WRVC1D      = 1;
  Inputs->TrainingEnables.RDTC1D      = 1;
  Inputs->TrainingEnables.DIMMODTT    = 1;
  Inputs->TrainingEnables.DIMMRONT    = 1;
  Inputs->TrainingEnables.WRDSEQT     = 1; //(UlxUlt) ? 0 : 1;
  Inputs->TrainingEnables.WRDSUDT     = (UlxUlt) ? 0 : 1;
  Inputs->TrainingEnables.WRSRT       = 1;
  Inputs->TrainingEnables.RDEQT       = 1;
  Inputs->TrainingEnables.RDODTT      = 1;
  Inputs->TrainingEnables.RDAPT       = 1;
  Inputs->TrainingEnables.CMDVC       = 1;
  Inputs->TrainingEnables.WRTC2D      = 1;
  Inputs->TrainingEnables.RDTC2D      = 1;
  Inputs->TrainingEnables.WRVC2D      = 1;
  Inputs->TrainingEnables.RDVC2D      = 1;
  Inputs->TrainingEnables.LCT         = 1;
  Inputs->TrainingEnables.RTL         = 1;
  Inputs->TrainingEnables.TAT         = 0;
  Inputs->TrainingEnables.RCVENC1D    = 1;
  Inputs->TrainingEnables.ALIASCHK    = 1;
  Inputs->TrainingEnables.RMC         = 0;
  Inputs->TrainingEnables.RMT         = 1;
  Inputs->TrainingEnables2.RDVC1D     = 1;
  Inputs->TrainingEnables2.TXTCO      = 0;
  Inputs->TrainingEnables2.TXTCODQS   = 0;
  Inputs->TrainingEnables2.CLKTCO     = 0;
  Inputs->TrainingEnables2.DCC        = 1;
  Inputs->TrainingEnables2.DQDFE      = 0;
  Inputs->TrainingEnables2.SOTC       = 0;
  Inputs->DqBitDccRerunInWrTPbd       = TRUE;
  Inputs->TrainingEnables2.CMDSR      = 0;
  Inputs->TrainingEnables2.CMDDSEQ    = 0;
  Inputs->TrainingEnables2.DIMMODTCA  = 1;
  Inputs->TrainingEnables2.PERIODICDCC  = 0;
  Inputs->TrainingEnables2.RMTBIT     = 0;

  Inputs->RmtPerTask              = TRUE;
  Inputs->TrainTrace              = FALSE;
  Inputs->ExitOnFailure           = TRUE;

  Inputs->DramDqOdt               = MrcAuto;
  Inputs->Lp4Npath                = FALSE;
  Inputs->LowSupplyEnData         = FALSE;
  Inputs->LowSupplyEnCcc          = FALSE;
  Inputs->Lp4DqsOscEn             = TRUE;

  Inputs->DllBwEn0 = 0;
  Inputs->DllBwEn1 = 1;
  Inputs->DllBwEn2 = 2;
  Inputs->DllBwEn3 = 2;

  Inputs->MarginLimitCheck = MARGIN_CHECK_DISABLE;
  Inputs->MarginLimitL2 = 200;

  // Detect if we are running under Simics
  Data32 = MrcCall->MrcMmioRead32 (Inputs->PciEBaseAddress + 0xFC);
  if ((Data32 & 0xFF) == 0x04) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Simics detected (0x%08X)\n", Data32);
    Inputs->SimicsFlag = 1;
  }

  if (!Inputs->SimicsFlag) {
    Inputs->SaGv = MrcSaGvDisabled; // (UlxUlt && (Inputs->CpuStepping == csIclA0)) ? MrcSaGvDisabled : MrcSaGvEnabled;
  } else {
    Inputs->SaGv = MrcSaGvDisabled;
  }

  if( !UlxUlt && (Inputs->CpuStepping >= csIclG0)) {
    Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, CAPID0_C_0_0_0_PCI_REG);
    Capid0C.Data = MrcCall->MrcMmioRead32 (Offset);
    if (Capid0C.Bits.SPARE_14) {
      Inputs->SaGv  = MrcSaGvDisabled;
    }
  }

  //Inputs->SaGv  = MrcSaGvDisabled;

  Inputs->DdrSpeedControl  = 1;     // 1 = Manual, frequencies and Gears will not be overridden in MrcEarlyOverrides
  // Frequencies and Gears configured as POR
  if (Inputs->SaGv == MrcSaGvEnabled) {
    Inputs->FreqSaGvLow   = 2133;
    Inputs->FreqSaGvMid   = 3733;
    Inputs->FreqMax       = 2400;

    Inputs->SaGvLowGear2  = 1;
    Inputs->SaGvMidGear2  = 1;
    Inputs->SaGvHighGear2 = 0;
  } else {
    Inputs->FreqMax       = 3733;
    Inputs->SaGvHighGear2 = 1;
  }


  Inputs->LoopBackTest  = 0;  // CPGC Loopback test
  Inputs->Ddr4OneDpc    = 3;  // DDR4 1DPC performance feature: 0 - Disabled; 1 - Enabled on DIMM0 only, 2 - Enabled on DIMM1 only; 3 - Enabled on both DIMMs. (bit [0] - DIMM0, bit [1] - DIMM1)

  Inputs->BdatEnable    = 0;
  Inputs->BdatTestType  = RankMarginToolPerBitType;

  // Read PCI 0:0:0:2 - Device ID
  DeviceId = MrcCall->MrcMmioRead32 (PciEBaseAddress);
  DeviceId = (DeviceId >> 16) & 0xFFFF;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "CPU Device ID: 0x%04X - ", DeviceId);
  switch (DeviceId) {
    case V_SA_DEVICE_ID_ICL_MB_ULT_1:
    case V_SA_DEVICE_ID_ICL_MB_ULT_2:
    case V_SA_DEVICE_ID_ICL_UN_ULT_1:
    case V_SA_DEVICE_ID_ICL_UN_ULT_2:
    case V_SA_DEVICE_ID_ICL_MB_ULX_1:
    case V_SA_DEVICE_ID_ICL_MB_ULX_2:
    case V_SA_DEVICE_ID_ICL_YN_ULX_1:
    case V_SA_DEVICE_ID_ICL_YN_ULX_2:
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
      Inputs->BoardType      = btMobile;  // Mobile: Y/U/YN/UN/SDS
      Inputs->MobilePlatform = TRUE;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ULT/ULX\n");
      break;

    case MRC_SA_DEVICE_ID_ICL_DT_1:
    case MRC_SA_DEVICE_ID_ICL_DT_2:
    case MRC_SA_DEVICE_ID_ICL_HALO_1:
    case MRC_SA_DEVICE_ID_ICL_HALO_2:
      Inputs->BoardType      = btDesktop;
      Inputs->MobilePlatform = FALSE;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Desktop / Halo / UP Server\n");
      break;

//    case V_SA_DEVICE_ID_JSL_I_1:
//      Inputs->BoardType      = btMobile;
//      Inputs->MobilePlatform = TRUE;
//      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rev1 JSL\n");
//      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: Unknown CPU Device ID!\n");
      MRC_DEADLOOP ();
  }

  // Interleaving mode of DQ/DQS pins - depends on board routing
  switch (BoardId) {
    // case Some_IL_Board:
    //  Inputs->DqPinsInterleaved = 1;
    //  break;

    default:
      Inputs->DqPinsInterleaved = 0;
  }

  // CPU ODT mode
  Inputs->VttCompForVsshi = 1;

  // Board CA Vref connectivity - depends on board routing
  Inputs->CaVrefConfig = 2;   // DDR4 boards

  // Select which pin is connected to CKE[1] for DDR4
  // 0 - xxDDR0_CKE_D4r1_LPechAr1 (CKE0/1 have shared delay)
  // 1 - xxDDR0_CKE_D4r1_LPechBr1 (CKE0/1 have separate delay)
  Inputs->SeparateCkeDelayDdr4 = 1;

  // LPDDR4: Bitmask of ranks that have CA bus terminated. Rank0 is terminating and Rank1 is non-terminating
  Inputs->CmdRanksTerminated = 0x01;

  Inputs->EpgEnable           = 0;  // EPG disabled by default.
  Inputs->Idd3n               = 26;
  Inputs->Idd3p               = 11;
  Inputs->SharedZqPin         = 0;
  Inputs->Ddr4DdpSharedClock  = 0;

  // Initialize the board-specific CMD/CTL/CLK and DQ/DQS mapping for LPDDR4
  MrcOemLpddrBoardMapping (MrcData, BoardId, FabId, BomId);

  // Initialize the board-specific RCOMP values
  MrcOemRcompValues (MrcData, BoardId);

  // Unlock CPU in case LT is enabled
  MrcCall->MrcMmioRead32 (0xFED40000);

  if (MrcIsTxtChipset ()) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Chipset is LT-capable, Unlocking Memory\n");
    MrcCall->MrcWriteMsr64 (0x2E6, 0);
  }




  // Get DIMM SpdBaseAddresses.
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerIn               = &Inputs->Controller[Controller];
    ControllerIn->ChannelCount = MAX_CHANNEL;
    for (Channel = 0;  Channel < MAX_CHANNEL; Channel++) {
      ChannelIn            = &ControllerIn->Channel[Channel];
      // Decide which channels and DIMMs are enabled.
      switch (Inputs->DisableDimmChannel[Channel]) {
        case 1:
          ChannelIn->Dimm[0].Status = DIMM_DISABLED;
          ChannelIn->Dimm[1].Status = DIMM_ENABLED;
          ChannelIn->Status         = CHANNEL_PRESENT;
          ControllerIn->ChannelCount++;
          ChannelIn->DimmCount      = 1;
          break;
        case 2:
          ChannelIn->Dimm[0].Status = DIMM_ENABLED;
          ChannelIn->Dimm[1].Status = DIMM_DISABLED;
          ChannelIn->Status         = CHANNEL_PRESENT;
          ControllerIn->ChannelCount++;
          ChannelIn->DimmCount      = 1;
          break;
        case 3:
          ChannelIn->Dimm[0].Status = DIMM_DISABLED;
          ChannelIn->Dimm[1].Status = DIMM_DISABLED;
          ChannelIn->Status         = CHANNEL_DISABLED;
          ChannelIn->DimmCount      = 0;
          break;
        default:
          ChannelIn->Dimm[0].Status = DIMM_ENABLED;
          ChannelIn->Dimm[1].Status = DIMM_ENABLED;
          ChannelIn->Status         = CHANNEL_PRESENT;
          ControllerIn->ChannelCount++;
          ChannelIn->DimmCount      = 2;
          break;
      }
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        Index   = (Channel * MAX_DIMMS_IN_CHANNEL) + Dimm;
        DimmIn  = &ChannelIn->Dimm[Dimm];
        if (SpdPresent) {
          DimmIn->SpdAddress = MrcOemGetSmBusDeviceAddress (MrcData, BoardId, (MRC_OemSmbusDeviceType) Index);
          MrcCall->MrcCopyMem ((UINT8 *) &DimmIn->Spd.MrcSpdString[0], (UINT8 *) MrcSpdStringConst, sizeof (DimmIn->Spd.MrcSpdString));
        }
        DimmIn->Spd.Flag.Bit.DimmNumber    = Dimm;
        DimmIn->Spd.Flag.Bit.ChannelNumber = Channel;
        DimmIn->Spd.Flag.Bit.MdSocket      = (DimmIn->SpdAddress > 0) ? 1 : 0;
      }
    }
  }
  // Enables MiniBIOS to support Memory Down configs such as Harris Beach which does not have an SPD.
#if (defined MEMORY_DOWN_SUPPORT && (MEMORY_DOWN_SUPPORT > 0))
  EnableMemoryDown (MrcData, BoardId, FabId, BomId, SpdPresent);
#endif

  // This enabled Fast/Warm boot flow.
  // In Stub mode we save the MrcSave struct to a file on the client.
  // In MiniBios the MrcSave struct should be flashed at offset MRC_SAVE_DATA_FLASH_PTR (0xFFD00000)
  if (MrcSaveExists ()) {
    MrcGetMrcSaveData ((UINT8 *) &MrcData->Save, sizeof (MrcSave));
    Crc32 = MrcCalculateCrc32 ((UINT8 *) (&MrcData->Save.Data), sizeof (MrcSaveData));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Calc. crc = 0x%x, Header crc = 0x%x\n", Crc32, MrcData->Save.Header.Crc);
    if (Crc32 == MrcData->Save.Header.Crc) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Save Data is valid.  Boot Mode: ");
      if (MrcGetBootMode (MrcData) == bmWarm) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "bmWarm\n");
        Inputs->BootMode = bmWarm;
      } else {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "bmFast\n");
        Inputs->BootMode = bmFast;
      }
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Save Data is not valid\nCold boot\n");
    }
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "bmCold\n");
    Inputs->BootMode = bmCold;
  }

  // Read SPD data.
  if (mrcSuccess != GetSpdData (Inputs->BootMode, MrcData)) {
    MRC_DEADLOOP ();
  }


  // Run the memory configuration code.
  Status = mrcSuccess;
  TrainingDone = FALSE;
  if (Status == mrcSuccess) {
    if (!TrainingDone) {
      Status = MrcStartMemoryConfiguration (MrcData, 0, NULL, 0);
    }

    switch (Status) {
      case mrcSuccess:
        TrainingDone = TRUE;
        break;

      default:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "!!!!!!!!!!!!!!!!!!!\n");
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, " ERROR: MRC failed\n");
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "!!!!!!!!!!!!!!!!!!!\n");
        TrainingDone = FALSE;
        MRC_DEADLOOP ();
    }

    //Set the MSR bit VIRTUAL_MSR_CR_POWER_CTL.SAPM_iMC_C2_POLICY to 0 if serialize_zq is 1.
    if (Inputs->SharedZqPin == 1) {
      MsrData = MrcCall->MrcReadMsr64 (MSR_POWER_CTL1);
      MsrData &= ~(UINT64)MRC_BIT2;
      MrcCall->MrcWriteMsr64 (MSR_POWER_CTL1, MsrData);
    }

    MrcSetDISB (MrcData);             // Set DRAM Initialization Status Bit, so that we can do Warm flow

    Status = BasicMemoryTest (MrcData);
    if (Status == mrcSuccess) {
    }
    MallocParams = (TMallocParams  *) OemMemoryBase ();
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*********************************************************************\n");
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*  MRC is done and MC is in NORMAL MODE and ready to use            *\n");
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*  Number of MMIO reads:  %8d                                  *\n", MallocParams->MmioReadPtr);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*  Number of MMIO writes: %8d                                  *\n", MallocParams->MmioWritePtr);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*  MrcSave: 0x%08X, size: 0x%08X bytes                      *\n", &MrcData->Save, sizeof (MrcSave));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*  Stack: Top: 0x%x Bottom: 0x%x Depth: %d\n",
      Debug->TopStackAddr.DataN,
      Debug->LowestStackAddr.DataN,
      Debug->TopStackAddr.DataN - Debug->LowestStackAddr.DataN
      );
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*********************************************************************\n");
    MrcOemDebugHook (MrcData, MRC_MEM_INIT_DONE);

#if REBOOT_TEST
    ResetCount = RtcRead (MRC_RESET_COUNT_CMOS_ADDR);
    if (ResetCount != 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "<------------------ REBOOT : %d resets left ----------------------> \n", ResetCount);
      RtcWrite (MRC_RESET_COUNT_CMOS_ADDR, ResetCount - 1);
      IoWrite8 (0xcf9, 6);
    }
#endif // REBOOT_TEST

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MRC Stack Depth: "); //_printStackDepth function prints the actual value and is called from assembly code.
  }



  return Status;
}

static
void
init_malloc (
  CPU_SETUP_OPTIONS *Input
  )
/**

Routine Description:

    init the malloc system. need to be call in the MiniBIOS start.

Arguments:

   N/A

Returns:

    N/A

**/
{
  TMallocParams *MallocParams;
  MallocParams  = (TMallocParams *) Input->nem_data_addr;

  MallocParams->NextAllocation = (sizeof (TMallocParams) + (UINTN) MallocParams);
  MallocParams->MmioReadPtr  = 0;
  MallocParams->MmioWritePtr = 0;
  return;
}

void
MmioWriteCount (
  void
  )
/**

Routine Description:

  This function count the number of access to writes MMIO registers .

Arguments:

  N/A

Returns:

  N/A

**/
{
  TMallocParams  *MallocParams;
  MallocParams = (TMallocParams *) OemMemoryBase ();
  MallocParams->MmioWritePtr++;
  return;
}

void
MmioReadCount (
  void
  )
/**

Routine Description:

     This function count the number of access to reads MMIO registers .

Arguments:

    N/A

Returns:

    N/A

**/
{
  TMallocParams  *MallocParams;
  MallocParams = (TMallocParams *) OemMemoryBase ();
  MallocParams->MmioReadPtr++;
  return;
}

BOOLEAN
MrcIsTxtProcessor (
  void
  )
/**

  Determines whether or not the current processor is TXT Capable.


  @retval TRUE          - If the current processor supports TXT
  @retval FALSE         - If the current processor does not support TXT

**/
{
  UINT32 TxtCapable = FALSE;

#ifdef __GNUC__  // GCC compiler
  //@todo:
#else
  ASM {
    mov   ecx, 1
    cpuid
    and   ecx, MRC_BIT6
    shr   ecx, 6
    mov   TxtCapable, ecx
  }
#endif // __GNUC__
  return (BOOLEAN) TxtCapable;
}

BOOLEAN
MrcIsTxtChipset (
  void
  )
/**

  Determines whether or not the current chipset is TXT Capable.


  @retval TRUE          - If the current chipset supports TXT
  @retval FALSE         - If the current chipset doesn't supports TXT

**/
{
  BOOLEAN TxtCapable;
  UINT32  Data32;

  Data32 = * (volatile UINT32 *) (0xFED30000 + 0x10);

  TxtCapable = (BOOLEAN) ((Data32 & MRC_BIT0) != 0);

  return TxtCapable;
}


UINT32
MrcCPUStepGet (
  void
  )
/**

Routine Description:

    This function returns the CPUID.1.EAX value.

Arguments:

    N/A
Returns:
    CPU ID

**/
{
  UINT32 Value;

  ASM {
    mov  eax, 1
    cpuid
    mov Value, eax
  }
  return Value;
}

void
GPIOBaseEnable (
  void
  )
/**

Routine Description:

    Enables GPIO base.

Arguments:

    N/A

Returns:

    N/A

**/
{
  ASM {

    ;
    ; Enable GPIO BASE I/O registers
    ;
    mov  eax, PCI_LPC_BASE + 48h
    mov  dx, 0CF8h
    out  dx, eax
    mov  eax, GPIO_BASE_ADDRESS
    add  dx, 4
    out  dx, eax

    mov  eax, PCI_LPC_BASE + 4Ch
    mov  dx, 0CF8h
    out  dx, eax
    add  dx, 4
    in   al, dx
    or   al, BIT4       ; GPIOBASE Enable
    out  dx, al
  }
  return;
}

/**
  This function return the SMBUS device address to each DIMM.

  @param[in]  MrcData         - Pointer to global MRC data.
  @param[in]  BoardId         - Board selector for correct SMBUS address
  @param[in]  SmbusDeviceType - Point to the require device address.

  @retval UINT8 - Smbus device address.

**/
static
UINT8
MrcOemGetSmBusDeviceAddress (
  MrcParameters *const    MrcData,
  UINT16                  BoardId,
  MRC_OemSmbusDeviceType  SmbusDeviceType
  )
{
  UINT8 SmBusDeviceAddress;

    switch (SmbusDeviceType) {
      case datOemSpd_0_0:
        SmBusDeviceAddress = 0xA0;
        break;
      case datOemSpd_0_1:
        SmBusDeviceAddress = 0xA2;
        break;
      case datOemSpd_1_0:
        SmBusDeviceAddress = 0xA4;
        break;
      case datOemSpd_1_1:
        SmBusDeviceAddress = 0xA6;
        break;
      case datOemVrefWrite_0:
        SmBusDeviceAddress = 0x00;
        break;
      case datOemVrefWrite_1:
        SmBusDeviceAddress = 0x00;
        break;
      case datOemVrefRead:
        SmBusDeviceAddress = 0x00;
        break;
      default :
        SmBusDeviceAddress = 0x00;
        break;
    }


  if (BoardId == BoardIdEhlDdr4Type3Rvp2) {
    switch (SmbusDeviceType) {
      case datOemSpd_0_0:
        SmBusDeviceAddress = 0xA0;
        break;
      case datOemSpd_0_1:
        SmBusDeviceAddress = 0xA2;
        break;
      case datOemSpd_1_0:
        SmBusDeviceAddress = 0xA4;
        break;
      case datOemSpd_1_1:
        SmBusDeviceAddress = 0xA6;
        break;
      case datOemVrefWrite_0:
        SmBusDeviceAddress = 0x00;
        break;
      case datOemVrefWrite_1:
        SmBusDeviceAddress = 0x00;
        break;
      case datOemVrefRead:
        SmBusDeviceAddress = 0x00;
        break;
      default :
        SmBusDeviceAddress = 0x00;
        break;
    }
  }

  return SmBusDeviceAddress;
}
