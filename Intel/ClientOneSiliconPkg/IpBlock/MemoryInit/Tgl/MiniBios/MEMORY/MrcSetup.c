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
#include "PchAccess.h"
#include "PchInfoLib.h"
#include "McAddress.h"
#include "MrcDebugHook.h"
#include "MrcStartMemoryConfiguration.h"
#include "MrcGeneral.h"
#include "MrcOemPlatform.h"
#include "MemoryUtils.h"
#include "MrcInterpreter.h"
#include "MrcMalloc.h"
#ifdef SSA_FLAG
#include "MrcSsaInitialize.h"
#endif
#define MAX_HEAP_SIZE (32 * 1024)

#define REBOOT_TEST 0


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
  datOemSpd_0_0_0,      ///< use for get the device address for controller 0 channel 0 dimm 0 - DDR4 - DDR5 - LPDDR4 - LPDDR5
  datOemSpd_0_0_1,      ///< use for get the device address for controller 0 channel 0 dimm 1 - DDR4
  datOemSpd_0_1_0,      ///< use for get the device address for controller 0 channel 1 dimm 0 -------- DDR5 - LPDDR4 - LPDDR5
  datOemSpd_0_1_1,      ///< use for get the device address for controller 0 channel 1 dimm 1 -------- DDR5 2DPC
  datOemSpd_0_2_0,      ///< use for get the device address for controller 0 channel 2 dimm 0 --------------- LPDDR4 - LPDDR5
  datOemSpd_0_3_0 = 6,  ///< use for get the device address for controller 0 channel 3 dimm 0 --------------- LPDDR4 - LPDDR5
  datOemSpd_1_0_0 = 8,  ///< use for get the device address for controller 1 channel 0 dimm 0 - DDR4 - DDR5 - LPDDR4 - LPDDR5
  datOemSpd_1_0_1,      ///< use for get the device address for controller 1 channel 0 dimm 1 - DDR4
  datOemSpd_1_1_0,      ///< use for get the device address for controller 1 channel 1 dimm 0 -------- DDR5 - LPDDR4 - LPDDR5
  datOemSpd_1_1_1,      ///< use for get the device address for controller 1 channel 1 dimm 1 -------- DDR5 2DPC
  datOemSpd_1_2_0,      ///< use for get the device address for controller 1 channel 2 dimm 0 --------------- LPDDR4 - LPDDR5
  datOemSpd_1_3_0 = 14, ///< use for get the device address for controller 1 channel 3 dimm 0 --------------- LPDDR4 - LPDDR5
  datOemVrefWrite_0_0,  ///< use for get the device address for dimm vref controlled potentiometer controller 0 channel 0
  datOemVrefWrite_0_1,  ///< use for get the device address for dimm vref controlled potentiometer controller 0 channel 1
  datOemVrefWrite_1_0,  ///< use for get the device address for dimm vref controlled potentiometer controller 1 channel 0
  datOemVrefWrite_1_1,  ///< use for get the device address for dimm vref controlled potentiometer controller 1 channel 1
  datOemVrefRead        ///< use for get the device address for cpu vref controlled potentiometer
} MRC_OemSmbusDeviceType;

const UINT8 MrcDataStringConst[] = "MRCD";
const UINT8 MrcSpdStringConst[]  = "SPD ";
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

  MrcWait (MrcData, DelayNs);     // Call it once to bring the code into cache
  for (i = 0; i < 3; i++) {
    start_time   = MrcOemGetCpuTimeNanoSec (MrcData);
    MrcWait (MrcData, DelayNs);
    finish_time  = MrcOemGetCpuTimeNanoSec (MrcData);
    Delta = finish_time - start_time;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "--> Delay = %lld ns = %lld us\n", Delta, MrcOemMemoryDivideU64ByU64 (Delta, 1000));
    if ((ABS (Delta - DelayNs)) > 300) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "-------> MrcWait() delay is not correct !!\n");
    }
  }
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
  UINT32          DeviceId;
  UINT32          Crc32;
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
  UINT32          CpuModelStep;
  UINT32          NewMaxFreq;
  UINT16          BoardId;
  UINT16          SAFE;
  UINT16          NS;
  UINT8           Controller;
  UINT8           Channel;
  UINT8           Dimm;
  UINT8           Index;
  UINT8           DisableChannel;
  UINT8           CmosValue;
  BOOLEAN         UlxUlt;
  BOOLEAN         SpdPresent;
#if REBOOT_TEST
  UINT8           ResetCount;
#endif // REBOOT_TEST
  UINT32 DmiBar;
  PCIE_CR_OPIO_RX_DLL_GLOBAL3_STRUCT  RxDllGlobal3;

  MrcIntOutput  MrcIntGlobalData;
  MrcParameters GlobalData;
  Init16550Uart ();
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
  MrcCall->MrcTmeInit                     = (MRC_TME_INIT) (&MrcTmeInit);
  MrcCall->MrcTxtAcheck                   = (MRC_TXT_ACHECK) (&Dummy);
  MrcCall->MrcSetIaGtImrExclusion         = (MRC_SET_IA_GT_IMR_EXCLUSION) (&Dummy);
  MrcCall->MrcSetIaGtImrExclusionLock     = (MRC_SET_IA_GT_IMR_EXCLUSION_LOCK) (&Dummy);
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

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR is %X\n", MchBarBaseAddress);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PCIEXBAR is %X\n", PciEBaseAddress);

  MrcOemDebugHook (MrcData, MRC_INITIALIZATION_START);
  // Determine the CPU and stepping
  CpuModelStep = MrcCPUStepGet ();
  Inputs->CpuidModel    = CpuModelStep & CPU_FAMILY_MASK;
  Inputs->CpuidStepping = CpuModelStep & CPU_STEPPING_MASK;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Cpu Model/Stepping: 0x%x\n", CpuModelStep);
  Status = MrcSetCpuInformation (MrcData, Inputs->CpuidModel, Inputs->CpuidStepping);
  if (Status != mrcSuccess) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_ERROR,
      "ERROR: CPU Family/Model/Step %Xh is not supported.  Continuing as ICL ULX/ULT last known stepping: %Xh.\n",
      CpuModelStep,
      csTglUlxUltLast
      );
    Inputs->CpuModel    = cmTGL_ULX_ULT;
    Inputs->CpuStepping = csTglUlxUltLast;
    Inputs->CpuFamily   = cfTgl;
    //MRC host structure is Byte set to 0.  So Inputs->[DtHalo,Mobile] is FALSE by default
    Inputs->UlxUlt      = TRUE;
  }
  UlxUlt = Inputs->UlxUlt;

  // This is needed for MrcWait
  Inputs->BClkFrequency = BCLK_DEFAULT;
  Inputs->TscTimeBase   = (Inputs->BClkFrequency / 1000 / 1000) * MrcGetCpuRatio (); // In microsec
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "TscTimeBase: %lld\n", Inputs->TscTimeBase);

  // Test MrcWait function
  TestTimer (MrcData, MRC_TIMER_1US);  // 1000 ns = 1 us

  // Check that SMBUS Base Address is programmed
  SmbusBaseAddress = GetSmBusBaseAddress ();
  if (SmbusBaseAddress == 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "SMBUS base address is not programmed!\n");
    return mrcFail;
  }
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
  BoardId = BoardIdTglUDdr4; // Default to DDR4 board
  // Switch for ECC/Memory Scrubbing test.
  Inputs->CleanMemory = FALSE;

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
  // Safe Configuration was moved to MrcSafeConfig() in MrcGeneral.c.  This is executed in the calltable.
  // This keeps the safe mode configuration uniform between Full and MiniBIOS.
  //Inputs->MrcSafeConfig = TRUE;
  Inputs->SafeMode = TRUE;
  Inputs->MrcSafeConfig = TRUE;
  if (Inputs->SafeMode) {
    SAFE = 0xFFFF;
  }
  NS = ~SAFE;

  if (Inputs->MemoryProfile == USER_PROFILE) {
    Inputs->Ratio                = 0;  // Auto
    Inputs->RefClk               = MRC_REF_CLOCK_133;
  }

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
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
  Inputs->RankInterleave                = TRUE;            // Enable Rank Interleave. HORI can't be enabled at the same time
  Inputs->EnhancedInterleave            = TRUE;            // Enable Enhanced Interleave.

  Inputs->WeaklockEn                    = TRUE;            // Enable Weak Lock
  Inputs->EnCmdRate                     = 7;               // Valid values are: 0,5,7,9,11,13,15

  Inputs->ChHashEnable                  = TRUE;            // Enale/disable CH HASH support
  Inputs->ChHashMask                    = 0x30CC;          // Addr bits[19:6] to include in Channel XOR function.
  Inputs->ChHashInterleaveBit           = 2;               // BIT8 (Valid values are 0-7 for BITS 6 - 13)
  Inputs->MsHashEnable                  = TRUE;            // Enale/disable CH HASH support
  Inputs->MsHashMask                    = 0x30C8;          // Addr bits[19:6] to include in Channel XOR function.
  Inputs->MsHashInterleaveBit           = 2;               // BIT8 (Valid values are 0-7 for BITS 6 - 13)

  // Options for Thermal settings
  Inputs->EnablePwrDn                   = 1;
  Inputs->EnablePwrDnLpddr              = 1;
  Inputs->Refresh2X                     = 0;

  Inputs->SrefCfgEna            = 1;
  Inputs->SrefCfgIdleTmr        = 0x200;
  Inputs->ThrtCkeMinDefeat      = 0;
  Inputs->ThrtCkeMinTmr         = 0x30;
  Inputs->ThrtCkeMinDefeatLpddr = 1;
  Inputs->ThrtCkeMinTmrLpddr    = 0x40;

  Inputs->AutoSelfRefreshSupport = TRUE;
  Inputs->ExtTemperatureSupport  = TRUE;

  Inputs->MaxRttWr = 0;
  Inputs->ForceSingleRank = FALSE;
  Inputs->ForceSingleSubchannel = FALSE;
  //Inputs->PerBankRefresh  = TRUE;
  Inputs->PerBankRefresh = FALSE;
  Inputs->Mars = TRUE;
  Inputs->RdTPbdDis       = TRUE;
  Inputs->WrTPbdDis       = TRUE;

  // Options for training steps
//  Inputs->SimicsFlag                  = 1;  // Simics flag disables MRC training.
  Inputs->LpFreqSwitch                = FALSE;  // <ICL> @todo Going to Normal mode for freq switch breaks CBT flow
  Inputs->DDR4MAP                     = 0;
  Inputs->TrainingEnables.SOT         = 1;
  Inputs->TrainingEnables.ECT         = 1;
  Inputs->TrainingEnables.RDMPRT      = 1;
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
  Inputs->TrainingEnables.WRDSEQT     = (UlxUlt) ? 0 : 1;
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
  Inputs->TrainingEnables.TAT         = 1;
  Inputs->TrainingEnables.RCVENC1D    = 1;
  Inputs->TrainingEnables.ALIASCHK    = 1;
  Inputs->TrainingEnables.RMC         = 1;
  Inputs->TrainingEnables.RMT         = 1;
  Inputs->TrainingEnables.MEMTST      = 1;
  Inputs->TrainingEnables2.RDVC1D     = 1;
  Inputs->TrainingEnables2.TXTCO      = 1;
  Inputs->TrainingEnables2.CLKTCO     = 1;
  Inputs->TrainingEnables2.DCC        = 1;
  Inputs->TrainingEnables2.RMTBIT     = 0;
  Inputs->DqBitDccRerunInWrTPbd = FALSE;

  Inputs->PowerTrainingMode       = (UlxUlt) ? MrcTmPower : MrcTmMargin;
  //Inputs->RmtPerTask              = TRUE;
  Inputs->RmtPerTask = FALSE;
  Inputs->TrainTrace              = FALSE;
  Inputs->ExitOnFailure           = TRUE;

  Inputs->DramDqOdt               = MrcAuto;
  Inputs->LowSupplyEnData         = TRUE;
  Inputs->LowSupplyEnCcc          = FALSE;
  Inputs->LpDqsOscEn              = TRUE;
  Inputs->RxMode                  = 0xFF;            // 0xFF = Auto, for other values see enum of MRC_RX_MODE_TYPE

  Inputs->SaGv = MrcSaGvDisabled;//MrcSaGvEnabled;

  Inputs->SaGvFreq[MrcSaGvPoint1] = 0;
  Inputs->SaGvFreq[MrcSaGvPoint2] = 0;
  Inputs->SaGvFreq[MrcSaGvPoint3] = 0;
  Inputs->SaGvFreq[MrcSaGvPoint4] = 0;
  Inputs->FreqMax                 = 0;

  Inputs->SaGvGear[MrcSaGvPoint1] = 0;
  Inputs->SaGvGear[MrcSaGvPoint2] = 0;
  Inputs->SaGvGear[MrcSaGvPoint3] = 0;
  Inputs->SaGvGear[MrcSaGvPoint4] = 0;
  Inputs->GearRatio               = 0;

  Inputs->Ddr4OneDpc = 3;  // DDR4 1DPC performance feature: 0 - Disabled; 1 - Enabled on DIMM0 only, 2 - Enabled on DIMM1 only; 3 - Enabled on both DIMMs. (bit [0] - DIMM0, bit [1] - DIMM1)

  // Set Scomp Bypass for LPDDR4/5
  Inputs->ScompBypass[0] = 1;
  Inputs->ScompBypass[1] = 1;
  Inputs->ScompBypass[2] = 1;
  Inputs->ScompBypass[3] = 1;
// Read PCI 0:0:0:2 - Device ID
  DeviceId = MrcCall->MrcMmioRead32 (PciEBaseAddress);
  DeviceId = (DeviceId >> 16) & 0xFFFF;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "CPU Device ID: 0x%04X - ", DeviceId);
  switch (DeviceId) {
    case MRC_SA_DEVICE_ID_TGL_MB_ULT_1:
    case MRC_SA_DEVICE_ID_TGL_MB_ULT_2:
    case MRC_SA_DEVICE_ID_TGL_MB_ULX_1:
    case MRC_SA_DEVICE_ID_TGL_MB_SIMICS_1:  // For Simics
      Inputs->BoardType      = btUser4; // ULT board type
      Inputs->MobilePlatform = TRUE;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ULT/ULX\n");
      break;

    case MRC_SA_DEVICE_ID_TGL_DT_1:
    case MRC_SA_DEVICE_ID_TGL_DT_2:
    case MRC_SA_DEVICE_ID_TGL_HALO_1:
    case MRC_SA_DEVICE_ID_TGL_HALO_2:
      Inputs->BoardType      = btCRBDT;
      Inputs->MobilePlatform = FALSE;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Desktop / Halo / UP Server\n");
      break;

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

  // Select which pin is connected to CKE[1] for DDR4
  // 0 - xxDDR0_CKE_D4r1_LPechAr1 (CKE0/1 have shared delay)
  // 1 - xxDDR0_CKE_D4r1_LPechBr1 (CKE0/1 have separate delay)
  Inputs->SeparateCkeDelayDdr4 = 1;

  // LPDDR4: Bitmask of ranks that have CA bus terminated. Rank0 is terminating and Rank1 is non-terminating
  Inputs->CmdRanksTerminated = 0x01;

  Inputs->EpgEnable = 0;  // EPG disabled by default.
  Inputs->Idd3n     = 26;
  Inputs->Idd3p     = 11;

  // Initialize the board-specific CMD/CTL/CLK and DQ/DQS mapping for LPDDR3
  MrcOemLpddrBoardMapping (MrcData, BoardId);

  // Initialize the board-specific RCOMP values
  MrcOemRcompValues (MrcData);

  // Limit DDR speed using CMOS override at offset 0x4B
  CmosValue = MrcCall->MrcRtcCmos (MRC_DDR_FREQ_CMOS_ADDR);
  switch (CmosValue) {
    case 13:
      NewMaxFreq = f4267;
      break;

    case 12:
      NewMaxFreq = f3200;
      break;

    case 11:
      NewMaxFreq = f2933;
      break;

    case 10:
      NewMaxFreq = f2667;
      break;

    case 9:
      NewMaxFreq = f2400;
      break;

    case 8:
      NewMaxFreq = f2133;
      break;

    case 7:
      NewMaxFreq = f1867;
      break;

    case 6:
      NewMaxFreq = f1600;
      break;

    case 5:
      NewMaxFreq = f1333;
      break;

    case 4:
      NewMaxFreq = f1067;
      break;

    case 0:
    default:
      NewMaxFreq = 0;
      break;
  }

  if (NewMaxFreq != 0) {
    Inputs->FreqMax = NewMaxFreq;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CMOS Max Frequency Override: Freq %d CMOS Value %x\n", NewMaxFreq, CmosValue);
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Inputs->FreqMax: %d\n", Inputs->FreqMax);

  // Unlock CPU in case LT is enabled
  MrcCall->MrcMmioRead32 (0xFED40000);

  if (MrcIsTxtChipset ()) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Chipset is LT-capable, Unlocking Memory\n");
    MrcCall->MrcWriteMsr64 (0x2E6, 0);
  }

  DisableChannel = MrcCall->MrcRtcCmos (MRC_CHANNEL_DISABLE_CMOS_ADDR);


  // Get DIMM SpdBaseAddresses.
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    ControllerIn               = &Inputs->Controller[Controller];
    ControllerIn->ChannelCount = MAX_CHANNEL;
    for (Channel = 0;  Channel < MAX_CHANNEL; Channel++) {
      ChannelIn            = &ControllerIn->Channel[Channel];
      if ((DisableChannel >> (Controller * MAX_CHANNEL + Channel)) & 1) {
        ChannelIn->Dimm[0].Status = DIMM_DISABLED;
        ChannelIn->Dimm[1].Status = DIMM_DISABLED;
        ChannelIn->Status         = CHANNEL_DISABLED;
        ChannelIn->DimmCount      = 0;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "!!!!!Controller %d Channel %d Disabled via CMOS!!!!!\n", Controller, Channel);
        continue;
      }
      ChannelIn->Status    = CHANNEL_PRESENT;
      ChannelIn->DimmCount = MAX_DIMMS_IN_CHANNEL;
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        Index              = (Controller << 3) | (Channel << 1) | Dimm;
        DimmIn             = &ChannelIn->Dimm[Dimm];
        DimmIn->Status     = DIMM_ENABLED;
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
  EnableMemoryDown (MrcData, BoardId, SpdPresent);
#endif

  // This enabled Fast/Warm boot flow.
  // In Stub mode we save the MrcSave struct to a file on the client.
  // In MiniBios the MrcSave struct should be flashed at offset MRC_SAVE_DATA_FLASH_PTR (0xFFD00000)
  if (MrcSaveExists (MrcData)) {
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
  if (Status == mrcSuccess) {
    Status = MrcStartMemoryConfiguration (MrcData, 0);
    switch (Status) {
      case mrcSuccess:
        break;

      default:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "!!!!!!!!!!!!!!!!!!!\n");
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, " ERROR: MRC failed\n");
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "!!!!!!!!!!!!!!!!!!!\n");
        MRC_DEADLOOP ();
    }

    MrcSetDISB (MrcData);             // Set DRAM Initialization Status Bit, so that we can do Warm flow

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
  UINT8    SmBusDeviceAddress;
    switch (SmbusDeviceType) {
      case datOemSpd_0_0_0:
        SmBusDeviceAddress = 0xA0;
        break;

      case datOemSpd_0_0_1:
        SmBusDeviceAddress = 0xA2;
        break;

      case datOemSpd_1_0_0:
        SmBusDeviceAddress = 0xA4;
        break;

      case datOemSpd_1_0_1:
        SmBusDeviceAddress = 0xA6;
        break;

      case datOemSpd_0_1_0:
      case datOemSpd_0_1_1:
      case datOemSpd_0_2_0:
      case datOemSpd_0_3_0:
      case datOemSpd_1_1_0:
      case datOemSpd_1_1_1:
      case datOemSpd_1_2_0:
      case datOemSpd_1_3_0:
      case datOemVrefWrite_0_0:
      case datOemVrefWrite_0_1:
      case datOemVrefWrite_1_0:
      case datOemVrefWrite_1_1:
      case datOemVrefRead:
      default:
        SmBusDeviceAddress = 0x00;
        break;
    }


  return SmBusDeviceAddress;
}
