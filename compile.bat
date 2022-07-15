$host.UI.RawUI.BackgroundColor = "Black"
CLS
@ECHO OFF
gcc src/main.cpp -o bin/main -Imodules -Isrc -lstdc++ -std=c++20
IF %ERRORLEVEL% == 0 (
  cd bin
  main
  cd..
)
:: -lWs2_32 -lD3D11 -ld3dcompiler
:: -lstdc++ -lWs2_32 -D_GLIBCXX_USE_CXX11_ABI=0