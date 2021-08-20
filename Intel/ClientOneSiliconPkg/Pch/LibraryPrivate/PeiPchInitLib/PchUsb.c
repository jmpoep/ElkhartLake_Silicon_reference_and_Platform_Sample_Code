/** @file
  Initializes both PCH Host and Device USB Controllers.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2020 Intel Corporation.

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
#include "PchUsb.h"
#include <Ppi/Spi.h>
#include <Library/PeiHsioLib.h>
#include <Library/UsbHostControllerInitLib.h>
#include <Library/UsbDeviceControllerInitLib.h>
#include <Library/PostCodeLib.h>
#include <Library/UsbLib.h>
#include <Library/Usb2PhyLib.h>
#include <Register/PchRegs.h>
#include <Register/UsbRegs.h>
#include <Register/PchRegsHsio.h>

/**
  Tune the USB 3.0 signals quality.

  @param[in]  Usb3HsioConfig      The USB3_HSIO_CONFIG policy instance
  @param[in]  XhciPciBase         XHCI PCI CFG Base Address
**/
STATIC
VOID
XhciUsb3HsioTuning (
  IN  USB3_HSIO_CONFIG      *Usb3HsioConfig,
  IN  CONST UINT64          XhciPciBase
  )
{
  HSIO_LANE  HsioLane;
  UINT8      Index;
  UINT8      LaneNum;
  UINT32     Data32And;
  UINT32     Data32Or;

  for (Index = 0; Index < GetPchXhciMaxUsb3PortNum (); Index++) {
    if ((Usb3HsioConfig->Port[Index].HsioTxDeEmphEnable == FALSE) &&
        (Usb3HsioConfig->Port[Index].HsioTxDownscaleAmpEnable == FALSE)) {
      continue;
    }

    if (PchFiaGetUsb3LaneNum (Index, &LaneNum)) {
      HsioGetLane (LaneNum, &HsioLane);
      //
      //Step 1: Make changes to any of the TX (Transmit) ModPHY Register Bit Fields
      //
      //
      // USB 3.0 TX Output -3.5dB De-Emphasis Adjustment Setting (ow2tapgen2deemph3p5)
      // HSIO_TX_DWORD5[21:16]
      //
      if (Usb3HsioConfig->Port[Index].HsioTxDeEmphEnable == TRUE) {
        HsioLaneAndThenOr32WithSusWrite (
          &HsioLane,
          R_HSIO_PCR_TX_DWORD5,
          (UINT32) ~B_HSIO_PCR_TX_DWORD5_OW2TAPGEN2DEEMPH3P5_5_0,
          (UINT32) (Usb3HsioConfig->Port[Index].HsioTxDeEmph << N_HSIO_PCR_TX_DWORD5_OW2TAPGEN2DEEMPH3P5_5_0)
          );
      }

      //
      // USB 3.0 TX Output Downscale Amplitude Adjustment (orate01margin)
      // HSIO_TX_DWORD8[21:16]
      //
      if (Usb3HsioConfig->Port[Index].HsioTxDownscaleAmpEnable == TRUE) {
        HsioLaneAndThenOr32WithSusWrite (
          &HsioLane,
          R_HSIO_PCR_TX_DWORD8,
          (UINT32) ~B_HSIO_PCR_TX_DWORD8_ORATE01MARGIN_5_0,
          (UINT32) (Usb3HsioConfig->Port[Index].HsioTxDownscaleAmp << N_HSIO_PCR_TX_DWORD8_ORATE01MARGIN_5_0)
          );
      }

      Data32And = ~0u;
      Data32Or  = 0;

      //
      // USB 3.0 TX Unique Transition Bit Scale for rate 3 (rate3UniqTranScale)
      // HSIO_TX_DWORD9[6:0]
      //
      if (Usb3HsioConfig->Port[Index].HsioTxRate3UniqTranEnable == TRUE) {
        Data32And &= (UINT32) ~B_HSIO_PCR_TX_DWORD9_RATE3UNIQTRANSCALE_6_0;
        Data32Or  |= (UINT32) (B_HSIO_PCR_TX_DWORD9_RATE3UNIQTRANENABLE | (Usb3HsioConfig->Port[Index].HsioTxRate3UniqTran << N_HSIO_PCR_TX_DWORD9_RATE3UNIQTRANSCALE_6_0));
      }

      //
      // USB 3.0 TX Unique Transition Bit Scale for rate 2 (rate2UniqTranScale)
      // HSIO_TX_DWORD9[14:8]
      //
      if (Usb3HsioConfig->Port[Index].HsioTxRate2UniqTranEnable == TRUE) {
        Data32And &= (UINT32) ~B_HSIO_PCR_TX_DWORD9_RATE2UNIQTRANSCALE_6_0;
        Data32Or  |= (UINT32) (B_HSIO_PCR_TX_DWORD9_RATE2UNIQTRANENABLE | (Usb3HsioConfig->Port[Index].HsioTxRate2UniqTran << N_HSIO_PCR_TX_DWORD9_RATE2UNIQTRANSCALE_6_0));
      }

      //
      // USB 3.0 TX Unique Transition Bit Scale for rate 1 (rate1UniqTranScale)
      // HSIO_TX_DWORD9[22:16]
      //
      if (Usb3HsioConfig->Port[Index].HsioTxRate1UniqTranEnable == TRUE) {
        Data32And &= (UINT32) ~B_HSIO_PCR_TX_DWORD9_RATE1UNIQTRANSCALE_6_0;
        Data32Or  |= (UINT32) (B_HSIO_PCR_TX_DWORD9_RATE1UNIQTRANENABLE | (Usb3HsioConfig->Port[Index].HsioTxRate1UniqTran << N_HSIO_PCR_TX_DWORD9_RATE1UNIQTRANSCALE_6_0));
      }

      //
      // USB 3.0 TX Unique Transition Bit Scale for rate 0 (rate0UniqTranScale)
      // HSIO_TX_DWORD9[30:24]
      //
      if (Usb3HsioConfig->Port[Index].HsioTxRate0UniqTranEnable == TRUE) {
        Data32And &= (UINT32) ~B_HSIO_PCR_TX_DWORD9_RATE0UNIQTRANSCALE_6_0;
        Data32Or  |= (UINT32) (B_HSIO_PCR_TX_DWORD9_RATE0UNIQTRANENABLE | (Usb3HsioConfig->Port[Index].HsioTxRate0UniqTran << N_HSIO_PCR_TX_DWORD9_RATE0UNIQTRANSCALE_6_0));
      }

      if (Usb3HsioConfig->Port[Index].HsioTxRate3UniqTranEnable ||
          Usb3HsioConfig->Port[Index].HsioTxRate2UniqTranEnable ||
          Usb3HsioConfig->Port[Index].HsioTxRate1UniqTranEnable ||
          Usb3HsioConfig->Port[Index].HsioTxRate0UniqTranEnable) {
        HsioLaneAndThenOr32WithSusWrite (
          &HsioLane,
          R_HSIO_PCR_TX_DWORD9,
          Data32And,
          Data32Or
          );
      }

      //
      // Signed Magnitude number added to the CTLE code.(ctle_adapt_offset_cfg_4_0)
      // HSIO_RX_DWORD25 [20:16]
      //
      if (Usb3HsioConfig->Port[Index].HsioCtrlAdaptOffsetCfgEnable == TRUE) {
        HsioLaneAndThenOr32WithSusWrite (
          &HsioLane,
          R_HSIO_PCR_RX_DWORD25,
          (UINT32) ~B_HSIO_PCR_RX_DWORD25_CTLE_ADAPT_OFFSET_CFG_4_0,
          (UINT32) (Usb3HsioConfig->Port[Index].HsioCtrlAdaptOffsetCfg << N_HSIO_PCR_RX_DWORD25_CTLE_ADAPT_OFFSET_CFG_4_0)
          );
      }

      Data32And = ~0u;
      Data32Or  = 0;

      //
      // LFPS filter select for n (filter_sel_n_2_0)
      // HSIO_RX_DWORD51 [29:27]
      //
      if (Usb3HsioConfig->Port[Index].HsioFilterSelNEnable == TRUE) {
        Data32And &= (UINT32)~B_HSIO_PCR_RX_DWORD51_FILTER_SEL_N_2_0;
        Data32Or  |= (Usb3HsioConfig->Port[Index].HsioFilterSelN << N_HSIO_PCR_RX_DWORD51_FILTER_SEL_N_2_0);
      }

      //
      // LFPS filter select for p (filter_sel_p_2_0)
      // HSIO_RX_DWORD51 [26:24]
      //
      if (Usb3HsioConfig->Port[Index].HsioFilterSelPEnable == TRUE) {
        Data32And &= (UINT32)~B_HSIO_PCR_RX_DWORD51_FILTER_SEL_P_2_0;
        Data32Or  |= (Usb3HsioConfig->Port[Index].HsioFilterSelP << N_HSIO_PCR_RX_DWORD51_FILTER_SEL_P_2_0);
      }

      //
      // Controls the input offset (olfpscfgpullupdwnres_sus_usb_2_0)
      // HSIO_RX_DWORD51 [2:0]
      //
      if (Usb3HsioConfig->Port[Index].HsioOlfpsCfgPullUpDwnResEnable == TRUE) {
        Data32And &= (UINT32)~B_HSIO_PCR_RX_DWORD51_OLFPSCFGPULLUPDWNRES_SUS_USB_2_0;
        Data32Or  |= (UINT32) (Usb3HsioConfig->Port[Index].HsioOlfpsCfgPullUpDwnRes);
      }

      if (Usb3HsioConfig->Port[Index].HsioOlfpsCfgPullUpDwnResEnable ||
          Usb3HsioConfig->Port[Index].HsioFilterSelNEnable ||
          Usb3HsioConfig->Port[Index].HsioFilterSelPEnable) {
        HsioLaneAndThenOr32WithSusWrite (
          &HsioLane,
          R_HSIO_PCR_RX_DWORD51,
          Data32And,
          Data32Or
          );
      }

      //
      // Step 2: Clear HSIO_TX_DWORD19 Bit[1] (o_calcinit bit) to 0b
      //
      HsioLaneAndThenOr32WithSusWrite (
        &HsioLane,
        R_HSIO_PCR_TX_DWORD19,
        (UINT32) ~(BIT1),
        (UINT32) (0)
        );

      //
      // Step 3: Set HSIO_TX_DWORD19 Bit[1] (o_calcinit) to 1b
      //
      HsioLaneAndThenOr32WithSusWrite (
        &HsioLane,
        R_HSIO_PCR_TX_DWORD19,
        (UINT32) ~(0),
        (UINT32) (BIT1)
        );
    }
  }
}

/*
  Performs PCH USB Controllers initialization

  @param[in] SiPolicy     The Silicon Policy PPI instance
*/
VOID
PchUsbConfigure (
  IN  SI_POLICY_PPI               *SiPolicy
  )
{
  EFI_STATUS            Status;
  USB_CONFIG            *UsbConfig;
  USB2_PHY_CONFIG       *Usb2PhyConfig;
  USB3_HSIO_CONFIG      *Usb3HsioConfig;
  UINT64                ControllerPciMmBase;
  UINT8                 InterruptPin;
  UINT8                 Irq;
  UINT32                Data32Or;
  UINT32                Data32And;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gUsbConfigGuid, (VOID *) &UsbConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gUsb2PhyConfigGuid, (VOID *) &Usb2PhyConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gUsb3HsioConfigGuid, (VOID *) &Usb3HsioConfig);
  ASSERT_EFI_ERROR (Status);

  ControllerPciMmBase = PCI_SEGMENT_LIB_ADDRESS (
                          DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                          DEFAULT_PCI_BUS_NUMBER_PCH,
                          PCI_DEVICE_NUMBER_PCH_XHCI,
                          PCI_FUNCTION_NUMBER_PCH_XHCI,
                          0
                          );

  //
  // Tune the USB 2.0 high-speed signals quality.
  //
  PostCode (0xB04);
  Usb2PhyProgramming (Usb2PhyConfig);

  //
  // Configure USB OTG
  //
  UsbConfigureOtg (UsbConfig);

  //
  // Configure USB3 ModPHY turning.
  //
  PostCode (0xB05);
  XhciUsb3HsioTuning (Usb3HsioConfig, ControllerPciMmBase);

  //
  // Configure PCH xHCI
  //
  PostCode (0xB06);
  XhciConfigure (UsbConfig, ControllerPciMmBase);

  if (PciSegmentRead16 (ControllerPciMmBase + PCI_VENDOR_ID_OFFSET) != 0xFFFF) {
    ///
    /// Configure xHCI interrupt
    ///
    InterruptPin = ItssGetDevIntPin (SiPolicy, PCI_DEVICE_NUMBER_PCH_XHCI, PCI_FUNCTION_NUMBER_PCH_XHCI);

    PciSegmentWrite8 (ControllerPciMmBase + PCI_INT_PIN_OFFSET, InterruptPin);
  }

  //
  // Set all necessary lock bits in xHCI controller
  //
  XhciLockConfiguration (UsbConfig, ControllerPciMmBase);

  //
  // Configure PCH OTG (xDCI)
  //
  PostCode (0xB08);
  ControllerPciMmBase = PCI_SEGMENT_LIB_ADDRESS (
                          DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                          DEFAULT_PCI_BUS_NUMBER_PCH,
                          PCI_DEVICE_NUMBER_PCH_XDCI,
                          PCI_FUNCTION_NUMBER_PCH_XDCI,
                          0
                          );

  XdciConfigure (UsbConfig, ControllerPciMmBase);

  if (PciSegmentRead16 (ControllerPciMmBase + PCI_VENDOR_ID_OFFSET) != 0xFFFF) {
    ///
    /// Configure xDCI interrupt
    ///
    ItssGetDevIntConfig (
      SiPolicy,
      PCI_DEVICE_NUMBER_PCH_XDCI,
      PCI_FUNCTION_NUMBER_PCH_XDCI,
      &InterruptPin,
      &Irq
      );

    //
    // Set Interrupt Pin and IRQ number
    //
    Data32Or = (UINT32) ((InterruptPin << N_OTG_PCR_PCICFGCTRL_INT_PIN) |
                          (Irq << N_OTG_PCR_PCICFGCTRL_PCI_IRQ));
    Data32And =~(UINT32) (B_OTG_PCR_PCICFGCTRL_PCI_IRQ | B_OTG_PCR_PCICFGCTRL_ACPI_IRQ | B_OTG_PCR_PCICFGCTRL_INT_PIN | B_OTG_PCR_PCICFGCTRL_ACPI_INT_EN);

    PchPcrAndThenOr32 (PID_OTG, R_OTG_PCR_PCICFGCTRL1, Data32And, Data32Or);
  }
}
