ACPI Debug feature - an alternative to Port 80 and WinDBG

How it works:
Acpi Debug does this:
Opens a 64kb memory buffer during POST.
Patches the buffer address in SSDT ASL code.
Displays the address in SETUP for user reference.
Write strings or numbers to the buffer from ASL code with the ADBG method.

How to use it:
Enable the feature in SETUP->Advanced->ACPI DEBUG, and confirm gEfiBpCommonPkgTokenSpaceGuid.PcdAcpiDebugEnable is TRUE.
The ACPI ASL code must be instrumented with the debug method.
Strings up to 32 characters (shorter strings will be padded with Zero's, longer strings will be truncated)
Examples:
ADBG("This is a test.")
ADBG(Arg0)

DXE version: The bios engineer will read the strings from the buffer on the target machine with Read/Write Everything utility.
Alternatively, read strings from a host machine using the ITP.
SMM version: Check debug serial that would show debug strings.

Sample code for ADBG:
External (MDBG, MethodObj)
Method (ADBG, 1, Serialized)
{
  If (CondRefOf (MDBG)) // Check if ACPI Debug SSDT is loaded
  {
    Return (MDBG (Arg0))
  }
  Return (0)
}

