/** @file
  This PPI provides services that allow NVM Express commands to be sent to an
  NVM Express controller or to a specific namespace in a NVM Express controller.

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

#ifndef _NVM_EXPRESS_PASS_THRU_H_
#define _NVM_EXPRESS_PASS_THRU_H_

///
/// Global ID for the NVM_EXPRESS_PASS_THRU_PPI.
///
#define NVM_EXPRESS_PASS_THRU_PPI_GIUD \
  { \
    0xba45de19, 0x9220, 0x4349, { 0xbf, 0xed, 0x68, 0xf3, 0x89, 0x2c, 0x12, 0x9c } \
  }

#define PEI_NVME_BOOT_PARTITION_ACCESS_PPI_GIUD \
  { \
    0x475156fe, 0xaaf3, 0x43b8, { 0xb4, 0xa8, 0xb9, 0xef, 0xb4, 0x64, 0x14, 0xe7 } \
  }

//
// Forward declaration for the PEI_NVME_CONTROLLER_PPI.
//
typedef struct _NVM_EXPRESS_PASS_THRU_PPI  NVM_EXPRESS_PASS_THRU_PPI;

//
// If this bit is set, then the EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL interface is
// for directly addressable namespaces.
//
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_PHYSICAL        0x0001
//
// If this bit is set, then the EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL interface is
// for a single volume logical namespace comprised of multiple namespaces.
//
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_LOGICAL         0x0002
//
// If this bit is set, then the EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL interface
// supports non-blocking I/O.
//
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_NONBLOCKIO      0x0004
//
// If this bit is set, then the EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL interface
// supports NVM command set.
//
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_CMD_SET_NVM     0x0008

//
// FusedOperation
//
#define NORMAL_CMD                  0x00
#define FUSED_FIRST_CMD             0x01
#define FUSED_SECOND_CMD            0x02

typedef struct {
  UINT32                            Opcode:8;
  UINT32                            FusedOperation:2;
  UINT32                            Reserved:22;
} NVME_CDW0;

//
// Flags
//
#define CDW2_VALID                  0x01
#define CDW3_VALID                  0x02
#define CDW10_VALID                 0x04
#define CDW11_VALID                 0x08
#define CDW12_VALID                 0x10
#define CDW13_VALID                 0x20
#define CDW14_VALID                 0x40
#define CDW15_VALID                 0x80

//
// Queue Type
//
#define NVME_ADMIN_QUEUE            0x00
#define NVME_IO_QUEUE               0x01

typedef struct {
  NVME_CDW0                         Cdw0;
  UINT8                             Flags;
  UINT32                            Nsid;
  UINT32                            Cdw2;
  UINT32                            Cdw3;
  UINT32                            Cdw10;
  UINT32                            Cdw11;
  UINT32                            Cdw12;
  UINT32                            Cdw13;
  UINT32                            Cdw14;
  UINT32                            Cdw15;
} EFI_NVM_EXPRESS_COMMAND;

typedef struct {
  UINT32                            DW0;
  UINT32                            DW1;
  UINT32                            DW2;
  UINT32                            DW3;
} EFI_NVM_EXPRESS_COMPLETION;

typedef struct {
  UINT64                            CommandTimeout;
  VOID                              *TransferBuffer;
  UINT32                            TransferLength;
  VOID                              *MetadataBuffer;
  UINT32                            MetadataLength;
  UINT8                             QueueType;
  EFI_NVM_EXPRESS_COMMAND           *NvmeCmd;
  EFI_NVM_EXPRESS_COMPLETION        *NvmeCompletion;
} EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET;

typedef struct {
  UINT32          Attributes;
  UINT32          IoAlign;
  UINT32          NvmeVersion;
} PEI_NVM_EXPRESS_PASS_THRU_MODE;

//
// Protocol funtion prototypes
//
/**
  Sends an NVM Express Command Packet to an NVM Express controller or namespace.

  @param[in]     This                A pointer to the NVM_EXPRESS_PASS_THRU_PPI instance.
  @param[in]     NamespaceId         A 32 bit namespace ID as defined in the NVMe specification to which the NVM Express Command
                                     Packet will be sent.  A value of 0 denotes the NVM Express controller, a value of all 0xFF's
                                     (all bytes are 0xFF) in the namespace ID specifies that the command packet should be sent to
                                     all valid namespaces.
  @param[in,out] Packet              A pointer to the NVM Express Command Packet.

  @retval EFI_SUCCESS                The NVM Express Command Packet was sent by the host. TransferLength bytes were transferred
                                     to, or from DataBuffer.
  @retval EFI_DEVICE_ERROR           A device error occurred while attempting to send the NVM Express Command Packet.
  @retval EFI_INVALID_PARAMETER      NamespaceId or the contents of EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET are invalid. The NVM
                                     Express Command Packet was not sent, so no additional status information is available.
  @retval EFI_UNSUPPORTED            The command described by the NVM Express Command Packet is not supported by the NVM Express
                                     controller. The NVM Express Command Packet was not sent so no additional status information
                                     is available.
  @retval EFI_TIMEOUT                A timeout occurred while waiting for the NVM Express Command Packet to execute.

**/
typedef
EFI_STATUS
(EFIAPI *PEI_NVM_EXPRESS_PASS_THRU_PASSTHRU)(
  IN     NVM_EXPRESS_PASS_THRU_PPI                   *This,
  IN     UINT32                                      NamespaceId,
  IN OUT EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET    *Packet
  );

struct _NVM_EXPRESS_PASS_THRU_PPI {
  PEI_NVM_EXPRESS_PASS_THRU_MODE                     *Mode;
  PEI_NVM_EXPRESS_PASS_THRU_PASSTHRU                 PassThru;
};

extern EFI_GUID gPeiNvmExpressPassThruPpiGuid;

#endif
