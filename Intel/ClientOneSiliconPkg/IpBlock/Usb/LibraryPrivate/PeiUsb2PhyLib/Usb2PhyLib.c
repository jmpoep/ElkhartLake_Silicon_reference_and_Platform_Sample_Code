/** @file
  Library for USB2 PHY programming for PCH.

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
#include <Library/Usb2PhyLib.h>

#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchSbiAccessLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include <Library/PeiHsioLib.h>
#include <Register/UsbRegs.h>
#include <Register/DciRegs.h>
#include <Register/PchPcrRegs.h>

//
// Structure for USB2 PHY reference frequency dependent parameters
//
typedef struct {
  UINT32    AndMask;  // Bitwise AND mask for programming
  UINT32    Value[3]; // Array of values for each USB2 PHY reference frequency
} USB2_PHY_REF_FREQ_PARAM;

//
// USB2 PHY reference frequency parameters list
//
typedef struct {
  USB2_PHY_REF_FREQ_PARAM   Plldivratios_0;
  USB2_PHY_REF_FREQ_PARAM   Sfrconfig_0;
  USB2_PHY_REF_FREQ_PARAM   Config_0;
  USB2_PHY_REF_FREQ_PARAM   Config_3;
  USB2_PHY_REF_FREQ_PARAM   Dft_1;
} USB2_PHY_FREQ_PARAMS;

//
// USB2 PHY parameters which depends on reference clock frequenc
//
USB2_PHY_FREQ_PARAMS Usb2PhyFreqParams = {
  // PLLDIVRATIOS_0
  {
    (UINT32)~(B_USB2_PCR_PLLDIVRATIOS_0_FBDIVRATIO),
    {
      (UINT32) (100 << N_USB2_PCR_PLLDIVRATIOS_0_FBDIVRATIO),
      (UINT32) (80 << N_USB2_PCR_PLLDIVRATIOS_0_FBDIVRATIO),
      (UINT32) (20 << N_USB2_PCR_PLLDIVRATIOS_0_FBDIVRATIO)
    }
  },
  // SFRCONFIG_0
  {
    (UINT32)~(B_USB2_PCR_SFRCONFIG_0_SFRTIMER_COEF),
    {
      (UINT32) (0x0 << N_USB2_PCR_SFRCONFIG_0_SFRTIMER_COEF),
      (UINT32) (0x1 << N_USB2_PCR_SFRCONFIG_0_SFRTIMER_COEF),
      (UINT32) (0x4 << N_USB2_PCR_SFRCONFIG_0_SFRTIMER_COEF)
    }
  },
  // CONFIG_0
  {
    (UINT32)~(B_USB2_PCR_CONFIG_0_INT_COEFF | B_USB2_PCR_CONFIG_0_PROP_COEFF),
    {
      ((0x1A << N_USB2_PCR_CONFIG_0_INT_COEFF) | (0xD << N_USB2_PCR_CONFIG_0_PROP_COEFF)),
      ((0x19 << N_USB2_PCR_CONFIG_0_INT_COEFF) | (0xD << N_USB2_PCR_CONFIG_0_PROP_COEFF)),
      ((0x19 << N_USB2_PCR_CONFIG_0_INT_COEFF) | (0xE << N_USB2_PCR_CONFIG_0_PROP_COEFF))
    }
  },
  // CONFIG_3
  {
    (UINT32)~(B_USB2_PCR_CONFIG_3_SFRCALIB_FMINCNT | B_USB2_PCR_CONFIG_3_SFRCALIB_FMAXCNT |
              B_USB2_PCR_CONFIG_3_TDCCALIB_OSCCNT  | B_USB2_PCR_CONFIG_3_LOCKTIMERCNT_TH),
    {
      ((0x59 << N_USB2_PCR_CONFIG_3_SFRCALIB_FMINCNT) | (0xE9 << N_USB2_PCR_CONFIG_3_SFRCALIB_FMAXCNT) |
       (0x4D << N_USB2_PCR_CONFIG_3_TDCCALIB_OSCCNT)  | (0xC << N_USB2_PCR_CONFIG_3_LOCKTIMERCNT_TH)),
      ((0x47 << N_USB2_PCR_CONFIG_3_SFRCALIB_FMINCNT) | (0xBB << N_USB2_PCR_CONFIG_3_SFRCALIB_FMAXCNT) |
       (0x3E << N_USB2_PCR_CONFIG_3_TDCCALIB_OSCCNT)  | (0xF << N_USB2_PCR_CONFIG_3_LOCKTIMERCNT_TH)),
      ((0x12 << N_USB2_PCR_CONFIG_3_SFRCALIB_FMINCNT) | (0x2F << N_USB2_PCR_CONFIG_3_SFRCALIB_FMAXCNT) |
       (0x10 << N_USB2_PCR_CONFIG_3_TDCCALIB_OSCCNT)  | (0x30 << N_USB2_PCR_CONFIG_3_LOCKTIMERCNT_TH)),
    }
  },
  // DFT_1
  {
    (UINT32)~(B_USB2_PCR_DFT_1_KPSCALE | B_USB2_PCR_DFT_1_KISCALE),
    {
      (UINT32) ((0x3 << N_USB2_PCR_DFT_1_KPSCALE) | (0x3 << N_USB2_PCR_DFT_1_KISCALE)),
      (UINT32) ((0x3 << N_USB2_PCR_DFT_1_KPSCALE) | (0x3 << N_USB2_PCR_DFT_1_KISCALE)),
      (UINT32) ((0x3 << N_USB2_PCR_DFT_1_KPSCALE) | (0x3 << N_USB2_PCR_DFT_1_KISCALE))
    }
  }
};

/**
  Programs USB2 PHY register with requested data

  @param[in]  Offset            USB2 PHY register offset
  @param[in]  Data32And         Mask with bits to clear
  @param[in]  Data32Or          Mask with bits to set
**/
STATIC
VOID
Usb2PhyProgramRegister (
  IN  UINT16  Offset,
  IN  UINT32  Data32And,
  IN  UINT32  Data32Or
  )
{
  EFI_STATUS      Status;
  UINT32          Data32;
  UINT32          Expected;
  UINT8           Response;

  //
  // Check for actual data in USB2 PHY register and verify accessibility
  //
  Status = PchSbiExecution (
             PID_USB2,
             Offset,
             PrivateControlRead,
             FALSE,
             &Data32,
             &Response
             );
  if (EFI_ERROR (Status)) {
    if ((PchPcrRead32 (PID_DCI, R_DCI_PCR_ECTRL) & B_DCI_PCR_ECTRL_USB2DBCEN) != 0) {
      return;
    }

    ASSERT_EFI_ERROR (Status);
    //
    // Due to error happening data wasn't read properly so cannot rely on it
    //
    return;
  }

  //
  // Data from register was successfully read so change it accordingly
  //
  Expected = (Data32 & Data32And) | Data32Or;
  DEBUG ((DEBUG_INFO, "Programming USB2 PHY register 0x%4X to 0x%8X\n", Offset, Expected));

  Status = PchSbiExecution (
             PID_USB2,
             Offset,
             PrivateControlWrite,
             TRUE,
             &Expected,
             &Response
             );
  ASSERT_EFI_ERROR (Status);

  HsioChipsetInitSusWrite32 (PID_USB2, Offset, Expected, Data32And, Data32Or);

  if (!IsSimicsEnvironment()) {
    DEBUG_CODE_BEGIN ();
    UINT32    Mask;
    //
    // Sanity check for potential data mismatch between written value and expected one
    //
    Status = PchSbiExecution (
               PID_USB2,
               Offset,
               PrivateControlRead,
               FALSE,
               &Data32,
               &Response
               );

    ASSERT_EFI_ERROR (Status);
    // Mask for checking only modified bits
    Mask = ((~Data32And) | Data32Or);
    if ((Expected & Mask) != (Data32 & Mask)) {
      DEBUG ((DEBUG_WARN, "Warning! Data mismatch after write. Read %08X\n", Data32));
    }
    DEBUG_CODE_END ();
  }
}

/**
  Programs USB2 PHY parameters that depend on reference clock frequency

  @param[in]  Usb2RefFreq          The USB2_PHY_REF_FREQ enum value
**/
STATIC
VOID
Usb2PhyClockDependentProgramming (
  IN  USB2_PHY_REF_FREQ     Usb2RefFreq
  )
{
  DEBUG ((
    DEBUG_INFO,
    "[%a] Programming USB2 PHY parameters based on freq enum: %d\n",
    __FUNCTION__, Usb2RefFreq
    ));

  if (Usb2RefFreq >= FREQ_MAX) {
    DEBUG ((
      DEBUG_ERROR,
      "[%a] %d is not valid option for USB2 PHY reference clock frequency. Skipping programming.\n",
      __FUNCTION__, Usb2RefFreq
      ));
    return;
  }

  //
  // PLLDIVRATIOS_0
  // Address offset: 0x7000
  //
  Usb2PhyProgramRegister (
    R_USB2_PCR_PLLDIVRATIOS_0,
    Usb2PhyFreqParams.Plldivratios_0.AndMask,
    Usb2PhyFreqParams.Plldivratios_0.Value[Usb2RefFreq]
  );

  //
  // SFRCONFIG_0
  // Address offset: 0x702C
  //
  Usb2PhyProgramRegister (
    R_USB2_PCR_SFRCONFIG_0,
    Usb2PhyFreqParams.Sfrconfig_0.AndMask,
    Usb2PhyFreqParams.Sfrconfig_0.Value[Usb2RefFreq]
    );

  //
  // CONFIG_0
  // Address offset: 0x7008
  //
  Usb2PhyProgramRegister (
    R_USB2_PCR_CONFIG_0,
    Usb2PhyFreqParams.Config_0.AndMask,
    Usb2PhyFreqParams.Config_0.Value[Usb2RefFreq]
    );

  //
  // CONFIG_3
  // Address offset: 0x7014
  //
  Usb2PhyProgramRegister (
    R_USB2_PCR_CONFIG_3,
    Usb2PhyFreqParams.Config_3.AndMask,
    Usb2PhyFreqParams.Config_3.Value[Usb2RefFreq]
    );

  //
  // DFT_1
  // Address offset: 0x7024
  // Values: [15:14] 11b, [13:12] 11b
  //
  Usb2PhyProgramRegister (
    R_USB2_PCR_DFT_1,
    Usb2PhyFreqParams.Dft_1.AndMask,
    Usb2PhyFreqParams.Dft_1.Value[Usb2RefFreq]
    );

  if (Usb2RefFreq != FREQ_19_2) {
    //
    // USB2 PLL1
    // Address offset: 0x7F02
    //
    Usb2PhyProgramRegister (
      R_USB2_PCR_PLL1,
      (UINT32)~(BIT29),
      (BIT30)
    );
  }
}

/**
  Tune the USB 2.0 high-speed signals quality.

  @param[in]  Usb2PhyConfig           The USB2_PHY_CONFIG policy instance
**/
VOID
Usb2PhyProgramming (
  IN  USB2_PHY_CONFIG   *Usb2PhyConfig
  )
{
  UINT32          Data32And;
  UINT32          Data32Or;
  UINT32          Data32;
  UINT8           PortIndex;
  UINT16          PortStatusOffset;
  UINT8           DbcPort;
  UINT8           Retry;
  UINT8           PpLane;
  UINT8           MaxUsbPortNumber;
  UINT16          Offset;

  DbcPort = 0xFF;

  DEBUG ((DEBUG_INFO, "[%a] Start\n", __FUNCTION__));

  //
  // Disable USB2 PHY Core PG AFE tuning
  //
  PmcUsb2CorePhyPowerGatingDisable ();

  //
  // USB2 GLOBAL PORT
  // Address offset: 0x4001
  //
  Usb2PhyProgramRegister (
    R_USB2_PCR_GLOBAL_PORT,
    (UINT32)~(BIT3),
    (BIT29 | BIT25 | BIT24 | BIT13 | BIT12 | BIT11)
    );

  //
  // GLB ADP VBUS COMP REG
  // Address offset: 0x402B
  //
  Usb2PhyProgramRegister (
    R_USB2_PCR_GLB_ADP_VBUS_REG,
    (UINT32)~0,
    (BIT22)
    );

  //
  // USB2 GLOBAL PORT2
  // Address offset: 0x402C
  //
  Usb2PhyProgramRegister (
    R_USB2_PCR_GLOBAL_PORT_2,
    (UINT32)~(BIT22),
    (BIT27 | BIT9 | BIT8 | BIT7)
    );


  //
  // USB2 COMPBG
  // Address offset: 0x7F04
  //
  Usb2PhyProgramRegister (
    R_USB2_PCR_CFG_COMPBG,
    (UINT32)~(BIT13 | BIT12 | BIT11 | BIT8),
    (BIT15 | BIT14 | BIT10 | BIT9 | BIT7)
    );

  //
  // USB2 SFRCONFIG_0
  // Address offset: 0x702C
  //
  Usb2PhyProgramRegister (
    R_USB2_PCR_SFRCONFIG_0,
    (UINT32)~(BIT8),
    (UINT32) (BIT9)
    );

  //
  // Program USB2 PHY reference clock frequency dependent parameters
  //
  Usb2PhyClockDependentProgramming (GetUsb2PhyRefFreq ());

  MaxUsbPortNumber = GetPchUsb2MaxPhysicalPortNum ();
  Data32 = PchPcrRead32 (PID_DCI, R_DCI_PCR_ECTRL);

  // Check if DbC is enabled and USB2 DBC is used
  if ((Data32 & (B_DCI_PCR_ECTRL_DBG_EN | B_DCI_PCR_ECTRL_USB2DBCEN)) != 0) {
    // Need to check few times for DbC port allowing bits to settle
    for (Retry = 0; Retry < 3; Retry++) {
      for (PortIndex = 0; PortIndex < MaxUsbPortNumber; PortIndex++) {
        // Check port status in DAP registers
        PortStatusOffset = R_XHCI_PCR_DAP_USB2PORT_STATUS_0 + (PortIndex * S_XHCI_MEM_PORTSC_PORT_SPACING);
        Data32 = PchPcrRead32 (PID_XHCI, PortStatusOffset);

        // Check if operating state says it's DbC port
        if ((Data32 & B_XHCI_PCR_DAP_USB2PORT_STATUS_0_OS) == V_XHCI_PCR_DAP_USB2PORT_STATUS_0_OS_DBC) {
          DEBUG ((DEBUG_INFO, "Port %d is used as a debug port\n", PortIndex));
          break;
        }
      }

      if (PortIndex < MaxUsbPortNumber) { // Found USB2 DbC Port index
        DbcPort = PortIndex + 1;          // Adding 1 to accomodate for next loop lane numbering
        break;
      }

      MicroSecondDelay (10);              // Wait 10us for bits to settle and retry
    }
  }

  // Numbering is starting from 1 to make sure port specific offset
  // is correctly calculated based on layout of registers
  for (PpLane = 1; PpLane <= MaxUsbPortNumber; PpLane++) {
    DEBUG ((DEBUG_INFO, "### PpLane %d\n", PpLane));
    if (PpLane == DbcPort) {              // Don't apply USB2 PHY configuration to port used as DbC connection
      continue;
    }

    //
    // USB2 PER PORT
    // Address Offset: 0x4000 + (N * 0x100) - where N is lane number
    //
    Offset = R_USB2_PCR_PP_LANE_BASE_ADDR | R_USB2_PCR_PER_PORT | (PpLane << 8);

    Data32And = (UINT32) ~(B_USB2_PCR_PER_PORT_PERPORTRXISET
      | B_USB2_PCR_PER_PORT_PERPORTTXPEHALF
      | B_USB2_PCR_PER_PORT_PERPORTPETXISET
      | B_USB2_PCR_PER_PORT_PERPORTTXISET);
    Data32Or  = (0x2 << N_USB2_PCR_PER_PORT_PERPORTRXISET)
      | (((Usb2PhyConfig->Port[PpLane - 1].Pehalfbit) & 0x1) << N_USB2_PCR_PER_PORT_PERPORTTXPEHALF)
      | (((Usb2PhyConfig->Port[PpLane - 1].Petxiset) & 0x7)  << N_USB2_PCR_PER_PORT_PERPORTPETXISET)
      | (((Usb2PhyConfig->Port[PpLane - 1].Txiset) & 0x7)    << N_USB2_PCR_PER_PORT_PERPORTTXISET);
    Data32Or |= (BIT31 | BIT30 | BIT29 | BIT28 | BIT27 | BIT26 | BIT4);
    Usb2PhyProgramRegister (Offset, Data32And, Data32Or);

    //
    // USB2 PER PORT 2
    // Address Offset: 0x4026 + (N * 0x100) - where N is lane number
    //
    Offset = R_USB2_PCR_PP_LANE_BASE_ADDR | R_USB2_PCR_PER_PORT_2 | (PpLane << 8);

    Data32And = (UINT32) ~(BIT31 | B_USB2_PCR_PER_PORT_2_TXEMPHASISEN);
    Data32Or  = (((Usb2PhyConfig->Port[PpLane - 1].Predeemp) & 0x3) << N_USB2_PCR_PER_PORT_2_TXEMPHASISEN);
    Data32Or |= (BIT30 | BIT25 | BIT1 | BIT0);
    Usb2PhyProgramRegister (Offset, Data32And, Data32Or);

    //
    // UTMI MISC REG PER PORT
    // Address Offset: 0x4008 + (N * 0x100) - where N is lane number
    //
    Offset = R_USB2_PCR_PP_LANE_BASE_ADDR | R_USB2_PCR_UTMI_MISC_PER_PORT | (PpLane << 8);

    Data32And = (UINT32) ~(BIT13 | BIT10);
    Data32Or  = (BIT12 | BIT11 | BIT9 | BIT7);
    Usb2PhyProgramRegister (Offset, Data32And, Data32Or);
  }
}
