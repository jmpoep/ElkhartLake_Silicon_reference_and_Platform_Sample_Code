/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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

#ifndef __OverClockSetup__H__
#define __OverClockSetup__H__
#ifdef __cplusplus
extern "C"
{
#endif

// SPD Defines
#define SPDGENERAL      0
#define SPDREVISION     1
#define DRAMDEVICETYPE  2

#define CASLATENCIESLSB_DEFAULT               14
#define CASLATENCIESMSB_DEFAULT               15
#define MINIMUMRASTOCASDELAYTIME_DEFAULT      18
#define MINIMUMROWPRECHARGEDELAYTIME_DEFAULT  20
#define UPPERNIBBLESFORTRASANDTRC_DEFAULT     21
#define TRASMIN_DEFAULT                       22

#define CASLATENCIESLSB_XMP1                  188
#define CASLATENCIESMSB_XMP1                  189
#define MINIMUMRASTOCASDELAYTIME_XMP1         192
#define MINIMUMROWPRECHARGEDELAYTIME_XMP1     191
#define UPPERNIBBLESFORTRASANDTRC_XMP1        194
#define TRASMIN_XMP1                          195

#define CASLATENCIESLSB_XMP2                  223
#define CASLATENCIESMSB_XMP2                  224
#define MINIMUMRASTOCASDELAYTIME_XMP2         227
#define MINIMUMROWPRECHARGEDELAYTIME_XMP2     226
#define UPPERNIBBLESFORTRASANDTRC_XMP2        229
#define TRASMIN_XMP2                          230

#define SPD_COUNT                             7

// SPD Profile
#define DEFAULT_SPD_PROFILE 0
#define CUSTOM_PROFILE      1
#define XMP_PROFILE_1       2
#define XMP_PROFILE_2       3
#define MEMORY_PROFILE_MAX  4

// Frequency Ratio Limits
#define MEMORY_RATIO_MIN    3
#define MEMORY_RATIO_MAX    15

#include <SetupPrivate.h>
#include <Library/CpuMailboxLib.h>
#include <MrcInterface.h>
#include <Protocol/MemInfo.h>

typedef struct {
  UINT32        tCK;
  MrcFrequency  Frequency;
  UINT8         FreqFlag;  // Bitmask of flags from MrcFreqFlag enum
} TRangeTable;

/**
  This function displays the Expected CPU Frequency based on Setup
  BusRatio and BusSpeed.

  @param This            Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param Action          Specifies the type of action taken by the browser.
  @param QuestionId      A unique value which is sent to the original exporting driver
                         so that it can identify the type of data to expect.
  @param Type            The type of value for the question.
  @param Value           A pointer to the data being sent to the original exporting driver.
  @param ActionRequest   On return, points to the action requested by the callback function.

  @retval EFI_SUCCESS       The function completed successfully.
**/
EFI_STATUS
EFIAPI
OcFormCallBackFunction (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  );

/**
  This function displays the Memory Timing values in the OC Setup Menu when Memory Profile is changed.

  @param This            Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param Action          Specifies the type of action taken by the browser.
  @param QuestionId      A unique value which is sent to the original exporting driver
                         so that it can identify the type of data to expect.
  @param Type            The type of value for the question.
  @param Value           A pointer to the data being sent to the original exporting driver.
  @param ActionRequest   On return, points to the action requested by the callback function.

  @retval EFI_SUCCESS - The function completed successfully
  @retval EFI_UNSUPPORTED - The Setup Menu was not updated
  @retval EFI_NOT_FOUND - There is an error in Locating protocols or retrieving browser data
**/
EFI_STATUS
EFIAPI
OcFormMemoryTimingCallBackFunction (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  );

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
