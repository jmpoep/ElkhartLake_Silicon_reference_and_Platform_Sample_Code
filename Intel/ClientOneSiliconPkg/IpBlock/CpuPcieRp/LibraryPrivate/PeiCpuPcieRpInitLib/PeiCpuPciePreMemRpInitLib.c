/** @file
  This file contains functions that initializes PCI Express Root Ports of CPU.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#include <Library/PeiCpuPciePreMemRpInitLib.h>
#include <CpuPcieHob.h>
#include <Library/CpuPcieRpLib.h>
#include <Library/PeiPchPcieClocksLib.h>
#include <Library/CpuPcieInfoLib.h>
#include <Library/PeiCpuPcieDekelInitLib.h>
#include <Register/CpuPcieRegs.h>
#include <Library/GpioPrivateLib.h>
#include <CpuPcieInfo.h>
#include <Library/TimerLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PeiServicesLib.h>
#include <CpuSbInfo.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include <CpuRegs.h>
#include <Library/PchFiaLib.h>
#include <Register/PchRegsHsio.h>
#include <Library/CpuPlatformLib.h>
/**
  Device information structure
**/
typedef struct {
  UINT16  Vid;
  UINT16  Did;
  UINT8   MaxLinkSpeed;
} PCIE_DEVICE_INFO;

/**
  Clear the register for disable CLKREQ

  @param[in] RpIndex                 Rootport Index
**/
VOID
EFIAPI
CpuPcieDisableClkReqMessaging (
  IN  UINT32                RpIndex
  )
{
  UINT64 RpBase;
  RpBase = CpuPcieBase (RpIndex);
  DEBUG ((DEBUG_INFO, "CpuPcieDisableClkReqMessaging Start\n"));
  PciSegmentAnd32 (RpBase + R_PCIE_CLKREQMP, (UINT32)~B_PCIE_CLKREQMP_CKREQMPEN);
  DEBUG ((DEBUG_INFO, "CpuPcieDisableClkReqMessaging End\n"));
}

/**
  Program the CLKREQ Assert pin

  @param[in] RpIndex                 Rootport Index
**/
VOID
EFIAPI
CpuPcieSetAssertClkReq (
  IN  UINT32                RpIndex
  )
{
  UINT64 RpBase;
  RpBase = CpuPcieBase (RpIndex);
  DEBUG ((DEBUG_INFO, "CpuPcieSetAssertClkReq Start\n"));
  PciSegmentAndThenOr32 (RpBase + R_PCIE_CLKREQMP, (UINT32)~B_PCIE_CLKREQMP_ASRTCLKREQP, B_PCIE_CLKREQMP_ASRTCLKREQP);
  DEBUG ((DEBUG_INFO, "CpuPcieSetAssertClkReq End\n"));
}

/**
  Program the registers in CPU Rootport

  @param[in] RpIndex                 Rootport Index
**/
VOID
EFIAPI
CpuPcieProgramClkReqMsgProtocolReg (
  IN  UINT32                RpIndex
  )
{
  UINT64  RpBase;
  UINT32  Data32Or;
  UINT32  Data32And;

  DEBUG ((DEBUG_INFO, "CpuPcieProgramClkReqMsgProtocolReg Start\n"));
  Data32And = (UINT32) ~B_PCIE_ACGR3S2_CLKREQMSGTXVLMDESTID_MASK;
  Data32Or = CPU_PCIE_CLKREQMSGTXVLMDESTID << B_PCIE_ACGR3S2_CLKREQMSGTXVLMDESTID_OFFSET;
  RpBase = CpuPcieBase (RpIndex);
  PciSegmentAndThenOr32 (RpBase + R_PCIE_ACGR3S2, Data32And, Data32Or);

  PciSegmentOr32(RpBase + R_PCIE_CLKREQMP, (B_PCIE_CLKREQMP_CLKREQMSGDL2DEBM | B_PCIE_CLKREQMP_CLKREQMSGL1EBM));

  Data32Or = ((CPU_PCIE_CLKREQMSGRXVLMI << B_PCIE_CLKREQMP_CLKREQMSGRXVLMI_OFFSET) | (CPU_PCIE_CLKREQMSGTXVLMI1 << B_PCIE_CLKREQMP_CLKREQMSGTXVLMI1_OFFSET) | (CPU_PCIE_CLKREQMSGTXVLMI0 << B_PCIE_CLKREQMP_CLKREQMSGTXVLMI0_OFFSET));
  PciSegmentAndThenOr32(RpBase + R_PCIE_CLKREQMP, (UINT32)~(B_PCIE_CLKREQMP_CLKREQMSGRXVLMI_MASK | B_PCIE_CLKREQMP_CLKREQMSGTXVLMI1_MASK | B_PCIE_CLKREQMP_CLKREQMSGTXVLMI0_MASK), Data32Or);

  Data32Or = B_PCIE_CLKREQMP_CKREQMPEN;
  PciSegmentOr32 (RpBase + R_PCIE_CLKREQMP, Data32Or);

  Data32And = ~(UINT32)(B_PCIE_AECR1G3_CRMTDDE | B_PCIE_AECR1G3_L1OFFRDYHEWT_MASK);
  Data32Or = B_PCIE_AECR1G3_L1OFFRDYHEWTEN | (V_PCIE_AECR1G3_L1OFFRDYHEWT << B_PCIE_AECR1G3_L1OFFRDYHEWT_OFFSET);
  PciSegmentAndThenOr32(RpBase + R_PCIE_AECR1G3, Data32And, Data32Or);

  DEBUG ((DEBUG_INFO, "CpuPcieProgramClkReqMsgProtocolReg End\n"));
}

/**
  Assign and Enable the CLKREQ# Messaging

  @param[in] RpEnabledMask                 Rootport Enable mask
**/
VOID
EFIAPI
CpuPcieEnableClkReqMsg (
  IN  UINT32                        RpEnabledMask
  )
{
  UINT32        RpIndex;
  UINT32        MaxCpuPciePortNum;

  DEBUG ((DEBUG_INFO, "CpuPcieEnableClkReqMsg Start\n"));

  MaxCpuPciePortNum = GetMaxCpuPciePortNum();
  for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; RpIndex++) {
    if (RpEnabledMask & (BIT0 << RpIndex)) {
      DEBUG ((DEBUG_INFO, "Configure CLKREQ# GPIO\n"));
      EnableClkReq (PchClockUsageCpuPcie0 + RpIndex); //Configure CLKREQ# GPIO
      PchConfigureCpuPciePortClkReqMapping (RpIndex);
      DEBUG ((DEBUG_INFO, "Program the registers in CPU Root port\n"));
      CpuPcieProgramClkReqMsgProtocolReg (RpIndex); // Program the registers in CPU Root port
      PchEnableCpuPciePortClkReqMapping(RpIndex);
    }
  }
  DEBUG ((DEBUG_INFO, "CpuPcieEnableClkReqMsg End\n"));
}

/**
  Polling the CLKREQ# Messaging Status bits

  @param[in] RpEnabledMask        Rootport Enable mask

  @retval ClkReqPollSts           Polling status bits
**/
UINT32
CpuPciePollClkReqMsgSts (
  IN  UINT32  RpEnabledMask
  )
{
  UINT32   Timeout;
  UINT32   RpIndex;
  UINT32   ClkReqAssertedMask;
  UINT32   MaxCpuPciePortNum;

  ClkReqAssertedMask = 0;
  MaxCpuPciePortNum = GetMaxCpuPciePortNum();
  Timeout = 0;
  do {
    for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; RpIndex++) {
      if (PchGetCpuPcieClkReqStatus (RpIndex)) {
        ClkReqAssertedMask |= (BIT0 << RpIndex);
        if (ClkReqAssertedMask == RpEnabledMask) {
          return ClkReqAssertedMask;
        }
        break;
      } else {
        MicroSecondDelay (1);
        Timeout++;
      }
    }
  } while (Timeout < 1000);

  return ClkReqAssertedMask;
}

/**
  Disable the CLKREQ# Messaging based on the polling of all rootport status bits

  @param[in] RpEnabledMask                 Rootport Enable mask
  @param[in] StatusBit                     CLKREQ status bit
**/
VOID
EFIAPI
CpuPcieDisableClkReqMsg (
  IN  UINT32                        RpEnabledMask,
  IN  UINT32                        StatusBit,
  IN  SA_PEG_HOB                    *SaPegHob
  )
{
  UINT32        RpIndex;
  DEBUG ((DEBUG_INFO, "CpuPcieDisableClkReqMsg Start\n"));
  DEBUG ((DEBUG_INFO, "Disable the CLKREQ# Messaging based on the polling\n"));
  for (RpIndex = 0; RpIndex < GetMaxCpuPciePortNum(); RpIndex++) {
    if ((RpEnabledMask - StatusBit) & (BIT0 << RpIndex)) {
      PchDisableCpuPciePortClkReq (RpIndex);
      DEBUG ((DEBUG_INFO, "L1SubStates should not be enabled if CLKREQ# messaging is not enabled\n"));
      SaPegHob->CpuPcieRp.L1SubStates[RpIndex] = 0; //L1SubStates should not be enabled if CLKREQ# messaging is not enabled
      SaPegHob->DisableClkReqMsg[RpIndex] = 1; //Indicates if CLKREQ# messaging is enabled or not
      DEBUG ((DEBUG_INFO, "Disable CLKREQ# messaging in Cpu Pcie RP\n"));
      CpuPcieDisableClkReqMessaging (RpIndex); // Disable CLKREQ# messaging in Cpu Pcie RP
    }
  }
  DEBUG ((DEBUG_INFO, "CpuPcieDisableClkReqMsg End\n"));
}

/**
  Assigns CLKREQ# to CPU PCIe ports

  @param[in] RpEnabledMask                 Rootport Enable mask
  @param[in] CPU_PCIE_RP_PREMEM_CONFIG      CpuPcieRpPreMemConfig to access the SA PCIe Pre Mem configuration
**/
VOID
EFIAPI
CpuPcieConfigureClockReqMessaging (
  IN  UINT32                        RpEnabledMask,
  IN  CPU_PCIE_RP_PREMEM_CONFIG     *CpuPcieRpPreMemConfig,
  IN  SA_PEG_HOB                    *SaPegHob
  )
{
  UINT32       RpIndex;
  DEBUG ((DEBUG_INFO, "CPU PCIE Clock Req configuration Start\n"));

  for (RpIndex = 0; RpIndex < GetMaxCpuPciePortNum(); RpIndex++) {
    DEBUG ((DEBUG_INFO, "Keeping L1SubStates enable by default for RpIndex %x\n", RpIndex));
    SaPegHob->CpuPcieRp.L1SubStates[RpIndex] = 1; // Keeping L1SubStates enable by default.
    SaPegHob->DisableClkReqMsg[RpIndex] = 0;// Keeping CLKREQ message enable by default
  }

  CpuPcieEnableClkReqMsg (RpEnabledMask);

  DEBUG ((DEBUG_INFO, "CPU PCIE Clock Req configuration End\n"));
}

/**
  Assertion of GPIOs on Link Down. Upon Link Down detection VWM message will be send to assert GPIO.

  @param[in] RpIndex                 Rootport Index
**/
VOID
EFIAPI
CpuPcieRpLinkDownGpios (
  IN  UINT32                RpIndex
  )
{
  UINT64  RpBase;
  UINT32  Data32Or;

  Data32Or = 0;

  DEBUG ((DEBUG_INFO, "Configure GPIOs for Link down Start\n"));

  RpBase = CpuPcieBase (RpIndex);
  Data32Or = (CPU_PCIE_CLKREQMSGTXVLMDESTID << B_PCIE_GDR_LDVWMDESTID_OFFSET) | (CPU_PCIE_GDR_LDVWMIDX << B_PCIE_GDR_LDVWMIDX_OFFSET) | (B_PCIE_GDR_VGPIOALDE);

    switch (RpIndex) {
      case 0:
        Data32Or |= 3 << B_PCIE_GDR_LDVWMBITLOC_OFFSET;
        break;
      case 1:
        Data32Or |= 0 << B_PCIE_GDR_LDVWMBITLOC_OFFSET;
        break;
      case 2:
        Data32Or |= 1 << B_PCIE_GDR_LDVWMBITLOC_OFFSET;
        break;
      case 3:
        Data32Or |= 2 << B_PCIE_GDR_LDVWMBITLOC_OFFSET;
        break;
      default:
        ASSERT (FALSE);
        return;
    }
  DEBUG ((DEBUG_INFO, "Value written to GDR register = %x\n", Data32Or));
  PciSegmentAndThenOr32 (RpBase + R_PCIE_GDR, (UINT32)~(B_PCIE_ACGR3S2_CLKREQMSGTXVLMDESTID_MASK | B_PCIE_GDR_LDVWMBITLOC_MASK | B_PCIE_GDR_LDVWMIDX_MASK | B_PCIE_GDR_VGPIOALDE), Data32Or);
  DEBUG ((DEBUG_INFO, "Value read back from GDR register = %x\n", PciSegmentRead32(RpBase + R_PCIE_GDR)));

  DEBUG ((DEBUG_INFO, "Configure GPIOs for Link down End\n"));
}

/**
  Limit Link Speed Based on Policy

  @param[in] RpIndex                 Rootport Index to Limit Speed
**/
VOID
EFIAPI
LimitLinkSpeed (
  IN     UINT32     RpIndex
  )
{
  CONST CPU_PCIE_RP_PREMEM_CONFIG    *CpuPcieRpPreMemConfig;
  UINT32                             Data32Or;
  UINT32                             Data32And;
  UINT64                             RpBase;
  UINT32                             Index;
  EFI_STATUS                         Status;
  SI_PREMEM_POLICY_PPI              *SiPreMemPolicyPpi;

  ///
  /// Get policy settings through the SaInitConfigBlock PPI
  ///
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *)SiPreMemPolicyPpi, &gCpuPcieRpPrememConfigGuid, (VOID *)&CpuPcieRpPreMemConfig);
  ASSERT_EFI_ERROR(Status);

  RpBase = CpuPcieBase (RpIndex);
  //
  // Set speed capability in rootport
  //
  DEBUG ((DEBUG_INFO, "Set speed capability in rootport %d\n", RpIndex));
  Data32And = (~((UINT32)(B_PCIE_MPC_PCIESD_MASK)));
  Data32Or = 0;
  for (Index = 0; Index < GetMaxCpuPciePortNum(); Index++)
  {
    DEBUG ((DEBUG_INFO, "PcieSpeed from policy = %x\n", CpuPcieRpPreMemConfig->PcieSpeed[Index]));
    switch (CpuPcieRpPreMemConfig->PcieSpeed[Index]) {
      case CpuPcieGen1:
        Data32Or |= (V_PCIE_MPC_PCIESD_GEN1 << B_PCIE_MPC_PCIESD_OFFSET);
        break;
      case CpuPcieGen2:
        Data32Or |= (V_PCIE_MPC_PCIESD_GEN2 << B_PCIE_MPC_PCIESD_OFFSET);
        break;
      case CpuPcieGen3:
        Data32Or |= (V_PCIE_MPC_PCIESD_GEN3 << B_PCIE_MPC_PCIESD_OFFSET);
        break;
      case CpuPcieGen4:
      case CpuPcieAuto:
        break;
    }
    if (Data32Or != 0) {
      DEBUG ((DEBUG_INFO, "PCIe Link Speed is Limited to Gen%x based on policy!!!\n", CpuPcieRpPreMemConfig->PcieSpeed[Index]));
    }
  }
  PciSegmentAndThenOr32 (RpBase + R_PCIE_MPC, Data32And, Data32Or);
}

/**
  Create Root Port Enabled mask by reading the DEVEN register

  @param[out] RpEnabledMask                 Rootport enabled mask based on DEVEN register
**/

UINT32
EFIAPI
GetRpEnMaskfromDevEn (
  )
{
  UINT32                 RpEnabledMask;
  UINT32                 DevEnable;

  RpEnabledMask = 0;

  //
  // Check DEVEN register
  //
  DEBUG((DEBUG_INFO, "Read DEVEN register\n"));
  DevEnable = PciSegmentRead32(PCI_SEGMENT_LIB_ADDRESS(SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN));
  DEBUG((DEBUG_INFO, "DevEnable = %x\n",DevEnable));
  if ((DevEnable & B_SA_DEVEN_D6EN_MASK) == B_SA_DEVEN_D6EN_MASK) {
    RpEnabledMask  |= BIT0;
  }
  if ((DevEnable & B_SA_DEVEN_D1F0EN_MASK) == B_SA_DEVEN_D1F0EN_MASK) {
    RpEnabledMask  |= BIT1;
  }
  if ((DevEnable &  B_SA_DEVEN_D1F1EN_MASK) ==  B_SA_DEVEN_D1F1EN_MASK) {
    RpEnabledMask  |= BIT2;
  }
  if ((DevEnable & B_SA_DEVEN_D1F2EN_MASK) == B_SA_DEVEN_D1F2EN_MASK) {
    RpEnabledMask  |= BIT3;
  }
  DEBUG((DEBUG_INFO, "RpEnabledMask formed from DEVEN = %x\n", RpEnabledMask));
  return RpEnabledMask;
}

/**
  Get the CPU PCIe enable root ports from straps fuse config

**/
UINT32
EFIAPI
GetRpEnMaskfromRpc (
  VOID
  )
{
  UINT32                 RpEnabledMask;
  UINT32                 MaxCpuPciePortNum;
  UINT32                 RpIndex;


  MaxCpuPciePortNum = GetMaxCpuPciePortNum();
  RpEnabledMask  = 0x0F; //assuming all Root ports are enabled

  //
  // Read STRPFUSECFG to get the furcation logic
  //
  for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; RpIndex++) { // Only in H/S sku more than one controller is present and RPC needs to be read
    switch (GetCpuPcieControllerConfig (RpIndex)) {
      case CPU_PCIE_1x16: //Pcie1x16
        RpEnabledMask &= ~(BIT1 | BIT2 | BIT3);
        RpEnabledMask |= BIT1;
        break;
      case CPU_PCIE_2x8: //Pcie2x8
        RpEnabledMask &= ~(BIT1 | BIT2 | BIT3);
        RpEnabledMask |= (BIT1 | BIT2);
        break;
      case CPU_PCIE_1x8_2x4: //Pcie1x8_2x4
        RpEnabledMask |= (BIT1 | BIT2 | BIT3);
        break;
      default:
        ASSERT(FALSE);
    }
    DEBUG((DEBUG_INFO, "RpEnabledMask formed after controllerconfig = %x\n", RpEnabledMask));
  }
  return RpEnabledMask;
}

/**
  Initialize the CPU PciExpress in PEI

  @param[in] IN PCIE_PEI_PREMEM_CONFIG    PciePeiPreMemConfig to access the PCIe Config related information
**/
VOID
EFIAPI
PciExpressInit (
  IN  CPU_PCIE_RP_PREMEM_CONFIG     *CpuPcieRpPreMemConfig
  )
{
  UINT32                RpEnabledMask;
  UINT32                MaxCpuPciePortNum;
  UINT32                RpIndex;
  UINT64                RpBase;
  UINT32                TimeoutUs;
  UINT32                Data32;
  SA_PEG_HOB            *SaPegHob;
  UINT32                RpEnMaskFromPolicy;
  UINT32                RpEnMaskFromRpc;
  UINT32                RpEnMaskFromDevEn;
  UINT32                LinkActiveEnableMask;
  UINTN                 RpDevice;
  UINTN                 RpFunction;
  UINT32                StatusBit;

  RpEnabledMask         = 0x00; //assuming all Root ports are disabled
  RpEnMaskFromPolicy    = 0x00;
  RpEnMaskFromDevEn     = 0x00;
  RpEnMaskFromRpc       = 0x00;
  LinkActiveEnableMask  = 0x00;

  MaxCpuPciePortNum = GetMaxCpuPciePortNum ();

  SaPegHob = NULL;
  SaPegHob = (SA_PEG_HOB *)GetFirstGuidHob(&gSaPegHobGuid);

  DEBUG((DEBUG_INFO, "Initialize CPU PciExpress controllers in Premem : PciExpressInit Start\n"));
  DEBUG((DEBUG_INFO, "MaxCpuPciePortNum = %x\n", MaxCpuPciePortNum));
  if (SaPegHob == NULL) {
    DEBUG((DEBUG_ERROR, "SaPegHob not found\n"));
    ASSERT(SaPegHob == NULL);
    return;
  }

  //
  //  Get RpEnabled mask from Policy
  //
  DEBUG ((DEBUG_INFO, "RpEnabledMask from Policy = %x\n", CpuPcieRpPreMemConfig->RpEnabledMask));
  if (CpuPcieRpPreMemConfig->RpEnabledMask != 0) {
    RpEnMaskFromPolicy = CpuPcieRpPreMemConfig->RpEnabledMask;
  }

  //
  //  Check for enabled Ports using Device ID
  //
  for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; RpIndex++) {
    RpEnMaskFromDevEn = GetRpEnMaskfromDevEn();
  }

  RpEnabledMask = (RpEnMaskFromPolicy & RpEnMaskFromDevEn);
  //
  // Read RPC to identify the furcation logic - applicable only for DT_HALO
  //
  if (GetCpuFamily () == CPUID_FULL_FAMILY_MODEL_TIGERLAKE_DT_HALO) {
    RpEnMaskFromRpc = GetRpEnMaskfromRpc ();
    RpEnabledMask &= RpEnMaskFromRpc;
  }

  if (SaPegHob != NULL) {
    SaPegHob->RpEnabledMask = RpEnabledMask;
    SaPegHob->RpEnMaskFromDevEn = RpEnMaskFromDevEn;
  }
  DEBUG((DEBUG_INFO, "SaPegHob->RpEnabledMask formed after reading DID/setup and controllerconfig = %x\n", SaPegHob->RpEnabledMask));

  if (RpEnabledMask == 0) {
    DEBUG((DEBUG_ERROR, " All CPU PCIe root ports are disabled!!!\n"));
    return;
  }

  //
  // Prior to initiating link training, BIOS should program PHY configuration registers.
  // Call DEKEL init function to configure the PHY registers
  //
    DEBUG((DEBUG_INFO, "Call DEKEL init function to configure the PHY registers\n"));
    DekelInit ((CPU_SB_DEVICE_PID) CPU_SB_PID_DEKEL_IO4);

  //
  // Enable CLKREQ# messaging flow
  //
  if (CpuPcieRpPreMemConfig->ClkReqMsgEnable != 0) {
    DEBUG ((DEBUG_INFO, "ClockReq Messaging Enable\n"));
    CpuPcieConfigureClockReqMessaging (RpEnabledMask, CpuPcieRpPreMemConfig, SaPegHob);
  }
  //
  // Clock output delay must be configured before enabling CLKREQ messaging flow
  //
  DEBUG((DEBUG_ERROR, " Before PchFiaSetClockOutputDelay!!!\n"));

  PchFiaSetClockOutputDelay();

  //
  // Assertion of GPIOs on Link Down - this is a debug feature, if any of the links go down, a GPIO is asserted to indicate the failure
  //
  if (CpuPcieRpPreMemConfig->LinkDownGpios != 0) {
    DEBUG ((DEBUG_INFO, "Assertion of GPIOs on Link Down\n"));
    for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; RpIndex++) {
      if (RpEnabledMask & (BIT0 << RpIndex)) {
        CpuPcieRpLinkDownGpios (RpIndex);
      }
    }
  }

  for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; RpIndex++) {
    RpBase = CpuPcieBase (RpIndex);
    if (RpEnabledMask & (BIT0 << RpIndex)) {
      //
      // Set TLS to gen1
      //
      GetCpuPcieRpDevFun (RpIndex, &RpDevice, &RpFunction);
      DEBUG ((DEBUG_INFO, "**** BDF = 0%x%x ****\n", RpDevice, RpFunction));
      DEBUG ((DEBUG_INFO, "Set TLS to gen1\n"));
      PciSegmentAndThenOr32 (RpBase + R_PCIE_LCTL2, (UINT32)~(B_PCIE_LCTL2_TLS_MASK), (UINT32) V_PCIE_LCTL2_TLS_GEN1);
      //
      // Limit Link Speed Based on Policy - Should be Executed before BLKDQDASD is cleared.
      //
      LimitLinkSpeed (RpIndex);
      //
      // Downstream Config Type 1 Conversion before any downstream aceess 0xEC[15] 1
      //
      RpBase = CpuPcieBase(RpIndex);
      PciSegmentOr32 (RpBase + R_PCIE_DC, B_PCIE_DC_DCT1C);
      //
      // Retrain link by clearing BLKDQDASD
      //
      DEBUG ((DEBUG_INFO, "Retrain link by clearing BLKDQDASD\n"));
      PciSegmentAnd32 (RpBase + R_PCIE_PCIEALC, (UINT32)~(B_PCIE_PCIEALC_BLKDQDASD));
    }
  }
  for (TimeoutUs = 0; ((LinkActiveEnableMask != RpEnabledMask) && (TimeoutUs < 1000)); TimeoutUs++) {
    for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; RpIndex++) {
      RpBase = CpuPcieBase (RpIndex);
      //DEBUG ((DEBUG_INFO, "RpIndex %d, Timeout %dus\n", RpIndex, TimeoutUs*100));
      if (CpuPcieIsLinkActive (RpBase)) {
        LinkActiveEnableMask |= (BIT0 << RpIndex);
      }
    }
    MicroSecondDelay (100);
  }

  ///
  /// This is a spec defined delay - a hard coded 100ms before endpoint access
  ///
  if (LinkActiveEnableMask != 0) {
    MicroSecondDelay (100000);
  }
  for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; RpIndex++) {
    RpBase = CpuPcieBase (RpIndex);
    if (RpEnabledMask & (BIT0 << RpIndex)) {
      DEBUG((DEBUG_INFO, "Target link speed = %x\n", (PciSegmentRead32(RpBase + R_PCIE_LCTL2) & B_PCIE_LCTL2_TLS_MASK)));
      Data32 = (PciSegmentRead32 (RpBase + R_PCIE_LCTL) >> 16); // Value of LSTS register
      DEBUG ((DEBUG_INFO, "Current link speed = %x\n", Data32 & B_PCIE_LSTS_CLS_MASK));
      DEBUG ((DEBUG_INFO, "Negotiated link Width = %x\n", (Data32 & B_PCIE_LSTS_NLW_MASK) >> 4));
      if (!(Data32 & B_PCIE_LSTS_LA)){
        DEBUG((DEBUG_ERROR, "Link is not active yet!!!\n"));
      }
    }
  }

  for (RpIndex = 0; RpIndex < MaxCpuPciePortNum; RpIndex++) {
    DEBUG((DEBUG_INFO, "Program the CLKREQ ASSERT pin\n"));
    CpuPcieSetAssertClkReq(RpIndex); // Program the CLKREQ ASSERT pin
  }

  StatusBit = CpuPciePollClkReqMsgSts(RpEnabledMask);
  DEBUG((DEBUG_INFO, "CpuPciePollClkReqMsgSts StatusBit = %x\n", StatusBit));
  if ((RpEnabledMask & StatusBit) != RpEnabledMask) {
    DEBUG((DEBUG_INFO, "CpuPciePollClkReqMsgSts failed, so Disable CLKREQ# messaging\n"));
    CpuPcieDisableClkReqMsg(RpEnabledMask, StatusBit, SaPegHob);
  }

  DEBUG((DEBUG_INFO, "**** Premem PciExpressInit End ****\n"));
  return;
}


