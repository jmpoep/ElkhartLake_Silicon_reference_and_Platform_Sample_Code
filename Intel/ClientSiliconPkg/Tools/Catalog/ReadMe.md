#CatalogDebug v0.4
##System Requirement:
1. Download and Install `Python 2.7`.
2. Add `Python 2.7` directory into system `path`.
3. Download and Install `Python for Windows Extensions Build 220` from [https://sourceforge.net/projects/pywin32/files/pywin32/Build%20220/pywin32-220.win-amd64-py2.7.exe](https://sourceforge.net/projects/pywin32/files/pywin32/Build%20220/)

##Encode:
1. Modify `C:\Edk2\Conf\build_rule.txt`.
	###4-HEX
		<Command.MSFT, Command.INTEL>
            C:\Python27\python.exe C:\Edk2\ClientSiliconPkg\Tools\Catalog\CatalogEncoder.py -I ${src} -O ${src}.c -D $(BUILD_DIR)\CatalogDataBase.txt
            "$(CC)" /Fo${dst} $(CC_FLAGS) $(INC) ${src}.c
	###SHA-1
		<Command.MSFT, Command.INTEL>
            C:\Python27\python.exe C:\Edk2\ClientSiliconPkg\Tools\Catalog\CatalogEncoder.py -I ${src} -O ${src}.c -D $(BUILD_DIR)\CatalogDataBase.txt -M SHA-1
            "$(CC)" /Fo${dst} $(CC_FLAGS) $(INC) ${src}.c		

##Decode:
1. Decoded message `DecodedLog.log` will be generated under `$(BUILD_DIR)` once following step is executed.
	###4-HEX
		$(BUILD_DIR)> copy C:\Edk2\ClientSiliconPkg\Tools\Catalog\CatalogDecoder.py $(BUILD_DIR)
    	$(BUILD_DIR)> python CatalogDecoder.py -I EncodedLog.log -O DecodedLog.log -D CatalogDataBase.txt
	###SHA-1
		$(BUILD_DIR)> copy C:\Edk2\ClientSiliconPkg\Tools\Catalog\CatalogDecoder.py $(BUILD_DIR)
    	$(BUILD_DIR)> python CatalogDecoder.py -I EncodedLog.log -O DecodedLog.log -D CatalogDataBase.txt -M SHA-1