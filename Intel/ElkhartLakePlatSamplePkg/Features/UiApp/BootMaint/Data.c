/** @file
  Define some data used for Boot Maint

@copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2016 Intel Corporation.

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

#include "BootMaint.h"

GLOBAL_REMOVE_IF_UNREFERENCED VOID                *mStartOpCodeHandle = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED VOID                *mEndOpCodeHandle = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_IFR_GUID_LABEL  *mStartLabel = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_IFR_GUID_LABEL  *mEndLabel = NULL;

GLOBAL_REMOVE_IF_UNREFERENCED STRING_DEPOSITORY   *FileOptionStrDepository = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED STRING_DEPOSITORY   *ConsoleOptionStrDepository;
GLOBAL_REMOVE_IF_UNREFERENCED STRING_DEPOSITORY   *BootOptionStrDepository;
GLOBAL_REMOVE_IF_UNREFERENCED STRING_DEPOSITORY   *BootOptionHelpStrDepository;
GLOBAL_REMOVE_IF_UNREFERENCED STRING_DEPOSITORY   *DriverOptionStrDepository;
GLOBAL_REMOVE_IF_UNREFERENCED STRING_DEPOSITORY   *DriverOptionHelpStrDepository;
GLOBAL_REMOVE_IF_UNREFERENCED STRING_DEPOSITORY   *TerminalStrDepository;

///
/// Terminal type string token storage
///
GLOBAL_REMOVE_IF_UNREFERENCED UINT16              TerminalType[] = {
  STRING_TOKEN(STR_COM_TYPE_0),
  STRING_TOKEN(STR_COM_TYPE_1),
  STRING_TOKEN(STR_COM_TYPE_2),
  STRING_TOKEN(STR_COM_TYPE_3),
};

///
/// Flow Control type string token storage
///
GLOBAL_REMOVE_IF_UNREFERENCED UINT16              mFlowControlType[2] = {
  STRING_TOKEN(STR_NONE_FLOW_CONTROL),
  STRING_TOKEN(STR_HARDWARE_FLOW_CONTROL)
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT32              mFlowControlValue[2] = {
  0,
  UART_FLOW_CONTROL_HARDWARE
};

///
/// Legacy resolution type string token storage
///
GLOBAL_REMOVE_IF_UNREFERENCED UINT16              mLegacyResolution[2] = {
  STRING_TOKEN(STR_LEGACY_RESOLUTION_85X24),
  STRING_TOKEN(STR_LEGACY_RESOLUTION_85X25)
};

///
/// File system selection menu
///
GLOBAL_REMOVE_IF_UNREFERENCED BM_MENU_OPTION      FsOptionMenu = {
  BM_MENU_OPTION_SIGNATURE,
  {NULL},
  0
};

///
/// Console Input Device Selection Menu
///
GLOBAL_REMOVE_IF_UNREFERENCED BM_MENU_OPTION      ConsoleInpMenu = {
  BM_MENU_OPTION_SIGNATURE,
  {NULL},
  0
};

///
/// Console Output Device Selection Menu
///
GLOBAL_REMOVE_IF_UNREFERENCED BM_MENU_OPTION      ConsoleOutMenu = {
  BM_MENU_OPTION_SIGNATURE,
  {NULL},
  0
};

///
/// Error Output Device Selection Menu
///
GLOBAL_REMOVE_IF_UNREFERENCED BM_MENU_OPTION      ConsoleErrMenu = {
  BM_MENU_OPTION_SIGNATURE,
  {NULL},
  0
};

///
/// Boot Option from variable Menu
///
GLOBAL_REMOVE_IF_UNREFERENCED BM_MENU_OPTION      BootOptionMenu = {
  BM_MENU_OPTION_SIGNATURE,
  {NULL},
  0
};

///
/// Driver Option from variable menu
///
GLOBAL_REMOVE_IF_UNREFERENCED BM_MENU_OPTION      DriverOptionMenu = {
  BM_MENU_OPTION_SIGNATURE,
  {NULL},
  0
};

///
/// Legacy FD Info from LegacyBios.GetBbsInfo()
///
GLOBAL_REMOVE_IF_UNREFERENCED BM_MENU_OPTION      LegacyFDMenu = {
  BM_MENU_OPTION_SIGNATURE,
  {NULL},
  0
};

///
/// Legacy HD Info from LegacyBios.GetBbsInfo()
///
GLOBAL_REMOVE_IF_UNREFERENCED BM_MENU_OPTION      LegacyHDMenu = {
  BM_MENU_OPTION_SIGNATURE,
  {NULL},
  0
};

///
/// Legacy CD Info from LegacyBios.GetBbsInfo()
///
GLOBAL_REMOVE_IF_UNREFERENCED BM_MENU_OPTION      LegacyCDMenu = {
  BM_MENU_OPTION_SIGNATURE,
  {NULL},
  0
};

///
/// Legacy NET Info from LegacyBios.GetBbsInfo()
///
GLOBAL_REMOVE_IF_UNREFERENCED BM_MENU_OPTION      LegacyNETMenu = {
  BM_MENU_OPTION_SIGNATURE,
  {NULL},
  0
};

///
/// Legacy NET Info from LegacyBios.GetBbsInfo()
///
GLOBAL_REMOVE_IF_UNREFERENCED BM_MENU_OPTION      LegacyBEVMenu = {
  BM_MENU_OPTION_SIGNATURE,
  {NULL},
  0
};

///
/// Files and sub-directories in current directory menu
///
GLOBAL_REMOVE_IF_UNREFERENCED BM_MENU_OPTION      DirectoryMenu = {
  BM_MENU_OPTION_SIGNATURE,
  {NULL},
  0
};

///
/// Handles in current system selection menu
///
GLOBAL_REMOVE_IF_UNREFERENCED BM_MENU_OPTION      DriverMenu = {
  BM_MENU_OPTION_SIGNATURE,
  {NULL},
  0
};

GLOBAL_REMOVE_IF_UNREFERENCED BM_MENU_OPTION      TerminalMenu = {
  BM_MENU_OPTION_SIGNATURE,
  {NULL},
  0
};

///
/// Value and string token correspondency for BaudRate
///
GLOBAL_REMOVE_IF_UNREFERENCED COM_ATTR            BaudRateList[19] = {
  {
    115200,
    STRING_TOKEN(STR_COM_BAUD_RATE_0)
  },
  {
    57600,
    STRING_TOKEN(STR_COM_BAUD_RATE_1)
  },
  {
    38400,
    STRING_TOKEN(STR_COM_BAUD_RATE_2)
  },
  {
    19200,
    STRING_TOKEN(STR_COM_BAUD_RATE_3)
  },
  {
    9600,
    STRING_TOKEN(STR_COM_BAUD_RATE_4)
  },
  {
    7200,
    STRING_TOKEN(STR_COM_BAUD_RATE_5)
  },
  {
    4800,
    STRING_TOKEN(STR_COM_BAUD_RATE_6)
  },
  {
    3600,
    STRING_TOKEN(STR_COM_BAUD_RATE_7)
  },
  {
    2400,
    STRING_TOKEN(STR_COM_BAUD_RATE_8)
  },
  {
    2000,
    STRING_TOKEN(STR_COM_BAUD_RATE_9)
  },
  {
    1800,
    STRING_TOKEN(STR_COM_BAUD_RATE_10)
  },
  {
    1200,
    STRING_TOKEN(STR_COM_BAUD_RATE_11)
  },
  {
    600,
    STRING_TOKEN(STR_COM_BAUD_RATE_12)
  },
  {
    300,
    STRING_TOKEN(STR_COM_BAUD_RATE_13)
  },
  {
    150,
    STRING_TOKEN(STR_COM_BAUD_RATE_14)
  },
  {
    134,
    STRING_TOKEN(STR_COM_BAUD_RATE_15)
  },
  {
    110,
    STRING_TOKEN(STR_COM_BAUD_RATE_16)
  },
  {
    75,
    STRING_TOKEN(STR_COM_BAUD_RATE_17)
  },
  {
    50,
    STRING_TOKEN(STR_COM_BAUD_RATE_18)
  }
};

///
/// Value and string token correspondency for DataBits
///
GLOBAL_REMOVE_IF_UNREFERENCED COM_ATTR            DataBitsList[4] = {
  {
    5,
    STRING_TOKEN(STR_COM_DATA_BITS_0)
  },
  {
    6,
    STRING_TOKEN(STR_COM_DATA_BITS_1)
  },
  {
    7,
    STRING_TOKEN(STR_COM_DATA_BITS_2)
  },
  {
    8,
    STRING_TOKEN(STR_COM_DATA_BITS_3)
  }
};

///
/// Value and string token correspondency for Parity
///
GLOBAL_REMOVE_IF_UNREFERENCED COM_ATTR            ParityList[5] = {
  {
    NoParity,
    STRING_TOKEN(STR_COM_PAR_0)
  },
  {
    EvenParity,
    STRING_TOKEN(STR_COM_PAR_1)
  },
  {
    OddParity,
    STRING_TOKEN(STR_COM_PAR_2)
  },
  {
    MarkParity,
    STRING_TOKEN(STR_COM_PAR_3)
  },
  {
    SpaceParity,
    STRING_TOKEN(STR_COM_PAR_4)
  }
};

///
/// Value and string token correspondency for Baudreate
///
GLOBAL_REMOVE_IF_UNREFERENCED COM_ATTR            StopBitsList[3] = {
  {
    OneStopBit,
    STRING_TOKEN(STR_COM_STOP_BITS_0)
  },
  {
    OneFiveStopBits,
    STRING_TOKEN(STR_COM_STOP_BITS_1)
  },
  {
    TwoStopBits,
    STRING_TOKEN(STR_COM_STOP_BITS_2)
  }
};

///
/// Guid for messaging path, used in Serial port setting.
///
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID            TerminalTypeGuid[4] = {
  DEVICE_PATH_MESSAGING_PC_ANSI,
  DEVICE_PATH_MESSAGING_VT_100,
  DEVICE_PATH_MESSAGING_VT_100_PLUS,
  DEVICE_PATH_MESSAGING_VT_UTF8
};
