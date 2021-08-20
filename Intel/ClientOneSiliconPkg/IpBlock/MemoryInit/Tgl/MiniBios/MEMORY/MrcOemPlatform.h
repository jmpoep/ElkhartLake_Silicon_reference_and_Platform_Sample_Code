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
#ifndef _MrcOemPlatform_h_
#define _MrcOemPlatform_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcInterface.h"
#include "MrcWriteDqDqs.h"
#include "crc.h"
#include "Smb.h"
#include "Io.h"
#include "PchAccess.h"
#include "PchInfoLib.h"

#define RTC_INDEX_MASK            (0x7F)
#define RTC_BANK_SIZE             (0x80)

#define RTC_SECONDS               (0x00)
#define RTC_MINUTES               (0x02)
#define RTC_HOURS                 (0x04)
#define RTC_DAY_OF_MONTH          (0x07)
#define RTC_MONTH                 (0x08)
#define RTC_YEAR                  (0x09)
#define CMOS_REGA                 (0x0A)
#define CMOS_REGB                 (0x0B)
#define CMOS_REGC                 (0x0C)
#define CMOS_REGD                 (0x0D)

#define RTC_UPDATE_IN_PROGRESS    (0x80)
#define RTC_HOLD                  (0x80)
#define RTC_MODE_24HOUR           (0x02)
#define RTC_CLOCK_DIVIDER         (0x20)
#define RTC_RATE_SELECT           (0x06)

#define BCD2BINARY(A)             (((((A) >> 4) & 0xF) * 10) + ((A) & 0xF))
#define CENTURY_OFFSET            (2000)

#define MRC_POST_CODE_LOW_BYTE_ADDR   (0x48)
#define MRC_POST_CODE_HIGH_BYTE_ADDR  (0x49)

#define GPIO_BASE_ADDRESS (0x800)

#define PLATFORM_MB             (0x04)
#define PLATFORM_SRVER          (0x01)
#define PLATFORM_DT             (0x01)

#define SB_BUS                  (0)
#define SB_PCI2ISA_DEVICE       (31)
#define SB_PCI2ISA_FUNC         (0)
#define SB_PCI2ISA_BUS_DEV_FUNC ((SB_BUS << 8) + ((SB_PCI2ISA_DEVICE << 3) + SB_PCI2ISA_FUNC))
#define PCI_LPC_BASE            (0x80000000 + (SB_PCI2ISA_BUS_DEV_FUNC << 8))

///
/// CPU SIMICS SA Device IDs B0:D0:F0
///
#define MRC_SA_DEVICE_ID_TGL_MB_SIMICS_1 0x9A00   ///< Tigerlake SIMICS

///
/// CPU Mobile SA Device IDs B0:D0:F0
///
#define MRC_SA_DEVICE_ID_TGL_MB_ULT_1 0x9A12   ///< Tigerlake Ult (TGL-U 4+2)
#define MRC_SA_DEVICE_ID_TGL_MB_ULT_2 0x9A14   ///< Tigerlake Ult (TGL-U 4+3e)
#define MRC_SA_DEVICE_ID_TGL_MB_ULX_1 0x9A10   ///< Tigerlake Ulx (TGL-Y 4+2)

///
/// CPU Desktop SA Device IDs B0:D0:F0
///
#define MRC_SA_DEVICE_ID_TGL_HALO_1   0x9A28   ///< Tigerlake Halo (6+1) SA DID
#define MRC_SA_DEVICE_ID_TGL_HALO_2   0x9A38   ///< Tigerlake Halo (8+2) SA DID

#define MRC_SA_DEVICE_ID_TGL_DT_1     0x9A2C   ///< Tigerlake Desktop (6+1) SA DID
#define MRC_SA_DEVICE_ID_TGL_DT_2     0x9A1C   ///< Tigerlake Desktop (4+1) SA DID

///
/// CPU Server SA Device IDs B0:D0:F0
///

#define MRC_EXIT_VALUE       (0xFF)
#define isprint(a)           (((a) >= ' ') && ((a) <= '~') ? (a) : 0)

typedef enum {
  MEMORY_ABSENT,    ///< No memory down and no physical memory slot.
  MEMORY_SLOT_ONLY, ///< No memory down and a physical memory slot.
  MEMORY_DOWN_ONLY, ///< Memory down and not a physical memory slot.
} MemorySlotStatus;

#define MAILBOX_WAIT_TIMEOUT  1000  ///< 1 millisecond
#define MAILBOX_WAIT_STALL    1     ///< 1 microsecond
#define MAILBOX_READ_TIMEOUT  10    ///< 10 microseconds

///
/// Expanded Overclocking Mailbox interface defintion, contains command id/completion code,
/// input parameters and the run/busy bit
///
typedef union _OC_MAILBOX_INTERFACE {
  UINT32 InterfaceData;
  struct {
    UINT8 CommandCompletion : 8; ///< Command ID and completion code
    UINT8 Param1            : 8; ///< Parameter 1, generally used to specify the CPU Domain ID
    UINT8 Param2            : 8; ///< Parameter 2, only current usage is as a core index for ratio limits message
    UINT8 Reserved          : 7; ///< Reserved for future use
    UINT8 RunBusy           : 1; ///< Run/Busy bit. This bit is set by BIOS to indicate the mailbox buffer is ready. pcode will clear this bit after the message is consumed.
  } Fields;
} OC_MAILBOX_INTERFACE;

///
///  Consolidated OC mailbox command structure containing both data and interface information
///
typedef struct _OC_MAILBOX_FULL {
  UINT32               Data;      ///< OC Mailbox read/write data
  OC_MAILBOX_INTERFACE Interface; ///< OC mailbox interface
} OC_MAILBOX_FULL;

///
///  Expanded Pcode Mailbox interface defintion, contains command id, address
///  and the run/busy bit
///
typedef union _PCODE_MAILBOX_INTERFACE {
  UINT32 InterfaceData;
  struct {
    UINT32 Command  : 8;  ///< Pcode mailbox command
    UINT32 Address  : 21; ///< Pcode mailbox address of command being issued
    UINT32 Reserved : 2;  ///< Reserved for future use
    UINT32 RunBusy  : 1;  ///< Run/Busy bit. This bit is set by BIOS to indicate the mailbox buffer is ready. pcode will clear this bit after the message is consumed.
  } Fields;
} PCODE_MAILBOX_INTERFACE;

///
///  Consolidated Pcode mailbox command structure containing both data and interface information
///
typedef struct _PCODE_MAILBOX_FULL {
  PCODE_MAILBOX_INTERFACE Interface; ///< Pcode mailbox interface
  UINT32                  Data;      ///< Pcode mailbox read/write data
} PCODE_MAILBOX_FULL;

/**
  Read the SPD data over the SMBus, for all DIMM slots and copy the data to the MrcData structure.
  The SPD data locations read is controlled by the current boot mode.

  @param[in]      BootMode - Mrc Boot Mode
  @param[in, out] MrcData  - Mrc Inputs structure

  @retval mrcSuccess if the read is successful, otherwise mrcDimmNotExist, which
  @retval indicates that no slots are populated.
**/
extern
MrcStatus
GetSpdData (
  IN     const MRC_BOOT_MODE  BootMode,
  IN OUT MrcParameters *const MrcData
  );

/*++

  8 bit I/O port read.

  @param[in] IoAddress - The I/O port read address.

  @retval The value read.
**/
extern
UINT8
MrcOemInPort8 (
  IN const UINT32 IoAddress
  );

/**
  8 bit I/O port write.

  @param[in] IoAddress - The I/O port read address.
  @param[in] Data      - The value to write.

  @retval Nothing.
**/
extern
void
MrcOemOutPort8 (
  IN const UINT32 IoAddress,
  IN const UINT8  Data
  );

/**
  16 bit I/O port read.

  @param[in] IoAddress - The I/O port read address.

  @retval The value read.
**/
extern
UINT16
MrcOemInPort16 (
  IN const UINT32 IoAddress
  );

/**
  16 bit I/O port write.

  @param[in] IoAddress - The I/O port read address.
  @param[in] Data      - The value to write.

  @retval Nothing.
**/
extern
void
MrcOemOutPort16 (
  IN const UINT32 IoAddress,
  IN const UINT16 Data
  );

/**
  32 bit I/O port read.

  @param[in] IoAddress - The I/O port read address.

  @retval The value read.
**/
extern
UINT32
MrcOemInPort32 (
  IN const UINT32 IoAddress
  );

/**

  32 bit I/O port write.

  @param[in] IoAddress - The I/O port read address.
  @param[in] Data      - The value to write.

  @retval Nothing.
**/
extern
void
MrcOemOutPort32 (
  IN const UINT32 IoAddress,
  IN const UINT32 Data
  );

/**
  The PCI index address.

  @retval The PCI index address.
**/
extern
UINT16
MrcOemPciIndex (
  void
  );

/**
  The PCI data address.

  @retval The PCI data address.
**/
extern
UINT16
MrcOemPciData (
  void
  );

/**
  Calculate the PCI device address for the given Bus/Device/Function/Offset.

  @param[in] Bus      - PCI bus
  @param[in] Device   - PCI device
  @param[in] Function - PCI function
  @param[in] Offset   - Offset

  @retval The PCI device address.
**/
extern
UINT32
GetPciDeviceAddress (
  IN const UINT8 Bus,
  IN const UINT8 Device,
  IN const UINT8 Function,
  IN const UINT8 Offset
  );

/**
  Calculate the PCIE device address for the given Bus/Device/Function/Offset.

  @param[in] Bus      - PCI bus
  @param[in] Device   - PCI device
  @param[in] Function - PCI function
  @param[in] Offset   - Offset

   The PCIE device address.

  @retval The PCIe device address
**/
extern
UINT32
GetPcieDeviceAddress (
  IN const UINT8 Bus,
  IN const UINT8 Device,
  IN const UINT8 Function,
  IN const UINT8 Offset
  );

/**
  Check if RTC date and time update is in progress and wait util it's finished.
  We have at least 244us when "update in progress bit" is seen as low to
  perform an operation on the RTC.

  @retval Zero on timeout or non-zero and RTC is ready for transaction.
**/
extern
UINT32
CheckUpdateComplete (
  void
  );

/**
  Initializes the RTC.

  @retval Nothing.
**/
extern
void
InitRtc (
  void
  );

/**
  Read specific RTC/CMOS RAM

  @param[in] Location        Point to RTC/CMOS RAM offset for read

  @retval The data of specific location in RTC/CMOS RAM.
**/
extern
UINT8
RtcRead (
  IN const UINT8 Location
  );

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
extern
void
GetRtcTime (
  OUT UINT8  *const Seconds,
  OUT UINT8  *const Minutes,
  OUT UINT8  *const Hours,
  OUT UINT8  *const DayOfMonth,
  OUT UINT8  *const Month,
  OUT UINT16 *const Year
  );

/**
  Write specific RTC/CMOS RAM

  @param[in] Location        Point to RTC/CMOS RAM offset for write
  @param[in] Value           The data that will be written to RTC/CMOS RAM
**/
extern
void
RtcWrite (
  IN const UINT8 Location,
  IN const UINT8 Value
  );

/**
  Read word from specific RTC/CMOS RAM

  @param[in] Location        Point to RTC/CMOS RAM offset for read

  @retval The data of specific location in RTC/CMOS RAM.
**/
extern
UINT16
RtcRead16 (
  IN const UINT8 Location
  );

/**
  Write word to specific RTC/CMOS RAM

  @param[in] Location        Point to RTC/CMOS RAM offset for write
  @param[in] Value           The data that will be written to RTC/CMOS RAM
**/
extern
void
RtcWrite16 (
  IN const UINT8   Location,
  IN const UINT16  Value
  );

/**
  Gets CPU ratio

  @param[in] Nothing

  @retval Cpu ratio.
**/
extern
UINT32
MrcGetCpuRatio (
  void
  );

/**
  Gets CPU current time.

  @param[in] Nothing

  @retval The current CPU time in milliseconds.
**/
extern
UINT64
GetCpuTime (
  void
  );

/**
  Gets CPU current time.

  @param[in] GlobalData - Pointer to global MRC data struct.

  @retval The current CPU time in milliseconds.
**/
UINT64
MrcOemGetCpuTimeMicroSec (
  IN VOID     *GlobalData
  );

/**
  Gets CPU current time.

  @param[in] GlobalData - Pointer to global MRC data struct.

  @retval The current CPU time in nanoseconds.
**/
UINT64
MrcOemGetCpuTimeNanoSec (
  IN VOID     *GlobalData
  );

/**
  Copy the specified number of memory bytes, a byte at a time, from the
  specified source to the specified destination.

  @param[in, out] Dest            - Destination pointer.
  @param[in]      Src             - Source pointer.
  @param[in]      NumBytes        - The number of bytes to copy.

  @retval Nothing.
**/
extern
void
MrcOemMemoryCpy (
  IN OUT UINT8 *Dest,
  IN UINT8     *Src,
  IN UINT32    NumBytes
  );

/**
  Sets the specified number of memory bytes, a byte at a time, at the
  specified destination.

  @param[in, out] Dest            - Destination pointer.
  @param[in]      Value           - The value to set.
  @param[in]      NumBytes        - The number of bytes to set.

  @retval Nothing.
**/
extern
void
MrcOemMemorySet (
  IN OUT UINT8 *Dest,
  IN UINT32    NumBytes,
  IN UINT32    Value
  );

/**
  Sets the specified number of memory dwords, a dword at a time, at the
  specified destination.

  @param[in, out] Dest            - Destination pointer.
  @param[in]      Value           - The value to set.
  @param[in]      NumWords        - The number of dwords to set.

  @retval Nothing.
**/
extern
void
SetMemWord (
  IN OUT UINT16    *Dest,
  IN UINT32        NumWords,
  IN const UINT16  Value
  );

/**
  Sets the specified number of memory dwords, a dword at a time, at the
  specified destination.

  @param[in, out] Dest            - Destination pointer.
  @param[in]      Value           - The value to set.
  @param[in]      NumDwords       - The number of dwords to set.

  @retval Nothing.
**/
extern
void
SetMemDword (
  IN OUT UINT32    *Dest,
  IN UINT32        NumDwords,
  IN const UINT32  Value
  );

/**
  Read 64 bits from the Memory Mapped I/O space.

  @param[in] Address - Memory mapped I/O address.

  @retval The 64 bit value read from the memory mapped I/O space.
**/
extern
UINT64
SaMmioRead64 (
  IN  UINT32 Address
  );

/**
  Shift the specified data value left by the specified count.

  @param[in] Data            - 64 bit number to shift left.
  @param[in] Count           - Number of bits to shift (0..63)

  @retval The number of bits shifted left.
**/
extern
UINT64
MrcOemMemoryLeftShiftU64 (
  IN const UINT64 Data,
  IN const UINT8  Count
  );

/**
  Shift the specified data value Right by the specified count..

  @param[in] Data            - UINT64 number to shift
  @param[in] Count           - number of bits to shift (0..63)

  @retval Returns the shifted UINT64 value.
**/
extern
UINT64
MrcOemMemoryRightShiftU64 (
  IN const UINT64 Data,
  IN const UINT8  Count
  );

/**
  this function Multiply UINT64 with a UINT32 number. Result is <= 64 bits
  need to be port for OEM platform requirements.

  @param[in] Multiplicand  - UINT64 number to be multiplied with
  @param[in] Multiplier - UINT32 number to multiply

  @retval N/A
**/
extern
UINT64
MrcOemMemoryMultiplyU64ByU32 (
  IN const UINT64 Multiplicand,
  IN const UINT32 Multiplier
  );

/**
  Divide UINT64 with a UINT64 number. Result is <= 32 bits

  @param[in] Dividend  - UINT64 number to be multiplied with
  @param[in] Divisor - UINT32 number to multiply

  @retval Returns the quotient result of UINT32 value.
**/
extern
UINT64
MrcOemMemoryDivideU64ByU64 (
  IN const UINT64 Dividend,
  IN const UINT64 Divisor
  );

/**
  Read 64 bits from the Memory Mapped I/O space.

  @param[in]  Offset      - Offset from the specified base address.

  @retval Nothing.
**/
extern
UINT64
MrcOemMmioRead64 (
  IN  UINT32 Address
  );

/**
  Read 32 bits from the Memory Mapped I/O space.

  @param[in]  Offset      - Offset from the specified base address.

  @retval Nothing.
**/
extern
UINT32
MrcOemMmioRead32 (
  IN  UINT32 Offset
  );

/**
  Read 16 bits from the Memory Mapped I/O space.

  @param[in]  Offset      - Offset from the specified base address.

  @retval Nothing.
**/
extern
UINT16
MrcOemMmioRead16 (
  IN  UINT32 Offset
  );

/**
  Read 8 bits from the Memory Mapped I/O space.

  @param[in]  Offset      - Offset from the specified base address.

  @retval Nothing.
**/
extern
UINT8
MrcOemMmioRead8 (
  IN  UINT32 Offset
  );

/**
  Write 64 bits to the Memory Mapped I/O space.

  @param[in] Offset      - Offset from the specified base address.
  @param[in] Value       - The value to write.

  @retval Nothing.
**/
extern
UINT64
MrcOemMmioWrite64 (
  IN UINT32 Address,
  IN UINT64 Value
  );

/**
  Write 32 bits to the Memory Mapped I/O space.

  @param[in] Offset      - Offset from the specified base address.
  @param[in] Value       - The value to write.

  @retval Nothing.
**/
extern
UINT32
MrcOemMmioWrite32 (
  IN UINT32 Offset,
  IN UINT32 Value
  );

/**
  Write 16 bits to the Memory Mapped I/O space.

  @param[in] Offset      - Offset from the specified base address.
  @param[in] Value       - The value to write.

  @retval Nothing.
**/
extern
UINT16
MrcOemMmioWrite16 (
  IN UINT32 Offset,
  IN UINT16 Value
  );

/**
  Write 8 bits to the Memory Mapped I/O space.

  @param[in] Offset      - Offset from the specified base address.
  @param[in] Value       - The value to write.

  @retval Nothing.
**/
extern
UINT8
MrcOemMmioWrite8 (
  IN UINT32 Offset,
  IN UINT8  Value
  );

/**
  Sets CpuModel and CpuStepping in MrcData based on CpuModelStep.

  @param[out] MrcData     - The Mrc Host data structure
  @param[in]  CpuModel    - The CPU Family Model.
  @param[in]  CpuStepping - The CPU Stepping.

  @retval - mrcSuccess if the model and stepping is found.  Otherwise mrcFail
**/
extern
MrcStatus
MrcSetCpuInformation (
  OUT MrcParameters  *MrcData,
  IN  MrcCpuModel    CpuModel,
  IN  MrcCpuStepping CpuStepping
  );

/**
  Generates a 32-bit random number.

  if Rand is NULL, then ASSERT().

  @param[out] Rand     Buffer pointer to store the 32-bit random value.

  @retval TRUE         Random number generated successfully.
  @retval FALSE        Failed to generate the random number.

**/
extern
BOOLEAN
GetRandomNumber32 (
  OUT     UINT32                    *Rand
  );

/**
  Read an MSR

  @param[in] Address

  @retval The MSR value.
**/
extern
UINT64
ReadMsr64 (
  UINT32 Address
  );

/**
  Write an MSR

  @param[in] Address
  @param[in] Data

  @retval Data written to MSR
**/
extern
UINT64
WriteMsr64 (
  UINT32 Address,
  UINT64 Data
  );

/**
  Initialize GPIO

  @param[in]  MrcData - Include all MRC global data
**/
void
MrcOemGpioInit (
  MrcParameters *const  MrcData
  );

/**
  Assert or deassert DRAM_RESET# pin; this is used in JEDEC Reset.

  @param[in] PciEBaseAddress  - PCI express base address.
  @param[in] ResetValue       - desired value of DRAM_RESET#. 1 - reset deasserted, 0 - reset asserted.
**/
void
MrcOemDramReset (
  UINT32 PciEBaseAddress,
  UINT32 ResetValue
  );

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
  );

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
  );

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
  );

/**
  Hook after normal mode is enabled

  @param[in] MrcData  - The MRC "global data" area.

  @retval Nothing.
**/
extern
void
MrcOemAfterNormalModeTestMenu (
  IN MrcParameters *MrcData
  );

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
  );

/**
  This function display on port 80 number.
  It can be different debug interface.
  This function can be use for any debug ability according to OEM requirements.

  @param[in] MrcData            - Mrc Global Data
  @param[in] DisplayDebugNumber - the number to display on port 80.

  @retval Nothing
**/
extern
void
MrcOemDebugHook (
  IN MrcParameters *MrcData,
  IN UINT16        DisplayDebugNumber
  );

#if (defined MEMORY_DOWN_SUPPORT && (MEMORY_DOWN_SUPPORT > 0))
extern
void
CopyMemoryDownSpd (
  IN OUT MrcParameters *const    MrcData,
  IN     const UINT8             *SpdIn[MAX_CONTROLLER][MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL],
  IN     const MemorySlotStatus  *Slot,
  IN     UINT16                  SpdSize
  );

/**
  Enables Memory Down support and sets SPD data for all DIMMs needing support.

  @param[in] MrcData    - MRC global data structure.
  @param[in] BoardId    - The ID of the board.
  @param[in] SpdPresent - SPD is present or memory is down.

  @retval Nothing
**/
extern
void
EnableMemoryDown (
  IN MrcParameters *const MrcData,
  IN const UINT16         BoardId,
  IN const BOOLEAN        SpdPresent
  );
#endif // MEMORY_DOWN_SUPPORT

/**
  Initialize the board-specific CMD/CTL/CLK and DQ/DQS mapping for LPDDR3.

  @param[in, out] MrcData - MRC global data structure.
  @param[in]      BoardId - The ID of the board.

**/
extern
void
MrcOemLpddrBoardMapping (
  IN MrcParameters *const MrcData,
  IN UINT16              BoardId
  );

/**
  Initialize the board-specific RCOMP values.

  @param[in, out] MrcData - MRC global data structure.
**/
void
MrcOemRcompValues (
  IN OUT MrcParameters *const MrcData
  );

/**
  Perform a byte read from the specified SMBus device address.

  @param[in] SmbusBaseAddress   - The SMBus base address.
  @param[in] SmBusDeviceAddress - SMBus device address to read from.
  @param[in] Offset             - Byte offset to read from.
  @param[out] Value             - Location to store read value.

  @retval: mrcSuccess if the read is successful, otherwise mrcFail and the read data is set to zero.
**/
extern
MrcStatus
MrcOemSmbusRead8 (
  IN const UINT32  SmbusBaseAddress,
  IN const UINT8   SmBusDeviceAddress,
  IN const UINT8   Offset,
  OUT UINT8 *const Value
  );

/**
  Perform a byte write to the specified SMBus device address.

  @param[in] SmbusBaseAddress   - The SMBus base address.
  @param[in] SmBusDeviceAddress - SMBus device address to write to.
  @param[in] Offset             - Byte offset to write to.
  @param[in] Value              - The value to write.

  @retval: mrcSuccess if the write is successful, otherwise mrcFail.
**/
extern
MrcStatus
MrcOemSmbusWrite8 (
  IN const UINT32  SmbusBaseAddress,
  IN const UINT8   SmBusDeviceAddress,
  IN const UINT8   Offset,
  IN UINT8         Value
  );

/**
  Perform a word read from the specified SMBus device address.

  @param[in] SmbusBaseAddress   - The SMBus base address.
  @param[in] SmBusDeviceAddress - SMBus device address to read from.
  @param[in] Offset             - Offset to read from.
  @param[out] Value             - Location to store read value.

  @retval:  mrcSuccess if the read is successful, otherwise mrcFail and the read data is set to zero.
**/
extern
MrcStatus
MrcOemSmbusRead16 (
  IN const UINT32   SmbusBaseAddress,
  IN const UINT8    SmBusDeviceAddress,
  IN const UINT8    Offset,
  OUT UINT16 *const Value
  );

/**
  Perform a word write to the specified SMBus device address.

  @param[in] SmbusBaseAddress   - The SMBus base address.
  @param[in] SmBusDeviceAddress - SMBus device address to write to.
  @param[in] Offset             - Offset to write to.
  @param[in] Value              - The value to write.

  @retval:  mrcSuccess if the write is successful, otherwise mrcFail.
**/
extern
MrcStatus
MrcOemSmbusWrite16 (
  IN const UINT32  SmbusBaseAddress,
  IN const UINT8   SmBusDeviceAddress,
  IN const UINT8   Offset,
  IN UINT16        Value
  );
/**
  Get the current PCH type.

  @retval PCH_GENERATION, see PchInfoLib.h
**/
PCH_GENERATION
MrcGetPchGeneration (
  void
  );

/**
  Get the current PCH Series.

  @retval PCH_SERIES, see PchInfoLib.h
**/
PCH_SERIES
MrcGetPchSeries (
  void
  );
/*
  Check on the processor if PRMRR is supported.

  @param[in]  Size  - PRMRR size requested in MB.  Must be natural size (2^x).

  @retval Size in MB.  0 if unsupported.
*/
UINT32
MrcCheckPrmrrSupport (
  MrcParameters *MrcData,
  UINT32        PrmrrSize
  );

/*
  This function will set and lock Core PRMRR which is required to be locked before enabling normal mode
  for memory.

  @param[in]  PrmrrBase - Base address of PRMRR range.  Must be naturally algined
  @param[in]  PrmrrSize - Size of the PRMRR range in Bytes
*/
VOID
MrcSetCorePrmrr (
  IN UINT64 PrmrrBase,
  IN UINT32 PrmrrSize
  );

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
  );

/**
  Set a GPIO value to indicate "End of BIOS POST" to BMC on a UP server board (Zumba Beach).

**/
VOID
MrcUpServerSendEndOfPost (
  VOID
  );

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
  );

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
  );

/**
  This function checks to see if the MrcSave was saved.

  @param[in, out] MrcData - MRC global data structure.

  @retval BOOLEAN - TRUE if MrcSave exists, otherwise FALSE.
**/
BOOLEAN
MrcSaveExists (
  IN OUT MrcParameters *const MrcData
  );

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
  );

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
  );

UINT32
MmioRead32 (
  IN      UINTN                     Address
  );

UINT32
MmioWrite32 (
  IN      UINTN                     Address,
  IN      UINT32                    Value
  );

UINT32
MmioOr32 (
  IN      UINTN                     Address,
  IN      UINT32                    OrData
  );

UINT32
MmioAndThenOr32 (
  IN      UINTN                     Address,
  IN      UINT32                    AndData,
  IN      UINT32                    OrData
  );

UINT16
MmioRead16 (
  IN      UINTN                     Address
  );

UINT16
MmioWrite16 (
  IN      UINTN                     Address,
  IN      UINT16                    Value
  );

UINT16
MmioOr16 (
  IN      UINTN                     Address,
  IN      UINT16                    OrData
  );


UINT16
MmioAndThenOr16 (
  IN      UINTN                     Address,
  IN      UINT16                    AndData,
  IN      UINT16                    OrData
  );

UINT8
MmioRead8 (
  IN      UINTN                     Address
  );

UINT8
MmioWrite8 (
  IN      UINTN                     Address,
  IN      UINT8                     Value
  );

VOID
ZeroMem (
  OUT VOID *Buffer,
  IN  UINTN  Length
  );

#endif // _MrcOemPlatform_h_

