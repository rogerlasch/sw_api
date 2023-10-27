@echo off
cd build
cl /c /MP /nologo  /EHsc /std:c++latest /D_WIN32_WINNT=0x0601 /D_SILENCE_ALL_CXX20_DEPRECATION_WARNINGS /I "D:\github\vcpkg\installed\x86-windows\include" ..\*.cpp ..\src\*.cpp
link /nologo /INCREMENTAL:NO /out:"..\main.exe" /MACHINE:X86 /MANIFEST:NO /LIBPATH:"D:\github\vcpkg\installed\x86-windows\lib" *.obj pqxx.lib
cd ..
