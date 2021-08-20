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
#   IN OUT EFI_IA32_REGISTER_SET *RegSet // rcx, r10
#   )
#------------------------------------------------------------------------------
ASM_PFX(IssueSwSmi):
  pushq %rbx
  pushq %rsi
  pushq %rdi
  pushq %rbp

  movq  %rcx, %r10
  movl  (%r10), %eax
  movl  4(%r10), %ebx
  movl  8(%r10), %ecx
  movl  12(%r10), %edx
  movl  16(%r10), %esi
  movl  20(%r10), %edi

  # no need to sync EFlags, because it only records status of RealMode.

  outb  %al, $APMC
  # Delay about a microsecond
  outb  %al, $MAGIC_STONE

  movl  %eax, (%r10)
  movl  %ebx, 4(%r10)
  movl  %ecx, 8(%r10)
  movl  %edx, 12(%r10)
  movl  %esi, 16(%r10)
  movl  %edi, 20(%r10)

  # only sync EFlags.CF back, because only CF will be checked later.
  # (Above MOV and OUT do not change CF.)
  pushfq
  popq  %rax
  andl  $1, %eax
  movl  24(%r10), %edx
  andb  $0xFE, %dl
  orb   %al, %dl
  movl  %edx, 24(%r10)

  popq  %rbp
  popq  %rdi
  popq  %rsi
  popq  %rbx
  ret

