/**@file
  This is the code that initializes eSPI.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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
#include <Library/PeiEspiInitLib.h>
#include <Library/DebugLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/EspiLib.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/PchPcrRegs.h>
#include <Register/SpiRegs.h>
#include <Register/PchRegsLpc.h>

/**
  Configure SPI/eSPI power management

  @param[in] SiPolicyPpi     Pointer to SI_POLICY_PPI
**/
STATIC
VOID
EspiConfigurePm (
  IN  SI_POLICY_PPI  *SiPolicy
  )
{
  EFI_STATUS          Status;
  PCH_GENERAL_CONFIG  *PchGeneralConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);
  //
  // Set SPI PCR 0xC004 bits 29, 10-8, 5-0 to 1b, 111b, 11111b
  if (PchGeneralConfig->PchMasterClockGating != 0) {
    PchPcrAndThenOr32 (PID_ESPISPI, R_SPI_PCR_CLK_CTL, ~0u, 0x2000073F);
  } else {
    PchPcrAndThenOr32 (PID_ESPISPI, R_SPI_PCR_CLK_CTL, 0xFFFF08C0, 0);
  }
  //
  // Clear SPI PCR 0xC008 bit 2,1,0
  // Set SPI PCR 0xC008 bit 5
  //
  if (PchGeneralConfig->PchMasterPowerGating != 0) {
    PchPcrAndThenOr32 (PID_ESPISPI, R_SPI_PCR_PWR_CTL, (UINT32)~(BIT2 | BIT1 | BIT0), BIT5);
  } else {
    PchPcrAndThenOr32 (PID_ESPISPI, R_SPI_PCR_CLK_CTL, 0, (BIT29 | BIT11));
    PchPcrAndThenOr32 (PID_ESPISPI, R_SPI_PCR_PWR_CTL, (UINT32)~(BIT5 | BIT3 | BIT2 | BIT1 | BIT0), 0);
  }
}

/**
  Configures PCH eSPI

  @param[in] SiPolicy           The Silicon Policy PPI instance
**/
VOID
EspiInit (
  IN  SI_POLICY_PPI  *SiPolicy
  )
{
  EFI_STATUS        Status;
  UINT32            Data32;
  UINT64            EspiPciBase;
  PCH_ESPI_CONFIG   *EspiConfig;

  DEBUG ((DEBUG_INFO, "[ConfigureEspi] Entry.\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gEspiConfigGuid, (VOID *) &EspiConfig);
  ASSERT_EFI_ERROR (Status);

  EspiPciBase = PCI_SEGMENT_LIB_ADDRESS (
                  DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                  DEFAULT_PCI_BUS_NUMBER_PCH,
                  PCI_DEVICE_NUMBER_PCH_LPC,
                  PCI_FUNCTION_NUMBER_PCH_LPC,
                  0
                  );

  EspiConfigurePm (SiPolicy);

  if ((PciSegmentRead32 (EspiPciBase + R_ESPI_CFG_PCBC) & B_ESPI_CFG_PCBC_ESPI_EN) == 0) {
    DEBUG ((DEBUG_INFO, "[ConfigureEspi] eSPI is disabled through strap\n"));
    return;
  }

  if (EspiConfig->LgmrEnable == TRUE) {
    PchLpcMemRangeSet (PCH_ESPI_LGMR_BASE_ADDRESS);
  }

  if (EspiConfig->HostC10ReportEnable == TRUE) {
    //
    // If desired enable HOST_C10 reporting in Virtual Wire Channel Error for Slave 0 (VWERR_SLV0)
    // No need to enable in both Slave 0 and Slave 1 because Slave 1 uses bits from Slave 0 register
    //
    PchPcrAndThenOr32 (
      PID_ESPISPI,
      R_ESPI_PCR_VWERR_SLV0,
      (UINT32) ~(B_ESPI_PCR_XERR_XNFES | B_ESPI_PCR_XERR_XFES),
      B_ESPI_PCR_VWERR_SLV0_VWHC10OE
      );
  }

  if (EspiConfig->BmeMasterSlaveEnabled == TRUE) {
    //
    // Set the BME bit on eSPI-MC
    //
    PciSegmentOr16 (EspiPciBase + PCI_COMMAND_OFFSET, (UINT32) EFI_PCI_COMMAND_BUS_MASTER);

    //
    // Set the BME bit on eSPI Slave 0 using the Tunneled Access
    //
    PchEspiSlaveGetConfig (0, R_ESPI_SLAVE_CHA_0_CAP_AND_CONF, &Data32);
    Data32 |= B_ESPI_SLAVE_BME;
    PchEspiSlaveSetConfig (0, R_ESPI_SLAVE_CHA_0_CAP_AND_CONF, Data32);

    Data32 = PchPcrRead32 (PID_ESPISPI, R_SPI_PCR_ESPI_SOFTSTRAPS);
    if (Data32 & B_SPI_PCR_ESPI_SLAVE) {
      //
      // Set the BME bit on eSPI Slave 1 using the Tunneled Access
      //
      PchEspiSlaveGetConfig (1, R_ESPI_SLAVE_CHA_0_CAP_AND_CONF, &Data32);
      Data32 |= B_ESPI_SLAVE_BME;
      PchEspiSlaveSetConfig (1, R_ESPI_SLAVE_CHA_0_CAP_AND_CONF, Data32);
    }
  }

  //
  // Set SBLCL bit after the initial eSPI link configuration to lock
  // access to Configuration Registers from offsets 0x0 - 0x7FF
  //
  PchPcrAndThenOr32 (
    PID_ESPISPI,
    (UINT16) R_ESPI_PCR_SLV_CFG_REG_CTL,
    ~0u,
    B_ESPI_PCR_SLV_CFG_REG_CTL_SBLCL
    );

  DEBUG ((DEBUG_INFO, "[ConfigureEspi] Exit.\n"));
}

