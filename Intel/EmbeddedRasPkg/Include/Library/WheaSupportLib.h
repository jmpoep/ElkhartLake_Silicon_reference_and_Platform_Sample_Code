/** @file
  Interface of WheaSciLib Interface.

  @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2017 Intel Corporation. <BR>

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary    and
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
**/

#ifndef __WHEA_SUPPORT_LIB_H__
#define __WHEA_SUPPORT_LIB_H__


/**
  This routine add EINJ error injection instruction entry. And it can install EINJ table.
  EINJ table only can install once.

  @param [in]  InjectionEntry    - pointer to EINJ error injection entry.
  @param [in]  InstallTableFlag  - TRUE --> Install EINJ table; FALSE --> don't install.

  @retval  VOID
**/
VOID
EFIAPI
AddEinjActionItem (
  IN   EFI_ACPI_6_0_EINJ_INJECTION_INSTRUCTION_ENTRY       *InjectionEntry,
  IN   BOOLEAN                                             InstallTableFlag
  );
#endif
