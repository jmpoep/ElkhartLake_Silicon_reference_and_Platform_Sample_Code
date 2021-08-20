import sys
import os
import glob
import fileinput
import array
from collections import namedtuple

# BIOS ID string format:
#
# $(BOARD_ID)$(BOARD_REV).$(BOARD_EXT).$(VERSION_MAJOR).$(BUILD_TYPE)$(VERSION_MINOR).YYMMDDHHMM
#     BoardId_Rev           BoardExt     VersionMajor          BuildType_VerMinor     TimeStamp
#
# Example: "TRFTCRB1.000.0008.D03.1501301017"
#
BiosIdStringList = namedtuple('BiosIdStringList', ['BoardId_Rev', 'BoardExt', 'VersionMajor', 'BuildType_VerMinor', 'TimeStamp'])

BiosIdSignature = "$IBIOSI$"

def get_bios_id_from_bin(binfile, biosidfile):

  # open binfile
  fin = open(binfile, "rb")

  # Read file to buffer
  buffer = fin.read()

  # get the offset of BiosIdSignature "$IBIOSI$"
  bios_id_sig_begin = buffer.find(BiosIdSignature)
  if bios_id_sig_begin == -1:
    print "Can not find BiosId signature in %s" % binfile
    fin.close()
    return -1

  # get the offset of BiosIdString
  bios_id_str_begin = bios_id_sig_begin + len(BiosIdSignature)

  # get BiosIdString buffer
  bios_id_str_bfr = buffer[bios_id_str_begin:bios_id_str_begin+64] # 64 = sizeof (BIOS_ID_STRING) - sizeof (NullTerminator)

  # create an unicode type arrary to access BiosIdString buffer...dont know how this wroks
  unicode_array = array.array('u', bios_id_str_bfr).tounicode()

  # seperate BiosIdString by '.' to bios_id_string_list
  bios_id_string_list = BiosIdStringList._make(unicode_array.split('.'))

  # Write to output file
  fout = open(biosidfile, "wb")
  fout.write("BOARD_REV     = %s\r\n" % bios_id_string_list.BoardId_Rev[7])
  fout.write("BUILD_TYPE    = %s\r\n" % bios_id_string_list.BuildType_VerMinor[0])
  fout.write("VERSION_MAJOR = %s\r\n" % bios_id_string_list.VersionMajor)
  fout.write("VERSION_MINOR = %s\r\n" % bios_id_string_list.BuildType_VerMinor[1:3])
  fout.write("BOARD_ID      = %s\r\n" % bios_id_string_list.BoardId_Rev[0:7])
  fout.write("BOARD_EXT     = %s\r\n" % bios_id_string_list.BoardExt)
  if bios_id_string_list.BoardExt[0:1] == "D":
    fout.write("BUILD_TARGET  = %s\r\n" % "DEBUG")
  else:
    fout.write("BUILD_TARGET  = %s\r\n" % "RELEASE")

  fin.close()
  fout.close()
  return 0

###################################################################################################
# Main
###################################################################################################

def main():
  if len(sys.argv) != 3:
    print "incorrent number of arguments"
    return 1

  ret = get_bios_id_from_bin(sys.argv[1], sys.argv[2])

  if ret != 0:
    return 1
  return 0

if __name__ == '__main__':
    sys.exit(main())
