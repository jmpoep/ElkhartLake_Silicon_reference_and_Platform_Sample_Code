# **EDK II Minimized firmware for Intel(R)ElkhartLake platforms**

##Features
The Minimized ElkhartLake provides the minimal feature of the ElkhartLake BIOS.

## **Windows Build Instructions**

### Pre-requisites

* Microsoft Visual Studio.
  - Visual Studio 2015 recommended and is used in the examples below.
* ASL compiler: Available from http://www.acpica.org
  - Install into `C:\ASL` to match default `tools_def.txt` configuration;
  - or update `tools_def.txt` to match ASL compiler location.
* NASM assembler:  Available from: http://www.nasm.us/
  - Install into `C:\NASM` to match default `tools_def.txt` configuration;
  - or update `tools_def.txt` to match NASM assembler location.
* Intel Binaries.
  - Please go to Intel Website to download essential binaries, and place into `ElkhartLakeOpenBoardPkg\Binaries`; or
    Contact your Intel window.

### Build
1. Type `cd Intel\ElkhartLakeBoardPkg`
2. Type 'prep' for debug build, 'prep r' for release build
3. Type 'bld' to build the Elkhart Lake BIOS image.
4. BIOS is generated in 'Build\ElkhartLakeBoardPkg\DEBUG_VS2015x86\FV\CLIENTBIOS.fd'
5. Create the IFWI using the BIOS ROM from Step 4 and the latest IFWI from the VP Simics PPR