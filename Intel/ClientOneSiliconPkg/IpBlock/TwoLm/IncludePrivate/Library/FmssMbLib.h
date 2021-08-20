/** @file
  Header file for Far Memory Sub System Mailbox Interface Lib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#ifndef FMSS_MB_LIB_H_
#define FMSS_MB_LIB_H_

#include <Uefi.h>

#define MB_TIMEOUT      1000  // 1000 micro seconds (1ms)
#define MB_TIMEINTERVAL 100  // 100 micro seconds
#define SET_BIT_HIGH    1
#define BIOS_FW         1 // If this command originated from platform BIOS/FW then the bit shall be set to "1"
#define MAX_REGIONS     4 // Consider max number of regions in 3DXP device as 4
#define HOST_OS         0



/* FM Mailbox Response Phase (FRSP) struct */
typedef union {
  struct {
    UINT32 FmTransactionStatus  : 3;
    /* FmTransactionStatus (FTS)  - Bits[02:00], RW, default = 0b
     * FTS contains the most recently received completion status[02:00] field
     * (Cpl, CplD, Write_GO VDM or Register Response VDM) associated with the
     * transaction initiated by the RUN_BSY bit.
     * Register Response VDM status for BIOS
     */

    UINT32 Rsvd : 29;
    /* Rsvd - Bits[31:03], RO, default = 0
     */
  } Bits;
  UINT32 Data;
} FRSP_FMHC_MAILBOX_STRUCT;


/* FM Mailbox Request Control (FRQC) struct */
typedef union {
  struct {
    UINT32 Command  : 4; //can be sub divided in 3:0 and 7:4
    /* Command   - Bits[07:00], RW, default = 0b
     * (encoding for VDM or MRd/MWr)
     * 04h = register read request VDM
     * 05h = register write request VDM
     */

    UINT32 Rsvd : 27;
    /* Rsvd - Bit[30:08], RO, default = 0
     */

    UINT32 RunBusy  : 1;
    /* RUN_BSY   - Bit[31], RW, default = 0b
     * BIOS may write to the FMHC MMIO mailbox registers (FRQC,FRPA, FHD)
     * only when RUN_BUSY is cleared to "0".After BIOS programs FRPA and/or FHD
     * (if it involves data transfer to Device), BIOS can initiate a transaction
     * by setting this bit to "1". This bit is automatically cleared to "0" when:
     * - the corresponding transaction has been completed, or
     * - after an unsupported command has been dropped (refer to FRPA)
     */

  } Bits;
  UINT32 Data;
} FRQC_FMHC_MAILBOX_STRUCT;


/* FM Mailbox Request Phase Attribute (FRPA) struct */
typedef union {
  struct {
    UINT64 FRP_VendorID  : 16; /* Vendor ID of 3DXP device, 0x8086 */
    UINT64 FRP_BDF : 16;       /* BDF of 3DXP device mem func, 0/3/7 */
    UINT64 FRP_VendorMessage : 8;
    /* FRP[39:32] = Vendor Message[7:0] for Register access VDM
     * Vendor Message = 1101_0100 // For read
     * Vendor Message = 1101_0011 // For write
     */
    UINT64 FRP_DW_BE : 4;
    /* FRP[43:40] = DW BE[03:00] for Register access VDM */
    UINT64 FRP_VDMReserved0 : 7;
    UINT64 FRP_VDMRW : 1; /* VDM 1b for write, 0b for read */
    UINT64 FRP_VDMReserved1 : 3;
    UINT64 FRP_VDMReserved2 : 9;
 } Bits;
  UINT64 Data;
} FRPA_FMHC_MAILBOX_STRUCT;


/* FM Mailbox Host Initiated Data Phase Index Data (FHD) struct */
typedef union {
  struct {
    UINT64 Rsvd : 16;
    UINT64 RegOffsetHigh : 8; /* FHD[23:16] = Register offset of 14:8 with Bit[15] always 0*/
    UINT64 RegOffsetLow :  8; /* FHD[31:24] = Register offset of 7:2 with Bit[1:0] always 0*/
    UINT64 RegisterWritePayload : 32; /* FHD[63:32] = Value to be written to VDM register in case of VDM write. Ignored for VDM read*/
  } Bits;
  UINT64 Data;
} FHD_FMHC_MAILBOX_STRUCT;


/* FM Mailbox Device-Data Index Data (FDD) struct */
// 1DW register write data and/or Offset[11:02] of register read/write request VDM

typedef union {
  struct {
    UINT32 FmMailboxDeviceDataIndexData : 32;

    /*1DW data from register response with data VDM (for register read)
     * BIOS should not read this register until the FRQC.RUN_BSY becomes "0" in order to
     * prevent the register read completion from being withheld by FMHC until
     * the associated Mailbox transaction has been completed.
     */
  } Bits;
  UINT32 Data;
} FDD_FMHC_MAILBOX_STRUCT;


/* FM Mailbox Pointers Control (FMPTRC) struct */
typedef union {
  struct {
    UINT64 CurrentWritePointerValue  : 5;
    /* WPTRV  - Bits[04:00], RW, default = 0b
     * QW-based pointer pointer value of of FHD_U_PCR. Firmware can read this
     * field to know the current position.
     * Firmware can write to this field to change the position.
     */

    UINT64 Rsvd0  : 3;
    /* Reserved  - Bits[07:05], RO, default = 0b
     */

    UINT64 CurrentReadPointerPositionValue : 5;
    /* RPTRV - Bits[12:08], RW, default = 0
     * QW-based pointer pointer value of FDD_U_PCR. Firmware can read this
     * field to know the current position. Firmware can write to this field
     * to change the position.
     */

    UINT64 Rsvd  : 51;
    /* Reserved  - Bits[63:13], RO, default = 0b
     */

  } Bits;
  UINT64 Data;
} FMPTRC_FMHC_MAILBOX_STRUCT;



typedef enum {
  Successful,
  Error
} FM_TRANSACTION_STATUS;


//
//*****************************************************
// 3DXP VDM Registers structures for Mailbox Interface
//*****************************************************
//

// Lower Mailbox Command Register (MBCMD0) struct
typedef union {
  struct {
    UINT32 TT      : 2;  // Bits[1:0]Transfer Type, 00=Initiate Transfer, 01=Continue Transfer, 10 = End Transfer
    UINT32 Rsvd    : 14; // Bits[15:2] Reserved
    UINT32 Packet  : 16; // Bits[31:16] The number of the data packet. Allows for a maximum image size of 32MB (65536 packets at 512bytes each)
  } Bits_Type1;
  struct {
    UINT32 LabelCmdRegionId  : 6;  // Bits[5:0] Region the Label command is targeted.
    UINT32 Rsvd              :26;  // Bits[31:6] Reserved
  } Bits_Type2;
  struct {
    UINT32 PageOffset        : 5;  // Bits[4:0] Page offset in case of Command Effect Log command
    UINT32 Rsvd              :27;  // Bits[31:6] Reserved
  } Bits_Type3;
  UINT32 Data;
} MBCMD0_FMSS_MAILBOX_STRUCT;


// Upper Mailbox Command1 Register(MBCMD1) struct
typedef union {
  struct {
    UINT32 FwMbOpcode  : 8;
    /* [39:32] FW MB Opcode for executing command.
     */
    UINT32 FwMbSubOpcode  : 8;
    /* [47:40] FW MB Opcode for executing command.
     */
    UINT32 DB  : 1;
    /* [48] DB: Doorbell, set by host to indicate that all inputs are opcodes
     * are ready and command can be started
     */
    UINT32 BH_MB_Type  : 1;
    /* [49] B/H MB Type: Command origin
     * BIOS/HOST Mailbox Type (B/H MB Type) bit indicates where the command
     * originated.  If this command originated from platform BIOS/FW then this
     * bit shall be set to "1".  If cleared to "0" then the command originated
     * from the HOST/OS.  Certain opcodes are only allowed to be processed if
     * originated from platform BIOS/FW.
     */
    UINT32 AllRegions  : 1;
    /* Bit[50] - Query All
     * when 1 the entire region table shall be reported through the outbox buffer.
     * Each query region shall consist of 8-byte data in the outbox buffer.
     * Thus host must read (M x 8) bytes from outbox if M regions are reported.
     * When 0, the device FW shall report the 8-byte data in outbox buffer based
     * on the region ID defined by bit[63:56]
     * OR
     * Bit[50] - Delete all regions. When set, all the regions that have been created shall be deleted.
     * OR
     * Bit[50] - Clear all regions. When set, all the regions that have been created shall be cleared.
     */
    UINT32 SecureErase : 1; // Used only for Format Region Command
    /* Bit[51] - Secure Erase: When 1, device shall write all zeroes to the region(s) affected
     */
    UINT32 Rsvd1  : 4;
    /* [55:51] - Reserved
     */
    UINT32 RegionId  : 6;
        /* [61:56] - Region ID
         * This field indicate which region to be queried. This bit is only valid when bit[50] is set to 0
         */
    UINT32 Rsvd2  : 2;
    /* [63:62] - Reserved */
  } Bits;
  UINT32 Data;
} MBCMD1_FMSS_MAILBOX_STRUCT;


// Lower Nonce Register (MBNCE0) struct
typedef union {
  struct {
    UINT32 Lower  : 32;
  } Bits;
  UINT32 Data;
} MBNCE0_FMSS_MAILBOX_STRUCT;


// Upper Nonce Register (MBNCE1) struct
typedef union {
  struct {
    UINT32 Upper  : 32;
  } Bits;
  UINT32 Data;
} MBNCE1_FMSS_MAILBOX_STRUCT;


// Lower Status Register (MBSTS0) struct
typedef union {
  struct {
    UINT32 MbComp  : 1;
    /* Mailbox completion bit; set when the command is completed
     */
    UINT32 NonceFb  : 1;
    /* The Nonce Fail Bit is only set for BIOS mailbox commands when the Nonce
     * fails to verify correctly, after nonce is set by platform BIOS/FW.
     */
    UINT32 Bos  : 1;
    /* background Operation State; this bit signifies that there is a background
     * / long operation in progress.
     */
    UINT32 Rsvd0  : 5;
    /* Reserved
     */
    UINT32 FwMbStatusCode  : 8;
    /* Table 5: Mailbox Return Codes
     */
    UINT32 Rsvd1  : 16;
    /* Reserved
     */
  } Bits;
  UINT32 Data;
} MBSTS0_FMSS_MAILBOX_STRUCT;


// Upper Status Register (MBSTS1) struct
typedef union {
  struct {
    UINT32 Lower  : 32;
  } Bits;
  UINT32 Data;
} MBSTS1_FMSS_MAILBOX_STRUCT;


//
// Enum for Mailbox Command Return status
//
typedef enum {
  MB_SUCCESS      = 0x0,
  InvalidCommandParameter = 0x1,
  DataTransferError    = 0x2,
  InternalDeviceError   = 0x3,
  UnsupportedCommand =  0x4,
  DeviceBusy    = 0x5,
  IncorrectPassphraseOrSecurityNonce =  0x6,
  FWAuthenticationFailed  = 0x7,
  InvalidSecurityState  = 0x8,
  SystemTimeNotSet  = 0x9,
  DataNotSet        = 0xA,
  Aborted           = 0xB,
} MAILBOX_RETURN_STATUS ;


//
// Enum for Buffer type required by the MB command
//
typedef enum {
  NONE   = 0,
  INBOX  = 1,
  OUTBOX = 2
} REQUIRED_BUFFER;


//
// Enum for Mailbox command Opcodes
//
typedef enum {
  NOOP                    = 0x0,
  Identify2lmModule       = 0x1,
  GetSecurityInfo         = 0x2,
  SetSecurityInfo         = 0x3,
  GetFeatures             = 0x4,
  SetFeatures             = 0x5,
  GetAdminFeatures        = 0x6,
  SetAdminFeatures        = 0x7,
  GetLogPage              = 0x8,
  UpdateFirmware          = 0x9,
  InjectError             = 0xA,
  LabelData               = 0xB,
  RegionProvision         = 0xC,
  SetLogPage              = 0xD,
  EmulatedBiosCommands    = 0xFD,
  VendorSpecificCommands  = 0xFF
} MAILBOX_MAINCMD_OPCODES;


//
// Enum for Identify 2LM MODULE Device Sub command Opcodes
//
typedef enum {
  Identify  = 0x0,
  DeviceCharacteristics = 0x1,
} IDENTIFY2LMMODULE_SUBCMD_OPCODES;


//
// Enum for SetSecurityInfo Sub command Opcodes
//
typedef enum {
  SetBiosSecurityNonce = 0x0,
  OverwriteDimm   = 0x1,
} SETSECURITYINFO_SUBCMD_OPCODES;

//
// Enum for Admin Features Sub command Opcodes
//
typedef enum {
  SystemTime = 0x0,
  PlatformConfigData = 0x1,
  ConfigLockdown = 0x5,
  LatchSystemShutdownState = 0x9,
} ADMINFEATURES_SUBCMD_OPCODES;


//
// Enum for Set and Get Log Page Sub command Opcodes (Reference Client FIS_v0.80)
//
typedef enum {
  SmartAndHealthInfo            = 0x0,
  FirmwareImageInfo             = 0x1,
  SmartThresholds               = 0x2,
  LongOperationStatus           = 0x4,
  ErrorLog                      = 0x5,
  BiosBootInfo                  = 0x6,
  TempAndPowerStatus            = 0x7,
  TempAndPowerSettings          = 0x8,
  KeyStorage                    = 0x9,
  HwParameters                  = 0xA,
  ThrottilePowerStateDescriptor = 0xB,
  CommandEffectInfo             = 0xFE,
  CommandEffectLog              = 0xFF
} SETGETLOGPAGE_SUBCMD_OPCODES;


//
// Enum for Update Firmware Sub command Opcodes
//
typedef enum {
  UpdateFwWithOffsets = 0x0,
  ActivateFw = 0x1,
} UPDATEFIRMWARE_SUBCMD_OPCODES;


//
// Enum for Inject Error Sub command Opcodes
//
typedef enum {
  EnableInjection       = 0x0,
  PoisonError           = 0x1,
  MediaTemperatureError = 0x2,
  SoftwareTriggers      = 0x3,
} INJECTERROR_SUBCMD_OPCODES;


//
// Enum for Region Provision Sub command Opcodes
//
typedef enum {
  QueryRegionLayout = 0x0,
  RegionCreate = 0x1,
  RegionDelete = 0x2,
  ClearRegion = 0x3,
  FormatRegion = 0x4,
} REGIONPROVISION_SUBCMD_OPCODES;



//
// Enum for Get Features Sub command Opcodes
//
typedef enum {
  AddressRangeScrub = 0x4,
  PmonRegisters = 0x7,
} GETFEATURES_SUBCMD_OPCODES;


//
// Enum for Sub command Opcodes of Label Methods
//
typedef enum {
  GetLabelInfo  = 0x0,
  GetLabelData  = 0x1,
  SetLabelData  = 0x2,
} LABELDATA_SUBCMD_OPCODES;


#pragma pack(1)
//
// MB Commands structure
//
typedef struct {
  MBCMD0_FMSS_MAILBOX_STRUCT MbCmd0Reg;
  MBCMD1_FMSS_MAILBOX_STRUCT MbCmd1Reg;
  UINT64    BiosNonceValue;
  UINT32    *InputPayloadPtr;
  UINT32    *OutputPayloadPtr;
  UINT8     InputPayloadSizeDw;
  UINT8     OutputPayloadSizeDw;
  UINT8     *DeviceReturnStatus;
} MAILBOX_CMD;


typedef struct {
  UINT8 CurrentState; //To be used in future for device initialization flow
  MAILBOX_RETURN_STATUS Status;
} BIOS_FMSS_MBSTATUS;


//
// Region Layout information
//
typedef struct { // struct of valid data fields only
  union {
   struct {
      UINT32 RegionId                  : 6; // Bit[5:0]This is the 6-bit region ID field. Valid value from 0 - 63.
      UINT32 LastRegionIndicator       : 1; // Bit[6]
      UINT32 RegionValidindicator      : 1; // Bit[7] this bit is set to '1' after the region is created. This bit is set to '0' when the region is invalid
      UINT32 RegionAttr_Mem_Storage    : 1; // bit[8] '1'= Memory, '0' = Storage
      UINT32 RegionAttr_FastZero       : 1; // bit[9] '1'= Fast Zero support; '0'= No Fast Zero support
      UINT32 Rsvd2                     : 6; // Bit[15:10]
      UINT32 BiosRegionType            : 8; // Bit[23:16] 0  = NVMe storage, 1 = Volatile Memory
                                            // 2 = Intel Reserved Region Memory,3 = Persistence Memory, Others = Reserved
      UINT32 ReadSectorSize            : 4; // Bit[27:24] 0 = Reserved; 1 = 512B; 2-15 = Reserved
      UINT32 WriteSectorSize           : 4; // Bit[31:28] 0-2 = Reserved; 3 = 2048B; 4-15 = Reserved
    } DW0Bits;
    UINT32 DW0Data;
  } DW0Data_Union;
  UINT32 RegionSize;
} REGION_LAYOUT_INFORMATION;


//
// Information of 2LM MODULE Device
//
typedef struct { // struct of valid data fields only
  UINT16 VendorID;  // bytes 1-0 unique identifier for the NVM 2LM MODULE vendor (0x8086)
  UINT16 DeviceID;  // bytes 3-2 Device ID of 2LM module
  UINT16 RevisionID; // bytes 5-4 Chip revision id (stepping) of the Asic
  UINT16 IFC;      // bytes 7-6 Interface Format Code (IFC): 0x301
  UINT64 FirmwareRevision; // bytes 15-8  (FWR): Contains revision of the firmware
  UINT64 Rsvd1; // bytes 23-16
  UINT64 Rsvd2; // bytes 32-24
  UINT32 RawCapacity; // bytes 32-35, The max capacity, in 4KB units, of the 2LM module that can be allocated for use in any of the supported modes (Memory, Storage or App Direct)
  UINT16 Manufacturer; // bytes 36-37, Manufacturer's ID code determined by JEDEC JEP-106 (or unique)
  UINT8  SerialNumber[20]; // bytes 57-38, these 20 bytes hold the unique serial number for the 2LM module2LM MODULE.
  UINT8  PartNumber[40]; // bytes 97-58, these 40 bytes contain the manufacturer's module part number, in ASCII character formatted bytes

  union { // Bytes 101-98, DIMM's SKU information providing details about DIMM capabilities and features.
    struct {
    UINT32 MemoryModeSupported     : 1; // Bit 0
    UINT32 StorageModeSupported    : 1; // Bit 1
    UINT32 PMemModeSupported       : 1; // Bit 2
    UINT32 DieSparingCapable     : 1; // Bit 3
    UINT32 Rsvd1                 : 13;  // Bit [16:4]
    UINT32 NvmeEncryption        : 1; // Bit 17
    UINT32 MemoryEncryption      : 1; // Bit 18
    UINT32 AppDirectEncryption   : 1; // Bit 19
    UINT32 Rsvd2                 : 12;  // Bit [31:20]
  } MODULE_2LM_SKU_Struct;
  UINT32 Data_MODULE_2LM_SKU;
  } MODULE_2LM_SKU_Union;

  UINT16 IFCE; // Bytes 103-102, Interface Format Code Extra (IFCE): 0x201
  UINT16 ClientApiVersion; // Bytes 105-104, BCD formatted revision of the firmware interface
  UINT8  Rsvd3[22]; // bytes 127-106

  union { // Bytes 129-128, Region capabilities
    struct {
      UINT16 MaxRegionSupported     : 6;  // Bit [5:0] Maximum number of regions this 2LM Module supports
      UINT16 Rsvd1                  : 2;  // Bit [7:6]
      UINT16 PlatformRegionRequired : 1;  // Bit 8, 0 - no platform region required
      // 1 - platform region is required.  A platform Region is required to be created  if any regions are to be utilized for Memory Mode or App Direct mode.
      // This region shall be used by the platform for vendor specific usage. (e.g. the Intel Restricted Region)
      UINT16 OutofOrderCreationDeletion : 1;  // Bit 9,0 - creation of Regions must be done in ascending Region ID order and deletion of regions shall be done in descending Region ID order
      // 1 - creation and deletion of regions may be done in any order
      UINT16 Rsvd2                  : 6;  // Bit [15:10]
    } REGION_CAPABILITIES_Struct;
    UINT16 Data_REGION_CAPABILITIES;
  } REGION_CAPABILITIES_Union;

  struct {    // bytes 169-130 2LM Capabilities
    union {    // byte 130
      struct {
        UINT8 TotalNumberOfRegions      :  6;  // Bit [5:0] Number of valid regions that have been created. 0 = 1 region, 3F'h = 64 regions.
        UINT8 Rsvd                      :  1;  // Bit 6
        UINT8 RegionProvisioned         :  1;  // Bit 7  0 - The device has not been provisioned, 1 - The device has been provisioned through create regions
      } Byte_130_Struct;
      UINT8 Data_Byte_130;
    } Byte130_Union;

    UINT8 Mcsrts;  // Bit [15:8] Maximum outstanding credit of CSR VDM register read/write TLP supported (MCSRTS),0 - not valid,1 - default value is 1 (min 1 credit)
    UINT8 Mhldts;  // Bit [23:16] Maximum outstanding credit of VDM NVMe hold/unblock TLP supported (MHLDTS) default value is 1
    UINT8 Mwss;  // Bit [31:24] Maximum outstanding credit of 2LM Memory Write (per media slice) supported (MWSS), default value is 18
    UINT8 Mrts;   // Bit [39:32] Maximum outstanding credit of 2LM Memory Read  TLP supported (MRTS), default value is 12
    UINT16 MemoryWriteAlignment;  // Bit [55:40] Region sector alignment Memory Write Support
    /* Bit[0] - 64B; Bit[1] - 128B; Bit[2] - 256B; Bit[3] - 512B; Bit[4] - 1KB; Bit[5] - 2KB; Bit[6] - 4KB; Bit[15:7]  - Reserved Default is only bit[1] is set
     */
    UINT16 MemoryReadAlignment;  // Bit [71:56] Region sector alignment Memory Read Support
    /* Bit[0] - 64B; Bit[1] - 128B; Bit[2] - 256B; Bit[3] - 512B; Bit[4] - 1KB; Bit[5] - 2KB; Bit[6] - 4KB; Bit[15:7]  - Reserved Default is only bit[1] is set
     */
    UINT16 PowerManagementExitLatency;   // Bit [87:72]
    /* Bit[81:72] Power Management Exit Latency Value: 10-bit value to indicate exit latency
     * Bit[84:82]: Reserved
     * Bit[87:85] Power Management Exit Latency Scale: 3-bit scaling factor for exit
     */
    UINT16 PowerManagementEntryLatency;   // Bit [103:88]
    /* Bit[97:88] Power Management Entry Latency Value: 10-bit value to indicate entry latency
     * Bit[100:98]: Reserved
     * Bit[103:101] Power Management Entry Latency Scale: 3-bit scaling factor for entry
     */
    UINT8 DeviceHealthStatus;     // Bit[111:104] 0x00 = Healthy. Device is able to process commands normally, 0x01 - 0xFF = Reserved/TBD
  } CAPABILITIES_2LM; // 2LM CAPABILITIES
} DEVICE_2LM_INFORMATION;

//
// Characteristics of 2LM MODULE Device
//
typedef struct {
  UINT16 ControllerTempShutdownThreshold; //CTST: This describes the temperature at which the controller will shutdown when it is detected to be this or higher.
  UINT16 MediaTempShutdownThreshold;  //MTST: This describes the temperature at which the FW will shutdown the device when the media is detected to be or higher in order to protect the 2LM Module & Data
  UINT16 ThrottlingStartThreshold;  //TSTT: This describes the media temperature at which the FW will start throttling to reduce overall thermals to keep the 2LM Module within safe operating temperatures
  UINT16 ThrottlingStopThreshold;  //TSPT: This describes the media temperature at which the FW will stop throttling to increase performance after it has reduced thermals to acceptable level
} DEVICE_2LM_CHARACTERISTICS;


//
// HW Parameters Command Register
//
typedef struct {
  // Partial Write Timeout (Bytes 1-0)
  UINT16 PartialWriteTimeout            :10; // Partial Write time out in micro sec
  UINT16 Reserved1                      :6 ; // Reserved
  // Arbitration Control   (Bytes 5-2)
  UINT8  FmRwrr                            ; // Far Memory Read Weighted Round Robin
  UINT8  FmWwrr                            ; // Far Memory Write Weighted Round Robin
  UINT8  Fmwrr                             ; // Far Memory Weighted Round Robin
  UINT8  Swrr                              ; // Storage Weighted Round Robin
  // Test Mode Control     (Bytes 7-6)
  UINT16 MdmEn                          :1 ; // Multipurpose buffer Mode enable/disable
  UINT16 InOrdExe                       :1 ; // In order execution enable/disable
  UINT16 Dis2kRdC                       :1 ; // Disable 2K read cache
  UINT16 Reserved2                      :13; // Reserved
  // LTR L1.2 Threshold    (Bytes 9-8)
  UINT16 Ltr_L1D2_ThVal                 :10; // LTR L1.2 Threshold Value
  UINT16 Reserved3                      :3 ; // Reserved
  UINT16 Ltr_L1D2_ThScale               :3 ; // LTR L1.2 Threshold Scale
  // Thermal management temp1 (Bytes 11-10)
  UINT16 Tmt1                              ; // Thermal Management Temperature 1
  // Thermal management temp1 (Bytes 13-12)
  UINT16 Tmt2                              ; // Thermal Management Temperature 2
  // Async Notifications Control0 (Bytes 15-14)
  UINT16 MediaDeathNotification         :1 ; // Media Death Notification Enable/Disable
  UINT16 HealthLogNotification          :1 ; // Health Log Notification Enable/Disable
  UINT16 Reserved4                      :4 ; // Reserved
  UINT16 TempBelowThrottleNotification  :1 ; // Temp crosses below TempThrottle Notification Enable/Disable
  UINT16 TempAboveThrottleNotification  :1 ; // Temp crosses above TempThrottle Notification Enable/Disable
  UINT16 MissingCommitBitNotification   :1 ; // Missing Commit Bit Notification Enable/Disable
  UINT16 Reserved5                      :7 ; // Reserved
  // System Power State      (Byte 16)
  UINT8  SysPwrState                    :4 ; // system power state indicates the platform power state
  UINT8  Reserved6                      :4 ; // Reserved
} HW_PARAMETERS;


#pragma pack()

/**
This function reads VDM register value from 2LM device.

@param[in]      RegOffset         FMHC Mailbox Register offset.
@param[out]     Data              VDM read data.

@retval EFI_SUCCESS            Successful completion of RegReadVdm.
**/
EFI_STATUS
EFIAPI
RegReadVdm (
  IN  UINT16      RegOffset,
  OUT UINT32      *Data
  );

/**
This function writes to VDM register in 2LM device.

@param[in]      RegOffset         FMHC Mailbox Register offset.
@param[in]      Data              VDM write data.

@retval EFI_SUCCESS            Successful completion of RegWriteVdm.
**/
EFI_STATUS
EFIAPI
RegWriteVdm (
  IN UINT16     RegOffset,
  IN UINT32     Data
  );


/**
This function issues Mailbox command to 2LM device.

@param[inout]      MbCmd        Structure with all the required parameters.

@retval EFI_SUCCESS            Successful completion of Mailbox communication.
**/
EFI_STATUS
EFIAPI
IssueMailboxCommand (
  IN MAILBOX_CMD    MbCmd
  );


//
// 3DXP Device Mailbox Commands as per the FIS document
//

//
// 3.1  Identify 2LM MODULE Device (01h)
// These commands return device specific information and various device characteristics.
//


// This command returns vital product data for a 2LM Module.
// There are no input parameters.
EFI_STATUS
EFIAPI
Identify2lmModuleCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  );


// This command returns various device characteristics, these are typically vendor specific characteristics.
// There are no input parameters.
EFI_STATUS
EFIAPI
IdentifyDeviceCharacteristicsCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  );


//
// 3.2  Set Security Info (03h)
//

// This command should only be utilized by the platform FW. No other SW should be allowed to set the BIOS Security Nonce.
// Once the security nonce is set, every mailbox command must receive the correct security nonce with the command to be executed.
// Until the nonce is set, it is ignored for all incoming mailbox commands.
EFI_STATUS
EFIAPI
SetSecurityBiosNonceCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT64    NonceValue
  );


//
// 3.3  Get Features (04h)
// Used to retrieve the modifiable settings for the2LM Module.
//

// This command is used to retrieve the values for the Address Range Scrub.
EFI_STATUS
EFIAPI
GetAddressRangeScrubCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  );


// This command allows the user to retrieve the current configuration for the Performance Monitor Registers.
EFI_STATUS
EFIAPI
GetPmonRegistersCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw,
  IN      UINT16    PmonRetrieveMask
  );

//
// 3.4  Set Features (05h)
// Sets various thresholds and policies that can be configured.
//

// This command is used to scrub for errors on the 2LM Module's PM Region only (scrubs can NOT be done on 2LM memory).
EFI_STATUS
EFIAPI
SetAddressRangeScrubCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
  );


// This command allows the user to configure the Performance Monitor Registers within the 2LM Module.
EFI_STATUS
EFIAPI
SetPmonRegistersCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
  );


//
// 3.5    Get Admin Features (06h)
//

// This command returns the system time set by the BIOS during boot.
// If not set, this command will generate an error (09h)and all data returned will be zeroed out.
// The return data for the command will be populated in the payload registers.
EFI_STATUS
EFIAPI
GetSystemTimeCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT64    *SystemTimeOutput
  );


// This command is a BIOS only command that performs a configuration lock for the current boot cycle.
// Calling the get of this function retrieves status from the command of whether or not the lock down command has already been called.
EFI_STATUS
EFIAPI
GetConfigLockdownCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT8     *LockStatus    // though o/p payload size is 1 byte,Mailbox r/w granularity is 1 DW
  );


// This command retrieves whether the 2LM Module will latch the SMART Last Shutdown Status and SMART Unsafe Shutdown Count.
// If the latch is enabled, on the next power-down, power-up sequence the SMART LSS & SMART Unsafe Shutdown Count will be latched.
EFI_STATUS
EFIAPI
GetLatchSystemShutdownStateCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT8     *ShutdownStatus // though o/p payload size is 1 byte,Mailbox r/w granularity is 1 DW
  );

//
// 3.6  Set Admin Features (07h)
//

// This command is used to set the date/time of the 2LM Module. BIOS is required to set this at every boot.
// Since the FFW does not have access to an RTC, the BIOS is needed to set the time so that logging and other time-sensitive features can be used appropriately.
EFI_STATUS
EFIAPI
SetSystemTimeCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT64     SystemTimeInput
);


// This command is a BIOS only command that performs a configuration lock for the current boot cycle.
// BIOS will make this call prior to transitioning to the OS. This call is only available to BIOS.
// There are no input payload values for this command.
EFI_STATUS
EFIAPI
SetConfigLockdownCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT64    BiosNonceValue
  );


// This command instructs the 2LM Module whether to latch the SMART Last Shutdown Status and SMART Unsafe Shutdown Count.
// If the latch is enabled, on the next power-down, power-up sequence the SMART LSS & SMART Unsafe Shutdown Count will be latched.
// This is a single shot setting, after latching it gets disabled until this command enables it again.
// The latched values will persist on the 2LM Module and they can be only be overwritten if the latch is enabled again
// and a powerdown, power-up sequence occurs.
EFI_STATUS
EFIAPI
SetLatchSystemShutdownStateCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
//  IN      UINT8     ShutdownStatus    // though i/p payload size is 1 byte,Mailbox r/w granularity is 1 DW
  );

//
// Get Log Page (08h)
// These commands allows for retrieval of various types of information from the FW.
// Error information, as well as health and status information for background operations, are retrieved.
//

// This command is used to retrieve the current health of the system, including SMART information.
EFI_STATUS
EFIAPI
GetSmartAndHealthInfoCommand (
  OUT     UINT8      *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  );


// This command identifies the running firmware version.
EFI_STATUS
EFIAPI
GetFirmwareImageInfoCommand (
  OUT     UINT8      *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  );


// This command returns the data that shows the state of the background operation currently executing.
// Information returned will include the command being executed, the current status of the operation (percentage done) and
// estimated time to completion of the command, and status code of the command.
// Only a single background operation is allowed at a time from any mailbox interface.
EFI_STATUS
EFIAPI
GetLongOpearationStatusCommand (
  OUT     UINT8      *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  );


// This command retrieves a compressed log of errors that FW has logged.
// The purpose of this log is to enable 3rd party software to view any important messages that have been generated by the FW.
EFI_STATUS
EFIAPI
GetErrorLogCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
  );


// This command returns BIOS stored boot information in outbox.
EFI_STATUS
EFIAPI
GetBiosBootInfoCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  );


// This command returns the temperature and power settings of the 2LM module.
EFI_STATUS
EFIAPI
GetTempAndPowerSettingsCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  );


// This command returns various HW parameter settings.
EFI_STATUS
EFIAPI
GetHwParametersCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  );


// This command returns stored key information in outbox.
EFI_STATUS
EFIAPI
GetKeyStorageCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw,
  IN      UINT16    StorageWindowValue
  );


// The Command Effect Info reports the size via number of Command Effect Entry count.
// This allows the host to pre-allocate the appropriate size buffer to satisfy a call to  Command Effect Log.
EFI_STATUS
EFIAPI
GetCommandEffectInfoCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  );


// The Command Effect Log is a variable length log page that reports the support for each NVM 2LM MODULE FW Command
// and the effect each command will have on the NV2LM MODULE subsystem.
// more details TBD
EFI_STATUS
EFIAPI
GetCommandEffectLogCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw,
  IN      UINT8     PageOffset
  );



//
// Inject Error (0Ah)
// These commands are used to inject errors into the part in order to do various types of software error testing.
// Not all errors injected will be triggered immediately.
//

// This command is used to enable injection within the part. This command is only accessible over the BIOS mailbox.
EFI_STATUS
EFIAPI
EnableInjectionCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT8     InjectionStatus
  );


// This command will allow setting poison on a particular DPA address (PM or 2LM) and allows for testing of host error flows.
EFI_STATUS
EFIAPI
PoisonErrorCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN OUT  UINT8     PoisonErrorStatus,
  IN OUT  UINT8     RegionType,
  IN OUT  UINT64    DpaAddress
  );


// This command injects a particular artificial temperature into the part.
EFI_STATUS
EFIAPI
MediaTempErrorCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT8     ErrorStatus,
  IN      UINT16    MediaTemp
  );


// These are software override triggers. These triggers allow the user to trip various software alarms without causing any harm to the part or FW.
EFI_STATUS
EFIAPI
SoftwareTriggersCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
  );


//
// Label Data (0Bh)
//

// This command returns the Label information storage are characteristics of the persistent memory region of the 2LM module.
EFI_STATUS
EFIAPI
GetLabelInfoCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw,
  IN      UINT8     RegionId
  );



// This command returns the label information data at a given offset.
EFI_STATUS
EFIAPI
GetLabelDataCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw,
  IN      UINT8     RegionId
//  IN      UINT32     Offset,
//  IN      UINT32     TransferLength
  );


// This command sets the label data for at a given offset of the label storage area.
EFI_STATUS
EFIAPI
SetLabelDataCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw,
  IN      UINT8     RegionId
//  IN      UINT8     Offset,
//  IN      UINT8     TransferLength
  );


//
// Set Log page (0Dh)
//

// This command allows storing the BIOS boot information.
EFI_STATUS
EFIAPI
SetBiosBootInfoCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
  );


// This command allows the setting of the various fields.
EFI_STATUS
EFIAPI
SetTempAndPowerSettingsCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
  );


// This command allows the setting of the various HW parameters.
EFI_STATUS
EFIAPI
SetHwParametersCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
  );


// This command allows to stored key information.
EFI_STATUS
EFIAPI
SetKeyStorageCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw,
  IN      UINT16    StorageWindowValue
  );


//
// Region Provision (0Ch)
//

// This command returns the Region layout of the 2LM module.
// RegionId = 0xFF, indicates QueryAll regions
EFI_STATUS
EFIAPI
QueryRegionLayoutCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw,
  IN      UINT8      RegionId
  );


// This is the command to create region. Once a region is created, the region setting persists across power cycles and boots.
// The created region may be deleted or cleared. Region ID used in creation shall start from Region ID 0 and be packed sequentially for subsequent regions.
// For Region Create, 8 bytes of region data is required in the inbox buffer.
EFI_STATUS
EFIAPI
RegionCreateCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
  );


// This is the command to delete region(s). Once a region is deleted, the associated region data shall be removed from the regions table
// and the total number of region shall be decremented by 1. Only Command register is required for Region Delete,
// no additional data is required in the inbox buffer.
// RegionId = 0xFF, indicates DeleteAll regions
EFI_STATUS
EFIAPI
RegionDeleteCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT8      RegionId
  );


// This is the command to clear region(s). Once a region is cleared, all the data returned will be 0, but actual data on the device may not be 0.
// Device FW shall increment the device's boot counter after clearing the region. Only Command register is required for Region Clear,
// no additional data is required in the inbox buffer.
// RegionId = 0xFF, indicates ClearAll regions
EFI_STATUS
EFIAPI
ClearRegionCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT8      RegionId
  );


// This is the command to format region(s). Once a region is formatted, the actual data on the device shall be cleared to 0.
// Device FW shall not increment the device's boot counter. Only Command register is required for Region format,
// no additional data is required in the inbox buffer.
// RegionId = 0xFF, indicates FormatAll regions
EFI_STATUS
EFIAPI
FormatRegionCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT8      RegionId,
  IN      UINT8      SecureErase
  );


//
// Update FW (09h)
// This command is available via the mailbox. Updated FW only takes effect after reboot / restart of the system,
// unless an Execute FW command is called after a successful Update FW command.
// In the case where multiple 2LM Module are being updated, a single system restart will allow all updated 2LM Module to run with the newest FW.
//


// This command allows updating of the running firmware.
// The FW can be updated via the mailbox and since the mailbox has a limited size and the FW may need to be sent in chunks w/ offsets.
// This command initiates the update firmware
EFI_STATUS
EFIAPI
InitiateUpdateFirmwareCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw,
  IN      UINT16    PacketNo
  );


// This command indicates the continuation/subsequent command for update firmware
EFI_STATUS
EFIAPI
ContinueUpdateFirmwareCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw,
  IN      UINT16    PacketNo
  );


// This command indicates the end of update firmware
EFI_STATUS
EFIAPI
EndUpdateFirmwareCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw,
  IN      UINT16    PacketNo        //TBD check if this field is required?
  );


// This command is used to force the execution of a newly updated FW image once the FW image has been downloaded
// and all proper steps have been taken to validate the image and save.
EFI_STATUS
EFIAPI
ActivateFwCommand (
  OUT     UINT8     *DeviceReturnStatus
  );


// This command retrieves the Smart threshold information.
EFI_STATUS
EFIAPI
GetSmartThresholdCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  );


// This command allows the setting of Smart Threshold
EFI_STATUS
EFIAPI
SetSmartThresholdCommand (
  OUT     UINT8     *DeviceReturnStatus,
  IN      UINT32    *InputPayloadPtr,
  IN      UINT8     InputPayloadSizeDw
  );

// This command is used to get the long operation status.
EFI_STATUS
EFIAPI
GetLongOperationStatusCommand (
  OUT     UINT8     *DeviceReturnStatus,
  OUT     UINT32    *OutputPayloadPtr,
  IN      UINT8     OutputPayloadSizeDw
  );
#endif /* FMSS_MB_LIB_H_ */
