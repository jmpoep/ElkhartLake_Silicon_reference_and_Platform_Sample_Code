#! python3
"""
FindPCD.py

Search for given PCD in provided DSC files, and returns as below:
return 0 if the PCD is found and defined FALSE.
return 1 if the PCD is found and defined TRUE.
return 2 if the PCD is not found.

License
Copyright (c) 2017 Intel Corporation. All rights reserved. This software
and associated documentation (if any) is furnished under a license and may
only be used or copied in accordance with the terms of the license. Except as
permitted by such license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any form or by
any means without the express written consent of Intel Corporation.
"""

import sys
import os
import argparse

from version import __version__

def main():
    opts = get_args(__version__)
    pcd_dict = {}
    opts.files.reverse()

    for file_name in opts.files:
        # Skip searching if input file type is not *.dsc.
        file_type = os.path.splitext(file_name)[1].strip('.').lower()
        if not file_type == 'dsc':
            print("\n")
            print("FindPCD WARNING: {} is not a dsc file, the file will not be searched!!!".format(file_name))
            continue

        with open(file_name, 'r') as infile:
            lines = infile.readlines()
        line_ptr = 0
        while line_ptr < len(lines):
            if_stack = []
            line = lines[line_ptr].strip()
            # Skip if "#" is found as the first character, the line is commented.
            if line.find('#') == 0:
                line_ptr += 1
                continue
            # Skip if the line is an empty line.
            if not line:
                line_ptr += 1
                continue
            # Process conditional statements.
            if line.find('!if') == 0:
                # Push if condition line_ptr into stack for nested conditional statement processing.
                if_stack.append(line_ptr)
                while len(if_stack) > 0:
                    line_ptr += 1
                    line = lines[line_ptr].strip()
                    # Skip the commented line.
                    if line.find('#') == 0:
                        continue
                    if line.find('!if') == 0:
                        if_stack.append(line_ptr)
                        continue
                    # Pop if condition line_ptr to form a block with endif line.
                    if line.find('!endif') == 0:
                        else_ptr = -1
                        if_ptr = if_stack.pop()
                        endif_ptr = line_ptr
                        line_ptr = if_ptr
                        # Search for "!else" statement existence.
                        while line_ptr < endif_ptr:
                            if not lines[line_ptr].find('!else') == -1:
                                else_ptr = line_ptr
                            line_ptr += 1
                        # Clean and process the if condition statement line.
                        if_line = lines[if_ptr].replace('!if', '').rstrip('\n').strip()
                        if_line = if_line.replace('(', '( ').replace(')', ' )').replace('AND', 'and').replace('OR', 'or')
                        if_line = if_line.replace('TRUE', '"TRUE"').replace('FALSE', '"FALSE"')
                        # Remove comment from the tail if it exists.
                        if not if_line.find('#') == -1:
                            if_line = if_line[:if_line.find('#')].strip()
                        if_array = if_line.split(' ')
                        if_line = ''
                        for index in range(len(if_array)):
                            if not if_array[index].find('Pcd') == -1:
                                if_array[index] = 'pcd_dict.get("{}")'.format(if_array[index])
                            if if_array[index].find('$') == 0:
                                if_array[index] = if_array[index].lstrip('$')
                                if_array[index+1] = 'os.getenv("{}")'.format(if_array[index+1])
                                if_array[index+4] = '"{}"'.format(if_array[index+4])
                        if_line = ' '.join(if_array)
                        # Check condition statement to determine if the block should be removed.
                        check = eval(if_line)
                        if check == True:
                            lines[if_ptr] = ''
                            # No 'else' statement found in the line.
                            if else_ptr == -1:
                                lines[endif_ptr] = ''
                            else:
                                line_ptr = else_ptr
                                while line_ptr <= endif_ptr:
                                    lines[line_ptr] = ''
                                    line_ptr += 1
                        else:
                            line_ptr = if_ptr
                            if else_ptr == -1:
                                while line_ptr <= endif_ptr:
                                    lines[line_ptr] = ''
                                    line_ptr += 1
                            else:
                                while line_ptr <= else_ptr:
                                    lines[line_ptr] = ''
                                    line_ptr += 1
                                lines[endif_ptr] = ''
                        line_ptr = endif_ptr
                line_ptr = if_ptr
                continue

            pcd_name, pcd_value = line.split('|')
            pcd_name = pcd_name.strip()
            pcd_value = pcd_value.rstrip('\n').strip()
            if not pcd_value.find('#') == -1:
                pcd_value = pcd_value[:pcd_value.find('#')].strip()
            pcd_dict[pcd_name] = pcd_value

            line_ptr += 1

    if pcd_dict.get(opts.pcd_name) is None:
        print("FindPCD Message: No PCD Found!!!")  # DEBUG
        sys.exit(2)
    if pcd_dict[opts.pcd_name] == 'TRUE':
        print("FindPCD Message: {} | {}".format(opts.pcd_name, pcd_dict[opts.pcd_name]))  # DEBUG
        sys.exit(1)
    elif pcd_dict[opts.pcd_name] == 'FALSE':
        print("FindPCD Message: {} | {}".format(opts.pcd_name, pcd_dict[opts.pcd_name]))  # DEBUG
        sys.exit(0)

def get_args(version_string):
    """Retrieves run time settings from command line.

    Returns:
        argparser object
    """
    # ***** Prepare argument parser *****
    parser = argparse.ArgumentParser(description='FindPCD {} (C) 2017 Intel(R) Corporation: Search dsc files for given PCD names.'.format(version_string))
    parser.add_argument(
            '-F', '--files',
            required=True,
            dest='files',
            nargs='+',
            help='Space separated list of files in current folder to be processed.')
    parser.add_argument(
            '-PCD', '--pcd_name',
            required=True,
            dest='pcd_name',
            help='PCD name to be searched in dsc files.')
    parser.add_argument(
            '-V', '--version',
            action='version',
            version="FindPCD {} (C) 2017 Intel(R) Corporation".format(version_string))

    args = parser.parse_args()
    return args

class InitError(Exception):
    def __init__(self, error_description):
        self.error_string = error_derscription
        return

if __name__ == "__main__":
    try:
        main()
    except InitError as e:
        print("FindPCD Execute Error!!!")
