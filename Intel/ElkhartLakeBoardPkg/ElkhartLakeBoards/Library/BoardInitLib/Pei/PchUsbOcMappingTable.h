/** @file
  PCH USB OverCurrent Port mapping tables

@copyright
  Copyright (c) 2018 - 2019 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.
  This file contains an 'Intel Peripheral Driver' and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the
  license agreement.
**/
#ifndef _PCH_USB_OC_MAPPING_TABLE_H_
#define _PCH_USB_OC_MAPPING_TABLE_H_

#include <PlatformBoardConfig.h>

// Default mapping table
extern USB_OC_MAP_TABLE mUsb2OverCurrentMappingTable;
extern USB_OC_MAP_TABLE mUsb3OverCurrentMappingTable;

// ElkhartLake ERB and RVP board specific mapping table
extern USB_OC_MAP_TABLE mEhlErbRvpUsb2OverCurrentMappingTable;
extern USB_OC_MAP_TABLE mEhlErbRvpUsb3OverCurrentMappingTable;

// ElkhartLake CRB board specific mapping table
extern USB_OC_MAP_TABLE mEhlCrbUsb2OverCurrentMappingTable;
extern USB_OC_MAP_TABLE mEhlCrbUsb3OverCurrentMappingTable;

// JasperLake
extern USB_OC_MAP_TABLE mJslUsb2OverCurrentMappingTable;
extern USB_OC_MAP_TABLE mJslUsb3OverCurrentMappingTable;

#endif // _PCH_USB_OC_MAPPING_TABLE_H_
