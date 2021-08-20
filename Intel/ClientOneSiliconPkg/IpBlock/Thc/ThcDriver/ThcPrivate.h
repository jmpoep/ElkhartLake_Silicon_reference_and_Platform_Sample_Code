/**@file
  Private Header file for Touch Host Controller Driver

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#ifndef _THC_PRIVATE_H_
#define _THC_PRIVATE_H_

#include <Uefi.h>
#include <PiDxe.h>

//
// Libraries
//
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/TimerLib.h>
//
// UEFI Driver Model Protocols
//
#include <Protocol/DriverBinding.h>
#include <Protocol/DriverSupportedEfiVersion.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/ComponentName.h>
#include <Protocol/PciIo.h>
//
// Produced Protocols
//
#include <Protocol/AbsolutePointer.h>
#include <Protocol/Thc.h>
//
// Guid
//
#include <Guid/EventGroup.h>
#include <Guid/EventLegacyBios.h>

//
// Registers
//
#include <Register/ThcRegs.h>
#include <Register/ThcRegsVer1.h>
//
// Other
//
#include <IndustryStandard/Pci30.h>

//#define THC_STANDALONE_DEBUG  0 // Required for stand alone driver Debug
#if THC_STANDALONE_DEBUG
#define THC_LOCAL_DEBUG_HELPER(Message, ...)  printf ((char *) Message, __VA_ARGS__);
#define THC_LOCAL_DEBUG(...)  THC_LOCAL_DEBUG_HELPER(__VA_ARGS__, 0)
#else
#define THC_LOCAL_DEBUG(Message, ...)
#endif

#define USE_EDGE_INTERRUPTS  TRUE  //@todo move to Pcd, once confirmed working on Si
#define THC_POLLING_PERIOD   1     // milliseconds

#define TOUCH_DRIVER_VERSION  0x00000001

//
// Protocol instances
//
extern EFI_DRIVER_BINDING_PROTOCOL  gThcDriverBinding;
extern EFI_COMPONENT_NAME_PROTOCOL  gThcDriverComponentName;
extern EFI_COMPONENT_NAME2_PROTOCOL gThcDriverComponentName2;
extern EFI_GUID                     gEfiTouchPanelGuid;

#define THC_SIGNATURE  0x54484344 //"THCD" Touch Host Controller Device
#define THC_CONTEXT_FROM_THC_PROTOCOL(a)      CR (a, THC_DEV, ThcProtocol, THC_SIGNATURE)
#define THC_CONTEXT_FROM_ABSPTR_PROTOCOL(a)   CR (a, THC_DEV, AbsPtrProtocol, THC_SIGNATURE)

#define SIZE_FIELD_RESOLUTION      64
#define PRD_MAX_ENTRIES            256
#define PRD_READ_TABLES_SUPPORTED  16
#define PRD_MAX_TABLES_SUPPORTED   PRD_READ_TABLES_SUPPORTED
#define PRD_WRITE_TABLES_SUPPORTED 1
#define POINTER_MASK               0x7F
#define POINTER_WRAPAROUND         0x80
#define WRAPAROUND_VALUE_16        16
#define WRAPAROUND_VALUE_0X90      0x90
#define ADDRESS_SHIFT              10 // right shift destination Address
#define SINGLE_FINGER_REPORT_ID    0x40


#pragma pack(push, 1) //ask compiler not to align struct

typedef enum {
  TouchReadDataTypeProprietary = 0,
  TouchReadDataTypeReserved0   = 1, // Value reserved
  TouchReadDataTypeReserved1   = 2, // Value reserved
  TouchReadDataTypeHidReport   = 3,
  TouchReadDataTypeGetFeatures = 4,
  TouchReadDataTypeTctlRsp     = 5, // When set, readData contains TouchIoctlStruct
  TouchReadDataTypeHidReports  = 6,
  TouchReadDataTypeMax         = 7
} TOUCH_READ_DATA_TYPE;

typedef struct  {
  UINT32 DataType;     // This must be a value from ReadDataTypes.
  /**
  The size in bytes of the readData, not including the
  size of ReadDataHdr. Will be the sum of all uFrames.
  Size of 0 is not allowed.
  **/
  UINT32 ReadDataSize;
  UINT32 Reserved;     // This field is deprecated and no longer used. Previously was BufferId.
  UINT32 ProtocolVer;  // Must match protocol version for this EDS
  UINT8  KernelCompatibilityID; // Must match TOUCH_COMPATIBILITY_ID reg field.
  UINT8  Reserved1[15]; // Padding for future growth.
  UINT32 TransactionId; // Number incremented for each new data Frame.
  UINT8  Reserved2[28]; // Padding for future growth.
} RAW_DATA_HEADER;

typedef struct {
  RAW_DATA_HEADER Header;
  /**
  This data can be vendor specific if DataType is
  TouchReadDataTypeProprietary. If DataType is
  TouchReadDataTypeHidReport, ReadData must match the
  SingleFingerReport structure defined in this EDS, or other
  defined HID report.
  This element is defined as a 1 byte array to allow it to
  compile in many environments. In reality, the size of the
  array will be ReadDataHdr.ReadDataSize.
  **/
  UINT8 ReadData[1];
} READ_DATA_BUFF;

//
// Lower Right Corner X,Y Coordinates will be (32767, 32767) and Top
// left corner will be (0,0)
//
typedef struct {
  UINT8 ReportId;    // Always 0x40.
  UINT8 TouchSts;    // Bit 0: 0 - No Touch, 1 - Touch. Bits 1-7 are ignored.
  UINT8 LowerXByte;  // Lower Byte value of X Coordinate. The Max of X coordinate will be 32767.
  UINT8 HigherXByte; // Higher Byte value of X Coordinate.
  UINT8 LowerYByte;  // Lower Byte value of Y Coordinate. The Max of Y coordinate will be 32767.
  UINT8 HigherYByte; // Higher Byte value of Y Coordinate.
} SINGLE_FINGER_REPORT;

typedef union {
  struct {
    UINT32 MaximumReadSize  : 14; // RO
    UINT32 MaximumWriteSize : 10; // RO
    UINT32 Reserved         : 8;  // RO
  } Fields;
  UINT32 Data;
} TOUCH_DATA_SIZE;

typedef union {
  struct {
    UINT32 TouchEnable                : 1;  // RW
    UINT32 ProprietaryDataModeEnabled : 1;  // RW
    UINT32 HidReportModeEnabled       : 1;  // RW
    UINT32 PowerState                 : 3;  // RW
    UINT32 Reserved                   : 26; // RO
  } Fields;
  UINT32 Data;
} TOUCH_CONFIG;

typedef union {
  struct {
    UINT32 TouchEnable                  : 1;  // RO
    UINT32 ProprietaryDataModeEnabled   : 1;  // RO
    UINT32 HidReportModeEnabled         : 1;  // RO
    UINT32 PowerState                   : 3;  // RO
    UINT32 Reserved                     : 26; // RO
  } Fields;
  UINT32 Data;
} TOUCH_STATE;

typedef union {
  struct {
    UINT32 ProprietaryDataModeSupported : 1; // RO
    UINT32 MaxSpiFrequencySupported     : 4; // RO
    UINT32 SingleIoSupported            : 1; // RO
    UINT32 DualIoSupported              : 1; // RO
    UINT32 QuadIoSupported              : 1; // RO
    UINT32 MaximumTouchPoints           : 8; // RO
    UINT32 MaximumResetTime             : 4; // RO
    UINT32 HeartBeatReportSupported     : 1; // RO
    UINT32 Reserved                     : 7; // RO
    UINT32 PerformanceLimitation        : 3; // RO
    UINT32 PrepForRegisterRead          : 1; // RO
  } Fields;
  UINT32 Data;
} TOUCH_CAPABILITIES;

typedef union {
  struct {
    UINT32 EdsMinorVersion              : 8; // RO
    UINT32 EdsMajorVersion              : 8; // RO
    UINT32 InterfaceRevisionNumber      : 8; // RO
    UINT32 EuKernelCompatibilityVersion : 8; // RO
  } Fields;
  UINT32 Data;
} TOUCH_COMPATIBILITY_ID;

typedef struct {
  UINT32                  TouchIntCause;        // Touch Interrupt Cause 0x0
  UINT32                  TouchErr;             // Touch Error 0x4
  TOUCH_DATA_SIZE         TouchDataSize;        // Touch Data Size 0x8
  TOUCH_CONFIG            TouchCfg;             // Touch Configuration 0xC
  TOUCH_STATE             TouchState;           // Touch Configuration 0x10
  UINT32                  TouchId;              // Touch ID 0x14
  TOUCH_CAPABILITIES      TouchCapabilities;    // Touch Capabilities 0x18
  UINT32                  TouchIcHwId;          // Touch IC HW ID 0x1C
  UINT32                  TouchIcHwRev;         // Touch IC HW Revision 0x20
  UINT32                  TouchIcFwRev;         // Touch IC FW Revision 0x24
  UINT32                  TouchCommand;         // Reserved Registers 0x28
  UINT32                  TouchInit;            // Reserved Registers 0x2C
  UINT32                  Reserved[1];          // Reserved Registers 0x30
  TOUCH_COMPATIBILITY_ID  TouchCompatibilityId; // Touch Compatibility ID 0x34
  UINT32                  Reserved2[2];         // Reserved Registers 0x38
} THC_DEVICE_REGISTERS;

typedef union {
  struct {
    UINT32 TssGo      : 1;  // THC SW Sequence Cycle Go  RW/1S/V
    UINT32 ThcSsCdIe  : 1;  // THC SW Sequencing Cycle Done Interrupt Enable  RW
    UINT32 ThcSsBtaEn : 1;  // THC SW Sequencing Bus Turnaround Enable  RW, In SPI mode, this bit is not used.
    UINT32 Rsvd0      : 1;  // RSVD  RO
    UINT32 TsiSsPType : 1;  // TSI SW Sequencing Bus Packet Type  RW, In SPI mode, this bit is not used.
    UINT32 ThcSsTrCt  : 1;  // THC SW Sequencing Command Type  RW
    UINT32 Rsvd1      : 2;  // RSVD  RO
    UINT32 ThcSsCmd   : 8;  // THC SW Sequencing Bus Command  RW
    UINT32 ThcSsBc    : 16; // THC SW Sequencing Bus Word Byte Count  RW
  } Fields;
  UINT32 Data;
} THC_M_PRT_SW_SEQ_CNTRL;

typedef union {
  struct {
    UINT32 Pcd        : 7;  // RW CB Depth for the 2nd RXDMA
    UINT32 Rsvd0      : 1;  // RO RSVD
    UINT32 Ptec       : 8;  // RW Table Entry Count for the 2nd RXDMA
    UINT32 PreFetchWm : 4;  // RW PRD prefetch Watermark for the 2nd RXDMA
    UINT32 Rsvd1      : 12; // RO Reserved
  } Fields;
  UINT32 Data;
} THC_M_PRT_RPRD_CNTRL_2;

typedef union {
  struct {
    UINT32 Start                : 1; // RW/V Start for the 2nd RXDMA
    UINT32 IeError              : 1; // RW Interrupt Enable on Error for the 2nd RXDMA
    UINT32 IeIoC                : 1; // RW Interrupt Enable on Completion for the 2nd RXDMA
    UINT32 IeStall              : 1; // RW Interrupt Enable on Stall for the 2nd RXDMA
    UINT32 Rsvd0                : 1; // RO RSVD
    UINT32 IeEof                : 1; // RW Interrupt Enable at EOF for the 2nd RXDMA
    UINT32 Rsvd1                : 1; // RO RSVD
    UINT32 IeDmaCpl             : 1; // RW Interrupt Enable on DMA Completion for the 2nd RXDMA
    UINT32 ThcPrdCbReadPointer  : 8; // RO/V THC PRD CB Read Pointer for the 2nd RXDMA
    UINT32 ThcPrdCbWritePointer : 8; // RW/V THC PRD CB Write Pointer for the 2nd RXDMA
    UINT32 Rsvd2                : 4; // RO Reserved
    UINT32 IntSwDmaEn           : 1; // RW/L Interrupt SW Enable on DMA Device Interrupt for the 2nd RXDMA
    UINT32 StopOverFlow         : 1; // RW Stop on Overflow for the 2nd RXDMA
    UINT32 UpdateHwStatus       : 1; // RO Update HwStatus for the 2nd RXDMA
    UINT32 ThcPrdCbPointerReset : 1; // RW/1S/V THC PRD CB Pointer Reset for the 2nd RXDMA
  } Fields;
  UINT32 Data;
} THC_M_PRT_READ_DMA_CNTRL_2;

typedef union {
  struct {
    UINT32 ThcWrDmaStart      : 1;  // RW/V Start WRDMA
    UINT32 ThcWrDmaIeIocError : 1;  // RW Interrupt Enable on Error for WRDMA
    UINT32 ThcWrDmaIeIoc      : 1;  // RW Interrupt Enable on IOC for WRDMA
    UINT32 ThcWrDmaIeDmaCpl   : 1;  // RW Interrupt Enable on WRDMA Completion
    UINT32 Rsvd0              : 19; // RO RSVD
    UINT32 ThcWrDmaUhs        : 1;  // RO Update HW Status for WRDMA
    UINT32 ThcWrDmaPtec       : 8;  // RW PRD Table Entry Count for WRDMA
  } Fields;
  UINT32 Data;
} THC_M_PRT_WRITE_DMA_CNTRL;

//128bit - 16 bytes
typedef struct {
  /**
  This field indicates the destination of the DMA in 64 bit host memory, Hardware supports a
  minimum alignment of 1KB. Software may choose a different fragmentation, so long as it is
  greater than 1KB (ex: 4KB).
  **/
  UINT64  DestinationAddress    : 54; //53:0
  UINT64  Reserved1             : 9;  //54:62
  UINT64  InterruptOnCompletion : 1;  //63
  /**
  The length of the DMA for this PRD Entry must be byte aligned with a maximum transfer length of 16MB-1.
  HW updates this field when the data corresponding to this entry is received. The length field is 1-
  based. Value 1 means 1 byte. Zero length PRD entry is not valid. A PRD entry's length must be
  multiple of 4KBytes except for the last entry in a PRD table. The last entry can be any size from 1
  Byte to 1M-1 Bytes.
  **/
  UINT64  Length                : 24; //87:64
  /**
  End of PRD (EOP)
  This bit indicates that this PRD entry is the final entry in the PRD table.
  It is updated by HW when it receives the last packet of a frame.
  **/
  UINT64  EndOfPrd              : 1;  //88
  /**
  HW Status: These bits are set by HW if the UHS bit is set after completing a PRD. It is cleared by
  SW after being consumed.
  Values:
  0: SW Reset Value
  1: Completed Successfully. This bit is set in the first PRD Entry with the EOP bit set upon successful
  PRD table completion.
  2: Completed with error. This bit is set in the PRD Entry where an error occurs such that the read
  DMA stops processing PRD entries.
  3: Rx Buffer overflow before this frame is received. There could be multiple frames got dropped
  before this status is set.
  **/
  UINT64  HwStatus              : 2;  //90:89
  UINT64  Reserved2             : 37; //127:91
} PRD_ENTRY;

typedef struct {
  PRD_ENTRY Entries[PRD_MAX_ENTRIES];
} PRD_TABLE;

typedef struct {
  EFI_PHYSICAL_ADDRESS    Buffer;
  EFI_PHYSICAL_ADDRESS    DevAddr;
  VOID                    *Mapping;
  PRD_ENTRY               Entries[PRD_MAX_ENTRIES];
  UINT32                  NumOfConfiguredEntries;
} DRIVER_PRD_TABLE;

typedef struct {
  EFI_PHYSICAL_ADDRESS    CommonPrdBuffer;
  EFI_PHYSICAL_ADDRESS    CommonPrdBufferDevAddr;
  VOID                    *CommonPrdBufferMapping;
  DRIVER_PRD_TABLE        DriverPrdTable[PRD_MAX_TABLES_SUPPORTED];
  UINT32                  NumOfPrdTables;
  UINT32                  BufferSize;
} THC_DMA;

typedef struct {
  UINT32 WriteDataType; // This refers to the enumerated type above
  /**
    This field designates the amount of data  to follow the header
    The WriteDataLen should result in a DWORD alignment.
  **/
  UINT32 WriteDataLength;
  //UINT8  WriteData[1];
} THC_WRITE_DATA_HDR;

//
// This data structure describes the header prepended to all data written to the
// Touch IC at the bulk data write (0x1000 + SPI_OFFSET [from the feedback buffer])
//
typedef enum {
  FW_STAGE1_LOAD       = 0,
  FW_STAGE2_LOAD       = 1,
  FEEDBACK_DATA        = 2,
  SET_FEATURES_DATA    = 3,
  GET_FEATURES_DATA    = 4,
  OUTPUT_REPORT_DATA   = 5,
  DATA_LOAD            = 6,
  TCTL_REQUEST         = 7,
  IMAGE_NOT_AVAILABLE  = 8,
  MAX_WRITE_DATA_TYPES = 9
} THC_WRITE_DATA_TYPE;

typedef enum {
  ThcFreqLow2p1MHz  = 0,
  ThcFreqLow2p5MHz  = 1,
  ThcFreqLow3MHz    = 2,
  ThcFreqLow3p75MHz = 3,
  ThcFreqLow5MHz    = 4,
  ThcFreqLow7p5MHz  = 5,
  ThcFreqLow15MHz   = 6,
  ThcFreqHigh17MHz  = 7,
  ThcFreqHigh20MHz  = 8,
  ThcFreqHigh24MHz  = 9,
  ThcFreqHigh30MHz  = 10,
  ThcFreqInvalid
} THC_PORT_FREQUENCY;

typedef enum {
  ThcEdsFreq7p812MHz  = 0xA, // 1010b
  ThcEdsFreq15p62MHz  = 0x9, // 1001b
  ThcEdsFreq17p86MHz  = 0x7, // 0111b
  ThcEdsFreq20p83MHz  = 0x6, // 0110b
  ThcEdsFreq25MHz     = 0x5, // 0101b
  ThcEdsFreq31p25MHz  = 0x4  // 0100b
} THC_EDS_FREQUENCY;

typedef enum {
  NoInterruptPending = 0,
  ReadDataAvailable  = 1, // - indicates data is ready to be read.
  ResetOccurred      = 2, // - indicates a reset occurred.
  ErrorOccurred      = 3, // - indicates an error occurred.
  ConfigChange       = 4  // - indicates the value of the TOUCH_CONFIG register has changed by the Touch IC.
} THC_INTERRUPT_TYPE;

typedef enum {
  IoReadyTimeout      = 100,
  StartQuiesceTimeout = 300,
  EndQuiesceTimeout   = 700,
  OutOfResetTimeout   = 300,
  WaitForResetTimeout = 750,
  CycleTimeout        = 1000,
  WritePollingTimeout = 100,
  PollingLoopTimeout  = 100000 // MicroSeconds
} THC_TIMERS;

typedef enum {
  ThcPioRead  = 0x4,
  ThcPioWrite = 0x6
} PIO_OP;

#pragma pack(pop)

typedef struct {
  UINTN                          Signature;
  EFI_HANDLE                     ControllerHandle;
  EFI_UNICODE_STRING_TABLE       *ControllerNameTable;
  EFI_PCI_IO_PROTOCOL            *PciIo;
  UINT64                         PciAttributes;
  UINT64                         PciBar0;
  UINT8                          PciPwrst;
  THC_DEVICE_REGISTERS           DeviceRegisters;
  THC_DMA                        DmaRead2; // Only RxDma2 used in HID AbsPtrMode
  THC_DMA                        DmaWrite;
  THC_PROTOCOL                   ThcProtocol;
  EFI_ABSOLUTE_POINTER_PROTOCOL  AbsPtrProtocol;
  EFI_ABSOLUTE_POINTER_MODE      AbsPtrMode;
  EFI_ABSOLUTE_POINTER_STATE     AbsPtrTouchData;
  BOOLEAN                        AbsPtrDataAvailable;
  UINT8                          *HidBuffer;
  BOOLEAN                        HidActive;
  BOOLEAN                        HidDataAvailable;
  EFI_EVENT                      PollingEvent;
  EFI_EVENT                      ExitEvent;
  SINGLE_FINGER_REPORT           Report;
  BOOLEAN                        ReadDone;
  BOOLEAN                        Initialized;
} THC_DEV;

#endif
