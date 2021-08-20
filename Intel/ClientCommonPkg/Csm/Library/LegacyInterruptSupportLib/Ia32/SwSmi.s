#
# This file contains a 'Sample Driver' and is licensed as such
# under the terms of your license agreement with Intel or your
# vendor.  This file may be modified by the user, subject to
# the additional terms of the license agreement
#
#
# Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
# This software and associated documentation (if any) is furnished
# under a license and may only be used or copied in accordance
# with the terms of the license. Except as permitted by such
# license, no part of this software or documentation may be
# reproduced, stored in a retrieval system, or transmitted in any
# form or by any means without the express written consent of
# Intel Corporation.
#
#
# Module Name:
#
#    SwSmi.asm
#
# Abstract:
#
#


ASM_GLOBAL ASM_PFX(IssueSwSmi)

.equ APMC,                0xB2
.equ MAGIC_STONE,         0xB4

#------------------------------------------------------------------------------
# VOID
# EFIAPI
# IssueSwSmi (
#   IN OUT EFI_IA32_REGISTER_SET *RegSet // esp + 4
#   )
#------------------------------------------------------------------------------
ASM_PFX(IssueSwSmi):
  pushl %ebx
  pushl %esi
  pushl %edi
  pushl %ebp

  movl  4(%esp), %ecx
  movl  (%ecx), %eax
  movl  4(%ecx), %ebx
  movl  12(%ecx), %edx
  movl  16(%ecx), %esi
  movl  20(%ecx), %edi
  movl  8(%ecx), %ecx

  # no need to sync EFlags, because it only records status of RealMode.

  outb  %al, $APMC
  # Delay about a microsecond
  outb  %al, $MAGIC_STONE

  pushl %ecx
  movl  4(%esp), %ecx
  movl  %eax, (%ecx)
  movl  %ebx, 4(%ecx)
  movl  %edx, 12(%ecx)
  movl  %esi, 16(%ecx)
  movl  %edi, 20(%ecx)
  popl  %eax
  movl  %eax, 8(%ecx)

  # only sync EFlags.CF back, because only CF will be checked later.
  # (Above MOV and OUT do not change CF.)
  pushfl
  popl  %eax
  andl  $1, %eax
  movl  24(%ecx), %edx
  andb  $0xFE, %dl
  orb   %al, %dl
  movl  %edx, 24(%ecx)

  popl  %ebp
  popl  %edi
  popl  %esi
  popl  %ebx
  ret

