/** @file
  Internal header of the Setup Component.

  Macros defined here are used to specify VFR FormId or QuestionId in VFR and SD files.
  When VFR files are updated, new macros may be required to specify new FormId or QuestionId.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2019 Intel Corporation.

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

#define MAIN_MAIN                                 4096
#define ADVANCED_MAIN                             4097
#define BOOT_MAIN                                 4098
#define BBS_ORDER_FORM                            4099
#define DEBUG_FORM_ID                             4102
#define PLATFORM_DEBUG_CONSENT_KEY                4103
#define PCI_FORM_ID                               4104
#define WHEA_SETUP_KEY                            4105
#define ACPI_FORM_ID                              4106
#define SETUP_VOLATILE_DATA_ID                    4107
#define CPU_FEATURES_ID                           4108
#define CPU_FORM_ID                               4109
#define POWER_CONFIG_FORM_ID                      4110
#define CPU_POWER_CONFIG_FORM_ID                  4111
#define VID_OPTIONS_FORM_ID                       4112
#define CPU_TURBO_OPTIONS_FORM_ID                 4113
#define CPU_LOCK_OPTIONS_FORM_ID                  4114
#define PERFORMANCE_MENU_CONFIG_FORM_ID           4115
#define PROCESSOR_CONFIG_FORM_ID                  4116
#define KEY_RatioLimit1                           4117
#define KEY_RatioLimit2                           4118
#define KEY_RatioLimit3                           4119
#define KEY_RatioLimit4                           4120
//
// KEY_RatioLimit5, KEY_RatioLimit6, KEY_RatioLimit7, KEY_RatioLimit8 are located below, values 4257-4260
//
#define KEY_XeVoltage                             4121
#define OVERCLOCK_KEY                             4122
#define GT_CONFIG_FORM_ID                         4123
#define MEMORY_CONFIG_FORM_ID                     4124
#define KEY_MEMINFO                               4125
#define KEY_MEMINFO1                              4126
#define KEY_MEMINFO2                              4127
#define KEY_MEMINFO3                              4128
#define KEY_MEMINFO4                              4129
#define KEY_MEMINFO5                              4130
#define KEY_MEMINFO6                              4131
#define KEY_MEMINFO7                              4132
#define KEY_MEMINFO8                              4133
#define KEY_MEMINFO9                              4134
#define KEY_MEMINFO10                             4135
#define MEMORY_FORM_ID                            4136
#define NB_FORM_ID                                4137
#define IGFX_FORM_ID                              4138
#define COMMON_NB_OPTIONS_FORM_ID                 4139
#define PEG_FORM_ID                               4140
#define IGFX_LCD_FORM_ID                          4141
#define GT_POWER_CONFIG_FORM_ID                   4142
#define SB_FORM_ID                                4143
#define PCIE_DEVICE_OPTIONS_FORM_ID               4144
#define USB_OPTIONS_FORM_ID                       4145
#define PCIE_FORM_ID                              5433
#define PCH_PCIE_CLOCK_FORM_ID                    5504
#define USB_TEST_OPTIONS_FORM_ID                  5300
#define TEST_USB_PORT_LOCK_FORM_ID                5301
#define TEST_USB_PORT_LOCK_POLICY_MENU_FORM_ID    5302
#define SATA_DEVICE_OPTIONS_FORM_ID               4146
#define PCH_SATA_SFMS_OPTIONS_FORM_ID             4147
#define PCIE_EQ_SETTINGS_FORM_ID                  4400
#define PCH_PCIERP0_OPTIONS_FORM_ID               5500
#define PCH_PCIERP1_OPTIONS_FORM_ID               4148
#define PCH_PCIERP2_OPTIONS_FORM_ID               4149
#define PCH_PCIERP3_OPTIONS_FORM_ID               4150
#define PCH_PCIERP4_OPTIONS_FORM_ID               4151
#define PCH_PCIERP5_OPTIONS_FORM_ID               4152
#define PCH_PCIERP6_OPTIONS_FORM_ID               4153
#define PCH_PCIERP7_OPTIONS_FORM_ID               4154
#define PCH_PCIERP8_OPTIONS_FORM_ID               4155
#define PCH_PCIERP9_OPTIONS_FORM_ID               5101
#define PCH_PCIERP10_OPTIONS_FORM_ID              5102
#define PCH_PCIERP11_OPTIONS_FORM_ID              5103
#define PCH_PCIERP12_OPTIONS_FORM_ID              5104
#define PCH_PCIERP13_OPTIONS_FORM_ID              5105
#define PCH_PCIERP14_OPTIONS_FORM_ID              5106
#define PCH_PCIERP15_OPTIONS_FORM_ID              5107
#define PCH_PCIERP16_OPTIONS_FORM_ID              5108
#define PCH_PCIERP17_OPTIONS_FORM_ID              5109
#define PCH_PCIERP18_OPTIONS_FORM_ID              5110
#define PCH_PCIERP19_OPTIONS_FORM_ID              5111
#define PCH_PCIERP20_OPTIONS_FORM_ID              5112
#define PCH_PCIERP21_OPTIONS_FORM_ID              5501
#define PCH_PCIERP22_OPTIONS_FORM_ID              5502
#define PCH_PCIERP23_OPTIONS_FORM_ID              5503
#define PCH_ASPM_PCIERP0_QUESTION_ID              5600
#define PCH_ASPM_PCIERP1_QUESTION_ID              5601
#define PCH_ASPM_PCIERP2_QUESTION_ID              5602
#define PCH_ASPM_PCIERP3_QUESTION_ID              5603
#define PCH_ASPM_PCIERP4_QUESTION_ID              5604
#define PCH_ASPM_PCIERP5_QUESTION_ID              5605
#define PCH_ASPM_PCIERP6_QUESTION_ID              5606
#define PCH_ASPM_PCIERP7_QUESTION_ID              5607
#define PCH_ASPM_PCIERP8_QUESTION_ID              5608
#define PCH_ASPM_PCIERP9_QUESTION_ID              5609
#define PCH_ASPM_PCIERP10_QUESTION_ID             5610
#define PCH_ASPM_PCIERP11_QUESTION_ID             5611
#define PCH_ASPM_PCIERP12_QUESTION_ID             5612
#define PCH_ASPM_PCIERP13_QUESTION_ID             5613
#define PCH_ASPM_PCIERP14_QUESTION_ID             5614
#define PCH_ASPM_PCIERP15_QUESTION_ID             5615
#define PCH_ASPM_PCIERP16_QUESTION_ID             5616
#define PCH_ASPM_PCIERP17_QUESTION_ID             5617
#define PCH_ASPM_PCIERP18_QUESTION_ID             5618
#define PCH_ASPM_PCIERP19_QUESTION_ID             5619
#define PCH_ASPM_PCIERP20_QUESTION_ID             5620
#define PCH_ASPM_PCIERP21_QUESTION_ID             5621
#define PCH_ASPM_PCIERP22_QUESTION_ID             5622
#define PCH_ASPM_PCIERP23_QUESTION_ID             5623
#define PCH_L1SUB_PCIERP0_QUESTION_ID             5624
#define PCH_L1SUB_PCIERP1_QUESTION_ID             5625
#define PCH_L1SUB_PCIERP2_QUESTION_ID             5626
#define PCH_L1SUB_PCIERP3_QUESTION_ID             5627
#define PCH_L1SUB_PCIERP4_QUESTION_ID             5628
#define PCH_L1SUB_PCIERP5_QUESTION_ID             5629
#define PCH_L1SUB_PCIERP6_QUESTION_ID             5630
#define PCH_L1SUB_PCIERP7_QUESTION_ID             5631
#define PCH_L1SUB_PCIERP8_QUESTION_ID             5632
#define PCH_L1SUB_PCIERP9_QUESTION_ID             5633
#define PCH_L1SUB_PCIERP10_QUESTION_ID            5634
#define PCH_L1SUB_PCIERP11_QUESTION_ID            5635
#define PCH_L1SUB_PCIERP12_QUESTION_ID            5636
#define PCH_L1SUB_PCIERP13_QUESTION_ID            5637
#define PCH_L1SUB_PCIERP14_QUESTION_ID            5638
#define PCH_L1SUB_PCIERP15_QUESTION_ID            5639
#define PCH_L1SUB_PCIERP16_QUESTION_ID            5640
#define PCH_L1SUB_PCIERP17_QUESTION_ID            5641
#define PCH_L1SUB_PCIERP18_QUESTION_ID            5642
#define PCH_L1SUB_PCIERP19_QUESTION_ID            5643
#define PCH_L1SUB_PCIERP20_QUESTION_ID            5644
#define PCH_L1SUB_PCIERP21_QUESTION_ID            5645
#define PCH_L1SUB_PCIERP22_QUESTION_ID            5646
#define PCH_L1SUB_PCIERP23_QUESTION_ID            5647
#define PCH_MVCE_PCIERP0_QUESTION_ID              5648
#define PCH_MVCE_PCIERP1_QUESTION_ID              5649
#define PCH_MVCE_PCIERP2_QUESTION_ID              5650
#define PCH_MVCE_PCIERP3_QUESTION_ID              5651
#define PCH_MVCE_PCIERP4_QUESTION_ID              5652
#define PCH_MVCE_PCIERP5_QUESTION_ID              5653
#define PCH_MVCE_PCIERP6_QUESTION_ID              5654
#define PCH_MVCE_PCIERP7_QUESTION_ID              5655
#define PCH_MVCE_PCIERP8_QUESTION_ID              5656
#define PCH_MVCE_PCIERP9_QUESTION_ID              5657
#define PCH_MVCE_PCIERP10_QUESTION_ID             5658
#define PCH_MVCE_PCIERP11_QUESTION_ID             5659
#define PCH_MVCE_PCIERP12_QUESTION_ID             5660
#define PCH_MVCE_PCIERP13_QUESTION_ID             5661
#define PCH_MVCE_PCIERP14_QUESTION_ID             5662
#define PCH_MVCE_PCIERP15_QUESTION_ID             5663
#define PCH_MVCE_PCIERP16_QUESTION_ID             5664
#define PCH_MVCE_PCIERP17_QUESTION_ID             5665
#define PCH_MVCE_PCIERP18_QUESTION_ID             5666
#define PCH_MVCE_PCIERP19_QUESTION_ID             5667
#define PCH_MVCE_PCIERP20_QUESTION_ID             5668
#define PCH_MVCE_PCIERP21_QUESTION_ID             5669
#define PCH_MVCE_PCIERP22_QUESTION_ID             5670
#define PCH_MVCE_PCIERP23_QUESTION_ID             5671
#define PCH_PTM_PCIERP0_QUESTION_ID               5672
#define PCH_PTM_PCIERP1_QUESTION_ID               5673
#define PCH_PTM_PCIERP2_QUESTION_ID               5674
#define PCH_PTM_PCIERP3_QUESTION_ID               5675
#define PCH_PTM_PCIERP4_QUESTION_ID               5676
#define PCH_PTM_PCIERP5_QUESTION_ID               5677
#define PCH_PTM_PCIERP6_QUESTION_ID               5678
#define PCH_PTM_PCIERP7_QUESTION_ID               5679
#define PCH_PTM_PCIERP8_QUESTION_ID               5680
#define PCH_PTM_PCIERP9_QUESTION_ID               5681
#define PCH_PTM_PCIERP10_QUESTION_ID              5682
#define PCH_PTM_PCIERP11_QUESTION_ID              5683
#define PCH_PTM_PCIERP12_QUESTION_ID              5684
#define PCH_PTM_PCIERP13_QUESTION_ID              5685
#define PCH_PTM_PCIERP14_QUESTION_ID              5686
#define PCH_PTM_PCIERP15_QUESTION_ID              5687
#define PCH_PTM_PCIERP16_QUESTION_ID              5688
#define PCH_PTM_PCIERP17_QUESTION_ID              5689
#define PCH_PTM_PCIERP18_QUESTION_ID              5690
#define PCH_PTM_PCIERP19_QUESTION_ID              5691
#define PCH_PTM_PCIERP20_QUESTION_ID              5692
#define PCH_PTM_PCIERP21_QUESTION_ID              5693
#define PCH_PTM_PCIERP22_QUESTION_ID              5694
#define PCH_PTM_PCIERP23_QUESTION_ID              5695
// Sa Pcie
#define CPU_PCIE_LANE_EQ_FORM_ID                   5505
#define CPU_PCIERP0_OPTIONS_FORM_ID                5506
#define CPU_PCIERP1_OPTIONS_FORM_ID                5507
#define CPU_PCIERP2_OPTIONS_FORM_ID                5508
#define CPU_PCIERP3_OPTIONS_FORM_ID                5509
#define CPU_PCIE_DEVICE_OPTIONS_FORM_ID           5510
#define PCH_HDAUDIO_OPTIONS_FORM_ID               4156
#define ME_FW_FIPS_MODE_FORM_ID                   4181
#define PCH_HDAUDIO_ADVANCED_OPTIONS_FORM_ID      4159
#define PCH_HDAUDIO_FEATURES_FORM_ID              4160
#define SECURITY_OPTIONS_FORM_ID                  4157
#define ME_FORM_ID                                4158
#define ME_PTT_CONFIGURATION_FORM_ID              4161
#define ME_DEBUG_CONFIGURATION_FORM_ID            4162
#define ME_FW_UPGRADE_FORM_ID                     4163
#define ARB_SVN_CONFIGURATION_FORM_ID             4164
#define THERMAL_CONFIG_FORM_ID                    4166
#define CPU_THERMAL_CONFIG_FORM_ID                4167
#define MEMORY_THERMAL_CONFIG_FORM_ID             4168
#define PLATFORM_THERMAL_CONFIG_FORM_ID           4169
#define POLICY_FORM_ID                            4170
#define KEY_TPM_GOTO                              4171
#define TPM_CONFIG_FORM_ID                        4172
#define KEY_TPM_ENABLE                            4173
#define KEY_TPM_DISABLE                           4174
#define KEY_TPM_ACTIVATE                          4175
#define KEY_TPM_DEACTIVATE                        4176
#define KEY_TPM_FORCE_CLEAR                       4177
#define KEY_TPM_MOR_ENABLE                        4178
#define KEY_TPM_MOR_DISABLE                       4179
#define ADVANCED_DEBUG_FORM_ID                    4182
#define USB_CONFIG_FORM_ID                        4183
#define FDC_V_DATA_KEY                            4186
#define FDC_NV_DATA_KEY                           4187
#define COMA_V_DATA_KEY                           4188
#define COMA_NV_DATA_KEY                          4189
#define COMB_V_DATA_KEY                           4190
#define COMB_NV_DATA_KEY                          4191
#define LPT_V_DATA_KEY                            4192
#define LPT_NV_DATA_KEY                           4193
#define NAT_FDC_V_DATA_KEY                        4199
#define NAT_FDC_NV_DATA_KEY                       4200
#define NAT_COMA_V_DATA_KEY                       4201
#define NAT_COMA_NV_DATA_KEY                      4202
#define NAT_LPT_V_DATA_KEY                        4203
#define NAT_LPT_NV_DATA_KEY                       4204
#define NAT_SIO_FORM_ID                           4205
#define NAT_FLOPPY_FORM_ID                        4206
#define NAT_SERIAL1_FORM_ID                       4207
#define NAT_PARALLEL_FORM_ID                      4208
#define WPCN381U_FDC_V_DATA_KEY                   4209
#define WPCN381U_FDC_NV_DATA_KEY                  4210
#define WPCN381U_COMA_V_DATA_KEY                  4211
#define WPCN381U_COMA_NV_DATA_KEY                 4212
#define WPCN381U_COMB_V_DATA_KEY                  4213
#define WPCN381U_COMB_NV_DATA_KEY                 4214
#define WPCN381U_LPT_V_DATA_KEY                   4215
#define WPCN381U_LPT_NV_DATA_KEY                  4216
#define WPCN381U_SIO_FORM_ID                      4217
#define WPCN381U_FLOPPY_FORM_ID                   4218
#define WPCN381U_SIO_SERIAL0_FORM_ID              4219
#define WPCN381U_SIO_SERIAL1_FORM_ID              4220
#define WPCN381U_PARALLEL_FORM_ID                 4221
#define HHM_FORM_ID                               4222
#define INTERNAL_TEMP_KEY                         4224
#define REMOTE_TEMP_KEY                           4225
#define FAN_1_KEY                                 4226
#define FAN_2_KEY                                 4227
#define FAN_3_KEY                                 4228
#define VOLT_1_5V_KEY                             4229
#define VOLT_3_3V_KEY                             4230
#define VOLT_5V_KEY                               4231
#define VOLT_12V_KEY                              4232
#define VOLT_CORE_KEY                             4233
#define CPU_FAN_KEY                               4236
#define PCH_DTS_TEMP_KEY                          4243
#define TS_ON_DIMM0_TEMP_KEY                      4245
#define TS_ON_DIMM1_TEMP_KEY                      4246
#define HDC_CONFIG_FORM_ID                        4256
#define KEY_RatioLimit5                           4257
#define KEY_RatioLimit6                           4258
#define KEY_RatioLimit7                           4259
#define KEY_RatioLimit8                           4260

#define USB_MASS_DEV_NUM_KEY                      6000
#define USB_MASS_DEV_VALID_KEY                    6001
#define USB_CONTROLLER_NUM_KEY                    6002
#define USB_SUPPORT_KEY                           6003

// ICC-related
// NOTE: in most keys, exact value doesn't matter. However, for some ICC keys,
// BIT0 distinguishes between CLOCK2- and CLOCK3-related options
#define ICC_SETUP_DATA_VAR                        5000
#define ICC_FORM_ID                               5001
#define KEY_ICC_STRINGS                           5002
#define KEY_ICC_PROFILE                           5003
#define KEY_ICC_LOCK                              5004
#define KEY_ICC_ADV_OPTIONS                       5005
#define KEY_ICC_SHOW_PROFILE                      5006
#define KEY_ICC_SHOW_CLOCK2                       5021
#define KEY_ICC_SHOW_CLOCK3                       5031
#define KEY_ICC_SHOW_FREQ2                        5022
#define KEY_ICC_SHOW_FREQ3                        5032
#define KEY_ICC_SHOW_SPREAD2                      5023
#define KEY_ICC_SHOW_SPREAD3                      5033
#define KEY_ICC_FREQ2                             5024
#define KEY_ICC_FREQ3                             5034
#define KEY_ICC_SPREAD2                           5025
#define KEY_ICC_SPREAD3                           5035
#define KEY_ICC_RATIO2                            5026
#define KEY_ICC_RATIO3                            5036

#define DEBUG_INTERFACE_FORM_ID                   4319
#define REWORK_INFORMATION_FORM_ID                4320
#define KEY_CpuRatioLimit                         4321
#define BOOTTIME_SETUP_KEY                        4322
#define KEY_TPM_SUPPORT                           4323
#define MEM_TRAINING_FORM_ID                      4324
#define MEM_THERMMGT_FORM_ID                      4328

#define SA_TCSS_OPTIONS_FORM_ID                   4332
#define SA_DISPLAY_OPTIONS_FORM_ID                4333

#define CPU_CTDP_OPTIONS_FORM_ID                  4329
#define CPU_CTDP_CUSTOM_OPTIONS_FORM_ID           4330
#define CSM_FORM_ID                               4334
#define SATA_DEVICE_KEY                           4335

#define RTD3_FORM_ID                              4339

#define AMT_FORM_ID                               4340
#define CIRA_CONFIGURATION_FORM_ID                4341
#define ASF_CONFIGURATION_FORM_ID                 4342
#define SECURE_ERASE_FORM_ID                      4351
#define MEBX_OEM_FLAGS_FORM_ID                    4343
#define MEBX_RESOLUTION_FORM_ID                   4344

#define GEN3_RP_PRESET_FORM_ID                    4345
#define GEN3_EP_PRESET_FORM_ID                    4346
#define GEN3_EP_HINT_FORM_ID                      4347
#define DPTF_FORM_ID                              4348

#define SERIAL_IO_OPTIONS_FORM_ID                 4349
#define ISCT_FORM_ID                              4350
#define RING_CONFIG_FORM_ID                       4353
#define UNCORE_CONFIG_FORM_ID                     4354

#define GEN3_RX_CTLE_CONTROL_FORM_ID              4356
#define DRAM_POWER_METER_FORM_ID                  4357
#define MEMORY_THERMAL_REPORTING_FORM_ID          4358
#define MEMORY_RAPL_FORM_ID                       4359

#define ME_FEATURES_ID                            4360

#define KEY_TPM2_GOTO                             4362

#define SECURE_BOOT_VARIABLE_KEY                  4363

#define KEY_MEMINFO11                             4364
#define KEY_MEMINFO12                             4365
#define KEY_MEMINFO13                             4366
#define CPU_SMM_FEATURE_ID                        4367
#define CPU_SMM_CONFIG_FORM_ID                    4368
#define CPU_PL3_OPTIONS_FORM_ID                   4369
#define IGFX_IUER_FORM_ID                         4370

#define PCH_SERIAL_IO_DMA_FORM_ID                 4371
#define PCH_SERIAL_IO_I2C0_FORM_ID                4372
#define PCH_SERIAL_IO_I2C1_FORM_ID                4373
#define PCH_SERIAL_IO_SPI0_FORM_ID                4374
#define PCH_SERIAL_IO_SPI1_FORM_ID                4375
#define PCH_SERIAL_IO_UART0_FORM_ID               4376
#define PCH_SERIAL_IO_UART1_FORM_ID               4377
#define PCH_SERIAL_IO_SDIO_FORM_ID                4378
#define TBT_FORM_ID                               4379
#define KEY_RING_MAX_OC_RATIO_LIMIT               4380
#define KEY_LOW_POWER_S0_IDLE                     4381
#define TBT_COMPILE_TYPE                          1
#define TOUCH_PAD_FORM_ID                         4382
#define TOUCH_PANEL_FORM_ID                       4383
#define FINGER_PRINT_FORM_ID                      4384

#define KEY_TPM_DEVICE_SELECT                     4387
#define KEY_TCG2_CONFIGURATION                    4388 // TCG2 implementation
#define PLATFORM_SETTINGS_FORM_ID                 4389
#define DMI_GEN3_RP_PRESET_FORM_ID                4390
#define DMI_GEN3_EP_PRESET_FORM_ID                4391
#define DMI_GEN3_EP_HINT_FORM_ID                  4392
#define DMI_GEN3_RX_CTLE_CONTROL_FORM_ID          4393
#define PEP_FORM_ID                               4394
#define KEY_MEMINFO_PROFILE                       4395
#define KEY_CSM_STATE                             4396

#if FixedPcdGetBool(PcdUpServerEnable) == 1
#define MEMORY_TSOD_FORM_ID                       4417
#endif

#define GOP_FORM_ID                               5089
#define LFP_CONFIG_FORM_ID                        5090
#define DEVICE1_EFP1_FORM_ID                      5091
#define DEVICE2_EFP2_FORM_ID                      5092
#define DEVICE3_EFP3_FORM_ID                      5093
#define KEY_DTBT_SUPPORT                          5094
#define TBT_SECURITY_LEVEL_KEY                    5115
#define KEY_TBT_BOOT_ON                           5117
#define KEY_TBT_USB_ON                            5118
#define TBT_OSSELECT_FORM_ID                      5118
#define KEY_TBT_OS_SELECTOR                       5119
// MipiCam
#define MIPICAM_OPTIONS_FORM_ID                   5042
// Storage and Communication Subsystem (SCS)
#define SCS_OPTIONS_FORM_ID                       5044
// Integrated Sensor Hub (ISH)
#define ISH_OPTIONS_FORM_ID                       5046
// Programmable Service Engine (PSE)
#define PSE_OPTIONS_FORM_ID                       5043
// Programmable Service Engine TGPIO Pin Mux
#define PCH_PSE_TGPIO0_PIN_MUX_FORM_ID            5038
#define PCH_PSE_TGPIO1_PIN_MUX_FORM_ID            5039
#define PCH_PSE_PWM_PIN_MUX_FORM_ID               5451

// PCH POWERON option menu
#define PCH_PWRON_OPTIONS_FORM_ID                 5045

// PCH Thermal Throttling Options Menu
#define PCH_THERMAL_THROTTLING_OPTIONS_FORM_ID    5054

// CPU VR Config
#define CPU_VR_OPTIONS_FORM_ID                    5047
#define CPU_SA_VR_OPTIONS_FORM_ID                 5048
#define CPU_IA_VR_OPTIONS_FORM_ID                 5049
#define CPU_ACOUSTIC_NOISE_FORM_ID                5050
#define CPU_GT_VR_OPTIONS_FORM_ID                 5052
#define CPU_FIVR_VR_OPTIONS_FORM_ID               5040

#define KEY_TjMaxOffset                           5041

#define CPU_SETUP_VOLATILE_DATA_ID                5053
#define THERMAL_SENSOR_1_KEY                      5054
#define THERMAL_SENSOR_2_KEY                      5055
#define THERMAL_SENSOR_3_KEY                      5056
#define THERMAL_SENSOR_4_KEY                      5057
#define THERMAL_SENSOR_5_KEY                      5058

#define KEY_EpochChange                           5100
#define KEY_SgxEpoch1                             5099
#define KEY_SgxChange                             5068
#define KEY_MaxPrmrrSize                          5125

#define VT_QUESTION_ID                            5146

#define CPU_BIOS_GUARD_FORM_ID                    5124

#define CX_ENABLE_QUESTION_ID                     5126
#define AC_SPLIT_LOCK_QUESTION_ID                 5127
#define HWP_ENABLE_QUESTION_ID                    5128
#define ITBM_ENABLE_QUESTION_ID                   5129
#define ENABLE_GV_QUESTION_ID                     5130
#define RTD3_SUPPORT_QUESTION_ID                  5131
#define SA_GV_QUESTION_ID                         5132
#define PAGE_IDLE_TIMEOUT_QUESTION_ID             5133
#define RAPLLIM1_ENABLE_QUESTION_ID               5134
#define RAPLLIM2_ENABLE_QUESTION_ID               5135
#define POWER_DOWN_MODE_QUESTION_ID               5136
#define VIDEO_RS2_QUESTION_ID                     5137
#define SA_PM_SUPPORT_QUESTION_ID                 5138
#define SA_PCIE_CKG_QUESTION_ID                   5139
#define PCH_DMI_ASPM_QUESTION_ID                  5140
#define SA_VTD_QUESTION_ID                        5141
#define PCH_LEGACY_IO_LOW_LATENCY_QUESTION_ID     5142

// PCH FW-Configuration Menu
#define PTT_TRIGGER_FORM_OPEN_ACTION_KEY          5069
#define MNG_STATE_KEY                             5070

// Platform Information Menu
#define STM_REV_KEY                               5072

// Connectivity Options Menu
#define CONNECTIVITY_OPTIONS_FORM_ID              5074
#define KEY_CNV_BT_AUDIO_OFFLOAD                  5230

// IMR Options Menu
#define PCH_PCIE_IMR_OPTIONS_FORM_ID              5075

#define DTBT_FORM_ID                              5076
#define DTBT_CONTROLLER0_FORM_ID                  5077
#define DTBT_CONTROLLER1_FORM_ID                  5078
#define DTBT_CONTROLLER2_FORM_ID                  5079
#define KEY_DTBT_CONTROLLER0                      5080
#define KEY_DTBT_CONTROLLER1                      5081
#define KEY_DTBT_CONTROLLER2                      5082
#define KEY_DTBT_CONTROLLER3                      5083
#define TBT_SETUP_VOLATILE_DATA_ID                5084
#define KEY_DTBT_CONTROLLER0_HOSTROUTER           5085
#define KEY_DTBT_CONTROLLER1_HOSTROUTER           5086
#define KEY_DTBT_CONTROLLER2_HOSTROUTER           5087
#define KEY_DTBT_CONTROLLER3_HOSTROUTER           5088
// FIVR Configuration Menu
#define FIVR_CONFIGURATION_FORM_ID                5089
// Discrete TBT Type (PCH or PEG) Support
#define KEY_DTBT_CONTROLLER_TYPE_0                5095
#define KEY_DTBT_CONTROLLER_TYPE_1                5096
#define KEY_DTBT_CONTROLLER_TYPE_2                5097
#define KEY_DTBT_CONTROLLER_TYPE_3                5098

#define ITBT_FORM_ID                            5200
#define ITBT_ROOTPORT0_FORM_ID                  5201
#define ITBT_ROOTPORT1_FORM_ID                  5202
#define ITBT_ROOTPORT2_FORM_ID                  5203
#define ITBT_ROOTPORT3_FORM_ID                  5204
#define ITBT_ROOTPORT4_FORM_ID                  5205
#define ITBT_ROOTPORT5_FORM_ID                  5206
#define KEY_ITBT_ROOTPORT0                      5207
#define KEY_ITBT_ROOTPORT1                      5208
#define KEY_ITBT_ROOTPORT2                      5209
#define KEY_ITBT_ROOTPORT3                      5210
#define KEY_ITBT_ROOTPORT4                      5211
#define KEY_ITBT_ROOTPORT5                      5212
#define SA_VMD_OPTIONS_FORM_ID                    5220
#define SA_2LM_OPTIONS_FORM_ID                    5221
#define KEY_ITBT_SUPPORT                          5250
// RFI Option Menu
#define CPU_RFI_VR_OPTIONS_FORM_ID                5251
// For SIO NCT6776F.
#define NCT_HWMON_FORM_ID                         5400
#define NCT_HWMON_CPU_TEMP_KEY                    5401
#define NCT_HWMON_CPU_FAN_KEY                     5402
#define NCT_HWMON_SYS_TEMP_KEY                    5403
#define NCT_HWMON_SYS_FAN_KEY                     5404
#define NCT_HWMON_AUX_TEMP_KEY                    5405
#define NCT_HWMON_AUX_FAN_KEY                     5406
#define NCT_HWMON_CPU_VCORE_KEY                   5407
#define NCT_HWMON_3VCC_KEY                        5408
#define NCT_HWMON_AVCC_KEY                        5409
#define NCT_HWMON_VIN0_KEY                        5410
#define NCT_HWMON_VIN1_KEY                        5411
#define NCT_HWMON_VIN2_KEY                        5412
#define NCT_HWMON_VIN3_KEY                        5413
// End of SIO NCT6776F.

#define PLL_TRIM_CONFIG_FORM_ID                   5414
#define SYS_FW_UPDATE_CONFIG_FORM_ID              5415
#define PLATFORM_VTIO_FORM_ID                     5420

#define KEY_RING_MIN_RATIO_LIMIT                  5416
#define KEY_RING_MAX_RATIO_LIMIT                  5417
#define KEY_CORE_MAX_OC_RATIO_LIMIT               5418

#define KEY_SA_TCSS_XHCI_EN                       5419
#define KEY_SA_TCSS_ROOT_PORT_0EN                 5445
#define KEY_SA_TCSS_ROOT_PORT_1EN                 5446
#define KEY_SA_TCSS_ROOT_PORT_2EN                 5447
#define KEY_SA_TCSS_ROOT_PORT_3EN                 5448
#define PLATFORM_TCSS_FORM_ID                     5421
// THC Options Menu
#define THC_OPTIONS_FORM_ID                       5422
#define KEY_ENABLE_THERMAL_FUN                    5423
#define KEY_TBT_VTD_SECURITY_ID                   5424

#define GEN4_RP_PRESET_FORM_ID                    5425
#define GEN4_EP_PRESET_FORM_ID                    5426
#define GEN4_EP_HINT_FORM_ID                      5427

// BCLK Configuration Menu
#define KEY_BCLK_RFI_FREQ0                        5428
#define KEY_BCLK_RFI_FREQ1                        5429
#define KEY_BCLK_RFI_FREQ2                        5430
#define KEY_BCLK_RFI_FREQ3                        5431

// WiFi Connectivity Menu
#define KEY_WIFI_POWER_LIMIT                      5432

#define ITBT_PCIERP0_OPTIONS_FORM_ID              5438
#define ITBT_PCIERP1_OPTIONS_FORM_ID              5439
#define ITBT_PCIERP2_OPTIONS_FORM_ID              5440
#define ITBT_PCIERP3_OPTIONS_FORM_ID              5442

#define TCSS_SA_USB_FORM_ID                       5441

// TCC Configuration Menu
#define TCC_MODE_CONFIG_FORM_ID                   5434
#define KEY_TCC_MODE                              5456
// WWAN Options Menu
#define WWAN_OPTIONS_FORM_ID                      5435

// SDEV Options
#define KEY_SdevXhciAcpiPathNameDevice1           5436
#define KEY_SdevXhciAcpiPathNameDevice2           5437

#define CHARGING_OPTIONS_FORM_ID                  5449
#define PLATFORM_DNX_CONFIG_FORM_ID               5450

//FUSA
#define FUSA_FORM_ID                              5443
#define KEY_GLOBAL_FUSA_EN                        5444

//FIA
#define PCH_FIA_OPTIONS_FORM_ID                   5445

// TSN GBE
#define TSN_GBE_OPTIONS_FORM_ID                   5452
#define KEY_MCC_TSN_GBE_LINK_SPEED                5453
#define KEY_PSE_TSN_GBE0_LINK_SPEED               5454
#define KEY_PSE_TSN_GBE1_LINK_SPEED               5455
#define PCH_TSN_GBE_MULTI_VC_QUESTION_ID          5457
#define PSE_TSN_GBE0_MULTI_VC_QUESTION_ID         5458
#define PSE_TSN_GBE1_MULTI_VC_QUESTION_ID         5459

#ifndef AUTO_ID
#define AUTO_ID(x) x
#endif
