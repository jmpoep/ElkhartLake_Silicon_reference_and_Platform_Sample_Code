## @file
# This file is used to define class for data type structure
#
# Copyright (c) 2011 - 2018, Intel Corporation. All rights reserved.<BR>
#
# This program and the accompanying materials are licensed and made available
# under the terms and conditions of the BSD License which accompanies this
# distribution. The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

'''
DataType
'''

##
# Module List Items
#
MODULE_LIST = ["BASE",
               "SEC",
               "PEI_CORE",
               "PEIM",
               "DXE_CORE",
               "DXE_DRIVER",
               "SMM_CORE",
               "DXE_RUNTIME_DRIVER",
               "DXE_SAL_DRIVER",
               "DXE_SMM_DRIVER",
               "UEFI_DRIVER",
               "UEFI_APPLICATION",
               "USER_DEFINED"]

VALID_DEPEX_MODULE_TYPE_LIST = ["PEIM",
                                "DXE_DRIVER",
                                "DXE_SMM_DRIVER",
                                "DXE_RUNTIME_DRIVER",
                                "DXE_SAL_DRIVER",
                                "UEFI_DRIVER",
                                ]
##
# Usage List Items
#
USAGE_LIST = ["CONSUMES",
              "SOMETIMES_CONSUMES",
              "PRODUCES",
              "SOMETIMES_PRODUCES"]

TAB_LANGUAGE_EN_US = 'en-US'
TAB_LANGUAGE_ENG   = 'eng'
TAB_LANGUAGE_EN    = 'en'
TAB_LANGUAGE_EN_X  = 'en-x-tianocore'

USAGE_ITEM_PRODUCES           = 'PRODUCES'
USAGE_ITEM_SOMETIMES_PRODUCES = 'SOMETIMES_PRODUCES'
USAGE_ITEM_CONSUMES           = 'CONSUMES'
USAGE_ITEM_SOMETIMES_CONSUMES = 'SOMETIMES_CONSUMES'
USAGE_ITEM_TO_START           = 'TO_START'
USAGE_ITEM_BY_START           = 'BY_START'
USAGE_ITEM_NOTIFY             = 'NOTIFY'
USAGE_ITEM_UNDEFINED          = 'UNDEFINED'

USAGE_CONSUMES_LIST = [USAGE_ITEM_CONSUMES,
                       'CONSUMED',
                       'ALWAYS_CONSUMED',
                       'ALWAYS_CONSUMES'
                       ]

USAGE_PRODUCES_LIST = [USAGE_ITEM_PRODUCES,
                       'PRODUCED',
                       'ALWAYS_PRODUCED',
                       'ALWAYS_PRODUCES'
                       ]

USAGE_SOMETIMES_PRODUCES_LIST = [USAGE_ITEM_SOMETIMES_PRODUCES,
                                 'SOMETIMES_PRODUCED'
                                 ]

USAGE_SOMETIMES_CONSUMES_LIST = [USAGE_ITEM_SOMETIMES_CONSUMES,
                                 'SOMETIMES_CONSUMED'
                                 ]

ITEM_UNDEFINED = 'UNDEFINED'

TAB_PCD_VALIDRANGE = '@ValidRange'
TAB_PCD_VALIDLIST = '@ValidList'
TAB_PCD_EXPRESSION = '@Expression'
TAB_PCD_PROMPT = '@Prompt'
TAB_STR_TOKENCNAME = 'STR'
TAB_STR_TOKENPROMPT = 'PROMPT'
TAB_STR_TOKENHELP = 'HELP'
TAB_STR_TOKENERR = 'ERR'

#
# Dictionary of usage tokens and their synonmys
#
ALL_USAGE_TOKENS = {
  "PRODUCES"           : "PRODUCES",
  "PRODUCED"           : "PRODUCES",
  "ALWAYS_PRODUCES"    : "PRODUCES",
  "ALWAYS_PRODUCED"    : "PRODUCES",
  "SOMETIMES_PRODUCES" : "SOMETIMES_PRODUCES",
  "SOMETIMES_PRODUCED" : "SOMETIMES_PRODUCES",
  "CONSUMES"           : "CONSUMES",
  "CONSUMED"           : "CONSUMES",
  "ALWAYS_CONSUMES"    : "CONSUMES",
  "ALWAYS_CONSUMED"    : "CONSUMES",
  "SOMETIMES_CONSUMES" : "SOMETIMES_CONSUMES",
  "SOMETIMES_CONSUMED" : "SOMETIMES_CONSUMES",
  "SOMETIME_CONSUMES"  : "SOMETIMES_CONSUMES",
  "UNDEFINED"          : "UNDEFINED"
  }

PROTOCOL_USAGE_TOKENS = {
  "TO_START"           : "TO_START",
  "BY_START"           : "BY_START"
  }

PROTOCOL_USAGE_TOKENS.update (ALL_USAGE_TOKENS)

#
# Dictionary of GUID type tokens
#
GUID_TYPE_TOKENS = {
  "Event"          : "Event",
  "File"           : "File",
  "FV"             : "FV",
  "GUID"           : "GUID",
  "Guid"           : "GUID",
  "HII"            : "HII",
  "HOB"            : "HOB",
  "Hob"            : "HOB",
  "Hob:"           : "HOB",
  "SystemTable"    : "SystemTable",
  "TokenSpaceGuid" : "TokenSpaceGuid",
  "UNDEFINED"      : "UNDEFINED"
  }

#
# Dictionary of Protocol Notify tokens and their synonyms
#
PROTOCOL_NOTIFY_TOKENS = {
  "NOTIFY"          : "NOTIFY",
  "PROTOCOL_NOTIFY" : "NOTIFY",
  "UNDEFINED"       : "UNDEFINED"
  }

#
# Dictionary of PPI Notify tokens and their synonyms
#
PPI_NOTIFY_TOKENS = {
  "NOTIFY"     : "NOTIFY",
  "PPI_NOTIFY" : "NOTIFY",
  "UNDEFINED"  : "UNDEFINED"
  }

EVENT_TOKENS = {
  "EVENT_TYPE_PERIODIC_TIMER" : "EVENT_TYPE_PERIODIC_TIMER",
  "EVENT_TYPE_RELATIVE_TIMER" : "EVENT_TYPE_RELATIVE_TIMER",
  "UNDEFINED"                 : "UNDEFINED"
  }

BOOTMODE_TOKENS = {
  "FULL"                  : "FULL",
  "MINIMAL"               : "MINIMAL",
  "NO_CHANGE"             : "NO_CHANGE",
  "DIAGNOSTICS"           : "DIAGNOSTICS",
  "DEFAULT"               : "DEFAULT",
  "S2_RESUME"             : "S2_RESUME",
  "S3_RESUME"             : "S3_RESUME",
  "S4_RESUME"             : "S4_RESUME",
  "S5_RESUME"             : "S5_RESUME",
  "FLASH_UPDATE"          : "FLASH_UPDATE",
  "RECOVERY_FULL"         : "RECOVERY_FULL",
  "RECOVERY_MINIMAL"      : "RECOVERY_MINIMAL",
  "RECOVERY_NO_CHANGE"    : "RECOVERY_NO_CHANGE",
  "RECOVERY_DIAGNOSTICS"  : "RECOVERY_DIAGNOSTICS",
  "RECOVERY_DEFAULT"      : "RECOVERY_DEFAULT",
  "RECOVERY_S2_RESUME"    : "RECOVERY_S2_RESUME",
  "RECOVERY_S3_RESUME"    : "RECOVERY_S3_RESUME",
  "RECOVERY_S4_RESUME"    : "RECOVERY_S4_RESUME",
  "RECOVERY_S5_RESUME"    : "RECOVERY_S5_RESUME",
  "RECOVERY_FLASH_UPDATE" : "RECOVERY_FLASH_UPDATE",
  "UNDEFINED"             : "UNDEFINED"
  }

HOB_TOKENS = {
  "PHIT"                : "PHIT",
  "MEMORY_ALLOCATION"   : "MEMORY_ALLOCATION",
  "LOAD_PEIM"           : "LOAD_PEIM",
  "RESOURCE_DESCRIPTOR" : "RESOURCE_DESCRIPTOR",
  "FIRMWARE_VOLUME"     : "FIRMWARE_VOLUME",
  "UNDEFINED"           : "UNDEFINED"
  }

##
# Usage List Items for Protocol
#
PROTOCOL_USAGE_LIST = USAGE_LIST + ["TO_START", "BY_START"]

##
# End of Line
# Use this but not os.linesep for os.linesep has bug in it.
#
END_OF_LINE = '\n'

##
# Arch List Items
#
ARCH_LIST = ["IA32",
             "X64",
             "IPF",
             "EBC",
             "COMMON"]
##
# PCD driver type list items
#
PCD_DIRVER_TYPE_LIST = ["PEI_PCD_DRIVER", "DXE_PCD_DRIVER"]

##
# Boot Mode List Items
#
BOOT_MODE_LIST = ["FULL",
                  "MINIMAL",
                  "NO_CHANGE",
                  "DIAGNOSTICS",
                  "DEFAULT",
                  "S2_RESUME",
                  "S3_RESUME",
                  "S4_RESUME",
                  "S5_RESUME",
                  "FLASH_UPDATE",
                  "RECOVERY_FULL",
                  "RECOVERY_MINIMAL",
                  "RECOVERY_NO_CHANGE",
                  "RECOVERY_DIAGNOSTICS",
                  "RECOVERY_DEFAULT",
                  "RECOVERY_S2_RESUME",
                  "RECOVERY_S3_RESUME",
                  "RECOVERY_S4_RESUME",
                  "RECOVERY_S5_RESUME",
                  "RECOVERY_FLASH_UPDATE"]

##
# Event Type List Items
#
EVENT_TYPE_LIST = ["EVENT_TYPE_PERIODIC_TIMER",
                   "EVENT_TYPE_RELATIVE_TIMER"]

##
# Hob Type List Items
#
HOB_TYPE_LIST = ["PHIT",
                 "MEMORY_ALLOCATION",
                 "RESOURCE_DESCRIPTOR",
                 "FIRMWARE_VOLUME",
                 "LOAD_PEIM"]

##
# GUID_TYPE_LIST
#
GUID_TYPE_LIST = ["Event", "File", "FV", "GUID", "HII", "HOB",
                  "SystemTable", "TokenSpaceGuid", "Variable"]
##
# PCD Usage Type List of Package
#
PCD_USAGE_TYPE_LIST_OF_PACKAGE = ["FeatureFlag", "PatchableInModule",
                             "FixedAtBuild", "Dynamic", "DynamicEx"]

##
# PCD Usage Type List of Module
#
PCD_USAGE_TYPE_LIST_OF_MODULE = ["FEATUREPCD", "PATCHPCD", "FIXEDPCD", "PCD", "PCDEX"]
##
# PCD Usage Type List of UPT
#
PCD_USAGE_TYPE_LIST_OF_UPT = PCD_USAGE_TYPE_LIST_OF_MODULE

##
# Binary File Type List
#
BINARY_FILE_TYPE_LIST = ["PE32", "PIC", "TE", "DXE_DEPEX", "VER", "UI", "COMPAT16", "FV", "BIN", "RAW",
                         "ACPI", "ASL",
                         "PEI_DEPEX",
                         "SMM_DEPEX",
                         "SUBTYPE_GUID",
                         "DISPOSABLE"
                         ]
BINARY_FILE_TYPE_LIST_IN_UDP = \
                        ["GUID", "FREEFORM",
                         "UEFI_IMAGE", "PE32", "PIC",
                         "PEI_DEPEX",
                         "DXE_DEPEX",
                         "SMM_DEPEX",
                         "FV", "TE",
                         "BIN", "VER", "UI"
                         ]

SUBTYPE_GUID_BINARY_FILE_TYPE = "FREEFORM"
##
# Possible values for COMPONENT_TYPE, and their descriptions, are listed in
# the table,
# "Component (module) Types." For each component, the BASE_NAME and
# COMPONENT_TYPE
# are required. The COMPONENT_TYPE definition is case sensitive.
#
COMPONENT_TYPE_LIST = [
                       "APPLICATION",
                       "ACPITABLE",
                       "APRIORI",
                       "BINARY",
                       "BS_DRIVER",
                       "CONFIG",
                       "FILE",
                       "FVIMAGEFILE",
                       "LIBRARY",
                       "LOGO",
                       "LEGACY16",
                       "MICROCODE",
                       "PE32_PEIM",
                       "PEI_CORE",
                       "RAWFILE",
                       "RT_DRIVER",
                       "SAL_RT_DRIVER",
                       "SECURITY_CORE",
                       "COMBINED_PEIM_DRIVER",
                       "PIC_PEIM",
                       "RELOCATABLE_PEIM"
                       ]

##
# Common Definitions
#
TAB_SPLIT = '.'
TAB_COMMENT_EDK1_START = '/*'
TAB_COMMENT_EDK1_END = '*/'
TAB_COMMENT_EDK1_SPLIT = '//'
TAB_COMMENT_SPLIT = '#'
TAB_EQUAL_SPLIT = '='
TAB_DEQUAL_SPLIT = '=='
TAB_VALUE_SPLIT = '|'
TAB_COMMA_SPLIT = ','
TAB_HORIZON_LINE_SPLIT = '-'
TAB_SPACE_SPLIT = ' '
TAB_UNDERLINE_SPLIT = '_'
TAB_SEMI_COLON_SPLIT = ';'
TAB_COLON_SPLIT = ':'
TAB_SECTION_START = '['
TAB_SECTION_END = ']'
TAB_OPTION_START = '<'
TAB_OPTION_END  = '>'
TAB_SLASH = '\\'
TAB_BACK_SLASH = '/'
TAB_SPECIAL_COMMENT = '##'
TAB_HEADER_COMMENT = '@file'
TAB_BINARY_HEADER_COMMENT = '@BinaryHeader'
TAB_STAR = '*'
TAB_ENCODING_UTF16LE = 'utf_16_le'
TAB_CAPHEX_START = '0X'
TAB_HEX_START = '0x'
TAB_PCD_ERROR = 'Error'
TAB_PCD_ERROR_SECTION_COMMENT = 'Error message section'
TAB_UNI_FILE_SUFFIXS = ['.uni', '.UNI', '.Uni']

TAB_EDK_SOURCE = '$(EDK_SOURCE)'
TAB_EFI_SOURCE = '$(EFI_SOURCE)'
TAB_WORKSPACE = '$(WORKSPACE)'

TAB_ARCH_NULL = ''
TAB_ARCH_COMMON = 'COMMON'
TAB_ARCH_IA32 = 'IA32'
TAB_ARCH_X64 = 'X64'
TAB_ARCH_IPF = 'IPF'
TAB_ARCH_ARM = 'ARM'
TAB_ARCH_EBC = 'EBC'

ARCH_LIST = \
[TAB_ARCH_IA32, TAB_ARCH_X64, TAB_ARCH_IPF, TAB_ARCH_ARM, TAB_ARCH_EBC]

SUP_MODULE_BASE = 'BASE'
SUP_MODULE_SEC = 'SEC'
SUP_MODULE_PEI_CORE = 'PEI_CORE'
SUP_MODULE_PEIM = 'PEIM'
SUP_MODULE_DXE_CORE = 'DXE_CORE'
SUP_MODULE_DXE_DRIVER = 'DXE_DRIVER'
SUP_MODULE_DXE_RUNTIME_DRIVER = 'DXE_RUNTIME_DRIVER'
SUP_MODULE_DXE_SAL_DRIVER = 'DXE_SAL_DRIVER'
SUP_MODULE_DXE_SMM_DRIVER = 'DXE_SMM_DRIVER'
SUP_MODULE_UEFI_DRIVER = 'UEFI_DRIVER'
SUP_MODULE_UEFI_APPLICATION = 'UEFI_APPLICATION'
SUP_MODULE_USER_DEFINED = 'USER_DEFINED'
SUP_MODULE_SMM_CORE = 'SMM_CORE'

SUP_MODULE_LIST = \
[SUP_MODULE_BASE, SUP_MODULE_SEC, SUP_MODULE_PEI_CORE, SUP_MODULE_PEIM, \
SUP_MODULE_DXE_CORE, SUP_MODULE_DXE_DRIVER, \
                   SUP_MODULE_DXE_RUNTIME_DRIVER, SUP_MODULE_DXE_SAL_DRIVER, \
                   SUP_MODULE_DXE_SMM_DRIVER, SUP_MODULE_UEFI_DRIVER, \
                   SUP_MODULE_UEFI_APPLICATION, SUP_MODULE_USER_DEFINED, \
                   SUP_MODULE_SMM_CORE]
SUP_MODULE_LIST_STRING = TAB_VALUE_SPLIT.join(l for l in SUP_MODULE_LIST)

EDK_COMPONENT_TYPE_LIBRARY = 'LIBRARY'
EDK_COMPONENT_TYPE_SECUARITY_CORE = 'SECUARITY_CORE'
EDK_COMPONENT_TYPE_PEI_CORE = 'PEI_CORE'
EDK_COMPONENT_TYPE_COMBINED_PEIM_DRIVER = 'COMBINED_PEIM_DRIVER'
EDK_COMPONENT_TYPE_PIC_PEIM = 'PIC_PEIM'
EDK_COMPONENT_TYPE_RELOCATABLE_PEIM = 'RELOCATABLE_PEIM'
EDK_COMPONENT_TYPE_BS_DRIVER = 'BS_DRIVER'
EDK_COMPONENT_TYPE_RT_DRIVER = 'RT_DRIVER'
EDK_COMPONENT_TYPE_SAL_RT_DRIVER = 'SAL_RT_DRIVER'
EDK_COMPONENT_TYPE_APPLICATION = 'APPLICATION'
EDK_NAME   = 'EDK'
EDKII_NAME = 'EDKII'

BINARY_FILE_TYPE_FW = 'FW'
BINARY_FILE_TYPE_GUID = 'GUID'
BINARY_FILE_TYPE_PREEFORM = 'PREEFORM'
BINARY_FILE_TYPE_UEFI_APP = 'UEFI_APP'
BINARY_FILE_TYPE_UNI_UI = 'UNI_UI'
BINARY_FILE_TYPE_SEC_UI = 'SEC_UI'
BINARY_FILE_TYPE_UNI_VER = 'UNI_VER'
BINARY_FILE_TYPE_SEC_VER = 'SEC_VER'
BINARY_FILE_TYPE_LIB = 'LIB'
BINARY_FILE_TYPE_PE32 = 'PE32'
BINARY_FILE_TYPE_PIC = 'PIC'
BINARY_FILE_TYPE_PEI_DEPEX = 'PEI_DEPEX'
BINARY_FILE_TYPE_DXE_DEPEX = 'DXE_DEPEX'
BINARY_FILE_TYPE_SMM_DEPEX = 'SMM_DEPEX'
BINARY_FILE_TYPE_TE = 'TE'
BINARY_FILE_TYPE_VER = 'VER'
BINARY_FILE_TYPE_UI = 'UI'
BINARY_FILE_TYPE_BIN = 'BIN'
BINARY_FILE_TYPE_FV = 'FV'
BINARY_FILE_TYPE_UI_LIST = [BINARY_FILE_TYPE_UNI_UI,
                            BINARY_FILE_TYPE_SEC_UI,
                            BINARY_FILE_TYPE_UI
                            ]
BINARY_FILE_TYPE_VER_LIST = [BINARY_FILE_TYPE_UNI_VER,
                            BINARY_FILE_TYPE_SEC_VER,
                            BINARY_FILE_TYPE_VER
                            ]

DEPEX_SECTION_LIST = ['<PEI_DEPEX>',
                      '<DXE_DEPEX>',
                      '<SMM_DEPEX>'
                      ]

PLATFORM_COMPONENT_TYPE_LIBRARY = 'LIBRARY'
PLATFORM_COMPONENT_TYPE_LIBRARY_CLASS = 'LIBRARY_CLASS'
PLATFORM_COMPONENT_TYPE_MODULE = 'MODULE'

TAB_LIBRARIES = 'Libraries'

TAB_SOURCE = 'Source'
TAB_SOURCES = 'Sources'
TAB_SOURCES_COMMON = TAB_SOURCES + TAB_SPLIT + TAB_ARCH_COMMON
TAB_SOURCES_IA32 = TAB_SOURCES + TAB_SPLIT + TAB_ARCH_IA32
TAB_SOURCES_X64 = TAB_SOURCES + TAB_SPLIT + TAB_ARCH_X64
TAB_SOURCES_IPF = TAB_SOURCES + TAB_SPLIT + TAB_ARCH_IPF
TAB_SOURCES_ARM = TAB_SOURCES + TAB_SPLIT + TAB_ARCH_ARM
TAB_SOURCES_EBC = TAB_SOURCES + TAB_SPLIT + TAB_ARCH_EBC

TAB_BINARIES = 'Binaries'
TAB_BINARIES_COMMON = TAB_BINARIES + TAB_SPLIT + TAB_ARCH_COMMON
TAB_BINARIES_IA32 = TAB_BINARIES + TAB_SPLIT + TAB_ARCH_IA32
TAB_BINARIES_X64 = TAB_BINARIES + TAB_SPLIT + TAB_ARCH_X64
TAB_BINARIES_IPF = TAB_BINARIES + TAB_SPLIT + TAB_ARCH_IPF
TAB_BINARIES_ARM = TAB_BINARIES + TAB_SPLIT + TAB_ARCH_ARM
TAB_BINARIES_EBC = TAB_BINARIES + TAB_SPLIT + TAB_ARCH_EBC

TAB_INCLUDES = 'Includes'
TAB_INCLUDES_COMMON = TAB_INCLUDES + TAB_SPLIT + TAB_ARCH_COMMON
TAB_INCLUDES_IA32 = TAB_INCLUDES + TAB_SPLIT + TAB_ARCH_IA32
TAB_INCLUDES_X64 = TAB_INCLUDES + TAB_SPLIT + TAB_ARCH_X64
TAB_INCLUDES_IPF = TAB_INCLUDES + TAB_SPLIT + TAB_ARCH_IPF
TAB_INCLUDES_ARM = TAB_INCLUDES + TAB_SPLIT + TAB_ARCH_ARM
TAB_INCLUDES_EBC = TAB_INCLUDES + TAB_SPLIT + TAB_ARCH_EBC

TAB_GUIDS = 'Guids'
TAB_GUIDS_COMMON = TAB_GUIDS + TAB_SPLIT + TAB_ARCH_COMMON
TAB_GUIDS_IA32 = TAB_GUIDS + TAB_SPLIT + TAB_ARCH_IA32
TAB_GUIDS_X64 = TAB_GUIDS + TAB_SPLIT + TAB_ARCH_X64
TAB_GUIDS_IPF = TAB_GUIDS + TAB_SPLIT + TAB_ARCH_IPF
TAB_GUIDS_ARM = TAB_GUIDS + TAB_SPLIT + TAB_ARCH_ARM
TAB_GUIDS_EBC = TAB_GUIDS + TAB_SPLIT + TAB_ARCH_EBC

TAB_PROTOCOLS = 'Protocols'
TAB_PROTOCOLS_COMMON = TAB_PROTOCOLS + TAB_SPLIT + TAB_ARCH_COMMON
TAB_PROTOCOLS_IA32 = TAB_PROTOCOLS + TAB_SPLIT + TAB_ARCH_IA32
TAB_PROTOCOLS_X64 = TAB_PROTOCOLS + TAB_SPLIT + TAB_ARCH_X64
TAB_PROTOCOLS_IPF = TAB_PROTOCOLS + TAB_SPLIT + TAB_ARCH_IPF
TAB_PROTOCOLS_ARM = TAB_PROTOCOLS + TAB_SPLIT + TAB_ARCH_ARM
TAB_PROTOCOLS_EBC = TAB_PROTOCOLS + TAB_SPLIT + TAB_ARCH_EBC

TAB_PPIS = 'Ppis'
TAB_PPIS_COMMON = TAB_PPIS + TAB_SPLIT + TAB_ARCH_COMMON
TAB_PPIS_IA32 = TAB_PPIS + TAB_SPLIT + TAB_ARCH_IA32
TAB_PPIS_X64 = TAB_PPIS + TAB_SPLIT + TAB_ARCH_X64
TAB_PPIS_IPF = TAB_PPIS + TAB_SPLIT + TAB_ARCH_IPF
TAB_PPIS_ARM = TAB_PPIS + TAB_SPLIT + TAB_ARCH_ARM
TAB_PPIS_EBC = TAB_PPIS + TAB_SPLIT + TAB_ARCH_EBC

TAB_LIBRARY_CLASSES = 'LibraryClasses'
TAB_LIBRARY_CLASSES_COMMON = TAB_LIBRARY_CLASSES + TAB_SPLIT + TAB_ARCH_COMMON
TAB_LIBRARY_CLASSES_IA32 = TAB_LIBRARY_CLASSES + TAB_SPLIT + TAB_ARCH_IA32
TAB_LIBRARY_CLASSES_X64 = TAB_LIBRARY_CLASSES + TAB_SPLIT + TAB_ARCH_X64
TAB_LIBRARY_CLASSES_IPF = TAB_LIBRARY_CLASSES + TAB_SPLIT + TAB_ARCH_IPF
TAB_LIBRARY_CLASSES_ARM = TAB_LIBRARY_CLASSES + TAB_SPLIT + TAB_ARCH_ARM
TAB_LIBRARY_CLASSES_EBC = TAB_LIBRARY_CLASSES + TAB_SPLIT + TAB_ARCH_EBC

TAB_PACKAGES = 'Packages'
TAB_PACKAGES_COMMON = TAB_PACKAGES + TAB_SPLIT + TAB_ARCH_COMMON
TAB_PACKAGES_IA32 = TAB_PACKAGES + TAB_SPLIT + TAB_ARCH_IA32
TAB_PACKAGES_X64 = TAB_PACKAGES + TAB_SPLIT + TAB_ARCH_X64
TAB_PACKAGES_IPF = TAB_PACKAGES + TAB_SPLIT + TAB_ARCH_IPF
TAB_PACKAGES_ARM = TAB_PACKAGES + TAB_SPLIT + TAB_ARCH_ARM
TAB_PACKAGES_EBC = TAB_PACKAGES + TAB_SPLIT + TAB_ARCH_EBC

TAB_PCDS = 'Pcds'
TAB_PCDS_FIXED_AT_BUILD = 'FixedAtBuild'
TAB_PCDS_PATCHABLE_IN_MODULE = 'PatchableInModule'
TAB_PCDS_FEATURE_FLAG = 'FeatureFlag'
TAB_PCDS_DYNAMIC_EX = 'DynamicEx'
TAB_PCDS_DYNAMIC_EX_DEFAULT = 'DynamicExDefault'
TAB_PCDS_DYNAMIC_EX_VPD = 'DynamicExVpd'
TAB_PCDS_DYNAMIC_EX_HII = 'DynamicExHii'
TAB_PCDS_DYNAMIC = 'Dynamic'
TAB_PCDS_DYNAMIC_DEFAULT = 'DynamicDefault'
TAB_PCDS_DYNAMIC_VPD = 'DynamicVpd'
TAB_PCDS_DYNAMIC_HII = 'DynamicHii'

TAB_PTR_TYPE_PCD = 'VOID*'

PCD_DYNAMIC_TYPE_LIST = [TAB_PCDS_DYNAMIC, TAB_PCDS_DYNAMIC_DEFAULT, \
                         TAB_PCDS_DYNAMIC_VPD, TAB_PCDS_DYNAMIC_HII]
PCD_DYNAMIC_EX_TYPE_LIST = [TAB_PCDS_DYNAMIC_EX, TAB_PCDS_DYNAMIC_EX_DEFAULT, \
                            TAB_PCDS_DYNAMIC_EX_VPD, TAB_PCDS_DYNAMIC_EX_HII]

## Dynamic-ex PCD types
#
gDYNAMIC_EX_PCD = [TAB_PCDS_DYNAMIC_EX, TAB_PCDS_DYNAMIC_EX_DEFAULT, \
                 TAB_PCDS_DYNAMIC_EX_VPD, TAB_PCDS_DYNAMIC_EX_HII]

TAB_PCDS_FIXED_AT_BUILD_NULL = TAB_PCDS + TAB_PCDS_FIXED_AT_BUILD
TAB_PCDS_FIXED_AT_BUILD_COMMON = TAB_PCDS + TAB_PCDS_FIXED_AT_BUILD + \
TAB_SPLIT + TAB_ARCH_COMMON
TAB_PCDS_FIXED_AT_BUILD_IA32 = TAB_PCDS + TAB_PCDS_FIXED_AT_BUILD + \
TAB_SPLIT + TAB_ARCH_IA32
TAB_PCDS_FIXED_AT_BUILD_X64 = TAB_PCDS + TAB_PCDS_FIXED_AT_BUILD + \
TAB_SPLIT + TAB_ARCH_X64
TAB_PCDS_FIXED_AT_BUILD_IPF = TAB_PCDS + TAB_PCDS_FIXED_AT_BUILD + \
TAB_SPLIT + TAB_ARCH_IPF
TAB_PCDS_FIXED_AT_BUILD_ARM = TAB_PCDS + TAB_PCDS_FIXED_AT_BUILD + \
TAB_SPLIT + TAB_ARCH_ARM
TAB_PCDS_FIXED_AT_BUILD_EBC = TAB_PCDS + TAB_PCDS_FIXED_AT_BUILD + \
TAB_SPLIT + TAB_ARCH_EBC

TAB_PCDS_PATCHABLE_IN_MODULE_NULL = TAB_PCDS + TAB_PCDS_PATCHABLE_IN_MODULE
TAB_PCDS_PATCHABLE_IN_MODULE_COMMON = TAB_PCDS + TAB_PCDS_PATCHABLE_IN_MODULE \
+ TAB_SPLIT + TAB_ARCH_COMMON
TAB_PCDS_PATCHABLE_IN_MODULE_IA32 = TAB_PCDS + TAB_PCDS_PATCHABLE_IN_MODULE + \
TAB_SPLIT + TAB_ARCH_IA32
TAB_PCDS_PATCHABLE_IN_MODULE_X64 = TAB_PCDS + TAB_PCDS_PATCHABLE_IN_MODULE + \
TAB_SPLIT + TAB_ARCH_X64
TAB_PCDS_PATCHABLE_IN_MODULE_IPF = TAB_PCDS + TAB_PCDS_PATCHABLE_IN_MODULE + \
TAB_SPLIT + TAB_ARCH_IPF
TAB_PCDS_PATCHABLE_IN_MODULE_ARM = TAB_PCDS + TAB_PCDS_PATCHABLE_IN_MODULE + \
TAB_SPLIT + TAB_ARCH_ARM
TAB_PCDS_PATCHABLE_IN_MODULE_EBC = TAB_PCDS + TAB_PCDS_PATCHABLE_IN_MODULE + \
TAB_SPLIT + TAB_ARCH_EBC

TAB_PCDS_FEATURE_FLAG_NULL = TAB_PCDS + TAB_PCDS_FEATURE_FLAG
TAB_PCDS_FEATURE_FLAG_COMMON = TAB_PCDS + TAB_PCDS_FEATURE_FLAG + TAB_SPLIT \
+ TAB_ARCH_COMMON
TAB_PCDS_FEATURE_FLAG_IA32 = TAB_PCDS + TAB_PCDS_FEATURE_FLAG + TAB_SPLIT + \
TAB_ARCH_IA32
TAB_PCDS_FEATURE_FLAG_X64 = TAB_PCDS + TAB_PCDS_FEATURE_FLAG + TAB_SPLIT + \
TAB_ARCH_X64
TAB_PCDS_FEATURE_FLAG_IPF = TAB_PCDS + TAB_PCDS_FEATURE_FLAG + TAB_SPLIT + \
TAB_ARCH_IPF
TAB_PCDS_FEATURE_FLAG_ARM = TAB_PCDS + TAB_PCDS_FEATURE_FLAG + TAB_SPLIT + \
TAB_ARCH_ARM
TAB_PCDS_FEATURE_FLAG_EBC = TAB_PCDS + TAB_PCDS_FEATURE_FLAG + TAB_SPLIT + \
TAB_ARCH_EBC

TAB_PCDS_DYNAMIC_EX_NULL = TAB_PCDS + TAB_PCDS_DYNAMIC_EX
TAB_PCDS_DYNAMIC_EX_DEFAULT_NULL = TAB_PCDS + TAB_PCDS_DYNAMIC_EX_DEFAULT
TAB_PCDS_DYNAMIC_EX_HII_NULL = TAB_PCDS + TAB_PCDS_DYNAMIC_EX_HII
TAB_PCDS_DYNAMIC_EX_VPD_NULL = TAB_PCDS + TAB_PCDS_DYNAMIC_EX_VPD
TAB_PCDS_DYNAMIC_EX_COMMON = TAB_PCDS + TAB_PCDS_DYNAMIC_EX + TAB_SPLIT + \
TAB_ARCH_COMMON
TAB_PCDS_DYNAMIC_EX_IA32 = TAB_PCDS + TAB_PCDS_DYNAMIC_EX + TAB_SPLIT + \
TAB_ARCH_IA32
TAB_PCDS_DYNAMIC_EX_X64 = TAB_PCDS + TAB_PCDS_DYNAMIC_EX + TAB_SPLIT + \
TAB_ARCH_X64
TAB_PCDS_DYNAMIC_EX_IPF = TAB_PCDS + TAB_PCDS_DYNAMIC_EX + TAB_SPLIT + \
TAB_ARCH_IPF
TAB_PCDS_DYNAMIC_EX_ARM = TAB_PCDS + TAB_PCDS_DYNAMIC_EX + TAB_SPLIT + \
TAB_ARCH_ARM
TAB_PCDS_DYNAMIC_EX_EBC = TAB_PCDS + TAB_PCDS_DYNAMIC_EX + TAB_SPLIT + \
TAB_ARCH_EBC

TAB_PCDS_DYNAMIC_NULL = TAB_PCDS + TAB_PCDS_DYNAMIC
TAB_PCDS_DYNAMIC_DEFAULT_NULL = TAB_PCDS + TAB_PCDS_DYNAMIC_DEFAULT
TAB_PCDS_DYNAMIC_HII_NULL = TAB_PCDS + TAB_PCDS_DYNAMIC_HII
TAB_PCDS_DYNAMIC_VPD_NULL = TAB_PCDS + TAB_PCDS_DYNAMIC_VPD
TAB_PCDS_DYNAMIC_COMMON = TAB_PCDS + TAB_PCDS_DYNAMIC + TAB_SPLIT + \
TAB_ARCH_COMMON
TAB_PCDS_DYNAMIC_IA32 = TAB_PCDS + TAB_PCDS_DYNAMIC + TAB_SPLIT + TAB_ARCH_IA32
TAB_PCDS_DYNAMIC_X64 = TAB_PCDS + TAB_PCDS_DYNAMIC + TAB_SPLIT + TAB_ARCH_X64
TAB_PCDS_DYNAMIC_IPF = TAB_PCDS + TAB_PCDS_DYNAMIC + TAB_SPLIT + TAB_ARCH_IPF
TAB_PCDS_DYNAMIC_ARM = TAB_PCDS + TAB_PCDS_DYNAMIC + TAB_SPLIT + TAB_ARCH_ARM
TAB_PCDS_DYNAMIC_EBC = TAB_PCDS + TAB_PCDS_DYNAMIC + TAB_SPLIT + TAB_ARCH_EBC

TAB_PCD_DYNAMIC_TYPE_LIST = [TAB_PCDS_DYNAMIC_DEFAULT_NULL, \
                             TAB_PCDS_DYNAMIC_VPD_NULL, \
                             TAB_PCDS_DYNAMIC_HII_NULL]
TAB_PCD_DYNAMIC_EX_TYPE_LIST = [TAB_PCDS_DYNAMIC_EX_DEFAULT_NULL, \
                                TAB_PCDS_DYNAMIC_EX_VPD_NULL, \
                                TAB_PCDS_DYNAMIC_EX_HII_NULL]

TAB_PCDS_PATCHABLE_LOAD_FIX_ADDRESS_PEI_PAGE_SIZE = \
'PcdLoadFixAddressPeiCodePageNumber'
TAB_PCDS_PATCHABLE_LOAD_FIX_ADDRESS_PEI_PAGE_SIZE_DATA_TYPE = 'UINT32'
TAB_PCDS_PATCHABLE_LOAD_FIX_ADDRESS_DXE_PAGE_SIZE = \
'PcdLoadFixAddressBootTimeCodePageNumber'
TAB_PCDS_PATCHABLE_LOAD_FIX_ADDRESS_DXE_PAGE_SIZE_DATA_TYPE = 'UINT32'
TAB_PCDS_PATCHABLE_LOAD_FIX_ADDRESS_RUNTIME_PAGE_SIZE = \
'PcdLoadFixAddressRuntimeCodePageNumber'
TAB_PCDS_PATCHABLE_LOAD_FIX_ADDRESS_RUNTIME_PAGE_SIZE_DATA_TYPE = 'UINT32'
TAB_PCDS_PATCHABLE_LOAD_FIX_ADDRESS_SMM_PAGE_SIZE = \
'PcdLoadFixAddressSmmCodePageNumber'
TAB_PCDS_PATCHABLE_LOAD_FIX_ADDRESS_SMM_PAGE_SIZE_DATA_TYPE = 'UINT32'
TAB_PCDS_PATCHABLE_LOAD_FIX_ADDRESS_LIST = \
[TAB_PCDS_PATCHABLE_LOAD_FIX_ADDRESS_PEI_PAGE_SIZE, \
TAB_PCDS_PATCHABLE_LOAD_FIX_ADDRESS_DXE_PAGE_SIZE, \
TAB_PCDS_PATCHABLE_LOAD_FIX_ADDRESS_RUNTIME_PAGE_SIZE, \
TAB_PCDS_PATCHABLE_LOAD_FIX_ADDRESS_SMM_PAGE_SIZE]
PCD_SECTION_LIST = [TAB_PCDS_FIXED_AT_BUILD_NULL.upper(), \
                    TAB_PCDS_PATCHABLE_IN_MODULE_NULL.upper(), \
                    TAB_PCDS_FEATURE_FLAG_NULL.upper(), \
                    TAB_PCDS_DYNAMIC_EX_NULL.upper(), \
                    TAB_PCDS_DYNAMIC_NULL.upper()]
INF_PCD_SECTION_LIST = ["FixedPcd".upper(), "FeaturePcd".upper(), \
                        "PatchPcd".upper(), "Pcd".upper(), "PcdEx".upper()]

TAB_DEPEX = 'Depex'
TAB_DEPEX_COMMON = TAB_DEPEX + TAB_SPLIT + TAB_ARCH_COMMON
TAB_DEPEX_IA32 = TAB_DEPEX + TAB_SPLIT + TAB_ARCH_IA32
TAB_DEPEX_X64 = TAB_DEPEX + TAB_SPLIT + TAB_ARCH_X64
TAB_DEPEX_IPF = TAB_DEPEX + TAB_SPLIT + TAB_ARCH_IPF
TAB_DEPEX_ARM = TAB_DEPEX + TAB_SPLIT + TAB_ARCH_ARM
TAB_DEPEX_EBC = TAB_DEPEX + TAB_SPLIT + TAB_ARCH_EBC

TAB_SKUIDS = 'SkuIds'

TAB_LIBRARIES = 'Libraries'
TAB_LIBRARIES_COMMON = TAB_LIBRARIES + TAB_SPLIT + TAB_ARCH_COMMON
TAB_LIBRARIES_IA32 = TAB_LIBRARIES + TAB_SPLIT + TAB_ARCH_IA32
TAB_LIBRARIES_X64 = TAB_LIBRARIES + TAB_SPLIT + TAB_ARCH_X64
TAB_LIBRARIES_IPF = TAB_LIBRARIES + TAB_SPLIT + TAB_ARCH_IPF
TAB_LIBRARIES_ARM = TAB_LIBRARIES + TAB_SPLIT + TAB_ARCH_ARM
TAB_LIBRARIES_EBC = TAB_LIBRARIES + TAB_SPLIT + TAB_ARCH_EBC

TAB_COMPONENTS = 'Components'
TAB_COMPONENTS_COMMON = TAB_COMPONENTS + TAB_SPLIT + TAB_ARCH_COMMON
TAB_COMPONENTS_IA32 = TAB_COMPONENTS + TAB_SPLIT + TAB_ARCH_IA32
TAB_COMPONENTS_X64 = TAB_COMPONENTS + TAB_SPLIT + TAB_ARCH_X64
TAB_COMPONENTS_IPF = TAB_COMPONENTS + TAB_SPLIT + TAB_ARCH_IPF
TAB_COMPONENTS_ARM = TAB_COMPONENTS + TAB_SPLIT + TAB_ARCH_ARM
TAB_COMPONENTS_EBC = TAB_COMPONENTS + TAB_SPLIT + TAB_ARCH_EBC

TAB_COMPONENTS_SOURCE_OVERRIDE_PATH = 'SOURCE_OVERRIDE_PATH'

TAB_BUILD_OPTIONS = 'BuildOptions'

TAB_DEFINE = 'DEFINE'
TAB_NMAKE = 'Nmake'
TAB_USER_EXTENSIONS = 'UserExtensions'
TAB_INCLUDE = '!include'
TAB_PRIVATE = 'Private'
TAB_INTEL = 'Intel'

#
# Common Define
#
TAB_COMMON_DEFINES = 'Defines'

#
# Inf Definitions
#
TAB_INF_DEFINES = TAB_COMMON_DEFINES
TAB_INF_DEFINES_INF_VERSION = 'INF_VERSION'
TAB_INF_DEFINES_BASE_NAME = 'BASE_NAME'
TAB_INF_DEFINES_FILE_GUID = 'FILE_GUID'
TAB_INF_DEFINES_MODULE_TYPE = 'MODULE_TYPE'
TAB_INF_DEFINES_EFI_SPECIFICATION_VERSION = 'EFI_SPECIFICATION_VERSION'
TAB_INF_DEFINES_UEFI_SPECIFICATION_VERSION = 'UEFI_SPECIFICATION_VERSION'
TAB_INF_DEFINES_PI_SPECIFICATION_VERSION = 'PI_SPECIFICATION_VERSION'
TAB_INF_DEFINES_EDK_RELEASE_VERSION = 'EDK_RELEASE_VERSION'
TAB_INF_DEFINES_MODULE_UNI_FILE    = 'MODULE_UNI_FILE'
TAB_INF_DEFINES_BINARY_MODULE = 'BINARY_MODULE'
TAB_INF_DEFINES_LIBRARY_CLASS = 'LIBRARY_CLASS'
TAB_INF_DEFINES_COMPONENT_TYPE = 'COMPONENT_TYPE'
TAB_INF_DEFINES_MAKEFILE_NAME = 'MAKEFILE_NAME'
TAB_INF_DEFINES_BUILD_NUMBER = 'BUILD_NUMBER'
TAB_INF_DEFINES_BUILD_TYPE = 'BUILD_TYPE'
TAB_INF_DEFINES_FFS_EXT = 'FFS_EXT'
TAB_INF_DEFINES_FV_EXT = 'FV_EXT'
TAB_INF_DEFINES_SOURCE_FV = 'SOURCE_FV'
TAB_INF_DEFINES_PACKAGE   = 'PACKAGE'
TAB_INF_DEFINES_VERSION_NUMBER = 'VERSION_NUMBER'
TAB_INF_DEFINES_VERSION = 'VERSION'
TAB_INF_DEFINES_VERSION_STRING = 'VERSION_STRING'
TAB_INF_DEFINES_PCD_IS_DRIVER = 'PCD_IS_DRIVER'
TAB_INF_DEFINES_TIANO_EDK1_FLASHMAP_H = 'TIANO_EDK1_FLASHMAP_H'
TAB_INF_DEFINES_ENTRY_POINT = 'ENTRY_POINT'
TAB_INF_DEFINES_UNLOAD_IMAGE = 'UNLOAD_IMAGE'
TAB_INF_DEFINES_CONSTRUCTOR = 'CONSTRUCTOR'
TAB_INF_DEFINES_DESTRUCTOR = 'DESTRUCTOR'
TAB_INF_DEFINES_PCI_VENDOR_ID  = 'PCI_VENDOR_ID'
TAB_INF_DEFINES_PCI_DEVICE_ID  = 'PCI_DEVICE_ID'
TAB_INF_DEFINES_PCI_CLASS_CODE = 'PCI_CLASS_CODE'
TAB_INF_DEFINES_PCI_REVISION   = 'PCI_REVISION'
TAB_INF_DEFINES_PCI_COMPRESS   = 'PCI_COMPRESS'
TAB_INF_DEFINES_DEFINE = 'DEFINE'
TAB_INF_DEFINES_SPEC = 'SPEC'
TAB_INF_DEFINES_UEFI_HII_RESOURCE_SECTION = 'UEFI_HII_RESOURCE_SECTION'
TAB_INF_DEFINES_CUSTOM_MAKEFILE = 'CUSTOM_MAKEFILE'
TAB_INF_DEFINES_MACRO = '__MACROS__'
TAB_INF_DEFINES_SHADOW = 'SHADOW'
TAB_INF_DEFINES_DPX_SOURCE = 'DPX_SOURCE'
TAB_INF_FIXED_PCD = 'FixedPcd'
TAB_INF_FEATURE_PCD = 'FeaturePcd'
TAB_INF_PATCH_PCD = 'PatchPcd'
TAB_INF_PCD = 'Pcd'
TAB_INF_PCD_EX = 'PcdEx'
TAB_INF_GUIDTYPE_VAR = 'Variable'
TAB_INF_ABSTRACT = 'STR_MODULE_ABSTRACT'
TAB_INF_DESCRIPTION = 'STR_MODULE_DESCRIPTION'
TAB_INF_LICENSE = 'STR_MODULE_LICENSE'
TAB_INF_BINARY_ABSTRACT = 'STR_MODULE_BINARY_ABSTRACT'
TAB_INF_BINARY_DESCRIPTION = 'STR_MODULE_BINARY_DESCRIPTION'
TAB_INF_BINARY_LICENSE = 'STR_MODULE_BINARY_LICENSE'
#
# Dec Definitions
#
TAB_DEC_DEFINES = TAB_COMMON_DEFINES
TAB_DEC_DEFINES_DEC_SPECIFICATION = 'DEC_SPECIFICATION'
TAB_DEC_DEFINES_PACKAGE_NAME = 'PACKAGE_NAME'
TAB_DEC_DEFINES_PACKAGE_GUID = 'PACKAGE_GUID'
TAB_DEC_DEFINES_PACKAGE_VERSION = 'PACKAGE_VERSION'
TAB_DEC_DEFINES_PKG_UNI_FILE    = 'PACKAGE_UNI_FILE'
TAB_DEC_PACKAGE_ABSTRACT = 'STR_PACKAGE_ABSTRACT'
TAB_DEC_PACKAGE_DESCRIPTION = 'STR_PACKAGE_DESCRIPTION'
TAB_DEC_PACKAGE_LICENSE = 'STR_PACKAGE_LICENSE'
TAB_DEC_BINARY_ABSTRACT = 'STR_PACKAGE_BINARY_ABSTRACT'
TAB_DEC_BINARY_DESCRIPTION = 'STR_PACKAGE_BINARY_DESCRIPTION'
TAB_DEC_BINARY_LICENSE = 'STR_PACKAGE_ASBUILT_LICENSE'
#
# Dsc Definitions
#
TAB_DSC_DEFINES = TAB_COMMON_DEFINES
TAB_DSC_DEFINES_PLATFORM_NAME = 'PLATFORM_NAME'
TAB_DSC_DEFINES_PLATFORM_GUID = 'PLATFORM_GUID'
TAB_DSC_DEFINES_PLATFORM_VERSION = 'PLATFORM_VERSION'
TAB_DSC_DEFINES_DSC_SPECIFICATION = 'DSC_SPECIFICATION'
TAB_DSC_DEFINES_OUTPUT_DIRECTORY = 'OUTPUT_DIRECTORY'
TAB_DSC_DEFINES_SUPPORTED_ARCHITECTURES = 'SUPPORTED_ARCHITECTURES'
TAB_DSC_DEFINES_BUILD_TARGETS = 'BUILD_TARGETS'
TAB_DSC_DEFINES_SKUID_IDENTIFIER = 'SKUID_IDENTIFIER'
TAB_DSC_DEFINES_FLASH_DEFINITION = 'FLASH_DEFINITION'
TAB_DSC_DEFINES_BUILD_NUMBER = 'BUILD_NUMBER'
TAB_DSC_DEFINES_MAKEFILE_NAME = 'MAKEFILE_NAME'
TAB_DSC_DEFINES_BS_BASE_ADDRESS = 'BsBaseAddress'
TAB_DSC_DEFINES_RT_BASE_ADDRESS = 'RtBaseAddress'
TAB_DSC_DEFINES_DEFINE = 'DEFINE'
TAB_FIX_LOAD_TOP_MEMORY_ADDRESS = 'FIX_LOAD_TOP_MEMORY_ADDRESS'

#
# TargetTxt Definitions
#
TAB_TAT_DEFINES_ACTIVE_PLATFORM = 'ACTIVE_PLATFORM'
TAB_TAT_DEFINES_ACTIVE_MODULE = 'ACTIVE_MODULE'
TAB_TAT_DEFINES_TOOL_CHAIN_CONF = 'TOOL_CHAIN_CONF'
TAB_TAT_DEFINES_MULTIPLE_THREAD = 'MULTIPLE_THREAD'
TAB_TAT_DEFINES_MAX_CONCURRENT_THREAD_NUMBER = 'MAX_CONCURRENT_THREAD_NUMBER'
TAB_TAT_DEFINES_TARGET = 'TARGET'
TAB_TAT_DEFINES_TOOL_CHAIN_TAG = 'TOOL_CHAIN_TAG'
TAB_TAT_DEFINES_TARGET_ARCH = 'TARGET_ARCH'
TAB_TAT_DEFINES_BUILD_RULE_CONF = "BUILD_RULE_CONF"

#
# ToolDef Definitions
#
TAB_TOD_DEFINES_TARGET = 'TARGET'
TAB_TOD_DEFINES_TOOL_CHAIN_TAG = 'TOOL_CHAIN_TAG'
TAB_TOD_DEFINES_TARGET_ARCH = 'TARGET_ARCH'
TAB_TOD_DEFINES_COMMAND_TYPE = 'COMMAND_TYPE'
TAB_TOD_DEFINES_FAMILY = 'FAMILY'
TAB_TOD_DEFINES_BUILDRULEFAMILY = 'BUILDRULEFAMILY'

#
# Conditional Statements
#
TAB_IF = '!if'
TAB_END_IF = '!endif'
TAB_ELSE_IF = '!elseif'
TAB_ELSE = '!else'
TAB_IF_DEF = '!ifdef'
TAB_IF_N_DEF = '!ifndef'
TAB_IF_EXIST = '!if exist'

#
# Unknown section
#
TAB_UNKNOWN = 'UNKNOWN'

#
# Header section (virtual section for abstract, description, copyright,
# license)
#
TAB_HEADER = 'Header'
TAB_HEADER_ABSTRACT = 'Abstract'
TAB_HEADER_DESCRIPTION = 'Description'
TAB_HEADER_COPYRIGHT = 'Copyright'
TAB_HEADER_LICENSE = 'License'
TAB_BINARY_HEADER_IDENTIFIER = 'BinaryHeader'
TAB_BINARY_HEADER_USERID = 'TianoCore'

#
# Build database path
#
DATABASE_PATH = ":memory:"
#
# used by ECC
#
MODIFIER_LIST = ['IN', 'OUT', 'OPTIONAL', 'UNALIGNED', 'EFI_RUNTIMESERVICE', \
                 'EFI_BOOTSERVICE', 'EFIAPI']
#
# Dependency Expression
#
DEPEX_SUPPORTED_OPCODE = ["BEFORE", "AFTER", "PUSH", "AND", "OR", "NOT", \
                          "END", "SOR", "TRUE", "FALSE", '(', ')']

TAB_STATIC_LIBRARY = "STATIC-LIBRARY-FILE"
TAB_DYNAMIC_LIBRARY = "DYNAMIC-LIBRARY-FILE"
TAB_FRAMEWORK_IMAGE = "EFI-IMAGE-FILE"
TAB_C_CODE_FILE = "C-CODE-FILE"
TAB_C_HEADER_FILE = "C-HEADER-FILE"
TAB_UNICODE_FILE = "UNICODE-TEXT-FILE"
TAB_DEPENDENCY_EXPRESSION_FILE = "DEPENDENCY-EXPRESSION-FILE"
TAB_UNKNOWN_FILE = "UNKNOWN-TYPE-FILE"
TAB_DEFAULT_BINARY_FILE = "_BINARY_FILE_"
#
# used to indicate the state of processing header comment section of dec,
# inf files
#
HEADER_COMMENT_NOT_STARTED = -1
HEADER_COMMENT_STARTED     = 0
HEADER_COMMENT_FILE        = 1
HEADER_COMMENT_ABSTRACT    = 2
HEADER_COMMENT_DESCRIPTION = 3
HEADER_COMMENT_COPYRIGHT   = 4
HEADER_COMMENT_LICENSE     = 5
HEADER_COMMENT_END         = 6

#
# Static values for data models
#
MODEL_UNKNOWN = 0

MODEL_FILE_C = 1001
MODEL_FILE_H = 1002
MODEL_FILE_ASM = 1003
MODEL_FILE_INF = 1011
MODEL_FILE_DEC = 1012
MODEL_FILE_DSC = 1013
MODEL_FILE_FDF = 1014
MODEL_FILE_INC = 1015
MODEL_FILE_CIF = 1016

MODEL_IDENTIFIER_FILE_HEADER = 2001
MODEL_IDENTIFIER_FUNCTION_HEADER = 2002
MODEL_IDENTIFIER_COMMENT = 2003
MODEL_IDENTIFIER_PARAMETER = 2004
MODEL_IDENTIFIER_STRUCTURE = 2005
MODEL_IDENTIFIER_VARIABLE = 2006
MODEL_IDENTIFIER_INCLUDE = 2007
MODEL_IDENTIFIER_PREDICATE_EXPRESSION = 2008
MODEL_IDENTIFIER_ENUMERATE = 2009
MODEL_IDENTIFIER_PCD = 2010
MODEL_IDENTIFIER_UNION = 2011
MODEL_IDENTIFIER_MACRO_IFDEF = 2012
MODEL_IDENTIFIER_MACRO_IFNDEF = 2013
MODEL_IDENTIFIER_MACRO_DEFINE = 2014
MODEL_IDENTIFIER_MACRO_ENDIF = 2015
MODEL_IDENTIFIER_MACRO_PROGMA = 2016
MODEL_IDENTIFIER_FUNCTION_CALLING = 2018
MODEL_IDENTIFIER_TYPEDEF = 2017
MODEL_IDENTIFIER_FUNCTION_DECLARATION = 2019
MODEL_IDENTIFIER_ASSIGNMENT_EXPRESSION = 2020

MODEL_EFI_PROTOCOL = 3001
MODEL_EFI_PPI = 3002
MODEL_EFI_GUID = 3003
MODEL_EFI_LIBRARY_CLASS = 3004
MODEL_EFI_LIBRARY_INSTANCE = 3005
MODEL_EFI_PCD = 3006
MODEL_EFI_SOURCE_FILE = 3007
MODEL_EFI_BINARY_FILE = 3008
MODEL_EFI_SKU_ID = 3009
MODEL_EFI_INCLUDE = 3010
MODEL_EFI_DEPEX = 3011

MODEL_PCD = 4000
MODEL_PCD_FIXED_AT_BUILD = 4001
MODEL_PCD_PATCHABLE_IN_MODULE = 4002
MODEL_PCD_FEATURE_FLAG = 4003
MODEL_PCD_DYNAMIC_EX = 4004
MODEL_PCD_DYNAMIC_EX_DEFAULT = 4005
MODEL_PCD_DYNAMIC_EX_VPD = 4006
MODEL_PCD_DYNAMIC_EX_HII = 4007
MODEL_PCD_DYNAMIC = 4008
MODEL_PCD_DYNAMIC_DEFAULT = 4009
MODEL_PCD_DYNAMIC_VPD = 4010
MODEL_PCD_DYNAMIC_HII = 4011

MODEL_META_DATA_FILE_HEADER = 5000
MODEL_META_DATA_HEADER = 5001
MODEL_META_DATA_INCLUDE = 5002
MODEL_META_DATA_DEFINE = 5003
MODEL_META_DATA_CONDITIONAL_STATEMENT_IF = 5004
MODEL_META_DATA_CONDITIONAL_STATEMENT_ELSE = 5005
MODEL_META_DATA_CONDITIONAL_STATEMENT_IFDEF = 5006
MODEL_META_DATA_CONDITIONAL_STATEMENT_IFNDEF = 5007
MODEL_META_DATA_BUILD_OPTION = 5008
MODEL_META_DATA_COMPONENT = 5009
MODEL_META_DATA_USER_EXTENSION = 5010
MODEL_META_DATA_PACKAGE = 5011
MODEL_META_DATA_NMAKE = 5012
MODEL_META_DATA_CONDITIONAL_STATEMENT_ELSEIF = 50013
MODEL_META_DATA_CONDITIONAL_STATEMENT_ENDIF = 5014
MODEL_META_DATA_COMPONENT_SOURCE_OVERRIDE_PATH = 5015

TOOL_FAMILY_LIST = ["MSFT",
                    "INTEL",
                    "GCC",
                    "RVCT"
                    ]

TYPE_HOB_SECTION = 'HOB'
TYPE_EVENT_SECTION = 'EVENT'
TYPE_BOOTMODE_SECTION = 'BOOTMODE'

PCD_ERR_CODE_MAX_SIZE = 4294967295
