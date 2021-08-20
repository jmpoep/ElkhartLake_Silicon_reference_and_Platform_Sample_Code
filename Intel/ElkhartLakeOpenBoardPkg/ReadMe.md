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
1. Open command window, go to the WORKSPACE.
2. Go to the board folder you want to build. ex. Type `cd Intel\ElkhartLakeOpenBoardPkg\ElkhartLakeSimics`.
3. Type `SetEdk2Env.bat`.
4. Type `prep` and make prebuild finish for debug build, `prep r` for release build.
5. Type `bld` to build ElkhartLake BIOS image.
6. BIOS is generated at `WORKSPACE\RomImages\BOARDNAME.fd`.
7. Whole Image for Simics is generated at `WORKSPACE\RomImages\MinPlatform\ElkhartLakeSimicsLP\EHL_Simics_DEBUG.bin`

The user can run FITC tool to build full image for flash (BIOS + ME + DESC). The user can also burn the BIOS image to correct flash region directly.

##Known limitations
1. This firmware project has only been validated on Simics.
2. This firmware project has only been validated booting to Microsoft Windows 10 x64 with AHCI mode.
3. This firmware project has only been validated using the Microsoft Visual Studio 2015 compiler.
