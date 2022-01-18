@ECHO OFF
SET PATH=%PATH%;d:\Arduino\bin
SET currdir=%CD%
set list=11 12 15 20
SET ip=20
set /p ip=Enter IP ( %list% ):


if %ip% == 1 (

	for %%n in ( %list% ) do (
		@SET "builddir=build\%%n\mlsc_all.ino.bin"
		if NOT EXIST "%builddir%" (
			echo "Compiling %%n"
			CALL :Compile %%n
		)
	)
	
	for %%n in ( %list% ) do (
		CALL :Upload %%n
	)
	
	goto:eof
)


REM @SET "builddir=build\%ip%\mlsc_all.ino.bin"

REM IF NOT EXIST %builddir% (
	echo "Compiling %ip%"
	CALL :Compile %ip%
REM )

CALL :Upload %ip%
goto:eof

::


:Compile
arduino-cli compile -e --build-property "build.extra_flags=\"-DMLSC_CLIENT_IP=%~1\"" -b esp8266:esp8266:nodemcuv2 --output-dir "build\%~1" %CD%
EXIT /B 0

:Upload
echo "Uploading %~1"
setlocal
cd build
cd %~1
for /f %%i in ('dir /b /a-d *.bin') do set RESULT=%%i
arduino-cli upload -v -b esp8266:esp8266:nodemcuv2 -p COM3  -i %RESULT%
endlocal
EXIT /B 0
