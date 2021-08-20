#ifndef __MrcMcRegisterStructIclCxxx_h__
#define __MrcMcRegisterStructIclCxxx_h__
/** @file
  This file was automatically generated. Modify at your own risk.
  Note that no error checking is done in these functions so ensure that the correct values are passed.

@copyright
  Copyright (c) 2010 - 2017 Intel Corporation. All rights reserved
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
    UINT32 Control_Policy_LO                       :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_ACCESS_CONTROL_POLICY_LO_STRUCT;

typedef union {
  struct {
    UINT32 Control_Policy_HI                       :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_ACCESS_CONTROL_POLICY_HI_STRUCT;

typedef union {
  struct {
    UINT32 Read_Policy_LO                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_ACCESS_READ_POLICY_LO_STRUCT;

typedef union {
  struct {
    UINT32 Read_Policy_HI                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_ACCESS_READ_POLICY_HI_STRUCT;

typedef union {
  struct {
    UINT32 Write_Policy_LO                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_ACCESS_WRITE_POLICY_LO_STRUCT;

typedef union {
  struct {
    UINT32 Write_Policy_HI                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_ACCESS_WRITE_POLICY_HI_STRUCT;

typedef union {
  struct {
    UINT32 DUMMYLow                                :  32;  // Bits 31:0
    UINT32 DUMMYHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CPGC_P_DUMMY_STRUCT;

typedef union {
  struct {
    UINT32 Dpat0_or_Err0                           :  1;  // Bits 0:0
    UINT32 Cmd0_or_Dpat1_or_Exe0                   :  2;  // Bits 2:1
    UINT32 Err1_or_Cmd1_or_Exe1                    :  2;  // Bits 4:3
    UINT32 Cmd0_grp_Sel                            :  2;  // Bits 6:5
    UINT32 Cmd1_grp_Sel                            :  2;  // Bits 8:7
    UINT32 Dpat0_grp_Sel                           :  2;  // Bits 10:9
    UINT32 Dpat1_grp_Sel                           :  2;  // Bits 12:11
    UINT32 Err0_grp_Sel                            :  2;  // Bits 14:13
    UINT32 Err1_grp_Sel                            :  2;  // Bits 16:15
    UINT32 Exe0_grp_Sel                            :  2;  // Bits 18:17
    UINT32 Exe1_grp_Sel                            :  2;  // Bits 20:19
    UINT32                                         :  11;  // Bits 31:21
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_VISA_MUX_SEL_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_CREDITS_INIT                     :  8;  // Bits 7:0
    UINT32 RSP_CREDITS_INIT                        :  8;  // Bits 15:8
    UINT32 RD_WR_CREDITS_INIT                      :  8;  // Bits 23:16
    UINT32 CREDITS_CONFIG_DONE                     :  1;  // Bits 24:24
    UINT32 RD_WR_CREDITS_OVERRIDE                  :  1;  // Bits 25:25
    UINT32 FORCE_ISM_ACTIVE                        :  1;  // Bits 26:26
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_CREDIT_CFG_STRUCT;

typedef union {
  struct {
    UINT32 DUMMYLow                                :  32;  // Bits 31:0
    UINT32 DUMMYHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CPGC_V_DUMMY_STRUCT;

typedef union {
  struct {
    UINT32 Address_Decode_Rotate_Repeats           :  6;  // Bits 5:0
    UINT32                                         :  18;  // Bits 23:6
    UINT32 Column_Addr_Invert_Select               :  2;  // Bits 25:24
    UINT32 Row_Addr_Invert_Select                  :  2;  // Bits 27:26
    UINT32 Bank_Addr_Invert_Select                 :  2;  // Bits 29:28
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_ADDRESS_CONTROL_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ADDRESS_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ADDRESS_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ADDRESS_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ADDRESS_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_DATA_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_DATA_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_DATA_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_DATA_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT32 Data_Select_Rotation_Repeats            :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_DATA_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Address_Decode_Rotate_Repeats_Current   :  6;  // Bits 5:0
    UINT32                                         :  10;  // Bits 15:6
    UINT32 Data_Select_Rotation_Repeats_Current    :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_ADDRESS_DATA_STATUS_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_1_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_2_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_3_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_4_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_5_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_6_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_7_STRUCT;

typedef union {
  struct {
    UINT32 Wait_Timer_Current                      :  16;  // Bits 15:0
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_ALGORITHM_WAIT_COUNT_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Wait_Time                               :  16;  // Bits 15:0
    UINT32                                         :  4;  // Bits 19:16
    UINT32 Timer                                   :  4;  // Bits 23:20
    UINT32 Wait_Clock_Frequency                    :  2;  // Bits 25:24
    UINT32                                         :  4;  // Bits 29:26
    UINT32 Select_Event                            :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Base_Repeats                            :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_BASE_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Base_Repeats_Current                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_BASE_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Base_Col_Repeats                        :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_BASE_COL_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Block_Repeats                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_BLOCK_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Block_Repeats_Current                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_BLOCK_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_8_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_9_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_10_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_11_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_12_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_13_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_14_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_15_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_16_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_17_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_18_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_19_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_20_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_21_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_22_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_23_STRUCT;

typedef union {
  struct {
    UINT32 Hammer_Repeats                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_HAMMER_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Hammer_Repeats_Current                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_HAMMER_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_8_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_9_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_10_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_11_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_12_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_13_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_14_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_15_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_8_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_9_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_10_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_11_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Repeats                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_OFFSET_REPEATS_0_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Repeats                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_OFFSET_REPEATS_1_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Repeats_Current                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_OFFSET_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Low_Row                                 :  18;  // Bits 17:0
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_REGION_LOW_ROW_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Low_Col                                 :  9;  // Bits 10:2
    UINT32                                         :  21;  // Bits 31:11
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_REGION_LOW_COL_STRUCT;

typedef union {
  struct {
    UINT32                                         :  5;  // Bits 4:0
    UINT32 Block_Origin_Col_Current                :  10;  // Bits 14:5
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_BLOCK_ORIGIN_COL_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Block_Origin_Row_Current                :  18;  // Bits 17:0
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_BLOCK_ORIGIN_ROW_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32                                         :  5;  // Bits 4:0
    UINT32 Base_Col_Current                        :  10;  // Bits 14:5
    UINT32                                         :  9;  // Bits 23:15
    UINT32 Base_Rank_Current                       :  5;  // Bits 28:24
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_BASE_ADDRESS_COL_RANK_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Base_Row_Current                        :  18;  // Bits 17:0
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Base_Bank_Current                       :  5;  // Bits 28:24
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_BASE_ADDRESS_ROW_BANK_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32                                         :  5;  // Bits 4:0
    UINT32 Offset_Col_Current                      :  10;  // Bits 14:5
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_COL_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Row_Current                      :  18;  // Bits 17:0
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_OFFSET_ADDRESS_ROW_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Block_Size_Bits_Col                     :  5;  // Bits 4:0
    UINT32 Block_Size_Bits_Row                     :  5;  // Bits 9:5
    UINT32 Block_Size_Num_Banks                    :  5;  // Bits 14:10
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Region_Size_Bits_Col                    :  5;  // Bits 20:16
    UINT32 Region_Size_Bits_Row                    :  5;  // Bits 25:21
    UINT32 Block_Size_Num_Ranks                    :  5;  // Bits 30:26
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_ADDRESS_SIZE_STRUCT;

typedef union {
  struct {
    UINT32 Block_Col_Move_One_Col                  :  1;  // Bits 0:0
    UINT32 Block_Col_Move_Half_Block               :  1;  // Bits 1:1
    UINT32 Hammer_Inc_Rate                         :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Block_Row_Move_One_Row                  :  1;  // Bits 4:4
    UINT32 Block_Row_Move_Half_Block               :  1;  // Bits 5:5
    UINT32 Row_Inc                                 :  4;  // Bits 9:6
    UINT32                                         :  1;  // Bits 10:10
    UINT32 Col_Inc                                 :  4;  // Bits 14:11
    UINT32 Reserved_Bank_Inc                       :  3;  // Bits 17:15
    UINT32 Reserved_Rank_Inc                       :  3;  // Bits 20:18
    UINT32 Address_Order0_Inc_Rate                 :  1;  // Bits 21:21
    UINT32 Address_Inversion_Enable                :  4;  // Bits 25:22
    UINT32 Address_Inversion_Rate                  :  1;  // Bits 26:26
    UINT32 Addr_Prbs_Carry_Mode                    :  1;  // Bits 27:27
    UINT32 Addr_Prbs_Col_En                        :  1;  // Bits 28:28
    UINT32 Addr_Prbs_Row_En                        :  1;  // Bits 29:29
    UINT32 Addr_Prbs_Bnk_En                        :  1;  // Bits 30:30
    UINT32 Addr_Prbs_Rnk_En                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_BASE_ADDRESS_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Seed                :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Seed                  :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Seed                   :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Seed                  :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CPGC2_ADDRESS_PRBS_SEED_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Current             :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Current               :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Current                :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Current               :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CPGC2_ADDRESS_PRBS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Save                :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Save                  :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Save                   :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Save                  :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CPGC2_ADDRESS_PRBS_SAVE_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Poly                :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Poly                  :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Poly                   :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Poly                  :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CPGC2_ADDRESS_PRBS_POLY_STRUCT;

typedef union {
  struct {
    UINT32 Prescaler_for_Clock_Freq                :  10;  // Bits 9:0
    UINT32                                         :  6;  // Bits 15:10
    UINT32 Clock_Freq                              :  10;  // Bits 25:16
    UINT32                                         :  2;  // Bits 27:26
    UINT32 Increment_Value                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_WAIT_2_START_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Command_Instruction_Current      :  3;  // Bits 2:0
    UINT32 Offset_Address_Instruction_Current      :  3;  // Bits 5:3
    UINT32 Offset_Group_Instruction_Current        :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Command_Instruction_Current             :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Algorithm_Instruction_Current           :  3;  // Bits 17:15
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Data_Instruction_Current                :  2;  // Bits 25:24
    UINT32                                         :  2;  // Bits 27:26
    UINT32 Address_Instruction_Current             :  2;  // Bits 29:28
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_CMD_FSM_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 START_TEST                              :  1;  // Bits 0:0
    UINT32 STOP_TEST                               :  1;  // Bits 1:1
    UINT32 CLEAR_ERRORS                            :  1;  // Bits 2:2
    UINT32                                         :  5;  // Bits 7:3
    UINT32 SINGLE_CMD_MODE                         :  1;  // Bits 8:8
    UINT32 CONTINUE_SINGLE_MODE                    :  1;  // Bits 9:9
    UINT32 SINGLE_MARCH_ELEMENT_MODE               :  1;  // Bits 10:10
    UINT32                                         :  21;  // Bits 31:11
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_CTL_STRUCT;

typedef union {
  struct {
    UINT32                                         :  8;  // Bits 7:0
    UINT32 GLOBAL_CLEAR_ERR_BIND                   :  1;  // Bits 8:8
    UINT32 GLOBAL_STOP_ON_ERR_BIND                 :  1;  // Bits 9:9
    UINT32 GLOBAL_START_BIND                       :  1;  // Bits 10:10
    UINT32 GLOBAL_STOP_BIND                        :  1;  // Bits 11:11
    UINT32 INITIALIZATION_MODE                     :  3;  // Bits 14:12
    UINT32                                         :  7;  // Bits 21:15
    UINT32 REQUEST_DATA_SIZE                       :  1;  // Bits 22:22
    UINT32 STRICT_WR_TO_RD_ORDER                   :  1;  // Bits 23:23
    UINT32 CHANNEL_ASSIGN                          :  4;  // Bits 27:24
    UINT32                                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_CFG_A_STRUCT;

typedef union {
  struct {
    UINT32 START_DELAY                             :  10;  // Bits 9:0
    UINT32                                         :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_CFG_B_STRUCT;

typedef union {
  struct {
    UINT32                                         :  20;  // Bits 19:0
    UINT32 CREDITS_INITIALIZED                     :  1;  // Bits 20:20
    UINT32                                         :  3;  // Bits 23:21
    UINT32 TEST_ABORTED                            :  1;  // Bits 24:24
    UINT32 EVENT_NOT_SEEN                          :  1;  // Bits 25:25
    UINT32 ALGO_WAIT                               :  1;  // Bits 26:26
    UINT32 SINGLE_MODE_PAUSED                      :  1;  // Bits 27:27
    UINT32 ALGO_DONE                               :  1;  // Bits 28:28
    UINT32 START_TEST_DELAY_BUSY                   :  1;  // Bits 29:29
    UINT32 TEST_BUSY                               :  1;  // Bits 30:30
    UINT32 TEST_DONE                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_0_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_1_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_2_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_3_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_4_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_5_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_6_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_7_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_8_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_9_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_10_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_11_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_12_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_13_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_14_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_15_STRUCT;

typedef union {
  struct {
    UINT32 fail_excess0                            :  1;  // Bits 0:0
    UINT32 fail_any0                               :  1;  // Bits 1:1
    UINT32 fail_count0                             :  2;  // Bits 3:2
    UINT32 ECC_chunk0                              :  4;  // Bits 7:4
    UINT32 fail_excess1                            :  1;  // Bits 8:8
    UINT32 fail_any1                               :  1;  // Bits 9:9
    UINT32 fail_count1                             :  2;  // Bits 11:10
    UINT32 ECC_chunk1                              :  4;  // Bits 15:12
    UINT32 fail_excess2                            :  1;  // Bits 16:16
    UINT32 fail_any2                               :  1;  // Bits 17:17
    UINT32 fail_count2                             :  2;  // Bits 19:18
    UINT32 ECC_chunk2                              :  4;  // Bits 23:20
    UINT32 fail_excess3                            :  1;  // Bits 24:24
    UINT32 fail_any3                               :  1;  // Bits 25:25
    UINT32 fail_count3                             :  2;  // Bits 27:26
    UINT32 ECC_chunk3                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_ECC1_STRUCT;

typedef union {
  struct {
    UINT32 fail_excess4                            :  1;  // Bits 0:0
    UINT32 fail_any4                               :  1;  // Bits 1:1
    UINT32 fail_count4                             :  2;  // Bits 3:2
    UINT32 ECC_chunk4                              :  4;  // Bits 7:4
    UINT32 fail_excess5                            :  1;  // Bits 8:8
    UINT32 fail_any5                               :  1;  // Bits 9:9
    UINT32 fail_count5                             :  2;  // Bits 11:10
    UINT32 ECC_chunk5                              :  4;  // Bits 15:12
    UINT32 fail_excess6                            :  1;  // Bits 16:16
    UINT32 fail_any6                               :  1;  // Bits 17:17
    UINT32 fail_count6                             :  2;  // Bits 19:18
    UINT32 ECC_chunk6                              :  4;  // Bits 23:20
    UINT32 fail_excess7                            :  1;  // Bits 24:24
    UINT32 fail_any7                               :  1;  // Bits 25:25
    UINT32 fail_count7                             :  2;  // Bits 27:26
    UINT32 ECC_chunk7                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_CONTENT_ECC2_STRUCT;

typedef union {
  struct {
    UINT32 Read_Command_Count_Current              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Mask_First_N_Reads                      :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_MASK_ERRS_FIRST_N_READS_STRUCT;

typedef union {
  struct {
    UINT32 BitmapValid                             :  1;  // Bits 0:0
    UINT32 SummaryValid                            :  1;  // Bits 1:1
    UINT32 RasterRepoFull                          :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 NumErrLogged                            :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 FailExcessAll                           :  1;  // Bits 8:8
    UINT32 FailAnyAll                              :  1;  // Bits 9:9
    UINT32 FailMax                                 :  2;  // Bits 11:10
    UINT32                                         :  4;  // Bits 15:12
    UINT32 RasterRepoMode                          :  2;  // Bits 17:16
    UINT32                                         :  12;  // Bits 29:18
    UINT32 StopOnRaster                            :  1;  // Bits 30:30
    UINT32 RasterRepoClear                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_RASTER_REPO_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Error_Summary                           :  16;  // Bits 15:0
    UINT32 Algorithm_Summary                       :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_ERR_SUMMARY_A_STRUCT;

typedef union {
  struct {
    UINT32 Algorithm_Summary                       :  2;  // Bits 1:0
    UINT32 Physical_Address_Summary                :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_ERR_SUMMARY_B_STRUCT;

typedef union {
  struct {
    UINT32 Physical_Address_Summary                :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC2_ERR_SUMMARY_C_STRUCT;

typedef union {
  struct {
    UINT32 BUF_PNTR_INC_RATE                       :  6;  // Bits 5:0
    UINT32 BUF_PNTR_INC_SCALE                      :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 BUF_STRT_PNTR                           :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 BUF_END_PNTR                            :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 WR_BUF_PTR                              :  4;  // Bits 23:20
    UINT32 RD_BUF_PTR                              :  4;  // Bits 27:24
    UINT32                                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_BUF_CTL_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ0_MODE                            :  2;  // Bits 1:0
    UINT32                                         :  1;  // Bits 2:2
    UINT32 UNISEQ1_MODE                            :  2;  // Bits 4:3
    UINT32                                         :  1;  // Bits 5:5
    UINT32 UNISEQ2_MODE                            :  2;  // Bits 7:6
    UINT32 WRITE_ADDRESS_AS_DATA                   :  1;  // Bits 8:8
    UINT32 READ_ADDRESS_AS_DATA                    :  1;  // Bits 9:9
    UINT32                                         :  3;  // Bits 12:10
    UINT32 ECC_DISABLE                             :  1;  // Bits 13:13
    UINT32 ECC_REPLACE_BYTE_CONTROL                :  1;  // Bits 14:14
    UINT32 ECC_DATA_SOURCE_SEL                     :  1;  // Bits 15:15
    UINT32 SAVE_LFSR_SEED_RATE                     :  8;  // Bits 23:16
    UINT32 RELOAD_LFSR_SEED_RATE                   :  5;  // Bits 28:24
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_CFG_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 UNISEQ0_LFSR_POLYNOMIAL_SIZE            :  3;  // Bits 4:2
    UINT32                                         :  2;  // Bits 6:5
    UINT32 UNISEQ0_LFSR_STAGGER                    :  1;  // Bits 7:7
    UINT32                                         :  2;  // Bits 9:8
    UINT32 UNISEQ1_LFSR_POLYNOMIAL_SIZE            :  3;  // Bits 12:10
    UINT32                                         :  2;  // Bits 14:13
    UINT32 UNISEQ1_LFSR_STAGGER                    :  1;  // Bits 15:15
    UINT32                                         :  2;  // Bits 17:16
    UINT32 UNISEQ2_LFSR_POLYNOMIAL_SIZE            :  3;  // Bits 20:18
    UINT32                                         :  2;  // Bits 22:21
    UINT32 UNISEQ2_LFSR_STAGGER                    :  1;  // Bits 23:23
    UINT32 LANE_ROTATE_RATE                        :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_XTRA_LFSR_CFG_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_0_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_1_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_2_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32 FREQ_SWEEP_EN                           :  1;  // Bits 1:1
    UINT32 L_COUNT_EN                              :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 M_CNT                                   :  8;  // Bits 23:16
    UINT32 N_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_LMN_0_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32 FREQ_SWEEP_EN                           :  1;  // Bits 1:1
    UINT32 L_COUNT_EN                              :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 M_CNT                                   :  8;  // Bits 23:16
    UINT32 N_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_LMN_1_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32 FREQ_SWEEP_EN                           :  1;  // Bits 1:1
    UINT32 L_COUNT_EN                              :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 M_CNT                                   :  8;  // Bits 23:16
    UINT32 N_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_LMN_2_STRUCT;

typedef union {
  struct {
    UINT32 ECC_INV_DC_MASK                         :  8;  // Bits 7:0
    UINT32 MASK_ROTATE_RATE                        :  4;  // Bits 11:8
    UINT32                                         :  4;  // Bits 15:12
    UINT32 BYTEGROUP_MAPPING                       :  9;  // Bits 24:16
    UINT32                                         :  4;  // Bits 28:25
    UINT32 DC_POL                                  :  1;  // Bits 29:29
    UINT32 DC_OR_INV                               :  1;  // Bits 30:30
    UINT32 MASK_ROTATE_EN                          :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_INVDCCTL_STRUCT;

typedef union {
  struct {
    UINT32 DATA_INV_DC_MASK_LO                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_INV_DC_MASK_LO_STRUCT;

typedef union {
  struct {
    UINT32 DATA_INV_DC_MASK_HI                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_INV_DC_MASK_HI_STRUCT;

typedef union {
  struct {
    UINT32 DATA_MASK_LO                            :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_DRAMDM_STRUCT;

typedef union {
  struct {
    UINT32 DATA_MASK_HI                            :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_XDRAMDM_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_WRSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_WRSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_WRSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_WRSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_WRSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_RDSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_RDSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_RDSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_RDSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_RDSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 LMN_WRSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_LMN_WRSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 LMN_WRSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_LMN_WRSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 LMN_WRSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_LMN_WRSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 LMN_RDSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_LMN_RDSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 LMN_RDSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_LMN_RDSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 LMN_RDSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_LMN_RDSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_WRSAVE_1_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_WRSAVE_2_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_RDSAVE_0_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_RDSAVE_1_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_UNISEQ_RDSAVE_2_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_0_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_1_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_2_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_3_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_4_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_5_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_6_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_7_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_8_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_9_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_10_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_11_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_12_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_13_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_14_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_DPAT_EXTBUF_15_STRUCT;

typedef union {
  struct {
    UINT32 STOP_ON_N                               :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 BE_TRAIN_ERR_EN                         :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 STOP_ON_ERROR_CTL                       :  2;  // Bits 13:12
    UINT32                                         :  2;  // Bits 15:14
    UINT32 ERRCHK_MASK_CHUNK                       :  8;  // Bits 23:16
    UINT32 ERRCHK_MASK_CACHELINE                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CTL_STRUCT;

typedef union {
  struct {
    UINT32 DATA_ERRCHK_MASK_LO                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_LNEN_LO_STRUCT;

typedef union {
  struct {
    UINT32 DATA_ERRCHK_MASK_HI                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_LNEN_HI_STRUCT;

typedef union {
  struct {
    UINT32 ECC_ERRCHK_MASK                         :  8;  // Bits 7:0
    UINT32                                         :  8;  // Bits 15:8
    UINT32 RANK_ERRCHK_MASK                        :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_XLNEN_STRUCT;

typedef union {
  struct {
    UINT32 LANE_ERR_STAT_LO                        :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_STAT03_STRUCT;

typedef union {
  struct {
    UINT32 LANE_ERR_STAT_HI                        :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_STAT47_STRUCT;

typedef union {
  struct {
    UINT32 ECC_LANE_ERR_STAT                       :  8;  // Bits 7:0
    UINT32 CHUNK_ERR_STAT                          :  8;  // Bits 15:8
    UINT32 RANK_ERR_STAT                           :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_STRUCT;

typedef union {
  struct {
    UINT32 BYTEGRP_ERR_STAT                        :  8;  // Bits 7:0
    UINT32 ECCGRP_ERR_STAT                         :  1;  // Bits 8:8
    UINT32                                         :  11;  // Bits 19:9
    UINT32 RD_CHUNK_NUM_STAT                       :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Nth_ERROR                               :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTRCTL_0_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTRCTL_1_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTRCTL_2_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTRCTL_3_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTRCTL_4_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTRCTL_5_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTRCTL_6_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTRCTL_7_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTRCTL_8_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTR_0_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTR_1_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTR_2_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTR_3_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTR_4_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTR_5_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTR_6_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTR_7_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTR_8_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER_OVERFLOW                  :  9;  // Bits 8:0
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_CNTR_OV_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_STATUS                            :  1;  // Bits 0:0
    UINT32 TEST_IN_PROGRESS                        :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_ERR_TEST_ERR_STAT_STRUCT;

typedef union {
  struct {
    UINT32 DUMMYLow                                :  32;  // Bits 31:0
    UINT32 DUMMYHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CPGC_D_DUMMY_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK0_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_RANK1_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_RANK2_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_RANK3_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_RANK4_MAPPING                       :  5;  // Bits 24:20
    UINT32 L2P_RANK5_MAPPING                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK6_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_RANK7_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_RANK8_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_RANK9_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_RANK10_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK11_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK12_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK13_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_RANK14_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_RANK15_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_RANK16_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK17_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK18_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK19_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_RANK20_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_RANK21_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_RANK22_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK23_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK24_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK25_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_RANK26_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_RANK27_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_RANK28_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK29_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK30_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK31_MAPPING                      :  5;  // Bits 9:5
    UINT32                                         :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK0_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_BANK1_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_BANK2_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_BANK3_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_BANK4_MAPPING                       :  5;  // Bits 24:20
    UINT32 L2P_BANK5_MAPPING                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK6_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_BANK7_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_BANK8_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_BANK9_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_BANK10_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK11_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK12_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK13_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_BANK14_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_BANK15_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_BANK16_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK17_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK18_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK19_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_BANK20_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_BANK21_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_BANK22_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK23_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK24_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK25_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_BANK26_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_BANK27_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_BANK28_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK29_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK30_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK31_MAPPING                      :  5;  // Bits 9:5
    UINT32                                         :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK0_SWIZZLE                       :  5;  // Bits 4:0
    UINT32 L2P_RANK1_SWIZZLE                       :  5;  // Bits 9:5
    UINT32 L2P_RANK2_SWIZZLE                       :  5;  // Bits 14:10
    UINT32 L2P_RANK3_SWIZZLE                       :  5;  // Bits 19:15
    UINT32 L2P_RANK4_SWIZZLE                       :  5;  // Bits 24:20
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK0_SWIZZLE                       :  5;  // Bits 4:0
    UINT32 L2P_BANK1_SWIZZLE                       :  5;  // Bits 9:5
    UINT32 L2P_BANK2_SWIZZLE                       :  5;  // Bits 14:10
    UINT32 L2P_BANK3_SWIZZLE                       :  5;  // Bits 19:15
    UINT32 L2P_BANK4_SWIZZLE                       :  5;  // Bits 24:20
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW0_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_ROW1_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_ROW2_SWIZZLE                        :  5;  // Bits 14:10
    UINT32 L2P_ROW3_SWIZZLE                        :  5;  // Bits 19:15
    UINT32 L2P_ROW4_SWIZZLE                        :  5;  // Bits 24:20
    UINT32 L2P_ROW5_SWIZZLE                        :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW6_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_ROW7_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_ROW8_SWIZZLE                        :  5;  // Bits 14:10
    UINT32 L2P_ROW9_SWIZZLE                        :  5;  // Bits 19:15
    UINT32 L2P_ROW10_SWIZZLE                       :  5;  // Bits 24:20
    UINT32 L2P_ROW11_SWIZZLE                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW12_SWIZZLE                       :  5;  // Bits 4:0
    UINT32 L2P_ROW13_SWIZZLE                       :  5;  // Bits 9:5
    UINT32 L2P_ROW14_SWIZZLE                       :  5;  // Bits 14:10
    UINT32 L2P_ROW15_SWIZZLE                       :  5;  // Bits 19:15
    UINT32 L2P_ROW16_SWIZZLE                       :  5;  // Bits 24:20
    UINT32 L2P_ROW17_SWIZZLE                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW0_XOR_SWIZZLE                    :  5;  // Bits 4:0
    UINT32 L2P_ROW1_XOR_SWIZZLE                    :  5;  // Bits 9:5
    UINT32 L2P_ROW2_XOR_SWIZZLE                    :  5;  // Bits 14:10
    UINT32 L2P_ROW3_XOR_SWIZZLE                    :  5;  // Bits 19:15
    UINT32                                         :  9;  // Bits 28:20
    UINT32 ADDR_DQ_INV_EN                          :  1;  // Bits 29:29
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_STRUCT;

typedef union {
  struct {
    UINT32 L2P_COL0_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_COL1_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_COL2_SWIZZLE                        :  5;  // Bits 14:10
    UINT32 L2P_COL3_SWIZZLE                        :  5;  // Bits 19:15
    UINT32 L2P_COL4_SWIZZLE                        :  5;  // Bits 24:20
    UINT32 L2P_COL5_SWIZZLE                        :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_COL6_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_COL7_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_COL8_SWIZZLE                        :  5;  // Bits 14:10
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_ROW_ADDR_DQ_MAP0_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CPGC_SEQ_ROW_ADDR_DQ_MAP1_STRUCT;

typedef union {
  struct {
    UINT32 DUMMYLow                                :  32;  // Bits 31:0
    UINT32 DUMMYHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CPGC_A_DUMMY_STRUCT;

typedef union {
  struct {
    UINT32 Address_Decode_Rotate_Repeats           :  6;  // Bits 5:0
    UINT32                                         :  18;  // Bits 23:6
    UINT32 Column_Addr_Invert_Select               :  2;  // Bits 25:24
    UINT32 Row_Addr_Invert_Select                  :  2;  // Bits 27:26
    UINT32 Bank_Addr_Invert_Select                 :  2;  // Bits 29:28
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_ADDRESS_CONTROL_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ADDRESS_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ADDRESS_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ADDRESS_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ADDRESS_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_DATA_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_DATA_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_DATA_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_DATA_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT32 Data_Select_Rotation_Repeats            :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_DATA_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Address_Decode_Rotate_Repeats_Current   :  6;  // Bits 5:0
    UINT32                                         :  10;  // Bits 15:6
    UINT32 Data_Select_Rotation_Repeats_Current    :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_ADDRESS_DATA_STATUS_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_1_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_2_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_3_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_4_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_5_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_6_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_7_STRUCT;

typedef union {
  struct {
    UINT32 Wait_Timer_Current                      :  16;  // Bits 15:0
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_ALGORITHM_WAIT_COUNT_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Wait_Time                               :  16;  // Bits 15:0
    UINT32                                         :  4;  // Bits 19:16
    UINT32 Timer                                   :  4;  // Bits 23:20
    UINT32 Wait_Clock_Frequency                    :  2;  // Bits 25:24
    UINT32                                         :  4;  // Bits 29:26
    UINT32 Select_Event                            :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Base_Repeats                            :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_BASE_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Base_Repeats_Current                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_BASE_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Base_Col_Repeats                        :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_BASE_COL_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Block_Repeats                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_BLOCK_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Block_Repeats_Current                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_BLOCK_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_8_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_9_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_10_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_11_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_12_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_13_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_14_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_15_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_16_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_17_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_18_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_19_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_20_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_21_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_22_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_COMMAND_INSTRUCTION_23_STRUCT;

typedef union {
  struct {
    UINT32 Hammer_Repeats                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_HAMMER_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Hammer_Repeats_Current                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_HAMMER_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_8_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_9_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_10_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_11_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_12_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_13_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_14_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_15_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_8_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_9_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_10_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_11_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Repeats                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_OFFSET_REPEATS_0_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Repeats                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_OFFSET_REPEATS_1_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Repeats_Current                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_OFFSET_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Low_Row                                 :  18;  // Bits 17:0
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_REGION_LOW_ROW_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Low_Col                                 :  9;  // Bits 10:2
    UINT32                                         :  21;  // Bits 31:11
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_REGION_LOW_COL_STRUCT;

typedef union {
  struct {
    UINT32                                         :  5;  // Bits 4:0
    UINT32 Block_Origin_Col_Current                :  10;  // Bits 14:5
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_BLOCK_ORIGIN_COL_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Block_Origin_Row_Current                :  18;  // Bits 17:0
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_BLOCK_ORIGIN_ROW_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32                                         :  5;  // Bits 4:0
    UINT32 Base_Col_Current                        :  10;  // Bits 14:5
    UINT32                                         :  9;  // Bits 23:15
    UINT32 Base_Rank_Current                       :  5;  // Bits 28:24
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_BASE_ADDRESS_COL_RANK_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Base_Row_Current                        :  18;  // Bits 17:0
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Base_Bank_Current                       :  5;  // Bits 28:24
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_BASE_ADDRESS_ROW_BANK_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32                                         :  5;  // Bits 4:0
    UINT32 Offset_Col_Current                      :  10;  // Bits 14:5
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_COL_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Row_Current                      :  18;  // Bits 17:0
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_OFFSET_ADDRESS_ROW_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Block_Size_Bits_Col                     :  5;  // Bits 4:0
    UINT32 Block_Size_Bits_Row                     :  5;  // Bits 9:5
    UINT32 Block_Size_Num_Banks                    :  5;  // Bits 14:10
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Region_Size_Bits_Col                    :  5;  // Bits 20:16
    UINT32 Region_Size_Bits_Row                    :  5;  // Bits 25:21
    UINT32 Block_Size_Num_Ranks                    :  5;  // Bits 30:26
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_ADDRESS_SIZE_STRUCT;

typedef union {
  struct {
    UINT32 Block_Col_Move_One_Col                  :  1;  // Bits 0:0
    UINT32 Block_Col_Move_Half_Block               :  1;  // Bits 1:1
    UINT32 Hammer_Inc_Rate                         :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Block_Row_Move_One_Row                  :  1;  // Bits 4:4
    UINT32 Block_Row_Move_Half_Block               :  1;  // Bits 5:5
    UINT32 Row_Inc                                 :  4;  // Bits 9:6
    UINT32                                         :  1;  // Bits 10:10
    UINT32 Col_Inc                                 :  4;  // Bits 14:11
    UINT32 Reserved_Bank_Inc                       :  3;  // Bits 17:15
    UINT32 Reserved_Rank_Inc                       :  3;  // Bits 20:18
    UINT32 Address_Order0_Inc_Rate                 :  1;  // Bits 21:21
    UINT32 Address_Inversion_Enable                :  4;  // Bits 25:22
    UINT32 Address_Inversion_Rate                  :  1;  // Bits 26:26
    UINT32 Addr_Prbs_Carry_Mode                    :  1;  // Bits 27:27
    UINT32 Addr_Prbs_Col_En                        :  1;  // Bits 28:28
    UINT32 Addr_Prbs_Row_En                        :  1;  // Bits 29:29
    UINT32 Addr_Prbs_Bnk_En                        :  1;  // Bits 30:30
    UINT32 Addr_Prbs_Rnk_En                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_BASE_ADDRESS_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Seed                :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Seed                  :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Seed                   :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Seed                  :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CPGC2_ADDRESS_PRBS_SEED_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Current             :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Current               :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Current                :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Current               :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CPGC2_ADDRESS_PRBS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Save                :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Save                  :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Save                   :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Save                  :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CPGC2_ADDRESS_PRBS_SAVE_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Poly                :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Poly                  :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Poly                   :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Poly                  :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CPGC2_ADDRESS_PRBS_POLY_STRUCT;

typedef union {
  struct {
    UINT32 Prescaler_for_Clock_Freq                :  10;  // Bits 9:0
    UINT32                                         :  6;  // Bits 15:10
    UINT32 Clock_Freq                              :  10;  // Bits 25:16
    UINT32                                         :  2;  // Bits 27:26
    UINT32 Increment_Value                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_WAIT_2_START_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Command_Instruction_Current      :  3;  // Bits 2:0
    UINT32 Offset_Address_Instruction_Current      :  3;  // Bits 5:3
    UINT32 Offset_Group_Instruction_Current        :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Command_Instruction_Current             :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Algorithm_Instruction_Current           :  3;  // Bits 17:15
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Data_Instruction_Current                :  2;  // Bits 25:24
    UINT32                                         :  2;  // Bits 27:26
    UINT32 Address_Instruction_Current             :  2;  // Bits 29:28
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_CMD_FSM_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 START_TEST                              :  1;  // Bits 0:0
    UINT32 STOP_TEST                               :  1;  // Bits 1:1
    UINT32 CLEAR_ERRORS                            :  1;  // Bits 2:2
    UINT32                                         :  5;  // Bits 7:3
    UINT32 SINGLE_CMD_MODE                         :  1;  // Bits 8:8
    UINT32 CONTINUE_SINGLE_MODE                    :  1;  // Bits 9:9
    UINT32 SINGLE_MARCH_ELEMENT_MODE               :  1;  // Bits 10:10
    UINT32                                         :  21;  // Bits 31:11
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_CTL_STRUCT;

typedef union {
  struct {
    UINT32                                         :  8;  // Bits 7:0
    UINT32 GLOBAL_CLEAR_ERR_BIND                   :  1;  // Bits 8:8
    UINT32 GLOBAL_STOP_ON_ERR_BIND                 :  1;  // Bits 9:9
    UINT32 GLOBAL_START_BIND                       :  1;  // Bits 10:10
    UINT32 GLOBAL_STOP_BIND                        :  1;  // Bits 11:11
    UINT32 INITIALIZATION_MODE                     :  3;  // Bits 14:12
    UINT32                                         :  7;  // Bits 21:15
    UINT32 REQUEST_DATA_SIZE                       :  1;  // Bits 22:22
    UINT32 STRICT_WR_TO_RD_ORDER                   :  1;  // Bits 23:23
    UINT32 CHANNEL_ASSIGN                          :  4;  // Bits 27:24
    UINT32                                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_CFG_A_STRUCT;

typedef union {
  struct {
    UINT32 START_DELAY                             :  10;  // Bits 9:0
    UINT32                                         :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_CFG_B_STRUCT;

typedef union {
  struct {
    UINT32                                         :  20;  // Bits 19:0
    UINT32 CREDITS_INITIALIZED                     :  1;  // Bits 20:20
    UINT32                                         :  3;  // Bits 23:21
    UINT32 TEST_ABORTED                            :  1;  // Bits 24:24
    UINT32 EVENT_NOT_SEEN                          :  1;  // Bits 25:25
    UINT32 ALGO_WAIT                               :  1;  // Bits 26:26
    UINT32 SINGLE_MODE_PAUSED                      :  1;  // Bits 27:27
    UINT32 ALGO_DONE                               :  1;  // Bits 28:28
    UINT32 START_TEST_DELAY_BUSY                   :  1;  // Bits 29:29
    UINT32 TEST_BUSY                               :  1;  // Bits 30:30
    UINT32 TEST_DONE                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_0_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_1_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_2_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_3_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_4_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_5_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_6_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_7_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_8_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_9_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_10_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_11_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_12_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_13_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_14_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_15_STRUCT;

typedef union {
  struct {
    UINT32 fail_excess0                            :  1;  // Bits 0:0
    UINT32 fail_any0                               :  1;  // Bits 1:1
    UINT32 fail_count0                             :  2;  // Bits 3:2
    UINT32 ECC_chunk0                              :  4;  // Bits 7:4
    UINT32 fail_excess1                            :  1;  // Bits 8:8
    UINT32 fail_any1                               :  1;  // Bits 9:9
    UINT32 fail_count1                             :  2;  // Bits 11:10
    UINT32 ECC_chunk1                              :  4;  // Bits 15:12
    UINT32 fail_excess2                            :  1;  // Bits 16:16
    UINT32 fail_any2                               :  1;  // Bits 17:17
    UINT32 fail_count2                             :  2;  // Bits 19:18
    UINT32 ECC_chunk2                              :  4;  // Bits 23:20
    UINT32 fail_excess3                            :  1;  // Bits 24:24
    UINT32 fail_any3                               :  1;  // Bits 25:25
    UINT32 fail_count3                             :  2;  // Bits 27:26
    UINT32 ECC_chunk3                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_ECC1_STRUCT;

typedef union {
  struct {
    UINT32 fail_excess4                            :  1;  // Bits 0:0
    UINT32 fail_any4                               :  1;  // Bits 1:1
    UINT32 fail_count4                             :  2;  // Bits 3:2
    UINT32 ECC_chunk4                              :  4;  // Bits 7:4
    UINT32 fail_excess5                            :  1;  // Bits 8:8
    UINT32 fail_any5                               :  1;  // Bits 9:9
    UINT32 fail_count5                             :  2;  // Bits 11:10
    UINT32 ECC_chunk5                              :  4;  // Bits 15:12
    UINT32 fail_excess6                            :  1;  // Bits 16:16
    UINT32 fail_any6                               :  1;  // Bits 17:17
    UINT32 fail_count6                             :  2;  // Bits 19:18
    UINT32 ECC_chunk6                              :  4;  // Bits 23:20
    UINT32 fail_excess7                            :  1;  // Bits 24:24
    UINT32 fail_any7                               :  1;  // Bits 25:25
    UINT32 fail_count7                             :  2;  // Bits 27:26
    UINT32 ECC_chunk7                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_CONTENT_ECC2_STRUCT;

typedef union {
  struct {
    UINT32 Read_Command_Count_Current              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Mask_First_N_Reads                      :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_MASK_ERRS_FIRST_N_READS_STRUCT;

typedef union {
  struct {
    UINT32 BitmapValid                             :  1;  // Bits 0:0
    UINT32 SummaryValid                            :  1;  // Bits 1:1
    UINT32 RasterRepoFull                          :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 NumErrLogged                            :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 FailExcessAll                           :  1;  // Bits 8:8
    UINT32 FailAnyAll                              :  1;  // Bits 9:9
    UINT32 FailMax                                 :  2;  // Bits 11:10
    UINT32                                         :  4;  // Bits 15:12
    UINT32 RasterRepoMode                          :  2;  // Bits 17:16
    UINT32                                         :  12;  // Bits 29:18
    UINT32 StopOnRaster                            :  1;  // Bits 30:30
    UINT32 RasterRepoClear                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_RASTER_REPO_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Error_Summary                           :  16;  // Bits 15:0
    UINT32 Algorithm_Summary                       :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_ERR_SUMMARY_A_STRUCT;

typedef union {
  struct {
    UINT32 Algorithm_Summary                       :  2;  // Bits 1:0
    UINT32 Physical_Address_Summary                :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_ERR_SUMMARY_B_STRUCT;

typedef union {
  struct {
    UINT32 Physical_Address_Summary                :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC2_ERR_SUMMARY_C_STRUCT;

typedef union {
  struct {
    UINT32 BUF_PNTR_INC_RATE                       :  6;  // Bits 5:0
    UINT32 BUF_PNTR_INC_SCALE                      :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 BUF_STRT_PNTR                           :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 BUF_END_PNTR                            :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 WR_BUF_PTR                              :  4;  // Bits 23:20
    UINT32 RD_BUF_PTR                              :  4;  // Bits 27:24
    UINT32                                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_BUF_CTL_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ0_MODE                            :  2;  // Bits 1:0
    UINT32                                         :  1;  // Bits 2:2
    UINT32 UNISEQ1_MODE                            :  2;  // Bits 4:3
    UINT32                                         :  1;  // Bits 5:5
    UINT32 UNISEQ2_MODE                            :  2;  // Bits 7:6
    UINT32 WRITE_ADDRESS_AS_DATA                   :  1;  // Bits 8:8
    UINT32 READ_ADDRESS_AS_DATA                    :  1;  // Bits 9:9
    UINT32                                         :  3;  // Bits 12:10
    UINT32 ECC_DISABLE                             :  1;  // Bits 13:13
    UINT32 ECC_REPLACE_BYTE_CONTROL                :  1;  // Bits 14:14
    UINT32 ECC_DATA_SOURCE_SEL                     :  1;  // Bits 15:15
    UINT32 SAVE_LFSR_SEED_RATE                     :  8;  // Bits 23:16
    UINT32 RELOAD_LFSR_SEED_RATE                   :  5;  // Bits 28:24
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_CFG_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 UNISEQ0_LFSR_POLYNOMIAL_SIZE            :  3;  // Bits 4:2
    UINT32                                         :  2;  // Bits 6:5
    UINT32 UNISEQ0_LFSR_STAGGER                    :  1;  // Bits 7:7
    UINT32                                         :  2;  // Bits 9:8
    UINT32 UNISEQ1_LFSR_POLYNOMIAL_SIZE            :  3;  // Bits 12:10
    UINT32                                         :  2;  // Bits 14:13
    UINT32 UNISEQ1_LFSR_STAGGER                    :  1;  // Bits 15:15
    UINT32                                         :  2;  // Bits 17:16
    UINT32 UNISEQ2_LFSR_POLYNOMIAL_SIZE            :  3;  // Bits 20:18
    UINT32                                         :  2;  // Bits 22:21
    UINT32 UNISEQ2_LFSR_STAGGER                    :  1;  // Bits 23:23
    UINT32 LANE_ROTATE_RATE                        :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_XTRA_LFSR_CFG_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_0_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_1_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_2_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32 FREQ_SWEEP_EN                           :  1;  // Bits 1:1
    UINT32 L_COUNT_EN                              :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 M_CNT                                   :  8;  // Bits 23:16
    UINT32 N_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_LMN_0_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32 FREQ_SWEEP_EN                           :  1;  // Bits 1:1
    UINT32 L_COUNT_EN                              :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 M_CNT                                   :  8;  // Bits 23:16
    UINT32 N_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_LMN_1_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32 FREQ_SWEEP_EN                           :  1;  // Bits 1:1
    UINT32 L_COUNT_EN                              :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 M_CNT                                   :  8;  // Bits 23:16
    UINT32 N_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_LMN_2_STRUCT;

typedef union {
  struct {
    UINT32 ECC_INV_DC_MASK                         :  8;  // Bits 7:0
    UINT32 MASK_ROTATE_RATE                        :  4;  // Bits 11:8
    UINT32                                         :  4;  // Bits 15:12
    UINT32 BYTEGROUP_MAPPING                       :  9;  // Bits 24:16
    UINT32                                         :  4;  // Bits 28:25
    UINT32 DC_POL                                  :  1;  // Bits 29:29
    UINT32 DC_OR_INV                               :  1;  // Bits 30:30
    UINT32 MASK_ROTATE_EN                          :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_INVDCCTL_STRUCT;

typedef union {
  struct {
    UINT32 DATA_INV_DC_MASK_LO                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_INV_DC_MASK_LO_STRUCT;

typedef union {
  struct {
    UINT32 DATA_INV_DC_MASK_HI                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_INV_DC_MASK_HI_STRUCT;

typedef union {
  struct {
    UINT32 DATA_MASK_LO                            :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_DRAMDM_STRUCT;

typedef union {
  struct {
    UINT32 DATA_MASK_HI                            :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_XDRAMDM_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_WRSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_WRSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_WRSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_WRSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_WRSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_RDSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_RDSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_RDSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_RDSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_RDSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 LMN_WRSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_LMN_WRSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 LMN_WRSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_LMN_WRSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 LMN_WRSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_LMN_WRSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 LMN_RDSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_LMN_RDSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 LMN_RDSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_LMN_RDSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 LMN_RDSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_LMN_RDSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_WRSAVE_1_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_WRSAVE_2_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_RDSAVE_0_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_RDSAVE_1_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_UNISEQ_RDSAVE_2_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_0_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_1_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_2_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_3_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_4_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_5_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_6_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_7_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_8_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_9_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_10_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_11_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_12_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_13_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_14_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_DPAT_EXTBUF_15_STRUCT;

typedef union {
  struct {
    UINT32 STOP_ON_N                               :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 BE_TRAIN_ERR_EN                         :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 STOP_ON_ERROR_CTL                       :  2;  // Bits 13:12
    UINT32                                         :  2;  // Bits 15:14
    UINT32 ERRCHK_MASK_CHUNK                       :  8;  // Bits 23:16
    UINT32 ERRCHK_MASK_CACHELINE                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CTL_STRUCT;

typedef union {
  struct {
    UINT32 DATA_ERRCHK_MASK_LO                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_LNEN_LO_STRUCT;

typedef union {
  struct {
    UINT32 DATA_ERRCHK_MASK_HI                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_LNEN_HI_STRUCT;

typedef union {
  struct {
    UINT32 ECC_ERRCHK_MASK                         :  8;  // Bits 7:0
    UINT32                                         :  8;  // Bits 15:8
    UINT32 RANK_ERRCHK_MASK                        :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_XLNEN_STRUCT;

typedef union {
  struct {
    UINT32 LANE_ERR_STAT_LO                        :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_STAT03_STRUCT;

typedef union {
  struct {
    UINT32 LANE_ERR_STAT_HI                        :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_STAT47_STRUCT;

typedef union {
  struct {
    UINT32 ECC_LANE_ERR_STAT                       :  8;  // Bits 7:0
    UINT32 CHUNK_ERR_STAT                          :  8;  // Bits 15:8
    UINT32 RANK_ERR_STAT                           :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_STRUCT;

typedef union {
  struct {
    UINT32 BYTEGRP_ERR_STAT                        :  8;  // Bits 7:0
    UINT32 ECCGRP_ERR_STAT                         :  1;  // Bits 8:8
    UINT32                                         :  11;  // Bits 19:9
    UINT32 RD_CHUNK_NUM_STAT                       :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Nth_ERROR                               :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTRCTL_0_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTRCTL_1_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTRCTL_2_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTRCTL_3_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTRCTL_4_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTRCTL_5_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTRCTL_6_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTRCTL_7_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTRCTL_8_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTR_0_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTR_1_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTR_2_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTR_3_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTR_4_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTR_5_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTR_6_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTR_7_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTR_8_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER_OVERFLOW                  :  9;  // Bits 8:0
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_CNTR_OV_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_STATUS                            :  1;  // Bits 0:0
    UINT32 TEST_IN_PROGRESS                        :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_ERR_TEST_ERR_STAT_STRUCT;

typedef union {
  struct {
    UINT32 DUMMYLow                                :  32;  // Bits 31:0
    UINT32 DUMMYHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CPGC_D_DUMMY_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK0_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_RANK1_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_RANK2_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_RANK3_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_RANK4_MAPPING                       :  5;  // Bits 24:20
    UINT32 L2P_RANK5_MAPPING                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK6_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_RANK7_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_RANK8_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_RANK9_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_RANK10_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK11_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK12_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK13_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_RANK14_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_RANK15_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_RANK16_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK17_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK18_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK19_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_RANK20_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_RANK21_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_RANK22_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK23_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK24_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK25_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_RANK26_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_RANK27_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_RANK28_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK29_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK30_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK31_MAPPING                      :  5;  // Bits 9:5
    UINT32                                         :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK0_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_BANK1_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_BANK2_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_BANK3_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_BANK4_MAPPING                       :  5;  // Bits 24:20
    UINT32 L2P_BANK5_MAPPING                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK6_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_BANK7_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_BANK8_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_BANK9_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_BANK10_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK11_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK12_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK13_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_BANK14_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_BANK15_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_BANK16_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK17_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK18_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK19_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_BANK20_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_BANK21_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_BANK22_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK23_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK24_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK25_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_BANK26_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_BANK27_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_BANK28_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK29_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK30_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK31_MAPPING                      :  5;  // Bits 9:5
    UINT32                                         :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK0_SWIZZLE                       :  5;  // Bits 4:0
    UINT32 L2P_RANK1_SWIZZLE                       :  5;  // Bits 9:5
    UINT32 L2P_RANK2_SWIZZLE                       :  5;  // Bits 14:10
    UINT32 L2P_RANK3_SWIZZLE                       :  5;  // Bits 19:15
    UINT32 L2P_RANK4_SWIZZLE                       :  5;  // Bits 24:20
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK0_SWIZZLE                       :  5;  // Bits 4:0
    UINT32 L2P_BANK1_SWIZZLE                       :  5;  // Bits 9:5
    UINT32 L2P_BANK2_SWIZZLE                       :  5;  // Bits 14:10
    UINT32 L2P_BANK3_SWIZZLE                       :  5;  // Bits 19:15
    UINT32 L2P_BANK4_SWIZZLE                       :  5;  // Bits 24:20
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW0_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_ROW1_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_ROW2_SWIZZLE                        :  5;  // Bits 14:10
    UINT32 L2P_ROW3_SWIZZLE                        :  5;  // Bits 19:15
    UINT32 L2P_ROW4_SWIZZLE                        :  5;  // Bits 24:20
    UINT32 L2P_ROW5_SWIZZLE                        :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW6_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_ROW7_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_ROW8_SWIZZLE                        :  5;  // Bits 14:10
    UINT32 L2P_ROW9_SWIZZLE                        :  5;  // Bits 19:15
    UINT32 L2P_ROW10_SWIZZLE                       :  5;  // Bits 24:20
    UINT32 L2P_ROW11_SWIZZLE                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW12_SWIZZLE                       :  5;  // Bits 4:0
    UINT32 L2P_ROW13_SWIZZLE                       :  5;  // Bits 9:5
    UINT32 L2P_ROW14_SWIZZLE                       :  5;  // Bits 14:10
    UINT32 L2P_ROW15_SWIZZLE                       :  5;  // Bits 19:15
    UINT32 L2P_ROW16_SWIZZLE                       :  5;  // Bits 24:20
    UINT32 L2P_ROW17_SWIZZLE                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW0_XOR_SWIZZLE                    :  5;  // Bits 4:0
    UINT32 L2P_ROW1_XOR_SWIZZLE                    :  5;  // Bits 9:5
    UINT32 L2P_ROW2_XOR_SWIZZLE                    :  5;  // Bits 14:10
    UINT32 L2P_ROW3_XOR_SWIZZLE                    :  5;  // Bits 19:15
    UINT32                                         :  9;  // Bits 28:20
    UINT32 ADDR_DQ_INV_EN                          :  1;  // Bits 29:29
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_STRUCT;

typedef union {
  struct {
    UINT32 L2P_COL0_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_COL1_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_COL2_SWIZZLE                        :  5;  // Bits 14:10
    UINT32 L2P_COL3_SWIZZLE                        :  5;  // Bits 19:15
    UINT32 L2P_COL4_SWIZZLE                        :  5;  // Bits 24:20
    UINT32 L2P_COL5_SWIZZLE                        :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_COL6_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_COL7_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_COL8_SWIZZLE                        :  5;  // Bits 14:10
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_ROW_ADDR_DQ_MAP0_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CPGC_SEQ_ROW_ADDR_DQ_MAP1_STRUCT;

typedef union {
  struct {
    UINT32 DUMMYLow                                :  32;  // Bits 31:0
    UINT32 DUMMYHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CPGC_A_DUMMY_STRUCT;

typedef union {
  struct {
    UINT32 Control_Policy_LO                       :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_ACCESS_CONTROL_POLICY_LO_STRUCT;

typedef union {
  struct {
    UINT32 Control_Policy_HI                       :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_ACCESS_CONTROL_POLICY_HI_STRUCT;

typedef union {
  struct {
    UINT32 Read_Policy_LO                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_ACCESS_READ_POLICY_LO_STRUCT;

typedef union {
  struct {
    UINT32 Read_Policy_HI                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_ACCESS_READ_POLICY_HI_STRUCT;

typedef union {
  struct {
    UINT32 Write_Policy_LO                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_ACCESS_WRITE_POLICY_LO_STRUCT;

typedef union {
  struct {
    UINT32 Write_Policy_HI                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_ACCESS_WRITE_POLICY_HI_STRUCT;

typedef union {
  struct {
    UINT32 DUMMYLow                                :  32;  // Bits 31:0
    UINT32 DUMMYHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CPGC_P_DUMMY_STRUCT;

typedef union {
  struct {
    UINT32 Dpat0_or_Err0                           :  1;  // Bits 0:0
    UINT32 Cmd0_or_Dpat1_or_Exe0                   :  2;  // Bits 2:1
    UINT32 Err1_or_Cmd1_or_Exe1                    :  2;  // Bits 4:3
    UINT32 Cmd0_grp_Sel                            :  2;  // Bits 6:5
    UINT32 Cmd1_grp_Sel                            :  2;  // Bits 8:7
    UINT32 Dpat0_grp_Sel                           :  2;  // Bits 10:9
    UINT32 Dpat1_grp_Sel                           :  2;  // Bits 12:11
    UINT32 Err0_grp_Sel                            :  2;  // Bits 14:13
    UINT32 Err1_grp_Sel                            :  2;  // Bits 16:15
    UINT32 Exe0_grp_Sel                            :  2;  // Bits 18:17
    UINT32 Exe1_grp_Sel                            :  2;  // Bits 20:19
    UINT32                                         :  11;  // Bits 31:21
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_VISA_MUX_SEL_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_CREDITS_INIT                     :  8;  // Bits 7:0
    UINT32 RSP_CREDITS_INIT                        :  8;  // Bits 15:8
    UINT32 RD_WR_CREDITS_INIT                      :  8;  // Bits 23:16
    UINT32 CREDITS_CONFIG_DONE                     :  1;  // Bits 24:24
    UINT32 RD_WR_CREDITS_OVERRIDE                  :  1;  // Bits 25:25
    UINT32 FORCE_ISM_ACTIVE                        :  1;  // Bits 26:26
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_CREDIT_CFG_STRUCT;

typedef union {
  struct {
    UINT32 DUMMYLow                                :  32;  // Bits 31:0
    UINT32 DUMMYHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CPGC_V_DUMMY_STRUCT;

typedef union {
  struct {
    UINT32 Address_Decode_Rotate_Repeats           :  6;  // Bits 5:0
    UINT32                                         :  18;  // Bits 23:6
    UINT32 Column_Addr_Invert_Select               :  2;  // Bits 25:24
    UINT32 Row_Addr_Invert_Select                  :  2;  // Bits 27:26
    UINT32 Bank_Addr_Invert_Select                 :  2;  // Bits 29:28
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_ADDRESS_CONTROL_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ADDRESS_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ADDRESS_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ADDRESS_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ADDRESS_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_DATA_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_DATA_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_DATA_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_DATA_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT32 Data_Select_Rotation_Repeats            :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_DATA_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Address_Decode_Rotate_Repeats_Current   :  6;  // Bits 5:0
    UINT32                                         :  10;  // Bits 15:6
    UINT32 Data_Select_Rotation_Repeats_Current    :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_ADDRESS_DATA_STATUS_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_1_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_2_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_3_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_4_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_5_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_6_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_7_STRUCT;

typedef union {
  struct {
    UINT32 Wait_Timer_Current                      :  16;  // Bits 15:0
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_ALGORITHM_WAIT_COUNT_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Wait_Time                               :  16;  // Bits 15:0
    UINT32                                         :  4;  // Bits 19:16
    UINT32 Timer                                   :  4;  // Bits 23:20
    UINT32 Wait_Clock_Frequency                    :  2;  // Bits 25:24
    UINT32                                         :  4;  // Bits 29:26
    UINT32 Select_Event                            :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Base_Repeats                            :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_BASE_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Base_Repeats_Current                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_BASE_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Base_Col_Repeats                        :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_BASE_COL_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Block_Repeats                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_BLOCK_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Block_Repeats_Current                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_BLOCK_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_8_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_9_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_10_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_11_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_12_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_13_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_14_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_15_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_16_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_17_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_18_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_19_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_20_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_21_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_22_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_COMMAND_INSTRUCTION_23_STRUCT;

typedef union {
  struct {
    UINT32 Hammer_Repeats                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_HAMMER_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Hammer_Repeats_Current                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_HAMMER_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_8_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_9_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_10_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_11_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_12_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_13_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_14_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_15_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_8_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_9_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_10_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_11_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Repeats                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_OFFSET_REPEATS_0_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Repeats                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_OFFSET_REPEATS_1_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Repeats_Current                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_OFFSET_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Low_Row                                 :  18;  // Bits 17:0
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_REGION_LOW_ROW_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Low_Col                                 :  9;  // Bits 10:2
    UINT32                                         :  21;  // Bits 31:11
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_REGION_LOW_COL_STRUCT;

typedef union {
  struct {
    UINT32                                         :  5;  // Bits 4:0
    UINT32 Block_Origin_Col_Current                :  10;  // Bits 14:5
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_BLOCK_ORIGIN_COL_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Block_Origin_Row_Current                :  18;  // Bits 17:0
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_BLOCK_ORIGIN_ROW_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32                                         :  5;  // Bits 4:0
    UINT32 Base_Col_Current                        :  10;  // Bits 14:5
    UINT32                                         :  9;  // Bits 23:15
    UINT32 Base_Rank_Current                       :  5;  // Bits 28:24
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_BASE_ADDRESS_COL_RANK_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Base_Row_Current                        :  18;  // Bits 17:0
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Base_Bank_Current                       :  5;  // Bits 28:24
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_BASE_ADDRESS_ROW_BANK_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32                                         :  5;  // Bits 4:0
    UINT32 Offset_Col_Current                      :  10;  // Bits 14:5
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_COL_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Row_Current                      :  18;  // Bits 17:0
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_OFFSET_ADDRESS_ROW_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Block_Size_Bits_Col                     :  5;  // Bits 4:0
    UINT32 Block_Size_Bits_Row                     :  5;  // Bits 9:5
    UINT32 Block_Size_Num_Banks                    :  5;  // Bits 14:10
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Region_Size_Bits_Col                    :  5;  // Bits 20:16
    UINT32 Region_Size_Bits_Row                    :  5;  // Bits 25:21
    UINT32 Block_Size_Num_Ranks                    :  5;  // Bits 30:26
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_ADDRESS_SIZE_STRUCT;

typedef union {
  struct {
    UINT32 Block_Col_Move_One_Col                  :  1;  // Bits 0:0
    UINT32 Block_Col_Move_Half_Block               :  1;  // Bits 1:1
    UINT32 Hammer_Inc_Rate                         :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Block_Row_Move_One_Row                  :  1;  // Bits 4:4
    UINT32 Block_Row_Move_Half_Block               :  1;  // Bits 5:5
    UINT32 Row_Inc                                 :  4;  // Bits 9:6
    UINT32                                         :  1;  // Bits 10:10
    UINT32 Col_Inc                                 :  4;  // Bits 14:11
    UINT32 Reserved_Bank_Inc                       :  3;  // Bits 17:15
    UINT32 Reserved_Rank_Inc                       :  3;  // Bits 20:18
    UINT32 Address_Order0_Inc_Rate                 :  1;  // Bits 21:21
    UINT32 Address_Inversion_Enable                :  4;  // Bits 25:22
    UINT32 Address_Inversion_Rate                  :  1;  // Bits 26:26
    UINT32 Addr_Prbs_Carry_Mode                    :  1;  // Bits 27:27
    UINT32 Addr_Prbs_Col_En                        :  1;  // Bits 28:28
    UINT32 Addr_Prbs_Row_En                        :  1;  // Bits 29:29
    UINT32 Addr_Prbs_Bnk_En                        :  1;  // Bits 30:30
    UINT32 Addr_Prbs_Rnk_En                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_BASE_ADDRESS_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Seed                :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Seed                  :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Seed                   :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Seed                  :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CPGC2_ADDRESS_PRBS_SEED_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Current             :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Current               :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Current                :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Current               :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CPGC2_ADDRESS_PRBS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Save                :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Save                  :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Save                   :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Save                  :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CPGC2_ADDRESS_PRBS_SAVE_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Poly                :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Poly                  :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Poly                   :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Poly                  :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CPGC2_ADDRESS_PRBS_POLY_STRUCT;

typedef union {
  struct {
    UINT32 Prescaler_for_Clock_Freq                :  10;  // Bits 9:0
    UINT32                                         :  6;  // Bits 15:10
    UINT32 Clock_Freq                              :  10;  // Bits 25:16
    UINT32                                         :  2;  // Bits 27:26
    UINT32 Increment_Value                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_WAIT_2_START_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Command_Instruction_Current      :  3;  // Bits 2:0
    UINT32 Offset_Address_Instruction_Current      :  3;  // Bits 5:3
    UINT32 Offset_Group_Instruction_Current        :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Command_Instruction_Current             :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Algorithm_Instruction_Current           :  3;  // Bits 17:15
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Data_Instruction_Current                :  2;  // Bits 25:24
    UINT32                                         :  2;  // Bits 27:26
    UINT32 Address_Instruction_Current             :  2;  // Bits 29:28
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_CMD_FSM_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 START_TEST                              :  1;  // Bits 0:0
    UINT32 STOP_TEST                               :  1;  // Bits 1:1
    UINT32 CLEAR_ERRORS                            :  1;  // Bits 2:2
    UINT32                                         :  5;  // Bits 7:3
    UINT32 SINGLE_CMD_MODE                         :  1;  // Bits 8:8
    UINT32 CONTINUE_SINGLE_MODE                    :  1;  // Bits 9:9
    UINT32 SINGLE_MARCH_ELEMENT_MODE               :  1;  // Bits 10:10
    UINT32                                         :  21;  // Bits 31:11
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_CTL_STRUCT;

typedef union {
  struct {
    UINT32                                         :  8;  // Bits 7:0
    UINT32 GLOBAL_CLEAR_ERR_BIND                   :  1;  // Bits 8:8
    UINT32 GLOBAL_STOP_ON_ERR_BIND                 :  1;  // Bits 9:9
    UINT32 GLOBAL_START_BIND                       :  1;  // Bits 10:10
    UINT32 GLOBAL_STOP_BIND                        :  1;  // Bits 11:11
    UINT32 INITIALIZATION_MODE                     :  3;  // Bits 14:12
    UINT32                                         :  7;  // Bits 21:15
    UINT32 REQUEST_DATA_SIZE                       :  1;  // Bits 22:22
    UINT32 STRICT_WR_TO_RD_ORDER                   :  1;  // Bits 23:23
    UINT32 CHANNEL_ASSIGN                          :  4;  // Bits 27:24
    UINT32                                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_CFG_A_STRUCT;

typedef union {
  struct {
    UINT32 START_DELAY                             :  10;  // Bits 9:0
    UINT32                                         :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_CFG_B_STRUCT;

typedef union {
  struct {
    UINT32                                         :  20;  // Bits 19:0
    UINT32 CREDITS_INITIALIZED                     :  1;  // Bits 20:20
    UINT32                                         :  3;  // Bits 23:21
    UINT32 TEST_ABORTED                            :  1;  // Bits 24:24
    UINT32 EVENT_NOT_SEEN                          :  1;  // Bits 25:25
    UINT32 ALGO_WAIT                               :  1;  // Bits 26:26
    UINT32 SINGLE_MODE_PAUSED                      :  1;  // Bits 27:27
    UINT32 ALGO_DONE                               :  1;  // Bits 28:28
    UINT32 START_TEST_DELAY_BUSY                   :  1;  // Bits 29:29
    UINT32 TEST_BUSY                               :  1;  // Bits 30:30
    UINT32 TEST_DONE                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_0_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_1_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_2_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_3_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_4_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_5_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_6_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_7_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_8_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_9_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_10_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_11_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_12_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_13_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_14_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_15_STRUCT;

typedef union {
  struct {
    UINT32 fail_excess0                            :  1;  // Bits 0:0
    UINT32 fail_any0                               :  1;  // Bits 1:1
    UINT32 fail_count0                             :  2;  // Bits 3:2
    UINT32 ECC_chunk0                              :  4;  // Bits 7:4
    UINT32 fail_excess1                            :  1;  // Bits 8:8
    UINT32 fail_any1                               :  1;  // Bits 9:9
    UINT32 fail_count1                             :  2;  // Bits 11:10
    UINT32 ECC_chunk1                              :  4;  // Bits 15:12
    UINT32 fail_excess2                            :  1;  // Bits 16:16
    UINT32 fail_any2                               :  1;  // Bits 17:17
    UINT32 fail_count2                             :  2;  // Bits 19:18
    UINT32 ECC_chunk2                              :  4;  // Bits 23:20
    UINT32 fail_excess3                            :  1;  // Bits 24:24
    UINT32 fail_any3                               :  1;  // Bits 25:25
    UINT32 fail_count3                             :  2;  // Bits 27:26
    UINT32 ECC_chunk3                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_ECC1_STRUCT;

typedef union {
  struct {
    UINT32 fail_excess4                            :  1;  // Bits 0:0
    UINT32 fail_any4                               :  1;  // Bits 1:1
    UINT32 fail_count4                             :  2;  // Bits 3:2
    UINT32 ECC_chunk4                              :  4;  // Bits 7:4
    UINT32 fail_excess5                            :  1;  // Bits 8:8
    UINT32 fail_any5                               :  1;  // Bits 9:9
    UINT32 fail_count5                             :  2;  // Bits 11:10
    UINT32 ECC_chunk5                              :  4;  // Bits 15:12
    UINT32 fail_excess6                            :  1;  // Bits 16:16
    UINT32 fail_any6                               :  1;  // Bits 17:17
    UINT32 fail_count6                             :  2;  // Bits 19:18
    UINT32 ECC_chunk6                              :  4;  // Bits 23:20
    UINT32 fail_excess7                            :  1;  // Bits 24:24
    UINT32 fail_any7                               :  1;  // Bits 25:25
    UINT32 fail_count7                             :  2;  // Bits 27:26
    UINT32 ECC_chunk7                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_CONTENT_ECC2_STRUCT;

typedef union {
  struct {
    UINT32 Read_Command_Count_Current              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Mask_First_N_Reads                      :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_MASK_ERRS_FIRST_N_READS_STRUCT;

typedef union {
  struct {
    UINT32 BitmapValid                             :  1;  // Bits 0:0
    UINT32 SummaryValid                            :  1;  // Bits 1:1
    UINT32 RasterRepoFull                          :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 NumErrLogged                            :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 FailExcessAll                           :  1;  // Bits 8:8
    UINT32 FailAnyAll                              :  1;  // Bits 9:9
    UINT32 FailMax                                 :  2;  // Bits 11:10
    UINT32                                         :  4;  // Bits 15:12
    UINT32 RasterRepoMode                          :  2;  // Bits 17:16
    UINT32                                         :  12;  // Bits 29:18
    UINT32 StopOnRaster                            :  1;  // Bits 30:30
    UINT32 RasterRepoClear                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_RASTER_REPO_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Error_Summary                           :  16;  // Bits 15:0
    UINT32 Algorithm_Summary                       :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_ERR_SUMMARY_A_STRUCT;

typedef union {
  struct {
    UINT32 Algorithm_Summary                       :  2;  // Bits 1:0
    UINT32 Physical_Address_Summary                :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_ERR_SUMMARY_B_STRUCT;

typedef union {
  struct {
    UINT32 Physical_Address_Summary                :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC2_ERR_SUMMARY_C_STRUCT;

typedef union {
  struct {
    UINT32 BUF_PNTR_INC_RATE                       :  6;  // Bits 5:0
    UINT32 BUF_PNTR_INC_SCALE                      :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 BUF_STRT_PNTR                           :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 BUF_END_PNTR                            :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 WR_BUF_PTR                              :  4;  // Bits 23:20
    UINT32 RD_BUF_PTR                              :  4;  // Bits 27:24
    UINT32                                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_BUF_CTL_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ0_MODE                            :  2;  // Bits 1:0
    UINT32                                         :  1;  // Bits 2:2
    UINT32 UNISEQ1_MODE                            :  2;  // Bits 4:3
    UINT32                                         :  1;  // Bits 5:5
    UINT32 UNISEQ2_MODE                            :  2;  // Bits 7:6
    UINT32 WRITE_ADDRESS_AS_DATA                   :  1;  // Bits 8:8
    UINT32 READ_ADDRESS_AS_DATA                    :  1;  // Bits 9:9
    UINT32                                         :  3;  // Bits 12:10
    UINT32 ECC_DISABLE                             :  1;  // Bits 13:13
    UINT32 ECC_REPLACE_BYTE_CONTROL                :  1;  // Bits 14:14
    UINT32 ECC_DATA_SOURCE_SEL                     :  1;  // Bits 15:15
    UINT32 SAVE_LFSR_SEED_RATE                     :  8;  // Bits 23:16
    UINT32 RELOAD_LFSR_SEED_RATE                   :  5;  // Bits 28:24
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_CFG_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 UNISEQ0_LFSR_POLYNOMIAL_SIZE            :  3;  // Bits 4:2
    UINT32                                         :  2;  // Bits 6:5
    UINT32 UNISEQ0_LFSR_STAGGER                    :  1;  // Bits 7:7
    UINT32                                         :  2;  // Bits 9:8
    UINT32 UNISEQ1_LFSR_POLYNOMIAL_SIZE            :  3;  // Bits 12:10
    UINT32                                         :  2;  // Bits 14:13
    UINT32 UNISEQ1_LFSR_STAGGER                    :  1;  // Bits 15:15
    UINT32                                         :  2;  // Bits 17:16
    UINT32 UNISEQ2_LFSR_POLYNOMIAL_SIZE            :  3;  // Bits 20:18
    UINT32                                         :  2;  // Bits 22:21
    UINT32 UNISEQ2_LFSR_STAGGER                    :  1;  // Bits 23:23
    UINT32 LANE_ROTATE_RATE                        :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_XTRA_LFSR_CFG_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_0_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_1_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_2_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32 FREQ_SWEEP_EN                           :  1;  // Bits 1:1
    UINT32 L_COUNT_EN                              :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 M_CNT                                   :  8;  // Bits 23:16
    UINT32 N_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_LMN_0_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32 FREQ_SWEEP_EN                           :  1;  // Bits 1:1
    UINT32 L_COUNT_EN                              :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 M_CNT                                   :  8;  // Bits 23:16
    UINT32 N_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_LMN_1_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32 FREQ_SWEEP_EN                           :  1;  // Bits 1:1
    UINT32 L_COUNT_EN                              :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 M_CNT                                   :  8;  // Bits 23:16
    UINT32 N_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_LMN_2_STRUCT;

typedef union {
  struct {
    UINT32 ECC_INV_DC_MASK                         :  8;  // Bits 7:0
    UINT32 MASK_ROTATE_RATE                        :  4;  // Bits 11:8
    UINT32                                         :  4;  // Bits 15:12
    UINT32 BYTEGROUP_MAPPING                       :  9;  // Bits 24:16
    UINT32                                         :  4;  // Bits 28:25
    UINT32 DC_POL                                  :  1;  // Bits 29:29
    UINT32 DC_OR_INV                               :  1;  // Bits 30:30
    UINT32 MASK_ROTATE_EN                          :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_INVDCCTL_STRUCT;

typedef union {
  struct {
    UINT32 DATA_INV_DC_MASK_LO                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_INV_DC_MASK_LO_STRUCT;

typedef union {
  struct {
    UINT32 DATA_INV_DC_MASK_HI                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_INV_DC_MASK_HI_STRUCT;

typedef union {
  struct {
    UINT32 DATA_MASK_LO                            :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_DRAMDM_STRUCT;

typedef union {
  struct {
    UINT32 DATA_MASK_HI                            :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_XDRAMDM_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_WRSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_WRSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_WRSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_WRSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_WRSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_RDSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_RDSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_RDSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_RDSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_RDSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 LMN_WRSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_LMN_WRSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 LMN_WRSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_LMN_WRSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 LMN_WRSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_LMN_WRSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 LMN_RDSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_LMN_RDSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 LMN_RDSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_LMN_RDSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 LMN_RDSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_LMN_RDSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_WRSAVE_1_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_WRSAVE_2_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_RDSAVE_0_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_RDSAVE_1_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_UNISEQ_RDSAVE_2_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_0_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_1_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_2_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_3_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_4_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_5_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_6_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_7_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_8_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_9_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_10_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_11_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_12_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_13_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_14_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_DPAT_EXTBUF_15_STRUCT;

typedef union {
  struct {
    UINT32 STOP_ON_N                               :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 BE_TRAIN_ERR_EN                         :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 STOP_ON_ERROR_CTL                       :  2;  // Bits 13:12
    UINT32                                         :  2;  // Bits 15:14
    UINT32 ERRCHK_MASK_CHUNK                       :  8;  // Bits 23:16
    UINT32 ERRCHK_MASK_CACHELINE                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CTL_STRUCT;

typedef union {
  struct {
    UINT32 DATA_ERRCHK_MASK_LO                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_LNEN_LO_STRUCT;

typedef union {
  struct {
    UINT32 DATA_ERRCHK_MASK_HI                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_LNEN_HI_STRUCT;

typedef union {
  struct {
    UINT32 ECC_ERRCHK_MASK                         :  8;  // Bits 7:0
    UINT32                                         :  8;  // Bits 15:8
    UINT32 RANK_ERRCHK_MASK                        :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_XLNEN_STRUCT;

typedef union {
  struct {
    UINT32 LANE_ERR_STAT_LO                        :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_STAT03_STRUCT;

typedef union {
  struct {
    UINT32 LANE_ERR_STAT_HI                        :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_STAT47_STRUCT;

typedef union {
  struct {
    UINT32 ECC_LANE_ERR_STAT                       :  8;  // Bits 7:0
    UINT32 CHUNK_ERR_STAT                          :  8;  // Bits 15:8
    UINT32 RANK_ERR_STAT                           :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_STRUCT;

typedef union {
  struct {
    UINT32 BYTEGRP_ERR_STAT                        :  8;  // Bits 7:0
    UINT32 ECCGRP_ERR_STAT                         :  1;  // Bits 8:8
    UINT32                                         :  11;  // Bits 19:9
    UINT32 RD_CHUNK_NUM_STAT                       :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Nth_ERROR                               :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTRCTL_0_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTRCTL_1_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTRCTL_2_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTRCTL_3_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTRCTL_4_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTRCTL_5_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTRCTL_6_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTRCTL_7_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTRCTL_8_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTR_0_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTR_1_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTR_2_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTR_3_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTR_4_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTR_5_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTR_6_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTR_7_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTR_8_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER_OVERFLOW                  :  9;  // Bits 8:0
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_CNTR_OV_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_STATUS                            :  1;  // Bits 0:0
    UINT32 TEST_IN_PROGRESS                        :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_ERR_TEST_ERR_STAT_STRUCT;

typedef union {
  struct {
    UINT32 DUMMYLow                                :  32;  // Bits 31:0
    UINT32 DUMMYHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CPGC_D_DUMMY_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK0_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_RANK1_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_RANK2_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_RANK3_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_RANK4_MAPPING                       :  5;  // Bits 24:20
    UINT32 L2P_RANK5_MAPPING                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK6_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_RANK7_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_RANK8_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_RANK9_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_RANK10_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK11_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK12_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK13_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_RANK14_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_RANK15_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_RANK16_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK17_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK18_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK19_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_RANK20_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_RANK21_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_RANK22_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK23_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK24_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK25_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_RANK26_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_RANK27_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_RANK28_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK29_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK30_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK31_MAPPING                      :  5;  // Bits 9:5
    UINT32                                         :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK0_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_BANK1_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_BANK2_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_BANK3_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_BANK4_MAPPING                       :  5;  // Bits 24:20
    UINT32 L2P_BANK5_MAPPING                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK6_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_BANK7_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_BANK8_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_BANK9_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_BANK10_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK11_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK12_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK13_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_BANK14_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_BANK15_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_BANK16_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK17_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK18_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK19_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_BANK20_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_BANK21_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_BANK22_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK23_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK24_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK25_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_BANK26_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_BANK27_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_BANK28_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK29_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK30_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK31_MAPPING                      :  5;  // Bits 9:5
    UINT32                                         :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK0_SWIZZLE                       :  5;  // Bits 4:0
    UINT32 L2P_RANK1_SWIZZLE                       :  5;  // Bits 9:5
    UINT32 L2P_RANK2_SWIZZLE                       :  5;  // Bits 14:10
    UINT32 L2P_RANK3_SWIZZLE                       :  5;  // Bits 19:15
    UINT32 L2P_RANK4_SWIZZLE                       :  5;  // Bits 24:20
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK0_SWIZZLE                       :  5;  // Bits 4:0
    UINT32 L2P_BANK1_SWIZZLE                       :  5;  // Bits 9:5
    UINT32 L2P_BANK2_SWIZZLE                       :  5;  // Bits 14:10
    UINT32 L2P_BANK3_SWIZZLE                       :  5;  // Bits 19:15
    UINT32 L2P_BANK4_SWIZZLE                       :  5;  // Bits 24:20
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW0_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_ROW1_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_ROW2_SWIZZLE                        :  5;  // Bits 14:10
    UINT32 L2P_ROW3_SWIZZLE                        :  5;  // Bits 19:15
    UINT32 L2P_ROW4_SWIZZLE                        :  5;  // Bits 24:20
    UINT32 L2P_ROW5_SWIZZLE                        :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW6_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_ROW7_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_ROW8_SWIZZLE                        :  5;  // Bits 14:10
    UINT32 L2P_ROW9_SWIZZLE                        :  5;  // Bits 19:15
    UINT32 L2P_ROW10_SWIZZLE                       :  5;  // Bits 24:20
    UINT32 L2P_ROW11_SWIZZLE                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW12_SWIZZLE                       :  5;  // Bits 4:0
    UINT32 L2P_ROW13_SWIZZLE                       :  5;  // Bits 9:5
    UINT32 L2P_ROW14_SWIZZLE                       :  5;  // Bits 14:10
    UINT32 L2P_ROW15_SWIZZLE                       :  5;  // Bits 19:15
    UINT32 L2P_ROW16_SWIZZLE                       :  5;  // Bits 24:20
    UINT32 L2P_ROW17_SWIZZLE                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW0_XOR_SWIZZLE                    :  5;  // Bits 4:0
    UINT32 L2P_ROW1_XOR_SWIZZLE                    :  5;  // Bits 9:5
    UINT32 L2P_ROW2_XOR_SWIZZLE                    :  5;  // Bits 14:10
    UINT32 L2P_ROW3_XOR_SWIZZLE                    :  5;  // Bits 19:15
    UINT32                                         :  9;  // Bits 28:20
    UINT32 ADDR_DQ_INV_EN                          :  1;  // Bits 29:29
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_STRUCT;

typedef union {
  struct {
    UINT32 L2P_COL0_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_COL1_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_COL2_SWIZZLE                        :  5;  // Bits 14:10
    UINT32 L2P_COL3_SWIZZLE                        :  5;  // Bits 19:15
    UINT32 L2P_COL4_SWIZZLE                        :  5;  // Bits 24:20
    UINT32 L2P_COL5_SWIZZLE                        :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_COL6_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_COL7_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_COL8_SWIZZLE                        :  5;  // Bits 14:10
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_ROW_ADDR_DQ_MAP0_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CPGC_SEQ_ROW_ADDR_DQ_MAP1_STRUCT;

typedef union {
  struct {
    UINT32 DUMMYLow                                :  32;  // Bits 31:0
    UINT32 DUMMYHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CPGC_A_DUMMY_STRUCT;

typedef union {
  struct {
    UINT32 Address_Decode_Rotate_Repeats           :  6;  // Bits 5:0
    UINT32                                         :  18;  // Bits 23:6
    UINT32 Column_Addr_Invert_Select               :  2;  // Bits 25:24
    UINT32 Row_Addr_Invert_Select                  :  2;  // Bits 27:26
    UINT32 Bank_Addr_Invert_Select                 :  2;  // Bits 29:28
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_ADDRESS_CONTROL_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ADDRESS_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ADDRESS_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ADDRESS_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Address_Order                           :  3;  // Bits 2:0
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Address_Decode_Enable                   :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ADDRESS_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_DATA_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_DATA_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_DATA_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Data_Background                         :  4;  // Bits 3:0
    UINT8  Background_Mode                         :  1;  // Bits 4:4
    UINT8  Alt_Data_Rotate_En                      :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_DATA_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT32 Data_Select_Rotation_Repeats            :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_DATA_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Address_Decode_Rotate_Repeats_Current   :  6;  // Bits 5:0
    UINT32                                         :  10;  // Bits 15:6
    UINT32 Data_Select_Rotation_Repeats_Current    :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_ADDRESS_DATA_STATUS_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  Command_Start_Pointer                   :  5;  // Bits 4:0
    UINT8  Inverse_Direction                       :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_1_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_2_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_3_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_4_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_5_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_6_STRUCT;

typedef union {
  struct {
    UINT8  FastY_Init                              :  1;  // Bits 0:0
    UINT8  Base_Range_Row                          :  1;  // Bits 1:1
    UINT8  Wait_Count_Clear                        :  1;  // Bits 2:2
    UINT8  Wait_Count_Start                        :  1;  // Bits 3:3
    UINT8  Wait_Event_Start                        :  1;  // Bits 4:4
    UINT8  Deselect_On                             :  1;  // Bits 5:5
    UINT8  Select_On                               :  1;  // Bits 6:6
    UINT8  BE_Train_Err_En                         :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_7_STRUCT;

typedef union {
  struct {
    UINT32 Wait_Timer_Current                      :  16;  // Bits 15:0
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_ALGORITHM_WAIT_COUNT_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Wait_Time                               :  16;  // Bits 15:0
    UINT32                                         :  4;  // Bits 19:16
    UINT32 Timer                                   :  4;  // Bits 23:20
    UINT32 Wait_Clock_Frequency                    :  2;  // Bits 25:24
    UINT32                                         :  4;  // Bits 29:26
    UINT32 Select_Event                            :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Base_Repeats                            :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_BASE_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Base_Repeats_Current                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_BASE_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Base_Col_Repeats                        :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_BASE_COL_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Block_Repeats                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_BLOCK_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Block_Repeats_Current                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_BLOCK_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_8_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_9_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_10_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_11_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_12_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_13_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_14_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_15_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_16_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_17_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_18_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_19_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_20_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_21_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_22_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Offset_Group_Srsp                       :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8  Address_Decode_or_PRBS_En               :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_COMMAND_INSTRUCTION_23_STRUCT;

typedef union {
  struct {
    UINT32 Hammer_Repeats                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_HAMMER_REPEATS_STRUCT;

typedef union {
  struct {
    UINT32 Hammer_Repeats_Current                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_HAMMER_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_8_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_9_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_10_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_11_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_12_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_13_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_14_STRUCT;

typedef union {
  struct {
    UINT8  Periodic_Data_Inv_Adj                   :  2;  // Bits 1:0
    UINT8  Periodic_Data_Inv_En                    :  1;  // Bits 2:2
    UINT8  Address_Direction                       :  3;  // Bits 5:3
    UINT8  Stripe                                  :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_INSTRUCTION_15_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_0_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_1_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_2_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_3_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_4_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_5_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_6_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_7_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_8_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_9_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_10_STRUCT;

typedef union {
  struct {
    UINT8  WriteCmd                                :  1;  // Bits 0:0
    UINT8  Srsp                                    :  1;  // Bits 1:1
    UINT8  Offset                                  :  1;  // Bits 2:2
    UINT8  Hammer                                  :  1;  // Bits 3:3
    UINT8  Alternate_Data                          :  1;  // Bits 4:4
    UINT8                                          :  1;  // Bits 5:5
    UINT8  Invert_Data                             :  1;  // Bits 6:6
    UINT8  Last                                    :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CPGC2_OFFSET_COMMAND_INSTRUCTION_11_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Repeats                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_OFFSET_REPEATS_0_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Repeats                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_OFFSET_REPEATS_1_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Repeats_Current                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_OFFSET_REPEATS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Low_Row                                 :  18;  // Bits 17:0
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_REGION_LOW_ROW_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Low_Col                                 :  9;  // Bits 10:2
    UINT32                                         :  21;  // Bits 31:11
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_REGION_LOW_COL_STRUCT;

typedef union {
  struct {
    UINT32                                         :  5;  // Bits 4:0
    UINT32 Block_Origin_Col_Current                :  10;  // Bits 14:5
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_BLOCK_ORIGIN_COL_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Block_Origin_Row_Current                :  18;  // Bits 17:0
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_BLOCK_ORIGIN_ROW_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32                                         :  5;  // Bits 4:0
    UINT32 Base_Col_Current                        :  10;  // Bits 14:5
    UINT32                                         :  9;  // Bits 23:15
    UINT32 Base_Rank_Current                       :  5;  // Bits 28:24
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_BASE_ADDRESS_COL_RANK_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Base_Row_Current                        :  18;  // Bits 17:0
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Base_Bank_Current                       :  5;  // Bits 28:24
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_BASE_ADDRESS_ROW_BANK_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32                                         :  5;  // Bits 4:0
    UINT32 Offset_Col_Current                      :  10;  // Bits 14:5
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_COL_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Row_Current                      :  18;  // Bits 17:0
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_OFFSET_ADDRESS_ROW_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Block_Size_Bits_Col                     :  5;  // Bits 4:0
    UINT32 Block_Size_Bits_Row                     :  5;  // Bits 9:5
    UINT32 Block_Size_Num_Banks                    :  5;  // Bits 14:10
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Region_Size_Bits_Col                    :  5;  // Bits 20:16
    UINT32 Region_Size_Bits_Row                    :  5;  // Bits 25:21
    UINT32 Block_Size_Num_Ranks                    :  5;  // Bits 30:26
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_ADDRESS_SIZE_STRUCT;

typedef union {
  struct {
    UINT32 Block_Col_Move_One_Col                  :  1;  // Bits 0:0
    UINT32 Block_Col_Move_Half_Block               :  1;  // Bits 1:1
    UINT32 Hammer_Inc_Rate                         :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Block_Row_Move_One_Row                  :  1;  // Bits 4:4
    UINT32 Block_Row_Move_Half_Block               :  1;  // Bits 5:5
    UINT32 Row_Inc                                 :  4;  // Bits 9:6
    UINT32                                         :  1;  // Bits 10:10
    UINT32 Col_Inc                                 :  4;  // Bits 14:11
    UINT32 Reserved_Bank_Inc                       :  3;  // Bits 17:15
    UINT32 Reserved_Rank_Inc                       :  3;  // Bits 20:18
    UINT32 Address_Order0_Inc_Rate                 :  1;  // Bits 21:21
    UINT32 Address_Inversion_Enable                :  4;  // Bits 25:22
    UINT32 Address_Inversion_Rate                  :  1;  // Bits 26:26
    UINT32 Addr_Prbs_Carry_Mode                    :  1;  // Bits 27:27
    UINT32 Addr_Prbs_Col_En                        :  1;  // Bits 28:28
    UINT32 Addr_Prbs_Row_En                        :  1;  // Bits 29:29
    UINT32 Addr_Prbs_Bnk_En                        :  1;  // Bits 30:30
    UINT32 Addr_Prbs_Rnk_En                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_BASE_ADDRESS_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Seed                :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Seed                  :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Seed                   :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Seed                  :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CPGC2_ADDRESS_PRBS_SEED_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Current             :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Current               :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Current                :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Current               :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CPGC2_ADDRESS_PRBS_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Save                :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Save                  :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Save                   :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Save                  :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CPGC2_ADDRESS_PRBS_SAVE_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 Address_PRBS_Column_Poly                :  9;  // Bits 10:2
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Address_PRBS_Rank_Poly                  :  5;  // Bits 20:16
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Address_PRBS_Row_Poly                   :  18;  // Bits 49:32
    UINT32                                         :  6;  // Bits 55:50
    UINT32 Address_PRBS_Bank_Poly                  :  5;  // Bits 60:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CPGC2_ADDRESS_PRBS_POLY_STRUCT;

typedef union {
  struct {
    UINT32 Prescaler_for_Clock_Freq                :  10;  // Bits 9:0
    UINT32                                         :  6;  // Bits 15:10
    UINT32 Clock_Freq                              :  10;  // Bits 25:16
    UINT32                                         :  2;  // Bits 27:26
    UINT32 Increment_Value                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_WAIT_2_START_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Command_Instruction_Current      :  3;  // Bits 2:0
    UINT32 Offset_Address_Instruction_Current      :  3;  // Bits 5:3
    UINT32 Offset_Group_Instruction_Current        :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Command_Instruction_Current             :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Algorithm_Instruction_Current           :  3;  // Bits 17:15
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Data_Instruction_Current                :  2;  // Bits 25:24
    UINT32                                         :  2;  // Bits 27:26
    UINT32 Address_Instruction_Current             :  2;  // Bits 29:28
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_CMD_FSM_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 START_TEST                              :  1;  // Bits 0:0
    UINT32 STOP_TEST                               :  1;  // Bits 1:1
    UINT32 CLEAR_ERRORS                            :  1;  // Bits 2:2
    UINT32                                         :  5;  // Bits 7:3
    UINT32 SINGLE_CMD_MODE                         :  1;  // Bits 8:8
    UINT32 CONTINUE_SINGLE_MODE                    :  1;  // Bits 9:9
    UINT32 SINGLE_MARCH_ELEMENT_MODE               :  1;  // Bits 10:10
    UINT32                                         :  21;  // Bits 31:11
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_CTL_STRUCT;

typedef union {
  struct {
    UINT32                                         :  8;  // Bits 7:0
    UINT32 GLOBAL_CLEAR_ERR_BIND                   :  1;  // Bits 8:8
    UINT32 GLOBAL_STOP_ON_ERR_BIND                 :  1;  // Bits 9:9
    UINT32 GLOBAL_START_BIND                       :  1;  // Bits 10:10
    UINT32 GLOBAL_STOP_BIND                        :  1;  // Bits 11:11
    UINT32 INITIALIZATION_MODE                     :  3;  // Bits 14:12
    UINT32                                         :  7;  // Bits 21:15
    UINT32 REQUEST_DATA_SIZE                       :  1;  // Bits 22:22
    UINT32 STRICT_WR_TO_RD_ORDER                   :  1;  // Bits 23:23
    UINT32 CHANNEL_ASSIGN                          :  4;  // Bits 27:24
    UINT32                                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_CFG_A_STRUCT;

typedef union {
  struct {
    UINT32 START_DELAY                             :  10;  // Bits 9:0
    UINT32                                         :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_CFG_B_STRUCT;

typedef union {
  struct {
    UINT32                                         :  20;  // Bits 19:0
    UINT32 CREDITS_INITIALIZED                     :  1;  // Bits 20:20
    UINT32                                         :  3;  // Bits 23:21
    UINT32 TEST_ABORTED                            :  1;  // Bits 24:24
    UINT32 EVENT_NOT_SEEN                          :  1;  // Bits 25:25
    UINT32 ALGO_WAIT                               :  1;  // Bits 26:26
    UINT32 SINGLE_MODE_PAUSED                      :  1;  // Bits 27:27
    UINT32 ALGO_DONE                               :  1;  // Bits 28:28
    UINT32 START_TEST_DELAY_BUSY                   :  1;  // Bits 29:29
    UINT32 TEST_BUSY                               :  1;  // Bits 30:30
    UINT32 TEST_DONE                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_0_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_1_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_2_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_3_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_4_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_5_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_6_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_7_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_8_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_9_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_10_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_11_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_12_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_13_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_14_STRUCT;

typedef union {
  struct {
    UINT32 Content                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_15_STRUCT;

typedef union {
  struct {
    UINT32 fail_excess0                            :  1;  // Bits 0:0
    UINT32 fail_any0                               :  1;  // Bits 1:1
    UINT32 fail_count0                             :  2;  // Bits 3:2
    UINT32 ECC_chunk0                              :  4;  // Bits 7:4
    UINT32 fail_excess1                            :  1;  // Bits 8:8
    UINT32 fail_any1                               :  1;  // Bits 9:9
    UINT32 fail_count1                             :  2;  // Bits 11:10
    UINT32 ECC_chunk1                              :  4;  // Bits 15:12
    UINT32 fail_excess2                            :  1;  // Bits 16:16
    UINT32 fail_any2                               :  1;  // Bits 17:17
    UINT32 fail_count2                             :  2;  // Bits 19:18
    UINT32 ECC_chunk2                              :  4;  // Bits 23:20
    UINT32 fail_excess3                            :  1;  // Bits 24:24
    UINT32 fail_any3                               :  1;  // Bits 25:25
    UINT32 fail_count3                             :  2;  // Bits 27:26
    UINT32 ECC_chunk3                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_ECC1_STRUCT;

typedef union {
  struct {
    UINT32 fail_excess4                            :  1;  // Bits 0:0
    UINT32 fail_any4                               :  1;  // Bits 1:1
    UINT32 fail_count4                             :  2;  // Bits 3:2
    UINT32 ECC_chunk4                              :  4;  // Bits 7:4
    UINT32 fail_excess5                            :  1;  // Bits 8:8
    UINT32 fail_any5                               :  1;  // Bits 9:9
    UINT32 fail_count5                             :  2;  // Bits 11:10
    UINT32 ECC_chunk5                              :  4;  // Bits 15:12
    UINT32 fail_excess6                            :  1;  // Bits 16:16
    UINT32 fail_any6                               :  1;  // Bits 17:17
    UINT32 fail_count6                             :  2;  // Bits 19:18
    UINT32 ECC_chunk6                              :  4;  // Bits 23:20
    UINT32 fail_excess7                            :  1;  // Bits 24:24
    UINT32 fail_any7                               :  1;  // Bits 25:25
    UINT32 fail_count7                             :  2;  // Bits 27:26
    UINT32 ECC_chunk7                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_CONTENT_ECC2_STRUCT;

typedef union {
  struct {
    UINT32 Read_Command_Count_Current              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_READ_COMMAND_COUNT_CURRENT_STRUCT;

typedef union {
  struct {
    UINT32 Mask_First_N_Reads                      :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_MASK_ERRS_FIRST_N_READS_STRUCT;

typedef union {
  struct {
    UINT32 BitmapValid                             :  1;  // Bits 0:0
    UINT32 SummaryValid                            :  1;  // Bits 1:1
    UINT32 RasterRepoFull                          :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 NumErrLogged                            :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 FailExcessAll                           :  1;  // Bits 8:8
    UINT32 FailAnyAll                              :  1;  // Bits 9:9
    UINT32 FailMax                                 :  2;  // Bits 11:10
    UINT32                                         :  4;  // Bits 15:12
    UINT32 RasterRepoMode                          :  2;  // Bits 17:16
    UINT32                                         :  12;  // Bits 29:18
    UINT32 StopOnRaster                            :  1;  // Bits 30:30
    UINT32 RasterRepoClear                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_RASTER_REPO_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Error_Summary                           :  16;  // Bits 15:0
    UINT32 Algorithm_Summary                       :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_ERR_SUMMARY_A_STRUCT;

typedef union {
  struct {
    UINT32 Algorithm_Summary                       :  2;  // Bits 1:0
    UINT32 Physical_Address_Summary                :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_ERR_SUMMARY_B_STRUCT;

typedef union {
  struct {
    UINT32 Physical_Address_Summary                :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC2_ERR_SUMMARY_C_STRUCT;

typedef union {
  struct {
    UINT32 BUF_PNTR_INC_RATE                       :  6;  // Bits 5:0
    UINT32 BUF_PNTR_INC_SCALE                      :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 BUF_STRT_PNTR                           :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 BUF_END_PNTR                            :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 WR_BUF_PTR                              :  4;  // Bits 23:20
    UINT32 RD_BUF_PTR                              :  4;  // Bits 27:24
    UINT32                                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_BUF_CTL_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ0_MODE                            :  2;  // Bits 1:0
    UINT32                                         :  1;  // Bits 2:2
    UINT32 UNISEQ1_MODE                            :  2;  // Bits 4:3
    UINT32                                         :  1;  // Bits 5:5
    UINT32 UNISEQ2_MODE                            :  2;  // Bits 7:6
    UINT32 WRITE_ADDRESS_AS_DATA                   :  1;  // Bits 8:8
    UINT32 READ_ADDRESS_AS_DATA                    :  1;  // Bits 9:9
    UINT32                                         :  3;  // Bits 12:10
    UINT32 ECC_DISABLE                             :  1;  // Bits 13:13
    UINT32 ECC_REPLACE_BYTE_CONTROL                :  1;  // Bits 14:14
    UINT32 ECC_DATA_SOURCE_SEL                     :  1;  // Bits 15:15
    UINT32 SAVE_LFSR_SEED_RATE                     :  8;  // Bits 23:16
    UINT32 RELOAD_LFSR_SEED_RATE                   :  5;  // Bits 28:24
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_CFG_STRUCT;

typedef union {
  struct {
    UINT32                                         :  2;  // Bits 1:0
    UINT32 UNISEQ0_LFSR_POLYNOMIAL_SIZE            :  3;  // Bits 4:2
    UINT32                                         :  2;  // Bits 6:5
    UINT32 UNISEQ0_LFSR_STAGGER                    :  1;  // Bits 7:7
    UINT32                                         :  2;  // Bits 9:8
    UINT32 UNISEQ1_LFSR_POLYNOMIAL_SIZE            :  3;  // Bits 12:10
    UINT32                                         :  2;  // Bits 14:13
    UINT32 UNISEQ1_LFSR_STAGGER                    :  1;  // Bits 15:15
    UINT32                                         :  2;  // Bits 17:16
    UINT32 UNISEQ2_LFSR_POLYNOMIAL_SIZE            :  3;  // Bits 20:18
    UINT32                                         :  2;  // Bits 22:21
    UINT32 UNISEQ2_LFSR_STAGGER                    :  1;  // Bits 23:23
    UINT32 LANE_ROTATE_RATE                        :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_XTRA_LFSR_CFG_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_0_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_1_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_2_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32 FREQ_SWEEP_EN                           :  1;  // Bits 1:1
    UINT32 L_COUNT_EN                              :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 M_CNT                                   :  8;  // Bits 23:16
    UINT32 N_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_LMN_0_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32 FREQ_SWEEP_EN                           :  1;  // Bits 1:1
    UINT32 L_COUNT_EN                              :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 M_CNT                                   :  8;  // Bits 23:16
    UINT32 N_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_LMN_1_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32 FREQ_SWEEP_EN                           :  1;  // Bits 1:1
    UINT32 L_COUNT_EN                              :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 M_CNT                                   :  8;  // Bits 23:16
    UINT32 N_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_LMN_2_STRUCT;

typedef union {
  struct {
    UINT32 ECC_INV_DC_MASK                         :  8;  // Bits 7:0
    UINT32 MASK_ROTATE_RATE                        :  4;  // Bits 11:8
    UINT32                                         :  4;  // Bits 15:12
    UINT32 BYTEGROUP_MAPPING                       :  9;  // Bits 24:16
    UINT32                                         :  4;  // Bits 28:25
    UINT32 DC_POL                                  :  1;  // Bits 29:29
    UINT32 DC_OR_INV                               :  1;  // Bits 30:30
    UINT32 MASK_ROTATE_EN                          :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_INVDCCTL_STRUCT;

typedef union {
  struct {
    UINT32 DATA_INV_DC_MASK_LO                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_INV_DC_MASK_LO_STRUCT;

typedef union {
  struct {
    UINT32 DATA_INV_DC_MASK_HI                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_INV_DC_MASK_HI_STRUCT;

typedef union {
  struct {
    UINT32 DATA_MASK_LO                            :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_DRAMDM_STRUCT;

typedef union {
  struct {
    UINT32 DATA_MASK_HI                            :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_XDRAMDM_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_WRSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_WRSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_WRSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_WRSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_WRSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_WRSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_RDSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_RDSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_RDSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_RDSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 UNISEQ_RDSTAT                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_RDSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 LMN_WRSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_LMN_WRSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 LMN_WRSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_LMN_WRSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 LMN_WRSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_LMN_WRSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 LMN_RDSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_LMN_RDSTAT_0_STRUCT;

typedef union {
  struct {
    UINT32 LMN_RDSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_LMN_RDSTAT_1_STRUCT;

typedef union {
  struct {
    UINT32 LMN_RDSTAT                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_LMN_RDSTAT_2_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_WRSAVE_0_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_WRSAVE_1_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_WRSAVE_2_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_RDSAVE_0_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_RDSAVE_1_STRUCT;

typedef union {
  struct {
    UINT32 PATTERN_BUFFER                          :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_UNISEQ_RDSAVE_2_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_0_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_1_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_2_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_3_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_4_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_5_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_6_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_7_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_8_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_9_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_10_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_11_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_12_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_13_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_14_STRUCT;

typedef union {
  struct {
    UINT32 DATA_LINE0                              :  8;  // Bits 7:0
    UINT32 DATA_LINE1                              :  8;  // Bits 15:8
    UINT32 DATA_LINE2                              :  8;  // Bits 23:16
    UINT32 DATA_LINE3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_DPAT_EXTBUF_15_STRUCT;

typedef union {
  struct {
    UINT32 STOP_ON_N                               :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 BE_TRAIN_ERR_EN                         :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 STOP_ON_ERROR_CTL                       :  2;  // Bits 13:12
    UINT32                                         :  2;  // Bits 15:14
    UINT32 ERRCHK_MASK_CHUNK                       :  8;  // Bits 23:16
    UINT32 ERRCHK_MASK_CACHELINE                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CTL_STRUCT;

typedef union {
  struct {
    UINT32 DATA_ERRCHK_MASK_LO                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_LNEN_LO_STRUCT;

typedef union {
  struct {
    UINT32 DATA_ERRCHK_MASK_HI                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_LNEN_HI_STRUCT;

typedef union {
  struct {
    UINT32 ECC_ERRCHK_MASK                         :  8;  // Bits 7:0
    UINT32                                         :  8;  // Bits 15:8
    UINT32 RANK_ERRCHK_MASK                        :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_XLNEN_STRUCT;

typedef union {
  struct {
    UINT32 LANE_ERR_STAT_LO                        :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_STAT03_STRUCT;

typedef union {
  struct {
    UINT32 LANE_ERR_STAT_HI                        :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_STAT47_STRUCT;

typedef union {
  struct {
    UINT32 ECC_LANE_ERR_STAT                       :  8;  // Bits 7:0
    UINT32 CHUNK_ERR_STAT                          :  8;  // Bits 15:8
    UINT32 RANK_ERR_STAT                           :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_ECC_CHNK_RANK_STAT_STRUCT;

typedef union {
  struct {
    UINT32 BYTEGRP_ERR_STAT                        :  8;  // Bits 7:0
    UINT32 ECCGRP_ERR_STAT                         :  1;  // Bits 8:8
    UINT32                                         :  11;  // Bits 19:9
    UINT32 RD_CHUNK_NUM_STAT                       :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Nth_ERROR                               :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTRCTL_0_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTRCTL_1_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTRCTL_2_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTRCTL_3_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTRCTL_4_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTRCTL_5_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTRCTL_6_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTRCTL_7_STRUCT;

typedef union {
  struct {
    UINT32 COUNTER_POINTER                         :  7;  // Bits 6:0
    UINT32 COUNTER_CONTROL                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTRCTL_8_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTR_0_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTR_1_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTR_2_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTR_3_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTR_4_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTR_5_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTR_6_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTR_7_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER                           :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTR_8_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_COUNTER_OVERFLOW                  :  9;  // Bits 8:0
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_CNTR_OV_STRUCT;

typedef union {
  struct {
    UINT32 ERROR_STATUS                            :  1;  // Bits 0:0
    UINT32 TEST_IN_PROGRESS                        :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_ERR_TEST_ERR_STAT_STRUCT;

typedef union {
  struct {
    UINT32 DUMMYLow                                :  32;  // Bits 31:0
    UINT32 DUMMYHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CPGC_D_DUMMY_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK0_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_RANK1_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_RANK2_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_RANK3_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_RANK4_MAPPING                       :  5;  // Bits 24:20
    UINT32 L2P_RANK5_MAPPING                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK6_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_RANK7_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_RANK8_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_RANK9_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_RANK10_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK11_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_RANK_L2P_MAPPING_B_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK12_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK13_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_RANK14_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_RANK15_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_RANK16_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK17_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_RANK_L2P_MAPPING_C_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK18_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK19_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_RANK20_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_RANK21_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_RANK22_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK23_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_RANK_L2P_MAPPING_D_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK24_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK25_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_RANK26_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_RANK27_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_RANK28_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_RANK29_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_RANK_L2P_MAPPING_E_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK30_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_RANK31_MAPPING                      :  5;  // Bits 9:5
    UINT32                                         :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_RANK_L2P_MAPPING_F_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK0_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_BANK1_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_BANK2_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_BANK3_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_BANK4_MAPPING                       :  5;  // Bits 24:20
    UINT32 L2P_BANK5_MAPPING                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_BANK_L2P_MAPPING_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK6_MAPPING                       :  5;  // Bits 4:0
    UINT32 L2P_BANK7_MAPPING                       :  5;  // Bits 9:5
    UINT32 L2P_BANK8_MAPPING                       :  5;  // Bits 14:10
    UINT32 L2P_BANK9_MAPPING                       :  5;  // Bits 19:15
    UINT32 L2P_BANK10_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK11_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_BANK_L2P_MAPPING_B_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK12_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK13_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_BANK14_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_BANK15_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_BANK16_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK17_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_BANK_L2P_MAPPING_C_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK18_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK19_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_BANK20_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_BANK21_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_BANK22_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK23_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_BANK_L2P_MAPPING_D_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK24_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK25_MAPPING                      :  5;  // Bits 9:5
    UINT32 L2P_BANK26_MAPPING                      :  5;  // Bits 14:10
    UINT32 L2P_BANK27_MAPPING                      :  5;  // Bits 19:15
    UINT32 L2P_BANK28_MAPPING                      :  5;  // Bits 24:20
    UINT32 L2P_BANK29_MAPPING                      :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_BANK_L2P_MAPPING_E_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK30_MAPPING                      :  5;  // Bits 4:0
    UINT32 L2P_BANK31_MAPPING                      :  5;  // Bits 9:5
    UINT32                                         :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_BANK_L2P_MAPPING_F_STRUCT;

typedef union {
  struct {
    UINT32 L2P_RANK0_SWIZZLE                       :  5;  // Bits 4:0
    UINT32 L2P_RANK1_SWIZZLE                       :  5;  // Bits 9:5
    UINT32 L2P_RANK2_SWIZZLE                       :  5;  // Bits 14:10
    UINT32 L2P_RANK3_SWIZZLE                       :  5;  // Bits 19:15
    UINT32 L2P_RANK4_SWIZZLE                       :  5;  // Bits 24:20
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_RANK_ADDR_SWIZZLE_STRUCT;

typedef union {
  struct {
    UINT32 L2P_BANK0_SWIZZLE                       :  5;  // Bits 4:0
    UINT32 L2P_BANK1_SWIZZLE                       :  5;  // Bits 9:5
    UINT32 L2P_BANK2_SWIZZLE                       :  5;  // Bits 14:10
    UINT32 L2P_BANK3_SWIZZLE                       :  5;  // Bits 19:15
    UINT32 L2P_BANK4_SWIZZLE                       :  5;  // Bits 24:20
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_BANK_ADDR_SWIZZLE_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW0_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_ROW1_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_ROW2_SWIZZLE                        :  5;  // Bits 14:10
    UINT32 L2P_ROW3_SWIZZLE                        :  5;  // Bits 19:15
    UINT32 L2P_ROW4_SWIZZLE                        :  5;  // Bits 24:20
    UINT32 L2P_ROW5_SWIZZLE                        :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW6_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_ROW7_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_ROW8_SWIZZLE                        :  5;  // Bits 14:10
    UINT32 L2P_ROW9_SWIZZLE                        :  5;  // Bits 19:15
    UINT32 L2P_ROW10_SWIZZLE                       :  5;  // Bits 24:20
    UINT32 L2P_ROW11_SWIZZLE                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_B_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW12_SWIZZLE                       :  5;  // Bits 4:0
    UINT32 L2P_ROW13_SWIZZLE                       :  5;  // Bits 9:5
    UINT32 L2P_ROW14_SWIZZLE                       :  5;  // Bits 14:10
    UINT32 L2P_ROW15_SWIZZLE                       :  5;  // Bits 19:15
    UINT32 L2P_ROW16_SWIZZLE                       :  5;  // Bits 24:20
    UINT32 L2P_ROW17_SWIZZLE                       :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_C_STRUCT;

typedef union {
  struct {
    UINT32 L2P_ROW0_XOR_SWIZZLE                    :  5;  // Bits 4:0
    UINT32 L2P_ROW1_XOR_SWIZZLE                    :  5;  // Bits 9:5
    UINT32 L2P_ROW2_XOR_SWIZZLE                    :  5;  // Bits 14:10
    UINT32 L2P_ROW3_XOR_SWIZZLE                    :  5;  // Bits 19:15
    UINT32                                         :  9;  // Bits 28:20
    UINT32 ADDR_DQ_INV_EN                          :  1;  // Bits 29:29
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_ROW_ADDR_SWIZZLE_X_STRUCT;

typedef union {
  struct {
    UINT32 L2P_COL0_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_COL1_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_COL2_SWIZZLE                        :  5;  // Bits 14:10
    UINT32 L2P_COL3_SWIZZLE                        :  5;  // Bits 19:15
    UINT32 L2P_COL4_SWIZZLE                        :  5;  // Bits 24:20
    UINT32 L2P_COL5_SWIZZLE                        :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_A_STRUCT;

typedef union {
  struct {
    UINT32 L2P_COL6_SWIZZLE                        :  5;  // Bits 4:0
    UINT32 L2P_COL7_SWIZZLE                        :  5;  // Bits 9:5
    UINT32 L2P_COL8_SWIZZLE                        :  5;  // Bits 14:10
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_COL_ADDR_SWIZZLE_B_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_ROW_ADDR_DQ_MAP0_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CPGC_SEQ_ROW_ADDR_DQ_MAP1_STRUCT;

typedef union {
  struct {
    UINT32 DUMMYLow                                :  32;  // Bits 31:0
    UINT32 DUMMYHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CPGC_A_DUMMY_STRUCT;

#pragma pack(pop)
#endif
