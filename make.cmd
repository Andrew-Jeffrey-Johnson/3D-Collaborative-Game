@echo off
PATH="%CD%\mingw64;%CD%\mingw64\bin;%CD%\mingw64\lib\gcc\x86_64-w64-mingw32\10.1.0;%CD%\mingw64\include\c++\10.1.0;%CD%\mingw64\include"
if not exist "objects" mkdir objects
"mingw64\bin\make"
if not exist "3dcollaborativegame.exe" echo COMPILATION ERROR. UNSUCCESSFUL BUILD. CHECK YOUR CODE. 
if exist "3dcollaborativegame.exe" echo Compilation successful. You may now close this window.
pause