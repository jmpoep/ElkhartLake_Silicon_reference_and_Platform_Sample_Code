#ifndef __Pci000Tgl_h__
#define __Pci000Tgl_h__
/** @file
  This file was automatically generated. Modify at your own risk.
  Note that no error checking is done in these functions so ensure that the correct values are passed.

@copyright
  Copyright (c) 2010 - 2019 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by the
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.
  This file contains an 'Intel Peripheral Driver' and is uniquely
  identified as "Intel Reference Module" and is licensed for Intel
  CPUs and chipsets under the terms of your license agreement with
  Intel or your vendor. This file may be modified by the user, subject
  to additional terms of the license agreement.

@par Specification Reference:
**/

#pragma pack(push, 1)
typedef union {
  struct {
    UINT32 PXPEPBAREN                              :  1;  // Bits 0:0
    UINT32                                         :  11;  // Bits 11:1
    UINT32 PXPEPBARLow                             :  20;  // Bits 31:12
    UINT32 PXPEPBARHigh                            :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PXPEPBAR_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 MCHBAREN                                :  1;  // Bits 0:0
    UINT32                                         :  16;  // Bits 16:1
    UINT32 MCHBARLow                               :  15;  // Bits 31:17
    UINT32 MCHBARHigh                              :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 GGCLCK                                  :  1;  // Bits 0:0
    UINT32 IVD                                     :  1;  // Bits 1:1
    UINT32 VAMEN                                   :  1;  // Bits 2:2
    UINT32                                         :  3;  // Bits 5:3
    UINT32 GGMS                                    :  2;  // Bits 7:6
    UINT32 GMS                                     :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} GGC_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 D0EN                                    :  1;  // Bits 0:0
    UINT32 D1F2EN                                  :  1;  // Bits 1:1
    UINT32 D1F1EN                                  :  1;  // Bits 2:2
    UINT32 D1F0EN                                  :  1;  // Bits 3:3
    UINT32 D2EN                                    :  1;  // Bits 4:4
    UINT32 SPARE5                                  :  1;  // Bits 5:5
    UINT32 D3EN                                    :  1;  // Bits 6:6
    UINT32 D4EN                                    :  1;  // Bits 7:7
    UINT32 SPARE9_8                                :  2;  // Bits 9:8
    UINT32 D5EN                                    :  1;  // Bits 10:10
    UINT32 SPARE11                                 :  1;  // Bits 11:11
    UINT32 D9EN                                    :  1;  // Bits 12:12
    UINT32 D6EN                                    :  1;  // Bits 13:13
    UINT32 D14F0EN                                 :  1;  // Bits 14:14
    UINT32 D8EN                                    :  1;  // Bits 15:15
    UINT32 SPARE16                                 :  1;  // Bits 16:16
    UINT32 D10EN                                   :  1;  // Bits 17:17
    UINT32 Reserved                                :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DEVEN_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 PCME                                    :  1;  // Bits 0:0
    UINT32 PAVPE                                   :  1;  // Bits 1:1
    UINT32 PAVPLCK                                 :  1;  // Bits 2:2
    UINT32 HVYMODSEL                               :  1;  // Bits 3:3
    UINT32 OVTATTACK                               :  1;  // Bits 4:4
    UINT32 RSVD1                                   :  1;  // Bits 5:5
    UINT32 ASMFEN                                  :  1;  // Bits 6:6
    UINT32 RSVD2                                   :  13;  // Bits 19:7
    UINT32 PCMBASE                                 :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PAVPC_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32 PRS                                     :  1;  // Bits 1:1
    UINT32 EPM                                     :  1;  // Bits 2:2
    UINT32 RSVD                                    :  1;  // Bits 3:3
    UINT32 DPRSIZE                                 :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 TopOfDPR                                :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DPR_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 PCIEXBAREN                              :  1;  // Bits 0:0
    UINT32 Length                                  :  3;  // Bits 3:1
    UINT32                                         :  22;  // Bits 25:4
    UINT32 ADMSK64                                 :  1;  // Bits 26:26
    UINT32 ADMSK128                                :  1;  // Bits 27:27
    UINT32 ADMSK256                                :  1;  // Bits 28:28
    UINT32 ADMSK512                                :  1;  // Bits 29:29
    UINT32 ADMSK1024                               :  1;  // Bits 30:30
    UINT32 PCIEXBARLow                             :  1;  // Bits 31:31
    UINT32 PCIEXBARHigh                            :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCIEXBAR_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 DMIBAREN                                :  1;  // Bits 0:0
    UINT32                                         :  11;  // Bits 11:1
    UINT32 DMIBARLow                               :  20;  // Bits 31:12
    UINT32 DMIBARHigh                              :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} DMIBAR_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 PCIE0SEG                                :  4;  // Bits 3:0
    UINT32 PCIE1SEG                                :  4;  // Bits 7:4
    UINT32 PCIE2SEG                                :  4;  // Bits 11:8
    UINT32 PCIE3SEG                                :  4;  // Bits 15:12
    UINT32 PCIE4SEG                                :  4;  // Bits 19:16
    UINT32 PCIE5SEG                                :  4;  // Bits 23:20
    UINT32 PCIE6SEG                                :  4;  // Bits 27:24
    UINT32 PCIE7SEG                                :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCIESEGMAP_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 PCIE0FUNC                               :  3;  // Bits 2:0
    UINT32 PCIE1FUNC                               :  3;  // Bits 5:3
    UINT32 PCIE2FUNC                               :  3;  // Bits 8:6
    UINT32 PCIE3FUNC                               :  3;  // Bits 11:9
    UINT32 PCIE4FUNC                               :  3;  // Bits 14:12
    UINT32 PCIE5FUNC                               :  3;  // Bits 17:15
    UINT32 PCIE6FUNC                               :  3;  // Bits 20:18
    UINT32 PCIE7FUNC                               :  3;  // Bits 23:21
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCIEFUNCMAP_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT8  LOCK                                    :  1;  // Bits 0:0
    UINT8                                          :  3;  // Bits 3:1
    UINT8  HIENABLE                                :  2;  // Bits 5:4
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} PAM0_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT8  LOENABLE                                :  2;  // Bits 1:0
    UINT8                                          :  2;  // Bits 3:2
    UINT8  HIENABLE                                :  2;  // Bits 5:4
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} PAM1_0_0_0_PCI_STRUCT;

typedef PAM1_0_0_0_PCI_STRUCT PAM2_0_0_0_PCI_STRUCT;

typedef PAM1_0_0_0_PCI_STRUCT PAM3_0_0_0_PCI_STRUCT;

typedef PAM1_0_0_0_PCI_STRUCT PAM4_0_0_0_PCI_STRUCT;

typedef PAM1_0_0_0_PCI_STRUCT PAM5_0_0_0_PCI_STRUCT;

typedef PAM1_0_0_0_PCI_STRUCT PAM6_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT8  MDAP10                                  :  1;  // Bits 0:0
    UINT8  MDAP11                                  :  1;  // Bits 1:1
    UINT8  MDAP12                                  :  1;  // Bits 2:2
    UINT8  MDAP60                                  :  1;  // Bits 3:3
    UINT8  MDAPCIe                                 :  1;  // Bits 4:4
    UINT8                                          :  2;  // Bits 6:5
    UINT8  HEN                                     :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} LAC_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32                                         :  19;  // Bits 19:1
    UINT32 TOMLow                                  :  12;  // Bits 31:20
    UINT32 TOMHigh                                 :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} TOM_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32                                         :  19;  // Bits 19:1
    UINT32 TOUUDLow                                :  12;  // Bits 31:20
    UINT32 TOUUDHigh                               :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} TOUUD_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32                                         :  19;  // Bits 19:1
    UINT32 BDSM                                    :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BDSM_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32                                         :  19;  // Bits 19:1
    UINT32 BGSM                                    :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BGSM_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32                                         :  19;  // Bits 19:1
    UINT32 TSEGMB                                  :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} TSEGMB_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32                                         :  19;  // Bits 19:1
    UINT32 TOLUD                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} TOLUD_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 DID2OVR                                 :  8;  // Bits 7:0
    UINT32 OE2                                     :  1;  // Bits 8:8
    UINT32                                         :  7;  // Bits 15:9
    UINT32 DID0OVR                                 :  8;  // Bits 23:16
    UINT32 OE0                                     :  1;  // Bits 24:24
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DIDOVR_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 DSERR                                   :  1;  // Bits 0:0
    UINT32 DMERR                                   :  1;  // Bits 1:1
    UINT32                                         :  4;  // Bits 5:2
    UINT32 UNSUPPORTED_ATOMIC                      :  1;  // Bits 6:6
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} ERRSTS_0_0_0_PCI_STRUCT;

typedef ERRSTS_0_0_0_PCI_STRUCT ERRCMD_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 DSESMI                                  :  1;  // Bits 0:0
    UINT32 DMESMI                                  :  1;  // Bits 1:1
    UINT32                                         :  4;  // Bits 5:2
    UINT32 UNSUPPORTED_ATOMIC                      :  1;  // Bits 6:6
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} SMICMD_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 DSESCI                                  :  1;  // Bits 0:0
    UINT32 DMESCI                                  :  1;  // Bits 1:1
    UINT32                                         :  4;  // Bits 5:2
    UINT32 UNSUPPORTED_ATOMIC                      :  1;  // Bits 6:6
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} SCICMD_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 SKPD                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} SKPD_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 CAP_ID                                  :  8;  // Bits 7:0
    UINT32 NEXT_CAP                                :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CAPID0_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 CAPIDLEN                                :  8;  // Bits 7:0
    UINT32 CAPID_VER                               :  4;  // Bits 11:8
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CAPCTRL0_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 SPARE_0                                 :  1;  // Bits 0:0
    UINT32 SPARE_1                                 :  1;  // Bits 1:1
    UINT32 OC_ENABLED_DSKU                         :  1;  // Bits 2:2
    UINT32 DDR_OVERCLOCK                           :  1;  // Bits 3:3
    UINT32 CRID                                    :  4;  // Bits 7:4
    UINT32 SPARE_8                                 :  1;  // Bits 8:8
    UINT32 SPARE_9                                 :  1;  // Bits 9:9
    UINT32 DID0OE                                  :  1;  // Bits 10:10
    UINT32 IGD                                     :  1;  // Bits 11:11
    UINT32 PDCD                                    :  1;  // Bits 12:12
    UINT32 X2APIC_EN                               :  1;  // Bits 13:13
    UINT32 DDPCD                                   :  1;  // Bits 14:14
    UINT32 CDD                                     :  1;  // Bits 15:15
    UINT32 FUFRD                                   :  1;  // Bits 16:16
    UINT32 D1NM                                    :  1;  // Bits 17:17
    UINT32 PEG60D                                  :  1;  // Bits 18:18
    UINT32 DDRSZ                                   :  2;  // Bits 20:19
    UINT32 PEGG2DIS                                :  1;  // Bits 21:21
    UINT32 DMIG2DIS                                :  1;  // Bits 22:22
    UINT32 VTDD                                    :  1;  // Bits 23:23
    UINT32 FDEE                                    :  1;  // Bits 24:24
    UINT32 ECCDIS                                  :  1;  // Bits 25:25
    UINT32 DW                                      :  1;  // Bits 26:26
    UINT32 PELWUD                                  :  1;  // Bits 27:27
    UINT32 PEG10D                                  :  1;  // Bits 28:28
    UINT32 PEG11D                                  :  1;  // Bits 29:29
    UINT32 PEG12D                                  :  1;  // Bits 30:30
    UINT32 NVME_DIS                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CAPID0_A_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 SPEGFX1                                 :  1;  // Bits 0:0
    UINT32 DPEGFX1                                 :  1;  // Bits 1:1
    UINT32 VMD_DIS                                 :  1;  // Bits 2:2
    UINT32 SH_OPI_EN                               :  1;  // Bits 3:3
    UINT32 SPARE_4                                 :  1;  // Bits 4:4
    UINT32 SPARE_5                                 :  1;  // Bits 5:5
    UINT32 SPARE_6                                 :  1;  // Bits 6:6
    UINT32 DDD                                     :  1;  // Bits 7:7
    UINT32 GMM_DIS                                 :  1;  // Bits 8:8
    UINT32 SPARE_9                                 :  1;  // Bits 9:9
    UINT32 SPARE_10                                :  1;  // Bits 10:10
    UINT32 HDCPD                                   :  1;  // Bits 11:11
    UINT32 LTECH                                   :  3;  // Bits 14:12
    UINT32 DMIG3DIS                                :  1;  // Bits 15:15
    UINT32 PEGX16D                                 :  1;  // Bits 16:16
    UINT32 ADDGFXCAP                               :  1;  // Bits 17:17
    UINT32 ADDGFXEN                                :  1;  // Bits 18:18
    UINT32 PKGTYP                                  :  1;  // Bits 19:19
    UINT32 PEGG3_DIS                               :  1;  // Bits 20:20
    UINT32 PLL_REF100_CFG                          :  3;  // Bits 23:21
    UINT32 SVM_DISABLE                             :  1;  // Bits 24:24
    UINT32 CACHESZ                                 :  3;  // Bits 27:25
    UINT32 SMT                                     :  1;  // Bits 28:28
    UINT32 OC_ENABLED                              :  1;  // Bits 29:29
    UINT32 NPK_DIS                                 :  1;  // Bits 30:30
    UINT32 IMGU_DIS                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CAPID0_B_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 Max_Data_Rate_At_GEAR1                  :  5;  // Bits 4:0
    UINT32 DISPLAY_PIPE3                           :  1;  // Bits 5:5
    UINT32 IDD                                     :  1;  // Bits 6:6
    UINT32 BCLKOCRANGE                             :  2;  // Bits 8:7
    UINT32 SE_DIS                                  :  1;  // Bits 9:9
    UINT32 FDSKUFP                                 :  4;  // Bits 13:10
    UINT32 QCLK_GV_DIS                             :  1;  // Bits 14:14
    UINT32 SPARE_15                                :  1;  // Bits 15:15
    UINT32 LPDDR4_EN                               :  1;  // Bits 16:16
    UINT32 MAX_DATA_RATE_LPDDR4                    :  5;  // Bits 21:17
    UINT32 DDR4_EN                                 :  1;  // Bits 22:22
    UINT32 MAX_DATA_RATE_DDR4                      :  5;  // Bits 27:23
    UINT32 PEGG4_DIS                               :  1;  // Bits 28:28
    UINT32 SPARE_31_29                             :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CAPID0_C_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 LPDDR5_EN                               :  1;  // Bits 0:0
    UINT32 MAX_DATA_RATE_LPDDR5                    :  5;  // Bits 5:1
    UINT32 DDR5_EN                                 :  1;  // Bits 6:6
    UINT32 MAX_DATA_RATE_DDR5                      :  5;  // Bits 11:7
    UINT32 IBECC_DIS                               :  1;  // Bits 12:12
    UINT32 VDDQ_VOLTAGE_MAX                        :  11;  // Bits 23:13
    UINT32 CRASHLOG_DIS                            :  1;  // Bits 24:24
    UINT32 SPARE                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CAPID0_E_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 PROC                                    :  8;  // Bits 7:0
    UINT32 FOUND                                   :  8;  // Bits 15:8
    UINT32 MSTEP                                   :  8;  // Bits 23:16
    UINT32 DOT                                     :  4;  // Bits 27:24
    UINT32                                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MID_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 RSVD_S0                                 :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 RSVD_S1                                 :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 RSVD_S2                                 :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 RSVD_S3                                 :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 RSVD_S4                                 :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 RSVD_RW                                 :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DEBUP0_0_0_0_PCI_STRUCT;
typedef union {
  struct {
    UINT32 RSVD0                                   :  3;  // Bits 2:0
    UINT32 RSVD1                                   :  1;  // Bits 3:3
    UINT32 RSVD2                                   :  3;  // Bits 6:4
    UINT32 RSVD3                                   :  1;  // Bits 7:7
    UINT32 RSVD4                                   :  3;  // Bits 10:8
    UINT32 RSVD5                                   :  1;  // Bits 11:11
    UINT32 RSVD6                                   :  3;  // Bits 14:12
    UINT32 RSVD7                                   :  1;  // Bits 15:15
    UINT32 RSVD8                                   :  3;  // Bits 18:16
    UINT32 RSVD9                                   :  1;  // Bits 19:19
    UINT32 RSVD10                                  :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DEBUP1_0_0_0_PCI_STRUCT;

#define PXPEPBAR_0_0_0_PCI_REG                                         (0x00000040)

  #define PXPEPBAR_0_0_0_PCI_PXPEPBAREN_OFF                            ( 0)
  #define PXPEPBAR_0_0_0_PCI_PXPEPBAREN_WID                            ( 1)
  #define PXPEPBAR_0_0_0_PCI_PXPEPBAREN_MSK                            (0x00000001)
  #define PXPEPBAR_0_0_0_PCI_PXPEPBAREN_MIN                            (0)
  #define PXPEPBAR_0_0_0_PCI_PXPEPBAREN_MAX                            (1) // 0x00000001
  #define PXPEPBAR_0_0_0_PCI_PXPEPBAREN_DEF                            (0x00000000)
  #define PXPEPBAR_0_0_0_PCI_PXPEPBAREN_HSH                            (0x41000040)

  #define PXPEPBAR_0_0_0_PCI_PXPEPBAR_OFF                              (12)
  #define PXPEPBAR_0_0_0_PCI_PXPEPBAR_WID                              (27)
  #define PXPEPBAR_0_0_0_PCI_PXPEPBAR_MSK                              (0x0000007FFFFFF000ULL)
  #define PXPEPBAR_0_0_0_PCI_PXPEPBAR_MIN                              (0)
  #define PXPEPBAR_0_0_0_PCI_PXPEPBAR_MAX                              (134217727) // 0x07FFFFFF
  #define PXPEPBAR_0_0_0_PCI_PXPEPBAR_DEF                              (0x00000000)
  #define PXPEPBAR_0_0_0_PCI_PXPEPBAR_HSH                              (0x5B180040)

#define MCHBAR_0_0_0_PCI_REG                                           (0x00000048)

  #define MCHBAR_0_0_0_PCI_MCHBAREN_OFF                                ( 0)
  #define MCHBAR_0_0_0_PCI_MCHBAREN_WID                                ( 1)
  #define MCHBAR_0_0_0_PCI_MCHBAREN_MSK                                (0x00000001)
  #define MCHBAR_0_0_0_PCI_MCHBAREN_MIN                                (0)
  #define MCHBAR_0_0_0_PCI_MCHBAREN_MAX                                (1) // 0x00000001
  #define MCHBAR_0_0_0_PCI_MCHBAREN_DEF                                (0x00000000)
  #define MCHBAR_0_0_0_PCI_MCHBAREN_HSH                                (0x41000048)

  #define MCHBAR_0_0_0_PCI_MCHBAR_OFF                                  (17)
  #define MCHBAR_0_0_0_PCI_MCHBAR_WID                                  (22)
  #define MCHBAR_0_0_0_PCI_MCHBAR_MSK                                  (0x0000007FFFFE0000ULL)
  #define MCHBAR_0_0_0_PCI_MCHBAR_MIN                                  (0)
  #define MCHBAR_0_0_0_PCI_MCHBAR_MAX                                  (4194303) // 0x003FFFFF
  #define MCHBAR_0_0_0_PCI_MCHBAR_DEF                                  (0x00000000)
  #define MCHBAR_0_0_0_PCI_MCHBAR_HSH                                  (0x56220048)

#define GGC_0_0_0_PCI_REG                                              (0x00000050)

  #define GGC_0_0_0_PCI_GGCLCK_OFF                                     ( 0)
  #define GGC_0_0_0_PCI_GGCLCK_WID                                     ( 1)
  #define GGC_0_0_0_PCI_GGCLCK_MSK                                     (0x00000001)
  #define GGC_0_0_0_PCI_GGCLCK_MIN                                     (0)
  #define GGC_0_0_0_PCI_GGCLCK_MAX                                     (1) // 0x00000001
  #define GGC_0_0_0_PCI_GGCLCK_DEF                                     (0x00000000)
  #define GGC_0_0_0_PCI_GGCLCK_HSH                                     (0x01000050)

  #define GGC_0_0_0_PCI_IVD_OFF                                        ( 1)
  #define GGC_0_0_0_PCI_IVD_WID                                        ( 1)
  #define GGC_0_0_0_PCI_IVD_MSK                                        (0x00000002)
  #define GGC_0_0_0_PCI_IVD_MIN                                        (0)
  #define GGC_0_0_0_PCI_IVD_MAX                                        (1) // 0x00000001
  #define GGC_0_0_0_PCI_IVD_DEF                                        (0x00000000)
  #define GGC_0_0_0_PCI_IVD_HSH                                        (0x01020050)

  #define GGC_0_0_0_PCI_VAMEN_OFF                                      ( 2)
  #define GGC_0_0_0_PCI_VAMEN_WID                                      ( 1)
  #define GGC_0_0_0_PCI_VAMEN_MSK                                      (0x00000004)
  #define GGC_0_0_0_PCI_VAMEN_MIN                                      (0)
  #define GGC_0_0_0_PCI_VAMEN_MAX                                      (1) // 0x00000001
  #define GGC_0_0_0_PCI_VAMEN_DEF                                      (0x00000000)
  #define GGC_0_0_0_PCI_VAMEN_HSH                                      (0x01040050)

  #define GGC_0_0_0_PCI_GGMS_OFF                                       ( 6)
  #define GGC_0_0_0_PCI_GGMS_WID                                       ( 2)
  #define GGC_0_0_0_PCI_GGMS_MSK                                       (0x000000C0)
  #define GGC_0_0_0_PCI_GGMS_MIN                                       (0)
  #define GGC_0_0_0_PCI_GGMS_MAX                                       (3) // 0x00000003
  #define GGC_0_0_0_PCI_GGMS_DEF                                       (0x00000000)
  #define GGC_0_0_0_PCI_GGMS_HSH                                       (0x020C0050)

  #define GGC_0_0_0_PCI_GMS_OFF                                        ( 8)
  #define GGC_0_0_0_PCI_GMS_WID                                        ( 8)
  #define GGC_0_0_0_PCI_GMS_MSK                                        (0x0000FF00)
  #define GGC_0_0_0_PCI_GMS_MIN                                        (0)
  #define GGC_0_0_0_PCI_GMS_MAX                                        (255) // 0x000000FF
  #define GGC_0_0_0_PCI_GMS_DEF                                        (0x00000005)
  #define GGC_0_0_0_PCI_GMS_HSH                                        (0x08100050)

#define DEVEN_0_0_0_PCI_REG                                            (0x00000054)

  #define DEVEN_0_0_0_PCI_D0EN_OFF                                     ( 0)
  #define DEVEN_0_0_0_PCI_D0EN_WID                                     ( 1)
  #define DEVEN_0_0_0_PCI_D0EN_MSK                                     (0x00000001)
  #define DEVEN_0_0_0_PCI_D0EN_MIN                                     (0)
  #define DEVEN_0_0_0_PCI_D0EN_MAX                                     (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_D0EN_DEF                                     (0x00000001)
  #define DEVEN_0_0_0_PCI_D0EN_HSH                                     (0x01000054)

  #define DEVEN_0_0_0_PCI_D1F2EN_OFF                                   ( 1)
  #define DEVEN_0_0_0_PCI_D1F2EN_WID                                   ( 1)
  #define DEVEN_0_0_0_PCI_D1F2EN_MSK                                   (0x00000002)
  #define DEVEN_0_0_0_PCI_D1F2EN_MIN                                   (0)
  #define DEVEN_0_0_0_PCI_D1F2EN_MAX                                   (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_D1F2EN_DEF                                   (0x00000001)
  #define DEVEN_0_0_0_PCI_D1F2EN_HSH                                   (0x01020054)

  #define DEVEN_0_0_0_PCI_D1F1EN_OFF                                   ( 2)
  #define DEVEN_0_0_0_PCI_D1F1EN_WID                                   ( 1)
  #define DEVEN_0_0_0_PCI_D1F1EN_MSK                                   (0x00000004)
  #define DEVEN_0_0_0_PCI_D1F1EN_MIN                                   (0)
  #define DEVEN_0_0_0_PCI_D1F1EN_MAX                                   (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_D1F1EN_DEF                                   (0x00000001)
  #define DEVEN_0_0_0_PCI_D1F1EN_HSH                                   (0x01040054)

  #define DEVEN_0_0_0_PCI_D1F0EN_OFF                                   ( 3)
  #define DEVEN_0_0_0_PCI_D1F0EN_WID                                   ( 1)
  #define DEVEN_0_0_0_PCI_D1F0EN_MSK                                   (0x00000008)
  #define DEVEN_0_0_0_PCI_D1F0EN_MIN                                   (0)
  #define DEVEN_0_0_0_PCI_D1F0EN_MAX                                   (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_D1F0EN_DEF                                   (0x00000001)
  #define DEVEN_0_0_0_PCI_D1F0EN_HSH                                   (0x01060054)

  #define DEVEN_0_0_0_PCI_D2EN_OFF                                     ( 4)
  #define DEVEN_0_0_0_PCI_D2EN_WID                                     ( 1)
  #define DEVEN_0_0_0_PCI_D2EN_MSK                                     (0x00000010)
  #define DEVEN_0_0_0_PCI_D2EN_MIN                                     (0)
  #define DEVEN_0_0_0_PCI_D2EN_MAX                                     (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_D2EN_DEF                                     (0x00000001)
  #define DEVEN_0_0_0_PCI_D2EN_HSH                                     (0x01080054)

  #define DEVEN_0_0_0_PCI_SPARE5_OFF                                   ( 5)
  #define DEVEN_0_0_0_PCI_SPARE5_WID                                   ( 1)
  #define DEVEN_0_0_0_PCI_SPARE5_MSK                                   (0x00000020)
  #define DEVEN_0_0_0_PCI_SPARE5_MIN                                   (0)
  #define DEVEN_0_0_0_PCI_SPARE5_MAX                                   (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_SPARE5_DEF                                   (0x00000001)
  #define DEVEN_0_0_0_PCI_SPARE5_HSH                                   (0x010A0054)

  #define DEVEN_0_0_0_PCI_D3EN_OFF                                     ( 6)
  #define DEVEN_0_0_0_PCI_D3EN_WID                                     ( 1)
  #define DEVEN_0_0_0_PCI_D3EN_MSK                                     (0x00000040)
  #define DEVEN_0_0_0_PCI_D3EN_MIN                                     (0)
  #define DEVEN_0_0_0_PCI_D3EN_MAX                                     (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_D3EN_DEF                                     (0x00000000)
  #define DEVEN_0_0_0_PCI_D3EN_HSH                                     (0x010C0054)

  #define DEVEN_0_0_0_PCI_D4EN_OFF                                     ( 7)
  #define DEVEN_0_0_0_PCI_D4EN_WID                                     ( 1)
  #define DEVEN_0_0_0_PCI_D4EN_MSK                                     (0x00000080)
  #define DEVEN_0_0_0_PCI_D4EN_MIN                                     (0)
  #define DEVEN_0_0_0_PCI_D4EN_MAX                                     (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_D4EN_DEF                                     (0x00000001)
  #define DEVEN_0_0_0_PCI_D4EN_HSH                                     (0x010E0054)

  #define DEVEN_0_0_0_PCI_SPARE9_8_OFF                                 ( 8)
  #define DEVEN_0_0_0_PCI_SPARE9_8_WID                                 ( 2)
  #define DEVEN_0_0_0_PCI_SPARE9_8_MSK                                 (0x00000300)
  #define DEVEN_0_0_0_PCI_SPARE9_8_MIN                                 (0)
  #define DEVEN_0_0_0_PCI_SPARE9_8_MAX                                 (3) // 0x00000003
  #define DEVEN_0_0_0_PCI_SPARE9_8_DEF                                 (0x00000000)
  #define DEVEN_0_0_0_PCI_SPARE9_8_HSH                                 (0x02100054)

  #define DEVEN_0_0_0_PCI_D5EN_OFF                                     (10)
  #define DEVEN_0_0_0_PCI_D5EN_WID                                     ( 1)
  #define DEVEN_0_0_0_PCI_D5EN_MSK                                     (0x00000400)
  #define DEVEN_0_0_0_PCI_D5EN_MIN                                     (0)
  #define DEVEN_0_0_0_PCI_D5EN_MAX                                     (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_D5EN_DEF                                     (0x00000001)
  #define DEVEN_0_0_0_PCI_D5EN_HSH                                     (0x01140054)

  #define DEVEN_0_0_0_PCI_SPARE11_OFF                                  (11)
  #define DEVEN_0_0_0_PCI_SPARE11_WID                                  ( 1)
  #define DEVEN_0_0_0_PCI_SPARE11_MSK                                  (0x00000800)
  #define DEVEN_0_0_0_PCI_SPARE11_MIN                                  (0)
  #define DEVEN_0_0_0_PCI_SPARE11_MAX                                  (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_SPARE11_DEF                                  (0x00000000)
  #define DEVEN_0_0_0_PCI_SPARE11_HSH                                  (0x01160054)

  #define DEVEN_0_0_0_PCI_D9EN_OFF                                     (12)
  #define DEVEN_0_0_0_PCI_D9EN_WID                                     ( 1)
  #define DEVEN_0_0_0_PCI_D9EN_MSK                                     (0x00001000)
  #define DEVEN_0_0_0_PCI_D9EN_MIN                                     (0)
  #define DEVEN_0_0_0_PCI_D9EN_MAX                                     (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_D9EN_DEF                                     (0x00000001)
  #define DEVEN_0_0_0_PCI_D9EN_HSH                                     (0x01180054)

  #define DEVEN_0_0_0_PCI_D6EN_OFF                                     (13)
  #define DEVEN_0_0_0_PCI_D6EN_WID                                     ( 1)
  #define DEVEN_0_0_0_PCI_D6EN_MSK                                     (0x00002000)
  #define DEVEN_0_0_0_PCI_D6EN_MIN                                     (0)
  #define DEVEN_0_0_0_PCI_D6EN_MAX                                     (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_D6EN_DEF                                     (0x00000001)
  #define DEVEN_0_0_0_PCI_D6EN_HSH                                     (0x011A0054)

  #define DEVEN_0_0_0_PCI_D14F0EN_OFF                                  (14)
  #define DEVEN_0_0_0_PCI_D14F0EN_WID                                  ( 1)
  #define DEVEN_0_0_0_PCI_D14F0EN_MSK                                  (0x00004000)
  #define DEVEN_0_0_0_PCI_D14F0EN_MIN                                  (0)
  #define DEVEN_0_0_0_PCI_D14F0EN_MAX                                  (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_D14F0EN_DEF                                  (0x00000001)
  #define DEVEN_0_0_0_PCI_D14F0EN_HSH                                  (0x011C0054)

  #define DEVEN_0_0_0_PCI_D8EN_OFF                                     (15)
  #define DEVEN_0_0_0_PCI_D8EN_WID                                     ( 1)
  #define DEVEN_0_0_0_PCI_D8EN_MSK                                     (0x00008000)
  #define DEVEN_0_0_0_PCI_D8EN_MIN                                     (0)
  #define DEVEN_0_0_0_PCI_D8EN_MAX                                     (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_D8EN_DEF                                     (0x00000001)
  #define DEVEN_0_0_0_PCI_D8EN_HSH                                     (0x011E0054)

  #define DEVEN_0_0_0_PCI_SPARE16_OFF                                  (16)
  #define DEVEN_0_0_0_PCI_SPARE16_WID                                  ( 1)
  #define DEVEN_0_0_0_PCI_SPARE16_MSK                                  (0x00010000)
  #define DEVEN_0_0_0_PCI_SPARE16_MIN                                  (0)
  #define DEVEN_0_0_0_PCI_SPARE16_MAX                                  (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_SPARE16_DEF                                  (0x00000000)
  #define DEVEN_0_0_0_PCI_SPARE16_HSH                                  (0x01200054)

  #define DEVEN_0_0_0_PCI_D10EN_OFF                                    (17)
  #define DEVEN_0_0_0_PCI_D10EN_WID                                    ( 1)
  #define DEVEN_0_0_0_PCI_D10EN_MSK                                    (0x00020000)
  #define DEVEN_0_0_0_PCI_D10EN_MIN                                    (0)
  #define DEVEN_0_0_0_PCI_D10EN_MAX                                    (1) // 0x00000001
  #define DEVEN_0_0_0_PCI_D10EN_DEF                                    (0x00000001)
  #define DEVEN_0_0_0_PCI_D10EN_HSH                                    (0x01220054)

  #define DEVEN_0_0_0_PCI_Reserved_OFF                                 (18)
  #define DEVEN_0_0_0_PCI_Reserved_WID                                 (14)
  #define DEVEN_0_0_0_PCI_Reserved_MSK                                 (0xFFFC0000)
  #define DEVEN_0_0_0_PCI_Reserved_MIN                                 (0)
  #define DEVEN_0_0_0_PCI_Reserved_MAX                                 (16383) // 0x00003FFF
  #define DEVEN_0_0_0_PCI_Reserved_DEF                                 (0x00000000)
  #define DEVEN_0_0_0_PCI_Reserved_HSH                                 (0x0E240054)

#define PAVPC_0_0_0_PCI_REG                                            (0x00000058)

  #define PAVPC_0_0_0_PCI_PCME_OFF                                     ( 0)
  #define PAVPC_0_0_0_PCI_PCME_WID                                     ( 1)
  #define PAVPC_0_0_0_PCI_PCME_MSK                                     (0x00000001)
  #define PAVPC_0_0_0_PCI_PCME_MIN                                     (0)
  #define PAVPC_0_0_0_PCI_PCME_MAX                                     (1) // 0x00000001
  #define PAVPC_0_0_0_PCI_PCME_DEF                                     (0x00000001)
  #define PAVPC_0_0_0_PCI_PCME_HSH                                     (0x01000058)

  #define PAVPC_0_0_0_PCI_PAVPE_OFF                                    ( 1)
  #define PAVPC_0_0_0_PCI_PAVPE_WID                                    ( 1)
  #define PAVPC_0_0_0_PCI_PAVPE_MSK                                    (0x00000002)
  #define PAVPC_0_0_0_PCI_PAVPE_MIN                                    (0)
  #define PAVPC_0_0_0_PCI_PAVPE_MAX                                    (1) // 0x00000001
  #define PAVPC_0_0_0_PCI_PAVPE_DEF                                    (0x00000000)
  #define PAVPC_0_0_0_PCI_PAVPE_HSH                                    (0x01020058)

  #define PAVPC_0_0_0_PCI_PAVPLCK_OFF                                  ( 2)
  #define PAVPC_0_0_0_PCI_PAVPLCK_WID                                  ( 1)
  #define PAVPC_0_0_0_PCI_PAVPLCK_MSK                                  (0x00000004)
  #define PAVPC_0_0_0_PCI_PAVPLCK_MIN                                  (0)
  #define PAVPC_0_0_0_PCI_PAVPLCK_MAX                                  (1) // 0x00000001
  #define PAVPC_0_0_0_PCI_PAVPLCK_DEF                                  (0x00000000)
  #define PAVPC_0_0_0_PCI_PAVPLCK_HSH                                  (0x01040058)

  #define PAVPC_0_0_0_PCI_HVYMODSEL_OFF                                ( 3)
  #define PAVPC_0_0_0_PCI_HVYMODSEL_WID                                ( 1)
  #define PAVPC_0_0_0_PCI_HVYMODSEL_MSK                                (0x00000008)
  #define PAVPC_0_0_0_PCI_HVYMODSEL_MIN                                (0)
  #define PAVPC_0_0_0_PCI_HVYMODSEL_MAX                                (1) // 0x00000001
  #define PAVPC_0_0_0_PCI_HVYMODSEL_DEF                                (0x00000000)
  #define PAVPC_0_0_0_PCI_HVYMODSEL_HSH                                (0x01060058)

  #define PAVPC_0_0_0_PCI_OVTATTACK_OFF                                ( 4)
  #define PAVPC_0_0_0_PCI_OVTATTACK_WID                                ( 1)
  #define PAVPC_0_0_0_PCI_OVTATTACK_MSK                                (0x00000010)
  #define PAVPC_0_0_0_PCI_OVTATTACK_MIN                                (0)
  #define PAVPC_0_0_0_PCI_OVTATTACK_MAX                                (1) // 0x00000001
  #define PAVPC_0_0_0_PCI_OVTATTACK_DEF                                (0x00000000)
  #define PAVPC_0_0_0_PCI_OVTATTACK_HSH                                (0x01080058)

  #define PAVPC_0_0_0_PCI_RSVD1_OFF                                    ( 5)
  #define PAVPC_0_0_0_PCI_RSVD1_WID                                    ( 1)
  #define PAVPC_0_0_0_PCI_RSVD1_MSK                                    (0x00000020)
  #define PAVPC_0_0_0_PCI_RSVD1_MIN                                    (0)
  #define PAVPC_0_0_0_PCI_RSVD1_MAX                                    (1) // 0x00000001
  #define PAVPC_0_0_0_PCI_RSVD1_DEF                                    (0x00000000)
  #define PAVPC_0_0_0_PCI_RSVD1_HSH                                    (0x010A0058)

  #define PAVPC_0_0_0_PCI_ASMFEN_OFF                                   ( 6)
  #define PAVPC_0_0_0_PCI_ASMFEN_WID                                   ( 1)
  #define PAVPC_0_0_0_PCI_ASMFEN_MSK                                   (0x00000040)
  #define PAVPC_0_0_0_PCI_ASMFEN_MIN                                   (0)
  #define PAVPC_0_0_0_PCI_ASMFEN_MAX                                   (1) // 0x00000001
  #define PAVPC_0_0_0_PCI_ASMFEN_DEF                                   (0x00000000)
  #define PAVPC_0_0_0_PCI_ASMFEN_HSH                                   (0x010C0058)

  #define PAVPC_0_0_0_PCI_RSVD2_OFF                                    ( 7)
  #define PAVPC_0_0_0_PCI_RSVD2_WID                                    (13)
  #define PAVPC_0_0_0_PCI_RSVD2_MSK                                    (0x000FFF80)
  #define PAVPC_0_0_0_PCI_RSVD2_MIN                                    (0)
  #define PAVPC_0_0_0_PCI_RSVD2_MAX                                    (8191) // 0x00001FFF
  #define PAVPC_0_0_0_PCI_RSVD2_DEF                                    (0x00000000)
  #define PAVPC_0_0_0_PCI_RSVD2_HSH                                    (0x0D0E0058)

  #define PAVPC_0_0_0_PCI_PCMBASE_OFF                                  (20)
  #define PAVPC_0_0_0_PCI_PCMBASE_WID                                  (12)
  #define PAVPC_0_0_0_PCI_PCMBASE_MSK                                  (0xFFF00000)
  #define PAVPC_0_0_0_PCI_PCMBASE_MIN                                  (0)
  #define PAVPC_0_0_0_PCI_PCMBASE_MAX                                  (4095) // 0x00000FFF
  #define PAVPC_0_0_0_PCI_PCMBASE_DEF                                  (0x00000000)
  #define PAVPC_0_0_0_PCI_PCMBASE_HSH                                  (0x0C280058)

#define DPR_0_0_0_PCI_REG                                              (0x0000005C)

  #define DPR_0_0_0_PCI_LOCK_OFF                                       ( 0)
  #define DPR_0_0_0_PCI_LOCK_WID                                       ( 1)
  #define DPR_0_0_0_PCI_LOCK_MSK                                       (0x00000001)
  #define DPR_0_0_0_PCI_LOCK_MIN                                       (0)
  #define DPR_0_0_0_PCI_LOCK_MAX                                       (1) // 0x00000001
  #define DPR_0_0_0_PCI_LOCK_DEF                                       (0x00000000)
  #define DPR_0_0_0_PCI_LOCK_HSH                                       (0x0100005C)

  #define DPR_0_0_0_PCI_PRS_OFF                                        ( 1)
  #define DPR_0_0_0_PCI_PRS_WID                                        ( 1)
  #define DPR_0_0_0_PCI_PRS_MSK                                        (0x00000002)
  #define DPR_0_0_0_PCI_PRS_MIN                                        (0)
  #define DPR_0_0_0_PCI_PRS_MAX                                        (1) // 0x00000001
  #define DPR_0_0_0_PCI_PRS_DEF                                        (0x00000000)
  #define DPR_0_0_0_PCI_PRS_HSH                                        (0x0102005C)

  #define DPR_0_0_0_PCI_EPM_OFF                                        ( 2)
  #define DPR_0_0_0_PCI_EPM_WID                                        ( 1)
  #define DPR_0_0_0_PCI_EPM_MSK                                        (0x00000004)
  #define DPR_0_0_0_PCI_EPM_MIN                                        (0)
  #define DPR_0_0_0_PCI_EPM_MAX                                        (1) // 0x00000001
  #define DPR_0_0_0_PCI_EPM_DEF                                        (0x00000000)
  #define DPR_0_0_0_PCI_EPM_HSH                                        (0x0104005C)

  #define DPR_0_0_0_PCI_RSVD_OFF                                       ( 3)
  #define DPR_0_0_0_PCI_RSVD_WID                                       ( 1)
  #define DPR_0_0_0_PCI_RSVD_MSK                                       (0x00000008)
  #define DPR_0_0_0_PCI_RSVD_MIN                                       (0)
  #define DPR_0_0_0_PCI_RSVD_MAX                                       (1) // 0x00000001
  #define DPR_0_0_0_PCI_RSVD_DEF                                       (0x00000000)
  #define DPR_0_0_0_PCI_RSVD_HSH                                       (0x0106005C)

  #define DPR_0_0_0_PCI_DPRSIZE_OFF                                    ( 4)
  #define DPR_0_0_0_PCI_DPRSIZE_WID                                    ( 8)
  #define DPR_0_0_0_PCI_DPRSIZE_MSK                                    (0x00000FF0)
  #define DPR_0_0_0_PCI_DPRSIZE_MIN                                    (0)
  #define DPR_0_0_0_PCI_DPRSIZE_MAX                                    (255) // 0x000000FF
  #define DPR_0_0_0_PCI_DPRSIZE_DEF                                    (0x00000000)
  #define DPR_0_0_0_PCI_DPRSIZE_HSH                                    (0x0808005C)

  #define DPR_0_0_0_PCI_TopOfDPR_OFF                                   (20)
  #define DPR_0_0_0_PCI_TopOfDPR_WID                                   (12)
  #define DPR_0_0_0_PCI_TopOfDPR_MSK                                   (0xFFF00000)
  #define DPR_0_0_0_PCI_TopOfDPR_MIN                                   (0)
  #define DPR_0_0_0_PCI_TopOfDPR_MAX                                   (4095) // 0x00000FFF
  #define DPR_0_0_0_PCI_TopOfDPR_DEF                                   (0x00000000)
  #define DPR_0_0_0_PCI_TopOfDPR_HSH                                   (0x0C28005C)

#define PCIEXBAR_0_0_0_PCI_REG                                         (0x00000060)

  #define PCIEXBAR_0_0_0_PCI_PCIEXBAREN_OFF                            ( 0)
  #define PCIEXBAR_0_0_0_PCI_PCIEXBAREN_WID                            ( 1)
  #define PCIEXBAR_0_0_0_PCI_PCIEXBAREN_MSK                            (0x00000001)
  #define PCIEXBAR_0_0_0_PCI_PCIEXBAREN_MIN                            (0)
  #define PCIEXBAR_0_0_0_PCI_PCIEXBAREN_MAX                            (1) // 0x00000001
  #define PCIEXBAR_0_0_0_PCI_PCIEXBAREN_DEF                            (0x00000000)
  #define PCIEXBAR_0_0_0_PCI_PCIEXBAREN_HSH                            (0x41000060)

  #define PCIEXBAR_0_0_0_PCI_Length_OFF                                ( 1)
  #define PCIEXBAR_0_0_0_PCI_Length_WID                                ( 3)
  #define PCIEXBAR_0_0_0_PCI_Length_MSK                                (0x0000000E)
  #define PCIEXBAR_0_0_0_PCI_Length_MIN                                (0)
  #define PCIEXBAR_0_0_0_PCI_Length_MAX                                (7) // 0x00000007
  #define PCIEXBAR_0_0_0_PCI_Length_DEF                                (0x00000000)
  #define PCIEXBAR_0_0_0_PCI_Length_HSH                                (0x43020060)

  #define PCIEXBAR_0_0_0_PCI_ADMSK64_OFF                               (26)
  #define PCIEXBAR_0_0_0_PCI_ADMSK64_WID                               ( 1)
  #define PCIEXBAR_0_0_0_PCI_ADMSK64_MSK                               (0x04000000)
  #define PCIEXBAR_0_0_0_PCI_ADMSK64_MIN                               (0)
  #define PCIEXBAR_0_0_0_PCI_ADMSK64_MAX                               (1) // 0x00000001
  #define PCIEXBAR_0_0_0_PCI_ADMSK64_DEF                               (0x00000000)
  #define PCIEXBAR_0_0_0_PCI_ADMSK64_HSH                               (0x41340060)

  #define PCIEXBAR_0_0_0_PCI_ADMSK128_OFF                              (27)
  #define PCIEXBAR_0_0_0_PCI_ADMSK128_WID                              ( 1)
  #define PCIEXBAR_0_0_0_PCI_ADMSK128_MSK                              (0x08000000)
  #define PCIEXBAR_0_0_0_PCI_ADMSK128_MIN                              (0)
  #define PCIEXBAR_0_0_0_PCI_ADMSK128_MAX                              (1) // 0x00000001
  #define PCIEXBAR_0_0_0_PCI_ADMSK128_DEF                              (0x00000000)
  #define PCIEXBAR_0_0_0_PCI_ADMSK128_HSH                              (0x41360060)

  #define PCIEXBAR_0_0_0_PCI_ADMSK256_OFF                              (28)
  #define PCIEXBAR_0_0_0_PCI_ADMSK256_WID                              ( 1)
  #define PCIEXBAR_0_0_0_PCI_ADMSK256_MSK                              (0x10000000)
  #define PCIEXBAR_0_0_0_PCI_ADMSK256_MIN                              (0)
  #define PCIEXBAR_0_0_0_PCI_ADMSK256_MAX                              (1) // 0x00000001
  #define PCIEXBAR_0_0_0_PCI_ADMSK256_DEF                              (0x00000000)
  #define PCIEXBAR_0_0_0_PCI_ADMSK256_HSH                              (0x41380060)

  #define PCIEXBAR_0_0_0_PCI_ADMSK512_OFF                              (29)
  #define PCIEXBAR_0_0_0_PCI_ADMSK512_WID                              ( 1)
  #define PCIEXBAR_0_0_0_PCI_ADMSK512_MSK                              (0x20000000)
  #define PCIEXBAR_0_0_0_PCI_ADMSK512_MIN                              (0)
  #define PCIEXBAR_0_0_0_PCI_ADMSK512_MAX                              (1) // 0x00000001
  #define PCIEXBAR_0_0_0_PCI_ADMSK512_DEF                              (0x00000000)
  #define PCIEXBAR_0_0_0_PCI_ADMSK512_HSH                              (0x413A0060)

  #define PCIEXBAR_0_0_0_PCI_ADMSK1024_OFF                             (30)
  #define PCIEXBAR_0_0_0_PCI_ADMSK1024_WID                             ( 1)
  #define PCIEXBAR_0_0_0_PCI_ADMSK1024_MSK                             (0x40000000)
  #define PCIEXBAR_0_0_0_PCI_ADMSK1024_MIN                             (0)
  #define PCIEXBAR_0_0_0_PCI_ADMSK1024_MAX                             (1) // 0x00000001
  #define PCIEXBAR_0_0_0_PCI_ADMSK1024_DEF                             (0x00000000)
  #define PCIEXBAR_0_0_0_PCI_ADMSK1024_HSH                             (0x413C0060)

  #define PCIEXBAR_0_0_0_PCI_PCIEXBAR_OFF                              (31)
  #define PCIEXBAR_0_0_0_PCI_PCIEXBAR_WID                              ( 8)
  #define PCIEXBAR_0_0_0_PCI_PCIEXBAR_MSK                              (0x0000007F80000000ULL)
  #define PCIEXBAR_0_0_0_PCI_PCIEXBAR_MIN                              (0)
  #define PCIEXBAR_0_0_0_PCI_PCIEXBAR_MAX                              (255) // 0x000000FF
  #define PCIEXBAR_0_0_0_PCI_PCIEXBAR_DEF                              (0x00000000)
  #define PCIEXBAR_0_0_0_PCI_PCIEXBAR_HSH                              (0x483E0060)

#define DMIBAR_0_0_0_PCI_REG                                           (0x00000068)

  #define DMIBAR_0_0_0_PCI_DMIBAREN_OFF                                ( 0)
  #define DMIBAR_0_0_0_PCI_DMIBAREN_WID                                ( 1)
  #define DMIBAR_0_0_0_PCI_DMIBAREN_MSK                                (0x00000001)
  #define DMIBAR_0_0_0_PCI_DMIBAREN_MIN                                (0)
  #define DMIBAR_0_0_0_PCI_DMIBAREN_MAX                                (1) // 0x00000001
  #define DMIBAR_0_0_0_PCI_DMIBAREN_DEF                                (0x00000000)
  #define DMIBAR_0_0_0_PCI_DMIBAREN_HSH                                (0x41000068)

  #define DMIBAR_0_0_0_PCI_DMIBAR_OFF                                  (12)
  #define DMIBAR_0_0_0_PCI_DMIBAR_WID                                  (27)
  #define DMIBAR_0_0_0_PCI_DMIBAR_MSK                                  (0x0000007FFFFFF000ULL)
  #define DMIBAR_0_0_0_PCI_DMIBAR_MIN                                  (0)
  #define DMIBAR_0_0_0_PCI_DMIBAR_MAX                                  (134217727) // 0x07FFFFFF
  #define DMIBAR_0_0_0_PCI_DMIBAR_DEF                                  (0x00000000)
  #define DMIBAR_0_0_0_PCI_DMIBAR_HSH                                  (0x5B180068)

#define PCIESEGMAP_0_0_0_PCI_REG                                       (0x00000078)

  #define PCIESEGMAP_0_0_0_PCI_PCIE0SEG_OFF                            ( 0)
  #define PCIESEGMAP_0_0_0_PCI_PCIE0SEG_WID                            ( 4)
  #define PCIESEGMAP_0_0_0_PCI_PCIE0SEG_MSK                            (0x0000000F)
  #define PCIESEGMAP_0_0_0_PCI_PCIE0SEG_MIN                            (0)
  #define PCIESEGMAP_0_0_0_PCI_PCIE0SEG_MAX                            (15) // 0x0000000F
  #define PCIESEGMAP_0_0_0_PCI_PCIE0SEG_DEF                            (0x00000001)
  #define PCIESEGMAP_0_0_0_PCI_PCIE0SEG_HSH                            (0x04000078)

  #define PCIESEGMAP_0_0_0_PCI_PCIE1SEG_OFF                            ( 4)
  #define PCIESEGMAP_0_0_0_PCI_PCIE1SEG_WID                            ( 4)
  #define PCIESEGMAP_0_0_0_PCI_PCIE1SEG_MSK                            (0x000000F0)
  #define PCIESEGMAP_0_0_0_PCI_PCIE1SEG_MIN                            (0)
  #define PCIESEGMAP_0_0_0_PCI_PCIE1SEG_MAX                            (15) // 0x0000000F
  #define PCIESEGMAP_0_0_0_PCI_PCIE1SEG_DEF                            (0x00000002)
  #define PCIESEGMAP_0_0_0_PCI_PCIE1SEG_HSH                            (0x04080078)

  #define PCIESEGMAP_0_0_0_PCI_PCIE2SEG_OFF                            ( 8)
  #define PCIESEGMAP_0_0_0_PCI_PCIE2SEG_WID                            ( 4)
  #define PCIESEGMAP_0_0_0_PCI_PCIE2SEG_MSK                            (0x00000F00)
  #define PCIESEGMAP_0_0_0_PCI_PCIE2SEG_MIN                            (0)
  #define PCIESEGMAP_0_0_0_PCI_PCIE2SEG_MAX                            (15) // 0x0000000F
  #define PCIESEGMAP_0_0_0_PCI_PCIE2SEG_DEF                            (0x00000003)
  #define PCIESEGMAP_0_0_0_PCI_PCIE2SEG_HSH                            (0x04100078)

  #define PCIESEGMAP_0_0_0_PCI_PCIE3SEG_OFF                            (12)
  #define PCIESEGMAP_0_0_0_PCI_PCIE3SEG_WID                            ( 4)
  #define PCIESEGMAP_0_0_0_PCI_PCIE3SEG_MSK                            (0x0000F000)
  #define PCIESEGMAP_0_0_0_PCI_PCIE3SEG_MIN                            (0)
  #define PCIESEGMAP_0_0_0_PCI_PCIE3SEG_MAX                            (15) // 0x0000000F
  #define PCIESEGMAP_0_0_0_PCI_PCIE3SEG_DEF                            (0x00000004)
  #define PCIESEGMAP_0_0_0_PCI_PCIE3SEG_HSH                            (0x04180078)

  #define PCIESEGMAP_0_0_0_PCI_PCIE4SEG_OFF                            (16)
  #define PCIESEGMAP_0_0_0_PCI_PCIE4SEG_WID                            ( 4)
  #define PCIESEGMAP_0_0_0_PCI_PCIE4SEG_MSK                            (0x000F0000)
  #define PCIESEGMAP_0_0_0_PCI_PCIE4SEG_MIN                            (0)
  #define PCIESEGMAP_0_0_0_PCI_PCIE4SEG_MAX                            (15) // 0x0000000F
  #define PCIESEGMAP_0_0_0_PCI_PCIE4SEG_DEF                            (0x00000005)
  #define PCIESEGMAP_0_0_0_PCI_PCIE4SEG_HSH                            (0x04200078)

  #define PCIESEGMAP_0_0_0_PCI_PCIE5SEG_OFF                            (20)
  #define PCIESEGMAP_0_0_0_PCI_PCIE5SEG_WID                            ( 4)
  #define PCIESEGMAP_0_0_0_PCI_PCIE5SEG_MSK                            (0x00F00000)
  #define PCIESEGMAP_0_0_0_PCI_PCIE5SEG_MIN                            (0)
  #define PCIESEGMAP_0_0_0_PCI_PCIE5SEG_MAX                            (15) // 0x0000000F
  #define PCIESEGMAP_0_0_0_PCI_PCIE5SEG_DEF                            (0x00000006)
  #define PCIESEGMAP_0_0_0_PCI_PCIE5SEG_HSH                            (0x04280078)

  #define PCIESEGMAP_0_0_0_PCI_PCIE6SEG_OFF                            (24)
  #define PCIESEGMAP_0_0_0_PCI_PCIE6SEG_WID                            ( 4)
  #define PCIESEGMAP_0_0_0_PCI_PCIE6SEG_MSK                            (0x0F000000)
  #define PCIESEGMAP_0_0_0_PCI_PCIE6SEG_MIN                            (0)
  #define PCIESEGMAP_0_0_0_PCI_PCIE6SEG_MAX                            (15) // 0x0000000F
  #define PCIESEGMAP_0_0_0_PCI_PCIE6SEG_DEF                            (0x00000000)
  #define PCIESEGMAP_0_0_0_PCI_PCIE6SEG_HSH                            (0x04300078)

  #define PCIESEGMAP_0_0_0_PCI_PCIE7SEG_OFF                            (28)
  #define PCIESEGMAP_0_0_0_PCI_PCIE7SEG_WID                            ( 4)
  #define PCIESEGMAP_0_0_0_PCI_PCIE7SEG_MSK                            (0xF0000000)
  #define PCIESEGMAP_0_0_0_PCI_PCIE7SEG_MIN                            (0)
  #define PCIESEGMAP_0_0_0_PCI_PCIE7SEG_MAX                            (15) // 0x0000000F
  #define PCIESEGMAP_0_0_0_PCI_PCIE7SEG_DEF                            (0x00000000)
  #define PCIESEGMAP_0_0_0_PCI_PCIE7SEG_HSH                            (0x04380078)

#define PCIEFUNCMAP_0_0_0_PCI_REG                                      (0x0000007C)

  #define PCIEFUNCMAP_0_0_0_PCI_PCIE0FUNC_OFF                          ( 0)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE0FUNC_WID                          ( 3)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE0FUNC_MSK                          (0x00000007)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE0FUNC_MIN                          (0)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE0FUNC_MAX                          (7) // 0x00000007
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE0FUNC_DEF                          (0x00000000)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE0FUNC_HSH                          (0x0300007C)

  #define PCIEFUNCMAP_0_0_0_PCI_PCIE1FUNC_OFF                          ( 3)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE1FUNC_WID                          ( 3)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE1FUNC_MSK                          (0x00000038)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE1FUNC_MIN                          (0)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE1FUNC_MAX                          (7) // 0x00000007
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE1FUNC_DEF                          (0x00000000)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE1FUNC_HSH                          (0x0306007C)

  #define PCIEFUNCMAP_0_0_0_PCI_PCIE2FUNC_OFF                          ( 6)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE2FUNC_WID                          ( 3)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE2FUNC_MSK                          (0x000001C0)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE2FUNC_MIN                          (0)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE2FUNC_MAX                          (7) // 0x00000007
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE2FUNC_DEF                          (0x00000000)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE2FUNC_HSH                          (0x030C007C)

  #define PCIEFUNCMAP_0_0_0_PCI_PCIE3FUNC_OFF                          ( 9)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE3FUNC_WID                          ( 3)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE3FUNC_MSK                          (0x00000E00)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE3FUNC_MIN                          (0)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE3FUNC_MAX                          (7) // 0x00000007
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE3FUNC_DEF                          (0x00000000)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE3FUNC_HSH                          (0x0312007C)

  #define PCIEFUNCMAP_0_0_0_PCI_PCIE4FUNC_OFF                          (12)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE4FUNC_WID                          ( 3)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE4FUNC_MSK                          (0x00007000)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE4FUNC_MIN                          (0)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE4FUNC_MAX                          (7) // 0x00000007
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE4FUNC_DEF                          (0x00000000)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE4FUNC_HSH                          (0x0318007C)

  #define PCIEFUNCMAP_0_0_0_PCI_PCIE5FUNC_OFF                          (15)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE5FUNC_WID                          ( 3)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE5FUNC_MSK                          (0x00038000)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE5FUNC_MIN                          (0)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE5FUNC_MAX                          (7) // 0x00000007
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE5FUNC_DEF                          (0x00000000)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE5FUNC_HSH                          (0x031E007C)

  #define PCIEFUNCMAP_0_0_0_PCI_PCIE6FUNC_OFF                          (18)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE6FUNC_WID                          ( 3)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE6FUNC_MSK                          (0x001C0000)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE6FUNC_MIN                          (0)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE6FUNC_MAX                          (7) // 0x00000007
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE6FUNC_DEF                          (0x00000000)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE6FUNC_HSH                          (0x0324007C)

  #define PCIEFUNCMAP_0_0_0_PCI_PCIE7FUNC_OFF                          (21)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE7FUNC_WID                          ( 3)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE7FUNC_MSK                          (0x00E00000)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE7FUNC_MIN                          (0)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE7FUNC_MAX                          (7) // 0x00000007
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE7FUNC_DEF                          (0x00000000)
  #define PCIEFUNCMAP_0_0_0_PCI_PCIE7FUNC_HSH                          (0x032A007C)

#define PAM0_0_0_0_PCI_REG                                             (0x00000080)

  #define PAM0_0_0_0_PCI_LOCK_OFF                                      ( 0)
  #define PAM0_0_0_0_PCI_LOCK_WID                                      ( 1)
  #define PAM0_0_0_0_PCI_LOCK_MSK                                      (0x00000001)
  #define PAM0_0_0_0_PCI_LOCK_MIN                                      (0)
  #define PAM0_0_0_0_PCI_LOCK_MAX                                      (1) // 0x00000001
  #define PAM0_0_0_0_PCI_LOCK_DEF                                      (0x00000000)
  #define PAM0_0_0_0_PCI_LOCK_HSH                                      (0x01000080)

  #define PAM0_0_0_0_PCI_HIENABLE_OFF                                  ( 4)
  #define PAM0_0_0_0_PCI_HIENABLE_WID                                  ( 2)
  #define PAM0_0_0_0_PCI_HIENABLE_MSK                                  (0x00000030)
  #define PAM0_0_0_0_PCI_HIENABLE_MIN                                  (0)
  #define PAM0_0_0_0_PCI_HIENABLE_MAX                                  (3) // 0x00000003
  #define PAM0_0_0_0_PCI_HIENABLE_DEF                                  (0x00000000)
  #define PAM0_0_0_0_PCI_HIENABLE_HSH                                  (0x02080080)

#define PAM1_0_0_0_PCI_REG                                             (0x00000081)

  #define PAM1_0_0_0_PCI_LOENABLE_OFF                                  ( 0)
  #define PAM1_0_0_0_PCI_LOENABLE_WID                                  ( 2)
  #define PAM1_0_0_0_PCI_LOENABLE_MSK                                  (0x00000003)
  #define PAM1_0_0_0_PCI_LOENABLE_MIN                                  (0)
  #define PAM1_0_0_0_PCI_LOENABLE_MAX                                  (3) // 0x00000003
  #define PAM1_0_0_0_PCI_LOENABLE_DEF                                  (0x00000000)
  #define PAM1_0_0_0_PCI_LOENABLE_HSH                                  (0x02000081)

  #define PAM1_0_0_0_PCI_HIENABLE_OFF                                  ( 4)
  #define PAM1_0_0_0_PCI_HIENABLE_WID                                  ( 2)
  #define PAM1_0_0_0_PCI_HIENABLE_MSK                                  (0x00000030)
  #define PAM1_0_0_0_PCI_HIENABLE_MIN                                  (0)
  #define PAM1_0_0_0_PCI_HIENABLE_MAX                                  (3) // 0x00000003
  #define PAM1_0_0_0_PCI_HIENABLE_DEF                                  (0x00000000)
  #define PAM1_0_0_0_PCI_HIENABLE_HSH                                  (0x02080081)

#define PAM2_0_0_0_PCI_REG                                             (0x00000082)
//Duplicate of PAM1_0_0_0_PCI_REG

#define PAM3_0_0_0_PCI_REG                                             (0x00000083)
//Duplicate of PAM1_0_0_0_PCI_REG

#define PAM4_0_0_0_PCI_REG                                             (0x00000084)
//Duplicate of PAM1_0_0_0_PCI_REG

#define PAM5_0_0_0_PCI_REG                                             (0x00000085)
//Duplicate of PAM1_0_0_0_PCI_REG

#define PAM6_0_0_0_PCI_REG                                             (0x00000086)
//Duplicate of PAM1_0_0_0_PCI_REG

#define LAC_0_0_0_PCI_REG                                              (0x00000087)

  #define LAC_0_0_0_PCI_MDAP10_OFF                                     ( 0)
  #define LAC_0_0_0_PCI_MDAP10_WID                                     ( 1)
  #define LAC_0_0_0_PCI_MDAP10_MSK                                     (0x00000001)
  #define LAC_0_0_0_PCI_MDAP10_MIN                                     (0)
  #define LAC_0_0_0_PCI_MDAP10_MAX                                     (1) // 0x00000001
  #define LAC_0_0_0_PCI_MDAP10_DEF                                     (0x00000000)
  #define LAC_0_0_0_PCI_MDAP10_HSH                                     (0x01000087)

  #define LAC_0_0_0_PCI_MDAP11_OFF                                     ( 1)
  #define LAC_0_0_0_PCI_MDAP11_WID                                     ( 1)
  #define LAC_0_0_0_PCI_MDAP11_MSK                                     (0x00000002)
  #define LAC_0_0_0_PCI_MDAP11_MIN                                     (0)
  #define LAC_0_0_0_PCI_MDAP11_MAX                                     (1) // 0x00000001
  #define LAC_0_0_0_PCI_MDAP11_DEF                                     (0x00000000)
  #define LAC_0_0_0_PCI_MDAP11_HSH                                     (0x01020087)

  #define LAC_0_0_0_PCI_MDAP12_OFF                                     ( 2)
  #define LAC_0_0_0_PCI_MDAP12_WID                                     ( 1)
  #define LAC_0_0_0_PCI_MDAP12_MSK                                     (0x00000004)
  #define LAC_0_0_0_PCI_MDAP12_MIN                                     (0)
  #define LAC_0_0_0_PCI_MDAP12_MAX                                     (1) // 0x00000001
  #define LAC_0_0_0_PCI_MDAP12_DEF                                     (0x00000000)
  #define LAC_0_0_0_PCI_MDAP12_HSH                                     (0x01040087)

  #define LAC_0_0_0_PCI_MDAP60_OFF                                     ( 3)
  #define LAC_0_0_0_PCI_MDAP60_WID                                     ( 1)
  #define LAC_0_0_0_PCI_MDAP60_MSK                                     (0x00000008)
  #define LAC_0_0_0_PCI_MDAP60_MIN                                     (0)
  #define LAC_0_0_0_PCI_MDAP60_MAX                                     (1) // 0x00000001
  #define LAC_0_0_0_PCI_MDAP60_DEF                                     (0x00000000)
  #define LAC_0_0_0_PCI_MDAP60_HSH                                     (0x01060087)

  #define LAC_0_0_0_PCI_MDAPCIe_OFF                                    ( 4)
  #define LAC_0_0_0_PCI_MDAPCIe_WID                                    ( 1)
  #define LAC_0_0_0_PCI_MDAPCIe_MSK                                    (0x00000010)
  #define LAC_0_0_0_PCI_MDAPCIe_MIN                                    (0)
  #define LAC_0_0_0_PCI_MDAPCIe_MAX                                    (1) // 0x00000001
  #define LAC_0_0_0_PCI_MDAPCIe_DEF                                    (0x00000001)
  #define LAC_0_0_0_PCI_MDAPCIe_HSH                                    (0x01080087)

  #define LAC_0_0_0_PCI_HEN_OFF                                        ( 7)
  #define LAC_0_0_0_PCI_HEN_WID                                        ( 1)
  #define LAC_0_0_0_PCI_HEN_MSK                                        (0x00000080)
  #define LAC_0_0_0_PCI_HEN_MIN                                        (0)
  #define LAC_0_0_0_PCI_HEN_MAX                                        (1) // 0x00000001
  #define LAC_0_0_0_PCI_HEN_DEF                                        (0x00000000)
  #define LAC_0_0_0_PCI_HEN_HSH                                        (0x010E0087)

#define TOM_0_0_0_PCI_REG                                              (0x000000A0)

  #define TOM_0_0_0_PCI_LOCK_OFF                                       ( 0)
  #define TOM_0_0_0_PCI_LOCK_WID                                       ( 1)
  #define TOM_0_0_0_PCI_LOCK_MSK                                       (0x00000001)
  #define TOM_0_0_0_PCI_LOCK_MIN                                       (0)
  #define TOM_0_0_0_PCI_LOCK_MAX                                       (1) // 0x00000001
  #define TOM_0_0_0_PCI_LOCK_DEF                                       (0x00000000)
  #define TOM_0_0_0_PCI_LOCK_HSH                                       (0x410000A0)

  #define TOM_0_0_0_PCI_TOM_OFF                                        (20)
  #define TOM_0_0_0_PCI_TOM_WID                                        (19)
  #define TOM_0_0_0_PCI_TOM_MSK                                        (0x0000007FFFF00000ULL)
  #define TOM_0_0_0_PCI_TOM_MIN                                        (0)
  #define TOM_0_0_0_PCI_TOM_MAX                                        (524287) // 0x0007FFFF
  #define TOM_0_0_0_PCI_TOM_DEF                                        (0x0007FFFF)
  #define TOM_0_0_0_PCI_TOM_HSH                                        (0x532800A0)

#define TOUUD_0_0_0_PCI_REG                                            (0x000000A8)

  #define TOUUD_0_0_0_PCI_LOCK_OFF                                     ( 0)
  #define TOUUD_0_0_0_PCI_LOCK_WID                                     ( 1)
  #define TOUUD_0_0_0_PCI_LOCK_MSK                                     (0x00000001)
  #define TOUUD_0_0_0_PCI_LOCK_MIN                                     (0)
  #define TOUUD_0_0_0_PCI_LOCK_MAX                                     (1) // 0x00000001
  #define TOUUD_0_0_0_PCI_LOCK_DEF                                     (0x00000000)
  #define TOUUD_0_0_0_PCI_LOCK_HSH                                     (0x410000A8)

  #define TOUUD_0_0_0_PCI_TOUUD_OFF                                    (20)
  #define TOUUD_0_0_0_PCI_TOUUD_WID                                    (19)
  #define TOUUD_0_0_0_PCI_TOUUD_MSK                                    (0x0000007FFFF00000ULL)
  #define TOUUD_0_0_0_PCI_TOUUD_MIN                                    (0)
  #define TOUUD_0_0_0_PCI_TOUUD_MAX                                    (524287) // 0x0007FFFF
  #define TOUUD_0_0_0_PCI_TOUUD_DEF                                    (0x00000000)
  #define TOUUD_0_0_0_PCI_TOUUD_HSH                                    (0x532800A8)

#define BDSM_0_0_0_PCI_REG                                             (0x000000B0)

  #define BDSM_0_0_0_PCI_LOCK_OFF                                      ( 0)
  #define BDSM_0_0_0_PCI_LOCK_WID                                      ( 1)
  #define BDSM_0_0_0_PCI_LOCK_MSK                                      (0x00000001)
  #define BDSM_0_0_0_PCI_LOCK_MIN                                      (0)
  #define BDSM_0_0_0_PCI_LOCK_MAX                                      (1) // 0x00000001
  #define BDSM_0_0_0_PCI_LOCK_DEF                                      (0x00000000)
  #define BDSM_0_0_0_PCI_LOCK_HSH                                      (0x010000B0)

  #define BDSM_0_0_0_PCI_BDSM_OFF                                      (20)
  #define BDSM_0_0_0_PCI_BDSM_WID                                      (12)
  #define BDSM_0_0_0_PCI_BDSM_MSK                                      (0xFFF00000)
  #define BDSM_0_0_0_PCI_BDSM_MIN                                      (0)
  #define BDSM_0_0_0_PCI_BDSM_MAX                                      (4095) // 0x00000FFF
  #define BDSM_0_0_0_PCI_BDSM_DEF                                      (0x00000000)
  #define BDSM_0_0_0_PCI_BDSM_HSH                                      (0x0C2800B0)

#define BGSM_0_0_0_PCI_REG                                             (0x000000B4)

  #define BGSM_0_0_0_PCI_LOCK_OFF                                      ( 0)
  #define BGSM_0_0_0_PCI_LOCK_WID                                      ( 1)
  #define BGSM_0_0_0_PCI_LOCK_MSK                                      (0x00000001)
  #define BGSM_0_0_0_PCI_LOCK_MIN                                      (0)
  #define BGSM_0_0_0_PCI_LOCK_MAX                                      (1) // 0x00000001
  #define BGSM_0_0_0_PCI_LOCK_DEF                                      (0x00000000)
  #define BGSM_0_0_0_PCI_LOCK_HSH                                      (0x010000B4)

  #define BGSM_0_0_0_PCI_BGSM_OFF                                      (20)
  #define BGSM_0_0_0_PCI_BGSM_WID                                      (12)
  #define BGSM_0_0_0_PCI_BGSM_MSK                                      (0xFFF00000)
  #define BGSM_0_0_0_PCI_BGSM_MIN                                      (0)
  #define BGSM_0_0_0_PCI_BGSM_MAX                                      (4095) // 0x00000FFF
  #define BGSM_0_0_0_PCI_BGSM_DEF                                      (0x00000001)
  #define BGSM_0_0_0_PCI_BGSM_HSH                                      (0x0C2800B4)

#define TSEGMB_0_0_0_PCI_REG                                           (0x000000B8)

  #define TSEGMB_0_0_0_PCI_LOCK_OFF                                    ( 0)
  #define TSEGMB_0_0_0_PCI_LOCK_WID                                    ( 1)
  #define TSEGMB_0_0_0_PCI_LOCK_MSK                                    (0x00000001)
  #define TSEGMB_0_0_0_PCI_LOCK_MIN                                    (0)
  #define TSEGMB_0_0_0_PCI_LOCK_MAX                                    (1) // 0x00000001
  #define TSEGMB_0_0_0_PCI_LOCK_DEF                                    (0x00000000)
  #define TSEGMB_0_0_0_PCI_LOCK_HSH                                    (0x010000B8)

  #define TSEGMB_0_0_0_PCI_TSEGMB_OFF                                  (20)
  #define TSEGMB_0_0_0_PCI_TSEGMB_WID                                  (12)
  #define TSEGMB_0_0_0_PCI_TSEGMB_MSK                                  (0xFFF00000)
  #define TSEGMB_0_0_0_PCI_TSEGMB_MIN                                  (0)
  #define TSEGMB_0_0_0_PCI_TSEGMB_MAX                                  (4095) // 0x00000FFF
  #define TSEGMB_0_0_0_PCI_TSEGMB_DEF                                  (0x00000000)
  #define TSEGMB_0_0_0_PCI_TSEGMB_HSH                                  (0x0C2800B8)

#define TOLUD_0_0_0_PCI_REG                                            (0x000000BC)

  #define TOLUD_0_0_0_PCI_LOCK_OFF                                     ( 0)
  #define TOLUD_0_0_0_PCI_LOCK_WID                                     ( 1)
  #define TOLUD_0_0_0_PCI_LOCK_MSK                                     (0x00000001)
  #define TOLUD_0_0_0_PCI_LOCK_MIN                                     (0)
  #define TOLUD_0_0_0_PCI_LOCK_MAX                                     (1) // 0x00000001
  #define TOLUD_0_0_0_PCI_LOCK_DEF                                     (0x00000000)
  #define TOLUD_0_0_0_PCI_LOCK_HSH                                     (0x010000BC)

  #define TOLUD_0_0_0_PCI_TOLUD_OFF                                    (20)
  #define TOLUD_0_0_0_PCI_TOLUD_WID                                    (12)
  #define TOLUD_0_0_0_PCI_TOLUD_MSK                                    (0xFFF00000)
  #define TOLUD_0_0_0_PCI_TOLUD_MIN                                    (0)
  #define TOLUD_0_0_0_PCI_TOLUD_MAX                                    (4095) // 0x00000FFF
  #define TOLUD_0_0_0_PCI_TOLUD_DEF                                    (0x00000001)
  #define TOLUD_0_0_0_PCI_TOLUD_HSH                                    (0x0C2800BC)

#define DIDOVR_0_0_0_PCI_REG                                           (0x000000C0)

  #define DIDOVR_0_0_0_PCI_DID2OVR_OFF                                 ( 0)
  #define DIDOVR_0_0_0_PCI_DID2OVR_WID                                 ( 8)
  #define DIDOVR_0_0_0_PCI_DID2OVR_MSK                                 (0x000000FF)
  #define DIDOVR_0_0_0_PCI_DID2OVR_MIN                                 (0)
  #define DIDOVR_0_0_0_PCI_DID2OVR_MAX                                 (255) // 0x000000FF
  #define DIDOVR_0_0_0_PCI_DID2OVR_DEF                                 (0x00000000)
  #define DIDOVR_0_0_0_PCI_DID2OVR_HSH                                 (0x080000C0)

  #define DIDOVR_0_0_0_PCI_OE2_OFF                                     ( 8)
  #define DIDOVR_0_0_0_PCI_OE2_WID                                     ( 1)
  #define DIDOVR_0_0_0_PCI_OE2_MSK                                     (0x00000100)
  #define DIDOVR_0_0_0_PCI_OE2_MIN                                     (0)
  #define DIDOVR_0_0_0_PCI_OE2_MAX                                     (1) // 0x00000001
  #define DIDOVR_0_0_0_PCI_OE2_DEF                                     (0x00000000)
  #define DIDOVR_0_0_0_PCI_OE2_HSH                                     (0x011000C0)

  #define DIDOVR_0_0_0_PCI_DID0OVR_OFF                                 (16)
  #define DIDOVR_0_0_0_PCI_DID0OVR_WID                                 ( 8)
  #define DIDOVR_0_0_0_PCI_DID0OVR_MSK                                 (0x00FF0000)
  #define DIDOVR_0_0_0_PCI_DID0OVR_MIN                                 (0)
  #define DIDOVR_0_0_0_PCI_DID0OVR_MAX                                 (255) // 0x000000FF
  #define DIDOVR_0_0_0_PCI_DID0OVR_DEF                                 (0x00000000)
  #define DIDOVR_0_0_0_PCI_DID0OVR_HSH                                 (0x082000C0)

  #define DIDOVR_0_0_0_PCI_OE0_OFF                                     (24)
  #define DIDOVR_0_0_0_PCI_OE0_WID                                     ( 1)
  #define DIDOVR_0_0_0_PCI_OE0_MSK                                     (0x01000000)
  #define DIDOVR_0_0_0_PCI_OE0_MIN                                     (0)
  #define DIDOVR_0_0_0_PCI_OE0_MAX                                     (1) // 0x00000001
  #define DIDOVR_0_0_0_PCI_OE0_DEF                                     (0x00000000)
  #define DIDOVR_0_0_0_PCI_OE0_HSH                                     (0x013000C0)

#define ERRSTS_0_0_0_PCI_REG                                           (0x000000C8)

  #define ERRSTS_0_0_0_PCI_DSERR_OFF                                   ( 0)
  #define ERRSTS_0_0_0_PCI_DSERR_WID                                   ( 1)
  #define ERRSTS_0_0_0_PCI_DSERR_MSK                                   (0x00000001)
  #define ERRSTS_0_0_0_PCI_DSERR_MIN                                   (0)
  #define ERRSTS_0_0_0_PCI_DSERR_MAX                                   (1) // 0x00000001
  #define ERRSTS_0_0_0_PCI_DSERR_DEF                                   (0x00000000)
  #define ERRSTS_0_0_0_PCI_DSERR_HSH                                   (0x010000C8)

  #define ERRSTS_0_0_0_PCI_DMERR_OFF                                   ( 1)
  #define ERRSTS_0_0_0_PCI_DMERR_WID                                   ( 1)
  #define ERRSTS_0_0_0_PCI_DMERR_MSK                                   (0x00000002)
  #define ERRSTS_0_0_0_PCI_DMERR_MIN                                   (0)
  #define ERRSTS_0_0_0_PCI_DMERR_MAX                                   (1) // 0x00000001
  #define ERRSTS_0_0_0_PCI_DMERR_DEF                                   (0x00000000)
  #define ERRSTS_0_0_0_PCI_DMERR_HSH                                   (0x010200C8)

  #define ERRSTS_0_0_0_PCI_UNSUPPORTED_ATOMIC_OFF                      ( 6)
  #define ERRSTS_0_0_0_PCI_UNSUPPORTED_ATOMIC_WID                      ( 1)
  #define ERRSTS_0_0_0_PCI_UNSUPPORTED_ATOMIC_MSK                      (0x00000040)
  #define ERRSTS_0_0_0_PCI_UNSUPPORTED_ATOMIC_MIN                      (0)
  #define ERRSTS_0_0_0_PCI_UNSUPPORTED_ATOMIC_MAX                      (1) // 0x00000001
  #define ERRSTS_0_0_0_PCI_UNSUPPORTED_ATOMIC_DEF                      (0x00000000)
  #define ERRSTS_0_0_0_PCI_UNSUPPORTED_ATOMIC_HSH                      (0x010C00C8)

#define ERRCMD_0_0_0_PCI_REG                                           (0x000000CA)
//Duplicate of ERRSTS_0_0_0_PCI_REG

#define SMICMD_0_0_0_PCI_REG                                           (0x000000CC)

  #define SMICMD_0_0_0_PCI_DSESMI_OFF                                  ( 0)
  #define SMICMD_0_0_0_PCI_DSESMI_WID                                  ( 1)
  #define SMICMD_0_0_0_PCI_DSESMI_MSK                                  (0x00000001)
  #define SMICMD_0_0_0_PCI_DSESMI_MIN                                  (0)
  #define SMICMD_0_0_0_PCI_DSESMI_MAX                                  (1) // 0x00000001
  #define SMICMD_0_0_0_PCI_DSESMI_DEF                                  (0x00000000)
  #define SMICMD_0_0_0_PCI_DSESMI_HSH                                  (0x010000CC)

  #define SMICMD_0_0_0_PCI_DMESMI_OFF                                  ( 1)
  #define SMICMD_0_0_0_PCI_DMESMI_WID                                  ( 1)
  #define SMICMD_0_0_0_PCI_DMESMI_MSK                                  (0x00000002)
  #define SMICMD_0_0_0_PCI_DMESMI_MIN                                  (0)
  #define SMICMD_0_0_0_PCI_DMESMI_MAX                                  (1) // 0x00000001
  #define SMICMD_0_0_0_PCI_DMESMI_DEF                                  (0x00000000)
  #define SMICMD_0_0_0_PCI_DMESMI_HSH                                  (0x010200CC)

  #define SMICMD_0_0_0_PCI_UNSUPPORTED_ATOMIC_OFF                      ( 6)
  #define SMICMD_0_0_0_PCI_UNSUPPORTED_ATOMIC_WID                      ( 1)
  #define SMICMD_0_0_0_PCI_UNSUPPORTED_ATOMIC_MSK                      (0x00000040)
  #define SMICMD_0_0_0_PCI_UNSUPPORTED_ATOMIC_MIN                      (0)
  #define SMICMD_0_0_0_PCI_UNSUPPORTED_ATOMIC_MAX                      (1) // 0x00000001
  #define SMICMD_0_0_0_PCI_UNSUPPORTED_ATOMIC_DEF                      (0x00000000)
  #define SMICMD_0_0_0_PCI_UNSUPPORTED_ATOMIC_HSH                      (0x010C00CC)

#define SCICMD_0_0_0_PCI_REG                                           (0x000000CE)

  #define SCICMD_0_0_0_PCI_DSESCI_OFF                                  ( 0)
  #define SCICMD_0_0_0_PCI_DSESCI_WID                                  ( 1)
  #define SCICMD_0_0_0_PCI_DSESCI_MSK                                  (0x00000001)
  #define SCICMD_0_0_0_PCI_DSESCI_MIN                                  (0)
  #define SCICMD_0_0_0_PCI_DSESCI_MAX                                  (1) // 0x00000001
  #define SCICMD_0_0_0_PCI_DSESCI_DEF                                  (0x00000000)
  #define SCICMD_0_0_0_PCI_DSESCI_HSH                                  (0x010000CE)

  #define SCICMD_0_0_0_PCI_DMESCI_OFF                                  ( 1)
  #define SCICMD_0_0_0_PCI_DMESCI_WID                                  ( 1)
  #define SCICMD_0_0_0_PCI_DMESCI_MSK                                  (0x00000002)
  #define SCICMD_0_0_0_PCI_DMESCI_MIN                                  (0)
  #define SCICMD_0_0_0_PCI_DMESCI_MAX                                  (1) // 0x00000001
  #define SCICMD_0_0_0_PCI_DMESCI_DEF                                  (0x00000000)
  #define SCICMD_0_0_0_PCI_DMESCI_HSH                                  (0x010200CE)

  #define SCICMD_0_0_0_PCI_UNSUPPORTED_ATOMIC_OFF                      ( 6)
  #define SCICMD_0_0_0_PCI_UNSUPPORTED_ATOMIC_WID                      ( 1)
  #define SCICMD_0_0_0_PCI_UNSUPPORTED_ATOMIC_MSK                      (0x00000040)
  #define SCICMD_0_0_0_PCI_UNSUPPORTED_ATOMIC_MIN                      (0)
  #define SCICMD_0_0_0_PCI_UNSUPPORTED_ATOMIC_MAX                      (1) // 0x00000001
  #define SCICMD_0_0_0_PCI_UNSUPPORTED_ATOMIC_DEF                      (0x00000000)
  #define SCICMD_0_0_0_PCI_UNSUPPORTED_ATOMIC_HSH                      (0x010C00CE)

#define SKPD_0_0_0_PCI_REG                                             (0x000000DC)

  #define SKPD_0_0_0_PCI_SKPD_OFF                                      ( 0)
  #define SKPD_0_0_0_PCI_SKPD_WID                                      (32)
  #define SKPD_0_0_0_PCI_SKPD_MSK                                      (0xFFFFFFFF)
  #define SKPD_0_0_0_PCI_SKPD_MIN                                      (0)
  #define SKPD_0_0_0_PCI_SKPD_MAX                                      (4294967295) // 0xFFFFFFFF
  #define SKPD_0_0_0_PCI_SKPD_DEF                                      (0x00000000)
  #define SKPD_0_0_0_PCI_SKPD_HSH                                      (0x200000DC)

#define CAPID0_0_0_0_PCI_REG                                           (0x000000E0)

  #define CAPID0_0_0_0_PCI_CAP_ID_OFF                                  ( 0)
  #define CAPID0_0_0_0_PCI_CAP_ID_WID                                  ( 8)
  #define CAPID0_0_0_0_PCI_CAP_ID_MSK                                  (0x000000FF)
  #define CAPID0_0_0_0_PCI_CAP_ID_MIN                                  (0)
  #define CAPID0_0_0_0_PCI_CAP_ID_MAX                                  (255) // 0x000000FF
  #define CAPID0_0_0_0_PCI_CAP_ID_DEF                                  (0x00000009)
  #define CAPID0_0_0_0_PCI_CAP_ID_HSH                                  (0x080000E0)

  #define CAPID0_0_0_0_PCI_NEXT_CAP_OFF                                ( 8)
  #define CAPID0_0_0_0_PCI_NEXT_CAP_WID                                ( 8)
  #define CAPID0_0_0_0_PCI_NEXT_CAP_MSK                                (0x0000FF00)
  #define CAPID0_0_0_0_PCI_NEXT_CAP_MIN                                (0)
  #define CAPID0_0_0_0_PCI_NEXT_CAP_MAX                                (255) // 0x000000FF
  #define CAPID0_0_0_0_PCI_NEXT_CAP_DEF                                (0x00000000)
  #define CAPID0_0_0_0_PCI_NEXT_CAP_HSH                                (0x081000E0)

#define CAPCTRL0_0_0_0_PCI_REG                                         (0x000000E2)

  #define CAPCTRL0_0_0_0_PCI_CAPIDLEN_OFF                              ( 0)
  #define CAPCTRL0_0_0_0_PCI_CAPIDLEN_WID                              ( 8)
  #define CAPCTRL0_0_0_0_PCI_CAPIDLEN_MSK                              (0x000000FF)
  #define CAPCTRL0_0_0_0_PCI_CAPIDLEN_MIN                              (0)
  #define CAPCTRL0_0_0_0_PCI_CAPIDLEN_MAX                              (255) // 0x000000FF
  #define CAPCTRL0_0_0_0_PCI_CAPIDLEN_DEF                              (0x00000014)
  #define CAPCTRL0_0_0_0_PCI_CAPIDLEN_HSH                              (0x080000E2)

  #define CAPCTRL0_0_0_0_PCI_CAPID_VER_OFF                             ( 8)
  #define CAPCTRL0_0_0_0_PCI_CAPID_VER_WID                             ( 4)
  #define CAPCTRL0_0_0_0_PCI_CAPID_VER_MSK                             (0x00000F00)
  #define CAPCTRL0_0_0_0_PCI_CAPID_VER_MIN                             (0)
  #define CAPCTRL0_0_0_0_PCI_CAPID_VER_MAX                             (15) // 0x0000000F
  #define CAPCTRL0_0_0_0_PCI_CAPID_VER_DEF                             (0x00000001)
  #define CAPCTRL0_0_0_0_PCI_CAPID_VER_HSH                             (0x041000E2)

#define CAPID0_A_0_0_0_PCI_REG                                         (0x000000E4)

  #define CAPID0_A_0_0_0_PCI_SPARE_0_OFF                               ( 0)
  #define CAPID0_A_0_0_0_PCI_SPARE_0_WID                               ( 1)
  #define CAPID0_A_0_0_0_PCI_SPARE_0_MSK                               (0x00000001)
  #define CAPID0_A_0_0_0_PCI_SPARE_0_MIN                               (0)
  #define CAPID0_A_0_0_0_PCI_SPARE_0_MAX                               (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_SPARE_0_DEF                               (0x00000000)
  #define CAPID0_A_0_0_0_PCI_SPARE_0_HSH                               (0x010000E4)

  #define CAPID0_A_0_0_0_PCI_SPARE_1_OFF                               ( 1)
  #define CAPID0_A_0_0_0_PCI_SPARE_1_WID                               ( 1)
  #define CAPID0_A_0_0_0_PCI_SPARE_1_MSK                               (0x00000002)
  #define CAPID0_A_0_0_0_PCI_SPARE_1_MIN                               (0)
  #define CAPID0_A_0_0_0_PCI_SPARE_1_MAX                               (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_SPARE_1_DEF                               (0x00000000)
  #define CAPID0_A_0_0_0_PCI_SPARE_1_HSH                               (0x010200E4)

  #define CAPID0_A_0_0_0_PCI_OC_ENABLED_DSKU_OFF                       ( 2)
  #define CAPID0_A_0_0_0_PCI_OC_ENABLED_DSKU_WID                       ( 1)
  #define CAPID0_A_0_0_0_PCI_OC_ENABLED_DSKU_MSK                       (0x00000004)
  #define CAPID0_A_0_0_0_PCI_OC_ENABLED_DSKU_MIN                       (0)
  #define CAPID0_A_0_0_0_PCI_OC_ENABLED_DSKU_MAX                       (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_OC_ENABLED_DSKU_DEF                       (0x00000000)
  #define CAPID0_A_0_0_0_PCI_OC_ENABLED_DSKU_HSH                       (0x010400E4)

  #define CAPID0_A_0_0_0_PCI_DDR_OVERCLOCK_OFF                         ( 3)
  #define CAPID0_A_0_0_0_PCI_DDR_OVERCLOCK_WID                         ( 1)
  #define CAPID0_A_0_0_0_PCI_DDR_OVERCLOCK_MSK                         (0x00000008)
  #define CAPID0_A_0_0_0_PCI_DDR_OVERCLOCK_MIN                         (0)
  #define CAPID0_A_0_0_0_PCI_DDR_OVERCLOCK_MAX                         (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_DDR_OVERCLOCK_DEF                         (0x00000000)
  #define CAPID0_A_0_0_0_PCI_DDR_OVERCLOCK_HSH                         (0x010600E4)

  #define CAPID0_A_0_0_0_PCI_CRID_OFF                                  ( 4)
  #define CAPID0_A_0_0_0_PCI_CRID_WID                                  ( 4)
  #define CAPID0_A_0_0_0_PCI_CRID_MSK                                  (0x000000F0)
  #define CAPID0_A_0_0_0_PCI_CRID_MIN                                  (0)
  #define CAPID0_A_0_0_0_PCI_CRID_MAX                                  (15) // 0x0000000F
  #define CAPID0_A_0_0_0_PCI_CRID_DEF                                  (0x00000000)
  #define CAPID0_A_0_0_0_PCI_CRID_HSH                                  (0x040800E4)

  #define CAPID0_A_0_0_0_PCI_SPARE_8_OFF                               ( 8)
  #define CAPID0_A_0_0_0_PCI_SPARE_8_WID                               ( 1)
  #define CAPID0_A_0_0_0_PCI_SPARE_8_MSK                               (0x00000100)
  #define CAPID0_A_0_0_0_PCI_SPARE_8_MIN                               (0)
  #define CAPID0_A_0_0_0_PCI_SPARE_8_MAX                               (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_SPARE_8_DEF                               (0x00000000)
  #define CAPID0_A_0_0_0_PCI_SPARE_8_HSH                               (0x011000E4)

  #define CAPID0_A_0_0_0_PCI_SPARE_9_OFF                               ( 9)
  #define CAPID0_A_0_0_0_PCI_SPARE_9_WID                               ( 1)
  #define CAPID0_A_0_0_0_PCI_SPARE_9_MSK                               (0x00000200)
  #define CAPID0_A_0_0_0_PCI_SPARE_9_MIN                               (0)
  #define CAPID0_A_0_0_0_PCI_SPARE_9_MAX                               (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_SPARE_9_DEF                               (0x00000000)
  #define CAPID0_A_0_0_0_PCI_SPARE_9_HSH                               (0x011200E4)

  #define CAPID0_A_0_0_0_PCI_DID0OE_OFF                                (10)
  #define CAPID0_A_0_0_0_PCI_DID0OE_WID                                ( 1)
  #define CAPID0_A_0_0_0_PCI_DID0OE_MSK                                (0x00000400)
  #define CAPID0_A_0_0_0_PCI_DID0OE_MIN                                (0)
  #define CAPID0_A_0_0_0_PCI_DID0OE_MAX                                (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_DID0OE_DEF                                (0x00000000)
  #define CAPID0_A_0_0_0_PCI_DID0OE_HSH                                (0x011400E4)

  #define CAPID0_A_0_0_0_PCI_IGD_OFF                                   (11)
  #define CAPID0_A_0_0_0_PCI_IGD_WID                                   ( 1)
  #define CAPID0_A_0_0_0_PCI_IGD_MSK                                   (0x00000800)
  #define CAPID0_A_0_0_0_PCI_IGD_MIN                                   (0)
  #define CAPID0_A_0_0_0_PCI_IGD_MAX                                   (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_IGD_DEF                                   (0x00000000)
  #define CAPID0_A_0_0_0_PCI_IGD_HSH                                   (0x011600E4)

  #define CAPID0_A_0_0_0_PCI_PDCD_OFF                                  (12)
  #define CAPID0_A_0_0_0_PCI_PDCD_WID                                  ( 1)
  #define CAPID0_A_0_0_0_PCI_PDCD_MSK                                  (0x00001000)
  #define CAPID0_A_0_0_0_PCI_PDCD_MIN                                  (0)
  #define CAPID0_A_0_0_0_PCI_PDCD_MAX                                  (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_PDCD_DEF                                  (0x00000000)
  #define CAPID0_A_0_0_0_PCI_PDCD_HSH                                  (0x011800E4)

  #define CAPID0_A_0_0_0_PCI_X2APIC_EN_OFF                             (13)
  #define CAPID0_A_0_0_0_PCI_X2APIC_EN_WID                             ( 1)
  #define CAPID0_A_0_0_0_PCI_X2APIC_EN_MSK                             (0x00002000)
  #define CAPID0_A_0_0_0_PCI_X2APIC_EN_MIN                             (0)
  #define CAPID0_A_0_0_0_PCI_X2APIC_EN_MAX                             (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_X2APIC_EN_DEF                             (0x00000000)
  #define CAPID0_A_0_0_0_PCI_X2APIC_EN_HSH                             (0x011A00E4)

  #define CAPID0_A_0_0_0_PCI_DDPCD_OFF                                 (14)
  #define CAPID0_A_0_0_0_PCI_DDPCD_WID                                 ( 1)
  #define CAPID0_A_0_0_0_PCI_DDPCD_MSK                                 (0x00004000)
  #define CAPID0_A_0_0_0_PCI_DDPCD_MIN                                 (0)
  #define CAPID0_A_0_0_0_PCI_DDPCD_MAX                                 (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_DDPCD_DEF                                 (0x00000000)
  #define CAPID0_A_0_0_0_PCI_DDPCD_HSH                                 (0x011C00E4)

  #define CAPID0_A_0_0_0_PCI_CDD_OFF                                   (15)
  #define CAPID0_A_0_0_0_PCI_CDD_WID                                   ( 1)
  #define CAPID0_A_0_0_0_PCI_CDD_MSK                                   (0x00008000)
  #define CAPID0_A_0_0_0_PCI_CDD_MIN                                   (0)
  #define CAPID0_A_0_0_0_PCI_CDD_MAX                                   (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_CDD_DEF                                   (0x00000000)
  #define CAPID0_A_0_0_0_PCI_CDD_HSH                                   (0x011E00E4)

  #define CAPID0_A_0_0_0_PCI_FUFRD_OFF                                 (16)
  #define CAPID0_A_0_0_0_PCI_FUFRD_WID                                 ( 1)
  #define CAPID0_A_0_0_0_PCI_FUFRD_MSK                                 (0x00010000)
  #define CAPID0_A_0_0_0_PCI_FUFRD_MIN                                 (0)
  #define CAPID0_A_0_0_0_PCI_FUFRD_MAX                                 (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_FUFRD_DEF                                 (0x00000000)
  #define CAPID0_A_0_0_0_PCI_FUFRD_HSH                                 (0x012000E4)

  #define CAPID0_A_0_0_0_PCI_D1NM_OFF                                  (17)
  #define CAPID0_A_0_0_0_PCI_D1NM_WID                                  ( 1)
  #define CAPID0_A_0_0_0_PCI_D1NM_MSK                                  (0x00020000)
  #define CAPID0_A_0_0_0_PCI_D1NM_MIN                                  (0)
  #define CAPID0_A_0_0_0_PCI_D1NM_MAX                                  (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_D1NM_DEF                                  (0x00000000)
  #define CAPID0_A_0_0_0_PCI_D1NM_HSH                                  (0x012200E4)

  #define CAPID0_A_0_0_0_PCI_PEG60D_OFF                                (18)
  #define CAPID0_A_0_0_0_PCI_PEG60D_WID                                ( 1)
  #define CAPID0_A_0_0_0_PCI_PEG60D_MSK                                (0x00040000)
  #define CAPID0_A_0_0_0_PCI_PEG60D_MIN                                (0)
  #define CAPID0_A_0_0_0_PCI_PEG60D_MAX                                (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_PEG60D_DEF                                (0x00000000)
  #define CAPID0_A_0_0_0_PCI_PEG60D_HSH                                (0x012400E4)

  #define CAPID0_A_0_0_0_PCI_DDRSZ_OFF                                 (19)
  #define CAPID0_A_0_0_0_PCI_DDRSZ_WID                                 ( 2)
  #define CAPID0_A_0_0_0_PCI_DDRSZ_MSK                                 (0x00180000)
  #define CAPID0_A_0_0_0_PCI_DDRSZ_MIN                                 (0)
  #define CAPID0_A_0_0_0_PCI_DDRSZ_MAX                                 (3) // 0x00000003
  #define CAPID0_A_0_0_0_PCI_DDRSZ_DEF                                 (0x00000000)
  #define CAPID0_A_0_0_0_PCI_DDRSZ_HSH                                 (0x022600E4)

  #define CAPID0_A_0_0_0_PCI_PEGG2DIS_OFF                              (21)
  #define CAPID0_A_0_0_0_PCI_PEGG2DIS_WID                              ( 1)
  #define CAPID0_A_0_0_0_PCI_PEGG2DIS_MSK                              (0x00200000)
  #define CAPID0_A_0_0_0_PCI_PEGG2DIS_MIN                              (0)
  #define CAPID0_A_0_0_0_PCI_PEGG2DIS_MAX                              (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_PEGG2DIS_DEF                              (0x00000000)
  #define CAPID0_A_0_0_0_PCI_PEGG2DIS_HSH                              (0x012A00E4)

  #define CAPID0_A_0_0_0_PCI_DMIG2DIS_OFF                              (22)
  #define CAPID0_A_0_0_0_PCI_DMIG2DIS_WID                              ( 1)
  #define CAPID0_A_0_0_0_PCI_DMIG2DIS_MSK                              (0x00400000)
  #define CAPID0_A_0_0_0_PCI_DMIG2DIS_MIN                              (0)
  #define CAPID0_A_0_0_0_PCI_DMIG2DIS_MAX                              (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_DMIG2DIS_DEF                              (0x00000000)
  #define CAPID0_A_0_0_0_PCI_DMIG2DIS_HSH                              (0x012C00E4)

  #define CAPID0_A_0_0_0_PCI_VTDD_OFF                                  (23)
  #define CAPID0_A_0_0_0_PCI_VTDD_WID                                  ( 1)
  #define CAPID0_A_0_0_0_PCI_VTDD_MSK                                  (0x00800000)
  #define CAPID0_A_0_0_0_PCI_VTDD_MIN                                  (0)
  #define CAPID0_A_0_0_0_PCI_VTDD_MAX                                  (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_VTDD_DEF                                  (0x00000000)
  #define CAPID0_A_0_0_0_PCI_VTDD_HSH                                  (0x012E00E4)

  #define CAPID0_A_0_0_0_PCI_FDEE_OFF                                  (24)
  #define CAPID0_A_0_0_0_PCI_FDEE_WID                                  ( 1)
  #define CAPID0_A_0_0_0_PCI_FDEE_MSK                                  (0x01000000)
  #define CAPID0_A_0_0_0_PCI_FDEE_MIN                                  (0)
  #define CAPID0_A_0_0_0_PCI_FDEE_MAX                                  (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_FDEE_DEF                                  (0x00000000)
  #define CAPID0_A_0_0_0_PCI_FDEE_HSH                                  (0x013000E4)

  #define CAPID0_A_0_0_0_PCI_ECCDIS_OFF                                (25)
  #define CAPID0_A_0_0_0_PCI_ECCDIS_WID                                ( 1)
  #define CAPID0_A_0_0_0_PCI_ECCDIS_MSK                                (0x02000000)
  #define CAPID0_A_0_0_0_PCI_ECCDIS_MIN                                (0)
  #define CAPID0_A_0_0_0_PCI_ECCDIS_MAX                                (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_ECCDIS_DEF                                (0x00000000)
  #define CAPID0_A_0_0_0_PCI_ECCDIS_HSH                                (0x013200E4)

  #define CAPID0_A_0_0_0_PCI_DW_OFF                                    (26)
  #define CAPID0_A_0_0_0_PCI_DW_WID                                    ( 1)
  #define CAPID0_A_0_0_0_PCI_DW_MSK                                    (0x04000000)
  #define CAPID0_A_0_0_0_PCI_DW_MIN                                    (0)
  #define CAPID0_A_0_0_0_PCI_DW_MAX                                    (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_DW_DEF                                    (0x00000000)
  #define CAPID0_A_0_0_0_PCI_DW_HSH                                    (0x013400E4)

  #define CAPID0_A_0_0_0_PCI_PELWUD_OFF                                (27)
  #define CAPID0_A_0_0_0_PCI_PELWUD_WID                                ( 1)
  #define CAPID0_A_0_0_0_PCI_PELWUD_MSK                                (0x08000000)
  #define CAPID0_A_0_0_0_PCI_PELWUD_MIN                                (0)
  #define CAPID0_A_0_0_0_PCI_PELWUD_MAX                                (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_PELWUD_DEF                                (0x00000000)
  #define CAPID0_A_0_0_0_PCI_PELWUD_HSH                                (0x013600E4)

  #define CAPID0_A_0_0_0_PCI_PEG10D_OFF                                (28)
  #define CAPID0_A_0_0_0_PCI_PEG10D_WID                                ( 1)
  #define CAPID0_A_0_0_0_PCI_PEG10D_MSK                                (0x10000000)
  #define CAPID0_A_0_0_0_PCI_PEG10D_MIN                                (0)
  #define CAPID0_A_0_0_0_PCI_PEG10D_MAX                                (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_PEG10D_DEF                                (0x00000000)
  #define CAPID0_A_0_0_0_PCI_PEG10D_HSH                                (0x013800E4)

  #define CAPID0_A_0_0_0_PCI_PEG11D_OFF                                (29)
  #define CAPID0_A_0_0_0_PCI_PEG11D_WID                                ( 1)
  #define CAPID0_A_0_0_0_PCI_PEG11D_MSK                                (0x20000000)
  #define CAPID0_A_0_0_0_PCI_PEG11D_MIN                                (0)
  #define CAPID0_A_0_0_0_PCI_PEG11D_MAX                                (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_PEG11D_DEF                                (0x00000000)
  #define CAPID0_A_0_0_0_PCI_PEG11D_HSH                                (0x013A00E4)

  #define CAPID0_A_0_0_0_PCI_PEG12D_OFF                                (30)
  #define CAPID0_A_0_0_0_PCI_PEG12D_WID                                ( 1)
  #define CAPID0_A_0_0_0_PCI_PEG12D_MSK                                (0x40000000)
  #define CAPID0_A_0_0_0_PCI_PEG12D_MIN                                (0)
  #define CAPID0_A_0_0_0_PCI_PEG12D_MAX                                (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_PEG12D_DEF                                (0x00000000)
  #define CAPID0_A_0_0_0_PCI_PEG12D_HSH                                (0x013C00E4)

  #define CAPID0_A_0_0_0_PCI_NVME_DIS_OFF                              (31)
  #define CAPID0_A_0_0_0_PCI_NVME_DIS_WID                              ( 1)
  #define CAPID0_A_0_0_0_PCI_NVME_DIS_MSK                              (0x80000000)
  #define CAPID0_A_0_0_0_PCI_NVME_DIS_MIN                              (0)
  #define CAPID0_A_0_0_0_PCI_NVME_DIS_MAX                              (1) // 0x00000001
  #define CAPID0_A_0_0_0_PCI_NVME_DIS_DEF                              (0x00000001)
  #define CAPID0_A_0_0_0_PCI_NVME_DIS_HSH                              (0x013E00E4)

#define CAPID0_B_0_0_0_PCI_REG                                         (0x000000E8)

  #define CAPID0_B_0_0_0_PCI_SPEGFX1_OFF                               ( 0)
  #define CAPID0_B_0_0_0_PCI_SPEGFX1_WID                               ( 1)
  #define CAPID0_B_0_0_0_PCI_SPEGFX1_MSK                               (0x00000001)
  #define CAPID0_B_0_0_0_PCI_SPEGFX1_MIN                               (0)
  #define CAPID0_B_0_0_0_PCI_SPEGFX1_MAX                               (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_SPEGFX1_DEF                               (0x00000000)
  #define CAPID0_B_0_0_0_PCI_SPEGFX1_HSH                               (0x010000E8)

  #define CAPID0_B_0_0_0_PCI_DPEGFX1_OFF                               ( 1)
  #define CAPID0_B_0_0_0_PCI_DPEGFX1_WID                               ( 1)
  #define CAPID0_B_0_0_0_PCI_DPEGFX1_MSK                               (0x00000002)
  #define CAPID0_B_0_0_0_PCI_DPEGFX1_MIN                               (0)
  #define CAPID0_B_0_0_0_PCI_DPEGFX1_MAX                               (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_DPEGFX1_DEF                               (0x00000000)
  #define CAPID0_B_0_0_0_PCI_DPEGFX1_HSH                               (0x010200E8)

  #define CAPID0_B_0_0_0_PCI_VMD_DIS_OFF                               ( 2)
  #define CAPID0_B_0_0_0_PCI_VMD_DIS_WID                               ( 1)
  #define CAPID0_B_0_0_0_PCI_VMD_DIS_MSK                               (0x00000004)
  #define CAPID0_B_0_0_0_PCI_VMD_DIS_MIN                               (0)
  #define CAPID0_B_0_0_0_PCI_VMD_DIS_MAX                               (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_VMD_DIS_DEF                               (0x00000000)
  #define CAPID0_B_0_0_0_PCI_VMD_DIS_HSH                               (0x010400E8)

  #define CAPID0_B_0_0_0_PCI_SH_OPI_EN_OFF                             ( 3)
  #define CAPID0_B_0_0_0_PCI_SH_OPI_EN_WID                             ( 1)
  #define CAPID0_B_0_0_0_PCI_SH_OPI_EN_MSK                             (0x00000008)
  #define CAPID0_B_0_0_0_PCI_SH_OPI_EN_MIN                             (0)
  #define CAPID0_B_0_0_0_PCI_SH_OPI_EN_MAX                             (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_SH_OPI_EN_DEF                             (0x00000000)
  #define CAPID0_B_0_0_0_PCI_SH_OPI_EN_HSH                             (0x010600E8)

  #define CAPID0_B_0_0_0_PCI_SPARE_4_OFF                               ( 4)
  #define CAPID0_B_0_0_0_PCI_SPARE_4_WID                               ( 1)
  #define CAPID0_B_0_0_0_PCI_SPARE_4_MSK                               (0x00000010)
  #define CAPID0_B_0_0_0_PCI_SPARE_4_MIN                               (0)
  #define CAPID0_B_0_0_0_PCI_SPARE_4_MAX                               (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_SPARE_4_DEF                               (0x00000000)
  #define CAPID0_B_0_0_0_PCI_SPARE_4_HSH                               (0x010800E8)

  #define CAPID0_B_0_0_0_PCI_SPARE_5_OFF                               ( 5)
  #define CAPID0_B_0_0_0_PCI_SPARE_5_WID                               ( 1)
  #define CAPID0_B_0_0_0_PCI_SPARE_5_MSK                               (0x00000020)
  #define CAPID0_B_0_0_0_PCI_SPARE_5_MIN                               (0)
  #define CAPID0_B_0_0_0_PCI_SPARE_5_MAX                               (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_SPARE_5_DEF                               (0x00000000)
  #define CAPID0_B_0_0_0_PCI_SPARE_5_HSH                               (0x010A00E8)

  #define CAPID0_B_0_0_0_PCI_SPARE_6_OFF                               ( 6)
  #define CAPID0_B_0_0_0_PCI_SPARE_6_WID                               ( 1)
  #define CAPID0_B_0_0_0_PCI_SPARE_6_MSK                               (0x00000040)
  #define CAPID0_B_0_0_0_PCI_SPARE_6_MIN                               (0)
  #define CAPID0_B_0_0_0_PCI_SPARE_6_MAX                               (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_SPARE_6_DEF                               (0x00000000)
  #define CAPID0_B_0_0_0_PCI_SPARE_6_HSH                               (0x010C00E8)

  #define CAPID0_B_0_0_0_PCI_DDD_OFF                                   ( 7)
  #define CAPID0_B_0_0_0_PCI_DDD_WID                                   ( 1)
  #define CAPID0_B_0_0_0_PCI_DDD_MSK                                   (0x00000080)
  #define CAPID0_B_0_0_0_PCI_DDD_MIN                                   (0)
  #define CAPID0_B_0_0_0_PCI_DDD_MAX                                   (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_DDD_DEF                                   (0x00000000)
  #define CAPID0_B_0_0_0_PCI_DDD_HSH                                   (0x010E00E8)

  #define CAPID0_B_0_0_0_PCI_GMM_DIS_OFF                               ( 8)
  #define CAPID0_B_0_0_0_PCI_GMM_DIS_WID                               ( 1)
  #define CAPID0_B_0_0_0_PCI_GMM_DIS_MSK                               (0x00000100)
  #define CAPID0_B_0_0_0_PCI_GMM_DIS_MIN                               (0)
  #define CAPID0_B_0_0_0_PCI_GMM_DIS_MAX                               (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_GMM_DIS_DEF                               (0x00000000)
  #define CAPID0_B_0_0_0_PCI_GMM_DIS_HSH                               (0x011000E8)

  #define CAPID0_B_0_0_0_PCI_SPARE_9_OFF                               ( 9)
  #define CAPID0_B_0_0_0_PCI_SPARE_9_WID                               ( 1)
  #define CAPID0_B_0_0_0_PCI_SPARE_9_MSK                               (0x00000200)
  #define CAPID0_B_0_0_0_PCI_SPARE_9_MIN                               (0)
  #define CAPID0_B_0_0_0_PCI_SPARE_9_MAX                               (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_SPARE_9_DEF                               (0x00000000)
  #define CAPID0_B_0_0_0_PCI_SPARE_9_HSH                               (0x011200E8)

  #define CAPID0_B_0_0_0_PCI_SPARE_10_OFF                              (10)
  #define CAPID0_B_0_0_0_PCI_SPARE_10_WID                              ( 1)
  #define CAPID0_B_0_0_0_PCI_SPARE_10_MSK                              (0x00000400)
  #define CAPID0_B_0_0_0_PCI_SPARE_10_MIN                              (0)
  #define CAPID0_B_0_0_0_PCI_SPARE_10_MAX                              (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_SPARE_10_DEF                              (0x00000000)
  #define CAPID0_B_0_0_0_PCI_SPARE_10_HSH                              (0x011400E8)

  #define CAPID0_B_0_0_0_PCI_HDCPD_OFF                                 (11)
  #define CAPID0_B_0_0_0_PCI_HDCPD_WID                                 ( 1)
  #define CAPID0_B_0_0_0_PCI_HDCPD_MSK                                 (0x00000800)
  #define CAPID0_B_0_0_0_PCI_HDCPD_MIN                                 (0)
  #define CAPID0_B_0_0_0_PCI_HDCPD_MAX                                 (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_HDCPD_DEF                                 (0x00000000)
  #define CAPID0_B_0_0_0_PCI_HDCPD_HSH                                 (0x011600E8)

  #define CAPID0_B_0_0_0_PCI_LTECH_OFF                                 (12)
  #define CAPID0_B_0_0_0_PCI_LTECH_WID                                 ( 3)
  #define CAPID0_B_0_0_0_PCI_LTECH_MSK                                 (0x00007000)
  #define CAPID0_B_0_0_0_PCI_LTECH_MIN                                 (0)
  #define CAPID0_B_0_0_0_PCI_LTECH_MAX                                 (7) // 0x00000007
  #define CAPID0_B_0_0_0_PCI_LTECH_DEF                                 (0x00000000)
  #define CAPID0_B_0_0_0_PCI_LTECH_HSH                                 (0x031800E8)

  #define CAPID0_B_0_0_0_PCI_DMIG3DIS_OFF                              (15)
  #define CAPID0_B_0_0_0_PCI_DMIG3DIS_WID                              ( 1)
  #define CAPID0_B_0_0_0_PCI_DMIG3DIS_MSK                              (0x00008000)
  #define CAPID0_B_0_0_0_PCI_DMIG3DIS_MIN                              (0)
  #define CAPID0_B_0_0_0_PCI_DMIG3DIS_MAX                              (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_DMIG3DIS_DEF                              (0x00000000)
  #define CAPID0_B_0_0_0_PCI_DMIG3DIS_HSH                              (0x011E00E8)

  #define CAPID0_B_0_0_0_PCI_PEGX16D_OFF                               (16)
  #define CAPID0_B_0_0_0_PCI_PEGX16D_WID                               ( 1)
  #define CAPID0_B_0_0_0_PCI_PEGX16D_MSK                               (0x00010000)
  #define CAPID0_B_0_0_0_PCI_PEGX16D_MIN                               (0)
  #define CAPID0_B_0_0_0_PCI_PEGX16D_MAX                               (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_PEGX16D_DEF                               (0x00000000)
  #define CAPID0_B_0_0_0_PCI_PEGX16D_HSH                               (0x012000E8)

  #define CAPID0_B_0_0_0_PCI_ADDGFXCAP_OFF                             (17)
  #define CAPID0_B_0_0_0_PCI_ADDGFXCAP_WID                             ( 1)
  #define CAPID0_B_0_0_0_PCI_ADDGFXCAP_MSK                             (0x00020000)
  #define CAPID0_B_0_0_0_PCI_ADDGFXCAP_MIN                             (0)
  #define CAPID0_B_0_0_0_PCI_ADDGFXCAP_MAX                             (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_ADDGFXCAP_DEF                             (0x00000000)
  #define CAPID0_B_0_0_0_PCI_ADDGFXCAP_HSH                             (0x012200E8)

  #define CAPID0_B_0_0_0_PCI_ADDGFXEN_OFF                              (18)
  #define CAPID0_B_0_0_0_PCI_ADDGFXEN_WID                              ( 1)
  #define CAPID0_B_0_0_0_PCI_ADDGFXEN_MSK                              (0x00040000)
  #define CAPID0_B_0_0_0_PCI_ADDGFXEN_MIN                              (0)
  #define CAPID0_B_0_0_0_PCI_ADDGFXEN_MAX                              (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_ADDGFXEN_DEF                              (0x00000000)
  #define CAPID0_B_0_0_0_PCI_ADDGFXEN_HSH                              (0x012400E8)

  #define CAPID0_B_0_0_0_PCI_PKGTYP_OFF                                (19)
  #define CAPID0_B_0_0_0_PCI_PKGTYP_WID                                ( 1)
  #define CAPID0_B_0_0_0_PCI_PKGTYP_MSK                                (0x00080000)
  #define CAPID0_B_0_0_0_PCI_PKGTYP_MIN                                (0)
  #define CAPID0_B_0_0_0_PCI_PKGTYP_MAX                                (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_PKGTYP_DEF                                (0x00000000)
  #define CAPID0_B_0_0_0_PCI_PKGTYP_HSH                                (0x012600E8)

  #define CAPID0_B_0_0_0_PCI_PEGG3_DIS_OFF                             (20)
  #define CAPID0_B_0_0_0_PCI_PEGG3_DIS_WID                             ( 1)
  #define CAPID0_B_0_0_0_PCI_PEGG3_DIS_MSK                             (0x00100000)
  #define CAPID0_B_0_0_0_PCI_PEGG3_DIS_MIN                             (0)
  #define CAPID0_B_0_0_0_PCI_PEGG3_DIS_MAX                             (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_PEGG3_DIS_DEF                             (0x00000000)
  #define CAPID0_B_0_0_0_PCI_PEGG3_DIS_HSH                             (0x012800E8)

  #define CAPID0_B_0_0_0_PCI_PLL_REF100_CFG_OFF                        (21)
  #define CAPID0_B_0_0_0_PCI_PLL_REF100_CFG_WID                        ( 3)
  #define CAPID0_B_0_0_0_PCI_PLL_REF100_CFG_MSK                        (0x00E00000)
  #define CAPID0_B_0_0_0_PCI_PLL_REF100_CFG_MIN                        (0)
  #define CAPID0_B_0_0_0_PCI_PLL_REF100_CFG_MAX                        (7) // 0x00000007
  #define CAPID0_B_0_0_0_PCI_PLL_REF100_CFG_DEF                        (0x00000000)
  #define CAPID0_B_0_0_0_PCI_PLL_REF100_CFG_HSH                        (0x032A00E8)

  #define CAPID0_B_0_0_0_PCI_SVM_DISABLE_OFF                           (24)
  #define CAPID0_B_0_0_0_PCI_SVM_DISABLE_WID                           ( 1)
  #define CAPID0_B_0_0_0_PCI_SVM_DISABLE_MSK                           (0x01000000)
  #define CAPID0_B_0_0_0_PCI_SVM_DISABLE_MIN                           (0)
  #define CAPID0_B_0_0_0_PCI_SVM_DISABLE_MAX                           (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_SVM_DISABLE_DEF                           (0x00000000)
  #define CAPID0_B_0_0_0_PCI_SVM_DISABLE_HSH                           (0x013000E8)

  #define CAPID0_B_0_0_0_PCI_CACHESZ_OFF                               (25)
  #define CAPID0_B_0_0_0_PCI_CACHESZ_WID                               ( 3)
  #define CAPID0_B_0_0_0_PCI_CACHESZ_MSK                               (0x0E000000)
  #define CAPID0_B_0_0_0_PCI_CACHESZ_MIN                               (0)
  #define CAPID0_B_0_0_0_PCI_CACHESZ_MAX                               (7) // 0x00000007
  #define CAPID0_B_0_0_0_PCI_CACHESZ_DEF                               (0x00000000)
  #define CAPID0_B_0_0_0_PCI_CACHESZ_HSH                               (0x033200E8)

  #define CAPID0_B_0_0_0_PCI_SMT_OFF                                   (28)
  #define CAPID0_B_0_0_0_PCI_SMT_WID                                   ( 1)
  #define CAPID0_B_0_0_0_PCI_SMT_MSK                                   (0x10000000)
  #define CAPID0_B_0_0_0_PCI_SMT_MIN                                   (0)
  #define CAPID0_B_0_0_0_PCI_SMT_MAX                                   (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_SMT_DEF                                   (0x00000000)
  #define CAPID0_B_0_0_0_PCI_SMT_HSH                                   (0x013800E8)

  #define CAPID0_B_0_0_0_PCI_OC_ENABLED_OFF                            (29)
  #define CAPID0_B_0_0_0_PCI_OC_ENABLED_WID                            ( 1)
  #define CAPID0_B_0_0_0_PCI_OC_ENABLED_MSK                            (0x20000000)
  #define CAPID0_B_0_0_0_PCI_OC_ENABLED_MIN                            (0)
  #define CAPID0_B_0_0_0_PCI_OC_ENABLED_MAX                            (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_OC_ENABLED_DEF                            (0x00000000)
  #define CAPID0_B_0_0_0_PCI_OC_ENABLED_HSH                            (0x013A00E8)

  #define CAPID0_B_0_0_0_PCI_NPK_DIS_OFF                               (30)
  #define CAPID0_B_0_0_0_PCI_NPK_DIS_WID                               ( 1)
  #define CAPID0_B_0_0_0_PCI_NPK_DIS_MSK                               (0x40000000)
  #define CAPID0_B_0_0_0_PCI_NPK_DIS_MIN                               (0)
  #define CAPID0_B_0_0_0_PCI_NPK_DIS_MAX                               (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_NPK_DIS_DEF                               (0x00000000)
  #define CAPID0_B_0_0_0_PCI_NPK_DIS_HSH                               (0x013C00E8)

  #define CAPID0_B_0_0_0_PCI_IMGU_DIS_OFF                              (31)
  #define CAPID0_B_0_0_0_PCI_IMGU_DIS_WID                              ( 1)
  #define CAPID0_B_0_0_0_PCI_IMGU_DIS_MSK                              (0x80000000)
  #define CAPID0_B_0_0_0_PCI_IMGU_DIS_MIN                              (0)
  #define CAPID0_B_0_0_0_PCI_IMGU_DIS_MAX                              (1) // 0x00000001
  #define CAPID0_B_0_0_0_PCI_IMGU_DIS_DEF                              (0x00000000)
  #define CAPID0_B_0_0_0_PCI_IMGU_DIS_HSH                              (0x013E00E8)

#define CAPID0_C_0_0_0_PCI_REG                                         (0x000000EC)

  #define CAPID0_C_0_0_0_PCI_Max_Data_Rate_At_GEAR1_OFF                ( 0)
  #define CAPID0_C_0_0_0_PCI_Max_Data_Rate_At_GEAR1_WID                ( 5)
  #define CAPID0_C_0_0_0_PCI_Max_Data_Rate_At_GEAR1_MSK                (0x0000001F)
  #define CAPID0_C_0_0_0_PCI_Max_Data_Rate_At_GEAR1_MIN                (0)
  #define CAPID0_C_0_0_0_PCI_Max_Data_Rate_At_GEAR1_MAX                (31) // 0x0000001F
  #define CAPID0_C_0_0_0_PCI_Max_Data_Rate_At_GEAR1_DEF                (0x00000000)
  #define CAPID0_C_0_0_0_PCI_Max_Data_Rate_At_GEAR1_HSH                (0x050000EC)

  #define CAPID0_C_0_0_0_PCI_DISPLAY_PIPE3_OFF                         ( 5)
  #define CAPID0_C_0_0_0_PCI_DISPLAY_PIPE3_WID                         ( 1)
  #define CAPID0_C_0_0_0_PCI_DISPLAY_PIPE3_MSK                         (0x00000020)
  #define CAPID0_C_0_0_0_PCI_DISPLAY_PIPE3_MIN                         (0)
  #define CAPID0_C_0_0_0_PCI_DISPLAY_PIPE3_MAX                         (1) // 0x00000001
  #define CAPID0_C_0_0_0_PCI_DISPLAY_PIPE3_DEF                         (0x00000000)
  #define CAPID0_C_0_0_0_PCI_DISPLAY_PIPE3_HSH                         (0x010A00EC)

  #define CAPID0_C_0_0_0_PCI_IDD_OFF                                   ( 6)
  #define CAPID0_C_0_0_0_PCI_IDD_WID                                   ( 1)
  #define CAPID0_C_0_0_0_PCI_IDD_MSK                                   (0x00000040)
  #define CAPID0_C_0_0_0_PCI_IDD_MIN                                   (0)
  #define CAPID0_C_0_0_0_PCI_IDD_MAX                                   (1) // 0x00000001
  #define CAPID0_C_0_0_0_PCI_IDD_DEF                                   (0x00000000)
  #define CAPID0_C_0_0_0_PCI_IDD_HSH                                   (0x010C00EC)

  #define CAPID0_C_0_0_0_PCI_BCLKOCRANGE_OFF                           ( 7)
  #define CAPID0_C_0_0_0_PCI_BCLKOCRANGE_WID                           ( 2)
  #define CAPID0_C_0_0_0_PCI_BCLKOCRANGE_MSK                           (0x00000180)
  #define CAPID0_C_0_0_0_PCI_BCLKOCRANGE_MIN                           (0)
  #define CAPID0_C_0_0_0_PCI_BCLKOCRANGE_MAX                           (3) // 0x00000003
  #define CAPID0_C_0_0_0_PCI_BCLKOCRANGE_DEF                           (0x00000000)
  #define CAPID0_C_0_0_0_PCI_BCLKOCRANGE_HSH                           (0x020E00EC)

  #define CAPID0_C_0_0_0_PCI_SE_DIS_OFF                                ( 9)
  #define CAPID0_C_0_0_0_PCI_SE_DIS_WID                                ( 1)
  #define CAPID0_C_0_0_0_PCI_SE_DIS_MSK                                (0x00000200)
  #define CAPID0_C_0_0_0_PCI_SE_DIS_MIN                                (0)
  #define CAPID0_C_0_0_0_PCI_SE_DIS_MAX                                (1) // 0x00000001
  #define CAPID0_C_0_0_0_PCI_SE_DIS_DEF                                (0x00000000)
  #define CAPID0_C_0_0_0_PCI_SE_DIS_HSH                                (0x011200EC)

  #define CAPID0_C_0_0_0_PCI_FDSKUFP_OFF                               (10)
  #define CAPID0_C_0_0_0_PCI_FDSKUFP_WID                               ( 4)
  #define CAPID0_C_0_0_0_PCI_FDSKUFP_MSK                               (0x00003C00)
  #define CAPID0_C_0_0_0_PCI_FDSKUFP_MIN                               (0)
  #define CAPID0_C_0_0_0_PCI_FDSKUFP_MAX                               (15) // 0x0000000F
  #define CAPID0_C_0_0_0_PCI_FDSKUFP_DEF                               (0x00000000)
  #define CAPID0_C_0_0_0_PCI_FDSKUFP_HSH                               (0x041400EC)

  #define CAPID0_C_0_0_0_PCI_QCLK_GV_DIS_OFF                           (14)
  #define CAPID0_C_0_0_0_PCI_QCLK_GV_DIS_WID                           ( 1)
  #define CAPID0_C_0_0_0_PCI_QCLK_GV_DIS_MSK                           (0x00004000)
  #define CAPID0_C_0_0_0_PCI_QCLK_GV_DIS_MIN                           (0)
  #define CAPID0_C_0_0_0_PCI_QCLK_GV_DIS_MAX                           (1) // 0x00000001
  #define CAPID0_C_0_0_0_PCI_QCLK_GV_DIS_DEF                           (0x00000000)
  #define CAPID0_C_0_0_0_PCI_QCLK_GV_DIS_HSH                           (0x011C00EC)

  #define CAPID0_C_0_0_0_PCI_SPARE_15_OFF                              (15)
  #define CAPID0_C_0_0_0_PCI_SPARE_15_WID                              ( 1)
  #define CAPID0_C_0_0_0_PCI_SPARE_15_MSK                              (0x00008000)
  #define CAPID0_C_0_0_0_PCI_SPARE_15_MIN                              (0)
  #define CAPID0_C_0_0_0_PCI_SPARE_15_MAX                              (1) // 0x00000001
  #define CAPID0_C_0_0_0_PCI_SPARE_15_DEF                              (0x00000000)
  #define CAPID0_C_0_0_0_PCI_SPARE_15_HSH                              (0x011E00EC)

  #define CAPID0_C_0_0_0_PCI_LPDDR4_EN_OFF                             (16)
  #define CAPID0_C_0_0_0_PCI_LPDDR4_EN_WID                             ( 1)
  #define CAPID0_C_0_0_0_PCI_LPDDR4_EN_MSK                             (0x00010000)
  #define CAPID0_C_0_0_0_PCI_LPDDR4_EN_MIN                             (0)
  #define CAPID0_C_0_0_0_PCI_LPDDR4_EN_MAX                             (1) // 0x00000001
  #define CAPID0_C_0_0_0_PCI_LPDDR4_EN_DEF                             (0x00000000)
  #define CAPID0_C_0_0_0_PCI_LPDDR4_EN_HSH                             (0x012000EC)

  #define CAPID0_C_0_0_0_PCI_MAX_DATA_RATE_LPDDR4_OFF                  (17)
  #define CAPID0_C_0_0_0_PCI_MAX_DATA_RATE_LPDDR4_WID                  ( 5)
  #define CAPID0_C_0_0_0_PCI_MAX_DATA_RATE_LPDDR4_MSK                  (0x003E0000)
  #define CAPID0_C_0_0_0_PCI_MAX_DATA_RATE_LPDDR4_MIN                  (0)
  #define CAPID0_C_0_0_0_PCI_MAX_DATA_RATE_LPDDR4_MAX                  (31) // 0x0000001F
  #define CAPID0_C_0_0_0_PCI_MAX_DATA_RATE_LPDDR4_DEF                  (0x00000000)
  #define CAPID0_C_0_0_0_PCI_MAX_DATA_RATE_LPDDR4_HSH                  (0x052200EC)

  #define CAPID0_C_0_0_0_PCI_DDR4_EN_OFF                               (22)
  #define CAPID0_C_0_0_0_PCI_DDR4_EN_WID                               ( 1)
  #define CAPID0_C_0_0_0_PCI_DDR4_EN_MSK                               (0x00400000)
  #define CAPID0_C_0_0_0_PCI_DDR4_EN_MIN                               (0)
  #define CAPID0_C_0_0_0_PCI_DDR4_EN_MAX                               (1) // 0x00000001
  #define CAPID0_C_0_0_0_PCI_DDR4_EN_DEF                               (0x00000000)
  #define CAPID0_C_0_0_0_PCI_DDR4_EN_HSH                               (0x012C00EC)

  #define CAPID0_C_0_0_0_PCI_MAX_DATA_RATE_DDR4_OFF                    (23)
  #define CAPID0_C_0_0_0_PCI_MAX_DATA_RATE_DDR4_WID                    ( 5)
  #define CAPID0_C_0_0_0_PCI_MAX_DATA_RATE_DDR4_MSK                    (0x0F800000)
  #define CAPID0_C_0_0_0_PCI_MAX_DATA_RATE_DDR4_MIN                    (0)
  #define CAPID0_C_0_0_0_PCI_MAX_DATA_RATE_DDR4_MAX                    (31) // 0x0000001F
  #define CAPID0_C_0_0_0_PCI_MAX_DATA_RATE_DDR4_DEF                    (0x00000000)
  #define CAPID0_C_0_0_0_PCI_MAX_DATA_RATE_DDR4_HSH                    (0x052E00EC)

  #define CAPID0_C_0_0_0_PCI_PEGG4_DIS_OFF                             (28)
  #define CAPID0_C_0_0_0_PCI_PEGG4_DIS_WID                             ( 1)
  #define CAPID0_C_0_0_0_PCI_PEGG4_DIS_MSK                             (0x10000000)
  #define CAPID0_C_0_0_0_PCI_PEGG4_DIS_MIN                             (0)
  #define CAPID0_C_0_0_0_PCI_PEGG4_DIS_MAX                             (1) // 0x00000001
  #define CAPID0_C_0_0_0_PCI_PEGG4_DIS_DEF                             (0x00000000)
  #define CAPID0_C_0_0_0_PCI_PEGG4_DIS_HSH                             (0x013800EC)

  #define CAPID0_C_0_0_0_PCI_SPARE_31_29_OFF                           (29)
  #define CAPID0_C_0_0_0_PCI_SPARE_31_29_WID                           ( 3)
  #define CAPID0_C_0_0_0_PCI_SPARE_31_29_MSK                           (0xE0000000)
  #define CAPID0_C_0_0_0_PCI_SPARE_31_29_MIN                           (0)
  #define CAPID0_C_0_0_0_PCI_SPARE_31_29_MAX                           (7) // 0x00000007
  #define CAPID0_C_0_0_0_PCI_SPARE_31_29_DEF                           (0x00000000)
  #define CAPID0_C_0_0_0_PCI_SPARE_31_29_HSH                           (0x033A00EC)

#define CAPID0_E_0_0_0_PCI_REG                                         (0x000000F0)

  #define CAPID0_E_0_0_0_PCI_LPDDR5_EN_OFF                             ( 0)
  #define CAPID0_E_0_0_0_PCI_LPDDR5_EN_WID                             ( 1)
  #define CAPID0_E_0_0_0_PCI_LPDDR5_EN_MSK                             (0x00000001)
  #define CAPID0_E_0_0_0_PCI_LPDDR5_EN_MIN                             (0)
  #define CAPID0_E_0_0_0_PCI_LPDDR5_EN_MAX                             (1) // 0x00000001
  #define CAPID0_E_0_0_0_PCI_LPDDR5_EN_DEF                             (0x00000000)
  #define CAPID0_E_0_0_0_PCI_LPDDR5_EN_HSH                             (0x010000F0)

  #define CAPID0_E_0_0_0_PCI_MAX_DATA_RATE_LPDDR5_OFF                  ( 1)
  #define CAPID0_E_0_0_0_PCI_MAX_DATA_RATE_LPDDR5_WID                  ( 5)
  #define CAPID0_E_0_0_0_PCI_MAX_DATA_RATE_LPDDR5_MSK                  (0x0000003E)
  #define CAPID0_E_0_0_0_PCI_MAX_DATA_RATE_LPDDR5_MIN                  (0)
  #define CAPID0_E_0_0_0_PCI_MAX_DATA_RATE_LPDDR5_MAX                  (31) // 0x0000001F
  #define CAPID0_E_0_0_0_PCI_MAX_DATA_RATE_LPDDR5_DEF                  (0x00000000)
  #define CAPID0_E_0_0_0_PCI_MAX_DATA_RATE_LPDDR5_HSH                  (0x050200F0)

  #define CAPID0_E_0_0_0_PCI_DDR5_EN_OFF                               ( 6)
  #define CAPID0_E_0_0_0_PCI_DDR5_EN_WID                               ( 1)
  #define CAPID0_E_0_0_0_PCI_DDR5_EN_MSK                               (0x00000040)
  #define CAPID0_E_0_0_0_PCI_DDR5_EN_MIN                               (0)
  #define CAPID0_E_0_0_0_PCI_DDR5_EN_MAX                               (1) // 0x00000001
  #define CAPID0_E_0_0_0_PCI_DDR5_EN_DEF                               (0x00000000)
  #define CAPID0_E_0_0_0_PCI_DDR5_EN_HSH                               (0x010C00F0)

  #define CAPID0_E_0_0_0_PCI_MAX_DATA_RATE_DDR5_OFF                    ( 7)
  #define CAPID0_E_0_0_0_PCI_MAX_DATA_RATE_DDR5_WID                    ( 5)
  #define CAPID0_E_0_0_0_PCI_MAX_DATA_RATE_DDR5_MSK                    (0x00000F80)
  #define CAPID0_E_0_0_0_PCI_MAX_DATA_RATE_DDR5_MIN                    (0)
  #define CAPID0_E_0_0_0_PCI_MAX_DATA_RATE_DDR5_MAX                    (31) // 0x0000001F
  #define CAPID0_E_0_0_0_PCI_MAX_DATA_RATE_DDR5_DEF                    (0x00000000)
  #define CAPID0_E_0_0_0_PCI_MAX_DATA_RATE_DDR5_HSH                    (0x050E00F0)

  #define CAPID0_E_0_0_0_PCI_IBECC_DIS_OFF                             (12)
  #define CAPID0_E_0_0_0_PCI_IBECC_DIS_WID                             ( 1)
  #define CAPID0_E_0_0_0_PCI_IBECC_DIS_MSK                             (0x00001000)
  #define CAPID0_E_0_0_0_PCI_IBECC_DIS_MIN                             (0)
  #define CAPID0_E_0_0_0_PCI_IBECC_DIS_MAX                             (1) // 0x00000001
  #define CAPID0_E_0_0_0_PCI_IBECC_DIS_DEF                             (0x00000000)
  #define CAPID0_E_0_0_0_PCI_IBECC_DIS_HSH                             (0x011800F0)

  #define CAPID0_E_0_0_0_PCI_VDDQ_VOLTAGE_MAX_OFF                      (13)
  #define CAPID0_E_0_0_0_PCI_VDDQ_VOLTAGE_MAX_WID                      (11)
  #define CAPID0_E_0_0_0_PCI_VDDQ_VOLTAGE_MAX_MSK                      (0x00FFE000)
  #define CAPID0_E_0_0_0_PCI_VDDQ_VOLTAGE_MAX_MIN                      (0)
  #define CAPID0_E_0_0_0_PCI_VDDQ_VOLTAGE_MAX_MAX                      (2047) // 0x000007FF
  #define CAPID0_E_0_0_0_PCI_VDDQ_VOLTAGE_MAX_DEF                      (0x00000000)
  #define CAPID0_E_0_0_0_PCI_VDDQ_VOLTAGE_MAX_HSH                      (0x0B1A00F0)

  #define CAPID0_E_0_0_0_PCI_CRASHLOG_DIS_OFF                          (24)
  #define CAPID0_E_0_0_0_PCI_CRASHLOG_DIS_WID                          ( 1)
  #define CAPID0_E_0_0_0_PCI_CRASHLOG_DIS_MSK                          (0x01000000)
  #define CAPID0_E_0_0_0_PCI_CRASHLOG_DIS_MIN                          (0)
  #define CAPID0_E_0_0_0_PCI_CRASHLOG_DIS_MAX                          (1) // 0x00000001
  #define CAPID0_E_0_0_0_PCI_CRASHLOG_DIS_DEF                          (0x00000000)
  #define CAPID0_E_0_0_0_PCI_CRASHLOG_DIS_HSH                          (0x013000F0)

  #define CAPID0_E_0_0_0_PCI_SPARE_OFF                                 (25)
  #define CAPID0_E_0_0_0_PCI_SPARE_WID                                 ( 7)
  #define CAPID0_E_0_0_0_PCI_SPARE_MSK                                 (0xFE000000)
  #define CAPID0_E_0_0_0_PCI_SPARE_MIN                                 (0)
  #define CAPID0_E_0_0_0_PCI_SPARE_MAX                                 (127) // 0x0000007F
  #define CAPID0_E_0_0_0_PCI_SPARE_DEF                                 (0x00000000)
  #define CAPID0_E_0_0_0_PCI_SPARE_HSH                                 (0x073200F0)

#define MID_0_0_0_PCI_REG                                              (0x000000F4)

  #define MID_0_0_0_PCI_PROC_OFF                                       ( 0)
  #define MID_0_0_0_PCI_PROC_WID                                       ( 8)
  #define MID_0_0_0_PCI_PROC_MSK                                       (0x000000FF)
  #define MID_0_0_0_PCI_PROC_MIN                                       (0)
  #define MID_0_0_0_PCI_PROC_MAX                                       (255) // 0x000000FF
  #define MID_0_0_0_PCI_PROC_DEF                                       (0x00000019)
  #define MID_0_0_0_PCI_PROC_HSH                                       (0x080000F4)

  #define MID_0_0_0_PCI_FOUND_OFF                                      ( 8)
  #define MID_0_0_0_PCI_FOUND_WID                                      ( 8)
  #define MID_0_0_0_PCI_FOUND_MSK                                      (0x0000FF00)
  #define MID_0_0_0_PCI_FOUND_MIN                                      (0)
  #define MID_0_0_0_PCI_FOUND_MAX                                      (255) // 0x000000FF
  #define MID_0_0_0_PCI_FOUND_DEF                                      (0x0000000F)
  #define MID_0_0_0_PCI_FOUND_HSH                                      (0x081000F4)

  #define MID_0_0_0_PCI_MSTEP_OFF                                      (16)
  #define MID_0_0_0_PCI_MSTEP_WID                                      ( 8)
  #define MID_0_0_0_PCI_MSTEP_MSK                                      (0x00FF0000)
  #define MID_0_0_0_PCI_MSTEP_MIN                                      (0)
  #define MID_0_0_0_PCI_MSTEP_MAX                                      (255) // 0x000000FF
  #define MID_0_0_0_PCI_MSTEP_DEF                                      (0x00000000)
  #define MID_0_0_0_PCI_MSTEP_HSH                                      (0x082000F4)

  #define MID_0_0_0_PCI_DOT_OFF                                        (24)
  #define MID_0_0_0_PCI_DOT_WID                                        ( 4)
  #define MID_0_0_0_PCI_DOT_MSK                                        (0x0F000000)
  #define MID_0_0_0_PCI_DOT_MIN                                        (0)
  #define MID_0_0_0_PCI_DOT_MAX                                        (15) // 0x0000000F
  #define MID_0_0_0_PCI_DOT_DEF                                        (0x00000000)
  #define MID_0_0_0_PCI_DOT_HSH                                        (0x043000F4)

#define DEBUP0_0_0_0_PCI_REG                                           (0x000000F8)

  #define DEBUP0_0_0_0_PCI_RSVD_S0_OFF                                 ( 0)
  #define DEBUP0_0_0_0_PCI_RSVD_S0_WID                                 ( 3)
  #define DEBUP0_0_0_0_PCI_RSVD_S0_MSK                                 (0x00000007)
  #define DEBUP0_0_0_0_PCI_RSVD_S0_MIN                                 (0)
  #define DEBUP0_0_0_0_PCI_RSVD_S0_MAX                                 (7) // 0x00000007
  #define DEBUP0_0_0_0_PCI_RSVD_S0_DEF                                 (0x00000000)
  #define DEBUP0_0_0_0_PCI_RSVD_S0_HSH                                 (0x030000F8)

  #define DEBUP0_0_0_0_PCI_RSVD_S1_OFF                                 ( 4)
  #define DEBUP0_0_0_0_PCI_RSVD_S1_WID                                 ( 3)
  #define DEBUP0_0_0_0_PCI_RSVD_S1_MSK                                 (0x00000070)
  #define DEBUP0_0_0_0_PCI_RSVD_S1_MIN                                 (0)
  #define DEBUP0_0_0_0_PCI_RSVD_S1_MAX                                 (7) // 0x00000007
  #define DEBUP0_0_0_0_PCI_RSVD_S1_DEF                                 (0x00000000)
  #define DEBUP0_0_0_0_PCI_RSVD_S1_HSH                                 (0x030800F8)

  #define DEBUP0_0_0_0_PCI_RSVD_S2_OFF                                 ( 8)
  #define DEBUP0_0_0_0_PCI_RSVD_S2_WID                                 ( 3)
  #define DEBUP0_0_0_0_PCI_RSVD_S2_MSK                                 (0x00000700)
  #define DEBUP0_0_0_0_PCI_RSVD_S2_MIN                                 (0)
  #define DEBUP0_0_0_0_PCI_RSVD_S2_MAX                                 (7) // 0x00000007
  #define DEBUP0_0_0_0_PCI_RSVD_S2_DEF                                 (0x00000000)
  #define DEBUP0_0_0_0_PCI_RSVD_S2_HSH                                 (0x031000F8)

  #define DEBUP0_0_0_0_PCI_RSVD_S3_OFF                                 (12)
  #define DEBUP0_0_0_0_PCI_RSVD_S3_WID                                 ( 3)
  #define DEBUP0_0_0_0_PCI_RSVD_S3_MSK                                 (0x00007000)
  #define DEBUP0_0_0_0_PCI_RSVD_S3_MIN                                 (0)
  #define DEBUP0_0_0_0_PCI_RSVD_S3_MAX                                 (7) // 0x00000007
  #define DEBUP0_0_0_0_PCI_RSVD_S3_DEF                                 (0x00000000)
  #define DEBUP0_0_0_0_PCI_RSVD_S3_HSH                                 (0x031800F8)

  #define DEBUP0_0_0_0_PCI_RSVD_S4_OFF                                 (16)
  #define DEBUP0_0_0_0_PCI_RSVD_S4_WID                                 ( 3)
  #define DEBUP0_0_0_0_PCI_RSVD_S4_MSK                                 (0x00070000)
  #define DEBUP0_0_0_0_PCI_RSVD_S4_MIN                                 (0)
  #define DEBUP0_0_0_0_PCI_RSVD_S4_MAX                                 (7) // 0x00000007
  #define DEBUP0_0_0_0_PCI_RSVD_S4_DEF                                 (0x00000000)
  #define DEBUP0_0_0_0_PCI_RSVD_S4_HSH                                 (0x032000F8)

  #define DEBUP0_0_0_0_PCI_RSVD_RW_OFF                                 (20)
  #define DEBUP0_0_0_0_PCI_RSVD_RW_WID                                 (12)
  #define DEBUP0_0_0_0_PCI_RSVD_RW_MSK                                 (0xFFF00000)
  #define DEBUP0_0_0_0_PCI_RSVD_RW_MIN                                 (0)
  #define DEBUP0_0_0_0_PCI_RSVD_RW_MAX                                 (4095) // 0x00000FFF
  #define DEBUP0_0_0_0_PCI_RSVD_RW_DEF                                 (0x00000000)
  #define DEBUP0_0_0_0_PCI_RSVD_RW_HSH                                 (0x0C2800F8)

#define DEBUP1_0_0_0_PCI_REG                                           (0x000000FC)

  #define DEBUP1_0_0_0_PCI_RSVD0_OFF                                   ( 0)
  #define DEBUP1_0_0_0_PCI_RSVD0_WID                                   ( 3)
  #define DEBUP1_0_0_0_PCI_RSVD0_MSK                                   (0x00000007)
  #define DEBUP1_0_0_0_PCI_RSVD0_MIN                                   (0)
  #define DEBUP1_0_0_0_PCI_RSVD0_MAX                                   (7) // 0x00000007
  #define DEBUP1_0_0_0_PCI_RSVD0_DEF                                   (0x00000000)
  #define DEBUP1_0_0_0_PCI_RSVD0_HSH                                   (0x030000FC)

  #define DEBUP1_0_0_0_PCI_RSVD1_OFF                                   ( 3)
  #define DEBUP1_0_0_0_PCI_RSVD1_WID                                   ( 1)
  #define DEBUP1_0_0_0_PCI_RSVD1_MSK                                   (0x00000008)
  #define DEBUP1_0_0_0_PCI_RSVD1_MIN                                   (0)
  #define DEBUP1_0_0_0_PCI_RSVD1_MAX                                   (1) // 0x00000001
  #define DEBUP1_0_0_0_PCI_RSVD1_DEF                                   (0x00000000)
  #define DEBUP1_0_0_0_PCI_RSVD1_HSH                                   (0x010600FC)

  #define DEBUP1_0_0_0_PCI_RSVD2_OFF                                   ( 4)
  #define DEBUP1_0_0_0_PCI_RSVD2_WID                                   ( 3)
  #define DEBUP1_0_0_0_PCI_RSVD2_MSK                                   (0x00000070)
  #define DEBUP1_0_0_0_PCI_RSVD2_MIN                                   (0)
  #define DEBUP1_0_0_0_PCI_RSVD2_MAX                                   (7) // 0x00000007
  #define DEBUP1_0_0_0_PCI_RSVD2_DEF                                   (0x00000000)
  #define DEBUP1_0_0_0_PCI_RSVD2_HSH                                   (0x030800FC)

  #define DEBUP1_0_0_0_PCI_RSVD3_OFF                                   ( 7)
  #define DEBUP1_0_0_0_PCI_RSVD3_WID                                   ( 1)
  #define DEBUP1_0_0_0_PCI_RSVD3_MSK                                   (0x00000080)
  #define DEBUP1_0_0_0_PCI_RSVD3_MIN                                   (0)
  #define DEBUP1_0_0_0_PCI_RSVD3_MAX                                   (1) // 0x00000001
  #define DEBUP1_0_0_0_PCI_RSVD3_DEF                                   (0x00000000)
  #define DEBUP1_0_0_0_PCI_RSVD3_HSH                                   (0x010E00FC)

  #define DEBUP1_0_0_0_PCI_RSVD4_OFF                                   ( 8)
  #define DEBUP1_0_0_0_PCI_RSVD4_WID                                   ( 3)
  #define DEBUP1_0_0_0_PCI_RSVD4_MSK                                   (0x00000700)
  #define DEBUP1_0_0_0_PCI_RSVD4_MIN                                   (0)
  #define DEBUP1_0_0_0_PCI_RSVD4_MAX                                   (7) // 0x00000007
  #define DEBUP1_0_0_0_PCI_RSVD4_DEF                                   (0x00000000)
  #define DEBUP1_0_0_0_PCI_RSVD4_HSH                                   (0x031000FC)

  #define DEBUP1_0_0_0_PCI_RSVD5_OFF                                   (11)
  #define DEBUP1_0_0_0_PCI_RSVD5_WID                                   ( 1)
  #define DEBUP1_0_0_0_PCI_RSVD5_MSK                                   (0x00000800)
  #define DEBUP1_0_0_0_PCI_RSVD5_MIN                                   (0)
  #define DEBUP1_0_0_0_PCI_RSVD5_MAX                                   (1) // 0x00000001
  #define DEBUP1_0_0_0_PCI_RSVD5_DEF                                   (0x00000000)
  #define DEBUP1_0_0_0_PCI_RSVD5_HSH                                   (0x011600FC)

  #define DEBUP1_0_0_0_PCI_RSVD6_OFF                                   (12)
  #define DEBUP1_0_0_0_PCI_RSVD6_WID                                   ( 3)
  #define DEBUP1_0_0_0_PCI_RSVD6_MSK                                   (0x00007000)
  #define DEBUP1_0_0_0_PCI_RSVD6_MIN                                   (0)
  #define DEBUP1_0_0_0_PCI_RSVD6_MAX                                   (7) // 0x00000007
  #define DEBUP1_0_0_0_PCI_RSVD6_DEF                                   (0x00000000)
  #define DEBUP1_0_0_0_PCI_RSVD6_HSH                                   (0x031800FC)

  #define DEBUP1_0_0_0_PCI_RSVD7_OFF                                   (15)
  #define DEBUP1_0_0_0_PCI_RSVD7_WID                                   ( 1)
  #define DEBUP1_0_0_0_PCI_RSVD7_MSK                                   (0x00008000)
  #define DEBUP1_0_0_0_PCI_RSVD7_MIN                                   (0)
  #define DEBUP1_0_0_0_PCI_RSVD7_MAX                                   (1) // 0x00000001
  #define DEBUP1_0_0_0_PCI_RSVD7_DEF                                   (0x00000000)
  #define DEBUP1_0_0_0_PCI_RSVD7_HSH                                   (0x011E00FC)

  #define DEBUP1_0_0_0_PCI_RSVD8_OFF                                   (16)
  #define DEBUP1_0_0_0_PCI_RSVD8_WID                                   ( 3)
  #define DEBUP1_0_0_0_PCI_RSVD8_MSK                                   (0x00070000)
  #define DEBUP1_0_0_0_PCI_RSVD8_MIN                                   (0)
  #define DEBUP1_0_0_0_PCI_RSVD8_MAX                                   (7) // 0x00000007
  #define DEBUP1_0_0_0_PCI_RSVD8_DEF                                   (0x00000000)
  #define DEBUP1_0_0_0_PCI_RSVD8_HSH                                   (0x032000FC)

  #define DEBUP1_0_0_0_PCI_RSVD9_OFF                                   (19)
  #define DEBUP1_0_0_0_PCI_RSVD9_WID                                   ( 1)
  #define DEBUP1_0_0_0_PCI_RSVD9_MSK                                   (0x00080000)
  #define DEBUP1_0_0_0_PCI_RSVD9_MIN                                   (0)
  #define DEBUP1_0_0_0_PCI_RSVD9_MAX                                   (1) // 0x00000001
  #define DEBUP1_0_0_0_PCI_RSVD9_DEF                                   (0x00000000)
  #define DEBUP1_0_0_0_PCI_RSVD9_HSH                                   (0x012600FC)

  #define DEBUP1_0_0_0_PCI_RSVD10_OFF                                  (20)
  #define DEBUP1_0_0_0_PCI_RSVD10_WID                                  (12)
  #define DEBUP1_0_0_0_PCI_RSVD10_MSK                                  (0xFFF00000)
  #define DEBUP1_0_0_0_PCI_RSVD10_MIN                                  (0)
  #define DEBUP1_0_0_0_PCI_RSVD10_MAX                                  (4095) // 0x00000FFF
  #define DEBUP1_0_0_0_PCI_RSVD10_DEF                                  (0x00000000)
  #define DEBUP1_0_0_0_PCI_RSVD10_HSH                                  (0x0C2800FC)
#pragma pack(pop)
#endif
