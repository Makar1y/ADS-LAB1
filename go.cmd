if %USERDOMAIN% == DESKTOPF goto :HomePC


@REM MIF pc
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :run


:HomePC
call D:\\Programs\\MSYSS2\\msys2_shell.cmd -mingw64 -defterm -no-start -here -c make


:run
pause
test.exe