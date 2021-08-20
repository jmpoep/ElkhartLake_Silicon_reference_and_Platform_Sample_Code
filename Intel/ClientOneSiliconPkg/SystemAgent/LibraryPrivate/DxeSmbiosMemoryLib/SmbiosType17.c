/** @file
  This library will determine memory configuration information from the chipset
  and memory and create SMBIOS memory structures appropriately.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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
#include "SmbiosMemory.h"
#include "MemoryConfig.h"

///
/// Memory Device (Type 17) data
///
GLOBAL_REMOVE_IF_UNREFERENCED SMBIOS_TABLE_TYPE17 SmbiosTableType17Data = {
  { EFI_SMBIOS_TYPE_MEMORY_DEVICE, sizeof (SMBIOS_TABLE_TYPE17), 0 },
  TO_BE_FILLED, ///< MemoryArrayHandle
  0xFFFE,       ///< MemoryErrorInformationHandle
  TO_BE_FILLED, ///< TotalWidth
  TO_BE_FILLED, ///< DataWidth
  TO_BE_FILLED, ///< Size
  TO_BE_FILLED, ///< FormFactor
  0,            ///< DeviceSet
  STRING_1,     ///< DeviceLocator
  STRING_2,     ///< BankLocator
  TO_BE_FILLED, ///< MemoryType
  {             ///< TypeDetail
    0,            ///< Reserved     :1;
    0,            ///< Other        :1;
    0,            ///< Unknown      :1;
    0,            ///< FastPaged    :1;
    0,            ///< StaticColumn :1;
    0,            ///< PseudoStatic :1;
    TO_BE_FILLED, ///< Rambus       :1;
    TO_BE_FILLED, ///< Synchronous  :1;
    0,            ///< Cmos         :1;
    0,            ///< Edo          :1;
    0,            ///< WindowDram   :1;
    0,            ///< CacheDram    :1;
    0,            ///< Nonvolatile  :1;
    0,            ///< Registered   :1;
    0,            ///< Unbuffered   :1;
    0,            ///< Reserved1    :1;
  },
  TO_BE_FILLED, ///< Speed
  TO_BE_FILLED, ///< Manufacturer
  TO_BE_FILLED, ///< SerialNumber
  TO_BE_FILLED, ///< AssetTag
  TO_BE_FILLED, ///< PartNumber
  TO_BE_FILLED, ///< Attributes
  TO_BE_FILLED, ///< ExtendedSize
  TO_BE_FILLED, ///< ConfiguredMemoryClockSpeed
  TO_BE_FILLED, ///< MinimumVoltage
  TO_BE_FILLED, ///< MaximumVoltage
  TO_BE_FILLED, ///< ConfiguredVoltage
};
GLOBAL_REMOVE_IF_UNREFERENCED SMBIOS_TYPE17_STRING_ARRAY SmbiosTableType17Strings = {
  TO_BE_FILLED_STRING,  ///< DeviceLocator
  TO_BE_FILLED_STRING,  ///< BankLocator
  TO_BE_FILLED_STRING,  ///< Manufacturer
  TO_BE_FILLED_STRING,  ///< SerialNumber
#ifdef MEMORY_ASSET_TAG ///< AssetTag
  MEMORY_ASSET_TAG,
#else
  "0123456789",
#endif
  TO_BE_FILLED_STRING   ///< PartNumber
};

/**
  Retrieves string for the SMBIOS Type 17 Table DeviceLocator field.

  @param[in]  Controller                    Desired Controller to get a DeviceLocator string for.
  @param[in]  Dimm                          Desired DIMM to get a DeviceLocator string for.
  @param[in]  MdSocket                      0 = Memory Down, 1 = Socketed.

  @retval                                   The DeviceLocator string
**/
CHAR8*
GetDeviceLocatorString (
  IN  UINT8               ControllerIndex,
  IN  UINT8               Dimm,
  IN  UINT8               MdSocket
  )
{
  CHAR8     *DeviceLocator;

  if (mMemoryDxeConfig->GetDeviceLocatorString != NULL) {
    DeviceLocator = mMemoryDxeConfig->GetDeviceLocatorString (
                                        mMemoryDxeConfig,
                                        ControllerIndex,
                                        Dimm,
                                        MdSocket
                                        );
    if (DeviceLocator != NULL) {
      return DeviceLocator;
    }
  }
  if (MdSocket) {
    return DeviceLocatorStringsDimm[ControllerIndex][Dimm];
  } else {
    return DeviceLocatorStringsMemoryDown[ControllerIndex][Dimm];
  }
}

/**
  Retrieves string for the SMBIOS Type 17 Table BankLocator field.

  @param[in]  Controller                    Desired Controller to get a BankLocator string for.
  @param[in]  Dimm                          Desired DIMM to get a BankLocator string for.
  @param[in]  MdSocket                      0 = Memory Down, 1 = Socketed.

  @retval                                   The BankLocator string
**/
CHAR8*
GetBankLocatorString (
  IN  UINT8               ControllerIndex,
  IN  UINT8               Dimm,
  IN  UINT8               MdSocket
  )
{
  CHAR8     *BankLocator;

  if (mMemoryDxeConfig->GetBankLocatorString != NULL) {
    BankLocator = mMemoryDxeConfig->GetBankLocatorString (
                                      mMemoryDxeConfig,
                                      ControllerIndex,
                                      Dimm,
                                      MdSocket
                                      );
    if (BankLocator != NULL) {
      return BankLocator;
    }
  }
  return BankLocatorStrings[Dimm >> 1];
}

/**
  This function installs SMBIOS Table Type 17 (Memory Device).
  This function installs one table per memory device slot, whether populated or not.

  @param[in] SmbiosProtocol     - Instance of Smbios Protocol

  @retval EFI_SUCCESS           - if the data is successfully reported.
  @retval EFI_OUT_OF_RESOURCES  - if not able to get resources.
  @retval EFI_INVALID_PARAMETER - if a required parameter in a subfunction is NULL.
**/
EFI_STATUS
InstallSmbiosType17 (
  IN  EFI_SMBIOS_PROTOCOL *SmbiosProtocol
  )
{
  EFI_STATUS                      Status;
  UINT16                          Index;
  UINT32                          DimmMemorySizeInMB;
  UINT8                           Dimm;
  UINT8                           *SmbusBuffer;
  CHAR8                           *StringBuffer;
  CHAR8                           *StringBufferStart;
  UINTN                           StringBufferSize;
  CHAR8                           StringBuffer2[4];
  UINT8                           IndexCounter;
  UINTN                           IdListIndex;
  UINT16                          MemoryTotalWidth;
  UINT16                          MemoryDataWidth;
  BOOLEAN                         FoundManufacturer;
  EFI_SMBIOS_HANDLE               SmbiosHandle;
  UINT16                          ManufactureIdLsb;
  UINT16                          ManufactureIdMsb;
  UINT16                          PartNoStartByte;
  UINT16                          PartNoEndByte;
  UINT16                          SerialNoStartByte;
  UINT16                          SerialNoEndByte;
  UINT8                           MemoryBusWidthByte;
  UINT8                           DramDeviceType;
  UINT8                           ModuleType;
  UINTN                           StrBuffLen;
  UINT8                           ChannelIndex;
  UINT8                           DimmIndex;
  UINT8                           ControllerIndex;
  UINT8                           MdSocket;

  Status = EFI_SUCCESS;

  /**
    StringBuffer should only use around 50 to 60 characters max.
    Therefore, allocate around double that, as a saftey margin
  **/
  StringBufferSize  = (sizeof (CHAR8)) * 100;
  StringBufferStart = AllocateZeroPool (StringBufferSize);
  if (StringBufferStart == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  /**
    Initialize variables for retrieving required data from SPD buffer.
    Since the first SPD byte in buffer is SPD_MANUFACTURER_ID_LSB,
    all fields offset should be subtracted by SPD_MANUFACTURER_ID_LSB.
    Assume default values to be DDR3 bytes, Non-JEDEC LPDDR3 and DDR3 use these SPD byte offsets.
  **/
  ManufactureIdLsb = 0;
  ManufactureIdMsb = DDR3_SPD_MANUFACTURER_ID_MSB - DDR3_SPD_MANUFACTURER_ID_LSB;
  PartNoStartByte = DDR3_SPD_PART_NO_START_BYTE - DDR3_SPD_MANUFACTURER_ID_LSB;
  PartNoEndByte = DDR3_SPD_PART_NO_END_BYTE - DDR3_SPD_MANUFACTURER_ID_LSB;
  SerialNoStartByte = DDR3_SPD_SERIAL_NO_START_BYTE - DDR3_SPD_MANUFACTURER_ID_LSB;
  SerialNoEndByte = DDR3_SPD_SERIAL_NO_END_BYTE - DDR3_SPD_MANUFACTURER_ID_LSB;
  //@todo - To be updated for 2xMC
  for (ControllerIndex = 0; ControllerIndex < MEM_CFG_MAX_CONTROLLERS; ControllerIndex++) {
    for (Dimm = 0; Dimm < (MEM_CFG_MAX_SOCKETS/MEM_CFG_MAX_CONTROLLERS); Dimm++) {
      ChannelIndex = Dimm >> 1;
      DimmIndex = Dimm & 0x1;
      ///
      /// Use channel slot map to check whether the Socket is supported in this SKU, some SKU only has 2 Sockets totally
      ///
      if ((mMemInfo->Controller[ControllerIndex].ChannelInfo[ChannelIndex].DimmInfo[DimmIndex].Status == DIMM_PRESENT) && (mMemInfo->Controller[ControllerIndex].ChannelInfo[ChannelIndex].DimmInfo[DimmIndex].DimmCapacity > 0)) {
        DramDeviceType = mMemInfo->Controller[ControllerIndex].ChannelInfo[ChannelIndex].DimmInfo[DimmIndex].SpdDramDeviceType;
        /// If DramDeviceType is JEDEC spec LPDDR3 or DDR4, use DDR4 SPD byte offsets.
        if ((DramDeviceType == DDR_DTYPE_JEDEC_LPDDR3) || (DramDeviceType == DDR_DTYPE_DDR4)) {
          ManufactureIdMsb = DDR4_SPD_MANUFACTURER_ID_MSB - DDR4_SPD_MANUFACTURER_ID_LSB;
          PartNoStartByte = DDR4_SPD_PART_NO_START_BYTE - DDR4_SPD_MANUFACTURER_ID_LSB;
          PartNoEndByte = DDR4_SPD_PART_NO_END_BYTE - DDR4_SPD_MANUFACTURER_ID_LSB;
          SerialNoStartByte = DDR4_SPD_SERIAL_NO_START_BYTE - DDR4_SPD_MANUFACTURER_ID_LSB;
          SerialNoEndByte = DDR4_SPD_SERIAL_NO_END_BYTE - DDR4_SPD_MANUFACTURER_ID_LSB;
        }
      }
    }
  }

  SmbusBuffer     = NULL;
  ///
  /// Each instance of table type 17 has the same MemoryArrayHandle
  ///
  SmbiosTableType17Data.MemoryArrayHandle = mSmbiosType16Handle;

  /**
    For each socket that exists, whether it is populated or not, generate Type 17.

    The Desktop and mobile only support 2 channels * 2 slots per channel = 4 sockets totally
    So there is rule here for Desktop and mobile that there are no more 4 DIMMS totally in a system:
     - Channel A/ Slot 0 --> SpdAddressTable[0] --> DeviceLocatorStringsDimm[0] --> MemInfoHobProtocol.MemInfoData.dimmSize[0]
     - Channel A/ Slot 1 --> SpdAddressTable[1] --> DeviceLocatorStringsDimm[1] --> MemInfoHobProtocol.MemInfoData.dimmSize[1]
     - Channel B/ Slot 0 --> SpdAddressTable[2] --> DeviceLocatorStringsDimm[2] --> MemInfoHobProtocol.MemInfoData.dimmSize[2]
     - Channel B/ Slot 1 --> SpdAddressTable[3] --> DeviceLocatorStringsDimm[3] --> MemInfoHobProtocol.MemInfoData.dimmSize[3]
  **/
  for (ControllerIndex = 0; ControllerIndex < MEM_CFG_MAX_CONTROLLERS; ControllerIndex++) {
    for (Dimm = 0; Dimm < (MEM_CFG_MAX_SOCKETS/MEM_CFG_MAX_CONTROLLERS); Dimm++) {
      ChannelIndex = Dimm >> 1;
      DimmIndex = Dimm & 0x1;

      if ((mMemInfo->Controller[ControllerIndex].ChannelInfo[ChannelIndex].DimmInfo[DimmIndex].Status == DIMM_PRESENT) && (mMemInfo->Controller[ControllerIndex].ChannelInfo[ChannelIndex].DimmInfo[DimmIndex].DimmCapacity > 0)) {

        ///
        /// Generate Memory Device info (Type 17)
        ///
        DramDeviceType = mMemInfo->Controller[ControllerIndex].ChannelInfo[ChannelIndex].DimmInfo[DimmIndex].SpdDramDeviceType;
        ModuleType = mMemInfo->Controller[ControllerIndex].ChannelInfo[ChannelIndex].DimmInfo[DimmIndex].SpdModuleType;
        MemoryBusWidthByte = mMemInfo->Controller[ControllerIndex].ChannelInfo[ChannelIndex].DimmInfo[DimmIndex].SpdModuleMemoryBusWidth;

        ///
        /// MRC save/restore hob only provides these SPD bytes: Non-JEDEC LPDDR3/DDR3 - 117 ~ 145; JEDEC LPDDR3/DDR4 - 320 ~ 348
        ///
        SmbusBuffer = (UINT8 *) &(mMemInfo->Controller[ControllerIndex].ChannelInfo[ChannelIndex].DimmInfo[DimmIndex].SpdSave);

        ///
        /// Use SPD data to generate Device Type info
        ///
        MdSocket = mMemInfo->Controller[ControllerIndex].ChannelInfo[ChannelIndex].DimmInfo[DimmIndex].MdSocket;
        SmbiosTableType17Strings.DeviceLocator  = GetDeviceLocatorString (ControllerIndex, Dimm, MdSocket);
        SmbiosTableType17Strings.BankLocator    = GetBankLocatorString (ControllerIndex, Dimm, MdSocket);

        ///
        /// Reset StringBuffer
        ///
        StringBuffer = StringBufferStart;

        ///
        /// Show name for known manufacturer or ID for unknown manufacturer
        ///
        FoundManufacturer = FALSE;

        ///
        /// Calculate index counter
        /// Clearing Bit7 as it is the Parity Bit for Byte 117
        ///
        IndexCounter = SmbusBuffer[ManufactureIdLsb] & (~0x80);

        ///
        /// Convert memory manufacturer ID to string
        ///
        for (IdListIndex = 0; MemoryModuleManufactureList[IdListIndex].Index != 0xff; IdListIndex++) {
          if (MemoryModuleManufactureList[IdListIndex].Index == IndexCounter &&
              MemoryModuleManufactureList[IdListIndex].ManufactureId == SmbusBuffer[ManufactureIdMsb]
              ) {
            SmbiosTableType17Strings.Manufacturer = MemoryModuleManufactureList[IdListIndex].ManufactureName;
            FoundManufacturer = TRUE;
            break;
          }
        }
        ///
        /// Use original data if no conversion information in conversion table
        ///
        StrBuffLen = StringBufferSize / sizeof (CHAR8);
        if (!(FoundManufacturer)) {
          AsciiStrCpyS (StringBuffer, StrBuffLen, "0x");
          for (Index = ManufactureIdLsb; Index <= ManufactureIdMsb; Index++) {
            if (Index == ManufactureIdLsb) {
              ///
              /// Clear the parity bit on the continuation counter for added readability
              ///
              AsciiValueToStringS (
                StringBuffer2,
                sizeof (StringBuffer2),
                PREFIX_ZERO | RADIX_HEX,
                (UINT8) (SmbusBuffer[Index] & (~0x80)),
                2);
            } else {
              AsciiValueToStringS (StringBuffer2, sizeof (StringBuffer2), PREFIX_ZERO | RADIX_HEX, SmbusBuffer[Index], 2);
            }
            AsciiStrCatS (StringBuffer, StrBuffLen, StringBuffer2);
          }
          SmbiosTableType17Strings.Manufacturer = StringBuffer;
          StrBuffLen -= AsciiStrSize (StringBuffer);
          StringBuffer += AsciiStrSize (StringBuffer);
        }
        AsciiStrCpyS (StringBuffer, StrBuffLen, "");
        for (Index = SerialNoStartByte; Index <= SerialNoEndByte; Index++) {
          AsciiValueToStringS (StringBuffer2, sizeof (StringBuffer2), PREFIX_ZERO | RADIX_HEX, SmbusBuffer[Index], 2);
          AsciiStrCatS (StringBuffer, StrBuffLen, StringBuffer2);
        }
        SmbiosTableType17Strings.SerialNumber = StringBuffer;
        StrBuffLen -= AsciiStrSize (StringBuffer);
        StringBuffer += AsciiStrSize (StringBuffer);

        AsciiStrCpyS (StringBuffer, StrBuffLen, "");
        for (Index = PartNoStartByte; Index <= PartNoEndByte; Index++) {
          AsciiSPrint (StringBuffer2, 4, "%c", SmbusBuffer[Index]);
          AsciiStrCatS (StringBuffer, StrBuffLen, StringBuffer2);
        }
        SmbiosTableType17Strings.PartNumber = StringBuffer;
        ASSERT ((StringBuffer + AsciiStrSize (StringBuffer)) < (StringBufferStart + StringBufferSize));

        SmbiosTableType17Data.Manufacturer = STRING_3;
        SmbiosTableType17Data.SerialNumber = STRING_4;
        SmbiosTableType17Data.AssetTag     = STRING_5;
        SmbiosTableType17Data.PartNumber   = STRING_6;

        ///
        /// Get the Memory TotalWidth and DataWidth info for DDR3
        /// refer to DDR3 SPD 1.0 spec, Byte 8: Module Memory Bus Width
        /// SPD Offset 8 Bits [2:0] DataWidth aka Primary Bus Width
        /// SPD Offset 8 Bits [4:3] Bus Width extension for ECC
        ///
        MemoryDataWidth = 8 * (1 << (MemoryBusWidthByte & 0x07));
        MemoryTotalWidth = MemoryDataWidth + 8 * (MemoryBusWidthByte & 0x18);
        SmbiosTableType17Data.TotalWidth = MemoryTotalWidth;
        SmbiosTableType17Data.DataWidth = MemoryDataWidth;

        DimmMemorySizeInMB = mMemInfo->Controller[ControllerIndex].ChannelInfo[ChannelIndex].DimmInfo[DimmIndex].DimmCapacity;
        ///
        /// See the DMTF SMBIOS Specification 2.7.1, section 7.18.4
        /// regarding use of the ExtendedSize field.
        ///
        if (DimmMemorySizeInMB < SMBIOS_TYPE17_USE_EXTENDED_SIZE) {
          SmbiosTableType17Data.Size = (UINT16) DimmMemorySizeInMB;
          SmbiosTableType17Data.ExtendedSize = 0;
        } else {
          SmbiosTableType17Data.Size = SMBIOS_TYPE17_USE_EXTENDED_SIZE;
          SmbiosTableType17Data.ExtendedSize = DimmMemorySizeInMB;
        }

        switch (ModuleType & DDR_MTYPE_SPD_MASK) {
          case DDR_MTYPE_SODIMM:
          case DDR_MTYPE_SO_UDIMM:
            /// Legacy non-JEDEC LPDDR3 SPD images use SODIMM module type which should be soldered down form factor.
            SmbiosTableType17Data.FormFactor = (DramDeviceType == DDR_DTYPE_LPDDR3) ? MemoryFormFactorRowOfChips : MemoryFormFactorSodimm;
            break;

          case DDR_MTYPE_RDIMM:
          case DDR_MTYPE_MINI_RDIMM:
            SmbiosTableType17Data.FormFactor = MemoryFormFactorRimm;
            break;

          case DDR_MTYPE_MEM_DOWN:
            SmbiosTableType17Data.FormFactor = MemoryFormFactorRowOfChips;
            break;

          case DDR_MTYPE_UDIMM:
          case DDR_MTYPE_MICRO_DIMM:
          case DDR_MTYPE_MINI_UDIMM:
          default:
            SmbiosTableType17Data.FormFactor = MemoryFormFactorDimm;
            break;
        }

        switch (DramDeviceType) {
          case DDR_DTYPE_DDR3:
            SmbiosTableType17Data.MemoryType = (UINT8) MemoryTypeDdr3;
            break;

          case DDR_DTYPE_DDR4:
            SmbiosTableType17Data.MemoryType = (UINT8) MemoryTypeDdr4;
            break;

          case DDR_DTYPE_LPDDR3:
          case DDR_DTYPE_JEDEC_LPDDR3:
            SmbiosTableType17Data.MemoryType = (UINT8) MemoryTypeLpddr3;
            break;

          default:
            SmbiosTableType17Data.MemoryType = (UINT8) MemoryTypeLpddr4;
            break;
        }

        if (SmbiosTableType17Data.FormFactor == MemoryFormFactorRimm) {
          SmbiosTableType17Data.TypeDetail.Rambus = 1;
        } else {
          SmbiosTableType17Data.TypeDetail.Rambus = 0;
        }
        SmbiosTableType17Data.TypeDetail.Synchronous  = 1;

        SmbiosTableType17Data.Speed = mMemInfo->Controller[ControllerIndex].ChannelInfo[ChannelIndex].DimmInfo[DimmIndex].Speed;
        SmbiosTableType17Data.Attributes = mMemInfo->Controller[ControllerIndex].ChannelInfo[ChannelIndex].DimmInfo[DimmIndex].RankInDimm & 0x0F;

        SmbiosTableType17Data.ConfiguredMemoryClockSpeed = (UINT16) mMemInfo->ConfiguredMemoryClockSpeed;
        SmbiosTableType17Data.MinimumVoltage             = 0;
        SmbiosTableType17Data.MaximumVoltage             = 0;
        SmbiosTableType17Data.ConfiguredVoltage          = (UINT16) mMemInfo->VddVoltage[mMemInfo->MemoryProfile];

      } else if ((BIT0 << DimmIndex) & ((ChannelIndex == 0) ? mMemoryDxeConfig->ChannelASlotMap : mMemoryDxeConfig->ChannelBSlotMap)) {
        ///
        /// Slot exists but Memory is not Populated in this slot.
        ///
        SmbiosTableType17Strings.DeviceLocator       = GetDeviceLocatorString (ControllerIndex, Dimm, 1);
        SmbiosTableType17Strings.BankLocator         = GetBankLocatorString (ControllerIndex, Dimm, 1);

        SmbiosTableType17Strings.Manufacturer        = NULL;
        SmbiosTableType17Strings.SerialNumber        = NULL;
        SmbiosTableType17Strings.PartNumber          = NULL;

        SmbiosTableType17Data.Manufacturer           = NO_STRING_AVAILABLE;
        SmbiosTableType17Data.SerialNumber           = NO_STRING_AVAILABLE;
        SmbiosTableType17Data.AssetTag               = NO_STRING_AVAILABLE;
        SmbiosTableType17Data.PartNumber             = NO_STRING_AVAILABLE;

        SmbiosTableType17Data.TotalWidth             = 0;
        SmbiosTableType17Data.DataWidth              = 0;
        SmbiosTableType17Data.Size                   = 0;
        SmbiosTableType17Data.FormFactor             = MemoryFormFactorUnknown;
        SmbiosTableType17Data.MemoryType             = MemoryTypeUnknown;
        SmbiosTableType17Data.TypeDetail.Rambus      = 0;
        SmbiosTableType17Data.TypeDetail.Synchronous = 0;
        SmbiosTableType17Data.Speed                  = 0;
        SmbiosTableType17Data.Attributes             = 0;
        SmbiosTableType17Data.ExtendedSize           = 0;
        SmbiosTableType17Data.MinimumVoltage         = 0;
        SmbiosTableType17Data.MaximumVoltage         = 0;
        SmbiosTableType17Data.ConfiguredVoltage      = 0;

        SmbiosTableType17Data.ConfiguredMemoryClockSpeed = 0;
      } else {
        ///
        /// Slot doesn't exist. Continue without adding Type 17 record for this slot.
        ///
        continue;
      }

      ///
      /// Generate Memory Device info (Type 17)
      ///
      Status = AddSmbiosEntry (
                 (EFI_SMBIOS_TABLE_HEADER *) &SmbiosTableType17Data,
                 (CHAR8 **) &SmbiosTableType17Strings,
                 SMBIOS_TYPE17_NUMBER_OF_STRINGS,
                 SmbiosProtocol,
                 &SmbiosHandle);
      if (EFI_ERROR (Status)) {
        goto CleanAndExit;
      }
    }
  }
CleanAndExit:
  FreePool (StringBufferStart);
  return Status;
}
