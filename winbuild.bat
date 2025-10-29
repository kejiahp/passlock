mkdir build 
cd build

cmake .. -G "Visual Studio 17 2022" -A x64
@if ERRORLEVEL 1 goto onError

cmake --build . --config Release
@if ERRORLEVEL 1 goto onError

goto onSuccess

:onError
@echo An error occured!

:onSuccess 
cd ..