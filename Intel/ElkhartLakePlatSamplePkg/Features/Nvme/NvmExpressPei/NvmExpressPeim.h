/** @file
  Private Header file for NvmExpress PEIM

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#ifndef _NVM_EXPRESS_PEIM_H_
#define _NVM_EXPRESS_PEIM_H_

#include <PiPei.h>

#include <Library/DebugLib.h>
#include <Library/PeimEntryPoint.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/TimerLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>

#include <Ppi/NvmExpressController.h>
#include <Ppi/NvmExpressPassThru.h>

#include <Ppi/BlockIo.h>
#include <Ppi/BlockIo2.h>

typedef struct _PEI_NVME_CONTROLLER_PRIVATE_DATA PEI_NVME_CONTROLLER_PRIVATE_DATA;
typedef struct _PEI_NVME_DEVICE_PRIVATE_DATA     PEI_NVME_DEVICE_PRIVATE_DATA;

//
// controller register offsets
//
#define NVME_CAP_OFFSET          0x0000  // Controller Capabilities
#define NVME_VER_OFFSET          0x0008  // Version
#define NVME_INTMS_OFFSET        0x000c  // Interrupt Mask Set
#define NVME_INTMC_OFFSET        0x0010  // Interrupt Mask Clear
#define NVME_CC_OFFSET           0x0014  // Controller Configuration
#define NVME_CSTS_OFFSET         0x001c  // Controller Status
#define NVME_NSSR_OFFSET         0x0020  // NVM Subsystem Reset
#define NVME_AQA_OFFSET          0x0024  // Admin Queue Attributes
#define NVME_ASQ_OFFSET          0x0028  // Admin Submission Queue Base Address
#define NVME_ACQ_OFFSET          0x0030  // Admin Completion Queue Base Address
#define NVME_SQ0_OFFSET          0x1000  // Submission Queue 0 (admin) Tail Doorbell
#define NVME_CQ0_OFFSET          0x1004  // Completion Queue 0 (admin) Head Doorbell

//
// These register offsets are defined as 0x1000 + (N * (4 << CAP.DSTRD))
// Get the doorbell stride bit shift value from the controller capabilities.
//
#define NVME_SQTDBL_OFFSET(QID, DSTRD)    0x1000 + ((2 * (QID)) * (4 << (DSTRD)))       // Submission Queue y (NVM) Tail Doorbell
#define NVME_CQHDBL_OFFSET(QID, DSTRD)    0x1000 + (((2 * (QID)) + 1) * (4 << (DSTRD))) // Completion Queue y (NVM) Head Doorbell

//
// Nvm Express Admin cmd opcodes
//
#define NVME_ADMIN_DEIOSQ_CMD                0x00
#define NVME_ADMIN_CRIOSQ_CMD                0x01
#define NVME_ADMIN_GET_LOG_PAGE_CMD          0x02
#define NVME_ADMIN_DEIOCQ_CMD                0x04
#define NVME_ADMIN_CRIOCQ_CMD                0x05
#define NVME_ADMIN_IDENTIFY_CMD              0x06
#define NVME_ADMIN_ABORT_CMD                 0x08
#define NVME_ADMIN_SET_FEATURES_CMD          0x09
#define NVME_ADMIN_GET_FEATURES_CMD          0x0A
#define NVME_ADMIN_ASYNC_EVENT_REQUEST_CMD   0x0C
#define NVME_ADMIN_NAMESACE_MANAGEMENT_CMD   0x0D
#define NVME_ADMIN_FW_COMMIT_CMD             0x10
#define NVME_ADMIN_FW_IAMGE_DOWNLOAD_CMD     0x11
#define NVME_ADMIN_NAMESACE_ATTACHMENT_CMD   0x15
#define NVME_ADMIN_FORMAT_NVM_CMD            0x80
#define NVME_ADMIN_SECURITY_SEND_CMD         0x81
#define NVME_ADMIN_SECURITY_RECEIVE_CMD      0x82

#define NVME_IO_FLUSH_OPC                    0
#define NVME_IO_WRITE_OPC                    1
#define NVME_IO_READ_OPC                     2

//
// Offset from the beginning of private data queue buffer
//
#define NVME_ASQ_BUF_OFFSET                  EFI_PAGE_SIZE

#define NVME_CONTROLLER_ID                        0

#define NVME_ASQ_SIZE                                    1     // Number of admin submission queue entries, which is 0-based
#define NVME_ACQ_SIZE                                    1     // Number of admin completion queue entries, which is 0-based

#define NVME_CSQ_SIZE                                    1     // Number of I/O submission queue entries, which is 0-based
#define NVME_CCQ_SIZE                                    1     // Number of I/O completion queue entries, which is 0-based

#define NVME_MAX_IO_QUEUES                               2     // Number of I/O queues supported by the driver, 1 for AQ, 1 for CQ
#define NVME_MAX_QUEUES                                  2     // Number of queues supported by the driver

#define NVME_CSQ_DEPTH                                   (NVME_CSQ_SIZE+1)
#define NVME_CCQ_DEPTH                                   (NVME_CCQ_SIZE+1)
#define NVME_PRP_SIZE                                    (4)    // Pages of PRP list

//
// Time out Value for Nvme transaction execution
//
#define NVME_GENERIC_TIMEOUT                             5000000   ///< us
#define NVME_CMD_WAIT                                    100       ///< us
#define NVME_CMD_TIMEOUT                                 20000000  ///< us

//
// Unique signature for private data structure.
//
#define PEI_NVME_CONTROLLER_PRIVATE_DATA_SIGNATURE    SIGNATURE_32 ('P','N','V','M')

#define PEI_NVME_CONTROLLER_PRIVATE_DATA_FROM_PASS_THRU(a) \
  CR (a, \
      PEI_NVME_CONTROLLER_PRIVATE_DATA, \
      Passthru, \
      PEI_NVME_CONTROLLER_PRIVATE_DATA_SIGNATURE \
      )

#pragma pack(1)

//
// 3.1.1 Offset 00h: CAP - Controller Capabilities
//
typedef struct {
  UINT16 Mqes;      // Maximum Queue Entries Supported
  UINT8  Cqr:1;     // Contiguous Queues Required
  UINT8  Ams:2;     // Arbitration Mechanism Supported
  UINT8  Rsvd1:5;
  UINT8  To;        // Timeout
  UINT16 Dstrd:4;
  UINT16 Rsvd2:1;
  UINT16 Css:4;     // Command Sets Supported
  UINT16 Rsvd3:7;
  UINT8  Mpsmin:4;
  UINT8  Mpsmax:4;
  UINT8  Rsvd4;
} NVME_CAP;

//
// 3.1.2 Offset 08h: VS - Version
//
typedef struct {
  UINT16 Mnr;       // Minor version number
  UINT16 Mjr;       // Major version number
} NVME_VER;

//
// 3.1.5 Offset 14h: CC - Controller Configuration
//
typedef struct {
  UINT16 En:1;       // Enable
  UINT16 Rsvd1:3;
  UINT16 Css:3;      // I/O Command Set Selected
  UINT16 Mps:4;      // Memory Page Size
  UINT16 Ams:3;      // Arbitration Mechanism Selected
  UINT16 Shn:2;      // Shutdown Notification
  UINT8  Iosqes:4;   // I/O Submission Queue Entry Size
  UINT8  Iocqes:4;   // I/O Completion Queue Entry Size
  UINT8  Rsvd2;
} NVME_CC;

//
// 3.1.6 Offset 1Ch: CSTS - Controller Status
//
typedef struct {
  UINT32 Rdy:1;      // Ready
  UINT32 Cfs:1;      // Controller Fatal Status
  UINT32 Shst:2;     // Shutdown Status
  UINT32 Nssro:1;    // NVM Subsystem Reset Occurred
  UINT32 Rsvd1:27;
} NVME_CSTS;

//
// 3.1.8 Offset 24h: AQA - Admin Queue Attributes
//
typedef struct {
  UINT16 Asqs:12;    // Submission Queue Size
  UINT16 Rsvd1:4;
  UINT16 Acqs:12;    // Completion Queue Size
  UINT16 Rsvd2:4;
} NVME_AQA;

//
// 3.1.9 Offset 28h: ASQ - Admin Submission Queue Base Address
//
typedef struct {
  UINT64 Rsvd1:12;
  UINT64 Asqb:52;    // Admin Submission Queue Base Address
} NVME_ASQ;

//
// 3.1.10 Offset 30h: ACQ - Admin Completion Queue Base Address
//
typedef struct {
  UINT64 Rsvd1:12;
  UINT64 Acqb:52;    // Admin Completion Queue Base Address
} NVME_ACQ;

//
// 3.1.11 Offset (1000h + ((2y) * (4 << CAP.DSTRD))): SQyTDBL - Submission Queue y Tail Doorbell
//
typedef struct {
  UINT16 Sqt;
  UINT16 Rsvd1;
} NVME_SQTDBL;

//
// 3.1.12 Offset (1000h + ((2y + 1) * (4 << CAP.DSTRD))): CQyHDBL - Completion Queue y Head Doorbell
//
typedef struct {
  UINT16 Cqh;
  UINT16 Rsvd1;
} NVME_CQHDBL;

//
// NVM command set structures
//
// Read Command
//
typedef struct {
  //
  // CDW 10, 11
  //
  UINT64 Slba;                /* Starting Sector Address */
  //
  // CDW 12
  //
  UINT16 Nlb;                 /* Number of Sectors */
  UINT16 Rsvd1:10;
  UINT16 Prinfo:4;            /* Protection Info Check */
  UINT16 Fua:1;               /* Force Unit Access */
  UINT16 Lr:1;                /* Limited Retry */
  //
  // CDW 13
  //
  UINT32 Af:4;                /* Access Frequency */
  UINT32 Al:2;                /* Access Latency */
  UINT32 Sr:1;                /* Sequential Request */
  UINT32 In:1;                /* Incompressible */
  UINT32 Rsvd2:24;
  //
  // CDW 14
  //
  UINT32 Eilbrt;              /* Expected Initial Logical Block Reference Tag */
  //
  // CDW 15
  //
  UINT16 Elbat;               /* Expected Logical Block Application Tag */
  UINT16 Elbatm;              /* Expected Logical Block Application Tag Mask */
} NVME_READ;

//
// Write Command
//
typedef struct {
  //
  // CDW 10, 11
  //
  UINT64 Slba;                /* Starting Sector Address */
  //
  // CDW 12
  //
  UINT16 Nlb;                 /* Number of Sectors */
  UINT16 Rsvd1:10;
  UINT16 Prinfo:4;            /* Protection Info Check */
  UINT16 Fua:1;               /* Force Unit Access */
  UINT16 Lr:1;                /* Limited Retry */
  //
  // CDW 13
  //
  UINT32 Af:4;                /* Access Frequency */
  UINT32 Al:2;                /* Access Latency */
  UINT32 Sr:1;                /* Sequential Request */
  UINT32 In:1;                /* Incompressible */
  UINT32 Rsvd2:24;
  //
  // CDW 14
  //
  UINT32 Ilbrt;               /* Initial Logical Block Reference Tag */
  //
  // CDW 15
  //
  UINT16 Lbat;                /* Logical Block Application Tag */
  UINT16 Lbatm;               /* Logical Block Application Tag Mask */
} NVME_WRITE;

//
// Flush
//
typedef struct {
  //
  // CDW 10
  //
  UINT32 Flush;               /* Flush */
} NVME_FLUSH;

//
// Write Uncorrectable command
//
typedef struct {
  //
  // CDW 10, 11
  //
  UINT64 Slba;                /* Starting LBA */
  //
  // CDW 12
  //
  UINT32 Nlb:16;              /* Number of  Logical Blocks */
  UINT32 Rsvd1:16;
} NVME_WRITE_UNCORRECTABLE;

//
// Write Zeroes command
//
typedef struct {
  //
  // CDW 10, 11
  //
  UINT64 Slba;                /* Starting LBA */
  //
  // CDW 12
  //
  UINT16 Nlb;                 /* Number of Logical Blocks */
  UINT16 Rsvd1:10;
  UINT16 Prinfo:4;            /* Protection Info Check */
  UINT16 Fua:1;               /* Force Unit Access */
  UINT16 Lr:1;                /* Limited Retry */
  //
  // CDW 13
  //
  UINT32 Rsvd2;
  //
  // CDW 14
  //
  UINT32 Ilbrt;               /* Initial Logical Block Reference Tag */
  //
  // CDW 15
  //
  UINT16 Lbat;                /* Logical Block Application Tag */
  UINT16 Lbatm;               /* Logical Block Application Tag Mask */
} NVME_WRITE_ZEROES;

//
// Compare command
//
typedef struct {
  //
  // CDW 10, 11
  //
  UINT64 Slba;                /* Starting LBA */
  //
  // CDW 12
  //
  UINT16 Nlb;                 /* Number of Logical Blocks */
  UINT16 Rsvd1:10;
  UINT16 Prinfo:4;            /* Protection Info Check */
  UINT16 Fua:1;               /* Force Unit Access */
  UINT16 Lr:1;                /* Limited Retry */
  //
  // CDW 13
  //
  UINT32 Rsvd2;
  //
  // CDW 14
  //
  UINT32 Eilbrt;              /* Expected Initial Logical Block Reference Tag */
  //
  // CDW 15
  //
  UINT16 Elbat;               /* Expected Logical Block Application Tag */
  UINT16 Elbatm;              /* Expected Logical Block Application Tag Mask */
} NVME_COMPARE;

typedef union {
  NVME_READ                   Read;
  NVME_WRITE                  Write;
  NVME_FLUSH                  Flush;
  NVME_WRITE_UNCORRECTABLE    WriteUncorrectable;
  NVME_WRITE_ZEROES           WriteZeros;
  NVME_COMPARE                Compare;
} NVME_CMD;

typedef struct {
  UINT16 Mp;                /* Maximum Power */
  UINT8  Rsvd1;             /* Reserved as of Nvm Express 1.1 Spec */
  UINT8  Mps:1;             /* Max Power Scale */
  UINT8  Nops:1;            /* Non-Operational State */
  UINT8  Rsvd2:6;           /* Reserved as of Nvm Express 1.1 Spec */
  UINT32 Enlat;             /* Entry Latency */
  UINT32 Exlat;             /* Exit Latency */
  UINT8  Rrt:5;             /* Relative Read Throughput */
  UINT8  Rsvd3:3;           /* Reserved as of Nvm Express 1.1 Spec */
  UINT8  Rrl:5;             /* Relative Read Leatency */
  UINT8  Rsvd4:3;           /* Reserved as of Nvm Express 1.1 Spec */
  UINT8  Rwt:5;             /* Relative Write Throughput */
  UINT8  Rsvd5:3;           /* Reserved as of Nvm Express 1.1 Spec */
  UINT8  Rwl:5;             /* Relative Write Leatency */
  UINT8  Rsvd6:3;           /* Reserved as of Nvm Express 1.1 Spec */
  UINT8  Rsvd7[16];         /* Reserved as of Nvm Express 1.1 Spec */
} NVME_PSDESCRIPTOR;

//
//  Identify Controller Data
//
typedef struct {
  //
  // Controller Capabilities and Features 0-255
  //
  UINT16 Vid;                 /* PCI Vendor ID */
  UINT16 Ssvid;               /* PCI sub-system vendor ID */
  UINT8  Sn[20];              /* Product serial number */

  UINT8  Mn[40];              /* Proeduct model number */
  UINT8  Fr[8];               /* Firmware Revision */
  UINT8  Rab;                 /* Recommended Arbitration Burst */
  UINT8  Ieee_oui[3];         /* Organization Unique Identifier */
  UINT8  Cmic;                /* Multi-interface Capabilities */
  UINT8  Mdts;                /* Maximum Data Transfer Size */
  UINT8  Cntlid[2];           /* Controller ID */
  UINT8  Rsvd1[176];          /* Reserved as of Nvm Express 1.1 Spec */
  //
  // Admin Command Set Attributes
  //
  UINT16 Oacs;                /* Optional Admin Command Support */
    #define NAMESPACE_MANAGEMENT_SUPPORTED  BIT3
    #define FW_DOWNLOAD_ACTIVATE_SUPPORTED  BIT2
    #define FORMAT_NVM_SUPPORTED            BIT1
    #define SECURITY_SEND_RECEIVE_SUPPORTED BIT0
  UINT8  Acl;                 /* Abort Command Limit */
  UINT8  Aerl;                /* Async Event Request Limit */
  UINT8  Frmw;                /* Firmware updates */
  UINT8  Lpa;                 /* Log Page Attributes */
  UINT8  Elpe;                /* Error Log Page Entries */
  UINT8  Npss;                /* Number of Power States Support */
  UINT8  Avscc;               /* Admin Vendor Specific Command Configuration */
  UINT8  Apsta;               /* Autonomous Power State Transition Attributes */
  UINT8  Rsvd2[246];          /* Reserved as of Nvm Express 1.1 Spec */
  //
  // NVM Command Set Attributes
  //
  UINT8  Sqes;                /* Submission Queue Entry Size */
  UINT8  Cqes;                /* Completion Queue Entry Size */
  UINT16 Rsvd3;               /* Reserved as of Nvm Express 1.1 Spec */
  UINT32 Nn;                  /* Number of Namespaces */
  UINT16 Oncs;                /* Optional NVM Command Support */
  UINT16 Fuses;               /* Fused Operation Support */
  UINT8  Fna;                 /* Format NVM Attributes */
  UINT8  Vwc;                 /* Volatile Write Cache */
  UINT16 Awun;                /* Atomic Write Unit Normal */
  UINT16 Awupf;               /* Atomic Write Unit Power Fail */
  UINT8  Nvscc;               /* NVM Vendor Specific Command Configuration */
  UINT8  Rsvd4;               /* Reserved as of Nvm Express 1.1 Spec */
  UINT16 Acwu;                /* Atomic Compare & Write Unit */
  UINT16 Rsvd5;               /* Reserved as of Nvm Express 1.1 Spec */
  UINT32 Sgls;                /* SGL Support  */
  UINT8  Rsvd6[164];          /* Reserved as of Nvm Express 1.1 Spec */
  //
  // I/O Command set Attributes
  //
  UINT8 Rsvd7[1344];          /* Reserved as of Nvm Express 1.1 Spec */
  //
  // Power State Descriptors
  //
  NVME_PSDESCRIPTOR PsDescriptor[32];

  UINT8  VendorData[1024];    /* Vendor specific data */
} NVME_ADMIN_CONTROLLER_DATA;

typedef struct {
  UINT16 Ms;                /* Metadata Size */
  UINT8  Lbads;             /* LBA Data Size */
  UINT8  Rp:2;              /* Relative Performance */
    #define LBAF_RP_BEST      00b
    #define LBAF_RP_BETTER    01b
    #define LBAF_RP_GOOD      10b
    #define LBAF_RP_DEGRADED  11b
  UINT8  Rsvd1:6;           /* Reserved as of Nvm Express 1.1 Spec */
} NVME_LBAFORMAT;

//
// Identify Namespace Data
//
typedef struct {
  //
  // NVM Command Set Specific
  //
  UINT64 Nsze;                /* Namespace Size (total number of blocks in formatted namespace) */
  UINT64 Ncap;                /* Namespace Capacity (max number of logical blocks) */
  UINT64 Nuse;                /* Namespace Utilization */
  UINT8  Nsfeat;              /* Namespace Features */
  UINT8  Nlbaf;               /* Number of LBA Formats */
  UINT8  Flbas;               /* Formatted LBA size */
  UINT8  Mc;                  /* Metadata Capabilities */
  UINT8  Dpc;                 /* End-to-end Data Protection capabilities */
  UINT8  Dps;                 /* End-to-end Data Protection Type Settings */
  UINT8  Nmic;                /* Namespace Multi-path I/O and Namespace Sharing Capabilities */
  UINT8  Rescap;              /* Reservation Capabilities */
  UINT8  Rsvd1[88];           /* Reserved as of Nvm Express 1.1 Spec */
  UINT64 Eui64;               /* IEEE Extended Unique Identifier */
  //
  // LBA Format
  //
  NVME_LBAFORMAT LbaFormat[16];

  UINT8 Rsvd2[192];           /* Reserved as of Nvm Express 1.1 Spec */
  UINT8 VendorData[3712];     /* Vendor specific data */
} NVME_ADMIN_NAMESPACE_DATA;

//
// NvmExpress Admin Identify Cmd
//
typedef struct {
  //
  // CDW 10
  //
  UINT32 Cns:2;
  UINT32 Rsvd1:30;
} NVME_ADMIN_IDENTIFY;

//
// NvmExpress Admin Create I/O Completion Queue
//
typedef struct {
  //
  // CDW 10
  //
  UINT32 Qid:16;              /* Queue Identifier */
  UINT32 Qsize:16;            /* Queue Size */

  //
  // CDW 11
  //
  UINT32 Pc:1;                /* Physically Contiguous */
  UINT32 Ien:1;               /* Interrupts Enabled */
  UINT32 Rsvd1:14;            /* reserved as of Nvm Express 1.1 Spec */
  UINT32 Iv:16;               /* Interrupt Vector for MSI-X or MSI*/
} NVME_ADMIN_CRIOCQ;

//
// NvmExpress Admin Create I/O Submission Queue
//
typedef struct {
  //
  // CDW 10
  //
  UINT32 Qid:16;              /* Queue Identifier */
  UINT32 Qsize:16;            /* Queue Size */

  //
  // CDW 11
  //
  UINT32 Pc:1;                /* Physically Contiguous */
  UINT32 Qprio:2;             /* Queue Priority */
  UINT32 Rsvd1:13;            /* Reserved as of Nvm Express 1.1 Spec */
  UINT32 Cqid:16;             /* Completion Queue ID */
} NVME_ADMIN_CRIOSQ;

//
// NvmExpress Admin Delete I/O Completion Queue
//
typedef struct {
  //
  // CDW 10
  //
  UINT16 Qid;
  UINT16 Rsvd1;
} NVME_ADMIN_DEIOCQ;

//
// NvmExpress Admin Delete I/O Submission Queue
//
typedef struct {
  //
  // CDW 10
  //
  UINT16 Qid;
  UINT16 Rsvd1;
} NVME_ADMIN_DEIOSQ;

//
// NvmExpress Admin Abort Command
//
typedef struct {
  //
  // CDW 10
  //
  UINT32 Sqid:16;             /* Submission Queue identifier */
  UINT32 Cid:16;              /* Command Identifier */
} NVME_ADMIN_ABORT;

//
// NvmExpress Admin Firmware Activate Command
//
typedef struct {
  //
  // CDW 10
  //
  UINT32 Fs:3;                /* Submission Queue identifier */
  UINT32 Aa:2;                /* Command Identifier */
  UINT32 Rsvd1:27;
} NVME_ADMIN_FIRMWARE_ACTIVATE;

//
// NvmExpress Admin Firmware Image Download Command
//
typedef struct {
  //
  // CDW 10
  //
  UINT32 Numd;                /* Number of Dwords */
  //
  // CDW 11
  //
  UINT32 Ofst;                /* Offset */
} NVME_ADMIN_FIRMWARE_IMAGE_DOWNLOAD;

//
// NvmExpress Admin Get Features Command
//
typedef struct {
  //
  // CDW 10
  //
  UINT32 Fid:8;                /* Feature Identifier */
  UINT32 Sel:3;                /* Select */
  UINT32 Rsvd1:21;
} NVME_ADMIN_GET_FEATURES;

//
// NvmExpress Admin Get Log Page Command
//
typedef struct {
  //
  // CDW 10
  //
  UINT32 Lid:8;               /* Log Page Identifier */
    #define LID_ERROR_INFO   0x1
    #define LID_SMART_INFO   0x2
    #define LID_FW_SLOT_INFO 0x3
  UINT32 Rsvd1:8;
  UINT32 Numd:12;             /* Number of Dwords */
  UINT32 Rsvd2:4;             /* Reserved as of Nvm Express 1.1 Spec */
} NVME_ADMIN_GET_LOG_PAGE;

//
// NvmExpress Admin Set Features Command
//
typedef struct {
  //
  // CDW 10
  //
  UINT32 Fid:8;               /* Feature Identifier */
  UINT32 Rsvd1:23;
  UINT32 Sv:1;                /* Save */
} NVME_ADMIN_SET_FEATURES;

//
// NvmExpress Admin Format NVM Command
//
typedef struct {
  //
  // CDW 10
  //
  UINT32 Lbaf:4;              /* LBA Format */
  UINT32 Ms:1;                /* Metadata Settings */
  UINT32 Pi:3;                /* Protection Information */
  UINT32 Pil:1;               /* Protection Information Location */
  UINT32 Ses:3;               /* Secure Erase Settings */
  UINT32 Rsvd1:20;
} NVME_ADMIN_FORMAT_NVM;

//
// NvmExpress Admin Security Receive Command
//
typedef struct {
  //
  // CDW 10
  //
  UINT32 Rsvd1:8;
  UINT32 Spsp:16;             /* SP Specific */
  UINT32 Secp:8;              /* Security Protocol */
  //
  // CDW 11
  //
  UINT32 Al;                  /* Allocation Length */
} NVME_ADMIN_SECURITY_RECEIVE;

//
// NvmExpress Admin Security Send Command
//
typedef struct {
  //
  // CDW 10
  //
  UINT32 Rsvd1:8;
  UINT32 Spsp:16;             /* SP Specific */
  UINT32 Secp:8;              /* Security Protocol */
  //
  // CDW 11
  //
  UINT32 Tl;                  /* Transfer Length */
} NVME_ADMIN_SECURITY_SEND;

typedef union {
  NVME_ADMIN_IDENTIFY                   Identify;
  NVME_ADMIN_CRIOCQ                     CrIoCq;
  NVME_ADMIN_CRIOSQ                     CrIoSq;
  NVME_ADMIN_DEIOCQ                     DeIoCq;
  NVME_ADMIN_DEIOSQ                     DeIoSq;
  NVME_ADMIN_ABORT                      Abort;
  NVME_ADMIN_FIRMWARE_ACTIVATE          Activate;
  NVME_ADMIN_FIRMWARE_IMAGE_DOWNLOAD    FirmwareImageDownload;
  NVME_ADMIN_GET_FEATURES               GetFeatures;
  NVME_ADMIN_GET_LOG_PAGE               GetLogPage;
  NVME_ADMIN_SET_FEATURES               SetFeatures;
  NVME_ADMIN_FORMAT_NVM                 FormatNvm;
  NVME_ADMIN_SECURITY_RECEIVE           SecurityReceive;
  NVME_ADMIN_SECURITY_SEND              SecuritySend;
} NVME_ADMIN_CMD;

typedef struct {
  UINT32 Cdw10;
  UINT32 Cdw11;
  UINT32 Cdw12;
  UINT32 Cdw13;
  UINT32 Cdw14;
  UINT32 Cdw15;
} NVME_RAW;

typedef union {
  NVME_ADMIN_CMD Admin;   // Union of Admin commands
  NVME_CMD       Nvm;     // Union of Nvm commands
  NVME_RAW       Raw;
} NVME_PAYLOAD;

//
// Submission Queue
//
typedef struct {
  //
  // CDW 0, Common to all comnmands
  //
  UINT8  Opc;               // Opcode
  UINT8  Fuse:2;            // Fused Operation
  UINT8  Rsvd1:5;
  UINT8  Psdt:1;            // PRP or SGL for Data Transfer
  UINT16 Cid;               // Command Identifier

  //
  // CDW 1
  //
  UINT32 Nsid;              // Namespace Identifier

  //
  // CDW 2,3
  //
  UINT64 Rsvd2;

  //
  // CDW 4,5
  //
  UINT64 Mptr;              // Metadata Pointer

  //
  // CDW 6-9
  //
  UINT64 Prp[2];            // First and second PRP entries

  NVME_PAYLOAD Payload;

} NVME_SQ;

//
// Completion Queue
//
typedef struct {
  //
  // CDW 0
  //
  UINT32 Dword0;
  //
  // CDW 1
  //
  UINT32 Rsvd1;
  //
  // CDW 2
  //
  UINT16 Sqhd;              // Submission Queue Head Pointer
  UINT16 Sqid;              // Submission Queue Identifier
  //
  // CDW 3
  //
  UINT16 Cid;               // Command Identifier
  UINT16 Pt:1;              // Phase Tag
  UINT16 Sc:8;              // Status Code
  UINT16 Sct:3;             // Status Code Type
  UINT16 Rsvd2:2;
  UINT16 Mo:1;              // More
  UINT16 Dnr:1;             // Retry
} NVME_CQ;

//
// Nvme private data structure.
//
struct _PEI_NVME_CONTROLLER_PRIVATE_DATA {
  UINT32                                    Signature;
  EFI_PEI_PPI_DESCRIPTOR                    PassthruPpiDescriptor;
  NVM_EXPRESS_PASS_THRU_PPI                 Passthru;
  PEI_NVM_EXPRESS_PASS_THRU_MODE            PassThruMode;
  UINTN                                     MmioBase;
  //
  // pointer to identify controller data
  //
  NVME_ADMIN_CONTROLLER_DATA                *ControllerData;
  //
  // pointer to DMA buffer
  //
  UINT8                                     *Buffer;
  //
  // Pointers to 4kB aligned submission & completion queues.
  //
  NVME_SQ                                   *SqBuffer[NVME_MAX_QUEUES];
  NVME_CQ                                   *CqBuffer[NVME_MAX_QUEUES];
  //
  // Submission and completion queue indices.
  //
  NVME_SQTDBL                               SqTdbl[NVME_MAX_QUEUES];
  NVME_CQHDBL                               CqHdbl[NVME_MAX_QUEUES];
  UINT8                                     Pt[NVME_MAX_QUEUES];
  UINT16                                    Cid[NVME_MAX_QUEUES];
  //
  // Nvme controller capabilities
  //
  NVME_CAP                                  Cap;
};


//
// Unique signature for private data structure.
//
#define PEI_NVME_DEVICE_PRIVATE_DATA_SIGNATURE     SIGNATURE_32 ('P','N','V','D')

//
// Nvme device private data structure
//
struct _PEI_NVME_DEVICE_PRIVATE_DATA {
  UINT32                                   Signature;
  UINT32                                   NamespaceId;
  UINT64                                   NamespaceUuid;
  EFI_PEI_BLOCK_IO_MEDIA                   Media;
  EFI_PEI_BLOCK_IO2_MEDIA                  Media2;
  EFI_PEI_RECOVERY_BLOCK_IO_PPI            BlockIoPpi;
  EFI_PEI_PPI_DESCRIPTOR                   BlockIoPpiDescriptor;
  EFI_PEI_RECOVERY_BLOCK_IO2_PPI           BlockIo2Ppi;
  EFI_PEI_PPI_DESCRIPTOR                   BlockIo2PpiDescriptor;
  PEI_NVME_CONTROLLER_PRIVATE_DATA         *Controller;
};

//
// Statments to retrieve the private data from produced protocols.
//

#define PEI_NVME_DEVICE_PRIVATE_DATA_FROM_BLOCK_IO(a) \
  CR (a, \
      PEI_NVME_DEVICE_PRIVATE_DATA, \
      BlockIoPpi, \
      PEI_NVME_DEVICE_PRIVATE_DATA_SIGNATURE \
      )

#define PEI_NVME_DEVICE_PRIVATE_DATA_FROM_BLOCK_IO2(a) \
  CR (a, \
      PEI_NVME_DEVICE_PRIVATE_DATA, \
      BlockIo2Ppi, \
      PEI_NVME_DEVICE_PRIVATE_DATA_SIGNATURE \
      )

#pragma pack()

#endif
