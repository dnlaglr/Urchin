@echo off
set BINDIR=C:\Program Files\Urchin
set URCHINBIN=urchin\bin\urchin.exe

echo "Installing Urchin..."

mkdir "%BINDIR%"
copy "%URCHINBIN%" "%BINDIR%\urchin.exe"

setlocal enabledelayedexpansion
set "PATH_FOUND=0"

for %%i in ("%PATH:;=" "%") do (
  if "%%i"=="%BINDIR%" (
    set "PATH_FOUND=1"
  )
)

if "!PATH_FOUND!"=="0" (
  setx PATH "%PATH%;%BINDIR%"
  echo "Updated PATH in system. Restart your command prompt to run Urchin from any directory."
)

echo "Installation complete! You can now run urchin '<command>' from any directory!"
