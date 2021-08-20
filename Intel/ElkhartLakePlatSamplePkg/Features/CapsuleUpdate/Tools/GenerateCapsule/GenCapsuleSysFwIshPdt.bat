@REM
@REM Usage:
@REM   GenCapsuleSysFwEc.bat [FMP Payload] [PDT Version] [Output Path]
@REM   FMP Payload  : The FMP payload used to create the Capsule image.
@REM   PDT Version  : PDT version in DEC format
@REM   Output Path  : The path for output Capsule image.
@REM
@echo off
setlocal
echo start

set FMP_CAPSULE_PAYLOAD=%1
set ISH_PDT_VERSION_DEC=%2
set FMP_CAPSULE_OUTPUT_DIR=%3

@REM
@REM A tricky way to covert FW Version from DEC to HEX
@REM
call cmd /c exit /b %ISH_PDT_VERSION_DEC%
set ISH_PDT_VERSION_HEX=0x%=exitcode%

@REM
@REM Setup enviroment variables
@REM
set FMP_CAPSULE_VENDOR=Intel
set FMP_CAPSULE_GUID=76CA0AD8-4A14-4389-B7E5-FD88791762AD
set FMP_CAPSULE_FILE=EhlSystemFwIshPdt_%ISH_PDT_VERSION_DEC%.cap
set FMP_CAPSULE_VERSION=%ISH_PDT_VERSION_HEX%
set FMP_CAPSULE_STRING=0.0.0.%ISH_PDT_VERSION_DEC%
set FMP_CAPSULE_NAME="Intel EHL ISH PDT %FMP_CAPSULE_STRING%"
set FMP_CAPSULE_LSV=0x00000000
set WINDOWS_CAPSULE_KEY=SAMPLE_DEVELOPMENT.pfx
set WINDOWS_CAPSULE_OUTPUT_DIR=%FMP_CAPSULE_OUTPUT_DIR%\WindowsCapsule\IshPdt

for %%i in ("%FMP_CAPSULE_FILE%") do SET WINDOWS_CAPSULE_NAME=%%~ni

if not exist "%FMP_CAPSULE_PAYLOAD%" exit /b 1

REM
REM Delete files if exist
REM
@del %FMP_CAPSULE_OUTPUT_DIR%\%FMP_CAPSULE_FILE% 1>NUL 2>&1
@del %WINDOWS_CAPSULE_OUTPUT_DIR%\%WINDOWS_CAPSULE_NAME%.* 1>NUL 2>&1

REM
REM Sign capsule using OpenSSL with EDK II Test Certificate
REM
call GenerateCapsule ^
  --encode ^
  -v ^
  --guid %FMP_CAPSULE_GUID% ^
  --fw-version %FMP_CAPSULE_VERSION% ^
  --lsv %FMP_CAPSULE_LSV% ^
  --capflag PersistAcrossReset ^
  --capflag InitiateReset ^
  --signing-tool-path=%WORKSPACE_PLATFORM%\%PLATFORM_PACKAGE%\Tools\OpenSSL ^
  --signer-private-cert=%WORKSPACE_CORE%\BaseTools\Source\Python\Pkcs7Sign\TestCert.pem ^
  --other-public-cert=%WORKSPACE_CORE%\BaseTools\Source\Python\Pkcs7Sign\TestSub.pub.pem ^
  --trusted-public-cert=%WORKSPACE_CORE%\BaseTools\Source\Python\Pkcs7Sign\TestRoot.pub.pem ^
  -o %FMP_CAPSULE_FILE% ^
  %FMP_CAPSULE_PAYLOAD%

copy %FMP_CAPSULE_FILE% %FMP_CAPSULE_OUTPUT_DIR%

REM
REM Generate Windows Capsule package with test key
REM
if exist "%WINDOWS_CAPSULE_KEY%" (
  CreateWindowsCapsule.py ^
    %WINDOWS_CAPSULE_NAME% ^
    %FMP_CAPSULE_STRING% ^
    %FMP_CAPSULE_GUID% ^
    %FMP_CAPSULE_FILE% ^
    %FMP_CAPSULE_VERSION% ^
    %FMP_CAPSULE_VENDOR% ^
    %FMP_CAPSULE_VENDOR% ^
    %FMP_CAPSULE_NAME% %WINDOWS_CAPSULE_KEY%

  xcopy /s/e/v/i/y WindowsCapsule %WINDOWS_CAPSULE_OUTPUT_DIR%
  rmdir /s /q WindowsCapsule
)

erase %FMP_CAPSULE_FILE%
