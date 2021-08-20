/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2017 Intel Corporation.

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

#ifndef _GENERIC_SIO_H_
#define _GENERIC_SIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <Protocol/PciIo.h>

// 51E9B4F9-555D-476c-8BB5-BD18D9A68878
#define EFI_BOARD_SIO_PROTOCOL_GUID \
    {0x51e9b4f9,0x555d,0x476c, {0x8b, 0xb5, 0xbd, 0x18, 0xd9, 0xa6, 0x88, 0x78}}

typedef struct _BOARD_SIO_PROTOCOL BOARD_SIO_PROTOCOL;

typedef struct _EFI_EISAID {
  UINT32                HID;
  UINT32                UID;
} EFI_EISAID;

//This list migt be extended if some devices
//not mention here present in SIO
typedef enum {
  dsNone=0,
  dsFDC,
  dsPS2K,  //PS2 Keyboard Controller if KBC on separate from MS Logical Device
  dsPS2M,  //PS2 Mouse Controller if MS on separate from KBC Logical Device
  dsPS2CK,//PS2 Keyboard Controller where KBC and MS on same Logical Device
  dsPS2CM,//PS2 Mouse Controller where KBC and MS on same Logical Device
  dsUART,
  dsLPT,
  dsGAME,
  dsSB16,
  dsMPU401,
  dsFmSynth,
  dsCIR,
  dsGPIO,
  dsHwMon,
  dsPME,
  dsACPI,
} SIO_DEV_TYPE;


typedef EFI_STATUS (*SIO_REGISTER) (
    IN BOARD_SIO_PROTOCOL    *This,
  IN BOOLEAN        Write,
  IN BOOLEAN        ExitCfgMode,
    IN UINT8              Register,
    IN OUT UINT8          *Value
);

typedef struct _T_ITEM_LIST {
  UINTN        InitialCount;
  UINTN        ItemCount;
  VOID        **Items;
}T_ITEM_LIST;

typedef EFI_STATUS (*SIO_RESOURCES)(
    IN BOARD_SIO_PROTOCOL   *This,
    IN BOOLEAN         Set,
  IN OUT T_ITEM_LIST    **Resources
);

//**********************************************************************
//
// Name:        BOARD_SIO_PROTOCOL
//
// Description: Functions to access the SIO.
//
// Fields:     Name        Type        Description
//        ------------------------------------------------------------
//
//**********************************************************************
typedef struct _BOARD_SIO_PROTOCOL {
    SIO_REGISTER           Access;
  SIO_RESOURCES      CurrentRes;
  SIO_RESOURCES      PossibleRes;
} BOARD_SIO_PROTOCOL;

#define PNP_HID EFI_PNP_ID

//--------------------------------------------
//Defines how to enter Exit config Mode
typedef enum _SPIO_GFG_OP_TYPE{
  cfgNone=0,    //Not required any sequence
  cfgByteSeq,
  cfgRoutine,
  cfgMaxCfg
} SPIO_GFG_OP_TYPE;

typedef VOID (*SPIO_ROUTINE) (
  VOID
  );

typedef struct _SPIO_SCRIPT {
  BOOLEAN    IdxDat;  //1=IDX 0=DAT
  BOOLEAN    WrRd;   //1=Write 0=Read
  UINT8    Value;   //if WrRd=0 wait for this data to come
} SPIO_SCRIPT;

typedef struct SPIO_SCRIPT_LST {
  SPIO_GFG_OP_TYPE  OpType;
  UINTN        InstrCount;
   VOID        *Instruction[1]; //  c4200
} SPIO_SCRIPT_LST;

//==================================================================
//Definitions of SIO Shared Resource Flags if this flags set
//and will share following type of resources with PREVIOUSE device
#define SIO_SHR_NONE  0x00
#define SIO_SHR_IO1    0x01 //device shares resources programmed in SIO_1_BASE_REG
#define SIO_SHR_IO2    0x02 //device shares resources programmed in SIO_2_BASE_REG
#define SIO_SHR_IO    (SIO_SHR_IO1 | SIO_SHR_IO2) //device shares resources programmed in both SIO_BASE_REG
#define SIO_SHR_IRQ1  0x04
#define SIO_SHR_IRQ2  0x08
#define SIO_SHR_IRQ    (SIO_SHR_IRQ1 | SIO_SHR_IRQ2)
#define SIO_SHR_DMA1  0x10
#define SIO_SHR_DMA2  0x20
#define SIO_SHR_DMA    (SIO_SHR_DMA1 | SIO_SHR_DMA2)
#define SIO_SHR_ALL    (SIO_SHR_IO | SIO_SHR_IRQ | SIO_SHR_DMA)
#define SIO_NO_RES    0x80 //this bit will be set if device not using any resources but must be enabled
               //at at least one call must return SUCCESS if this flag
//all other values reserved

#pragma pack(push,1)

  typedef struct _SIO_DEV_V_DATA {
    UINT8    DevImplemented;
    UINT16    DevBase1;
    UINT16    DevBase2;
    UINT8    DevIrq1;
    UINT8    DevIrq2;
    UINT8    DevDma1;
    UINT8    DevDma2;
  } SIO_DEV_V_DATA;

  typedef struct _SIO_DEV_NV_DATA {
    UINT8    DevEnable;
    UINT8    DevPrsId;
    UINT8    DevMode;
  } SIO_DEV_NV_DATA;

#pragma pack(pop)

typedef enum {
  isNone=0,
  isPrsSelect,
  isBeforeActivate,
  isAfterActivate,
  isGetSetupData,
  isMaxInitStep
} SIO_INIT_STEP;

//SIO Component Initialization Routine ptrototype
typedef EFI_STATUS (*SIO_INIT)( IN BOARD_SIO_PROTOCOL   *This,
                IN EFI_PCI_IO_PROTOCOL   *PciIo,
                IN SIO_INIT_STEP     InitStep);

//Device table used for porting see YourSioNameDxe.c
typedef struct _SPIO_DEV_LST {
  SIO_DEV_TYPE  Type;
  UINT8      LDN;    //LogicalDevice #
  UINT8      UID;     //Unique ID if there are 2 or more
                //devices of the same type in this SPIO
  UINT16      PnpId;
  BOOLEAN       Implemented;//Implemented on this Platform (has connector)
  BOOLEAN      HasSetup;  //TRUE If Device has SETUP screen and se
  UINT8      Flags;    //set if Device shares all or some of it's resources
  UINT8      AslName[5]; //ASL DEVICE OBJECT NAME to look for _PRS in AML
                //if this field not 0,0,0,0 the rest of the table ignored.
  UINT16      ResBase[2];  //Base Address for SIO_1_BASE_REG and SIO_2_BASE_REG
  UINT8      ResLen[2];
  UINT16      IrqMask[2];
  UINT8      DmaMask[2];
  SIO_INIT    InitRoutine;
//  UINTN      SetupOffset; //offset in SIO_SETUP_VAR for this device if any
//  UINTN      VolatileOffset; //offset in SIO_SETUP_VOLATILE data for this device if any
} SPIO_DEV_LST;

//This structure will define a multiple SIO Porting Information
//It will be an array of such structures each of them will represent
//a different SIO Device.
typedef struct _SPIO_LIST_ITEM {
  //This Information is needed to identify right LPC bridge for the SIO
  // value of  -1 (0xF..F) means Do not check this parameter
  UINT32      IsaVenDevId;
  UINT32      IsaSubVenId;
  UINT8      IsaBusNo;
  UINT8      IsaDevNo;
  UINT8      IsaFuncNo;
//  //This is the information Needed Get Sio Setup Data
//  //----------------------------------------
//  UINT16      *SetupVarName;
//  UINT16      *VolatileVarName;
//  EFI_GUID    *SioVarGuid;
//  //This is the information Needed to access SIO Generic Registers
//  //----------------------------------------
  UINT16      SioIndex;
  UINT16      SioData;
  // Dev Select and Activate
  UINT8      DevSel;
  UINT8      Activate;
  UINT8      ActivVal;
  UINT8      DeactVal;
  //Generic registers location
  UINT8      Base1Hi;
  UINT8      Base1Lo;
  UINT8      Base2Hi;
  UINT8      Base2Lo;
  UINT8      Irq1;
  UINT8      Irq2;
  UINT8      Dma1;
  UINT8      Dma2;
  //List of devices inside this SIO
  UINTN      DevCount;
  SPIO_DEV_LST  *SioDevList;
  //List of valid registers inside SIO to check if they has to be saved
  //----------------------------------------
  //in BOOT_SCRIPT_SAVE for S3 state Resume
  //This is for global registers which are the same for all devices in SIO
  UINTN      GlobalInclRegCount;
  UINT8      *GlobalIncludeReg; //Buffer will be located in GSPIO structure
  //This is for Local registers they are unique for each device in SIO
  UINTN      LocalInclRegCount;
  UINT8      *LocalIncludeReg; //Buffer will be located in SIO_DEV structure
  //----------------------------------------
  //How To enter/exit Configuration mode if any
  SPIO_SCRIPT_LST  *EnterCfgMode;
  SPIO_SCRIPT_LST  *ExitCfgMode;
}SPIO_LIST_ITEM;

typedef struct _GSPIO GSPIO;

//SPIO Device Private Data section
typedef struct _SPIO_DEV {
  BOARD_SIO_PROTOCOL  BoardSio;
  EFI_DEVICE_PATH_PROTOCOL *DevicePath;
  EFI_HANDLE      Handle;
//  BOOLEAN        Implemented;  //Present in SPIO_DEV.DeviceInfo;
  BOOLEAN        Started;
  BOOLEAN        Assigned;
  BOOLEAN        Initialized;
  BOOLEAN        IrqReserved;
//  UINT8        LDN;      //Present in SPIO_DEV.DeviceInfo;
  UINT8        Reserved;
//  UINTN        Flags;      //Present in SPIO_DEV.DeviceInfo;
  struct _SPIO_DEV  *ResOwner;
  struct _SPIO_DEV  *ResConsumer;
//  SIO_DEV_TYPE    Type;      //Present in SPIO_DEV.DeviceInfo;
  EFI_EISAID      EisaId;
  T_ITEM_LIST      CRS;
  T_ITEM_LIST      PRS;
  //SIO_INIT      InitRoutine;  //Present in SPIO_DEV.DeviceInfo;
//we will need it to generate boot script for s3 resume
  UINT8        *LocalCfgDump;
  GSPIO        *Owner;
  SPIO_DEV_LST    *DeviceInfo;
  SIO_DEV_NV_DATA    NvData;
  SIO_DEV_V_DATA    VlData;
  EFI_HANDLE      ImageHandle;
} SPIO_DEV;

//Global Super IO device Private Structure
typedef struct _GSPIO {
  //UINT16      Indx;
  //UINT16      Data;
//  EFI_HANDLE    ImageHandle; don't need it
  EFI_HANDLE    CntrHandle;
  EFI_HANDLE    SupportedHandle; //
  EFI_DEVICE_PATH_PROTOCOL   *CntrDevPath;
  EFI_PCI_IO_PROTOCOL *IsaBrgPciIo;
  BOOLEAN      InCfgMode;
  UINTN      DeviceCount;
  SPIO_DEV    **DeviceList;
  //we will need it to generate boot script for s3 resume
  UINT8      *GlobalCfgDump;
  SPIO_LIST_ITEM  *SpioInfo;
} GSPIO;

#define SIO_DEV_STATUS_VAR_NAME  L"SIO_DEV_STATUS_VAR"

#define SIO_DEV_STATUS_VAR_GUID \
  {0x5820de98, 0xfc8e, 0x4b0b, 0xa4, 0xb9, 0xa, 0x94, 0xd, 0x16, 0x2a, 0x7e}

//
// Bit values of various SIO devices defined in SIO_DEV_STATUS
//
#define SIO_DEV_COM1    0x0001
#define SIO_DEV_COM2    0x0002
#define SIO_DEV_LPT      0x0004
#define SIO_DEV_FDC      0x0008
#define SIO_DEV_SB16    0x0010
#define SIO_DEV_MIDI    0x0020
#define SIO_DEV_MSSAUDIO  0x0040
#define SIO_DEV_FMSYNTH    0x0080
#define SIO_DEV_GAME1    0x0100
#define SIO_DEV_GAME2    0x0200
#define SIO_DEV_KBC      0x0400
#define SIO_DEV_EC      0x0800
#define SIO_DEV_COM3        0x1000
#define SIO_DEV_COM4        0x2000
#define SIO_DEV_PS2MS    0x4000

typedef union {
  UINT16  DEV_STATUS;
  struct  {
    UINT16   SerialA    : 1;  //bit 0 - Serial A
    UINT16   SerialB   : 1;  //bit 1  - Serial B
    UINT16  Lpt      : 1;  //bit 2 - LPT
    UINT16  Fdd      : 1;  //bit 3 - FDD
    UINT16  Sb16    : 1;  //bit 4 - SB16 Audio
    UINT16  Midi    : 1;  //bit 5 - MIDI
    UINT16  MssAudio  : 1;  //bit 6 - MSS Audio
    UINT16  FmSynth    : 1;  //bit 7 - AdLib sound (FM synth)
    UINT16  Game1    : 1;  //bit 8 - Game port #1
    UINT16  Game2    : 1;  //bit 9 - Game port #2
    UINT16  Key60_64  : 1;  //bit a - KBC
    UINT16  Ec62_66    : 1;  //bit b - EC
    UINT16  SerialC    : 1;  //bit c - Reserved
    UINT16  SerialD    : 1;  //bit d - Reserved
    UINT16  Ps2Mouse  : 1;  //bit e - PS/2 Mouse
    UINT16  Res3    : 1;  //bit f - Reserved
  } DEV_FIELD;
} SIO_DEV_STATUS;


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
