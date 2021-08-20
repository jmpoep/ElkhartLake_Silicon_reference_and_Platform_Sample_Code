#GenNvs
##System Requirement:
1. Download and Install `Python 2.7`.
2. Add `Python 2.7` directory into system `path`.
3. Download and unzip `Python Lex-Yacc v3.4` from [http://www.dabeaz.com/ply/ply-3.4.tar.gz](http://www.dabeaz.com/ply/ply-3.4.tar.gz)
4. Move `./ply-3.4/ply/lex.py` and `./ply-3.4/ply/yacc.py` to be in the same folder as `GenNvs.py`.

##Execution:

    %WORKSPACE%\ClientSiliconPkg\Tools\GenNvs>python GenNvs.py -I InputFileName -O OutputRootDirectory -R FilterTag1 FilterTag2...

##Input .aht format:
- The first 3 line of .aht file should be the file name of .asl, the file name of .h and the structure name in .h file.
- There MUST be an `Offset()` right after each `#endif`, execpt it's in the end of structure.
- Support array and build switch.
###Sample.aht
    @ASLPATH=Results/ASLs/MyASL.asl
    @HPATH=Results/Hs/MyDefine.h
    @STRUCTURE_NAME=MY_STRUCTURE_NAME
    /** @file
        ...
    @copyright
        ...
    **/
      OperationRegion(...)
      Field(...)
      {
      VAR1, 16,      // [VariableName1] comment1
      Offset(10),
      SSS0, 32,      // [SSSSS,3        ] SSSSSID=0
      SSS1, 32,      //                   SSSSSID=1
      SSS2, 32,      // [SSSSS,End      ] SSSSSID=2
      #ifdef
      ...
      #else
      ...
      #endif
      Offset(50),
      ...
      #ifdef
      ...
      #else
      ...
      #endif
    }

##Output format:
###MyASL.asl
    /** @file
        ...
    @copyright
        ...
    **/
    Field(...){
        Offset(0),      VAR1, 16, // [VariableName1] comment1
        Offset(10),               // Offset(2) : Offset(9), Reserved bytes
        Offset(10),     SSS0, 32, // Offset(10),    SSSSSID=0
        Offset(14),     SSS1, 32, // Offset(14),    SSSSSID=1
        Offset(18),     SSS2, 32, // Offset(18),    SSSSSID=2
        #ifdef
        ...
        #else
        ...
        #endif
        Offset(50),               // Offset(3) : Offset(49), Reserved bytes
        ...
        #ifdef
        ...
        #else
        ...
        #endif
    }
###MyDefine.h 
    /**...
    copyright
    **/
    #ifndef _MY_DEFINE_H_
    #define _MY_DEFINE_H_

    #pragma pack (push,1)
    typedef struct {
        UINT16   VariableName1;               ///< Offset 0     comment1
        UINT8    Reserved0[8];                ///< Offset 2:9
        UINT32   SSSSS[3];                    ///< Offset 10      SSSSSID=0
                                              ///< Offset 14      SSSSSID=1
                                              ///< Offset 18      SSSSSID=2
        #ifdef
        ...
        UINT8    Reserved1[proper size];      ///< Offset x:49
        #else
        ...
        UINT8    Reserved2[proper size];      ///< Offset y:49     
        #endif
        ...
        #ifdef
        ...
        #else
        ...
        #endif
    } MY_STRUCTURE_NAME;
    #pragma pack(pop)
    #endif
##Trouble shooting:
- The tool throws out the first 50 characters of the unknown token if unknown tokens occurs while lexical analysis.
- The tool lists the following 10 tokens in the stack, when there are parsing errors which stops the construction of the parsing tree.
- For missing offset (after `#endif`) and offset overflow, the tool will show the location of the error directly.

##Converts Python script into executable Windows programs:
1. Execute `System Requirement` located at top of document.
2. Download and Install py2exe from [https://sourceforge.net/projects/py2exe/files/py2exe/0.6.9/](https://sourceforge.net/projects/py2exe/files/py2exe/0.6.9/). (`py2exe-0.6.9.win64-py2.7.amd64.exe` for x64 system) 
3. Execute `python Setup.py install` under `%WORKSPACE%\ClientSiliconPkg\Tools\GenNvs\`
4. Execute `python Setup.py py2exe` under `%WORKSPACE%\ClientSiliconPkg\Tools\GenNvs\`
5. Executable Windows programs is generated at `%WORKSPACE%\ClientSiliconPkg\Tools\GenNvs\dist\GenNvs.exe`. `%WORKSPACE%\ClientSiliconPkg\Tools\GenNvs\dist\python27.dll` is needed to be in the same folder as `GenNvs.exe` while executed.