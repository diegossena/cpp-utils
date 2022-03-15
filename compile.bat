CLS
@ECHO OFF
gcc src/main.cpp -o bin/main -Imodules -Isrc -lstdc++ -lD3D11 -ld3dcompiler
IF %ERRORLEVEL% == 0 (
  cd bin
  main
  cd..
)
:: -lstdc++ -lWs2_32 -D_GLIBCXX_USE_CXX11_ABI=0