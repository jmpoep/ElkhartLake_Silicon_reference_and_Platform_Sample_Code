8 - Royal Park Platform Override (RPPO) {#royalparkplatformoverride}
===

Royal Park Platform Override tags (RPPO-XXX-XXXX) document issues that a Platform team has resolved with an override of Royal Park.

The Active RPPO table lists every issue which is currently resolved with an override. It is a catalog of all such existing overrides.

The Retired RPPO table lists issues which previously required such overrides. It is purely historical as these overrides have all been deleted (are no longer needed).

### Active RPCO-ICLs ElkhartLakePlatSamplePkg/Override

|     Tag      | Client HSD | BP HSD | Status / Planned EOL |   Area   | Description                                                                                                                   |
|:-------------|:-----------|:-------|:---------------------|:---------|:------------------------------------------------------------------------------------------------------------------------------|
|RPPO-CNL-0052 |1209012154  |        |                      |PLATFORM  |Enable Catalog Build in one tree KBL tip                                                                                       |
|RPPO-CNL-0087 |1804715904  |        |                      |PLATFORM  |[Capsule Update] SysFw update feature enablement (3rd stage) (Fault tolerance and Seamless Recovery support)                   |
|RPPO-CNL-0090 |1504760429  |        |BP 1.6.1.0            |FSPW      |FSP to be loaded as standard FV and PeiCore inside FSP can dispatch PEIMs from boot loader.                                    |                                                      |

### Retired RPPOs ElkhartLakePlatSamplePkg/Override

|      Tag     | Client HSD | BP HSD | Status / Planned EOL |   Area   | Description                                                                                                                   |
|:-------------|:-----------|:-------|:---------------------|:---------|:------------------------------------------------------------------------------------------------------------------------------|
|RPPO-ICL-xxxx |            |        |                      |          |                                                                                                                               |
|RPPO-ICL-0001 |1604288624  |        |                      |SHELL     |Reporting Incorrect data in Type 0, 2,3 and 10                                                                                 |
|RPPO-ICL-0002 |220512590   |        |                      |CORE      |Preserve descriptors across call to PciGetBusRange                                                                             |
|RPPO-ICL-0003 |1604424664  |        |                      |CORE      |Remove ConfigBlock from FSP Wrapper as it should use UPD directly                                                              |
|RPPO-ICL-0059 |1209437989  |1375424 |BP 1.4.1.0            |SECURITY  |ICL ACM headers increased hash size from 2048 bits (SHA256) to 3072 bits (SHA384).                                             |
|RPPO-ICL-0060 |1406687827  |        |                      |CORE      |ICL-A2 PO: IPU BIOS setup options needs design change for ICL Program                                                          |
|RPPO-ICL-0080 |1504542482  |        |                      |PLATFORM  |Pre-OS connectivity feature support in ICL.                                                                                    |
|RPPO-ICL-0081 |1504706940  |        |                      |PLATFORM  |Fix Linker illegal text relocation issue for Xcode toolchain                                                                   |
|RPPO-ICL-0082 |1406659399  |        |                      |SECURITY  |Changing TPM2 recieve message to only request tpm suspend on S3 resume                                                         |
|RPPO-ICL-0092 |1806191007  |1375649 |TBD                   |PCH       |Switch to HS400 is not working with core driver                                                                                |
|RPPO-SKL-0002 |1205700453  |        |                      |PLATFORM  |ASSERT if use third-party AHCI whose port number exceed 3.                                                                     |
|RPPO-SKL-0003 |1205953088  |        |                      |PLATFORM  |AhciMode.c spend 10ms on each un-plugged port.                                                                                 |
|RPPO-SKL-0004 |1206090050  |        |                      |PLATFORM  |Marvell 9182 AHCI controller can't drive up in native UEFI mode.                                                               |
|RPPO-SKL-0015 |1206352998  |        |                      |SECURITY  |NEWCENTURY_STS SMI causes hang in SKL Bios                                                                                     |
|RPPO-SKL-0026 |1404331317  |        |                      |PLATFORM  |HSTI optimization platform driver is not present in SKL/KBL causing 600+ ms of extra post time                                 |
|RPPO-SKL-0033 |1504083754  |        |                      |CORE      |Override FCE tools in KBL stream to resolve long delay during build process                                                    |
|RPPO-KBL-0038 |1207163253  |        |                      |PLATFORM  |System boots to EFI after flashing new SPI image                                                                               |
|RPPO-KBL-0043 |1206371435  |        |                      |CORE      |Add GCC Support to Kabylake BIOS                                                                                               |
|RPPO-KBL-0069 |1208882263  |        |                      |SECURITY  |ME HFSTS resgisters change based on power source and causes inconsistent TPM measurements.                                     |
|RPPO-KBL-0083 |1604334659  |        |                      |PLATFORM  |Bios Conf Tool Verification Failed for TPM devices                                                                             |
|RPPO-CNL-0042 |1404702096  |        |                      |PCH       |UFS command timeout is set too high in V26 BIOS                                                                                |
|RPPO-CNL-0053 |1604228165  |        |                      |PCH       |[CNL-Z0 RVP UFS] UFS is detecting in the BIOS, unable to boot and install OS                                                   |
|RPPO-CNL-0061 |1604324896  |        |                      |PLATFORM  |[CNL U1] Adding support for USB 3.1 Gen2 device detection (superspeedplus). XHCI Spec update is needed to remove this Override.|
|RPPO-CNL-0062 |220151832   |        |                      |SECURITY  |[CFL43e-CNP] - TXT fails to launch on CFL43e/CNP                                                                               |
|RPPO-CNL-0063 |1405865867  |        |                      |PCH       |UFS Should be checking for UFS_DEVICE_PATH not SCSI_DEVICE_PATH                                                                |
|RPPO-CNL-0064 |220190201   |        |                      |CORE      |[CNL]ASSERT in CNL Debug Performance Build with UDK2017 RC3                                                                    |
|RPPO-CNL-0065 |1604351459  |        |                      |CORE      |SPI DTPM 2.0 not enumerating in TPM management console and Device manager                                                      |
|RPPO-CNL-0066 |1209512627  |        |                      |CORE      |Add PTT specific override                                                                                                      |
|RPPO-CNL-0067 |1805160582  |        |                      |PCH       |[CNL] Port new UFS driver behavior during controller initialization to platform override.                                      |
|RPPO-CNL-0072 |1504598696  |        |                      |PLATFORM  |Enable GCC compilation for CFL/CNL/ICL source tree                                                                             |
|RPPO-CNL-0073 |1209709218  |        |                      |SECURITY  |Strong Admin Password solution back ported from BP1410                                                                         |
|RPPO-CNL-0075 |1208965129  |        |                      |SECURITY  |OpalPasswordSmm multiple access outside of valid memory regions                                                                |
|RPPO-CNL-0076 |2201077290  |        |                      |SECURITY  |Avoid AuthVariable Timestamp Zeroing on APPEND_WRITE                                                                           |
|RPPO-CNL-0077 |1504644083  |        |                      |PLATFORM  |Enable Xcode compilation for CFL/CNL/ICL source tree                                                                           |
|RPPO-CNL-0079 |1504665005  |        |BP 1.5.1.0            |CORE      |Core Device connection behavior is changed after defer Pci Expansion Rom enabled.                                              |
|RPPO-CNL-0081 |1604576410  |        |BP 1.5.1.0            |PLATFORM  |CNL-Security: Capsule update is getting failed in CNL U11 with Prod Silicon in EDK Shell & Windows environment                 |
|RPPO-CNL-0089 |1406547329  |1375534 |BP 1.6.1.0            |SECURITY  |Firmware BIOS lockdown                                                                                                         |

