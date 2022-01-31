CLS
@ECHO OFF
gcc main.cpp -o bin/main -Isrc -lstdc++ -lWs2_32 -D_GLIBCXX_USE_CXX11_ABI=0
bin\\main