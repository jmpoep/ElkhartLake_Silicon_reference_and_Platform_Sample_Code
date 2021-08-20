/** @file
  Pcie Root Port info header

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

#ifndef _PCH_PCIERP_INFO_H_
#define _PCH_PCIERP_INFO_H_

//
// Number of PCIe ports per PCIe controller
//
#define PCH_PCIE_CONTROLLER_PORTS                     4u

//
// Number of PCIe lanes per PCIe port
//
#define PCH_PCIE_LANES_PER_PORT                       1

//
// Number of PCIe lanes per PCIe controller
//
#define PCH_PCIE_LANES_PER_CONTROLLER                 (PCH_PCIE_CONTROLLER_PORTS * PCH_PCIE_LANES_PER_PORT)

//
// PCH PCI Express Root Ports for single function devices in
//
#define PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1       28
#define PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_2       29
#define PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_3       27
#define PCI_DEVICE_NUMBER_PCH_PCIE_ROOT_PORTS     28
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_1  0
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_2  1
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_3  2
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_4  3
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_5  4
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_6  5
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_7  6
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_8  7
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_9  0
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_10 1
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_11 2
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_12 3
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_13 4
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_14 5
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_15 6
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_16 7
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_17 0
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_18 1
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_19 2
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_20 3
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_21 4
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_22 5
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_23 6
#define PCI_FUNCTION_NUMBER_PCH_PCIE_ROOT_PORT_24 7

#endif
