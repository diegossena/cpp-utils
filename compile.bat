CLS
@ECHO OFF
gcc src/main.cpp -o bin/main -Imodules -lstdc++
IF %ERRORLEVEL% == 0 (
  bin\\main
  echo.
)
:: -lstdc++ -lWs2_32 -D_GLIBCXX_USE_CXX11_ABI=0