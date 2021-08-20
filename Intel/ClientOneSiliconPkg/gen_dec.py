#! python
#
# This file contains 'Framework Code' and is licensed as such
# under the terms of your license agreement with Intel or your
# vendor. This file may not be modified, except as allowed by
# additional terms of your license agreement.
#
## @file
# gen_dec.py
#
# Copyright (c) 2017, Intel Corporation. All rights reserved.
# This software and associated documentation (if any) is furnished
# under a license and may only be used or copied in accordance
# with the terms of the license. Except as permitted by such
# license, no part of this software or documentation may be
# reproduced, stored in a retrieval system, or transmitted in any
# form or by any means without the express written consent of
# Intel Corporation.
#

import argparse
import re
import sys
import traceback

_section_regex = re.compile(r"^[^#]*?\[(.+)\](.*)")
_comment_strip = re.compile(r"^([^#]*)[#]*.*?")
_arch = ["IA32", "X64", "IPF", "ARM", "AARCH64", "EBC"]
try:
    basestring
except NameError:
    basestring = str

def _find_sections(dec_file, section_name, flatten=True):
    sections = []
    for section_entry in dec_file:
        if section_entry[0][0] == section_name or str(section_entry[0][0]).lower() == section_name.lower():
            sections.append(section_entry[1])
    if flatten:
        lines = []
        for section in sections:
            lines.extend(section)
        return lines
    else:
        return sections

def read_dec_file(dec_file_name):
    with open(dec_file_name) as f:
        lines = f.readlines()
    dec_file = [ ((0, ""), []) ]
    current_section = dec_file[0][1]
    for line in lines:
        data = _section_regex.match(line)
        if data:
            current_section = []
            dec_file.append(((data.group(1), data.group(2)), current_section))
        else:
            current_section.append(line)
    return dec_file

def get_formations(dec_file):
    forms = _find_sections(dec_file, "Products")
    formations = set()
    for formation in forms:
        data = _comment_strip.match(formation)
        if data:
            form = data.group(1)
        else:
            raise ValueError("regex error")
        form = form.strip()
        if form != "":
            formations.add(form)
    return formations

def generate_dec_file(dec_file, selected_formation):
    dec_file[-1][-1][-1] += '\n'
    if len(dec_file[0][1]) > 0 and dec_file[0][1][0].rfind("\r\n") != -1:
        line_ending = "\r\n"
    else:
        line_ending = "\n"
    formations = get_formations(dec_file)
    if selected_formation not in formations:
        raise ValueError("Formation {} does not exist".format(selected_formation))
    remaining_dec = []
    for section in dec_file:
        if section[0][0] != 0:
            if section[0][0].lower() == "products":
                continue
            headers = section[0][0].split(",")
            headers = [header.strip() for header in headers]
            remaining_headers = set()
            for header in headers:
                has_formation_specifier = False
                for formation in formations:
                    if header.endswith(".{}".format(formation)):
                        has_formation_specifier = True
                        if formation == selected_formation:
                            remaining_headers.add(header[0:header.rfind(".{}".format(formation))])
                if not has_formation_specifier:
                    remaining_headers.add(header)
            if set(headers) == remaining_headers:
                remaining_headers = headers
            if len(remaining_headers) > 0:
                new_header = "[{}]".format(", ".join(remaining_headers))
                create_section = True
                for new_section in remaining_dec:
                    if isinstance(new_section[0][0], basestring) and new_section[0][0].strip().lower() == new_header.strip().lower():
                        if section[0][1].lower().find("restricted") == -1 and section[0][1].lower().find("internalonly") == -1:
                            if new_section[0][1].lower().find("restricted") == -1 and new_section[0][1].lower().find("internalonly") == -1:
                                create_section = False
                                new_section[1].extend(section[1])
                if create_section:
                    remaining_dec.append(((new_header, section[0][1]), section[1]))
        else:
            remaining_dec.append(section)
    output = []
    for section in remaining_dec:
        if section[0][0] != 0:
            output.append("{}{}{}".format(section[0][0], section[0][1], line_ending))
        output.extend(section[1])
    return output

def main():
    try:
        parser = argparse.ArgumentParser()
        parser.add_argument("dec_file_template", help="Template file that will be used to generate the DEC file")
        parser.add_argument("selected_formation", help="Selects which form of the DEC file to create, must be present in the [Formations] section of the template")
        parser.add_argument("output_dec_file", nargs="?", help="Name of the DEC file to be created")
        if len(sys.argv) <= 2:
            parser.print_help()
            return 1
        parsed_args = parser.parse_args()
        output_dec_file = parsed_args.output_dec_file
        if output_dec_file is None:
            if parsed_args.dec_file_template.rfind(".template") != -1:
                output_dec_file = parsed_args.dec_file_template
                output_dec_file = output_dec_file[0:output_dec_file.rfind(".template")]
                if output_dec_file.rfind(".dec") == -1:
                    output_dec_file = "{}.dec".format(output_dec_file)
            else:
                print("Error: Input file extension is not .template, please specify output file name explicitly")
                return 1
        dec = generate_dec_file(read_dec_file(parsed_args.dec_file_template), parsed_args.selected_formation)
        #convert name from .template to .dec and save file
        with open(output_dec_file, "w") as out:
            out.write("".join(dec))
    except Exception as e:
        traceback.print_exc()
        print ("Error: {}".format(str(e)))
        return 1

if __name__ == "__main__":
    main()