/** @file
  I2C bus configuration management interface

  The I2C host driver uses this API to configure the
  switches and multiplexers in the I2C bus to gain access
  to the desired I2C device at its maximum clock frequency.

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

#ifndef __I2C_BUS_CONFIGURATION_MANAGEMENT_H__
#define __I2C_BUS_CONFIGURATION_MANAGEMENT_H__

#include <Protocol/I2cMaster.h>

///
/// I2C bus configuration management protocol
///
/// The I2C driver stack uses the concept of an I2C bus configuration
/// as a way to describe a particular state of the switches and
/// multiplexers in the I2C bus.
///
/// A simple I2C bus does not have any multiplexers or switches is
/// described to the I2C driver stack with a single I2C bus configuration.
///
/// An I2C bus with switches and multiplexers use an I2C bus configuration
/// to describe each of the unique settings for the switches and multiplexers.
/// However the I2C platform driver only needs to define the I2C bus
/// configurations that the software uses, which is a subset of the
/// total.
///
/// The I2C bus configuration description includes a list of I2C devices
/// which may be accessed when this I2C bus configuration is enabled.
/// I2C devices before a switch or multiplexer should be included in one
/// I2C bus configuration while I2C devices after a switch or multiplexer
/// should be on another I2C bus configuration.
///
/// The I2C bus configuration management protocol is an optional
/// protocol provided by the I2C platform driver.  When the I2C bus
/// configuration protocol is not defined the host driver assumes a
/// single I2C bus configuration and operates the I2C bus at 100 KHz.
/// When the I2C bus configuration protocol is available, the I2C host
/// driver uses the I2C bus configuration protocol to call into the
/// I2C platform driver to set the switches and multiplexers and set
/// the maximum I2C bus frequency.
///
/// The platform designers determine the maximum I2C bus frequency by
/// selecting a frequency which supports all of the I2C devices on the
/// I2C bus for the setting of switches and multiplexers.  The platform
/// designers must validate this against the I2C device data sheets and
/// any limits of the I2C controller or bus length.
///
/// The I2C host driver uses an index into a list or array of I2C bus
/// configurations to keep the platform implementation hidden from the
/// rest of the I2C stack.  The protocol exposes BusConfigurationCount
/// to enable the I2C host driver to perform bounds checking on the I2C
/// bus configuration value supplied by the upper layers.  The I2C bus
/// layer also is told during the I2C device enumeration which I2C bus
/// configuration is in use for each of the I2C devices.  While this
/// is hidden from the upper layers the I2C bus configuration is
/// provided to the I2C host driver when performing I2C requests.
///
/// When the I2C bus configuration protocol is available, the I2C host
/// driver calls EnableBusConfiguration to enable access to the necessary
/// I2C bus configuration.  This host driver may optimize calls to
/// EnableBusConfiguration by only calling the routine only when the I2C
/// bus configuration value changes between I2C requests.
///
/// When I2C operations are necessary on the same I2C bus to change I2C
/// GPIO devices, multiplexers or switches, the I2C platform layer uses
/// the I2C master protocol to perform the necessary I2C operations.
///
/// It is up to the I2C platform driver to choose the proper I2C bus
/// configuration when ExitBootServices is called.
///
typedef struct _EFI_I2C_BUS_CONFIGURATION_MANAGEMENT_PROTOCOL EFI_I2C_BUS_CONFIGURATION_MANAGEMENT_PROTOCOL;


/**
  Enable access to an I2C bus configuration.

  This routine must be called at or below TPL_NOTIFY.  For synchronous
  requests this routine must be called at or below TPL_CALLBACK.

  Reconfigure the switches and multiplexers in the I2C bus to enable
  access to a specific I2C bus configuration.  Also select the maximum
  clock frequency for this I2C bus configuration.

  This routine uses the I2cMaster protocol when the platform routine
  needs to perform I2C operations on the local bus.  This eliminates
  any recursion in the I2C stack for configuration operations on the
  local bus.  This works because the local I2C bus is idle while the
  I2C bus configuration is being enabled.

  The platform layer must perform I2C operations on other I2C busses
  by using the EFI_I2C_HOST_PROTOCOL or third party driver interface
  for the specific device.  This requirement is because the I2C host
  driver controls the flow of requests to the I2C conroller.  Use the
  EFI_I2C_HOST_PROTOCOL when the device is not defined in the platform's
  ACPI tables.  Use the third party driver when it is available or
  EFI_I2C_BUS_PROTOCOL when the thrid party driver is not available
  but the device is defined in the platform's ACPI tables.

  @param[in]  This            Address of an EFI_I2C_BUS_CONFIGURATION_MANAGEMENT_PROTOCOL
                              structure
  @param[in]  I2cBusConfiguration Index into a list or array of I2C bus
                                  configurations.
  @param[in]  I2cMaster       Address of an EFI_I2C_MASTER_PROTOCOL
                              structure.  This protocol may only be used
                              for this specific operation and should not
                              be referenced after this operation completes!
  @param[in]  Event           Event to set when the operation is
                              complete.
  @param[out] Status          Buffer to receive the operation
                              status.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval EFI_DEVICE_ERROR      There was an I2C error (NACK) during the operation.
                                This could indicate the slave device is not present.
  @retval EFI_INVALID_PARAMETER I2cMaster is NULL
  @retval EFI_INVALID_PARAMETER TPL is too high
  @retval EFI_NO_MAPPING        Invalid I2cBusConfiguration value
  @retval EFI_NO_RESPONSE       The I2C device is not responding to the
                                slave address.  EFI_DEVICE_ERROR may also be
                                returned if the controller can not distinguish
                                when the NACK occurred.
  @retval EFI_NOT_FOUND         I2C slave address exceeds maximum address
  @retval EFI_NOT_READY         I2C bus is busy or operation pending, wait for
                                the event and then read status.
  @retval EFI_OUT_OF_RESOURCES  Insufficient memory for I2C operation
  @retval EFI_TIMEOUT           The transaction did not complete within an internally
                                specified timeout period.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_I2C_BUS_CONFIGURATION_MANAGEMENT_ENABLE_I2C_BUS_CONFIGURATION) (
  IN CONST EFI_I2C_BUS_CONFIGURATION_MANAGEMENT_PROTOCOL *This,
  IN UINTN I2cBusConfiguration,
  IN CONST EFI_I2C_MASTER_PROTOCOL *I2cMaster,
  IN EFI_EVENT Event OPTIONAL,
  IN EFI_STATUS *Status OPTIONAL
  );


///
/// I2C bus configuration management protocol
///
struct _EFI_I2C_BUS_CONFIGURATION_MANAGEMENT_PROTOCOL {
  ///
  /// Enable an I2C bus configuration for use
  ///
  EFI_I2C_BUS_CONFIGURATION_MANAGEMENT_ENABLE_I2C_BUS_CONFIGURATION EnableI2cBusConfiguration;

  ///
  /// Number of switch and multiplexer configurations for this
  /// I2C bus.
  ///
  UINTN I2cBusConfigurationCount;
};

#endif  //  __I2C_BUS_CONFIGURATION_MANAGEMENT_H__
