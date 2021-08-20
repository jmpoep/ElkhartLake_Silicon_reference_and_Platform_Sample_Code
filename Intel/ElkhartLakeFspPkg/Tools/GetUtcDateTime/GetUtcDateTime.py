## @ GetUtcDateTime.py
#
# Copyright (c) 2019, Intel Corporation. All rights reserved.<BR>
# This program and the accompanying materials are licensed and made available under
# the terms and conditions of the BSD License that accompanies this distribution.
# The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php.
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
##
import sys
import datetime

def Usage():
    print ("GetUtcDateTime Version 0.1")
    print ("Usage:")
    print ("    GetUtcDateTime --year: Return year YYYY (ascii) of now(UTC)")
    print ("    GetUtcDateTime --date: Return date MMDD (ascii) of now(UTC)")
    print ("    GetUtcDateTime --time: Return time HHMM (ascii) of now(UTC)")

def Main():
  if len(sys.argv) == 1:
    Usage()
    return 0

  today = datetime.datetime.utcnow()
  if sys.argv[1].strip().lower() == "--year":
    ReversedNumber = str(today.year)[::-1]
    print (''.join(hex(ord(HexString))[2:] for HexString in ReversedNumber))
    return 0
  if sys.argv[1].strip().lower() == "--date":
    ReversedNumber = str(today.strftime("%m%d"))[::-1]
    print (''.join(hex(ord(HexString))[2:] for HexString in ReversedNumber))
    return 0
  if sys.argv[1].strip().lower() == "--time":
    ReversedNumber = str(today.strftime("%H%M"))[::-1]
    print (''.join(hex(ord(HexString))[2:] for HexString in ReversedNumber))
    return 0
  else:
    Usage()
    return 0

if __name__ == '__main__':
    sys.exit(Main())