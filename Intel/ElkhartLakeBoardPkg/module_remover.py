#! python3
#
# This file contains 'Framework Code' and is licensed as such
# under the terms of your license agreement with Intel or your
# vendor. This file may not be modified, except as allowed by
# additional terms of your license agreement.
#
## @file
# module_remover.py
#
# Copyright (c) 2018, Intel Corporation. All rights reserved.
# This software and associated documentation (if any) is furnished
# under a license and may only be used or copied in accordance
# with the terms of the license. Except as permitted by such
# license, no part of this software or documentation may be
# reproduced, stored in a retrieval system, or transmitted in any
# form or by any means without the express written consent of
# Intel Corporation.
#

import os
import subprocess
import sys

TITLE = "Module Remover"

def main():
    if len(sys.argv) < 2:
        print("Missing FMMT file argument!")
    if len(sys.argv) < 3:
        print("Missing FD file argument!")
    if len(sys.argv) < 4:
        print("Missing module arguments!")
        return 1

    fmmt_file = sys.argv[1]
    fd_file = sys.argv[2]

    print(TITLE)
    print()
    print("FMMT file: {}".format(fmmt_file))
    print("FD file: {}".format(fd_file))

    if not os.path.isfile(fmmt_file):
        print("FMMT file not found!")
        return 1
    if not os.path.isfile(fd_file):
        print("FD file not found!")
        return 1

    print("Modules:")
    file_list = sys.argv[3:]
    for file_name in file_list:
        print("  {}".format(file_name))
    print()

    #Initialize FMMT args for potential delete command
    fmmt_args = [fmmt_file, '-d', fd_file]
    files_found = False

    # Dump FD file and parse FV/file list
    print("Processing FD file ...")
    process = subprocess.run([fmmt_file, '-v', fd_file], stdout=subprocess.PIPE, encoding='utf-8')
    output = process.stdout.splitlines()
    for line in output:
        line = line.strip()
        if line.startswith("FV"):
            fv_number = line.split()[0]
        if line.count('\"') == 2:
            file_name = line.split('\"')[1]
            if file_name in file_list:
                files_found = True
                fmmt_args.append(fv_number)
                fmmt_args.append(file_name)

    for file_name in file_list:
        if file_name not in fmmt_args:
            print("Not found: {}".format(file_name))

    #Finalize FMMT args for delete command
    if files_found:
        fmmt_args.append(fd_file)
        print()
        print(" ".join(fmmt_args))
        process = subprocess.run(fmmt_args)

    return process.returncode

if __name__ == "__main__":
    sys.exit(main())
