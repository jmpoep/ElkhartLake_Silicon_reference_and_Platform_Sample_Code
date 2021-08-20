/** @file
  Intel ACPI Reference Code for Dynamic Platform & Thermal Framework
  Used for driver debugging and validation.
@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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


Scope(\_SB.IETM)
{
  // TEVT (Trigger EvenT)
  // Used for DPTF driver debugging and validation
  // This function will generate an event of the event code as given in arg1 for the participant given in parameter arg0.
  // Arguments: (2)
  //   Arg0 - The device object name string.
  //   Arg1 - An Integer containing the notification code to be used in Notify.
  // Return Value:
  //   None
  //
  Method(TEVT,2,Serialized,,,{StrObj,IntObj})
  {
    Switch(ToString(Arg0))
    {
      case("IETM") {
        Notify(\_SB.IETM, Arg1) // Intel Extended Thermal Manager (DPTF Manager)
      }

      case("TCPU") {
        Notify(\_SB.PC00.TCPU, Arg1) // TCPU Participant (SA Thermal Device)
      }

      case("CAM1") {
        Notify(\_SB.CAM1, Arg1) // 2D Camera Participant
      }

#ifdef EC_SUPPORT
      case("CHRG") {
        Notify(\_SB.PC00.LPCB.H_EC.CHRG, Arg1) // Charger Participant
      }
#endif

#ifdef ECLITE_PSE_SUPPORT
      case("CHRG") {
        Notify(\_SB.CHRG, Arg1) // Charger Participant
      }
#endif //ECLITE_PSE_SUPPORT

      case("DPLY") {
        Notify(\_SB.PC00.DPLY, Arg1) // Display Participant
      }

      case("TPCH") {
        Notify(\_SB.TPCH, Arg1) // PCH FIVR Participant
      }

      case("SEN2") {
#ifdef EC_SUPPORT
        Notify(\_SB.PC00.LPCB.H_EC.SEN2, Arg1) // Sensor Participant
#endif
#ifdef ECLITE_PSE_SUPPORT
        Notify(\_SB.SEN2, Arg1) // Sensor Participant
#endif //ECLITE_PSE_SUPPORT
      }

      case("SEN3") {
#ifdef EC_SUPPORT
        Notify(\_SB.PC00.LPCB.H_EC.SEN3, Arg1) // Sensor Participant
#endif
#ifdef ECLITE_PSE_SUPPORT
        Notify(\_SB.SEN3, Arg1) // Sensor Participant
#endif //ECLITE_PSE_SUPPORT
      }

      case("SEN4") {
#ifdef EC_SUPPORT
        Notify(\_SB.PC00.LPCB.H_EC.SEN4, Arg1) // Sensor Participant
#endif
#ifdef ECLITE_PSE_SUPPORT
        Notify(\_SB.SEN4, Arg1) // Sensor Participant
#endif //ECLITE_PSE_SUPPORT
      }

      case("SEN5") {
#ifdef EC_SUPPORT
        Notify(\_SB.PC00.LPCB.H_EC.SEN5, Arg1) // Sensor Participant
#endif
#ifdef ECLITE_PSE_SUPPORT
        Notify(\_SB.SEN5, Arg1) // Sensor Participant
#endif //ECLITE_PSE_SUPPORT
      }

      case("STG1") {
        Notify(\_SB.STG1, Arg1) // Storage Participant
      }

      case("STG2") {
        Notify(\_SB.STG2, Arg1) // Storage Participant
      }

      case("TFN1") {
#ifdef EC_SUPPORT
        Notify(\_SB.PC00.LPCB.H_EC.TFN1, Arg1) // Fan Participant
#endif
#ifdef ECLITE_PSE_SUPPORT
        Notify(\_SB.TFN1, Arg1) // Fan Participant
#endif //ECLITE_PSE_SUPPORT
      }

      case("TPWR") {
        Notify(\_SB.TPWR, Arg1) // Power Participant
      }

      case("VIR1") {
        Notify(\_SB.VIR1, Arg1) // Virtual Sensor Participant
      }

      case("VIR2") {
        Notify(\_SB.VIR2, Arg1) // Virtual Sensor Participant
      }

      case("WRLS") {
        Notify(\_SB.WRLS, Arg1) // Wireless Participant Device
      }

      case("WWAN") {
        Notify(\_SB.WWAN, Arg1) // WWAN Participant
      }
    }
  }

} // End Scope(\_SB.IETM)
