/** @file
This file contains doxygen commands definitions for creating
ClientSiliconPkg override documentation

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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

@par Specification
**/

/**
 @page FSP Package override

  FSP Override tags (FSPO-xxxx) document issues that Royal Park team has resolved with an override of Royal Park.

  The Active FSPO table lists every issue which is currently resolved with an override. It is a catalog of all such existing overrides.

  The Retired FSPO table lists issues which previously required such overrides. It is purely historical as these overrides have all been deleted (are no longer needed).
<BR>
<CENTER>
<STRONG>Active FSPOs</STRONG>
<BR>in IcelakeFspPkg/Override
</CENTER>

<table border="1" style="width:1200px">
<tr>
  <th>Tag</th>
  <th>Client HSD</th>
  <th>BP HSD</th>
  <th>Status / Planned EOL</th>
  <th>Description</th>
</tr>
  <tr> <td>FSPO-0009</td> <td>1504760411</td> <td></td>         <td></td> <td>FSP should not  modify IDT and let boot loader to initialize it.</td> </tr>
  <tr> <td>FSPO-0013</td> <td>2205371834</td> <td></td>         <td></td> <td>FSP-M should not care about where the stack is located relative to the FSP heap</td> </tr>
</table>

<BR>
<CENTER>
<STRONG>Retired FSPOs</STRONG>
<BR>formerly in KabylakeFspPkg/Override
</CENTER>

<table border="1" style="width:1200px">
<tr>
  <th>Tag</th>
  <th>Client HSD</th>
  <th>BP HSD</th>
  <th>Actual EOL</th>
  <th>Description</th>
</tr>
  <tr> <td>FSCO-0001</td> <td></td>           <td></td>         <td></td> <td>1504005677:Enabling Performance measurement for FSP Binary - Publish FSP performance records through FPDT. Other tags used SIPO-KBL-0001, RPPO-KBL-0045</td> </tr>
  <tr> <td>FSCO-0002</td> <td></td>           <td></td>         <td></td> <td>1604100118:Rename KBL FSP UPD Structure to match version 2.0 Draft 5</td> </tr>
  <tr> <td>FSPO-0003</td> <td></td>           <td></td>         <td></td> <td>1604155579: [Kabylake.other] Need to change the FSP UPD signature to align with FSP2.0 spec</td> </tr>
  <tr> <td>FSPO-0004</td> <td></td>           <td></td>         <td></td> <td>1604155579: [Kabylake.other] Add SpecVersion in FSP_INFO_HEADER</td> </tr>
  <tr> <td>FSPO-0008</td> <td>1504388079</td> <td></td>         <td></td> <td>[KBL FSP] Fail to open bsf file by BCT due to invalid string found in BSE OPTION field</td> </tr>
  <tr> <td>FSPO-0005</td> <td>1209012154</td> <td></td>         <td></td> <td>Enable Catalog Build in one tree</td> </tr>
  <tr> <td>FSPO-0006</td> <td>1209090011</td> <td></td>         <td></td> <td>Update FSP GCC build tool version to GCC 5.4</td> </tr>
  <tr> <td>FSPO-0007</td> <td>1405254128</td> <td></td>         <td></td> <td>Use open source PeiRsa2048Sha256GuidedSectionExtractLib instead of PeiSignedSectionVerificationLib for FV authentication</td> </tr>
  <tr> <td>FSPO-0011</td> <td>1506112645</td> <td></td>         <td></td> <td>Support TraceHub Trace in FSP package</td> </tr>
  <tr> <td>FSPO-0012</td> <td>1506769010</td> <td></td>         <td></td> <td>[EHL] BP 1.5.2.0 formal core sync up</td> </tr>
  <tr> <td>FSPO-0010</td> <td>1405254128</td> <td>Bug 1241</td> <td></td> <td>FSP to be loaded as standard FV and PeiCore inside FSP can dispatch PEIMs from boot loader</td> </tr>
  </table>

**/

