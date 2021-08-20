/** @file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2017 Intel Corporation.

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

 @par Specification
**/
ASM_GLOBAL ASM_PFX(McStaticDdr4Config)
ASM_PFX(McStaticDdr4Config):
    // updating register MC_Init_State_G_0_0_0_MCHBAR 
    // edx <-- r9 [0x5030] (dword)
    movl  0xfed15030, %edx 

    or    $0x400000, %edx 
    // r9 [0x5030] <-- edx (dword)
    movl  %edx, 0xfed15030 

    // writing to register DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001214] <-- 0x0000000034e60000 (dword)
    movl   $0x34e60000, 0xfed11214 

    // writing to register DDRCKECTL_CR_DDRCRCTLCOMP_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001210] <-- 0x0000000000556000 (dword)
    movl   $0x556000, 0xfed11210 

    // writing to register DDRCKECTL_CR_DDRCRCTLCONTROLS1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001224] <-- 0x000000000adc2274 (dword)
    movl   $0xadc2274, 0xfed11224 

    // writing to register DDRCKECTL_CR_DDRCRCTLCONTROLS_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000121c] <-- 0x0000000000f4a010 (dword)
    movl   $0xf4a010, 0xfed1121c 

    // writing to register DDRCKECTL_CR_DDRCRCTLPICODING_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001218] <-- 0x0000000070102040 (dword)
    movl   $0x70102040, 0xfed11218 

    // writing to register DDRCKECTL_CR_DDRCRCTLRANKSUSED_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001220] <-- 0x00000000d0ce430b (dword)
    movl   $0xd0ce430b, 0xfed11220 

    // writing to register DDRCMD_CR_DDRCRCMDCOMP_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001200] <-- 0x0000000079556000 (dword)
    movl   $0x79556000, 0xfed11200 

    // writing to register DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001314] <-- 0x00000000ad6c0000 (dword)
    movl   $0xad6c0000, 0xfed11314 

    // writing to register DDRCKECTL_CR_DDRCRCTLCOMP_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001310] <-- 0x0000000000556000 (dword)
    movl   $0x556000, 0xfed11310 

    // writing to register DDRCKECTL_CR_DDRCRCTLCONTROLS1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001324] <-- 0x00000000188e640e (dword)
    movl   $0x188e640e, 0xfed11324 

    // writing to register DDRCKECTL_CR_DDRCRCTLCONTROLS_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000131c] <-- 0x000000000061c010 (dword)
    movl   $0x61c010, 0xfed1131c 

    // writing to register DDRCKECTL_CR_DDRCRCTLPICODING_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001318] <-- 0x0000000070102040 (dword)
    movl   $0x70102040, 0xfed11318 

    // writing to register DDRCKECTL_CR_DDRCRCTLRANKSUSED_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001320] <-- 0x00000000b0cda30b (dword)
    movl   $0xb0cda30b, 0xfed11320 

    // writing to register DDRCMD_CR_DDRCRCMDCOMP_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001300] <-- 0x00000000f1556000 (dword)
    movl   $0xf1556000, 0xfed11300 

    // writing to register DDRCLK_CR_DDRCRCLKCOMP_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001c2c] <-- 0x0000000001d35000 (dword)
    movl   $0x1d35000, 0xfed11c2c 

    // writing to register DDRCLK_CR_DDRCRCLKCOMP_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001d2c] <-- 0x0000000001d35000 (dword)
    movl   $0x1d35000, 0xfed11d2c 

    // writing to register DDRCMD_CR_DDRCRCMDCOMP_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001a00] <-- 0x00000000bc556000 (dword)
    movl   $0xbc556000, 0xfed11a00 

    // writing to register DDRCMD_CR_DDRCRCMDCONTROLS1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001a10] <-- 0x000000007e53cb4e (dword)
    movl   $0x7e53cb4e, 0xfed11a10 

    // writing to register DDRCMD_CR_DDRCRCMDCONTROLS_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001a0c] <-- 0x0000000099038000 (dword)
    movl   $0x99038000, 0xfed11a0c 

    // writing to register DDRCMD_CR_DDRCRCMDPICODING_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001a08] <-- 0x0000000091ebe040 (dword)
    movl   $0x91ebe040, 0xfed11a08 

    // writing to register DDRCMD_CR_DDRCRCMDCOMP_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001b00] <-- 0x0000000027556000 (dword)
    movl   $0x27556000, 0xfed11b00 

    // writing to register DDRCMD_CR_DDRCRCMDCONTROLS1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001b10] <-- 0x0000000067d1581a (dword)
    movl   $0x67d1581a, 0xfed11b10 

    // writing to register DDRCMD_CR_DDRCRCMDCONTROLS_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001b0c] <-- 0x0000000012d64010 (dword)
    movl   $0x12d64010, 0xfed11b0c 

    // writing to register DDRCMD_CR_DDRCRCMDPICODING_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001b08] <-- 0x00000000e21e2040 (dword)
    movl   $0xe21e2040, 0xfed11b08 

    // writing to register DDRCMD_CR_DDRCRCMDCOMP_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001400] <-- 0x00000000bc556000 (dword)
    movl   $0xbc556000, 0xfed11400 

    // writing to register DDRCMD_CR_DDRCRCMDCONTROLS1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001410] <-- 0x000000007e53cb4e (dword)
    movl   $0x7e53cb4e, 0xfed11410 

    // writing to register DDRCMD_CR_DDRCRCMDCONTROLS_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000140c] <-- 0x0000000099038000 (dword)
    movl   $0x99038000, 0xfed1140c 

    // writing to register DDRCMD_CR_DDRCRCMDPICODING_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001408] <-- 0x0000000091ebe040 (dword)
    movl   $0x91ebe040, 0xfed11408 

    // writing to register DDRCMD_CR_DDRCRCMDCOMP_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001500] <-- 0x0000000027556000 (dword)
    movl   $0x27556000, 0xfed11500 

    // writing to register DDRCMD_CR_DDRCRCMDCONTROLS1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001510] <-- 0x0000000067d1581a (dword)
    movl   $0x67d1581a, 0xfed11510 

    // writing to register DDRCMD_CR_DDRCRCMDCONTROLS_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000150c] <-- 0x0000000012d64010 (dword)
    movl   $0x12d64010, 0xfed1150c 

    // writing to register DDRCMD_CR_DDRCRCMDPICODING_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001508] <-- 0x00000000e21e2040 (dword)
    movl   $0xe21e2040, 0xfed11508 

    // writing to register DDRCKECTL_CR_DDRCMDMISR_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001c28] <-- 0x0000000000000006 (dword)
    movl   $0x6, 0xfed11c28 

    // writing to register DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001c14] <-- 0x000000009e200000 (dword)
    movl   $0x9e200000, 0xfed11c14 

    // writing to register DDRCKECTL_CR_DDRCRCTLCOMP_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001c10] <-- 0x0000000000556000 (dword)
    movl   $0x556000, 0xfed11c10 

    // writing to register DDRCKECTL_CR_DDRCRCTLCONTROLS1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001c24] <-- 0x00000000563bd879 (dword)
    movl   $0x563bd879, 0xfed11c24 

    // writing to register DDRCKECTL_CR_DDRCRCTLCONTROLS_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001c1c] <-- 0x0000000004620010 (dword)
    movl   $0x4620010, 0xfed11c1c 

    // writing to register DDRCKECTL_CR_DDRCRCTLPICODING_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001c18] <-- 0x00000000c8102040 (dword)
    movl   $0xc8102040, 0xfed11c18 

    // writing to register DDRCKECTL_CR_DDRCRCTLRANKSUSED_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001c20] <-- 0x00000000d0cf0fcf (dword)
    movl   $0xd0cf0fcf, 0xfed11c20 

    // writing to register DDRCKECTL_CR_DDRCMDMISR_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001d28] <-- 0x0000000000000094 (dword)
    movl   $0x94, 0xfed11d28 

    // writing to register DDRCKECTL_CR_DDRCRCTLCOMPOFFSET_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001d14] <-- 0x00000000b3380000 (dword)
    movl   $0xb3380000, 0xfed11d14 

    // writing to register DDRCKECTL_CR_DDRCRCTLCOMP_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001d10] <-- 0x0000000000556000 (dword)
    movl   $0x556000, 0xfed11d10 

    // writing to register DDRCKECTL_CR_DDRCRCTLCONTROLS1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001d24] <-- 0x00000000d9889d08 (dword)
    movl   $0xd9889d08, 0xfed11d24 

    // writing to register DDRCKECTL_CR_DDRCRCTLCONTROLS_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001d1c] <-- 0x000000000e11c110 (dword)
    movl   $0xe11c110, 0xfed11d1c 

    // writing to register DDRCKECTL_CR_DDRCRCTLPICODING_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001d18] <-- 0x00000000f8102040 (dword)
    movl   $0xf8102040, 0xfed11d18 

    // writing to register DDRCKECTL_CR_DDRCRCTLRANKSUSED_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001d20] <-- 0x0000000070cddfcf (dword)
    movl   $0x70cddfcf, 0xfed11d20 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000060] <-- 0x000000004c8f9c00 (dword)
    movl   $0x4c8f9c00, 0xfed10060 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000080] <-- 0x00000000244c0000 (dword)
    movl   $0x244c0000, 0xfed10080 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000006c] <-- 0x00000000320bd7c0 (dword)
    movl   $0x320bd7c0, 0xfed1006c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000070] <-- 0x00000000161a7669 (dword)
    movl   $0x161a7669, 0xfed10070 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000088] <-- 0x00000000e541ef7d (dword)
    movl   $0xe541ef7d, 0xfed10088 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000008c] <-- 0x0000000020683ecc (dword)
    movl   $0x20683ecc, 0xfed1008c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000090] <-- 0x00000000c92ae009 (dword)
    movl   $0xc92ae009, 0xfed10090 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000007c] <-- 0x000000005a000000 (dword)
    movl   $0x5a000000, 0xfed1007c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000098] <-- 0x0000000047c4e000 (dword)
    movl   $0x47c4e000, 0xfed10098 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000009c] <-- 0x000000004a6dee00 (dword)
    movl   $0x4a6dee00, 0xfed1009c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000000a0] <-- 0x000000005c8ed000 (dword)
    movl   $0x5c8ed000, 0xfed100a0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000000a8] <-- 0x000000000576f000 (dword)
    movl   $0x576f000, 0xfed100a8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000040] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10040 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000044] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10044 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000004c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed1004c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000050] <-- 0x00000000918986bc (dword)
    movl   $0x918986bc, 0xfed10050 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000054] <-- 0x00000000e22f47aa (dword)
    movl   $0xe22f47aa, 0xfed10054 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000058] <-- 0x00000000959a968c (dword)
    movl   $0x959a968c, 0xfed10058 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000005c] <-- 0x0000000080f597b9 (dword)
    movl   $0x80f597b9, 0xfed1005c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000010] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10010 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000014] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10014 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000018] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10018 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000001c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed1001c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000000] <-- 0x00000000400d00ac (dword)
    movl   $0x400d00ac, 0xfed10000 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000004] <-- 0x00000000fc0d80ac (dword)
    movl   $0xfc0d80ac, 0xfed10004 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000008] <-- 0x00000000340100ac (dword)
    movl   $0x340100ac, 0xfed10008 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000000c] <-- 0x00000000b40100ac (dword)
    movl   $0xb40100ac, 0xfed1000c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000020] <-- 0x00000000e9900020 (dword)
    movl   $0xe9900020, 0xfed10020 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000024] <-- 0x0000000004a40020 (dword)
    movl   $0x4a40020, 0xfed10024 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000028] <-- 0x00000000d3980020 (dword)
    movl   $0xd3980020, 0xfed10028 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000002c] <-- 0x000000001b240020 (dword)
    movl   $0x1b240020, 0xfed1002c 

    // writing to register DDRDATA_CR_TXXTALK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000048] <-- 0x0000000011111011 (dword)
    movl   $0x11111011, 0xfed10048 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000160] <-- 0x00000000605fe400 (dword)
    movl   $0x605fe400, 0xfed10160 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000180] <-- 0x0000000020404000 (dword)
    movl   $0x20404000, 0xfed10180 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000016c] <-- 0x00000000720bdf80 (dword)
    movl   $0x720bdf80, 0xfed1016c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000170] <-- 0x00000000c31e728f (dword)
    movl   $0xc31e728f, 0xfed10170 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000188] <-- 0x0000000009c56927 (dword)
    movl   $0x9c56927, 0xfed10188 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000018c] <-- 0x00000000e0f21f09 (dword)
    movl   $0xe0f21f09, 0xfed1018c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000190] <-- 0x000000003fdb8002 (dword)
    movl   $0x3fdb8002, 0xfed10190 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000017c] <-- 0x0000000072000000 (dword)
    movl   $0x72000000, 0xfed1017c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000198] <-- 0x00000000b5756400 (dword)
    movl   $0xb5756400, 0xfed10198 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000019c] <-- 0x0000000061141800 (dword)
    movl   $0x61141800, 0xfed1019c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000001a0] <-- 0x0000000080d43400 (dword)
    movl   $0x80d43400, 0xfed101a0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000001a8] <-- 0x00000000885c9c00 (dword)
    movl   $0x885c9c00, 0xfed101a8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000140] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10140 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000144] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10144 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000014c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed1014c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000150] <-- 0x00000000d9006fdd (dword)
    movl   $0xd9006fdd, 0xfed10150 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000154] <-- 0x00000000194f0759 (dword)
    movl   $0x194f0759, 0xfed10154 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000158] <-- 0x00000000e801e47f (dword)
    movl   $0xe801e47f, 0xfed10158 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000015c] <-- 0x000000004e5a223e (dword)
    movl   $0x4e5a223e, 0xfed1015c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000110] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10110 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000114] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10114 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000118] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10118 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000011c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed1011c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000100] <-- 0x00000000740480a4 (dword)
    movl   $0x740480a4, 0xfed10100 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000104] <-- 0x00000000b00c00a4 (dword)
    movl   $0xb00c00a4, 0xfed10104 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000108] <-- 0x00000000880980a4 (dword)
    movl   $0x880980a4, 0xfed10108 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000010c] <-- 0x00000000100580a4 (dword)
    movl   $0x100580a4, 0xfed1010c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000120] <-- 0x00000000eca40020 (dword)
    movl   $0xeca40020, 0xfed10120 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000124] <-- 0x0000000053d00020 (dword)
    movl   $0x53d00020, 0xfed10124 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000128] <-- 0x0000000035840020 (dword)
    movl   $0x35840020, 0xfed10128 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000012c] <-- 0x0000000022d40020 (dword)
    movl   $0x22d40020, 0xfed1012c 

    // writing to register DDRDATA_CR_TXXTALK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000148] <-- 0x0000000010012123 (dword)
    movl   $0x10012123, 0xfed10148 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000260] <-- 0x00000000de695c00 (dword)
    movl   $0xde695c00, 0xfed10260 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000280] <-- 0x0000000084840000 (dword)
    movl   $0x84840000, 0xfed10280 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000026c] <-- 0x00000000620bebc0 (dword)
    movl   $0x620bebc0, 0xfed1026c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000270] <-- 0x00000000f01e6251 (dword)
    movl   $0xf01e6251, 0xfed10270 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000288] <-- 0x0000000052b58637 (dword)
    movl   $0x52b58637, 0xfed10288 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000028c] <-- 0x0000000040823e4d (dword)
    movl   $0x40823e4d, 0xfed1028c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000290] <-- 0x00000000b4ec4809 (dword)
    movl   $0xb4ec4809, 0xfed10290 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000027c] <-- 0x000000005a000000 (dword)
    movl   $0x5a000000, 0xfed1027c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000298] <-- 0x00000000c9128a00 (dword)
    movl   $0xc9128a00, 0xfed10298 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000029c] <-- 0x00000000cfef8800 (dword)
    movl   $0xcfef8800, 0xfed1029c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000002a0] <-- 0x00000000fd974600 (dword)
    movl   $0xfd974600, 0xfed102a0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000002a8] <-- 0x0000000012d07c00 (dword)
    movl   $0x12d07c00, 0xfed102a8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000240] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10240 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000244] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10244 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000024c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed1024c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000250] <-- 0x0000000018222bf9 (dword)
    movl   $0x18222bf9, 0xfed10250 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000254] <-- 0x000000008d931480 (dword)
    movl   $0x8d931480, 0xfed10254 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000258] <-- 0x00000000e12174b4 (dword)
    movl   $0xe12174b4, 0xfed10258 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000025c] <-- 0x000000003b226046 (dword)
    movl   $0x3b226046, 0xfed1025c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000210] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10210 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000214] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10214 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000218] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10218 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000021c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed1021c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000200] <-- 0x00000000440e00a4 (dword)
    movl   $0x440e00a4, 0xfed10200 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000204] <-- 0x000000008c0480a4 (dword)
    movl   $0x8c0480a4, 0xfed10204 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000208] <-- 0x00000000cc0800a4 (dword)
    movl   $0xcc0800a4, 0xfed10208 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000020c] <-- 0x00000000100000a4 (dword)
    movl   $0x100000a4, 0xfed1020c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000220] <-- 0x0000000086cc0020 (dword)
    movl   $0x86cc0020, 0xfed10220 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000224] <-- 0x00000000e8600020 (dword)
    movl   $0xe8600020, 0xfed10224 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000228] <-- 0x00000000c1d80020 (dword)
    movl   $0xc1d80020, 0xfed10228 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000022c] <-- 0x0000000035b40020 (dword)
    movl   $0x35b40020, 0xfed1022c 

    // writing to register DDRDATA_CR_TXXTALK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000248] <-- 0x0000000023123011 (dword)
    movl   $0x23123011, 0xfed10248 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000360] <-- 0x000000002a7cf200 (dword)
    movl   $0x2a7cf200, 0xfed10360 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000380] <-- 0x0000000024cc0200 (dword)
    movl   $0x24cc0200, 0xfed10380 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000036c] <-- 0x00000000620bc380 (dword)
    movl   $0x620bc380, 0xfed1036c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000370] <-- 0x000000000b1e7ccb (dword)
    movl   $0xb1e7ccb, 0xfed10370 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000388] <-- 0x00000000b383465b (dword)
    movl   $0xb383465b, 0xfed10388 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000038c] <-- 0x0000000060f21e94 (dword)
    movl   $0x60f21e94, 0xfed1038c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000390] <-- 0x00000000ef3dc002 (dword)
    movl   $0xef3dc002, 0xfed10390 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000037c] <-- 0x0000000072000000 (dword)
    movl   $0x72000000, 0xfed1037c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000398] <-- 0x00000000f30a2c00 (dword)
    movl   $0xf30a2c00, 0xfed10398 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000039c] <-- 0x000000005b1dfa00 (dword)
    movl   $0x5b1dfa00, 0xfed1039c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000003a0] <-- 0x00000000899ad800 (dword)
    movl   $0x899ad800, 0xfed103a0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000003a8] <-- 0x0000000049c31200 (dword)
    movl   $0x49c31200, 0xfed103a8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000340] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10340 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000344] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10344 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000034c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed1034c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000350] <-- 0x00000000a9993464 (dword)
    movl   $0xa9993464, 0xfed10350 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000354] <-- 0x00000000837adb65 (dword)
    movl   $0x837adb65, 0xfed10354 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000358] <-- 0x00000000a1917724 (dword)
    movl   $0xa1917724, 0xfed10358 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000035c] <-- 0x0000000037d92193 (dword)
    movl   $0x37d92193, 0xfed1035c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000310] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10310 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000314] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10314 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000318] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10318 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000031c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed1031c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000300] <-- 0x00000000500600ac (dword)
    movl   $0x500600ac, 0xfed10300 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000304] <-- 0x000000002c0500ac (dword)
    movl   $0x2c0500ac, 0xfed10304 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000308] <-- 0x00000000600d00ac (dword)
    movl   $0x600d00ac, 0xfed10308 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000030c] <-- 0x00000000dc0880ac (dword)
    movl   $0xdc0880ac, 0xfed1030c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000320] <-- 0x00000000f6980020 (dword)
    movl   $0xf6980020, 0xfed10320 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000324] <-- 0x00000000cbe80020 (dword)
    movl   $0xcbe80020, 0xfed10324 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000328] <-- 0x00000000f6ac0020 (dword)
    movl   $0xf6ac0020, 0xfed10328 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000032c] <-- 0x00000000663c0020 (dword)
    movl   $0x663c0020, 0xfed1032c 

    // writing to register DDRDATA_CR_TXXTALK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000348] <-- 0x0000000021222201 (dword)
    movl   $0x21222201, 0xfed10348 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000460] <-- 0x000000008358de00 (dword)
    movl   $0x8358de00, 0xfed10460 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000480] <-- 0x0000000084000000 (dword)
    movl   $0x84000000, 0xfed10480 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000046c] <-- 0x00000000220bd780 (dword)
    movl   $0x220bd780, 0xfed1046c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000470] <-- 0x00000000d91e7aae (dword)
    movl   $0xd91e7aae, 0xfed10470 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000488] <-- 0x000000004a4b72ce (dword)
    movl   $0x4a4b72ce, 0xfed10488 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000048c] <-- 0x00000000c0221640 (dword)
    movl   $0xc0221640, 0xfed1048c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000490] <-- 0x00000000cc691809 (dword)
    movl   $0xcc691809, 0xfed10490 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000047c] <-- 0x000000005a000000 (dword)
    movl   $0x5a000000, 0xfed1047c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000498] <-- 0x000000002dcd1000 (dword)
    movl   $0x2dcd1000, 0xfed10498 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000049c] <-- 0x00000000e7b2a200 (dword)
    movl   $0xe7b2a200, 0xfed1049c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000004a0] <-- 0x00000000041a4a00 (dword)
    movl   $0x41a4a00, 0xfed104a0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000004a8] <-- 0x00000000d6aee600 (dword)
    movl   $0xd6aee600, 0xfed104a8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000440] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10440 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000444] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10444 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000044c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed1044c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000450] <-- 0x00000000347a3178 (dword)
    movl   $0x347a3178, 0xfed10450 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000454] <-- 0x000000002bfdd987 (dword)
    movl   $0x2bfdd987, 0xfed10454 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000458] <-- 0x00000000f0183d32 (dword)
    movl   $0xf0183d32, 0xfed10458 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000045c] <-- 0x0000000041da1716 (dword)
    movl   $0x41da1716, 0xfed1045c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000410] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10410 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000414] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10414 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000418] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10418 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000041c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed1041c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000400] <-- 0x00000000400c00a4 (dword)
    movl   $0x400c00a4, 0xfed10400 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000404] <-- 0x000000009c0180a4 (dword)
    movl   $0x9c0180a4, 0xfed10404 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000408] <-- 0x00000000c40980a4 (dword)
    movl   $0xc40980a4, 0xfed10408 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000040c] <-- 0x00000000440400a4 (dword)
    movl   $0x440400a4, 0xfed1040c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000420] <-- 0x0000000029d40020 (dword)
    movl   $0x29d40020, 0xfed10420 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000424] <-- 0x0000000022680020 (dword)
    movl   $0x22680020, 0xfed10424 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000428] <-- 0x00000000b63c0020 (dword)
    movl   $0xb63c0020, 0xfed10428 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000042c] <-- 0x00000000b8400020 (dword)
    movl   $0xb8400020, 0xfed1042c 

    // writing to register DDRDATA_CR_TXXTALK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000448] <-- 0x0000000012202210 (dword)
    movl   $0x12202210, 0xfed10448 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000560] <-- 0x0000000070f1ac00 (dword)
    movl   $0x70f1ac00, 0xfed10560 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000580] <-- 0x0000000024c80000 (dword)
    movl   $0x24c80000, 0xfed10580 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000056c] <-- 0x00000000120bf380 (dword)
    movl   $0x120bf380, 0xfed1056c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000570] <-- 0x000000002d1e68d1 (dword)
    movl   $0x2d1e68d1, 0xfed10570 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000588] <-- 0x00000000db643013 (dword)
    movl   $0xdb643013, 0xfed10588 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000058c] <-- 0x0000000080523694 (dword)
    movl   $0x80523694, 0xfed1058c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000590] <-- 0x000000008f42a802 (dword)
    movl   $0x8f42a802, 0xfed10590 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000057c] <-- 0x0000000072000000 (dword)
    movl   $0x72000000, 0xfed1057c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000598] <-- 0x000000005010e000 (dword)
    movl   $0x5010e000, 0xfed10598 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000059c] <-- 0x00000000101b9c00 (dword)
    movl   $0x101b9c00, 0xfed1059c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000005a0] <-- 0x0000000040bd5e00 (dword)
    movl   $0x40bd5e00, 0xfed105a0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000005a8] <-- 0x0000000017829400 (dword)
    movl   $0x17829400, 0xfed105a8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000540] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10540 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000544] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10544 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000054c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed1054c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000550] <-- 0x00000000c9ad3c6b (dword)
    movl   $0xc9ad3c6b, 0xfed10550 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000554] <-- 0x00000000f59e53c9 (dword)
    movl   $0xf59e53c9, 0xfed10554 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000558] <-- 0x000000009cf6153e (dword)
    movl   $0x9cf6153e, 0xfed10558 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000055c] <-- 0x0000000049058b20 (dword)
    movl   $0x49058b20, 0xfed1055c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000510] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10510 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000514] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10514 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000518] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10518 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000051c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed1051c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000500] <-- 0x00000000300800ac (dword)
    movl   $0x300800ac, 0xfed10500 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000504] <-- 0x000000009c0400ac (dword)
    movl   $0x9c0400ac, 0xfed10504 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000508] <-- 0x00000000080180ac (dword)
    movl   $0x80180ac, 0xfed10508 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000050c] <-- 0x00000000a80d80ac (dword)
    movl   $0xa80d80ac, 0xfed1050c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000520] <-- 0x0000000019680020 (dword)
    movl   $0x19680020, 0xfed10520 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000524] <-- 0x00000000604c0020 (dword)
    movl   $0x604c0020, 0xfed10524 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000528] <-- 0x0000000090dc0020 (dword)
    movl   $0x90dc0020, 0xfed10528 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000052c] <-- 0x0000000081600020 (dword)
    movl   $0x81600020, 0xfed1052c 

    // writing to register DDRDATA_CR_TXXTALK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000548] <-- 0x0000000031111003 (dword)
    movl   $0x31111003, 0xfed10548 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000660] <-- 0x00000000b2ace200 (dword)
    movl   $0xb2ace200, 0xfed10660 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000680] <-- 0x0000000084442000 (dword)
    movl   $0x84442000, 0xfed10680 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000066c] <-- 0x00000000520be780 (dword)
    movl   $0x520be780, 0xfed1066c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000670] <-- 0x000000002e1e76e1 (dword)
    movl   $0x2e1e76e1, 0xfed10670 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000688] <-- 0x0000000093117710 (dword)
    movl   $0x93117710, 0xfed10688 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000068c] <-- 0x00000000a08a3e90 (dword)
    movl   $0xa08a3e90, 0xfed1068c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000690] <-- 0x00000000e9e92809 (dword)
    movl   $0xe9e92809, 0xfed10690 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000067c] <-- 0x000000005a000000 (dword)
    movl   $0x5a000000, 0xfed1067c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000698] <-- 0x00000000addd8200 (dword)
    movl   $0xaddd8200, 0xfed10698 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000069c] <-- 0x000000001a9ba400 (dword)
    movl   $0x1a9ba400, 0xfed1069c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000006a0] <-- 0x000000001d8af600 (dword)
    movl   $0x1d8af600, 0xfed106a0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000006a8] <-- 0x00000000c8fbe000 (dword)
    movl   $0xc8fbe000, 0xfed106a8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000640] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10640 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000644] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10644 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000064c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed1064c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000650] <-- 0x0000000005c4dacf (dword)
    movl   $0x5c4dacf, 0xfed10650 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000654] <-- 0x000000009de31daf (dword)
    movl   $0x9de31daf, 0xfed10654 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000658] <-- 0x000000000fed0bdf (dword)
    movl   $0xfed0bdf, 0xfed10658 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000065c] <-- 0x00000000dc2a4cb0 (dword)
    movl   $0xdc2a4cb0, 0xfed1065c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000610] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10610 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000614] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10614 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000618] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10618 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000061c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed1061c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000600] <-- 0x000000002c0d80ac (dword)
    movl   $0x2c0d80ac, 0xfed10600 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000604] <-- 0x00000000b80d80ac (dword)
    movl   $0xb80d80ac, 0xfed10604 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000608] <-- 0x00000000ac0080ac (dword)
    movl   $0xac0080ac, 0xfed10608 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000060c] <-- 0x00000000fc0400ac (dword)
    movl   $0xfc0400ac, 0xfed1060c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000620] <-- 0x00000000da180020 (dword)
    movl   $0xda180020, 0xfed10620 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000624] <-- 0x000000009d880020 (dword)
    movl   $0x9d880020, 0xfed10624 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000628] <-- 0x00000000ab740020 (dword)
    movl   $0xab740020, 0xfed10628 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000062c] <-- 0x00000000c3880020 (dword)
    movl   $0xc3880020, 0xfed1062c 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000760] <-- 0x00000000f5f2e200 (dword)
    movl   $0xf5f2e200, 0xfed10760 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000780] <-- 0x0000000020882000 (dword)
    movl   $0x20882000, 0xfed10780 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000076c] <-- 0x00000000320bf380 (dword)
    movl   $0x320bf380, 0xfed1076c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000770] <-- 0x00000000211a68eb (dword)
    movl   $0x211a68eb, 0xfed10770 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000788] <-- 0x00000000687c3f93 (dword)
    movl   $0x687c3f93, 0xfed10788 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000078c] <-- 0x0000000040281730 (dword)
    movl   $0x40281730, 0xfed1078c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000790] <-- 0x00000000f6833802 (dword)
    movl   $0xf6833802, 0xfed10790 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000077c] <-- 0x00000000f2000000 (dword)
    movl   $0xf2000000, 0xfed1077c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000798] <-- 0x00000000c0e1e600 (dword)
    movl   $0xc0e1e600, 0xfed10798 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000079c] <-- 0x00000000b68aac00 (dword)
    movl   $0xb68aac00, 0xfed1079c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000007a0] <-- 0x00000000e157fc00 (dword)
    movl   $0xe157fc00, 0xfed107a0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000007a8] <-- 0x0000000044571000 (dword)
    movl   $0x44571000, 0xfed107a8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000740] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10740 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000744] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10744 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000074c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed1074c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000750] <-- 0x00000000fdbbd082 (dword)
    movl   $0xfdbbd082, 0xfed10750 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000754] <-- 0x000000001d85528a (dword)
    movl   $0x1d85528a, 0xfed10754 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000758] <-- 0x000000006a7cabfc (dword)
    movl   $0x6a7cabfc, 0xfed10758 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000075c] <-- 0x00000000e48a3e64 (dword)
    movl   $0xe48a3e64, 0xfed1075c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000710] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10710 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000714] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10714 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000718] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10718 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000071c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed1071c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000700] <-- 0x00000000540a00ac (dword)
    movl   $0x540a00ac, 0xfed10700 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000704] <-- 0x00000000cc0a00ac (dword)
    movl   $0xcc0a00ac, 0xfed10704 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000708] <-- 0x00000000500d80ac (dword)
    movl   $0x500d80ac, 0xfed10708 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000070c] <-- 0x00000000140100ac (dword)
    movl   $0x140100ac, 0xfed1070c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000720] <-- 0x0000000017540020 (dword)
    movl   $0x17540020, 0xfed10720 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000724] <-- 0x0000000028b00020 (dword)
    movl   $0x28b00020, 0xfed10724 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000728] <-- 0x00000000c8b40020 (dword)
    movl   $0xc8b40020, 0xfed10728 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000072c] <-- 0x00000000045c0020 (dword)
    movl   $0x45c0020, 0xfed1072c 

    // writing to register DDRDATA_CR_TXXTALK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000748] <-- 0x0000000033312101 (dword)
    movl   $0x33312101, 0xfed10748 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000860] <-- 0x000000001be83200 (dword)
    movl   $0x1be83200, 0xfed10860 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000880] <-- 0x0000000020044000 (dword)
    movl   $0x20044000, 0xfed10880 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000086c] <-- 0x00000000520bebd0 (dword)
    movl   $0x520bebd0, 0xfed1086c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000870] <-- 0x00000000f11e6630 (dword)
    movl   $0xf11e6630, 0xfed10870 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000888] <-- 0x0000000027b686aa (dword)
    movl   $0x27b686aa, 0xfed10888 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000088c] <-- 0x00000000c0f81658 (dword)
    movl   $0xc0f81658, 0xfed1088c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000890] <-- 0x00000000d24ed809 (dword)
    movl   $0xd24ed809, 0xfed10890 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000087c] <-- 0x000000005a000000 (dword)
    movl   $0x5a000000, 0xfed1087c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000898] <-- 0x0000000022bd4200 (dword)
    movl   $0x22bd4200, 0xfed10898 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000089c] <-- 0x00000000217e2c00 (dword)
    movl   $0x217e2c00, 0xfed1089c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000008a0] <-- 0x000000002d082a00 (dword)
    movl   $0x2d082a00, 0xfed108a0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000008a8] <-- 0x00000000f535c800 (dword)
    movl   $0xf535c800, 0xfed108a8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000840] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10840 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000844] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10844 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000084c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed1084c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000850] <-- 0x000000005705538e (dword)
    movl   $0x5705538e, 0xfed10850 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000854] <-- 0x0000000062d88438 (dword)
    movl   $0x62d88438, 0xfed10854 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000858] <-- 0x00000000c3e6f914 (dword)
    movl   $0xc3e6f914, 0xfed10858 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000085c] <-- 0x000000003a1f53f5 (dword)
    movl   $0x3a1f53f5, 0xfed1085c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000810] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10810 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000814] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10814 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000818] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10818 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000081c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed1081c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000800] <-- 0x00000000400c00a4 (dword)
    movl   $0x400c00a4, 0xfed10800 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000804] <-- 0x00000000200d00a4 (dword)
    movl   $0x200d00a4, 0xfed10804 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000808] <-- 0x00000000c40a00a4 (dword)
    movl   $0xc40a00a4, 0xfed10808 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000080c] <-- 0x00000000680580a4 (dword)
    movl   $0x680580a4, 0xfed1080c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000820] <-- 0x0000000010ac0020 (dword)
    movl   $0x10ac0020, 0xfed10820 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000824] <-- 0x000000000d840020 (dword)
    movl   $0xd840020, 0xfed10824 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000828] <-- 0x00000000eaac0020 (dword)
    movl   $0xeaac0020, 0xfed10828 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000082c] <-- 0x0000000059500020 (dword)
    movl   $0x59500020, 0xfed1082c 

    // writing to register DDRDATA_CR_TXXTALK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000848] <-- 0x0000000022121031 (dword)
    movl   $0x22121031, 0xfed10848 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000960] <-- 0x000000004d218600 (dword)
    movl   $0x4d218600, 0xfed10960 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000980] <-- 0x0000000080080000 (dword)
    movl   $0x80080000, 0xfed10980 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000096c] <-- 0x00000000420bc380 (dword)
    movl   $0x420bc380, 0xfed1096c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000970] <-- 0x00000000781e7a42 (dword)
    movl   $0x781e7a42, 0xfed10970 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000988] <-- 0x00000000d0eb7c6f (dword)
    movl   $0xd0eb7c6f, 0xfed10988 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000098c] <-- 0x0000000060583f5d (dword)
    movl   $0x60583f5d, 0xfed1098c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000990] <-- 0x000000004460a802 (dword)
    movl   $0x4460a802, 0xfed10990 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000097c] <-- 0x0000000072000000 (dword)
    movl   $0x72000000, 0xfed1097c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000998] <-- 0x0000000093c91800 (dword)
    movl   $0x93c91800, 0xfed10998 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000099c] <-- 0x00000000f899dc00 (dword)
    movl   $0xf899dc00, 0xfed1099c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000009a0] <-- 0x0000000038325400 (dword)
    movl   $0x38325400, 0xfed109a0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000009a8] <-- 0x00000000009f9400 (dword)
    movl   $0x9f9400, 0xfed109a8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000940] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10940 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000944] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10944 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000094c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed1094c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000950] <-- 0x00000000b6e16363 (dword)
    movl   $0xb6e16363, 0xfed10950 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000954] <-- 0x000000005fb7d1d3 (dword)
    movl   $0x5fb7d1d3, 0xfed10954 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000958] <-- 0x00000000ff615d39 (dword)
    movl   $0xff615d39, 0xfed10958 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000095c] <-- 0x00000000bf4520c9 (dword)
    movl   $0xbf4520c9, 0xfed1095c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000910] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10910 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000914] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10914 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000918] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10918 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000091c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed1091c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000900] <-- 0x00000000300e00a4 (dword)
    movl   $0x300e00a4, 0xfed10900 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000904] <-- 0x00000000900d00a4 (dword)
    movl   $0x900d00a4, 0xfed10904 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000908] <-- 0x000000004c0400a4 (dword)
    movl   $0x4c0400a4, 0xfed10908 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000090c] <-- 0x00000000600900a4 (dword)
    movl   $0x600900a4, 0xfed1090c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000920] <-- 0x00000000879c0020 (dword)
    movl   $0x879c0020, 0xfed10920 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000924] <-- 0x000000005f140020 (dword)
    movl   $0x5f140020, 0xfed10924 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000928] <-- 0x00000000def80020 (dword)
    movl   $0xdef80020, 0xfed10928 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000092c] <-- 0x0000000085f40020 (dword)
    movl   $0x85f40020, 0xfed1092c 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a60] <-- 0x000000003e07da00 (dword)
    movl   $0x3e07da00, 0xfed10a60 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a80] <-- 0x0000000084cc4000 (dword)
    movl   $0x84cc4000, 0xfed10a80 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a6c] <-- 0x00000000620bdfd0 (dword)
    movl   $0x620bdfd0, 0xfed10a6c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a70] <-- 0x000000000b1e78ce (dword)
    movl   $0xb1e78ce, 0xfed10a70 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a88] <-- 0x0000000068c6f8cb (dword)
    movl   $0x68c6f8cb, 0xfed10a88 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a8c] <-- 0x0000000020a81e49 (dword)
    movl   $0x20a81e49, 0xfed10a8c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a90] <-- 0x00000000a02c5809 (dword)
    movl   $0xa02c5809, 0xfed10a90 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a7c] <-- 0x000000005a000000 (dword)
    movl   $0x5a000000, 0xfed10a7c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a98] <-- 0x000000009bd14800 (dword)
    movl   $0x9bd14800, 0xfed10a98 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a9c] <-- 0x000000006d847600 (dword)
    movl   $0x6d847600, 0xfed10a9c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000aa0] <-- 0x00000000cc807200 (dword)
    movl   $0xcc807200, 0xfed10aa0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000aa8] <-- 0x00000000e7da1a00 (dword)
    movl   $0xe7da1a00, 0xfed10aa8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a40] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10a40 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a44] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10a44 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a4c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed10a4c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a50] <-- 0x000000006977922f (dword)
    movl   $0x6977922f, 0xfed10a50 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a54] <-- 0x00000000ca7df820 (dword)
    movl   $0xca7df820, 0xfed10a54 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a58] <-- 0x00000000302abf24 (dword)
    movl   $0x302abf24, 0xfed10a58 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a5c] <-- 0x000000007071d0de (dword)
    movl   $0x7071d0de, 0xfed10a5c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a10] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10a10 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a14] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10a14 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a18] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10a18 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a1c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10a1c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a00] <-- 0x00000000f80600ac (dword)
    movl   $0xf80600ac, 0xfed10a00 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a04] <-- 0x00000000800880ac (dword)
    movl   $0x800880ac, 0xfed10a04 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a08] <-- 0x00000000340600ac (dword)
    movl   $0x340600ac, 0xfed10a08 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a0c] <-- 0x00000000580880ac (dword)
    movl   $0x580880ac, 0xfed10a0c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a20] <-- 0x00000000c78c0020 (dword)
    movl   $0xc78c0020, 0xfed10a20 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a24] <-- 0x0000000024cc0020 (dword)
    movl   $0x24cc0020, 0xfed10a24 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a28] <-- 0x0000000034340020 (dword)
    movl   $0x34340020, 0xfed10a28 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a2c] <-- 0x00000000b6a40020 (dword)
    movl   $0xb6a40020, 0xfed10a2c 

    // writing to register DDRDATA_CR_TXXTALK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000a48] <-- 0x0000000022021012 (dword)
    movl   $0x22021012, 0xfed10a48 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b60] <-- 0x0000000011bd0200 (dword)
    movl   $0x11bd0200, 0xfed10b60 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b80] <-- 0x00000000204c0000 (dword)
    movl   $0x204c0000, 0xfed10b80 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b6c] <-- 0x00000000220bf780 (dword)
    movl   $0x220bf780, 0xfed10b6c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b70] <-- 0x00000000391e6c28 (dword)
    movl   $0x391e6c28, 0xfed10b70 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b88] <-- 0x00000000f0b96c8d (dword)
    movl   $0xf0b96c8d, 0xfed10b88 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b8c] <-- 0x00000000e0103f08 (dword)
    movl   $0xe0103f08, 0xfed10b8c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b90] <-- 0x00000000b74ea802 (dword)
    movl   $0xb74ea802, 0xfed10b90 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b7c] <-- 0x0000000072000000 (dword)
    movl   $0x72000000, 0xfed10b7c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b98] <-- 0x00000000190b9a00 (dword)
    movl   $0x190b9a00, 0xfed10b98 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b9c] <-- 0x00000000e5e41c00 (dword)
    movl   $0xe5e41c00, 0xfed10b9c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000ba0] <-- 0x0000000060fe2800 (dword)
    movl   $0x60fe2800, 0xfed10ba0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000ba8] <-- 0x00000000bef8be00 (dword)
    movl   $0xbef8be00, 0xfed10ba8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b40] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10b40 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b44] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10b44 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b4c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed10b4c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b50] <-- 0x00000000a4a839f0 (dword)
    movl   $0xa4a839f0, 0xfed10b50 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b54] <-- 0x00000000578842c8 (dword)
    movl   $0x578842c8, 0xfed10b54 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b58] <-- 0x000000002cca2317 (dword)
    movl   $0x2cca2317, 0xfed10b58 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b5c] <-- 0x000000001f36390d (dword)
    movl   $0x1f36390d, 0xfed10b5c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b10] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10b10 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b14] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10b14 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b18] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10b18 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b1c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10b1c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b00] <-- 0x00000000380000ac (dword)
    movl   $0x380000ac, 0xfed10b00 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b04] <-- 0x00000000500800ac (dword)
    movl   $0x500800ac, 0xfed10b04 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b08] <-- 0x00000000080800ac (dword)
    movl   $0x80800ac, 0xfed10b08 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b0c] <-- 0x000000004c0480ac (dword)
    movl   $0x4c0480ac, 0xfed10b0c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b20] <-- 0x0000000078a40020 (dword)
    movl   $0x78a40020, 0xfed10b20 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b24] <-- 0x00000000d5ac0020 (dword)
    movl   $0xd5ac0020, 0xfed10b24 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b28] <-- 0x00000000e6680020 (dword)
    movl   $0xe6680020, 0xfed10b28 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b2c] <-- 0x00000000c4a40020 (dword)
    movl   $0xc4a40020, 0xfed10b2c 

    // writing to register DDRDATA_CR_TXXTALK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000b48] <-- 0x0000000000323100 (dword)
    movl   $0x323100, 0xfed10b48 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c60] <-- 0x000000003cfabe00 (dword)
    movl   $0x3cfabe00, 0xfed10c60 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c80] <-- 0x00000000248c0000 (dword)
    movl   $0x248c0000, 0xfed10c80 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c6c] <-- 0x00000000420bff80 (dword)
    movl   $0x420bff80, 0xfed10c6c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c70] <-- 0x00000000dc1e7e25 (dword)
    movl   $0xdc1e7e25, 0xfed10c70 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c88] <-- 0x0000000087ed4964 (dword)
    movl   $0x87ed4964, 0xfed10c88 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c8c] <-- 0x00000000809a3eb5 (dword)
    movl   $0x809a3eb5, 0xfed10c8c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c90] <-- 0x00000000cb4c0809 (dword)
    movl   $0xcb4c0809, 0xfed10c90 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c7c] <-- 0x00000000da000000 (dword)
    movl   $0xda000000, 0xfed10c7c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c98] <-- 0x00000000eb249c00 (dword)
    movl   $0xeb249c00, 0xfed10c98 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c9c] <-- 0x000000001dc85a00 (dword)
    movl   $0x1dc85a00, 0xfed10c9c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000ca0] <-- 0x0000000083bed400 (dword)
    movl   $0x83bed400, 0xfed10ca0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000ca8] <-- 0x00000000fa79e400 (dword)
    movl   $0xfa79e400, 0xfed10ca8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c40] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10c40 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c44] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10c44 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c4c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed10c4c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c50] <-- 0x0000000072feef78 (dword)
    movl   $0x72feef78, 0xfed10c50 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c54] <-- 0x000000005b06eb29 (dword)
    movl   $0x5b06eb29, 0xfed10c54 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c58] <-- 0x000000002e55b9ee (dword)
    movl   $0x2e55b9ee, 0xfed10c58 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c5c] <-- 0x000000000716385d (dword)
    movl   $0x716385d, 0xfed10c5c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c10] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10c10 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c14] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10c14 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c18] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10c18 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c1c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10c1c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c00] <-- 0x000000006c0080a4 (dword)
    movl   $0x6c0080a4, 0xfed10c00 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c04] <-- 0x00000000ac0800a4 (dword)
    movl   $0xac0800a4, 0xfed10c04 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c08] <-- 0x00000000700600a4 (dword)
    movl   $0x700600a4, 0xfed10c08 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c0c] <-- 0x00000000340c00a4 (dword)
    movl   $0x340c00a4, 0xfed10c0c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c20] <-- 0x00000000dcdc0020 (dword)
    movl   $0xdcdc0020, 0xfed10c20 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c24] <-- 0x00000000b6780020 (dword)
    movl   $0xb6780020, 0xfed10c24 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c28] <-- 0x00000000841c0020 (dword)
    movl   $0x841c0020, 0xfed10c28 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000c2c] <-- 0x000000006ee80020 (dword)
    movl   $0x6ee80020, 0xfed10c2c 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d60] <-- 0x00000000c5be5200 (dword)
    movl   $0xc5be5200, 0xfed10d60 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d80] <-- 0x0000000024c02000 (dword)
    movl   $0x24c02000, 0xfed10d80 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d6c] <-- 0x00000000020befd0 (dword)
    movl   $0x20befd0, 0xfed10d6c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d70] <-- 0x00000000521e62c6 (dword)
    movl   $0x521e62c6, 0xfed10d70 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d88] <-- 0x0000000048b2b9cc (dword)
    movl   $0x48b2b9cc, 0xfed10d88 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d8c] <-- 0x0000000020021e40 (dword)
    movl   $0x20021e40, 0xfed10d8c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d90] <-- 0x000000009002b802 (dword)
    movl   $0x9002b802, 0xfed10d90 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d7c] <-- 0x0000000072000000 (dword)
    movl   $0x72000000, 0xfed10d7c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d98] <-- 0x00000000b2e7d000 (dword)
    movl   $0xb2e7d000, 0xfed10d98 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d9c] <-- 0x000000006cabb400 (dword)
    movl   $0x6cabb400, 0xfed10d9c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000da0] <-- 0x00000000a2578400 (dword)
    movl   $0xa2578400, 0xfed10da0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000da8] <-- 0x0000000019930a00 (dword)
    movl   $0x19930a00, 0xfed10da8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d40] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10d40 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d44] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10d44 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d4c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed10d4c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d50] <-- 0x000000004dc7705c (dword)
    movl   $0x4dc7705c, 0xfed10d50 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d54] <-- 0x0000000021238bdd (dword)
    movl   $0x21238bdd, 0xfed10d54 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d58] <-- 0x00000000d6c42f20 (dword)
    movl   $0xd6c42f20, 0xfed10d58 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d5c] <-- 0x000000006cd5b1a8 (dword)
    movl   $0x6cd5b1a8, 0xfed10d5c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d10] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10d10 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d14] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10d14 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d18] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10d18 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d1c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10d1c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d00] <-- 0x00000000b80180a4 (dword)
    movl   $0xb80180a4, 0xfed10d00 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d04] <-- 0x00000000c40e00a4 (dword)
    movl   $0xc40e00a4, 0xfed10d04 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d08] <-- 0x00000000540880a4 (dword)
    movl   $0x540880a4, 0xfed10d08 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d0c] <-- 0x00000000600400a4 (dword)
    movl   $0x600400a4, 0xfed10d0c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d20] <-- 0x00000000753c0020 (dword)
    movl   $0x753c0020, 0xfed10d20 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d24] <-- 0x000000005c6c0020 (dword)
    movl   $0x5c6c0020, 0xfed10d24 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d28] <-- 0x00000000c3100020 (dword)
    movl   $0xc3100020, 0xfed10d28 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000d2c] <-- 0x000000001a100020 (dword)
    movl   $0x1a100020, 0xfed10d2c 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e60] <-- 0x00000000b9795a00 (dword)
    movl   $0xb9795a00, 0xfed10e60 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e80] <-- 0x0000000020c02000 (dword)
    movl   $0x20c02000, 0xfed10e80 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e6c] <-- 0x00000000420bd780 (dword)
    movl   $0x420bd780, 0xfed10e6c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e70] <-- 0x000000008d1e62e7 (dword)
    movl   $0x8d1e62e7, 0xfed10e70 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e88] <-- 0x0000000009bc40d3 (dword)
    movl   $0x9bc40d3, 0xfed10e88 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e8c] <-- 0x0000000060c81638 (dword)
    movl   $0x60c81638, 0xfed10e8c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e90] <-- 0x00000000357d8809 (dword)
    movl   $0x357d8809, 0xfed10e90 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e7c] <-- 0x00000000da000000 (dword)
    movl   $0xda000000, 0xfed10e7c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e98] <-- 0x000000007835bc00 (dword)
    movl   $0x7835bc00, 0xfed10e98 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e9c] <-- 0x00000000e3e90200 (dword)
    movl   $0xe3e90200, 0xfed10e9c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000ea0] <-- 0x0000000057306800 (dword)
    movl   $0x57306800, 0xfed10ea0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000ea8] <-- 0x00000000edeaa400 (dword)
    movl   $0xedeaa400, 0xfed10ea8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e40] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10e40 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e44] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10e44 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e4c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed10e4c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e50] <-- 0x0000000029f1c73b (dword)
    movl   $0x29f1c73b, 0xfed10e50 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e54] <-- 0x0000000011db15eb (dword)
    movl   $0x11db15eb, 0xfed10e54 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e58] <-- 0x000000003867176c (dword)
    movl   $0x3867176c, 0xfed10e58 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e5c] <-- 0x000000002b58ce8c (dword)
    movl   $0x2b58ce8c, 0xfed10e5c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e10] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10e10 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e14] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10e14 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e18] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10e18 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e1c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10e1c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e00] <-- 0x000000007c0180ac (dword)
    movl   $0x7c0180ac, 0xfed10e00 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e04] <-- 0x00000000480200ac (dword)
    movl   $0x480200ac, 0xfed10e04 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e08] <-- 0x00000000c00500ac (dword)
    movl   $0xc00500ac, 0xfed10e08 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e0c] <-- 0x00000000240900ac (dword)
    movl   $0x240900ac, 0xfed10e0c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e20] <-- 0x000000009c100020 (dword)
    movl   $0x9c100020, 0xfed10e20 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e24] <-- 0x000000002bc40020 (dword)
    movl   $0x2bc40020, 0xfed10e24 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e28] <-- 0x00000000eafc0020 (dword)
    movl   $0xeafc0020, 0xfed10e28 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000e2c] <-- 0x0000000044dc0020 (dword)
    movl   $0x44dc0020, 0xfed10e2c 

    // writing to register DDRDATA_CR_DATATRAINFEEDBACK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f60] <-- 0x00000000e7097c00 (dword)
    movl   $0xe7097c00, 0xfed10f60 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f80] <-- 0x0000000084c00000 (dword)
    movl   $0x84c00000, 0xfed10f80 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f6c] <-- 0x00000000520befd0 (dword)
    movl   $0x520befd0, 0xfed10f6c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f70] <-- 0x00000000571e6291 (dword)
    movl   $0x571e6291, 0xfed10f70 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f88] <-- 0x0000000003058268 (dword)
    movl   $0x3058268, 0xfed10f88 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL4_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f8c] <-- 0x0000000020b216d8 (dword)
    movl   $0x20b216d8, 0xfed10f8c 

    // writing to register DDRDATA_CR_DDRCRDATACONTROL5_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f90] <-- 0x000000001f72b802 (dword)
    movl   $0x1f72b802, 0xfed10f90 

    // writing to register DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f7c] <-- 0x0000000072000000 (dword)
    movl   $0x72000000, 0xfed10f7c 

    // writing to register DDRDATA_CR_DELTADQSRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f98] <-- 0x00000000527ae800 (dword)
    movl   $0x527ae800, 0xfed10f98 

    // writing to register DDRDATA_CR_DELTADQSRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f9c] <-- 0x00000000ac7b6a00 (dword)
    movl   $0xac7b6a00, 0xfed10f9c 

    // writing to register DDRDATA_CR_DELTADQSRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000fa0] <-- 0x000000001a741200 (dword)
    movl   $0x1a741200, 0xfed10fa0 

    // writing to register DDRDATA_CR_DELTADQSRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000fa8] <-- 0x00000000e3716800 (dword)
    movl   $0xe3716800, 0xfed10fa8 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f40] <-- 0x00000000000a402a (dword)
    movl   $0xa402a, 0xfed10f40 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f44] <-- 0x000000006800001b (dword)
    movl   $0x6800001b, 0xfed10f44 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f4c] <-- 0x0000000000150000 (dword)
    movl   $0x150000, 0xfed10f4c 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f50] <-- 0x000000000fbd9613 (dword)
    movl   $0xfbd9613, 0xfed10f50 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f54] <-- 0x00000000166dbb9b (dword)
    movl   $0x166dbb9b, 0xfed10f54 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f58] <-- 0x000000001014eefc (dword)
    movl   $0x1014eefc, 0xfed10f58 

    // writing to register DDRDATA_CR_RXOFFSETVDQRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f5c] <-- 0x00000000fa5f1a92 (dword)
    movl   $0xfa5f1a92, 0xfed10f5c 

    // writing to register DDRDATA_CR_RXPERBITRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f10] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10f10 

    // writing to register DDRDATA_CR_RXPERBITRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f14] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10f14 

    // writing to register DDRDATA_CR_RXPERBITRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f18] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10f18 

    // writing to register DDRDATA_CR_RXPERBITRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f1c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed10f1c 

    // writing to register DDRDATA_CR_RXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f00] <-- 0x00000000340d00a4 (dword)
    movl   $0x340d00a4, 0xfed10f00 

    // writing to register DDRDATA_CR_RXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f04] <-- 0x00000000280c00a4 (dword)
    movl   $0x280c00a4, 0xfed10f04 

    // writing to register DDRDATA_CR_RXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f08] <-- 0x00000000a00800a4 (dword)
    movl   $0xa00800a4, 0xfed10f08 

    // writing to register DDRDATA_CR_RXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f0c] <-- 0x00000000a00600a4 (dword)
    movl   $0xa00600a4, 0xfed10f0c 

    // writing to register DDRDATA_CR_TXTRAINRANK0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f20] <-- 0x00000000eb300020 (dword)
    movl   $0xeb300020, 0xfed10f20 

    // writing to register DDRDATA_CR_TXTRAINRANK1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f24] <-- 0x000000004d2c0020 (dword)
    movl   $0x4d2c0020, 0xfed10f24 

    // writing to register DDRDATA_CR_TXTRAINRANK2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f28] <-- 0x0000000071a00020 (dword)
    movl   $0x71a00020, 0xfed10f28 

    // writing to register DDRDATA_CR_TXTRAINRANK3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f2c] <-- 0x000000001d840020 (dword)
    movl   $0x1d840020, 0xfed10f2c 

    // writing to register DDRDATA_CR_TXXTALK_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000000f48] <-- 0x0000000010101011 (dword)
    movl   $0x10101011, 0xfed10f48 

    // writing to register DDRCOMP_CR_DDRCRDATACOMP2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000001e2c] <-- 0x000000000000001f (dword)
    movl   $0x1f, 0xfed11e2c 

    // writing to register DDRSCRAM_CR_DDRMISCCONTROL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002008] <-- 0x00000000001ee702 (dword)
    movl   $0x1ee702, 0xfed12008 

    // writing to register DDRSCRAM_CR_DDRMISCCONTROL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002034] <-- 0x0000000028540010 (dword)
    movl   $0x28540010, 0xfed12034 

    // writing to register DDRSCRAM_CR_DDRMISCCONTROL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002038] <-- 0x0000000028540010 (dword)
    movl   $0x28540010, 0xfed12038 

    // writing to register MCMISCS_DELTADQSCOMMON1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000020b0] <-- 0x0000000068000000 (dword)
    movl   $0x68000000, 0xfed120b0 

    // writing to register MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000209c] <-- 0x00000000b8940735 (dword)
    movl   $0xb8940735, 0xfed1209c 

    // writing to register MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000020a0] <-- 0x000000000cb3caf0 (dword)
    movl   $0xcb3caf0, 0xfed120a0 

    // writing to register MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000020a4] <-- 0x00000000f2083574 (dword)
    movl   $0xf2083574, 0xfed120a4 

    // writing to register MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x00000000000020a8] <-- 0x000000005cf8a94f (dword)
    movl   $0x5cf8a94f, 0xfed120a8 

    // writing to register MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000203c] <-- 0x000000002f72a065 (dword)
    movl   $0x2f72a065, 0xfed1203c 

    // writing to register MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002040] <-- 0x00000000bb54b448 (dword)
    movl   $0xbb54b448, 0xfed12040 

    // writing to register MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002044] <-- 0x0000000033f74d45 (dword)
    movl   $0x33f74d45, 0xfed12044 

    // writing to register MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002048] <-- 0x00000000f021835c (dword)
    movl   $0xf021835c, 0xfed12048 

    // writing to register MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000204c] <-- 0x0000000037d85a95 (dword)
    movl   $0x37d85a95, 0xfed1204c 

    // writing to register MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002050] <-- 0x00000000c1a74072 (dword)
    movl   $0xc1a74072, 0xfed12050 

    // writing to register MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002054] <-- 0x000000002d2bcf44 (dword)
    movl   $0x2d2bcf44, 0xfed12054 

    // writing to register MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002058] <-- 0x00000000fc907ad7 (dword)
    movl   $0xfc907ad7, 0xfed12058 

    // writing to register MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000205c] <-- 0x00000000bee9ac23 (dword)
    movl   $0xbee9ac23, 0xfed1205c 

    // writing to register MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002060] <-- 0x00000000d36ae7eb (dword)
    movl   $0xd36ae7eb, 0xfed12060 

    // writing to register MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002064] <-- 0x00000000e50245e3 (dword)
    movl   $0xe50245e3, 0xfed12064 

    // writing to register MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002068] <-- 0x000000009f8957ce (dword)
    movl   $0x9f8957ce, 0xfed12068 

    // writing to register MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000206c] <-- 0x000000009c994aab (dword)
    movl   $0x9c994aab, 0xfed1206c 

    // writing to register MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002070] <-- 0x00000000fb01d407 (dword)
    movl   $0xfb01d407, 0xfed12070 

    // writing to register MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002074] <-- 0x0000000027fcd04c (dword)
    movl   $0x27fcd04c, 0xfed12074 

    // writing to register MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002078] <-- 0x00000000d215a5ab (dword)
    movl   $0xd215a5ab, 0xfed12078 

    // writing to register MCMISCS_READCFGCH0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000201c] <-- 0x0000000039244004 (dword)
    movl   $0x39244004, 0xfed1201c 

    // writing to register MCMISCS_READCFGCH1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002020] <-- 0x0000000039242004 (dword)
    movl   $0x39242004, 0xfed12020 

    // writing to register MCMISCS_READCFGCH2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002024] <-- 0x000000003924e005 (dword)
    movl   $0x3924e005, 0xfed12024 

    // writing to register MCMISCS_READCFGCH3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002028] <-- 0x000000003924d005 (dword)
    movl   $0x3924d005, 0xfed12028 

    // writing to register MCMISCS_ROCOUNTTRAINCH0DEV0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000207c] <-- 0x00000000f1bcf361 (dword)
    movl   $0xf1bcf361, 0xfed1207c 

    // writing to register MCMISCS_ROCOUNTTRAINCH0DEV1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002080] <-- 0x000000003fbd2f35 (dword)
    movl   $0x3fbd2f35, 0xfed12080 

    // writing to register MCMISCS_ROCOUNTTRAINCH1DEV0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002084] <-- 0x00000000610b4eb3 (dword)
    movl   $0x610b4eb3, 0xfed12084 

    // writing to register MCMISCS_ROCOUNTTRAINCH1DEV1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002088] <-- 0x00000000dbb33b7b (dword)
    movl   $0xdbb33b7b, 0xfed12088 

    // writing to register MCMISCS_ROCOUNTTRAINCH2DEV0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000208c] <-- 0x00000000fbe791fc (dword)
    movl   $0xfbe791fc, 0xfed1208c 

    // writing to register MCMISCS_ROCOUNTTRAINCH2DEV1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002090] <-- 0x000000006af6146b (dword)
    movl   $0x6af6146b, 0xfed12090 

    // writing to register MCMISCS_ROCOUNTTRAINCH3DEV0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002094] <-- 0x00000000b61cdf0f (dword)
    movl   $0xb61cdf0f, 0xfed12094 

    // writing to register MCMISCS_ROCOUNTTRAINCH3DEV1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002098] <-- 0x0000000007e381f7 (dword)
    movl   $0x7e381f7, 0xfed12098 

    // writing to register MCMISCS_WRITECFGCH0_0_0_0_MCHBAR of MCHBAR
    // r9 [0x000000000000200c] <-- 0x00000000ffdc0186 (dword)
    movl   $0xffdc0186, 0xfed1200c 

    // writing to register MCMISCS_WRITECFGCH1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002010] <-- 0x00000000ffe80186 (dword)
    movl   $0xffe80186, 0xfed12010 

    // writing to register MCMISCS_WRITECFGCH2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002014] <-- 0x00000000ffc80186 (dword)
    movl   $0xffc80186, 0xfed12014 

    // writing to register MCMISCS_WRITECFGCH3_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002018] <-- 0x00000000ffd80186 (dword)
    movl   $0xffd80186, 0xfed12018 

    // writing to register DDRVREF_CR_DDRCRVREFADJUST1_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002d08] <-- 0x00000000ba420120 (dword)
    movl   $0xba420120, 0xfed12d08 

    // writing to register DDRVREF_CR_DDRCRVREFADJUST2_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002d0c] <-- 0x000000000dfae6e3 (dword)
    movl   $0xdfae6e3, 0xfed12d0c 

    // writing to register DDRVREF_CR_DDRCRVREFCONTROL_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002d04] <-- 0x0000000000486e01 (dword)
    movl   $0x486e01, 0xfed12d04 

    // writing to register DDRVSSHIGH_CR_DDRCRVSSHICONTROL_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002e04] <-- 0x000000000042d21f (dword)
    movl   $0x42d21f, 0xfed12e04 

    // writing to register DDRVSSHIGH_CR_DDRCRVTTFORVSSHICORNRTROL_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002e08] <-- 0x000000000064810b (dword)
    movl   $0x64810b, 0xfed12e08 

    // writing to register DDRVSSHIGH_CR_DDRCRVSSHICONTROL_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000003004] <-- 0x000000000042d21f (dword)
    movl   $0x42d21f, 0xfed13004 

    // writing to register DDRVSSHIGH_CR_DDRCRVTTFORVSSHICORNRTROL_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000003008] <-- 0x000000000064810b (dword)
    movl   $0x64810b, 0xfed13008 

    // writing to register DDRVSSHIGH_CR_DDRCRVSSHICONTROL_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002f04] <-- 0x000000000042d21f (dword)
    movl   $0x42d21f, 0xfed12f04 

    // writing to register DDRVSSHIGH_CR_DDRCRVTTFORVSSHICORNRTROL_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000002f08] <-- 0x000000000064810b (dword)
    movl   $0x64810b, 0xfed12f08 

    // writing to register DDRVTT_CR_DDRCRVTTGENCONTROL_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000003400] <-- 0x000000000164890b (dword)
    movl   $0x164890b, 0xfed13400 

    // writing to register DDRVTT_CR_DDRCRVTTGENCONTROL_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000003800] <-- 0x000000000164890b (dword)
    movl   $0x164890b, 0xfed13800 

    // writing to register DDRVTT_CR_DDRCRVTTGENCONTROL_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000003200] <-- 0x000000000164890b (dword)
    movl   $0x164890b, 0xfed13200 

    // writing to register DDRVTT_CR_DDRCRVTTGENCONTROL_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000003600] <-- 0x000000000164890b (dword)
    movl   $0x164890b, 0xfed13600 

    // writing to register DDRVTT_CR_DDRCRVTTGENCONTROL_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000003300] <-- 0x000000000164890b (dword)
    movl   $0x164890b, 0xfed13300 

    // writing to register DDRVTT_CR_DDRCRVTTGENCONTROL_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000003700] <-- 0x000000000164890b (dword)
    movl   $0x164890b, 0xfed13700 

    // writing to register DDRVTT_CR_DDRCRVTTGENCONTROL_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000003100] <-- 0x000000000164890b (dword)
    movl   $0x164890b, 0xfed13100 

    // writing to register DDRVTT_CR_DDRCRVTTGENCONTROL_0_0_0_MCHBAR of MCHBAR
    // r9 [0x0000000000003500] <-- 0x000000000164890b (dword)
    movl   $0x164890b, 0xfed13500 

    // writing to register channel_ehash_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000005028] <-- 0x00000000270f7d40 (dword)
    movl   $0x270f7d40, 0xfed15028 

    // writing to register channel_hash_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000005024] <-- 0x00000000020846c0 (dword)
    movl   $0x20846c0, 0xfed15024 

    // writing to register ecc_inj_addr_compare_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000005088] <-- 0x00000000abaaeed9 (dword)
    movl   $0xabaaeed9, 0xfed15088 

    // writing to register ecc_inj_addr_mask_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000508c] <-- 0x00000000fbbeffff (dword)
    movl   $0xfbbeffff, 0xfed1508c 

    // writing to register ipc_mc_arb_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000005078] <-- 0x000000000049c2b5 (dword)
    movl   $0x49c2b5, 0xfed15078 

    // writing to register mad_dimm_ch0_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000500c] <-- 0x0000000000000440 (dword)
    movl   $0x440, 0xfed1500c 

    // writing to register mad_dimm_ch1_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000005010] <-- 0x0000000000000440 (dword)
    movl   $0x440, 0xfed15010 

    // writing to register mad_inter_channel_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000005000] <-- 0x0000000003040000 (dword)
    movl   $0x3040000, 0xfed15000 

    // writing to register mad_intra_ch0_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000005004] <-- 0x0000000000000010 (dword)
    movl   $0x10, 0xfed15004 

    // writing to register mad_intra_ch1_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000005008] <-- 0x0000000000000010 (dword)
    movl   $0x10, 0xfed15008 

    // writing to register mc_global_driver_gate_cfg_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000005138] <-- 0x0000000000000154 (dword)
    movl   $0x154, 0xfed15138 

    // writing to register mcdecs_cbit_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000501c] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed1501c 

    // writing to register mcdecs_misc_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000005018] <-- 0x00000000cfc90000 (dword)
    movl   $0xcfc90000, 0xfed15018 

    // writing to register pm_sref_config_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000005060] <-- 0x00000000000106c8 (dword)
    movl   $0x106c8, 0xfed15060 

    // writing to register rcomp_timer_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000005084] <-- 0x0000000000016cf1 (dword)
    movl   $0x16cf1, 0xfed15084 

    // writing to register remapbase_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x5094] <-- 0x7f (dword)
    movl   $0x7f, 0xfed15094 

    // writing to register remapbase_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x0000000000005090] <-- 0xfff00000 (dword)
    movl   $0xfff00000, 0xfed15090 

    // writing to register remaplimit_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x509c] <-- 0x0 (dword)
    movl   $0x0, 0xfed1509c 

    // writing to register remaplimit_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x0000000000005098] <-- 0x0 (dword)
    movl   $0x0, 0xfed15098 

    // writing to register sc_qos_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x5134] <-- 0x70d06 (dword)
    movl   $0x70d06, 0xfed15134 

    // writing to register sc_qos_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x0000000000005130] <-- 0xa07c02ce (dword)
    movl   $0xa07c02ce, 0xfed15130 

    // writing to register tolud_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000050bc] <-- 0x86000000 (dword)
    movl   $0x86000000, 0xfed150bc 

    // writing to register ddrpl_cfg_dtf_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000005200] <-- 0x000000000cbe9680 (dword)
    movl   $0xcbe9680, 0xfed15200 

    // writing to register ddrpl_debug_dtf_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000005208] <-- 0x000000001a9c0000 (dword)
    movl   $0x1a9c0000, 0xfed15208 

    // writing to register ddrpl_filter_dtf_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000005204] <-- 0x0000000000003481 (dword)
    movl   $0x3481, 0xfed15204 

    // writing to register ddr4_mr0_mr1_content_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000043a0] <-- 0x0000000001010210 (dword)
    movl   $0x1010210, 0xfed143a0 

    // writing to register ddr4_mr1_odic_values_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000043dc] <-- 0x0000000000514440 (dword)
    movl   $0x514440, 0xfed143dc 

    // writing to register ddr4_mr2_mr3_content_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000043a4] <-- 0x0000000000000010 (dword)
    movl   $0x10, 0xfed143a4 

    // writing to register ddr4_mr2_rtt_wr_values_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x43b4] <-- 0x14401301 (dword)
    movl   $0x14401301, 0xfed143b4 

    // writing to register ddr4_mr2_rtt_wr_values_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x00000000000043b0] <-- 0x2432442 (dword)
    movl   $0x2432442, 0xfed143b0 

    // writing to register ddr4_mr6_mr7_content_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000043ac] <-- 0x0000000000000415 (dword)
    movl   $0x415, 0xfed143ac 

    // writing to register ddr4_mr6_vref_values_0_0_0_mchbar[0] <HIGH> of MCHBAR
    // r9 [0x43bc] <-- 0x1e430018 (dword)
    movl   $0x1e430018, 0xfed143bc 

    // writing to register ddr4_mr6_vref_values_0_0_0_mchbar[0] <LOW> of MCHBAR
    // r9 [0x00000000000043b8] <-- 0x2d16321e (dword)
    movl   $0x2d16321e, 0xfed143b8 

    // writing to register ddr4_mr6_vref_values_0_0_0_mchbar[1] <HIGH> of MCHBAR
    // r9 [0x43c4] <-- 0x54027123 (dword)
    movl   $0x54027123, 0xfed143c4 

    // writing to register ddr4_mr6_vref_values_0_0_0_mchbar[1] <LOW> of MCHBAR
    // r9 [0x00000000000043c0] <-- 0x6c0d2c23 (dword)
    movl   $0x6c0d2c23, 0xfed143c0 

    // writing to register ecc_inject_count_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004274] <-- 0x00000000000003b3 (dword)
    movl   $0x3b3, 0xfed14274 

    // writing to register lp4_dqs_oscillator_params_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000042c8] <-- 0x00000000005600f7 (dword)
    movl   $0x5600f7, 0xfed142c8 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[0] of MCHBAR
    // r9 [0x0000000000004380] <-- 0x0000000003daa44f (dword)
    movl   $0x3daa44f, 0xfed14380 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[1] of MCHBAR
    // r9 [0x0000000000004384] <-- 0x000000000269b4e5 (dword)
    movl   $0x269b4e5, 0xfed14384 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[2] of MCHBAR
    // r9 [0x0000000000004388] <-- 0x0000000001e5c305 (dword)
    movl   $0x1e5c305, 0xfed14388 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[3] of MCHBAR
    // r9 [0x000000000000438c] <-- 0x000000000339e82b (dword)
    movl   $0x339e82b, 0xfed1438c 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[4] of MCHBAR
    // r9 [0x0000000000004390] <-- 0x0000000000288d50 (dword)
    movl   $0x288d50, 0xfed14390 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[5] of MCHBAR
    // r9 [0x0000000000004394] <-- 0x0000000000b2ba90 (dword)
    movl   $0xb2ba90, 0xfed14394 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[6] of MCHBAR
    // r9 [0x0000000000004398] <-- 0x00000000001f3d74 (dword)
    movl   $0x1f3d74, 0xfed14398 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[7] of MCHBAR
    // r9 [0x000000000000439c] <-- 0x0000000001f2f4e4 (dword)
    movl   $0x1f2f4e4, 0xfed1439c 

    // writing to register lpddr_mr_content_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x43cc] <-- 0x7eec7650 (dword)
    movl   $0x7eec7650, 0xfed143cc 

    // writing to register lpddr_mr_content_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x00000000000043c8] <-- 0xa9e792bb (dword)
    movl   $0xa9e792bb, 0xfed143c8 

    // writing to register mc_init_state_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004254] <-- 0x0000000000000003 (dword)
    movl   $0x3, 0xfed14254 

    // writing to register mc_refresh_stagger_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004244] <-- 0x000000000000713a (dword)
    movl   $0x713a, 0xfed14244 

    // writing to register mcmnts_spare_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000043fc] <-- 0x0000000082fc0024 (dword)
    movl   $0x82fc0024, 0xfed143fc 

    // writing to register pm_dimm_act_energy_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004268] <-- 0x000000000000b779 (dword)
    movl   $0xb779, 0xfed14268 

    // writing to register pm_dimm_idle_energy_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004260] <-- 0x000000000000312d (dword)
    movl   $0x312d, 0xfed14260 

    // writing to register pm_dimm_pd_energy_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004264] <-- 0x0000000000000836 (dword)
    movl   $0x836, 0xfed14264 

    // writing to register pm_dimm_rd_energy_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000426c] <-- 0x00000000000088dc (dword)
    movl   $0x88dc, 0xfed1426c 

    // writing to register pm_dimm_wr_energy_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004270] <-- 0x000000000000f3c3 (dword)
    movl   $0xf3c3, 0xfed14270 

    // writing to register rh_control_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000042c0] <-- 0x00000000005b30e0 (dword)
    movl   $0x5b30e0, 0xfed142c0 

    // writing to register rh_lfsr_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x42bc] <-- 0x1751e467 (dword)
    movl   $0x1751e467, 0xfed142bc 

    // writing to register rh_lfsr_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x00000000000042b8] <-- 0x64146433 (dword)
    movl   $0x64146433, 0xfed142b8 

    // writing to register tc_mr2_shaddow_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000424c] <-- 0x0000000000000010 (dword)
    movl   $0x10, 0xfed1424c 

    // writing to register tc_rfp_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004238] <-- 0x0000000054005442 (dword)
    movl   $0x54005442, 0xfed14238 

    // writing to register tc_rftp_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000423c] <-- 0x00000000006a1860 (dword)
    movl   $0x6a1860, 0xfed1423c 

    // writing to register tc_srexittp_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000042c4] <-- 0x0000000000000c72 (dword)
    movl   $0xc72, 0xfed142c4 

    // writing to register tc_srftp_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004240] <-- 0x0000000061000200 (dword)
    movl   $0x61000200, 0xfed14240 

    // writing to register tc_zqcal_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004248] <-- 0x0000000010010010 (dword)
    movl   $0x10010010, 0xfed14248 

    // writing to register wdb_visa_sel_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004258] <-- 0x0000000000003e00 (dword)
    movl   $0x3e00, 0xfed14258 

    // writing to register ddr4_mr0_mr1_content_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000047a0] <-- 0x0000000002010214 (dword)
    movl   $0x2010214, 0xfed147a0 

    // writing to register ddr4_mr1_odic_values_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000047dc] <-- 0x0000000000155150 (dword)
    movl   $0x155150, 0xfed147dc 

    // writing to register ddr4_mr2_mr3_content_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000047a4] <-- 0x0000000000000010 (dword)
    movl   $0x10, 0xfed147a4 

    // writing to register ddr4_mr2_rtt_wr_values_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x47b4] <-- 0x22021000 (dword)
    movl   $0x22021000, 0xfed147b4 

    // writing to register ddr4_mr2_rtt_wr_values_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x00000000000047b0] <-- 0x40130140 (dword)
    movl   $0x40130140, 0xfed147b0 

    // writing to register ddr4_mr6_mr7_content_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000047ac] <-- 0x0000000000000403 (dword)
    movl   $0x403, 0xfed147ac 

    // writing to register ddr4_mr6_vref_values_0_0_0_mchbar[0] <HIGH> of MCHBAR
    // r9 [0x47bc] <-- 0x664a0256 (dword)
    movl   $0x664a0256, 0xfed147bc 

    // writing to register ddr4_mr6_vref_values_0_0_0_mchbar[0] <LOW> of MCHBAR
    // r9 [0x00000000000047b8] <-- 0xc0e1f54 (dword)
    movl   $0xc0e1f54, 0xfed147b8 

    // writing to register ddr4_mr6_vref_values_0_0_0_mchbar[1] <HIGH> of MCHBAR
    // r9 [0x47c4] <-- 0x65295e07 (dword)
    movl   $0x65295e07, 0xfed147c4 

    // writing to register ddr4_mr6_vref_values_0_0_0_mchbar[1] <LOW> of MCHBAR
    // r9 [0x00000000000047c0] <-- 0x1749546e (dword)
    movl   $0x1749546e, 0xfed147c0 

    // writing to register ecc_inject_count_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004674] <-- 0x000000000000003d (dword)
    movl   $0x3d, 0xfed14674 

    // writing to register lp4_dqs_oscillator_params_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000046c8] <-- 0x00000000008506f3 (dword)
    movl   $0x8506f3, 0xfed146c8 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[0] of MCHBAR
    // r9 [0x0000000000004780] <-- 0x00000000009dd78a (dword)
    movl   $0x9dd78a, 0xfed14780 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[1] of MCHBAR
    // r9 [0x0000000000004784] <-- 0x00000000036fd00d (dword)
    movl   $0x36fd00d, 0xfed14784 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[2] of MCHBAR
    // r9 [0x0000000000004788] <-- 0x0000000000b1c75d (dword)
    movl   $0xb1c75d, 0xfed14788 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[3] of MCHBAR
    // r9 [0x000000000000478c] <-- 0x0000000000ba428e (dword)
    movl   $0xba428e, 0xfed1478c 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[4] of MCHBAR
    // r9 [0x0000000000004790] <-- 0x0000000002a458ed (dword)
    movl   $0x2a458ed, 0xfed14790 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[5] of MCHBAR
    // r9 [0x0000000000004794] <-- 0x00000000012650af (dword)
    movl   $0x12650af, 0xfed14794 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[6] of MCHBAR
    // r9 [0x0000000000004798] <-- 0x00000000033e7345 (dword)
    movl   $0x33e7345, 0xfed14798 

    // writing to register lpddr4_discrete_mr_values_0_0_0_mchbar[7] of MCHBAR
    // r9 [0x000000000000479c] <-- 0x0000000003f55f00 (dword)
    movl   $0x3f55f00, 0xfed1479c 

    // writing to register lpddr_mr_content_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x47cc] <-- 0x7e280de0 (dword)
    movl   $0x7e280de0, 0xfed147cc 

    // writing to register lpddr_mr_content_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x00000000000047c8] <-- 0xe00e9eec (dword)
    movl   $0xe00e9eec, 0xfed147c8 

    // writing to register mc_init_state_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004654] <-- 0x0000000000000003 (dword)
    movl   $0x3, 0xfed14654 

    // writing to register mc_refresh_stagger_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004644] <-- 0x0000000000004071 (dword)
    movl   $0x4071, 0xfed14644 

    // writing to register mcmnts_spare_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000047fc] <-- 0x00000000e9a20047 (dword)
    movl   $0xe9a20047, 0xfed147fc 

    // writing to register pm_dimm_act_energy_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004668] <-- 0x0000000000004094 (dword)
    movl   $0x4094, 0xfed14668 

    // writing to register pm_dimm_idle_energy_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004660] <-- 0x0000000000003028 (dword)
    movl   $0x3028, 0xfed14660 

    // writing to register pm_dimm_pd_energy_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004664] <-- 0x0000000000001c20 (dword)
    movl   $0x1c20, 0xfed14664 

    // writing to register pm_dimm_rd_energy_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000466c] <-- 0x000000000000b493 (dword)
    movl   $0xb493, 0xfed1466c 

    // writing to register pm_dimm_wr_energy_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004670] <-- 0x0000000000007276 (dword)
    movl   $0x7276, 0xfed14670 

    // writing to register rh_control_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000046c0] <-- 0x0000000003af20e0 (dword)
    movl   $0x3af20e0, 0xfed146c0 

    // writing to register rh_lfsr_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x46bc] <-- 0x33c7b22e (dword)
    movl   $0x33c7b22e, 0xfed146bc 

    // writing to register rh_lfsr_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x00000000000046b8] <-- 0xe18bce1b (dword)
    movl   $0xe18bce1b, 0xfed146b8 

    // writing to register tc_mr2_shaddow_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000464c] <-- 0x0000000000000010 (dword)
    movl   $0x10, 0xfed1464c 

    // writing to register tc_rfp_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004638] <-- 0x000000003a005461 (dword)
    movl   $0x3a005461, 0xfed14638 

    // writing to register tc_rftp_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000463c] <-- 0x0000000000c11860 (dword)
    movl   $0xc11860, 0xfed1463c 

    // writing to register tc_srexittp_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000046c4] <-- 0x0000000000000cc9 (dword)
    movl   $0xcc9, 0xfed146c4 

    // writing to register tc_srftp_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004640] <-- 0x0000000061000200 (dword)
    movl   $0x61000200, 0xfed14640 

    // writing to register tc_zqcal_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004648] <-- 0x0000000010010006 (dword)
    movl   $0x10010006, 0xfed14648 

    // writing to register mcscheds_spare_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004078] <-- 0x000000000000b8c0 (dword)
    movl   $0xb8c0, 0xfed14078 

    // writing to register pm_pdwn_config_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004040] <-- 0x00000000007567af (dword)
    movl   $0x7567af, 0xfed14040 

    // writing to register reut_ch_misc_cke_ctrl_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004190] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed14190 

    // writing to register sc_gs_cfg_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x408c] <-- 0x0 (dword)
    movl   $0x0, 0xfed1408c 

    // writing to register sc_gs_cfg_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x0000000000004088] <-- 0x31002068 (dword)
    movl   $0x31002068, 0xfed14088 

    // writing to register sc_gs_cfg_training_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000419c] <-- 0x000000000000000a (dword)
    movl   $0xa, 0xfed1419c 

    // writing to register sc_odt_matrix_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004080] <-- 0x00000000b4e19da3 (dword)
    movl   $0xb4e19da3, 0xfed14080 

    // writing to register sc_pcit_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000403c] <-- 0x00000000006900e7 (dword)
    movl   $0x6900e7, 0xfed1403c 

    // writing to register sc_pr_cnt_config_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004038] <-- 0x000000000010001e (dword)
    movl   $0x10001e, 0xfed14038 

    // writing to register sc_roundtrip_latency_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x4024] <-- 0x645a4756 (dword)
    movl   $0x645a4756, 0xfed14024 

    // writing to register sc_roundtrip_latency_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x0000000000004020] <-- 0x29292929 (dword)
    movl   $0x29292929, 0xfed14020 

    // writing to register sc_wdbwm_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x406c] <-- 0xb511326 (dword)
    movl   $0xb511326, 0xfed1406c 

    // writing to register sc_wdbwm_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x0000000000004068] <-- 0x20351517 (dword)
    movl   $0x20351517, 0xfed14068 

    // writing to register sched_cbit_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004028] <-- 0x00000000b0800500 (dword)
    movl   $0xb0800500, 0xfed14028 

    // writing to register sched_second_cbit_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000402c] <-- 0x0000000071735c44 (dword)
    movl   $0x71735c44, 0xfed1402c 

    // writing to register sched_third_cbit_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000041a0] <-- 0x00000000519b021a (dword)
    movl   $0x519b021a, 0xfed141a0 

    // writing to register spid_low_power_ctl_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004198] <-- 0x0000000088444443 (dword)
    movl   $0x88444443, 0xfed14198 

    // writing to register tc_act_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004004] <-- 0x0000000000088514 (dword)
    movl   $0x88514, 0xfed14004 

    // writing to register tc_odt_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x4074] <-- 0x7 (dword)
    movl   $0x7, 0xfed14074 

    // writing to register tc_odt_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x0000000000004070] <-- 0x2cb0002 (dword)
    movl   $0x2cb0002, 0xfed14070 

    // writing to register tc_pre_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004000] <-- 0x000000001ba6380b (dword)
    movl   $0x1ba6380b, 0xfed14000 

    // writing to register tc_pwrdn_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x4054] <-- 0x1b (dword)
    movl   $0x1b, 0xfed14054 

    // writing to register tc_pwrdn_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x0000000000004050] <-- 0x10940504 (dword)
    movl   $0x10940504, 0xfed14050 

    // writing to register tc_rdrd_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000400c] <-- 0x0000000007060405 (dword)
    movl   $0x7060405, 0xfed1400c 

    // writing to register tc_rdwr_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004010] <-- 0x0000000007060606 (dword)
    movl   $0x7060606, 0xfed14010 

    // writing to register tc_wrrd_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004014] <-- 0x0000000007071317 (dword)
    movl   $0x7071317, 0xfed14014 

    // writing to register tc_wrwr_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004018] <-- 0x0000000007070405 (dword)
    movl   $0x7070405, 0xfed14018 

    // writing to register wmm_read_config_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004044] <-- 0x000000000000005e (dword)
    movl   $0x5e, 0xfed14044 

    // writing to register deadlock_breaker_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000045a4] <-- 0x0000000083860c30 (dword)
    movl   $0x83860c30, 0xfed145a4 

    // writing to register dft_block_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004484] <-- 0x0000000000ad003c (dword)
    movl   $0xad003c, 0xfed14484 

    // writing to register dft_misc_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004430] <-- 0x0000000044010000 (dword)
    movl   $0x44010000, 0xfed14430 

    // writing to register ecc_dft_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004434] <-- 0x0000000000010900 (dword)
    movl   $0x10900, 0xfed14434 

    // writing to register mcscheds_spare_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004478] <-- 0x00000000000086c0 (dword)
    movl   $0x86c0, 0xfed14478 

    // writing to register pm_pdwn_config_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004440] <-- 0x000000000075a4c5 (dword)
    movl   $0x75a4c5, 0xfed14440 

    // writing to register reut_ch_misc_cke_ctrl_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004590] <-- 0x0000000000000000 (dword)
    movl   $0x0, 0xfed14590 

    // writing to register sc_gs_cfg_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x448c] <-- 0x0 (dword)
    movl   $0x0, 0xfed1448c 

    // writing to register sc_gs_cfg_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x0000000000004488] <-- 0x71002048 (dword)
    movl   $0x71002048, 0xfed14488 

    // writing to register sc_gs_cfg_training_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000459c] <-- 0x00000000000000f2 (dword)
    movl   $0xf2, 0xfed1459c 

    // writing to register sc_odt_matrix_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004480] <-- 0x00000000d7a1bd23 (dword)
    movl   $0xd7a1bd23, 0xfed14480 

    // writing to register sc_pcit_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000443c] <-- 0x0000000000950045 (dword)
    movl   $0x950045, 0xfed1443c 

    // writing to register sc_pr_cnt_config_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004438] <-- 0x00000000001a0029 (dword)
    movl   $0x1a0029, 0xfed14438 

    // writing to register sc_roundtrip_latency_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x4424] <-- 0x4f614d64 (dword)
    movl   $0x4f614d64, 0xfed14424 

    // writing to register sc_roundtrip_latency_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x0000000000004420] <-- 0x2b2b2b2b (dword)
    movl   $0x2b2b2b2b, 0xfed14420 

    // writing to register sc_wdbwm_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x446c] <-- 0x3e511326 (dword)
    movl   $0x3e511326, 0xfed1446c 

    // writing to register sc_wdbwm_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x0000000000004468] <-- 0x20351517 (dword)
    movl   $0x20351517, 0xfed14468 

    // writing to register sched_cbit_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004428] <-- 0x0000000000400000 (dword)
    movl   $0x400000, 0xfed14428 

    // writing to register sched_second_cbit_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000442c] <-- 0x000000001a38c054 (dword)
    movl   $0x1a38c054, 0xfed1442c 

    // writing to register sched_third_cbit_0_0_0_mchbar of MCHBAR
    // r9 [0x00000000000045a0] <-- 0x00000000a1888562 (dword)
    movl   $0xa1888562, 0xfed145a0 

    // writing to register spid_low_power_ctl_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004598] <-- 0x00000000a8444443 (dword)
    movl   $0xa8444443, 0xfed14598 

    // writing to register tc_act_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004404] <-- 0x0000000000088514 (dword)
    movl   $0x88514, 0xfed14404 

    // writing to register tc_odt_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x4474] <-- 0x7 (dword)
    movl   $0x7, 0xfed14474 

    // writing to register tc_odt_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x0000000000004470] <-- 0x2cc0012 (dword)
    movl   $0x2cc0012, 0xfed14470 

    // writing to register tc_pre_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004400] <-- 0x000000001bc6380c (dword)
    movl   $0x1bc6380c, 0xfed14400 

    // writing to register tc_pwrdn_0_0_0_mchbar <HIGH> of MCHBAR
    // r9 [0x4454] <-- 0x1b (dword)
    movl   $0x1b, 0xfed14454 

    // writing to register tc_pwrdn_0_0_0_mchbar <LOW> of MCHBAR
    // r9 [0x0000000000004450] <-- 0x11940504 (dword)
    movl   $0x11940504, 0xfed14450 

    // writing to register tc_rdrd_0_0_0_mchbar of MCHBAR
    // r9 [0x000000000000440c] <-- 0x0000000007060405 (dword)
    movl   $0x7060405, 0xfed1440c 

    // writing to register tc_rdwr_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004410] <-- 0x0000000008070707 (dword)
    movl   $0x8070707, 0xfed14410 

    // writing to register tc_wrrd_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004414] <-- 0x0000000007071317 (dword)
    movl   $0x7071317, 0xfed14414 

    // writing to register tc_wrwr_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004418] <-- 0x0000000007070405 (dword)
    movl   $0x7070405, 0xfed14418 

    // writing to register wmm_read_config_0_0_0_mchbar of MCHBAR
    // r9 [0x0000000000004444] <-- 0x000000000000005d (dword)
    movl   $0x5d, 0xfed14444 

    // writing to register DDRCKECTL_CR_DDRCRCTLPICODING_0_0_0_MCHBAR of MCHBAR
    // r9 [4632] <-- 4128 (dword)
    movl   $0x1020, 0xfed11218 

    // writing to register DDRCKECTL_CR_DDRCRCTLPICODING_0_0_0_MCHBAR of MCHBAR
    // r9 [4888] <-- 4128 (dword)
    movl   $0x1020, 0xfed11318 

    // writing to register DDRCKECTL_CR_DDRCRCTLPICODING_0_0_0_MCHBAR of MCHBAR
    // r9 [34840] <-- 4128 (dword)
    movl   $0x1020, 0xfed18818 

    // writing to register DDRCKECTL_CR_DDRCRCTLPICODING_0_0_0_MCHBAR of MCHBAR
    // r9 [33816] <-- 4128 (dword)
    movl   $0x1020, 0xfed18418 

    // writing to register DDRCKECTL_CR_DDRCRCTLPICODING_0_0_0_MCHBAR of MCHBAR
    // r9 [34072] <-- 4128 (dword)
    movl   $0x1020, 0xfed18518 

    // writing to register DDRCOMPCR_DDRCRCOMPOVR_0_0_0_MCHBAR of MCHBAR
    // r9 [14880] <-- 0xffffffff (dword)
    movl   $0xffffffff, 0xfed13a20 

    // writing to register DDRCOMPCR_DDRCRDATACOMP0_0_0_0_MCHBAR of MCHBAR
    // r9 [14848] <-- 0xffffffff (dword)
    movl   $0xffffffff, 0xfed13a00 

    // writing to register DDRCOMPCR_DDRCRDATACOMP1_0_0_0_MCHBAR of MCHBAR
    // r9 [14852] <-- 0xffffffff (dword)
    movl   $0xffffffff, 0xfed13a04 

    // writing to register DDRCOMPCR_DDRCRCMDCOMP_0_0_0_MCHBAR of MCHBAR
    // r9 [14856] <-- 0xffffffff (dword)
    movl   $0xffffffff, 0xfed13a08 

    // writing to register DDRCOMPCR_DDRCRCTLCOMP_0_0_0_MCHBAR of MCHBAR
    // r9 [14860] <-- 0xffffffff (dword)
    movl   $0xffffffff, 0xfed13a0c 

    // writing to register DDRCOMPCR_DDRCRDATACOMP2_0_0_0_MCHBAR of MCHBAR
    // r9 [14892] <-- 0xffffffff (dword)
    movl   $0xffffffff, 0xfed13a2c 

    // writing to register DDRDATA_CR_RCOMPDATA0_0_0_0_MCHBAR of MCHBAR
    // r9 [13888] <-- 0xffffffff (dword)
    movl   $0xffffffff, 0xfed13640 

    // writing to register DDRDATA_CR_RCOMPDATA1_0_0_0_MCHBAR of MCHBAR
    // r9 [13892] <-- 0xffffffff (dword)
    movl   $0xffffffff, 0xfed13644 

    // writing to register DDRDATA_CR_RCOMPDATA2_0_0_0_MCHBAR of MCHBAR
    // r9 [13900] <-- 0xffffffff (dword)
    movl   $0xffffffff, 0xfed1364c 

    // updating register MC_Init_State_G_0_0_0_MCHBAR 
    // edx <-- r9 [0x5030] (dword)
    movl   0xfed15030, %edx 

    or    $0x40010, %edx 

    // r9 [0x5030] <-- edx (dword)
    movl  %edx, 0xfed15030 

    // setting MC normal mode
    // writing to register MCDFXS_CR_REUT_CH_SEQ_CFG_0_0_0_MCHBAR_MCMAIN_0 of MCHBAR
    // r9 [0x48a8] <-- 0x3000 (dword)
    movl   $0x3000, 0xfed148a8 

        // writing to register MCDFXS_CR_REUT_CH_SEQ_CFG_0_0_0_MCHBAR_MCMAIN_1 of MCHBAR
        // r9 [0x48b0] <-- 0x3000 (dword)
    movl   $0x3000, 0xfed148b0 

    ret
