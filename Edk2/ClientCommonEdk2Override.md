6 - Client Common Edk2 Override (CCEO) {#clientcommonedk2override}
===

# Description
Client Common Edk2 Override tags `CCEO-xxxx` document issues that Client BIOS team has resolved with an Common override of EDK2 Open Source code.

The Active CCEO table lists every issue which is currently resolved with an override.  It is a catalog of all such existing overrides.

The Retired CCEO table lists issues which previously required such overrides. It is purely historical as these overrides have all been deleted (are no longer needed).

# Active CCEOs in ClientCommonEdk2/Override
//
// InternalOnlyBegin
//
BP HSD can be the bugzilla number(b) or master sha-id(m), please fill below items at the next line of each override
1. Override category: A:New feature, B:Workaround for chipset/hardware, C:Factory or internal tool support, D:Edk2 code bug
2. Plan to remove it: A: Future BP core update, B: Chipset/hardware change, C: Tool update, D: Other solution from BP core team
3. Author's name
//
// InternalOnlyEnd
//
| Tag     | Client HSD | BP HSD                                 | Plan EOL | Add WWYY | Description |
| :------ | :--------- | :------                                | :--------| :------- | :---------- |
|CCEO-0001|2280811     |                                        |          |          |BIOS W/A for VBIOS limitation above 8MB
 1: B 2: B  3: Chang, Tomson                // InternalOnlyContent
|CCEO-0002|220738527   |1375568                                 | BP201903 |          |Fix error in CPU frequency calculation
 1: A 2: A  3: Ratnayake, Senaka            // InternalOnlyContent
|CCEO-0004|1805888240  |N/A                                     |N/A       |          |Cannot enter RST Legacy OROM UI using USB keyboard
 1: D 2: D  3: Peng, NickX                  // InternalOnlyContent
|CCEO-0005|1805160582  |b1343                                   | BP201903 |          |Port new UFS driver behavior during controller initialization to platform override.
 1: A 2: A  3: Albecki, Mateusz             // InternalOnlyContent
|CCEO-0006|2206251456  |1375751                                 | BP201903 |          |Add a function to read the stack value at FSP entry to support using bootloader stack in FSP
 1: D 2: D  3: Manninen, Eija               // InternalOnlyContent
|CCEO-0007|1504760429  |                                        | BP201903 |          |FSP to be loaded as standard FV and PeiCore inside FSP can dispatch PEIMs from boot loader
 1: A 2: A  3: Chen, TerryX                 // InternalOnlyContent
|CCEO-0008|1606812150  |4ec00f82edc845548a2000fe514c6898932b8c95| BP201903 |          |Removed warning for a long time waiting when "keep user data" has checked
 1: D 2: A  3: Chu, Maggie                  // InternalOnlyContent
|CCEO-0009|2206224568  |0176af142ef632c82f37cd3616f0184241f4fcbb &
                        736c436e5355e1370f13392a6cecf2cf260608a8| BP201903 |          |Need an override to PciBusDxe driver because BIOS code is writing to MMIO enable bit in command register before it has actually set all BARs on a PCIe device
 1: D 2: A  3: Venur, Sumana                // InternalOnlyContent
|CCEO-0010|2206921981  |39699d078c01117a2073ebe14337ef8569674578| BP201903 |          |Pull in changes from current EDK2 master; eliminate iASL compiler warning.
 1: D 2: A  3: Gough, Robert                // InternalOnlyContent
|CCEO-0011|1409055209  |b49758c11280a0dfba981632ed6ed06ed80a30d8| BP201903 |          |Allow enabling TPM 1.2 device from disabled state
 1: D 2: A  3: Gonzalez del Cueto, Rodrigo  // InternalOnlyContent
|CCEO-0012|1504760429  |2bb4a7ca6299298f84da4657576b140f178c7458| BP201903 |          |Support SecCore and PeiCore in different FV
 1: A 2: A  3: Shih HaoX Liu                // InternalOnlyContent
|CCEO-0013|15070068740 |b3497bad1221704a5dbc5da0b10f42625f1ad2ed| BP201903 |          |Pull the partial fix of b3497bad1221704a5dbc5da0b10f42625f1ad2ed from master.
 1: D 2: A  3: Chen, Kenji                  // InternalOnlyContent
|CCEO-0014|2207143516  |3d3416e892ac32c871031c65351afca11a715306| BP201903 |          |BaseTools: Fix the problem using FILE_GUID override in .dsc
 1: D 2: A  3: Shindo, Miki                 // InternalOnlyContent
|CCEO-0016|1604627623 |073a76e662934e0115c6931c4b5d60fa88d933d9 &
                       7c3a1efd15243df7783c4a5a6be412e99402f5a0 &
                       68edd7dbad77d7170ee0e1c5dbefae93ea9997b1 &
                       0aac2f777a688a146050bed47753e2dcf801d3c7 &
                       0d25074cbcc272532d6ca5a47974ac5b31f4b6ec &
                       3eb69b081c683f9d825930d0c511e43c0485e5d2 | BP201903 |          |Add CET feature support in SMM.
 1: D 2: A  3: Kuo, Donald                  // InternalOnlyContent
|CCEO-0017|15070068740 |8a9301cdd75439e781754014f514fa06d99140d1| BP201903 |          |Pull the change of "Add a Pcd to skip Opal prompt" from master.
 1: D 2: A  3: Chen, Kenji                  // InternalOnlyContent
|CCEO-0015|1507155086  |0b836855fb4df66f7ca035a7b67a064c0088ed69| BP201905 |          |Pull the change of "BaseTools: Sometime write file not immediate to disk" from master.
 1: D 2: A  3: Gao, Liming                  // InternalOnlyContent
|CCEO-0018|2207339846 |2f818ed0fb57d98985d151781a2ce9b8683129ee &
                       643556fc484397364f92fcfe7aed8abe1c082de0 &
                       5bc96263ea2bfecb07deea81c68a6c3e226ebda1 | BP201903 |          |Support Module Overrides in BaseTool
 1: A 2: A  3: Shindo, Miki                  // InternalOnlyContent
|CCEO-0019|N/A        |1e948802e7556d87bd0cc86e5082594d9cb1c622 | BP201905 |          |NetworkPkg: Add DSC/FDF include segment files to NetworkPkg
 1: D 2: A  3: Gao, Liming                  // InternalOnlyContent
|CCEO-0020|1507230184 |I38b14c3c4ac7a00b37eae71ac904fe94b23cfc1d| BP201903 |          |MdePkg: implement MmServicesTableLib based on traditional SMM
 1: A 2: A  3: Yan-TingX Chen               // InternalOnlyContent
|CCEO-0021|N/A        |04797875d1d53e53e31eca4fa01bc3cf6929f39c &
                       6b74ccf0f8b53256b696ce921d50b873f6f9db57 | BP201908 |          |BaseTools:Make BaseTools support new rules to generate RAW FFS FILE
 1: D 2: A  3: Gao, Liming                  // InternalOnlyContent
|CCEO-0022|1607367928 |a18f784cfdbe17855ec4376e80db927e1a81aaca | BP201903 |          |Upgrade openssl lib from 1.1.0h to 1.1.0j
 1: D 2: A  3: Cheng, Ching JenX            // InternalOnlyContent

# Retired CCEOs - formerly in ClientCommonEdk2/Override
//
// InternalOnlyBegin
//
Please fill below items at the next line of each override
4. Retired category: A:Core sync B:Chipset/hardware update C:Factory process change or internal tool update D:Work out the other solution with core team E:Not require
//
// InternalOnlyEnd
//
| Tag     | Client HSD | BP HSD                                            | Actual EOL | Del WWYY | Description |
| :------ | :--------- | :------                                           | :--------- | :------- | :---------- |
|CCEO-0003|1209512627  |                                        |          |            |Add PTT specific override
 1: A 2: A  3: Chiang, Dakota 4: D            // InternalOnlyContent
