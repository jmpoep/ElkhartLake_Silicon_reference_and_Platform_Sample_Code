6 - Royal Park Common Override (RPCO) {#royalparkcommonoverride}
===

# Description
Royal Park Common Override tags `RPCO-xxxx` document issues that Royal Park team has resolved with an override of Royal Park.

The Active RPCO table lists every issue which is currently resolved with an override.  It is a catalog of all such existing overrides.

The Retired RPCO table lists issues which previously required such overrides. It is purely historical as these overrides have all been deleted (are no longer needed).

# Active RPCOs in ClientCommonPkg/Override
| Tag     | Client HSD | BP HSD | Status / Planned EOL | Description |
| :------ | :--------- | :----- | :------------------- | :---------- |
|RPCO-0104|1805079608  |BpCommon|Master                |Secure Erase failed with HDD Password.

# Retired RPCOs - formerly in ClientCommonPkg/Override
| Tag     | Client HSD | BP HSD | Actual EOL | Description |
| :------ | :--------- | :----- | :--------- | :---------- |
|RPCO-0000|2282010     |1375010 |BP1220_RP01 |eMMC boot support in Simics Platform
|RPCO-0001|2502486     |1374933 |BP1210_RP01 |Free-up unaligned pages in PEI AllocateAligned routines
|RPCO-0002|5249948     |1375004 |BP1310_RP01 |ASSERT after reset introduced in BdsSetMemoryTypeInformationVariable function
|RPCO-0003|5318789     |1375009 |BP1211_RP01 |"Configuration Changed" message is continously displayed under HDD BIOS Setting
|RPCO-0004|N/A         |N/A     |BP1310_RP01 |SLE support for Hotkey
|RPCO-0005|5317810     |        |BP1310_RP01 |ClientBIOS does not support NVME device paths
|RPCO-0006|2503158     |1374970 |BP1220_RP01 |Add support for ReclaimForOS() at EndOfDxe instead of ReadyToBoot
|RPCO-0007|2281974     |        |            |CAP PCR's for Measurement failures
|RPCO-0008|5507704     |1375011 |BP1220_RP01 |TXT: TpmDetectedCallback dispatched again if Tpm 2.0 is installed.
|RPCO-0009|2504096     |1375301 |BP 1.4.1.0  |Eliminate the non-MdePkg interfaces for MpService protocol for PI v1.2 compliance
|RPCO-0010|5506016     |1375007 |BP1330_RP01 |Changing MemoryInit into library break TXT SCLEAN and ACHECK functionality.
|RPCO-0011|4027532     |1375278 |BP 1.4.1.0  |Improve S3 resume responsiveness by opting out of TpmSelfTest
|RPCO-0012|N/A         |1374918 |BP1220_RP01 |Add new API BuildResourceDescriptorWithOwnerHob() in HobLib
|RPCO-0013|2502954     |1375005 |BP1220_RP01 |Integrate FSP: Add PCD switch to change the sequence of the end of PEI phase signal.
|RPCO-0014|2503410     |1375006 |            |Change the way to get S3 Memory infor from AcpiVariableCompatibility Guid to MemInfoHob in MRC.
|RPCO-0015|2503658     |1375002 |BP1220_RP01 |Update FSP with v1.1 APIs
|RPCO-0016|2281887     |1375003 |BP1230_RP01 |Integrate FSP into the EDKII tree
|RPCO-0017|2503858     |        |BP1211_RP01 |FSP GCC compiler support. Fix fsp_vpd.h with GCC4.8 with Ubuntu OS.
|RPCO-0018|2503858     |        |BP1230_RP01 |FSP GCC compiler support. Let FspHeader.aslc match FspPatchTable.h.
|RPCO-0019|2504054     |        |BP1211_RP01 |Apply security patch for Variable services
|RPCO-0020|5585017     |1375015 |BP1211_RP01 |Unable to preload OS using EFI network method. PC 00A7 with Blank display
|RPCO-0021|2503744     |N/A     |            |Use -D instead of /D for Clang/GCC compiler
|RPCO-0022|            |1375016 |BP1211_RP01 |FSP GCC compatibility fixes & typos
|RPCO-0023|5585227     |        |BP1211_RP01 |FSP support microcode region size auto detection
|RPCO-0024|5507752     |        |BP1220_RP01 |Need to define MDEPKG_NDEBUG in release build for all packages using MdePkg DebugLib
|RPCO-0025|N/A         |N/A     |BP1220_RP01 |Add support for Memory Profiling
|RPCO-0026|5635440     |N/A     |BP1220_RP01 |NetworkPkg\IScsiDxe Driver incorrectly answers ComponentNameProtocol for Child it does not own
|RPCO-0027|2282106     |        |            |USB HID Emulation does not work in XHCI mode inHSW/BDW/SKL BIOS.
|RPCO-0028|5584445     |        |BP1220_RP01 |Add "!include" support in SkylakeFspPkg\SkylakeFspPkg.dsc
|RPCO-0029|1205540355  |1375279 |BP 1.4.1.0  |Onboard Numlock, Capslock and scrolllock LEDs keys are not synched to external USB Keyboard
|RPCO-0030|            |N/A     |            |Improvement for terminal ConsoleIn.
|RPCO-0031|2502486     |        |BP1310_RP01 |Fix KW scan issues in SKL Platform Pkg
|RPCO-0032|5635242     |        |BP1220_RP01 |DxeMain.c displaying incorrect FV Hob information
|RPCO-0033|5586567     |1374994 |BP1310_RP01 |Build command "build -m XXX.inf fds" fails
|RPCO-0034|5506016     |N/A     |            |Responsiveness optimization for TPM module and driver
|RPCO-0035|            |        |BP1310_RP01 |Skip uninstall ACPI SDT protocol procedure
|RPCO-0036|            |        |BP1310_RP01 |Create a new copy of ACPI table at GetAcpiTable2()
|RPCO-0037|            |        |            |Force to refer to ACPI _PRT not legacy $PIR
|RPCO-0038|2280811     |        |            |BIOS W/A for VBIOS limitation above 8MB
|RPCO-0039|            |        |BP1320_RP01 |Build Rule and Build Tool enhancement
|RPCO-0040|2502247     |        |BP1320_RP01 |Add Visual Studio 14 toolchain to tools_def.template and prebuild.bat
|RPCO-0041|            |        |            |Add SignFv tool definitions.
|RPCO-0042|            |        |BP1320_RP01 |Increase stack size from 32768 to 262144.
|RPCO-0043|1205663322  |1375115 |BP1310_RP01 |Add PCD:PcdShadowPeiCore to specify whether shadow PeiCore is needed.
|RPCO-0044|1404256869  |1375255 |BP1410_RP01 |Remove IntelFrameworkPkg and IntelFrameworkModulePkg from Royal Park effective BP 1.4
|RPCO-0045|1206618408  |1375266 |BP1330_RP01 |Implement Initial draft of FSP 2.0 - Part6 "FSP Wrapper utilizes FSP2.0 functionality"
|RPCO-0046|2504623     |        |            |HDD security feature accepting non alphanumeric char as password.
|RPCO-0047|1404331317  |N/A     |N/A         |HSTI optimization platform driver is not present in SKL/KBL causing 600+ ms of extra post time. (non-override)
|RPCO-0048|1205580536  |        |BP1310_RP01 | Security: UEFI Secure Boot enablement fails, bios not allowing PK certificate enrollment.
|RPCO-0049|1206609504  |        |BP1310_RP01 |Century change in date field in BIOS Setup does not work properly.
|RPCO-0050|1206407602  |        |BP1310_RP01 |MOR bit update locking - Win10 VSM requirement.
|RPCO-0051|1206681086  |        |BP1310_RP01 |Extend TPerReset to the encrypted drives on the onboard storage controllers.
|RPCO-0052|1404308237  |        |            |When TPM2_Startup (State) fails, BIOS incorrectly handling the failure path.
|RPCO-0053|1206666622  |        |            |Add ability to delay/skip HDD unlock in HddPasswordDxe module. Required for SecureErase using HDD password supplied thru WSMAN command.
|RPCO-0054|1404339595  |        |BP1320_RP01 |Fix potentially uninitialized variable usage and enforce it moving forward.
|RPCO-0055|1205572150  |N/A     |            |Enhance efivarstore variables on being able to modify variable attributes.
|RPCO-0056|1206727659  |        |BP1310_RP01 |Signal SmmIplGuidedEventNotify on gEfiEventExitBootServicesGuid and gEfiEventReadyToBootGuid.
|RPCO-0057|1206912312  |        |            |Adding GCC Link Time Optimization (LTO).
|RPCO-0058|1206679038  |        |BP1320_RP01 |ShellPkg: Fix Shell fail with redundant space following delay number.
|RPCO-0059|1604004841  |        |BP1320_RP01 |BIOS support for DebugLib instance based on UefiDebugLibDebugPortProtocol.
|RPCO-0060|1404256869  |1375255 |BP1330_RP01 |Remove IntelFrameworkPkg and IntelFrameworkModulePkg from Royal Park effective BP 1.4
|RPCO-0061|1206654072  |1374890 |BP 1.4.1.0  |Switch to NASM in Royal Park
|RPCO-0062|1205650082  |N/A     |            |NPK/SVEN-TX: Support Catalog debug messages (replace ASCII strings with enums)
|RPCO-0063|1207152792  |N/A     |N/A         |[RP1320] Diagnostic Mode: Dispatch events and FSP debug messages. (/Override/DiagnosticsMode/...
|RPCO-0064|1207484728  |1375261 |BP1330_RP01 |Request to make EFI_TCG_FINAL_LOG_AREA_SIZE configurable
|RPCO-0065|1207559816  |N/A     |BP1330_RP01 |Remove 1.x interfaces from both IntelFspPkg and IntelFspWrapperPkg
|RPCO-0066|1207576971  |N/A     |BP1330_RP01 |Align the IntelFspPkg and IntelFspWrapperPkg to FSP v2.0 Spec
|RPCO-0067|1207892209  |N/A     |BP1410_RC03 |Implement BIOS side of NPK debugger control interface (scratch pad bits in SCRPD2 )
|RPCO-0068|1304650909  |N/A     |            |OS state not restored after 1st resume from S4.
|RPCO-0069|1209358671  |N/A     |BP1410_RC03 |Add smbios record size check in DxeSmbiosDataHobLib to avoid adding smbios tables incorrectly.
|RPCO-0071|1209579297  |N/A     |BP1410_RC03 |Work around for avold system hang while enabling enabling Smm Page Level Protection (CopperPoint)
|RPCO-0072|1804707972  |N/A     |BP1410_RC03 |Failed to unlock SSD with ATA password after Sx
|RPCO-0073|1209654069  |N/A     |BP1410_RC03 |RS2 HLK Requirement for Security: NoPPIClear must be set to TRUE or PPRequiredForClear must be set to FALSE
|RPCO-0074|1209680784  |N/A     |BP1410_RC03 |TraceHubDebugWrite() is not supported if module has already built a gEfiCallerIdGuid Guid Hob
|RPCO-0075|1209826921  |N/A     |N/A         |Add a layer between DebugLib and debug port
|RPCO-0076|1504390093  |N/A     |            |Memory access violation in Legacy USB SMI handler.
|RPCO-0077|22058464    |N/A     |BP 1.4.1.0  |Apply a patch from SSG to un-block NX bit set for those non-SMM range in SMM mode.
|RPCO-0078|1406517360  |N/A     |            |InitializeUsb3DebugPort () may break DCI functionality
|RPCO-0079|1604539304  |N/A     |            |Update Preboot WiFi/BT binaries for OEMs
|RPCO-0080|1504598696  |N/A     |            |Enable GCC compilation for CFL/CNL/ICL source tree
|RPCO-0081|220738527   |1375568 |            |Fix error in CPU frequency calculation
|RPCO-0082|1604586084  |1375571 |BP1510_RP02 |UEFI-Wi-Fi(BIOS): Ping command fails to give output sporadically in EDK shell
|RPCO-0083|1604586074  |N/A     |BP1510_RP02 |UEFI-WiFi(BIOS): DHCP IP not taken sporadically after connecting to Wi-Fi access point
|RPCO-0084|1604613622  |N/A     |            |CFL+CNP BIOS: Gfx PEIM Merge Tools are not working
|RPCO-0085|2201959647  |1375591 |BP1510_RP02 |Pinging fails after switching Network in Connection Manager/EDK Shell
|RPCO-0086|1504688413  |N/A     |N/A         |Remove the IntelFrameworkModulePkg and IntelFrameworkPkg usage from CNL and later projects
|RPCO-0089|220818230   |1375528 |BP 1.4.3.0  |Initialize APs in SMM on S3 resume with only one INIT-SIPI-SIPI instead of 2.
|RPCO-0090|2201619209  |1375606 |BP 1.4.3.0  |If ins/outs is executing on a thread, a page fault will occur if SMI is generated.
|RPCO-0091|1504706940  |1375548 |BP 1.4.3.0  |Fix Linker illegal text relocation issue for Xcode toolchain.
|RPCO-0093|1604334659  |N/A     |N/A         |Bios Conf Tool Verification Failed for TPM devices
|RPCO-0094|1805888240  |N/A     |N/A         |Cannot enter RST Legacy OROM UI using USB keyboard
|RPCO-0095|1406659399  |1375596 |            |Changing TPM2 recieve message to only request tpm suspend on S3 resume
|RPCO-0096|1805160582  |N/A     |N/A         |Port new UFS driver behavior during controller initialization to platform override.
|RPCO-0097|2202458542  |1375619 |BP 1.6.1.0  |EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem() and EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollIo() are taking more time than given delay for polling.
|RPCO-0098|2203568947  |1375625 |BP1520      |Untested Memory Not Covered by SMM Protection
|RPCO-0099|1506123397  |N/A     |            |SplitFspBin.py update to support X64 driver in FSP binary
|RPCO-0100|            |N/A     |            |Disabled auto inline in MicroSecondDelay() to avoid VS2017 build error.
|RPCO-0101|2204468023  |1375680 |N/A         |[ICL HaT] BIOS may write uninitialized MOR variable
|RPCO-0102|2204790744  |1375728 |BP 1.6.1.0 or 1.7.1.0 |BaseTools: Support Array and C code style initialization in Structure PCD for GPIO setting
|RPCO-0103|            |        |BP 1.6.1.0 or 1.7.1.0 |DscBuildData.py : fix bug in setting a value of a pcd from another pcd
|RPCO-1000|1206750264  |1375262 |N/A         |Add DEC "UserExtensions" section support for PackageDocumentTool. Override Location:UtilitiesInternalOnly\PackageDocumentTools\
|RPCO-1001|1206772321  |N/A     |N/A         |Utilize PackageDocumentTool for SiPkgApi documentation. Override Location:UtilitiesInternalOnly\PackageDocumentTools\
|RPCO-0092|1209512627  |N/A     |N/A         |Add PTT specific override