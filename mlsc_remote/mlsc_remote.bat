@ECHO OFF
REM SET PATH=%PATH%;d:\Arduino\bin
SET currdir=%CD%

@echo off
setlocal

CALL :ARG-PARSER %*

set host=%ARG_H%
REM set /p host=Enter Hostname:


set host=%host:"=%

set directory=%host: =_%

echo "directory %directory%"

if "%ARG_U%" NEQ "1" (

	echo "Compiling %host%"

	arduino-cli compile -e --build-property "build.extra_flags=\"-DMLSC_CLIENT_HOSTNAME=\"%host%\"\"" -b esp8266:esp8266:nodemcuv2 --output-dir "build\%directory%" %CD%
)

echo "Uploading %host%"
setlocal
cd build
cd %directory%
for /f %%i in ('dir /b /a-d *.bin') do set RESULT=%%i
arduino-cli upload -v -b esp8266:esp8266:nodemcuv2 -p COM3  -i %RESULT%
endlocal


::*********************************************************
:: Parse commandline arguments into sane variables
:: See the following scenario as usage example:
:: >> thisfile.bat /a /b "c:\" /c /foo 5
:: >> CALL :ARG-PARSER %*
:: ARG_a=1
:: ARG_b=c:\
:: ARG_c=1
:: ARG_foo=5
::*********************************************************
:ARG-PARSER
    ::Loop until two consecutive empty args
    :loopargs
        IF "%~1%~2" EQU "" GOTO :EOF

        set "arg1=%~1" 
        set "arg2=%~2"
        shift

        ::Allow either / or -
        set "tst1=%arg1:-=/%"
        if "%arg1%" NEQ "" (
            set "tst1=%tst1:~0,1%"
        ) ELSE (
            set "tst1="
        )

        set "tst2=%arg2:-=/%"
        if "%arg2%" NEQ "" (
            set "tst2=%tst2:~0,1%"
        ) ELSE (
            set "tst2="
        )


        ::Capture assignments (eg. /foo bar)
        IF "%tst1%" EQU "/"  IF "%tst2%" NEQ "/" IF "%tst2%" NEQ "" (
            set "ARG_%arg1:~1%=%arg2%"
            GOTO loopargs
        )

        ::Capture flags (eg. /foo)
        IF "%tst1%" EQU "/" (
            set "ARG_%arg1:~1%=1"
            GOTO loopargs
        )
    goto loopargs
GOTO :EOF
