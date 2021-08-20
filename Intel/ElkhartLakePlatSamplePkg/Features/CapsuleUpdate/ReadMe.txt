This file describe how to build system firmware Capsules with ElkhartLakePlatSamplePkg\capsulebuild.bat

There are several Capsule targets supported:
1. Monolithic Capsule      - A single Capsule to update multiple components on IFWI
   ESRT entry GUID: 7FEB1D5D-33F4-48D3-BD11-C4B36B6D0E57
   Involved payloads: ClientBios.rom (must be a valid BIOS ROM)
                      Me.bin         (could be dummy file started with $DUM. if it's dummy, ME FW update would be skipped)
                      Pdt.bin        (could be dummy file started with $DUM. if it's dummy, PDT update would be skipped)

2. Standalone BIOS Capsule - A Capsule to update BIOS only.
   ESRT entry GUID: 6C8E136F-D3E6-4131-AC32-4687CB4ABD27
   Involved payloads: ClientBios.rom (must be a valid BIOS ROM)

3. Standalone ME Capsule   - A Capsule to update ME FW only.
   ESRT entry GUID: 0EAB05C1-766A-4805-A039-3081DE0210C7
   Involved payloads: Me.bin (must be a valid ME binary)

4. Standalone ISH PDT Capsule - A Capsule to update ISH PDT only.
   ESRT entry GUID: 76CA0AD8-4A14-4389-B7E5-FD88791762AD
   Involved payloads: Pdt.bin (must be a valid PDT binary)

   P.S. Current PDT Version is always 5 which causes some difficulties of validation:
          1. User is hard to tell the difference between different PDT binaries.
          2. WOS would skip PDT Capsule upgrade with the same FW version.
        So we use a virtual version stored in UEFI variable to represent PDT version on current platform.
        It means user needs to assign a virtual PDT version when creating PDT FMP Capsule image.

By default capsulebuild.bat generates a Monolithic Capsule.
See [How to Use] below for further details.

[Pre-Requisites]
1. Windows operating system
2. Having Python 2.7 installed
3. If you want to test Capsule update in Windows, having WDK/SDK installed to generate Windows update driver.
   The script to generate Windows update driver requires below files:
   a. signtool.exe under
      C:\Program Files (x86)\Windows Kits\10\bin\x64
      or
      C:\Program Files (x86)\Windows Kits\8.1\bin\x64
      or
      C:\Program Files (x86)\Windows Kits\10\bin\*\x64

   b. Inf2Cat.exe under
      C:\Program Files (x86)\Windows Kits\10\bin\x86
      or
      C:\Program Files (x86)\Windows Kits\10\bin\*\x86

[How to Use]
1. Replace relative payload images (e.g., ClientBios.rom, Pdt.bin, Me.bin and etc.) of your interests with the real ones in this directory.
2. Under ElkhartLakePlatSamplePkg, open Command prompt, run:
     capsulebuild [BIOS type:SPI/BFX][target:all/bios/me/pdt][-mever ^<ME Build Version^>][-pdtver ^<PDT Version^>][help]

        BIOS type   BIOS type to build capsule: SPI/BFX.
                    default: If BIOS type is NOT assigned, BIOS rom file is SPI rom.
                             Buid SPI capsule.
                    BFX    : BIOS rom file is BFX rom. Buid BFX capsule.

        target   Assign Capsule build targets: all/bios/me/pdt, default is building Monolithic Capsule

                 default: If target is NOT assigned, build Monolithic Capsule

                 all    : Build Monolithic Capsule + all standalone Capsules
                 bios   : Build Standalone BIOS Capsule
                 me     : Build Standalone ME Capsule
                 pdt    : Build Standalone PDT Capsule

        -mever   To indicate ME Build version of CapsuleUpdateConfig\Me.bin.
                 It's mandatory if building capsules with [all] or [me] target
        -pdtver  To assign a virtual PDT version of CapsuleUpdateConfig\Pdt.bin.
                 It's mandatory if building capsules with [all] or [pdt] target
                 e.g., "capsulebuild.bat pdt -pdtver 2"
        Note*: As of now we dont have the knowledge to parse ME version from a given ME FW image.
               So ME version needs to be provided manually by the user.

3. If the build is success, EhlSystemFwXXXX.cap would be observed in CapsuleOutput directory.
4. Windows Update driver (if generated) would be found in CapsuleOutput\WindowsCapsule

Examples:
   a. capsulebuild.bat
        => Default build. Build a Monolithic capsule. EhlSystemFwMono_xxxx.cap would be observed in CapsuleOutput directory.
           Windows update driver (if generated) would be found in CapsuleOutput\WindowsCapsule\Monolithic

   b. capsulebuild.bat bios me -mever 1033
        => Build both standalone ME capsule and BIOS capsule. 1033 indicates ME build verion of Me.bin
           EhlSystemFwMe_1033.cap and EhlSystemFwBios_xxxx.cap would be observed in CapsuleOutput directory.
           Windows update driver (if generated) would be found in CapsuleOutput\WindowsCapsule\Me and CapsuleOutput\WindowsCapsule\Bios

   c. capsulebuild.bat all -mever 1033
        => Build Monolithic Capsule and standalone BIOS/ME Capsules. 1033 indicates ME build verion of Me.bin
           EhlSystemFwMono_xxxx.cap, EhlSystemFwBios_xxxx.cap and EhlSystemFwMe_1033.cap would be observed in CapsuleOutput directory.
           Windows update drivers (if generated) would be found in CapsuleOutput\WindowsCapsule

[Apply Capsule in UEFI Shell]

1. Put Capsule file and CapsuleApp.efi in USB storage.
2. In EFI Shell, switch file system to the USB storage (e.g. Fs0:)
3. fs0:> CapsuleApp <Capsule file name (e.g. EhlSystemFwXXXX.Cap)>
4. System should restart
5. After reboot, a progress bar which indicates the update is in progress should be observed with Intel logo.

[Apply Capsule update package in Windows]

Pre-Requisites:
        1. Disable Secure Boot in BIOS setup question to allow firmware upgrade.
        2. Please check the system date and time if it is correct or not.
        3. Set "testsigning" on through bcdedit using below admin command prompt:
                "bcdedit /set testsigning on" and reboot the system.
        4. Confirm the changes by typing "bcdedit" in cmd prompt. Below status should be observed:
                  testsigning                       Yes

Installing the Firmware driver package:
        1. Copy EhlSystemFwXXXX directory to SUT
        2. Do the below things to install the certificate file.
                  a. Double click on the security catalog file (cat file) from package.
                  b. Click on View Signature.
                  c. Click on View Certificate followed by clicking on Install Certificate.
                  d. For Store Location, choose "Local Machine". Click next and Manually browse and select "Trusted Root Certification Authorities".
                  e. Click OK and next to install the certificate on the system for one time.
                  f. You should get the popup message "The Import was Successful"
        3. Enter to driver package created. Run "pnputil -i -a EhlSystemFwXXXX.inf" as Administrator. Then restart system.