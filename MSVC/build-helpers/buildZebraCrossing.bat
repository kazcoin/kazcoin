@ECHO ON
cd C:\MyProjects\BitcoinDeps\ZebraCrossing\
if %errorlevel% NEQ 0 goto ERRORCLEANUP
rmdir /s /Q build32
mkdir build32
cd build32
%HOMEPATH%\myapps\cmake\bin\cmake -G "Visual Studio 12" ..
if %errorlevel% NEQ 0 goto ERRORCLEANUP
set VisualStudioVersion=12.0
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\vcvars32.bat"
msbuild.exe  libzxing.vcxproj /p:Configuration="Debug" /p:Platform="Win32"
if %errorlevel% NEQ 0 goto ERRORCLEANUP
msbuild.exe  libzxing.vcxproj /p:Configuration="Release" /p:Platform="Win32"
if %errorlevel% NEQ 0 goto ERRORCLEANUP
cd C:\MyProjects\BitcoinDeps\ZebraCrossing\
if %errorlevel% NEQ 0 goto ERRORCLEANUP
rmdir /s /Q build64
mkdir build64
cd build64
%HOMEPATH%\myapps\cmake\bin\cmake -G "Visual Studio 12 Win64" ..
REM
REM now build 64 bit
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x64
msbuild.exe  libzxing.vcxproj /p:Configuration="Release" /p:Platform="x64"
if %errorlevel% NEQ 0 goto ERRORCLEANUP
msbuild.exe  libzxing.vcxproj /p:Configuration="Debug" /p:Platform="x64"
if %errorlevel% NEQ 0 goto ERRORCLEANUP
echo All finished!
pause
goto EOF
:ERRORCLEANUP
echo Something went wrong, please check the directories in this batch file!
pause
:EOF