/** @file
  Header file for VMD Lib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#ifndef _VMD_INIT_LIB_H_
#define _VMD_INIT_LIB_H_

#include <VmdPeiConfig.h>


/* VMD Configuration Base Address I */
typedef union {
  struct {
    UINT32 MemorySpaceIndicator : 1;
    /* MemorySpaceIndicator  - Bits[0:0], RO, default = 0b
     * BAR resource is memory (as opposed to I/O).
     */
    UINT32 Type : 2;
    /* Type - Bits[2:1], RW_L, default = 10b
     * Memory type claimed by this BAR is 64-bit addressable
     * Lock: VMCONFIG.VMDLOCK
     */
    UINT32 Prefetchable : 1;
    /* Prefetchable - Bits[3:3], RW_L, default = 1b
     * BAR points to Prefetchable memory.
     */
    UINT32 Rsvd : 16;
    /* Rsvd - Bits[19:4], RO, default = 0
     */
    UINT32 MemoryBaseAddress : 12;
    /* MemoryBaseAddress - Bits[38:20], RW_V, default = 0
     * This field was split. It's value spans this field and the field of similar
     * name in the next/preceding struct (define if required).
     *
     * Sets the location of the CFGBAR in memory space. The size is programmed
     * in CFGBARSZ by BIOS. CFGBARSZ specifies the lowest order address bit that
     * is writable. The minimum granularity is 1MB.
     * If CFGBAR.Type = 10b, then bits 63:32 are writable.
     * If CFGBAR.Type = 00b, then bits 63:32 are read-only.
     */
  } Bits;
  UINT32 Data;
} CFGBAR_N0_VMD_STRUCT;


/* VMD Memory Base Address Range 1 I */
typedef union {
  struct {
    UINT32 MemorySpaceIndicator : 1;
    /* MemorySpaceIndicator - Bits[0:0], RO, default = 0b
     * BAR resource is memory (as opposed to I/O).
     */
    UINT32 Type : 2;
    /* Type - Bits[2:1], RW_L, default = 10b
     * Memory type claimed by this BAR is 64-bit addressable
     * Lock: VMCONFIG.VMDLOCK
     */
    UINT32 Prefetchable : 1;
    /* Prefetchable - Bits[3:3], RW_L, default = 1b
     * BAR points to Prefetchable memory.
     * Lock: VMCONFIG.VMDLOCK
     */
    UINT32 Rsvd : 8;
    /* Rsvd - Bits[11:4], RV, default = 0
     */
    UINT32 MemoryBaseAddress : 20;
    /* MemoryBaseAddress - Bits[31:12], RW_V, default = 0
     * This field was split. It's value spans this field and the field of
     * similar name in the next/preceding struct (define if required).
     *
     * Sets the location of the MEMBAR1 in memory space. The size is programmed
     * in MEMBAR1SZ by BIOS. MEMBAR1SZ specifies the lowest order address bit
     * that is writable. The minimum granularity is 4kB.
     * If MEMBAR1.Type = 10b, then bits 38:32 are writable.
     * If MEMBAR1.Type = 10b, then bits 38:32 are read-only.
     * If MEMBAR1SZ = 0, then all address bits are read-only.
     * If MEMBAR1SZ < 12, then the effective value is 12.
     */
  } Bits;
  UINT32 Data;
} MEMBAR1_N0_VMD_STRUCT;


/* VMD Memory Base Address Range 2 I */
typedef union {
  struct {
    UINT32 MemorySpaceIndicator : 1;
    /* MemorySpaceIndicator - Bits[0:0], RO, default = 0b
     * BAR resource is memory (as opposed to I/O).
     */
    UINT32 Type : 2;
    /* Type - Bits[2:1], RW_L, default = 10b
     * Memory type claimed by this BAR is 64-bit addressable
     * Lock: VMCONFIG.VMDLOCK
     */
    UINT32 Prefetchable : 1;
    /* Prefetchable - Bits[3:3], RW_L, default = 1b
     * BAR points to Prefetchable memory.
     * Lock: VMCONFIG.VMDLOCK
     */
    UINT32 Rsvd : 8;
    /* Rsvd - Bits[11:4], RV, default = 0
     */
    UINT32 MemoryBaseAddress : 20;
    /* MemoryBaseAddress - Bits[31:12], RW_V, default = 0
     * This field was split. It's value spans this field and the field of similar
     * name in the next/preceding struct (define if required).
     *
     * Sets the location of the MEMBAR1 in memory space. The size is programmed
     * in MEMBAR2SZ by BIOS. MEMBAR2SZ specifies the lowest order address bit
     * that is writable. The minimum granularity is 4kB.
     * If MEMBAR2.Type = 10b, then bits 38:32 are writable.
     * If MEMBAR2.Type = 10b, then bits 38:32 are read-only.
     * If MEMBAR2SZ = 0, then all address bits are read-only.
     * If MEMBAR2SZ < 12, then the effective value is 12.
     */
  } Bits;
  UINT32 Data;
} MEMBAR2_N0_VMD_STRUCT;


/* Volume Management Capability */
typedef union {
 struct {
   UINT32 BusRestrictCap : 1;
   /* BUS_RESTRICT_CAP - Bits[0:0], RO, default = 0b
    * 0: Indicates that hardware supports a separate set of bus encodings for
    * VMD. Bus restrictrions are not required.
    * 1: Indicates that bus restrictions are required. BIOS must program
    * VMCONFIG.BUS_RESTRICTIONS field. VMD may only use 128 bus numbers unless
    * VMD owns all devices in its ACPI domain. VMD driver reads this field to
    * determine if bus number restrictions are required. When set, VMD driver
    * must also read VMCONFIG.BUS_RESTRICTIONS field to determine what range of
    * bus numbers to use for Secondary and Subbordinate bus ranges.
    */
   UINT32 Rsvd : 31;
   /* Rsvd - Bits[31:1], RO, default = 0
    */
 } Bits;
 UINT32 Data;
} VMCAP_VMD_STRUCT;


/* Volume Management Configuration */
typedef union {
  struct {
    UINT32 VmdLock : 1;
    /* VmdLock - Bits[0:0], RW_O, default = 0b
     * Locks registers in the Volume Management Device.
     * This must be set by BIOS after programming VMD registers.
     */
    UINT32 MsiRmpDis : 1;
    /* MSI_RMP_DIS - Bits[1:1], RWS, default = 0b
     * MSI Remapping Disable - When set, causes MSI transactions to bypass the
     * remap indexing that triggers a native VMD MSI-X Table Entries.
     * The original MSI will be set up without indexing, however, the Requestor
     * ID will be changed to match the VMD before being translated by VTd.
     * This bit is programmed by the OS or by the VMD Driver.
     */
    UINT32 Rsvd1 : 2;
    /* Rsvd - Bits[3:2], RV, default = 0
     */
    UINT32 DevIdSelect : 4;
    /* DEVID_SELECT - Bits[7:4], RWS_L, default = 0000b
     * Selects the Device ID that appears in the Device ID register. Values are
     * device specific. Only BIOS may program this register field.
     * Volume Management Device v2.0 for Server uses Device ID values 0x28C0 to 0x28CF.
     * Lock: VMCONFIG.VMDLOCK
     */
    UINT32 BusRestrictions : 2;
    /* BUS_RESTRICTIONS - Bits[9:8], RO/RWS_L, default = 00b
     * 00: VMD-Owned Root Port and PCI Switch Bridges must use the 0-127 of bus
     * numbers (0 is the first bus in CFGBAR at offset 0).
     * 01: VMD-Owned Root Port and PCI Switch Bridges must use the 128-255 of
     * bus numbers (128 is the first bus in CFGBAR at offset 0).
     * 10: VMD-Owned Root Port and PCI Switch Bridges may use 0-255 bus numbers
     * (0 is the first bus in CFGBAR at offset 0). This is only used in the
     * event that VMD owns all devices within its ACPI domain.
     * 11: reserved
     * This field is read only when VMCAP.BUS_RESTRICT_CAP bit is clear.
     * BIOS programs this field to a value that ensures the OS visible busses
     * in the ACPI domain where this VMD resides do not conflict with bus number
     * encodings assigned to VMD. VMD driver reads this field to select the
     * appropriate range of bus numbers to use in Secondary and Subordinate Bus
     * registers of PCIe Root Port and Switch Bridges. VMD driver does not use
     * this field to determine the primary bus number for PCIe Root Port and
     * Switch Bridges owned by VMD. The primary bus number must be the same as
     * the Root Bus number that the VMD Root Complext Integrated Endpoint
     * resides on.
     * Lock: VMCONFIG.VMDLOCK
     */
    UINT32 Did_Assign: 16;
    /* DID_ASSIGN - Bits[25:10]
     * The requirement is for BIOS to set new field in VMCONFIG : DID_ASSIGN.
     * In practice, only 8 MSB (VMCONFIG B0:D14:F0, offset 0x44 bits 25:10 DID_ASSIGN)
     * of VMD device id are expected to change project to project (each client
     * project has different 8 MSB for ICL it is 0x8A).
     * BIOS can simply copy those 8 MSB from DID of device0 and BIOS should write
     * the lower 8 MSB to 0x35 (that value is not expected to change, yet we allow
     * programming here as well to be on the safe side).
     */
    UINT32 Rsvd2 : 6;
    /* Reserved: Bits[31:10], RO, default = 0
     */
  } Bits;
  UINT32 Data;
} VMCONFIG_VMD_STRUCT;


/* Volume Management Assignment */
typedef union {
  struct {
    UINT32 PortAssign : 32;
/*
    UINT32 port_assign_a:1;
    UINT32 port_assign_b:1;
    UINT32 port_assign_c:1;
    UINT32 port_assign_d:1;
    UINT32 port_assign_rsvd:28;
*/
    /* Port_Assign - Bits[31:0], RWS_L, default = 0000b
     * Each bit corresponds to a device number on the same bus number as VMD
     * (RootBus0). For each bit set, the associated device will be assigned to
     * the VMD and hidden from the OS. Each bit may be Read-Write for BIOS or
     * Read Only based on the specific VMD implementation.
     * To discover which bits are writable, BIOS may write 1's to all bits and
     * read the value back.
     * Lock: VMCONFIG.VMDLOCK
     */
  } Bits;
  UINT32 Data;
} VMASSIGN_VMD_STRUCT;


/* VMD Configuration BAR Size */
typedef union {
  struct {
    UINT8 Size : 8;
    /* Size - Bits[7:0], RWS_L, default = 'h00
     * Value indicating the size of CFGBAR. This value is written by BIOS
     * prior to enumeration. The value indicates the lowest order address bit
     * that is Writable in CFGBAR. The only legal settings are 20 to 28 (decimal),
     * representing BAR sizes of 1MB through 256MB.
     * If CFGBARSZ = 0, then all address bits are read-only.
     * If CFGBARSZ < 20, then the effective value is 20.
     * If CFGBARSZ > 28, then the effective value is 28.
     * Lock: VMCONFIG.VMDLOCK
    */
  } Bits;
  UINT8 Data;
} CFGBARSZ_VMD_STRUCT;


/* VMD Memory BAR 1 Size */
typedef union {
  struct {
    UINT8 Size : 8;
    /* Size - Bits[7:0], RWS_L, default = 00h
     * Value indicating the size of MEMBAR1SZ. This value is written by BIOS
     * prior to enumeration. The value indicates the lowest order address bit
     * that is writable in MEMBAR1SZ. The only legal settings are 12 to 47 (decimal),
     * representing BAR sizes of 4kB through 256TB.
     * If MEMBAR1SZ = 0, then all address bits are read-only.
     * If MEMBAR1SZ < 12, then the effective value is 12.
     * If MEMBAR1SZ > 47, then the effective value is 47.
     * Lock: VMCONFIG.VMDLOCK
    */
  } Bits;
  UINT8 Data;
} MEMBAR1SZ_VMD_STRUCT;


/* VMD Memory BAR 2 Size */
typedef union {
  struct {
    UINT8 Size : 8;
    /* Size - Bits[7:0], RWS_L, default = 00h
     * Value indicating the size of MEMBAR2SZ. This value is written by BIOS
     * prior to enumeration. The value indicates the lowest order address bit
     * that is writable in MEMBAR2SZ. The only legal settings are 12 to 47 (decimal),
     * representing BAR sizes of 4kB through 256TB.
     * If MEMBAR2SZ = 0, then all address bits are read-only.
     * If MEMBAR2SZ < 12, then the effective value is 12.
     * If MEMBAR2SZ > 47, then the effective value is 47.
     * Lock: VMCONFIG.VMDLOCK
    */
  } Bits;
  UINT8 Data;
} MEMBAR2SZ_VMD_STRUCT;


/* Root Bus Where VMD Resides */
typedef union {
  struct {
    UINT8 Bus : 8;
    /* Bus - Bits[7:0], RO, default = 00h
     * The Root Bus that the Volume Management Device endpoint resides on.
     * This also specifies the bus number where the devices and functions that
     * VMD owns reside.
    */
  } Bits;
  UINT8 Data;
} ROOTBUS_VMD_STRUCT;


/* Volume Management Function 0 Assignment */
typedef union {
  struct {
    UINT32 Device : 32;
    /* Device - Bits[31:0], RWS-L, default = 00000000h
     * Each bit corresponds to a device number on the same bus number as VMD (Bus0).
     * For each bit set, the associated device function 0 will be assigned to
     * the VMD and hidden from the OS.Each bit may be Read-Write for BIOS or
     * Read Only based on the specific VMD implementation. To discover which bits
     * are writeable, BIOS may write 1's to all bits and read the value back.
     * If a bit in this register is set for a device, then a dummy function will
     * appear at function 0 in its place in OS visible configuration space.
     * Lock: VMCONFIG.VMDLOCK
    */
  } Bits;
  UINT32 Data;
} FN0_ASSIGN_VMD_STRUCT;


/* Volume Management Function 1 Assignment */
typedef union {
  struct {
    UINT32 Device : 32;
    /* Device - Bits[31:0], RWS-L, default = 00000000h
     * Each bit corresponds to a device number on the same bus number as VMD (Bus0).
     * For each bit set, the associated device function 1 will be assigned to
     * the VMD and hidden from the OS.Each bit may be Read-Write for BIOS or
     * Read Only based on the specific VMD implementation. To discover which bits
     * are writeable, BIOS may write 1's to all bits and read the value back.
     * If a bit in this register is set for a device, and the corresponding bit
     * for function 0 is not set in FN0_ASSIGN, then a dummy function will appear
     * at function 0 for the device in CFGBAR configuration space.
     * Lock: VMCONFIG.VMDLOCK
    */
  } Bits;
  UINT32 Data;
} FN1_ASSIGN_VMD_STRUCT;


/* Volume Management Function 2 Assignment */
typedef union {
  struct {
    UINT32 Device : 32;
    /* Device - Bits[31:0], RWS-L, default = 00000000h
     * Each bit corresponds to a device number on the same bus number as VMD (Bus0).
     * For each bit set, the associated device function 2 will be assigned to
     * the VMD and hidden from the OS.Each bit may be Read-Write for BIOS or
     * Read Only based on the specific VMD implementation. To discover which bits
     * are writeable, BIOS may write 1's to all bits and read the value back.
     * If a bit in this register is set for a device, and the corresponding bit
     * for function 0 is not set in FN0_ASSIGN, then a dummy function will appear
     * at function 0 for the device in CFGBAR configuration space.
     * Lock: VMCONFIG.VMDLOCK
    */
  } Bits;
  UINT32 Data;
} FN2_ASSIGN_VMD_STRUCT;


/* Volume Management Function 3 Assignment */
typedef union {
  struct {
    UINT32 Device : 32;
    /* Device - Bits[31:0], RWS-L, default = 00000000h
     * Each bit corresponds to a device number on the same bus number as VMD (Bus0).
     * For each bit set, the associated device function 3 will be assigned to
     * the VMD and hidden from the OS.Each bit may be Read-Write for BIOS or
     * Read Only based on the specific VMD implementation. To discover which bits
     * are writeable, BIOS may write 1's to all bits and read the value back.
     * If a bit in this register is set for a device, and the corresponding bit
     * for function 0 is not set in FN0_ASSIGN, then a dummy function will appear
     * at function 0 for the device in CFGBAR configuration space.
     * Lock: VMCONFIG.VMDLOCK
    */
  } Bits;
  UINT32 Data;
} FN3_ASSIGN_VMD_STRUCT;


/* Volume Management Function 4 Assignment */
typedef union {
  struct {
    UINT32 Device : 32;
    /* Device - Bits[31:0], RWS-L, default = 00000000h
     * Each bit corresponds to a device number on the same bus number as VMD (Bus0).
     * For each bit set, the associated device function 4 will be assigned to
     * the VMD and hidden from the OS.Each bit may be Read-Write for BIOS or
     * Read Only based on the specific VMD implementation. To discover which bits
     * are writeable, BIOS may write 1's to all bits and read the value back.
     * If a bit in this register is set for a device, and the corresponding bit
     * for function 0 is not set in FN0_ASSIGN, then a dummy function will appear
     * at function 0 for the device in CFGBAR configuration space.
     * Lock: VMCONFIG.VMDLOCK
    */
  } Bits;
  UINT32 Data;
} FN4_ASSIGN_VMD_STRUCT;


/* Volume Management Function 5 Assignment */
typedef union {
  struct {
    UINT32 Device : 32;
    /* Device - Bits[31:0], RWS-L, default = 00000000h
     * Each bit corresponds to a device number on the same bus number as VMD (Bus0).
     * For each bit set, the associated device function 5 will be assigned to
     * the VMD and hidden from the OS.Each bit may be Read-Write for BIOS or
     * Read Only based on the specific VMD implementation. To discover which bits
     * are writeable, BIOS may write 1's to all bits and read the value back.
     * If a bit in this register is set for a device, and the corresponding bit
     * for function 0 is not set in FN0_ASSIGN, then a dummy function will appear
     * at function 0 for the device in CFGBAR configuration space.
     * Lock: VMCONFIG.VMDLOCK
    */
  } Bits;
  UINT32 Data;
} FN5_ASSIGN_VMD_STRUCT;


/* Volume Management Function 6 Assignment */
typedef union {
  struct {
    UINT32 Device : 32;
    /* Device - Bits[31:0], RWS-L, default = 00000000h
     * Each bit corresponds to a device number on the same bus number as VMD (Bus0).
     * For each bit set, the associated device function 6 will be assigned to
     * the VMD and hidden from the OS.Each bit may be Read-Write for BIOS or
     * Read Only based on the specific VMD implementation. To discover which bits
     * are writeable, BIOS may write 1's to all bits and read the value back.
     * If a bit in this register is set for a device, and the corresponding bit
     * for function 0 is not set in FN0_ASSIGN, then a dummy function will appear
     * at function 0 for the device in CFGBAR configuration space.
     * Lock: VMCONFIG.VMDLOCK
    */
  } Bits;
  UINT32 Data;
} FN6_ASSIGN_VMD_STRUCT;


/* Volume Management Function 7 Assignment */
typedef union {
  struct {
    UINT32 Device : 32;
    /* Device - Bits[31:0], RWS-L, default = 00000000h
     * Each bit corresponds to a device number on the same bus number as VMD (Bus0).
     * For each bit set, the associated device function 7 will be assigned to
     * the VMD and hidden from the OS.Each bit may be Read-Write for BIOS or
     * Read Only based on the specific VMD implementation. To discover which bits
     * are writeable, BIOS may write 1's to all bits and read the value back.
     * If a bit in this register is set for a device, and the corresponding bit
     * for function 0 is not set in FN0_ASSIGN, then a dummy function will appear
     * at function 0 for the device in CFGBAR configuration space.
     * Lock: VMCONFIG.VMDLOCK
    */
  } Bits;
  UINT32 Data;
} FN7_ASSIGN_VMD_STRUCT;


/**
  This function performs basic initialization for VMD in PEI phase (post-mem)
  @param[in]    VMD_PEI_PREMEM_CONFIG - Pointer to config data
  @retval     EFI_SUCCESS     Successfully initialized VMD
**/
EFI_STATUS
EFIAPI
VmdInit (
IN   VMD_PEI_CONFIG  *VmdPeiConfig
);

#endif /* _VMD_INIT_LIB_H_ */
