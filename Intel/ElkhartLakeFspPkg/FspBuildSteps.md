Intel is a trademark or registered trademark of Intel Corporation or its
subsidiaries in the United States and other countries.
*Other names and brands may be claimed as the property of others.
Copyright (c) 2016 - 2019, Intel Corporation. All rights reserved.

# FSP build steps for building ElkhartLake FSP binary

In order to build ElkhartLake FSP binary, following packages needs to be
downloaded along with the FSP SDK open source packages
* ElkhartLakeFspPkg --> contains all the ElkhartLake FSP Platform code
* ClientOneSiliconPkg --> contains all the ElkhartLake Silicon initialization code
* ClientSiliconPkg   --> contains common code for Client Silicon

Override folder under ElkhartLakeFspPkg takes precedence over the downloaded
versions of the packages. For example, when *build_rule.template* and
*tools_def.template* present under *ElkhartLakeFspPkg/Override/BaseTools/Conf*,
they have to be used before calling the *BuildFv.cmd* under ElkhartLakeFspPkg

Using BuildFsp.cmd (or BuildFsp.sh) is recommended.
Please refer to the usage notes by command - "BuildFsp.cmd /h"

## FSP SDK open source packages and hash versions
SDK open source packages may need some customization to build this version of FSP,
please contact Intel to get the github link for the EDK2 packages used.