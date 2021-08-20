/** @file
  Hardware Monitor implementation.

@copyright
  Copyright (c) 2013-2015, Intel Corporation. All rights reserved.
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor. This file may be modified by the user, subject to
  the additional terms of the license agreement.
**/

/*++

Module Name:
  HwMonInit.c

Abstract:
  This file contains the actual Hardware Monitor implementation. It contains
  the hardware monitor initialization code and auxiliary procedures,  as well
  as a huge configuration table. There are enough build option statements
  that the most common configuration will not require any change to the table
  (all is done through file Config.h).

  Because ISA IO operations are slow, this code implements several
  optimizations for speed minimizing the number of required IO operations and
  executing many other CPU and memory operations between IO cycles:
  1) Two consecutive ISA IOs will cause a delay in that the second IO will
     only execute once the first is completed, so the time spent in CPU and
     memory operations disappear within the required delay between ISA IO
     operations.
  2) Some registers have bits belonging to different operations and could
     appear two or more times within the initial register table. So executing
     all operations in memory and only executing IO write operations once all
     values have been defined minimize the number of IOs.
  3) Registers are organized in banks, so setting all registers of a
     particular bank before moving to the next bank minimizes the number of
     bank IO operations.

--*/

#include <Library/TimerLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include "Config.h"
#include "HwMonInit.h"
#include "NctHwMonRegs.h"

/**
  This table is grouped by functionality being programmed, and will swing
  through several banks. The HWMON initialization code will pass through it
  several times, one for each bank. This table will change size based in
  which monitoring or fan control method is enabled. Therefore, the table
  needs a recognizable terminator. As there is only banks 0-7, requesting
  bank 8 will act as the terminator.

  Each table line is Bank, Register, Mask, Value. Values are defined in
  file config.h, which should be modified for a particular hardware monitor
  configuration. Two boards with the same configuration require no changes.

  Mask values should have bits set for bits that will be preserved from the
  current register value, and bits cleared where new value will be written.
  Any particular bit must not be set both within Mask and Value fields, if
  this happens the final result will have the particular bit set.

  Because IO consume time, Mask have an added function. If a mask is set
  to 0x00, this means that no register bit needs to be preserved and
  therefore there is no initial read of the particular register to preserve
  some required bits.

  Notice that some register are placed twice in the table, the first time
  with a mask of 0x00. This is for clarity purpose only, and the end
  result is a single write operation with the bytewise OR of the 2 values.
**/

HWMON_REGISTER_INFO  HwMonInitialRegister[] = {
  //
  // Disable monitoring before starting to program HWMON. Then program
  // FAN PWM frequencies.
  //
  {0x00, 0x40, 0x04, SIO_HWMON_CONFIGURATION_START              },
  {0x00, 0x00, 0x00, SIO_HWMON_SYS_FAN_PWM_FREQ                 },
  {0x00, 0x02, 0x00, SIO_HWMON_CPU_FAN_PWM_FREQ                 },
  {0x00, 0x10, 0x00, SIO_HWMON_AUX_FAN_PWM_FREQ                 },

  //
  // Create mask inputs in cache to selectively en/disable some interrupts.
  //
  {0x00, 0x43, 0x00, SIO_SMI_ALERT_MASK1                        },
  {0x00, 0x44, 0x00, SIO_SMI_ALERT_MASK2                        },
  {0x00, 0x46, 0x00, SIO_SMI_ALERT_MASK3                        },
  {0x04, 0x51, 0x00, SIO_SMI_ALERT_MASK4                        },
  {0x00, 0x4C, 0x00, SIO_HWMON_OVT_CONTROL                      },

  //
  // Set common values.
  //
  {0x00, 0x48, 0x00, HWMON_SMBUS_ADDRESS_REG_VAL                },
  {0x00, 0x5d, 0x00, HWMON_B0_R5D                               },
  {0x00, 0x5e, 0x00, SIO_HWMON_CURRENT_SENSOR_TEMP              },
  {0x00, 0xae, 0x00, SIO_HWMON_PECI_ENABLE                      },

#ifdef SIO_HWMON_SYSFAN_THERMAL_CRUISE
  {0x00, 0x04, 0x00, SIO_HWMON_SYSFAN_METHOD                    },
  {0x01, 0x00, 0x00, (0x80 | SIO_HWMON_TEMP_SEL_SYSTIN)         },
  {0x01, 0x01, 0x00, HWMON_SYS_FAN_TARGET_TEMP                  },
  {0x01, 0x03, 0x00, HWMON_SYS_FAN_STEP_UP_TIME                 },
  {0x01, 0x04, 0x00, HWMON_SYS_FAN_STEP_DOWN_TIME               },
  {0x01, 0x05, 0x00, HWMON_SYS_STOP_FAN_SPEED                   },
  {0x01, 0x06, 0x00, HWMON_SYS_START_FAN_SPEED                  },
  {0x01, 0x07, 0x00, HWMON_SYS_STOP_FAN_TIME                    },
  {0x01, 0x31, 0x00, HWMON_SYS_FAN_STYLE                        },
  {0x01, 0x0c, 0x00, HWMON_SYS_FAN_TEMP_TOLERANCE_H             },
  {0x01, 0x02, 0x00, HWMON_SYS_FAN_TEMP_TOLERANCE_L             },
  {0x01, 0x02, 0x0f, HWMON_FAN_CONTROL_THERMAL_CR               },
#endif SIO_HWMON_SYSFAN_THERMAL_CRUISE

#ifdef SIO_HWMON_SYSFAN_SMART_FAN
  {0x00, 0x04, 0x00, SIO_HWMON_SYSFAN_METHOD                    },
  {0x01, 0x00, 0x00, (0x80 | SIO_HWMON_TEMP_SEL_SYSTIN)         },
  {0x01, 0x21, 0x00, HWMON_SYS_FAN_SF4_T1                       },
  {0x01, 0x22, 0x00, HWMON_SYS_FAN_SF4_T2                       },
  {0x01, 0x23, 0x00, HWMON_SYS_FAN_SF4_T3                       },
  {0x01, 0x24, 0x00, HWMON_SYS_FAN_SF4_T4                       },
  {0x01, 0x27, 0x00, HWMON_SYS_FAN_SF4_PWM1                     },
  {0x01, 0x28, 0x00, HWMON_SYS_FAN_SF4_PWM2                     },
  {0x01, 0x29, 0x00, HWMON_SYS_FAN_SF4_PWM3                     },
  {0x01, 0x2a, 0x00, HWMON_SYS_FAN_SF4_PWM4                     },
  {0x01, 0x35, 0x00, HWMON_SYS_FAN_CRITICAL_TEMP                },
  {0x01, 0x38, 0x00, HWMON_SYS_FAN_CRITICAL_TOLER               },
  {0x01, 0x31, 0x00, HWMON_SYS_FAN_STYLE                        },
  {0x01, 0x0c, 0x00, HWMON_SYS_FAN_TEMP_TOLERANCE_H             },
  {0x01, 0x02, 0x00, HWMON_SYS_FAN_TEMP_TOLERANCE_L             },
  {0x01, 0x02, 0x0f, HWMON_FAN_CONTROL_SMART_FAN                },
#endif SIO_HWMON_SYSFAN_SMART_FAN

#ifdef SIO_HWMON_CPUFAN_THERMAL_CRUISE
  {0x02, 0x00, 0x60, (0x80 | SIO_HWMON_TEMP_SEL_CPU_TIN)        },
  {0x02, 0x01, 0x00, HWMON_CPU_FAN_TARGET_TEMP                  },
  {0x02, 0x03, 0x00, HWMON_CPU_FAN_STEP_UP_TIME                 },
  {0x02, 0x04, 0x00, HWMON_CPU_FAN_STEP_DOWN_TIME               },
  {0x02, 0x05, 0x00, HWMON_CPU_STOP_FAN_SPEED                   },
  {0x02, 0x06, 0x00, HWMON_CPU_START_FAN_SPEED                  },
  {0x02, 0x07, 0x00, HWMON_CPU_STOP_FAN_TIME                    },
  {0x02, 0x31, 0x00, HWMON_CPU_FAN_STYLE                        },
  {0x02, 0x0c, 0x00, HWMON_CPU_FAN_TEMP_TOLERANCE_H             },
  {0x02, 0x02, 0x00, HWMON_CPU_FAN_TEMP_TOLERANCE_L             },
  {0x02, 0x02, 0x0f, HWMON_FAN_CONTROL_THERMAL_CR               },
#endif SIO_HWMON_CPUFAN_THERMAL_CRUISE

#ifdef SIO_HWMON_CPUFAN_SMART_FAN
  {0x02, 0x00, 0x60, (0x80 | SIO_HWMON_TEMP_SEL_CPU_TIN)        },
  {0x02, 0x21, 0x00, HWMON_CPU_FAN_SF4_T1                       },
  {0x02, 0x22, 0x00, HWMON_CPU_FAN_SF4_T2                       },
  {0x02, 0x23, 0x00, HWMON_CPU_FAN_SF4_T3                       },
  {0x02, 0x24, 0x00, HWMON_CPU_FAN_SF4_T4                       },
  {0x02, 0x27, 0x00, HWMON_CPU_FAN_SF4_PWM1                     },
  {0x02, 0x28, 0x00, HWMON_CPU_FAN_SF4_PWM2                     },
  {0x02, 0x29, 0x00, HWMON_CPU_FAN_SF4_PWM3                     },
  {0x02, 0x2a, 0x00, HWMON_CPU_FAN_SF4_PWM4                     },
  {0x02, 0x35, 0x00, HWMON_CPU_FAN_CRITICAL_TEMP                },
  {0x02, 0x38, 0x00, HWMON_CPU_FAN_CRITICAL_TOLER               },
  {0x02, 0x31, 0x00, HWMON_CPU_FAN_STYLE                        },
  {0x02, 0x0c, 0x00, HWMON_CPU_FAN_TEMP_TOLERANCE_H             },
  {0x02, 0x02, 0x00, HWMON_CPU_FAN_TEMP_TOLERANCE_L             },
  {0x02, 0x02, 0x0f, HWMON_FAN_CONTROL_SMART_FAN                },
#endif SIO_HWMON_CPUFAN_SMART_FAN

#ifdef SIO_HWMON_AUXFAN_THERMAL_CRUISE
  {0x03, 0x00, 0x60, (0x80 | SIO_HWMON_TEMP_SEL_AUX_TIN)        },
  {0x03, 0x01, 0x00, HWMON_AUX_FAN_TARGET_TEMP                  },
  {0x03, 0x03, 0x00, HWMON_AUX_FAN_STEP_UP_TIME                 },
  {0x03, 0x04, 0x00, HWMON_AUX_FAN_STEP_DOWN_TIME               },
  {0x03, 0x05, 0x00, HWMON_AUX_STOP_FAN_SPEED                   },
  {0x03, 0x06, 0x00, HWMON_AUX_START_FAN_SPEED                  },
  {0x03, 0x07, 0x00, HWMON_AUX_STOP_FAN_TIME                    },
  {0x03, 0x31, 0x00, HWMON_AUX_FAN_STYLE                        },
  {0x03, 0x0c, 0x00, HWMON_AUX_FAN_TEMP_TOLERANCE_H             },
  {0x03, 0x02, 0x00, HWMON_AUX_FAN_TEMP_TOLERANCE_L             },
  {0x03, 0x02, 0x0f, HWMON_FAN_CONTROL_THERMAL_CR               },
#endif SIO_HWMON_AUXFAN_THERMAL_CRUISE

#ifdef SIO_HWMON_AUXFAN_SMART_FAN
  {0x03, 0x00, 0x60, (0x80 | SIO_HWMON_TEMP_SEL_AUX_TIN)        },
  {0x03, 0x21, 0x00, HWMON_AUX_FAN_SF4_T1                       },
  {0x03, 0x22, 0x00, HWMON_AUX_FAN_SF4_T2                       },
  {0x03, 0x23, 0x00, HWMON_AUX_FAN_SF4_T3                       },
  {0x03, 0x24, 0x00, HWMON_AUX_FAN_SF4_T4                       },
  {0x03, 0x27, 0x00, HWMON_AUX_FAN_SF4_PWM1                     },
  {0x03, 0x28, 0x00, HWMON_AUX_FAN_SF4_PWM2                     },
  {0x03, 0x29, 0x00, HWMON_AUX_FAN_SF4_PWM3                     },
  {0x03, 0x2a, 0x00, HWMON_AUX_FAN_SF4_PWM4                     },
  {0x03, 0x35, 0x00, HWMON_AUX_FAN_CRITICAL_TEMP                },
  {0x03, 0x38, 0x00, HWMON_AUX_FAN_CRITICAL_TOLER               },
  {0x03, 0x31, 0x00, HWMON_AUX_FAN_STYLE                        },
  {0x03, 0x0c, 0x00, HWMON_AUX_FAN_TEMP_TOLERANCE_H             },
  {0x03, 0x02, 0x00, HWMON_AUX_FAN_TEMP_TOLERANCE_L             },
  {0x03, 0x02, 0x0f, HWMON_FAN_CONTROL_SMART_FAN                },
#endif SIO_HWMON_AUXFAN_SMART_FAN

#ifdef SIO_HWMON_MONITOR_SYS_FAN
  {0x06, 0x3a, 0x00, HWMON_SYSFAN_COUNT_LIMIT                   },
#endif // SIO_HWMON_MONITOR_SYS_FAN

#ifdef SIO_HWMON_MONITOR_CPU_FAN
  {0x06, 0x3c, 0x00, HWMON_CPUFAN_COUNT_LIMIT                   },
#endif // SIO_HWMON_MONITOR_CPU_FAN

#ifdef SIO_HWMON_MONITOR_AUX_FAN0
  {0x06, 0x3e, 0x00, HWMON_AUXFAN_COUNT_LIMIT                   },
#endif // SIO_HWMON_MONITOR_AUX_FAN0

#ifdef SIO_HWMON_MONITOR_OVT1
  {0x06, 0x21, 0x00, SIO_HWMON_TEMP_SEL_SYSTIN                  },
  {0x00, 0x3a, 0x00, HWMON_SYS_FAN_CRITICAL_TEMP                },
  {0x00, 0x39, 0x00, HWMON_SYS_OVT_TEMPERATURE                  },
  {0x00, 0x18, 0x00, 0x00                                       },
#else // SIO_HWMON_MONITOR_OVT1
  {0x00, 0x18, 0x00, 0x41},
#endif // SIO_HWMON_MONITOR_OVT1

#ifdef SIO_HWMON_MONITOR_OVT2
  {0x06, 0x22, 0x00, SIO_HWMON_TEMP_SEL_CPU_TIN                 },
  {0x01, 0x53, 0x00, HWMON_CPU_FAN_CRITICAL_TEMP                },
  {0x01, 0x55, 0x00, HWMON_CPU_OVT_TEMPERATURE                  },
  {0x01, 0x52, 0x00, HWMON_CPU_OVT_CONTROL                      },
  {0x00, 0x4C, 0xf7, 0x00                                       },
#else // SIO_HWMON_MONITOR_OVT2
  {0x01, 0x52, 0x00, 0x01                                       },
  {0x00, 0x4C, 0xf7, 0x08                                       },
#endif // SIO_HWMON_MONITOR_OVT2

#ifdef SIO_HWMON_MONITOR_OVT3
  {0x06, 0x23, 0x00, SIO_HWMON_TEMP_SEL_AUX_TIN                 },
  {0x02, 0x53, 0x00, HWMON_AUX_FAN_CRITICAL_TEMP                },
  {0x02, 0x55, 0x00, HWMON_AUX_OVT_TEMPERATURE                  },
  {0x02, 0x52, 0x00, HWMON_AUX_OVT_CONTROL                      },
  {0x00, 0x4C, 0xef, 0x00                                       },
#else // SIO_HWMON_MONITOR_OVT3
  {0x02, 0x52, 0x00, 0x01                                       },
  {0x00, 0x4C, 0xef, 0x10                                       },
#endif // SIO_HWMON_MONITOR_OVT3

#ifdef SIO_HWMON_MONITOR_3VCC
  {0x00, 0x31, 0x00, HWMON_MONITOR_3VCC_HIGH                    },
  {0x00, 0x32, 0x00, HWMON_MONITOR_3VCC_LOW                     },
#endif // SIO_HWMON_MONITOR_3VCC

#ifdef SIO_HWMON_MONITOR_AVCC
  {0x00, 0x2f, 0x00, HWMON_MONITOR_AVCC_HIGH                    },
  {0x00, 0x30, 0x00, HWMON_MONITOR_AVCC_LOW                     },
#endif // SIO_HWMON_MONITOR_AVCC

#ifdef SIO_HWMON_MONITOR_CPU_VCORE
  {0x00, 0x2b, 0x00, HWMON_MONITOR_CPU_VCORE_HIGH               },
  {0x00, 0x2c, 0x00, HWMON_MONITOR_CPU_VCORE_LOW                },
#endif // SIO_HWMON_MONITOR_CPU_VCORE

#ifdef SIO_HWMON_MONITOR_VIN0
  {0x00, 0x2d, 0x00, HWMON_MONITOR_VIN0_HIGH                    },
  {0x00, 0x2e, 0x00, HWMON_MONITOR_VIN0_LOW                     },
#endif // SIO_HWMON_MONITOR_VIN0

#ifdef SIO_HWMON_MONITOR_VIN1
  {0x00, 0x33, 0x00, HWMON_MONITOR_VIN1_HIGH                    },
  {0x00, 0x34, 0x00, HWMON_MONITOR_VIN1_LOW                     },
#endif // SIO_HWMON_MONITOR_VIN1

#ifdef SIO_HWMON_MONITOR_VIN2
  {0x00, 0x35, 0x00, HWMON_MONITOR_VIN2_HIGH                    },
  {0x00, 0x36, 0x00, HWMON_MONITOR_VIN2_LOW                     },
#endif // SIO_HWMON_MONITOR_VIN2

#ifdef SIO_HWMON_MONITOR_VIN3
  {0x00, 0x37, 0x00, HWMON_MONITOR_VIN3_HIGH                    },
  {0x00, 0x38, 0x00, HWMON_MONITOR_VIN3_LOW                     },
#endif // SIO_HWMON_MONITOR_VIN3

  {0x06, 0x44, 0x00, SIO_HWMON_SYS_FAN_PULSE                    },
  {0x06, 0x45, 0x00, SIO_HWMON_CPU_FAN_PULSE                    },
  {0x06, 0x46, 0x00, SIO_HWMON_AUX_FAN_PULSE                    },
  {0x07, 0x09, 0x00, SIO_PECI_CRITICAL_TEMP                     },
  {0x07, 0x03, 0x00, SIO_PECI_AGENT_CONFIG                      },
  {0x07, 0x02, 0x00, SIO_PECI_TIMING_CONFIG                     },
  {0x07, 0x01, 0x00, SIO_PECI_ENABLE                            },

//
// Use bank 8 to indicate table end.
//
  {0x08, 0x00, 0x00, 0x00}
};

//
// Defining values that will be used when creating the StatusClearTable.
//
#ifdef  SIO_HWMON_MONITOR_OVT2
#define STS1_BIT5               0x20
#else
#define STS1_BIT5               0x00
#endif // SIO_HWMON_MONITOR_OVT2

#ifdef  SIO_HWMON_MONITOR_OVT1
#define STS1_BIT4               0x10
#else
#define STS1_BIT4               0x00
#endif // SIO_HWMON_MONITOR_OVT1

#ifdef  SIO_HWMON_MONITOR_3VCC
#define STS1_BIT3               0x08
#else
#define STS1_BIT3               0x00
#endif // SIO_HWMON_MONITOR_3VCC

#ifdef  SIO_HWMON_MONITOR_AVCC
#define STS1_BIT2               0x04
#else
#define STS1_BIT2               0x00
#endif // SIO_HWMON_MONITOR_AVCC

#ifdef  SIO_HWMON_MONITOR_VIN0
#define STS1_BIT1               0x02
#else
#define STS1_BIT1               0x00
#endif // SIO_HWMON_MONITOR_VIN0

#ifdef  SIO_HWMON_MONITOR_CPU_VCORE
#define STS1_BIT0               0x01
#else
#define STS1_BIT0               0x00
#endif // SIO_HWMON_MONITOR_CPU_VCORE

#define STATUS1_MASK  STS1_BIT4 | STS1_BIT5 | STS1_BIT3 | STS1_BIT2 | STS1_BIT1 | STS1_BIT0

#ifdef  SIO_HWMON_MONITOR_CASE_OPEN1
#define STS2_BIT6               0x40
#else
#define STS2_BIT6               0x00
#endif // SIO_HWMON_MONITOR_CASE_OPEN1

#ifdef  SIO_HWMON_MONITOR_OVT3
#define STS2_BIT5               0x20
#else
#define STS2_BIT5               0x00
#endif // SIO_HWMON_MONITOR_OVT3

#ifdef  SIO_HWMON_MONITOR_CASE_OPEN0
#define STS2_BIT4               0x10
#else
#define STS2_BIT4               0x00
#endif // SIO_HWMON_MONITOR_CASE_OPEN0

#ifdef  SIO_HWMON_MONITOR_VIN2
#define STS2_BIT2               0x04
#else
#define STS2_BIT2               0x00
#endif // SIO_HWMON_MONITOR_VIN2

#ifdef  SIO_HWMON_MONITOR_VIN3
#define STS2_BIT1               0x02
#else
#define STS2_BIT1               0x00
#endif // SIO_HWMON_MONITOR_VIN3

#ifdef  SIO_HWMON_MONITOR_VIN1
#define STS2_BIT0               0x01
#else
#define STS2_BIT0               0x00
#endif // SIO_HWMON_MONITOR_VIN1

#define STATUS2_MASK  STS2_BIT6 | STS2_BIT5 | STS2_BIT4 | STS2_BIT2 | STS2_BIT1 | STS2_BIT0

#ifdef  SIO_HWMON_MONITOR_AUX_FAN0
#define STS4_BIT5               0x20
#else
#define STS4_BIT5               0x00
#endif // SIO_HWMON_MONITOR_AUX_FAN0

#ifdef  SIO_HWMON_MONITOR_CPU_FAN
#define STS4_BIT4               0x10
#else
#define STS4_BIT4               0x00
#endif // SIO_HWMON_MONITOR_CPU_FAN

#ifdef  SIO_HWMON_MONITOR_SYS_FAN
#define STS4_BIT3               0x08
#else
#define STS4_BIT3               0x00
#endif // SIO_HWMON_MONITOR_SYS_FAN

#define STATUS4_MASK  STS4_BIT5 | STS4_BIT4 | STS4_BIT3

//
// Table used to verify that all status bits are cleared before continuing.
// Bits are cleared simply by reading the status register, they must be
// cleared before AMT starts.
//
HWMON_REGISTER_PAIR StatusClearTable[3] = {
  {0x41, STATUS1_MASK},
  {0x42, STATUS2_MASK},
  {0x45, STATUS4_MASK},
};

NCT6776F_HWMON_PROTOCOL *ProtocolPtr = NULL;

UINT8
HwMonReadRegister (
  IN  UINT8     Register
  )
{
  UINT8 Value;

  ProtocolPtr->ReadMonitorRegister (Register, &Value);
  return Value;
}

/**
  This procedure locates a particular register (index) within the register
  cache. If found, it returns the index within the cache where it was found,
  if not found it returns the next index within the cache in order to create
  a new entry at the end of the cache.

  @param[in]  RegisterCache   Pointer to the cache.
  @param[in]  DesiredPort     The register being searched.
  @param[in]  RegisterCount   Total number of registers currently stored in cache.
  @param[out] index           Pointer to memory used to return cache index
                              where port structure is stored.

  @retval BOOLEAN             indicates if the register was found in the cache.
**/
BOOLEAN
HwMonLocateRegister (
  IN  SIO_REGISTER_SETTING  *RegisterCache,
  OUT UINT8                 *Index,
  IN  UINT8                 DesiredPort,
  IN  UINT8                 RegisterCount
  )
{
  BOOLEAN Found = FALSE;
  UINT8 i;

  //
  // Set index value to end of cache, just in case if register not found.
  //
  *Index = RegisterCount;
  if (RegisterCount == 0) {
    return FALSE;
  }

  //
  // Search the registers in memory for a match.
  //
  for (i=0; i<RegisterCount; i++) {
    if (RegisterCache[i].Port == DesiredPort) {
      Found = TRUE;

      //
      // Return the index of the register that matched desired port.
      //
      *Index = i;
      break;
    }
  }
  return Found;
}

/**
  This procedure returns a register value. If the register already exists in
  the cache table, it returns the current value within the table else it reads
  the physical register, creates an entry within the cache and returns the
  value read.
  The Mask input acts as a hint. If Mask is set to 0, it indicates that it's
  not necessary to read the port, as all bits will be changed. Instead, if
  the register is not yet in the cache then an entry with value of 0 will be
  created without actually reading the register (Saves 2 LPC IO times).

  @param[in]  RegisterCache   Pointer to the cache.
  @param[in]  DesiredPort     The register being searched.
  @param[in]  RegisterCount   Total number of registers currently stored in cache.
  @param[in]  Mask            indicates bits that must be cleared because they'll be changed.

  @retval Value               Current value of a particular register within
                              the cache or in physical register, with bits
                              that'll be changed in current operation cleared.

**/
UINT8
HwMonReturnRegisterValue (
  IN  SIO_REGISTER_SETTING  *RegisterCache,
  IN  OUT UINT8             *RegisterCount,
  IN  UINT8                 DesiredPort,
  IN  UINT8                 Mask
  )
{
  UINT8 Index;
  UINT8 Value;

  //
  // Try to locate the register within the cache. Read value if found.
  //
  if (HwMonLocateRegister (RegisterCache,
                           &Index,
                           DesiredPort,
                           *RegisterCount)) {
    Value = RegisterCache[Index].Value;
  } else {

    //
    // Register not found, save register and value at the end of current
    // valid cache.
    //
    Index = *RegisterCount;

    //
    // Verify the mask hint, if 0 set Value to 0 else do the actual read.
    //
    if (Mask == 0) {
      Value = 0;
    } else {
      Value = HwMonReadRegister (DesiredPort);
    }

    //
    // Save port and value into memory cache.
    //
    RegisterCache[Index].Port = DesiredPort;
    RegisterCache[Index].Value = Value;

    //
    // Increment index and store it back as size of valid cache.
    //
    Index += 1;
    *RegisterCount = Index;
  }
  return Value;
}

/**
  Record the 8-bit register value into the cache.

  @param[in]  RegisterCache   Pointer to the cache.
  @param[in]  RegisterCount   Total number of registers currently stored in cache.
  @param[in]  DesiredPort     The register associated with the value.
  @param[in]  Value           The new value for the register.
**/
VOID
HwMonSaveRegisterValue (
  IN  SIO_REGISTER_SETTING  *RegisterCache,
  IN  OUT UINT8             *RegisterCount,
  IN  UINT8                 DesiredPort,
  IN  UINT8                 Value
  )
{
  UINT8 Index;

  //
  // Locate the register within the cache. As this procedure is only called
  // after a HwMonReturnRegisterValue for the same register, the register
  // image will always be present in memory (HwMonReturnRegisterValue creates
  // a new image if there was none before).
  //
  HwMonLocateRegister (RegisterCache, &Index, DesiredPort, *RegisterCount);
  RegisterCache[Index].Value = Value; // save new value in cache.
}

/**
  This procedure scans the input table for each bank and creates a cache table
  of end values. Once the table was scanned for a particular bank, then it
  writes the final values into the SIO while saving the operation into the S3
  script table.

  @param[in]  HwMonProtocol  Pointer to SIO published protocol.
**/

VOID
HwMonInit (
  IN  NCT6776F_HWMON_PROTOCOL *HwMonProtocol
  )
{
  SIO_REGISTER_SETTING    Cache[200];
  HWMON_REGISTER_INFO    *SettingsPtr;
  UINT32                  T;
  UINT8                   CurrentBank;
  UINT8                   RegisterCount;
  UINT8                   Value;
  UINT8                   i;

  DEBUG ((DEBUG_INFO, "HwMonInit - Start\n"));
  //
  // Transfer protocol address to be used by HwMonReadRegister.
  //
  ProtocolPtr = HwMonProtocol;

  //
  // Scan table for each bank: change to bank, fill cache table and send
  // values out to HwMon.
  //
  for (CurrentBank=0; CurrentBank<8; CurrentBank++) {
    //
    // Restart register cache for current bank.
    //
    for (i=0; i < 200; i++) {
      Cache[i].Port = 0;
      Cache[i].Value = 0;
    }
    RegisterCount = 0;
    SettingsPtr = HwMonInitialRegister;

    //
    // Now scan the table searching for bank matches.
    //
    while (SettingsPtr->Bank < 8) {
      if (SettingsPtr->Bank == CurrentBank) {
        //
        // Bank match, retrieve the register value from cache and generate
        // new value. Then replace value in the cache.
        //
        Value = HwMonReturnRegisterValue (Cache,
                                          &RegisterCount,
                                          SettingsPtr->Register,
                                          SettingsPtr->Mask);

        //
        // Clear bits that will be changed and write new value to these bits.
        //
        Value &= SettingsPtr->Mask;
        Value |= SettingsPtr->Value;

        //
        // Now save new value to cache.
        //
        HwMonSaveRegisterValue (Cache,
                                &RegisterCount,
                                SettingsPtr->Register,
                                Value);
      }
      SettingsPtr++;
    }

    //
    // Scan completed, write the final values into the SIO.
    //
    HwMonProtocol->SetMonitorBankValues((HWMON_REGISTER_PAIR*) Cache,
                                         CurrentBank,
                                         RegisterCount
                                       );
  }

  //
  // Return to bank 0 and enable SMI and monitoring.
  //
  DEBUG ((DEBUG_INFO, "Enable SMI \n"));
  Cache[0].Port = 0x40;
  Cache[0].Value = SIO_HWMON_CONFIGURATION_END;
  HwMonProtocol->SetMonitorBankValues((HWMON_REGISTER_PAIR*) Cache,
                                       0,
                                       1
                                     );

  //
  // Read the Hardware Monitor status in order to clear them before AMT
  // starts to read them through SMBUS. Notice that some bits in status 1 & 2
  // take some time to settle. So a delay is needed.
  // To do: Delay code changed, some adjustment through trial and error needed.
  //
  //MicroSecondDelay (10000); //this value might change.
  for (T=0; T<100000; T++) {
      IoWrite8 (0x82, HwMonReadRegister (0x41));
  }
  for (i=0; i<3; i++) {
    Value = HwMonReadRegister (StatusClearTable[i].Register);
    Value &= StatusClearTable[i].Value;
    while (0 != Value) {
      Value = HwMonReadRegister (StatusClearTable[i].Register);
      Value &= StatusClearTable[i].Value;
    }
  }
  DEBUG ((DEBUG_INFO, "HwMonInit - End\n"));
}