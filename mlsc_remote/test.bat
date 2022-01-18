@echo off
setlocal

CALL :ARG-PARSER %*

::Print examples
echo: R:	%ARG_R%
echo: H:   %ARG_H%


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