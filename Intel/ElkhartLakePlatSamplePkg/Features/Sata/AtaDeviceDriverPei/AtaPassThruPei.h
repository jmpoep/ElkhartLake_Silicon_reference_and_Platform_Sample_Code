/** @file
  Install Pei phase ATA passthru PPI.

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

@par Specification
**/
#ifndef _PEI_ATA_PASS_THRU_H_
#define _PEI_ATA_PASS_THRU_H_

#include <Uefi.h>

#include <IndustryStandard/Pci.h>
#include <IndustryStandard/Atapi.h>
#include <IndustryStandard/Scsi.h>

#include <PiPei.h>

#include <Ppi/BlockIo.h>

#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/PeimEntryPoint.h>
#include <Library/PeiServicesLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PciLib.h>

#include <Ppi/AtaHostControllerPpi.h>
#include <Ppi/AtaPassThruPpi.h>
#include "AhciMode.h"
#include "IdeMode.h"

#define PEI_ATA_PASS_THRU_SIGNATURE  SIGNATURE_32 ('p', 'a', 'p', 't')
#define PEI_ATA_DEVICE_SIGNATURE     SIGNATURE_32 ('p', 'd', 'e', 'v')
#define ATA_NONBLOCKING_TASK_SIGNATURE  SIGNATURE_32 ('a', 't', 's', 'k')

typedef struct _ATA_NONBLOCK_TASK ATA_NONBLOCK_TASK;

typedef enum {
  EfiAtaIdeMode,
  EfiAtaAhciMode,
  EfiAtaRaidMode,
  EfiAtaUnknownMode
} EFI_ATA_HC_WORK_MODE;

typedef enum {
  EfiIdeCdrom,                  /* ATAPI CDROM */
  EfiIdeHarddisk,               /* Hard Disk */
  EfiPortMultiplier,            /* Port Multiplier */
  EfiIdeUnknown
} EFI_ATA_DEVICE_TYPE;

///
/// EFI_ATA_IDENTIFY_DATA & EFI_ATAPI_IDENTIFY_DATA structure
///
/// The definition of these two structures is not part of the protocol
/// definition because the ATA/ATAPI Specification controls the definition
/// of all the fields. The ATA/ATAPI Specification can obsolete old fields
/// or redefine existing fields.
typedef ATA_IDENTIFY_DATA   EFI_ATA_IDENTIFY_DATA;
typedef ATAPI_IDENTIFY_DATA EFI_ATAPI_IDENTIFY_DATA;

///
/// This flag indicates whether the IDENTIFY data is a response from an ATA device
/// (EFI_ATA_IDENTIFY_DATA) or response from an ATAPI device
/// (EFI_ATAPI_IDENTIFY_DATA).  According to the ATA/ATAPI specification,
/// EFI_IDENTIFY_DATA is for an ATA device if bit 15 of the Config field is zero.
/// The Config field is common to both EFI_ATA_IDENTIFY_DATA and
/// EFI_ATAPI_IDENTIFY_DATA.
///
#define   EFI_ATAPI_DEVICE_IDENTIFY_DATA  0x8000

///
/// EFI_IDENTIFY_DATA structure.
///
typedef union {
  ///
  /// The data that is returned by an ATA device upon successful completion
  /// of the ATA IDENTIFY_DEVICE command.
  ///
  EFI_ATA_IDENTIFY_DATA       AtaData;
  ///
  /// The data that is returned by an ATAPI device upon successful completion
  /// of the ATA IDENTIFY_PACKET_DEVICE command.
  ///
  EFI_ATAPI_IDENTIFY_DATA     AtapiData;
} EFI_IDENTIFY_DATA;

//
// Ahci mode device info
//
typedef struct {
  UINT32                            Signature;
  LIST_ENTRY                        Link;

  UINT16                            Port;
  UINT16                            PortMultiplier;
  EFI_ATA_DEVICE_TYPE               Type;

  EFI_IDENTIFY_DATA                 *IdentifyData;
} EFI_ATA_DEVICE_INFO;

typedef struct {
  UINT32                            Signature;

  EFI_ATA_PASS_THRU_MODE            AtaPassThruMode;
  PEI_ATA_PASS_THRU_PPI             PeiAtaPassThruPpi;
  EFI_PEI_PPI_DESCRIPTOR            PeiAtaPassThruPpiList;

  EFI_ATA_HC_WORK_MODE              Mode;
  EFI_AHCI_REGISTERS                AhciRegisters;
  UINTN                             MmioBase;
  //
  // The attached device list
  //
  LIST_ENTRY                        DeviceList;
  //
  // For AtaPassThru protocol, using the following bytes to record the previous call in
  // GetNextPort()/GetNextDevice().
  //
  UINT16                            PreviousPort;
  UINT16                            PreviousPortMultiplier;
} PEI_ATA_PASS_THRU_INSTANCE;

//
// Task for Non-blocking mode.
//
struct _ATA_NONBLOCK_TASK {
  UINT32                            Signature;
  LIST_ENTRY                        Link;

  UINT16                            Port;
  UINT16                            PortMultiplier;
  EFI_ATA_PASS_THRU_COMMAND_PACKET  *Packet;
  BOOLEAN                           IsStart;
  EFI_EVENT                         Event;
  UINT64                            RetryTimes;
  BOOLEAN                           InfiniteWait;
  VOID                              *Map;            // Pointer to map.
  VOID                              *TableMap;       // Pointer to PRD table map.
  EFI_ATA_DMA_PRD                   *MapBaseAddress; //  Pointer to range Base address for Map.
  UINTN                             PageCount;       //  The page numbers used by PCIO freebuffer.
};

//
// Timeout value which uses 100ns as a unit.
// It means 3 second span.
//
#define ATA_ATAPI_TIMEOUT           EFI_TIMER_PERIOD_SECONDS(3)
#define ATA_SPINUP_TIMEOUT          EFI_TIMER_PERIOD_SECONDS(10)        // RP_OVERRIDE_SKL

#define IS_ALIGNED(addr, size)      (((UINTN) (addr) & (size - 1)) == 0)

#define PEI_ATA_PASS_THRU_PRIVATE_DATA_FROM_THIS(a) \
  CR (a, \
      PEI_ATA_PASS_THRU_INSTANCE, \
      PeiAtaPassThruPpi, \
      PEI_ATA_PASS_THRU_SIGNATURE \
      )

#define PEI_ATA_DEVICE_INFO_FROM_THIS(a) \
  CR (a, \
      EFI_ATA_DEVICE_INFO, \
      Link, \
      PEI_ATA_DEVICE_SIGNATURE \
      );

#define ATA_NON_BLOCK_TASK_FROM_ENTRY(a) \
  CR (a, \
      ATA_NONBLOCK_TASK, \
      Link, \
      ATA_NONBLOCKING_TASK_SIGNATURE \
      );

/**
  Traverse the attached ATA devices list to find out the device to access.

  @param[in]  Instance            A pointer to the ATA_ATAPI_PASS_THRU_INSTANCE instance.
  @param[in]  Port                The port number of the ATA device to send the command.
  @param[in]  PortMultiplierPort  The port multiplier port number of the ATA device to send the command.
                                  If there is no port multiplier, then specify 0xFFFF.
  @param[in]  DeviceType          The device type of the ATA device.

  @retval     The pointer to the data structure of the device info to access.

**/
LIST_ENTRY *
EFIAPI
SearchDeviceInfoList (
  IN  PEI_ATA_PASS_THRU_INSTANCE     *Instance,
  IN  UINT16                         Port,
  IN  UINT16                         PortMultiplier,
  IN  EFI_ATA_DEVICE_TYPE            DeviceType
  );

/**
  Allocate device info data structure to contain device info.
  And insert the data structure to the tail of device list for tracing.

  @param[in]  Instance            A pointer to the ATA_ATAPI_PASS_THRU_INSTANCE instance.
  @param[in]  Port                The port number of the ATA device to send the command.
  @param[in]  PortMultiplierPort  The port multiplier port number of the ATA device to send the command.
                                  If there is no port multiplier, then specify 0xFFFF.
  @param[in]  DeviceType          The device type of the ATA device.
  @param[in]  IdentifyData        The data buffer to store the output of the IDENTIFY cmd.

  @retval EFI_SUCCESS             Successfully insert the ata device to the tail of device list.
  @retval EFI_OUT_OF_RESOURCES    Can not allocate enough resource for use.

**/
EFI_STATUS
EFIAPI
CreateNewDeviceInfo (
  IN  PEI_ATA_PASS_THRU_INSTANCE     *Instance,
  IN  UINT16                         Port,
  IN  UINT16                         PortMultiplier,
  IN  EFI_ATA_DEVICE_TYPE            DeviceType,
  IN  EFI_IDENTIFY_DATA              *IdentifyData
  );

/**
  Destroy all attached ATA devices info.

  @param[in]  Instance          A pointer to the ATA_ATAPI_PASS_THRU_INSTANCE instance.

**/
VOID
EFIAPI
DestroyDeviceInfoList (
  IN  PEI_ATA_PASS_THRU_INSTANCE  *Instance
  );


/**
  Sends an ATA command to an ATA device that is attached to the ATA controller. This function
  supports both blocking I/O and non-blocking I/O. The blocking I/O functionality is required,
  and the non-blocking I/O functionality is optional.

  @param[in]      This               A pointer to the EFI_ATA_PASS_THRU_PROTOCOL instance.
  @param[in]      Port               The port number of the ATA device to send the command.
  @param[in]      PortMultiplierPort The port multiplier port number of the ATA device to send the command.
                                     If there is no port multiplier, then specify 0xFFFF.
  @param[in, out] Packet             A pointer to the ATA command to send to the ATA device specified by Port
                                     and PortMultiplierPort.
  @param[in]      Event              If non-blocking I/O is not supported then Event is ignored, and blocking
                                     I/O is performed. If Event is NULL, then blocking I/O is performed. If
                                     Event is not NULL and non blocking I/O is supported, then non-blocking
                                     I/O is performed, and Event will be signaled when the ATA command completes.

  @retval EFI_SUCCESS                The ATA command was sent by the host. For bi-directional commands,
                                     InTransferLength bytes were transferred from InDataBuffer. For write and
                                     bi-directional commands, OutTransferLength bytes were transferred by OutDataBuffer.
  @retval EFI_BAD_BUFFER_SIZE        The ATA command was not executed. The number of bytes that could be transferred
                                     is returned in InTransferLength. For write and bi-directional commands,
                                     OutTransferLength bytes were transferred by OutDataBuffer.
  @retval EFI_NOT_READY              The ATA command could not be sent because there are too many ATA commands
                                     already queued. The caller may retry again later.
  @retval EFI_DEVICE_ERROR           A device error occurred while attempting to send the ATA command.
  @retval EFI_INVALID_PARAMETER      Port, PortMultiplierPort, or the contents of Acb are invalid. The ATA
                                     command was not sent, so no additional status information is available.

**/
EFI_STATUS
EFIAPI
PeiAtaPassThruPassThru (
  IN     PEI_ATA_PASS_THRU_PPI            *This,
  IN     UINT16                           Port,
  IN     UINT16                           PortMultiplierPort,
  IN OUT EFI_ATA_PASS_THRU_COMMAND_PACKET *Packet
  );

/**
  Used to retrieve the list of legal port numbers for ATA devices on an ATA controller.
  These can either be the list of ports where ATA devices are actually present or the
  list of legal port numbers for the ATA controller. Regardless, the caller of this
  function must probe the port number returned to see if an ATA device is actually
  present at that location on the ATA controller.

  The GetNextPort() function retrieves the port number on an ATA controller. If on input
  Port is 0xFFFF, then the port number of the first port on the ATA controller is returned
  in Port and EFI_SUCCESS is returned.

  If Port is a port number that was returned on a previous call to GetNextPort(), then the
  port number of the next port on the ATA controller is returned in Port, and EFI_SUCCESS
  is returned. If Port is not 0xFFFF and Port was not returned on a previous call to
  GetNextPort(), then EFI_INVALID_PARAMETER is returned.

  If Port is the port number of the last port on the ATA controller, then EFI_NOT_FOUND is
  returned.

  @param[in]     This           A pointer to the EFI_ATA_PASS_THRU_PROTOCOL instance.
  @param[in,out] Port           On input, a pointer to the port number on the ATA controller.
                                On output, a pointer to the next port number on the ATA
                                controller. An input value of 0xFFFF retrieves the first port
                                number on the ATA controller.

  @retval EFI_SUCCESS           The next port number on the ATA controller was returned in Port.
  @retval EFI_NOT_FOUND         There are no more ports on this ATA controller.
  @retval EFI_INVALID_PARAMETER Port is not 0xFFFF and Port was not returned on a previous call
                                to GetNextPort().

**/

EFI_STATUS
EFIAPI
PeiAtaPassThruGetNextPort (
  IN PEI_ATA_PASS_THRU_PPI      *This,
  IN OUT UINT16                 *Port
  );


/**
  Used to retrieve the list of legal port multiplier port numbers for ATA devices on a port of an ATA
  controller. These can either be the list of port multiplier ports where ATA devices are actually
  present on port or the list of legal port multiplier ports on that port. Regardless, the caller of this
  function must probe the port number and port multiplier port number returned to see if an ATA
  device is actually present.

  The GetNextDevice() function retrieves the port multiplier port number of an ATA device
  present on a port of an ATA controller.

  If PortMultiplierPort points to a port multiplier port number value that was returned on a
  previous call to GetNextDevice(), then the port multiplier port number of the next ATA device
  on the port of the ATA controller is returned in PortMultiplierPort, and EFI_SUCCESS is
  returned.

  If PortMultiplierPort points to 0xFFFF, then the port multiplier port number of the first
  ATA device on port of the ATA controller is returned in PortMultiplierPort and
  EFI_SUCCESS is returned.

  If PortMultiplierPort is not 0xFFFF and the value pointed to by PortMultiplierPort
  was not returned on a previous call to GetNextDevice(), then EFI_INVALID_PARAMETER
  is returned.

  If PortMultiplierPort is the port multiplier port number of the last ATA device on the port of
  the ATA controller, then EFI_NOT_FOUND is returned.

  @param[in]      This               A pointer to the EFI_ATA_PASS_THRU_PROTOCOL instance.
  @param[in]      Port               The port number present on the ATA controller.
  @param[in, out] PortMultiplierPort On input, a pointer to the port multiplier port number of an
                                     ATA device present on the ATA controller.
                                     If on input a PortMultiplierPort of 0xFFFF is specified,
                                     then the port multiplier port number of the first ATA device
                                     is returned. On output, a pointer to the port multiplier port
                                     number of the next ATA device present on an ATA controller.

  @retval EFI_SUCCESS                The port multiplier port number of the next ATA device on the port
                                     of the ATA controller was returned in PortMultiplierPort.
  @retval EFI_NOT_FOUND              There are no more ATA devices on this port of the ATA controller.
  @retval EFI_INVALID_PARAMETER      PortMultiplierPort is not 0xFFFF, and PortMultiplierPort was not
                                     returned on a previous call to GetNextDevice().

**/
EFI_STATUS
EFIAPI
PeiAtaPassThruGetNextDevice (
  IN PEI_ATA_PASS_THRU_PPI      *This,
  IN UINT16                     Port,
  IN OUT UINT16                 *PortMultiplierPort
  );

/**
  Initialize ATA host controller at AHCI mode.

  The function is designed to initialize ATA host controller.

  @param[in]  Instance          A pointer to the ATA_ATAPI_PASS_THRU_INSTANCE instance.

**/
EFI_STATUS
EFIAPI
AhciModeInitialization (
  IN  PEI_ATA_PASS_THRU_INSTANCE    *Instance
  );

/**
  Start a non data transfer on specific port.

  @param[in]       PciIo               The PCI IO protocol instance.
  @param[in]       AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param[in]       Port                The number of port.
  @param[in]       PortMultiplier      The timeout value of stop.
  @param[in]       AtapiCommand        The atapi command will be used for the
                                       transfer.
  @param[in]       AtapiCommandLength  The length of the atapi command.
  @param[in]       AtaCommandBlock     The EFI_ATA_COMMAND_BLOCK data.
  @param[in, out]  AtaStatusBlock      The EFI_ATA_STATUS_BLOCK data.
  @param[in]       Timeout             The timeout value of non data transfer, uses 100ns as a unit.
  @param[in]       Task                Optional. Pointer to the ATA_NONBLOCK_TASK
                                       used by non-blocking mode.

  @retval EFI_DEVICE_ERROR    The non data transfer abort with error occurs.
  @retval EFI_TIMEOUT         The operation is time out.
  @retval EFI_UNSUPPORTED     The device is not ready for transfer.
  @retval EFI_SUCCESS         The non data transfer executes successfully.

**/
EFI_STATUS
EFIAPI
AhciNonDataTransfer (
  IN     EFI_AHCI_REGISTERS            *AhciRegisters,
  IN     UINT8                         Port,
  IN     UINT8                         PortMultiplier,
  IN     EFI_AHCI_ATAPI_COMMAND        *AtapiCommand OPTIONAL,
  IN     UINT8                         AtapiCommandLength,
  IN     EFI_ATA_COMMAND_BLOCK         *AtaCommandBlock,
  IN OUT EFI_ATA_STATUS_BLOCK          *AtaStatusBlock,
  IN     UINT64                        Timeout,
  IN     ATA_NONBLOCK_TASK             *Task
  );

/**
  Start a DMA data transfer on specific port

  @param[in]       Instance            The ATA_ATAPI_PASS_THRU_INSTANCE protocol instance.
  @param[in]       AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param[in]       Port                The number of port.
  @param[in]       PortMultiplier      The timeout value of stop.
  @param[in]       AtapiCommand        The atapi command will be used for the
                                       transfer.
  @param[in]       AtapiCommandLength  The length of the atapi command.
  @param[in]       Read                The transfer direction.
  @param[in]       AtaCommandBlock     The EFI_ATA_COMMAND_BLOCK data.
  @param[in, out]  AtaStatusBlock      The EFI_ATA_STATUS_BLOCK data.
  @param[in, out]  MemoryAddr          The pointer to the data buffer.
  @param[in]       DataCount           The data count to be transferred.
  @param[in]       Timeout             The timeout value of non data transfer, uses 100ns as a unit.
  @param[in]       Task                Optional. Pointer to the ATA_NONBLOCK_TASK
                                       used by non-blocking mode.

  @retval EFI_DEVICE_ERROR    The DMA data transfer abort with error occurs.
  @retval EFI_TIMEOUT         The operation is time out.
  @retval EFI_UNSUPPORTED     The device is not ready for transfer.
  @retval EFI_SUCCESS         The DMA data transfer executes successfully.

**/
EFI_STATUS
EFIAPI
AhciDmaTransfer (
  IN     PEI_ATA_PASS_THRU_INSTANCE   *Instance,
  IN     EFI_AHCI_REGISTERS           *AhciRegisters,
  IN     UINT8                        Port,
  IN     UINT8                        PortMultiplier,
  IN     EFI_AHCI_ATAPI_COMMAND       *AtapiCommand OPTIONAL,
  IN     UINT8                        AtapiCommandLength,
  IN     BOOLEAN                      Read,
  IN     EFI_ATA_COMMAND_BLOCK        *AtaCommandBlock,
  IN OUT EFI_ATA_STATUS_BLOCK         *AtaStatusBlock,
  IN OUT VOID                         *MemoryAddr,
  IN     UINT32                       DataCount,
  IN     UINT64                       Timeout,
  IN     ATA_NONBLOCK_TASK            *Task
  );

/**
  Start a PIO data transfer on specific port.

  @param[in]       PciIo               The PCI IO protocol instance.
  @param[in]       AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param[in]       Port                The number of port.
  @param[in]       PortMultiplier      The timeout value of stop.
  @param[in]       AtapiCommand        The atapi command will be used for the
                                       transfer.
  @param[in]       AtapiCommandLength  The length of the atapi command.
  @param[in]       Read                The transfer direction.
  @param[in]       AtaCommandBlock     The EFI_ATA_COMMAND_BLOCK data.
  @param[in, out]  AtaStatusBlock      The EFI_ATA_STATUS_BLOCK data.
  @param[in, out]  MemoryAddr          The pointer to the data buffer.
  @param[in]       DataCount           The data count to be transferred.
  @param[in]       Timeout             The timeout value of non data transfer, uses 100ns as a unit.
  @param[in]       Task                Optional. Pointer to the ATA_NONBLOCK_TASK
                                       used by non-blocking mode.

  @retval EFI_DEVICE_ERROR    The PIO data transfer abort with error occurs.
  @retval EFI_TIMEOUT         The operation is time out.
  @retval EFI_UNSUPPORTED     The device is not ready for transfer.
  @retval EFI_SUCCESS         The PIO data transfer executes successfully.

**/
EFI_STATUS
EFIAPI
AhciPioTransfer (
  IN     EFI_AHCI_REGISTERS         *AhciRegisters,
  IN     UINT8                      Port,
  IN     UINT8                      PortMultiplier,
  IN     EFI_AHCI_ATAPI_COMMAND     *AtapiCommand OPTIONAL,
  IN     UINT8                      AtapiCommandLength,
  IN     BOOLEAN                    Read,
  IN     EFI_ATA_COMMAND_BLOCK      *AtaCommandBlock,
  IN OUT EFI_ATA_STATUS_BLOCK       *AtaStatusBlock,
  IN OUT VOID                       *MemoryAddr,
  IN     UINT32                     DataCount,
  IN     UINT64                     Timeout
  );

/**
  Initializes the ATA passthru PPI.

  @param[in]  FileHandle           Handle of the file being invoked.
  @param[in]  PeiServices          Describes the list of possible PEI Services.

  @retval     EFI_SUCCESS          Operation performed successfully.
  @retval     EFI_OUT_OF_RESOURCES Not enough memory to allocate.

**/
EFI_STATUS
EFIAPI
InitializeAtaPassThru (
  IN EFI_PEI_FILE_HANDLE        FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  );

#endif
