/** @file
  Initializes TSN mGBE Controller (TSN).

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2020 Intel Corporation.

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

#include <PiPei.h>
#include <Ppi/SiPolicy.h>
#include <Register/PchRegs.h>
#include <Register/TsnRegs.h>
#include <Register/PchPcrRegs.h>
#include <Library/IoLib.h>
#include <Library/TsnLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PeiItssLib.h>
#include <Library/PeiHsioLib.h>
#include <Library/PeiPseLib.h>
#include <Library/PeiTsnInitLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/PchFiaLib.h>
#include <IndustryStandard/Pci30.h>
#include <Library/PchInfoLib.h>
#include <TsnMacAddrSubRegion.h>
#include <TsnConfigSubRegion.h>
#include <Library/PchPcrLib.h>
#include <Library/PsfLib.h>
#include <Library/PmcPrivateLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED TSN_CONFIG               *mTsnConfig = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED PSE_CONFIG               *mPseConfig = NULL;

#define TSN_MAX_LANE     5
#define TSN_FIRST_LANE   7
#define TSN_LANE_7       0
#define TSN_LANE_8       1
#define TSN_LANE_9       2
#define TSN_LANE_10      3
#define TSN_LANE_11      4
#define PSE_GBE_DMA_MAX_CHANNEL 16

typedef struct {
  UINT32       Offset;
  UINT32       AndData;
  UINT32       OrData;
} TSN_MODPHY_CONFIG;

TSN_MODPHY_CONFIG Tsn_Pll_1G_34Mhz[] = {
  {R_MODPHY_PCR_LCPLL_DWORD0,    B_MODPHY_PCR_LCPLL_DWORD0,    B_MODPHY_PCR_LCPLL_DWORD0_CLK38_4MHZ_1G    },
  {R_MODPHY_PCR_LCPLL_DWORD2,    B_MODPHY_PCR_LCPLL_DWORD2,    N_MODPHY_PCR_LCPLL_DWORD2_CLK38_4MHZ_1G    },
  {R_MODPHY_PCR_LCPLL_DWORD7,    B_MODPHY_PCR_LCPLL_DWORD7,    N_MODPHY_PCR_LCPLL_DWORD7_CLK38_4MHZ_1G    },
  {R_MODPHY_PCR_LPPLL_DWORD10,   B_MODPHY_PCR_LPPLL_DWORD10,   N_MODPHY_PCR_LPPLL_DWORD10_CLK38_4MHZ_1G   },
  {R_MODPHY_PCR_CMN_ANA_DWORD30, B_MODPHY_PCR_CMN_ANA_DWORD30, N_MODPHY_PCR_CMN_ANA_DWORD30_CLK38_4MHZ_1G }
};

TSN_MODPHY_CONFIG Tsn_Pll_2_5G_34Mhz[] = {
  {R_MODPHY_PCR_LCPLL_DWORD0,    B_MODPHY_PCR_LCPLL_DWORD0,    B_MODPHY_PCR_LCPLL_DWORD0_CLK38_4MHZ_2_5G    },
  {R_MODPHY_PCR_LCPLL_DWORD2,    B_MODPHY_PCR_LCPLL_DWORD2,    N_MODPHY_PCR_LCPLL_DWORD2_CLK38_4MHZ_2_5G    },
  {R_MODPHY_PCR_LCPLL_DWORD7,    B_MODPHY_PCR_LCPLL_DWORD7,    N_MODPHY_PCR_LCPLL_DWORD7_CLK38_4MHZ_2_5G    },
  {R_MODPHY_PCR_LPPLL_DWORD10,   B_MODPHY_PCR_LPPLL_DWORD10,   N_MODPHY_PCR_LPPLL_DWORD10_CLK38_4MHZ_2_5G   },
  {R_MODPHY_PCR_CMN_ANA_DWORD30, B_MODPHY_PCR_CMN_ANA_DWORD30, N_MODPHY_PCR_CMN_ANA_DWORD30_CLK38_4MHZ_2_5G }
};


TSN_MODPHY_CONFIG Tsn_Pll_1G_24Mhz[] = {
  {R_MODPHY_PCR_LCPLL_DWORD0,    B_MODPHY_PCR_LCPLL_DWORD0,    B_MODPHY_PCR_LCPLL_DWORD0_CLK24MHZ_1G    },
  {R_MODPHY_PCR_LCPLL_DWORD2,    B_MODPHY_PCR_LCPLL_DWORD2,    N_MODPHY_PCR_LCPLL_DWORD2_CLK24MHZ_1G    },
  {R_MODPHY_PCR_LCPLL_DWORD7,    B_MODPHY_PCR_LCPLL_DWORD7,    N_MODPHY_PCR_LCPLL_DWORD7_CLK24MHZ_1G    },
  {R_MODPHY_PCR_LPPLL_DWORD10,   B_MODPHY_PCR_LPPLL_DWORD10,   N_MODPHY_PCR_LPPLL_DWORD10_CLK24MHZ_1G   },
  {R_MODPHY_PCR_CMN_ANA_DWORD30, B_MODPHY_PCR_CMN_ANA_DWORD30, N_MODPHY_PCR_CMN_ANA_DWORD30_CLK24MHZ_1G }
};

TSN_MODPHY_CONFIG Tsn_Pll_2_5G_24Mhz[] = {
  {R_MODPHY_PCR_LCPLL_DWORD0,    B_MODPHY_PCR_LCPLL_DWORD0,    B_MODPHY_PCR_LCPLL_DWORD0_CLK24MHZ_2_5G    },
  {R_MODPHY_PCR_LCPLL_DWORD2,    B_MODPHY_PCR_LCPLL_DWORD2,    N_MODPHY_PCR_LCPLL_DWORD2_CLK24MHZ_2_5G    },
  {R_MODPHY_PCR_LCPLL_DWORD7,    B_MODPHY_PCR_LCPLL_DWORD7,    N_MODPHY_PCR_LCPLL_DWORD7_CLK24MHZ_2_5G    },
  {R_MODPHY_PCR_LPPLL_DWORD10,   B_MODPHY_PCR_LPPLL_DWORD10,   N_MODPHY_PCR_LPPLL_DWORD10_CLK24MHZ_2_5G   },
  {R_MODPHY_PCR_CMN_ANA_DWORD30, B_MODPHY_PCR_CMN_ANA_DWORD30, N_MODPHY_PCR_CMN_ANA_DWORD30_CLK24MHZ_2_5G }
};

TSN_MODPHY_CONFIG Tsn_Pll_Common[] = {
  {R_MODPHY_PCR_LCPLL_DWORD4,    B_MODPHY_PCR_LCPLL_DWORD4,    N_MODPHY_PCR_LCPLL_DWORD4_COMMON    },
  {R_MODPHY_PCR_LCPLL_DWORD6,    B_MODPHY_PCR_LCPLL_DWORD6,    N_MODPHY_PCR_LCPLL_DWORD6_COMMON    },
  {R_MODPHY_PCR_LCPLL_DWORD8,    B_MODPHY_PCR_LCPLL_DWORD8,    N_MODPHY_PCR_LCPLL_DWORD8_COMMON    },
  {R_MODPHY_PCR_LCPLL_DWORD12,   B_MODPHY_PCR_LCPLL_DWORD12,   N_MODPHY_PCR_LCPLL_DWORD12_COMMON   },
  {R_MODPHY_PCR_LCPLL_DWORD18,   B_MODPHY_PCR_LCPLL_DWORD18,   N_MODPHY_PCR_LCPLL_DWORD18_COMMON   },
  {R_MODPHY_PCR_LCPLL_DWORD19,   B_MODPHY_PCR_LCPLL_DWORD19,   N_MODPHY_PCR_LCPLL_DWORD19_COMMON   },
  {R_MODPHY_PCR_LCPLL_DWORD11,   B_MODPHY_PCR_LCPLL_DWORD11,   N_MODPHY_PCR_LCPLL_DWORD11_COMMON   },
  //{R_MODPHY_PCR_CMN_DIG_DWORD1,  B_MODPHY_PCR_CMN_DIG_DWORD1,  N_MODPHY_PCR_CMN_DIG_DWORD1_COMMON  },
  {R_MODPHY_PCR_CMN_DIG_DWORD2,  B_MODPHY_PCR_CMN_DIG_DWORD2,  N_MODPHY_PCR_CMN_DIG_DWORD2_COMMON  },
  {R_MODPHY_PCR_CMN_DIG_DWORD12, B_MODPHY_PCR_CMN_DIG_DWORD12, N_MODPHY_PCR_CMN_DIG_DWORD12_COMMON },
  {R_MODPHY_PCR_CMN_DIG_DWORD15, B_MODPHY_PCR_CMN_DIG_DWORD15, N_MODPHY_PCR_CMN_DIG_DWORD15_COMMON },
  {R_MODPHY_PCR_CMN_ANA_DWORD10, B_MODPHY_PCR_CMN_ANA_DWORD10, N_MODPHY_PCR_CMN_ANA_DWORD10_COMMON }
};

TSN_MODPHY_CONFIG Tsn_Dlane_Data[] = {
  {R_MODPHY_DLANE8_PCR_SET3,                    B_MODPHY_PCR_SET3,                    N_MODPHY_PCR_COMMON                         },
  {R_MODPHY_DLANE8_PCR_2TAP_DEEMPH3P5_RATE1,    B_MODPHY_PCR_2TAP_DEEMPH3P5_RATE1,    N_MODPHY_PCR_2TAP_DEEMPH3P5_RATE1_COMMON    },
  {R_MODPHY_DLANE8_PCR_2TAP_DEEMPH3P5_RATE0,    B_MODPHY_PCR_2TAP_DEEMPH3P5_RATE0,    N_MODPHY_PCR_2TAP_DEEMPH3P5_RATE0_COMMON    },
  {R_MODPHY_DLANE8_PCR_RXPICTRL1,               B_MODPHY_PCR_RXPICTRL1,               N_MODPHY_PCR_RXPICTRL1_COMMON               },
  {R_MODPHY_DLANE8_PCR_RSVD4,                   B_MODPHY_PCR_RSVD4,                   N_MODPHY_PCR_RSVD4_COMMON                   },
  {R_MODPHY_DLANE8_PCR_RSVD9,                   B_MODPHY_PCR_RSVD9,                   N_MODPHY_PCR_RSVD9_COMMON                   },
  {R_MODPHY_DLANE8_PCR_RSVD19,                  B_MODPHY_PCR_RSVD19,                  N_MODPHY_PCR_RSVD19_COMMON                  },
  {R_MODPHY_DLANE8_PCR_REG1C,                   B_MODPHY_PCR_REG1C,                   N_MODPHY_PCR_REG1C_COMMON                   },
  {R_MODPHY_DLANE8_PCR_REG21,                   B_MODPHY_PCR_REG21,                   N_MODPHY_PCR_REG21_COMMON                   },
  {R_MODPHY_DLANE8_PCR_RXUPIFCFGGHALFRATE_0,    B_MODPHY_PCR_RXUPIFCFGGHALFRATE_0,    N_MODPHY_PCR_RXUPIFCFGGHALFRATE_0_COMMON    },
  {R_MODPHY_DLANE8_PCR_RXUPPFCFGGQUARTERRATE_0, B_MODPHY_PCR_RXUPPFCFGGQUARTERRATE_0, N_MODPHY_PCR_RXUPPFCFGGQUARTERRATE_0_COMMON },
  {R_MODPHY_DLANE8_PCR_REG54,                   B_MODPHY_PCR_REG54,                   N_MODPHY_PCR_REG54_COMMON                   },
  {R_MODPHY_DLANE8_PCR_RSVD5E,                  B_MODPHY_PCR_RSVD5E,                  N_MODPHY_PCR_RSVD5E_COMMON                  },
  {R_MODPHY_DLANE8_PCR_RSVD75,                  B_MODPHY_PCR_RSVD75,                  N_MODPHY_PCR_RSVD75_COMMON                  },
  {R_MODPHY_DLANE8_PCR_REG7A,                   B_MODPHY_PCR_REG7A,                   N_MODPHY_PCR_REG7A_COMMON                   },
  {R_MODPHY_DLANE8_PCR_RSVD8B,                  B_MODPHY_PCR_RSVD8B,                  N_MODPHY_PCR_RSVD8B_COMMON                  },
  {R_MODPHY_DLANE8_PCR_RSVD8D,                  B_MODPHY_PCR_RSVD8D,                  N_MODPHY_PCR_RSVD8D_COMMON                  },
  {R_MODPHY_DLANE8_PCR_RSVDEB,                  B_MODPHY_PCR_RSVDEB,                  N_MODPHY_PCR_RSVDEB_COMMON                  },
  {R_MODPHY_DLANE8_PCR_RSVD80,                  B_MODPHY_PCR_RSVD80,                  N_MODPHY_PCR_RSVD80_COMMON                  },
  {R_MODPHY_DLANE8_PCR_RSVDAB,                  B_MODPHY_PCR_RSVDAB,                  N_MODPHY_PCR_RSVDAB_COMMON                  },
  {R_MODPHY_DLANE8_PCR_PCS_DWORD14,             B_MODPHY_PCR_PCS_DWORD14,             N_MODPHY_PCR_PCS_DWORD14_COMMON             },
  {R_MODPHY_DLANE8_PCR_TX_DWORD18,              B_MODPHY_PCR_TX_DWORD18,              N_MODPHY_PCR_TX_DWORD18_COMMON              },
  {R_MODPHY_DLANE8_PCR_PCS_DWORD15,             B_MODPHY_PCR_PCS_DWORD15,             N_MODPHY_PCR_PCS_DWORD15_COMMON             },
  {R_MODPHY_DLANE8_PCR_TX_DWORD19,              B_MODPHY_PCR_TX_DWORD19,              N_MODPHY_PCR_TX_DWORD19_COMMON              },
  {R_MODPHY_DLANE8_PCR_RX_DWORD5,               B_MODPHY_PCR_RX_DWORD5,               N_MODPHY_PCR_RX_DWORD5_COMMON               },
  {R_MODPHY_DLANE8_PCR_RX_DWORD20,              B_MODPHY_PCR_RX_DWORD20,              N_MODPHY_PCR_RX_DWORD20_COMMON              },
  {R_MODPHY_DLANE8_PCR_RX_DWORD51,              B_MODPHY_PCR_RX_DWORD51,              N_MODPHY_PCR_RX_DWORD51_COMMON              },
  {R_MODPHY_DLANE8_PCR_RX_DWORD61,              B_MODPHY_PCR_RX_DWORD61,              N_MODPHY_PCR_RX_DWORD61_COMMON              }
};

//
// Maximum loop time for Tsn status check
// 4000 * 50 = 200 mSec in total
//
#define TSN_MAX_LOOP_TIME       4000
#define TSN_GMII_DELAY          50

/**
  The function programs the TSN PLL registers.

  @param[in]  TsnPllSbiId     PID of the modphy PLL to use
  @param[in]  TsnLinkSpeed    Link Speed selection. See TSN_LINK_SPEED_OPTIONS.
**/
STATIC
VOID
TsnModPhyProg (
  PCH_SBI_PID             PortId,
  TSN_MODPHY_CONFIG       *TablePtr,
  UINT16                  NumberOfEntry
)
{
  UINT16                  Index;
  UINT16                  TableSize;
  TSN_MODPHY_CONFIG       *TempPtr;

  TableSize = sizeof (TSN_MODPHY_CONFIG);
  TempPtr = TablePtr;

  DEBUG ((DEBUG_INFO, "Tsn ModPhy Prog: TableEntry %d\n",NumberOfEntry));

  for (Index=0; Index<NumberOfEntry; Index++) {
    PchPcrAndThenOr32 (
      PortId,
      TempPtr->Offset,
      (UINT32) ~(TempPtr->AndData),
      TempPtr->OrData
      );

    // Read back
    DEBUG ((DEBUG_INFO, "Tsn ModPhy Prog: PortId: 0x%02x, Offset: 0x%04x, Value: 0x%08x\n",PortId,TempPtr->Offset,PchPcrRead32(PortId,TempPtr->Offset)));

    TempPtr++;
  }

}

STATIC
VOID
TsnModPhyInit (
  UINT8                   TsnLinkSpeed,
  UINT8                   LaneNumber,
  UINT8                   SkipPLL
)
{
  TSN_MODPHY_CONFIG *ModPhyTablePtr;
  UINT16            TableEntry;
  PCH_SBI_PID       PortId;
  UINT32            AdjustOffset;
  UINT32            Index;

  AdjustOffset = 0;

  DEBUG ((DEBUG_INFO, "Tsn ModPhy Prog: Configure Lane %d, LinkSpeed %x\n",LaneNumber,TsnLinkSpeed));

  if (SkipPLL == 0) {
    switch (LaneNumber) {
      case 7:
      case 8:
      case 9:
        PortId = PID_MODPHY1;
      break;

      case 10:
      case 11:
      default:
        PortId = PID_MODPHY3;
      break;
    }

    // Program PLL for different Link Speed
    switch (TsnLinkSpeed) {
      case (TSN_LINK_SPEED_2_5G_24MHZ):
        ModPhyTablePtr = &Tsn_Pll_2_5G_24Mhz[0];
        TableEntry = ARRAY_SIZE (Tsn_Pll_2_5G_24Mhz);
      break;

      case (TSN_LINK_SPEED_1G_24MHZ):
        ModPhyTablePtr = &Tsn_Pll_1G_24Mhz[0];
        TableEntry = ARRAY_SIZE (Tsn_Pll_1G_24Mhz);
      break;

      case (TSN_LINK_SPEED_2_5G_34MHZ):
        ModPhyTablePtr = &Tsn_Pll_2_5G_34Mhz[0];
        TableEntry = ARRAY_SIZE (Tsn_Pll_2_5G_34Mhz);
      break;

      case (TSN_LINK_SPEED_1G_34MHZ):
      default:
        ModPhyTablePtr = &Tsn_Pll_1G_34Mhz[0];
        TableEntry = ARRAY_SIZE (Tsn_Pll_1G_34Mhz);
      break;
    }
    TsnModPhyProg (PortId, ModPhyTablePtr, TableEntry);

    // Program Common PLL
    ModPhyTablePtr = &Tsn_Pll_Common[0];
    TableEntry = ARRAY_SIZE (Tsn_Pll_Common);
    TsnModPhyProg (PortId, ModPhyTablePtr, TableEntry);
  }

  // Program DLane
  switch(LaneNumber) {
    case 7:
      PortId = PID_MODPHY1;
      AdjustOffset = 0xC00;
    break;
    case 8:
      PortId = PID_MODPHY2;
      AdjustOffset = 0x00;
      break;
    case 9:
      PortId = PID_MODPHY2;
      AdjustOffset = 0x400;
      break;
    case 11:
      PortId = PID_MODPHY2;
      AdjustOffset = 0xC00;
      break;
    case 10:
    default:
      PortId = PID_MODPHY2;
      AdjustOffset = 0x800;
    break;
  }
  ModPhyTablePtr = &Tsn_Dlane_Data[0];
  TableEntry = ARRAY_SIZE (Tsn_Dlane_Data);

  // Update Offset address according to lane number
  for (Index=0; Index<TableEntry; Index++) {
    ModPhyTablePtr->Offset += AdjustOffset;
    ModPhyTablePtr++;
  }
  ModPhyTablePtr = &Tsn_Dlane_Data[0];
  TsnModPhyProg (PortId, ModPhyTablePtr, TableEntry);

  //Restore back offset
  ModPhyTablePtr = &Tsn_Dlane_Data[0];
  for (Index=0; Index<TableEntry; Index++) {
    ModPhyTablePtr->Offset -= AdjustOffset;
    ModPhyTablePtr++;
  }
}

/**
  Check for MDIO Phy GMII Busy Status.

  1. Ensure that MDIO_ADDRESS offset 200h [0] = 0b
  2. Poll MDIO_ADDRESS offset 200h [0] up to 200ms

  @param [in] PchTsnBar0   Tsn MMIO space

  @retval EFI_SUCCESS
  @retval EFI_TIMEOUT
**/
EFI_STATUS
PhyGmiiBusyStatus (
  IN      UINT32  TsnBar0
  )
{
  UINT32  Count;

  for (Count = 0; Count < TSN_MAX_LOOP_TIME; ++Count) {
    if (MmioRead32 (TsnBar0 + R_TSN_MEM_MAC_MDIO_ADDRESS) & B_TSN_MEM_MAC_MDIO_GMII_BUSY) {
      MicroSecondDelay (TSN_GMII_DELAY);
    } else {
      return EFI_SUCCESS;
    }
  }
  DEBUG ((DEBUG_ERROR, "PhyGMIIBusyStatus Timeout in %d micro seconds\n", TSN_MAX_LOOP_TIME * TSN_GMII_DELAY));
  return EFI_TIMEOUT;
}

UINT32
GetPseTsnGbeDmaVcTcDefault (
  VOID
  )
{
  // DMA VC/TC mapping default data
  /*
          Tx          |         Rx
  ---------------------------------------
  TC1: Tx DMA Ch#15-8 | TC1: Rx DMA Ch#15-8
  TC0: Tx DMA Ch#0-7  | TC0: Rx DMA Ch#0-7
  */
  return (UINT32) 0xFFFF0000;
}

UINT32
GetPchTsnGbeDmaVcTcDefault (
  VOID
  )
{
  // DMA VC/TC mapping default data
  /*
          Tx         |         Rx
  ---------------------------------------
  TC1: Tx DMA Ch#7-4 | TC1: Rx DMA Ch#7-4
  TC0: Tx DMA Ch#0-3 | TC0: Rx DMA Ch#0-3
  */
  return (UINT32) 0x0000FF00;
}

UINT32
GetTsnGbeMsiVcTcDefault (
  VOID
  )
{
  // MSI VC/TC mapping default data
  /*
        DMA MSI       |     Non-DMA MSI
  ---------------------------------------------
  TC0: MSI vector 0-7  | TC0: MSI vector 26-31
  TC1: MSI vector 8-15 |
    */
  return (UINT32) 0x0000FF00;
}

/**
  Configures Pch Timed Sensitive Network (TSN) Controller Registers and MAC Programming

  @param[in] SiPolicy
  @param[in] PchTsnBase  - Pch Tsn Base Address
**/
STATIC
VOID
PchTsnBiosProg (
  IN  SI_POLICY_PPI   *SiPolicy,
  IN  UINT32          PchTsnBase
  )
{
  EFI_STATUS                      Status;
  UINTN                           PchTsnBar0;
  TSN_MAC_ADDR_SUB_REGION         *TsnMacAddr;
  PSE_TSN_CONFIG_SUB_REGION       *TsnConfigData;
  TSN_CONFIG                      *TsnConfig;
  UINT8                           TsnPortIndex;
  UINT32                          TsnMacAddrLow = 0;
  UINT32                          TsnMacAddrHigh = 0;
  UINT32                          Data32OrDmaTc0;
  UINT32                          Data32OrDmaTc1;
  UINT32                          Data32OrMsiTc0;
  UINT32                          Data32OrMsiTc1;
  UINT32                          DmaVcTcMapDefault;
  UINT32                          MsiVcTcMapDefault;
  UINT32                          MacLow;
  UINT32                          MacHigh;
  UINT32                          MacMdioAddressValue;
  UINT16                          GcrValue;
  UINT8                           MultiVcEnable;
  EFI_BOOT_MODE                   BootMode;

  Data32OrDmaTc0 = 0;
  Data32OrDmaTc1 = 0;
  Data32OrMsiTc0 = 0;
  Data32OrMsiTc1 = 0;

  DEBUG ((DEBUG_INFO, "PchTsnBiosProg() Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gTsnConfigGuid, (VOID *) &TsnConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  // Program Temp Bar
  PciSegmentWrite32 (PchTsnBase + R_TSN_CFG_BAR0_LOW,  PcdGet32 (PcdSiliconInitTempMemBaseAddr));

  // Enable Memory Space encoding
  PciSegmentOr32 (PchTsnBase + PCI_COMMAND_OFFSET, (EFI_PCI_COMMAND_MEMORY_SPACE));

  // Program MAC address for TSN on PCH
  PchTsnBar0 = PciSegmentRead32 (PchTsnBase + R_TSN_CFG_BAR0_LOW) & ~(B_TSN_CFG_BAR0_MASK);

  DEBUG ((DEBUG_INFO, "PchTsnBar0: 0x%x\n",PchTsnBar0));

  if (PchTsnBar0 == 0xFFFFF000) {
    DEBUG ((DEBUG_INFO, "TSN BAR not found\n"));
    Status = EFI_UNSUPPORTED;
  }

  if (BootMode != BOOT_ON_S3_RESUME) {
    TsnMacAddr = (TSN_MAC_ADDR_SUB_REGION*) mTsnConfig->TsnSubRegion[0].BaseAddress;
    for (TsnPortIndex = 0; TsnPortIndex < TSN_PORT_MAX; TsnPortIndex++) {
      if ((PchTsnDevNumber () == TsnMacAddr->Config.Port[TsnPortIndex].Bdf.Dev) &&
        (PchTsnFuncNumber () == TsnMacAddr->Config.Port[TsnPortIndex].Bdf.Func)) {
        TsnMacAddrLow = TsnMacAddr->Config.Port[TsnPortIndex].MacAddr.U32MacAddr[0];
        TsnMacAddrHigh = TsnMacAddr->Config.Port[TsnPortIndex].MacAddr.U32MacAddr[1];
        break;
      }
    }
    DEBUG ((DEBUG_INFO, "Start Mac address programming\n"));

    MmioWrite32 (PchTsnBar0 + R_TSN_MEM_MAC_ADDRESS0_LOW, TsnMacAddrLow);
    //
    // Program MacAddressHigh[15:0]
    // MacAddressHigh[31] Address Enable Bit
    //
    MmioWrite32 (PchTsnBar0 + R_TSN_MEM_MAC_ADDRESS0_HIGH, ((TsnMacAddrHigh & R_TSN_MEM_MAC_ADDRESS_HIGH_MASK) | B_TSN_MEM_ADDRESS_ENABLE));
    MacLow = MmioRead32 (PchTsnBar0 + R_TSN_MEM_MAC_ADDRESS0_LOW);
    MacHigh = MmioRead32 (PchTsnBar0 + R_TSN_MEM_MAC_ADDRESS0_HIGH);
    DEBUG ((DEBUG_INFO, "Mac Address Low: 0x%x Mac Address High: 0x%x \n", MacLow, MacHigh));
    Status = EFI_SUCCESS;
  }

  // Perform GCR programming in S3 resume as well.
  //
  // Reading Tsn Adhoc Register GCR mgbe_mdio
  //
  MacMdioAddressValue = MmioRead32 (PchTsnBar0 + R_TSN_MEM_MAC_MDIO_ADDRESS);
  MacMdioAddressValue &= (UINT32) ~(B_TSN_MEM_MAC_MDIO_ADDRESS_MASK);
  MacMdioAddressValue |= (V_TSN_MEM_MAC_MDIO_ADHOC_GCR_ADD << N_TSN_MEM_MAC_MDIO_PHYAD) \
                        | (V_TSN_MEM_MAC_MDIO_CLK_TRAIL << N_TSN_MEM_MAC_MDIO_CLK_TRAIL) \
                        | (V_TSN_MEM_MAC_MDIO_CLK_CSR_DIV_10 << N_TSN_MEM_MAC_MDIO_CLK_CSR) \
                        | V_TSN_MEM_MAC_MDIO_GMII_22_PHY_READ | B_TSN_MEM_MAC_MDIO_GMII_BUSY;
  MmioWrite32 (PchTsnBar0 + R_TSN_MEM_MAC_MDIO_ADDRESS, MacMdioAddressValue);

  //
  // Wait for MDIO frame transfer complete before reading MDIO DATA register
  //
  Status = PhyGmiiBusyStatus (PchTsnBar0);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "TSN GMII Busy. Adhoc Register read invalid\n"));
  }
  GcrValue = MmioRead16 (PchTsnBar0 + R_TSN_MEM_MAC_MDIO_DATA);
  DEBUG ((DEBUG_INFO, "TSN MDIO (0x200): 0x%x GCR : 0x%x\n", MacMdioAddressValue, GcrValue));

  //
  // Disable Auto-Negotiation and Clear Adhoc Link Mode Bit
  //
  GcrValue &= (UINT16) ~B_TSN_MEM_MAC_ADHOC_LINK_MODE;
  GcrValue |= B_TSN_MEM_MAC_ADHOC_PHY_AUTONEG_DISABLE;

  switch (TsnConfig->PchTsnGbeLinkSpeed) {
    case (TSN_LINK_SPEED_2_5G_24MHZ):
      GcrValue |= (UINT16) V_TSN_MEM_MAC_ADHOC_LINK_MODE_2_5G;
      break;
    case (TSN_LINK_SPEED_1G_24MHZ):
      GcrValue |= (UINT16) V_TSN_MEM_MAC_ADHOC_LINK_MODE_1G;
      break;
    case (TSN_LINK_SPEED_2_5G_34MHZ):
      GcrValue |= (UINT16) V_TSN_MEM_MAC_ADHOC_LINK_MODE_2_5G;
      break;
    case (TSN_LINK_SPEED_1G_34MHZ):
      GcrValue |= (UINT16) V_TSN_MEM_MAC_ADHOC_LINK_MODE_1G;
      break;
    default:
      break;
  }

  //
  // Write Link Speed Mode to Global Configuration Register (GCR)
  //
  MmioWrite16 (PchTsnBar0 + R_TSN_MEM_MAC_MDIO_DATA, GcrValue);
  MacMdioAddressValue = MmioRead32 (PchTsnBar0 + R_TSN_MEM_MAC_MDIO_ADDRESS);
  MacMdioAddressValue &= (UINT32) ~(B_TSN_MEM_MAC_MDIO_ADDRESS_MASK);
  MacMdioAddressValue |= (V_TSN_MEM_MAC_MDIO_ADHOC_GCR_ADD << N_TSN_MEM_MAC_MDIO_PHYAD) \
                        | (V_TSN_MEM_MAC_MDIO_CLK_TRAIL << N_TSN_MEM_MAC_MDIO_CLK_TRAIL) \
                        | (V_TSN_MEM_MAC_MDIO_CLK_CSR_DIV_10 << N_TSN_MEM_MAC_MDIO_CLK_CSR) \
                        | V_TSN_MEM_MAC_MDIO_GMII_22_PHY_WRITE | B_TSN_MEM_MAC_MDIO_GMII_BUSY;
  MmioWrite32 (PchTsnBar0 + R_TSN_MEM_MAC_MDIO_ADDRESS, MacMdioAddressValue);
  DEBUG ((DEBUG_INFO, "TSN MDIO (0x200): 0x%x GCR : 0x%x\n", MacMdioAddressValue, GcrValue));

  // Disable Memory Space encoding
  PciSegmentAnd16 (PchTsnBase + PCI_COMMAND_OFFSET, (UINT16) (~EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER));
  PciSegmentWrite32 (PchTsnBase + R_TSN_CFG_BAR0_LOW,  0);

  DEBUG ((DEBUG_INFO, "Start PCH TSN DMA VC/TC programming\n"));
  TsnConfigData = (PSE_TSN_CONFIG_SUB_REGION*) mTsnConfig->TsnSubRegion[2].BaseAddress;
  // Program VC/TC mapping to sideband registers if MCC is A0 stepping
  // Program VC/TC mapping to Pch Tsn Mmio registers if MCC is B0 stepping
  if (PchStepping () == PCH_A0) {
    MultiVcEnable = mTsnConfig->PchTsnGbeMultiVcEnable;
    if (MultiVcEnable) {
      DmaVcTcMapDefault = GetPchTsnGbeDmaVcTcDefault ();
      Data32OrDmaTc0 = ((UINT32) ~DmaVcTcMapDefault) & B_TSN_PCR_AXIID_TO_TC0_MAP_0; // Bit[31:16] are reserved
      Data32OrDmaTc1 = DmaVcTcMapDefault & B_TSN_PCR_AXIID_TO_TC1_MAP_0; // Bit[31:16] are reserved
      MsiVcTcMapDefault = GetTsnGbeMsiVcTcDefault ();
      Data32OrMsiTc0 = ((UINT32) ~MsiVcTcMapDefault) & B_TSN_PCR_MSI_TO_TC0_MAP; // Bit[25:16] are reserved
      Data32OrMsiTc1 = MsiVcTcMapDefault & B_TSN_PCR_MSI_TO_TC1_MAP; // Bit[25:16] are reserved
    }

    for (TsnPortIndex = 0; TsnPortIndex < TSN_PORT_MAX; TsnPortIndex++) {
      if ((PchTsnDevNumber () == TsnConfigData->Config.Port[TsnPortIndex].Bdf.Dev) &&
        (PchTsnFuncNumber () == TsnConfigData->Config.Port[TsnPortIndex].Bdf.Func)) {
        MultiVcEnable = TRUE;
        if (TsnConfigData->Config.Port[TsnPortIndex].VcTcPort.Valid) {
          Data32OrDmaTc0 = ((UINT32) ~TsnConfigData->Config.Port[TsnPortIndex].VcTcPort.DmaVcTcMap.Data) & B_TSN_PCR_AXIID_TO_TC0_MAP_0; // Bit[31:16] are reserved
          Data32OrDmaTc1 = TsnConfigData->Config.Port[TsnPortIndex].VcTcPort.DmaVcTcMap.Data & B_TSN_PCR_AXIID_TO_TC1_MAP_0; // Bit[31:16] are reserved
          Data32OrMsiTc0 = ((UINT32) ~TsnConfigData->Config.Port[TsnPortIndex].VcTcPort.MsiVcTcMap) & B_TSN_PCR_MSI_TO_TC0_MAP; // Bit[25:16] are reserved
          Data32OrMsiTc1 = TsnConfigData->Config.Port[TsnPortIndex].VcTcPort.MsiVcTcMap & B_TSN_PCR_MSI_TO_TC1_MAP; // Bit[25:16] are reserved
        } else {
          DmaVcTcMapDefault = GetPchTsnGbeDmaVcTcDefault ();
          Data32OrDmaTc0 = ((UINT32) ~DmaVcTcMapDefault) & B_TSN_PCR_AXIID_TO_TC0_MAP_0; // Bit[31:16] are reserved
          Data32OrDmaTc1 = DmaVcTcMapDefault & B_TSN_PCR_AXIID_TO_TC1_MAP_0; // Bit[31:16] are reserved
          MsiVcTcMapDefault = GetTsnGbeMsiVcTcDefault ();
          Data32OrMsiTc0 = ((UINT32) ~MsiVcTcMapDefault) & B_TSN_PCR_MSI_TO_TC0_MAP; // Bit[25:16] are reserved
          Data32OrMsiTc1 = MsiVcTcMapDefault & B_TSN_PCR_MSI_TO_TC1_MAP; // Bit[25:16] are reserved
        }
        break;
      }
    }

    if (MultiVcEnable) {
      DEBUG ((DEBUG_INFO, "PCH GBE MultiVC Enabled\n"));
      PchPcrAndThenOr32 (
        PID_TSN,
        R_TSN_PCR_AXIID_TO_TC0_MAP_0,
        (UINT32) ~B_TSN_PCR_AXIID_TO_TC0_MAP_0,
        Data32OrDmaTc0
        );
      PchPcrAndThenOr32 (
        PID_TSN,
        R_TSN_PCR_AXIID_TO_TC1_MAP_0,
        (UINT32) ~B_TSN_PCR_AXIID_TO_TC1_MAP_0,
        Data32OrDmaTc1
        );
      PchPcrAndThenOr32 (
        PID_TSN,
        R_TSN_PCR_MSI_TO_TC0_MAP,
        (UINT32) ~B_TSN_PCR_MSI_TO_TC0_MAP,
        Data32OrMsiTc0
        );
      PchPcrAndThenOr32 (
        PID_TSN,
        R_TSN_PCR_MSI_TO_TC1_MAP,
        (UINT32) ~B_TSN_PCR_MSI_TO_TC1_MAP,
        Data32OrMsiTc1
        );
    }
  }

  PchPcrAndThenOr32 (
    PID_TSN,
    R_TSN_PCR_PMCTL,
    (UINT32) ~B_TSN_PCR_PMCTL_CLOCKGATE,
    B_TSN_PCR_PMCTL_CLOCKGATE
    );

  DEBUG ((DEBUG_INFO, "PchTsnBiosProg () End\n"));
}

UINT32
GetPseTsnDmaVcTcDefault (
  VOID
  )
{
  // DMA VC/TC mapping default data
  /*
          Tx         |         Rx
  ---------------------------------------
  TC1: Tx DMA Ch#7-4 | TC1: Rx DMA Ch#7-4
  TC0: Tx DMA Ch#0-3 | TC0: Rx DMA Ch#0-3
  */
  return (UINT32) 0x0000FF00;
}

/**
  Configures Pse Timed Sensitive Network (TSN) Controller Registers and MAC Programming

  @param[in] SiPolicy
  @param[in] Index      PSE TSN GBE Controller Index
**/
STATIC
EFI_STATUS
PseTsnBiosProg (
  IN  SI_POLICY_PPI   *SiPolicy,
  IN  UINT8           Index
  )
{
  EFI_STATUS                      Status;
  UINTN                           PseTsnBase;
  UINTN                           PseTsnBar0;
  TSN_MAC_ADDR_SUB_REGION         *TsnMacAddr;
  PSE_TSN_CONFIG_SUB_REGION       *TsnConfigData;
  UINT8                           TsnPortIndex;
  UINT32                          TsnMacAddrLow = 0;
  UINT32                          TsnMacAddrHigh = 0;
  DMA_VC_TC_BIT                   DmaVcTcMapData;
  TSN_CONFIG                      *TsnConfig;
  UINT32                          MacMdioAddressValue;
  UINT16                          GcrValue;
  UINT8                           MultiVcEnable;
  UINT32                          RxChannel;
  UINT32                          TxChannel;
  UINT32                          DmaCtlChIndex;
  UINT32                          DmaChannelOffset;

  DEBUG ((DEBUG_INFO, "PseTsnBiosProg () for Device %d, Function %d Start\n", PseTsnDevNumber (Index), PseTsnFuncNumber (Index)));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gTsnConfigGuid, (VOID *) &TsnConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  TsnMacAddr = (TSN_MAC_ADDR_SUB_REGION*) mTsnConfig->TsnSubRegion[0].BaseAddress;
  TsnConfigData = (PSE_TSN_CONFIG_SUB_REGION*) mTsnConfig->TsnSubRegion[2].BaseAddress;

  PseTsnBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PseTsnDevNumber (Index),
                 PseTsnFuncNumber (Index),
                 0
                 );
  DEBUG ((DEBUG_INFO, "PseTsnBase: 0x%x\n", PseTsnBase));
  // Program Temp Bar
  PciSegmentWrite32 (PseTsnBase + R_TSN_CFG_BAR0_LOW,  PcdGet32 (PcdSiliconInitTempMemBaseAddr));

  // Enable Memory Space encoding
  PciSegmentOr32 (PseTsnBase + PCI_COMMAND_OFFSET, (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER));

  // Program MAC address for TSN on PSE
  PseTsnBar0 = PciSegmentRead32 (PseTsnBase + R_TSN_CFG_BAR0_LOW) & ~(B_TSN_CFG_BAR0_MASK);

  DEBUG ((DEBUG_INFO, "PseTsnBar0: 0x%x\n",PseTsnBar0));

  if (PseTsnBar0 != 0xFFFFF000) {
    for (TsnPortIndex = 0; TsnPortIndex < TSN_PORT_MAX; TsnPortIndex++) {
      if ((PseTsnDevNumber (Index) == TsnMacAddr->Config.Port[TsnPortIndex].Bdf.Dev) &&
        (PseTsnFuncNumber (Index) == TsnMacAddr->Config.Port[TsnPortIndex].Bdf.Func)) {
        TsnMacAddrLow = TsnMacAddr->Config.Port[TsnPortIndex].MacAddr.U32MacAddr[0];
        TsnMacAddrHigh = TsnMacAddr->Config.Port[TsnPortIndex].MacAddr.U32MacAddr[1];
        break;
      }
    }

    if (TsnMacAddrLow) {
      DEBUG ((DEBUG_INFO, "Start Mac address programming\n"));
      MmioWrite32 (PseTsnBar0 + R_TSN_MEM_MAC_ADDRESS0_LOW, TsnMacAddrLow);
      //
      // Program MacAddressHigh[15:0]
      // MacAddressHigh[31] Address Enable Bit
      //
      MmioWrite32 (PseTsnBar0 + R_TSN_MEM_MAC_ADDRESS0_HIGH, ((TsnMacAddrHigh & R_TSN_MEM_MAC_ADDRESS_HIGH_MASK) | B_TSN_MEM_ADDRESS_ENABLE));
    }

    MultiVcEnable = FALSE;

    if (mPseConfig->Gbe[Index].OwnerShip == HOST_OWNED) {
      DEBUG ((DEBUG_INFO, "PSE TSN owned by host, start PSE TSN DMA VC/TC programming\n"));
      MultiVcEnable = mTsnConfig->PseTsnGbeMultiVcEnable[Index];
      if (MultiVcEnable) {
        DmaVcTcMapData.Data = GetPseTsnGbeDmaVcTcDefault ();
      }
      for (TsnPortIndex = 0; TsnPortIndex < TSN_PORT_MAX; TsnPortIndex++) {
        if ((PseTsnDevNumber (Index) == TsnConfigData->Config.Port[TsnPortIndex].Bdf.Dev) &&
          (PseTsnFuncNumber (Index) == TsnConfigData->Config.Port[TsnPortIndex].Bdf.Func)) {
          MultiVcEnable = TRUE;
          if (TsnConfigData->Config.Port[TsnPortIndex].VcTcPort.Valid) {
            DmaVcTcMapData = TsnConfigData->Config.Port[TsnPortIndex].VcTcPort.DmaVcTcMap;
          } else {
            DmaVcTcMapData.Data = GetPseTsnGbeDmaVcTcDefault ();
          }
          break;
        }
      }

      if (MultiVcEnable) {
        DEBUG ((DEBUG_INFO, "PSE GBE%d MultiVC Enabled. VcTc Data Map %x\n", Index, DmaVcTcMapData.Data));
        // DMA CTL CH0
        for (DmaCtlChIndex = 0; DmaCtlChIndex < PSE_GBE_DMA_MAX_CHANNEL; DmaCtlChIndex++) {
          switch (DmaCtlChIndex) {
            case 0:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH0;
              TxChannel        = DmaVcTcMapData.Fields.TxCh0;
              RxChannel        = DmaVcTcMapData.Fields.TxCh0;
              break;
            case 1:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH1;
              TxChannel        = DmaVcTcMapData.Fields.TxCh1;
              RxChannel        = DmaVcTcMapData.Fields.TxCh1;
              break;
            case 2:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH2;
              TxChannel        = DmaVcTcMapData.Fields.TxCh2;
              RxChannel        = DmaVcTcMapData.Fields.TxCh2;
              break;
            case 3:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH3;
              TxChannel        = DmaVcTcMapData.Fields.TxCh3;
              RxChannel        = DmaVcTcMapData.Fields.TxCh3;
              break;
            case 4:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH4;
              TxChannel        = DmaVcTcMapData.Fields.TxCh4;
              RxChannel        = DmaVcTcMapData.Fields.TxCh4;
              break;
            case 5:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH5;
              TxChannel        = DmaVcTcMapData.Fields.TxCh5;
              RxChannel        = DmaVcTcMapData.Fields.TxCh5;
              break;
            case 6:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH6;
              TxChannel        = DmaVcTcMapData.Fields.TxCh6;
              RxChannel        = DmaVcTcMapData.Fields.TxCh6;
              break;
            case 7:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH7;
              TxChannel        = DmaVcTcMapData.Fields.TxCh7;
              RxChannel        = DmaVcTcMapData.Fields.TxCh7;
              break;
            case 8:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH8;
              TxChannel        = DmaVcTcMapData.Fields.TxCh8;
              RxChannel        = DmaVcTcMapData.Fields.TxCh8;
              break;
            case 9:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH9;
              TxChannel        = DmaVcTcMapData.Fields.TxCh9;
              RxChannel        = DmaVcTcMapData.Fields.TxCh9;
              break;
            case 10:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH10;
              TxChannel        = DmaVcTcMapData.Fields.TxCh10;
              RxChannel        = DmaVcTcMapData.Fields.TxCh10;
              break;
            case 11:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH11;
              TxChannel        = DmaVcTcMapData.Fields.TxCh11;
              RxChannel        = DmaVcTcMapData.Fields.TxCh11;
              break;
            case 12:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH12;
              TxChannel        = DmaVcTcMapData.Fields.TxCh12;
              RxChannel        = DmaVcTcMapData.Fields.TxCh12;
              break;
            case 13:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH13;
              TxChannel        = DmaVcTcMapData.Fields.TxCh13;
              RxChannel        = DmaVcTcMapData.Fields.TxCh13;
              break;
            case 14:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH14;
              TxChannel        = DmaVcTcMapData.Fields.TxCh14;
              RxChannel        = DmaVcTcMapData.Fields.TxCh14;
              break;
            case 15:
              DmaChannelOffset = R_TSN_MEM_DMA_CTL_CH15;
              TxChannel        = DmaVcTcMapData.Fields.TxCh15;
              RxChannel        = DmaVcTcMapData.Fields.TxCh15;
              break;
            default:
              DmaChannelOffset = 0;
              TxChannel     = 0;
              RxChannel     = 0;
              break;
          }

          if (DmaChannelOffset != 0) {
            DEBUG ((DEBUG_INFO, "    Ch%d Vc1 WR %x, Vc1 RD %x\n", DmaCtlChIndex, TxChannel, RxChannel));
            MmioAndThenOr32 (
              PseTsnBar0 + DmaChannelOffset,
              (UINT32) ~B_TSN_MEM_DMA_CTL_CH_VC_MAP,
              (UINT32) ((TxChannel << N_TSN_MEM_IOSF_WR_VC01) | (RxChannel << N_TSN_MEM_IOSF_RD_VC01))
            );
          }
        }
      }
    }

    //
    // Reading Tsn Adhoc Register GCR mgbe_mdio
    //
    MacMdioAddressValue = MmioRead32 (PseTsnBar0 + R_TSN_MEM_MAC_MDIO_ADDRESS);
    MacMdioAddressValue &= (UINT32) ~(B_TSN_MEM_MAC_MDIO_ADDRESS_MASK);
    MacMdioAddressValue |= (V_TSN_MEM_MAC_MDIO_ADHOC_GCR_ADD << N_TSN_MEM_MAC_MDIO_PHYAD) \
                         | (V_TSN_MEM_MAC_MDIO_CLK_TRAIL << N_TSN_MEM_MAC_MDIO_CLK_TRAIL) \
                         | (V_TSN_MEM_MAC_MDIO_CLK_CSR_DIV_10 << N_TSN_MEM_MAC_MDIO_CLK_CSR) \
                         | V_TSN_MEM_MAC_MDIO_GMII_22_PHY_READ | B_TSN_MEM_MAC_MDIO_GMII_BUSY;
    MmioWrite32 (PseTsnBar0 + R_TSN_MEM_MAC_MDIO_ADDRESS, MacMdioAddressValue);

    //
    // Wait for MDIO frame transfer complete before reading MDIO DATA register
    //
    Status = PhyGmiiBusyStatus(PseTsnBar0);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "TSN GMII Busy. Adhoc Register read invalid\n"));
    }
    GcrValue = MmioRead16 (PseTsnBar0 + R_TSN_MEM_MAC_MDIO_DATA);
    DEBUG ((DEBUG_INFO, "TSN MDIO (0x200): 0x%x GCR : 0x%x\n", MacMdioAddressValue, GcrValue));

    //
    // Disable Auto-Negotiation and Clear Adhoc Link Mode Bit
    //
    GcrValue &= (UINT16) ~B_TSN_MEM_MAC_ADHOC_LINK_MODE;
    GcrValue |= B_TSN_MEM_MAC_ADHOC_PHY_AUTONEG_DISABLE;

    switch (TsnConfig->PseTsnGbeLinkSpeed[Index]) {
      case (TSN_LINK_SPEED_2_5G_24MHZ):
        GcrValue |= (UINT16) V_TSN_MEM_MAC_ADHOC_LINK_MODE_2_5G;
        break;
      case (TSN_LINK_SPEED_1G_24MHZ):
        GcrValue |= (UINT16) V_TSN_MEM_MAC_ADHOC_LINK_MODE_1G;
        break;
      case (TSN_LINK_SPEED_2_5G_34MHZ):
        GcrValue |= (UINT16) V_TSN_MEM_MAC_ADHOC_LINK_MODE_2_5G;
        break;
      case (TSN_LINK_SPEED_1G_34MHZ):
        GcrValue |= (UINT16) V_TSN_MEM_MAC_ADHOC_LINK_MODE_1G;
        break;
      default:
        break;
    }

    //
    // Write Link Speed Mode to Global Configuration Register (GCR)
    //
    MmioWrite16 (PseTsnBar0 + R_TSN_MEM_MAC_MDIO_DATA, GcrValue);
    MacMdioAddressValue = MmioRead32 (PseTsnBar0 + R_TSN_MEM_MAC_MDIO_ADDRESS);
    MacMdioAddressValue &= (UINT32) ~(B_TSN_MEM_MAC_MDIO_ADDRESS_MASK);
    MacMdioAddressValue |= (V_TSN_MEM_MAC_MDIO_ADHOC_GCR_ADD << N_TSN_MEM_MAC_MDIO_PHYAD) \
                         | (V_TSN_MEM_MAC_MDIO_CLK_TRAIL << N_TSN_MEM_MAC_MDIO_CLK_TRAIL) \
                         | (V_TSN_MEM_MAC_MDIO_CLK_CSR_DIV_10 << N_TSN_MEM_MAC_MDIO_CLK_CSR) \
                         | V_TSN_MEM_MAC_MDIO_GMII_22_PHY_WRITE | B_TSN_MEM_MAC_MDIO_GMII_BUSY;
    MmioWrite32 (PseTsnBar0 + R_TSN_MEM_MAC_MDIO_ADDRESS, MacMdioAddressValue);
    DEBUG ((DEBUG_INFO, "TSN MDIO (0x200): 0x%x GCR : 0x%x\n", MacMdioAddressValue, GcrValue));


    Status = EFI_SUCCESS;
  } else {
    DEBUG ((DEBUG_INFO, "PSE TSN BAR not found\n"));
    Status = EFI_UNSUPPORTED;
  }

  // Disable Memory Space encoding
  PciSegmentAnd16 (PseTsnBase + PCI_COMMAND_OFFSET, (UINT16) (~EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER));
  PciSegmentWrite32 (PseTsnBase + R_TSN_CFG_BAR0_LOW,  0);

  DEBUG ((DEBUG_INFO, "PseTsnBiosProg () End\n"));
  return Status;
}

/**
  Configures PCH Timed Sensitive Network (TSN) Controller Interrupt

  @param[in] SiPolicy
**/
STATIC
VOID
TsnConfigureInterrupt (
  IN  SI_POLICY_PPI   *SiPolicy
  )
{
  UINT8     InterruptPin;
  UINT8     Irq;
  UINT32    Data32Or;
  UINT32    Data32And;

  DEBUG ((DEBUG_INFO, "Pch Tsn Interrupt Configuration Start\n"));

  ///
  /// Configure TSN interrupt
  ///
  ItssGetDevIntConfig (
    SiPolicy,
    PCI_DEVICE_NUMBER_PCH_TSN,
    PCI_FUNCTION_NUMBER_PCH_TSN,
    &InterruptPin,
    &Irq
    );

  Data32Or =  (UINT32) ((InterruptPin << N_TSN_PCR_PCICFGCTR_IPIN1) |
                        (Irq << N_TSN_PCR_PCICFGCTR_PCI_IRQ));
  Data32And =~(UINT32) (B_TSN_PCR_PCICFGCTR_PCI_IRQ | B_TSN_PCR_PCICFGCTR_ACPI_IRQ | B_TSN_PCR_PCICFGCTR_IPIN1);

  PchPcrAndThenOr32 (PID_TSN, R_TSN_PCR_PCICFGCTRL, Data32And, Data32Or);

  DEBUG ((DEBUG_INFO, "Pch Tsn Interrupt Configuration End\n"));
}

/**
  Configures PSE Timed Sensitive Network (TSN) Controller

  @param[in] SiPolicy
**/
STATIC
VOID
PseTsnConfigure (
  IN  SI_POLICY_PPI   *SiPolicy
  )
{
  UINT8          Index = 0;
  for (Index = 0; Index < GetPchMaxPseGbeControllersNum (); Index++) {
    if (IsPseTsnPresent (Index)) {
      PseTsnBiosProg (SiPolicy, Index);
    }
  }
}

/**
  Initialize the Intel TSN Controller

  @param[in] SiPolicy             Policy
**/
VOID
TsnInit (
  IN  SI_POLICY_PPI    *SiPolicy
  )
{
  EFI_STATUS             Status;
  UINT32                 PchTsnBase;
  UINT8                  PchTsnLane;
  UINT8                  PseTsn0Lane;
  UINT8                  PseTsn1Lane;
  BOOLEAN                IsFiaLanePse0TsnOwned;
  BOOLEAN                IsFiaLanePse1TsnOwned;
  BOOLEAN                IsFiaLanePchTsnOwned;
  UINT8                  SkipPLL;
  UINT8                  LaneInit[TSN_MAX_LANE] = {0,0,0,0,0};

  PchTsnLane = 0;
  PseTsn0Lane = 0;
  PseTsn1Lane = 0;

  DEBUG ((DEBUG_INFO, "TsnInit() Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gTsnConfigGuid, (VOID *) &mTsnConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPseConfigGuid, (VOID *) &mPseConfig);
  ASSERT_EFI_ERROR (Status);

  // Configure PCH TSN
  if (mTsnConfig->PchTsnEnable) {
    DEBUG ((DEBUG_INFO, "PCH TSN is Enabled\n"));

    PchTsnBase = PCI_SEGMENT_LIB_ADDRESS (
                  DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                  DEFAULT_PCI_BUS_NUMBER_PCH,
                  PCI_DEVICE_NUMBER_PCH_TSN,
                  PCI_FUNCTION_NUMBER_PCH_TSN,
                  0
                  );
    //
    // Check if Tsn is available
    //
    if ((PciSegmentRead16 (PchTsnBase + PCI_VENDOR_ID_OFFSET)) == 0xFFFF) {
      DEBUG ((DEBUG_INFO, "Tsn config space not accessible! Tsn not available\n"));
    } else {
      GpioEnablePchTsn ();
      PchTsnBiosProg (SiPolicy, PchTsnBase);
      TsnConfigureInterrupt (SiPolicy);
    }
  } else {
    DEBUG ((DEBUG_INFO, "PCH TSN is Disabled\n"));
    PsfDisableTsnDevice();
    PmcStaticDisableTsn();
  }

  // Configure PSE TSN
  if (IsPseEnabled ()) {
    PseTsnConfigure (SiPolicy);
  }

  //
  // Configure TSN PLL
  //

  IsFiaLanePse0TsnOwned = PchFiaGetTsnLaneNum (0, &PseTsn0Lane);
  IsFiaLanePse1TsnOwned = PchFiaGetTsnLaneNum (1, &PseTsn1Lane);
  IsFiaLanePchTsnOwned  = PchFiaGetTsnLaneNum (2, &PchTsnLane);

  if (mTsnConfig->PchTsnEnable && mTsnConfig->PchTsnGbeSgmiiEnable && IsFiaLanePchTsnOwned) {
    SkipPLL = 0;
    LaneInit[PchTsnLane-TSN_FIRST_LANE] = 1;
    TsnModPhyInit(mTsnConfig->PchTsnGbeLinkSpeed,PchTsnLane,SkipPLL);
  }

  if (mTsnConfig->PseTsnGbeSgmiiEnable[0] && IsFiaLanePse0TsnOwned) {
    SkipPLL = 0;
    // If lane 8 being configure, Skip PLL
    if(LaneInit[TSN_LANE_8] == 1) {
      SkipPLL = 1;
    }
    LaneInit[PseTsn0Lane-TSN_FIRST_LANE] = 1;
    TsnModPhyInit(mTsnConfig->PseTsnGbeLinkSpeed[0],PseTsn0Lane,SkipPLL);
  }

  if (mTsnConfig->PseTsnGbeSgmiiEnable[1] && IsFiaLanePse1TsnOwned) {
    SkipPLL = 0;
    if((PseTsn1Lane==9) && (LaneInit[TSN_LANE_8]==1 || LaneInit[TSN_LANE_7]==1)) {
      SkipPLL = 1;
    } else if ((PseTsn1Lane==11) && (LaneInit[TSN_LANE_10]==1)) {
      SkipPLL = 1;
    }
    LaneInit[PseTsn1Lane-TSN_FIRST_LANE] = 1;
    TsnModPhyInit(mTsnConfig->PseTsnGbeLinkSpeed[0],PseTsn1Lane,SkipPLL);
  }

  DEBUG ((DEBUG_INFO, "TsnInit() End\n"));
}
